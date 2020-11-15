#include "primer.h"

#include <assert.h>

#include "stb/stretchy_buffer.h"

#include "useful.h"
#include "symbols.h"
#include "config.h"
#include "typer.h"

// Taking static references to pre-defined symbols:
static int symbols_loaded = 0;

static SymbolID symbol_string = SYM_NULL;
static SymbolID symbol_unit = SYM_NULL;
static SymbolID symbol_u1 = SYM_NULL;
static SymbolID symbol_u8 = SYM_NULL;
static SymbolID symbol_u16 = SYM_NULL;
static SymbolID symbol_u32 = SYM_NULL;
static SymbolID symbol_u64 = SYM_NULL;
static SymbolID symbol_u128 = SYM_NULL;
static SymbolID symbol_s8 = SYM_NULL;
static SymbolID symbol_s16 = SYM_NULL;
static SymbolID symbol_s32 = SYM_NULL;
static SymbolID symbol_s64 = SYM_NULL;
static SymbolID symbol_s128 = SYM_NULL;
static SymbolID symbol_f32 = SYM_NULL;
static SymbolID symbol_f64 = SYM_NULL;

static void ensureStaticSymbolsLoaded(void);

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
static void pushSymbol(Primer* primer, SymbolID defnID, void* type, AstNode* node, AstContext context, int isOverloadedDefn);
static Scope* pushFrame(Primer* primer, Scope* scope, AstContext ctx, AstNode* func);
static Frame popFrame(Primer* primer);
Frame* topFrame(Primer* primer);
Scope* topFrameScope(Primer* primer);
AstNode* topFrameFunc(Primer* primer);
static AstContext topFrameContext(Primer* primer);

static size_t allocatedScopeCount = 0;
static Scope allocatedScopes[MAX_AST_NODE_COUNT];
inline static Scope* newScope(Scope* parent, SymbolID defnID, void* type, AstNode* defn, AstContext context, int isOverloadedDefn);
static Scope* newRootScope(Typer* typer);
static Defn* lookupSymbolUntil(Scope* scope, SymbolID lookupID, Scope* endScopeP, AstContext context);

//
// Static implementation:
//

void ensureStaticSymbolsLoaded() {
    if (symbols_loaded == 0) {
        symbol_string = Symbol("String");
        symbol_unit = Symbol("Unit");
        symbol_u1   = Symbol("U1");
        symbol_u8   = Symbol("U8");
        symbol_u16  = Symbol("U16");
        symbol_u32  = Symbol("U32");
        symbol_u64  = Symbol("U64");
        symbol_u128 = Symbol("U128");
        symbol_s8   = Symbol("S8");
        symbol_s16  = Symbol("S16");
        symbol_s32  = Symbol("S32");
        symbol_s64  = Symbol("S64");
        symbol_s128 = Symbol("S128");
        symbol_f32  = Symbol("F32");
        symbol_f64  = Symbol("F64");
        symbols_loaded = 1;
    }
}

