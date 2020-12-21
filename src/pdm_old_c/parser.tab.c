/* A Bison parser, made by GNU Bison 3.7.3.  */

/* Skeleton implementation for Bison GLR parsers in C

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

/* C GLR parser skeleton written by Paul Hilfinger.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.7.3"

/* Skeleton name.  */
#define YYSKELETON_NAME "glr.c"

/* Pure parsers.  */
#define YYPURE 1







# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "parser.tab.h"

/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_TK_VID = 3,                     /* "a VID (ID with first letter lowercase)"  */
  YYSYMBOL_TK_TID = 4,                     /* "a TID (ID with first letter uppercase)"  */
  YYSYMBOL_TK_HOLE = 5,                    /* "a HOLE (ID without any letters)"  */
  YYSYMBOL_TK_KW_NAMESPACE = 6,            /* "'namespace'"  */
  YYSYMBOL_TK_KW_MOD = 7,                  /* "'mod'"  */
  YYSYMBOL_TK_KW_DO = 8,                   /* "'do'"  */
  YYSYMBOL_TK_KW_IF = 9,                   /* "'if'"  */
  YYSYMBOL_TK_KW_THEN = 10,                /* "'then'"  */
  YYSYMBOL_TK_KW_ELSE = 11,                /* "'else'"  */
  YYSYMBOL_TK_KW_OPERATOR = 12,            /* "'operator'"  */
  YYSYMBOL_TK_KW_MATCH = 13,               /* "'match'"  */
  YYSYMBOL_TK_KW_WITH = 14,                /* "'with'"  */
  YYSYMBOL_TK_KW_RETURN = 15,              /* "'return'"  */
  YYSYMBOL_TK_KW_DISCARD = 16,             /* "'discard'"  */
  YYSYMBOL_TK_KW_REQUIRE = 17,             /* "'require'"  */
  YYSYMBOL_TK_KW_IMPORT = 18,              /* "'import'"  */
  YYSYMBOL_TK_KW_EXPORT = 19,              /* "'export'"  */
  YYSYMBOL_TK_KW_LINK = 20,                /* "'link'"  */
  YYSYMBOL_TK_KW_FROM = 21,                /* "'from'"  */
  YYSYMBOL_TK_KW_AS = 22,                  /* "'as'"  */
  YYSYMBOL_TK_KW_FUN = 23,                 /* "'fun'"  */
  YYSYMBOL_TK_KW_LET = 24,                 /* "'let'"  */
  YYSYMBOL_TK_KW_SET = 25,                 /* "'set'"  */
  YYSYMBOL_TK_KW_DEF = 26,                 /* "'def'"  */
  YYSYMBOL_TK_KW_TYPE = 27,                /* "'type'"  */
  YYSYMBOL_TK_KW_ENUM = 28,                /* "'enum'"  */
  YYSYMBOL_TK_KW_AND = 29,                 /* "'and'"  */
  YYSYMBOL_TK_KW_XOR = 30,                 /* "'xor'"  */
  YYSYMBOL_TK_KW_OR = 31,                  /* "'or'"  */
  YYSYMBOL_TK_KW_NOT = 32,                 /* "'not'"  */
  YYSYMBOL_TK_KW_TTUPLE = 33,              /* "'Tuple'"  */
  YYSYMBOL_TK_KW_TARRAY = 34,              /* "'Array'"  */
  YYSYMBOL_TK_DINT_LIT = 35,               /* TK_DINT_LIT  */
  YYSYMBOL_TK_XINT_LIT = 36,               /* TK_XINT_LIT  */
  YYSYMBOL_TK_FLOAT_LIT = 37,              /* TK_FLOAT_LIT  */
  YYSYMBOL_TK_DQSTRING_LIT = 38,           /* TK_DQSTRING_LIT  */
  YYSYMBOL_TK_SQSTRING_LIT = 39,           /* TK_SQSTRING_LIT  */
  YYSYMBOL_TK_DOT = 40,                    /* "'.'"  */
  YYSYMBOL_TK_COLON = 41,                  /* "':'"  */
  YYSYMBOL_TK_COMMA = 42,                  /* "','"  */
  YYSYMBOL_TK_SEMICOLON = 43,              /* "';'"  */
  YYSYMBOL_TK_DBL_COLON = 44,              /* "'::'"  */
  YYSYMBOL_TK_TPL_COLON = 45,              /* "':::'"  */
  YYSYMBOL_TK_LPAREN = 46,                 /* "'('"  */
  YYSYMBOL_TK_RPAREN = 47,                 /* "')'"  */
  YYSYMBOL_TK_LSQBRK = 48,                 /* "'['"  */
  YYSYMBOL_TK_RSQBRK = 49,                 /* "']'"  */
  YYSYMBOL_TK_LCYBRK = 50,                 /* "'{'"  */
  YYSYMBOL_TK_RCYBRK = 51,                 /* "'}'"  */
  YYSYMBOL_TK_ARROW = 52,                  /* "'->'"  */
  YYSYMBOL_TK_ASTERISK = 53,               /* "'*'"  */
  YYSYMBOL_TK_FSLASH = 54,                 /* "'/'"  */
  YYSYMBOL_TK_PERCENT = 55,                /* "'%'"  */
  YYSYMBOL_TK_PLUS = 56,                   /* "'+'"  */
  YYSYMBOL_TK_MINUS = 57,                  /* "'-'"  */
  YYSYMBOL_TK_LTHAN = 58,                  /* "'<'"  */
  YYSYMBOL_TK_LETHAN = 59,                 /* "'<='"  */
  YYSYMBOL_TK_GTHAN = 60,                  /* "'>'"  */
  YYSYMBOL_TK_GETHAN = 61,                 /* "'>='"  */
  YYSYMBOL_TK_BIND = 62,                   /* "'='"  */
  YYSYMBOL_TK_EQUALS = 63,                 /* "'=='"  */
  YYSYMBOL_TK_NEQUALS = 64,                /* "'!='"  */
  YYSYMBOL_TK_DOLLAR = 65,                 /* "'$'"  */
  YYSYMBOL_TK_CARET = 66,                  /* "'^'"  */
  YYSYMBOL_TK_AMPERSAND = 67,              /* "'&'"  */
  YYSYMBOL_TK_EXCLAIM = 68,                /* "'!'"  */
  YYSYMBOL_TK_EOS = 69,                    /* "EOS"  */
  YYSYMBOL_YYACCEPT = 70,                  /* $accept  */
  YYSYMBOL_script = 71,                    /* script  */
  YYSYMBOL_scriptContent = 72,             /* scriptContent  */
  YYSYMBOL_scriptContentStmt = 73,         /* scriptContentStmt  */
  YYSYMBOL_moduleStmt = 74,                /* moduleStmt  */
  YYSYMBOL_moduleContent = 75,             /* moduleContent  */
  YYSYMBOL_chainPrefixStmt = 76,           /* chainPrefixStmt  */
  YYSYMBOL_letStmt = 77,                   /* letStmt  */
  YYSYMBOL_setStmt = 78,                   /* setStmt  */
  YYSYMBOL_discardStmt = 79,               /* discardStmt  */
  YYSYMBOL_moduleContentStmt = 80,         /* moduleContentStmt  */
  YYSYMBOL_defStmt = 81,                   /* defStmt  */
  YYSYMBOL_typedefStmt = 82,               /* typedefStmt  */
  YYSYMBOL_typedefStmt_enum = 83,          /* typedefStmt_enum  */
  YYSYMBOL_importStmt = 84,                /* importStmt  */
  YYSYMBOL_linkStmt = 85,                  /* linkStmt  */
  YYSYMBOL_linkStmtItem = 86,              /* linkStmtItem  */
  YYSYMBOL_linkStmtContent = 87,           /* linkStmtContent  */
  YYSYMBOL_tid = 88,                       /* tid  */
  YYSYMBOL_vid = 89,                       /* vid  */
  YYSYMBOL_floatl = 90,                    /* floatl  */
  YYSYMBOL_stringl = 91,                   /* stringl  */
  YYSYMBOL_unit = 92,                      /* unit  */
  YYSYMBOL_expr = 93,                      /* expr  */
  YYSYMBOL_expr_cl = 94,                   /* expr_cl  */
  YYSYMBOL_expr_cl2 = 95,                  /* expr_cl2  */
  YYSYMBOL_parenExpr = 96,                 /* parenExpr  */
  YYSYMBOL_primaryExpr = 97,               /* primaryExpr  */
  YYSYMBOL_vparen = 98,                    /* vparen  */
  YYSYMBOL_vtuple = 99,                    /* vtuple  */
  YYSYMBOL_vstruct = 100,                  /* vstruct  */
  YYSYMBOL_ifThenElse = 101,               /* ifThenElse  */
  YYSYMBOL_chain = 102,                    /* chain  */
  YYSYMBOL_chainPrefix = 103,              /* chainPrefix  */
  YYSYMBOL_vlambda = 104,                  /* vlambda  */
  YYSYMBOL_postfixExpr = 105,              /* postfixExpr  */
  YYSYMBOL_vtcall = 106,                   /* vtcall  */
  YYSYMBOL_vvcall = 107,                   /* vvcall  */
  YYSYMBOL_dotNmExpr = 108,                /* dotNmExpr  */
  YYSYMBOL_dotIxExpr = 109,                /* dotIxExpr  */
  YYSYMBOL_colonNmExpr = 110,              /* colonNmExpr  */
  YYSYMBOL_castExpr = 111,                 /* castExpr  */
  YYSYMBOL_unaryExpr = 112,                /* unaryExpr  */
  YYSYMBOL_unaryOp = 113,                  /* unaryOp  */
  YYSYMBOL_binaryExpr = 114,               /* binaryExpr  */
  YYSYMBOL_mulBinaryOp = 115,              /* mulBinaryOp  */
  YYSYMBOL_mulBinaryExpr = 116,            /* mulBinaryExpr  */
  YYSYMBOL_addBinaryOp = 117,              /* addBinaryOp  */
  YYSYMBOL_addBinaryExpr = 118,            /* addBinaryExpr  */
  YYSYMBOL_cmpBinaryOp = 119,              /* cmpBinaryOp  */
  YYSYMBOL_cmpBinaryExpr = 120,            /* cmpBinaryExpr  */
  YYSYMBOL_eqBinaryOp = 121,               /* eqBinaryOp  */
  YYSYMBOL_eqBinaryExpr = 122,             /* eqBinaryExpr  */
  YYSYMBOL_andBinaryExpr = 123,            /* andBinaryExpr  */
  YYSYMBOL_xorBinaryExpr = 124,            /* xorBinaryExpr  */
  YYSYMBOL_orBinaryExpr = 125,             /* orBinaryExpr  */
  YYSYMBOL_typespec = 126,                 /* typespec  */
  YYSYMBOL_typespec_cl = 127,              /* typespec_cl  */
  YYSYMBOL_primaryTypespec = 128,          /* primaryTypespec  */
  YYSYMBOL_postfixTypespec = 129,          /* postfixTypespec  */
  YYSYMBOL_ttarg = 130,                    /* ttarg  */
  YYSYMBOL_ttarg_cl = 131,                 /* ttarg_cl  */
  YYSYMBOL_vtarg = 132,                    /* vtarg  */
  YYSYMBOL_vtarg_cl = 133,                 /* vtarg_cl  */
  YYSYMBOL_vstructField = 134,             /* vstructField  */
  YYSYMBOL_vstructField_cl = 135,          /* vstructField_cl  */
  YYSYMBOL_vpatternField = 136,            /* vpatternField  */
  YYSYMBOL_lpatternField = 137,            /* lpatternField  */
  YYSYMBOL_tpatternField = 138,            /* tpatternField  */
  YYSYMBOL_lpattern = 139,                 /* lpattern  */
  YYSYMBOL_vpattern = 140,                 /* vpattern  */
  YYSYMBOL_tpattern = 141,                 /* tpattern  */
  YYSYMBOL_vpatternField_cl = 142,         /* vpatternField_cl  */
  YYSYMBOL_lpatternField_cl = 143,         /* lpatternField_cl  */
  YYSYMBOL_tpatternField_cl = 144          /* tpatternField_cl  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;


/* Default (constant) value used for initialization for null
   right-hand sides.  Unlike the standard yacc.c template, here we set
   the default value of $$ to a zeroed-out value.  Since the default
   value is undefined, this behavior is technically correct.  */
static YYSTYPE yyval_default;
static YYLTYPE yyloc_default
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;



#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif
#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YYFREE
# define YYFREE free
#endif
#ifndef YYMALLOC
# define YYMALLOC malloc
#endif
#ifndef YYREALLOC
# define YYREALLOC realloc
#endif

#ifdef __cplusplus
  typedef bool yybool;
# define yytrue true
# define yyfalse false
#else
  /* When we move to stdbool, get rid of the various casts to yybool.  */
  typedef signed char yybool;
# define yytrue 1
# define yyfalse 0
#endif

#ifndef YYSETJMP
# include <setjmp.h>
# define YYJMP_BUF jmp_buf
# define YYSETJMP(Env) setjmp (Env)
/* Pacify Clang and ICC.  */
# define YYLONGJMP(Env, Val)                    \
 do {                                           \
   longjmp (Env, Val);                          \
   YY_ASSERT (0);                               \
 } while (yyfalse)
#endif

#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* The _Noreturn keyword of C11.  */
#ifndef _Noreturn
# if (defined __cplusplus \
      && ((201103 <= __cplusplus && !(__GNUC__ == 4 && __GNUC_MINOR__ == 7)) \
          || (defined _MSC_VER && 1900 <= _MSC_VER)))
#  define _Noreturn [[noreturn]]
# elif (!defined __cplusplus                     \
        && (201112 <= (defined __STDC_VERSION__ ? __STDC_VERSION__ : 0)  \
            || 4 < __GNUC__ + (7 <= __GNUC_MINOR__) \
            || (defined __apple_build_version__ \
                ? 6000000 <= __apple_build_version__ \
                : 3 < __clang_major__ + (5 <= __clang_minor__))))
   /* _Noreturn works as-is.  */
# elif 2 < __GNUC__ + (8 <= __GNUC_MINOR__) || 0x5110 <= __SUNPRO_C
#  define _Noreturn __attribute__ ((__noreturn__))
# elif 1200 <= (defined _MSC_VER ? _MSC_VER : 0)
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  7
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   384

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  70
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  75
/* YYNRULES -- Number of rules.  */
#define YYNRULES  148
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  257
/* YYMAXRHS -- Maximum number of symbols on right-hand side of rule.  */
#define YYMAXRHS 6
/* YYMAXLEFT -- Maximum number of symbols to the left of a handle
   accessed by $0, $-1, etc., in any rule.  */
#define YYMAXLEFT 0

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   324

/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69
};

#if YYDEBUG
/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   231,   231,   234,   235,   238,   246,   249,   250,   258,
     259,   260,   263,   266,   269,   273,   274,   275,   276,   277,
     278,   281,   282,   285,   288,   292,   296,   299,   302,   303,
     310,   311,   313,   316,   317,   320,   327,   330,   331,   334,
     335,   339,   340,   341,   342,   343,   344,   347,   348,   349,
     350,   351,   352,   353,   356,   359,   362,   365,   366,   369,
     370,   371,   374,   375,   378,   382,   383,   384,   385,   386,
     387,   390,   393,   394,   397,   400,   403,   407,   408,   412,
     413,   416,   417,   418,   419,   420,   424,   427,   428,   429,
     432,   433,   436,   437,   440,   441,   444,   445,   446,   447,
     450,   451,   454,   455,   458,   459,   462,   463,   466,   467,
     470,   471,   479,   482,   483,   487,   488,   489,   492,   493,
     494,   503,   504,   507,   508,   513,   514,   517,   518,   526,
     529,   530,   533,   536,   537,   540,   541,   544,   545,   546,
     549,   550,   553,   556,   557,   560,   561,   564,   565
};
#endif

