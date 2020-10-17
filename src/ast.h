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
    AST_VSTRUCT, AST_CHAIN,
    AST_LAMBDA,
    AST_ITE,
    AST_DOT_INDEX, AST_DOT_NAME,
    AST_VLET, AST_VDEF, AST_TDEF, AST_EXTERN, AST_STMT_WITH, AST_STMT_RETURN,
    AST_TCALL, AST_VCALL,
    AST_UNARY, AST_BINARY,
    AST_TPATTERN, AST_VPATTERN, AST_TPATTERN_SINGLETON, AST_VPATTERN_SINGLETON,
    AST_TPATTERN_FIELD,AST_VTUPLE_FIELD,AST_VSTRUCT_FIELD,AST_VPATTERN_FIELD
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

AstNode* NewAstModule(Loc loc, SymbolID moduleID);
void AttachImportHeaderToAstModule(AstNode* module, AstNode* mapping);
void AttachExportHeaderToAstModule(AstNode* module, AstNode* mapping);
void PushStmtToAstModule(AstNode* module, AstNode* def);

AstNode* NewAstVID(Loc loc, SymbolID symbolID);
AstNode* NewAstIntLiteral(Loc loc, size_t value, int base);
AstNode* NewAstFloatLiteral(Loc loc, long double value);
AstNode* NewAstStringLiteral(Loc loc, int* valueSb);
AstNode* NewAstVParen(Loc loc, AstNode* it);
AstNode* NewAstUnit(Loc loc);

AstNode* NewAstVTuple(Loc loc);
AstNode* NewAstVStruct(Loc loGetc);
AstNode* NewAstChain(Loc loc);
AstNode* NewAstTPatternSingleton(Loc loc, SymbolID name, AstNode* rhs);
AstNode* NewAstVPatternSingleton(Loc loc, SymbolID name, AstNode* rhs);
AstNode* NewAstTPattern(Loc loc);
AstNode* NewAstVPattern(Loc loc);

void PushFieldToAstTuple(Loc loc, AstNode* tuple, AstNode* value);
void PushFieldToAstStruct(Loc loc, AstNode* struct_, SymbolID name, AstNode* value);
void PushFieldToAstPattern(Loc loc, AstNode* pattern, SymbolID name, AstNode* typespec);

void PushStmtToAstChain(AstNode* chain, AstNode* statement);
void SetAstChainResult(AstNode* chain, AstNode* result);

AstNode* NewAstIte(Loc loc, AstNode* cond, AstNode* ifTrue, AstNode* ifFalse);
AstNode* NewAstDotIndex(Loc loc, AstNode* lhs, size_t index);
AstNode* NewAstDotName(Loc loc, AstNode* lhs, SymbolID rhs);

AstNode* NewAstLambda(Loc loc, AstNode** patterns, int patternCount, AstNode* body);

AstNode* NewAstLetStmt(Loc loc, AstNode* lhsPattern, AstNode* rhs);
AstNode* NewAstVDefStmt(Loc loc, SymbolID lhs, AstNode* optTemplatePattern, AstNode* patterns[], int patternsCount, AstNode* rhs);
AstNode* NewAstTDefStmt(Loc loc, SymbolID lhs, AstNode* optPattern, AstNode* optRhs);
AstNode* NewAstExternStmt(Loc loc, SymbolID lhs, AstNode* typespec);
AstNode* NewAstWithStmt(Loc loc, AstNode* checked);

AstNode* NewAstVCall(Loc loc, AstNode* lhs, AstNode* args[], int argsCount);
AstNode* NewAstTCall(Loc loc, AstNode* lhs, AstNode* args[], int argsCount);
AstNode* NewAstUnary(Loc loc, AstUnaryOperator op, AstNode* arg);
AstNode* NewAstBinary(Loc loc, AstBinaryOperator op, AstNode* ltArg, AstNode* rtArg);

AstNode* NewAstTID(Loc loc, SymbolID symbolID);
AstNode* NewAstTTuple(Loc loc);
AstNode* NewAstTParen(Loc loc, AstNode* it);

//
// Lambda capture registration:
//

void AddAstLambdaDefn(AstNode* lambda, void* defn);
void ReqAstLambdaDefn(AstNode* lambda, void* defn);

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

int GetAstPatternLength(AstNode* node);
AstNode* GetAstPatternFieldAt(AstNode* node, int index);
SymbolID GetAstSingletonPatternName(AstNode* node);
AstNode* GetAstSingletonPatternRhs(AstNode* node);

int GetAstTupleLength(AstNode* node);
int GetAstStructLength(AstNode* node);
int GetAstChainPrefixLength(AstNode* node);
AstNode* GetAstChainResult(AstNode* node);
AstNode* GetAstTupleItemAt(AstNode* node, int index);
AstNode* GetAstStructFieldAt(AstNode* node, int index);
AstNode* GetAstChainPrefixStmtAt(AstNode* node, int index);

AstNode* GetAstIteCond(AstNode* ite);
AstNode* GetAstIteIfTrue(AstNode* ite);
AstNode* GetAstIteIfFalse(AstNode* ite);

AstNode* GetAstDotIndexLhs(AstNode* dot);
size_t GetAstDotIndexRhs(AstNode* dot);
AstNode* GetAstDotNameLhs(AstNode* dot);
SymbolID GetAstDotNameRhs(AstNode* dot);

int CountAstLambdaCaptures(AstNode* lambda);
int CountAstLambdaPatterns(AstNode* lambda);
void* GetAstLambdaCaptureAt(AstNode* lambda, int index);
AstNode* GetAstLambdaPatternAt(AstNode* lambda, int index);
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

AstNode* GetAstLetStmtLhs(AstNode* bindStmt);
AstNode* GetAstLetStmtRhs(AstNode* bindStmt);

AstNode* GetAstDefValueStmtOptTemplatePattern(AstNode* defStmt);
SymbolID GetAstDefValueStmtLhs(AstNode* defStmt);
AstNode* GetAstDefValueStmtRhs(AstNode* defStmt);

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

void* GetAstNodeTypingExt_Value(AstNode* node);
void* GetAstNodeTypingExt_Type(AstNode* node);
void SetAstNodeTypingExt_Value(AstNode* node, void* type);
void SetAstNodeTypingExt_Type(AstNode* node, void* type);

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