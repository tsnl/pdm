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

    // the typer is used by the primer to create metatypes.
    Typer* typer;

    // new scopes can extend previous ones, and are organized into 'frames' stored in this stack:
    Frame* frameStackSB;
    int frameStackCount;
};

size_t allocatedPrimersCount = 0;
Primer allocatedPrimers[MAX_PRIMER_COUNT];

static Primer* createPrimer(Typer* typer);
static void pushSymbol(Primer* primer, SymbolID defnID, void* type, AstNode* node, AstContext context);
static Scope* pushFrame(Primer* primer, Scope* scope, AstContext ctx, AstNode* func);
static Frame popFrame(Primer* primer);
Frame* topFrame(Primer* primer);
Scope* topFrameScope(Primer* primer);
AstNode* topFrameFunc(Primer* primer);
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

    pushFrame(primer,primer->root,ASTCTX_VALUE,topFrameFunc(primer));

    return primer;
}
void pushSymbol(Primer* primer, SymbolID defnID, void* type, AstNode* defnAstNode, AstContext context) {
    if (defnID) {
        Scope* parent = topFrameScope(primer);
        Scope* scope = newScope(parent, defnID, type, defnAstNode, context);
        primer->frameStackSB[primer->frameStackCount-1].endScope = scope;

        AstNode* topLambda = topFrameFunc(primer);
        if (topLambda) {
            Defn* defn = scope;
            AddAstLambdaDefn(topLambda,defn);
        }
    }
}
Scope* pushFrame(Primer* primer, Scope* optNewScope, AstContext ctx, AstNode* func) {
    if (func) {
        if (GetAstNodeKind(func) != AST_LAMBDA) {
            if (DEBUG) {
                printf("!!- non-lambda parent func in `pushFrame`.\n");
            } else {
                assert(0 && "non-lambda parent func in `pushFrame`");
            }
        }
    }

    Scope* topScope = topFrameScope(primer);
    if (optNewScope == NULL) {
        optNewScope = topScope;
    } else if (topScope != primer->root) {
        int ok = (optNewScope->parent == topScope);
        if (!ok) {
            if (DEBUG) {
                printf("!!- Invalid scope pushed in primer; parent must be the top frame scope at push-time.\n");
            } else {
                assert(0 && "primer: invalid scope pushed; parent must be the top frame scope at push-time.");
            }
            return NULL;
        }
    }
    Frame frame = {ctx,optNewScope,optNewScope,func};
    int bufCount = sb_count(primer->frameStackSB);
    if (primer->frameStackCount == bufCount) {
        sb_push(primer->frameStackSB,frame);
    } else {
        primer->frameStackSB[primer->frameStackCount] = frame;
    }
    primer->frameStackCount++;
    return optNewScope;
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
Frame* topFrame(Primer* primer) {
    if (primer->frameStackCount > 0) {
        Frame* topFrame = NULL;
        for (int index = primer->frameStackCount-1; index >= 0; index--) {
            Frame* frame = &primer->frameStackSB[index];
            int isEmpty = (frame->begScope == frame->endScope && frame->begScope == NULL);
            if (!isEmpty) {
                topFrame = frame;
                break;
            }
        }
        if (topFrame) {
            return topFrame;
        }
    }
    return NULL;
}
Scope* topFrameScope(Primer* primer) {
    Frame* frame = topFrame(primer);
    if (frame) {
        return frame->endScope;
    }
    return primer->root;
}
AstNode* topFrameFunc(Primer* primer) {
    Frame* frame = topFrame(primer);
    if (frame) {
        return frame->func;
    }
    return NULL;
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

inline Scope* newScope(Scope* parent, SymbolID defnID, void* type, AstNode* defnAstNode, AstContext context) {
    Scope* scope = &allocatedScopes[allocatedScopeCount++];
    scope->parent = parent;
    scope->defnID = defnID;
    scope->type = type;
    scope->context = context;
    scope->defnAstNode = defnAstNode;
    return scope;
}
Scope* newRootScope(Typer* typer) {
    Scope* root = NULL;
    
    root = newScope(root, Symbol("u1"), GetIntType(typer,INT_1), NULL, ASTCTX_TYPING);
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
    AstNode* topFunc = topFrameFunc(primer);
    if (topFunc) {
        SetAstNodeParentFunc(node,topFunc);
    }
    
    AstKind kind = GetAstNodeKind(node);
    switch (kind) {
        case AST_ID:
        {
            SetAstIdLookupScope(node, topFrameScope(primer));
            break;
        }
        case AST_LET:
        {
            Loc loc = GetAstNodeLoc(node);
            SymbolID defnID = GetAstLetStmtLhs(node);
            void* type = CreateMetatype(loc, primer->typer, "let:%s", GetSymbolText(defnID));
            pushSymbol(primer, defnID, type, node, ASTCTX_VALUE);
            SetAstNodeValueType(node, type);
            break;
        }
        case AST_STRUCT:
        {
            break;
        }
        case AST_T_PATTERN:
        case AST_V_PATTERN:
        {
            break;
        }
        case AST_PAREN:
        case AST_CHAIN:
        {
            pushFrame(primer, NULL, ASTCTX_VALUE, topFrameFunc(primer));
            break;
        }
        case AST_DEF:
        {
            // void* type = GetAstNodeType(node);
            
            // todo: check if multiple template arguments were provided. correct if so.

            pushFrame(primer, NULL, ASTCTX_VALUE, topFrameFunc(primer));
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
            Loc loc = GetAstNodeLoc(node);
            SymbolID defnID = GetAstFieldName(node);
            // todo: valueTypeP encodes a first-order type
            void* type = CreateMetatype(loc, primer->typer, "template:%s", GetSymbolText(defnID));
            pushSymbol(primer, defnID, type, node, ASTCTX_TYPING);
            SetAstNodeValueType(node, type);
            break;
        }
        case AST_FIELD__PATTERN_ITEM:
        {
            Loc loc = GetAstNodeLoc(node);
            // defining the formal arg symbol in the lambda scope:
            SymbolID defnID = GetAstFieldName(node);
            void* type = CreateMetatype(loc, primer->typer, "pattern:%s", GetSymbolText(defnID));
            pushSymbol(primer, defnID, type, node, ASTCTX_VALUE);
            SetAstNodeValueType(node, type);

            // pushing a typing frame for RHS
            pushFrame(primer,NULL,ASTCTX_TYPING,topFrameFunc(primer));
            break;
        }
        case AST_FIELD__STRUCT_ITEM:
        {
            // SymbolID defnID = GetAstFieldName(node);
            SetAstNodeValueType(node, GetAstNodeValueType(GetAstFieldRhs(node)));
            break;
        }
        case AST_LAMBDA:
        {
            // pushing a new frame for the function's contents:
            pushFrame(primer,NULL,ASTCTX_VALUE,node);
            break;
        }
        case AST_EXTERN:
        case AST_TYPEDEF:
        {
            pushFrame(primer,NULL,ASTCTX_TYPING,topFrameFunc(primer));
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
        case AST_TYPEDEF:
        case AST_EXTERN:
        case AST_DEF:
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
    pushFrame(primer,NULL,ASTCTX_VALUE,topFrameFunc(primer));
    size_t moduleStmtLength = GetAstModuleLength(module);
    for (size_t index = 0; index < moduleStmtLength; index++) {
        // todo: HACKY let the symbol define itself as type or value in `PrimeModule`
        AstNode* stmt = GetAstModuleStmtAt(module, index);
        Loc loc = GetAstNodeLoc(stmt);
        AstKind stmtKind = GetAstNodeKind(stmt);
        if (stmtKind == AST_DEF) {
            SymbolID lhs = GetAstDefStmtLhs(stmt);
            char const* symbolText = GetSymbolText(lhs);
            void* valType = CreateMetatype(loc, primer->typer, "def-func:%s", symbolText);
            void* typingType = CreateMetatype(loc, primer->typer, "def-type:%s", symbolText);
            pushSymbol(primer, lhs, valType, stmt, ASTCTX_VALUE);
            pushSymbol(primer, lhs, typingType, stmt, ASTCTX_TYPING);
            // storing the defined metatypes on the statement:
            SetAstNodeValueType(stmt,valType);
            SetAstNodeTypingType(stmt,typingType);
        } else if (stmtKind == AST_EXTERN) {
            SymbolID lhs = GetAstExternStmtName(stmt);
            char const* symbolText = GetSymbolText(lhs);
            void* valType = CreateMetatype(loc, primer->typer, "extern:%s", symbolText);
            pushSymbol(primer, lhs, valType, stmt, ASTCTX_VALUE);
            SetAstNodeValueType(stmt,valType);
        } else if (stmtKind == AST_TYPEDEF) {
            SymbolID lhs = GetAstTypedefStmtName(stmt);
            char const* symbolText = GetSymbolText(lhs);
            
            void* typingContextType = CreateMetatype(loc, primer->typer, "typedef:%s", symbolText);
            // todo: replace this invocation of FuncType with something different, like CastType?
            void* valueContextType = GetFuncType(primer->typer, typingContextType, typingContextType);
            
            pushSymbol(primer, lhs, typingContextType, stmt, ASTCTX_TYPING);
            pushSymbol(primer, lhs, valueContextType, stmt, ASTCTX_VALUE);
            
            SetAstNodeTypingType(stmt, typingContextType);
            SetAstNodeValueType(stmt, valueContextType);
        } else {
            if (DEBUG) {
                printf("!!- PrimeModule: Unsupported statement kind in module\n");
            } else {
                assert(0 && "PrimeModule: Unsupported statement kind in module");
            }
        }
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
