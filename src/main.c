#include <stdio.h>

#include "source.h"
#include "lexer.h"
#include "symbols.h"

int main() {
    InitSymbols();
    printf("Doing compiler stuff...\nDone!\n");
    DeInitSymbols();
    return 0;
}
