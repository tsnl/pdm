#include <stdio.h>

#include "symbols.h"
#include "interp.h"

int main() {
    Interp* interp = CreateInterp();
    Source* scriptSource = CreateSource("test/test1.hub");
    if (!scriptSource) {
        printf("File not found.\n");
        return 1;
    }

    int result;
    
    result = InterpLoadModuleSource(interp, scriptSource);
    if (!result) {
        printf("Loading failed.\n");
        return 1;
    }
    printf("Loading succeeded.\n");
    
    result = InterpTypecheckModules(interp);
    if (!result) {
        printf("Linking failed.\n");
        return 1;
    }

    result = InterpCompile(interp);
    if (!result) {
        printf("LLVM emission failed.\n");
    }

    // TODO: execute, emit an executable, or just exit after reporting the program's validity.
    DestroyInterp(interp);

    printf("Compilation succeded.\n");
    return 0;
}