#define YYPACT_NINF (-131)
#define YYTABLE_NINF (-1)

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      27,    33,    57,    27,    60,  -131,     0,  -131,    63,  -131,
     132,  -131,    73,    91,    73,   138,   138,  -131,   129,    66,
    -131,  -131,  -131,  -131,  -131,  -131,   133,  -131,  -131,   121,
      69,  -131,   125,   125,  -131,   139,  -131,    91,    73,    16,
     131,  -131,   144,   135,   128,   136,  -131,   169,   154,     5,
     135,  -131,    45,  -131,    -7,  -131,  -131,  -131,    39,   334,
     147,    45,   151,    91,  -131,  -131,   159,   155,   158,   161,
    -131,  -131,  -131,   -25,    73,  -131,   131,  -131,    37,    19,
    -131,  -131,  -131,   218,   180,  -131,  -131,  -131,  -131,  -131,
    -131,  -131,  -131,  -131,  -131,  -131,  -131,   105,  -131,  -131,
    -131,  -131,  -131,  -131,    37,   334,  -131,    73,  -131,  -131,
    -131,    45,    45,    45,   296,  -131,  -131,  -131,   200,    16,
      45,  -131,  -131,  -131,   168,  -131,  -131,  -131,  -131,  -131,
      42,    51,  -131,  -131,   296,  -131,   140,   119,   108,    98,
     194,   195,   193,    19,   296,   185,  -131,  -131,  -131,   167,
     181,    87,  -131,   -21,     7,   228,   257,   296,  -131,  -131,
     167,   213,  -131,    50,   196,  -131,    37,  -131,   -22,    37,
    -131,    71,    37,   296,  -131,   296,  -131,  -131,  -131,  -131,
    -131,   296,  -131,  -131,   296,  -131,  -131,  -131,  -131,   296,
    -131,  -131,   296,   296,   296,   296,   173,   177,  -131,   296,
    -131,  -131,   197,   191,    73,  -131,  -131,  -131,  -131,  -131,
    -131,    85,  -131,    37,  -131,     6,    91,    45,  -131,   296,
     296,  -131,   232,    73,  -131,  -131,  -131,  -131,  -131,   140,
     119,   127,    98,   194,   195,   296,   296,  -131,  -131,  -131,
    -131,   296,  -131,   296,  -131,  -131,  -131,   198,  -131,     8,
    -131,  -131,  -131,  -131,  -131,  -131,  -131
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     2,     0,     5,     0,     1,     0,     3,
       0,     4,     0,     0,     0,     0,     0,    20,     0,     0,
      15,    16,    17,    18,    19,    31,     0,    34,    33,     0,
       0,    30,     0,     0,     6,     0,     7,     0,     0,     0,
       0,   141,     0,     0,     0,     0,     8,     0,     0,     0,
       0,    35,     0,   143,     0,   135,   136,   147,     0,     0,
       0,     0,     0,     0,    28,    26,     0,     0,     0,     0,
     115,   132,   118,   112,     0,   140,     0,   142,     0,     0,
      49,    50,    32,     0,     0,    48,    51,    52,    41,    47,
      65,    42,    43,    44,    53,    45,    46,    77,    66,    67,
      68,    69,    70,    21,     0,     0,    23,     0,    24,    25,
      29,     0,     0,     0,     0,   120,   144,   148,     0,     0,
     134,   139,   133,   137,     0,    85,    83,    81,    82,    84,
       0,     0,    79,    90,     0,    36,    94,   100,   104,   106,
     108,   110,    86,     0,     0,     0,     9,    10,    11,    48,
      14,     0,   130,     0,     0,     0,     0,     0,    78,    22,
       0,     0,   113,     0,     0,   122,   121,   123,     0,     0,
     145,     0,     0,     0,    54,     0,    55,    80,    87,    88,
      89,     0,    92,    93,     0,    96,    97,    98,    99,     0,
     102,   103,     0,     0,     0,     0,     0,     0,    62,     0,
      59,    60,     0,    14,     0,    56,    74,    75,    76,    72,
      37,     0,   126,   125,   127,     0,     0,     0,   116,     0,
       0,   119,    57,     0,   138,    64,    39,    40,    91,    95,
     101,   105,   107,   109,   111,     0,     0,   129,    63,    61,
     131,     0,    73,     0,    71,    27,   114,     0,   124,     0,
     146,    12,    13,    38,   128,   117,    58
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -131,  -131,  -131,   241,    64,  -131,    94,  -131,  -131,  -131,
     230,  -131,  -131,  -131,  -131,  -131,   209,  -131,    -1,   -12,
    -131,    -8,   -27,   -71,  -131,  -131,   -72,    10,  -131,  -131,
     187,  -131,  -131,  -131,  -131,  -131,  -131,  -131,  -131,  -131,
    -131,   -52,  -130,  -131,  -131,  -131,    78,  -131,    74,  -131,
      75,  -131,    76,    79,    77,  -131,   -43,  -131,  -131,  -131,
      56,  -131,    34,  -131,    81,  -131,   -15,  -118,   202,   143,
      58,   146,  -131,  -131,  -131
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     3,     4,     5,    18,   145,   146,   147,   148,
      19,    20,    21,    22,    23,    24,    48,    49,    70,    85,
      86,    87,    88,   165,   211,   131,    89,    90,    91,    92,
      93,    94,    95,   151,    96,    97,    98,    99,   100,   101,
     102,   132,   133,   134,   135,   181,   136,   184,   137,   189,
     138,   192,   139,   140,   141,   142,   104,   163,    72,    73,
     167,   168,   214,   215,   152,   153,   122,   123,    57,   124,
      42,    43,    54,   171,    58
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      26,   170,    30,    41,   177,    29,   118,   103,    25,    71,
     206,    25,   130,   150,    32,    33,    41,    78,   106,    25,
     220,   204,    25,    41,    53,    56,    50,    52,    52,    47,
     205,    79,   158,   114,     1,    74,     6,    50,   221,    55,
      75,   115,   207,    80,    81,    82,    27,    28,   243,    31,
      10,   228,   121,   159,    83,   109,    65,     7,    84,   116,
      79,    56,    52,    51,    52,   119,   244,   120,   161,   162,
     164,   166,   149,   197,    17,    55,    25,    71,    68,    69,
     203,    76,    17,    83,   173,   210,   212,    84,    77,   174,
      25,    31,   217,   175,   158,   160,    78,   222,   176,   218,
     225,    60,   226,     9,   227,   250,    11,   120,    67,    36,
      79,   143,   144,   223,   213,    39,   121,    40,   224,   125,
      68,    69,    80,    81,    82,    27,    28,   241,   237,    27,
      28,   120,   242,    83,    25,    31,     1,    84,   201,     1,
     126,   158,    31,   127,   128,   154,   155,    12,   247,    13,
      12,   156,    13,   129,    37,    14,    15,    16,    14,    15,
      16,   190,   191,   157,   251,   252,   185,   186,   187,   188,
     253,    38,   212,    40,   246,   182,   183,   166,    44,    45,
      34,    39,    46,    25,    31,   185,   186,   187,   188,    78,
      61,    63,   160,   178,   179,   180,    59,    64,    62,   105,
     213,   107,   110,    79,   143,   144,   112,   111,   245,   113,
     169,   120,   125,    68,    69,    80,    81,    82,    27,    28,
     172,    25,    31,   193,   195,   194,    83,    78,   198,   199,
      84,   208,   200,   126,   216,   235,   127,   128,   219,   236,
     238,    79,   239,   249,     8,   202,   129,   255,    35,   108,
     125,    68,    69,    80,    81,    82,    27,    28,    66,   256,
      25,    31,   229,   230,    83,    51,    78,   231,    84,   232,
       0,   126,   234,   233,   127,   128,   248,   254,   117,     0,
      79,     0,     0,     0,   129,   240,   196,     0,     0,   125,
      68,    69,    80,    81,    82,    27,    28,     0,     0,    25,
      31,     0,     0,    83,   209,    78,     0,    84,     0,     0,
     126,     0,     0,   127,   128,     0,     0,     0,     0,    79,
       0,     0,     0,   129,     0,     0,     0,     0,   125,    68,
      69,    80,    81,    82,    27,    28,     0,    25,    31,     0,
       0,     0,    83,    78,     0,     0,    84,     0,     0,   126,
       0,     0,   127,   128,     0,     0,     0,    79,     0,     0,
       0,     0,   129,     0,     0,     0,     0,    68,    69,    80,
      81,    82,    27,    28,     0,     0,     0,     0,     0,     0,
      83,     0,     0,     0,    84
};

static const yytype_int16 yycheck[] =
{
      12,   119,    14,    30,   134,    13,    78,    59,     3,    52,
       3,     3,    83,    84,    15,    16,    43,     9,    61,     3,
      42,    42,     3,    50,    39,    40,    38,    39,    40,    37,
      51,    23,   104,    58,     7,    42,     3,    49,    60,    40,
      47,    66,    35,    35,    36,    37,    38,    39,    42,     4,
      50,   181,    79,   105,    46,    63,    51,     0,    50,    74,
      23,    76,    74,    47,    76,    46,    60,    79,   111,   112,
     113,   114,    84,   144,    10,    76,     3,   120,    33,    34,
     151,    42,    18,    46,    42,   156,   157,    50,    49,    47,
       3,     4,    42,    42,   166,   107,     9,   169,    47,    49,
     172,    43,   173,    43,   175,   223,    43,   119,    50,    43,
      23,    24,    25,    42,   157,    46,   143,    48,    47,    32,
      33,    34,    35,    36,    37,    38,    39,    42,   199,    38,
      39,   143,    47,    46,     3,     4,     7,    50,    51,     7,
      53,   213,     4,    56,    57,    40,    41,    18,   219,    20,
      18,    46,    20,    66,    21,    26,    27,    28,    26,    27,
      28,    63,    64,    58,   235,   236,    58,    59,    60,    61,
     241,    50,   243,    48,   217,    56,    57,   220,    32,    33,
      51,    46,    43,     3,     4,    58,    59,    60,    61,     9,
      62,    22,   204,    53,    54,    55,    52,    43,    62,    52,
     243,    50,    43,    23,    24,    25,    48,    52,   216,    48,
      10,   223,    32,    33,    34,    35,    36,    37,    38,    39,
      52,     3,     4,    29,    31,    30,    46,     9,    43,    62,
      50,     3,    51,    53,    21,    62,    56,    57,    42,    62,
      43,    23,    51,    11,     3,   151,    66,    49,    18,    62,
      32,    33,    34,    35,    36,    37,    38,    39,    49,   249,
       3,     4,   184,   189,    46,    47,     9,   192,    50,   193,
      -1,    53,   195,   194,    56,    57,   220,   243,    76,    -1,
      23,    -1,    -1,    -1,    66,   204,   143,    -1,    -1,    32,
      33,    34,    35,    36,    37,    38,    39,    -1,    -1,     3,
       4,    -1,    -1,    46,    47,     9,    -1,    50,    -1,    -1,
      53,    -1,    -1,    56,    57,    -1,    -1,    -1,    -1,    23,
      -1,    -1,    -1,    66,    -1,    -1,    -1,    -1,    32,    33,
      34,    35,    36,    37,    38,    39,    -1,     3,     4,    -1,
      -1,    -1,    46,     9,    -1,    -1,    50,    -1,    -1,    53,
      -1,    -1,    56,    57,    -1,    -1,    -1,    23,    -1,    -1,
      -1,    -1,    66,    -1,    -1,    -1,    -1,    33,    34,    35,
      36,    37,    38,    39,    -1,    -1,    -1,    -1,    -1,    -1,
      46,    -1,    -1,    -1,    50
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     7,    71,    72,    73,    74,     3,     0,    73,    43,
      50,    43,    18,    20,    26,    27,    28,    74,    75,    80,
      81,    82,    83,    84,    85,     3,    89,    38,    39,    91,
      89,     4,    88,    88,    51,    80,    43,    21,    50,    46,
      48,    92,   140,   141,   141,   141,    43,    91,    86,    87,
      89,    47,    89,   136,   142,    88,   136,   138,   144,    52,
     140,    62,    62,    22,    43,    51,    86,   140,    33,    34,
      88,   126,   128,   129,    42,    47,    42,    49,     9,    23,
      35,    36,    37,    46,    50,    89,    90,    91,    92,    96,
      97,    98,    99,   100,   101,   102,   104,   105,   106,   107,
     108,   109,   110,   111,   126,    52,   126,    50,   100,    91,
      43,    52,    48,    48,    58,    66,   136,   138,    96,    46,
      89,    92,   136,   137,   139,    32,    53,    56,    57,    66,
      93,    95,   111,   112,   113,   114,   116,   118,   120,   122,
     123,   124,   125,    24,    25,    76,    77,    78,    79,    89,
      93,   103,   134,   135,    40,    41,    46,    58,    96,   111,
      89,   126,   126,   127,   126,    93,   126,   130,   131,    10,
     137,   143,    52,    42,    47,    42,    47,   112,    53,    54,
      55,   115,    56,    57,   117,    58,    59,    60,    61,   119,
      63,    64,   121,    29,    30,    31,   139,    93,    43,    62,
      51,    51,    76,    93,    42,    51,     3,    35,     3,    47,
      93,    94,    93,   126,   132,   133,    21,    42,    49,    42,
      42,    60,    96,    42,    47,    96,    93,    93,   112,   116,
     118,   120,   122,   123,   124,    62,    62,    93,    43,    51,
     134,    42,    47,    42,    60,    91,   126,    93,   130,    11,
     137,    93,    93,    93,   132,    49,    97
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    70,    71,    72,    72,    73,    74,    75,    75,    76,
      76,    76,    77,    78,    79,    80,    80,    80,    80,    80,
      80,    81,    81,    82,    83,    84,    85,    86,    87,    87,
      88,    89,    90,    91,    91,    92,    93,    94,    94,    95,
      95,    96,    96,    96,    96,    96,    96,    97,    97,    97,
      97,    97,    97,    97,    98,    99,   100,   101,   101,   102,
     102,   102,   103,   103,   104,   105,   105,   105,   105,   105,
     105,   106,   107,   107,   108,   109,   110,   111,   111,   112,
     112,   113,   113,   113,   113,   113,   114,   115,   115,   115,
     116,   116,   117,   117,   118,   118,   119,   119,   119,   119,
     120,   120,   121,   121,   122,   122,   123,   123,   124,   124,
     125,   125,   126,   127,   127,   128,   128,   128,   129,   129,
     129,   130,   130,   131,   131,   132,   132,   133,   133,   134,
     135,   135,   136,   137,   137,   138,   138,   139,   139,   139,
     140,   140,   141,   142,   142,   143,   143,   144,   144
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     3,     1,     5,     2,     3,     1,
       1,     1,     4,     4,     1,     1,     1,     1,     1,     1,
       1,     5,     6,     5,     5,     6,     5,     6,     2,     3,
       1,     1,     1,     1,     1,     2,     1,     1,     3,     3,
       3,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     3,     3,     3,     4,     6,     3,
       3,     4,     2,     3,     4,     1,     1,     1,     1,     1,
       1,     4,     3,     4,     3,     3,     3,     1,     2,     1,
       2,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     3,     1,     1,     1,     3,     1,     1,     1,     1,
       1,     3,     1,     1,     1,     3,     1,     3,     1,     3,
       1,     3,     1,     1,     3,     1,     4,     6,     1,     4,
       2,     1,     1,     1,     3,     1,     1,     1,     3,     3,
       1,     3,     2,     1,     1,     1,     1,     1,     3,     1,
       3,     1,     3,     1,     3,     1,     3,     1,     3
};


/* YYDPREC[RULE-NUM] -- Dynamic precedence of rule #RULE-NUM (0 if none).  */
static const yytype_int8 yydprec[] =
{
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0
};

/* YYMERGER[RULE-NUM] -- Index of merging function for rule #RULE-NUM.  */
static const yytype_int8 yymerger[] =
{
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0
};

/* YYIMMEDIATE[RULE-NUM] -- True iff rule #RULE-NUM is not to be deferred, as
   in the case of predicates.  */
static const yybool yyimmediate[] =
{
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0
};

/* YYCONFLP[YYPACT[STATE-NUM]] -- Pointer into YYCONFL of start of
   list of conflicting reductions corresponding to action entry for
   state STATE-NUM in yytable.  0 means no conflicts.  The list in
   yyconfl is terminated by a rule number of 0.  */
static const yytype_int8 yyconflp[] =
{
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     1,     0,     0,     0,     0,     3,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     5,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0
};

/* YYCONFL[I] -- lists of conflicting rule numbers, each terminated by
   0, pointed into by YYCONFLP.  */
static const short yyconfl[] =
{
       0,    77,     0,   104,     0,   105,     0
};


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (0)
#endif

# define YYRHSLOC(Rhs, K) ((Rhs)[K].yystate.yyloc)



#undef yynerrs
#define yynerrs (yystackp->yyerrcnt)
#undef yychar
#define yychar (yystackp->yyrawchar)
#undef yylval
#define yylval (yystackp->yyval)
#undef yylloc
#define yylloc (yystackp->yyloc)


enum { YYENOMEM = -2 };

typedef enum { yyok, yyaccept, yyabort, yyerr } YYRESULTTAG;

#define YYCHK(YYE)                              \
  do {                                          \
    YYRESULTTAG yychk_flag = YYE;               \
    if (yychk_flag != yyok)                     \
      return yychk_flag;                        \
  } while (0)

/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   SIZE_MAX < YYMAXDEPTH * sizeof (GLRStackItem)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif

/* Minimum number of free items on the stack allowed after an
   allocation.  This is to allow allocation and initialization
   to be completed by functions that call yyexpandGLRStack before the
   stack is expanded, thus insuring that all necessary pointers get
   properly redirected to new data.  */
#define YYHEADROOM 2

#ifndef YYSTACKEXPANDABLE
#  define YYSTACKEXPANDABLE 1
#endif

#if YYSTACKEXPANDABLE
# define YY_RESERVE_GLRSTACK(Yystack)                   \
  do {                                                  \
    if (Yystack->yyspaceLeft < YYHEADROOM)              \
      yyexpandGLRStack (Yystack);                       \
  } while (0)
#else
# define YY_RESERVE_GLRSTACK(Yystack)                   \
  do {                                                  \
    if (Yystack->yyspaceLeft < YYHEADROOM)              \
      yyMemoryExhausted (Yystack);                      \
  } while (0)
#endif

/** State numbers. */
typedef int yy_state_t;

/** Rule numbers. */
typedef int yyRuleNum;

/** Item references. */
typedef short yyItemNum;

typedef struct yyGLRState yyGLRState;
typedef struct yyGLRStateSet yyGLRStateSet;
typedef struct yySemanticOption yySemanticOption;
typedef union yyGLRStackItem yyGLRStackItem;
typedef struct yyGLRStack yyGLRStack;

struct yyGLRState {
  /** Type tag: always true.  */
  yybool yyisState;
  /** Type tag for yysemantics.  If true, yysval applies, otherwise
   *  yyfirstVal applies.  */
  yybool yyresolved;
  /** Number of corresponding LALR(1) machine state.  */
  yy_state_t yylrState;
  /** Preceding state in this stack */
  yyGLRState* yypred;
  /** Source position of the last token produced by my symbol */
  YYPTRDIFF_T yyposn;
  union {
    /** First in a chain of alternative reductions producing the
     *  nonterminal corresponding to this state, threaded through
     *  yynext.  */
    yySemanticOption* yyfirstVal;
    /** Semantic value for this state.  */
    YYSTYPE yysval;
  } yysemantics;
  /** Source location for this state.  */
  YYLTYPE yyloc;
};

struct yyGLRStateSet {
  yyGLRState** yystates;
  /** During nondeterministic operation, yylookaheadNeeds tracks which
   *  stacks have actually needed the current lookahead.  During deterministic
   *  operation, yylookaheadNeeds[0] is not maintained since it would merely
   *  duplicate yychar != YYEMPTY.  */
  yybool* yylookaheadNeeds;
  YYPTRDIFF_T yysize;
  YYPTRDIFF_T yycapacity;
};

struct yySemanticOption {
  /** Type tag: always false.  */
  yybool yyisState;
  /** Rule number for this reduction */
  yyRuleNum yyrule;
  /** The last RHS state in the list of states to be reduced.  */
  yyGLRState* yystate;
  /** The lookahead for this reduction.  */
  int yyrawchar;
  YYSTYPE yyval;
  YYLTYPE yyloc;
  /** Next sibling in chain of options.  To facilitate merging,
   *  options are chained in decreasing order by address.  */
  yySemanticOption* yynext;
};

/** Type of the items in the GLR stack.  The yyisState field
 *  indicates which item of the union is valid.  */
union yyGLRStackItem {
  yyGLRState yystate;
  yySemanticOption yyoption;
};

struct yyGLRStack {
  int yyerrState;
  /* To compute the location of the error token.  */
  yyGLRStackItem yyerror_range[3];

  int yyerrcnt;
  int yyrawchar;
  YYSTYPE yyval;
  YYLTYPE yyloc;

