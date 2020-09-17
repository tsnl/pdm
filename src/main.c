#include <stdio.h>

#include "symbols.h"
#include "interp.h"

int main() {
    int exitCode;
    Interp* interp = CreateInterp();
    Source* scriptSource = CreateSource("test/test3.hub");
    if (!scriptSource) {
        printf("File not found.\n");
        exitCode = 0;
        goto finish;
    }
    int result = LoadScript(interp, scriptSource);
    if (result) {
        printf("Loading succeeded.\n");
        exitCode = 0;
    } else {
        printf("Loading failed.\n");
        exitCode = 1;
        goto finish;
    }
    
    if (!FinalizeLoadedScripts(interp)) {
        exitCode = 1;
        goto finish;
    }

    // TODO: execute, emit an executable, or just exit after reporting the program's validity.

    finish: {
        DestroyInterp(interp);
        return exitCode;
    }
}


// TODO: lookup all ID nodes
// TODO: initialize definitions to valid types
// TODO: apply typer to obtain and check set of substitutions
// TODO: generate LLVM IR
// TODO: generate SMT checking assertions
