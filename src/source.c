#include "source.h"

#include <stdio.h>

char const* prefix(FeedbackKind kind) {
    switch (kind) {
    case FBK_FATAL: return "FATAL";
    case FBK_ERROR: return "ERROR";
    case FBK_WARNING: return "WARNING";
    case FBK_INFO: return "INFO";
    case FBK_DEBUG: return "DEBUG";
    default: return NULL;
    }
}

void feedback(FeedbackKind kind, Loc loc, char const* fmt, ...) {
    const int feedback_buf_size = 1024;
    char feedback_buf[feedback_buf_size] = {0};
    va_list args;
    va_start(args, fmt);
    vsnprintf(feedback_buf, feedback_buf_size-1, fmt, args);
    va_end(args);

    // Printing a message to stderr:
    if (loc.line_index > 0 && loc.column_index > 0) {
        fprintf(stderr, "- %s [%d:%d]: %s\n", prefix(kind), 1+loc.line_index, 1+loc.column_index, feedback_buf);
    } else {
        fprintf(stderr, "- %s: %s\n", prefix(kind), feedback_buf);
    }
}
