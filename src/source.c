#include "source.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

void PostFeedback(FeedbackKind kind, FeedbackNote* firstNote, char const* fmt, ...) {
    const int feedbackBufSize = 1024;
    char feedbackBuf[feedbackBufSize] = {0};
    va_list args;
    va_start(args, fmt);
    vsnprintf(feedbackBuf, feedbackBufSize-1, fmt, args);
    va_end(args);

    // Printing a message to stderr:
    for (FeedbackNote* noteP = firstNote; noteP; noteP = noteP->nextP) {
        Loc loc = noteP->loc;
        if (loc.lineIndex > 0 && loc.colIndex > 0) {
            fprintf(stderr, "- %s [%d:%d]: %s\n", prefix(kind), 1+loc.lineIndex, 1+loc.colIndex, feedbackBuf);
        } else {
            fprintf(stderr, "- %s: %s\n", prefix(kind), feedbackBuf);
        }
        fprintf(stderr, "  %s\n", noteP->message);
        fprintf(stderr, "  in [%s]\n", noteP->sourceP->path);
    }
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

    sourceP->peekLoc.offset = -1;
    sourceP->peekLoc.lineIndex = 0;
    sourceP->peekLoc.colIndex = -1;  // if LF is first char, line&col refreshed. else, colIndex++ => (0)

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

int ReadSourceReaderHead(Source* sourceP) {
    return sourceP->peekChar;
}

int AdvanceSourceReaderHead(Source* sourceP) {
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
    if (sourceP->promisedChar != EOF) {
        // using the promised char
        readChar = sourceP->promisedChar;
        sourceP->promisedChar = EOF;
    } else {
        // reading a fresh char
        readChar = fgetc(sourceP->fp);
        if (readChar < 0) {
            // EOF
            sourceP->peekChar = EOF;
            sourceP->atEof = 1;
            return 0;
        }
    }

    // Updating the peekChar, loc, and other attributes:
    sourceP->peekChar = readChar;
    sourceP->atEof = 0;
    sourceP->peekLoc.offset += 1;
    if (readChar == '\n' || readChar == '\r') {
        sourceP->peekLoc.lineIndex++;
        sourceP->peekLoc.colIndex = 0;
        
        // normalizing CRLF and CR line-endings to LF:
        if (readChar == '\r') {
            if (!feof(sourceP->fp)) {
                // reading the next char (for an LF)
                char nextChar = fgetc(sourceP->fp);
                if (nextChar != '\n') {
                    // Whoops! Not a Windows CRLF.
                    // Let's promise the read character for later:
                    sourceP->promisedChar = nextChar;
                }
            }
            sourceP->peekChar = '\n';
        }
    } else {
        sourceP->peekLoc.colIndex++;
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
    if (SourceReaderAtSof(source)) { return -1; }
    if (SourceReaderAtEof(source)) { return +1; }
    else {
        *locP = source->peekLoc;
        return 0;
    }
}
