#ifndef INCLUDED_SOURCE_H
#define INCLUDED_SOURCE_H

#include <stdarg.h>

typedef struct Loc          Loc;
typedef struct Package      Package;
typedef struct Source       Source;
typedef enum   FeedbackKind FeedbackKind;

struct Package {
    char const* abs_path;
    Source* sources_p;
};

struct Source {
    char const* rel_path;
    Source* prev;
};

struct Loc {
    Source* source;
    int line_index;
    int column_index;
};

enum FeedbackKind {
    FBK_FATAL,
    FBK_ERROR,
    FBK_WARNING,
    FBK_INFO,
    FBK_DEBUG
};

void feedback(FeedbackKind kind, Loc loc, char const* fmt, ...);

#endif  // INCLUDED_SOURCE_H
