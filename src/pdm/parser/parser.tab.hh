// A Bison parser, made by GNU Bison 3.7.6.

// Skeleton interface for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015, 2018-2021 Free Software Foundation, Inc.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

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
#line 21 "parser.yy"

    #include "pdm/core/config.hh"

    #include "pdm/feedback/feedback.hh"
    #include "pdm/feedback/severity.hh"
    #include "pdm/feedback/letter.hh"
    #include "pdm/feedback/note.hh"

    #include "pdm/ast/node.hh"
    #include "pdm/ast/manager.hh"
    #include "pdm/ast/visitor.hh"

    #include "pdm/parser/lexer.hh"

    #include "pdm/source/local-script-source.hh"
    #include "pdm/source/local-package-source.hh"

#line 67 "parser.tab.hh"


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
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
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

#line 11 "parser.yy"
namespace pdm { namespace parser {
#line 197 "parser.tab.hh"




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
      // "val_id"
      // "TypeId"
      // "CLS_ID"
      // "__42__"
      // "42"
      // "0x2a"
      // "42u"
      // "0x2Au"
      // "4.2"
      // "\"dq-string-literal\""
      // "'sq-string-literal'"
      // tid
      // vid
      // cid
      // floatl
      // stringl
      char dummy1[sizeof (TokenInfo)];

      // import_field_group
      char dummy2[sizeof (ast::ImportStmt::FieldGroup*)];

      // native_mod_exp
      char dummy3[sizeof (pdm::ast::BaseModExp*)];

      // mod_field
      char dummy4[sizeof (pdm::ast::BaseModExp::Field*)];

      // mul_binary_op
      // add_binary_op
      // cmp_binary_op
      // eq_binary_op
      char dummy5[sizeof (pdm::ast::BinaryOperator)];

      // class_spec
      // primary_class_spec
      // mod_prefix_cid_class_spec
      // class_exp_class_spec
      char dummy6[sizeof (pdm::ast::ClassSpec*)];

      // enum_type_spec_field
      char dummy7[sizeof (pdm::ast::EnumTypeSpec::Field*)];

      // mut_expr
      // expr
      // long_exp
      // bracketed_exp
      // paren_exp
      // vtupleExpr
      // vstructExpr
      // primary_exp
      // int_expr
      // if_exp
      // chain_exp
      // lambda_exp
      // postfix_exp
      // vcall_exp
      // dot_name_exp
      // dot_index_exp
      // unary_exp
      // binary_exp
      // mul_binary_exp
      // add_binary_exp
      // cmp_binary_exp
      // eq_binary_exp
      // and_binary_exp
      // xor_binary_exp
      // or_binary_exp
      char dummy8[sizeof (pdm::ast::Exp*)];

      // fn_type_spec
      char dummy9[sizeof (pdm::ast::FnTypeSpec*)];

      // script_header_stmt
      // import_stmt
      char dummy10[sizeof (pdm::ast::HeaderStmt*)];

      // destructured_lpattern
      // lpattern
      char dummy11[sizeof (pdm::ast::LPattern*)];

      // lpattern_field
      char dummy12[sizeof (pdm::ast::LPattern::Field*)];

      // mod_prefix
      char dummy13[sizeof (pdm::ast::ModAddress*)];

      // script
      char dummy14[sizeof (pdm::ast::Script*)];

      // script_field
      char dummy15[sizeof (pdm::ast::Script::Field*)];

      // chain_prefix_stmt
      // const_stmt
      // val_stmt
      // var_stmt
      // set_stmt
      // discard_stmt
      char dummy16[sizeof (pdm::ast::Stmt*)];

      // struct_exp_field
      char dummy17[sizeof (pdm::ast::StructExp::Field*)];

      // struct_type_spec_field
      char dummy18[sizeof (pdm::ast::StructTypeSpec::Field*)];

      // targ
      char dummy19[sizeof (pdm::ast::TArg*)];

      // tpattern
      char dummy20[sizeof (pdm::ast::TPattern*)];

      // tpattern_field
      char dummy21[sizeof (pdm::ast::TPattern::Field*)];

      // type_query_exp
      char dummy22[sizeof (pdm::ast::TypeQueryExp*)];

      // type_query_op
      char dummy23[sizeof (pdm::ast::TypeQueryKind)];

      // type_spec
      // mod_prefix_tid
      // tuple_type_spec
      // array_type_spec
      // struct_type_spec
      // enum_type_spec
      char dummy24[sizeof (pdm::ast::TypeSpec*)];

      // unary_op
      char dummy25[sizeof (pdm::ast::UnaryOperator)];

      // varg
      char dummy26[sizeof (pdm::ast::VArg*)];

      // vpattern
      char dummy27[sizeof (pdm::ast::VPattern*)];

      // vpattern_field
      char dummy28[sizeof (pdm::ast::VPattern::Field*)];

      // import_field_cl1
      char dummy29[sizeof (std::vector<ast::ImportStmt::Field*>)];

      // import_field_group_sl0
      char dummy30[sizeof (std::vector<ast::ImportStmt::FieldGroup*>)];

      // mod_field_sl
      char dummy31[sizeof (std::vector<pdm::ast::BaseModExp::Field*>)];

      // enum_type_spec_field_cl
      char dummy32[sizeof (std::vector<pdm::ast::EnumTypeSpec::Field*>)];

      // mut_expr_cl1
      // expr_cl2
      char dummy33[sizeof (std::vector<pdm::ast::Exp*>)];

      // script_header
      char dummy34[sizeof (std::vector<pdm::ast::HeaderStmt*>)];

      // lpattern_field_cl
      char dummy35[sizeof (std::vector<pdm::ast::LPattern::Field*>)];

      // script_field_sl
      char dummy36[sizeof (std::vector<pdm::ast::Script::Field*>)];

      // chain_prefix
      char dummy37[sizeof (std::vector<pdm::ast::Stmt*>)];

      // stringls
      char dummy38[sizeof (std::vector<pdm::ast::StringExp::Piece>)];

      // struct_exp_field_cl
      char dummy39[sizeof (std::vector<pdm::ast::StructExp::Field*>)];

      // struct_type_spec_field_cl
      char dummy40[sizeof (std::vector<pdm::ast::StructTypeSpec::Field*>)];

      // targ_cl
      char dummy41[sizeof (std::vector<pdm::ast::TArg*>)];

      // tpattern_field_cl1
      char dummy42[sizeof (std::vector<pdm::ast::TPattern::Field*>)];

      // type_query_exp_sl0
      char dummy43[sizeof (std::vector<pdm::ast::TypeQueryExp*>)];

