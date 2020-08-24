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
    TK_KW_IMPORT, TK_KW_EXPORT, TK_KW_DO, TK_KW_IF, TK_KW_THEN, TK_KW_ELSE, TK_KW_OPERATOR, TK_KW_MATCH,
    TK_DINT_LIT, TK_XINT_LIT, TK_FLOAT_LIT, TK_DQSTRING_LIT, TK_SQSTRING_LIT,
    TK_DOT, TK_COLON, TK_COMMA, TK_SEMICOLON,
    TK_NOT, TK_REF,
    TK_LPAREN, TK_RPAREN, TK_LSQBRK, TK_RSQBRK, TK_LCYBRK, TK_RCYBRK,
    TK_ARROW_LT,
    TK_ASTERISK, TK_FSLASH, TK_PERCENT,
    TK_PLUS, TK_MINUS,
    TK_LTHAN, TK_LETHAN, TK_GTHAN, TK_GETHAN,
    TK_EQUALS, TK_NEQUALS,
    TK_BINARY_AND, TK_BINARY_OR
};

struct TokenInfo {
    Loc loc;
    long double asFloat;
    size_t asInt;
    SymbolID asID;
};

#endif  // INCLUDED_LEXER_H
