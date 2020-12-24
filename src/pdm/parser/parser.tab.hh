// A Bison parser, made by GNU Bison 3.7.3.

// Skeleton interface for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015, 2018-2020 Free Software Foundation, Inc.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

// As a special exception, you may create a larger work that contains
// part or all of the Bison parser skeleton and distribute that work
// under terms of your choice, so long as that work isn't itself a
// parser generator using the skeleton or a modified version thereof
// as a parser skeleton.  Alternatively, if you modify or redistribute
// the parser skeleton itself, you may (at your option) remove this
// special exception, which will cause the skeleton and the resulting
// Bison output files to be licensed under the GNU General Public
// License without this special exception.

// This special exception was added by the Free Software Foundation in
// version 2.2 of Bison.


/**
 ** \file parser.tab.hh
 ** Define the pdm::parser::parser class.
 */

// C++ LALR(1) parser skeleton written by Akim Demaille.

// DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
// especially those whose name start with YY_ or yy_.  They are
// private implementation details that can be changed or removed.

#ifndef YY_YY_PARSER_TAB_HH_INCLUDED
# define YY_YY_PARSER_TAB_HH_INCLUDED
// "%code requires" blocks.
#line 32 "parser.yy"

    #include "pdm/core/config.hh"

    // todo: include more AST files here:
    #include "pdm/ast/node.hh"
    #include "pdm/ast/manager.hh"
    #include "pdm/ast/script/script.hh"
    #include "pdm/ast/exp/exp.hh"
    #include "pdm/ast/exp/struct.hh"
    #include "pdm/ast/exp/unary.hh"
    #include "pdm/ast/exp/binary.hh"
    #include "pdm/ast/exp/tcall.hh"
    #include "pdm/ast/stmt/stmt.hh"
    #include "pdm/ast/pattern/vpattern.hh"
    #include "pdm/ast/pattern/lpattern.hh"
    #include "pdm/ast/pattern/tpattern.hh"
    #include "pdm/ast/typespec/typespec.hh"
    #include "pdm/ast/typespec/struct.hh"
    #include "pdm/ast/typespec/tcall.hh"

    #include "pdm/parser/reader.hh"
    #include "pdm/parser/lexer.hh"

    #include "pdm/source/source.hh"
    #include "pdm/source/pos.hh"
    #include "pdm/source/loc.hh"

#line 77 "parser.tab.hh"


# include <cstdlib> // std::abort
# include <iostream>
# include <stdexcept>
# include <string>
# include <vector>

#if defined __cplusplus
# define YY_CPLUSPLUS __cplusplus
#else
# define YY_CPLUSPLUS 199711L
#endif

// Support move semantics when possible.
#if 201103L <= YY_CPLUSPLUS
# define YY_MOVE           std::move
# define YY_MOVE_OR_COPY   move
# define YY_MOVE_REF(Type) Type&&
# define YY_RVREF(Type)    Type&&
# define YY_COPY(Type)     Type
#else
# define YY_MOVE
# define YY_MOVE_OR_COPY   copy
# define YY_MOVE_REF(Type) Type&
# define YY_RVREF(Type)    const Type&
# define YY_COPY(Type)     const Type&
#endif

// Support noexcept when possible.
#if 201103L <= YY_CPLUSPLUS
# define YY_NOEXCEPT noexcept
# define YY_NOTHROW
#else
# define YY_NOEXCEPT
# define YY_NOTHROW throw ()
#endif

// Support constexpr when possible.
#if 201703 <= YY_CPLUSPLUS
# define YY_CONSTEXPR constexpr
#else
# define YY_CONSTEXPR
#endif


#ifndef YY_ASSERT
# include <cassert>
# define YY_ASSERT assert
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

/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif

#line 22 "parser.yy"
namespace pdm { namespace parser {
#line 212 "parser.tab.hh"




  /// A Bison parser.
  class parser
  {
  public:
#ifndef YYSTYPE
  /// A buffer to store and retrieve objects.
  ///
  /// Sort of a variant, but does not keep track of the nature
  /// of the stored data, since that knowledge is available
  /// via the current parser state.
  class semantic_type
  {
  public:
    /// Type of *this.
    typedef semantic_type self_type;

    /// Empty construction.
    semantic_type () YY_NOEXCEPT
      : yybuffer_ ()
    {}

    /// Construct and fill.
    template <typename T>
    semantic_type (YY_RVREF (T) t)
    {
      YY_ASSERT (sizeof (T) <= size);
      new (yyas_<T> ()) T (YY_MOVE (t));
    }

#if 201103L <= YY_CPLUSPLUS
    /// Non copyable.
    semantic_type (const self_type&) = delete;
    /// Non copyable.
    self_type& operator= (const self_type&) = delete;
#endif

    /// Destruction, allowed only if empty.
    ~semantic_type () YY_NOEXCEPT
    {}

# if 201103L <= YY_CPLUSPLUS
    /// Instantiate a \a T in here from \a t.
    template <typename T, typename... U>
    T&
    emplace (U&&... u)
    {
      return *new (yyas_<T> ()) T (std::forward <U>(u)...);
    }
# else
    /// Instantiate an empty \a T in here.
    template <typename T>
    T&
    emplace ()
    {
      return *new (yyas_<T> ()) T ();
    }

    /// Instantiate a \a T in here from \a t.
    template <typename T>
    T&
    emplace (const T& t)
    {
      return *new (yyas_<T> ()) T (t);
    }
# endif

    /// Instantiate an empty \a T in here.
    /// Obsolete, use emplace.
    template <typename T>
    T&
    build ()
    {
      return emplace<T> ();
    }

    /// Instantiate a \a T in here from \a t.
    /// Obsolete, use emplace.
    template <typename T>
    T&
    build (const T& t)
    {
      return emplace<T> (t);
    }

    /// Accessor to a built \a T.
    template <typename T>
    T&
    as () YY_NOEXCEPT
    {
      return *yyas_<T> ();
    }

    /// Const accessor to a built \a T (for %printer).
    template <typename T>
    const T&
    as () const YY_NOEXCEPT
    {
      return *yyas_<T> ();
    }

    /// Swap the content with \a that, of same type.
    ///
    /// Both variants must be built beforehand, because swapping the actual
    /// data requires reading it (with as()), and this is not possible on
    /// unconstructed variants: it would require some dynamic testing, which
    /// should not be the variant's responsibility.
    /// Swapping between built and (possibly) non-built is done with
    /// self_type::move ().
    template <typename T>
    void
    swap (self_type& that) YY_NOEXCEPT
    {
      std::swap (as<T> (), that.as<T> ());
    }

    /// Move the content of \a that to this.
    ///
    /// Destroys \a that.
    template <typename T>
    void
    move (self_type& that)
    {
# if 201103L <= YY_CPLUSPLUS
      emplace<T> (std::move (that.as<T> ()));
# else
      emplace<T> ();
      swap<T> (that);
# endif
      that.destroy<T> ();
    }

# if 201103L <= YY_CPLUSPLUS
    /// Move the content of \a that to this.
    template <typename T>
    void
    move (self_type&& that)
    {
      emplace<T> (std::move (that.as<T> ()));
      that.destroy<T> ();
    }
#endif

    /// Copy the content of \a that to this.
    template <typename T>
    void
    copy (const self_type& that)
    {
      emplace<T> (that.as<T> ());
    }

    /// Destroy the stored \a T.
    template <typename T>
    void
    destroy ()
    {
      as<T> ().~T ();
    }

  private:
#if YY_CPLUSPLUS < 201103L
    /// Non copyable.
    semantic_type (const self_type&);
    /// Non copyable.
    self_type& operator= (const self_type&);
#endif

    /// Accessor to raw memory as \a T.
    template <typename T>
    T*
    yyas_ () YY_NOEXCEPT
    {
      void *yyp = yybuffer_.yyraw;
      return static_cast<T*> (yyp);
     }

    /// Const accessor to raw memory as \a T.
    template <typename T>
    const T*
    yyas_ () const YY_NOEXCEPT
    {
      const void *yyp = yybuffer_.yyraw;
      return static_cast<const T*> (yyp);
     }

    /// An auxiliary type to compute the largest semantic type.
    union union_type
    {
      // "42"
      // "0x2a"
      // "4.2"
      // "\"dq-string-literal\""
      // "'sq-string-literal'"
      char dummy1[sizeof (TokenInfo)];

      // mulBinaryOp
      // addBinaryOp
      // cmpBinaryOp
      // eqBinaryOp
      char dummy2[sizeof (pdm::ast::BinaryOperator)];

      // enum_field
      char dummy3[sizeof (pdm::ast::EnumStmt::Field*)];

      // expr
      // parenExpr
      // unitExpr
      // primaryExpr
      // int_expr
      // vparenExpr
      // vtupleExpr
      // vstructExpr
      // ifThenElseExpr
      // chainExpr
      // vlambdaExpr
      // postfixExpr
      // vtcallExpr
      // vvcallExpr
      // dotNmExpr
      // dotIxExpr
      // unaryExpr
      // binaryExpr
      // mulBinaryExpr
      // addBinaryExpr
      // cmpBinaryExpr
      // eqBinaryExpr
      // andBinaryExpr
      // xorBinaryExpr
      // orBinaryExpr
      char dummy4[sizeof (pdm::ast::Exp*)];

      // lpattern
      // lpattern_naked
      char dummy5[sizeof (pdm::ast::LPattern*)];

      // lpatternField
      char dummy6[sizeof (pdm::ast::LPattern::Field*)];

      // script
      char dummy7[sizeof (pdm::ast::Script*)];

      // scriptContentStmt
      // mod_stmt
      // chainPrefixStmt
      // constStmt
      // letStmt
      // varStmt
      // setStmt
      // discardStmt
      // moduleContentStmt
      // fn_stmt
      // type_stmt
      // enum_stmt
      // typeclass_stmt
      // using_stmt
      // importStmt
      char dummy8[sizeof (pdm::ast::Stmt*)];

      // vstructExprField
      char dummy9[sizeof (pdm::ast::StructExp::Field*)];