      // type_spec_cl2
      char dummy44[sizeof (std::vector<pdm::ast::TypeSpec*>)];

      // varg_cl
      char dummy45[sizeof (std::vector<pdm::ast::VArg*>)];

      // vpattern_field_cl
      char dummy46[sizeof (std::vector<pdm::ast::VPattern::Field*>)];
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
    VID = 258,                     // "val_id"
    TID = 259,                     // "TypeId"
    CID = 260,                     // "CLS_ID"
    HOLE = 261,                    // "__42__"
    KW_USING = 262,                // "using"
    KW_MOD = 263,                  // "mod"
    KW_STRUCT = 264,               // "struct"
    KW_ENUM = 265,                 // "enum"
    KW_TYPECLASS = 266,            // "typeclass"
    KW_IF = 267,                   // "if"
    KW_THEN = 268,                 // "then"
    KW_ELSE = 269,                 // "else"
    KW_MATCH = 270,                // "match"
    KW_WITH = 271,                 // "with"
    KW_IMPORTS = 272,              // "imports"
    KW_EXTERN = 273,               // "extern"
    KW_FROM = 274,                 // "from"
    KW_CONST = 275,                // "const"
    KW_VAL = 276,                  // "val"
    KW_VAR = 277,                  // "var"
    KW_LET = 278,                  // "let"
    KW_SET = 279,                  // "set"
    KW_FN = 280,                   // "anonymous_fn"
    KW_AND = 281,                  // "and"
    KW_XOR = 282,                  // "xor"
    KW_OR = 283,                   // "or"
    KW_NOT = 284,                  // "not"
    KW_OUT = 285,                  // "out"
    KW_INOUT = 286,                // "inout"
    KW_DISCARD = 287,              // "discard"
    KW_AS = 288,                   // "as"
    KW_FOR = 289,                  // "for"
    KW_CORE_PROFILE = 290,         // "CORE_PROFILE"
    KW_BROWSER_PROFILE = 291,      // "BROWSER_PROFILE"
    KW_NATIVE_PROFILE = 292,       // "NATIVE_PROFILE"
    DINT_LIT = 293,                // "42"
    XINT_LIT = 294,                // "0x2a"
    UNSIGNED_DINT_LIT = 295,       // "42u"
    UNSIGNED_XINT_LIT = 296,       // "0x2Au"
    FLOAT_LIT = 297,               // "4.2"
    DQSTRING_LIT = 298,            // "\"dq-string-literal\""
    SQSTRING_LIT = 299,            // "'sq-string-literal'"
    DOT = 300,                     // "."
    COLON = 301,                   // ":"
    COMMA = 302,                   // ","
    SEMICOLON = 303,               // ";"
    DBL_COLON = 304,               // "::"
    LPAREN = 305,                  // "("
    RPAREN = 306,                  // ")"
    LSQBRK = 307,                  // "["
    RSQBRK = 308,                  // "]"
    LCYBRK = 309,                  // "{"
    RCYBRK = 310,                  // "}"
    ARROW = 311,                   // "->"
    ASTERISK = 312,                // "*"
    FSLASH = 313,                  // "/"
    PERCENT = 314,                 // "%"
    PLUS = 315,                    // "+"
    MINUS = 316,                   // "-"
    LTHAN = 317,                   // "<"
    LETHAN = 318,                  // "<="
    GTHAN = 319,                   // ">"
    GETHAN = 320,                  // ">="
    BIND = 321,                    // "="
    EQUALS = 322,                  // "=="
    NEQUALS = 323,                 // "!="
    CARET = 324,                   // "^"
    AMPERSAND = 325,               // "&"
    EXCLAIM = 326,                 // "!"
    PIPE = 327,                    // "|"
    EOS = 328,                     // "EOS"
    COLON_LTHAN = 329,             // ":<"
    GTHAN_COLON = 330,             // ">:"
    NONE = 331                     // "<null>"
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
        YYNTOKENS = 77, ///< Number of tokens.
        S_YYEMPTY = -2,
        S_YYEOF = 0,                             // "end of file"
        S_YYerror = 1,                           // error
        S_YYUNDEF = 2,                           // "invalid token"
        S_VID = 3,                               // "val_id"
        S_TID = 4,                               // "TypeId"
        S_CID = 5,                               // "CLS_ID"
        S_HOLE = 6,                              // "__42__"
        S_KW_USING = 7,                          // "using"
        S_KW_MOD = 8,                            // "mod"
        S_KW_STRUCT = 9,                         // "struct"
        S_KW_ENUM = 10,                          // "enum"
        S_KW_TYPECLASS = 11,                     // "typeclass"
        S_KW_IF = 12,                            // "if"
        S_KW_THEN = 13,                          // "then"
        S_KW_ELSE = 14,                          // "else"
        S_KW_MATCH = 15,                         // "match"
        S_KW_WITH = 16,                          // "with"
        S_KW_IMPORTS = 17,                       // "imports"
        S_KW_EXTERN = 18,                        // "extern"
        S_KW_FROM = 19,                          // "from"
        S_KW_CONST = 20,                         // "const"
        S_KW_VAL = 21,                           // "val"
        S_KW_VAR = 22,                           // "var"
        S_KW_LET = 23,                           // "let"
        S_KW_SET = 24,                           // "set"
        S_KW_FN = 25,                            // "anonymous_fn"
        S_KW_AND = 26,                           // "and"
        S_KW_XOR = 27,                           // "xor"
        S_KW_OR = 28,                            // "or"
        S_KW_NOT = 29,                           // "not"
        S_KW_OUT = 30,                           // "out"
        S_KW_INOUT = 31,                         // "inout"
        S_KW_DISCARD = 32,                       // "discard"
        S_KW_AS = 33,                            // "as"
        S_KW_FOR = 34,                           // "for"
        S_KW_CORE_PROFILE = 35,                  // "CORE_PROFILE"
        S_KW_BROWSER_PROFILE = 36,               // "BROWSER_PROFILE"
        S_KW_NATIVE_PROFILE = 37,                // "NATIVE_PROFILE"
        S_DINT_LIT = 38,                         // "42"
        S_XINT_LIT = 39,                         // "0x2a"
        S_UNSIGNED_DINT_LIT = 40,                // "42u"
        S_UNSIGNED_XINT_LIT = 41,                // "0x2Au"
        S_FLOAT_LIT = 42,                        // "4.2"
        S_DQSTRING_LIT = 43,                     // "\"dq-string-literal\""
        S_SQSTRING_LIT = 44,                     // "'sq-string-literal'"
        S_DOT = 45,                              // "."
        S_COLON = 46,                            // ":"
        S_COMMA = 47,                            // ","
        S_SEMICOLON = 48,                        // ";"
        S_DBL_COLON = 49,                        // "::"
        S_LPAREN = 50,                           // "("
        S_RPAREN = 51,                           // ")"
        S_LSQBRK = 52,                           // "["
        S_RSQBRK = 53,                           // "]"
        S_LCYBRK = 54,                           // "{"
        S_RCYBRK = 55,                           // "}"
        S_ARROW = 56,                            // "->"
        S_ASTERISK = 57,                         // "*"
        S_FSLASH = 58,                           // "/"
        S_PERCENT = 59,                          // "%"
        S_PLUS = 60,                             // "+"
        S_MINUS = 61,                            // "-"
        S_LTHAN = 62,                            // "<"
        S_LETHAN = 63,                           // "<="
        S_GTHAN = 64,                            // ">"
        S_GETHAN = 65,                           // ">="
        S_BIND = 66,                             // "="
        S_EQUALS = 67,                           // "=="
        S_NEQUALS = 68,                          // "!="
        S_CARET = 69,                            // "^"
        S_AMPERSAND = 70,                        // "&"
        S_EXCLAIM = 71,                          // "!"
        S_PIPE = 72,                             // "|"
        S_EOS = 73,                              // "EOS"
        S_COLON_LTHAN = 74,                      // ":<"
        S_GTHAN_COLON = 75,                      // ">:"
        S_NONE = 76,                             // "<null>"
        S_YYACCEPT = 77,                         // $accept
        S_script = 78,                           // script
        S_script_header = 79,                    // script_header
        S_script_header_stmt = 80,               // script_header_stmt
        S_script_field = 81,                     // script_field
        S_script_field_sl = 82,                  // script_field_sl
        S_native_mod_exp = 83,                   // native_mod_exp
        S_mod_field_sl = 84,                     // mod_field_sl
        S_mod_field = 85,                        // mod_field
        S_import_stmt = 86,                      // import_stmt
        S_import_field_group_sl0 = 87,           // import_field_group_sl0
        S_import_field_group = 88,               // import_field_group
        S_import_field_cl1 = 89,                 // import_field_cl1
        S_chain_prefix_stmt = 90,                // chain_prefix_stmt
        S_const_stmt = 91,                       // const_stmt
        S_val_stmt = 92,                         // val_stmt
        S_var_stmt = 93,                         // var_stmt
        S_set_stmt = 94,                         // set_stmt
        S_discard_stmt = 95,                     // discard_stmt
        S_tid = 96,                              // tid
        S_vid = 97,                              // vid
        S_cid = 98,                              // cid
        S_floatl = 99,                           // floatl
        S_stringl = 100,                         // stringl
        S_mod_prefix = 101,                      // mod_prefix
        S_mut_expr = 102,                        // mut_expr
        S_mut_expr_cl1 = 103,                    // mut_expr_cl1
        S_expr = 104,                            // expr
        S_long_exp = 105,                        // long_exp
        S_expr_cl2 = 106,                        // expr_cl2
        S_type_query_exp_sl0 = 107,              // type_query_exp_sl0
        S_bracketed_exp = 108,                   // bracketed_exp
        S_paren_exp = 109,                       // paren_exp
        S_vtupleExpr = 110,                      // vtupleExpr
        S_vstructExpr = 111,                     // vstructExpr
        S_primary_exp = 112,                     // primary_exp
        S_int_expr = 113,                        // int_expr
        S_stringls = 114,                        // stringls
        S_if_exp = 115,                          // if_exp
        S_chain_exp = 116,                       // chain_exp
        S_chain_prefix = 117,                    // chain_prefix
        S_lambda_exp = 118,                      // lambda_exp
        S_postfix_exp = 119,                     // postfix_exp
        S_vcall_exp = 120,                       // vcall_exp
        S_dot_name_exp = 121,                    // dot_name_exp
        S_dot_index_exp = 122,                   // dot_index_exp
        S_unary_exp = 123,                       // unary_exp
        S_unary_op = 124,                        // unary_op
        S_binary_exp = 125,                      // binary_exp
        S_mul_binary_op = 126,                   // mul_binary_op
        S_mul_binary_exp = 127,                  // mul_binary_exp
        S_add_binary_op = 128,                   // add_binary_op
        S_add_binary_exp = 129,                  // add_binary_exp
        S_cmp_binary_op = 130,                   // cmp_binary_op
        S_cmp_binary_exp = 131,                  // cmp_binary_exp
        S_eq_binary_op = 132,                    // eq_binary_op
        S_eq_binary_exp = 133,                   // eq_binary_exp
        S_and_binary_exp = 134,                  // and_binary_exp
        S_xor_binary_exp = 135,                  // xor_binary_exp
        S_or_binary_exp = 136,                   // or_binary_exp
        S_type_query_exp = 137,                  // type_query_exp
        S_type_query_op = 138,                   // type_query_op
        S_type_spec_cl2 = 139,                   // type_spec_cl2
        S_type_spec = 140,                       // type_spec
        S_mod_prefix_tid = 141,                  // mod_prefix_tid
        S_tuple_type_spec = 142,                 // tuple_type_spec
        S_array_type_spec = 143,                 // array_type_spec
        S_struct_type_spec = 144,                // struct_type_spec
        S_struct_type_spec_field_cl = 145,       // struct_type_spec_field_cl
        S_struct_type_spec_field = 146,          // struct_type_spec_field
        S_enum_type_spec_field = 147,            // enum_type_spec_field
        S_enum_type_spec_field_cl = 148,         // enum_type_spec_field_cl
        S_enum_type_spec = 149,                  // enum_type_spec
        S_fn_type_spec = 150,                    // fn_type_spec
        S_targ = 151,                            // targ
        S_targ_cl = 152,                         // targ_cl
        S_varg = 153,                            // varg
        S_varg_cl = 154,                         // varg_cl
        S_class_spec = 155,                      // class_spec
        S_primary_class_spec = 156,              // primary_class_spec
        S_mod_prefix_cid_class_spec = 157,       // mod_prefix_cid_class_spec
        S_class_exp_class_spec = 158,            // class_exp_class_spec
        S_struct_exp_field = 159,                // struct_exp_field
        S_vpattern_field = 160,                  // vpattern_field
        S_lpattern_field = 161,                  // lpattern_field
        S_tpattern_field = 162,                  // tpattern_field
        S_destructured_lpattern = 163,           // destructured_lpattern
        S_lpattern = 164,                        // lpattern
        S_vpattern = 165,                        // vpattern
        S_tpattern = 166,                        // tpattern
        S_vpattern_field_cl = 167,               // vpattern_field_cl
        S_lpattern_field_cl = 168,               // lpattern_field_cl
        S_tpattern_field_cl1 = 169,              // tpattern_field_cl1
        S_struct_exp_field_cl = 170              // struct_exp_field_cl
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
      case symbol_kind::S_VID: // "val_id"
      case symbol_kind::S_TID: // "TypeId"
      case symbol_kind::S_CID: // "CLS_ID"
      case symbol_kind::S_HOLE: // "__42__"
      case symbol_kind::S_DINT_LIT: // "42"
      case symbol_kind::S_XINT_LIT: // "0x2a"
      case symbol_kind::S_UNSIGNED_DINT_LIT: // "42u"
      case symbol_kind::S_UNSIGNED_XINT_LIT: // "0x2Au"
      case symbol_kind::S_FLOAT_LIT: // "4.2"
      case symbol_kind::S_DQSTRING_LIT: // "\"dq-string-literal\""
      case symbol_kind::S_SQSTRING_LIT: // "'sq-string-literal'"
      case symbol_kind::S_tid: // tid
      case symbol_kind::S_vid: // vid
      case symbol_kind::S_cid: // cid
      case symbol_kind::S_floatl: // floatl
      case symbol_kind::S_stringl: // stringl
        value.move< TokenInfo > (std::move (that.value));
        break;

