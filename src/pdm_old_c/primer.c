#include "primer.h"

#include <assert.h>

#include "stb/stretchy_buffer.h"

#include "useful.h"
#include "symbols.h"
#include "config.h"
#include "typer.h"
#include "code-printer.h"

//
// Type definitions:
//

struct Scope {
    Scope* parent;
    SymbolID defnID;
    AstNode* defnAstNode;
    Scope** dbgChildrenSb;
};
struct Frame {
    Scope* begScope;
    Scope* endScope;
    AstNode* moduleStmt;
    AstNode* vlambda;
};

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
    Frame* rootFrame;

    // the typer is used by the primer to create metatypes.
    Manager* typer;

    // new scopes can extend previous ones, and are organized into 'frames' stored in this stack:
    Frame* frameStackSB;
    int frameStackCount;
};

size_t allocatedPrimersCount = 0;
Primer allocatedPrimers[MAX_PRIMER_COUNT];

static Primer* createPrimer(Manager* typer);
static void pushSymbol(Primer* primer, SymbolID defnID, void* type, AstNode* node);
static Scope* pushFrame(Primer* primer, Scope* scope, AstNode* optFunc);
static Scope* pushFrameWithMod(Primer* primer, Scope* scope, AstNode* optFunc, AstNode* optModuleStmt);
static Frame popFrame(Primer* primer);
Frame* topFrame(Primer* primer);
Scope* topFrameScope(Primer* primer);
AstNode* topFrameFunc(Primer* primer);
AstNode* topFrameModuleStmt(Primer* primer);

static size_t allocatedScopeCount = 0;
static Scope allocatedScopes[MAX_AST_NODE_COUNT];
inline static Scope* newScope(Scope* parent, SymbolID defnID, void* type, AstNode* defn);
static Scope* newRootScope(Manager* typer, Frame* frame);
static Scope* newBuiltinTypedefScope(Manager* typer, Scope* prevScope, SymbolID name, void* type);
static DefnScope* lookupSymbolUntil(Scope* scope, SymbolID lookupID, Scope* endScopeP);

static void debugPrintPrimer(Primer* primer);
static void helpDebugPrintScopeSubtree(CodePrinter* cp, Scope* scope);

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

Primer* createPrimer(Manager* typer) {
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
    primer->rootFrame = malloc(sizeof(Frame));
    primer->root = newRootScope(typer, primer->rootFrame);
    
    pushFrame(primer,primer->root,topFrameFunc(primer));

    return primer;
}
void pushSymbol(Primer* primer, SymbolID defnID, void* type, AstNode* defnAstNode) {
    if (defnID) {
        Scope* parent = topFrameScope(primer);
        Scope* scope = newScope(parent, defnID, type, defnAstNode);
        primer->frameStackSB[primer->frameStackCount-1].endScope = scope;

        AstNode* topLambda = topFrameFunc(primer);
        if (topLambda) {
            DefnScope* defn = scope;
            AddAstLambdaDefn(topLambda,defn);
        }
    }
}
Scope* pushFrame(Primer* primer, Scope* optNewScope, AstNode* optFunc) {
    return pushFrameWithMod(primer, optNewScope, optFunc, NULL);
}
Scope* pushFrameWithMod(Primer* primer, Scope* optNewScope, AstNode* optFunc, AstNode* optModuleStmt) {
    if (optFunc) {
        AstKind nodeKind = GetAstNodeKind(optFunc);
        COMPILER_ASSERT_VA(
            nodeKind == AST_VLAMBDA, 
            "pushFrameWithMod: unexpected optFunc->kind: %s", AstKindAsText(nodeKind)
        );
    } else {
        optFunc = topFrameFunc(primer);
    }
    if (optModuleStmt) {
        AstKind nodeKind = GetAstNodeKind(optModuleStmt);
        COMPILER_ASSERT_VA(
            nodeKind == AST_STMT_MODULE,
            "pushFrameWithMod: unexpected optModuleStmt->kind: %s", AstKindAsText(nodeKind)
        );
    } else {
        optModuleStmt = topFrameModuleStmt(primer);
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
    Frame frame = {optNewScope,optNewScope,optModuleStmt,optFunc};
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
        return frame;
    } else {
        if (DEBUG) {
            printf("!!- primer: Cannot pop from an empty frame.\n");
        } else {
            assert(0 && "primer: Cannot pop from an empty frame.\n");
        }
        Frame frame;
        frame.begScope = NULL;
        frame.endScope = NULL;
        frame.moduleStmt = NULL;
        frame.vlambda = NULL;
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
        return frame->vlambda;
    }
    return NULL;
}
AstNode* topFrameModuleStmt(Primer* primer) {
    Frame* frame = topFrame(primer);
    if (frame) {
        return frame->moduleStmt;
    } else {
        return NULL;
    }
}

