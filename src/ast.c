#include "ast.h"

#include <assert.h>

#include "useful.h"
#include "config.h"
#include "source.h"
#include "symbols.h"
#include "primer.h"

#include "stb/stretchy_buffer.h"

typedef struct AstModule   AstModule;
typedef struct AstID       AstID;
typedef union  AstInfo     AstInfo;
typedef struct AstNodeList AstNodeList;
typedef struct AstCall     AstCall;
typedef struct AstCast     AstCast;
typedef struct AstField    AstField;
typedef enum   AstBinaryOperator AstBinaryOperator;
typedef struct AstDotIndex AstDotIndex;
typedef struct AstDotName  AstDotName;
typedef struct AstLambda   AstLambda;
typedef struct AstLet      AstLet;
typedef struct AstDef      AstDef;
typedef struct AstVal      AstVal;
typedef struct AstExtern   AstExtern;
typedef struct AstTypedef  AstTypedef;
typedef struct AstCheck    AstCheck;
typedef struct AstUnary    AstUnary;
typedef struct AstBinary   AstBinary;
typedef struct AstInt      AstInt;
typedef struct AstChain    AstChain;
typedef struct AstStruct   AstStruct;

struct AstNodeList {
    size_t count;
    AstNodeList* next;
    AstNode* items[MAX_AST_NODES_PER_LIST];
};

struct AstModule {
    SymbolID name;
    AstNodeList* items;
    AstNode* importHeader;
    AstNode* exportHeader;
};
struct AstID {
    SymbolID name;
    void* lookupScope;
    void* defn;
};
struct AstField {
    SymbolID name;
    AstNode* rhs;
    int index;
    AstNode* parent;
};
struct AstDotIndex {
    AstNode* lhs;
    size_t index;
};
struct AstDotName {
    AstNode* lhs;
    SymbolID symbol;
};
struct AstLambda {
    AstNodeList* patternList;
    AstNode* body;
    Defn** capturesSB;
    Defn** localsSB;
};
struct AstLet {
    SymbolID lhs;
    AstNode* optTypespec;
    AstNode* rhs;
};
struct AstDef {
    SymbolID lhs;
    AstNode* optTemplatePattern;
    AstNode* rhs;
};
struct AstVal {
    SymbolID lhs;
    AstNode* optTemplatePattern;
    AstNode* bodyPattern;
};
struct AstExtern {
    SymbolID name;
    AstNode* typespec;
};
struct AstTypedef {
    SymbolID name;
    AstNode* optPattern;
    AstNode* optRhs;
    // void* valueDefnType;
};
struct AstCheck {
    AstNode* checked;
};
struct AstCall {
    AstNode* lhs;
    AstNodeList* args;
    int isTemplateCall;
};
struct AstCast {
    AstNode* castTypespec;
    AstNode* rhs;
};
struct AstUnary {
    AstUnaryOperator operator;
    AstNode* operand;
};
struct AstBinary {
    AstBinaryOperator operator;
    AstNode* ltOperand;
    AstNode* rtOperand;
};
struct AstInt {
    size_t value;
    int base;
};
struct AstChain {
    AstNodeList* prefix;
    AstNode* result;
};

union AstInfo {
    AstModule       Module;
    AstID           ID;
    AstUnary        Unary;
    AstBinary       Binary;
    AstInt          Int;
    long double     Float;
    int*            UnicodeStringSb;
    AstNodeList*    GenericList_items;
    AstCall         Call;
    AstCast         Cast;
    AstNode*        CastTypespec;
    AstField        Field;
    AstDotIndex     DotIx;
    AstDotName      DotNm;
    AstLambda       Lambda;
    AstLet          Let;
    AstDef          Def;
    AstVal          Val;
    AstExtern       Extern;
    AstTypedef      Typedef;
    AstCheck        Check;
    AstChain        Chain;
    AstNode*        Paren_item;
};

struct AstNode {
    Loc loc;
    AstKind kind;
    AstInfo as;
    int typingExtCount_v;
    int typingExtCount_t;
    void* typingExt_v;
    void* typingExt_t;
    AstContext lookupContext;
    void* llvmRepr;
    AstNode* parentFunc;
};

//
// Constructor helpers:
//

static size_t allocatedNodeCount = 0;
static AstNode allocatedNodes[MAX_AST_LIST_COUNT];

static size_t allocatedListCount = 0;
static AstNodeList allocatedLists[MAX_AST_LIST_COUNT];

static AstNode* newNode(Loc loc, AstKind kind);
static AstNodeList* newNodeList(void);
static void pushListElement(AstNodeList* list, AstNode* node);
static int countList(AstNodeList* list);
static AstNode* listItemAt(AstNodeList* list, int index);

AstNode* newNode(Loc loc, AstKind kind) {
    AstNode* node = &allocatedNodes[allocatedNodeCount++];
    node->loc = loc;
    node->kind = kind;
    node->typingExt_v = NULL;
    node->typingExt_t = NULL;
    node->lookupContext = __ASTCTX_NONE;
    node->llvmRepr = NULL;
    node->parentFunc = NULL;
    return node;
}
AstNodeList* newNodeList(void) {
    AstNodeList* listP = &allocatedLists[allocatedListCount++];
    listP->count = 0;
    listP->next = NULL;
    return listP;
}
void pushListElement(AstNodeList* list, AstNode* node) {
    if (list->count == MAX_AST_NODES_PER_LIST) {
        if (!list->next) {
            list->next = newNodeList();
        }
        return pushListElement(list->next, node);
    } else {
        size_t index = list->count++;
        list->items[index] = node;
    }
}
int countList(AstNodeList* list) {
    int countSoFar = list->count;
    if (list->next) {
        return countSoFar + countList(list->next);
    } else {
        return countSoFar;
    }
}
AstNode* listItemAt(AstNodeList* list, int index) {
    if (DEBUG) {
        if (index < 0) {
            COMPILER_ERROR("listItemAt: invalid list index");
            return NULL;
        }
    }
    if (index >= MAX_AST_NODES_PER_LIST) {
        return listItemAt(list->next, index - MAX_AST_NODES_PER_LIST);
    } else {
        return list->items[index];
    }
}