      case symbol_kind::S_import_field_group: // import_field_group
        value.move< ast::ImportStmt::FieldGroup* > (std::move (that.value));
        break;

      case symbol_kind::S_native_mod_exp: // native_mod_exp
        value.move< pdm::ast::BaseModExp* > (std::move (that.value));
        break;

      case symbol_kind::S_mod_field: // mod_field
        value.move< pdm::ast::BaseModExp::Field* > (std::move (that.value));
        break;

      case symbol_kind::S_mul_binary_op: // mul_binary_op
      case symbol_kind::S_add_binary_op: // add_binary_op
      case symbol_kind::S_cmp_binary_op: // cmp_binary_op
      case symbol_kind::S_eq_binary_op: // eq_binary_op
        value.move< pdm::ast::BinaryOperator > (std::move (that.value));
        break;

      case symbol_kind::S_class_spec: // class_spec
      case symbol_kind::S_primary_class_spec: // primary_class_spec
      case symbol_kind::S_mod_prefix_cid_class_spec: // mod_prefix_cid_class_spec
      case symbol_kind::S_class_exp_class_spec: // class_exp_class_spec
        value.move< pdm::ast::ClassSpec* > (std::move (that.value));
        break;

      case symbol_kind::S_enum_type_spec_field: // enum_type_spec_field
        value.move< pdm::ast::EnumTypeSpec::Field* > (std::move (that.value));
        break;

