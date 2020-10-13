#ifndef INCLUDED_USEFUL_H
#define INCLUDED_USEFUL_H

#include <stdbool.h>
#include <stdarg.h>

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

#endif  // INCLUDED_USEFUL_H
