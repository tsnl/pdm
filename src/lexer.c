#include "lexer.h"

#include <ctype.h>
#include <assert.h>
#include <string.h>

#include "config.h"
#include "source.h"
#include "useful.h"

#include "intern/strings.h"
#include "stb/stretchy_buffer.h"

struct strings* symbolsDict;

static SymbolID kwImportSymbolID = 0;
static SymbolID kwExportSymbolID = 0;
static SymbolID kwDoSymbolID = 0;
static SymbolID kwIfSymbolID = 0;
static SymbolID kwThenSymbolID = 0;
static SymbolID kwElseSymbolID = 0;
static SymbolID kwOperatorSymbolID = 0;
static SymbolID kwMatchSymbolID = 0;
static SymbolID kwWithSymbolID = 0;
static SymbolID kwReturnSymbolID = 0;
static SymbolID kwCheckSymbolID = 0;

static TokenKind lexOneToken(Source* source, TokenInfo* infoP);
static TokenKind lexOneSimpleToken(Source* source, TokenInfo* infoP);
static TokenKind helpLexOneSimpleToken(Source* source, TokenInfo* infoP);
static TokenKind lexOneNumber(Source* source, TokenInfo* optInfoP);
static TokenKind lexOneIntChunk(Source* source, TokenInfo* optInfoP, int noPrefix);
static TokenKind lexOneIdOrKeyword(Source* source, TokenInfo* optInfoP);
static TokenKind lexOneString(Source* source, TokenInfo* infoP);
inline static void skipWhitespace(Source* source);

inline static bool isFirstIdChar(char ch);
inline static bool isIdChar(char ch);

// In general, we assume the source head is over the first character of the token to read.
// - This 'hovering reader' approach => LL(1) lexer.
// - Read, Advance, Read, Advance...
// - if (Advance...) is an effective way to check for and handle EOFs.

void InitLexer(void) {
    symbolsDict = strings_new();
    kwImportSymbolID = strings_intern(symbolsDict, "import");
    kwExportSymbolID = strings_intern(symbolsDict, "export");
    kwDoSymbolID = strings_intern(symbolsDict, "do");
    kwIfSymbolID = strings_intern(symbolsDict, "if");
    kwThenSymbolID = strings_intern(symbolsDict, "then");
    kwElseSymbolID = strings_intern(symbolsDict, "else");
    kwOperatorSymbolID = strings_intern(symbolsDict, "operator");
    kwMatchSymbolID = strings_intern(symbolsDict, "match");
    kwWithSymbolID = strings_intern(symbolsDict, "with");
    kwReturnSymbolID = strings_intern(symbolsDict, "return");
    kwCheckSymbolID = strings_intern(symbolsDict, "check");
}

void DeInitLexer(void) {
    // do nothing for now.
    strings_free(symbolsDict);
}

TokenKind lexOneToken(Source* source, TokenInfo* infoP) {
    // At SOF, reading the first character.
    if (SourceReaderAtSof(source)) {
        AdvanceSourceReaderHead(source);
    }
    
    // Ignoring whitespace & comments:
    while (isspace(ReadSourceReaderHead(source)) || ReadSourceReaderHead(source) == '#') {
        skipWhitespace(source);
        if (ReadSourceReaderHead(source) == '#') {
            do {
                AdvanceSourceReaderHead(source);
            } while (ReadSourceReaderHead(source) != '\n' && !SourceReaderAtEof(source));
        }
        skipWhitespace(source);
    }

    // If at EOF, returning TK_EOS (not TK_NULL!) to indicate the end of this token stream.
    if (SourceReaderAtEof(source)) {
        return TK_EOS;
    }

    //
    // Populating 'loc' before any real tokens:
    //

    GetSourceReaderHeadLoc(source, &infoP->loc);
    
    //
    // Simple tokens:
    //

    TokenKind kind = lexOneSimpleToken(source, infoP);
    if (kind != TK_NULL) {
        return kind;
    }

    //
    // Numbers:
    //

    if (isdigit(ReadSourceReaderHead(source))) {
        return lexOneNumber(source, infoP);
    }

    //
    // Strings:
    //

    if (ReadSourceReaderHead(source) == '"' || ReadSourceReaderHead(source) == '\'') {
        return lexOneString(source, infoP);
    }
    
    //
    // IDs and keywords:
    //

    if (isFirstIdChar(ReadSourceReaderHead(source))) {
        return lexOneIdOrKeyword(source, infoP);
    }

    //
    // Error: unknown token kind.
    // Offer feedback with location.
    //
    
    char offendingChar = ReadSourceReaderHead(source);
    FeedbackNote note = {"here...", infoP->loc, NULL};
    PostFeedback(FBK_ERROR, &note, "Before '%c' (%d), expected a valid token.", offendingChar, (int)offendingChar);

    return TK_NULL;
}