      case symbol_kind::S_mut_expr: // mut_expr
      case symbol_kind::S_expr: // expr
      case symbol_kind::S_long_exp: // long_exp
      case symbol_kind::S_bracketed_exp: // bracketed_exp
      case symbol_kind::S_paren_exp: // paren_exp
      case symbol_kind::S_vtupleExpr: // vtupleExpr
      case symbol_kind::S_vstructExpr: // vstructExpr
      case symbol_kind::S_primary_exp: // primary_exp
      case symbol_kind::S_int_expr: // int_expr
      case symbol_kind::S_if_exp: // if_exp
      case symbol_kind::S_chain_exp: // chain_exp
      case symbol_kind::S_lambda_exp: // lambda_exp
      case symbol_kind::S_postfix_exp: // postfix_exp
      case symbol_kind::S_vcall_exp: // vcall_exp
      case symbol_kind::S_dot_name_exp: // dot_name_exp
      case symbol_kind::S_dot_index_exp: // dot_index_exp
      case symbol_kind::S_unary_exp: // unary_exp
      case symbol_kind::S_binary_exp: // binary_exp
      case symbol_kind::S_mul_binary_exp: // mul_binary_exp
      case symbol_kind::S_add_binary_exp: // add_binary_exp
      case symbol_kind::S_cmp_binary_exp: // cmp_binary_exp
      case symbol_kind::S_eq_binary_exp: // eq_binary_exp
      case symbol_kind::S_and_binary_exp: // and_binary_exp
      case symbol_kind::S_xor_binary_exp: // xor_binary_exp
      case symbol_kind::S_or_binary_exp: // or_binary_exp
        value.move< pdm::ast::Exp* > (std::move (that.value));
        break;

      case symbol_kind::S_fn_type_spec: // fn_type_spec
        value.move< pdm::ast::FnTypeSpec* > (std::move (that.value));
        break;

      case symbol_kind::S_script_header_stmt: // script_header_stmt
      case symbol_kind::S_import_stmt: // import_stmt
        value.move< pdm::ast::HeaderStmt* > (std::move (that.value));
        break;

      case symbol_kind::S_destructured_lpattern: // destructured_lpattern
      case symbol_kind::S_lpattern: // lpattern
        value.move< pdm::ast::LPattern* > (std::move (that.value));
        break;

      case symbol_kind::S_lpattern_field: // lpattern_field
        value.move< pdm::ast::LPattern::Field* > (std::move (that.value));
        break;

      case symbol_kind::S_mod_prefix: // mod_prefix
        value.move< pdm::ast::ModAddress* > (std::move (that.value));
        break;

      case symbol_kind::S_script: // script
        value.move< pdm::ast::Script* > (std::move (that.value));
        break;

      case symbol_kind::S_script_field: // script_field
        value.move< pdm::ast::Script::Field* > (std::move (that.value));
        break;

      case symbol_kind::S_chain_prefix_stmt: // chain_prefix_stmt
      case symbol_kind::S_const_stmt: // const_stmt
      case symbol_kind::S_val_stmt: // val_stmt
      case symbol_kind::S_var_stmt: // var_stmt
      case symbol_kind::S_set_stmt: // set_stmt
      case symbol_kind::S_discard_stmt: // discard_stmt
        value.move< pdm::ast::Stmt* > (std::move (that.value));
        break;

      case symbol_kind::S_struct_exp_field: // struct_exp_field
        value.move< pdm::ast::StructExp::Field* > (std::move (that.value));
        break;

      case symbol_kind::S_struct_type_spec_field: // struct_type_spec_field
        value.move< pdm::ast::StructTypeSpec::Field* > (std::move (that.value));
        break;

      case symbol_kind::S_targ: // targ
        value.move< pdm::ast::TArg* > (std::move (that.value));
        break;

      case symbol_kind::S_tpattern: // tpattern
        value.move< pdm::ast::TPattern* > (std::move (that.value));
        break;

