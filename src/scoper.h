#ifndef INCLUDED_SCOPER_H
#define INCLUDED_SCOPER_H

#include "symbols.h"
#include "ast.h"

typedef struct Scoper Scoper;
typedef struct Scope Scope;

Scoper* CreateScoper(void* typer);
int ScopeModule(Scoper* scoper, AstNode* node);

void* LookupSymbol(Scope* scope, SymbolID lookupID, AstContext context);
void* LookupSymbolUntil(Scope* scope, SymbolID lookupID, Scope* endScopeP, AstContext context);

#endif  // INCLUDED_SCOPER_H
