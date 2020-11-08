#include "source.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "useful.h"

#define FEEDBACK_BUF_SIZE (1024)

int errorPosted = 0;
Source* sourcesHead = NULL;
Source* sourcesTail = NULL;

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

FeedbackNote* CreateFeedbackNote(char const* message, Loc loc, FeedbackNote* next) {
    FeedbackNote* note = malloc(sizeof(FeedbackNote));
    note->message = message;
    note->loc = loc;
    note->nextP = next;
    return note;
}
void PostFeedback(FeedbackKind kind, FeedbackNote* firstNote, char const* fmt, ...) {
    if (kind == FBK_ERROR) {
        errorPosted = 1;
    }
    
    char feedbackBuf[FEEDBACK_BUF_SIZE] = {0};
    va_list args;
    va_start(args, fmt);
    vsnprintf(feedbackBuf, FEEDBACK_BUF_SIZE-1, fmt, args);
    va_end(args);

    // Printing a message to stderr:
    fprintf(stderr, "%s: %s\n", prefix(kind), feedbackBuf);
    for (FeedbackNote* noteP = firstNote; noteP; noteP = noteP->nextP) {
        Loc loc = noteP->loc;
        // if (loc.lineIndex > 0 && loc.colIndex > 0) {
        fprintf(stderr, "- %s", noteP->message);
        if (loc.lineIndex >= 0) {
            fprintf(stderr, " [%s:%d:%d]", noteP->loc.source->path, 1+loc.lineIndex, 1+loc.colIndex);
        }
        fprintf(stderr, "\n\n");
    }
}
int GetErrorPosted(void) {
    return errorPosted;
}

Loc NullLoc(void) {
    return (Loc) {NULL,-1,-1};
}
Span NullSpan(void) {
    return (Span) {NULL,-1,-1,-1,-1};
}

Span NewSpan(Loc first, Loc last) {
    if (first.source && last.source) {
        COMPILER_ASSERT(first.source == last.source, "Cannot make Span across two Locs of different 'source'.");
    } else {
        COMPILER_ASSERT(first.source || last.source, "Cannot make Span across two Locs without 'source'.");
    }
    Span span;
    span.source = first.source;
    span.first_line = first.lineIndex+1;
    span.first_column = first.colIndex+1;
    span.last_line = last.lineIndex+1;
    span.last_column = last.colIndex+1;
    return span;
}
Loc Span2Loc(Span span) {
    return FirstLocOfSpan(span);
}
Loc FirstLocOfSpan(Span span) {
    Loc loc;
    loc.source = span.source;
    loc.lineIndex = span.first_line-1;
    loc.colIndex = span.first_column-1;
    return loc;
}
Loc LastLocOfSpan(Span span) {
    Loc loc;
    loc.source = span.source;
    loc.lineIndex = span.last_line-1;
    loc.colIndex = span.last_column-1;
    return loc;
}

Source* CreateSource(char const* path) {
    Source* sourceP = (Source*)malloc(sizeof(Source));
    sourceP->prev = sourcesTail;
    sourceP->next = NULL;
    if (sourcesHead == NULL) {
        sourcesHead = sourceP;
    }
    sourcesTail = sourceP;
    
    sourceP->path = (char const*)strdup(path);
    if (!sourceP->path) {
        goto fail;
    }

    sourceP->fp = NULL;
    sourceP->fp = fopen(path, "r");
    if (!sourceP->fp) {
        goto fail;
    }

    sourceP->peekLoc.lineIndex = 0;
    sourceP->peekLoc.colIndex = -1;  // if LF is first char, col refreshed, line++; else, colIndex++ => (0)
    sourceP->peekLoc.source = sourceP;

    sourceP->peekChar = EOF;
    sourceP->promisedChar = EOF;
    sourceP->atEof = 0;

    return sourceP;

fail:
    if (sourceP) {
        free(sourceP);
    }
    return NULL;
}
Source* DupSource(Source* old) {
    return CreateSource(old->path);
}

int ReadSourceReaderHead(Source* sourceP) {
    return sourceP->peekChar;
}

int AdvanceSourceReaderHead(Source* source) {
    // Reading a character from the file, or just returning a promised
    // char if stored.
    // If a second char was read and not used, it is 'promised' for later.
    // - Characters are promised when we read for and do not obtain CRLFs.
    // Reading a char = advancing tape by 1.

    // (peekChar, atEof)
    // |- EOF, false: at start of file, no chars loaded
    // |- EOF, true: at end of file, last char loaded
    // |- (*), false: reading from the file

    char readChar;
    if (source->promisedChar != EOF) {
        // using the promised char
        readChar = source->promisedChar;
        source->promisedChar = EOF;
    } else if (SourceReaderAtEof(source)) {
        // already at EOF, cannot move further, returning 0
        return 0;
    } else {
        // reading a fresh char
        readChar = fgetc(source->fp);
        if (readChar < 0) {
            // found EOF, but read a char (moved into post-tape)
            source->peekChar = EOF;
            source->atEof = 1;
            return 1;
        }
    }

    // Updating the peekChar, loc, and other attributes:
    source->peekChar = readChar;
    source->atEof = 0;
    if (readChar == '\n' || readChar == '\r') {
        source->peekLoc.lineIndex++;
        source->peekLoc.colIndex = 0;
        
        // normalizing CRLF and CR line-endings to LF:
        if (readChar == '\r') {
            if (!feof(source->fp)) {
                // reading the next char (for an LF)
                char nextChar = fgetc(source->fp);
                if (nextChar != '\n') {
                    // Whoops! Not a Windows CRLF.
                    // Let's promise the read character for later:
                    source->promisedChar = nextChar;
                }
            }
            source->peekChar = '\n';
        }
    } else {
        source->peekLoc.colIndex++;
    }
    return 1;
}

int SourceReaderAtEof(Source* sourceP) {
    return sourceP->atEof;
}

int SourceReaderAtSof(Source* sourceP) {
    return sourceP->peekChar == EOF && !sourceP->atEof;
}

int GetSourceReaderHeadLoc(Source* source, Loc* locP) {
    if (SourceReaderAtSof(source)) { 
        // at SOF, no peekLoc is available.
        return -1; 
    }
    else {
        *locP = source->peekLoc;
        if (SourceReaderAtEof(source)) { 
            return +1; 
        }
        else {
            return 0;
        }
    }
}