//
// Constructor implementations:
//

static int isStmtKindModuleLevel(AstKind kind);
static int isIdKind(AstKind kind);
static int isCallKind(AstKind kind);
static AstNode* helpCreateAstCall(Loc loc, AstKind kind, AstNode* lhs, AstNode* args[], int argsCount);

int isStmtKindModuleLevel(AstKind kind) {
    return (
        kind == AST_DEF_VALUE ||
        kind == AST_DEF_TYPE ||
        kind == AST_EXTERN ||
        0
    );
}
int isIdKind(AstKind kind) {
    return (
        kind == AST_TID ||
        kind == AST_VID ||
        0
    );
}
int isCallKind(AstKind kind) {
    return (
        kind == AST_TCALL ||
        kind == AST_VCALL ||
        0
    );
}
AstNode* helpCreateAstCall(Loc loc, AstKind kind, AstNode* lhs, AstNode* args[], int argsCount) {
    AstNode* callNode = newNode(loc,kind);
    callNode->as.Call.lhs = lhs;
    callNode->as.Call.args = newNodeList();
    for (int index = 0; index < argsCount; index++) {
        AstNode* arg = args[index];
        pushListElement(callNode->as.Call.args,arg);
    }
    return callNode;
}

AstNode* CreateAstModule(Loc loc, SymbolID moduleID) {
    AstNode* node = newNode(loc, AST_MODULE);
    node->as.Module.name = moduleID;
    node->as.Module.items = newNodeList();
    return node;
}

void AttachImportHeaderToAstModule(AstNode* module, AstNode* mapping) {
    module->as.Module.importHeader = mapping;
}
void AttachExportHeaderToAstModule(AstNode* module, AstNode* mapping) {
    module->as.Module.exportHeader = mapping;
}
void PushStmtToAstModule(AstNode* module, AstNode* def) {
    AstKind nodeKind = GetAstNodeKind(def);
    COMPILER_ASSERT(isStmtKindModuleLevel(nodeKind), "Cannot push non-def/extern to AstModule.");
    pushListElement(module->as.Module.items, def);
}

AstNode* CreateAstVID(Loc loc, SymbolID symbolID) {
    AstNode* idNode = newNode(loc, AST_VID);
    idNode->as.ID.name = symbolID;
    idNode->as.ID.lookupScope = NULL;
    idNode->as.ID.defn = NULL;
    return idNode;
}
AstNode* CreateAstIntLiteral(Loc loc, size_t value, int base) {
    AstNode* intNode = newNode(loc, AST_LITERAL_INT);
    intNode->as.Int.value = value;
    intNode->as.Int.base = base;
    return intNode;
}
AstNode* CreateAstFloatLiteral(Loc loc, long double value) {
    AstNode* floatNode = newNode(loc, AST_LITERAL_FLOAT);
    floatNode->as.Float = value;
    return floatNode;
}
AstNode* CreateAstStringLiteral(Loc loc, int* valueSb) {
    AstNode* stringNode = newNode(loc, AST_LITERAL_STRING);
    stringNode->as.UnicodeStringSb = valueSb;
    return stringNode;
}
AstNode* CreateAstVParen(Loc loc, AstNode* it) {
    AstNode* parenNode = newNode(loc, AST_VPAREN);
    parenNode->as.Paren_item = it;
    return parenNode;
}
AstNode* CreateAstUnit(Loc loc) {
    return newNode(loc, AST_UNIT);
}

AstNode* CreateAstVTuple(Loc loc) {
    AstNode* tupleNode = newNode(loc, AST_VTUPLE);
    tupleNode->as.GenericList_items = newNodeList();
    return tupleNode;
}
AstNode* CreateAstStruct(Loc loc) {
    AstNode* structNode = newNode(loc, AST_VSTRUCT);
    structNode->as.GenericList_items = newNodeList();
    return structNode;
}

AstNode* CreateAstChain(Loc loc) {
    AstNode* chainNode = newNode(loc, AST_CHAIN);
    chainNode->as.Chain.prefix = newNodeList();
    chainNode->as.Chain.result = NULL;
    return chainNode;
}

AstNode* CreateAstPattern(Loc loc, int isTemplatePattern) {
    AstNode* patternNode = newNode(loc, isTemplatePattern ? AST_T_PATTERN:AST_V_PATTERN);
    patternNode->as.GenericList_items = newNodeList();
    patternNode->as.GenericList_items->count = 0;
    return patternNode;
}