      case symbol_kind::S_tpattern_field: // tpattern_field
        value.move< pdm::ast::TPattern::Field* > (std::move (that.value));
        break;

      case symbol_kind::S_type_query_exp: // type_query_exp
        value.move< pdm::ast::TypeQueryExp* > (std::move (that.value));
        break;

      case symbol_kind::S_type_query_op: // type_query_op
        value.move< pdm::ast::TypeQueryKind > (std::move (that.value));
        break;

      case symbol_kind::S_type_spec: // type_spec
      case symbol_kind::S_mod_prefix_tid: // mod_prefix_tid
      case symbol_kind::S_tuple_type_spec: // tuple_type_spec
      case symbol_kind::S_array_type_spec: // array_type_spec
      case symbol_kind::S_struct_type_spec: // struct_type_spec
      case symbol_kind::S_enum_type_spec: // enum_type_spec
        value.move< pdm::ast::TypeSpec* > (std::move (that.value));
        break;

      case symbol_kind::S_unary_op: // unary_op
        value.move< pdm::ast::UnaryOperator > (std::move (that.value));
        break;

      case symbol_kind::S_varg: // varg
        value.move< pdm::ast::VArg* > (std::move (that.value));
        break;

      case symbol_kind::S_vpattern: // vpattern
        value.move< pdm::ast::VPattern* > (std::move (that.value));
        break;

      case symbol_kind::S_vpattern_field: // vpattern_field
        value.move< pdm::ast::VPattern::Field* > (std::move (that.value));
        break;

      case symbol_kind::S_import_field_cl1: // import_field_cl1
        value.move< std::vector<ast::ImportStmt::Field*> > (std::move (that.value));
        break;

      case symbol_kind::S_import_field_group_sl0: // import_field_group_sl0
        value.move< std::vector<ast::ImportStmt::FieldGroup*> > (std::move (that.value));
        break;

      case symbol_kind::S_mod_field_sl: // mod_field_sl
        value.move< std::vector<pdm::ast::BaseModExp::Field*> > (std::move (that.value));
        break;

      case symbol_kind::S_enum_type_spec_field_cl: // enum_type_spec_field_cl
        value.move< std::vector<pdm::ast::EnumTypeSpec::Field*> > (std::move (that.value));
        break;

      case symbol_kind::S_mut_expr_cl1: // mut_expr_cl1
      case symbol_kind::S_expr_cl2: // expr_cl2
        value.move< std::vector<pdm::ast::Exp*> > (std::move (that.value));
        break;

      case symbol_kind::S_script_header: // script_header
        value.move< std::vector<pdm::ast::HeaderStmt*> > (std::move (that.value));
        break;

      case symbol_kind::S_lpattern_field_cl: // lpattern_field_cl
        value.move< std::vector<pdm::ast::LPattern::Field*> > (std::move (that.value));
        break;

      case symbol_kind::S_script_field_sl: // script_field_sl
        value.move< std::vector<pdm::ast::Script::Field*> > (std::move (that.value));
        break;

      case symbol_kind::S_chain_prefix: // chain_prefix
        value.move< std::vector<pdm::ast::Stmt*> > (std::move (that.value));
        break;

      case symbol_kind::S_stringls: // stringls
        value.move< std::vector<pdm::ast::StringExp::Piece> > (std::move (that.value));
        break;

      case symbol_kind::S_struct_exp_field_cl: // struct_exp_field_cl
        value.move< std::vector<pdm::ast::StructExp::Field*> > (std::move (that.value));
        break;

      case symbol_kind::S_struct_type_spec_field_cl: // struct_type_spec_field_cl
        value.move< std::vector<pdm::ast::StructTypeSpec::Field*> > (std::move (that.value));
        break;

      case symbol_kind::S_targ_cl: // targ_cl
        value.move< std::vector<pdm::ast::TArg*> > (std::move (that.value));
        break;

      case symbol_kind::S_tpattern_field_cl1: // tpattern_field_cl1
        value.move< std::vector<pdm::ast::TPattern::Field*> > (std::move (that.value));
        break;

      case symbol_kind::S_type_query_exp_sl0: // type_query_exp_sl0
        value.move< std::vector<pdm::ast::TypeQueryExp*> > (std::move (that.value));
        break;

      case symbol_kind::S_type_spec_cl2: // type_spec_cl2
        value.move< std::vector<pdm::ast::TypeSpec*> > (std::move (that.value));
        break;

      case symbol_kind::S_varg_cl: // varg_cl
        value.move< std::vector<pdm::ast::VArg*> > (std::move (that.value));
        break;

      case symbol_kind::S_vpattern_field_cl: // vpattern_field_cl
        value.move< std::vector<pdm::ast::VPattern::Field*> > (std::move (that.value));
        break;

      default:
        break;
    }

      }
