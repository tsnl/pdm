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
typedef enum AstBuiltinVDefKind AstBuiltinVDefKind;

enum AstKind {
    AST_ERROR = -1,
    AST_NULL = 0,
    AST_MODULE,
    AST_TID, AST_VID,
    AST_LITERAL_INT, AST_LITERAL_FLOAT, AST_LITERAL_STRING, 
    AST_UNIT, 
    AST_VCAST,
    AST_VPAREN, AST_VTUPLE, 
    AST_TPAREN, AST_TTUPLE,
    AST_VSTRUCT, AST_CHAIN,
    AST_LAMBDA,
    AST_ITE,
    AST_DOT_INDEX, AST_DOT_NAME,
    AST_VLET, AST_VDEF, AST_TDEF, AST_EXTERN, AST_STMT_WITH, AST_STMT_RETURN,
    AST_TCALL, AST_VCALL,
    AST_UNARY, AST_BINARY,
    AST_TPATTERN, AST_VPATTERN, AST_TPATTERN_SINGLETON, AST_VPATTERN_SINGLETON,
    AST_TPATTERN_FIELD,AST_VTUPLE_FIELD,AST_VSTRUCT_FIELD,AST_VPATTERN_FIELD,
    AST_TYPE2VAL,
    AST_VDEF_BUILTIN
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

enum AstBuiltinVDefKind {
    AST_BUILTIN_NULL = 0,

    //
    // unary:
    //
    
    AST_BUILTIN_POS_F64, AST_BUILTIN_POS_F32,
    AST_BUILTIN_NEG_F64, AST_BUILTIN_NEG_F32,

    AST_BUILTIN_POS_S128, AST_BUILTIN_POS_S64, AST_BUILTIN_POS_S32, AST_BUILTIN_POS_S16, AST_BUILTIN_POS_S8,
    AST_BUILTIN_NEG_S128, AST_BUILTIN_NEG_S64, AST_BUILTIN_NEG_S32, AST_BUILTIN_NEG_S16, AST_BUILTIN_NEG_S8,

    AST_BUILTIN_NOT_U128, AST_BUILTIN_NOT_U64, AST_BUILTIN_NOT_U32, AST_BUILTIN_NOT_U16, AST_BUILTIN_NOT_U8, AST_BUILTIN_NOT_U1,
    AST_BUILTIN_POS_U128, AST_BUILTIN_POS_U64, AST_BUILTIN_POS_U32, AST_BUILTIN_POS_U16, AST_BUILTIN_POS_U8, AST_BUILTIN_POS_U1,

    //
    // binary:
    //

    // '*'
    AST_BUILTIN_MUL_F64,AST_BUILTIN_MUL_F32, 
    AST_BUILTIN_MUL_S128,AST_BUILTIN_MUL_S64,AST_BUILTIN_MUL_S32,AST_BUILTIN_MUL_S16,AST_BUILTIN_MUL_S8,
    AST_BUILTIN_MUL_U128,AST_BUILTIN_MUL_U64,AST_BUILTIN_MUL_U32,AST_BUILTIN_MUL_U16,AST_BUILTIN_MUL_U8,AST_BUILTIN_MUL_U1,

    // '/': fpdiv, quo
    AST_BUILTIN_DIV_F64,AST_BUILTIN_DIV_F32, 
    AST_BUILTIN_QUO_S128,AST_BUILTIN_QUO_S64,AST_BUILTIN_QUO_S32,AST_BUILTIN_QUO_S16,AST_BUILTIN_QUO_S8,
    AST_BUILTIN_QUO_U128,AST_BUILTIN_QUO_U64,AST_BUILTIN_QUO_U32,AST_BUILTIN_QUO_U16,AST_BUILTIN_QUO_U8,AST_BUILTIN_QUO_U1,

    // '%'
    AST_BUILTIN_REM_S128,AST_BUILTIN_REM_S64,AST_BUILTIN_REM_S32,AST_BUILTIN_REM_S16,AST_BUILTIN_REM_S8,
    AST_BUILTIN_REM_U128,AST_BUILTIN_REM_U64,AST_BUILTIN_REM_U32,AST_BUILTIN_REM_U16,AST_BUILTIN_REM_U8,AST_BUILTIN_REM_U1,

    // '+'
    AST_BUILTIN_ADD_F64,AST_BUILTIN_ADD_F32, 
    AST_BUILTIN_ADD_S128,AST_BUILTIN_ADD_S64,AST_BUILTIN_ADD_S32,AST_BUILTIN_ADD_S16,AST_BUILTIN_ADD_S8,
    AST_BUILTIN_ADD_U128,AST_BUILTIN_ADD_U64,AST_BUILTIN_ADD_U32,AST_BUILTIN_ADD_U16,AST_BUILTIN_ADD_U8,AST_BUILTIN_ADD_U1,

    // '-'
    AST_BUILTIN_SUBTRACT_F64,AST_BUILTIN_SUBTRACT_F32, 
    AST_BUILTIN_SUBTRACT_S128,AST_BUILTIN_SUBTRACT_S64,AST_BUILTIN_SUBTRACT_S32,AST_BUILTIN_SUBTRACT_S16,AST_BUILTIN_SUBTRACT_S8,
    AST_BUILTIN_SUBTRACT_U128,AST_BUILTIN_SUBTRACT_U64,AST_BUILTIN_SUBTRACT_U32,AST_BUILTIN_SUBTRACT_U16,AST_BUILTIN_SUBTRACT_U8,AST_BUILTIN_SUBTRACT_U1,

