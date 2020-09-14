#include "interp.h"

#include "parser.h"
#include "scoper.h"
#include "typer.h"

struct Interp {

};

Interp* CreateInterp(void) {
    InitSymbols();
    return NULL;
}

void DestroyInterp(Interp* interp) {
    DeInitSymbols();
}

int ExecuteScript(Interp* interp, Source* scriptSource) {
    AstNode* moduleAstNode = ParseSource(scriptSource);
    if (!moduleAstNode) {
        return 0;
    }
    Scoper* scoper = CreateScoper();
    if (!ScopeModule(scoper, moduleAstNode)) {
        return 0;
    }
    
    // todo: apply typer

    // todo: compile to executable form
    
    // todo: execute

    return 1;
}