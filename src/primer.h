#ifndef INCLUDED_PRIMER_H
#define INCLUDED_PRIMER_H

#include "symbols.h"
#include "ast.h"

typedef struct Primer Primer;
typedef struct Scope Scope;
typedef struct Scope Defn;

Primer* CreatePrimer(void* typer);
int PrimeModule(Primer* primer, AstNode* node);

Defn* LookupSymbol(Scope* scope, SymbolID lookupID, AstContext context);
Defn* LookupSymbolUntil(Scope* scope, SymbolID lookupID, Scope* endScopeP, AstContext context);

SymbolID GetDefnName(Defn* defn);
AstNode* GetDefnNode(Defn* defn);
AstContext GetDefnContext(Defn* defn);
void* GetDefnType(Defn* defn);

#endif  // INCLUDED_PRIMER_H