      // structTypespecField
      char dummy10[sizeof (pdm::ast::StructTypespec::Field*)];

      // ttarg
      // vtarg
      char dummy11[sizeof (pdm::ast::TArg*)];

      // tpattern
      char dummy12[sizeof (pdm::ast::TPattern*)];

      // tpatternField
      char dummy13[sizeof (pdm::ast::TPattern::Field*)];

      // typespec
      // primaryTypespec
      // tupleTypespec
      // mod_prefix_tid
      // postfixTypespec
      // ttcall
      // tdot
      // unaryTypespec
      // long_typespec
      // structTypespec
      char dummy14[sizeof (pdm::ast::Typespec*)];

      // unaryOp
      char dummy15[sizeof (pdm::ast::UnaryOperator)];

      // vpattern
      char dummy16[sizeof (pdm::ast::VPattern*)];

      // vpatternField
      char dummy17[sizeof (pdm::ast::VPattern::Field*)];

      // "<val_id>"
      // "<TypeId>"
      // "<__42__>"
      // tid
      // vid
      // floatl
      // stringl
      char dummy18[sizeof (pdm::parser::TokenInfo)];

      // enum_field_pl
      // unprefixed_enum_field_pl
      char dummy19[sizeof (std::vector<pdm::ast::EnumStmt::Field*>)];

      // expr_cl1
      // expr_cl2
      // expr_sl
      char dummy20[sizeof (std::vector<pdm::ast::Exp*>)];

      // lpatternField_cl
      char dummy21[sizeof (std::vector<pdm::ast::LPattern::Field*>)];

      // scriptContent
      char dummy22[sizeof (std::vector<pdm::ast::Script*>)];

      // moduleContent
      // chainPrefix
      char dummy23[sizeof (std::vector<pdm::ast::Stmt*>)];

      // stringls
      char dummy24[sizeof (std::vector<pdm::ast::StringExp::Piece*>)];

      // vstructExprField_cl
      char dummy25[sizeof (std::vector<pdm::ast::StructExp::Field*>)];

      // structTypespecField_cl
      char dummy26[sizeof (std::vector<pdm::ast::StructTypespec::Field*>)];

      // ttarg_cl
      // vtarg_cl
      char dummy27[sizeof (std::vector<pdm::ast::TArg*>)];

      // tpattern_seq
      char dummy28[sizeof (std::vector<pdm::ast::TPattern*>)];

      // tpatternField_cl
      char dummy29[sizeof (std::vector<pdm::ast::TPattern::Field*>)];

      // typespec_cl1
      // typespec_cl2
      char dummy30[sizeof (std::vector<pdm::ast::Typespec*>)];

      // vpatternField_cl
      char dummy31[sizeof (std::vector<pdm::ast::VPattern::Field*>)];

      // mod_prefix
      char dummy32[sizeof (std::vector<pdm::intern::String>)];
    };

    /// The size of the largest semantic type.
    enum { size = sizeof (union_type) };

    /// A buffer to store semantic values.
    union
    {
      /// Strongest alignment constraints.
      long double yyalign_me;
      /// A buffer large enough to store any of the semantic values.
      char yyraw[size];
    } yybuffer_;
  };

#else
    typedef YYSTYPE semantic_type;
#endif
    /// Symbol locations.
    typedef pdm::source::Loc location_type;

    /// Syntax errors thrown from user actions.
    struct syntax_error : std::runtime_error
    {
      syntax_error (const location_type& l, const std::string& m)
        : std::runtime_error (m)
        , location (l)
      {}

      syntax_error (const syntax_error& s)
        : std::runtime_error (s.what ())
        , location (s.location)
      {}

      ~syntax_error () YY_NOEXCEPT YY_NOTHROW;

      location_type location;
    };

    /// Token kinds.
    struct token
    {
      enum token_kind_type
      {
        YYEMPTY = -2,
    YYEOF = 0,                     // "end of file"
    YYerror = 256,                 // error
    YYUNDEF = 257,                 // "invalid token"
    VID = 258,                     // "<val_id>"
    TID = 259,                     // "<TypeId>"
    HOLE = 260,                    // "<__42__>"
    KW_USING = 261,                // "using"
    KW_MOD = 262,                  // "mod"
    KW_IF = 263,                   // "if"
    KW_THEN = 264,                 // "then"
    KW_ELSE = 265,                 // "else"
    KW_MATCH = 266,                // "match"
    KW_WITH = 267,                 // "with"
    KW_IMPORT = 268,               // "import"
    KW_FROM = 269,                 // "from"
    KW_CONST = 270,                // "const"
    KW_LET = 271,                  // "let"
    KW_VAR = 272,                  // "var"
    KW_SET = 273,                  // "set"
    KW_FN = 274,                   // "fn"
    KW_TYPE = 275,                 // "type"
    KW_ENUM = 276,                 // "enum"
    KW_AND = 277,                  // "and"
    KW_XOR = 278,                  // "xor"
    KW_OR = 279,                   // "or"
    KW_NOT = 280,                  // "not"
    KW_TYPECLASS = 281,            // "typeclass"
    DINT_LIT = 282,                // "42"
    XINT_LIT = 283,                // "0x2a"
    FLOAT_LIT = 284,               // "4.2"
    DQSTRING_LIT = 285,            // "\"dq-string-literal\""
    SQSTRING_LIT = 286,            // "'sq-string-literal'"
    DOT = 287,                     // "."
    COLON = 288,                   // ":"
    COMMA = 289,                   // ","
    SEMICOLON = 290,               // ";"
    DBL_COLON = 291,               // "::"
    LPAREN = 292,                  // "("
    RPAREN = 293,                  // ")"
    LSQBRK = 294,                  // "["
    RSQBRK = 295,                  // "]"
    LCYBRK = 296,                  // "{"
    RCYBRK = 297,                  // "}"
    ARROW = 298,                   // "->"
    ASTERISK = 299,                // "*"
    FSLASH = 300,                  // "/"
    PERCENT = 301,                 // "%"
    PLUS = 302,                    // "+"
    MINUS = 303,                   // "-"
    LTHAN = 304,                   // "<"
    LETHAN = 305,                  // "<="
    GTHAN = 306,                   // ">"
    GETHAN = 307,                  // ">="
    BIND = 308,                    // "="
    EQUALS = 309,                  // "=="
    NEQUALS = 310,                 // "!="
    CARET = 311,                   // "^"
    AMPERSAND = 312,               // "&"
    EXCLAIM = 313,                 // "!"
    PIPE = 314,                    // "|"
    EOS = 315,                     // "EOS"
    NONE = 316                     // "<null>"
      };
      /// Backward compatibility alias (Bison 3.6).
      typedef token_kind_type yytokentype;
    };

    /// Token kind, as returned by yylex.
    typedef token::yytokentype token_kind_type;

    /// Backward compatibility alias (Bison 3.6).
    typedef token_kind_type token_type;

