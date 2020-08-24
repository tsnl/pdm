#pragma once

#include <stdbool.h>
#include <stdarg.h>

// invokes sprintf, then strdup using a short stack-buffer.
inline static char* fmt(char const* format, ...) {
    ssize_t const bufsize = 256;
    char buffer[bufsize];
    va_list ap;
    va_start(ap, format);
    int count = vsnprintf(buffer, bufsize-1, format, ap);
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