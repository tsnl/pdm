#include "source.h"

#include <stdio.h>
#include <string.h>

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

Source* newTailSource(Source* prev, char const* pathSuffix) {
    Source* sourceP = (Source*)malloc(sizeof(Source));
    sourceP->prev = prev;
    sourceP->next = NULL;
    sourceP->pathSuffix = (char const*)strdup(pathSuffix);
    if (!sourceP->pathSuffix) {
        goto fail;
    }

    sourceP->fp = NULL;
    sourceP->fp = fopen(pathSuffix);
    if (!sourceP->fp) {
        goto fail;
    }

    sourceP->loc.offset = -1;
    sourceP->loc.lineIndex = 0;
    sourceP->loc.columnIndex = -1;  // if LF is first char, line&col refreshed. else, colIndex++ => (0)

    sourceP->peekChar = fgetc(sourceP->fp);
    sourceP->atEof = false;

fail:
    if (sourceP) {
        free(sourceP);
    }
    return NULL;
}

void PostFeedback(FeedbackKind kind, Loc loc, char const* fmt, ...) {
    const int feedbackBufSize = 1024;
    char feedbackBuf[feedbackBufSize] = {0};
    va_list args;
    va_start(args, fmt);
    vsnprintf(feedbackBuf, feedbackBufSize-1, fmt, args);
    va_end(args);

    // Printing a message to stderr:
    if (loc.lineIndex > 0 && loc.columnIndex > 0) {
        fprintf(stderr, "- %s [%d:%d]: %s\n", prefix(kind), 1+loc.lineIndex, 1+loc.columnIndex, feedbackBuf);
    } else {
        fprintf(stderr, "- %s: %s\n", prefix(kind), feedbackBuf);
    }
}

void NewPackage(Package* packageP, char const* pathPrefix) {
    packageP->pathPrefix = strdup(pathPrefix);
    packageP->sourcesHead = NULL;
    packageP->sourcesTail = NULL;
}

Source* AddSourceToPackage(Package* packageP, char const* pathSuffix) {
    Source* newSource = newTailSource(newSource->sourcesTail, pathSuffix);
    return newSource;
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
        if (feof(sourceP)) {
            // EOF
            sourceP->peekChar = EOF;
            sourceP->atEof = true;
            return 0;
        } else {
            // reading a fresh char
            readChar = fgetc(sourceP->fp);
        }
    }

    // Updating the peekChar, loc, and other attributes:
    sourceP->peekChar = readChar;
    sourceP->atEof = false;
    sourceP->peekLoc.offset += 1;
    if (readChar == '\n' || readChar == '\r') {
        sourceP->peekLoc.lineIndex++;
        sourceP->peekLoc.columnIndex = 0;
        
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
        sourceP->peekLoc.columnIndex++;
    }
    return 1;
}

int GetSourceReaderHeadLoc(Source* source, Loc* locP) {
    if (SourceReaderAtSof(source)) { return -1; }
    if (SourceReaderAtEof(source)) { return +1; }
    else {
        *locP = source->peekLoc;
        return 0;
    }
}