  YYJMP_BUF yyexception_buffer;
  yyGLRStackItem* yyitems;
  yyGLRStackItem* yynextFree;
  YYPTRDIFF_T yyspaceLeft;
  yyGLRState* yysplitPoint;
  yyGLRState* yylastDeleted;
  yyGLRStateSet yytops;
};

#if YYSTACKEXPANDABLE
static void yyexpandGLRStack (yyGLRStack* yystackp);
#endif

_Noreturn static void
yyFail (yyGLRStack* yystackp, YYLTYPE *yylocp, Source* source, AstNode** outp, const char* yymsg)
{
  if (yymsg != YY_NULLPTR)
    yyerror (yylocp, source, outp, yymsg);
  YYLONGJMP (yystackp->yyexception_buffer, 1);
}

_Noreturn static void
yyMemoryExhausted (yyGLRStack* yystackp)
{
  YYLONGJMP (yystackp->yyexception_buffer, 2);
}

/** Accessing symbol of state YYSTATE.  */
static inline yysymbol_kind_t
yy_accessing_symbol (yy_state_t yystate)
{
  return YY_CAST (yysymbol_kind_t, yystos[yystate]);
}

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"",
  "\"a VID (ID with first letter lowercase)\"",
  "\"a TID (ID with first letter uppercase)\"",
  "\"a HOLE (ID without any letters)\"", "\"'namespace'\"", "\"'mod'\"",
  "\"'do'\"", "\"'if'\"", "\"'then'\"", "\"'else'\"", "\"'operator'\"",
  "\"'match'\"", "\"'with'\"", "\"'return'\"", "\"'discard'\"",
  "\"'require'\"", "\"'import'\"", "\"'export'\"", "\"'link'\"",
  "\"'from'\"", "\"'as'\"", "\"'fun'\"", "\"'let'\"", "\"'set'\"",
  "\"'def'\"", "\"'type'\"", "\"'enum'\"", "\"'and'\"", "\"'xor'\"",
  "\"'or'\"", "\"'not'\"", "\"'Tuple'\"", "\"'Array'\"", "TK_DINT_LIT",
  "TK_XINT_LIT", "TK_FLOAT_LIT", "TK_DQSTRING_LIT", "TK_SQSTRING_LIT",
  "\"'.'\"", "\"':'\"", "\"','\"", "\"';'\"", "\"'::'\"", "\"':::'\"",
  "\"'('\"", "\"')'\"", "\"'['\"", "\"']'\"", "\"'{'\"", "\"'}'\"",
  "\"'->'\"", "\"'*'\"", "\"'/'\"", "\"'%'\"", "\"'+'\"", "\"'-'\"",
  "\"'<'\"", "\"'<='\"", "\"'>'\"", "\"'>='\"", "\"'='\"", "\"'=='\"",
  "\"'!='\"", "\"'$'\"", "\"'^'\"", "\"'&'\"", "\"'!'\"", "\"EOS\"",
  "$accept", "script", "scriptContent", "scriptContentStmt", "moduleStmt",
  "moduleContent", "chainPrefixStmt", "letStmt", "setStmt", "discardStmt",
  "moduleContentStmt", "defStmt", "typedefStmt", "typedefStmt_enum",
  "importStmt", "linkStmt", "linkStmtItem", "linkStmtContent", "tid",
  "vid", "floatl", "stringl", "unit", "expr", "expr_cl", "expr_cl2",
  "parenExpr", "primaryExpr", "vparen", "vtuple", "vstruct", "ifThenElse",
  "chain", "chainPrefix", "vlambda", "postfixExpr", "vtcall", "vvcall",
  "dotNmExpr", "dotIxExpr", "colonNmExpr", "castExpr", "unaryExpr",
  "unaryOp", "binaryExpr", "mulBinaryOp", "mulBinaryExpr", "addBinaryOp",
  "addBinaryExpr", "cmpBinaryOp", "cmpBinaryExpr", "eqBinaryOp",
  "eqBinaryExpr", "andBinaryExpr", "xorBinaryExpr", "orBinaryExpr",
  "typespec", "typespec_cl", "primaryTypespec", "postfixTypespec", "ttarg",
  "ttarg_cl", "vtarg", "vtarg_cl", "vstructField", "vstructField_cl",
  "vpatternField", "lpatternField", "tpatternField", "lpattern",
  "vpattern", "tpattern", "vpatternField_cl", "lpatternField_cl",
  "tpatternField_cl", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#if YYDEBUG

# ifndef YYFPRINTF
#  define YYFPRINTF fprintf
# endif

# define YY_FPRINTF                             \
  YY_IGNORE_USELESS_CAST_BEGIN YY_FPRINTF_

# define YY_FPRINTF_(Args)                      \
  do {                                          \
    YYFPRINTF Args;                             \
    YY_IGNORE_USELESS_CAST_END                  \
  } while (0)

# define YY_DPRINTF                             \
  YY_IGNORE_USELESS_CAST_BEGIN YY_DPRINTF_

# define YY_DPRINTF_(Args)                      \
  do {                                          \
    if (yydebug)                                \
      YYFPRINTF Args;                           \
    YY_IGNORE_USELESS_CAST_END                  \
  } while (0)


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

# ifndef YY_LOCATION_PRINT
#  if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static int
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  int res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += YYFPRINTF (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += YYFPRINTF (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += YYFPRINTF (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += YYFPRINTF (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += YYFPRINTF (yyo, "-%d", end_col);
    }
  return res;
 }

#   define YY_LOCATION_PRINT(File, Loc)          \
  yy_location_print_ (File, &(Loc))

#  else
#   define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#  endif
# endif /* !defined YY_LOCATION_PRINT */



/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, Source* source, AstNode** outp)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  YYUSE (yylocationp);
  YYUSE (source);
  YYUSE (outp);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, Source* source, AstNode** outp)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  YY_LOCATION_PRINT (yyo, *yylocationp);
  YYFPRINTF (yyo, ": ");
  yy_symbol_value_print (yyo, yykind, yyvaluep, yylocationp, source, outp);
  YYFPRINTF (yyo, ")");
}

# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                  \
  do {                                                                  \
    if (yydebug)                                                        \
      {                                                                 \
        YY_FPRINTF ((stderr, "%s ", Title));                            \
        yy_symbol_print (stderr, Kind, Value, Location, source, outp);        \
        YY_FPRINTF ((stderr, "\n"));                                    \
      }                                                                 \
  } while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;

static void yypstack (yyGLRStack* yystackp, YYPTRDIFF_T yyk)
  YY_ATTRIBUTE_UNUSED;
static void yypdumpstack (yyGLRStack* yystackp)
  YY_ATTRIBUTE_UNUSED;

#else /* !YYDEBUG */

# define YY_DPRINTF(Args) do {} while (yyfalse)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)

#endif /* !YYDEBUG */



/** Fill in YYVSP[YYLOW1 .. YYLOW0-1] from the chain of states starting
 *  at YYVSP[YYLOW0].yystate.yypred.  Leaves YYVSP[YYLOW1].yystate.yypred
 *  containing the pointer to the next state in the chain.  */
static void yyfillin (yyGLRStackItem *, int, int) YY_ATTRIBUTE_UNUSED;
static void
yyfillin (yyGLRStackItem *yyvsp, int yylow0, int yylow1)
{
  int i;
  yyGLRState *s = yyvsp[yylow0].yystate.yypred;
  for (i = yylow0-1; i >= yylow1; i -= 1)
    {
#if YYDEBUG
      yyvsp[i].yystate.yylrState = s->yylrState;
#endif
      yyvsp[i].yystate.yyresolved = s->yyresolved;
      if (s->yyresolved)
        yyvsp[i].yystate.yysemantics.yysval = s->yysemantics.yysval;
      else
        /* The effect of using yysval or yyloc (in an immediate rule) is
         * undefined.  */
        yyvsp[i].yystate.yysemantics.yyfirstVal = YY_NULLPTR;
      yyvsp[i].yystate.yyloc = s->yyloc;
      s = yyvsp[i].yystate.yypred = s->yypred;
    }
}


/** If yychar is empty, fetch the next token.  */
static inline yysymbol_kind_t
yygetToken (int *yycharp, yyGLRStack* yystackp, Source* source, AstNode** outp)
{
  yysymbol_kind_t yytoken;
  YYUSE (source);
  YYUSE (outp);
  if (*yycharp == YYEMPTY)
    {
      YY_DPRINTF ((stderr, "Reading a token\n"));
      *yycharp = yylex (&yylval, &yylloc, source);
    }
  if (*yycharp <= YYEOF)
    {
      *yycharp = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YY_DPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (*yycharp);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }
  return yytoken;
}

/* Do nothing if YYNORMAL or if *YYLOW <= YYLOW1.  Otherwise, fill in
 * YYVSP[YYLOW1 .. *YYLOW-1] as in yyfillin and set *YYLOW = YYLOW1.
 * For convenience, always return YYLOW1.  */
static inline int yyfill (yyGLRStackItem *, int *, int, yybool)
     YY_ATTRIBUTE_UNUSED;
static inline int
yyfill (yyGLRStackItem *yyvsp, int *yylow, int yylow1, yybool yynormal)
{
  if (!yynormal && yylow1 < *yylow)
    {
      yyfillin (yyvsp, *yylow, yylow1);
      *yylow = yylow1;
    }
  return yylow1;
}

/** Perform user action for rule number YYN, with RHS length YYRHSLEN,
 *  and top stack item YYVSP.  YYLVALP points to place to put semantic
 *  value ($$), and yylocp points to place for location information
 *  (@$).  Returns yyok for normal return, yyaccept for YYACCEPT,
 *  yyerr for YYERROR, yyabort for YYABORT.  */
static YYRESULTTAG
yyuserAction (yyRuleNum yyn, int yyrhslen, yyGLRStackItem* yyvsp,
              yyGLRStack* yystackp,
              YYSTYPE* yyvalp, YYLTYPE *yylocp, Source* source, AstNode** outp)
{
  yybool yynormal YY_ATTRIBUTE_UNUSED = yystackp->yysplitPoint == YY_NULLPTR;
  int yylow;
  YYUSE (yyvalp);
  YYUSE (yylocp);
  YYUSE (source);
  YYUSE (outp);
  YYUSE (yyrhslen);
# undef yyerrok
# define yyerrok (yystackp->yyerrState = 0)
# undef YYACCEPT
# define YYACCEPT return yyaccept
# undef YYABORT
# define YYABORT return yyabort
# undef YYERROR
# define YYERROR return yyerrok, yyerr
# undef YYRECOVERING
# define YYRECOVERING() (yystackp->yyerrState != 0)
# undef yyclearin
# define yyclearin (yychar = YYEMPTY)
# undef YYFILL
# define YYFILL(N) yyfill (yyvsp, &yylow, (N), yynormal)
# undef YYBACKUP
# define YYBACKUP(Token, Value)                                              \
  return yyerror (yylocp, source, outp, YY_("syntax error: cannot back up")),     \
         yyerrok, yyerr

  yylow = 1;
  if (yyrhslen == 0)
    *yyvalp = yyval_default;
  else
    *yyvalp = yyvsp[YYFILL (1-yyrhslen)].yystate.yysemantics.yysval;
  /* Default location. */
  YYLLOC_DEFAULT ((*yylocp), (yyvsp - yyrhslen), yyrhslen);
  yystackp->yyerror_range[1].yystate.yyloc = *yylocp;

  switch (yyn)
    {
  case 2: /* script: scriptContent  */
#line 231 "parser.yy"
                    { ((*yyvalp).nt) = NewAstScriptWithModulesSb((*yylocp), source, (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ntSb)); *outp = ((*yyvalp).nt); }
#line 1449 "parser.tab.c"
    break;

  case 3: /* scriptContent: scriptContentStmt "';'"  */
#line 234 "parser.yy"
                                                       { ((*yyvalp).ntSb) = NULL; sb_push(((*yyvalp).ntSb),(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.nt)); }
#line 1455 "parser.tab.c"
    break;

  case 4: /* scriptContent: scriptContent scriptContentStmt "';'"  */
#line 235 "parser.yy"
                                                       { ((*yyvalp).ntSb) = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ntSb); sb_push(((*yyvalp).ntSb),(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.nt)); }
#line 1461 "parser.tab.c"
    break;

  case 5: /* scriptContentStmt: moduleStmt  */
#line 238 "parser.yy"
                    { ((*yyvalp).nt) = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.nt); }
#line 1467 "parser.tab.c"
    break;

  case 6: /* moduleStmt: "'mod'" "a VID (ID with first letter lowercase)" "'{'" moduleContent "'}'"  */
#line 246 "parser.yy"
                                                            { ((*yyvalp).nt) = NewAstModuleStmtWithStmtSb((*yylocp), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.token).ID_symbolID, (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ntSb)); }
#line 1473 "parser.tab.c"
    break;

  case 7: /* moduleContent: moduleContentStmt "';'"  */
#line 249 "parser.yy"
                                                       { ((*yyvalp).ntSb) = NULL; sb_push(((*yyvalp).ntSb), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.nt)); }
#line 1479 "parser.tab.c"
    break;

  case 8: /* moduleContent: moduleContent moduleContentStmt "';'"  */
#line 250 "parser.yy"
                                                       { ((*yyvalp).ntSb) = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ntSb); sb_push(((*yyvalp).ntSb), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.nt)); }
#line 1485 "parser.tab.c"
    break;

  case 9: /* chainPrefixStmt: letStmt  */
#line 258 "parser.yy"
                    { ((*yyvalp).nt) = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.nt); }
#line 1491 "parser.tab.c"
    break;

  case 10: /* chainPrefixStmt: setStmt  */
#line 259 "parser.yy"
                    { ((*yyvalp).nt) = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.nt); }
#line 1497 "parser.tab.c"
    break;

  case 11: /* chainPrefixStmt: discardStmt  */
#line 260 "parser.yy"
                    { ((*yyvalp).nt) = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.nt); }
#line 1503 "parser.tab.c"
    break;

  case 12: /* letStmt: "'let'" lpattern "'='" expr  */
#line 263 "parser.yy"
                                        { ((*yyvalp).nt) = NewAstLetStmt((*yylocp), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.nt), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.nt)); }
#line 1509 "parser.tab.c"
    break;

  case 13: /* setStmt: "'set'" expr "'='" expr  */
#line 266 "parser.yy"
                                    { ((*yyvalp).nt) = NewAstSetStmt((*yylocp), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.nt), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.nt)); }
#line 1515 "parser.tab.c"
    break;

  case 14: /* discardStmt: expr  */
#line 269 "parser.yy"
              { ((*yyvalp).nt) = NewAstDiscardStmt((*yylocp), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.nt)); }
#line 1521 "parser.tab.c"
    break;

  case 15: /* moduleContentStmt: defStmt  */
#line 273 "parser.yy"
                            { ((*yyvalp).nt) = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.nt); }
#line 1527 "parser.tab.c"
    break;

  case 16: /* moduleContentStmt: typedefStmt  */
#line 274 "parser.yy"
                            { ((*yyvalp).nt) = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.nt); }
#line 1533 "parser.tab.c"
    break;

  case 17: /* moduleContentStmt: typedefStmt_enum  */
#line 275 "parser.yy"
                            { ((*yyvalp).nt) = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.nt); }
#line 1539 "parser.tab.c"
    break;

  case 18: /* moduleContentStmt: importStmt  */
#line 276 "parser.yy"
                            { ((*yyvalp).nt) = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.nt); }
#line 1545 "parser.tab.c"
    break;

  case 19: /* moduleContentStmt: linkStmt  */
#line 277 "parser.yy"
                            { ((*yyvalp).nt) = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.nt); }
#line 1551 "parser.tab.c"
    break;

  case 20: /* moduleContentStmt: moduleStmt  */
#line 278 "parser.yy"
                            { ((*yyvalp).nt) = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.nt); }
#line 1557 "parser.tab.c"
    break;

  case 21: /* defStmt: "'def'" vid vpattern "'->'" castExpr  */
#line 281 "parser.yy"
                                                          { ((*yyvalp).nt) = NewAstDefStmt((*yylocp), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.token).ID_symbolID, NULL, (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.nt), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.nt)); }
#line 1563 "parser.tab.c"
    break;

  case 22: /* defStmt: "'def'" vid tpattern vpattern "'->'" castExpr  */
#line 282 "parser.yy"
                                                          { ((*yyvalp).nt) = NewAstDefStmt((*yylocp), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval.token).ID_symbolID, (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.nt),   (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.nt), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.nt)); }
#line 1569 "parser.tab.c"
    break;

  case 23: /* typedefStmt: "'type'" tid tpattern "'='" typespec  */
#line 285 "parser.yy"
                                                 { ((*yyvalp).nt) = NewAstTypedefStmt((*yylocp), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.token).ID_symbolID, (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.nt), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.nt)); }
#line 1575 "parser.tab.c"
    break;

  case 24: /* typedefStmt_enum: "'enum'" tid tpattern "'='" vstruct  */
#line 288 "parser.yy"
                                               { ((*yyvalp).nt) = NewAstTypedefEnumStmt((*yylocp), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.token).ID_symbolID, (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.nt), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.nt)); }
#line 1581 "parser.tab.c"
    break;

  case 25: /* importStmt: "'import'" vid "'from'" stringl "'as'" stringl  */
#line 292 "parser.yy"
                                                            { ((*yyvalp).nt) = NewAstImportStmt((*yylocp), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval.token).ID_symbolID, (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.token).String_utf8string, (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token).String_utf8string); }
#line 1587 "parser.tab.c"
    break;

  case 26: /* linkStmt: "'link'" stringl "'{'" linkStmtContent "'}'"  */
#line 296 "parser.yy"
                                                               { ((*yyvalp).nt) = NewAstLinkStmt((*yylocp), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.token).String_utf8string, (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ntSb)); }
#line 1593 "parser.tab.c"
    break;

  case 27: /* linkStmtItem: vid vpattern "'->'" typespec "'from'" stringl  */
#line 299 "parser.yy"
                                                            { ((*yyvalp).nt) = NewAstLinkStmtItem((*yylocp), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-5)].yystate.yysemantics.yysval.token).ID_symbolID, (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval.nt), NewAstType2Val((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yyloc),(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.nt)), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token).String_utf8string); }
#line 1599 "parser.tab.c"
    break;

  case 28: /* linkStmtContent: linkStmtItem "';'"  */
#line 302 "parser.yy"
                                                    { ((*yyvalp).ntSb) = NULL; sb_push(((*yyvalp).ntSb),(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.nt)); }
#line 1605 "parser.tab.c"
    break;

  case 29: /* linkStmtContent: linkStmtContent linkStmtItem "';'"  */
