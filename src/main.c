#include <stdio.h>

#include "symbols.h"
#include "interp.h"

int main() {
    Interp* interp = CreateInterp();
    Source* scriptSource = CreateSource("test/test2.hub");
    
    int result = ExecuteScript(interp, scriptSource);
    int exitCode;
    if (result) {
        printf("Execution succeeded.\n");
        exitCode = 0;
    } else {
        printf("Execution failed.\n");
        exitCode = 1;
    }
    
    DestroyInterp(interp);
    return exitCode;
}