#endif

      /// Copy constructor.
      basic_symbol (const basic_symbol& that);

      /// Constructors for typed symbols.
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
      basic_symbol (typename Base::kind_type t, ast::ImportStmt::FieldGroup*&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const ast::ImportStmt::FieldGroup*& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, pdm::ast::BaseModExp*&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const pdm::ast::BaseModExp*& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, pdm::ast::BaseModExp::Field*&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const pdm::ast::BaseModExp::Field*& v, const location_type& l)
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
      basic_symbol (typename Base::kind_type t, pdm::ast::ClassSpec*&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const pdm::ast::ClassSpec*& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, pdm::ast::EnumTypeSpec::Field*&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const pdm::ast::EnumTypeSpec::Field*& v, const location_type& l)
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
      basic_symbol (typename Base::kind_type t, pdm::ast::FnTypeSpec*&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const pdm::ast::FnTypeSpec*& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, pdm::ast::HeaderStmt*&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const pdm::ast::HeaderStmt*& v, const location_type& l)
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
      basic_symbol (typename Base::kind_type t, pdm::ast::ModAddress*&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const pdm::ast::ModAddress*& v, const location_type& l)
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
      basic_symbol (typename Base::kind_type t, pdm::ast::Script::Field*&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const pdm::ast::Script::Field*& v, const location_type& l)
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
      basic_symbol (typename Base::kind_type t, pdm::ast::StructTypeSpec::Field*&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const pdm::ast::StructTypeSpec::Field*& v, const location_type& l)
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
      basic_symbol (typename Base::kind_type t, pdm::ast::TypeQueryExp*&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const pdm::ast::TypeQueryExp*& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, pdm::ast::TypeQueryKind&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const pdm::ast::TypeQueryKind& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, pdm::ast::TypeSpec*&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const pdm::ast::TypeSpec*& v, const location_type& l)
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
      basic_symbol (typename Base::kind_type t, pdm::ast::VArg*&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const pdm::ast::VArg*& v, const location_type& l)
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
      basic_symbol (typename Base::kind_type t, std::vector<ast::ImportStmt::Field*>&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const std::vector<ast::ImportStmt::Field*>& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, std::vector<ast::ImportStmt::FieldGroup*>&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const std::vector<ast::ImportStmt::FieldGroup*>& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, std::vector<pdm::ast::BaseModExp::Field*>&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const std::vector<pdm::ast::BaseModExp::Field*>& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, std::vector<pdm::ast::EnumTypeSpec::Field*>&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const std::vector<pdm::ast::EnumTypeSpec::Field*>& v, const location_type& l)
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
      basic_symbol (typename Base::kind_type t, std::vector<pdm::ast::HeaderStmt*>&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const std::vector<pdm::ast::HeaderStmt*>& v, const location_type& l)
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
      basic_symbol (typename Base::kind_type t, std::vector<pdm::ast::Script::Field*>&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const std::vector<pdm::ast::Script::Field*>& v, const location_type& l)
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
      basic_symbol (typename Base::kind_type t, std::vector<pdm::ast::StringExp::Piece>&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const std::vector<pdm::ast::StringExp::Piece>& v, const location_type& l)
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
      basic_symbol (typename Base::kind_type t, std::vector<pdm::ast::StructTypeSpec::Field*>&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const std::vector<pdm::ast::StructTypeSpec::Field*>& v, const location_type& l)
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
      basic_symbol (typename Base::kind_type t, std::vector<pdm::ast::TypeQueryExp*>&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const std::vector<pdm::ast::TypeQueryExp*>& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, std::vector<pdm::ast::TypeSpec*>&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const std::vector<pdm::ast::TypeSpec*>& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, std::vector<pdm::ast::VArg*>&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const std::vector<pdm::ast::VArg*>& v, const location_type& l)
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

      /// Destroy the symbol.
      ~basic_symbol ()
      {
        clear ();
      }

      /// Destroy contents, and record that is empty.
      void clear () YY_NOEXCEPT
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
      case symbol_kind::S_VID: // "val_id"
      case symbol_kind::S_TID: // "TypeId"
      case symbol_kind::S_CID: // "CLS_ID"
      case symbol_kind::S_HOLE: // "__42__"
      case symbol_kind::S_DINT_LIT: // "42"
      case symbol_kind::S_XINT_LIT: // "0x2a"
      case symbol_kind::S_UNSIGNED_DINT_LIT: // "42u"
      case symbol_kind::S_UNSIGNED_XINT_LIT: // "0x2Au"
      case symbol_kind::S_FLOAT_LIT: // "4.2"
      case symbol_kind::S_DQSTRING_LIT: // "\"dq-string-literal\""
      case symbol_kind::S_SQSTRING_LIT: // "'sq-string-literal'"
      case symbol_kind::S_tid: // tid
      case symbol_kind::S_vid: // vid
      case symbol_kind::S_cid: // cid
      case symbol_kind::S_floatl: // floatl
      case symbol_kind::S_stringl: // stringl
        value.template destroy< TokenInfo > ();
        break;

      case symbol_kind::S_import_field_group: // import_field_group
        value.template destroy< ast::ImportStmt::FieldGroup* > ();
        break;

      case symbol_kind::S_native_mod_exp: // native_mod_exp
        value.template destroy< pdm::ast::BaseModExp* > ();
        break;

      case symbol_kind::S_mod_field: // mod_field
        value.template destroy< pdm::ast::BaseModExp::Field* > ();
        break;

      case symbol_kind::S_mul_binary_op: // mul_binary_op
      case symbol_kind::S_add_binary_op: // add_binary_op
      case symbol_kind::S_cmp_binary_op: // cmp_binary_op
      case symbol_kind::S_eq_binary_op: // eq_binary_op
        value.template destroy< pdm::ast::BinaryOperator > ();
        break;

      case symbol_kind::S_class_spec: // class_spec
      case symbol_kind::S_primary_class_spec: // primary_class_spec
      case symbol_kind::S_mod_prefix_cid_class_spec: // mod_prefix_cid_class_spec
      case symbol_kind::S_class_exp_class_spec: // class_exp_class_spec
        value.template destroy< pdm::ast::ClassSpec* > ();
        break;

      case symbol_kind::S_enum_type_spec_field: // enum_type_spec_field
        value.template destroy< pdm::ast::EnumTypeSpec::Field* > ();
        break;

      case symbol_kind::S_mut_expr: // mut_expr
      case symbol_kind::S_expr: // expr
      case symbol_kind::S_long_exp: // long_exp
      case symbol_kind::S_bracketed_exp: // bracketed_exp
      case symbol_kind::S_paren_exp: // paren_exp
      case symbol_kind::S_vtupleExpr: // vtupleExpr
      case symbol_kind::S_vstructExpr: // vstructExpr
      case symbol_kind::S_primary_exp: // primary_exp
      case symbol_kind::S_int_expr: // int_expr
      case symbol_kind::S_if_exp: // if_exp
      case symbol_kind::S_chain_exp: // chain_exp
      case symbol_kind::S_lambda_exp: // lambda_exp
      case symbol_kind::S_postfix_exp: // postfix_exp
      case symbol_kind::S_vcall_exp: // vcall_exp
      case symbol_kind::S_dot_name_exp: // dot_name_exp
      case symbol_kind::S_dot_index_exp: // dot_index_exp
      case symbol_kind::S_unary_exp: // unary_exp
      case symbol_kind::S_binary_exp: // binary_exp
      case symbol_kind::S_mul_binary_exp: // mul_binary_exp
      case symbol_kind::S_add_binary_exp: // add_binary_exp
      case symbol_kind::S_cmp_binary_exp: // cmp_binary_exp
      case symbol_kind::S_eq_binary_exp: // eq_binary_exp
      case symbol_kind::S_and_binary_exp: // and_binary_exp
      case symbol_kind::S_xor_binary_exp: // xor_binary_exp
      case symbol_kind::S_or_binary_exp: // or_binary_exp
        value.template destroy< pdm::ast::Exp* > ();
        break;

      case symbol_kind::S_fn_type_spec: // fn_type_spec
        value.template destroy< pdm::ast::FnTypeSpec* > ();
        break;

      case symbol_kind::S_script_header_stmt: // script_header_stmt
      case symbol_kind::S_import_stmt: // import_stmt
        value.template destroy< pdm::ast::HeaderStmt* > ();
        break;

      case symbol_kind::S_destructured_lpattern: // destructured_lpattern
      case symbol_kind::S_lpattern: // lpattern
        value.template destroy< pdm::ast::LPattern* > ();
        break;

      case symbol_kind::S_lpattern_field: // lpattern_field
        value.template destroy< pdm::ast::LPattern::Field* > ();
        break;

      case symbol_kind::S_mod_prefix: // mod_prefix
        value.template destroy< pdm::ast::ModAddress* > ();
        break;

      case symbol_kind::S_script: // script
        value.template destroy< pdm::ast::Script* > ();
        break;

      case symbol_kind::S_script_field: // script_field
        value.template destroy< pdm::ast::Script::Field* > ();
        break;

      case symbol_kind::S_chain_prefix_stmt: // chain_prefix_stmt
      case symbol_kind::S_const_stmt: // const_stmt
      case symbol_kind::S_val_stmt: // val_stmt
      case symbol_kind::S_var_stmt: // var_stmt
      case symbol_kind::S_set_stmt: // set_stmt
      case symbol_kind::S_discard_stmt: // discard_stmt
        value.template destroy< pdm::ast::Stmt* > ();
        break;

      case symbol_kind::S_struct_exp_field: // struct_exp_field
        value.template destroy< pdm::ast::StructExp::Field* > ();
        break;

      case symbol_kind::S_struct_type_spec_field: // struct_type_spec_field
        value.template destroy< pdm::ast::StructTypeSpec::Field* > ();
        break;

      case symbol_kind::S_targ: // targ
        value.template destroy< pdm::ast::TArg* > ();
        break;

      case symbol_kind::S_tpattern: // tpattern
        value.template destroy< pdm::ast::TPattern* > ();
        break;

      case symbol_kind::S_tpattern_field: // tpattern_field
        value.template destroy< pdm::ast::TPattern::Field* > ();
        break;

      case symbol_kind::S_type_query_exp: // type_query_exp
        value.template destroy< pdm::ast::TypeQueryExp* > ();
        break;

      case symbol_kind::S_type_query_op: // type_query_op
        value.template destroy< pdm::ast::TypeQueryKind > ();
        break;

      case symbol_kind::S_type_spec: // type_spec
      case symbol_kind::S_mod_prefix_tid: // mod_prefix_tid
      case symbol_kind::S_tuple_type_spec: // tuple_type_spec
      case symbol_kind::S_array_type_spec: // array_type_spec
      case symbol_kind::S_struct_type_spec: // struct_type_spec
      case symbol_kind::S_enum_type_spec: // enum_type_spec
        value.template destroy< pdm::ast::TypeSpec* > ();
        break;

      case symbol_kind::S_unary_op: // unary_op
        value.template destroy< pdm::ast::UnaryOperator > ();
        break;

      case symbol_kind::S_varg: // varg
        value.template destroy< pdm::ast::VArg* > ();
        break;

      case symbol_kind::S_vpattern: // vpattern
        value.template destroy< pdm::ast::VPattern* > ();
        break;

      case symbol_kind::S_vpattern_field: // vpattern_field
        value.template destroy< pdm::ast::VPattern::Field* > ();
        break;

      case symbol_kind::S_import_field_cl1: // import_field_cl1
        value.template destroy< std::vector<ast::ImportStmt::Field*> > ();
        break;

      case symbol_kind::S_import_field_group_sl0: // import_field_group_sl0
        value.template destroy< std::vector<ast::ImportStmt::FieldGroup*> > ();
        break;

      case symbol_kind::S_mod_field_sl: // mod_field_sl
        value.template destroy< std::vector<pdm::ast::BaseModExp::Field*> > ();
        break;

      case symbol_kind::S_enum_type_spec_field_cl: // enum_type_spec_field_cl
        value.template destroy< std::vector<pdm::ast::EnumTypeSpec::Field*> > ();
        break;

      case symbol_kind::S_mut_expr_cl1: // mut_expr_cl1
      case symbol_kind::S_expr_cl2: // expr_cl2
        value.template destroy< std::vector<pdm::ast::Exp*> > ();
        break;

      case symbol_kind::S_script_header: // script_header
        value.template destroy< std::vector<pdm::ast::HeaderStmt*> > ();
        break;

      case symbol_kind::S_lpattern_field_cl: // lpattern_field_cl
        value.template destroy< std::vector<pdm::ast::LPattern::Field*> > ();
        break;

      case symbol_kind::S_script_field_sl: // script_field_sl
        value.template destroy< std::vector<pdm::ast::Script::Field*> > ();
        break;

      case symbol_kind::S_chain_prefix: // chain_prefix
        value.template destroy< std::vector<pdm::ast::Stmt*> > ();
        break;

      case symbol_kind::S_stringls: // stringls
        value.template destroy< std::vector<pdm::ast::StringExp::Piece> > ();
        break;

      case symbol_kind::S_struct_exp_field_cl: // struct_exp_field_cl
        value.template destroy< std::vector<pdm::ast::StructExp::Field*> > ();
        break;

      case symbol_kind::S_struct_type_spec_field_cl: // struct_type_spec_field_cl
        value.template destroy< std::vector<pdm::ast::StructTypeSpec::Field*> > ();
        break;

      case symbol_kind::S_targ_cl: // targ_cl
        value.template destroy< std::vector<pdm::ast::TArg*> > ();
        break;

      case symbol_kind::S_tpattern_field_cl1: // tpattern_field_cl1
        value.template destroy< std::vector<pdm::ast::TPattern::Field*> > ();
        break;

      case symbol_kind::S_type_query_exp_sl0: // type_query_exp_sl0
        value.template destroy< std::vector<pdm::ast::TypeQueryExp*> > ();
        break;

      case symbol_kind::S_type_spec_cl2: // type_spec_cl2
        value.template destroy< std::vector<pdm::ast::TypeSpec*> > ();
        break;

      case symbol_kind::S_varg_cl: // varg_cl
        value.template destroy< std::vector<pdm::ast::VArg*> > ();
        break;

      case symbol_kind::S_vpattern_field_cl: // vpattern_field_cl
        value.template destroy< std::vector<pdm::ast::VPattern::Field*> > ();
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
      void clear () YY_NOEXCEPT;

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
#else
      symbol_type (int tok, const location_type& l)
        : super_type(token_type (tok), l)
