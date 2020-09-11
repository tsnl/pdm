#ifndef INCLUDED_LEXER_H
#define INCLUDED_LEXER_H

#include <stdio.h>
#include <stddef.h>

#include "source.h"
#include "symbols.h"

typedef size_t LexerID;
typedef enum   TokenKind TokenKind;
typedef struct TokenInfo TokenInfo;

void InitLexer(void);
void DeInitLexer(void);

TokenKind LexOneToken(Source* source, TokenInfo* optInfoP);

enum TokenKind {
    TK_EOS = -1,
    TK_NULL = 0,
    TK_ID,
    TK_KW_IMPORT, TK_KW_EXPORT, TK_KW_DO, TK_KW_IF, TK_KW_THEN, TK_KW_ELSE, TK_KW_OPERATOR, 
    TK_KW_MATCH, TK_KW_RETURN, TK_KW_CHECK,
    TK_DINT_LIT, TK_XINT_LIT, TK_FLOAT_LIT, TK_DQSTRING_LIT, TK_SQSTRING_LIT,
    TK_DOT, TK_COLON, TK_COMMA, TK_SEMICOLON,
    TK_NOT, TK_CARET,
    TK_LPAREN, TK_RPAREN, TK_LSQBRK, TK_RSQBRK, TK_LCYBRK, TK_RCYBRK,
    TK_ARROW,
    TK_ASTERISK, TK_FSLASH, TK_PERCENT,
    TK_PLUS, TK_MINUS,
    TK_LTHAN, TK_LETHAN, TK_GTHAN, TK_GETHAN,
    TK_BIND, TK_EQUALS, TK_NEQUALS,
    TK_AND, TK_OR,
};

struct TokenInfo {
    Loc loc;
    union {
        long double Float;
        size_t Int;
        SymbolID ID;
        char* Utf8String;
    } as;
};

#endif  // INCLUDED_LEXER_H