TokenKind lexOneSimpleToken(Source* source, TokenInfo* optInfoP) {
    TokenKind tk = helpLexOneSimpleToken(source, optInfoP);
    if (tk != TK_NULL) {
        AdvanceSourceReaderHead(source);
    }
    return tk;
}
TokenKind helpLexOneSimpleToken(Source* source, TokenInfo* optInfoP) {
    // lexes all of a simple token, advances EXCEPT the last character.
    switch (ReadSourceReaderHead(source)) {
        case '.': return TK_DOT;
        case ':': return TK_COLON;
        case ',': return TK_COMMA;
        case ';': return TK_SEMICOLON;
        case '(': return TK_LPAREN;
        case ')': return TK_RPAREN;
        case '[': return TK_LSQBRK;
        case ']': return TK_RSQBRK;
        case '{': return TK_LCYBRK;
        case '}': return TK_RCYBRK;
        case '*': return TK_ASTERISK;
        case '/': return TK_FSLASH;
        case '%': return TK_PERCENT;
        case '+': return TK_PLUS;
        case '^': return TK_CARET;
        case '&': return TK_AND;
        case '|': return TK_OR;
        case '=':
        {
            if (AdvanceSourceReaderHead(source)) {
                if (ReadSourceReaderHead(source) == '=') {
                    return TK_EQUALS;
                }
            }
            return TK_BIND;
        }
        case '!':
        {
            if (AdvanceSourceReaderHead(source)) {
                if (ReadSourceReaderHead(source) == '=') {
                    return TK_NEQUALS;
                }
            }
            return TK_NOT;
        }
        case '-': 
        {
            if (AdvanceSourceReaderHead(source)) {
                if (ReadSourceReaderHead(source) == '>') {
                    return TK_ARROW;
                }
            }
            return TK_MINUS;
        }
        case '<': 
        {
            if (AdvanceSourceReaderHead(source)) {
                if (ReadSourceReaderHead(source) == '=') {
                    return TK_LETHAN;
                }
            }
            return TK_LTHAN;
        }
        case '>':
        {
            if (AdvanceSourceReaderHead(source)) {
                if (ReadSourceReaderHead(source) == '=') {
                    return TK_GETHAN;
                }
            }
            return TK_GTHAN;
        }
        default:
        {
            return TK_NULL;
        }
    }
}
TokenKind lexOneNumber(Source* source, TokenInfo* optInfoP) {
    TokenInfo prefixTokenInfo;
    TokenKind prefixTokenKind = lexOneIntChunk(source, &prefixTokenInfo, 0);
    if (prefixTokenKind == TK_DINT_LIT) {
        if (ReadSourceReaderHead(source) == '.') {
            // float
            if (AdvanceSourceReaderHead(source)) {
                TokenInfo suffixTokenInfo;
                TokenKind suffixTokenKind = lexOneIntChunk(source, &suffixTokenInfo, true);
                
                // converting prefix and suffix ints into a double value:
                if (optInfoP) {
                    double dotPrefix = prefixTokenInfo.as.Int;
                    double dotSuffix = suffixTokenInfo.as.Int;
                    while (dotSuffix >= 1.0) {
                        dotSuffix /= 10;
                    }
                    double value = dotPrefix + dotSuffix;
                    if (optInfoP) {
                        optInfoP->as.Float = value;
                    }
                }
                return TK_FLOAT_LIT;
            }
        }
    }
    if (optInfoP) {
        *optInfoP = prefixTokenInfo;
    }
    return prefixTokenKind;
}
TokenKind lexOneIntChunk(Source* source, TokenInfo* optInfoP, int noPrefix) {
    // Checking for a hex prefix:
    TokenKind tokenKind = TK_DINT_LIT;
    if (!noPrefix) {
        if (ReadSourceReaderHead(source) == '0') {
            if (AdvanceSourceReaderHead(source)) {
                if (ReadSourceReaderHead(source) == 'x') {
                    // 0x hex prefix detected.
                    AdvanceSourceReaderHead(source);
                    tokenKind = TK_XINT_LIT;
                }
            }
        }
    }
    // Repeatedly reading integer characters:
    size_t value = 0;
    do {
        char intChar = ReadSourceReaderHead(source);
        if (intChar == '_') {
            continue;
        } else if (tokenKind == TK_DINT_LIT) {
            if (isdigit(intChar)) {
                value = (10*value) + (intChar - '0');
            } else {
                break;
            }
        } else if (tokenKind == TK_XINT_LIT) {
            if (isxdigit(intChar)) {
                if      (intChar == 'a' || intChar == 'A') { value = (16*value) + (10); }
                else if (intChar == 'b' || intChar == 'B') { value = (16*value) + (11); }
                else if (intChar == 'c' || intChar == 'C') { value = (16*value) + (12); }
                else if (intChar == 'd' || intChar == 'D') { value = (16*value) + (13); }
                else if (intChar == 'e' || intChar == 'E') { value = (16*value) + (14); }
                else if (intChar == 'f' || intChar == 'F') { value = (16*value) + (15); }
                else { value = (16*value) + (intChar - '0'); }
            } else {
                break;
            }
        } else if (DEBUG) {
            printf("!!- Invalid state.\n");
        } else {
            assert(0 && "Invalid state.");
        }
    } while (AdvanceSourceReaderHead(source));

    // Writing results to infoP:
    if (optInfoP) {
        optInfoP->as.Int = value;
    }

    // Returning results:
    return tokenKind;
}
TokenKind lexOneIdOrKeyword(Source* source, TokenInfo* optInfoP) {
    // The longest supported ID is (MAX_ID_LEN) characters long.
    size_t index;
    char charBuf[MAX_ID_LEN+1];
    for (index = 0; index < MAX_ID_LEN; index++) {
        // reading the next character:
        char ch = ReadSourceReaderHead(source);
        
        // adding the character to the charBuf:
        if (isIdChar(ch)) {
            charBuf[index] = ch;
            if (!AdvanceSourceReaderHead(source)) {
                break;
            }
        } else {
            break;
        }
    }
    charBuf[index] = '\0';
    if (isIdChar(ReadSourceReaderHead(source))) {
        // ID too long, error.
        PostFeedback(FBK_ERROR, NULL, "ID '%s...' exceeds the maximum supported ID length of (%d) characters.", charBuf, MAX_ID_LEN);
        return TK_NULL;
    }

    // Looking up charBuf as a keyword or symbol:
    SymbolID kwID = strings_lookup(symbolsDict, charBuf);
    if (kwID == 0) {
        SymbolID symbolID = Symbol(charBuf);
        assert(kwID == 0 && "`strings_lookup` produced an ID but no match.");
        if (optInfoP) {
            optInfoP->as.ID = symbolID;
        }
        return TK_ID;
    }
    if (kwID == kwImportSymbolID) { return TK_KW_IMPORT; }
    if (kwID == kwExportSymbolID) { return TK_KW_EXPORT; }
    if (kwID == kwDoSymbolID) { return TK_KW_DO; }
    if (kwID == kwIfSymbolID) { return TK_KW_IF; }
    if (kwID == kwThenSymbolID) { return TK_KW_THEN; }
    if (kwID == kwElseSymbolID) { return TK_KW_ELSE; }
    if (kwID == kwOperatorSymbolID) { return TK_KW_OPERATOR; }
    if (kwID == kwMatchSymbolID) { return TK_KW_MATCH; }
    if (kwID == kwWithSymbolID) { return TK_KW_WITH; }
    if (kwID == kwReturnSymbolID) { return TK_KW_RETURN; }
    if (kwID == kwCheckSymbolID) { return TK_KW_CHECK; }
    if (DEBUG) {
        printf("!!- Keyword not implemented: '%s' (id=%d)\n", strings_lookup_id(symbolsDict, kwID), kwID);
    } else {
        assert(0 && "Unimplemented keyword");
    }
    return TK_NULL;
}
static TokenKind lexOneString(Source* source, TokenInfo* infoP) {
    // reading the first character, i.e., the quote character:
    int quoteChar = ReadSourceReaderHead(source);
    TokenKind tokenKind;
    if (quoteChar == '"') {
        tokenKind = TK_DQSTRING_LIT;
    } else if (quoteChar == '\'') { 
        tokenKind = TK_SQSTRING_LIT;
    } else if (DEBUG) {
        assert(0 && "Invalid quote character.");
    }
    AdvanceSourceReaderHead(source);

    // reading the string content:
    int* contentStretchyBuffer = NULL;
    while (ReadSourceReaderHead(source) != quoteChar) {
        if (ReadSourceReaderHead(source) == '\\') {
            Loc escapeSequenceLoc;
            GetSourceReaderHeadLoc(source, &escapeSequenceLoc);

            AdvanceSourceReaderHead(source);

            int valid = 1;
            if (ReadSourceReaderHead(source) == 'n') {
                sb_push(contentStretchyBuffer, '\n');
            } else if (ReadSourceReaderHead(source) == 'r') {
                sb_push(contentStretchyBuffer, '\r');
            } else if (ReadSourceReaderHead(source) == 'a') {
                sb_push(contentStretchyBuffer, '\a');
            } else if (ReadSourceReaderHead(source) == 't') {
                sb_push(contentStretchyBuffer, '\t');
            } else if (ReadSourceReaderHead(source) == '\\') {
                sb_push(contentStretchyBuffer, '\\');
            } else if (ReadSourceReaderHead(source) == quoteChar) {
                sb_push(contentStretchyBuffer, quoteChar);
            } else {
                valid = 0;
            }
            AdvanceSourceReaderHead(source);

            if (!valid) {
                char invalidSecondChar = ReadSourceReaderHead(source);
                
                // invalid escape sequence!
                FeedbackNote note = {"here...", escapeSequenceLoc, NULL};

                if (invalidSecondChar == EOF) {
                    PostFeedback(FBK_ERROR, &note, "Invalid escape sequence at EOF");
                } else {
                    PostFeedback(FBK_ERROR, &note, "Invalid escape sequence: \\%c", invalidSecondChar);
                }
                break;
            }

        } else {
            sb_push(contentStretchyBuffer, ReadSourceReaderHead(source));
            AdvanceSourceReaderHead(source);
        }
    }

    // reading the closing quote character:
    if (ReadSourceReaderHead(source) == quoteChar) {
        AdvanceSourceReaderHead(source);
        sb_push(contentStretchyBuffer, '\0');
        infoP->as.UnicodeStringSb = contentStretchyBuffer;
        return tokenKind;
    } else {
        FeedbackNote firstNote = {"here...", infoP->loc, NULL};
        PostFeedback(FBK_ERROR, &firstNote, "Invalid string literal");
        return TK_NULL;
    }
}