void PushFieldToAstTuple(Loc loc, AstNode* tuple, AstNode* value) {
    AstNode* field = newNode(loc, AST_FIELD__TUPLE_ITEM);
    field->as.Field.name = SYM_NULL;
    field->as.Field.rhs = value;
    field->as.Field.index = countList(tuple->as.GenericList_items);
    field->as.Field.parent = tuple;
    pushListElement(tuple->as.GenericList_items, field);
}
void PushFieldToAstStruct(Loc loc, AstNode* struct_, SymbolID name, AstNode* value) {
    AstNode* field = newNode(loc, AST_FIELD__STRUCT_ITEM);
    field->as.Field.name = name;
    field->as.Field.rhs = value;
    field->as.Field.index = countList(struct_->as.GenericList_items);
    field->as.Field.parent = struct_;
    pushListElement(struct_->as.GenericList_items, field);
}
void PushFieldToAstPattern(Loc loc, AstNode* pattern, SymbolID name, AstNode* typespec) {
    assert(pattern->kind == AST_T_PATTERN || pattern->kind == AST_V_PATTERN);
    AstKind fieldKind = (pattern->kind == AST_T_PATTERN ? AST_FIELD__TEMPLATE_ITEM : AST_FIELD__PATTERN_ITEM);
    AstNode* field = newNode(loc, fieldKind);
    field->as.Field.name = name;
    field->as.Field.rhs = typespec;
    field->as.Field.index = countList(pattern->as.GenericList_items);
    field->as.Field.parent = pattern;
    pushListElement(pattern->as.GenericList_items, field);
}
void PushStmtToAstChain(AstNode* chain, AstNode* statement) {
    pushListElement(chain->as.Chain.prefix, statement);
}
void SetAstChainResult(AstNode* chain, AstNode* result) {
    chain->as.Chain.result = result;
}

AstNode* CreateAstIte(Loc loc, AstNode* cond, AstNode* ifTrue, AstNode* ifFalse) {
    AstNode* iteNode = newNode(loc, AST_ITE);
    iteNode->as.GenericList_items = newNodeList();
    pushListElement(iteNode->as.GenericList_items, cond);
    pushListElement(iteNode->as.GenericList_items, ifTrue);
    pushListElement(iteNode->as.GenericList_items, ifFalse);
    return iteNode;
}

AstNode* CreateAstDotIndex(Loc loc, AstNode* lhs, size_t index) {
    AstNode* dotNode = newNode(loc, AST_DOT_INDEX);
    dotNode->as.DotIx.lhs = lhs;
    dotNode->as.DotIx.index = index;
    return dotNode;
}

AstNode* CreateAstDotName(Loc loc, AstNode* lhs, SymbolID rhs) {
    AstNode* dotNode = newNode(loc, AST_DOT_NAME);
    dotNode->as.DotNm.lhs = lhs;
    dotNode->as.DotNm.symbol = rhs;
    return dotNode;
}

AstNode* CreateAstLambda(Loc loc, AstNode** patterns, int patternCount, AstNode* body) {
    AstNode* lambdaNode = newNode(loc, AST_LAMBDA);
    lambdaNode->as.Lambda.patternList = newNodeList(); {
        for (int patternIndex = 0; patternIndex < patternCount; patternIndex++) {
            AstNode* pattern = patterns[patternIndex];
            pushListElement(lambdaNode->as.Lambda.patternList,pattern);
        }
    }
    lambdaNode->as.Lambda.body = body;
    lambdaNode->as.Lambda.capturesSB = NULL;
    lambdaNode->as.Lambda.localsSB = NULL;
    return lambdaNode;
}
void AddAstLambdaDefn(AstNode* lambda, void* rawDefn) {
    Defn* defn = rawDefn;
    sb_push(lambda->as.Lambda.localsSB,defn);
}
void ReqAstLambdaDefn(AstNode* lambda, void* rawDefn) {
    Defn* defn = rawDefn;
    int localCount = sb_count(lambda->as.Lambda.localsSB);
    for (int localIndex = 0; localIndex < localCount; localIndex++) {
        Defn* localDefn = lambda->as.Lambda.localsSB[localIndex];
        if (defn == localDefn) {
            // this defn was a local. returning early.
            return;
        }
    }

    // this defn was a capture.
    int captureCount = sb_count(lambda->as.Lambda.capturesSB);
    int pushReq = 1;
    for (int captureIndex = 0; captureIndex < captureCount; captureIndex++) {
        Defn* captureDefn = lambda->as.Lambda.capturesSB[captureIndex];
        if (defn == captureDefn) {
            // this defn was a capture that was already added. returning early.
            pushReq = 0;
            break;
        }
    }
    if (pushReq) {
        sb_push(lambda->as.Lambda.capturesSB,defn);
        if (lambda->parentFunc) {
            ReqAstLambdaDefn(lambda->parentFunc,defn);
        }
    }
}
int CountAstLambdaCaptures(AstNode* lambda) {
    return sb_count(lambda->as.Lambda.capturesSB);
}
void* GetAstLambdaCaptureAt(AstNode* lambda, int index) {
    return lambda->as.Lambda.capturesSB[index];
}

AstNode* CreateAstLetStmt(Loc loc, SymbolID lhs, AstNode* optTypespec, AstNode* rhs) {
    AstNode* letNode = newNode(loc, AST_LET);
    letNode->as.Let.lhs = lhs;
    letNode->as.Let.optTypespec = optTypespec;
    letNode->as.Let.rhs = rhs;
    return letNode;
}
AstNode* CreateAstDefValueStmt(Loc loc, SymbolID lhs, AstNode* optTemplatePattern, AstNode* patterns[], int patternsCount, AstNode* rhs) {
    COMPILER_ASSERT(patternsCount > 0 && patterns, "Cannot create a 'def' statement with 0 patterns. Create a 'let' statement instead.");

    AstNode* defNode = newNode(loc, AST_DEF_VALUE);
    defNode->as.Def.lhs = lhs;
    defNode->as.Def.optTemplatePattern = optTemplatePattern;
    
    // de-sugaring patterns into a lambda:
    defNode->as.Def.rhs = CreateAstLambda(loc,patterns,patternsCount,rhs);
    
    // todo: un-disable multi-pattern def statements
    int multiPatternDefStatementsDisabled = 1;
    if (multiPatternDefStatementsDisabled && patternsCount > 1) {
        COMPILER_ERROR("DISABLED: multi-pattern 'def' statements.\n");
        return NULL;
    }

    return defNode;
}
AstNode* CreateAstDefTypeStmt(Loc loc, SymbolID lhs, AstNode* optPattern, AstNode* optRhs) {
    AstNode* td = newNode(loc, AST_DEF_TYPE);
    td->as.Typedef.name = lhs;
    td->as.Typedef.optPattern = optPattern;
    td->as.Typedef.optRhs = optRhs;
    return td;
}
AstNode* CreateAstExternStmt(Loc loc, SymbolID lhs, AstNode* typespec) {
    AstNode* defNode = newNode(loc, AST_EXTERN);
    defNode->as.Extern.name = lhs;
    defNode->as.Extern.typespec = typespec;
    return defNode;
}

