#include "primer.h"

#include <assert.h>

#include "stb/stretchy_buffer.h"

#include "symbols.h"
#include "config.h"
#include "typer.h"

// The primer performs `Lexical Analysis`, which involves traversing the AST, building a tree of
// contexts from linked list node stored in stack frames, and using this tree to look up symbols'
// types.
// At the end of Lexical Analysis, we have a typeP for each typed expression, ready for 
// typing/unification after analysis.
// Crucially, each context contains at most *one* definition.

struct Primer {
    Scope* root;

    // stackBegP and stackEndP track scopes for chains and functions that can be pushed or popped.
    Scope* currentScopeP;

    // each module context tree starts forward declarations of [all] its symbols.
    // the below 'beg' and 'end' pointers let us iterate through them.
    // - import statements can use these pointers to map to another module.
    // - `beg` points to the first INCLUSIVE element
    // - `end` points to the last INCLUSIVE element
    Scope* currentModuleDefBegP;
    Scope* currentModuleDefEndP;

    // the typer is used by the primer to create metatypes.
    Typer* typer;

    AstContext* contextStackSB;
    int contextStackCount;
};

struct Scope {
    Scope* parent;
    SymbolID defnID;
    void* valueTypeP;
    void* typingTypeP;
};

size_t allocatedScopersCount = 0;
Primer allocatedScopers[MAX_SCOPER_COUNT];
static size_t allocatedScopeStackFramesCount = 0;

static Primer* createPrimer(Typer* typer);
static void pushPrimerContext(Primer* primer, AstContext ctx);
static AstContext topPrimerContext(Primer* primer);
static void popPrimerContext(Primer* primer);

static size_t allocatedScopeCount = 0;
static Scope allocatedScopes[MAX_AST_NODE_COUNT];
inline static Scope* newScope(Scope* parent, SymbolID defnID, void* valueTypeP, void* typingTypeP);
static Scope* newRootScope(Typer* typer);
static Scope* defineSymbol(Scope* parent, SymbolID defnID, void* valueTypeP, void* typingTypeP);
static void* lookupSymbol(Scope* scope, SymbolID lookupID, AstContext context);
static void* lookupSymbolUntil(Scope* scope, SymbolID lookupID, Scope* endScopeP, AstContext context);

//
// Static implementation:
//

Primer* createPrimer(Typer* typer) {
    Primer* primer = NULL;
    if (allocatedScopersCount < MAX_SCOPER_COUNT) {
        primer = &allocatedScopers[allocatedScopersCount++];
    } else {
        return NULL;
    }
    primer->typer = typer;
    primer->contextStackSB = NULL;
    primer->contextStackCount = 0;
    primer->root = newRootScope(typer);
    primer->currentScopeP = primer->root;
    primer->currentModuleDefBegP = NULL;
    primer->currentModuleDefEndP = NULL;
    return primer;
}
void pushPrimerContext(Primer* primer, AstContext ctx) {
    int bufCount = sb_count(primer->contextStackSB);
    if (primer->contextStackCount == bufCount) {
        sb_push(primer->contextStackSB,ctx);
    }
    primer->contextStackCount++;
}
AstContext topPrimerContext(Primer* primer) {
    if (!primer->contextStackSB) {
        if (DEBUG) {
            printf("!!- Primer context stack empty. Defaulting to value.\n");
        } else {
            assert(0 && "Primer context stack empty.");
        }
        return ASTCTX_VALUE;
    }
    return primer->contextStackSB[primer->contextStackCount-1];
}
void popPrimerContext(Primer* primer) {
    primer->contextStackCount--;
}

inline Scope* newScope(Scope* parent, SymbolID defnID, void* valueTypeP, void* typingTypeP) {
    Scope* scopeP = &allocatedScopes[allocatedScopeCount++];
    scopeP->parent = parent;
    scopeP->defnID = defnID;
    scopeP->valueTypeP = valueTypeP;
    scopeP->typingTypeP = typingTypeP;
    return scopeP;
}
Scope* newRootScope(Typer* typer) {
    Scope* root = NULL;
    
    root = newScope(root, Symbol("u8"), NULL, GetIntType(typer,INT_8));
    root = newScope(root, Symbol("u16"), NULL, GetIntType(typer,INT_16));
    root = newScope(root, Symbol("u32"), NULL, GetIntType(typer,INT_32));
    root = newScope(root, Symbol("u64"), NULL, GetIntType(typer,INT_64));

    root = newScope(root, Symbol("f32"), NULL, GetFloatType(typer,FLOAT_32));
    root = newScope(root, Symbol("f64"), NULL, GetFloatType(typer,FLOAT_64));
    
    return root;
}
Scope* defineSymbol(Scope* parent, SymbolID defnID, void* valueTypeP, void* typingTypeP) {
    return (Scope*)newScope(parent, defnID, valueTypeP, typingTypeP);
}
void* lookupSymbol(Scope* scope, SymbolID lookupID, AstContext context) {
    return lookupSymbolUntil(scope, lookupID, NULL, context);
}
void* lookupSymbolUntil(Scope* scope, SymbolID lookupID, Scope* endScopeP, AstContext context) {
    if (scope->defnID == lookupID) {
        if (context == ASTCTX_TYPING) {
            return scope->typingTypeP;
        } else {
            return scope->valueTypeP;
        }
    }
    if (scope == endScopeP) {
        // this is the last scope
        // we haven't found the symbol
        // return NULL => not found.
        return NULL;
    } else {
        // try repeating on parent
        if (scope->parent) {
            return lookupSymbolUntil(scope->parent, lookupID, endScopeP, context);
        } else {
            return NULL;
        }
    }
}

//
// Implementation:
//

