#ifndef INCLUDED_AST_H
#define INCLUDED_AST_H

#include <stdio.h>

#include "config.h"
#include "source.h"
#include "symbols.h"

typedef struct AstNode AstNode;
typedef struct AstNode RawAstNode;

typedef enum AstKind AstKind;
typedef enum AstUnaryOperator AstUnaryOperator;
typedef enum AstBinaryOperator AstBinaryOperator;
typedef enum AstContext AstContext;

enum AstKind {
    AST_ERROR = -1,
    AST_NULL = 0,
    AST_MODULE,
    AST_TID, AST_VID,
    AST_LITERAL_INT, AST_LITERAL_FLOAT, AST_LITERAL_STRING, 
    AST_UNIT, AST_VPAREN, AST_VTUPLE, AST_TPAREN, AST_TTUPLE,
    AST_STRUCT, AST_CHAIN,
    AST_LAMBDA,
    AST_ITE,
    AST_DOT_INDEX, AST_DOT_NAME,
    AST_LET, AST_DEF_VALUE, AST_DEF_TYPE, AST_EXTERN, AST_STMT_WITH, AST_STMT_RETURN,
    AST_TCALL, AST_VCALL,
    AST_UNARY, AST_BINARY,
    AST_T_PATTERN, AST_V_PATTERN,
    AST_FIELD__TEMPLATE_ITEM,AST_FIELD__TUPLE_ITEM,AST_FIELD__STRUCT_ITEM,AST_FIELD__PATTERN_ITEM
};

enum AstUnaryOperator {
    UOP_NOT, UOP_GETREF, UOP_DEREF,
    UOP_PLUS, UOP_MINUS,
    __UOP_COUNT
};
enum AstBinaryOperator {
    BOP_MUL, BOP_DIV, BOP_REM,
    BOP_ADD, BOP_SUB,
    BOP_LTHAN, BOP_LETHAN, BOP_GTHAN, BOP_GETHAN,
    BOP_EQUALS, BOP_NEQUALS,
    BOP_AND, BOP_OR, BOP_XOR,
    __BOP_COUNT
};

enum AstContext {
    ASTCTX_TYPING,
    ASTCTX_VALUE,
    __ASTCTX_COUNT,
    __ASTCTX_NONE
};

//
// Constructors:
//

AstNode* CreateAstModule(Loc loc, SymbolID moduleID);
void AttachImportHeaderToAstModule(AstNode* module, AstNode* mapping);
void AttachExportHeaderToAstModule(AstNode* module, AstNode* mapping);
void PushStmtToAstModule(AstNode* module, AstNode* def);

AstNode* CreateAstVID(Loc loc, SymbolID symbolID);
AstNode* CreateAstIntLiteral(Loc loc, size_t value, int base);
AstNode* CreateAstFloatLiteral(Loc loc, long double value);
AstNode* CreateAstStringLiteral(Loc loc, int* valueSb);
AstNode* CreateAstVParen(Loc loc, AstNode* it);
AstNode* CreateAstUnit(Loc loc);

AstNode* CreateAstVTuple(Loc loc);
AstNode* CreateAstStruct(Loc loc);
AstNode* CreateAstChain(Loc loc);
AstNode* CreateAstPattern(Loc loc, int isTemplatePattern);

void PushFieldToAstTuple(Loc loc, AstNode* tuple, AstNode* value);
void PushFieldToAstStruct(Loc loc, AstNode* struct_, SymbolID name, AstNode* value);
void PushFieldToAstPattern(Loc loc, AstNode* pattern, SymbolID name, AstNode* typespec);

void PushStmtToAstChain(AstNode* chain, AstNode* statement);
void SetAstChainResult(AstNode* chain, AstNode* result);

AstNode* CreateAstIte(Loc loc, AstNode* cond, AstNode* ifTrue, AstNode* ifFalse);
AstNode* CreateAstDotIndex(Loc loc, AstNode* lhs, size_t index);
AstNode* CreateAstDotName(Loc loc, AstNode* lhs, SymbolID rhs);

AstNode* CreateAstLambda(Loc loc, AstNode* pattern, AstNode* body);
void AddAstLambdaDefn(AstNode* lambda, void* defn);
void ReqAstLambdaDefn(AstNode* lambda, void* defn);
int CountAstLambdaCaptures(AstNode* lambda);
void* GetAstLambdaCaptureAt(AstNode* lambda, int index);

AstNode* CreateAstLetStmt(Loc loc, SymbolID lhs, AstNode* optTypespec, AstNode* rhs);
AstNode* CreateAstDefValueStmt(Loc loc, SymbolID lhs, AstNode* optTemplatePattern, AstNode* patterns[], int patternsCount, AstNode* rhs);
AstNode* CreateAstDefTypeStmt(Loc loc, SymbolID lhs, AstNode* optPattern, AstNode* optRhs);
AstNode* CreateAstExternStmt(Loc loc, SymbolID lhs, AstNode* typespec);
AstNode* CreateAstWithStmt(Loc loc, AstNode* checked);

AstNode* CreateAstVCall(Loc loc, AstNode* lhs, AstNode* args[], int argsCount);
AstNode* CreateAstTCall(Loc loc, AstNode* lhs, AstNode* args[], int argsCount);
AstNode* CreateAstUnary(Loc loc, AstUnaryOperator op, AstNode* arg);
AstNode* CreateAstBinary(Loc loc, AstBinaryOperator op, AstNode* ltArg, AstNode* rtArg);

AstNode* NewAstTID(Loc loc, SymbolID symbolID);
AstNode* CreateAstTTuple(Loc loc);
AstNode* CreateAstTParen(Loc loc, AstNode* it);

