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
#line 28 "parser.yy"

    #include <stb/stretchy_buffer.h>

    #include "pdm/core/config.hh"

    // todo: include more AST files here:
    #include "pdm/ast/node.hh"
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

#line 78 "parser.tab.hh"


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

#line 18 "parser.yy"
namespace pdm { namespace parser {
#line 208 "parser.tab.hh"




  /// A Bison parser.
  class parser
  {
  public:
#ifndef YYSTYPE
    /// Symbol semantic values.
    union semantic_type
    {
#line 85 "parser.yy"

    pdm::parser::TokenInfo token;
    
    pdm::ast::Script* script;
    pdm::ast::Script** script_sb;
    
    pdm::ast::Stmt* stmt;
    pdm::ast::Stmt** stmt_sb;

    pdm::ast::Exp* exp;
    pdm::ast::Exp** exp_sb;

    pdm::ast::UnaryOperator uop;
    pdm::ast::BinaryOperator bop;

    pdm::ast::StructExp::Field* structexp_field;
    pdm::ast::StructExp::Field** structexp_field_sb;

    pdm::ast::Typespec* typespec;
    pdm::ast::Typespec** typespec_sb;

    pdm::ast::LPattern* lpattern;
    pdm::ast::VPattern* vpattern;
    pdm::ast::TPattern* tpattern;
    pdm::ast::LPattern::Field* lpattern_field;
    pdm::ast::VPattern::Field* vpattern_field;
    pdm::ast::TPattern::Field* tpattern_field;

    pdm::ast::TCallExp::Arg* tcallexp_arg;
    pdm::ast::TCallExp::Arg** tcallexp_arg_sb;

    pdm::ast::TCallTypespec::Arg* tcallts_arg;
    pdm::ast::TCallTypespec::Arg** tcallts_arg_sb;

