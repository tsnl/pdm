#include "lexer.h"

#include <ctype.h>
#include <assert.h>
#include <string.h>

#include "config.h"
#include "useful.h"

#include "intern/strings.h"

struct strings* symbolsDict;

static SymbolID kwImportSymbolID = 0;
static SymbolID kwExportSymbolID = 0;
static SymbolID kwDoSymbolID = 0;
static SymbolID kwIfSymbolID = 0;
static SymbolID kwThenSymbolID = 0;
static SymbolID kwElseSymbolID = 0;
static SymbolID kwOperatorSymbolID = 0;
static SymbolID kwMatchSymbolID = 0;

static TokenKind lexOneNumber(Source* source, TokenInfo* optInfoP);
static TokenKind lexOneIntChunk(Source* source, TokenInfo* optInfoP, bool noPrefix);
static TokenKind lexOneIdOrKeyword(Source* source, TokenInfo* optInfoP);
inline static void skipWhitespace(Source* source);

inline static bool isIdChar(char ch);

// In general, we assume the source head is over the first character of the token to read.
// - This 'hovering reader' approach => LL(1) lexer.
// - Read, Advance, Read, Advance...
// - if(Advance) is an effective way to handle EOFs.

void InitLexer(void) {
    kwImportSymbolID = strings_intern(symbolsDict, "import");
    kwExportSymbolID = strings_intern(symbolsDict, "export");
    kwDoSymbolID = strings_intern(symbolsDict, "do");
    kwIfSymbolID = strings_intern(symbolsDict, "if");
    kwThenSymbolID = strings_intern(symbolsDict, "then");
    kwElseSymbolID = strings_intern(symbolsDict, "else");
    kwOperatorSymbolID = strings_intern(symbolsDict, "operator");
    kwMatchSymbolID = strings_intern(symbolsDict, "match");
}

void DeInitLexer(void) {
    // do nothing for now.
}

TokenKind LexOneToken(Source* source, TokenInfo* optInfoP) {
    // At SOF, reading the first character.
    if (SourceReaderAtSof(source)) {
        AdvanceSourceReaderHead(source);
    }

    // If at EOF, returning TK_EOS (not TK_NULL!) to indicate the end of this token stream.
    if (SourceReaderAtEof(source)) {
        return TK_EOS;
    }
    
    //
    // Ignoring whitespace and comments:
    //

    skipWhitespace(source);

    while (ReadSourceReaderHead(source) == '#') {
        for (;;) {
            AdvanceSourceReaderHead(source);
            if (ReadSourceReaderHead(source) == '\n') {
                break;
            }
        }
        skipWhitespace(source);
    }

    //
    // Simple tokens:
    //

    switch (ReadSourceReaderHead(source)) {
        case '(': return TK_LPAREN;
        case ')': return TK_RPAREN;
        case '[': return TK_LSQBRK;
        case ']': return TK_RSQBRK;
        case '{': return TK_LCYBRK;
        case '}': return TK_RCYBRK;
        case ',': return TK_COMMA;
        case ':': return TK_COLON;
        case ';': return TK_SEMICOLON;
        case '=': return TK_EQUALS;
        case '*': return TK_ASTERISK;
        case '/': return TK_FSLASH;
        case '%': return TK_PERCENT;
        case '+': return TK_PLUS;
        case '&': return TK_AND;
        case '|': return TK_OR;
        case '^': return TK_CARET;
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
                } else if (ReadSourceReaderHead(source) == '>') {
                    return TK_NEQUALS;
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
    }

    //
    // Numbers:
    //

    TokenKind numTk = lexOneNumber(source, optInfoP);
    if (numTk != TK_NULL) {
        return numTk;
    }

    //
    // Strings:
    //

    // if (GetSourceReaderHeadLoc(source) == '"') {
    //     // todo: scan double-quoted strings
    // }
    // if (GetSourceReaderHeadLoc(source) == '\'') {
    //     // todo: scan single-quoted strings
    // }

    //
    // IDs and keywords:
    //

    TokenKind idOrKeywordTk = lexOneIdOrKeyword(source, optInfoP);
    if (numTk != TK_NULL) {
        return idOrKeywordTk;
    }

    return TK_NULL;
}

TokenKind lexOneNumber(Source* source, TokenInfo* optInfoP) {
    TokenInfo prefixTokenInfo;
    TokenKind prefixTokenKind = lexOneIntChunk(source, &prefixTokenInfo, false);
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

TokenKind lexOneIntChunk(Source* source, TokenInfo* optInfoP, bool noPrefix) {
    // Checking for a hex prefix:
    TokenKind tokenKind;
    if (!noPrefix) {
        tokenKind = TK_DINT_LIT;
        if (ReadSourceReaderHead(source) == '0') {
            if (AdvanceSourceReaderHead(source)) {
                if (ReadSourceReaderHead(source) == 'x') {
                    // 0x hex prefix detected.
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
        if (!AdvanceSourceReaderHead(source)) {
            break;
        }
        // adding the character to the charBuf:
        if (isIdChar(ch)) {
            charBuf[index++] = ch;
        } else {
            break;
        }
    }
    charBuf[index] = '\0';
    if (isIdChar(ReadSourceReaderHead(source))) {
        // ID too long, error.
        // TODO: feedback here
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
    else {
        assert(0 && "Unimplemented keyword");
    }
}

inline void skipWhitespace(Source* source) {
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
                break;
            }
        }
    } while (AdvanceSourceReaderHead(source));
}

inline bool isIdChar(char ch) {
    return isalpha(ch) || ch == '_';
}
