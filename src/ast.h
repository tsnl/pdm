#ifndef INCLUDED_AST_H
#define INCLUDED_AST_H

#include <stdio.h>

#include "config.h"
#include "source.h"
#include "symbols.h"
#include "unicoder.h"

typedef struct AstNode AstNode;
typedef struct AstNode RawAstNode;

typedef enum AstKind AstKind;
typedef enum AstUnaryOperator AstUnaryOperator;
typedef enum AstBinaryOperator AstBinaryOperator;
typedef enum AstContext AstContext;

enum AstKind {
    AST_ERROR = -1,
    AST_NULL = 0,
    AST_SCRIPT,
    AST_MODULE,
    AST_TID, AST_VID,
    AST_LITERAL_INT, AST_LITERAL_FLOAT, AST_LITERAL_STRING, 
    AST_UNIT, 
    AST_VCAST,
    AST_VPAREN, AST_VTUPLE, 
    AST_TPAREN, AST_TTUPLE, AST_TARRAY,
    AST_VSTRUCT, AST_TSTRUCT, AST_CHAIN,
    AST_VPTR,
    AST_VLAMBDA,AST_TLAMBDA,
    AST_ITE,
    AST_DOT_INDEX, AST_DOT_NAME, AST_COLON_NAME,
    AST_STMT_VLET, AST_STMT_VDEF, AST_STMT_TDEF, AST_TDEF_ENUM, AST_STMT_EXTERN, AST_STMT_ASSERT, AST_STMT_RETURN,
    AST_TCALL, AST_VCALL,
    AST_UNARY, AST_BINARY,
    AST_TPATTERN, AST_VPATTERN, AST_TPATTERN_SINGLETON, AST_VPATTERN_SINGLETON,
    AST_ORPHANED_FIELD,AST_VTUPLE_FIELD,AST_VSTRUCT_FIELD,
    AST_VPATTERN_FIELD,AST_TPATTERN_FIELD,AST_VPATTERN_SINGLETON_FIELD,AST_TPATTERN_SINGLETON_FIELD,
    AST_TSTRUCT_FIELD,AST_TTUPLE_FIELD,
    AST_TPTR,
    AST_TYPE2VAL,
    AST_VAL2TYPE,
    AST_VDEF_BUILTIN,
    AST_STMT_MODULE, AST_STMT_IMPORT,
    AST_STMT_SET, AST_STMT_DISCARD,
};