#line 303 "parser.yy"
                                                    { ((*yyvalp).ntSb) = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ntSb); sb_push(((*yyvalp).ntSb),(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.nt)); }
#line 1611 "parser.tab.c"
    break;

  case 30: /* tid: "a TID (ID with first letter uppercase)"  */
#line 310 "parser.yy"
                { ((*yyvalp).token) = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token); }
#line 1617 "parser.tab.c"
    break;

  case 31: /* vid: "a VID (ID with first letter lowercase)"  */
#line 311 "parser.yy"
                { ((*yyvalp).token) = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token); }
#line 1623 "parser.tab.c"
    break;

  case 32: /* floatl: TK_FLOAT_LIT  */
#line 313 "parser.yy"
                    { ((*yyvalp).token) = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token); }
#line 1629 "parser.tab.c"
    break;

  case 33: /* stringl: TK_SQSTRING_LIT  */
#line 316 "parser.yy"
                        { ((*yyvalp).token) = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token); }
#line 1635 "parser.tab.c"
    break;

  case 34: /* stringl: TK_DQSTRING_LIT  */
#line 317 "parser.yy"
                        { ((*yyvalp).token) = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token); }
#line 1641 "parser.tab.c"
    break;

  case 35: /* unit: "'('" "')'"  */
#line 320 "parser.yy"
                            { ((*yyvalp).nt) = NewAstUnit((*yylocp)); }
#line 1647 "parser.tab.c"
    break;

  case 36: /* expr: binaryExpr  */
#line 327 "parser.yy"
                    { ((*yyvalp).nt) = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.nt); }
#line 1653 "parser.tab.c"
    break;

  case 37: /* expr_cl: expr  */
#line 330 "parser.yy"
                                { ((*yyvalp).ntSb) = NULL; sb_push((((*yyvalp).ntSb)),(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.nt)); }
#line 1659 "parser.tab.c"
    break;

  case 38: /* expr_cl: expr_cl "','" expr  */
#line 331 "parser.yy"
                                { ((*yyvalp).ntSb) = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ntSb); sb_push((((*yyvalp).ntSb)),(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.nt)); }
#line 1665 "parser.tab.c"
    break;

  case 39: /* expr_cl2: expr "','" expr  */
#line 334 "parser.yy"
                                 { ((*yyvalp).ntSb) = NULL; sb_push(((*yyvalp).ntSb),(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.nt)); sb_push(((*yyvalp).ntSb),(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.nt)); }
#line 1671 "parser.tab.c"
    break;

  case 40: /* expr_cl2: expr_cl2 "','" expr  */
#line 335 "parser.yy"
                                 { ((*yyvalp).ntSb) = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ntSb); sb_push(((*yyvalp).ntSb),(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.nt)); }
#line 1677 "parser.tab.c"
    break;

  case 41: /* parenExpr: unit  */
#line 339 "parser.yy"
                    { ((*yyvalp).nt) = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.nt); }
#line 1683 "parser.tab.c"
    break;

  case 42: /* parenExpr: vparen  */
#line 340 "parser.yy"
                    { ((*yyvalp).nt) = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.nt); }
#line 1689 "parser.tab.c"
    break;

  case 43: /* parenExpr: vtuple  */
#line 341 "parser.yy"
                    { ((*yyvalp).nt) = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.nt); }
#line 1695 "parser.tab.c"
    break;

  case 44: /* parenExpr: vstruct  */
#line 342 "parser.yy"
                    { ((*yyvalp).nt) = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.nt); }
#line 1701 "parser.tab.c"
    break;

  case 45: /* parenExpr: chain  */
#line 343 "parser.yy"
                    { ((*yyvalp).nt) = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.nt); }
#line 1707 "parser.tab.c"
    break;

  case 46: /* parenExpr: vlambda  */
#line 344 "parser.yy"
                    { ((*yyvalp).nt) = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.nt); }
#line 1713 "parser.tab.c"
    break;

  case 47: /* primaryExpr: parenExpr  */
#line 347 "parser.yy"
                    { ((*yyvalp).nt) = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.nt); }
#line 1719 "parser.tab.c"
    break;

  case 48: /* primaryExpr: vid  */
#line 348 "parser.yy"
                    { ((*yyvalp).nt) = NewAstVID((*yylocp), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token).ID_symbolID); }
#line 1725 "parser.tab.c"
    break;

  case 49: /* primaryExpr: TK_DINT_LIT  */
#line 349 "parser.yy"
                    { ((*yyvalp).nt) = NewAstIntLiteral((*yylocp), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token).Int, 10); }
#line 1731 "parser.tab.c"
    break;

  case 50: /* primaryExpr: TK_XINT_LIT  */
#line 350 "parser.yy"
                    { ((*yyvalp).nt) = NewAstIntLiteral((*yylocp), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token).Int, 16); }
#line 1737 "parser.tab.c"
    break;

  case 51: /* primaryExpr: floatl  */
#line 351 "parser.yy"
                    { ((*yyvalp).nt) = NewAstFloatLiteral((*yylocp), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token).Float); }
#line 1743 "parser.tab.c"
    break;

  case 52: /* primaryExpr: stringl  */
#line 352 "parser.yy"
                    { ((*yyvalp).nt) = NewAstStringLiteral((*yylocp), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token).String_utf8string); }
#line 1749 "parser.tab.c"
    break;

  case 53: /* primaryExpr: ifThenElse  */
#line 353 "parser.yy"
                    { ((*yyvalp).nt) = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.nt); }
#line 1755 "parser.tab.c"
    break;

  case 54: /* vparen: "'('" expr "')'"  */
#line 356 "parser.yy"
                                { ((*yyvalp).nt) = NewAstVParen((*yylocp), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.nt)); }
#line 1761 "parser.tab.c"
    break;

  case 55: /* vtuple: "'('" expr_cl2 "')'"  */
#line 359 "parser.yy"
                                        { ((*yyvalp).nt) = NewAstVTupleWithFieldsSb((*yylocp), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ntSb)); }
#line 1767 "parser.tab.c"
    break;

  case 56: /* vstruct: "'{'" vstructField_cl "'}'"  */
#line 362 "parser.yy"
                                              { ((*yyvalp).nt) = NewAstVStructWithFieldsSb((*yylocp), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ntSb)); }
#line 1773 "parser.tab.c"
    break;

  case 57: /* ifThenElse: "'if'" parenExpr "'then'" parenExpr  */
#line 365 "parser.yy"
                                                                     { ((*yyvalp).nt) = NewAstIte((*yylocp), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.nt), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.nt), NULL); }
#line 1779 "parser.tab.c"
    break;

  case 58: /* ifThenElse: "'if'" parenExpr "'then'" parenExpr "'else'" primaryExpr  */
#line 366 "parser.yy"
                                                                     { ((*yyvalp).nt) = NewAstIte((*yylocp), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval.nt), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.nt), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.nt)); }
#line 1785 "parser.tab.c"
    break;

  case 59: /* chain: "'{'" expr "'}'"  */
#line 369 "parser.yy"
                                                { ((*yyvalp).nt) = NewAstChainWith((*yylocp), NULL, (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.nt)); }
#line 1791 "parser.tab.c"
    break;

  case 60: /* chain: "'{'" chainPrefix "'}'"  */
#line 370 "parser.yy"
                                                { ((*yyvalp).nt) = NewAstChainWith((*yylocp), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ntSb), NULL); }
#line 1797 "parser.tab.c"
    break;

  case 61: /* chain: "'{'" chainPrefix expr "'}'"  */
#line 371 "parser.yy"
                                                { ((*yyvalp).nt) = NewAstChainWith((*yylocp), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ntSb), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.nt)); }
#line 1803 "parser.tab.c"
    break;

  case 62: /* chainPrefix: chainPrefixStmt "';'"  */
#line 374 "parser.yy"
                                                { ((*yyvalp).ntSb) = NULL; sb_push((((*yyvalp).ntSb)),(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.nt)); }
#line 1809 "parser.tab.c"
    break;

  case 63: /* chainPrefix: chainPrefix chainPrefixStmt "';'"  */
#line 375 "parser.yy"
                                                { ((*yyvalp).ntSb) = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ntSb); sb_push((((*yyvalp).ntSb)),(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.nt)); }
#line 1815 "parser.tab.c"
    break;

  case 64: /* vlambda: "'fun'" lpattern "'->'" parenExpr  */
#line 378 "parser.yy"
                                              { ((*yyvalp).nt) = NULL; }
#line 1821 "parser.tab.c"
    break;

  case 65: /* postfixExpr: primaryExpr  */
#line 382 "parser.yy"
                    { ((*yyvalp).nt) = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.nt); }
#line 1827 "parser.tab.c"
    break;

  case 66: /* postfixExpr: vtcall  */
#line 383 "parser.yy"
                    { ((*yyvalp).nt) = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.nt); }
#line 1833 "parser.tab.c"
    break;

  case 67: /* postfixExpr: vvcall  */
#line 384 "parser.yy"
                    { ((*yyvalp).nt) = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.nt); }
#line 1839 "parser.tab.c"
    break;

  case 68: /* postfixExpr: dotNmExpr  */
#line 385 "parser.yy"
                    { ((*yyvalp).nt) = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.nt); }
#line 1845 "parser.tab.c"
    break;

  case 69: /* postfixExpr: dotIxExpr  */
#line 386 "parser.yy"
                    { ((*yyvalp).nt) = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.nt); }
#line 1851 "parser.tab.c"
    break;

  case 70: /* postfixExpr: colonNmExpr  */
#line 387 "parser.yy"
                    { ((*yyvalp).nt) = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.nt); }
#line 1857 "parser.tab.c"
    break;

  case 71: /* vtcall: postfixExpr "'<'" vtarg_cl "'>'"  */
#line 390 "parser.yy"
                                                { ((*yyvalp).nt) = NewAstTCallWithArgsSb((*yylocp), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.nt), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ntSb)); }
#line 1863 "parser.tab.c"
    break;

  case 72: /* vvcall: postfixExpr "'('" "')'"  */
#line 393 "parser.yy"
                                                { ((*yyvalp).nt) = NewAstVCallWithArgsSb((*yylocp), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.nt), NULL); }
#line 1869 "parser.tab.c"
    break;

  case 73: /* vvcall: postfixExpr "'('" expr_cl "')'"  */
#line 394 "parser.yy"
                                                { ((*yyvalp).nt) = NewAstVCallWithArgsSb((*yylocp), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.nt), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ntSb)); }
#line 1875 "parser.tab.c"
    break;

  case 74: /* dotNmExpr: postfixExpr "'.'" "a VID (ID with first letter lowercase)"  */
#line 397 "parser.yy"
                                        { ((*yyvalp).nt) = NewAstDotName((*yylocp), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.nt), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token).ID_symbolID); }
#line 1881 "parser.tab.c"
    break;

  case 75: /* dotIxExpr: postfixExpr "'.'" TK_DINT_LIT  */
#line 400 "parser.yy"
                                        { ((*yyvalp).nt) = NewAstDotIndex((*yylocp), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.nt), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token).Int); }
#line 1887 "parser.tab.c"
    break;

  case 76: /* colonNmExpr: postfixExpr "':'" "a VID (ID with first letter lowercase)"  */
#line 403 "parser.yy"
                                        { ((*yyvalp).nt) = NewAstColonName((*yylocp), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.nt), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token).ID_symbolID); }
#line 1893 "parser.tab.c"
    break;

  case 77: /* castExpr: postfixExpr  */
#line 407 "parser.yy"
                         { ((*yyvalp).nt) = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.nt); }
#line 1899 "parser.tab.c"
    break;

  case 78: /* castExpr: typespec parenExpr  */
#line 408 "parser.yy"
                         { ((*yyvalp).nt) = NewAstVCast((*yylocp), NewAstType2Val((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yyloc),(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.nt)), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.nt)); }
#line 1905 "parser.tab.c"
    break;

  case 79: /* unaryExpr: castExpr  */
#line 412 "parser.yy"
                            { ((*yyvalp).nt) = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.nt); }
#line 1911 "parser.tab.c"
    break;

  case 80: /* unaryExpr: unaryOp unaryExpr  */
#line 413 "parser.yy"
                            { ((*yyvalp).nt) = NewAstUnary((*yylocp), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.uop), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.nt)); }
#line 1917 "parser.tab.c"
    break;

  case 81: /* unaryOp: "'+'"  */
#line 416 "parser.yy"
                    { ((*yyvalp).uop) = UOP_PLUS; }
#line 1923 "parser.tab.c"
    break;

  case 82: /* unaryOp: "'-'"  */
#line 417 "parser.yy"
                    { ((*yyvalp).uop) = UOP_MINUS; }
#line 1929 "parser.tab.c"
    break;

  case 83: /* unaryOp: "'*'"  */
#line 418 "parser.yy"
                    { ((*yyvalp).uop) = UOP_DEREF; }
#line 1935 "parser.tab.c"
    break;

  case 84: /* unaryOp: "'^'"  */
#line 419 "parser.yy"
                    { ((*yyvalp).uop) = UOP_GETREF; }
#line 1941 "parser.tab.c"
    break;

  case 85: /* unaryOp: "'not'"  */
#line 420 "parser.yy"
                    { ((*yyvalp).uop) = UOP_NOT; }
#line 1947 "parser.tab.c"
    break;

  case 86: /* binaryExpr: orBinaryExpr  */
#line 424 "parser.yy"
                    { ((*yyvalp).nt) = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.nt); }
#line 1953 "parser.tab.c"
    break;

  case 87: /* mulBinaryOp: "'*'"  */
#line 427 "parser.yy"
                    { ((*yyvalp).bop) = BOP_MUL; }
#line 1959 "parser.tab.c"
    break;

  case 88: /* mulBinaryOp: "'/'"  */
#line 428 "parser.yy"
                    { ((*yyvalp).bop) = BOP_DIV; }
#line 1965 "parser.tab.c"
    break;

  case 89: /* mulBinaryOp: "'%'"  */
#line 429 "parser.yy"
                    { ((*yyvalp).bop) = BOP_REM; }
#line 1971 "parser.tab.c"
    break;

  case 90: /* mulBinaryExpr: unaryExpr  */
#line 432 "parser.yy"
                                            { ((*yyvalp).nt) = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.nt); }
#line 1977 "parser.tab.c"
    break;

  case 91: /* mulBinaryExpr: mulBinaryExpr mulBinaryOp unaryExpr  */
#line 433 "parser.yy"
                                            { ((*yyvalp).nt) = NewAstBinary((*yylocp), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.bop), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.nt), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.nt)); }
#line 1983 "parser.tab.c"
    break;

  case 92: /* addBinaryOp: "'+'"  */
#line 436 "parser.yy"
                { ((*yyvalp).bop) = BOP_ADD; }
#line 1989 "parser.tab.c"
    break;

  case 93: /* addBinaryOp: "'-'"  */
#line 437 "parser.yy"
                { ((*yyvalp).bop) = BOP_SUBTRACT; }
#line 1995 "parser.tab.c"
    break;

  case 94: /* addBinaryExpr: mulBinaryExpr  */
#line 440 "parser.yy"
                                                { ((*yyvalp).nt) = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.nt); }
#line 2001 "parser.tab.c"
    break;

  case 95: /* addBinaryExpr: addBinaryExpr addBinaryOp mulBinaryExpr  */
#line 441 "parser.yy"
                                                { ((*yyvalp).nt) = NewAstBinary((*yylocp), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.bop), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.nt), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.nt)); }
#line 2007 "parser.tab.c"
    break;

  case 96: /* cmpBinaryOp: "'<'"  */
#line 444 "parser.yy"
                    { ((*yyvalp).bop) = BOP_LTHAN; }
#line 2013 "parser.tab.c"
    break;

  case 97: /* cmpBinaryOp: "'<='"  */
#line 445 "parser.yy"
                    { ((*yyvalp).bop) = BOP_LETHAN; }
#line 2019 "parser.tab.c"
    break;

  case 98: /* cmpBinaryOp: "'>'"  */
#line 446 "parser.yy"
                    { ((*yyvalp).bop) = BOP_GTHAN; }
#line 2025 "parser.tab.c"
    break;

  case 99: /* cmpBinaryOp: "'>='"  */
#line 447 "parser.yy"
                    { ((*yyvalp).bop) = BOP_GETHAN; }
#line 2031 "parser.tab.c"
    break;

  case 100: /* cmpBinaryExpr: addBinaryExpr  */
#line 450 "parser.yy"
                                                { ((*yyvalp).nt) = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.nt); }
#line 2037 "parser.tab.c"
    break;

  case 101: /* cmpBinaryExpr: cmpBinaryExpr cmpBinaryOp addBinaryExpr  */
#line 451 "parser.yy"
                                                { ((*yyvalp).nt) = NewAstBinary((*yylocp), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.bop), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.nt), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.nt)); }
#line 2043 "parser.tab.c"
    break;

  case 102: /* eqBinaryOp: "'=='"  */
#line 454 "parser.yy"
                    { ((*yyvalp).bop) = BOP_EQUALS; }
#line 2049 "parser.tab.c"
    break;

  case 103: /* eqBinaryOp: "'!='"  */
#line 455 "parser.yy"
                    { ((*yyvalp).bop) = BOP_NEQUALS; }
#line 2055 "parser.tab.c"
    break;

  case 104: /* eqBinaryExpr: cmpBinaryExpr  */
#line 458 "parser.yy"
                                            { ((*yyvalp).nt) = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.nt); }
#line 2061 "parser.tab.c"
    break;

  case 105: /* eqBinaryExpr: eqBinaryExpr eqBinaryOp cmpBinaryExpr  */
#line 459 "parser.yy"
                                            { ((*yyvalp).nt) = NewAstBinary((*yylocp), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.bop), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.nt), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.nt)); }
#line 2067 "parser.tab.c"
    break;

  case 106: /* andBinaryExpr: eqBinaryExpr  */
#line 462 "parser.yy"
                                            { ((*yyvalp).nt) = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.nt); }
#line 2073 "parser.tab.c"
    break;

  case 107: /* andBinaryExpr: andBinaryExpr "'and'" eqBinaryExpr  */
#line 463 "parser.yy"
                                            { ((*yyvalp).nt) = NewAstBinary((*yylocp), BOP_AND, (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.nt), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.nt)); }
#line 2079 "parser.tab.c"
    break;

  case 108: /* xorBinaryExpr: andBinaryExpr  */
#line 466 "parser.yy"
                                            { ((*yyvalp).nt) = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.nt); }
