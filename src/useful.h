#ifndef INCLUDED_USEFUL_H
#define INCLUDED_USEFUL_H

//
//
//
// FMT/strings
//
//
//

#include <string.h>
#include <stdbool.h>
#include <stdarg.h>
#include <stdio.h>

#define SHORT_BUF_SIZE (256)

// invokes sprintf, then strdup using a short stack-buffer.
inline static char* fmt(char const* format, ...) {
    char buffer[SHORT_BUF_SIZE];
    va_list ap;
    va_start(ap, format);
    int count = vsnprintf(buffer, SHORT_BUF_SIZE-1, format, ap);
    va_end(ap);
    if (count < 0) {
        return NULL;
    } else {
        buffer[count] = '\0';
        return strdup(buffer);
    }
}

inline bool streq(char const* s, char const* t) {
    return !strcmp(s, t);
}

//
//
//
// CHECK
//
//
//

#include "config.h"
#include <assert.h>
#include <stdio.h>
#include <stdarg.h>

#define COMPILER_ERROR_VA(M, ...) __compilerErrorHandler(__FILE__,__LINE__,M,__VA_ARGS__)
#define COMPILER_ASSERT_VA(C,M,...) if (!(C)) {__compilerErrorHandler(__FILE__,__LINE__,"Assertion failed: " #C, M, __VA_ARGS__)}

#define COMPILER_ERROR(M) (__compilerErrorHandler(__FILE__,__LINE__,M))
#define COMPILER_ASSERT(C,M) ((C) ? (1) : __compilerErrorHandler(__FILE__,__LINE__,"Assertion failed: " #C, M))

int __compilerErrorHandler(char const* filename, long int line, char const* format, ...);

#endif  // INCLUDED_USEFUL_H