inline void skipWhitespace(Source* source) {
    int stop = 0;
    do {
        switch (ReadSourceReaderHead(source)) {
            case ' ':
            case '\t':
            case '\n': 
            case '\v':
            {
                continue;
            }
            default: 
            {
                stop = 1;
                break;
            }
        }
    } while (!stop && AdvanceSourceReaderHead(source));
}

inline bool isFirstIdChar(char ch) {
    return isalpha(ch) || ch == '_';
}
inline bool isIdChar(char ch) {
    return isalnum(ch) || ch == '_';
}

TokenKind LexOneToken(Source* source, TokenInfo* infoP) {
    TokenKind tk = lexOneToken(source, infoP);
    // char buffer[512];
    // TokenAsText(tk, infoP, buffer, 512);
    // printf("%s\n", buffer);
    return tk;
}

void DebugLexer(Source* source) {
    TokenInfo info;
    char lineBuffer[512];
    for (;;) {
        TokenKind kind = LexOneToken(source, &info);
        if (kind == TK_NULL) {
            printf("Terminated with TK_NULL\n");
            break;
        }
        if (kind == TK_EOS) {
            printf("Terminated with TK_EOS\n");
            break;
        }
        assert(TokenToText(kind, &info, lineBuffer, 512) < 512);
        printf("%s\n", lineBuffer);
    }
    // char buffer[512];
    // TokenAsText(tk, infoP, buffer, 512);
    // printf("%s\n", buffer);
}

