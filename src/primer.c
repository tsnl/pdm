#include "primer.h"

#include <assert.h>

#include "stb/stretchy_buffer.h"

#include "useful.h"
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
        AstKind nodeKind = GetAstNodeKind(func);
        COMPILER_ASSERT_VA(
            nodeKind == AST_LAMBDA, 
            "Non-lambda parent func in `pushFrame`: %s", AstKindAsText(nodeKind)
        );
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
    
    root = newScope(root, Symbol("u1"), NewOrGetIntType(typer,INT_1), NULL, ASTCTX_TYPING);
    root = newScope(root, Symbol("u8"), NewOrGetIntType(typer,INT_8), NULL, ASTCTX_TYPING);
    root = newScope(root, Symbol("u16"), NewOrGetIntType(typer,INT_16), NULL, ASTCTX_TYPING);
    root = newScope(root, Symbol("u32"), NewOrGetIntType(typer,INT_32), NULL, ASTCTX_TYPING);
    root = newScope(root, Symbol("u64"), NewOrGetIntType(typer,INT_64), NULL, ASTCTX_TYPING);
    root = newScope(root, Symbol("u128"), NewOrGetIntType(typer,INT_128), NULL, ASTCTX_TYPING);

    root = newScope(root, Symbol("f32"), NewOrGetFloatType(typer,FLOAT_32), NULL, ASTCTX_TYPING);
    root = newScope(root, Symbol("f64"), NewOrGetFloatType(typer,FLOAT_64), NULL, ASTCTX_TYPING);
    
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

// primer_pre and primer_post are the pre and post visitor callbacks for the primer pass.
// - primer_pre runs before all children are visited (prefix order)
// - primer_post runs after all children are visited (postfix order)
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
        case AST_TID:
        {
            SetAstIdLookupScope(node, topFrameScope(primer));
            SetAstNodeLookupContext(node, ASTCTX_TYPING);
            break;
        }
        case AST_VID:
        {
            SetAstIdLookupScope(node, topFrameScope(primer));
            SetAstNodeLookupContext(node, ASTCTX_VALUE);
            break;
        }
        case AST_VLET:
        {
            Loc loc = GetAstNodeLoc(node);
            SymbolID defnID = GetAstLetStmtLhs(node);
            void* type = NewMetavarType(loc, primer->typer, "let:%s", GetSymbolText(defnID));
            pushSymbol(primer, defnID, type, node, ASTCTX_VALUE);
            SetAstNodeTypingExt_SingleV(node,type);
            break;
        }
        case AST_VSTRUCT:
        {
            break;
        }
        case AST_TPATTERN:
        case AST_VPATTERN:
        {
            break;
        }
        case AST_VPAREN:
        case AST_CHAIN:
        {
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
        case AST_TPATTERN_SINGLETON:
        case AST_TPATTERN_FIELD:
        {
            Loc loc = GetAstNodeLoc(node);
            SymbolID defnID = SYM_NULL;
            if (kind == AST_TPATTERN_SINGLETON) {
                defnID = GetAstFieldName(node);
            } else {
                COMPILER_ASSERT(kind == AST_TPATTERN_FIELD, "Expected kind to be either AST_TPATTERN_SINGLETON or AST_TPATTERN_SINGLETON");
                defnID = GetAstFieldName(node);
            }
            void* type = NewMetavarType(loc, primer->typer, "tpattern:%s", GetSymbolText(defnID));
            pushSymbol(primer, defnID, type, node, ASTCTX_TYPING);
            SetAstNodeTypingExt_SingleV(node, type);
            break;
        }
        case AST_VPATTERN_SINGLETON:
        case AST_VPATTERN_FIELD:
        {
            Loc loc = GetAstNodeLoc(node);
            SymbolID defnID = SYM_NULL;
            if (kind == AST_VPATTERN_SINGLETON) {
                defnID = GetAstSingletonPatternName(node);
            } else {
                COMPILER_ASSERT(kind == AST_VPATTERN_FIELD, "expected either ast_vpattern_singleton or ast_field__pattern_item");
                defnID = GetAstFieldName(node);
            }

            // defining a value symbol:
            void* patternType = NewMetavarType(loc, primer->typer, "vpattern:%s", GetSymbolText(defnID));
            pushSymbol(primer, defnID, patternType, node, ASTCTX_VALUE);
            SetAstNodeTypingExt_SingleV(node, patternType);

            // pushing a typing frame for RHS
            pushFrame(primer,NULL,ASTCTX_TYPING,topFrameFunc(primer));
            break;
        }
        case AST_VSTRUCT_FIELD:
        {
            // SymbolID defnID = GetAstFieldName(node);
            SetAstNodeTypingExt_SingleV(node, GetAstNodeTypingExt_SingleV(GetAstFieldRhs(node)));
            break;
        }
        case AST_LAMBDA:
        {
            // pushing a new frame for the function's contents:
            pushFrame(primer,NULL,ASTCTX_VALUE,node);
            break;
        }
        case AST_EXTERN:
        case AST_TDEF:
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
        case AST_VPAREN:
        case AST_LAMBDA:
        case AST_VPATTERN_FIELD:
        case AST_EXTERN:
        case AST_TDEF:
        {
            // pop for each case where a frame is pushed in `primer_pre`.
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

//
//
// API:
//
//

Primer* CreatePrimer(void* typer) {
    return createPrimer(typer);
}
int PrimeModule(Primer* primer, AstNode* module) {
    if (DEBUG) {
        assert(GetAstNodeKind(module) == AST_MODULE);
    }

    // defining all module-symbols in one go, storing as typing extensions:
    pushFrame(primer,NULL,ASTCTX_VALUE,topFrameFunc(primer));
    size_t moduleStmtLength = GetAstModuleLength(module);
    for (size_t index = 0; index < moduleStmtLength; index++) {
        // todo: HACKY let the symbol define itself as type or value in `PrimeModule`
        AstNode* stmt = GetAstModuleStmtAt(module, index);
        Loc loc = GetAstNodeLoc(stmt);
        AstKind stmtKind = GetAstNodeKind(stmt);
        if (stmtKind == AST_VDEF) {
            SymbolID lhs = GetAstDefValueStmtLhs(stmt);
            void* valueType = NewMetavarType(loc,primer->typer,"def-func:%s",GetSymbolText(lhs));
            pushSymbol(primer,lhs,valueType,stmt,ASTCTX_VALUE);
            SetAstNodeTypingExt_SingleV(stmt,valueType);
        } else if (stmtKind == AST_EXTERN) {
            SymbolID lhs = GetAstExternStmtName(stmt);
            void* valueType = NewMetavarType(loc,primer->typer,"extern:%s",GetSymbolText(lhs));
            pushSymbol(primer,lhs,valueType,stmt,ASTCTX_VALUE);
            SetAstNodeTypingExt_SingleV(stmt,valueType);
        } else if (stmtKind == AST_TDEF) {
            SymbolID lhs = GetAstTypedefStmtName(stmt);
            char const* symbolText = GetSymbolText(lhs);
            void* typingType = NewMetavarType(loc,primer->typer,"typedef:%s",symbolText);
            pushSymbol(primer,lhs,typingType,stmt,ASTCTX_TYPING);
            SetAstNodeTypingExt_SingleT(stmt, typingType);
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
