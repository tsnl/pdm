#include "interp.h"

#include <stdio.h>
#include "lexer.h"
#include "parser.h"
#include "scoper.h"
#include "typer.h"

struct Interp {

};

Interp* CreateInterp(void) {
    InitSymbols();
    InitLexer();
    return NULL;
}

void DestroyInterp(Interp* interp) {
    DeInitSymbols();
    DeInitLexer();
}

int ExecuteScript(Interp* interp, Source* scriptSource) {
    // LEXER DEBUG:
    // DebugLexer(scriptSource);
    // return 1;
    
    AstNode* moduleAstNode = ParseSource(scriptSource);
    if (!moduleAstNode) {
        return 0;
    }

    // DEBUG
    printf("Start of Module dump:\n\n");
    PrintNode(stdout, moduleAstNode);
    printf("\n\nEnd of Module dump.\n");
    
    return 0;

    Scoper* scoper = CreateScoper();
    if (!ScopeModule(scoper, moduleAstNode)) {
        return 0;
    }
    
    // todo: apply typer

    // todo: compile to executable form
    
    // todo: execute

    return 1;
}