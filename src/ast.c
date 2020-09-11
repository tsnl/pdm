#include "ast.h"

#include <assert.h>

#include "config.h"

#include "source.h"
#include "symbols.h"

typedef struct AstModule   AstModule;
typedef struct AstID       AstID;
typedef union  AstInfo     AstInfo;
typedef struct AstList     AstList;
typedef struct AstCall     AstCall;
typedef struct AstField    AstField;
typedef enum   AstBinaryOperator AstBinaryOperator;
typedef struct AstDotIndex AstDotIndex;
typedef struct AstDotName  AstDotName;
typedef struct AstLambda   AstLambda;
typedef struct AstBind     AstBind;
typedef struct AstCheck    AstCheck;
typedef struct AstUnary    AstUnary;
typedef struct AstBinary   AstBinary;

struct AstModule {
    SymbolID name;
    AstList* items;
    AstNode* importHeader;
    AstNode* exportHeader;
};
struct AstID {
    SymbolID name;
    void* scopeP;
};
struct AstList {
    size_t count;
    AstNode* items[MAX_ARG_COUNT];
};
struct AstField {
    SymbolID name;
    AstNode* rhs;
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
    AstNode* pattern;
    AstNode* body;
};
struct AstBind {
    SymbolID name;
    AstNode* templatePattern;
    AstNode* rhs;
};
struct AstCheck {
    AstNode* checked;
    char* utf8Message;
};
struct AstCall {
    AstNode* lhs;
    AstList* args;
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

union AstInfo {
    AstModule   Module;
    AstID       ID;
    AstUnary    Unary;
    AstBinary   Binary;
    size_t      Int;
    long double Float;
    char*       Utf8String;
    AstList*    Items;
    AstCall     Call;
    AstField    Field;
    AstDotIndex DotIx;
    AstDotName  DotNm;
    AstLambda   Lambda;
    AstBind     Bind;
    AstCheck    Check;
};

struct AstNode {
    Loc loc;
    AstKind kind;
    AstInfo info;
    void* typeP;
};

//
// Constructor helpers:
//

static size_t allocatedNodeCount = 0;
static AstNode allocatedNodes[MAX_NODE_COUNT];

static size_t allocatedListCount = 0;
static AstList allocatedLists[MAX_NODE_COUNT];

static AstNode* allocateNode(Loc loc, AstKind kind);
static AstList* allocateList(void);
static int pushListElement(AstList* list, AstNode* node);

AstNode* allocateNode(Loc loc, AstKind kind) {
    AstNode* node = &allocatedNodes[allocatedNodeCount++];
    node->loc = loc;
    node->kind = kind;
    return node;
}

AstList* allocateList(void) {
    AstList* listP = &allocatedLists[allocatedListCount++];
    listP->count = 0;
    return listP;
}

int pushListElement(AstList* list, AstNode* node) {
    if (list->count == MAX_ARG_COUNT) {
        return 0;
    } else {
        size_t index = list->count++;
        list->items[index] = node;
        return 1;
    }
}

//
// Constructor implementations:
//

AstNode* CreateAstModule(Loc loc, SymbolID moduleID) {
    AstNode* node = allocateNode(loc, AST_MODULE);
    node->info.Module.name = moduleID;
    node->info.Module.items = allocateList();
    return node;
}

void AttachImportHeaderToAstModule(AstNode* module, AstNode* mapping) {
    module->info.Module.importHeader = mapping;
}

void AttachExportHeaderToAstModule(AstNode* module, AstNode* mapping) {
    module->info.Module.exportHeader = mapping;
}

int PushStmtToAstModule(AstNode* module, AstNode* stmt) {
    return pushListElement(module->info.Module.items, stmt);
}

AstNode* CreateAstId(Loc loc, SymbolID symbolID) {
    AstNode* idNode = allocateNode(loc, AST_ID);
    idNode->info.ID.name = symbolID;
    idNode->info.ID.scopeP = NULL;
    return idNode;
}

AstNode* CreateAstIntLiteral(Loc loc, size_t value) {
    AstNode* intNode = allocateNode(loc, AST_LITERAL_INT);
    intNode->info.Int = value;
    return intNode;
}

AstNode* CreateAstFloatLiteral(Loc loc, long double value) {
    AstNode* floatNode = allocateNode(loc, AST_LITERAL_FLOAT);
    floatNode->info.Float = value;
    return floatNode;
}

AstNode* CreateAstStringLiteral(Loc loc, char* value) {
    AstNode* stringNode = allocateNode(loc, AST_LITERAL_STRING);
    stringNode->info.Utf8String = value;
    return stringNode;
}

AstNode* CreateAstList(Loc loc) {
    AstNode* listNode = allocateNode(loc, AST_SLICE);
    listNode->info.Items = allocateList();
    listNode->info.Items->count = 0;
    return listNode;
}

AstNode* CreateAstStruct(Loc loc) {
    AstNode* structNode = allocateNode(loc, AST_STRUCT);
    structNode->info.Items = allocateList();
    structNode->info.Items->count = 0;
    return structNode;
}

AstNode* CreateAstChain(Loc loc) {
    AstNode* chainNode = allocateNode(loc, AST_CHAIN);
    chainNode->info.Items = allocateList();
    chainNode->info.Items->count = 0;
    return chainNode;
}

AstNode* CreateAstPattern(Loc loc) {
    AstNode* patternNode = allocateNode(loc, AST_PATTERN);
    patternNode->info.Items = allocateList();
    patternNode->info.Items->count = 0;
    return patternNode;
}

int PushItemToAstTuple(AstNode* tuple, AstNode* pushed) {
    return pushListElement(tuple->info.Items, pushed);
}

int PushItemToAstList(AstNode* list, AstNode* pushed) {
    return pushListElement(list->info.Items, pushed);
}

int PushFieldToAstStruct(Loc loc, AstNode* struct_, SymbolID name, AstNode* value) {
    AstNode* field = allocateNode(loc, AST_FIELD);
    field->info.Field.name = name;
    field->info.Field.rhs = value;
    return pushListElement(struct_->info.Items, field);
}

int PushFieldToAstPattern(Loc loc, AstNode* pattern, SymbolID name, AstNode* typespec) {
    AstNode* field = allocateNode(loc, AST_FIELD);
    field->info.Field.name = name;
    field->info.Field.rhs = typespec;
    return pushListElement(pattern->info.Items, field);
}

int PushStmtToAstChain(AstNode* chain, AstNode* statement) {
    return pushListElement(chain->info.Items, statement);
}

AstNode* CreateAstIte(Loc loc, AstNode* cond, AstNode* ifTrue, AstNode* ifFalse) {
    AstNode* iteNode = allocateNode(loc, AST_ITE);
    iteNode->info.Items = allocateList();
    iteNode->info.Items->count = 3;
    iteNode->info.Items->items[0] = cond;
    iteNode->info.Items->items[1] = ifTrue;
    iteNode->info.Items->items[2] = ifFalse;
    return iteNode;
}

AstNode* CreateAstDotIndex(Loc loc, AstNode* lhs, size_t index) {
    AstNode* dotNode = allocateNode(loc, AST_DOT_INDEX);
    dotNode->info.DotIx.lhs = lhs;
    dotNode->info.DotIx.index = index;
    return dotNode;
}

AstNode* CreateAstDotName(Loc loc, AstNode* lhs, SymbolID rhs) {
    AstNode* dotNode = allocateNode(loc, AST_DOT_NAME);
    dotNode->info.DotNm.lhs = lhs;
    dotNode->info.DotNm.symbol = rhs;
    return dotNode;
}

AstNode* CreateAstLambda(Loc loc, AstNode* pattern, AstNode* body) {
    AstNode* lambdaNode = allocateNode(loc, AST_LAMBDA);
    lambdaNode->info.Lambda.pattern = pattern;
    lambdaNode->info.Lambda.body = body;
    return lambdaNode;
}

AstNode* CreateAstBindStmt(Loc loc, SymbolID lhs, AstNode* templatePattern, AstNode* rhs) {
    AstNode* bindNode = allocateNode(loc, AST_STMT_BIND);
    bindNode->info.Bind.name = lhs;
    bindNode->info.Bind.templatePattern = templatePattern;
    bindNode->info.Bind.rhs = rhs;
    return bindNode;
}

AstNode* CreateAstCheckStmt(Loc loc, AstNode* checked, char* value) {
    AstNode* checkNode = allocateNode(loc, AST_STMT_CHECK);
    checkNode->info.Check.checked = checked;
    checkNode->info.Check.utf8Message = value;
    return checkNode;
}

AstNode* CreateAstTemplateCall(Loc loc, AstNode* lhs) {
    AstNode* callNode = allocateNode(loc, AST_TEMPLATE_CALL);
    callNode->info.Call.lhs = lhs;
    callNode->info.Call.args = allocateList();
    return callNode;
}

AstNode* CreateAstValueCall(Loc loc, AstNode* lhs) {
    AstNode* callNode = allocateNode(loc, AST_VALUE_CALL);
    callNode->info.Call.lhs = lhs;
    callNode->info.Call.args = allocateList();
    return callNode;
}

int PushActualArgToAstCall(AstNode* call, AstNode* actualArg) {
    return pushListElement(call->info.Call.args, actualArg);
}

AstNode* CreateAstUnary(Loc loc, AstUnaryOperator op, AstNode* arg) {
    AstNode* unaryNode = allocateNode(loc, AST_UNARY);
    unaryNode->info.Unary.operator = op;
    unaryNode->info.Unary.operand = arg;
    return unaryNode;
}

AstNode* CreateAstBinary(Loc loc, AstUnaryOperator op, AstNode* ltArg, AstNode* rtArg) {
    AstNode* binaryNode = allocateNode(loc, AST_BINARY);
    binaryNode->info.Binary.operator = op;
    binaryNode->info.Binary.ltOperand = ltArg;
    binaryNode->info.Binary.rtOperand = rtArg;
    return binaryNode;
}

//
// Getter helpers:
//

inline static size_t getListLength(AstList* list);
inline static AstNode* getListItemAt(AstList* list, size_t index);

inline size_t getListLength(AstList* list) {
    return list->count;
}

inline AstNode* getListItemAt(AstList* list, size_t index) {
    if (DEBUG && index >= list->count) {
        // element out of bounds!
        return NULL;
    }
    return list->items[index];
}

//
// Getter implementation:
//

SymbolID GetAstModuleName(AstNode* module) {
    return module->info.Module.name;
}

size_t GetAstModuleLength(AstNode* module) {
    return getListLength(module->info.Module.items);
}

AstNode* GetAstModuleStmtAt(AstNode* module, size_t index) {
    return getListItemAt(module->info.Module.items, index);
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
    return node->info.ID.name;
}

size_t GetAstIntLiteralValue(AstNode* node) {
    return node->info.Int;
}

long double GetAstFloatLiteralValue(AstNode* node) {
    return node->info.Float;
}

char const* GetAstStringLiteralUtf8Value(AstNode* node) {
    return node->info.Utf8String;
}

size_t GetAstTupleLength(AstNode* node) {
    return getListLength(node->info.Items);
}

size_t GetAstListLength(AstNode* node) {
    return getListLength(node->info.Items);
}

size_t GetAstStructLength(AstNode* node) {
    return getListLength(node->info.Items);
}

size_t GetAstPatternLength(AstNode* node) {
    return getListLength(node->info.Items);
}

size_t GetAstChainLength(AstNode* node) {
    return getListLength(node->info.Items);
}

AstNode* GetAstTupleItemAt(AstNode* node, size_t index) {
    return getListItemAt(node->info.Items, index);
}

AstNode* GetAstListItemAt(AstNode* node, size_t index) {
    return getListItemAt(node->info.Items, index);
}

AstNode* GetAstStructFieldAt(AstNode* node, size_t index) {
    return getListItemAt(node->info.Items, index);
}

AstNode* GetAstPatternFieldAt(AstNode* node, size_t index) {
    return getListItemAt(node->info.Items, index);
}

AstNode* GetAstChainStmtAt(AstNode* node, size_t index) {
    return getListItemAt(node->info.Items, index);
}

AstNode* GetAstIteCond(AstNode* ite) {
    return getListItemAt(ite->info.Items, 0);
}

AstNode* GetAstIteIfTrue(AstNode* ite) {
    return getListItemAt(ite->info.Items, 1);
}

AstNode* GetAstIteIfFalse(AstNode* ite) {
    return getListItemAt(ite->info.Items, 2);
}

AstNode* GetAstDotIndexLhs(AstNode* dot) {
    return dot->info.DotIx.lhs;
}

size_t GetAstDotIndexRhs(AstNode* dot) {
    return dot->info.DotIx.index;
}

AstNode* GetAstDotNameLhs(AstNode* dot) {
    return dot->info.DotNm.lhs;
}

SymbolID GetAstDotNameRhs(AstNode* dot) {
    return dot->info.DotNm.symbol;
}

// TODO: implement these getters

AstNode* GetAstLambdaPattern(AstNode* node) {
    return node->info.Lambda.pattern;
}

AstNode* GetAstLambdaBody(AstNode* node) {
    return node->info.Lambda.body;
}

SymbolID GetAstBindStmtLhs(AstNode* bindStmt) {
    return bindStmt->info.Bind.name;
}

AstNode* GetAstBindStmtTemplatePattern(AstNode* bindStmt) {
    return bindStmt->info.Bind.templatePattern;
}

AstNode* GetAstBindStmtRhs(AstNode* bindStmt) {
    return bindStmt->info.Bind.rhs;
}

AstNode* GetAstCheckStmtChecked(AstNode* checkStmt) {
    return checkStmt->info.Check.checked;
}

char* GetAstCheckStmtMessage(AstNode* checkStmt) {
    return checkStmt->info.Check.utf8Message;
}

AstNode* GetAstCallLhs(AstNode* call) {
    return call->info.Call.lhs;
}

size_t GetAstCallArgCount(AstNode* call) {
    return getListLength(call->info.Call.args);
}

AstNode* GetAstCallArgAt(AstNode* call, size_t index) {
    return getListItemAt(call->info.Call.args, index);
}

SymbolID GetAstFieldName(AstNode* field) {
    assert(field->kind == AST_FIELD);
    return field->info.Field.name;
}

AstNode* GetAstFieldRhs(AstNode* field) {
    assert(field->kind == AST_FIELD);
    return field->info.Field.rhs;
}

AstUnaryOperator GetAstUnaryOperator(AstNode* unary) {
    return unary->info.Unary.operator;
}
AstNode* GetAstUnaryOperand(AstNode* unary) {
    return unary->info.Unary.operand;
}
AstBinaryOperator GetAstBinaryOperator(AstNode* binary) {
    return binary->info.Binary.operator;
}
AstNode* GetAstBinaryLtOperand(AstNode* binary) {
    return binary->info.Binary.ltOperand;
}
AstNode* GetAstBinaryRtOperand(AstNode* binary) {
    return binary->info.Binary.rtOperand;
}

//
// Scoper and typer storage:
//

void* GetAstNodeTypeP(AstNode* node) {
    return node->typeP;
}

void SetAstNodeTypeP(AstNode* node, void* typeP) {
    node->typeP = typeP;
}

void* GetAstIdScopeP(AstNode* node) {
    return node->info.ID.scopeP;
}

void SetAstIdScopeP(AstNode* node, void* scopeP) {
    node->info.ID.scopeP = scopeP;
}

//
// Visitor API:
//

inline static int visitChildren(void* context, AstNode* node, VisitorCb preVisitorCb, VisitorCb postVisitorCb) {
    switch (GetAstNodeKind(node)) {
        case AST_LITERAL_INT:
        case AST_LITERAL_FLOAT:
        case AST_LITERAL_STRING:
        case AST_ID:
        {
            return 1;
        }
        case AST_STRUCT:
        {
            size_t structLength = GetAstTupleLength(node);
            for (size_t index = 0; index < structLength; index++) {
                AstNode* structField = GetAstStructFieldAt(node, index);
                AstNode* fieldRhs = GetAstFieldRhs(structField);
                if (!visit(context, fieldRhs, preVisitorCb, postVisitorCb)) {
                    return 0;
                }
            }
            return 1;
        }
        case AST_CHAIN:
        {
            size_t chainLength = GetAstTupleLength(node);
            for (size_t index = 0; index < chainLength; index++) {
                AstNode* chainStmt = GetAstChainStmtAt(node, index);
                if (!visit(context, chainStmt, preVisitorCb, postVisitorCb)) {
                    return 0;
                }
            }
            return 1;
        }
        case AST_ITE:
        {
            return (
                visit(context, GetAstIteCond(node), preVisitorCb, postVisitorCb) &&
                visit(context, GetAstIteIfTrue(node), preVisitorCb, postVisitorCb) &&
                visit(context, GetAstIteIfFalse(node), preVisitorCb, postVisitorCb)
            );
        }
        case AST_LAMBDA:
        {
            return (
                visit(context, GetAstLambdaPattern(node), preVisitorCb, postVisitorCb) &&
                visit(context, GetAstLambdaBody(node), preVisitorCb, postVisitorCb)
            );
        }
        case AST_DOT_INDEX:
        {
            return (
                visit(context, GetAstDotIndexLhs(node), preVisitorCb, postVisitorCb)
                // visit(context, GetAstDotIndexRhs(node), preVisitorCb, postVisitorCb)
            );
        }
        case AST_DOT_NAME:
        {
            return (
                visit(context, GetAstDotNameLhs(node), preVisitorCb, postVisitorCb)
                // visit(context, GetAstDotNameRhs(node), preVisitorCb, postVisitorCb)
            );
        }
        case AST_STMT_BIND:
        {
            return visit(context, GetAstBindStmtRhs(node), preVisitorCb, postVisitorCb);
        }
        case AST_STMT_CHECK:
        {
            return visit(context, GetAstCheckStmtChecked(node), preVisitorCb, postVisitorCb);
        }
        case AST_TEMPLATE_CALL:
        case AST_VALUE_CALL:
        {
            if (!visit(context, GetAstCallLhs(node), preVisitorCb, postVisitorCb)) {
                return 0;
            }
            size_t argCount = GetAstCallArgCount(node);
            for (size_t index = 0; index < argCount; index++) {
                if (!visit(context, GetAstCallArgAt(node, index), preVisitorCb, postVisitorCb)) {
                    return 0;
                }
            }
            return 1;
        }
        case AST_PATTERN:
        {
            if (!visit(context, GetAstCallLhs(node), preVisitorCb, postVisitorCb)) {
                return 0;
            }
            size_t argCount = GetAstCallArgCount(node);
            for (size_t index = 0; index < argCount; index++) {
                if (!visit(context, GetAstCallArgAt(node, index), preVisitorCb, postVisitorCb)) {
                    return 0;
                }
            }
            return 1;
        }
        case AST_FIELD:
        {
            return visit(context, GetAstFieldRhs(node), preVisitorCb, postVisitorCb);
        }
        case AST_MODULE:
        {
            // TODO: implement 'visit' for modules.
            assert(0 && "'module' AST node Unsupported AST node in 'visit'.");
        }
        case AST_NULL:
        {
            if (DEBUG) {
                assert(0 && "Cannot visit a NULL AST node.");
            }
            return 0;
        }
        case AST_ERROR:
        {
            if (DEBUG) {
                assert(0 && "Cannot visit an ERROR AST node.");
            }
            return 0;
        }
        default:
        {
            if (DEBUG) {
                assert(0 && "Unsupport AST node in 'visit'");
            }
            return 0;
        }
    }
}

int visit(void* context, AstNode* node, VisitorCb preVisitorCb, VisitorCb postVisitorCb) {
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
// Reflection:
//

char const unaryOperatorTextArray[__UOP_COUNT][2] = {
    [UOP_NOT] = "!",
    [UOP_GETREF] = "^",
    [UOP_DEREF] = "*"
};
char const binaryOperatorTextArray[__BOP_COUNT][3] = {
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
    [BOP_AND] = "&", 
    [BOP_OR] = "|",
    [BOP_XOR] = "^"
};

char const* GetUnaryOperatorText(AstUnaryOperator op) {
    return unaryOperatorTextArray[op];
};

char const* GetBinaryOperatorText(AstBinaryOperator op) {
    return binaryOperatorTextArray[op];
}