    pdm::ast::StructTypespec::Field* structts_field;
    pdm::ast::StructTypespec::Field** structts_field_sb;

#line 259 "parser.tab.hh"

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
    TK_VID = 258,                  // "<val_id>"
    TK_TID = 259,                  // "<TypeId>"
    TK_HOLE = 260,                 // "<__42__>"
    TK_KW_USING = 261,             // "using"
    TK_KW_MOD = 262,               // "mod"
    TK_KW_IF = 263,                // "if"
    TK_KW_THEN = 264,              // "then"
    TK_KW_ELSE = 265,              // "else"
    TK_KW_MATCH = 266,             // "match"
    TK_KW_WITH = 267,              // "with"
    TK_KW_IMPORT = 268,            // "import"
    TK_KW_LINK = 269,              // "link"
    TK_KW_FROM = 270,              // "from"
    TK_KW_AS = 271,                // "as"
    TK_KW_LET = 272,               // "let"
    TK_KW_SET = 273,               // "set"
    TK_KW_FN = 274,                // "fn"
    TK_KW_TYPE = 275,              // "type"
    TK_KW_ENUM = 276,              // "enum"
    TK_KW_AND = 277,               // "and"
    TK_KW_XOR = 278,               // "xor"
    TK_KW_OR = 279,                // "or"
    TK_KW_NOT = 280,               // "not"
    TK_DINT_LIT = 281,             // "42"
    TK_XINT_LIT = 282,             // "0x2a"
    TK_FLOAT_LIT = 283,            // "4.2"
    TK_DQSTRING_LIT = 284,         // "\"dq-string-literal\""
    TK_SQSTRING_LIT = 285,         // "'sq-string-literal'"
    TK_DOT = 286,                  // "."
    TK_COLON = 287,                // ":"
    TK_COMMA = 288,                // ","
    TK_SEMICOLON = 289,            // ";"
    TK_DBL_COLON = 290,            // "::"
    TK_LPAREN = 291,               // "("
    TK_RPAREN = 292,               // ")"
    TK_LSQBRK = 293,               // "["
    TK_RSQBRK = 294,               // "]"
    TK_LCYBRK = 295,               // "{"
    TK_RCYBRK = 296,               // "}"
    TK_ARROW = 297,                // "->"
    TK_ASTERISK = 298,             // "*"
    TK_FSLASH = 299,               // "/"
    TK_PERCENT = 300,              // "%"
    TK_PLUS = 301,                 // "+"
    TK_MINUS = 302,                // "-"
    TK_LTHAN = 303,                // "<"
    TK_LETHAN = 304,               // "<="
    TK_GTHAN = 305,                // ">"
    TK_GETHAN = 306,               // ">="
    TK_BIND = 307,                 // "="
    TK_EQUALS = 308,               // "=="
    TK_NEQUALS = 309,              // "!="
    TK_CARET = 310,                // "^"
    TK_AMPERSAND = 311,            // "&"
    TK_EXCLAIM = 312,              // "!"
    TK_EOS = 313,                  // "EOS"
    TK_NULL = 314                  // "<null>"
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
        YYNTOKENS = 60, ///< Number of tokens.
        S_YYEMPTY = -2,
        S_YYEOF = 0,                             // "end of file"
        S_YYerror = 1,                           // error
        S_YYUNDEF = 2,                           // "invalid token"
        S_TK_VID = 3,                            // "<val_id>"
        S_TK_TID = 4,                            // "<TypeId>"
        S_TK_HOLE = 5,                           // "<__42__>"
        S_TK_KW_USING = 6,                       // "using"
        S_TK_KW_MOD = 7,                         // "mod"
        S_TK_KW_IF = 8,                          // "if"
        S_TK_KW_THEN = 9,                        // "then"
        S_TK_KW_ELSE = 10,                       // "else"
        S_TK_KW_MATCH = 11,                      // "match"
        S_TK_KW_WITH = 12,                       // "with"
        S_TK_KW_IMPORT = 13,                     // "import"
        S_TK_KW_LINK = 14,                       // "link"
        S_TK_KW_FROM = 15,                       // "from"
        S_TK_KW_AS = 16,                         // "as"
        S_TK_KW_LET = 17,                        // "let"
        S_TK_KW_SET = 18,                        // "set"
        S_TK_KW_FN = 19,                         // "fn"
        S_TK_KW_TYPE = 20,                       // "type"
        S_TK_KW_ENUM = 21,                       // "enum"
        S_TK_KW_AND = 22,                        // "and"
        S_TK_KW_XOR = 23,                        // "xor"
        S_TK_KW_OR = 24,                         // "or"
        S_TK_KW_NOT = 25,                        // "not"
        S_TK_DINT_LIT = 26,                      // "42"
        S_TK_XINT_LIT = 27,                      // "0x2a"
        S_TK_FLOAT_LIT = 28,                     // "4.2"
        S_TK_DQSTRING_LIT = 29,                  // "\"dq-string-literal\""
        S_TK_SQSTRING_LIT = 30,                  // "'sq-string-literal'"
        S_TK_DOT = 31,                           // "."
        S_TK_COLON = 32,                         // ":"
        S_TK_COMMA = 33,                         // ","
        S_TK_SEMICOLON = 34,                     // ";"
        S_TK_DBL_COLON = 35,                     // "::"
        S_TK_LPAREN = 36,                        // "("
        S_TK_RPAREN = 37,                        // ")"
        S_TK_LSQBRK = 38,                        // "["
        S_TK_RSQBRK = 39,                        // "]"
        S_TK_LCYBRK = 40,                        // "{"
        S_TK_RCYBRK = 41,                        // "}"
        S_TK_ARROW = 42,                         // "->"
        S_TK_ASTERISK = 43,                      // "*"
        S_TK_FSLASH = 44,                        // "/"
        S_TK_PERCENT = 45,                       // "%"
        S_TK_PLUS = 46,                          // "+"
        S_TK_MINUS = 47,                         // "-"
        S_TK_LTHAN = 48,                         // "<"
        S_TK_LETHAN = 49,                        // "<="
        S_TK_GTHAN = 50,                         // ">"
        S_TK_GETHAN = 51,                        // ">="
        S_TK_BIND = 52,                          // "="
        S_TK_EQUALS = 53,                        // "=="
        S_TK_NEQUALS = 54,                       // "!="
        S_TK_CARET = 55,                         // "^"
        S_TK_AMPERSAND = 56,                     // "&"
        S_TK_EXCLAIM = 57,                       // "!"
        S_TK_EOS = 58,                           // "EOS"
        S_TK_NULL = 59,                          // "<null>"
        S_YYACCEPT = 60,                         // $accept
        S_script = 61,                           // script
        S_scriptContent = 62,                    // scriptContent
        S_scriptContentStmt = 63,                // scriptContentStmt
        S_moduleStmt = 64,                       // moduleStmt
        S_moduleContent = 65,                    // moduleContent
        S_chainPrefixStmt = 66,                  // chainPrefixStmt
        S_letStmt = 67,                          // letStmt
        S_setStmt = 68,                          // setStmt
        S_discardStmt = 69,                      // discardStmt
        S_moduleContentStmt = 70,                // moduleContentStmt
        S_defStmt = 71,                          // defStmt
        S_typedefStmt = 72,                      // typedefStmt
        S_typedefStmt_enum = 73,                 // typedefStmt_enum
        S_importStmt = 74,                       // importStmt
        S_linkStmt = 75,                         // linkStmt
        S_linkStmtItem = 76,                     // linkStmtItem
        S_linkStmtContent = 77,                  // linkStmtContent
        S_tid = 78,                              // tid
        S_vid = 79,                              // vid
        S_floatl = 80,                           // floatl
        S_stringl = 81,                          // stringl
        S_expr = 82,                             // expr
        S_expr_cl1 = 83,                         // expr_cl1
        S_expr_cl2 = 84,                         // expr_cl2
        S_parenExpr = 85,                        // parenExpr
        S_unitExpr = 86,                         // unitExpr
        S_primaryExpr = 87,                      // primaryExpr
        S_vparenExpr = 88,                       // vparenExpr
        S_vtupleExpr = 89,                       // vtupleExpr
        S_vstructExpr = 90,                      // vstructExpr
        S_ifThenElseExpr = 91,                   // ifThenElseExpr
        S_chainExpr = 92,                        // chainExpr
        S_chainPrefix = 93,                      // chainPrefix
        S_vlambdaExpr = 94,                      // vlambdaExpr
        S_postfixExpr = 95,                      // postfixExpr
        S_vtcallExpr = 96,                       // vtcallExpr
        S_vvcallExpr = 97,                       // vvcallExpr
        S_dotNmExpr = 98,                        // dotNmExpr
        S_dotIxExpr = 99,                        // dotIxExpr
        S_unaryExpr = 100,                       // unaryExpr
        S_unaryOp = 101,                         // unaryOp
        S_binaryExpr = 102,                      // binaryExpr
        S_mulBinaryOp = 103,                     // mulBinaryOp
        S_mulBinaryExpr = 104,                   // mulBinaryExpr
        S_addBinaryOp = 105,                     // addBinaryOp
        S_addBinaryExpr = 106,                   // addBinaryExpr
        S_cmpBinaryOp = 107,                     // cmpBinaryOp
        S_cmpBinaryExpr = 108,                   // cmpBinaryExpr
        S_eqBinaryOp = 109,                      // eqBinaryOp
        S_eqBinaryExpr = 110,                    // eqBinaryExpr
        S_andBinaryExpr = 111,                   // andBinaryExpr
        S_xorBinaryExpr = 112,                   // xorBinaryExpr
        S_orBinaryExpr = 113,                    // orBinaryExpr
        S_typespec = 114,                        // typespec
        S_typespec_cl = 115,                     // typespec_cl
        S_structTypespecField = 116,             // structTypespecField
        S_structTypespecField_cl = 117,          // structTypespecField_cl
        S_primaryTypespec = 118,                 // primaryTypespec
        S_parenTypespec = 119,                   // parenTypespec
        S_structTypespec = 120,                  // structTypespec
        S_tupleTypespec = 121,                   // tupleTypespec
        S_postfixTypespec = 122,                 // postfixTypespec
        S_ttcall = 123,                          // ttcall
        S_tdot = 124,                            // tdot
        S_unaryTypespec = 125,                   // unaryTypespec
        S_ttarg = 126,                           // ttarg
        S_ttarg_cl = 127,                        // ttarg_cl
        S_vtarg = 128,                           // vtarg
        S_vtarg_cl = 129,                        // vtarg_cl
        S_vstructExprField = 130,                // vstructExprField
        S_vpatternField = 131,                   // vpatternField
        S_lpatternField = 132,                   // lpatternField
        S_tpatternField = 133,                   // tpatternField
        S_lpattern = 134,                        // lpattern
        S_vpattern = 135,                        // vpattern
        S_tpattern = 136,                        // tpattern
        S_vpatternField_cl = 137,                // vpatternField_cl
        S_lpatternField_cl = 138,                // lpatternField_cl
        S_tpatternField_cl = 139,                // tpatternField_cl
        S_vstructExprField_cl = 140              // vstructExprField_cl
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
        , value (std::move (that.value))
        , location (std::move (that.location))
      {}
#endif