#endif
      {}
#if 201103L <= YY_CPLUSPLUS
      symbol_type (int tok, TokenInfo v, location_type l)
        : super_type(token_type (tok), std::move (v), std::move (l))
#else
      symbol_type (int tok, const TokenInfo& v, const location_type& l)
        : super_type(token_type (tok), v, l)
#endif
      {}
    };

    /// Build a parser object.
    parser (pdm::source::ISource* source_yyarg, pdm::parser::Lexer* lexer_yyarg, pdm::ast::Manager* mgr_yyarg, pdm::ast::Script** returnp_yyarg);
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
      make_VID (TokenInfo v, location_type l)
      {
        return symbol_type (token::VID, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_VID (const TokenInfo& v, const location_type& l)
      {
        return symbol_type (token::VID, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TID (TokenInfo v, location_type l)
      {
        return symbol_type (token::TID, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_TID (const TokenInfo& v, const location_type& l)
      {
        return symbol_type (token::TID, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CID (TokenInfo v, location_type l)
      {
        return symbol_type (token::CID, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_CID (const TokenInfo& v, const location_type& l)
      {
        return symbol_type (token::CID, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_HOLE (TokenInfo v, location_type l)
      {
        return symbol_type (token::HOLE, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_HOLE (const TokenInfo& v, const location_type& l)
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
      make_KW_STRUCT (location_type l)
      {
        return symbol_type (token::KW_STRUCT, std::move (l));
      }
#else
      static
      symbol_type
      make_KW_STRUCT (const location_type& l)
      {
        return symbol_type (token::KW_STRUCT, l);
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
      make_KW_IMPORTS (location_type l)
      {
        return symbol_type (token::KW_IMPORTS, std::move (l));
      }
#else
      static
      symbol_type
      make_KW_IMPORTS (const location_type& l)
      {
        return symbol_type (token::KW_IMPORTS, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_KW_EXTERN (location_type l)
      {
        return symbol_type (token::KW_EXTERN, std::move (l));
      }
#else
      static
      symbol_type
      make_KW_EXTERN (const location_type& l)
      {
        return symbol_type (token::KW_EXTERN, l);
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
      make_KW_VAL (location_type l)
      {
        return symbol_type (token::KW_VAL, std::move (l));
      }
#else
      static
      symbol_type
      make_KW_VAL (const location_type& l)
      {
        return symbol_type (token::KW_VAL, l);
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
      make_KW_OUT (location_type l)
      {
        return symbol_type (token::KW_OUT, std::move (l));
      }
#else
      static
      symbol_type
      make_KW_OUT (const location_type& l)
      {
        return symbol_type (token::KW_OUT, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_KW_INOUT (location_type l)
      {
        return symbol_type (token::KW_INOUT, std::move (l));
      }
#else
      static
      symbol_type
      make_KW_INOUT (const location_type& l)
      {
        return symbol_type (token::KW_INOUT, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_KW_DISCARD (location_type l)
      {
        return symbol_type (token::KW_DISCARD, std::move (l));
      }
#else
      static
      symbol_type
      make_KW_DISCARD (const location_type& l)
      {
        return symbol_type (token::KW_DISCARD, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_KW_AS (location_type l)
      {
        return symbol_type (token::KW_AS, std::move (l));
      }
#else
      static
      symbol_type
      make_KW_AS (const location_type& l)
      {
        return symbol_type (token::KW_AS, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_KW_FOR (location_type l)
      {
        return symbol_type (token::KW_FOR, std::move (l));
      }
#else
      static
      symbol_type
      make_KW_FOR (const location_type& l)
      {
        return symbol_type (token::KW_FOR, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_KW_CORE_PROFILE (location_type l)
      {
        return symbol_type (token::KW_CORE_PROFILE, std::move (l));
      }
#else
      static
      symbol_type
      make_KW_CORE_PROFILE (const location_type& l)
      {
        return symbol_type (token::KW_CORE_PROFILE, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_KW_BROWSER_PROFILE (location_type l)
      {
        return symbol_type (token::KW_BROWSER_PROFILE, std::move (l));
      }
#else
      static
      symbol_type
      make_KW_BROWSER_PROFILE (const location_type& l)
      {
        return symbol_type (token::KW_BROWSER_PROFILE, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_KW_NATIVE_PROFILE (location_type l)
      {
        return symbol_type (token::KW_NATIVE_PROFILE, std::move (l));
      }
#else
      static
      symbol_type
      make_KW_NATIVE_PROFILE (const location_type& l)
      {
        return symbol_type (token::KW_NATIVE_PROFILE, l);
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
      make_UNSIGNED_DINT_LIT (TokenInfo v, location_type l)
      {
        return symbol_type (token::UNSIGNED_DINT_LIT, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_UNSIGNED_DINT_LIT (const TokenInfo& v, const location_type& l)
      {
        return symbol_type (token::UNSIGNED_DINT_LIT, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_UNSIGNED_XINT_LIT (TokenInfo v, location_type l)
      {
        return symbol_type (token::UNSIGNED_XINT_LIT, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_UNSIGNED_XINT_LIT (const TokenInfo& v, const location_type& l)
      {
        return symbol_type (token::UNSIGNED_XINT_LIT, v, l);
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
      make_COLON_LTHAN (location_type l)
      {
        return symbol_type (token::COLON_LTHAN, std::move (l));
      }
#else
      static
      symbol_type
      make_COLON_LTHAN (const location_type& l)
      {
        return symbol_type (token::COLON_LTHAN, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_GTHAN_COLON (location_type l)
      {
        return symbol_type (token::GTHAN_COLON, std::move (l));
      }
#else
      static
      symbol_type
      make_GTHAN_COLON (const location_type& l)
      {
        return symbol_type (token::GTHAN_COLON, l);
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

    static const short yypact_ninf_;
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
      yylast_ = 659,     ///< Last index in yytable_.
      yynnts_ = 94,  ///< Number of nonterminal symbols.
      yyfinal_ = 3 ///< Termination state number.
    };


    // User arguments.
    pdm::source::ISource* source;
    pdm::parser::Lexer* lexer;
    pdm::ast::Manager* mgr;
    pdm::ast::Script** returnp;

  };


#line 11 "parser.yy"
} } // pdm::parser
#line 3735 "parser.tab.hh"


// "%code provides" blocks.
#line 39 "parser.yy"

    using Tk = pdm::parser::parser::token_kind_type;
#line 186 "parser.yy"

    // int yylex(pdm::parser::TokenInfo *lvalp, pdm::source::Loc *llocp, pdm::source::ISource* source, pdm::parser::Lexer* lexer);
    int yylex(pdm::parser::parser::semantic_type* st, pdm::source::Loc* llocp, pdm::source::ISource* source, pdm::parser::Lexer* lexer);
    void yyerror(pdm::source::Loc* llocp, char const* message, pdm::source::ISource* source, pdm::parser::Lexer* lexer);

#line 3748 "parser.tab.hh"


#endif // !YY_YY_PARSER_TAB_HH_INCLUDED