AstNode* CreateAstWithStmt(Loc loc, AstNode* checked) {
    AstNode* checkNode = newNode(loc, AST_STMT_WITH);
    checkNode->as.Check.checked = checked;
    return checkNode;
}

AstNode* CreateAstVCall(Loc loc, AstNode* lhs, AstNode* args[], int argsCount) {
    return helpCreateAstCall(loc,AST_VCALL,lhs,args,argsCount);
}
AstNode* CreateAstTCall(Loc loc, AstNode* lhs, AstNode* args[], int argsCount) {
    return helpCreateAstCall(loc,AST_TCALL,lhs,args,argsCount);
}
AstNode* CreateAstUnary(Loc loc, AstUnaryOperator op, AstNode* arg) {
    AstNode* unaryNode = newNode(loc, AST_UNARY);
    unaryNode->as.Unary.operator = op;
    unaryNode->as.Unary.operand = arg;
    return unaryNode;
}
AstNode* CreateAstBinary(Loc loc, AstBinaryOperator op, AstNode* ltArg, AstNode* rtArg) {
    AstNode* binaryNode = newNode(loc, AST_BINARY);
    binaryNode->as.Binary.operator = op;
    binaryNode->as.Binary.ltOperand = ltArg;
    binaryNode->as.Binary.rtOperand = rtArg;
    return binaryNode;
}

AstNode* NewAstTID(Loc loc, SymbolID symbolID) {
    AstNode* idNode = newNode(loc, AST_TID);
    idNode->as.ID.name = symbolID;
    idNode->as.ID.lookupScope = NULL;
    idNode->as.ID.defn = NULL;
    return idNode;
}
AstNode* NewAstTTuple(Loc loc) {
    AstNode* tupleNode = newNode(loc,AST_TTUPLE);
    tupleNode->as.GenericList_items = newNodeList();
    return tupleNode;
}
AstNode* NewAstTParen(Loc loc, AstNode* it) {
    AstNode* parenNode = newNode(loc,AST_TPAREN);
    parenNode->as.Paren_item = it;
    return parenNode;
}

//
// Getter implementation:
//

SymbolID GetAstModuleName(AstNode* module) {
    return module->as.Module.name;
}
int GetAstModuleLength(AstNode* module) {
    return countList(module->as.Module.items);
}
AstNode* GetAstModuleStmtAt(AstNode* module, int index) {
    return listItemAt(module->as.Module.items, index);
}

size_t GetAstNodeKey(AstNode* node) {
    return (size_t)(node - allocatedNodes);
}

Loc GetAstNodeLoc(AstNode* node) {
    return node->loc;
}

AstKind GetAstNodeKind(AstNode* node) {
    return node->kind;
}

SymbolID GetAstIdName(AstNode* node) {
    if (DEBUG) {
        assert(isIdKind(node->kind));
    }
    return node->as.ID.name;
}

size_t GetAstIntLiteralValue(AstNode* node) {
    return node->as.Int.value;
}
int GetAstIntLiteralBase(AstNode* node) {
    return node->as.Int.base;
}
long double GetAstFloatLiteralValue(AstNode* node) {
    return node->as.Float;
}
int const* GetAstStringLiteralValue(AstNode* node) {
    return node->as.UnicodeStringSb;
}
AstNode* GetAstParenItem(AstNode* node) {
    if (DEBUG) {
        assert(node->kind == AST_VPAREN);
    }
    return node->as.Paren_item;
}

int GetAstTupleLength(AstNode* node) {
    return countList(node->as.GenericList_items);
}
int GetAstStructLength(AstNode* node) {
    return countList(node->as.GenericList_items);
}
int GetAstPatternLength(AstNode* node) {
    return countList(node->as.GenericList_items);
}
int GetAstChainPrefixLength(AstNode* node) {
    return countList(node->as.Chain.prefix);
}
AstNode* GetAstChainResult(AstNode* node) {
    return node->as.Chain.result;
}

AstNode* GetAstTupleItemAt(AstNode* node, int index) {
    if (DEBUG) {
        assert(node->kind == AST_VTUPLE);
    }
    return listItemAt(node->as.GenericList_items, index);
}
AstNode* GetAstStructFieldAt(AstNode* node, int index) {
    if (DEBUG) {
        assert(node->kind == AST_VSTRUCT);
    }
    return listItemAt(node->as.GenericList_items, index);
}
AstNode* GetAstPatternFieldAt(AstNode* node, int index) {
    if (DEBUG) {
        assert(node->kind == AST_T_PATTERN || node->kind == AST_V_PATTERN);
    }
    return listItemAt(node->as.GenericList_items, index);
}
AstNode* GetAstChainPrefixStmtAt(AstNode* node, int index) {
    if (DEBUG) {
        assert(node->kind == AST_CHAIN);
    }
    return listItemAt(node->as.Chain.prefix, index);
}