    // '<'
    AST_BUILTIN_LTHAN_F64,AST_BUILTIN_LTHAN_F32, 
    AST_BUILTIN_LTHAN_S128,AST_BUILTIN_LTHAN_S64,AST_BUILTIN_LTHAN_S32,AST_BUILTIN_LTHAN_S16,AST_BUILTIN_LTHAN_S8,
    AST_BUILTIN_LTHAN_U128,AST_BUILTIN_LTHAN_U64,AST_BUILTIN_LTHAN_U32,AST_BUILTIN_LTHAN_U16,AST_BUILTIN_LTHAN_U8,AST_BUILTIN_LTHAN_U1,

    // '<='
    AST_BUILTIN_LETHAN_F64,AST_BUILTIN_LETHAN_F32, 
    AST_BUILTIN_LETHAN_S128,AST_BUILTIN_LETHAN_S64,AST_BUILTIN_LETHAN_S32,AST_BUILTIN_LETHAN_S16,AST_BUILTIN_LETHAN_S8,
    AST_BUILTIN_LETHAN_U128,AST_BUILTIN_LETHAN_U64,AST_BUILTIN_LETHAN_U32,AST_BUILTIN_LETHAN_U16,AST_BUILTIN_LETHAN_U8,AST_BUILTIN_LETHAN_U1,

    // '>'
    AST_BUILTIN_GTHAN_F64,AST_BUILTIN_GTHAN_F32, 
    AST_BUILTIN_GTHAN_S128,AST_BUILTIN_GTHAN_S64,AST_BUILTIN_GTHAN_S32,AST_BUILTIN_GTHAN_S16,AST_BUILTIN_GTHAN_S8,
    AST_BUILTIN_GTHAN_U128,AST_BUILTIN_GTHAN_U64,AST_BUILTIN_GTHAN_U32,AST_BUILTIN_GTHAN_U16,AST_BUILTIN_GTHAN_U8,AST_BUILTIN_GTHAN_U1,

    // '>='
    AST_BUILTIN_GETHAN_F64,AST_BUILTIN_GETHAN_F32, 
    AST_BUILTIN_GETHAN_S128,AST_BUILTIN_GETHAN_S64,AST_BUILTIN_GETHAN_S32,AST_BUILTIN_GETHAN_S16,AST_BUILTIN_GETHAN_S8,
    AST_BUILTIN_GETHAN_U128,AST_BUILTIN_GETHAN_U64,AST_BUILTIN_GETHAN_U32,AST_BUILTIN_GETHAN_U16,AST_BUILTIN_GETHAN_U8,AST_BUILTIN_GETHAN_U1,

    // '=='
    AST_BUILTIN_EQUALS_F64,AST_BUILTIN_EQUALS_F32, 
    AST_BUILTIN_EQUALS_S128,AST_BUILTIN_EQUALS_S64,AST_BUILTIN_EQUALS_S32,AST_BUILTIN_EQUALS_S16,AST_BUILTIN_EQUALS_S8,
    AST_BUILTIN_EQUALS_U128,AST_BUILTIN_EQUALS_U64,AST_BUILTIN_EQUALS_U32,AST_BUILTIN_EQUALS_U16,AST_BUILTIN_EQUALS_U8,AST_BUILTIN_EQUALS_U1,

    // '!='
    AST_BUILTIN_NOTEQUALS_F64,AST_BUILTIN_NOTEQUALS_F32, 
    AST_BUILTIN_NOTEQUALS_S128,AST_BUILTIN_NOTEQUALS_S64,AST_BUILTIN_NOTEQUALS_S32,AST_BUILTIN_NOTEQUALS_S16,AST_BUILTIN_NOTEQUALS_S8,
    AST_BUILTIN_NOTEQUALS_U128,AST_BUILTIN_NOTEQUALS_U64,AST_BUILTIN_NOTEQUALS_U32,AST_BUILTIN_NOTEQUALS_U16,AST_BUILTIN_NOTEQUALS_U8,AST_BUILTIN_NOTEQUALS_U1,

    // 'and','xor','or'
    AST_BUILTIN_AND_U128,AST_BUILTIN_AND_U64,AST_BUILTIN_AND_U32,AST_BUILTIN_AND_U16,AST_BUILTIN_AND_U8,AST_BUILTIN_AND_U1,
    AST_BUILTIN_XOR_U128,AST_BUILTIN_XOR_U64,AST_BUILTIN_XOR_U32,AST_BUILTIN_XOR_U16,AST_BUILTIN_XOR_U8,AST_BUILTIN_XOR_U1,
    AST_BUILTIN_OR_U128,AST_BUILTIN_OR_U64,AST_BUILTIN_OR_U32,AST_BUILTIN_OR_U16,AST_BUILTIN_OR_U8,AST_BUILTIN_OR_U1
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

AstNode* NewAstVCast(Loc loc,AstNode* toTypespec,AstNode* fromExpr);

AstNode* NewAstBuiltinVDefStmt(SymbolID lhs, AstBuiltinVDefKind builtinVDefKind);

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

AstNode* GetAstVCastToTypespecType2Val(AstNode* vcast);
AstNode* GetAstVCastRhs(AstNode* vcast);

AstNode* GetAstType2ValTypespec(AstNode* type2Val);

AstBuiltinVDefKind GetAstBuiltinVDefKind(AstNode* builtinVDef);

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