    /// Symbol kinds.
    struct symbol_kind
    {
      enum symbol_kind_type
      {
        YYNTOKENS = 62, ///< Number of tokens.
        S_YYEMPTY = -2,
        S_YYEOF = 0,                             // "end of file"
        S_YYerror = 1,                           // error
        S_YYUNDEF = 2,                           // "invalid token"
        S_VID = 3,                               // "<val_id>"
        S_TID = 4,                               // "<TypeId>"
        S_HOLE = 5,                              // "<__42__>"
        S_KW_USING = 6,                          // "using"
        S_KW_MOD = 7,                            // "mod"
        S_KW_IF = 8,                             // "if"
        S_KW_THEN = 9,                           // "then"
        S_KW_ELSE = 10,                          // "else"
        S_KW_MATCH = 11,                         // "match"
        S_KW_WITH = 12,                          // "with"
        S_KW_IMPORT = 13,                        // "import"
        S_KW_FROM = 14,                          // "from"
        S_KW_CONST = 15,                         // "const"
        S_KW_LET = 16,                           // "let"
        S_KW_VAR = 17,                           // "var"
        S_KW_SET = 18,                           // "set"
        S_KW_FN = 19,                            // "fn"
        S_KW_TYPE = 20,                          // "type"
        S_KW_ENUM = 21,                          // "enum"
        S_KW_AND = 22,                           // "and"
        S_KW_XOR = 23,                           // "xor"
        S_KW_OR = 24,                            // "or"
        S_KW_NOT = 25,                           // "not"
        S_KW_TYPECLASS = 26,                     // "typeclass"
        S_DINT_LIT = 27,                         // "42"
        S_XINT_LIT = 28,                         // "0x2a"
        S_FLOAT_LIT = 29,                        // "4.2"
        S_DQSTRING_LIT = 30,                     // "\"dq-string-literal\""
        S_SQSTRING_LIT = 31,                     // "'sq-string-literal'"
        S_DOT = 32,                              // "."
        S_COLON = 33,                            // ":"
        S_COMMA = 34,                            // ","
        S_SEMICOLON = 35,                        // ";"
        S_DBL_COLON = 36,                        // "::"
        S_LPAREN = 37,                           // "("
        S_RPAREN = 38,                           // ")"
        S_LSQBRK = 39,                           // "["
        S_RSQBRK = 40,                           // "]"
        S_LCYBRK = 41,                           // "{"
        S_RCYBRK = 42,                           // "}"
        S_ARROW = 43,                            // "->"
        S_ASTERISK = 44,                         // "*"
        S_FSLASH = 45,                           // "/"
        S_PERCENT = 46,                          // "%"
        S_PLUS = 47,                             // "+"
        S_MINUS = 48,                            // "-"
        S_LTHAN = 49,                            // "<"
        S_LETHAN = 50,                           // "<="
        S_GTHAN = 51,                            // ">"
        S_GETHAN = 52,                           // ">="
        S_BIND = 53,                             // "="
        S_EQUALS = 54,                           // "=="
        S_NEQUALS = 55,                          // "!="
        S_CARET = 56,                            // "^"
        S_AMPERSAND = 57,                        // "&"
        S_EXCLAIM = 58,                          // "!"
        S_PIPE = 59,                             // "|"
        S_EOS = 60,                              // "EOS"
        S_NONE = 61,                             // "<null>"
        S_YYACCEPT = 62,                         // $accept
        S_script = 63,                           // script
        S_scriptContent = 64,                    // scriptContent
        S_scriptContentStmt = 65,                // scriptContentStmt
        S_mod_stmt = 66,                         // mod_stmt
        S_moduleContent = 67,                    // moduleContent
        S_chainPrefixStmt = 68,                  // chainPrefixStmt
        S_constStmt = 69,                        // constStmt
        S_letStmt = 70,                          // letStmt
        S_varStmt = 71,                          // varStmt
        S_setStmt = 72,                          // setStmt
        S_discardStmt = 73,                      // discardStmt
        S_moduleContentStmt = 74,                // moduleContentStmt
        S_fn_stmt = 75,                          // fn_stmt
        S_type_stmt = 76,                        // type_stmt
        S_enum_stmt = 77,                        // enum_stmt
        S_enum_field_pl = 78,                    // enum_field_pl
        S_unprefixed_enum_field_pl = 79,         // unprefixed_enum_field_pl
        S_enum_field = 80,                       // enum_field
        S_typeclass_stmt = 81,                   // typeclass_stmt
        S_using_stmt = 82,                       // using_stmt
        S_importStmt = 83,                       // importStmt
        S_tid = 84,                              // tid
        S_vid = 85,                              // vid
        S_floatl = 86,                           // floatl
        S_stringl = 87,                          // stringl
        S_expr = 88,                             // expr
        S_expr_cl1 = 89,                         // expr_cl1
        S_expr_cl2 = 90,                         // expr_cl2
        S_expr_sl = 91,                          // expr_sl
        S_parenExpr = 92,                        // parenExpr
        S_unitExpr = 93,                         // unitExpr
        S_primaryExpr = 94,                      // primaryExpr
        S_int_expr = 95,                         // int_expr
        S_stringls = 96,                         // stringls
        S_vparenExpr = 97,                       // vparenExpr
        S_vtupleExpr = 98,                       // vtupleExpr
        S_vstructExpr = 99,                      // vstructExpr
        S_ifThenElseExpr = 100,                  // ifThenElseExpr
        S_chainExpr = 101,                       // chainExpr
        S_chainPrefix = 102,                     // chainPrefix
        S_vlambdaExpr = 103,                     // vlambdaExpr
        S_postfixExpr = 104,                     // postfixExpr
        S_vtcallExpr = 105,                      // vtcallExpr
        S_vvcallExpr = 106,                      // vvcallExpr
        S_dotNmExpr = 107,                       // dotNmExpr
        S_dotIxExpr = 108,                       // dotIxExpr
        S_unaryExpr = 109,                       // unaryExpr
        S_unaryOp = 110,                         // unaryOp
        S_binaryExpr = 111,                      // binaryExpr
        S_mulBinaryOp = 112,                     // mulBinaryOp
        S_mulBinaryExpr = 113,                   // mulBinaryExpr
        S_addBinaryOp = 114,                     // addBinaryOp
        S_addBinaryExpr = 115,                   // addBinaryExpr
        S_cmpBinaryOp = 116,                     // cmpBinaryOp
        S_cmpBinaryExpr = 117,                   // cmpBinaryExpr
        S_eqBinaryOp = 118,                      // eqBinaryOp
        S_eqBinaryExpr = 119,                    // eqBinaryExpr
        S_andBinaryExpr = 120,                   // andBinaryExpr
        S_xorBinaryExpr = 121,                   // xorBinaryExpr
        S_orBinaryExpr = 122,                    // orBinaryExpr
        S_typespec = 123,                        // typespec
        S_typespec_cl1 = 124,                    // typespec_cl1
        S_typespec_cl2 = 125,                    // typespec_cl2
        S_structTypespecField = 126,             // structTypespecField
        S_structTypespecField_cl = 127,          // structTypespecField_cl
        S_primaryTypespec = 128,                 // primaryTypespec
        S_tupleTypespec = 129,                   // tupleTypespec
        S_mod_prefix_tid = 130,                  // mod_prefix_tid
        S_mod_prefix = 131,                      // mod_prefix
        S_postfixTypespec = 132,                 // postfixTypespec
        S_ttcall = 133,                          // ttcall
        S_tdot = 134,                            // tdot
        S_unaryTypespec = 135,                   // unaryTypespec
        S_long_typespec = 136,                   // long_typespec
        S_structTypespec = 137,                  // structTypespec
        S_ttarg = 138,                           // ttarg
        S_ttarg_cl = 139,                        // ttarg_cl
        S_vtarg = 140,                           // vtarg
        S_vtarg_cl = 141,                        // vtarg_cl
        S_vstructExprField = 142,                // vstructExprField
        S_vpatternField = 143,                   // vpatternField
        S_lpatternField = 144,                   // lpatternField
        S_tpatternField = 145,                   // tpatternField
        S_lpattern = 146,                        // lpattern
        S_lpattern_naked = 147,                  // lpattern_naked
        S_vpattern = 148,                        // vpattern
        S_tpattern = 149,                        // tpattern
        S_vpatternField_cl = 150,                // vpatternField_cl
        S_lpatternField_cl = 151,                // lpatternField_cl
        S_tpatternField_cl = 152,                // tpatternField_cl
        S_vstructExprField_cl = 153,             // vstructExprField_cl
        S_tpattern_seq = 154                     // tpattern_seq
      };
    };

    /// (Internal) symbol kind.
    typedef symbol_kind::symbol_kind_type symbol_kind_type;

    /// The number of tokens.
    static const symbol_kind_type YYNTOKENS = symbol_kind::YYNTOKENS;

    /// A complete symbol.
    ///
    /// Expects its Base type to provide access to the symbol kind
    /// via kind ().
    ///
    /// Provide access to semantic value and location.
    template <typename Base>
    struct basic_symbol : Base
    {
      /// Alias to Base.
      typedef Base super_type;

