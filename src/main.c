#include <stdio.h>

#include "symbols.h"
#include "interp.h"

int main() {
    Interp* interp = CreateInterp();
    Source* scriptSource = CreateSource("test/test1.hub");
    ExecuteScript(interp, scriptSource);
    DestroyInterp(interp);
    return 0;
}
