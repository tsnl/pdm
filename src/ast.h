#pragma once

#include "source.h"
#include "symbols.h"

#define MAX_ARG_COUNT  (64)
#define MAX_NODE_COUNT (MAX_ARG_COUNT * 1024)

typedef struct AstNode AstNode;

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
int PushItemToAstChain(AstNode* chain, AstNode* statement);

AstNode* CreateAstIte(Loc loc, AstNode* cond, AstNode* ifTrue, AstNode* ifFalse);
AstNode* CreateAstDotIndex(Loc loc, AstNode* lhs, size_t index);
AstNode* CreateAstDotName(Loc loc, AstNode* lhs, SymbolID rhs);

AstNode* CreateAstLambda(Loc loc, AstNode* pattern, AstNode* body);

AstNode* CreateAstBindStmt(Loc loc, SymbolID lhs, AstNode* templatePattern, AstNode* rhs);
AstNode* CreateAstCheckStmt(Loc loc, AstNode* checked, char* value);
AstNode* CreateAstReturnStmt(Loc loc, SymbolID label, AstNode* returned);

AstNode* CreateAstCall(Loc loc, AstNode* called);
int PushActualTemplateArgToAstCall(AstNode* call, AstNode* templateArg);
int PushActualValueArgToAstCall(AstNode* call, AstNode* valueArg);

// TODO: Write getters.