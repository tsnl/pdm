#include "lexer.h"

#include <ctype.h>
#include <assert.h>
#include <string.h>

#include "intern/strings.h"
#include "stb/stretchy_buffer.h"

#include "config.h"
#include "source.h"
#include "useful.h"

#include "parser.tab.h"

struct strings* symbolsDict;

static SymbolID kwNamespaceSymbolID = 0;
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
static SymbolID kwDiscardSymbolID = 0;
static SymbolID kwLinkSymbolID = 0;
static SymbolID kwFunSymbolID = 0;
static SymbolID kwDefSymbolID = 0;
static SymbolID kwLetSymbolID = 0;
static SymbolID kwAndSymbolID = 0;
static SymbolID kwXOrSymbolID = 0;
static SymbolID kwOrSymbolID = 0;
static SymbolID kwNotSymbolID = 0;
static SymbolID kwSetSymbolID = 0;
static SymbolID kwTypeSymbolID = 0;
static SymbolID kwEnumSymbolID = 0;
static SymbolID kwModSymbolID = 0;
static SymbolID kwTTupleSymbolID = 0;
static SymbolID kwTArraySymbolID = 0;
static SymbolID kwFromSymbolID = 0;
static SymbolID kwAsSymbolID = 0;

static TokenKind lexOneToken(Source* source, TokenInfo* info, Span* span);
static TokenKind lexOneSimpleToken(Source* source);
static TokenKind helpLexOneSimpleToken(Source* source);
static TokenKind lexOneNumber(Source* source, TokenInfo* info);
static TokenKind lexOneIntChunk(Source* source, TokenInfo* info, int noPrefix);
static TokenKind lexOneIdOrKeyword(Source* source, TokenInfo* info);
static TokenKind lexOneString(Source* source, TokenInfo* info, Loc firstLoc);
inline static void skipWhitespace(Source* source);

inline static bool isFirstIdChar(char ch);
inline static bool isIdChar(char ch);

static int getIdTextKind(char const* idText);

// In general, we assume the source head is over the first character of the token to read.
// - This 'hovering reader' approach => LL(1) lexer.
// - Read, Advance, Read, Advance...
// - if (Advance...) is an effective way to check for and handle EOFs.

void InitLexer(void) {
    symbolsDict = strings_new();
    kwNamespaceSymbolID = strings_intern(symbolsDict, "namespace");
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
    kwDiscardSymbolID = strings_intern(symbolsDict, "discard");
    kwLinkSymbolID = strings_intern(symbolsDict, "link");
    kwFunSymbolID = strings_intern(symbolsDict, "fun");
    kwDefSymbolID = strings_intern(symbolsDict, "def");
    kwLetSymbolID = strings_intern(symbolsDict, "let");
    kwAndSymbolID = strings_intern(symbolsDict, "and");
    kwXOrSymbolID = strings_intern(symbolsDict, "xor");
    kwOrSymbolID = strings_intern(symbolsDict, "or");
    kwNotSymbolID = strings_intern(symbolsDict, "not");
    kwSetSymbolID = strings_intern(symbolsDict, "set");
    kwTypeSymbolID = strings_intern(symbolsDict, "type");
    kwEnumSymbolID = strings_intern(symbolsDict, "enum");
    kwModSymbolID = strings_intern(symbolsDict, "mod");
    kwTArraySymbolID = strings_intern(symbolsDict, "Array");
    kwTTupleSymbolID = strings_intern(symbolsDict, "Tuple");
    kwFromSymbolID = strings_intern(symbolsDict, "from");
    kwAsSymbolID = strings_intern(symbolsDict, "as");
}

void DeInitLexer(void) {
    // do nothing for now.
    strings_free(symbolsDict);
}

