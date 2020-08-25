#include "ast.h"

#include "source.h"
#include "symbols.h"

typedef enum   AstKind     AstKind;
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

enum AstKind {
    AST_ERROR = -1,
    AST_NULL = 0,

    // ids:
    AST_ID,
    
    // literals:
    AST_LITERAL_INT, AST_LITERAL_FLOAT, AST_LITERAL_STRING, 
    
    // compounds:
    AST_TUPLE, AST_STRUCT, AST_SLICE, AST_CHAIN,  AST_ITE,
    AST_LAMBDA,

    // dots:
    AST_DOT_INDEX, AST_DOT_NAME,
    
    // statements:
    AST_STMT_BIND, AST_STMT_CHECK, AST_STMT_RETURN,

    // calls:
    AST_CALL_PAREN, AST_CALL_SQBRK,

    // fields & patterns:
    AST_PATTERN,
    AST_FIELD
};

struct AstField {
    SymbolID name;
    AstNode* node;
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
    AstNode* called;
    AstList* templates;
    AstList* values;
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
    SymbolID    ID;
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
};

struct AstList {
    size_t count;
    AstNode* items[MAX_ARG_COUNT];
};

static size_t allocatedNodes = 0;
static AstNode nodes[MAX_NODE_COUNT];

static size_t allocatedLists = 0;
static AstList lists[MAX_NODE_COUNT];

static AstNode* allocateNode(Loc loc, AstKind kind);
static AstList* allocateList(void);
static int pushListElement(AstList* list, AstNode* node);

AstNode* allocateNode(Loc loc, AstKind kind) {
    AstNode* node = &nodes[allocatedNodes++];
    node->loc = loc;
    node->kind = kind;
    return node;
}

AstList* allocateList(void) {
    AstList* call = &lists[allocatedLists++];
    call->count = 0;
    return call;
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

AstNode* CreateAstID(Loc loc, SymbolID symbolID) {
    AstNode* idNode = allocateNode(loc, AST_ID);
    idNode->info.ID = symbolID;
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
    field->info.Field.node = value;
    return pushListElement(struct_->info.Items, field);
}

int PushFieldToAstPattern(Loc loc, AstNode* pattern, SymbolID name, AstNode* typespec) {
    AstNode* field = allocateNode(loc, AST_FIELD);
    field->info.Field.name = name;
    field->info.Field.node = typespec;
    return pushListElement(pattern->info.Items, field);
}

int PushItemToAstChain(AstNode* chain, AstNode* statement) {
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
    returnNode->info.Return.node = returned;
    return returnNode;
}

AstNode* CreateAstCall(Loc loc, AstNode* called) {
    AstNode* callNode = allocateNode(loc, AST_CALL_PAREN);
    callNode->info.Call.called = called;
    callNode->info.Call.templates = allocateList();
    callNode->info.Call.values = allocateList();
    return callNode;
}

int PushActualTemplateArgToAstCall(AstNode* call, AstNode* templateArg) {
    return pushListElement(call->info.Call.templates, templateArg);
}

int PushActualValueArgToAstCall(AstNode* call, AstNode* valueArg) {
    return pushListElement(call->info.Call.values, valueArg);
}