#line 2085 "parser.tab.c"
    break;

  case 109: /* xorBinaryExpr: xorBinaryExpr "'xor'" andBinaryExpr  */
#line 467 "parser.yy"
                                            { ((*yyvalp).nt) = NewAstBinary((*yylocp), BOP_XOR, (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.nt), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.nt)); }
#line 2091 "parser.tab.c"
    break;

  case 110: /* orBinaryExpr: xorBinaryExpr  */
#line 470 "parser.yy"
                                            { ((*yyvalp).nt) = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.nt); }
#line 2097 "parser.tab.c"
    break;

  case 111: /* orBinaryExpr: orBinaryExpr "'or'" xorBinaryExpr  */
#line 471 "parser.yy"
                                            { ((*yyvalp).nt) = NewAstBinary((*yylocp), BOP_OR, (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.nt), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.nt)); }
#line 2103 "parser.tab.c"
    break;

  case 112: /* typespec: postfixTypespec  */
#line 479 "parser.yy"
                       { ((*yyvalp).nt) = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.nt); }
#line 2109 "parser.tab.c"
    break;

  case 113: /* typespec_cl: typespec  */
#line 482 "parser.yy"
                                    { ((*yyvalp).ntSb) = NULL; sb_push(((*yyvalp).ntSb),(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.nt)); }
#line 2115 "parser.tab.c"
    break;

  case 114: /* typespec_cl: typespec_cl "','" typespec  */
#line 483 "parser.yy"
                                    { ((*yyvalp).ntSb) = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ntSb); sb_push(((*yyvalp).ntSb),(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.nt)); }
#line 2121 "parser.tab.c"
    break;

  case 115: /* primaryTypespec: tid  */
#line 487 "parser.yy"
                                                                { ((*yyvalp).nt) = NewAstTID((*yylocp), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token).ID_symbolID); }
#line 2127 "parser.tab.c"
    break;

  case 116: /* primaryTypespec: "'Tuple'" "'['" typespec_cl "']'"  */
#line 488 "parser.yy"
                                                                { ((*yyvalp).nt) = NewAstTTupleWithFieldsSb((*yylocp),(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ntSb)); }
#line 2133 "parser.tab.c"
    break;

  case 117: /* primaryTypespec: "'Array'" "'['" typespec "','" expr "']'"  */
#line 489 "parser.yy"
                                                                { ((*yyvalp).nt) = NewAstTArray((*yylocp),(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.nt),NewAstVal2Type((*yylocp),(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.nt))); }
#line 2139 "parser.tab.c"
    break;

  case 118: /* postfixTypespec: primaryTypespec  */
#line 492 "parser.yy"
                                                  { ((*yyvalp).nt) = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.nt); }
#line 2145 "parser.tab.c"
    break;

  case 119: /* postfixTypespec: postfixTypespec "'<'" ttarg_cl "'>'"  */
#line 493 "parser.yy"
                                                  { ((*yyvalp).nt) = NewAstTCallWithArgsSb((*yylocp), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.nt), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ntSb)); }
#line 2151 "parser.tab.c"
    break;

  case 120: /* postfixTypespec: postfixTypespec "'^'"  */
#line 494 "parser.yy"
                                                  { ((*yyvalp).nt) = NewAstTPtr((*yylocp), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.nt)); }
#line 2157 "parser.tab.c"
    break;

  case 121: /* ttarg: typespec  */
#line 503 "parser.yy"
                { ((*yyvalp).nt) = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.nt); }
#line 2163 "parser.tab.c"
    break;

  case 122: /* ttarg: expr  */
#line 504 "parser.yy"
                { ((*yyvalp).nt) = NewAstVal2Type((*yylocp),(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.nt)); }
#line 2169 "parser.tab.c"
    break;

  case 123: /* ttarg_cl: ttarg  */
#line 507 "parser.yy"
                                { ((*yyvalp).ntSb) = NULL; sb_push(((*yyvalp).ntSb),(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.nt)); }
#line 2175 "parser.tab.c"
    break;

  case 124: /* ttarg_cl: ttarg_cl "','" ttarg  */
#line 508 "parser.yy"
                                { ((*yyvalp).ntSb) = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ntSb); sb_push(((*yyvalp).ntSb),(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.nt)); }
#line 2181 "parser.tab.c"
    break;

  case 125: /* vtarg: typespec  */
#line 513 "parser.yy"
               { ((*yyvalp).nt) = NewAstType2Val((*yylocp),(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.nt)); }
#line 2187 "parser.tab.c"
    break;

  case 126: /* vtarg: expr  */
#line 514 "parser.yy"
               { ((*yyvalp).nt) = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.nt); }
#line 2193 "parser.tab.c"
    break;

  case 127: /* vtarg_cl: vtarg  */
#line 517 "parser.yy"
                                { ((*yyvalp).ntSb) = NULL; sb_push(((*yyvalp).ntSb),(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.nt)); }
#line 2199 "parser.tab.c"
    break;

  case 128: /* vtarg_cl: vtarg_cl "','" vtarg  */
#line 518 "parser.yy"
                                { ((*yyvalp).ntSb) = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ntSb); sb_push(((*yyvalp).ntSb),(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.nt)); }
#line 2205 "parser.tab.c"
    break;

  case 129: /* vstructField: vid "'='" expr  */
#line 526 "parser.yy"
                       { ((*yyvalp).nt) = NewAstField((*yylocp), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.token).ID_symbolID, (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.nt)); }
#line 2211 "parser.tab.c"
    break;

  case 130: /* vstructField_cl: vstructField  */
#line 529 "parser.yy"
                                            { ((*yyvalp).ntSb) = NULL; sb_push(((*yyvalp).ntSb),(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.nt)); }
#line 2217 "parser.tab.c"
    break;

  case 131: /* vstructField_cl: vstructField_cl "','" vstructField  */
#line 530 "parser.yy"
                                            { ((*yyvalp).ntSb) = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ntSb); sb_push(((*yyvalp).ntSb),(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.nt)); }
#line 2223 "parser.tab.c"
    break;

  case 132: /* vpatternField: vid typespec  */
#line 533 "parser.yy"
                   { ((*yyvalp).nt) = NewAstField((*yylocp), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.token).ID_symbolID, NewAstType2Val((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yyloc),(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.nt))); }
#line 2229 "parser.tab.c"
    break;

  case 133: /* lpatternField: vpatternField  */
#line 536 "parser.yy"
                    { ((*yyvalp).nt) = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.nt); }
#line 2235 "parser.tab.c"
    break;

  case 134: /* lpatternField: vid  */
#line 537 "parser.yy"
                    { ((*yyvalp).nt) = NewAstField((*yylocp), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token).ID_symbolID, NULL); }
#line 2241 "parser.tab.c"
    break;

  case 135: /* tpatternField: tid  */
#line 540 "parser.yy"
                    { ((*yyvalp).nt) = NewAstField((*yylocp), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token).ID_symbolID, NULL); }
#line 2247 "parser.tab.c"
    break;

  case 136: /* tpatternField: vpatternField  */
#line 541 "parser.yy"
                    { ((*yyvalp).nt) = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.nt); }
#line 2253 "parser.tab.c"
    break;

  case 137: /* lpattern: lpatternField  */
#line 544 "parser.yy"
                                            { ((*yyvalp).nt) = NewAstVPatternSingleton((*yylocp),(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.nt)); }
#line 2259 "parser.tab.c"
    break;

  case 138: /* lpattern: "'('" lpatternField_cl "')'"  */
#line 545 "parser.yy"
                                            { ((*yyvalp).nt) = NewAstVPatternWithFieldsSb((*yylocp),(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ntSb)); }
#line 2265 "parser.tab.c"
    break;

  case 139: /* lpattern: unit  */
#line 546 "parser.yy"
                                            { ((*yyvalp).nt) = NewAstVPatternWithFieldsSb((*yylocp),NULL); }
#line 2271 "parser.tab.c"
    break;

  case 140: /* vpattern: "'('" vpatternField_cl "')'"  */
#line 549 "parser.yy"
                                            { ((*yyvalp).nt) = NewAstVPatternWithFieldsSb((*yylocp),(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ntSb)); }
#line 2277 "parser.tab.c"
    break;

  case 141: /* vpattern: unit  */
#line 550 "parser.yy"
                                            { ((*yyvalp).nt) = NewAstVPatternWithFieldsSb((*yylocp),NULL); }
#line 2283 "parser.tab.c"
    break;

  case 142: /* tpattern: "'['" tpatternField_cl "']'"  */
#line 553 "parser.yy"
                                            { ((*yyvalp).nt) = NewAstVPatternWithFieldsSb((*yylocp),(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ntSb)); }
#line 2289 "parser.tab.c"
    break;

  case 143: /* vpatternField_cl: vpatternField  */
#line 556 "parser.yy"
                                                { ((*yyvalp).ntSb) = NULL; sb_push(((*yyvalp).ntSb),(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.nt)); }
#line 2295 "parser.tab.c"
    break;

  case 144: /* vpatternField_cl: vpatternField_cl "','" vpatternField  */
#line 557 "parser.yy"
                                                { ((*yyvalp).ntSb) = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ntSb); sb_push(((*yyvalp).ntSb),(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.nt)); }
#line 2301 "parser.tab.c"
    break;

  case 145: /* lpatternField_cl: lpatternField  */
#line 560 "parser.yy"
                                                { ((*yyvalp).ntSb) = NULL; sb_push(((*yyvalp).ntSb),(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.nt)); }
#line 2307 "parser.tab.c"
    break;

  case 146: /* lpatternField_cl: lpatternField_cl "','" lpatternField  */
#line 561 "parser.yy"
                                                { ((*yyvalp).ntSb) = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ntSb); sb_push(((*yyvalp).ntSb),(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.nt)); }
#line 2313 "parser.tab.c"
    break;

  case 147: /* tpatternField_cl: tpatternField  */
#line 564 "parser.yy"
                                                { ((*yyvalp).ntSb) = NULL; sb_push(((*yyvalp).ntSb),(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.nt)); }
#line 2319 "parser.tab.c"
    break;

  case 148: /* tpatternField_cl: tpatternField_cl "','" tpatternField  */
#line 565 "parser.yy"
                                                { ((*yyvalp).ntSb) = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ntSb); sb_push(((*yyvalp).ntSb),(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.nt)); }
#line 2325 "parser.tab.c"
    break;


#line 2329 "parser.tab.c"

      default: break;
    }

  return yyok;
# undef yyerrok
# undef YYABORT
# undef YYACCEPT
# undef YYERROR
# undef YYBACKUP
# undef yyclearin
# undef YYRECOVERING
}


static void
yyuserMerge (int yyn, YYSTYPE* yy0, YYSTYPE* yy1)
{
  YYUSE (yy0);
  YYUSE (yy1);

  switch (yyn)
    {

      default: break;
    }
}

                              /* Bison grammar-table manipulation.  */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep, YYLTYPE *yylocationp, Source* source, AstNode** outp)
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);
  YYUSE (source);
  YYUSE (outp);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}

/** Number of symbols composing the right hand side of rule #RULE.  */
static inline int
yyrhsLength (yyRuleNum yyrule)
{
  return yyr2[yyrule];
}

static void
yydestroyGLRState (char const *yymsg, yyGLRState *yys, Source* source, AstNode** outp)
{
  if (yys->yyresolved)
    yydestruct (yymsg, yy_accessing_symbol (yys->yylrState),
                &yys->yysemantics.yysval, &yys->yyloc, source, outp);
  else
    {
#if YYDEBUG
      if (yydebug)
        {
          if (yys->yysemantics.yyfirstVal)
            YY_FPRINTF ((stderr, "%s unresolved", yymsg));
          else
            YY_FPRINTF ((stderr, "%s incomplete", yymsg));
          YY_SYMBOL_PRINT ("", yy_accessing_symbol (yys->yylrState), YY_NULLPTR, &yys->yyloc);
        }
#endif

      if (yys->yysemantics.yyfirstVal)
        {
          yySemanticOption *yyoption = yys->yysemantics.yyfirstVal;
          yyGLRState *yyrh;
          int yyn;
          for (yyrh = yyoption->yystate, yyn = yyrhsLength (yyoption->yyrule);
               yyn > 0;
               yyrh = yyrh->yypred, yyn -= 1)
            yydestroyGLRState (yymsg, yyrh, source, outp);
        }
    }
}

/** Left-hand-side symbol for rule #YYRULE.  */
static inline yysymbol_kind_t
yylhsNonterm (yyRuleNum yyrule)
{
  return YY_CAST (yysymbol_kind_t, yyr1[yyrule]);
}

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

/** True iff LR state YYSTATE has only a default reduction (regardless
 *  of token).  */
static inline yybool
yyisDefaultedState (yy_state_t yystate)
{
  return yypact_value_is_default (yypact[yystate]);
}

/** The default reduction for YYSTATE, assuming it has one.  */
static inline yyRuleNum
yydefaultAction (yy_state_t yystate)
{
  return yydefact[yystate];
}

#define yytable_value_is_error(Yyn) \
  0

/** The action to take in YYSTATE on seeing YYTOKEN.
 *  Result R means
 *    R < 0:  Reduce on rule -R.
 *    R = 0:  Error.
 *    R > 0:  Shift to state R.
 *  Set *YYCONFLICTS to a pointer into yyconfl to a 0-terminated list
 *  of conflicting reductions.
 */
static inline int
yygetLRActions (yy_state_t yystate, yysymbol_kind_t yytoken, const short** yyconflicts)
{
  int yyindex = yypact[yystate] + yytoken;
  if (yytoken == YYSYMBOL_YYerror)
    {
      // This is the error token.
      *yyconflicts = yyconfl;
      return 0;
    }
  else if (yyisDefaultedState (yystate)
           || yyindex < 0 || YYLAST < yyindex || yycheck[yyindex] != yytoken)
    {
      *yyconflicts = yyconfl;
      return -yydefact[yystate];
    }
  else if (! yytable_value_is_error (yytable[yyindex]))
    {
      *yyconflicts = yyconfl + yyconflp[yyindex];
      return yytable[yyindex];
    }
  else
    {
      *yyconflicts = yyconfl + yyconflp[yyindex];
      return 0;
    }
}

/** Compute post-reduction state.
 * \param yystate   the current state
 * \param yysym     the nonterminal to push on the stack
 */
static inline yy_state_t
yyLRgotoState (yy_state_t yystate, yysymbol_kind_t yysym)
{
  int yyr = yypgoto[yysym - YYNTOKENS] + yystate;
  if (0 <= yyr && yyr <= YYLAST && yycheck[yyr] == yystate)
    return yytable[yyr];
  else
    return yydefgoto[yysym - YYNTOKENS];
}

static inline yybool
yyisShiftAction (int yyaction)
{
  return 0 < yyaction;
}

static inline yybool
yyisErrorAction (int yyaction)
{
  return yyaction == 0;
}

                                /* GLRStates */

/** Return a fresh GLRStackItem in YYSTACKP.  The item is an LR state
 *  if YYISSTATE, and otherwise a semantic option.  Callers should call
 *  YY_RESERVE_GLRSTACK afterwards to make sure there is sufficient
 *  headroom.  */

static inline yyGLRStackItem*
yynewGLRStackItem (yyGLRStack* yystackp, yybool yyisState)
{
  yyGLRStackItem* yynewItem = yystackp->yynextFree;
  yystackp->yyspaceLeft -= 1;
  yystackp->yynextFree += 1;
  yynewItem->yystate.yyisState = yyisState;
  return yynewItem;
}

/** Add a new semantic action that will execute the action for rule
 *  YYRULE on the semantic values in YYRHS to the list of
 *  alternative actions for YYSTATE.  Assumes that YYRHS comes from
 *  stack #YYK of *YYSTACKP. */
static void
yyaddDeferredAction (yyGLRStack* yystackp, YYPTRDIFF_T yyk, yyGLRState* yystate,
                     yyGLRState* yyrhs, yyRuleNum yyrule)
{
  yySemanticOption* yynewOption =
    &yynewGLRStackItem (yystackp, yyfalse)->yyoption;
  YY_ASSERT (!yynewOption->yyisState);
  yynewOption->yystate = yyrhs;
  yynewOption->yyrule = yyrule;
  if (yystackp->yytops.yylookaheadNeeds[yyk])
    {
      yynewOption->yyrawchar = yychar;
      yynewOption->yyval = yylval;
      yynewOption->yyloc = yylloc;
    }
  else
    yynewOption->yyrawchar = YYEMPTY;
  yynewOption->yynext = yystate->yysemantics.yyfirstVal;
  yystate->yysemantics.yyfirstVal = yynewOption;

  YY_RESERVE_GLRSTACK (yystackp);
}

                                /* GLRStacks */

/** Initialize YYSET to a singleton set containing an empty stack.  */
static yybool
yyinitStateSet (yyGLRStateSet* yyset)
{
  yyset->yysize = 1;
  yyset->yycapacity = 16;
  yyset->yystates
    = YY_CAST (yyGLRState**,
               YYMALLOC (YY_CAST (YYSIZE_T, yyset->yycapacity)
                         * sizeof yyset->yystates[0]));
  if (! yyset->yystates)
    return yyfalse;
  yyset->yystates[0] = YY_NULLPTR;
  yyset->yylookaheadNeeds
    = YY_CAST (yybool*,
               YYMALLOC (YY_CAST (YYSIZE_T, yyset->yycapacity)
                         * sizeof yyset->yylookaheadNeeds[0]));
  if (! yyset->yylookaheadNeeds)
    {
      YYFREE (yyset->yystates);
      return yyfalse;
    }
  memset (yyset->yylookaheadNeeds,
          0,
          YY_CAST (YYSIZE_T, yyset->yycapacity) * sizeof yyset->yylookaheadNeeds[0]);
  return yytrue;
}

static void yyfreeStateSet (yyGLRStateSet* yyset)
{
  YYFREE (yyset->yystates);
  YYFREE (yyset->yylookaheadNeeds);
}

/** Initialize *YYSTACKP to a single empty stack, with total maximum
 *  capacity for all stacks of YYSIZE.  */
static yybool
yyinitGLRStack (yyGLRStack* yystackp, YYPTRDIFF_T yysize)
{
  yystackp->yyerrState = 0;
  yynerrs = 0;
  yystackp->yyspaceLeft = yysize;
  yystackp->yyitems
    = YY_CAST (yyGLRStackItem*,
               YYMALLOC (YY_CAST (YYSIZE_T, yysize)
                         * sizeof yystackp->yynextFree[0]));
  if (!yystackp->yyitems)
    return yyfalse;
  yystackp->yynextFree = yystackp->yyitems;
  yystackp->yysplitPoint = YY_NULLPTR;
  yystackp->yylastDeleted = YY_NULLPTR;
  return yyinitStateSet (&yystackp->yytops);
}