AstNode* GetAstIteCond(AstNode* ite) {
    if (DEBUG) {
        assert(ite->kind == AST_ITE);
    }
    return listItemAt(ite->as.GenericList_items, 0);
}
AstNode* GetAstIteIfTrue(AstNode* ite) {
    if (DEBUG) {
        assert(ite->kind == AST_ITE);
    }
    return listItemAt(ite->as.GenericList_items, 1);
}
AstNode* GetAstIteIfFalse(AstNode* ite) {
    if (DEBUG) {
        assert(ite->kind == AST_ITE);
    }
    return listItemAt(ite->as.GenericList_items, 2);
}

AstNode* GetAstDotIndexLhs(AstNode* dot) {
    if (DEBUG) {
        assert(dot->kind == AST_DOT_INDEX);
    }
    return dot->as.DotIx.lhs;
}
size_t GetAstDotIndexRhs(AstNode* dot) {
    if (DEBUG) {
        assert(dot->kind == AST_DOT_INDEX);
    }
    return dot->as.DotIx.index;
}

AstNode* GetAstDotNameLhs(AstNode* dot) {
    if (DEBUG) {
        assert(dot->kind == AST_DOT_NAME);
    }
    return dot->as.DotNm.lhs;
}
SymbolID GetAstDotNameRhs(AstNode* dot) {
    if (DEBUG) {
        assert(dot->kind == AST_DOT_NAME);
    }
    return dot->as.DotNm.symbol;
}

int CountAstLambdaPatterns(AstNode* lambda) {
    return countList(lambda->as.Lambda.patternList);
}
AstNode* GetAstLambdaPatternAt(AstNode* node, int index) {
    if (DEBUG) {
        assert(node->kind == AST_LAMBDA);
    }
    return listItemAt(node->as.Lambda.patternList,index);
}
AstNode* GetAstLambdaBody(AstNode* node) {
    if (DEBUG) {
        assert(node->kind == AST_LAMBDA);
    }
    return node->as.Lambda.body;
}

SymbolID GetAstLetStmtLhs(AstNode* bindStmt) {
    if (DEBUG) {
        assert(bindStmt->kind == AST_LET);
    }
    return bindStmt->as.Let.lhs;
}
AstNode* GetAstLetStmtRhs(AstNode* bindStmt) {
    if (DEBUG) {
        assert(bindStmt->kind == AST_LET);
    }
    return bindStmt->as.Let.rhs;
}

AstNode* GetAstWithStmtChecked(AstNode* checkStmt) {
    if (DEBUG) {
        assert(checkStmt->kind == AST_STMT_WITH);
    }
    return checkStmt->as.Check.checked;
}

AstNode* GetAstCallLhs(AstNode* call) {
    if (DEBUG) {
        assert(isCallKind(call->kind) && "GetAstCallLhs on non-call!");
    }
    return call->as.Call.lhs;
}
int GetAstCallArgCount(AstNode* call) {
    return countList(call->as.Call.args);
}
AstNode* GetAstCallArgAt(AstNode* call, int index) {
    return listItemAt(call->as.Call.args,index);
}
int IsAstCallTemplate(AstNode* call) {
    if (DEBUG) {
        assert(isCallKind(call->kind));
    }
    return call->kind == AST_TCALL;
}

SymbolID GetAstFieldName(AstNode* field) {
    if (DEBUG) {
        assert(
            field->kind == AST_FIELD__PATTERN_ITEM ||
            field->kind == AST_FIELD__STRUCT_ITEM ||
            field->kind == AST_FIELD__TEMPLATE_ITEM ||
            field->kind == AST_FIELD__TUPLE_ITEM
        );
    }
    return field->as.Field.name;
}
AstNode* GetAstFieldRhs(AstNode* field) {
    if (DEBUG) {
        assert(
            field->kind == AST_FIELD__PATTERN_ITEM ||
            field->kind == AST_FIELD__STRUCT_ITEM ||
            field->kind == AST_FIELD__TEMPLATE_ITEM ||
            field->kind == AST_FIELD__TUPLE_ITEM
        );
    }
    return field->as.Field.rhs;
}
int GetAstFieldIndex(AstNode* field) {
    return field->as.Field.index;
}
AstNode* GetAstFieldParent(AstNode* field) {
    return field->as.Field.parent;
}

AstUnaryOperator GetAstUnaryOperator(AstNode* unary) {
    if (DEBUG) {
        assert(unary->kind == AST_UNARY);
    }
    return unary->as.Unary.operator;
}
AstNode* GetAstUnaryOperand(AstNode* unary) {
    if (DEBUG) {
        assert(unary->kind == AST_UNARY);
    }
    return unary->as.Unary.operand;
}

AstBinaryOperator GetAstBinaryOperator(AstNode* binary) {
    if (DEBUG) {
        assert(binary->kind == AST_BINARY);
    }
    return binary->as.Binary.operator;
}
AstNode* GetAstBinaryLtOperand(AstNode* binary) {
    if (DEBUG) {
        assert(binary->kind == AST_BINARY);
    }
    return binary->as.Binary.ltOperand;
}
AstNode* GetAstBinaryRtOperand(AstNode* binary) {
    if (DEBUG) {
        assert(binary->kind == AST_BINARY);
    }
    return binary->as.Binary.rtOperand;
}

