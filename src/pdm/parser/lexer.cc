#include "lexer.hh"

#include <vector>
#include <string>
#include <sstream>
#include <iomanip>

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

    static int TokenToText(TokenKind tk, TokenInfo* ti, char* buf, int bufLength);

    struct Keywords {
        intern::String using_int_str;
        intern::String cls_int_str;
        intern::String import_int_str;
        intern::String if_int_str;
        intern::String then_int_str;
        intern::String else_int_str;
        intern::String match_int_str;
        intern::String with_int_str;
        intern::String discard_int_str;
        intern::String fn_int_str;
        intern::String val_int_str;
        intern::String var_int_str;
        intern::String const_int_str;
        intern::String and_int_str;
        intern::String xor_int_str;
        intern::String or_int_str;
        intern::String not_int_str;
        intern::String set_int_str;
        intern::String mod_int_str;
        intern::String from_int_str;
        intern::String out_int_str;
        intern::String inout_int_str;
        intern::String enum_int_str;

        Keywords()
        :   using_int_str{},
            cls_int_str{},
            import_int_str{},
            if_int_str{},
            then_int_str{},
            else_int_str{},
            match_int_str{},
            with_int_str{},
            discard_int_str{},
            fn_int_str{},
            val_int_str{},
            var_int_str{},
            const_int_str{},
            and_int_str{},
            xor_int_str{},
            or_int_str{},
            not_int_str{},
            set_int_str{},
            mod_int_str{},
            from_int_str{},
            out_int_str{},
            inout_int_str{},
            enum_int_str{}
        {
            intern::String::ensure_init();

            using_int_str = "using";
            cls_int_str = "cls";
            import_int_str = "import";
            if_int_str = "if";
            then_int_str = "then";
            else_int_str = "else";
            match_int_str = "match";
            with_int_str = "with";
            discard_int_str = "discard";
            fn_int_str = "fn";
            val_int_str = "val";
            var_int_str = "var";
            const_int_str = "const";
            and_int_str = "and";
            xor_int_str = "xor";
            or_int_str = "or";
            not_int_str = "not";
            set_int_str = "set";
            mod_int_str = "mod";
            from_int_str = "from";
            out_int_str = "out";
            inout_int_str = "inout";
            enum_int_str = "enum";
        }
    };

    static Keywords keywords{};

}

//
// Helpers (2)
//

namespace pdm::parser::aux {

    static TokenKind lexOneToken(Reader* source, TokenInfo* info, source::Loc* out_loc);
    static TokenKind lexOneSimpleToken(Reader* source);
    static TokenKind helpLexOneSimpleToken(Reader* source);
    static TokenKind lexOneNumber(Reader* source, TokenInfo* optInfoP);
    static TokenKind lexOneIntChunk(Reader* source, TokenInfo* info, int noPrefix);
    static TokenKind lexOneIdOrKeyword(Reader* source, TokenInfo* info, source::Pos const& firstPos);
    static TokenKind lexOneString(Reader* source, TokenInfo* infoP, source::Pos const& firstPos);
    inline static void skipWhitespace(Reader* source);

    inline static bool isFirstIdChar(char ch);
    inline static bool isIdChar(char ch);

    static int getIdTextKind(char const* idText);

    // In general, we assume the source head is over the first character of the token to read.
    // - This 'hovering reader' approach => LL(1) lexer.
    // - Read, Advance, Read, Advance...
    // - if (Advance...) is an effective way to check for and handle EOFs.