Primer* createPrimer(Typer* typer) {
    ensureStaticSymbolsLoaded();
    
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
void pushSymbol(Primer* primer, SymbolID defnID, void* type, AstNode* defnAstNode, AstContext context, int isOverloadedDefn) {
    if (defnID) {
        Scope* parent = topFrameScope(primer);
        Scope* scope = newScope(parent, defnID, type, defnAstNode, context, isOverloadedDefn);
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
            nodeKind == AST_VLAMBDA, 
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

inline Scope* newScope(Scope* parent, SymbolID defnID, void* type, AstNode* defnAstNode, AstContext context, int isOverloadedDefn) {
    Scope* scope = &allocatedScopes[allocatedScopeCount++];
    scope->parent = parent;
    scope->defnID = defnID;
    scope->type = type;
    scope->context = context;
    scope->defnAstNode = defnAstNode;
    scope->isOverloadedDefn = isOverloadedDefn;
    return scope;
}
Scope* newRootScope(Typer* typer) {
    Scope* root = NULL;
    
    //
    // Native scalar types:
    //

    root = newScope(root, symbol_unit, GetUnitType(typer), NULL, ASTCTX_TYPING, 0);

    root = newScope(root, symbol_string, GetStringType(typer), NULL, ASTCTX_TYPING, 0);

    root = newScope(root, symbol_u1, GetIntType(typer,INT_1,0), NULL, ASTCTX_TYPING, 0);
    root = newScope(root, symbol_u8, GetIntType(typer,INT_8,0), NULL, ASTCTX_TYPING, 0);
    root = newScope(root, symbol_u16, GetIntType(typer,INT_16,0), NULL, ASTCTX_TYPING, 0);
    root = newScope(root, symbol_u32, GetIntType(typer,INT_32,0), NULL, ASTCTX_TYPING, 0);
    root = newScope(root, symbol_u64, GetIntType(typer,INT_64,0), NULL, ASTCTX_TYPING, 0);
    root = newScope(root, symbol_u128, GetIntType(typer,INT_128,0), NULL, ASTCTX_TYPING, 0);

    root = newScope(root, symbol_s8, GetIntType(typer,INT_8,1), NULL, ASTCTX_TYPING, 0);
    root = newScope(root, symbol_s16, GetIntType(typer,INT_16,1), NULL, ASTCTX_TYPING, 0);
    root = newScope(root, symbol_s32, GetIntType(typer,INT_32,1), NULL, ASTCTX_TYPING, 0);
    root = newScope(root, symbol_s64, GetIntType(typer,INT_64,1), NULL, ASTCTX_TYPING, 0);
    root = newScope(root, symbol_s128, GetIntType(typer,INT_128,1), NULL, ASTCTX_TYPING, 0);

    root = newScope(root, symbol_f32, GetFloatType(typer,FLOAT_32), NULL, ASTCTX_TYPING, 0);
    root = newScope(root, symbol_f64, GetFloatType(typer,FLOAT_64), NULL, ASTCTX_TYPING, 0);

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
    
    // scripts:
    if (GetAstNodeKind(node) == AST_SCRIPT) {
        return 1;
    }

    // modules:
    else if (GetAstNodeKind(node) == AST_MODULE) {
        AstNode* module = node;

        // todo: push & bind the module namespace

        // defining all module-symbols in one go, storing as VALUE typing extensions:
        pushFrame(primer,NULL,ASTCTX_VALUE,topFrameFunc(primer));
        size_t moduleStmtLength = GetAstModuleLength(module);
        for (size_t index = 0; index < moduleStmtLength; index++) {
            // todo: HACKY let the symbol define itself as type or value in `PrimeScript`
            AstNode* stmt = GetAstModuleStmtAt(module, index);
            Loc loc = GetAstNodeLoc(stmt);
            AstKind stmtKind = GetAstNodeKind(stmt);
            if (stmtKind == AST_STMT_VDEF) {
                SymbolID lhs = GetAstDefValueStmtLhs(stmt);
                void* valueType = NewMetavarType(loc,primer->typer,"def-func:%s",GetSymbolText(lhs));
                pushSymbol(primer,lhs,valueType,stmt,ASTCTX_VALUE,1);
                SetAstNodeTypingExt_Value(stmt,valueType);
            } else if (stmtKind == AST_STMT_EXTERN) {
                SymbolID lhs = GetAstExternStmtName(stmt);
                void* valueType = NewMetavarType(loc,primer->typer,"extern:%s",GetSymbolText(lhs));
                pushSymbol(primer,lhs,valueType,stmt,ASTCTX_VALUE,1);
                SetAstNodeTypingExt_Value(stmt,valueType);
            } else if (stmtKind == AST_STMT_TDEF) {
                SymbolID lhs = GetAstTypedefStmtName(stmt);
                char const* symbolText = GetSymbolText(lhs);
                void* typingType = NewMetavarType(loc,primer->typer,"typedef:%s",symbolText);
                pushSymbol(primer,lhs,typingType,stmt,ASTCTX_TYPING,0);
                SetAstNodeTypingExt_Type(stmt, typingType);
            } else {
                FeedbackNote* note = CreateFeedbackNote("statement here...", loc, NULL);
                PostFeedback(FBK_ERROR, note, "Unsupported statement kind in module: %s", AstKindAsText(stmtKind));
                if (DEBUG) {
                    printf("!!- PrimeScript: Unsupported statement kind in module\n");
                } else {
                    assert(0 && "PrimeScript: Unsupported statement kind in module");
                }
            }
        }
        return 1;
    } 
    
    // all other kinds of nodes:
    else {
        AstNode* topFunc = topFrameFunc(primer);
        if (topFunc) {
            SetAstNodeParentFunc(node,topFunc);
        }

        // whatever the node, we store if it is evaluated in a type or value context here:
        SetAstNodeLookupContext(node,topFrameContext(primer));
        
        AstKind kind = GetAstNodeKind(node);
        switch (kind) {
            case AST_TID:
            {
                SetAstIdLookupScope(node, topFrameScope(primer));
                break;
            }
            case AST_VID:
            {
                SetAstIdLookupScope(node, topFrameScope(primer));
                break;
            }
            case AST_VPAREN:
            case AST_CHAIN:
            {
                pushFrame(primer, NULL, ASTCTX_VALUE, topFrameFunc(primer));
                break;
            }
            case AST_TPATTERN_FIELD:
            case AST_VPATTERN_FIELD:
            case AST_TPATTERN_SINGLETON_FIELD:
            case AST_VPATTERN_SINGLETON_FIELD:
            {
                // defining and storing on pattern
                int isTyping = (kind == AST_TPATTERN_FIELD || kind == AST_TPATTERN_SINGLETON_FIELD);
                int isValue = (kind == AST_VPATTERN_FIELD || kind == AST_VPATTERN_SINGLETON_FIELD);

                Loc loc = GetAstNodeLoc(node);
                SymbolID defnID = GetAstFieldName(node);
                
                void* patternType = NewMetavarType(loc, primer->typer, "%cpattern:%s", (isValue ? 'v':'t'), GetSymbolText(defnID));
                pushSymbol(primer, defnID, patternType, node, (isValue ? ASTCTX_VALUE:ASTCTX_TYPING), 0);
                
                if (isValue) {
                    SetAstNodeTypingExt_Value(node,patternType);
                } else {
                    SetAstNodeTypingExt_Type(node,patternType);
                }

                if (isValue) {
                    // pushing a new typing frame for RHS in mixed (value/type) items:
                    pushFrame(primer,NULL,ASTCTX_TYPING,topFrameFunc(primer));
                }
                break;
            }
            case AST_VSTRUCT_FIELD:
            {
                // SymbolID defnID = GetAstFieldName(node);
                SetAstNodeTypingExt_Value(node, GetAstNodeTypingExt_Value(GetAstFieldRhs(node)));
                break;
            }
            case AST_VLAMBDA:
            {
                // pushing a new frame for the function's contents:
                pushFrame(primer,NULL,ASTCTX_VALUE,node);
                break;
            }
            case AST_STMT_EXTERN:
            case AST_STMT_TDEF:
            {
                pushFrame(primer,NULL,ASTCTX_TYPING,topFrameFunc(primer));
                break;
            }
            case AST_VCAST:
            {
                // push a value scope, let type2val push a separate type scope.
                pushFrame(primer,NULL,ASTCTX_VALUE,topFrameFunc(primer));
                break;
            }
            case AST_TYPE2VAL:
            {
                // push a type scope, just for this little typespec
                pushFrame(primer,NULL,ASTCTX_TYPING,topFrameFunc(primer));
                break;
            }
            case AST_VAL2TYPE:
            {
                // push a value scope, just for this little value
                pushFrame(primer,NULL,ASTCTX_VALUE,topFrameFunc(primer));
                break;
            }
            default:
            {
                break;
            }
        }
        return 1;
    }
}
int primer_post(void* rawPrimer, AstNode* node) {
    Primer* primer = rawPrimer;
    AstKind kind = GetAstNodeKind(node);
    switch (kind) {
        case AST_CHAIN:
        case AST_VPAREN:
        case AST_VLAMBDA:
        case AST_VPATTERN_FIELD:
        case AST_VPATTERN_SINGLETON_FIELD:
        case AST_STMT_EXTERN:
        case AST_STMT_TDEF:
        case AST_VCAST:
        case AST_TYPE2VAL:
        case AST_VAL2TYPE:
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
int PrimeScript(Primer* primer, AstNode* script) {
    
    if (DEBUG) {
        assert(GetAstNodeKind(script) == AST_SCRIPT);
    }
    
    // visiting the AST:
    if (!RecursivelyVisitAstNode(primer, script, primer_pre, primer_post)) {
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
