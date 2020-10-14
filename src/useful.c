#include "useful.h"

int __compilerErrorHandler(char const* filename, long int line, char const* format, ...) {
    if (DEBUG) {
        printf("!!- COMPILER ERROR at [%s:%d]\n", filename, line);

        va_list ap;
        va_start(ap,format);
        vprintf(format,ap);
        va_end(ap);
    } else {
        assert(0 && "A fatal compiler error occurred.");
    }
    return 0;
}