      /// Default constructor.
      basic_symbol ()
        : value ()
        , location ()
      {}

#if 201103L <= YY_CPLUSPLUS
      /// Move constructor.
      basic_symbol (basic_symbol&& that)
        : Base (std::move (that))
        , value ()
        , location (std::move (that.location))
      {
        switch (this->kind ())
    {
      case symbol_kind::S_DINT_LIT: // "42"
      case symbol_kind::S_XINT_LIT: // "0x2a"
      case symbol_kind::S_FLOAT_LIT: // "4.2"
      case symbol_kind::S_DQSTRING_LIT: // "\"dq-string-literal\""
      case symbol_kind::S_SQSTRING_LIT: // "'sq-string-literal'"
        value.move< TokenInfo > (std::move (that.value));
        break;

      case symbol_kind::S_mulBinaryOp: // mulBinaryOp
      case symbol_kind::S_addBinaryOp: // addBinaryOp
      case symbol_kind::S_cmpBinaryOp: // cmpBinaryOp
      case symbol_kind::S_eqBinaryOp: // eqBinaryOp
        value.move< pdm::ast::BinaryOperator > (std::move (that.value));
        break;

      case symbol_kind::S_enum_field: // enum_field
        value.move< pdm::ast::EnumStmt::Field* > (std::move (that.value));
        break;

      case symbol_kind::S_expr: // expr
      case symbol_kind::S_parenExpr: // parenExpr
      case symbol_kind::S_unitExpr: // unitExpr
      case symbol_kind::S_primaryExpr: // primaryExpr
      case symbol_kind::S_int_expr: // int_expr
      case symbol_kind::S_vparenExpr: // vparenExpr
      case symbol_kind::S_vtupleExpr: // vtupleExpr
      case symbol_kind::S_vstructExpr: // vstructExpr
      case symbol_kind::S_ifThenElseExpr: // ifThenElseExpr
      case symbol_kind::S_chainExpr: // chainExpr
      case symbol_kind::S_vlambdaExpr: // vlambdaExpr
      case symbol_kind::S_postfixExpr: // postfixExpr
      case symbol_kind::S_vtcallExpr: // vtcallExpr
      case symbol_kind::S_vvcallExpr: // vvcallExpr
      case symbol_kind::S_dotNmExpr: // dotNmExpr
      case symbol_kind::S_dotIxExpr: // dotIxExpr
      case symbol_kind::S_unaryExpr: // unaryExpr
      case symbol_kind::S_binaryExpr: // binaryExpr
      case symbol_kind::S_mulBinaryExpr: // mulBinaryExpr
      case symbol_kind::S_addBinaryExpr: // addBinaryExpr
      case symbol_kind::S_cmpBinaryExpr: // cmpBinaryExpr
      case symbol_kind::S_eqBinaryExpr: // eqBinaryExpr
      case symbol_kind::S_andBinaryExpr: // andBinaryExpr
      case symbol_kind::S_xorBinaryExpr: // xorBinaryExpr
      case symbol_kind::S_orBinaryExpr: // orBinaryExpr
        value.move< pdm::ast::Exp* > (std::move (that.value));
        break;

      case symbol_kind::S_lpattern: // lpattern
      case symbol_kind::S_lpattern_naked: // lpattern_naked
        value.move< pdm::ast::LPattern* > (std::move (that.value));
        break;

      case symbol_kind::S_lpatternField: // lpatternField
        value.move< pdm::ast::LPattern::Field* > (std::move (that.value));
        break;

      case symbol_kind::S_script: // script
        value.move< pdm::ast::Script* > (std::move (that.value));
        break;

      case symbol_kind::S_scriptContentStmt: // scriptContentStmt
      case symbol_kind::S_mod_stmt: // mod_stmt
      case symbol_kind::S_chainPrefixStmt: // chainPrefixStmt
      case symbol_kind::S_constStmt: // constStmt
      case symbol_kind::S_letStmt: // letStmt
      case symbol_kind::S_varStmt: // varStmt
      case symbol_kind::S_setStmt: // setStmt
      case symbol_kind::S_discardStmt: // discardStmt
      case symbol_kind::S_moduleContentStmt: // moduleContentStmt
      case symbol_kind::S_fn_stmt: // fn_stmt
      case symbol_kind::S_type_stmt: // type_stmt
      case symbol_kind::S_enum_stmt: // enum_stmt
      case symbol_kind::S_typeclass_stmt: // typeclass_stmt
      case symbol_kind::S_using_stmt: // using_stmt
      case symbol_kind::S_importStmt: // importStmt
        value.move< pdm::ast::Stmt* > (std::move (that.value));
        break;

      case symbol_kind::S_vstructExprField: // vstructExprField
        value.move< pdm::ast::StructExp::Field* > (std::move (that.value));
        break;

      case symbol_kind::S_structTypespecField: // structTypespecField
        value.move< pdm::ast::StructTypespec::Field* > (std::move (that.value));
        break;

      case symbol_kind::S_ttarg: // ttarg
      case symbol_kind::S_vtarg: // vtarg
        value.move< pdm::ast::TArg* > (std::move (that.value));
        break;

      case symbol_kind::S_tpattern: // tpattern
        value.move< pdm::ast::TPattern* > (std::move (that.value));
        break;

      case symbol_kind::S_tpatternField: // tpatternField
        value.move< pdm::ast::TPattern::Field* > (std::move (that.value));
        break;

      case symbol_kind::S_typespec: // typespec
      case symbol_kind::S_primaryTypespec: // primaryTypespec
      case symbol_kind::S_tupleTypespec: // tupleTypespec
      case symbol_kind::S_mod_prefix_tid: // mod_prefix_tid
      case symbol_kind::S_postfixTypespec: // postfixTypespec
      case symbol_kind::S_ttcall: // ttcall
      case symbol_kind::S_tdot: // tdot
      case symbol_kind::S_unaryTypespec: // unaryTypespec
      case symbol_kind::S_long_typespec: // long_typespec
      case symbol_kind::S_structTypespec: // structTypespec
        value.move< pdm::ast::Typespec* > (std::move (that.value));
        break;

      case symbol_kind::S_unaryOp: // unaryOp
        value.move< pdm::ast::UnaryOperator > (std::move (that.value));
        break;

      case symbol_kind::S_vpattern: // vpattern
        value.move< pdm::ast::VPattern* > (std::move (that.value));
        break;

      case symbol_kind::S_vpatternField: // vpatternField
        value.move< pdm::ast::VPattern::Field* > (std::move (that.value));
        break;

      case symbol_kind::S_VID: // "<val_id>"
      case symbol_kind::S_TID: // "<TypeId>"
      case symbol_kind::S_HOLE: // "<__42__>"
      case symbol_kind::S_tid: // tid
      case symbol_kind::S_vid: // vid
      case symbol_kind::S_floatl: // floatl
      case symbol_kind::S_stringl: // stringl
        value.move< pdm::parser::TokenInfo > (std::move (that.value));
        break;

      case symbol_kind::S_enum_field_pl: // enum_field_pl
      case symbol_kind::S_unprefixed_enum_field_pl: // unprefixed_enum_field_pl
        value.move< std::vector<pdm::ast::EnumStmt::Field*> > (std::move (that.value));
        break;

      case symbol_kind::S_expr_cl1: // expr_cl1
      case symbol_kind::S_expr_cl2: // expr_cl2
      case symbol_kind::S_expr_sl: // expr_sl
        value.move< std::vector<pdm::ast::Exp*> > (std::move (that.value));
        break;

      case symbol_kind::S_lpatternField_cl: // lpatternField_cl
        value.move< std::vector<pdm::ast::LPattern::Field*> > (std::move (that.value));
        break;

      case symbol_kind::S_scriptContent: // scriptContent
        value.move< std::vector<pdm::ast::Script*> > (std::move (that.value));
        break;

      case symbol_kind::S_moduleContent: // moduleContent
      case symbol_kind::S_chainPrefix: // chainPrefix
        value.move< std::vector<pdm::ast::Stmt*> > (std::move (that.value));
        break;

      case symbol_kind::S_stringls: // stringls
        value.move< std::vector<pdm::ast::StringExp::Piece*> > (std::move (that.value));
        break;

      case symbol_kind::S_vstructExprField_cl: // vstructExprField_cl
        value.move< std::vector<pdm::ast::StructExp::Field*> > (std::move (that.value));
        break;

      case symbol_kind::S_structTypespecField_cl: // structTypespecField_cl
        value.move< std::vector<pdm::ast::StructTypespec::Field*> > (std::move (that.value));
        break;

      case symbol_kind::S_ttarg_cl: // ttarg_cl
      case symbol_kind::S_vtarg_cl: // vtarg_cl
        value.move< std::vector<pdm::ast::TArg*> > (std::move (that.value));
        break;

      case symbol_kind::S_tpattern_seq: // tpattern_seq
        value.move< std::vector<pdm::ast::TPattern*> > (std::move (that.value));
        break;

      case symbol_kind::S_tpatternField_cl: // tpatternField_cl
        value.move< std::vector<pdm::ast::TPattern::Field*> > (std::move (that.value));
        break;

      case symbol_kind::S_typespec_cl1: // typespec_cl1
      case symbol_kind::S_typespec_cl2: // typespec_cl2
        value.move< std::vector<pdm::ast::Typespec*> > (std::move (that.value));
        break;

      case symbol_kind::S_vpatternField_cl: // vpatternField_cl
        value.move< std::vector<pdm::ast::VPattern::Field*> > (std::move (that.value));
        break;

      case symbol_kind::S_mod_prefix: // mod_prefix
        value.move< std::vector<pdm::intern::String> > (std::move (that.value));
        break;

      default:
        break;
    }

      }
#endif

      /// Copy constructor.
      basic_symbol (const basic_symbol& that);

      /// Constructor for valueless symbols, and symbols from each type.
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, location_type&& l)
        : Base (t)
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const location_type& l)
        : Base (t)
        , location (l)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, TokenInfo&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const TokenInfo& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, pdm::ast::BinaryOperator&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const pdm::ast::BinaryOperator& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, pdm::ast::EnumStmt::Field*&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const pdm::ast::EnumStmt::Field*& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, pdm::ast::Exp*&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const pdm::ast::Exp*& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, pdm::ast::LPattern*&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const pdm::ast::LPattern*& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, pdm::ast::LPattern::Field*&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const pdm::ast::LPattern::Field*& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, pdm::ast::Script*&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const pdm::ast::Script*& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, pdm::ast::Stmt*&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const pdm::ast::Stmt*& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, pdm::ast::StructExp::Field*&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const pdm::ast::StructExp::Field*& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, pdm::ast::StructTypespec::Field*&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const pdm::ast::StructTypespec::Field*& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, pdm::ast::TArg*&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const pdm::ast::TArg*& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, pdm::ast::TPattern*&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const pdm::ast::TPattern*& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, pdm::ast::TPattern::Field*&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const pdm::ast::TPattern::Field*& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, pdm::ast::Typespec*&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const pdm::ast::Typespec*& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, pdm::ast::UnaryOperator&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const pdm::ast::UnaryOperator& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, pdm::ast::VPattern*&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const pdm::ast::VPattern*& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, pdm::ast::VPattern::Field*&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const pdm::ast::VPattern::Field*& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, pdm::parser::TokenInfo&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const pdm::parser::TokenInfo& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, std::vector<pdm::ast::EnumStmt::Field*>&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const std::vector<pdm::ast::EnumStmt::Field*>& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, std::vector<pdm::ast::Exp*>&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const std::vector<pdm::ast::Exp*>& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, std::vector<pdm::ast::LPattern::Field*>&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const std::vector<pdm::ast::LPattern::Field*>& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, std::vector<pdm::ast::Script*>&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const std::vector<pdm::ast::Script*>& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, std::vector<pdm::ast::Stmt*>&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const std::vector<pdm::ast::Stmt*>& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, std::vector<pdm::ast::StringExp::Piece*>&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const std::vector<pdm::ast::StringExp::Piece*>& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, std::vector<pdm::ast::StructExp::Field*>&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const std::vector<pdm::ast::StructExp::Field*>& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, std::vector<pdm::ast::StructTypespec::Field*>&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const std::vector<pdm::ast::StructTypespec::Field*>& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, std::vector<pdm::ast::TArg*>&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const std::vector<pdm::ast::TArg*>& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, std::vector<pdm::ast::TPattern*>&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const std::vector<pdm::ast::TPattern*>& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, std::vector<pdm::ast::TPattern::Field*>&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const std::vector<pdm::ast::TPattern::Field*>& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, std::vector<pdm::ast::Typespec*>&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const std::vector<pdm::ast::Typespec*>& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, std::vector<pdm::ast::VPattern::Field*>&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const std::vector<pdm::ast::VPattern::Field*>& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, std::vector<pdm::intern::String>&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const std::vector<pdm::intern::String>& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

      /// Destroy the symbol.
      ~basic_symbol ()
      {
        clear ();
      }

