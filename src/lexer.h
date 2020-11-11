#ifndef INCLUDED_LEXER_H
#define INCLUDED_LEXER_H

#include <stdio.h>
#include <stddef.h>

#include "source.h"
#include "symbols.h"
#include "unicoder.h"

typedef size_t LexerID;
// typedef enum TokenKind TokenKind;
typedef int TokenKind;
typedef union TokenInfo TokenInfo;

void InitLexer(void);
void DeInitLexer(void);

TokenKind LexOneToken(Source* source, TokenInfo* info, Span* span);

// including/configuring parser.tab.h:
// enum TokenKind {
//     TK_EOS = -1,
//     TK_NULL = 0,
//     TK_VID, TK_TID, TK_HOLE,
//     TK_KW_DO, TK_KW_IF, TK_KW_THEN, TK_KW_ELSE, TK_KW_OPERATOR, 
//     TK_KW_MATCH, TK_KW_WITH, TK_KW_RETURN, TK_KW_DISCARD,
//     TK_KW_IMPORT, TK_KW_EXPORT, TK_KW_EXTERN,
//     TK_KW_FUN, TK_KW_SET, TK_KW_LET, TK_KW_DEF,
//     TK_KW_AND, TK_KW_XOR, TK_KW_OR, TK_KW_NOT,
//     TK_DINT_LIT, TK_XINT_LIT, TK_FLOAT_LIT, TK_DQSTRING_LIT, TK_SQSTRING_LIT,
//     TK_DOT, TK_COLON, TK_COMMA, TK_SEMICOLON,
//     TK_EXCLAIM, TK_CARET,
//     TK_DBL_COLON, TK_TPL_COLON,
//     TK_LPAREN, TK_RPAREN, TK_LSQBRK, TK_RSQBRK, TK_LCYBRK, TK_RCYBRK,
//     TK_ARROW,
//     TK_ASTERISK, TK_FSLASH, TK_PERCENT,
//     TK_PLUS, TK_MINUS,
//     TK_LTHAN, TK_LETHAN, TK_GTHAN, TK_GETHAN,
//     TK_BIND, TK_EQUALS, TK_NEQUALS,
//     TK_DOLLAR,
//     __TK_ERROR
// };
// #define YYTOKENTYPE TokenKind

union TokenInfo {
    long double Float;
    size_t Int;
    SymbolID ID_symbolID;
    Utf8String String_utf8string;
};

//
// Reflection
//

void DebugLexer(Source* source);
int TokenToText(TokenKind tk, TokenInfo* ti, char* buf, int bufLength);
void DebugPrintToken(char const* prefix, TokenKind tk, TokenInfo* ti, Span* span);

#endif  // INCLUDED_LEXER_H