int TokenToText(TokenKind tk, TokenInfo* ti, char* buf, int bufLength) {
    int const maxInfoLen = MAX_ID_LEN;
    char const* name;
    char info[maxInfoLen+1] = {'\0'};
    switch (tk)
    {
        case TK_DOT:
        {
            name = ".";
            break;
        }
        case TK_COMMA:
        {
            name = ",";
            break;
        }
        case TK_COLON:
        {
            name = ":";
            break;
        }
        case TK_LPAREN:
        {
            name = "(";
            break;
        }
        case TK_RPAREN:
        {
            name = ")";
            break;
        }
        case TK_LSQBRK:
        {
            name = "[";
            break;
        }
        case TK_RSQBRK:
        {
            name = "]";
            break;
        }
        case TK_LCYBRK:
        {
            name = "{";
            break;
        }
        case TK_RCYBRK:
        {
            name = "}";
            break;
        }
        case TK_SEMICOLON:
        {
            name = ";";
            break;
        }
        case TK_ASTERISK:
        {
            name = "*";
            break;
        }
        case TK_FSLASH:
        {
            name = "/";
            break;
        }
        case TK_PERCENT:
        {
            name = "%";
            break;
        }
        case TK_PLUS:
        {
            name = "+";
            break;
        }
        case TK_MINUS:
        {
            name = "-";
            break;
        }
        case TK_AND:
        {
            name = "&";
            break;
        }
        case TK_OR:
        {
            name = "|";
            break;
        }
        case TK_CARET:
        {
            name = "^";
            break;
        }
        case TK_NOT:
        {
            name = "!";
            break;
        }
        case TK_BIND:
        {
            name = "=";
            break;
        }
        case TK_EQUALS:
        {
            name = "==";
            break;
        }
        case TK_NEQUALS:
        {
            name = "!=";
            break;
        }
        case TK_KW_IMPORT:
        {
            name = "import";
            break;
        }
        case TK_KW_EXPORT:
        {
            name = "export";
            break;
        }
        case TK_KW_DO:
        {
            name = "do";
            break;
        }
        case TK_KW_IF:
        {
            name = "if";
            break;
        }
        case TK_KW_THEN:
        {
            name = "then";
            break;
        }
        case TK_KW_ELSE:
        {
            name = "else";
            break;
        }
        case TK_KW_OPERATOR:
        {
            name = "operator";
            break;
        }
        case TK_KW_MATCH:
        {
            name = "match";
            break;
        }
        case TK_KW_RETURN:
        {
            name = "return";
            break;
        }
        case TK_KW_CHECK:
        {
            name = "check";
            break;
        }
        case TK_DINT_LIT:
        {
            name = "<d-int>";
            snprintf(info, maxInfoLen, "%zd", ti->as.Int);
            break;
        }
        case TK_XINT_LIT:
        {
            name = "<x-int>";
            snprintf(info, maxInfoLen, "%zd", ti->as.Int);
            break;
        }
        case TK_FLOAT_LIT:
        {
            name = "<float>";
            snprintf(info, maxInfoLen, "%Lf", ti->as.Float);
            break;
        }
        case TK_DQSTRING_LIT:
        {
            name = "<text>";
            info[0] = '"';
            int index;
            for (index = 0; ti->as.UnicodeStringSb[index]; index++) {
                // todo: handle escape sequences correctly
                info[1+index] = ti->as.UnicodeStringSb[index];
            }
            info[index+1] = '"';
            break;
        }
        case TK_SQSTRING_LIT:
        {
            name = "<text>";
            info[0] = '\'';
            int index;
            for (index = 0; ti->as.UnicodeStringSb[index]; index++) {
                // todo: handle escape sequences correctly
                info[1+index] = ti->as.UnicodeStringSb[index];
            }
            info[index+1] = '\'';
            break;
        }
        case TK_ID:
        {
            name = "<id>";
            snprintf(info, maxInfoLen, "%s", GetSymbolText(ti->as.ID));
            break;
        }
        case TK_ARROW:
        {
            name = "->";
            break;
        }
        case TK_NULL:
        {
            name = "<NULL>";
            break;
        }
        default:
        {
            break;
        }
    }
    if (info[0]) {
        return snprintf(buf, bufLength-1, "%s (%s)", info, name);
    } else {
        return snprintf(buf, bufLength-1, "%s", name);
    }
}