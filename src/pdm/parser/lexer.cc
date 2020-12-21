#include "lexer.hh"

#include <vector>
#include <string>
#include <sstream>

#include <cctype>
#include <cassert>
#include <cstring>

extern "C" {
    #include <intern/strings.h>
    #include <stb/stretchy_buffer.h>
}

#include "pdm/source/pos.hh"
#include "pdm/source/loc.hh"

#include "pdm/feedback/feedback.hh"
#include "pdm/feedback/letter.hh"
#include "pdm/feedback/severity.hh"
#include "pdm/feedback/note.hh"

#include "pdm/core/integer.hh"

#include "parser.tab.hh"

// #include "config.h"
// #include "source.h"
// #include "useful.h"

// 
// Helpers (1):
//
namespace pdm::parser::aux {

    static int const MAX_ID_LEN = 256;
    static int const MAX_INFO_LEN = MAX_ID_LEN + 1;

    static TokenKind LexOneToken(Reader* reader, TokenInfo* out_info, source::Loc* out_loc);
    
    struct Keywords {
        intern::String using_intstr;
        intern::String import_intstr;
        intern::String export_intstr;
        intern::String if_intstr;
        intern::String then_intstr;
        intern::String else_intstr;
        intern::String operator_intstr;
        intern::String match_intstr;
        intern::String with_intstr;
        intern::String return_intstr;
        intern::String discard_intstr;
        intern::String link_intstr;
        intern::String fn_intstr;
        intern::String let_intstr;
        intern::String and_intstr;
        intern::String x_or_intstr;
        intern::String or_intstr;
        intern::String not_intstr;
        intern::String set_intstr;
        intern::String type_intstr;
        intern::String enum_intstr;
        intern::String mod_intstr;
        intern::String from_intstr;
        intern::String as_intstr;

        Keywords() {
            intern::String::ensure_init();

            using_intstr = "using";
            import_intstr = "import";
            export_intstr = "export";
            if_intstr = "if";
            then_intstr = "then";
            else_intstr = "else";
            operator_intstr = "operator";
            match_intstr = "match";
            with_intstr = "with";
            return_intstr = "return";
            discard_intstr = "discard";
            link_intstr = "link";
            fn_intstr = "fn";
            let_intstr = "let";
            and_intstr = "and";
            x_or_intstr = "xor";
            or_intstr = "or";
            not_intstr = "not";
            set_intstr = "set";
            type_intstr = "type";
            enum_intstr = "enum";
            mod_intstr = "mod";
            from_intstr = "from";
            as_intstr = "as";
        }
    };

    static Keywords keywords;

}

//
// Definitions:
//

namespace pdm::parser {

    bool Lexer::setup(source::Source* source) {
        return m_reader.setup(source);
    }

    TokenKind Lexer::lex_one_token(TokenInfo* out_info, source::Loc* out_loc) {
        return aux::LexOneToken(&m_reader, out_info, out_loc);
    }

}


//
// Helpers (2)
//

namespace pdm::parser::aux {

    static TokenKind lexOneToken(Reader* source, TokenInfo* info, source::Loc* out_loc);
    static TokenKind lexOneSimpleToken(Reader* source);
    static TokenKind helpLexOneSimpleToken(Reader* source);
    static TokenKind lexOneNumber(Reader* source, TokenInfo* info);
    static TokenKind lexOneIntChunk(Reader* source, TokenInfo* info, int noPrefix);
    static TokenKind lexOneIdOrKeyword(Reader* source, TokenInfo* info, source::Pos& firstPos);
    static TokenKind lexOneString(Reader* source, TokenInfo* info, source::Pos& firstPos);
    inline static void skipWhitespace(Reader* source);

    inline static bool isFirstIdChar(char ch);
    inline static bool isIdChar(char ch);

    static int getIdTextKind(char const* idText);

    // In general, we assume the source head is over the first character of the token to read.
    // - This 'hovering reader' approach => LL(1) lexer.
    // - Read, Advance, Read, Advance...
    // - if (Advance...) is an effective way to check for and handle EOFs.