AstNode* GetAstDefValueStmtOptTemplatePattern(AstNode* def) {
    return def->as.Def.optTemplatePattern;
}
int GetAstDefValueStmtArgCount(AstNode* def) {
    
}
AstNode* GetAstDefValueStmtArgAt(AstNode* def) {

}
SymbolID GetAstDefValueStmtLhs(AstNode* def) {
    return def->as.Def.lhs;
}
AstNode* GetAstDefValueStmtRhs(AstNode* def) {
    return def->as.Def.rhs;
}

SymbolID GetAstValStmtLhs(AstNode* valStmt) {
    return valStmt->as.Val.lhs;
}
AstNode* GetAstValStmtOptTemplatePattern(AstNode* valStmt) {
    return valStmt->as.Val.optTemplatePattern;
}
AstNode* GetAstValStmtPattern(AstNode* valStmt) {
    return valStmt->as.Val.bodyPattern;
}

SymbolID GetAstExternStmtName(AstNode* externDef) {
    return externDef->as.Extern.name;
}
AstNode* GetAstExternTypespec(AstNode* externDef) {
    return externDef->as.Extern.typespec;
}

SymbolID GetAstTypedefStmtName(AstNode* td) {
    return td->as.Typedef.name;
}
AstNode* GetAstTypedefStmtOptPattern(AstNode* td) {
    return td->as.Typedef.optPattern;
}
AstNode* GetAstTypedefStmtOptRhs(AstNode* td) {
    return td->as.Typedef.optRhs;
}

//
// Scoper and typer storage:
//

void* GetAstNodeTypingExt_SingleV(AstNode* node) {
    COMPILER_ASSERT(node->typingExtCount_v == -1,"single ext <=> count == -1");
    return node->typingExt_v;
}
void* GetAstNodeTypingExt_SingleT(AstNode* node) {
    COMPILER_ASSERT(node->typingExtCount_t == -1,"single ext <=> count == -1");
    return node->typingExt_t;
}
void* GetAstNodeTypingExt_ArrayV(AstNode* node, int* lenP) {
    *lenP = node->typingExtCount_v;
    return node->typingExt_v;
}
void* GetAstNodeTypingExt_ArrayT(AstNode* node, int* lenP) {
    *lenP = node->typingExtCount_t;
    return node->typingExt_t;
}
void SetAstNodeTypingExt_SingleV(AstNode* node, void* type) {
    if (DEBUG) {
        COMPILER_ASSERT(type,"SetAstNodeTypingExt_SingleV: null arg set.");
    }
    node->typingExt_v = type;
    node->typingExtCount_v = -1;
}
void SetAstNodeTypingExt_SingleT(AstNode* node, void* type) {
    if (DEBUG) {
        COMPILER_ASSERT(type,"SetAstNodeTypingExt_SingleT: null arg set.");
    }
    node->typingExt_t = type;
    node->typingExtCount_t = -1;
}
void SetAstNodeTypingExt_ArrayV(AstNode* node, int count, void* typeArray) {
    if (DEBUG && count) {
        COMPILER_ASSERT(typeArray,"SetAstNodeTypingExt_ArrayV: NULL array for non-empty count.");
    }
    node->typingExtCount_v = count;
    node->typingExt_v = typeArray;
}
void SetAstNodeTypingExt_ArrayT(AstNode* node, int count, void* typeArray) {
    if (DEBUG && count) {
        COMPILER_ASSERT(typeArray,"SetAstNodeTypingExt_ArrayT: NULL array for non-empty count.");
    }
    node->typingExtCount_t = count;
    node->typingExt_t = typeArray;
}

// void SetAstTypedefStmtValueDefnType(AstNode* node, void* valueDefn) {
//     node->as.Typedef.valueDefnType = valueDefn;
// }
// void* GetAstTypedefStmtValueDefnType(AstNode* node) {
//     return node->as.Typedef.valueDefnType;
// }

AstNode* GetAstCastTypespec(AstNode* cast) {
    return cast->as.Cast.castTypespec->as.CastTypespec;
}
AstNode* GetAstCastRhs(AstNode* cast) {
    return cast->as.Cast.rhs;
}

AstNode* GetAstNodeParentFunc(AstNode* node) {
    return node->parentFunc;
}
void SetAstNodeParentFunc(AstNode* node, AstNode* parentFunc) {
    if (parentFunc->kind != AST_LAMBDA) {
        COMPILER_ERROR("non-lambda parent func in 'SetAstNodeParentFunc'.");
    }
    node->parentFunc = parentFunc;
}

AstContext GetAstNodeLookupContext(AstNode* node) {
    return node->lookupContext;
}
void SetAstNodeLookupContext(AstNode* node, AstContext context) {
    node->lookupContext = context;
}

void* GetAstIdLookupScope(AstNode* node) {
    return node->as.ID.lookupScope;
}
void SetAstIdLookupScope(AstNode* node, void* scopeP) {
    node->as.ID.lookupScope = scopeP;
}
void* GetAstIdDefn(AstNode* node) {
    return node->as.ID.defn;
}
void SetAstIdDefn(AstNode* node, void* defn) {
    node->as.ID.defn = defn;
}

//
// Visitor API:
//

