#ifndef INCLUDED_LEXER_H
#define INCLUDED_LEXER_H

#include <stddef.h>
#include <stdio.h>

#include "source.h"

typedef size_t LexerID;
typedef enum   TokenKind TokenKind;
typedef struct TokenInfo TokenInfo;

LexerID create_lexer(FILE* file);
TokenKind lex_one_token(LexerID lexer, TokenInfo* opt_info_p);

enum TokenKind {
    TK_NULL = 0,
    TK_ID,
    TK_KW_IMPORT, TK_KW_EXPORT, TK_KW_DO, TK_KW_IF, TK_KW_THEN, TK_KW_ELSE, TK_KW_OPERATOR, TK_KW_MATCH,
    TK_DINT_LIT, TK_XINT_LIT, TK_FLOAT_LIT, TK_DQSTRING_LIT, TK_SQSTRING_LIT,
    
    TK_DOT, TK_COLON, TK_COMMA, TK_SEMICOLON,
    TK_NOT, TK_REF,
    TK_LPAREN, TK_RPAREN, TK_LSQBRK, TK_RSQBRK, TK_LCYBRK, TK_RCYBRK,
    TK_BIND, TK_RIGHT_ARROW,
    TK_ASTERISK, TK_FSLASH, TK_PERCENT,
    TK_PLUS, TK_MINUS,
    TK_LTHAN, TK_LETHAN, TK_GTHAN, TK_GETHAN,
    TK_EQUALS, TK_NEQUALS,
    TK_AND, TK_OR
};

struct TokenInfo {
    Loc loc;
    char const* text;
    union {
        long double as_float;
        size_t as_int;
    } value;
};

#endif  // INCLUDED_LEXER_H