    TokenKind lexOneToken(Reader* source, TokenInfo* info, source::Loc* out_loc) {
        // At SOF, reading the first character.
        if (source->at_sof()) {
            source->advance_head();
        }
        
        // Ignoring whitespace & comments:
        while (isspace(source->read_head()) || source->read_head() == '#') {
            skipWhitespace(source);
            if (source->read_head() == '#') {
                do {
                    source->advance_head();
                } while (source->read_head() != '\n' && !source->at_eof());
            }
            skipWhitespace(source);
        }

        // If at EOF, returning yy::parser::token::token_kind_type::TK_EOS (not yy::parser::token::token_kind_type::TK_NULL!) to indicate the end of this token stream.
        if (source->at_eof()) {
            return yy::parser::token::token_kind_type::TK_EOS;
        }

        //
        // populating firstLoc before any real tokens:
        //

        // Loc firstLoc; 
        source::Pos firstPos = *source->opt_head_pos();
        assert(source->opt_head_pos() != nullptr);

        //
        // Simple tokens:
        //

        TokenKind outKind = lexOneSimpleToken(source);
        if (outKind == yy::parser::token::token_kind_type::TK_NULL) {
            // must be a more complex token...

            int firstChar = source->read_head();
            
            // numbers:
            if (isdigit(firstChar)) {
                outKind = lexOneNumber(source, info);
            }

            // strings:    
            else if (firstChar == '"' || firstChar == '\'') {
                outKind = lexOneString(source, info, firstPos);
            }

            // IDs and keywords:
            else if (isFirstIdChar(firstChar)) {
                outKind = lexOneIdOrKeyword(source, info, firstPos);
            }

            // Error: unknown token kind.
            // Offer feedback with location, RETURN EARLY with yy::parser::token::token_kind_type::TK_NULL
            else {
                std::vector<feedback::Note*> notes; {
                    notes.reserve(1);
                    notes.push_back(new feedback::SourceLocNote("here...", source::Loc(firstPos)));
                }
                char offendingChar = firstChar;
                std::stringstream headline_ss;
                headline_ss 
                    << "Before '" << offendingChar << "' " 
                    << "(" << (int)offendingChar << ") "
                    << "expected a valid token.";
                feedback::Letter* letter = new feedback::Letter(
                    feedback::Severity::FatalError,
                    std::move(headline_ss.str()),
                    std::move(std::string("")),
                    std::move(notes)
                );
                feedback::post(letter);
                return yy::parser::token::token_kind_type::TK_NULL;
            }
        }

        // populating lastLoc, creating span, returning VALID token kind found so far:
        source::Pos lastPos = *source->opt_head_pos();
        *out_loc = source::Loc{firstPos, lastPos};
        return outKind;
    }