#if YYSTACKEXPANDABLE
# define YYRELOC(YYFROMITEMS, YYTOITEMS, YYX, YYTYPE)                   \
  &((YYTOITEMS)                                                         \
    - ((YYFROMITEMS) - YY_REINTERPRET_CAST (yyGLRStackItem*, (YYX))))->YYTYPE

/** If *YYSTACKP is expandable, extend it.  WARNING: Pointers into the
    stack from outside should be considered invalid after this call.
    We always expand when there are 1 or fewer items left AFTER an
    allocation, so that we can avoid having external pointers exist
    across an allocation.  */
static void
yyexpandGLRStack (yyGLRStack* yystackp)
{
  yyGLRStackItem* yynewItems;
  yyGLRStackItem* yyp0, *yyp1;
  YYPTRDIFF_T yynewSize;
  YYPTRDIFF_T yyn;
  YYPTRDIFF_T yysize = yystackp->yynextFree - yystackp->yyitems;
  if (YYMAXDEPTH - YYHEADROOM < yysize)
    yyMemoryExhausted (yystackp);
  yynewSize = 2*yysize;
  if (YYMAXDEPTH < yynewSize)
    yynewSize = YYMAXDEPTH;
  yynewItems
    = YY_CAST (yyGLRStackItem*,
               YYMALLOC (YY_CAST (YYSIZE_T, yynewSize)
                         * sizeof yynewItems[0]));
  if (! yynewItems)
    yyMemoryExhausted (yystackp);
  for (yyp0 = yystackp->yyitems, yyp1 = yynewItems, yyn = yysize;
       0 < yyn;
       yyn -= 1, yyp0 += 1, yyp1 += 1)
    {
      *yyp1 = *yyp0;
      if (*YY_REINTERPRET_CAST (yybool *, yyp0))
        {
          yyGLRState* yys0 = &yyp0->yystate;
          yyGLRState* yys1 = &yyp1->yystate;
          if (yys0->yypred != YY_NULLPTR)
            yys1->yypred =
              YYRELOC (yyp0, yyp1, yys0->yypred, yystate);
          if (! yys0->yyresolved && yys0->yysemantics.yyfirstVal != YY_NULLPTR)
            yys1->yysemantics.yyfirstVal =
              YYRELOC (yyp0, yyp1, yys0->yysemantics.yyfirstVal, yyoption);
        }
      else
        {
          yySemanticOption* yyv0 = &yyp0->yyoption;
          yySemanticOption* yyv1 = &yyp1->yyoption;
          if (yyv0->yystate != YY_NULLPTR)
            yyv1->yystate = YYRELOC (yyp0, yyp1, yyv0->yystate, yystate);
          if (yyv0->yynext != YY_NULLPTR)
            yyv1->yynext = YYRELOC (yyp0, yyp1, yyv0->yynext, yyoption);
        }
    }
  if (yystackp->yysplitPoint != YY_NULLPTR)
    yystackp->yysplitPoint = YYRELOC (yystackp->yyitems, yynewItems,
                                      yystackp->yysplitPoint, yystate);

  for (yyn = 0; yyn < yystackp->yytops.yysize; yyn += 1)
    if (yystackp->yytops.yystates[yyn] != YY_NULLPTR)
      yystackp->yytops.yystates[yyn] =
        YYRELOC (yystackp->yyitems, yynewItems,
                 yystackp->yytops.yystates[yyn], yystate);
  YYFREE (yystackp->yyitems);
  yystackp->yyitems = yynewItems;
  yystackp->yynextFree = yynewItems + yysize;
  yystackp->yyspaceLeft = yynewSize - yysize;
}
#endif

static void
yyfreeGLRStack (yyGLRStack* yystackp)
{
  YYFREE (yystackp->yyitems);
  yyfreeStateSet (&yystackp->yytops);
}

/** Assuming that YYS is a GLRState somewhere on *YYSTACKP, update the
 *  splitpoint of *YYSTACKP, if needed, so that it is at least as deep as
 *  YYS.  */
static inline void
yyupdateSplit (yyGLRStack* yystackp, yyGLRState* yys)
{
  if (yystackp->yysplitPoint != YY_NULLPTR && yystackp->yysplitPoint > yys)
    yystackp->yysplitPoint = yys;
}

/** Invalidate stack #YYK in *YYSTACKP.  */
static inline void
yymarkStackDeleted (yyGLRStack* yystackp, YYPTRDIFF_T yyk)
{
  if (yystackp->yytops.yystates[yyk] != YY_NULLPTR)
    yystackp->yylastDeleted = yystackp->yytops.yystates[yyk];
  yystackp->yytops.yystates[yyk] = YY_NULLPTR;
}

/** Undelete the last stack in *YYSTACKP that was marked as deleted.  Can
    only be done once after a deletion, and only when all other stacks have
    been deleted.  */
static void
yyundeleteLastStack (yyGLRStack* yystackp)
{
  if (yystackp->yylastDeleted == YY_NULLPTR || yystackp->yytops.yysize != 0)
    return;
  yystackp->yytops.yystates[0] = yystackp->yylastDeleted;
  yystackp->yytops.yysize = 1;
  YY_DPRINTF ((stderr, "Restoring last deleted stack as stack #0.\n"));
  yystackp->yylastDeleted = YY_NULLPTR;
}

static inline void
yyremoveDeletes (yyGLRStack* yystackp)
{
  YYPTRDIFF_T yyi, yyj;
  yyi = yyj = 0;
  while (yyj < yystackp->yytops.yysize)
    {
      if (yystackp->yytops.yystates[yyi] == YY_NULLPTR)
        {
          if (yyi == yyj)
            YY_DPRINTF ((stderr, "Removing dead stacks.\n"));
          yystackp->yytops.yysize -= 1;
        }
      else
        {
          yystackp->yytops.yystates[yyj] = yystackp->yytops.yystates[yyi];
          /* In the current implementation, it's unnecessary to copy
             yystackp->yytops.yylookaheadNeeds[yyi] since, after
             yyremoveDeletes returns, the parser immediately either enters
             deterministic operation or shifts a token.  However, it doesn't
             hurt, and the code might evolve to need it.  */
          yystackp->yytops.yylookaheadNeeds[yyj] =
            yystackp->yytops.yylookaheadNeeds[yyi];
          if (yyj != yyi)
            YY_DPRINTF ((stderr, "Rename stack %ld -> %ld.\n",
                        YY_CAST (long, yyi), YY_CAST (long, yyj)));
          yyj += 1;
        }
      yyi += 1;
    }
}

/** Shift to a new state on stack #YYK of *YYSTACKP, corresponding to LR
 * state YYLRSTATE, at input position YYPOSN, with (resolved) semantic
 * value *YYVALP and source location *YYLOCP.  */
static inline void
yyglrShift (yyGLRStack* yystackp, YYPTRDIFF_T yyk, yy_state_t yylrState,
            YYPTRDIFF_T yyposn,
            YYSTYPE* yyvalp, YYLTYPE* yylocp)
{
  yyGLRState* yynewState = &yynewGLRStackItem (yystackp, yytrue)->yystate;

  yynewState->yylrState = yylrState;
  yynewState->yyposn = yyposn;
  yynewState->yyresolved = yytrue;
  yynewState->yypred = yystackp->yytops.yystates[yyk];
  yynewState->yysemantics.yysval = *yyvalp;
  yynewState->yyloc = *yylocp;
  yystackp->yytops.yystates[yyk] = yynewState;

  YY_RESERVE_GLRSTACK (yystackp);
}

/** Shift stack #YYK of *YYSTACKP, to a new state corresponding to LR
 *  state YYLRSTATE, at input position YYPOSN, with the (unresolved)
 *  semantic value of YYRHS under the action for YYRULE.  */
static inline void
yyglrShiftDefer (yyGLRStack* yystackp, YYPTRDIFF_T yyk, yy_state_t yylrState,
                 YYPTRDIFF_T yyposn, yyGLRState* yyrhs, yyRuleNum yyrule)
{
  yyGLRState* yynewState = &yynewGLRStackItem (yystackp, yytrue)->yystate;
  YY_ASSERT (yynewState->yyisState);

  yynewState->yylrState = yylrState;
  yynewState->yyposn = yyposn;
  yynewState->yyresolved = yyfalse;
  yynewState->yypred = yystackp->yytops.yystates[yyk];
  yynewState->yysemantics.yyfirstVal = YY_NULLPTR;
  yystackp->yytops.yystates[yyk] = yynewState;

  /* Invokes YY_RESERVE_GLRSTACK.  */
  yyaddDeferredAction (yystackp, yyk, yynewState, yyrhs, yyrule);
}

#if !YYDEBUG
# define YY_REDUCE_PRINT(Args)
#else
# define YY_REDUCE_PRINT(Args)          \
  do {                                  \
    if (yydebug)                        \
      yy_reduce_print Args;             \
  } while (0)

/*----------------------------------------------------------------------.
| Report that stack #YYK of *YYSTACKP is going to be reduced by YYRULE. |
`----------------------------------------------------------------------*/

static inline void
yy_reduce_print (yybool yynormal, yyGLRStackItem* yyvsp, YYPTRDIFF_T yyk,
                 yyRuleNum yyrule, Source* source, AstNode** outp)
{
  int yynrhs = yyrhsLength (yyrule);
  int yylow = 1;
  int yyi;
  YY_FPRINTF ((stderr, "Reducing stack %ld by rule %d (line %d):\n",
               YY_CAST (long, yyk), yyrule - 1, yyrline[yyrule]));
  if (! yynormal)
    yyfillin (yyvsp, 1, -yynrhs);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YY_FPRINTF ((stderr, "   $%d = ", yyi + 1));
      yy_symbol_print (stderr,
                       yy_accessing_symbol (yyvsp[yyi - yynrhs + 1].yystate.yylrState),
                       &yyvsp[yyi - yynrhs + 1].yystate.yysemantics.yysval,
                       &(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL ((yyi + 1) - (yynrhs))].yystate.yyloc)                       , source, outp);
      if (!yyvsp[yyi - yynrhs + 1].yystate.yyresolved)
        YY_FPRINTF ((stderr, " (unresolved)"));
      YY_FPRINTF ((stderr, "\n"));
    }
}
#endif

/** Pop the symbols consumed by reduction #YYRULE from the top of stack
 *  #YYK of *YYSTACKP, and perform the appropriate semantic action on their
 *  semantic values.  Assumes that all ambiguities in semantic values
 *  have been previously resolved.  Set *YYVALP to the resulting value,
 *  and *YYLOCP to the computed location (if any).  Return value is as
 *  for userAction.  */
static inline YYRESULTTAG
yydoAction (yyGLRStack* yystackp, YYPTRDIFF_T yyk, yyRuleNum yyrule,
            YYSTYPE* yyvalp, YYLTYPE *yylocp, Source* source, AstNode** outp)
{
  int yynrhs = yyrhsLength (yyrule);

  if (yystackp->yysplitPoint == YY_NULLPTR)
    {
      /* Standard special case: single stack.  */
      yyGLRStackItem* yyrhs
        = YY_REINTERPRET_CAST (yyGLRStackItem*, yystackp->yytops.yystates[yyk]);
      YY_ASSERT (yyk == 0);
      yystackp->yynextFree -= yynrhs;
      yystackp->yyspaceLeft += yynrhs;
      yystackp->yytops.yystates[0] = & yystackp->yynextFree[-1].yystate;
      YY_REDUCE_PRINT ((yytrue, yyrhs, yyk, yyrule, source, outp));
      return yyuserAction (yyrule, yynrhs, yyrhs, yystackp,
                           yyvalp, yylocp, source, outp);
    }
  else
    {
      yyGLRStackItem yyrhsVals[YYMAXRHS + YYMAXLEFT + 1];
      yyGLRState* yys = yyrhsVals[YYMAXRHS + YYMAXLEFT].yystate.yypred
        = yystackp->yytops.yystates[yyk];
      int yyi;
      if (yynrhs == 0)
        /* Set default location.  */
        yyrhsVals[YYMAXRHS + YYMAXLEFT - 1].yystate.yyloc = yys->yyloc;
      for (yyi = 0; yyi < yynrhs; yyi += 1)
        {
          yys = yys->yypred;
          YY_ASSERT (yys);
        }
      yyupdateSplit (yystackp, yys);
      yystackp->yytops.yystates[yyk] = yys;
      YY_REDUCE_PRINT ((yyfalse, yyrhsVals + YYMAXRHS + YYMAXLEFT - 1, yyk, yyrule, source, outp));
      return yyuserAction (yyrule, yynrhs, yyrhsVals + YYMAXRHS + YYMAXLEFT - 1,
                           yystackp, yyvalp, yylocp, source, outp);
    }
}

/** Pop items off stack #YYK of *YYSTACKP according to grammar rule YYRULE,
 *  and push back on the resulting nonterminal symbol.  Perform the
 *  semantic action associated with YYRULE and store its value with the
 *  newly pushed state, if YYFORCEEVAL or if *YYSTACKP is currently
 *  unambiguous.  Otherwise, store the deferred semantic action with
 *  the new state.  If the new state would have an identical input
 *  position, LR state, and predecessor to an existing state on the stack,
 *  it is identified with that existing state, eliminating stack #YYK from
 *  *YYSTACKP.  In this case, the semantic value is
 *  added to the options for the existing state's semantic value.
 */
static inline YYRESULTTAG
yyglrReduce (yyGLRStack* yystackp, YYPTRDIFF_T yyk, yyRuleNum yyrule,
             yybool yyforceEval, Source* source, AstNode** outp)
{
  YYPTRDIFF_T yyposn = yystackp->yytops.yystates[yyk]->yyposn;

  if (yyforceEval || yystackp->yysplitPoint == YY_NULLPTR)
    {
      YYSTYPE yysval;
      YYLTYPE yyloc;

      YYRESULTTAG yyflag = yydoAction (yystackp, yyk, yyrule, &yysval, &yyloc, source, outp);
      if (yyflag == yyerr && yystackp->yysplitPoint != YY_NULLPTR)
        YY_DPRINTF ((stderr,
                     "Parse on stack %ld rejected by rule %d (line %d).\n",
                     YY_CAST (long, yyk), yyrule - 1, yyrline[yyrule - 1]));
      if (yyflag != yyok)
        return yyflag;
      YY_SYMBOL_PRINT ("-> $$ =", yylhsNonterm (yyrule), &yysval, &yyloc);
      yyglrShift (yystackp, yyk,
                  yyLRgotoState (yystackp->yytops.yystates[yyk]->yylrState,
                                 yylhsNonterm (yyrule)),
                  yyposn, &yysval, &yyloc);
    }
  else
    {
      YYPTRDIFF_T yyi;
      int yyn;
      yyGLRState* yys, *yys0 = yystackp->yytops.yystates[yyk];
      yy_state_t yynewLRState;

      for (yys = yystackp->yytops.yystates[yyk], yyn = yyrhsLength (yyrule);
           0 < yyn; yyn -= 1)
        {
          yys = yys->yypred;
          YY_ASSERT (yys);
        }
      yyupdateSplit (yystackp, yys);
      yynewLRState = yyLRgotoState (yys->yylrState, yylhsNonterm (yyrule));
      YY_DPRINTF ((stderr,
                   "Reduced stack %ld by rule %d (line %d); action deferred.  "
                   "Now in state %d.\n",
                   YY_CAST (long, yyk), yyrule - 1, yyrline[yyrule - 1],
                   yynewLRState));
      for (yyi = 0; yyi < yystackp->yytops.yysize; yyi += 1)
        if (yyi != yyk && yystackp->yytops.yystates[yyi] != YY_NULLPTR)
          {
            yyGLRState *yysplit = yystackp->yysplitPoint;
            yyGLRState *yyp = yystackp->yytops.yystates[yyi];
            while (yyp != yys && yyp != yysplit && yyp->yyposn >= yyposn)
              {
                if (yyp->yylrState == yynewLRState && yyp->yypred == yys)
                  {
                    yyaddDeferredAction (yystackp, yyk, yyp, yys0, yyrule);
                    yymarkStackDeleted (yystackp, yyk);
                    YY_DPRINTF ((stderr, "Merging stack %ld into stack %ld.\n",
                                 YY_CAST (long, yyk), YY_CAST (long, yyi)));
                    return yyok;
                  }
                yyp = yyp->yypred;
              }
          }
      yystackp->yytops.yystates[yyk] = yys;
      yyglrShiftDefer (yystackp, yyk, yynewLRState, yyposn, yys0, yyrule);
    }
  return yyok;
}

static YYPTRDIFF_T
yysplitStack (yyGLRStack* yystackp, YYPTRDIFF_T yyk)
{
  if (yystackp->yysplitPoint == YY_NULLPTR)
    {
      YY_ASSERT (yyk == 0);
      yystackp->yysplitPoint = yystackp->yytops.yystates[yyk];
    }
  if (yystackp->yytops.yycapacity <= yystackp->yytops.yysize)
    {
      YYPTRDIFF_T state_size = YYSIZEOF (yystackp->yytops.yystates[0]);
      YYPTRDIFF_T half_max_capacity = YYSIZE_MAXIMUM / 2 / state_size;
      if (half_max_capacity < yystackp->yytops.yycapacity)
        yyMemoryExhausted (yystackp);
      yystackp->yytops.yycapacity *= 2;

      {
        yyGLRState** yynewStates
          = YY_CAST (yyGLRState**,
                     YYREALLOC (yystackp->yytops.yystates,
                                (YY_CAST (YYSIZE_T, yystackp->yytops.yycapacity)
                                 * sizeof yynewStates[0])));
        if (yynewStates == YY_NULLPTR)
          yyMemoryExhausted (yystackp);
        yystackp->yytops.yystates = yynewStates;
      }

      {
        yybool* yynewLookaheadNeeds
          = YY_CAST (yybool*,
                     YYREALLOC (yystackp->yytops.yylookaheadNeeds,
                                (YY_CAST (YYSIZE_T, yystackp->yytops.yycapacity)
                                 * sizeof yynewLookaheadNeeds[0])));
        if (yynewLookaheadNeeds == YY_NULLPTR)
          yyMemoryExhausted (yystackp);
        yystackp->yytops.yylookaheadNeeds = yynewLookaheadNeeds;
      }
    }
  yystackp->yytops.yystates[yystackp->yytops.yysize]
    = yystackp->yytops.yystates[yyk];
  yystackp->yytops.yylookaheadNeeds[yystackp->yytops.yysize]
    = yystackp->yytops.yylookaheadNeeds[yyk];
  yystackp->yytops.yysize += 1;
  return yystackp->yytops.yysize - 1;
}