      /// Copy constructor.
      basic_symbol (const basic_symbol& that);
      /// Constructor for valueless symbols.
      basic_symbol (typename Base::kind_type t,
                    YY_MOVE_REF (location_type) l);

      /// Constructor for symbols with semantic value.
      basic_symbol (typename Base::kind_type t,
                    YY_RVREF (semantic_type) v,
                    YY_RVREF (location_type) l);

      /// Destroy the symbol.
      ~basic_symbol ()
      {
        clear ();
      }

      /// Destroy contents, and record that is empty.
      void clear ()
      {
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
    {};

    /// Build a parser object.
    parser (pdm::source::Source* source_yyarg, pdm::parser::Lexer* lexer_yyarg, pdm::ast::Script** outp_yyarg);
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
      yylast_ = 424,     ///< Last index in yytable_.
      yynnts_ = 81,  ///< Number of nonterminal symbols.
      yyfinal_ = 7 ///< Termination state number.
    };


    // User arguments.
    pdm::source::Source* source;
    pdm::parser::Lexer* lexer;
    pdm::ast::Script** outp;

  };


#line 18 "parser.yy"
} } // pdm::parser
#line 1014 "parser.tab.hh"


// "%code provides" blocks.
#line 208 "parser.yy"

    int yylex(pdm::parser::TokenInfo *lvalp, pdm::source::Loc *llocp, pdm::source::Source* source, pdm::parser::Lexer* lexer);
    void yyerror(pdm::source::Loc* llocp, char const* message, pdm::source::Source* source, pdm::parser::Lexer* lexer);

#line 1023 "parser.tab.hh"


#endif // !YY_YY_PARSER_TAB_HH_INCLUDED