TokenKind lexOneToken(Source* source, TokenInfo* info, Span* span) {
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
    // populating firstLoc before any real tokens:
    //

    Loc firstLoc; 
    GetSourceReaderHeadLoc(source, &firstLoc);
    
    //
    // Simple tokens:
    //

    TokenKind outKind = lexOneSimpleToken(source);
    if (outKind == TK_NULL) {
        // must be a more complex token...

        int firstChar = ReadSourceReaderHead(source);
        
        // numbers:
        if (isdigit(firstChar)) {
            outKind = lexOneNumber(source, info);
        }

        // strings:    
        else if (firstChar == '"' || firstChar == '\'') {
            outKind = lexOneString(source, info, firstLoc);
        }

        // IDs and keywords:
        else if (isFirstIdChar(firstChar)) {
            outKind = lexOneIdOrKeyword(source, info);
        }

        // Error: unknown token kind.
        // Offer feedback with location, RETURN EARLY with TK_NULL
        else {
            char offendingChar = firstChar;
            FeedbackNote note = {"here...", firstLoc, NULL};
            PostFeedback(FBK_ERROR, &note, "Before '%c' (%d), expected a valid token.", offendingChar, (int)offendingChar);
            return TK_NULL;
        }
    }

    // populating lastLoc, creating span, returning VALID token kind found so far:
    Loc lastLoc; 
    // int headPos = GetSourceReaderHeadLoc(source,&lastLoc);
    GetSourceReaderHeadLoc(source,&lastLoc);
    *span = NewSpan(firstLoc,lastLoc);
    return outKind;
}