/** True iff YYY0 and YYY1 represent identical options at the top level.
 *  That is, they represent the same rule applied to RHS symbols
 *  that produce the same terminal symbols.  */
static yybool
yyidenticalOptions (yySemanticOption* yyy0, yySemanticOption* yyy1)
{
  if (yyy0->yyrule == yyy1->yyrule)
    {
      yyGLRState *yys0, *yys1;
      int yyn;
      for (yys0 = yyy0->yystate, yys1 = yyy1->yystate,
           yyn = yyrhsLength (yyy0->yyrule);
           yyn > 0;
           yys0 = yys0->yypred, yys1 = yys1->yypred, yyn -= 1)
        if (yys0->yyposn != yys1->yyposn)
          return yyfalse;
      return yytrue;
    }
  else
    return yyfalse;
}

/** Assuming identicalOptions (YYY0,YYY1), destructively merge the
 *  alternative semantic values for the RHS-symbols of YYY1 and YYY0.  */
static void
yymergeOptionSets (yySemanticOption* yyy0, yySemanticOption* yyy1)
{
  yyGLRState *yys0, *yys1;
  int yyn;
  for (yys0 = yyy0->yystate, yys1 = yyy1->yystate,
       yyn = yyrhsLength (yyy0->yyrule);
       0 < yyn;
       yys0 = yys0->yypred, yys1 = yys1->yypred, yyn -= 1)
    {
      if (yys0 == yys1)
        break;
      else if (yys0->yyresolved)
        {
          yys1->yyresolved = yytrue;
          yys1->yysemantics.yysval = yys0->yysemantics.yysval;
        }
      else if (yys1->yyresolved)
        {
          yys0->yyresolved = yytrue;
          yys0->yysemantics.yysval = yys1->yysemantics.yysval;
        }
      else
        {
          yySemanticOption** yyz0p = &yys0->yysemantics.yyfirstVal;
          yySemanticOption* yyz1 = yys1->yysemantics.yyfirstVal;
          while (yytrue)
            {
              if (yyz1 == *yyz0p || yyz1 == YY_NULLPTR)
                break;
              else if (*yyz0p == YY_NULLPTR)
                {
                  *yyz0p = yyz1;
                  break;
                }
              else if (*yyz0p < yyz1)
                {
                  yySemanticOption* yyz = *yyz0p;
                  *yyz0p = yyz1;
                  yyz1 = yyz1->yynext;
                  (*yyz0p)->yynext = yyz;
                }
              yyz0p = &(*yyz0p)->yynext;
            }
          yys1->yysemantics.yyfirstVal = yys0->yysemantics.yyfirstVal;
        }
    }
}

/** Y0 and Y1 represent two possible actions to take in a given
 *  parsing state; return 0 if no combination is possible,
 *  1 if user-mergeable, 2 if Y0 is preferred, 3 if Y1 is preferred.  */
static int
yypreference (yySemanticOption* y0, yySemanticOption* y1)
{
  yyRuleNum r0 = y0->yyrule, r1 = y1->yyrule;
  int p0 = yydprec[r0], p1 = yydprec[r1];

  if (p0 == p1)
    {
      if (yymerger[r0] == 0 || yymerger[r0] != yymerger[r1])
        return 0;
      else
        return 1;
    }
  if (p0 == 0 || p1 == 0)
    return 0;
  if (p0 < p1)
    return 3;
  if (p1 < p0)
    return 2;
  return 0;
}

static YYRESULTTAG yyresolveValue (yyGLRState* yys,
                                   yyGLRStack* yystackp, Source* source, AstNode** outp);


/** Resolve the previous YYN states starting at and including state YYS
 *  on *YYSTACKP. If result != yyok, some states may have been left
 *  unresolved possibly with empty semantic option chains.  Regardless
 *  of whether result = yyok, each state has been left with consistent
 *  data so that yydestroyGLRState can be invoked if necessary.  */
static YYRESULTTAG
yyresolveStates (yyGLRState* yys, int yyn,
                 yyGLRStack* yystackp, Source* source, AstNode** outp)
{
  if (0 < yyn)
    {
      YY_ASSERT (yys->yypred);
      YYCHK (yyresolveStates (yys->yypred, yyn-1, yystackp, source, outp));
      if (! yys->yyresolved)
        YYCHK (yyresolveValue (yys, yystackp, source, outp));
    }
  return yyok;
}

/** Resolve the states for the RHS of YYOPT on *YYSTACKP, perform its
 *  user action, and return the semantic value and location in *YYVALP
 *  and *YYLOCP.  Regardless of whether result = yyok, all RHS states
 *  have been destroyed (assuming the user action destroys all RHS
 *  semantic values if invoked).  */
static YYRESULTTAG
yyresolveAction (yySemanticOption* yyopt, yyGLRStack* yystackp,
                 YYSTYPE* yyvalp, YYLTYPE *yylocp, Source* source, AstNode** outp)
{
  yyGLRStackItem yyrhsVals[YYMAXRHS + YYMAXLEFT + 1];
  int yynrhs = yyrhsLength (yyopt->yyrule);
  YYRESULTTAG yyflag =
    yyresolveStates (yyopt->yystate, yynrhs, yystackp, source, outp);
  if (yyflag != yyok)
    {
      yyGLRState *yys;
      for (yys = yyopt->yystate; yynrhs > 0; yys = yys->yypred, yynrhs -= 1)
        yydestroyGLRState ("Cleanup: popping", yys, source, outp);
      return yyflag;
    }

  yyrhsVals[YYMAXRHS + YYMAXLEFT].yystate.yypred = yyopt->yystate;
  if (yynrhs == 0)
    /* Set default location.  */
    yyrhsVals[YYMAXRHS + YYMAXLEFT - 1].yystate.yyloc = yyopt->yystate->yyloc;
  {
    int yychar_current = yychar;
    YYSTYPE yylval_current = yylval;
    YYLTYPE yylloc_current = yylloc;
    yychar = yyopt->yyrawchar;
    yylval = yyopt->yyval;
    yylloc = yyopt->yyloc;
    yyflag = yyuserAction (yyopt->yyrule, yynrhs,
                           yyrhsVals + YYMAXRHS + YYMAXLEFT - 1,
                           yystackp, yyvalp, yylocp, source, outp);
    yychar = yychar_current;
    yylval = yylval_current;
    yylloc = yylloc_current;
  }
  return yyflag;
}

#if YYDEBUG
static void
yyreportTree (yySemanticOption* yyx, int yyindent)
{
  int yynrhs = yyrhsLength (yyx->yyrule);
  int yyi;
  yyGLRState* yys;
  yyGLRState* yystates[1 + YYMAXRHS];
  yyGLRState yyleftmost_state;

  for (yyi = yynrhs, yys = yyx->yystate; 0 < yyi; yyi -= 1, yys = yys->yypred)
    yystates[yyi] = yys;
  if (yys == YY_NULLPTR)
    {
      yyleftmost_state.yyposn = 0;
      yystates[0] = &yyleftmost_state;
    }
  else
    yystates[0] = yys;

  if (yyx->yystate->yyposn < yys->yyposn + 1)
    YY_FPRINTF ((stderr, "%*s%s -> <Rule %d, empty>\n",
                 yyindent, "", yysymbol_name (yylhsNonterm (yyx->yyrule)),
                 yyx->yyrule - 1));
  else
    YY_FPRINTF ((stderr, "%*s%s -> <Rule %d, tokens %ld .. %ld>\n",
                 yyindent, "", yysymbol_name (yylhsNonterm (yyx->yyrule)),
                 yyx->yyrule - 1, YY_CAST (long, yys->yyposn + 1),
                 YY_CAST (long, yyx->yystate->yyposn)));
  for (yyi = 1; yyi <= yynrhs; yyi += 1)
    {
      if (yystates[yyi]->yyresolved)
        {
          if (yystates[yyi-1]->yyposn+1 > yystates[yyi]->yyposn)
            YY_FPRINTF ((stderr, "%*s%s <empty>\n", yyindent+2, "",
                         yysymbol_name (yy_accessing_symbol (yystates[yyi]->yylrState))));
          else
            YY_FPRINTF ((stderr, "%*s%s <tokens %ld .. %ld>\n", yyindent+2, "",
                         yysymbol_name (yy_accessing_symbol (yystates[yyi]->yylrState)),
                         YY_CAST (long, yystates[yyi-1]->yyposn + 1),
                         YY_CAST (long, yystates[yyi]->yyposn)));
        }
      else
        yyreportTree (yystates[yyi]->yysemantics.yyfirstVal, yyindent+2);
    }
}
#endif

static YYRESULTTAG
yyreportAmbiguity (yySemanticOption* yyx0,
                   yySemanticOption* yyx1, YYLTYPE *yylocp, Source* source, AstNode** outp)
{
  YYUSE (yyx0);
  YYUSE (yyx1);

#if YYDEBUG
  YY_FPRINTF ((stderr, "Ambiguity detected.\n"));
  YY_FPRINTF ((stderr, "Option 1,\n"));
  yyreportTree (yyx0, 2);
  YY_FPRINTF ((stderr, "\nOption 2,\n"));
  yyreportTree (yyx1, 2);
  YY_FPRINTF ((stderr, "\n"));
#endif

  yyerror (yylocp, source, outp, YY_("syntax is ambiguous"));
  return yyabort;
}

/** Resolve the locations for each of the YYN1 states in *YYSTACKP,
 *  ending at YYS1.  Has no effect on previously resolved states.
 *  The first semantic option of a state is always chosen.  */
static void
yyresolveLocations (yyGLRState *yys1, int yyn1,
                    yyGLRStack *yystackp, Source* source, AstNode** outp)
{
  if (0 < yyn1)
    {
      yyresolveLocations (yys1->yypred, yyn1 - 1, yystackp, source, outp);
      if (!yys1->yyresolved)
        {
          yyGLRStackItem yyrhsloc[1 + YYMAXRHS];
          int yynrhs;
          yySemanticOption *yyoption = yys1->yysemantics.yyfirstVal;
          YY_ASSERT (yyoption);
          yynrhs = yyrhsLength (yyoption->yyrule);
          if (0 < yynrhs)
            {
              yyGLRState *yys;
              int yyn;
              yyresolveLocations (yyoption->yystate, yynrhs,
                                  yystackp, source, outp);
              for (yys = yyoption->yystate, yyn = yynrhs;
                   yyn > 0;
                   yys = yys->yypred, yyn -= 1)
                yyrhsloc[yyn].yystate.yyloc = yys->yyloc;
            }
          else
            {
              /* Both yyresolveAction and yyresolveLocations traverse the GSS
                 in reverse rightmost order.  It is only necessary to invoke
                 yyresolveLocations on a subforest for which yyresolveAction
                 would have been invoked next had an ambiguity not been
                 detected.  Thus the location of the previous state (but not
                 necessarily the previous state itself) is guaranteed to be
                 resolved already.  */
              yyGLRState *yyprevious = yyoption->yystate;
              yyrhsloc[0].yystate.yyloc = yyprevious->yyloc;
            }
          YYLLOC_DEFAULT ((yys1->yyloc), yyrhsloc, yynrhs);
        }
    }
}

/** Resolve the ambiguity represented in state YYS in *YYSTACKP,
 *  perform the indicated actions, and set the semantic value of YYS.
 *  If result != yyok, the chain of semantic options in YYS has been
 *  cleared instead or it has been left unmodified except that
 *  redundant options may have been removed.  Regardless of whether
 *  result = yyok, YYS has been left with consistent data so that
 *  yydestroyGLRState can be invoked if necessary.  */
static YYRESULTTAG
yyresolveValue (yyGLRState* yys, yyGLRStack* yystackp, Source* source, AstNode** outp)
{
  yySemanticOption* yyoptionList = yys->yysemantics.yyfirstVal;
  yySemanticOption* yybest = yyoptionList;
  yySemanticOption** yypp;
  yybool yymerge = yyfalse;
  YYSTYPE yysval;
  YYRESULTTAG yyflag;
  YYLTYPE *yylocp = &yys->yyloc;

  for (yypp = &yyoptionList->yynext; *yypp != YY_NULLPTR; )
    {
      yySemanticOption* yyp = *yypp;

      if (yyidenticalOptions (yybest, yyp))
        {
          yymergeOptionSets (yybest, yyp);
          *yypp = yyp->yynext;
        }
      else
        {
          switch (yypreference (yybest, yyp))
            {
            case 0:
              yyresolveLocations (yys, 1, yystackp, source, outp);
              return yyreportAmbiguity (yybest, yyp, yylocp, source, outp);
              break;
            case 1:
              yymerge = yytrue;
              break;
            case 2:
              break;
            case 3:
              yybest = yyp;
              yymerge = yyfalse;
              break;
            default:
              /* This cannot happen so it is not worth a YY_ASSERT (yyfalse),
                 but some compilers complain if the default case is
                 omitted.  */
              break;
            }
          yypp = &yyp->yynext;
        }
    }

  if (yymerge)
    {
      yySemanticOption* yyp;
      int yyprec = yydprec[yybest->yyrule];
      yyflag = yyresolveAction (yybest, yystackp, &yysval, yylocp, source, outp);
      if (yyflag == yyok)
        for (yyp = yybest->yynext; yyp != YY_NULLPTR; yyp = yyp->yynext)
          {
            if (yyprec == yydprec[yyp->yyrule])
              {
                YYSTYPE yysval_other;
                YYLTYPE yydummy;
                yyflag = yyresolveAction (yyp, yystackp, &yysval_other, &yydummy, source, outp);
                if (yyflag != yyok)
                  {
                    yydestruct ("Cleanup: discarding incompletely merged value for",
                                yy_accessing_symbol (yys->yylrState),
                                &yysval, yylocp, source, outp);
                    break;
                  }
                yyuserMerge (yymerger[yyp->yyrule], &yysval, &yysval_other);
              }
          }
    }
  else
    yyflag = yyresolveAction (yybest, yystackp, &yysval, yylocp, source, outp);

  if (yyflag == yyok)
    {
      yys->yyresolved = yytrue;
      yys->yysemantics.yysval = yysval;
    }
  else
    yys->yysemantics.yyfirstVal = YY_NULLPTR;
  return yyflag;
}

static YYRESULTTAG
yyresolveStack (yyGLRStack* yystackp, Source* source, AstNode** outp)
{
  if (yystackp->yysplitPoint != YY_NULLPTR)
    {
      yyGLRState* yys;
      int yyn;

      for (yyn = 0, yys = yystackp->yytops.yystates[0];
           yys != yystackp->yysplitPoint;
           yys = yys->yypred, yyn += 1)
        continue;
      YYCHK (yyresolveStates (yystackp->yytops.yystates[0], yyn, yystackp
                             , source, outp));
    }
  return yyok;
}

static void
yycompressStack (yyGLRStack* yystackp)
{
  yyGLRState* yyp, *yyq, *yyr;

  if (yystackp->yytops.yysize != 1 || yystackp->yysplitPoint == YY_NULLPTR)
    return;

  for (yyp = yystackp->yytops.yystates[0], yyq = yyp->yypred, yyr = YY_NULLPTR;
       yyp != yystackp->yysplitPoint;
       yyr = yyp, yyp = yyq, yyq = yyp->yypred)
    yyp->yypred = yyr;

  yystackp->yyspaceLeft += yystackp->yynextFree - yystackp->yyitems;
  yystackp->yynextFree = YY_REINTERPRET_CAST (yyGLRStackItem*, yystackp->yysplitPoint) + 1;
  yystackp->yyspaceLeft -= yystackp->yynextFree - yystackp->yyitems;
  yystackp->yysplitPoint = YY_NULLPTR;
  yystackp->yylastDeleted = YY_NULLPTR;

  while (yyr != YY_NULLPTR)
    {
      yystackp->yynextFree->yystate = *yyr;
      yyr = yyr->yypred;
      yystackp->yynextFree->yystate.yypred = &yystackp->yynextFree[-1].yystate;
      yystackp->yytops.yystates[0] = &yystackp->yynextFree->yystate;
      yystackp->yynextFree += 1;
      yystackp->yyspaceLeft -= 1;
    }
}

static YYRESULTTAG
yyprocessOneStack (yyGLRStack* yystackp, YYPTRDIFF_T yyk,
                   YYPTRDIFF_T yyposn, YYLTYPE *yylocp, Source* source, AstNode** outp)
{
  while (yystackp->yytops.yystates[yyk] != YY_NULLPTR)
    {
      yy_state_t yystate = yystackp->yytops.yystates[yyk]->yylrState;
      YY_DPRINTF ((stderr, "Stack %ld Entering state %d\n",
                   YY_CAST (long, yyk), yystate));

      YY_ASSERT (yystate != YYFINAL);

      if (yyisDefaultedState (yystate))
        {
          YYRESULTTAG yyflag;
          yyRuleNum yyrule = yydefaultAction (yystate);
          if (yyrule == 0)
            {
              YY_DPRINTF ((stderr, "Stack %ld dies.\n", YY_CAST (long, yyk)));
              yymarkStackDeleted (yystackp, yyk);
              return yyok;
            }
          yyflag = yyglrReduce (yystackp, yyk, yyrule, yyimmediate[yyrule], source, outp);
          if (yyflag == yyerr)
            {
              YY_DPRINTF ((stderr,
                           "Stack %ld dies "
                           "(predicate failure or explicit user error).\n",
                           YY_CAST (long, yyk)));
              yymarkStackDeleted (yystackp, yyk);
              return yyok;
            }
          if (yyflag != yyok)
            return yyflag;
        }
      else
        {
          yysymbol_kind_t yytoken = yygetToken (&yychar, yystackp, source, outp);
          const short* yyconflicts;
          const int yyaction = yygetLRActions (yystate, yytoken, &yyconflicts);
          yystackp->yytops.yylookaheadNeeds[yyk] = yytrue;

          for (/* nothing */; *yyconflicts; yyconflicts += 1)
            {
              YYRESULTTAG yyflag;
              YYPTRDIFF_T yynewStack = yysplitStack (yystackp, yyk);
              YY_DPRINTF ((stderr, "Splitting off stack %ld from %ld.\n",
                           YY_CAST (long, yynewStack), YY_CAST (long, yyk)));
              yyflag = yyglrReduce (yystackp, yynewStack,
                                    *yyconflicts,
                                    yyimmediate[*yyconflicts], source, outp);
              if (yyflag == yyok)
                YYCHK (yyprocessOneStack (yystackp, yynewStack,
                                          yyposn, yylocp, source, outp));
              else if (yyflag == yyerr)
                {
                  YY_DPRINTF ((stderr, "Stack %ld dies.\n", YY_CAST (long, yynewStack)));
                  yymarkStackDeleted (yystackp, yynewStack);
                }
              else
                return yyflag;
            }

          if (yyisShiftAction (yyaction))
            break;
          else if (yyisErrorAction (yyaction))
            {
              YY_DPRINTF ((stderr, "Stack %ld dies.\n", YY_CAST (long, yyk)));
              yymarkStackDeleted (yystackp, yyk);
              break;
            }
          else
            {
              YYRESULTTAG yyflag = yyglrReduce (yystackp, yyk, -yyaction,
                                                yyimmediate[-yyaction], source, outp);
              if (yyflag == yyerr)
                {
                  YY_DPRINTF ((stderr,
                               "Stack %ld dies "
                               "(predicate failure or explicit user error).\n",
                               YY_CAST (long, yyk)));
                  yymarkStackDeleted (yystackp, yyk);
                  break;
                }
              else if (yyflag != yyok)
                return yyflag;
            }
        }
    }
  return yyok;
}