enum AstUnaryOperator {
    UOP_NOT, UOP_GETREF, UOP_DEREF,
    UOP_PLUS, UOP_MINUS,
    __UOP_COUNT
};
enum AstBinaryOperator {
    BOP_MUL, BOP_DIV, BOP_REM,
    BOP_ADD, BOP_SUBTRACT,
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

AstNode* NewAstScriptWithModulesSb(Span span, Source* source, AstNode** mov_modulesSb);
AstNode* NewAstModule(Span span, SymbolID moduleID);
AstNode* NewAstModuleWithStmtSb(Span span, SymbolID moduleID, AstNode** mov_contentSb);
void PushStmtToAstModule(AstNode* module, AstNode* def);

AstNode* NewAstVID(Span span, SymbolID symbolID);
AstNode* NewAstIntLiteral(Span span, size_t value, int base);
AstNode* NewAstFloatLiteral(Span span, long double value);
AstNode* NewAstStringLiteral(Span span, Utf8String value);
AstNode* NewAstVParen(Span span, AstNode* it);
AstNode* NewAstUnit(Span span);

AstNode* NewAstField(Span span, SymbolID lhs, AstNode* rhs);
AstNode* NewAstVTuple(Span span);
AstNode* NewAstVTupleWithFieldsSb(Span span, AstNode** mov_fieldsSb);
AstNode* NewAstVStruct(Span span);
AstNode* NewAstVStructWithFieldsSb(Span span, AstNode** mov_fieldsSb);
AstNode* NewAstChain(Span span);
AstNode* NewAstChainWith(Span span, AstNode** mov_prefixSb, AstNode* result);

AstNode* NewAstTStruct(Span span);
AstNode* NewAstTStructWithFieldsSb(Span span, AstNode** mov_fieldsSb);
AstNode* NewAstTPattern(Span span);
AstNode* NewAstVPattern(Span span);
AstNode* NewAstVPatternWithFieldsSb(Span span, AstNode** mov_fieldsSb);
AstNode* NewAstTPatternWithFieldsSb(Span span, AstNode** mov_fieldsSb);
AstNode* NewAstVPatternSingleton(Span span, AstNode* field);
AstNode* NewAstTPatternSingleton(Span span, AstNode* field);

AstNode* NewAstVPtr(Span span, AstNode* arg);

void PushFieldToAstTTuple(AstNode* ttuple, AstNode* field);
void PushFieldToAstTStruct(AstNode* tstruct, AstNode* field);
void PushFieldToAstTPattern(AstNode* tpattern, AstNode* field);

void PushFieldToAstVTuple(AstNode* vstruct, AstNode* field);
void PushFieldToAstVStruct(AstNode* vstruct, AstNode* field);
void PushFieldToAstVPattern(AstNode* vpattern, AstNode* field);

void PushFieldToAstVTupleFromRaw(Span span, AstNode* tuple, AstNode* value);
void PushFieldToAstVStructFromRaw(Span span, AstNode* struct_, SymbolID name, AstNode* value);
void PushFieldToAstVPatternFromRaw(Span span, AstNode* pattern, AstKind fieldKind, SymbolID name, AstNode* typespec);

void PushStmtToAstChain(AstNode* chain, AstNode* statement);
void SetAstChainResult(AstNode* chain, AstNode* result);

AstNode* NewAstIte(Span span, AstNode* cond, AstNode* ifTrue, AstNode* ifFalse);
AstNode* NewAstDotIndex(Span span, AstNode* lhs, size_t index);
AstNode* NewAstDotName(Span span, AstNode* lhs, SymbolID rhs);
AstNode* NewAstColonName(Span span, AstNode* lhs, SymbolID rhs);

AstNode* NewAstVLambda(Span span, AstNode* pattern, AstNode* body);
AstNode* NewAstTLambda(Span span, AstNode* pattern, AstNode* body);

AstNode* NewAstModuleStmt(Span span, SymbolID boundName, Utf8String fromStr, Utf8String asStr);
AstNode* NewAstImportStmt(Span span, SymbolID module, SymbolID suffix, int glob);

AstNode* NewAstLetStmt(Span span, AstNode* lhsPattern, AstNode* rhs);
AstNode* NewAstDefStmt(Span span, SymbolID lhs, AstNode* optTemplatePattern, AstNode* pattern, AstNode* rhs);
AstNode* NewAstTypedefStmt(Span span, SymbolID lhs, AstNode* optPattern, AstNode* rhs);
AstNode* NewAstTypedefEnumStmt(Span span, SymbolID lhs, AstNode* optPattern, AstNode* rhs);
AstNode* NewAstSetStmt(Span span, AstNode* lhs, AstNode* rhs);
AstNode* NewAstAssertStmt(Span span, AstNode* checked);
AstNode* NewAstDiscardStmt(Span span, AstNode* discarded);
AstNode* NewAstExternStmt(Span span, SymbolID lhs, AstNode* pattern, AstNode* typespec);

AstNode* NewAstVCall(Span span, AstNode* lhs, AstNode* args[], int argsCount);
AstNode* NewAstVCallWithArgsSb(Span span, AstNode* lhs, AstNode** mov_argsSb);

AstNode* NewAstTCall(Span span, AstNode* lhs, AstNode* args[], int argsCount);
AstNode* NewAstTCallWithArgsSb(Span span, AstNode* lhs, AstNode** mov_argsSb);

AstNode* NewAstUnary(Span span, AstUnaryOperator op, AstNode* arg);
AstNode* NewAstBinary(Span span, AstBinaryOperator op, AstNode* ltArg, AstNode* rtArg);

AstNode* NewAstTID(Span span, SymbolID symbolID);
AstNode* NewAstTTuple(Span span);
AstNode* NewAstTTupleWithFieldsSb(Span span, AstNode** mov_fieldsSb);
AstNode* NewAstTArray(Span span, AstNode* typespec, AstNode* count);
AstNode* NewAstTParen(Span span, AstNode* it);
AstNode* NewAstTPtr(Span span, AstNode* pointee);

AstNode* NewAstVCast(Span span,AstNode* toTypespec,AstNode* fromExpr);
AstNode* NewAstType2Val(Span span, AstNode* typespec);
AstNode* NewAstVal2Type(Span span, AstNode* valueExpr);

//
// Lambda capture registration:
//

void AddAstLambdaDefn(AstNode* lambda, void* defn);
void ReqAstLambdaDefn(AstNode* lambda, void* defn);

//
// Getters:
//

int GetAstScriptLength(AstNode* node);
AstNode* GetAstScriptModuleAt(AstNode* node, int index);

SymbolID GetAstModuleName(AstNode* module);
int GetAstModuleLength(AstNode* module);
AstNode* GetAstModuleStmtAt(AstNode* module, int index);

size_t GetAstNodeKey(AstNode* node);
AstKind GetAstNodeKind(AstNode* node);
Loc GetAstNodeLoc(AstNode* node);
Span GetAstNodeSpan(AstNode* node);

SymbolID GetAstIdName(AstNode* node);
size_t GetAstIntLiteralValue(AstNode* node);
int GetAstIntLiteralBase(AstNode* node);
long double GetAstFloatLiteralValue(AstNode* node);
Utf8String GetAstStringLiteralValue(AstNode* node);
AstNode* GetAstParenItem(AstNode* node);

int GetAstPatternLength(AstNode* node);
AstNode* GetAstPatternFieldAt(AstNode* node, int index);

AstNode* GetAstSingletonPatternField(AstNode* node);

int GetAstTupleLength(AstNode* node);
int CountAstStructFields(AstNode* node);
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
AstNode* GetAstColonNameLhs(AstNode* colon);
SymbolID GetAstColonNameRhs(AstNode* colon);

int CountAstLambdaCaptures(AstNode* lambda);
void* GetAstVLambdaCaptureAt(AstNode* lambda, int index);
AstNode* GetAstVLambdaPattern(AstNode* lambda);
AstNode* GetAstVLambdaBody(AstNode* lambda);

AstNode* GetAstAssertStmtChecked(AstNode* checkStmt);
AstNode* GetAstDiscardStmtDiscarded(AstNode* discardStmt);

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
AstNode* GetAstExternPattern(AstNode* externDef);
AstNode* GetAstExternTypespec(AstNode* externDef);

SymbolID GetAstTypedefStmtName(AstNode* td);
AstNode* GetAstTypedefStmtOptPattern(AstNode* td);
AstNode* GetAstTypedefStmtOptRhs(AstNode* td);

AstNode* GetAstVCastTypespec(AstNode* vcast);
AstNode* GetAstVCastRhs(AstNode* vcast);

AstNode* GetAstVPtrPointee(AstNode* vptr);
AstNode* GetAstTPtrPointee(AstNode* tptr);

AstNode* GetAstType2ValTypespec(AstNode* type2Val);
AstNode* GetAstVal2TypeExpr(AstNode* val2type);

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
void SetAstIdDefnScope(AstNode* node, void* defn);

// Visitor API: calls a 'VisitorCb' function pre- and post- visiting children.
// - `context` can be used to propagate contextual information as the visitor recurses.
typedef int(*VisitorCb)(void* context, AstNode* node);

int RecursivelyVisitAstNode(void* context, AstNode* node, VisitorCb preVisitorCb, VisitorCb postVisitorCb);

//
// Constant evaluation:
//

int IsAstNodeConstEvaluable(AstNode* node);

void* GetAstNodeConstValue(AstNode* node);
void SetAstNodeConstValue(AstNode* node, void* value);

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