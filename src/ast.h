#pragma once

#include "source.h"
#include "symbols.h"

typedef struct AstNode AstNode;
typedef enum   AstKind AstKind;

enum AstKind {
    AST_ERROR = -1,
    AST_NULL = 0,
    AST_MODULE,
    AST_ID,
    AST_LITERAL_INT, AST_LITERAL_FLOAT, AST_LITERAL_STRING, 
    AST_TUPLE, AST_STRUCT, AST_SLICE, AST_CHAIN,  AST_ITE,
    AST_LAMBDA,
    AST_DOT_INDEX, AST_DOT_NAME,
    AST_STMT_BIND, AST_STMT_CHECK, AST_STMT_RETURN,
    AST_TEMPLATE_CALL, AST_VALUE_CALL, AST_SQBRK_CALL,
    AST_PATTERN, AST_FIELD
};

//
// Constructors:
//

AstNode* CreateAstModule(Loc loc, SymbolID moduleID);
int PushStmtToAstModule(AstNode* module, AstNode* stmt);

AstNode* CreateAstID(Loc loc, SymbolID symbolID);
AstNode* CreateAstIntLiteral(Loc loc, size_t value);
AstNode* CreateAstFloatLiteral(Loc loc, long double value);
AstNode* CreateAstStringLiteral(Loc loc, char* value);

AstNode* CreateAstTuple(Loc loc);
AstNode* CreateAstSlice(Loc loc);
AstNode* CreateAstStruct(Loc loc);
AstNode* CreateAstChain(Loc loc);
AstNode* CreateAstPattern(Loc loc);

int PushItemToAstTuple(AstNode* tuple, AstNode* pushed);
int PushItemToAstSlice(AstNode* slice, AstNode* pushed);
int PushFieldToAstStruct(Loc loc, AstNode* struct_, SymbolID name, AstNode* value);
int PushFieldToAstPattern(Loc loc, AstNode* pattern, SymbolID name, AstNode* typespec);
int PushStmtToAstChain(AstNode* chain, AstNode* statement);

AstNode* CreateAstIte(Loc loc, AstNode* cond, AstNode* ifTrue, AstNode* ifFalse);
AstNode* CreateAstDotIndex(Loc loc, AstNode* lhs, size_t index);
AstNode* CreateAstDotName(Loc loc, AstNode* lhs, SymbolID rhs);

AstNode* CreateAstLambda(Loc loc, AstNode* pattern, AstNode* body);

AstNode* CreateAstBindStmt(Loc loc, SymbolID lhs, AstNode* templatePattern, AstNode* rhs);
AstNode* CreateAstCheckStmt(Loc loc, AstNode* checked, char* messageValue);
AstNode* CreateAstReturnStmt(Loc loc, SymbolID label, AstNode* returned);

AstNode* CreateAstTemplateCall(Loc loc, AstNode* lhs);
AstNode* CreateAstValueCall(Loc loc, AstNode* lhs);
AstNode* CreateAstSqBrkCall(Loc loc, AstNode* lhs);
int PushActualArgToAstCall(AstNode* call, AstNode* actualArg);

//
// Getters:
//

SymbolID GetAstModuleName(AstNode* module);
size_t GetAstModuleLength(AstNode* module);
AstNode* GetAstModuleStmtAt(AstNode* module, size_t index);

size_t GetAstNodeKey(AstNode* node);
AstKind GetAstNodeKind(AstNode* node);
Loc GetAstNodeLoc(AstNode* node);

SymbolID GetAstIDSymbol(AstNode* node);
size_t GetAstIntLiteralValue(AstNode* node);
long double GetAstFloatLiteralValue(AstNode* node);
char const* GetAstStringLiteralUtf8Value(AstNode* node);

size_t GetAstTupleLength(AstNode* node);
size_t GetAstSliceLength(AstNode* node);
size_t GetAstStructLength(AstNode* node);
size_t GetAstPatternLength(AstNode* node);
size_t GetAstChainLength(AstNode* node);
AstNode* GetAstTupleItemAt(AstNode* node, size_t index);
AstNode* GetAstSliceItemAt(AstNode* node, size_t index);
AstNode* GetAstStructFieldAt(AstNode* node, size_t index);
AstNode* GetAstPatternFieldAt(AstNode* node, size_t index);
AstNode* GetAstChainStmtAt(AstNode* node, size_t index);

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
AstNode* GetAstBindStmtTemplatePattern(AstNode* bindStmt);
AstNode* GetAstBindStmtRhs(AstNode* bindStmt);

AstNode* GetAstCheckStmtChecked(AstNode* checkStmt);
char* GetAstCheckStmtMessage(AstNode* checkStmt);
SymbolID GetAstReturnStmtLabel(AstNode* returnStmt);
AstNode* GetAstReturnStmtValue(AstNode* returnStmt);

AstNode* GetAstCallLhs(AstNode* call);
size_t GetAstCallArgCount(AstNode* call);
AstNode* GetAstCallArgAt(AstNode* call, size_t index);

SymbolID GetAstFieldName(AstNode* field);
AstNode* GetAstFieldRhs(AstNode* field);

//
// Symbol and type storage:
//

void* GetAstNodeTypeP(AstNode* node);
void SetAstNodeTypeP(AstNode* node, void* typeP);

void* GetAstIDScopeP(AstNode* node);
void SetAstIDScopeP(AstNode* node, void* scopeP);

//
// We can implement a Visitor API if required.
//

typedef int(*VisitorCb)(void* context, AstNode* node);

int visit(void* context, AstNode* node, VisitorCb visitorCb);

// TODO: Use 'break' statements to early return from chains.