inline static int visitChildren(void* context, AstNode* node, VisitorCb preVisitorCb, VisitorCb postVisitorCb) {
    AstKind nodeKind = GetAstNodeKind(node);
    switch (nodeKind) {
        case AST_UNIT:
        case AST_LITERAL_INT:
        case AST_LITERAL_FLOAT:
        case AST_LITERAL_STRING:
        case AST_VID:
        case AST_TID:
        {
            return 1;
        }
        case AST_VPAREN:
        case AST_TPAREN:
        {
            RecursivelyVisitAstNode(context, node->as.Paren_item, preVisitorCb, postVisitorCb);
            return 1;
        }
        case AST_ITE:
        {
            return (
                RecursivelyVisitAstNode(context, GetAstIteCond(node), preVisitorCb, postVisitorCb) &&
                RecursivelyVisitAstNode(context, GetAstIteIfTrue(node), preVisitorCb, postVisitorCb) &&
                RecursivelyVisitAstNode(context, GetAstIteIfFalse(node), preVisitorCb, postVisitorCb)
            );
        }
        case AST_LAMBDA:
        {
            AstNode* lambda = node;

            // visiting each arg pattern:
            int patternCount = CountAstLambdaPatterns(lambda);
            for (int patternIndex = 0; patternIndex < patternCount; patternIndex++) {
                AstNode* pattern = GetAstLambdaPatternAt(node,patternIndex);
                if (!RecursivelyVisitAstNode(context,pattern,preVisitorCb,postVisitorCb)) {
                    return 0;
                }
            }

            // visiting the body:
            if (!RecursivelyVisitAstNode(context,GetAstLambdaBody(node),preVisitorCb,postVisitorCb)) {
                return 0;
            }

            // all ok!
            return 1;
        }
        case AST_DOT_INDEX:
        {
            return RecursivelyVisitAstNode(context, GetAstDotIndexLhs(node), preVisitorCb, postVisitorCb);
        }
        case AST_DOT_NAME:
        {
            return RecursivelyVisitAstNode(context, GetAstDotNameLhs(node), preVisitorCb, postVisitorCb);
        }
        case AST_UNARY:
        {
            return RecursivelyVisitAstNode(context, GetAstUnaryOperand(node), preVisitorCb, postVisitorCb);
        }
        case AST_BINARY:
        {
            return (
                RecursivelyVisitAstNode(context, GetAstBinaryLtOperand(node), preVisitorCb, postVisitorCb) &&
                RecursivelyVisitAstNode(context, GetAstBinaryRtOperand(node), preVisitorCb, postVisitorCb)
            );
        }
        case AST_LET:
        {
            return RecursivelyVisitAstNode(context, GetAstLetStmtRhs(node), preVisitorCb, postVisitorCb);
        }
        case AST_DEF_VALUE:
        {
            return RecursivelyVisitAstNode(context,GetAstDefValueStmtRhs(node),preVisitorCb,postVisitorCb);
        }
        case AST_STMT_WITH:
        {
            return RecursivelyVisitAstNode(context, GetAstWithStmtChecked(node), preVisitorCb, postVisitorCb);
        }
        case AST_VCALL:
        case AST_TCALL:
        {
            if (!RecursivelyVisitAstNode(context, GetAstCallLhs(node), preVisitorCb, postVisitorCb)) {
                return 0;
            }
            int argCount = GetAstCallArgCount(node);
            for (int argIndex = 0; argIndex < argCount; argIndex++) {
                AstNode* arg = GetAstCallArgAt(node,argIndex);
                if (!RecursivelyVisitAstNode(context, arg, preVisitorCb, postVisitorCb)) {
                    return 0;
                }
            }
            return 1;
        }
        case AST_T_PATTERN:
        case AST_V_PATTERN:
        {
            int patternLength = GetAstPatternLength(node);
            for (int i = 0; i < patternLength; i++) {
                AstNode* patternField = GetAstPatternFieldAt(node, i);
                if (!RecursivelyVisitAstNode(context, patternField, preVisitorCb, postVisitorCb)) {
                    return 0;
                }
            }
            return 1;
        }
        case AST_VTUPLE:
        case AST_TTUPLE:
        {
            int tupleLength = GetAstTupleLength(node);
            for (int i = 0; i < tupleLength; i++) {
                AstNode* tupleField = GetAstTupleItemAt(node, i);
                if (!RecursivelyVisitAstNode(context, tupleField, preVisitorCb, postVisitorCb)) {
                    return 0;
                }
            }
            return 1;
        }
        case AST_VSTRUCT:
        {
            size_t structLength = GetAstTupleLength(node);
            for (size_t index = 0; index < structLength; index++) {
                AstNode* structField = GetAstStructFieldAt(node, index);
                if (!RecursivelyVisitAstNode(context, structField, preVisitorCb, postVisitorCb)) {
                    return 0;
                }
            }
            return 1;
        }
        case AST_CHAIN:
        {
            size_t chainLength = GetAstChainPrefixLength(node);
            for (size_t index = 0; index < chainLength; index++) {
                AstNode* chainStmt = GetAstChainPrefixStmtAt(node, index);
                if (!RecursivelyVisitAstNode(context, chainStmt, preVisitorCb, postVisitorCb)) {
                    return 0;
                }
            }
            AstNode* result = GetAstChainResult(node);
            if (result && !RecursivelyVisitAstNode(context, result, preVisitorCb, postVisitorCb)) {
                return 0;
            }
            return 1;
        }
        case AST_FIELD__PATTERN_ITEM:
        case AST_FIELD__STRUCT_ITEM:
        case AST_FIELD__TEMPLATE_ITEM:
        case AST_FIELD__TUPLE_ITEM:
        {
            AstNode* rhs = GetAstFieldRhs(node);
            if (rhs && !RecursivelyVisitAstNode(context, rhs, preVisitorCb, postVisitorCb)) {
                return 0;
            }
            return 1;
        }
        case AST_MODULE:
        {
            int moduleLength = GetAstModuleLength(node);
            for (int i = 0; i < moduleLength; i++) {
                AstNode* moduleField = GetAstModuleStmtAt(node, i);
                if (!RecursivelyVisitAstNode(context, moduleField, preVisitorCb, postVisitorCb)) {
                    return 0;
                }
            }
            return 1;
        }
        case AST_EXTERN:
        {
            AstNode* typespec = GetAstExternTypespec(node);
            return RecursivelyVisitAstNode(context, typespec, preVisitorCb, postVisitorCb);
        }
        case AST_DEF_TYPE:
        {
            AstNode* optPattern = GetAstTypedefStmtOptPattern(node);
            if (optPattern) {
                AstNode* pattern = optPattern;
                if (!RecursivelyVisitAstNode(context, pattern, preVisitorCb, postVisitorCb)) {
                    return 0;
                }
            }
            AstNode* optRhs = GetAstTypedefStmtOptRhs(node);
            if (optRhs) {
                AstNode* rhs = optRhs;
                if (!RecursivelyVisitAstNode(context, rhs, preVisitorCb, postVisitorCb)) {
                    return 0;
                }
            }
            return 1;
        }
        case AST_NULL:
        {
            COMPILER_ERROR("Cannot visit a NULL AST node.");
            return 0;
        }
        case AST_ERROR:
        {
            COMPILER_ERROR("Cannot visit an ERROR AST node.");
            return 0;
        }
        default:
        {
            COMPILER_ERROR_VA("Unsupported AST node in 'visit' of type %s.", AstKindAsText(nodeKind));
            return 0;
        }
    }
}

