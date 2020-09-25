#ifndef INCLUDED_PRIMER_H
#define INCLUDED_PRIMER_H

#include "symbols.h"
#include "ast.h"

typedef struct Primer Primer;
typedef struct Scope Scope;

Primer* CreatePrimer(void* typer);
int PrimeModule(Primer* primer, AstNode* node);

void* LookupSymbol(Scope* scope, SymbolID lookupID, AstContext context);
void* LookupSymbolUntil(Scope* scope, SymbolID lookupID, Scope* endScopeP, AstContext context);

#endif  // INCLUDED_PRIMER_H