inline Scope* newScope(Scope* parent, SymbolID defnID, void* type, AstNode* defnAstNode) {
    Scope* scope = &allocatedScopes[allocatedScopeCount++];
    scope->parent = parent;
    scope->defnID = defnID;
    scope->defnAstNode = defnAstNode;
    
    scope->dbgChildrenSb = NULL;
    if (scope->parent) {
        sb_push(scope->parent->dbgChildrenSb,scope);
    }

    return scope;
}
Scope* newRootScope(Manager* typer, Frame* rootFrame) {
    Scope* prevScope = NULL;
    
    //
    // Native scalar types:
    //

    prevScope = newBuiltinTypedefScope(typer,prevScope,symbol_unit,GetUnitType(typer));
    rootFrame->begScope = prevScope;

    prevScope = newBuiltinTypedefScope(typer,prevScope,symbol_string,GetStringType(typer));
    
    prevScope = newBuiltinTypedefScope(typer, prevScope, symbol_u1, GetIntType(typer,INT_1,0));
    prevScope = newBuiltinTypedefScope(typer, prevScope, symbol_u8, GetIntType(typer,INT_8,0));
    prevScope = newBuiltinTypedefScope(typer, prevScope, symbol_u16, GetIntType(typer,INT_16,0));
    prevScope = newBuiltinTypedefScope(typer, prevScope, symbol_u32, GetIntType(typer,INT_32,0));
    prevScope = newBuiltinTypedefScope(typer, prevScope, symbol_u64, GetIntType(typer,INT_64,0));
    prevScope = newBuiltinTypedefScope(typer, prevScope, symbol_u128, GetIntType(typer,INT_128,0));

    prevScope = newBuiltinTypedefScope(typer, prevScope, symbol_s8, GetIntType(typer,INT_8,1));
    prevScope = newBuiltinTypedefScope(typer, prevScope, symbol_s16, GetIntType(typer,INT_16,1));
    prevScope = newBuiltinTypedefScope(typer, prevScope, symbol_s32, GetIntType(typer,INT_32,1));
    prevScope = newBuiltinTypedefScope(typer, prevScope, symbol_s64, GetIntType(typer,INT_64,1));
    prevScope = newBuiltinTypedefScope(typer, prevScope, symbol_s128, GetIntType(typer,INT_128,1));

    prevScope = newBuiltinTypedefScope(typer, prevScope, symbol_f32, GetFloatType(typer,FLOAT_32));
    prevScope = newBuiltinTypedefScope(typer, prevScope, symbol_f64, GetFloatType(typer,FLOAT_64));

    rootFrame->endScope = prevScope;
    rootFrame->vlambda = NULL;

    return prevScope;
}
Scope* newBuiltinTypedefScope(Manager* typer, Scope* prevScope, SymbolID name, void* type) {
    AstNode* node = NewAstBuiltinTypedefNode(name, type);
    return newScope(prevScope, name, type, node);
}
DefnScope* lookupSymbolUntil(Scope* scope, SymbolID lookupID, Scope* endScopeP) {
    if (lookupID == SYM_NULL) {
        return NULL;
    }
    if (scope->defnID == lookupID) {
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
            return lookupSymbolUntil(scope->parent, lookupID, endScopeP);
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

// earlydef stores a metavar on TypingExt_Value instead of waiting
// for visitor... 
// this allows shared access to multiple function scopes.
static int primer_pre_earlydef(void* primer, AstNode* node);

int primer_pre_earlydef(void* rawPrimer, AstNode* node) {
    Loc loc = GetAstNodeLoc(node);
    Primer* primer = rawPrimer;
    AstKind nodeKind = GetAstNodeKind(node);
    
    if (nodeKind == AST_SCRIPT) {
        pushFrame(primer, NULL, NULL);
        int scriptLen = GetAstScriptLength(node);
        for (int index = 0; index < scriptLen; index++) {
            AstNode* stmt = GetAstScriptStmtAt(node,index);

            if (0 == primer_pre_earlydef(primer, stmt)) {
                return 0;
            }
        }
        
        // wait till primer_post to pop
        return 1;
    }

    else if (nodeKind == AST_STMT_MODULE) {
        Type* moduleType = NewModuleType(primer->typer, node);
        SetAstNodeTypingExt_Value(node, moduleType);

        // defining a symbol before pushing a frame:
        SymbolID defnID = AstModuleStmt_GetName(node);
        pushSymbol(primer, defnID, moduleType, node);

        // pushing a content frame:
        pushFrameWithMod(primer, NULL, NULL, node);

        // defining all module-symbols in one go, with primer_pre_earlydef
        size_t moduleStmtLength = AstModuleStmt_GetLength(node);
        for (size_t index = 0; index < moduleStmtLength; index++) {
            // todo: HACKY let the symbol define itself as type or value in `PrimeScript`
            AstNode* stmt = AstModuleStmt_GetStmtAt(node, index);
            // Loc loc = GetAstNodeLoc(stmt);
            // AstKind stmtKind = GetAstNodeKind(stmt);
            
            if (0 == primer_pre_earlydef(primer, stmt)) {
                return 0;
            }
        }

        // wait to pop until primer_post.
        // this way, arguments and nested scopes are in-scope.

        return 1;
    }

    else if (nodeKind == AST_STMT_VDEF) {
        Loc loc = GetAstNodeLoc(node);

        SymbolID lhs = GetAstDefValueStmtLhs(node);
        void* valueType = NewMetavarType(loc,primer->typer,"def:%s",GetSymbolText(lhs));
        pushSymbol(primer,lhs,valueType,node);
        SetAstNodeTypingExt_Value(node,valueType);
        return 1;
    }
    else if (nodeKind == AST_STMT_LINK) {
        // Loc loc = GetAstNodeLoc(node);

        int itemCount = AstLinkStmt_CountItems(node);
        for (int index = 0; index < itemCount; index++) {
            AstNode* linkStmt = AstLinkStmt_GetItemAt(node,index);
            int res = primer_pre_earlydef(primer, linkStmt);
            if (res == 0) {
                return 0;
            }
        }
        return 1;
    }
    else if (nodeKind == AST_STMT_LINK_ITEM) {
        Loc loc = GetAstNodeLoc(node);

        SymbolID lhs = AstLinkItem_GetName(node);
        void* valueType = NewMetavarType(loc,primer->typer,"extern:%s",GetSymbolText(lhs));
        pushSymbol(primer,lhs,valueType,node);
        SetAstNodeTypingExt_Value(node,valueType);
        return 1;
    }
    else if (nodeKind == AST_STMT_TDEF) {
        Loc loc = GetAstNodeLoc(node);

        SymbolID lhs = GetAstTypedefStmtName(node);
        char const* symbolText = GetSymbolText(lhs);
        void* typingType = NewMetavarType(loc,primer->typer,"type:%s",symbolText);
        pushSymbol(primer,lhs,typingType,node);
        SetAstNodeTypingExt_Type(node, typingType);
        return 1;
    }
    else if (nodeKind == AST_STMT_IMPORT) {
        // todo: dispatch for the other module, prime, and prepare for type-checking.
        COMPILER_ERROR("NotImplemented: primer_pre_earlydef for AST_STMT_IMPORT");
        return 1;
    }
    else {
        FeedbackNote* note = CreateFeedbackNote("statement here...", loc, NULL);
        PostFeedback(FBK_ERROR, note, "Unsupported statement kind in module: %s", AstKindAsText(nodeKind));
        
        if (DEBUG) {
            COMPILER_ERROR_VA("Unsupported statement kind in module: %s", AstKindAsText(nodeKind));
        }

        // if (DEBUG) {
        //     printf("!!- PrimeScript: Unsupported statement kind in module\n");
        // } else {
        //     assert(0 && "PrimeScript: Unsupported statement kind in module");
        // }
        return 0;
    }
}

int primer_pre(void* rawPrimer, AstNode* node) {
    Primer* primer = rawPrimer;
    AstKind nodeKind = GetAstNodeKind(node);
    
    // for all nodes: setting a parent module and function
    SetAstNodeParentFunc(node, topFrameFunc(primer));
    SetAstNodeParentModuleStmt(node, topFrameModuleStmt(primer));

    // scripts & modules get predefed:
    if (nodeKind == AST_SCRIPT || nodeKind == AST_STMT_MODULE) {
        return primer_pre_earlydef(primer, node);
    }

    // all other kinds of nodes:
    else {
        AstNode* topFunc = topFrameFunc(primer);
        if (topFunc) {
            SetAstNodeParentFunc(node,topFunc);
        }

        switch (nodeKind) {
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
                pushFrame(primer, NULL, topFrameFunc(primer));
                break;
            }
            case AST_TPATTERN_FIELD:
            case AST_VPATTERN_FIELD:
            case AST_TPATTERN_SINGLETON_FIELD:
            case AST_VPATTERN_SINGLETON_FIELD:
            {
                // defining and storing on pattern
                int isTyping = (nodeKind == AST_TPATTERN_FIELD || nodeKind == AST_TPATTERN_SINGLETON_FIELD);
                int isValue = (nodeKind == AST_VPATTERN_FIELD || nodeKind == AST_VPATTERN_SINGLETON_FIELD);
                COMPILER_ASSERT(isTyping ^ isValue, "Invalid typing/value pattern setup.");

                Loc loc = GetAstNodeLoc(node);
                SymbolID defnID = GetAstFieldName(node);
                
                void* patternType = NewMetavarType(loc, primer->typer, "%cpattern:%s", (isValue ? 'v':'t'), GetSymbolText(defnID));
                pushSymbol(primer, defnID, patternType, node);
                
                if (isValue) {
                    SetAstNodeTypingExt_Value(node,patternType);
                } else {
                    SetAstNodeTypingExt_Type(node,patternType);
                }

                if (isValue) {
                    // pushing a new typing frame for RHS in mixed (value/type) items:
                    pushFrame(primer,NULL,topFrameFunc(primer));
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
                AstNode* lambda = node;
                pushFrame(primer,NULL,lambda);
                break;
            }
            case AST_STMT_LINK:
            case AST_STMT_TDEF:
            {
                pushFrame(primer,NULL,topFrameFunc(primer));
                break;
            }
            case AST_VCAST:
            {
                // push a value scope, let type2val push a separate type scope.
                pushFrame(primer,NULL,topFrameFunc(primer));
                break;
            }
            case AST_TYPE2VAL:
            {
                // push a type scope, just for this little typespec
                pushFrame(primer,NULL,topFrameFunc(primer));
                break;
            }
            case AST_VAL2TYPE:
            {
                // push a value scope, just for this little value
                pushFrame(primer,NULL,topFrameFunc(primer));
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
        case AST_SCRIPT:
        case AST_STMT_MODULE:
        {
            // popping, setting the content frame:
            Frame frame = popFrame(primer);
            Frame* framePtr = malloc(sizeof(Frame));
            *framePtr = frame;
            SetAstModuleContentFrame(node, framePtr);
            break;
        }

        case AST_CHAIN:
        case AST_VPAREN:
        case AST_VLAMBDA:
        case AST_VPATTERN_FIELD:
        case AST_VPATTERN_SINGLETON_FIELD:
        case AST_STMT_LINK:
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
// Debug printing:
//
//

void debugPrintPrimer(Primer* primer) {
    CodePrinter printer = CreateCodePrinter(stdout, 0);
    PrintText(
        &printer,
        "Scoper Dump Key\n"
        "- 'scope-kind <id> -(*)'  indicates 0 children\n"
        "- 'scope-kind <id> -> \\n' indicates 1 child, next line\n"
        "- 'scope-kind <id> -> { ... }' indicates many children\n"
        "- start from primer->rootFrame->begScope:"
    );
    IndentPrinter(&printer);
    PrintText(&printer, "\n");
    helpDebugPrintScopeSubtree(&printer, primer->rootFrame->begScope);
    DeIndentPrinter(&printer);
    PrintText(&printer, "\n");
}
void helpDebugPrintScopeSubtree(CodePrinter* cp, Scope* scope) {
    if (DEBUG && scope != NULL) {
        PrintText(cp, "scope ");
        PrintText(cp, GetSymbolText(scope->defnID));
        
        int subtreeCount = sb_count(scope->dbgChildrenSb);
        if (subtreeCount == 0) {
            // IndentPrinter(cp);
            PrintText(cp, " -(*)");
            // DeIndentPrinter(cp);
        }
        else if (subtreeCount == 1) {
            PrintText(cp, " -> \n");
            Scope* childScope = scope->dbgChildrenSb[0];
            helpDebugPrintScopeSubtree(cp, childScope);
            // PrintText(cp, "} (");
            // PrintText(cp, GetSymbolText(scope->defnID));
            // PrintText(cp, ")\n");
        }
        else if (subtreeCount >= 1) {
            PrintText(cp, " -> {");
            IndentPrinter(cp);
            PrintText(cp, "\n");
            
            for (int subtreeIndex = 0; subtreeIndex < subtreeCount; subtreeIndex++) {
                Scope* childScope = scope->dbgChildrenSb[subtreeIndex];
                helpDebugPrintScopeSubtree(cp, childScope);
                if (subtreeIndex != subtreeCount-1) {
                    PrintText(cp, "\n");
                }
            }
            DeIndentPrinter(cp);
            PrintText(cp, "\n");

            PrintText(cp, "}");
            if (subtreeCount > 0) {
                PrintText(cp, " (");
                PrintText(cp, GetSymbolText(scope->defnID));
                PrintText(cp, ")");
            }
        }
    }
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

    if (DEBUG) {
        debugPrintPrimer(primer);
    }

    return 1;
}
DefnScope* LookupSymbol(Scope* scope, SymbolID lookupID) {
    return lookupSymbolUntil(scope, lookupID, NULL);
}
DefnScope* LookupSymbolUntil(Scope* scope, SymbolID lookupID, Scope* endScopeP) {
    return lookupSymbolUntil(scope, lookupID, endScopeP);
}
DefnScope* LookupSymbolInFrame(Frame* frame, SymbolID lookupID) {
    return lookupSymbolUntil(frame->endScope, lookupID, frame->begScope);
}

// After definition, IDs are looked up, map to type IDs.
// These type IDs can be stored in the AST.

SymbolID GetDefnName(DefnScope* defn) {
    return defn->defnID;
}
AstNode* GetDefnNode(DefnScope* defn) {
    return defn->defnAstNode;
}