static void
yyreportSyntaxError (yyGLRStack* yystackp, Source* source, AstNode** outp)
{
  if (yystackp->yyerrState != 0)
    return;
  yyerror (&yylloc, source, outp, YY_("syntax error"));
  yynerrs += 1;
}

/* Recover from a syntax error on *YYSTACKP, assuming that *YYSTACKP->YYTOKENP,
   yylval, and yylloc are the syntactic category, semantic value, and location
   of the lookahead.  */
static void
yyrecoverSyntaxError (yyGLRStack* yystackp, Source* source, AstNode** outp)
{
  if (yystackp->yyerrState == 3)
    /* We just shifted the error token and (perhaps) took some
       reductions.  Skip tokens until we can proceed.  */
    while (yytrue)
      {
        yysymbol_kind_t yytoken;
        int yyj;
        if (yychar == YYEOF)
          yyFail (yystackp, &yylloc, source, outp, YY_NULLPTR);
        if (yychar != YYEMPTY)
          {
            /* We throw away the lookahead, but the error range
               of the shifted error token must take it into account.  */
            yyGLRState *yys = yystackp->yytops.yystates[0];
            yyGLRStackItem yyerror_range[3];
            yyerror_range[1].yystate.yyloc = yys->yyloc;
            yyerror_range[2].yystate.yyloc = yylloc;
            YYLLOC_DEFAULT ((yys->yyloc), yyerror_range, 2);
            yytoken = YYTRANSLATE (yychar);
            yydestruct ("Error: discarding",
                        yytoken, &yylval, &yylloc, source, outp);
            yychar = YYEMPTY;
          }
        yytoken = yygetToken (&yychar, yystackp, source, outp);
        yyj = yypact[yystackp->yytops.yystates[0]->yylrState];
        if (yypact_value_is_default (yyj))
          return;
        yyj += yytoken;
        if (yyj < 0 || YYLAST < yyj || yycheck[yyj] != yytoken)
          {
            if (yydefact[yystackp->yytops.yystates[0]->yylrState] != 0)
              return;
          }
        else if (! yytable_value_is_error (yytable[yyj]))
          return;
      }

  /* Reduce to one stack.  */
  {
    YYPTRDIFF_T yyk;
    for (yyk = 0; yyk < yystackp->yytops.yysize; yyk += 1)
      if (yystackp->yytops.yystates[yyk] != YY_NULLPTR)
        break;
    if (yyk >= yystackp->yytops.yysize)
      yyFail (yystackp, &yylloc, source, outp, YY_NULLPTR);
    for (yyk += 1; yyk < yystackp->yytops.yysize; yyk += 1)
      yymarkStackDeleted (yystackp, yyk);
    yyremoveDeletes (yystackp);
    yycompressStack (yystackp);
  }

  /* Pop stack until we find a state that shifts the error token.  */
  yystackp->yyerrState = 3;
  while (yystackp->yytops.yystates[0] != YY_NULLPTR)
    {
      yyGLRState *yys = yystackp->yytops.yystates[0];
      int yyj = yypact[yys->yylrState];
      if (! yypact_value_is_default (yyj))
        {
          yyj += YYSYMBOL_YYerror;
          if (0 <= yyj && yyj <= YYLAST && yycheck[yyj] == YYSYMBOL_YYerror
              && yyisShiftAction (yytable[yyj]))
            {
              /* Shift the error token.  */
              int yyaction = yytable[yyj];
              /* First adjust its location.*/
              YYLTYPE yyerrloc;
              yystackp->yyerror_range[2].yystate.yyloc = yylloc;
              YYLLOC_DEFAULT (yyerrloc, (yystackp->yyerror_range), 2);
              YY_SYMBOL_PRINT ("Shifting", yy_accessing_symbol (yyaction),
                               &yylval, &yyerrloc);
              yyglrShift (yystackp, 0, yyaction,
                          yys->yyposn, &yylval, &yyerrloc);
              yys = yystackp->yytops.yystates[0];
              break;
            }
        }
      yystackp->yyerror_range[1].yystate.yyloc = yys->yyloc;
      if (yys->yypred != YY_NULLPTR)
        yydestroyGLRState ("Error: popping", yys, source, outp);
      yystackp->yytops.yystates[0] = yys->yypred;
      yystackp->yynextFree -= 1;
      yystackp->yyspaceLeft += 1;
    }
  if (yystackp->yytops.yystates[0] == YY_NULLPTR)
    yyFail (yystackp, &yylloc, source, outp, YY_NULLPTR);
}

#define YYCHK1(YYE)                                                          \
  do {                                                                       \
    switch (YYE) {                                                           \
    case yyok:                                                               \
      break;                                                                 \
    case yyabort:                                                            \
      goto yyabortlab;                                                       \
    case yyaccept:                                                           \
      goto yyacceptlab;                                                      \
    case yyerr:                                                              \
      goto yyuser_error;                                                     \
    default:                                                                 \
      goto yybuglab;                                                         \
    }                                                                        \
  } while (0)

/*----------.
| yyparse.  |
`----------*/

int
yyparse (Source* source, AstNode** outp)
{
  int yyresult;
  yyGLRStack yystack;
  yyGLRStack* const yystackp = &yystack;
  YYPTRDIFF_T yyposn;

  YY_DPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY;
  yylval = yyval_default;
  yylloc = yyloc_default;

  if (! yyinitGLRStack (yystackp, YYINITDEPTH))
    goto yyexhaustedlab;
  switch (YYSETJMP (yystack.yyexception_buffer))
    {
    case 0: break;
    case 1: goto yyabortlab;
    case 2: goto yyexhaustedlab;
    default: goto yybuglab;
    }
  yyglrShift (&yystack, 0, 0, 0, &yylval, &yylloc);
  yyposn = 0;

  while (yytrue)
    {
      /* For efficiency, we have two loops, the first of which is
         specialized to deterministic operation (single stack, no
         potential ambiguity).  */
      /* Standard mode. */
      while (yytrue)
        {
          yy_state_t yystate = yystack.yytops.yystates[0]->yylrState;
          YY_DPRINTF ((stderr, "Entering state %d\n", yystate));
          if (yystate == YYFINAL)
            goto yyacceptlab;
          if (yyisDefaultedState (yystate))
            {
              yyRuleNum yyrule = yydefaultAction (yystate);
              if (yyrule == 0)
                {
                  yystack.yyerror_range[1].yystate.yyloc = yylloc;
                  yyreportSyntaxError (&yystack, source, outp);
                  goto yyuser_error;
                }
              YYCHK1 (yyglrReduce (&yystack, 0, yyrule, yytrue, source, outp));
            }
          else
            {
              yysymbol_kind_t yytoken = yygetToken (&yychar, yystackp, source, outp);
              const short* yyconflicts;
              int yyaction = yygetLRActions (yystate, yytoken, &yyconflicts);
              if (*yyconflicts)
                /* Enter nondeterministic mode.  */
                break;
              if (yyisShiftAction (yyaction))
                {
                  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
                  yychar = YYEMPTY;
                  yyposn += 1;
                  yyglrShift (&yystack, 0, yyaction, yyposn, &yylval, &yylloc);
                  if (0 < yystack.yyerrState)
                    yystack.yyerrState -= 1;
                }
              else if (yyisErrorAction (yyaction))
                {
                  yystack.yyerror_range[1].yystate.yyloc = yylloc;
                  /* Issue an error message unless the scanner already
                     did. */
                  if (yychar != YYerror)
                    yyreportSyntaxError (&yystack, source, outp);
                  goto yyuser_error;
                }
              else
                YYCHK1 (yyglrReduce (&yystack, 0, -yyaction, yytrue, source, outp));
            }
        }

      /* Nondeterministic mode. */
      while (yytrue)
        {
          yysymbol_kind_t yytoken_to_shift;
          YYPTRDIFF_T yys;

          for (yys = 0; yys < yystack.yytops.yysize; yys += 1)
            yystackp->yytops.yylookaheadNeeds[yys] = yychar != YYEMPTY;

          /* yyprocessOneStack returns one of three things:

              - An error flag.  If the caller is yyprocessOneStack, it
                immediately returns as well.  When the caller is finally
                yyparse, it jumps to an error label via YYCHK1.

              - yyok, but yyprocessOneStack has invoked yymarkStackDeleted
                (&yystack, yys), which sets the top state of yys to NULL.  Thus,
                yyparse's following invocation of yyremoveDeletes will remove
                the stack.

              - yyok, when ready to shift a token.

             Except in the first case, yyparse will invoke yyremoveDeletes and
             then shift the next token onto all remaining stacks.  This
             synchronization of the shift (that is, after all preceding
             reductions on all stacks) helps prevent double destructor calls
             on yylval in the event of memory exhaustion.  */

          for (yys = 0; yys < yystack.yytops.yysize; yys += 1)
            YYCHK1 (yyprocessOneStack (&yystack, yys, yyposn, &yylloc, source, outp));
          yyremoveDeletes (&yystack);
          if (yystack.yytops.yysize == 0)
            {
              yyundeleteLastStack (&yystack);
              if (yystack.yytops.yysize == 0)
                yyFail (&yystack, &yylloc, source, outp, YY_("syntax error"));
              YYCHK1 (yyresolveStack (&yystack, source, outp));
              YY_DPRINTF ((stderr, "Returning to deterministic operation.\n"));
              yystack.yyerror_range[1].yystate.yyloc = yylloc;
              yyreportSyntaxError (&yystack, source, outp);
              goto yyuser_error;
            }

          /* If any yyglrShift call fails, it will fail after shifting.  Thus,
             a copy of yylval will already be on stack 0 in the event of a
             failure in the following loop.  Thus, yychar is set to YYEMPTY
             before the loop to make sure the user destructor for yylval isn't
             called twice.  */
          yytoken_to_shift = YYTRANSLATE (yychar);
          yychar = YYEMPTY;
          yyposn += 1;
          for (yys = 0; yys < yystack.yytops.yysize; yys += 1)
            {
              yy_state_t yystate = yystack.yytops.yystates[yys]->yylrState;
              const short* yyconflicts;
              int yyaction = yygetLRActions (yystate, yytoken_to_shift,
                              &yyconflicts);
              /* Note that yyconflicts were handled by yyprocessOneStack.  */
              YY_DPRINTF ((stderr, "On stack %ld, ", YY_CAST (long, yys)));
              YY_SYMBOL_PRINT ("shifting", yytoken_to_shift, &yylval, &yylloc);
              yyglrShift (&yystack, yys, yyaction, yyposn,
                          &yylval, &yylloc);
              YY_DPRINTF ((stderr, "Stack %ld now in state #%d\n",
                           YY_CAST (long, yys),
                           yystack.yytops.yystates[yys]->yylrState));
            }

          if (yystack.yytops.yysize == 1)
            {
              YYCHK1 (yyresolveStack (&yystack, source, outp));
              YY_DPRINTF ((stderr, "Returning to deterministic operation.\n"));
              yycompressStack (&yystack);
              break;
            }
        }
      continue;
    yyuser_error:
      yyrecoverSyntaxError (&yystack, source, outp);
      yyposn = yystack.yytops.yystates[0]->yyposn;
    }

 yyacceptlab:
  yyresult = 0;
  goto yyreturn;

 yybuglab:
  YY_ASSERT (yyfalse);
  goto yyabortlab;

 yyabortlab:
  yyresult = 1;
  goto yyreturn;

 yyexhaustedlab:
  yyerror (&yylloc, source, outp, YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturn;

 yyreturn:
  if (yychar != YYEMPTY)
    yydestruct ("Cleanup: discarding lookahead",
                YYTRANSLATE (yychar), &yylval, &yylloc, source, outp);

  /* If the stack is well-formed, pop the stack until it is empty,
     destroying its entries as we go.  But free the stack regardless
     of whether it is well-formed.  */
  if (yystack.yyitems)
    {
      yyGLRState** yystates = yystack.yytops.yystates;
      if (yystates)
        {
          YYPTRDIFF_T yysize = yystack.yytops.yysize;
          YYPTRDIFF_T yyk;
          for (yyk = 0; yyk < yysize; yyk += 1)
            if (yystates[yyk])
              {
                while (yystates[yyk])
                  {
                    yyGLRState *yys = yystates[yyk];
                    yystack.yyerror_range[1].yystate.yyloc = yys->yyloc;
                    if (yys->yypred != YY_NULLPTR)
                      yydestroyGLRState ("Cleanup: popping", yys, source, outp);
                    yystates[yyk] = yys->yypred;
                    yystack.yynextFree -= 1;
                    yystack.yyspaceLeft += 1;
                  }
                break;
              }
        }
      yyfreeGLRStack (&yystack);
    }

  return yyresult;
}

/* DEBUGGING ONLY */
#if YYDEBUG
static void
yy_yypstack (yyGLRState* yys)
{
  if (yys->yypred)
    {
      yy_yypstack (yys->yypred);
      YY_FPRINTF ((stderr, " -> "));
    }
  YY_FPRINTF ((stderr, "%d@%ld", yys->yylrState, YY_CAST (long, yys->yyposn)));
}

static void
yypstates (yyGLRState* yyst)
{
  if (yyst == YY_NULLPTR)
    YY_FPRINTF ((stderr, "<null>"));
  else
    yy_yypstack (yyst);
  YY_FPRINTF ((stderr, "\n"));
}

static void
yypstack (yyGLRStack* yystackp, YYPTRDIFF_T yyk)
{
  yypstates (yystackp->yytops.yystates[yyk]);
}

static void
yypdumpstack (yyGLRStack* yystackp)
{
#define YYINDEX(YYX)                                                    \
  YY_CAST (long,                                                        \
           ((YYX)                                                       \
            ? YY_REINTERPRET_CAST (yyGLRStackItem*, (YYX)) - yystackp->yyitems \
            : -1))

  yyGLRStackItem* yyp;
  for (yyp = yystackp->yyitems; yyp < yystackp->yynextFree; yyp += 1)
    {
      YY_FPRINTF ((stderr, "%3ld. ",
                   YY_CAST (long, yyp - yystackp->yyitems)));
      if (*YY_REINTERPRET_CAST (yybool *, yyp))
        {
          YY_ASSERT (yyp->yystate.yyisState);
          YY_ASSERT (yyp->yyoption.yyisState);
          YY_FPRINTF ((stderr, "Res: %d, LR State: %d, posn: %ld, pred: %ld",
                       yyp->yystate.yyresolved, yyp->yystate.yylrState,
                       YY_CAST (long, yyp->yystate.yyposn),
                       YYINDEX (yyp->yystate.yypred)));
          if (! yyp->yystate.yyresolved)
            YY_FPRINTF ((stderr, ", firstVal: %ld",
                         YYINDEX (yyp->yystate.yysemantics.yyfirstVal)));
        }
      else
        {
          YY_ASSERT (!yyp->yystate.yyisState);
          YY_ASSERT (!yyp->yyoption.yyisState);
          YY_FPRINTF ((stderr, "Option. rule: %d, state: %ld, next: %ld",
                       yyp->yyoption.yyrule - 1,
                       YYINDEX (yyp->yyoption.yystate),
                       YYINDEX (yyp->yyoption.yynext)));
        }
      YY_FPRINTF ((stderr, "\n"));
    }

  YY_FPRINTF ((stderr, "Tops:"));
  {
    YYPTRDIFF_T yyi;
    for (yyi = 0; yyi < yystackp->yytops.yysize; yyi += 1)
      YY_FPRINTF ((stderr, "%ld: %ld; ", YY_CAST (long, yyi),
                   YYINDEX (yystackp->yytops.yystates[yyi])));
    YY_FPRINTF ((stderr, "\n"));
  }
#undef YYINDEX
}
#endif

#undef yylval
#undef yychar
#undef yynerrs
#undef yylloc




#line 568 "parser.yy"


#include <stdio.h>

#include "lexer.h"

#include "useful.h"
#include "source.h"
#include "ast.h"

RawAstNode* ParseScript(Source* source) {
    // TODO: implement me from `parser.c`
    AstNode* out = NULL;
    int result = yyparse(source, &out);
    if (result == 0) {
        return out;
    } else {
        COMPILER_ERROR("yyparse == 0 <=> error");
        return NULL;
    }
}

// int yylex (YYSTYPE *lvalp) {
//     /* TODO: Put value onto Bison stack. */
//     return TK_NULL;
// }

int yylex(YYSTYPE* lvalp, YYLTYPE* llocp, Source* source) {
    // see:
    // https://www.gnu.org/software/bison/manual/html_node/Calling-Convention.html

    TokenInfo* info = &lvalp->token;
    llocp->source = source;
    int tk = LexOneToken(source,info,llocp);
    if (DEBUG) {
        DebugPrintToken("YYLEX:", tk, info, llocp);
    }
    if (tk == TK_EOS) {
        return YYEOF;
    } else {
        return tk;
    }
}

void yyerror(YYLTYPE* llocp, Source* source, AstNode** outp, char const* message) {
    Loc loc = FirstLocOfSpan(*llocp);
    FeedbackNote* note = CreateFeedbackNote("here...", loc, NULL);
    PostFeedback(
        FBK_ERROR, note,
        "Parser error: %s", message
    );
}
