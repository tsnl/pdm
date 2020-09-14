#include <stdio.h>

#include "symbols.h"
#include "interp.h"

int main() {
    Interp* interp = CreateInterp();
    Source* scriptSource = CreateSource("test/test1.hub");
    if (!ExecuteScript(interp, scriptSource)) {
        printf("Execution failed.\n");
        return 1;
    }
    printf("Execution done.\n");
    DestroyInterp(interp);
    return 0;
}