static int primer_pre(void* primer, AstNode* node);
static int primer_post(void* primer, AstNode* node);

int primer_pre(void* rawPrimer, AstNode* node) {
    Primer* primer = rawPrimer;
    AstKind kind = GetAstNodeKind(node);
    switch (kind) {
        case AST_ID:
        {
            SetAstIdScopeP(node, primer->currentScopeP);
            SetAstIdLookupContext(node,topPrimerContext(primer));
            break;
        }
        case AST_STMT_BIND:
        {
            SymbolID defnID = GetAstBindStmtLhs(node);
            void* valueTypeP = CreateMetatype(primer->typer, "let<v>%s", GetSymbolText(defnID));
            // void* typingTypeP = CreateMetatype(primer->typer, "let<t>%s", GetSymbolText(defnID));
            void* typingTypeP = NULL;
            primer->currentScopeP = defineSymbol(primer->currentScopeP, defnID, valueTypeP, typingTypeP);
            SetAstNodeValueType(node, valueTypeP);
            SetAstNodeTypingType(node, typingTypeP);
            break;
        }
        case AST_STRUCT:
        {
            break;
        }
        case AST_PATTERN:
        {
            pushPrimerContext(primer, ASTCTX_TYPING);
            break;
        }
        case AST_CHAIN:
        {
            AstNode* result = GetAstChainResult(node);
            break;
        }
        case AST_FIELD__MODULE_ITEM:
        {
            // already defined before running the visitor, doing nothing.
            void* typingType = GetAstNodeTypingType(node);
            void* valueType = GetAstNodeValueType(node);
            break;
        }
        case AST_UNARY:
        {
            break;
        }
        case AST_BINARY:
        {
            break;
        }
        case AST_FIELD__TEMPLATE_ITEM:
        {
            SymbolID defnID = GetAstFieldName(node);
            // todo: valueTypeP encodes a first-order type
            void* valueTypeP = CreateMetatype(primer->typer, "template<v>%s", GetSymbolText(defnID));
            void* typingTypeP = CreateMetatype(primer->typer, "template<t>%s", GetSymbolText(defnID));
            primer->currentScopeP = defineSymbol(primer->currentScopeP, defnID, valueTypeP, typingTypeP);
            SetAstNodeValueType(node, valueTypeP);
            SetAstNodeTypingType(node, typingTypeP);
            break;
        }
        case AST_FIELD__PATTERN_ITEM:
        {
            SymbolID defnID = GetAstFieldName(node);
            void* valueTypeP = CreateMetatype(primer->typer, "pattern<v>%s", GetSymbolText(defnID));
            // void* typingTypeP = CreateMetatype(primer->typer, "pattern<t> %s", GetSymbolText(defnID));
            void* typingTypeP = NULL;
            primer->currentScopeP = defineSymbol(primer->currentScopeP, defnID, valueTypeP, typingTypeP);
            SetAstNodeValueType(node, valueTypeP);
            SetAstNodeTypingType(node, typingTypeP);
            break;
        }
        case AST_FIELD__STRUCT_ITEM:
        {
            SymbolID defnID = GetAstFieldName(node);
            SetAstNodeValueType(node, GetAstNodeValueType(GetAstFieldRhs(node)));
            break;
        }
        default:
        {
            break;
        }
    }
    return 1;
}
int primer_post(void* rawPrimer, AstNode* node) {
    Primer* primer = rawPrimer;
    AstKind kind = GetAstNodeKind(node);
    switch (kind) {
        case AST_PATTERN:
        {
            popPrimerContext(primer);
            break;
        }
        default:
        {
            break;
        }
    }
    return 1;
}

Primer* CreatePrimer(void* typer) {
    return createPrimer(typer);
}

int PrimeModule(Primer* primer, AstNode* module) {
    if (DEBUG) {
        assert(GetAstNodeKind(module) == AST_MODULE);
    }

    // defining all module-symbols in one binding group
    // building primerP->currentModuleDef{Beg -> End}P before visiting
    size_t moduleStmtLength = GetAstModuleLength(module);
    for (size_t index = 0; index < moduleStmtLength; index++) {
        AstNode* field = GetAstModuleFieldAt(module, index);
        void* valueTypeP = CreateMetatype(primer->typer, "define<v>%s", GetSymbolText(GetAstFieldName(field)));
        void* typingTypeP = CreateMetatype(primer->typer, "define<t>%s", GetSymbolText(GetAstFieldName(field)));
        primer->currentScopeP = defineSymbol(primer->currentScopeP, GetAstFieldName(field), valueTypeP, typingTypeP);
        primer->currentModuleDefEndP = primer->currentScopeP;
        if (primer->currentModuleDefBegP == NULL) {
            primer->currentModuleDefBegP = primer->currentScopeP;
        }

        // storing the defined metatypes on the field:
        assert(GetAstNodeKind(field) == AST_FIELD__MODULE_ITEM);
        SetAstNodeValueType(field,valueTypeP);
        SetAstNodeTypingType(field,typingTypeP);
    }

    // visiting the AST:
    pushPrimerContext(primer,ASTCTX_VALUE);
    if (!visit(primer, module, primer_pre, primer_post)) {
        return 0;
    }
    popPrimerContext(primer);
    return 1;
}

void* LookupSymbol(Scope* scope, SymbolID lookupID, AstContext context) {
    return lookupSymbol(scope, lookupID, context);
}

void* LookupSymbolUntil(Scope* scope, SymbolID lookupID, Scope* endScopeP, AstContext context) {
    return lookupSymbolUntil(scope, lookupID, endScopeP, context);
}

// After definition, IDs are looked up, map to type IDs.
// These type IDs can be stored in the AST.

// todo: define builtin IDs