int RecursivelyVisitAstNode(void* context, AstNode* node, VisitorCb preVisitorCb, VisitorCb postVisitorCb) {
    if (preVisitorCb) {
        if (!preVisitorCb(context, node)) {
            return 0;
        }
    }
    if (!visitChildren(context, node, preVisitorCb, postVisitorCb)) {
        return 0;
    }
    if (postVisitorCb) {
        if (!postVisitorCb(context, node)) {
            return 0;
        }
    }
    return 1;
}

//
// LLVM representations
//

void SetAstNodeLlvmRepr(AstNode* node, void* repr) {
    node->llvmRepr = repr;
}

void* GetAstNodeLlvmRepr(AstNode* node) {
    return node->llvmRepr;
}

//
// Reflection:
//

char const unaryOperatorTextArray[__UOP_COUNT][2] = {
    [UOP_NOT] = "!",
    [UOP_GETREF] = "^",
    [UOP_DEREF] = "*"
};
char const binaryOperatorTextArray[__BOP_COUNT][4] = {
    [BOP_MUL] = "*",
    [BOP_DIV] = "/",
    [BOP_REM] = "%",
    [BOP_ADD] = "+",
    [BOP_SUB] = "-",
    [BOP_LTHAN] = "<", 
    [BOP_LETHAN] = "<=", 
    [BOP_GTHAN] = ">", 
    [BOP_GETHAN] = ">=",
    [BOP_EQUALS] = "==", 
    [BOP_NEQUALS] = "!=",
    [BOP_AND] = "and",
    [BOP_OR] = "or",
    [BOP_XOR] = "xor"
};

//
// Reflection:
//

char const* AstKindAsText(AstKind kind) {
    switch (kind) {
        case AST_MODULE: return "AST_MODULE";
        case AST_TID: return "AST_TID";
        case AST_VID: return "AST_VID";
        case AST_LITERAL_INT: return "AST_LITERAL_INT"; 
        case AST_LITERAL_FLOAT: return "AST_LITERAL_FLOAT"; 
        case AST_LITERAL_STRING: return "AST_LITERAL_STRING"; 
        case AST_UNIT: return "AST_UNIT"; 
        case AST_TPAREN: return "AST_TPAREN";
        case AST_VPAREN: return "AST_VPAREN"; 
        case AST_VTUPLE: return "AST_VTUPLE"; 
        case AST_VSTRUCT: return "AST_VSTRUCT"; 
        case AST_CHAIN: return "AST_CHAIN";
        case AST_LAMBDA: return "AST_LAMBDA";
        case AST_ITE: return "AST_ITE";
        case AST_DOT_INDEX: return "AST_DOT_INDEX"; 
        case AST_DOT_NAME: return "AST_DOT_NAME";
        case AST_LET: return "AST_LET"; 
        case AST_DEF_VALUE: return "AST_DEF"; 
        case AST_DEF_TYPE: return "AST_TYPEDEF"; 
        case AST_EXTERN: return "AST_EXTERN"; 
        case AST_STMT_WITH: return "AST_STMT_WITH"; 
        case AST_STMT_RETURN: return "AST_STMT_RETURN";
        case AST_VCALL: return "AST_V_CALL";
        case AST_TCALL: return "AST_T_CALL";
        case AST_UNARY: return "AST_UNARY"; 
        case AST_BINARY: return "AST_BINARY";
        case AST_T_PATTERN: return "AST_T_PATTERN"; 
        case AST_V_PATTERN: return "AST_V_PATTERN";
        case AST_FIELD__TEMPLATE_ITEM: return "AST_FIELD__TEMPLATE_ITEM";
        case AST_FIELD__TUPLE_ITEM: return "AST_FIELD__TUPLE_ITEM";
        case AST_FIELD__STRUCT_ITEM: return "AST_FIELD__STRUCT_ITEM";
        case AST_FIELD__PATTERN_ITEM: return "AST_FIELD__PATTERN_ITEM";
        default: return "AST_?";
    }
}

char const* AstUnaryOperatorAsText(AstUnaryOperator op) {
    return unaryOperatorTextArray[op];
};
char const* AstBinaryOperatorAsText(AstBinaryOperator op) {
    return binaryOperatorTextArray[op];
}
