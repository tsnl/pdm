#include "scoper.h"

#include <assert.h>

#include "symbols.h"
#include "config.h"
#include "typer.h"

// The scoper performs `Lexical Analysis`, which involves traversing the AST, building a tree of
// contexts from linked list node stored in stack frames, and using this tree to look up symbols'
// types.
// At the end of Lexical Analysis, we have a typeP for each typed expression, ready for 
// typing/unification after analysis.
// Crucially, each context contains at most *one* definition.

struct Scoper {
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

    // the typer is used by the scoper to create metatypes.
    Typer* typer;
};

struct Scope {
    Scope* parent;
    SymbolID defnID;
    void* valueTypeP;
    void* typingTypeP;
};

size_t allocatedScopersCount = 0;
Scoper allocatedScopers[MAX_SCOPER_COUNT];
static size_t allocatedScopeStackFramesCount = 0;

static Scoper* createScoper(Typer* typer);

static size_t allocatedScopeCount = 0;
static Scope allocatedScopes[MAX_AST_NODE_COUNT];
inline static Scope* newScope(Scope* parent, SymbolID defnID, void* valueTypeP, void* typingTypeP);
static Scope* defineSymbol(Scope* parent, SymbolID defnID, void* valueTypeP, void* typingTypeP);
static void* lookupSymbol(Scope* scope, SymbolID lookupID, AstContext context);
static void* lookupSymbolUntil(Scope* scope, SymbolID lookupID, Scope* endScopeP, AstContext context);

//
// Static implementation:
//

Scoper* createScoper(Typer* typer) {
    Scoper* scoper = NULL;
    if (allocatedScopersCount < MAX_SCOPER_COUNT) {
        scoper = &allocatedScopers[allocatedScopersCount++];
    } else {
        return NULL;
    }
    scoper->currentScopeP = NULL;
    scoper->currentModuleDefBegP = NULL;
    scoper->currentModuleDefEndP = NULL;
    scoper->typer = typer;
    return scoper;
}

inline Scope* newScope(Scope* parent, SymbolID defnID, void* valueTypeP, void* typingTypeP) {
    Scope* scopeP = &allocatedScopes[allocatedScopeCount++];
    scopeP->parent = parent;
    scopeP->defnID = defnID;
    scopeP->valueTypeP = valueTypeP;
    scopeP->typingTypeP = typingTypeP;
    return scopeP;
}
Scope* defineSymbol(Scope* parent, SymbolID defnID, void* valueTypeP, void* typingTypeP) {
    return (Scope*)newScope(parent, defnID, valueTypeP, typingTypeP);
}
void* lookupSymbol(Scope* scope, SymbolID lookupID, AstContext context) {
    return lookupSymbolUntil(scope, lookupID, NULL, context);
}
void* lookupSymbolUntil(Scope* scope, SymbolID lookupID, Scope* endScopeP, AstContext context) {
    if (scope->defnID == lookupID) {
        return scope->valueTypeP;
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

static int scoper_pre(void* scoper, AstNode* node);
static int scoper_post(void* scoper, AstNode* node);

int scoper_pre(void* rawScoper, AstNode* node) {
    Scoper* scoper = rawScoper;
    AstKind kind = GetAstNodeKind(node);
    switch (kind) {
        case AST_ID:
        {
            SetAstIdScopeP(node, scoper->currentScopeP);
            break;
        }
        case AST_STMT_BIND:
        {
            SymbolID defnID = GetAstBindStmtLhs(node);
            void* valueTypeP = CreateMetatype(scoper->typer, "let<v> %s", GetSymbolText(defnID));
            void* typingTypeP = CreateMetatype(scoper->typer, "let<t> %s", GetSymbolText(defnID));
            scoper->currentScopeP = defineSymbol(scoper->currentScopeP, defnID, valueTypeP, typingTypeP);
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
            break;
        }
        case AST_CHAIN:
        {
            break;
        }
        case AST_FIELD__MODULE_ITEM:
        {
            // already defined before running the visitor, doing nothing.
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
            void* valueTypeP = CreateMetatype(scoper->typer, "template %s", GetSymbolText(defnID));
            void* typingTypeP = CreateMetatype(scoper->typer, "template %s", GetSymbolText(defnID));
            scoper->currentScopeP = defineSymbol(scoper->currentScopeP, defnID, valueTypeP, typingTypeP);
            break;
        }
        case AST_FIELD__PATTERN_ITEM:
        {
            SymbolID defnID = GetAstFieldName(node);
            void* valueTypeP = CreateMetatype(scoper->typer, "pattern %s", GetSymbolText(defnID));
            void* typingTypeP = CreateMetatype(scoper->typer, "pattern %s", GetSymbolText(defnID));
            scoper->currentScopeP = defineSymbol(scoper->currentScopeP, defnID, valueTypeP, typingTypeP);
            break;
        }
        case AST_FIELD__STRUCT_ITEM:
        {
            // todo: define a scoper symbol chain for structs similar to modules.
            break;
        }
        default:
        {
            break;
        }
    }
    return 1;
}

int scoper_post(void* rawScoper, AstNode* node) {
    Scoper* scoper = rawScoper;
    AstKind kind = GetAstNodeKind(node);
    switch (kind) {
        default:
        {
            break;
        }
    }
    return 1;
}

Scoper* CreateScoper(void* typer) {
    return createScoper(typer);
}

int ScopeModule(Scoper* scoper, AstNode* module) {
    if (DEBUG) {
        assert(GetAstNodeKind(module) == AST_MODULE);
    }

    // defining all module-symbols in one binding group
    // building scoperP->currentModuleDef{Beg -> End}P before visiting
    size_t moduleStmtLength = GetAstModuleLength(module);
    for (size_t index = 0; index < moduleStmtLength; index++) {
        AstNode* field = GetAstModuleFieldAt(module, index);
        void* valueTypeP = CreateMetatype(scoper->typer, "define<v> %s", GetSymbolText(GetAstFieldName(field)));
        void* typingTypeP = CreateMetatype(scoper->typer, "define<t> %s", GetSymbolText(GetAstFieldName(field)));
        scoper->currentScopeP = defineSymbol(scoper->currentScopeP, GetAstFieldName(field), valueTypeP, typingTypeP);
        scoper->currentModuleDefEndP = scoper->currentScopeP;
        if (scoper->currentModuleDefBegP == NULL) {
            scoper->currentModuleDefBegP = scoper->currentScopeP;
        }
    }

    // visiting the AST:
    if (!visit(scoper, module, scoper_pre, scoper_post)) {
        return 0;
    }
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