    TokenKind lexOneToken(Reader* reader, TokenInfo* info, source::Loc* out_loc) {
        // At SOF, reading the first character.
        if (reader->at_sof()) {
            reader->advance_head();
        }
        
        // Ignoring whitespace & comments:
        while (isspace(reader->read_head()) || reader->read_head() == '#') {
            skipWhitespace(reader);
            if (reader->read_head() == '#') {
                do {
                    reader->advance_head();
                } while (reader->read_head() != '\n' && !reader->at_eof());
            }
            skipWhitespace(reader);
        }

        // If at EOF, returning Tk::EOS (not Tk::NONE!) to indicate the end of this token stream.
        if (reader->at_eof()) {
            return Tk::EOS;
        }

        //
        // populating firstLoc before any real tokens:
        //

        // Loc firstLoc; 
        source::Pos firstPos = *reader->opt_head_pos();
        assert(reader->opt_head_pos() != nullptr);

        //
        // Simple tokens:
        //

        TokenKind outKind = lexOneSimpleToken(reader);
        if (outKind == Tk::NONE) {
            // must be a more complex token...

            int firstChar = reader->read_head();
            
            // numbers:
            if (isdigit(firstChar)) {
                outKind = lexOneNumber(reader, info);
            }

            // strings:    
            else if (firstChar == '"' || firstChar == '\'') {
                outKind = lexOneString(reader, info, firstPos);
            }

            // IDs and keywords:
            else if (isFirstIdChar(firstChar)) {
                outKind = lexOneIdOrKeyword(reader, info, firstPos);
            }

            // Error: unknown token kind.
            // Offer feedback with location, RETURN EARLY with Tk::NONE
            else {
                source::Loc loc {firstPos};
                loc.source(reader->opt_source());

                std::vector<feedback::Note*> notes; {
                    notes.reserve(1);
                    notes.push_back(new feedback::SourceLocNote("here...", loc));
                }
                char offendingChar = firstChar;
                std::stringstream headline_ss;
                headline_ss 
                    << "Before '" << offendingChar << "' " 
                    << "(U+" << std::hex << (int)offendingChar << ") "
                    << "expected a valid token.";
                feedback::Letter* letter = new feedback::Letter(
                    feedback::Severity::FatalError,
                    std::move(headline_ss.str()),
                    std::move(std::string("")),
                    std::move(notes)
                );
                feedback::post(letter);
                return Tk::NONE;
            }
        }

        // populating lastLoc, creating span, returning VALID token kind found so far:
        source::Pos lastPos = *reader->opt_head_pos();
        *out_loc = source::Loc{firstPos, lastPos};
        return outKind;
    }

