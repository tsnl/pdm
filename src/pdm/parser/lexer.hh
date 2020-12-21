#ifndef INCLUDED_PDM_PARSER_LEXER_HH
#define INCLUDED_PDM_PARSER_LEXER_HH

#include <cstdio>
#include <cstddef>

#include "pdm/source/loc.hh"
#include "pdm/core/intern.hh"
#include "pdm/core/utf8.hh"

#include "reader.hh"

namespace pdm::parser {

    typedef int TokenKind;
    
    union TokenInfo {
        long double Float;
        size_t Int;
        intern::String ID_intstr;
        utf8::String* String_utf8string;
    };

    class Lexer {
      private:
        Reader m_reader;

      public:
        Lexer(): m_reader() {}

      public:
        bool setup(source::Source* source);

      public:
        TokenKind lex_one_token(TokenInfo* out_info, source::Loc* out_loc);
    };

    //
    // Reflection
    //

    std::string token_to_str(TokenKind tk, TokenInfo* ti, char* buf, int buf_length);
    void debug_print_token(char const* prefix, TokenKind tk, TokenInfo* ti, source::Loc* span);

}

#endif  // INCLUDED_PDM_PARSER_LEXER_H


