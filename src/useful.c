#include "useful.h"

int __compilerErrorHandler(char const* filename, long int line, char const* prefix, char const* format, ...) {
    if (DEBUG) {
        printf("!!- COMPILER ERROR at [%s:%ld]\n", filename, line);

        if (prefix) {
            printf("!!- ... %s\n", prefix);
        }

        printf("!!- ... ");
        va_list ap; va_start(ap,format);
        vprintf(format,ap);
        va_end(ap);
        printf("\n");
    } else {
        assert(0 && "A fatal compiler error occurred.");
    }

    // always returns 0, so it can be used as an error branch
    return 0;
}