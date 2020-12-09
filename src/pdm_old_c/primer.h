#ifndef INCLUDED_PRIMER_H
#define INCLUDED_PRIMER_H

#include "symbols.h"
#include "ast.h"

// The same primer must be used for all scripts linked together.
// Each new symbol occupies its own 'Scope'. Scopes are chained (linked) for lookup.
// Each Scope/DefnScope points to one such node.
// Frames store a chain of Scopes by beg and end, usually for container deref.

typedef struct Primer Primer;
typedef struct Scope Scope;
typedef struct Scope DefnScope;
typedef struct Frame Frame;

Primer* CreatePrimer(void* typer);
int PrimeScript(Primer* primer, AstNode* node);

DefnScope* LookupSymbol(Scope* scope, SymbolID lookupID);
DefnScope* LookupSymbolUntil(Scope* scope, SymbolID lookupID, Scope* endScopeP);
DefnScope* LookupSymbolInFrame(Frame* frame, SymbolID lookupID);

SymbolID GetDefnName(DefnScope* defn);
AstNode* GetDefnNode(DefnScope* defn);

#endif  // INCLUDED_PRIMER_H