    TokenKind lexOneSimpleToken(Reader* source) {
        TokenKind tk = helpLexOneSimpleToken(source);
        // if (tk != Tk::NONE) {
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
                    return Tk::DOT;
                }
                break;
            }
            case ',':
            {
                if (source->advance_head()) {
                    return Tk::COMMA;
                }
                break;
            }
            case ';':
            {
                if (source->advance_head()) {
                    return Tk::SEMICOLON;
                }
                break;
            }
            case '(':
            {
                if (source->advance_head()) {
                    return Tk::LPAREN;
                }
                break;
            }
            case ')':
            {
                if (source->advance_head()) {
                    return Tk::RPAREN;
                }
                break;
            }
            case '[':
            {
                if (source->advance_head()) {
                    return Tk::LSQBRK;
                }
                break;
            }
            case ']':
            {
                if (source->advance_head()) {
                    return Tk::RSQBRK;
                }
                break;
            }
            case '{':
            {
                if (source->advance_head()) {
                    return Tk::LCYBRK;
                }
                break;
            }
            case '}':
            {
                if (source->advance_head()) {
                    return Tk::RCYBRK;
                }
                break;
            }
            case '*':
            {
                if (source->advance_head()) {
                    return Tk::ASTERISK;
                }
                break;
            }
            case '/':
            {
                if (source->advance_head()) {
                    return Tk::FSLASH;
                }
                break;
            }
            case '%':
            {
                if (source->advance_head()) {
                    return Tk::PERCENT;
                }
                break;
            }
            case '+':
            {
                if (source->advance_head()) {
                    return Tk::PLUS;
                }
                break;
            }
            case '^':
            {
                if (source->advance_head()) {
                    return Tk::CARET;
                }
                break;
            }
            case '&':
            {
                if (source->advance_head()) {
                    return Tk::AMPERSAND;
                }
                break;
            }
            case '|':
            {
                if (source->advance_head()) {
                    return Tk::PIPE;
                }
                break;
            }
            
            case '=':
            {
                if (source->advance_head()) {
                    if (source->read_head() == '=' && source->advance_head()) {
                        return Tk::EQUALS;
                    }
                    return Tk::BIND;
                }
                break;
            }
            case ':': 
            {
                if (source->advance_head()) {
                    if (source->read_head() == ':' && source->advance_head()) {
                        return Tk::DBL_COLON;
                    }
                    else if (source->read_head() == '<' && source->advance_head()) {
                        return Tk::COLON_LTHAN;
                    }
                    return Tk::COLON;
                }
                break;
            }
            case '!':
            {
                if (source->advance_head()) {
                    return Tk::EXCLAIM;
                }
                break;
            }
            case '-': 
            {
                if (source->advance_head()) {
                    if (source->read_head() == '>' && source->advance_head()) {
                        return Tk::ARROW;
                    }
                    return Tk::MINUS;
                }
                break;
            }
            case '<': 
            {
                if (source->advance_head()) {
                    if (source->read_head() == '=' && source->advance_head()) {
                        return Tk::LETHAN;
                    } else if (source->read_head() == '>' && source->advance_head()) {
                        return Tk::NEQUALS;
                    }
                    return Tk::LTHAN;
                }
                break;
            }
            case '>':
            {
                if (source->advance_head()) {
                    if (source->read_head() == '=' && source->advance_head()) {
                        return Tk::GETHAN;
                    }
                    else if (source->read_head() == ':' && source->advance_head()) {
                        return Tk::GTHAN_COLON;
                    }
                    return Tk::GTHAN;
                }
                break;
            }
            default:
            {
                break;
            }
        }
        return Tk::NONE;
    }
    TokenKind lexOneNumber(Reader* source, TokenInfo* infoP) {
        TokenInfo prefixTokenInfo{};
        TokenKind prefixTokenKind = lexOneIntChunk(source, &prefixTokenInfo, 0);
        
        TokenKind outTokenKind;
        TokenInfo outTokenInfo{};
        if (prefixTokenKind == Tk::DINT_LIT && source->read_head() == '.' && source->advance_head()) {
            // float
            TokenInfo suffixTokenInfo{};
            lexOneIntChunk(source, &suffixTokenInfo, true);

            // converting prefix and suffix ints into a double value:
            double dotPrefix = prefixTokenInfo.Int;
            double dotSuffix = suffixTokenInfo.Int;
            while (dotSuffix >= 1.0) {
                dotSuffix /= 10;
            }
            double value = dotPrefix + dotSuffix;

            outTokenKind = Tk::FLOAT_LIT;
            outTokenInfo.Float = value;
        }
        else if (source->read_head() == 'u' && source->advance_head()) {
            // unsigned int
            switch (prefixTokenKind)
            {
                case Tk::DINT_LIT:
                {
                    outTokenKind = Tk::UNSIGNED_DINT_LIT;
                    break;
                }
                case Tk::XINT_LIT:
                {
                    outTokenKind = Tk::UNSIGNED_XINT_LIT;
                    break;
                }
                default:
                {
                    assert(0 && "Unsupported prefix token kind.");
                }
            }
            outTokenInfo = prefixTokenInfo;
        }
        else {
            outTokenKind = prefixTokenKind;
            outTokenInfo = prefixTokenInfo;
        }

        *infoP = outTokenInfo;
        return outTokenKind;
    }
    TokenKind lexOneIntChunk(Reader* source, TokenInfo* infoP, int noPrefix) {
        // Checking for a hex prefix:
        TokenKind tokenKind = Tk::DINT_LIT;
        if (!noPrefix) {
            if (source->read_head() == '0' && source->advance_head()) {
                if (source->read_head() == 'x' && source->advance_head()) {
                    // 0x hex prefix detected.
                    tokenKind = Tk::XINT_LIT;
                }
            }
        }
        // Repeatedly reading integer characters:
        size_t value = 0;
        do {
            int intChar = source->read_head();
            if (intChar == '_') {
                continue;
            } else if (tokenKind == Tk::DINT_LIT) {
                if (isdigit(intChar)) {
                    value = (10*value) + (intChar - '0');
                } else {
                    break;
                }
            } else if (tokenKind == Tk::XINT_LIT) {
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
        infoP->Int = value;

        // Returning results:
        return tokenKind;
    }
    TokenKind lexOneIdOrKeyword(Reader* source, TokenInfo* infoP, source::Pos const& firstPos) {
        // The longest supported ID is (MAX_ID_LEN) characters long.
        size_t index;
        char charBuf[MAX_ID_LEN+1];
        for (index = 0; index < MAX_ID_LEN; index++) {
            // reading the next character:
            char ch = static_cast<char>(source->read_head());
            
            // adding the character to the charBuf:
            if (isIdChar(ch) && source->advance_head()) {
                charBuf[index] = ch;
            } else {
                break;
            }
        }
        int length = index;
        charBuf[length] = '\0';
        if (isIdChar(static_cast<char>(source->read_head())) && length == MAX_ID_LEN) {
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
            return Tk::NONE;
        }
        charBuf[index] = '\0';

        // Looking up charBuf as a keyword or symbol:
        intern::String intstr = charBuf;
        if (intstr == keywords.using_int_str) { return Tk::KW_USING; }
        if (intstr == keywords.cls_int_str) { return Tk::KW_CLS; }
        if (intstr == keywords.import_int_str) { return Tk::KW_IMPORT; }
        if (intstr == keywords.if_int_str) { return Tk::KW_IF; }
        if (intstr == keywords.then_int_str) { return Tk::KW_THEN; }
        if (intstr == keywords.else_int_str) { return Tk::KW_ELSE; }
        if (intstr == keywords.match_int_str) { return Tk::KW_MATCH; }
        if (intstr == keywords.with_int_str) { return Tk::KW_WITH; }
        if (intstr == keywords.const_int_str) { return Tk::KW_CONST; }
        if (intstr == keywords.val_int_str) { return Tk::KW_VAL; }
        if (intstr == keywords.var_int_str) { return Tk::KW_VAR; }
        if (intstr == keywords.and_int_str) { return Tk::KW_AND; }
        if (intstr == keywords.xor_int_str) { return Tk::KW_XOR; }
        if (intstr == keywords.or_int_str) { return Tk::KW_OR; }
        if (intstr == keywords.not_int_str) { return Tk::KW_NOT; }
        if (intstr == keywords.set_int_str) { return Tk::KW_SET; }
        if (intstr == keywords.fn_int_str) { return Tk::KW_FN; }
        if (intstr == keywords.mod_int_str) { return Tk::KW_MOD; }
        if (intstr == keywords.from_int_str) { return Tk::KW_FROM; }
        if (intstr == keywords.out_int_str) { return Tk::KW_OUT; }
        if (intstr == keywords.inout_int_str) { return Tk::KW_INOUT; }
        if (intstr == keywords.discard_int_str) { return Tk::KW_DISCARD; }
        if (intstr == keywords.enum_int_str) { return Tk::KW_ENUM; }
        else {
            infoP->ID_intstr = intstr;
            return getIdTextKind(charBuf);
        }
    }
    TokenKind lexOneString(Reader* source, TokenInfo* infoP, source::Pos const& firstPos) {
        // reading the first character, i.e., the quote character:
        int quoteChar = source->read_head();
        TokenKind tokenKind;
        if (quoteChar == '"') {
            tokenKind = Tk::DQSTRING_LIT;
        } else if (quoteChar == '\'') { 
            tokenKind = Tk::SQSTRING_LIT;
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
                std::move(std::string("Invalid string literal")),
                std::move("Before EOF, expected quotechar: <" + std::string(1,quoteChar) + ">"),
                std::move(notes)
            ));
            return Tk::NONE;
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
        bool contains_letters_before_cp = false;
        bool contains_lowercase_letters = false;
        for (char const* cp = idText; *cp; cp++) {
            if (isalpha(*cp)) {
                // if the first letter is lowercase, this must be a value ID
                if (!contains_letters_before_cp && islower(*cp)) {
                    return Tk::VID;
                }

                // if a letter that is not the first letter is lowercase, must be a TID
                if (islower(*cp)) {
                    contains_lowercase_letters = true;
                }

                // updating variables outside the loop for the next iter:
                contains_letters_before_cp = true;
            }
        }
        if (contains_letters_before_cp) {
            if (contains_lowercase_letters) {
                return Tk::TID;
            } else {
                return Tk::CID;
            }
        } else {
            return Tk::HOLE;
        }
    }

    TokenKind LexOneToken(Reader* source, TokenInfo* infoP, source::Loc* span) {
        TokenKind tk = lexOneToken(source, infoP, span);

        bool const print_tokens_in_debug_mode = false;
        if (DEBUG && print_tokens_in_debug_mode) {
            char buffer[512];
            aux::TokenToText(tk, infoP, buffer, 512);
            printf("%s\n", buffer);
        }

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
        TokenInfo tok_info{};
        source::Loc tok_loc = source::Loc::none;
        for (;;) {
            TokenKind kind = aux::LexOneToken(source, &tok_info, &tok_loc);
            if (kind == Tk::NONE) {
                printf("Terminated with TK_NULL\n");
                break;
            }
            if (kind == Tk::EOS) {
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
            case Tk::DOT:
            {
                name = ".";
                break;
            }
            case Tk::COMMA:
            {
                name = ",";
                break;
            }
            case Tk::COLON:
            {
                name = ":";
                break;
            }
            case Tk::LPAREN:
            {
                name = "(";
                break;
            }
            case Tk::RPAREN:
            {
                name = ")";
                break;
            }
            case Tk::LSQBRK:
            {
                name = "[";
                break;
            }
            case Tk::RSQBRK:
            {
                name = "]";
                break;
            }
            case Tk::LCYBRK:
            {
                name = "{";
                break;
            }
            case Tk::RCYBRK:
            {
                name = "}";
                break;
            }
            case Tk::SEMICOLON:
            {
                name = ";";
                break;
            }
            case Tk::ASTERISK:
            {
                name = "*";
                break;
            }
            case Tk::FSLASH:
            {
                name = "/";
                break;
            }
            case Tk::PERCENT:
            {
                name = "%";
                break;
            }
            case Tk::PLUS:
            {
                name = "+";
                break;
            }
            case Tk::MINUS:
            {
                name = "-";
                break;
            }
            case Tk::CARET:
            {
                name = "^";
                break;
            }
            case Tk::EXCLAIM:
            {
                name = "!";
                break;
            }
            case Tk::BIND:
            {
                name = "=";
                break;
            }
            case Tk::EQUALS:
            {
                name = "==";
                break;
            }
            case Tk::NEQUALS:
            {
                name = "!=";
                break;
            }
            case Tk::KW_USING:
            {
                name = "using";
                break;
            }
            case Tk::KW_CLS:
            {
                name = "cls";
                break;
            }
            case Tk::KW_MOD:
            {
                name = "mod";
                break;
            }
            case Tk::KW_IMPORT:
            {
                name = "import";
                break;
            }
            case Tk::KW_IF:
            {
                name = "if";
                break;
            }
            case Tk::KW_THEN:
            {
                name = "then";
                break;
            }
            case Tk::KW_ELSE:
            {
                name = "else";
                break;
            }
            case Tk::KW_MATCH:
            {
                name = "match";
                break;
            }
            case Tk::KW_AND:
            {
                name = "and";
                break;
            }
            case Tk::KW_XOR:
            {
                name = "xor";
                break;
            }
            case Tk::KW_OR:
            {
                name = "or";
                break;
            }
            case Tk::KW_NOT:
            {
                name = "not";
                break;
            }
            case Tk::KW_VAL:
            {
                name = "val";
                break;
            }
            case Tk::KW_VAR:
            {
                name = "var";
                break;
            }
            case Tk::KW_CONST:
            {
                name = "const";
                break;
            }
            case Tk::KW_SET:
            {
                name = "set";
                break;
            }
            case Tk::KW_FROM:
            {
                name = "from";
                break;
            }
            case Tk::KW_DISCARD:
            {
                name = "discard";
                break;
            }
            case Tk::DINT_LIT:
            {
                name = "<d-int>";
                snprintf(info, MAX_INFO_LEN, "%zd", ti->Int);
                break;
            }
            case Tk::XINT_LIT:
            {
                name = "<x-int>";
                snprintf(info, MAX_INFO_LEN, "%zd", ti->Int);
                break;
            }
            case Tk::FLOAT_LIT:
            {
                name = "<float>";
                snprintf(info, MAX_INFO_LEN, "%Lf", ti->Float);
                break;
            }
            case Tk::DQSTRING_LIT:
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
            case Tk::SQSTRING_LIT:
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
            case Tk::VID:
            {
                name = "<vid>";
                snprintf(info, MAX_INFO_LEN, "%s", ti->ID_intstr.content());
                break;
            }
            case Tk::TID:
            {
                name = "<tid>";
                snprintf(info, MAX_INFO_LEN, "%s", ti->ID_intstr.content());
                break;
            }
            case Tk::ARROW:
            {
                name = "->";
                break;
            }
            case Tk::NONE:
            {
                name = "<NONE>";
                break;
            }
            case Tk::EOS:
            {
                name = "<EOS>";
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

//
// Definitions:
//

namespace pdm::parser {

    bool Lexer::setup(source::ISource* source) {
        return m_reader.setup(source);
    }

    TokenKind Lexer::lex_one_token(TokenInfo* out_info, source::Loc* out_loc) {
        return aux::LexOneToken(&m_reader, out_info, out_loc);
    }

    void debug_print_token(char const* prefix, TokenKind tk, TokenInfo* ti, source::Loc* locp)  {
        return aux::DebugPrintToken(prefix, tk, ti, locp);
    }

}
