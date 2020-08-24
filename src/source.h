#ifndef INCLUDED_SOURCE_H
#define INCLUDED_SOURCE_H

#include <stdarg.h>
#include <stdio.h>

// Compilers transform source into some output; this module models that source.
// - NewPackage: mark a filesystem subtree as a package.
// - AddSourceToPackage: add a source file to a package using the source path prefix within the package subtree.
// - PostFeedback: writes a feedback message about a Source.

typedef struct Loc          Loc;
typedef struct Package      Package;
typedef struct Source       Source;
typedef enum   FeedbackKind FeedbackKind;
typedef struct FeedbackNote FeedbackNote;

struct Package {
    char const* pathPrefix;
    Source* sourcesHead;
    Source* sourcesTail;
};

struct Source {
    char const* pathSuffix;
    Source* prev;
    Source* next;
    FILE* fp;
    Loc peekLoc;
    int peekChar;
    int atEof;
};

struct Loc {
    ssize_t offset;
    int lineIndex;
    int colIndex;
};

void NewPackage(Package* packageP, char const* pathPrefix);
Source* AddSourceToPackage(Package* package);

enum FeedbackKind {
    FBK_FATAL,
    FBK_ERROR,
    FBK_WARNING,
    FBK_INFO,
    FBK_DEBUG
};

struct FeedbackNote {
    char const* message;
    Source* sourceP;
    Loc loc;
    FeedbackNote* nextP;
};

void PostFeedback(FeedbackKind kind, FeedbackNote* firstNote, char const* fmt, ...);

// The SourceReader API models strings as a finite tape with a traversing head capable of reading 1 char.
// - AdvanceSourceReaderHead: advance head by (+1) bytes.
// - ReadSourceReaderHead: read the char under the head.
// - SourceReaderAtSof: (1) iff the head is not positioned on the tape, but before it, else (0)
// - SourceReaderAtEof: (1) iff the head is not positioned on the tape, but after it,  else (0)
// - GetSourceReaderHeadLoc: populates a Loc struct describing the head's position

// NOTE: for a 0-length tape, the head proceeds from SOF to EOF in one Advance.

// advances the reading head by one character.
// must be called before peeking the first character.
// returns (0) if the head is in EOF after reading, else (1)
int AdvanceSourceReaderHead(Source* sourceP);

// returns the character under head in the filestream, else EOF.
int ReadSourceReaderHead(Source* sourceP);

// returns (1) if the source is at SOF, else (0).
// if Peek returns EOF and SourceReaderAtSof is (0), then we are at the EOF (end of file).
int SourceReaderAtSof(Source* sourceP);

// returns (1) if the source is at EOF, else (0).
// if Peek returns EOF and SourceReaderAtEof is (0), then we are at the SOF (start of file).
int SourceReaderAtEof(Source* sourceP);

// populates a Loc struct describing the head's position.
// returns (0) if head is in-tape, (1) if head is at EOF, (-1) if head is at SOF.
int GetSourceReaderHeadLoc(Source* source, Loc* locP);

#endif  // INCLUDED_SOURCE_H