      /// Destroy contents, and record that is empty.
      void clear ()
      {
        // User destructor.
        symbol_kind_type yykind = this->kind ();
        basic_symbol<Base>& yysym = *this;
        (void) yysym;
        switch (yykind)
        {
       default:
          break;
        }

        // Value type destructor.
switch (yykind)
    {
      case symbol_kind::S_DINT_LIT: // "42"
      case symbol_kind::S_XINT_LIT: // "0x2a"
      case symbol_kind::S_FLOAT_LIT: // "4.2"
      case symbol_kind::S_DQSTRING_LIT: // "\"dq-string-literal\""
      case symbol_kind::S_SQSTRING_LIT: // "'sq-string-literal'"
        value.template destroy< TokenInfo > ();
        break;

      case symbol_kind::S_mulBinaryOp: // mulBinaryOp
      case symbol_kind::S_addBinaryOp: // addBinaryOp
      case symbol_kind::S_cmpBinaryOp: // cmpBinaryOp
      case symbol_kind::S_eqBinaryOp: // eqBinaryOp
        value.template destroy< pdm::ast::BinaryOperator > ();
        break;

      case symbol_kind::S_enum_field: // enum_field
        value.template destroy< pdm::ast::EnumStmt::Field* > ();
        break;

      case symbol_kind::S_expr: // expr
      case symbol_kind::S_parenExpr: // parenExpr
      case symbol_kind::S_unitExpr: // unitExpr
      case symbol_kind::S_primaryExpr: // primaryExpr
      case symbol_kind::S_int_expr: // int_expr
      case symbol_kind::S_vparenExpr: // vparenExpr
      case symbol_kind::S_vtupleExpr: // vtupleExpr
      case symbol_kind::S_vstructExpr: // vstructExpr
      case symbol_kind::S_ifThenElseExpr: // ifThenElseExpr
      case symbol_kind::S_chainExpr: // chainExpr
      case symbol_kind::S_vlambdaExpr: // vlambdaExpr
      case symbol_kind::S_postfixExpr: // postfixExpr
      case symbol_kind::S_vtcallExpr: // vtcallExpr
      case symbol_kind::S_vvcallExpr: // vvcallExpr
      case symbol_kind::S_dotNmExpr: // dotNmExpr
      case symbol_kind::S_dotIxExpr: // dotIxExpr
      case symbol_kind::S_unaryExpr: // unaryExpr
      case symbol_kind::S_binaryExpr: // binaryExpr
      case symbol_kind::S_mulBinaryExpr: // mulBinaryExpr
      case symbol_kind::S_addBinaryExpr: // addBinaryExpr
      case symbol_kind::S_cmpBinaryExpr: // cmpBinaryExpr
      case symbol_kind::S_eqBinaryExpr: // eqBinaryExpr
      case symbol_kind::S_andBinaryExpr: // andBinaryExpr
      case symbol_kind::S_xorBinaryExpr: // xorBinaryExpr
      case symbol_kind::S_orBinaryExpr: // orBinaryExpr
        value.template destroy< pdm::ast::Exp* > ();
        break;

      case symbol_kind::S_lpattern: // lpattern
      case symbol_kind::S_lpattern_naked: // lpattern_naked
        value.template destroy< pdm::ast::LPattern* > ();
        break;

      case symbol_kind::S_lpatternField: // lpatternField
        value.template destroy< pdm::ast::LPattern::Field* > ();
        break;

      case symbol_kind::S_script: // script
        value.template destroy< pdm::ast::Script* > ();
        break;

      case symbol_kind::S_scriptContentStmt: // scriptContentStmt
      case symbol_kind::S_mod_stmt: // mod_stmt
      case symbol_kind::S_chainPrefixStmt: // chainPrefixStmt
      case symbol_kind::S_constStmt: // constStmt
      case symbol_kind::S_letStmt: // letStmt
      case symbol_kind::S_varStmt: // varStmt
      case symbol_kind::S_setStmt: // setStmt
      case symbol_kind::S_discardStmt: // discardStmt
      case symbol_kind::S_moduleContentStmt: // moduleContentStmt
      case symbol_kind::S_fn_stmt: // fn_stmt
      case symbol_kind::S_type_stmt: // type_stmt
      case symbol_kind::S_enum_stmt: // enum_stmt
      case symbol_kind::S_typeclass_stmt: // typeclass_stmt
      case symbol_kind::S_using_stmt: // using_stmt
      case symbol_kind::S_importStmt: // importStmt
        value.template destroy< pdm::ast::Stmt* > ();
        break;

      case symbol_kind::S_vstructExprField: // vstructExprField
        value.template destroy< pdm::ast::StructExp::Field* > ();
        break;

      case symbol_kind::S_structTypespecField: // structTypespecField
        value.template destroy< pdm::ast::StructTypespec::Field* > ();
        break;

      case symbol_kind::S_ttarg: // ttarg
      case symbol_kind::S_vtarg: // vtarg
        value.template destroy< pdm::ast::TArg* > ();
        break;

      case symbol_kind::S_tpattern: // tpattern
        value.template destroy< pdm::ast::TPattern* > ();
        break;

      case symbol_kind::S_tpatternField: // tpatternField
        value.template destroy< pdm::ast::TPattern::Field* > ();
        break;

      case symbol_kind::S_typespec: // typespec
      case symbol_kind::S_primaryTypespec: // primaryTypespec
      case symbol_kind::S_tupleTypespec: // tupleTypespec
      case symbol_kind::S_mod_prefix_tid: // mod_prefix_tid
      case symbol_kind::S_postfixTypespec: // postfixTypespec
      case symbol_kind::S_ttcall: // ttcall
      case symbol_kind::S_tdot: // tdot
      case symbol_kind::S_unaryTypespec: // unaryTypespec
      case symbol_kind::S_long_typespec: // long_typespec
      case symbol_kind::S_structTypespec: // structTypespec
        value.template destroy< pdm::ast::Typespec* > ();
        break;

      case symbol_kind::S_unaryOp: // unaryOp
        value.template destroy< pdm::ast::UnaryOperator > ();
        break;

      case symbol_kind::S_vpattern: // vpattern
        value.template destroy< pdm::ast::VPattern* > ();
        break;

      case symbol_kind::S_vpatternField: // vpatternField
        value.template destroy< pdm::ast::VPattern::Field* > ();
        break;

      case symbol_kind::S_VID: // "<val_id>"
      case symbol_kind::S_TID: // "<TypeId>"
      case symbol_kind::S_HOLE: // "<__42__>"
      case symbol_kind::S_tid: // tid
      case symbol_kind::S_vid: // vid
      case symbol_kind::S_floatl: // floatl
      case symbol_kind::S_stringl: // stringl
        value.template destroy< pdm::parser::TokenInfo > ();
        break;

      case symbol_kind::S_enum_field_pl: // enum_field_pl
      case symbol_kind::S_unprefixed_enum_field_pl: // unprefixed_enum_field_pl
        value.template destroy< std::vector<pdm::ast::EnumStmt::Field*> > ();
        break;

      case symbol_kind::S_expr_cl1: // expr_cl1
      case symbol_kind::S_expr_cl2: // expr_cl2
      case symbol_kind::S_expr_sl: // expr_sl
        value.template destroy< std::vector<pdm::ast::Exp*> > ();
        break;

      case symbol_kind::S_lpatternField_cl: // lpatternField_cl
        value.template destroy< std::vector<pdm::ast::LPattern::Field*> > ();
        break;

      case symbol_kind::S_scriptContent: // scriptContent
        value.template destroy< std::vector<pdm::ast::Script*> > ();
        break;

      case symbol_kind::S_moduleContent: // moduleContent
      case symbol_kind::S_chainPrefix: // chainPrefix
        value.template destroy< std::vector<pdm::ast::Stmt*> > ();
        break;

      case symbol_kind::S_stringls: // stringls
        value.template destroy< std::vector<pdm::ast::StringExp::Piece*> > ();
        break;

      case symbol_kind::S_vstructExprField_cl: // vstructExprField_cl
        value.template destroy< std::vector<pdm::ast::StructExp::Field*> > ();
        break;

      case symbol_kind::S_structTypespecField_cl: // structTypespecField_cl
        value.template destroy< std::vector<pdm::ast::StructTypespec::Field*> > ();
        break;

      case symbol_kind::S_ttarg_cl: // ttarg_cl
      case symbol_kind::S_vtarg_cl: // vtarg_cl
        value.template destroy< std::vector<pdm::ast::TArg*> > ();
        break;

      case symbol_kind::S_tpattern_seq: // tpattern_seq
        value.template destroy< std::vector<pdm::ast::TPattern*> > ();
        break;

      case symbol_kind::S_tpatternField_cl: // tpatternField_cl
        value.template destroy< std::vector<pdm::ast::TPattern::Field*> > ();
        break;

      case symbol_kind::S_typespec_cl1: // typespec_cl1
      case symbol_kind::S_typespec_cl2: // typespec_cl2
        value.template destroy< std::vector<pdm::ast::Typespec*> > ();
        break;

      case symbol_kind::S_vpatternField_cl: // vpatternField_cl
        value.template destroy< std::vector<pdm::ast::VPattern::Field*> > ();
        break;

      case symbol_kind::S_mod_prefix: // mod_prefix
        value.template destroy< std::vector<pdm::intern::String> > ();
        break;

      default:
        break;
    }

        Base::clear ();
      }

#if YYDEBUG || 0
      /// The user-facing name of this symbol.
      const char *name () const YY_NOEXCEPT
      {
        return parser::symbol_name (this->kind ());
      }
#endif // #if YYDEBUG || 0


      /// Backward compatibility (Bison 3.6).
      symbol_kind_type type_get () const YY_NOEXCEPT;

      /// Whether empty.
      bool empty () const YY_NOEXCEPT;

      /// Destructive move, \a s is emptied into this.
      void move (basic_symbol& s);

      /// The semantic value.
      semantic_type value;

      /// The location.
      location_type location;

    private:
#if YY_CPLUSPLUS < 201103L
      /// Assignment operator.
      basic_symbol& operator= (const basic_symbol& that);
#endif
    };

    /// Type access provider for token (enum) based symbols.
    struct by_kind
    {
      /// Default constructor.
      by_kind ();

#if 201103L <= YY_CPLUSPLUS
      /// Move constructor.
      by_kind (by_kind&& that);
#endif

      /// Copy constructor.
      by_kind (const by_kind& that);

      /// The symbol kind as needed by the constructor.
      typedef token_kind_type kind_type;

      /// Constructor from (external) token numbers.
      by_kind (kind_type t);

      /// Record that this symbol is empty.
      void clear ();

      /// Steal the symbol kind from \a that.
      void move (by_kind& that);

      /// The (internal) type number (corresponding to \a type).
      /// \a empty when empty.
      symbol_kind_type kind () const YY_NOEXCEPT;

      /// Backward compatibility (Bison 3.6).
      symbol_kind_type type_get () const YY_NOEXCEPT;

      /// The symbol kind.
      /// \a S_YYEMPTY when empty.
      symbol_kind_type kind_;
    };

    /// Backward compatibility for a private implementation detail (Bison 3.6).
    typedef by_kind by_type;

