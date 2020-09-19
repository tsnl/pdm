#include <stdio.h>

#include "symbols.h"
#include "interp.h"

int main() {
    Interp* interp = CreateInterp();
    Source* scriptSource = CreateSource("test/test3.hub");
    if (!scriptSource) {
        printf("File not found.\n");
        return 1;
    }
    int result = LoadScript(interp, scriptSource);
    if (result) {
        printf("Loading succeeded.\n");
        if (!FinalizeLoadedScripts(interp)) {
            printf("Linking failed.\n");
            return 1;
        }
    } else {
        printf("Loading failed.\n");
        return 1;
    }

    // TODO: typecheck from entry point

    // TODO: execute, emit an executable, or just exit after reporting the program's validity.
    DestroyInterp(interp);
    return 0;
}

// TODO: initialize definitions to valid types
// TODO: apply typer to obtain and check set of substitutions
// TODO: generate LLVM IR
// TODO: generate SMT checking assertions
