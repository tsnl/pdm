#ifndef INCLUDED_INTERP_H
#define INCLUDED_INTERP_H

#include "source.h"
#include "symbols.h"

typedef struct Interp Interp;

Interp* CreateInterp(void);
void DestroyInterp(Interp* interp);

int LoadScript(Interp* interp, Source* scriptSource);
int FinalizeLoadedScripts(Interp* interp);
int Execute(Interp* interp, Source* scriptSource, SymbolID entryPointName);
int Compile(Interp* interp, Source* scriptSource, SymbolID optEntryPointName);

#endif  // INCLUDED_INTERP_H