    TokenKind lexOneSimpleToken(Reader* source) {
        TokenKind tk = helpLexOneSimpleToken(source);
        // if (tk != yy::parser::token::token_kind_type::TK_NULL) {
        //     source->advance_head();
        // }
        return tk;
    }
    TokenKind helpLexOneSimpleToken(Reader* source) {
        // lexes all of a simple token
        // - return 'NULL' and do not advance characters at all to opt-out, leaving reader head as is.
        switch (source->read_head()) {
            case '.':
            {
                if (source->advance_head()) {
                    return yy::parser::token::token_kind_type::TK_DOT;
                }
                break;
            }
            case ',':
            {
                if (source->advance_head()) {
                    return yy::parser::token::token_kind_type::TK_COMMA;
                }
                break;
            }
            case ';':
            {
                if (source->advance_head()) {
                    return yy::parser::token::token_kind_type::TK_SEMICOLON;
                }
                break;
            }
            case '(':
            {
                if (source->advance_head()) {
                    return yy::parser::token::token_kind_type::TK_LPAREN;
                }
                break;
            }
            case ')':
            {
                if (source->advance_head()) {
                    return yy::parser::token::token_kind_type::TK_RPAREN;
                }
                break;
            }
            case '[':
            {
                if (source->advance_head()) {
                    return yy::parser::token::token_kind_type::TK_LSQBRK;
                }
                break;
            }
            case ']':
            {
                if (source->advance_head()) {
                    return yy::parser::token::token_kind_type::TK_RSQBRK;
                }
                break;
            }
            case '{':
            {
                if (source->advance_head()) {
                    return yy::parser::token::token_kind_type::TK_LCYBRK;
                }
                break;
            }
            case '}':
            {
                if (source->advance_head()) {
                    return yy::parser::token::token_kind_type::TK_RCYBRK;
                }
                break;
            }
            case '*':
            {
                if (source->advance_head()) {
                    return yy::parser::token::token_kind_type::TK_ASTERISK;
                }
                break;
            }
            case '/':
            {
                if (source->advance_head()) {
                    return yy::parser::token::token_kind_type::TK_FSLASH;
                }
                break;
            }
            case '%':
            {
                if (source->advance_head()) {
                    return yy::parser::token::token_kind_type::TK_PERCENT;
                }
                break;
            }
            case '+':
            {
                if (source->advance_head()) {
                    return yy::parser::token::token_kind_type::TK_PLUS;
                }
                break;
            }
            case '^':
            {
                if (source->advance_head()) {
                    return yy::parser::token::token_kind_type::TK_CARET;
                }
                break;
            }
            case '&':
            {
                if (source->advance_head()) {
                    return yy::parser::token::token_kind_type::TK_KW_AND;
                }
                break;
            }
            case '|':
            {
                if (source->advance_head()) {
                    return yy::parser::token::token_kind_type::TK_KW_OR;
                }
                break;
            }
            
            case '=':
            {
                if (source->advance_head()) {
                    if (source->read_head() == '=' && source->advance_head()) {
                        return yy::parser::token::token_kind_type::TK_EQUALS;
                    }
                    return yy::parser::token::token_kind_type::TK_BIND;
                }
                break;
            }
            case ':': 
            {
                if (source->advance_head()) {
                    if (source->read_head() == ':' && source->advance_head()) {
                        return yy::parser::token::token_kind_type::TK_DBL_COLON;
                    }
                    return yy::parser::token::token_kind_type::TK_COLON;
                }
                break;
            }
            case '!':
            {
                if (source->advance_head()) {
                    if (source->read_head() == '=' && source->advance_head()) {
                        return yy::parser::token::token_kind_type::TK_NEQUALS;
                    }
                    return yy::parser::token::token_kind_type::TK_EXCLAIM;
                }
                break;
            }
            case '-': 
            {
                if (source->advance_head()) {
                    if (source->read_head() == '>' && source->advance_head()) {
                        return yy::parser::token::token_kind_type::TK_ARROW;
                    }
                    return yy::parser::token::token_kind_type::TK_MINUS;
                }
                break;
            }
            case '<': 
            {
                if (source->advance_head()) {
                    if (source->read_head() == '=' && source->advance_head()) {
                        return yy::parser::token::token_kind_type::TK_LETHAN;
                    }
                    return yy::parser::token::token_kind_type::TK_LTHAN;
                }
                break;
            }
            case '>':
            {
                if (source->advance_head()) {
                    if (source->read_head() == '=' && source->advance_head()) {
                        return yy::parser::token::token_kind_type::TK_GETHAN;
                    }
                    return yy::parser::token::token_kind_type::TK_GTHAN;
                }
                break;
            }
            default:
            {
                break;
            }
        }
        return yy::parser::token::token_kind_type::TK_NULL;
    }
    TokenKind lexOneNumber(Reader* source, TokenInfo* optInfoP) {
        TokenInfo prefixTokenInfo;
        TokenKind prefixTokenKind = lexOneIntChunk(source, &prefixTokenInfo, 0);
        if (prefixTokenKind == yy::parser::token::token_kind_type::TK_DINT_LIT) {
            if (source->read_head() == '.' && source->advance_head()) {
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
                return yy::parser::token::token_kind_type::TK_FLOAT_LIT;
            
            }
        }
        if (optInfoP) {
            *optInfoP = prefixTokenInfo;
        }
        return prefixTokenKind;
    }
    TokenKind lexOneIntChunk(Reader* source, TokenInfo* optInfoP, int noPrefix) {
        // Checking for a hex prefix:
        TokenKind tokenKind = yy::parser::token::token_kind_type::TK_DINT_LIT;
        if (!noPrefix) {
            if (source->read_head() == '0') {
                if (source->advance_head()) {
                    if (source->read_head() == 'x') {
                        // 0x hex prefix detected.
                        source->advance_head();
                        tokenKind = yy::parser::token::token_kind_type::TK_XINT_LIT;
                    }
                }
            }
        }
        // Repeatedly reading integer characters:
        size_t value = 0;
        do {
            char intChar = source->read_head();
            if (intChar == '_') {
                continue;
            } else if (tokenKind == yy::parser::token::token_kind_type::TK_DINT_LIT) {
                if (isdigit(intChar)) {
                    value = (10*value) + (intChar - '0');
                } else {
                    break;
                }
            } else if (tokenKind == yy::parser::token::token_kind_type::TK_XINT_LIT) {
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
        } while (source->advance_head());

        // Writing results to infoP:
        if (optInfoP) {
            optInfoP->Int = value;
        }

        // Returning results:
        return tokenKind;
    }
    TokenKind lexOneIdOrKeyword(Reader* source, TokenInfo* infoP, source::Pos const& firstPos) {
        // The longest supported ID is (MAX_ID_LEN) characters long.
        size_t index;
        char charBuf[MAX_ID_LEN+1];
        for (index = 0; index < MAX_ID_LEN; index++) {
            // reading the next character:
            char ch = source->read_head();
            
            // adding the character to the charBuf:
            if (isIdChar(ch) && source->advance_head()) {
                charBuf[index] = ch;
            } else {
                break;
            }
        }
        int length = index;
        charBuf[length] = '\0';
        if (isIdChar(source->read_head()) && length == MAX_ID_LEN) {
            // ID too long, so ID char after end of ID, so error.
            std::vector<feedback::Note*> notes(1); {
                std::string desc0 = "Starting here...";
                notes[0] = new feedback::SourceLocNote(
                    std::move(desc0), 
                    source::Loc(firstPos)
                );
            }
            feedback::post(new feedback::Letter(
                feedback::Severity::FatalError,
                std::move((std::stringstream() 
                    << "ID '" << charBuf << "...' exceeds "
                    << "the maximum supported ID length of "
                    << "(" << MAX_ID_LEN << ") characters.").str()),
                std::move(std::string("Please use a shorter identifier fragment instead.")),
                std::move(notes)
            ));
            return yy::parser::token::token_kind_type::TK_NULL;
        }
        charBuf[index] = '\0';

        // Looking up charBuf as a keyword or symbol:
        intern::String intstr = charBuf;
        if (intstr == keywords.using_intstr) { return yy::parser::token::token_kind_type::TK_KW_USING; }
        if (intstr == keywords.import_intstr) { return yy::parser::token::token_kind_type::TK_KW_IMPORT; }
        if (intstr == keywords.if_intstr) { return yy::parser::token::token_kind_type::TK_KW_IF; }
        if (intstr == keywords.then_intstr) { return yy::parser::token::token_kind_type::TK_KW_THEN; }
        if (intstr == keywords.else_intstr) { return yy::parser::token::token_kind_type::TK_KW_ELSE; }
        if (intstr == keywords.match_intstr) { return yy::parser::token::token_kind_type::TK_KW_MATCH; }
        if (intstr == keywords.with_intstr) { return yy::parser::token::token_kind_type::TK_KW_WITH; }
        if (intstr == keywords.link_intstr) { return yy::parser::token::token_kind_type::TK_KW_LINK; }
        if (intstr == keywords.fn_intstr) { return yy::parser::token::token_kind_type::TK_KW_FN; }
        if (intstr == keywords.let_intstr) { return yy::parser::token::token_kind_type::TK_KW_LET; }
        if (intstr == keywords.and_intstr) { return yy::parser::token::token_kind_type::TK_KW_AND; }
        if (intstr == keywords.x_or_intstr) { return yy::parser::token::token_kind_type::TK_KW_XOR; }
        if (intstr == keywords.or_intstr) { return yy::parser::token::token_kind_type::TK_KW_OR; }
        if (intstr == keywords.not_intstr) { return yy::parser::token::token_kind_type::TK_KW_NOT; }
        if (intstr == keywords.set_intstr) { return yy::parser::token::token_kind_type::TK_KW_SET; }
        if (intstr == keywords.type_intstr) { return yy::parser::token::token_kind_type::TK_KW_TYPE; }
        if (intstr == keywords.enum_intstr) { return yy::parser::token::token_kind_type::TK_KW_ENUM; }
        if (intstr == keywords.mod_intstr) { return yy::parser::token::token_kind_type::TK_KW_MOD; }
        if (intstr == keywords.from_intstr) { return yy::parser::token::token_kind_type::TK_KW_FROM; }
        if (intstr == keywords.as_intstr) { return yy::parser::token::token_kind_type::TK_KW_AS; }
        else {
            infoP->ID_intstr = intstr;
            return getIdTextKind(charBuf);
        }
    }
    static TokenKind lexOneString(Reader* source, TokenInfo* infoP, source::Pos const& firstPos) {
        // reading the first character, i.e., the quote character:
        int quoteChar = source->read_head();
        TokenKind tokenKind;
        if (quoteChar == '"') {
            tokenKind = yy::parser::token::token_kind_type::TK_DQSTRING_LIT;
        } else if (quoteChar == '\'') { 
            tokenKind = yy::parser::token::token_kind_type::TK_SQSTRING_LIT;
        } else if (DEBUG) {
            assert(0 && "Invalid quote character.");
        }
        source->advance_head();

        // reading the string content:
        utf8::StringBuilder sb;
        while (source->read_head() != quoteChar) {
            if (source->read_head() == '\\') {
                source::Pos escapeSequencePos = *source->opt_head_pos();
                source->advance_head();

                int valid = 1;
                if (source->read_head() == 'n') {
                    sb.append_u32('\n');
                } else if (source->read_head() == 'r') {
                    sb.append_u32('\r');
                } else if (source->read_head() == 'a') {
                    sb.append_u32('\a');
                } else if (source->read_head() == 't') {
                    sb.append_u32('\t');
                } else if (source->read_head() == '0') {
                    sb.append_u32(0);
                } else if (source->read_head() == '\\') {
                    sb.append_u32('\\');
                } else if (source->read_head() == quoteChar) {
                    sb.append_u32(quoteChar);
                } else {
                    valid = 0;
                }
                source->advance_head();

                if (!valid) {
                    // invalid escape sequence!
                    
                    char invalidSecondChar = source->read_head();
                    std::string desc = "Valid escape sequences: \\n, \\r, \\a, \\t, \\0, \\\\, \\\", or \\'";
                    std::vector<feedback::Note*> notes(1); {
                        notes[0] = new feedback::SourceLocNote(
                            std::move(std::string("here...")),
                            source::Loc(escapeSequencePos)
                        );
                    }
                    
                    std::string headline = (invalidSecondChar == EOF) ? 
                        ("Invalid escape sequence at EOF") :
                        (std::stringstream{} << "Invalid escape sequence: \\" << invalidSecondChar).str();
                    
                    feedback::post(new feedback::Letter(
                        feedback::Severity::FatalError,
                        std::move(headline),
                        std::move(desc),
                        std::move(notes)
                    ));

                    break;
                }

            } else {
                // todo: scan multi-byte sequences
                int head_char_i = source->read_head();
                assert(0 <= head_char_i && head_char_i <= 127);
                u32 head_char = static_cast<u32>(head_char_i);
                sb.append_u32(source->read_head());
                source->advance_head();
            }
        }

        // reading the closing quote character:
        if (source->read_head() != quoteChar) {
            std::vector<feedback::Note*> notes(1); {
                notes[0] = new feedback::SourceLocNote("string literal here...", source::Loc(firstPos));
            }
            feedback::post(new feedback::Letter(
                feedback::Severity::FatalError,
                std::move("Invalid string literal"),
                std::move("Before EOF, expected quotechar: <" + std::string(1,quoteChar) + ">"),
                std::move(notes)
            ));
            return yy::parser::token::token_kind_type::TK_NULL;
        }
        source->advance_head();
        infoP->String_utf8string = new utf8::String(sb.strdup());
        return tokenKind;
    }

    inline void skipWhitespace(Reader* source) {
        int stop = 0;
        do {
            switch (source->read_head()) {
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
        } while (!stop && source->advance_head());
    }

    inline bool isFirstIdChar(char ch) {
        return isalpha(ch) || ch == '_';
    }
    inline bool isIdChar(char ch) {
        return isalnum(ch) || ch == '_';
    }

    int getIdTextKind(char const* idText) {
        if (*idText == '\0') {
            return yy::parser::token::token_kind_type::TK_HOLE;
        } else if (isupper(*idText)) {
            return yy::parser::token::token_kind_type::TK_TID;
        } else if (islower(*idText)) {
            return yy::parser::token::token_kind_type::TK_VID;
        } else {
            return getIdTextKind(idText+1);
        }
    }

    TokenKind LexOneToken(Reader* source, TokenInfo* infoP, source::Loc* span) {
        TokenKind tk = lexOneToken(source, infoP, span);
        // char buffer[512];
        // TokenAsText(tk, infoP, buffer, 512);
        // printf("%s\n", buffer);
        return tk;
    }
}


//
// Helpers (3)
//

namespace pdm::parser::aux {

    void DebugLexer(Reader* source);
    void DebugPrintToken(char const* prefix, TokenKind tk, TokenInfo* ti, source::Loc* loc);
    int TokenToText(TokenKind tk, TokenInfo* ti, char* buf, int bufLength);

    void DebugLexer(Reader* source) {
        TokenInfo tok_info;
        source::Loc tok_loc = source::Loc::none;
        for (;;) {
            TokenKind kind = aux::LexOneToken(source, &tok_info, &tok_loc);
            if (kind == yy::parser::token::token_kind_type::TK_NULL) {
                printf("Terminated with TK_NULL\n");
                break;
            }
            if (kind == yy::parser::token::token_kind_type::TK_EOS) {
                printf("Terminated with TK_EOS\n");
                break;
            }
            DebugPrintToken("DBGLEX:", kind, &tok_info, &tok_loc);
        }
        // char buffer[512];
        // TokenAsText(tk, infoP, buffer, 512);
        // printf("%s\n", buffer);
    }

    int TokenToText(TokenKind tk, TokenInfo* ti, char* buf, int bufLength) {
        char const* name;
        char info[MAX_INFO_LEN] = {'\0'};
        switch (tk)
        {
            case yy::parser::token::token_kind_type::TK_DOT:
            {
                name = ".";
                break;
            }
            case yy::parser::token::token_kind_type::TK_COMMA:
            {
                name = ",";
                break;
            }
            case yy::parser::token::token_kind_type::TK_COLON:
            {
                name = ":";
                break;
            }
            case yy::parser::token::token_kind_type::TK_LPAREN:
            {
                name = "(";
                break;
            }
            case yy::parser::token::token_kind_type::TK_RPAREN:
            {
                name = ")";
                break;
            }
            case yy::parser::token::token_kind_type::TK_LSQBRK:
            {
                name = "[";
                break;
            }
            case yy::parser::token::token_kind_type::TK_RSQBRK:
            {
                name = "]";
                break;
            }
            case yy::parser::token::token_kind_type::TK_LCYBRK:
            {
                name = "{";
                break;
            }
            case yy::parser::token::token_kind_type::TK_RCYBRK:
            {
                name = "}";
                break;
            }
            case yy::parser::token::token_kind_type::TK_SEMICOLON:
            {
                name = ";";
                break;
            }
            case yy::parser::token::token_kind_type::TK_ASTERISK:
            {
                name = "*";
                break;
            }
            case yy::parser::token::token_kind_type::TK_FSLASH:
            {
                name = "/";
                break;
            }
            case yy::parser::token::token_kind_type::TK_PERCENT:
            {
                name = "%";
                break;
            }
            case yy::parser::token::token_kind_type::TK_PLUS:
            {
                name = "+";
                break;
            }
            case yy::parser::token::token_kind_type::TK_MINUS:
            {
                name = "-";
                break;
            }
            case yy::parser::token::token_kind_type::TK_CARET:
            {
                name = "^";
                break;
            }
            case yy::parser::token::token_kind_type::TK_EXCLAIM:
            {
                name = "!";
                break;
            }
            case yy::parser::token::token_kind_type::TK_BIND:
            {
                name = "=";
                break;
            }
            case yy::parser::token::token_kind_type::TK_EQUALS:
            {
                name = "==";
                break;
            }
            case yy::parser::token::token_kind_type::TK_NEQUALS:
            {
                name = "!=";
                break;
            }
            case yy::parser::token::token_kind_type::TK_KW_USING:
            {
                name = "using";
                break;
            }
            case yy::parser::token::token_kind_type::TK_KW_MOD:
            {
                name = "mod";
                break;
            }
            case yy::parser::token::token_kind_type::TK_KW_FN:
            {
                name = "fn";
                break;
            }
            case yy::parser::token::token_kind_type::TK_KW_LINK:
            {
                name = "link";
                break;
            }
            case yy::parser::token::token_kind_type::TK_KW_IMPORT:
            {
                name = "import";
                break;
            }
            case yy::parser::token::token_kind_type::TK_KW_IF:
            {
                name = "if";
                break;
            }
            case yy::parser::token::token_kind_type::TK_KW_THEN:
            {
                name = "then";
                break;
            }
            case yy::parser::token::token_kind_type::TK_KW_ELSE:
            {
                name = "else";
                break;
            }
            case yy::parser::token::token_kind_type::TK_KW_MATCH:
            {
                name = "match";
                break;
            }
            case yy::parser::token::token_kind_type::TK_KW_AND:
            {
                name = "and";
                break;
            }
            case yy::parser::token::token_kind_type::TK_KW_XOR:
            {
                name = "xor";
                break;
            }
            case yy::parser::token::token_kind_type::TK_KW_OR:
            {
                name = "or";
                break;
            }
            case yy::parser::token::token_kind_type::TK_KW_NOT:
            {
                name = "not";
                break;
            }
            case yy::parser::token::token_kind_type::TK_KW_LET:
            {
                name = "let";
                break;
            }
            case yy::parser::token::token_kind_type::TK_KW_SET:
            {
                name = "set";
                break;
            }
            case yy::parser::token::token_kind_type::TK_KW_FROM:
            {
                name = "from";
                break;
            }
            case yy::parser::token::token_kind_type::TK_KW_AS:
            {
                name = "as";
                break;
            }
            case yy::parser::token::token_kind_type::TK_KW_TYPE:
            {
                name = "type";
                break;
            }
            case yy::parser::token::token_kind_type::TK_KW_ENUM:
            {
                name = "enum";
                break;
            }
            case yy::parser::token::token_kind_type::TK_DINT_LIT:
            {
                name = "<d-int>";
                snprintf(info, MAX_INFO_LEN, "%zd", ti->Int);
                break;
            }
            case yy::parser::token::token_kind_type::TK_XINT_LIT:
            {
                name = "<x-int>";
                snprintf(info, MAX_INFO_LEN, "%zd", ti->Int);
                break;
            }
            case yy::parser::token::token_kind_type::TK_FLOAT_LIT:
            {
                name = "<float>";
                snprintf(info, MAX_INFO_LEN, "%Lf", ti->Float);
                break;
            }
            case yy::parser::token::token_kind_type::TK_DQSTRING_LIT:
            {
                name = "<text>";
                info[0] = '"';
                int index;
                for (index = 0; ti->String_utf8string->const_data()[index]; index++) {
                    // todo: handle escape sequences correctly
                    info[1+index] = ti->String_utf8string->const_data()[index];
                }
                info[index+1] = '"';
                break;
            }
            case yy::parser::token::token_kind_type::TK_SQSTRING_LIT:
            {
                name = "<text>";
                info[0] = '\'';
                int index;
                for (index = 0; ti->String_utf8string->const_data()[index]; index++) {
                    // todo: handle escape sequences correctly
                    info[1+index] = ti->String_utf8string->const_data()[index];
                }
                info[index+1] = '\'';
                break;
            }
            case yy::parser::token::token_kind_type::TK_VID:
            {
                name = "<vid>";
                snprintf(info, MAX_INFO_LEN, "%s", ti->ID_intstr.content());
                break;
            }
            case yy::parser::token::token_kind_type::TK_TID:
            {
                name = "<tid>";
                snprintf(info, MAX_INFO_LEN, "%s", ti->ID_intstr.content());
                break;
            }
            case yy::parser::token::token_kind_type::TK_ARROW:
            {
                name = "->";
                break;
            }
            case yy::parser::token::token_kind_type::TK_NULL:
            {
                name = "<NULL>";
                break;
            }
            case yy::parser::token::token_kind_type::TK_EOS:
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

    void DebugPrintToken(char const* prefix, TokenKind tk, TokenInfo* ti, source::Loc* loc) {
        char lineBuffer[64]; 
        TokenToText(tk,ti,lineBuffer,64);
        printf(
            "%s %s [%d:%d-%d:%d]\n",
            prefix, lineBuffer, 
            loc->first_line(),loc->first_column(), 
            loc->last_line(),loc->last_column()
        );
    }

}
