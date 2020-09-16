#ifndef INCLUDED_AST_H
#define INCLUDED_AST_H

#include <stdio.h>

#include "config.h"
#include "source.h"
#include "symbols.h"

typedef struct AstNode AstNode;
typedef enum AstKind AstKind;
typedef enum AstUnaryOperator AstUnaryOperator;
typedef enum AstBinaryOperator AstBinaryOperator;

enum AstKind {
    AST_ERROR = -1,
    AST_NULL = 0,
    AST_MODULE,
    AST_ID,
    AST_LITERAL_INT, AST_LITERAL_FLOAT, AST_LITERAL_STRING, 
    AST_UNIT, AST_PAREN, AST_TUPLE, 
    AST_STRUCT, AST_CHAIN,
    AST_LAMBDA,
    AST_ITE,
    AST_DOT_INDEX, AST_DOT_NAME,
    AST_STMT_BIND, AST_STMT_CHECK, AST_STMT_RETURN,
    AST_CALL,
    AST_UNARY, AST_BINARY,
    AST_PATTERN, AST_FIELD
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

//
// Constructors:
//

AstNode* CreateAstModule(Loc loc, SymbolID moduleID);
void AttachImportHeaderToAstModule(AstNode* module, AstNode* mapping);
void AttachExportHeaderToAstModule(AstNode* module, AstNode* mapping);
void PushFieldToAstModule(Loc loc, AstNode* module, SymbolID fieldID, AstNode* pattern, AstNode* value);

AstNode* CreateAstId(Loc loc, SymbolID symbolID);
AstNode* CreateAstIntLiteral(Loc loc, size_t value, int base);
AstNode* CreateAstFloatLiteral(Loc loc, long double value);
AstNode* CreateAstStringLiteral(Loc loc, int* valueSb);
AstNode* CreateAstParen(Loc loc, AstNode* it);
AstNode* CreateAstUnit(Loc loc);

AstNode* CreateAstTuple(Loc loc);
AstNode* CreateAstStruct(Loc loc);
AstNode* CreateAstChain(Loc loc);
AstNode* CreateAstPattern(Loc loc);

void PushFieldToAstTuple(Loc loc, AstNode* tuple, AstNode* value);
void PushFieldToAstStruct(Loc loc, AstNode* struct_, SymbolID name, AstNode* value);
void PushFieldToAstPattern(Loc loc, AstNode* pattern, SymbolID name, AstNode* typespec);
void PushStmtToAstChain(AstNode* chain, AstNode* statement);
void SetAstChainResult(AstNode* chain, AstNode* result);

AstNode* CreateAstIte(Loc loc, AstNode* cond, AstNode* ifTrue, AstNode* ifFalse);
AstNode* CreateAstDotIndex(Loc loc, AstNode* lhs, size_t index);
AstNode* CreateAstDotName(Loc loc, AstNode* lhs, SymbolID rhs);

AstNode* CreateAstLambda(Loc loc, AstNode* pattern, AstNode* body);

AstNode* CreateAstBindStmt(Loc loc, SymbolID lhs, AstNode* rhs);
AstNode* CreateAstCheckStmt(Loc loc, AstNode* checked, AstNode* message);

AstNode* CreateAstCall(Loc loc, AstNode* lhs, AstNode* rhs);
AstNode* CreateAstUnary(Loc loc, AstUnaryOperator op, AstNode* arg);
AstNode* CreateAstBinary(Loc loc, AstBinaryOperator op, AstNode* ltArg, AstNode* rtArg);

//
// Getters:
//

SymbolID GetAstModuleName(AstNode* module);
int GetAstModuleLength(AstNode* module);
AstNode* GetAstModuleFieldAt(AstNode* module, int index);

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

SymbolID GetAstBindStmtLhs(AstNode* bindStmt);
AstNode* GetAstBindStmtRhs(AstNode* bindStmt);

AstNode* GetAstCheckStmtChecked(AstNode* checkStmt);
AstNode* GetAstCheckStmtMessage(AstNode* checkStmt);

AstNode* GetAstCallLhs(AstNode* call);
AstNode* GetAstCallRhs(AstNode* call);

SymbolID GetAstFieldName(AstNode* field);
AstNode* GetAstFieldPattern(AstNode* field);
AstNode* GetAstFieldRhs(AstNode* field);

AstUnaryOperator GetAstUnaryOperator(AstNode* unary);
AstNode* GetAstUnaryOperand(AstNode* unary);
AstBinaryOperator GetAstBinaryOperator(AstNode* binary);
AstNode* GetAstBinaryLtOperand(AstNode* binary);
AstNode* GetAstBinaryRtOperand(AstNode* binary);

//
// Symbol and type storage:
//

void* GetAstNodeTypeP(AstNode* node);
void SetAstNodeTypeP(AstNode* node, void* typeP);

void* GetAstIdScopeP(AstNode* node);
void SetAstIdScopeP(AstNode* node, void* scopeP);

// Visitor API: calls a 'VisitorCb' function pre- and post- visiting children.
// - `context` can be used to propagate contextual information as the visitor recurses.
typedef int(*VisitorCb)(void* context, AstNode* node);

int visit(void* context, AstNode* node, VisitorCb preVisitorCb, VisitorCb postVisitorCb);

//
// Reflection:
//

char const* GetUnaryOperatorText(AstUnaryOperator op);
char const* GetBinaryOperatorText(AstBinaryOperator op);

#endif  // INCLUDED_AST_H