TokenKind lexOneSimpleToken(Source* source) {
    TokenKind tk = helpLexOneSimpleToken(source);
    // if (tk != TK_NULL) {
    //     AdvanceSourceReaderHead(source);
    // }
    return tk;
}
TokenKind helpLexOneSimpleToken(Source* source) {
    // lexes all of a simple token
    // - return 'NULL' and do not advance characters at all to opt-out, leaving reader head as is.
    switch (ReadSourceReaderHead(source)) {
        case '.':
        {
            if (AdvanceSourceReaderHead(source)) {
                return TK_DOT;
            }
            break;
        }
        case ',':
        {
            if (AdvanceSourceReaderHead(source)) {
                return TK_COMMA;
            }
            break;
        }
        case ';':
        {
            if (AdvanceSourceReaderHead(source)) {
                return TK_SEMICOLON;
            }
            break;
        }
        case '(':
        {
            if (AdvanceSourceReaderHead(source)) {
                return TK_LPAREN;
            }
            break;
        }
        case ')':
        {
            if (AdvanceSourceReaderHead(source)) {
                return TK_RPAREN;
            }
            break;
        }
        case '[':
        {
            if (AdvanceSourceReaderHead(source)) {
                return TK_LSQBRK;
            }
            break;
        }
        case ']':
        {
            if (AdvanceSourceReaderHead(source)) {
                return TK_RSQBRK;
            }
            break;
        }
        case '{':
        {
            if (AdvanceSourceReaderHead(source)) {
                return TK_LCYBRK;
            }
            break;
        }
        case '}':
        {
            if (AdvanceSourceReaderHead(source)) {
                return TK_RCYBRK;
            }
            break;
        }
        case '*':
        {
            if (AdvanceSourceReaderHead(source)) {
                return TK_ASTERISK;
            }
            break;
        }
        case '/':
        {
            if (AdvanceSourceReaderHead(source)) {
                return TK_FSLASH;
            }
            break;
        }
        case '%':
        {
            if (AdvanceSourceReaderHead(source)) {
                return TK_PERCENT;
            }
            break;
        }
        case '+':
        {
            if (AdvanceSourceReaderHead(source)) {
                return TK_PLUS;
            }
            break;
        }
        case '^':
        {
            if (AdvanceSourceReaderHead(source)) {
                return TK_CARET;
            }
            break;
        }
        case '&':
        {
            if (AdvanceSourceReaderHead(source)) {
                return TK_KW_AND;
            }
            break;
        }
        case '|':
        {
            if (AdvanceSourceReaderHead(source)) {
                return TK_KW_OR;
            }
            break;
        }
        case '$':
        {
            if (AdvanceSourceReaderHead(source)) {
                return TK_DOLLAR;
            }
            break;
        }

        case '=':
        {
            if (AdvanceSourceReaderHead(source)) {
                if (ReadSourceReaderHead(source) == '=' && AdvanceSourceReaderHead(source)) {
                    return TK_EQUALS;
                }
                return TK_BIND;
            }
            break;
        }
        case ':': 
        {
            if (AdvanceSourceReaderHead(source)) {
                if (ReadSourceReaderHead(source) == ':' && AdvanceSourceReaderHead(source)) {
                    if (ReadSourceReaderHead(source) == ':' && AdvanceSourceReaderHead(source)) {
                        return TK_TPL_COLON;
                    }
                }
                return TK_COLON;
            }
            break;
        }
        case '!':
        {
            if (AdvanceSourceReaderHead(source)) {
                if (ReadSourceReaderHead(source) == '=' && AdvanceSourceReaderHead(source)) {
                    return TK_NEQUALS;
                }
                return TK_EXCLAIM;
            }
            break;
        }
        case '-': 
        {
            if (AdvanceSourceReaderHead(source)) {
                if (ReadSourceReaderHead(source) == '>' && AdvanceSourceReaderHead(source)) {
                    return TK_ARROW;
                }
                return TK_MINUS;
            }
            break;
        }
        case '<': 
        {
            if (AdvanceSourceReaderHead(source)) {
                if (ReadSourceReaderHead(source) == '=' && AdvanceSourceReaderHead(source)) {
                    return TK_LETHAN;
                }
                return TK_LTHAN;
            }
            break;
        }
        case '>':
        {
            if (AdvanceSourceReaderHead(source)) {
                if (ReadSourceReaderHead(source) == '=' && AdvanceSourceReaderHead(source)) {
                    return TK_GETHAN;
                }
                return TK_GTHAN;
            }
            break;
        }
        default:
        {
            break;
        }
    }
    return TK_NULL;
}
TokenKind lexOneNumber(Source* source, TokenInfo* optInfoP) {
    TokenInfo prefixTokenInfo;
    TokenKind prefixTokenKind = lexOneIntChunk(source, &prefixTokenInfo, 0);
    if (prefixTokenKind == TK_DINT_LIT) {
        if (ReadSourceReaderHead(source) == '.' && AdvanceSourceReaderHead(source)) {
            // float
            TokenInfo suffixTokenInfo;
            lexOneIntChunk(source, &suffixTokenInfo, true);
            
            // converting prefix and suffix ints into a double value:
            if (optInfoP) {
                double dotPrefix = prefixTokenInfo.Int;
                double dotSuffix = suffixTokenInfo.Int;
                while (dotSuffix >= 1.0) {
                    dotSuffix /= 10;
                }
                double value = dotPrefix + dotSuffix;
                if (optInfoP) {
                    optInfoP->Float = value;
                }
            }
            return TK_FLOAT_LIT;
        
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
        optInfoP->Int = value;
    }

    // Returning results:
    return tokenKind;
}
TokenKind lexOneIdOrKeyword(Source* source, TokenInfo* infoP) {
    // The longest supported ID is (MAX_ID_LEN) characters long.
    size_t index;
    char charBuf[MAX_ID_LEN+1];
    for (index = 0; index < MAX_ID_LEN;) {
        // reading the next character:
        char ch = ReadSourceReaderHead(source);
        
        // adding the character to the charBuf:
        if (isIdChar(ch) && AdvanceSourceReaderHead(source)) {
            charBuf[index++] = ch;
        } else {
            break;
        }
    }
    if (isIdChar(ReadSourceReaderHead(source))) {
        // ID too long, so ID char after end of ID, so error.
        PostFeedback(FBK_ERROR, NULL, "ID '%s...' exceeds the maximum supported ID length of (%d) characters.", charBuf, MAX_ID_LEN);
        return TK_NULL;
    }
    charBuf[index] = '\0';

    // Looking up charBuf as a keyword or symbol:
    SymbolID kwID = strings_lookup(symbolsDict, charBuf);
    if (kwID == 0) {
        SymbolID symbolID = Symbol(charBuf);
        assert(symbolID != 0 && "`strings_lookup` produced an ID but no match.");
        if (infoP) {
            infoP->ID_symbolID = symbolID;
        }
        return getIdTextKind(charBuf);
    }
    if (kwID == kwNamespaceSymbolID) { return TK_KW_NAMESPACE; }
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
    if (kwID == kwDiscardSymbolID) { return TK_KW_DISCARD; }
    if (kwID == kwLinkSymbolID) { return TK_KW_LINK; }
    if (kwID == kwFunSymbolID) { return TK_KW_FUN; }
    if (kwID == kwDefSymbolID) { return TK_KW_DEF; }
    if (kwID == kwLetSymbolID) { return TK_KW_LET; }
    if (kwID == kwAndSymbolID) { return TK_KW_AND; }
    if (kwID == kwXOrSymbolID) { return TK_KW_XOR; }
    if (kwID == kwOrSymbolID) { return TK_KW_OR; }
    if (kwID == kwNotSymbolID) { return TK_KW_NOT; }
    if (kwID == kwSetSymbolID) { return TK_KW_SET; }
    if (kwID == kwTypeSymbolID) { return TK_KW_TYPE; }
    if (kwID == kwEnumSymbolID) { return TK_KW_ENUM; }
    if (kwID == kwModSymbolID) { return TK_KW_MOD; }
    if (kwID == kwTTupleSymbolID) { return TK_KW_TTUPLE; }
    if (kwID == kwTArraySymbolID) { return TK_KW_TARRAY; }
    if (kwID == kwFromSymbolID) { return TK_KW_FROM; }
    if (kwID == kwAsSymbolID) { return TK_KW_AS; }
    if (DEBUG) {
        printf("!!- Keyword not implemented: '%s' (id=%d)\n", strings_lookup_id(symbolsDict, kwID), kwID);
    } else {
        assert(0 && "Unimplemented keyword");
    }
    return TK_NULL;
}
static TokenKind lexOneString(Source* source, TokenInfo* infoP, Loc firstLoc) {
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
            } else if (ReadSourceReaderHead(source) == '0') {
                sb_push(contentStretchyBuffer, 0);
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
        Utf32String utf32string = NewUtf32String(contentStretchyBuffer, sb_count(contentStretchyBuffer));
        Utf8String utf8string = ConvertUtf32StringToUtf8String(utf32string);
        infoP->String_utf8string = utf8string;
        return tokenKind;
    } else {
        FeedbackNote firstNote = {"here...", firstLoc, NULL};
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

int getIdTextKind(char const* idText) {
    if (*idText == '\0') {
        return TK_HOLE;
    } else if (isupper(*idText)) {
        return TK_TID;
    } else if (islower(*idText)) {
        return TK_VID;
    } else {
        return getIdTextKind(idText+1);
    }
}

TokenKind LexOneToken(Source* source, TokenInfo* infoP, Span* span) {
    TokenKind tk = lexOneToken(source, infoP, span);
    // char buffer[512];
    // TokenAsText(tk, infoP, buffer, 512);
    // printf("%s\n", buffer);
    return tk;
}

void DebugLexer(Source* source) {
    TokenInfo info;
    Span span;
    for (;;) {
        TokenKind kind = LexOneToken(source, &info, &span);
        if (kind == TK_NULL) {
            printf("Terminated with TK_NULL\n");
            break;
        }
        if (kind == TK_EOS) {
            printf("Terminated with TK_EOS\n");
            break;
        }
        DebugPrintToken("DBGLEX:", kind, &info, &span);
    }
    // char buffer[512];
    // TokenAsText(tk, infoP, buffer, 512);
    // printf("%s\n", buffer);
}

#define MAX_INFO_LEN (MAX_ID_LEN+1)

int TokenToText(TokenKind tk, TokenInfo* ti, char* buf, int bufLength) {
    char const* name;
    char info[MAX_INFO_LEN] = {'\0'};
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
        case TK_CARET:
        {
            name = "^";
            break;
        }
        case TK_EXCLAIM:
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
        case TK_KW_NAMESPACE:
        {
            name = "namespace";
            break;
        }
        case TK_KW_MOD:
        {
            name = "mod";
            break;
        }
        case TK_KW_DEF:
        {
            name = "def";
            break;
        }
        case TK_KW_LINK:
        {
            name = "link";
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
        case TK_KW_AND:
        {
            name = "and";
            break;
        }
        case TK_KW_XOR:
        {
            name = "xor";
            break;
        }
        case TK_KW_OR:
        {
            name = "or";
            break;
        }
        case TK_KW_NOT:
        {
            name = "not";
            break;
        }
        case TK_KW_LET:
        {
            name = "let";
            break;
        }
        case TK_KW_SET:
        {
            name = "set";
            break;
        }
        case TK_KW_FROM:
        {
            name = "from";
            break;
        }
        case TK_KW_AS:
        {
            name = "as";
            break;
        }
        case TK_KW_TYPE:
        {
            name = "type";
            break;
        }
        case TK_KW_ENUM:
        {
            name = "enum";
            break;
        }
        case TK_KW_DISCARD:
        {
            name = "discard";
            break;
        }
        case TK_DINT_LIT:
        {
            name = "<d-int>";
            snprintf(info, MAX_INFO_LEN, "%zd", ti->Int);
            break;
        }
        case TK_XINT_LIT:
        {
            name = "<x-int>";
            snprintf(info, MAX_INFO_LEN, "%zd", ti->Int);
            break;
        }
        case TK_FLOAT_LIT:
        {
            name = "<float>";
            snprintf(info, MAX_INFO_LEN, "%Lf", ti->Float);
            break;
        }
        case TK_DQSTRING_LIT:
        {
            name = "<text>";
            info[0] = '"';
            int index;
            for (index = 0; ti->String_utf8string.buf[index]; index++) {
                // todo: handle escape sequences correctly
                info[1+index] = ti->String_utf8string.buf[index];
            }
            info[index+1] = '"';
            break;
        }
        case TK_SQSTRING_LIT:
        {
            name = "<text>";
            info[0] = '\'';
            int index;
            for (index = 0; ti->String_utf8string.buf[index]; index++) {
                // todo: handle escape sequences correctly
                info[1+index] = ti->String_utf8string.buf[index];
            }
            info[index+1] = '\'';
            break;
        }
        case TK_VID:
        {
            name = "<vid>";
            snprintf(info, MAX_INFO_LEN, "%s", GetSymbolText(ti->ID_symbolID));
            break;
        }
        case TK_TID:
        {
            name = "<tid>";
            snprintf(info, MAX_INFO_LEN, "%s", GetSymbolText(ti->ID_symbolID));
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
        case TK_EOS:
        {
            name = "<EOF>";
            break;
        }
        default:
        {
            name = "<?>";
            break;
        }
    }
    if (info[0]) {
        return snprintf(buf, bufLength-1, "%s (%s)", info, name);
    } else {
        return snprintf(buf, bufLength-1, "%s", name);
    }
}

void DebugPrintToken(char const* prefix, TokenKind tk, TokenInfo* ti, Span* span) {
    char lineBuffer[64]; 
    TokenToText(tk,ti,lineBuffer,64);
    printf("%s %s [%d:%d-%d:%d]\n", prefix, lineBuffer, span->first_line,span->first_column, span->last_line,span->last_column);
}
