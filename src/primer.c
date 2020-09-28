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

typedef struct Frame Frame;

struct Primer {
    Scope* root;

    // the typer is used by the primer to create metatypes.
    Typer* typer;

    // new scopes can extend previous ones, and are organized into 'frames' stored in this stack:
    Frame* frameStackSB;
    int frameStackCount;
};

struct Scope {
    Scope* parent;
    SymbolID defnID;
    AstNode* defnAstNode;
    AstContext context;
    void* type;
};

struct Frame {
    AstContext context;
    Scope* begScopeP;
    Scope* endScopeP;
};

size_t allocatedPrimersCount = 0;
Primer allocatedPrimers[MAX_PRIMER_COUNT];

static Primer* createPrimer(Typer* typer);
static Scope* pushFrame(Primer* primer, Scope* scope, AstContext ctx);
static void pushFrameSymbol(Primer* primer, SymbolID defnID, void* type, AstNode* node, AstContext context);
static Frame popFrame(Primer* primer);
Scope* topFrameScope(Primer* primer);
static AstContext topFrameContext(Primer* primer);

static size_t allocatedScopeCount = 0;
static Scope allocatedScopes[MAX_AST_NODE_COUNT];
inline static Scope* newScope(Scope* parent, SymbolID defnID, void* type, AstNode* defn, AstContext context);
static Scope* newRootScope(Typer* typer);
static Defn* lookupSymbolUntil(Scope* scope, SymbolID lookupID, Scope* endScopeP, AstContext context);

//
// Static implementation:
//

Primer* createPrimer(Typer* typer) {
    Primer* primer = NULL;
    if (allocatedPrimersCount < MAX_PRIMER_COUNT) {
        primer = &allocatedPrimers[allocatedPrimersCount++];
    } else {
        return NULL;
    }
    primer->typer = typer;
    primer->frameStackSB = NULL;
    primer->frameStackCount = 0;
    primer->root = newRootScope(typer);

    pushFrame(primer,primer->root,ASTCTX_VALUE);

    return primer;
}
Scope* pushFrame(Primer* primer, Scope* optNewScope, AstContext ctx) {
    if (optNewScope == NULL) {
        optNewScope = topFrameScope(primer);
    } else {
        int ok = (optNewScope->parent == topFrameScope(primer));
        if (!ok) {
            if (DEBUG) {
                printf("primer: Invalid scope pushed; parent must be the top frame scope at push-time.\n");
            } else {
                assert(0 && "primer: Invalid scope pushed; parent must be the top frame scope at push-time.");
            }
            return NULL;
        }
    }
    Frame frame = {ctx,optNewScope,optNewScope};
    int bufCount = sb_count(primer->frameStackSB);
    if (primer->frameStackCount == bufCount) {
        sb_push(primer->frameStackSB,frame);
    } else {
        primer->frameStackSB[primer->frameStackCount] = frame;
    }
    primer->frameStackCount++;
    return optNewScope;
}
void pushFrameSymbol(Primer* primer, SymbolID defnID, void* type, AstNode* defn, AstContext context) {
    Scope* parent = topFrameScope(primer);
    primer->frameStackSB[primer->frameStackCount-1].endScopeP = (Scope*)newScope(parent, defnID, type, defn, context);
}
Frame popFrame(Primer* primer) {
    if (primer->frameStackCount > 0) {
        primer->frameStackCount--;
        Frame frame = primer->frameStackSB[primer->frameStackCount];
        primer->frameStackSB[primer->frameStackCount].context = __ASTCTX_NONE;
        return frame;
    } else {
        if (DEBUG) {
            printf("!!- primer: Cannot pop from an empty frame.\n");
        } else {
            assert(0 && "primer: Cannot pop from an empty frame.\n");
        }
        Frame frame;
        frame.context = __ASTCTX_NONE;
        return frame;
    }
}
Scope* topFrameScope(Primer* primer) {
    if (primer->frameStackCount > 0) {
        Frame* topFrame = NULL;
        for (int index = primer->frameStackCount-1; index >= 0; index--) {
            Frame* frame = &primer->frameStackSB[index];
            int isEmpty = (frame->begScopeP == frame->endScopeP && frame->begScopeP == NULL);
            if (!isEmpty) {
                topFrame = frame;
                break;
            }
        }
        if (topFrame) {
            return topFrame->endScopeP;
        } else {
            return primer->root;
        }
    } else {
        return NULL;
    }
}
AstContext topFrameContext(Primer* primer) {
    if (!primer->frameStackSB) {
        if (DEBUG) {
            printf("!!- Primer context stack empty.\n");
        } else {
            assert(0 && "Primer context stack empty.");
        }
        return __ASTCTX_NONE;
    }
    return primer->frameStackSB[primer->frameStackCount-1].context;
}

