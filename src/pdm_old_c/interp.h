#ifndef INCLUDED_INTERP_H
#define INCLUDED_INTERP_H

#include "source.h"
#include "symbols.h"
#include "ast.h"

typedef struct Interp Interp;

Interp* CreateInterp(void);
void DestroyInterp(Interp* interp);

int InterpLoadModuleSource(Interp* interp, Source* scriptSource);
int InterpTypecheckModules(Interp* interp);
int InterpCompile(Interp* interp);
int InterpExecute(Interp* interp, Source* entryModule, SymbolID entryFieldName);
int InterpExecuteWithArgList(Interp* interp, Source* entryModule, SymbolID entryFieldName, int argc, char const* argv[]);

int InterpLoadedScriptCount(Interp* interp);
Source* GetLoadedModuleSourceAt(Interp* interp, int index);
AstNode* GetLoadedModuleAstNodeAt(Interp* interp, int index);

#endif  // INCLUDED_INTERP_H
