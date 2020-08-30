#include "ast.h"

#include "config.h"

#include "source.h"
#include "symbols.h"

typedef struct AstModule   AstModule;
typedef struct AstID       AstID;
typedef union  AstInfo     AstInfo;
typedef struct AstList     AstList;
typedef struct AstCall     AstCall;
typedef struct AstField    AstField;
typedef enum   AstOperator AstOperator;
typedef struct AstDotIndex AstDotIndex;
typedef struct AstDotName  AstDotName;
typedef struct AstLambda   AstLambda;
typedef struct AstBind     AstBind;
typedef struct AstCheck    AstCheck;

struct AstModule {
    SymbolID name;
    AstList* items;
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

enum AstOperator {
    OP_BMUL, OP_BDIV, OP_BREM,
    OP_BADD, OP_BSUB,
    OP_BLTHAN, OP_BGTHAN, OP_BLETHAN, OP_BGETHAN,
    OP_BEQUALS, OP_BNEQUALS,
    OP_BAND, OP_BOR, OP_BXOR,
    OP_UNOT, OP_UPLUS, OP_UMINUS, OP_UGETREF, OP_UDEREF
};

union AstInfo {
    AstModule   Module;
    AstID       ID;
    AstOperator OP;
    size_t      Int;
    long double Float;
    char*       Utf8String;
    AstList*    Items;
    AstCall     Call;
    AstField    Field;
    AstField    Return;
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
    AstNode* node = allocatedNode(loc, AST_MODULE);
    node->info.Module.name = moduleID;
    node->info.Module.items = allocateList();
    return node;
}

int PushStmtToAstModule(AstNode* module, AstNode* stmt) {
    return pushListElement(module->info.Module.items, stmt);
}

AstNode* CreateAstID(Loc loc, SymbolID symbolID) {
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

AstNode* CreateAstTuple(Loc loc) {
    AstNode* tupleNode = allocateNode(loc, AST_TUPLE);
    tupleNode->info.Items = allocateList();
    tupleNode->info.Items->count = 0;
    return tupleNode;
}

AstNode* CreateAstSlice(Loc loc) {
    AstNode* sliceNode = allocateNode(loc, AST_SLICE);
    sliceNode->info.Items = allocateList();
    sliceNode->info.Items->count = 0;
    return sliceNode;
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

int PushItemToAstSlice(AstNode* slice, AstNode* pushed) {
    return pushListElement(slice->info.Items, pushed);
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

AstNode* CreateAstReturnStmt(Loc loc, SymbolID label, AstNode* returned) {
    AstNode* returnNode = allocateNode(loc, AST_STMT_RETURN);
    returnNode->info.Return.name = label;
    returnNode->info.Return.rhs = returned;
    return returnNode;
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

AstNode* CreateAstSqBrkCall(Loc loc, AstNode* lhs) {
    AstNode* callNode = allocateNode(loc, AST_SQBRK_CALL);
    callNode->info.Call.lhs = lhs;
    callNode->info.Call.args = allocateList();
    return callNode;
}

int PushActualArgToAstCall(AstNode* call, AstNode* actualArg) {
    return pushListElement(call->info.Call.args, actualArg);
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

SymbolID GetAstIDSymbol(AstNode* node) {
    return node->info.ID;
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
    return getListLength(node);
}

size_t GetAstSliceLength(AstNode* node) {
    return getListLength(node);
}

size_t GetAstStructLength(AstNode* node) {
    return getListLength(node);
}

size_t GetAstPatternLength(AstNode* node) {
    return getListLength(node);
}

size_t GetAstChainLength(AstNode* node) {
    return getListLength(node);
}

AstNode* GetAstTupleItemAt(AstNode* node, size_t index) {
    return getListLength(node);
}

AstNode* GetAstSliceItemAt(AstNode* node, size_t index) {
    return getListLength(node);
}

AstNode* GetAstStructItemAt(AstNode* node, size_t index) {
    return getListLength(node);
}

AstNode* GetAstPatternItemAt(AstNode* node, size_t index) {
    return getListLength(node);
}

AstNode* GetAstChainStmtAt(AstNode* node, size_t index) {
    return getListLength(node);
}

AstNode* GetAstIteCond(AstNode* ite) {
    return getListItemAt(ite, 0);
}

AstNode* GetAstIteIfTrue(AstNode* ite) {
    return getListItemAt(ite, 1);
}

AstNode* GetAstIteIfFalse(AstNode* ite) {
    return getListItemAt(ite, 2);
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

//
// Scoper and typer storage:
//

void* GetAstNodeTypeP(AstNode* node) {
    return node->typeP;
}

void SetAstNodeTypeP(AstNode* node, void* typeP) {
    node->typeP = typeP;
}

void* GetAstIDScopeP(AstNode* node) {
    return node->info.ID.scopeP;
}

void SetAstIDScopeP(AstNode* node, void* scopeP) {
    node->info.ID.scopeP = scopeP;
}

//
// Visitor API:
//

int visit(void* context, AstNode* node, VisitorCb visitorCb) {
    if (!visitorCb(context, node)) {
        return 0;
    }
    AstKind kind = GetAstNodeKind(node);
    switch (kind) {
        case AST_LITERAL_INT:
        case AST_LITERAL_FLOAT:
        case AST_LITERAL_STRING:
        case AST_ID:
        {
            return 1;
        }
        case AST_TUPLE:
        {
            size_t tupleLength = GetAstTupleLength(node);
            for (size_t index = 0; index < tupleLength; index++) {
                AstNode* tupleItem = GetAstTupleItemAt(node, index);
                if (!visit(context, tupleItem, visitorCb)) {
                    return 0;
                }
            }
            return 1;
        }
        case AST_STRUCT:
        {
            size_t structLength = GetAstTupleLength(node);
            for (size_t index = 0; index < structLength; index++) {
                AstNode* structField = GetAstStructFieldAt(node, index);
                AstNode* fieldRhs = GetAstFieldRhs(structField);
                if (!visit(context, fieldRhs, visitorCb)) {
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
                if (!visit(context, chainStmt, visitorCb)) {
                    return 0;
                }
            }
            return 1;
        }
        case AST_ITE:
        {
            return (
                visit(context, GetAstIteCond(node), visitorCb) &&
                visit(context, GetAstIteIfTrue(node), visitorCb) &&
                visit(context, GetAstIteIfFalse(node), visitorCb)
            );
        }
        case AST_LAMBDA:
        {
            return (
                visit(context, GetAstLambdaPattern(node), visitorCb) &&
                visit(context, GetAstLambdaBody(node), visitorCb)
            );
        }
        case AST_DOT_INDEX:
        {
            return (
                visit(context, GetAstDotIndexLhs(node), visitorCb) &&
                visit(context, GetAstDotIndexRhs(node), visitorCb)
            );
        }
        case AST_DOT_NAME:
        {
            return (
                visit(context, GetAstDotNameLhs(node), visitorCb) &&
                visit(context, GetAstDotNameRhs(node), visitorCb)
            );
        }
        case AST_STMT_BIND:
        {
            return visit(context, GetAstBindStmtRhs(node), visitorCb);
        }
        case AST_STMT_CHECK:
        {
            return visit(context, GetAstCheckStmtChecked(node), visitorCb);
        }
        case AST_STMT_RETURN:
        {
            return visit(context, GetAstReturnStmtValue(node), visitorCb);
        }
        case AST_TEMPLATE_CALL:
        case AST_VALUE_CALL:
        case AST_SQBRK_CALL:
        {
            if (!visit(context, GetAstCallLhs(node), visitorCb)) {
                return 0;
            }
            size_t argCount = GetAstCallArgCount(node);
            for (size_t index = 0; index < argCount; index++) {
                if (!visit(context, GetAstCallArgAt(node, index), visitorCb)) {
                    return 0;
                }
            }
            return 1;
        }
        case AST_PATTERN:
        {
            if (!visit(context, GetAstCallLhs(node), visitorCb)) {
                return 0;
            }
            size_t argCount = GetAstCallArgCount(node);
            for (size_t index = 0; index < argCount; index++) {
                if (!visit(context, GetAstCallArgAt(node, index), visitorCb)) {
                    return 0;
                }
            }
            return 1;
        }
        case AST_FIELD:
        {
            return visit(context, GetAstFieldRhs(node), visitorCb);
        }
    }
}