//
// Getters:
//

SymbolID GetAstModuleName(AstNode* module);
int GetAstModuleLength(AstNode* module);
AstNode* GetAstModuleStmtAt(AstNode* module, int index);

size_t GetAstNodeKey(AstNode* node);
AstKind GetAstNodeKind(AstNode* node);
Loc GetAstNodeLoc(AstNode* node);

SymbolID GetAstIdName(AstNode* node);
size_t GetAstIntLiteralValue(AstNode* node);
int GetAstIntLiteralBase(AstNode* node);
long double GetAstFloatLiteralValue(AstNode* node);
int const* GetAstStringLiteralValue(AstNode* node);
AstNode* GetAstParenItem(AstNode* node);

int GetAstTupleLength(AstNode* node);
int GetAstStructLength(AstNode* node);
int GetAstPatternLength(AstNode* node);
int GetAstChainPrefixLength(AstNode* node);
AstNode* GetAstChainResult(AstNode* node);
AstNode* GetAstTupleItemAt(AstNode* node, int index);
AstNode* GetAstStructFieldAt(AstNode* node, int index);
AstNode* GetAstPatternFieldAt(AstNode* node, int index);
AstNode* GetAstChainPrefixStmtAt(AstNode* node, int index);

AstNode* GetAstIteCond(AstNode* ite);
AstNode* GetAstIteIfTrue(AstNode* ite);
AstNode* GetAstIteIfFalse(AstNode* ite);

AstNode* GetAstDotIndexLhs(AstNode* dot);
size_t GetAstDotIndexRhs(AstNode* dot);
AstNode* GetAstDotNameLhs(AstNode* dot);
SymbolID GetAstDotNameRhs(AstNode* dot);

AstNode* GetAstLambdaPattern(AstNode* lambda);
AstNode* GetAstLambdaBody(AstNode* lambda);

AstNode* GetAstWithStmtChecked(AstNode* checkStmt);

int IsAstCallTemplate(AstNode* call);
AstNode* GetAstCallLhs(AstNode* call);
int GetAstCallArgCount(AstNode* call);
AstNode* GetAstCallArgAt(AstNode* call, int index);

SymbolID GetAstFieldName(AstNode* field);
AstNode* GetAstModuleFieldPattern(AstNode* field);
AstNode* GetAstFieldRhs(AstNode* field);
int GetAstFieldIndex(AstNode* field);

AstUnaryOperator GetAstUnaryOperator(AstNode* unary);
AstNode* GetAstUnaryOperand(AstNode* unary);
AstBinaryOperator GetAstBinaryOperator(AstNode* binary);
AstNode* GetAstBinaryLtOperand(AstNode* binary);
AstNode* GetAstBinaryRtOperand(AstNode* binary);

SymbolID GetAstLetStmtLhs(AstNode* bindStmt);
AstNode* GetAstLetStmtRhs(AstNode* bindStmt);

AstNode* GetAstDefStmtOptTemplatePattern(AstNode* defStmt);
SymbolID GetAstDefStmtLhs(AstNode* defStmt);
AstNode* GetAstDefStmtRhs(AstNode* defStmt);

AstNode* GetAstValStmtOptTemplatePattern(AstNode* valStmt);
SymbolID GetAstValStmtLhs(AstNode* valStmt);
AstNode* GetAstValStmtPattern(AstNode* valStmt);

SymbolID GetAstExternStmtName(AstNode* externDef);
AstNode* GetAstExternTypespec(AstNode* externDef);

SymbolID GetAstTypedefStmtName(AstNode* td);
AstNode* GetAstTypedefStmtOptPattern(AstNode* td);
AstNode* GetAstTypedefStmtOptRhs(AstNode* td);

//
// Symbol and type storage:
//

void* GetAstNodeTypingExt_SingleV(AstNode* node);
void* GetAstNodeTypingExt_SingleT(AstNode* node);
void* GetAstNodeTypingExt_ArrayV(AstNode* node, int* lenP);
void* GetAstNodeTypingExt_ArrayT(AstNode* node, int* lenP);

void SetAstNodeTypingExt_SingleV(AstNode* node, void* type);
void SetAstNodeTypingExt_SingleT(AstNode* node, void* type);
void SetAstNodeTypingExt_ArrayV(AstNode* node, int count, void* typeArray);
void SetAstNodeTypingExt_ArrayT(AstNode* node, int count, void* typeArray);

AstNode* GetAstNodeParentFunc(AstNode* node);
void SetAstNodeParentFunc(AstNode* node, AstNode* parentFunc);

AstContext GetAstNodeLookupContext(AstNode* node);
void SetAstNodeLookupContext(AstNode* node, AstContext context);

void* GetAstIdLookupScope(AstNode* node);
void* GetAstIdDefn(AstNode* node);
void SetAstIdLookupScope(AstNode* node, void* scope);
void SetAstIdDefn(AstNode* node, void* defn);

// Visitor API: calls a 'VisitorCb' function pre- and post- visiting children.
// - `context` can be used to propagate contextual information as the visitor recurses.
typedef int(*VisitorCb)(void* context, AstNode* node);

int RecursivelyVisitAstNode(void* context, AstNode* node, VisitorCb preVisitorCb, VisitorCb postVisitorCb);

//
// LLVM representations
//

void SetAstNodeLlvmRepr(AstNode* node, void* repr);
void* GetAstNodeLlvmRepr(AstNode* node);

//
// Reflection:
//

char const* AstKindAsText(AstKind kind);
char const* AstUnaryOperatorAsText(AstUnaryOperator op);
char const* AstBinaryOperatorAsText(AstBinaryOperator op);

#endif  // INCLUDED_AST_H