    /// "External" symbols: returned by the scanner.
    struct symbol_type : basic_symbol<by_kind>
    {
      /// Superclass.
      typedef basic_symbol<by_kind> super_type;

      /// Empty symbol.
      symbol_type () {}

      /// Constructor for valueless symbols, and symbols from each type.
#if 201103L <= YY_CPLUSPLUS
      symbol_type (int tok, location_type l)
        : super_type(token_type (tok), std::move (l))
      {
        YY_ASSERT (tok == token::YYEOF || tok == token::YYerror || tok == token::YYUNDEF || tok == token::KW_USING || tok == token::KW_MOD || tok == token::KW_IF || tok == token::KW_THEN || tok == token::KW_ELSE || tok == token::KW_MATCH || tok == token::KW_WITH || tok == token::KW_IMPORT || tok == token::KW_FROM || tok == token::KW_CONST || tok == token::KW_LET || tok == token::KW_VAR || tok == token::KW_SET || tok == token::KW_FN || tok == token::KW_TYPE || tok == token::KW_ENUM || tok == token::KW_AND || tok == token::KW_XOR || tok == token::KW_OR || tok == token::KW_NOT || tok == token::KW_TYPECLASS || tok == token::DOT || tok == token::COLON || tok == token::COMMA || tok == token::SEMICOLON || tok == token::DBL_COLON || tok == token::LPAREN || tok == token::RPAREN || tok == token::LSQBRK || tok == token::RSQBRK || tok == token::LCYBRK || tok == token::RCYBRK || tok == token::ARROW || tok == token::ASTERISK || tok == token::FSLASH || tok == token::PERCENT || tok == token::PLUS || tok == token::MINUS || tok == token::LTHAN || tok == token::LETHAN || tok == token::GTHAN || tok == token::GETHAN || tok == token::BIND || tok == token::EQUALS || tok == token::NEQUALS || tok == token::CARET || tok == token::AMPERSAND || tok == token::EXCLAIM || tok == token::PIPE || tok == token::EOS || tok == token::NONE);
      }
#else
      symbol_type (int tok, const location_type& l)
        : super_type(token_type (tok), l)
      {
        YY_ASSERT (tok == token::YYEOF || tok == token::YYerror || tok == token::YYUNDEF || tok == token::KW_USING || tok == token::KW_MOD || tok == token::KW_IF || tok == token::KW_THEN || tok == token::KW_ELSE || tok == token::KW_MATCH || tok == token::KW_WITH || tok == token::KW_IMPORT || tok == token::KW_FROM || tok == token::KW_CONST || tok == token::KW_LET || tok == token::KW_VAR || tok == token::KW_SET || tok == token::KW_FN || tok == token::KW_TYPE || tok == token::KW_ENUM || tok == token::KW_AND || tok == token::KW_XOR || tok == token::KW_OR || tok == token::KW_NOT || tok == token::KW_TYPECLASS || tok == token::DOT || tok == token::COLON || tok == token::COMMA || tok == token::SEMICOLON || tok == token::DBL_COLON || tok == token::LPAREN || tok == token::RPAREN || tok == token::LSQBRK || tok == token::RSQBRK || tok == token::LCYBRK || tok == token::RCYBRK || tok == token::ARROW || tok == token::ASTERISK || tok == token::FSLASH || tok == token::PERCENT || tok == token::PLUS || tok == token::MINUS || tok == token::LTHAN || tok == token::LETHAN || tok == token::GTHAN || tok == token::GETHAN || tok == token::BIND || tok == token::EQUALS || tok == token::NEQUALS || tok == token::CARET || tok == token::AMPERSAND || tok == token::EXCLAIM || tok == token::PIPE || tok == token::EOS || tok == token::NONE);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      symbol_type (int tok, TokenInfo v, location_type l)
        : super_type(token_type (tok), std::move (v), std::move (l))
      {
        YY_ASSERT (tok == token::DINT_LIT || tok == token::XINT_LIT || tok == token::FLOAT_LIT || tok == token::DQSTRING_LIT || tok == token::SQSTRING_LIT);
      }
#else
      symbol_type (int tok, const TokenInfo& v, const location_type& l)
        : super_type(token_type (tok), v, l)
      {
        YY_ASSERT (tok == token::DINT_LIT || tok == token::XINT_LIT || tok == token::FLOAT_LIT || tok == token::DQSTRING_LIT || tok == token::SQSTRING_LIT);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      symbol_type (int tok, pdm::parser::TokenInfo v, location_type l)
        : super_type(token_type (tok), std::move (v), std::move (l))
      {
        YY_ASSERT (tok == token::VID || tok == token::TID || tok == token::HOLE);
      }
#else
      symbol_type (int tok, const pdm::parser::TokenInfo& v, const location_type& l)
        : super_type(token_type (tok), v, l)
      {
        YY_ASSERT (tok == token::VID || tok == token::TID || tok == token::HOLE);
      }
#endif
    };

    /// Build a parser object.
    parser (pdm::source::Source* source_yyarg, pdm::parser::Lexer* lexer_yyarg, pdm::ast::Manager* mgr_yyarg, pdm::ast::Script** returnp_yyarg);
    virtual ~parser ();

#if 201103L <= YY_CPLUSPLUS
    /// Non copyable.
    parser (const parser&) = delete;
    /// Non copyable.
    parser& operator= (const parser&) = delete;
#endif

    /// Parse.  An alias for parse ().
    /// \returns  0 iff parsing succeeded.
    int operator() ();

    /// Parse.
    /// \returns  0 iff parsing succeeded.
    virtual int parse ();

#if YYDEBUG
    /// The current debugging stream.
    std::ostream& debug_stream () const YY_ATTRIBUTE_PURE;
    /// Set the current debugging stream.
    void set_debug_stream (std::ostream &);

    /// Type for debugging levels.
    typedef int debug_level_type;
    /// The current debugging level.
    debug_level_type debug_level () const YY_ATTRIBUTE_PURE;
    /// Set the current debugging level.
    void set_debug_level (debug_level_type l);
#endif

    /// Report a syntax error.
    /// \param loc    where the syntax error is found.
    /// \param msg    a description of the syntax error.
    virtual void error (const location_type& loc, const std::string& msg);

    /// Report a syntax error.
    void error (const syntax_error& err);

#if YYDEBUG || 0
    /// The user-facing name of the symbol whose (internal) number is
    /// YYSYMBOL.  No bounds checking.
    static const char *symbol_name (symbol_kind_type yysymbol);
#endif // #if YYDEBUG || 0


    // Implementation of make_symbol for each symbol type.
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_YYEOF (location_type l)
      {
        return symbol_type (token::YYEOF, std::move (l));
      }
#else
      static
      symbol_type
      make_YYEOF (const location_type& l)
      {
        return symbol_type (token::YYEOF, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_YYerror (location_type l)
      {
        return symbol_type (token::YYerror, std::move (l));
      }
#else
      static
      symbol_type
      make_YYerror (const location_type& l)
      {
        return symbol_type (token::YYerror, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_YYUNDEF (location_type l)
      {
        return symbol_type (token::YYUNDEF, std::move (l));
      }
#else
      static
      symbol_type
      make_YYUNDEF (const location_type& l)
      {
        return symbol_type (token::YYUNDEF, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_VID (pdm::parser::TokenInfo v, location_type l)
      {
        return symbol_type (token::VID, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_VID (const pdm::parser::TokenInfo& v, const location_type& l)
      {
        return symbol_type (token::VID, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TID (pdm::parser::TokenInfo v, location_type l)
      {
        return symbol_type (token::TID, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_TID (const pdm::parser::TokenInfo& v, const location_type& l)
      {
        return symbol_type (token::TID, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_HOLE (pdm::parser::TokenInfo v, location_type l)
      {
        return symbol_type (token::HOLE, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_HOLE (const pdm::parser::TokenInfo& v, const location_type& l)
      {
        return symbol_type (token::HOLE, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_KW_USING (location_type l)
      {
        return symbol_type (token::KW_USING, std::move (l));
      }
#else
      static
      symbol_type
      make_KW_USING (const location_type& l)
      {
        return symbol_type (token::KW_USING, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_KW_MOD (location_type l)
      {
        return symbol_type (token::KW_MOD, std::move (l));
      }
#else
      static
      symbol_type
      make_KW_MOD (const location_type& l)
      {
        return symbol_type (token::KW_MOD, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_KW_IF (location_type l)
      {
        return symbol_type (token::KW_IF, std::move (l));
      }
#else
      static
      symbol_type
      make_KW_IF (const location_type& l)
      {
        return symbol_type (token::KW_IF, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_KW_THEN (location_type l)
      {
        return symbol_type (token::KW_THEN, std::move (l));
      }
#else
      static
      symbol_type
      make_KW_THEN (const location_type& l)
      {
        return symbol_type (token::KW_THEN, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_KW_ELSE (location_type l)
      {
        return symbol_type (token::KW_ELSE, std::move (l));
      }
#else
      static
      symbol_type
      make_KW_ELSE (const location_type& l)
      {
        return symbol_type (token::KW_ELSE, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_KW_MATCH (location_type l)
      {
        return symbol_type (token::KW_MATCH, std::move (l));
      }
#else
      static
      symbol_type
      make_KW_MATCH (const location_type& l)
      {
        return symbol_type (token::KW_MATCH, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_KW_WITH (location_type l)
      {
        return symbol_type (token::KW_WITH, std::move (l));
      }
#else
      static
      symbol_type
      make_KW_WITH (const location_type& l)
      {
        return symbol_type (token::KW_WITH, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_KW_IMPORT (location_type l)
      {
        return symbol_type (token::KW_IMPORT, std::move (l));
      }
#else
      static
      symbol_type
      make_KW_IMPORT (const location_type& l)
      {
        return symbol_type (token::KW_IMPORT, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_KW_FROM (location_type l)
      {
        return symbol_type (token::KW_FROM, std::move (l));
      }
#else
      static
      symbol_type
      make_KW_FROM (const location_type& l)
      {
        return symbol_type (token::KW_FROM, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_KW_CONST (location_type l)
      {
        return symbol_type (token::KW_CONST, std::move (l));
      }
#else
      static
      symbol_type
      make_KW_CONST (const location_type& l)
      {
        return symbol_type (token::KW_CONST, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_KW_LET (location_type l)
      {
        return symbol_type (token::KW_LET, std::move (l));
      }
#else
      static
      symbol_type
      make_KW_LET (const location_type& l)
      {
        return symbol_type (token::KW_LET, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_KW_VAR (location_type l)
      {
        return symbol_type (token::KW_VAR, std::move (l));
      }
#else
      static
      symbol_type
      make_KW_VAR (const location_type& l)
      {
        return symbol_type (token::KW_VAR, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_KW_SET (location_type l)
      {
        return symbol_type (token::KW_SET, std::move (l));
      }
#else
      static
      symbol_type
      make_KW_SET (const location_type& l)
      {
        return symbol_type (token::KW_SET, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_KW_FN (location_type l)
      {
        return symbol_type (token::KW_FN, std::move (l));
      }
#else
      static
      symbol_type
      make_KW_FN (const location_type& l)
      {
        return symbol_type (token::KW_FN, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_KW_TYPE (location_type l)
      {
        return symbol_type (token::KW_TYPE, std::move (l));
      }
#else
      static
      symbol_type
      make_KW_TYPE (const location_type& l)
      {
        return symbol_type (token::KW_TYPE, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_KW_ENUM (location_type l)
      {
        return symbol_type (token::KW_ENUM, std::move (l));
      }
#else
      static
      symbol_type
      make_KW_ENUM (const location_type& l)
      {
        return symbol_type (token::KW_ENUM, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_KW_AND (location_type l)
      {
        return symbol_type (token::KW_AND, std::move (l));
      }
#else
      static
      symbol_type
      make_KW_AND (const location_type& l)
      {
        return symbol_type (token::KW_AND, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_KW_XOR (location_type l)
      {
        return symbol_type (token::KW_XOR, std::move (l));
      }
#else
      static
      symbol_type
      make_KW_XOR (const location_type& l)
      {
        return symbol_type (token::KW_XOR, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_KW_OR (location_type l)
      {
        return symbol_type (token::KW_OR, std::move (l));
      }
#else
      static
      symbol_type
      make_KW_OR (const location_type& l)
      {
        return symbol_type (token::KW_OR, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_KW_NOT (location_type l)
      {
        return symbol_type (token::KW_NOT, std::move (l));
      }
#else
      static
      symbol_type
      make_KW_NOT (const location_type& l)
      {
        return symbol_type (token::KW_NOT, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_KW_TYPECLASS (location_type l)
      {
        return symbol_type (token::KW_TYPECLASS, std::move (l));
      }
#else
      static
      symbol_type
      make_KW_TYPECLASS (const location_type& l)
      {
        return symbol_type (token::KW_TYPECLASS, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_DINT_LIT (TokenInfo v, location_type l)
      {
        return symbol_type (token::DINT_LIT, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_DINT_LIT (const TokenInfo& v, const location_type& l)
      {
        return symbol_type (token::DINT_LIT, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_XINT_LIT (TokenInfo v, location_type l)
      {
        return symbol_type (token::XINT_LIT, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_XINT_LIT (const TokenInfo& v, const location_type& l)
      {
        return symbol_type (token::XINT_LIT, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_FLOAT_LIT (TokenInfo v, location_type l)
      {
        return symbol_type (token::FLOAT_LIT, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_FLOAT_LIT (const TokenInfo& v, const location_type& l)
      {
        return symbol_type (token::FLOAT_LIT, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_DQSTRING_LIT (TokenInfo v, location_type l)
      {
        return symbol_type (token::DQSTRING_LIT, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_DQSTRING_LIT (const TokenInfo& v, const location_type& l)
      {
        return symbol_type (token::DQSTRING_LIT, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_SQSTRING_LIT (TokenInfo v, location_type l)
      {
        return symbol_type (token::SQSTRING_LIT, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_SQSTRING_LIT (const TokenInfo& v, const location_type& l)
      {
        return symbol_type (token::SQSTRING_LIT, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_DOT (location_type l)
      {
        return symbol_type (token::DOT, std::move (l));
      }
#else
      static
      symbol_type
      make_DOT (const location_type& l)
      {
        return symbol_type (token::DOT, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_COLON (location_type l)
      {
        return symbol_type (token::COLON, std::move (l));
      }
#else
      static
      symbol_type
      make_COLON (const location_type& l)
      {
        return symbol_type (token::COLON, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_COMMA (location_type l)
      {
        return symbol_type (token::COMMA, std::move (l));
      }
#else
      static
      symbol_type
      make_COMMA (const location_type& l)
      {
        return symbol_type (token::COMMA, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_SEMICOLON (location_type l)
      {
        return symbol_type (token::SEMICOLON, std::move (l));
      }
#else
      static
      symbol_type
      make_SEMICOLON (const location_type& l)
      {
        return symbol_type (token::SEMICOLON, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_DBL_COLON (location_type l)
      {
        return symbol_type (token::DBL_COLON, std::move (l));
      }
#else
      static
      symbol_type
      make_DBL_COLON (const location_type& l)
      {
        return symbol_type (token::DBL_COLON, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_LPAREN (location_type l)
      {
        return symbol_type (token::LPAREN, std::move (l));
      }
#else
      static
      symbol_type
      make_LPAREN (const location_type& l)
      {
        return symbol_type (token::LPAREN, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_RPAREN (location_type l)
      {
        return symbol_type (token::RPAREN, std::move (l));
      }
#else
      static
      symbol_type
      make_RPAREN (const location_type& l)
      {
        return symbol_type (token::RPAREN, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_LSQBRK (location_type l)
      {
        return symbol_type (token::LSQBRK, std::move (l));
      }
#else
      static
      symbol_type
      make_LSQBRK (const location_type& l)
      {
        return symbol_type (token::LSQBRK, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_RSQBRK (location_type l)
      {
        return symbol_type (token::RSQBRK, std::move (l));
      }
#else
      static
      symbol_type
      make_RSQBRK (const location_type& l)
      {
        return symbol_type (token::RSQBRK, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_LCYBRK (location_type l)
      {
        return symbol_type (token::LCYBRK, std::move (l));
      }
#else
      static
      symbol_type
      make_LCYBRK (const location_type& l)
      {
        return symbol_type (token::LCYBRK, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_RCYBRK (location_type l)
      {
        return symbol_type (token::RCYBRK, std::move (l));
      }
#else
      static
      symbol_type
      make_RCYBRK (const location_type& l)
      {
        return symbol_type (token::RCYBRK, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ARROW (location_type l)
      {
        return symbol_type (token::ARROW, std::move (l));
      }
#else
      static
      symbol_type
      make_ARROW (const location_type& l)
      {
        return symbol_type (token::ARROW, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ASTERISK (location_type l)
      {
        return symbol_type (token::ASTERISK, std::move (l));
      }
#else
      static
      symbol_type
      make_ASTERISK (const location_type& l)
      {
        return symbol_type (token::ASTERISK, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_FSLASH (location_type l)
      {
        return symbol_type (token::FSLASH, std::move (l));
      }
#else
      static
      symbol_type
      make_FSLASH (const location_type& l)
      {
        return symbol_type (token::FSLASH, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_PERCENT (location_type l)
      {
        return symbol_type (token::PERCENT, std::move (l));
      }
#else
      static
      symbol_type
      make_PERCENT (const location_type& l)
      {
        return symbol_type (token::PERCENT, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_PLUS (location_type l)
      {
        return symbol_type (token::PLUS, std::move (l));
      }
#else
      static
      symbol_type
      make_PLUS (const location_type& l)
      {
        return symbol_type (token::PLUS, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_MINUS (location_type l)
      {
        return symbol_type (token::MINUS, std::move (l));
      }
#else
      static
      symbol_type
      make_MINUS (const location_type& l)
      {
        return symbol_type (token::MINUS, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_LTHAN (location_type l)
      {
        return symbol_type (token::LTHAN, std::move (l));
      }
#else
      static
      symbol_type
      make_LTHAN (const location_type& l)
      {
        return symbol_type (token::LTHAN, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_LETHAN (location_type l)
      {
        return symbol_type (token::LETHAN, std::move (l));
      }
#else
      static
      symbol_type
      make_LETHAN (const location_type& l)
      {
        return symbol_type (token::LETHAN, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_GTHAN (location_type l)
      {
        return symbol_type (token::GTHAN, std::move (l));
      }
#else
      static
      symbol_type
      make_GTHAN (const location_type& l)
      {
        return symbol_type (token::GTHAN, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_GETHAN (location_type l)
      {
        return symbol_type (token::GETHAN, std::move (l));
      }
#else
      static
      symbol_type
      make_GETHAN (const location_type& l)
      {
        return symbol_type (token::GETHAN, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_BIND (location_type l)
      {
        return symbol_type (token::BIND, std::move (l));
      }
#else
      static
      symbol_type
      make_BIND (const location_type& l)
      {
        return symbol_type (token::BIND, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_EQUALS (location_type l)
      {
        return symbol_type (token::EQUALS, std::move (l));
      }
#else
      static
      symbol_type
      make_EQUALS (const location_type& l)
      {
        return symbol_type (token::EQUALS, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_NEQUALS (location_type l)
      {
        return symbol_type (token::NEQUALS, std::move (l));
      }
#else
      static
      symbol_type
      make_NEQUALS (const location_type& l)
      {
        return symbol_type (token::NEQUALS, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CARET (location_type l)
      {
        return symbol_type (token::CARET, std::move (l));
      }
#else
      static
      symbol_type
      make_CARET (const location_type& l)
      {
        return symbol_type (token::CARET, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_AMPERSAND (location_type l)
      {
        return symbol_type (token::AMPERSAND, std::move (l));
      }
#else
      static
      symbol_type
      make_AMPERSAND (const location_type& l)
      {
        return symbol_type (token::AMPERSAND, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_EXCLAIM (location_type l)
      {
        return symbol_type (token::EXCLAIM, std::move (l));
      }
#else
      static
      symbol_type
      make_EXCLAIM (const location_type& l)
      {
        return symbol_type (token::EXCLAIM, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_PIPE (location_type l)
      {
        return symbol_type (token::PIPE, std::move (l));
      }
#else
      static
      symbol_type
      make_PIPE (const location_type& l)
      {
        return symbol_type (token::PIPE, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_EOS (location_type l)
      {
        return symbol_type (token::EOS, std::move (l));
      }
#else
      static
      symbol_type
      make_EOS (const location_type& l)
      {
        return symbol_type (token::EOS, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_NONE (location_type l)
      {
        return symbol_type (token::NONE, std::move (l));
      }
#else
      static
      symbol_type
      make_NONE (const location_type& l)
      {
        return symbol_type (token::NONE, l);
      }
#endif


  private:
#if YY_CPLUSPLUS < 201103L
    /// Non copyable.
    parser (const parser&);
    /// Non copyable.
    parser& operator= (const parser&);
#endif


    /// Stored state numbers (used for stacks).
    typedef short state_type;

    /// Compute post-reduction state.
    /// \param yystate   the current state
    /// \param yysym     the nonterminal to push on the stack
    static state_type yy_lr_goto_state_ (state_type yystate, int yysym);

    /// Whether the given \c yypact_ value indicates a defaulted state.
    /// \param yyvalue   the value to check
    static bool yy_pact_value_is_default_ (int yyvalue);

    /// Whether the given \c yytable_ value indicates a syntax error.
    /// \param yyvalue   the value to check
    static bool yy_table_value_is_error_ (int yyvalue);

    static const signed char yypact_ninf_;
    static const signed char yytable_ninf_;

    /// Convert a scanner token kind \a t to a symbol kind.
    /// In theory \a t should be a token_kind_type, but character literals
    /// are valid, yet not members of the token_type enum.
    static symbol_kind_type yytranslate_ (int t);

#if YYDEBUG || 0
    /// For a symbol, its name in clear.
    static const char* const yytname_[];
#endif // #if YYDEBUG || 0


    // Tables.
    // YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
    // STATE-NUM.
    static const short yypact_[];

    // YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
    // Performed when YYTABLE does not specify something else to do.  Zero
    // means the default is an error.
    static const unsigned char yydefact_[];

    // YYPGOTO[NTERM-NUM].
    static const short yypgoto_[];

    // YYDEFGOTO[NTERM-NUM].
    static const short yydefgoto_[];

    // YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
    // positive, shift that token.  If negative, reduce the rule whose
    // number is the opposite.  If YYTABLE_NINF, syntax error.
    static const short yytable_[];

    static const short yycheck_[];

    // YYSTOS[STATE-NUM] -- The (internal number of the) accessing
    // symbol of state STATE-NUM.
    static const unsigned char yystos_[];

    // YYR1[YYN] -- Symbol number of symbol that rule YYN derives.
    static const unsigned char yyr1_[];

    // YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.
    static const signed char yyr2_[];


#if YYDEBUG
    // YYRLINE[YYN] -- Source line where rule number YYN was defined.
    static const short yyrline_[];
    /// Report on the debug stream that the rule \a r is going to be reduced.
    virtual void yy_reduce_print_ (int r) const;
    /// Print the state stack on the debug stream.
    virtual void yy_stack_print_ () const;

    /// Debugging level.
    int yydebug_;
    /// Debug stream.
    std::ostream* yycdebug_;

    /// \brief Display a symbol kind, value and location.
    /// \param yyo    The output stream.
    /// \param yysym  The symbol.
    template <typename Base>
    void yy_print_ (std::ostream& yyo, const basic_symbol<Base>& yysym) const;
#endif

    /// \brief Reclaim the memory associated to a symbol.
    /// \param yymsg     Why this token is reclaimed.
    ///                  If null, print nothing.
    /// \param yysym     The symbol.
    template <typename Base>
    void yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const;

  private:
    /// Type access provider for state based symbols.
    struct by_state
    {
      /// Default constructor.
      by_state () YY_NOEXCEPT;

      /// The symbol kind as needed by the constructor.
      typedef state_type kind_type;

      /// Constructor.
      by_state (kind_type s) YY_NOEXCEPT;

      /// Copy constructor.
      by_state (const by_state& that) YY_NOEXCEPT;

      /// Record that this symbol is empty.
      void clear () YY_NOEXCEPT;

      /// Steal the symbol kind from \a that.
      void move (by_state& that);

      /// The symbol kind (corresponding to \a state).
      /// \a symbol_kind::S_YYEMPTY when empty.
      symbol_kind_type kind () const YY_NOEXCEPT;

      /// The state number used to denote an empty symbol.
      /// We use the initial state, as it does not have a value.
      enum { empty_state = 0 };

      /// The state.
      /// \a empty when empty.
      state_type state;
    };

    /// "Internal" symbol: element of the stack.
    struct stack_symbol_type : basic_symbol<by_state>
    {
      /// Superclass.
      typedef basic_symbol<by_state> super_type;
      /// Construct an empty symbol.
      stack_symbol_type ();
      /// Move or copy construction.
      stack_symbol_type (YY_RVREF (stack_symbol_type) that);
      /// Steal the contents from \a sym to build this.
      stack_symbol_type (state_type s, YY_MOVE_REF (symbol_type) sym);
#if YY_CPLUSPLUS < 201103L
      /// Assignment, needed by push_back by some old implementations.
      /// Moves the contents of that.
      stack_symbol_type& operator= (stack_symbol_type& that);

      /// Assignment, needed by push_back by other implementations.
      /// Needed by some other old implementations.
      stack_symbol_type& operator= (const stack_symbol_type& that);
#endif
    };

    /// A stack with random access from its top.
    template <typename T, typename S = std::vector<T> >
    class stack
    {
    public:
      // Hide our reversed order.
      typedef typename S::iterator iterator;
      typedef typename S::const_iterator const_iterator;
      typedef typename S::size_type size_type;
      typedef typename std::ptrdiff_t index_type;

      stack (size_type n = 200)
        : seq_ (n)
      {}

#if 201103L <= YY_CPLUSPLUS
      /// Non copyable.
      stack (const stack&) = delete;
      /// Non copyable.
      stack& operator= (const stack&) = delete;
#endif

      /// Random access.
      ///
      /// Index 0 returns the topmost element.
      const T&
      operator[] (index_type i) const
      {
        return seq_[size_type (size () - 1 - i)];
      }

      /// Random access.
      ///
      /// Index 0 returns the topmost element.
      T&
      operator[] (index_type i)
      {
        return seq_[size_type (size () - 1 - i)];
      }

      /// Steal the contents of \a t.
      ///
      /// Close to move-semantics.
      void
      push (YY_MOVE_REF (T) t)
      {
        seq_.push_back (T ());
        operator[] (0).move (t);
      }

      /// Pop elements from the stack.
      void
      pop (std::ptrdiff_t n = 1) YY_NOEXCEPT
      {
        for (; 0 < n; --n)
          seq_.pop_back ();
      }

      /// Pop all elements from the stack.
      void
      clear () YY_NOEXCEPT
      {
        seq_.clear ();
      }

      /// Number of elements on the stack.
      index_type
      size () const YY_NOEXCEPT
      {
        return index_type (seq_.size ());
      }

      /// Iterator on top of the stack (going downwards).
      const_iterator
      begin () const YY_NOEXCEPT
      {
        return seq_.begin ();
      }

      /// Bottom of the stack.
      const_iterator
      end () const YY_NOEXCEPT
      {
        return seq_.end ();
      }

      /// Present a slice of the top of a stack.
      class slice
      {
      public:
        slice (const stack& stack, index_type range)
          : stack_ (stack)
          , range_ (range)
        {}

        const T&
        operator[] (index_type i) const
        {
          return stack_[range_ - i];
        }

      private:
        const stack& stack_;
        index_type range_;
      };

    private:
#if YY_CPLUSPLUS < 201103L
      /// Non copyable.
      stack (const stack&);
      /// Non copyable.
      stack& operator= (const stack&);
#endif
      /// The wrapped container.
      S seq_;
    };


    /// Stack type.
    typedef stack<stack_symbol_type> stack_type;

    /// The stack.
    stack_type yystack_;

    /// Push a new state on the stack.
    /// \param m    a debug message to display
    ///             if null, no trace is output.
    /// \param sym  the symbol
    /// \warning the contents of \a s.value is stolen.
    void yypush_ (const char* m, YY_MOVE_REF (stack_symbol_type) sym);

    /// Push a new look ahead token on the state on the stack.
    /// \param m    a debug message to display
    ///             if null, no trace is output.
    /// \param s    the state
    /// \param sym  the symbol (for its value and location).
    /// \warning the contents of \a sym.value is stolen.
    void yypush_ (const char* m, state_type s, YY_MOVE_REF (symbol_type) sym);

    /// Pop \a n symbols from the stack.
    void yypop_ (int n = 1);

    /// Constants.
    enum
    {
      yylast_ = 619,     ///< Last index in yytable_.
      yynnts_ = 93,  ///< Number of nonterminal symbols.
      yyfinal_ = 7 ///< Termination state number.
    };


    // User arguments.
    pdm::source::Source* source;
    pdm::parser::Lexer* lexer;
    pdm::ast::Manager* mgr;
    pdm::ast::Script** returnp;

  };


#line 22 "parser.yy"
} } // pdm::parser
#line 3166 "parser.tab.hh"


// "%code provides" blocks.
#line 209 "parser.yy"

    int yylex(pdm::parser::TokenInfo *lvalp, pdm::source::Loc *llocp, pdm::source::Source* source, pdm::parser::Lexer* lexer);
    void yyerror(pdm::source::Loc* llocp, char const* message, pdm::source::Source* source, pdm::parser::Lexer* lexer);

#line 3175 "parser.tab.hh"


#endif // !YY_YY_PARSER_TAB_HH_INCLUDED
