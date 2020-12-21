/* A Bison parser, made by GNU Bison 3.7.3.  */

/* Skeleton interface for Bison GLR parsers in C

   Copyright (C) 2002-2015, 2018-2020 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

#ifndef YY_YY_PARSER_TAB_H_INCLUDED
# define YY_YY_PARSER_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
#line 126 "parser.yy"

    #include "ast.h"
    #include "source.h"
    #include "lexer.h"
    #include "extra-tokens.h"

    #include "stb/stretchy_buffer.h"

#line 53 "parser.tab.h"

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    TK_VID = 258,                  /* "a VID (ID with first letter lowercase)"  */
    TK_TID = 259,                  /* "a TID (ID with first letter uppercase)"  */
    TK_HOLE = 260,                 /* "a HOLE (ID without any letters)"  */
    TK_KW_NAMESPACE = 261,         /* "'namespace'"  */
    TK_KW_MOD = 262,               /* "'mod'"  */
    TK_KW_DO = 263,                /* "'do'"  */
    TK_KW_IF = 264,                /* "'if'"  */
    TK_KW_THEN = 265,              /* "'then'"  */
    TK_KW_ELSE = 266,              /* "'else'"  */
    TK_KW_OPERATOR = 267,          /* "'operator'"  */
    TK_KW_MATCH = 268,             /* "'match'"  */
    TK_KW_WITH = 269,              /* "'with'"  */
    TK_KW_RETURN = 270,            /* "'return'"  */
    TK_KW_DISCARD = 271,           /* "'discard'"  */
    TK_KW_REQUIRE = 272,           /* "'require'"  */
    TK_KW_IMPORT = 273,            /* "'import'"  */
    TK_KW_EXPORT = 274,            /* "'export'"  */
    TK_KW_LINK = 275,              /* "'link'"  */
    TK_KW_FROM = 276,              /* "'from'"  */
    TK_KW_AS = 277,                /* "'as'"  */
    TK_KW_FUN = 278,               /* "'fun'"  */
    TK_KW_LET = 279,               /* "'let'"  */
    TK_KW_SET = 280,               /* "'set'"  */
    TK_KW_DEF = 281,               /* "'def'"  */
    TK_KW_TYPE = 282,              /* "'type'"  */
    TK_KW_ENUM = 283,              /* "'enum'"  */
    TK_KW_AND = 284,               /* "'and'"  */
    TK_KW_XOR = 285,               /* "'xor'"  */
    TK_KW_OR = 286,                /* "'or'"  */
    TK_KW_NOT = 287,               /* "'not'"  */
    TK_KW_TTUPLE = 288,            /* "'Tuple'"  */
    TK_KW_TARRAY = 289,            /* "'Array'"  */
    TK_DINT_LIT = 290,             /* TK_DINT_LIT  */
    TK_XINT_LIT = 291,             /* TK_XINT_LIT  */
    TK_FLOAT_LIT = 292,            /* TK_FLOAT_LIT  */
    TK_DQSTRING_LIT = 293,         /* TK_DQSTRING_LIT  */
    TK_SQSTRING_LIT = 294,         /* TK_SQSTRING_LIT  */
    TK_DOT = 295,                  /* "'.'"  */
    TK_COLON = 296,                /* "':'"  */
    TK_COMMA = 297,                /* "','"  */
    TK_SEMICOLON = 298,            /* "';'"  */
    TK_DBL_COLON = 299,            /* "'::'"  */
    TK_TPL_COLON = 300,            /* "':::'"  */
    TK_LPAREN = 301,               /* "'('"  */
    TK_RPAREN = 302,               /* "')'"  */
    TK_LSQBRK = 303,               /* "'['"  */
    TK_RSQBRK = 304,               /* "']'"  */
    TK_LCYBRK = 305,               /* "'{'"  */
    TK_RCYBRK = 306,               /* "'}'"  */
    TK_ARROW = 307,                /* "'->'"  */
    TK_ASTERISK = 308,             /* "'*'"  */
    TK_FSLASH = 309,               /* "'/'"  */
    TK_PERCENT = 310,              /* "'%'"  */
    TK_PLUS = 311,                 /* "'+'"  */
    TK_MINUS = 312,                /* "'-'"  */
    TK_LTHAN = 313,                /* "'<'"  */
    TK_LETHAN = 314,               /* "'<='"  */
    TK_GTHAN = 315,                /* "'>'"  */
    TK_GETHAN = 316,               /* "'>='"  */
    TK_BIND = 317,                 /* "'='"  */
    TK_EQUALS = 318,               /* "'=='"  */
    TK_NEQUALS = 319,              /* "'!='"  */
    TK_DOLLAR = 320,               /* "'$'"  */
    TK_CARET = 321,                /* "'^'"  */
    TK_AMPERSAND = 322,            /* "'&'"  */
    TK_EXCLAIM = 323,              /* "'!'"  */
    TK_EOS = 324                   /* "EOS"  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 39 "parser.yy"

    TokenInfo token;
    AstNode* nt;
    AstNode** ntSb;
    AstUnaryOperator uop;
    AstBinaryOperator bop;

#line 147 "parser.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
typedef Span YYLTYPE;



int yyparse (Source* source, AstNode** outp);
/* "%code provides" blocks.  */
#line 135 "parser.yy"

    int yylex(YYSTYPE *lvalp, YYLTYPE *llocp, Source* source);
    void yyerror(YYLTYPE* llocp, Source* source, AstNode** outp, char const* message);

#line 167 "parser.tab.h"

#endif /* !YY_YY_PARSER_TAB_H_INCLUDED  */
