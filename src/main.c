#include <stdio.h>

#include "symbols.h"
#include "interp.h"

int main() {
    Interp* interp = CreateInterp();
    Source* scriptSource = CreateSource("test/test3.hub");
    
    int result = LoadScript(interp, scriptSource);
    int exitCode;
    if (result) {
        printf("Loading succeeded.\n");
        exitCode = 0;
    } else {
        printf("Loading failed.\n");
        exitCode = 1;
        goto finish;
    }
    
    FinalizeLoadedScripts(interp);

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