inline Scope* newScope(Scope* parent, SymbolID defnID, void* type, AstNode* defn, AstContext context) {
    Scope* scope = &allocatedScopes[allocatedScopeCount++];
    scope->parent = parent;
    scope->defnID = defnID;
    scope->type = type;
    scope->context = context;
    return scope;
}
Scope* newRootScope(Typer* typer) {
    Scope* root = NULL;
    
    root = newScope(root, Symbol("u8"), GetIntType(typer,INT_8), NULL, ASTCTX_TYPING);
    root = newScope(root, Symbol("u16"), GetIntType(typer,INT_16), NULL, ASTCTX_TYPING);
    root = newScope(root, Symbol("u32"), GetIntType(typer,INT_32), NULL, ASTCTX_TYPING);
    root = newScope(root, Symbol("u64"), GetIntType(typer,INT_64), NULL, ASTCTX_TYPING);
    root = newScope(root, Symbol("u128"), GetIntType(typer,INT_128), NULL, ASTCTX_TYPING);

    root = newScope(root, Symbol("f32"), GetFloatType(typer,FLOAT_32), NULL, ASTCTX_TYPING);
    root = newScope(root, Symbol("f64"), GetFloatType(typer,FLOAT_64), NULL, ASTCTX_TYPING);
    
    return root;
}
Defn* lookupSymbolUntil(Scope* scope, SymbolID lookupID, Scope* endScopeP, AstContext context) {
    if (lookupID == SYM_NULL) {
        return NULL;
    }
    if (scope->context == context && scope->defnID == lookupID) {
        return scope;
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
    SetAstNodeLookupContext(node,topFrameContext(primer));
    
    AstKind kind = GetAstNodeKind(node);
    switch (kind) {
        case AST_ID:
        {
            SetAstIdLookupScope(node, topFrameScope(primer));
            break;
        }
        case AST_STMT_BIND:
        {
            SymbolID defnID = GetAstBindStmtLhs(node);
            void* type = CreateMetatype(primer->typer, "let:%s", GetSymbolText(defnID));
            pushFrameSymbol(primer, defnID, type, node, ASTCTX_VALUE);
            SetAstNodeType(node, type);
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
        case AST_PAREN:
        case AST_CHAIN:
        {
            pushFrame(primer, NULL, ASTCTX_VALUE);
            break;
        }
        case AST_FIELD__MODULE_ITEM:
        {
            // void* type = GetAstNodeType(node);
            // todo: (in primer_pre:__MODULE_ITEM) push a type frame if this is a type definition?
            pushFrame(primer, NULL, ASTCTX_VALUE);
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
            void* type = CreateMetatype(primer->typer, "template:%s", GetSymbolText(defnID));
            pushFrameSymbol(primer, defnID, type, node, ASTCTX_TYPING);
            SetAstNodeType(node, type);
            break;
        }
        case AST_FIELD__PATTERN_ITEM:
        {
            // defining the formal arg symbol in the lambda scope:
            SymbolID defnID = GetAstFieldName(node);
            void* type = CreateMetatype(primer->typer, "pattern:%s", GetSymbolText(defnID));
            pushFrameSymbol(primer, defnID, type, node, ASTCTX_VALUE);
            SetAstNodeType(node, type);

            // pushing a typing frame for RHS
            pushFrame(primer,NULL,ASTCTX_TYPING);
            break;
        }
        case AST_FIELD__STRUCT_ITEM:
        {
            // SymbolID defnID = GetAstFieldName(node);
            SetAstNodeType(node, GetAstNodeType(GetAstFieldRhs(node)));
            break;
        }
        case AST_LAMBDA:
        {
            // pushing a new frame for the function's contents:
            pushFrame(primer,NULL,ASTCTX_VALUE);
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
        case AST_CHAIN:
        case AST_PAREN:
        case AST_LAMBDA:
        case AST_FIELD__PATTERN_ITEM:
        case AST_FIELD__MODULE_ITEM:
        {
            popFrame(primer);
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
    pushFrame(primer,NULL,ASTCTX_VALUE);
    size_t moduleStmtLength = GetAstModuleLength(module);
    for (size_t index = 0; index < moduleStmtLength; index++) {
        // todo: HACKY let the symbol define itself as type or value in `PrimeModule`
        AstNode* field = GetAstModuleFieldAt(module, index);
        void* type = CreateMetatype(primer->typer, "define:%s", GetSymbolText(GetAstFieldName(field)));
        pushFrameSymbol(primer, GetAstFieldName(field), type, field, ASTCTX_VALUE);
        
        // storing the defined metatypes on the field:
        assert(GetAstNodeKind(field) == AST_FIELD__MODULE_ITEM);
        SetAstNodeType(field,type);
    }
    
    // visiting the AST:
    if (!RecursivelyVisitAstNode(primer, module, primer_pre, primer_post)) {
        return 0;
    }
    popFrame(primer);
    return 1;
}

Defn* LookupSymbol(Scope* scope, SymbolID lookupID, AstContext context) {
    return lookupSymbolUntil(scope, lookupID, NULL, context);
}

Defn* LookupSymbolUntil(Scope* scope, SymbolID lookupID, Scope* endScopeP, AstContext context) {
    return lookupSymbolUntil(scope, lookupID, endScopeP, context);
}

// After definition, IDs are looked up, map to type IDs.
// These type IDs can be stored in the AST.

SymbolID GetDefnName(Defn* defn) {
    return defn->defnID;
}
AstNode* GetDefnNode(Defn* defn) {
    return defn->defnAstNode;
}
AstContext GetDefnContext(Defn* defn) {
    return defn->context;
}
void* GetDefnType(Defn* defn) {
    return defn->type;
}
