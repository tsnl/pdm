// A Bison parser, made by GNU Bison 3.7.3.

// Skeleton implementation for Bison LALR(1) parsers in C++

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

// DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
// especially those whose name start with YY_ or yy_.  They are
// private implementation details that can be changed or removed.



// First part of user prologue.
#line 75 "parser.yy"

    // #define YYSTYPE pdm::parser::TokenInfo

#line 45 "parser.tab.cc"


#include "parser.tab.hh"




#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> // FIXME: INFRINGES ON USER NAME SPACE.
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif


// Whether we are compiled with exception support.
#ifndef YY_EXCEPTIONS
# if defined __GNUC__ && !defined __EXCEPTIONS
#  define YY_EXCEPTIONS 0
# else
#  define YY_EXCEPTIONS 1
# endif
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K].location)
/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

# ifndef YYLLOC_DEFAULT
#  define YYLLOC_DEFAULT(Current, Rhs, N)                               \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).begin  = YYRHSLOC (Rhs, 1).begin;                   \
          (Current).end    = YYRHSLOC (Rhs, N).end;                     \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).begin = (Current).end = YYRHSLOC (Rhs, 0).end;      \
        }                                                               \
    while (false)
# endif


// Enable debugging if requested.
#if YYDEBUG

// A pseudo ostream that takes yydebug_ into account.
# define YYCDEBUG if (yydebug_) (*yycdebug_)

# define YY_SYMBOL_PRINT(Title, Symbol)         \
  do {                                          \
    if (yydebug_)                               \
    {                                           \
      *yycdebug_ << Title << ' ';               \
      yy_print_ (*yycdebug_, Symbol);           \
      *yycdebug_ << '\n';                       \
    }                                           \
  } while (false)

# define YY_REDUCE_PRINT(Rule)          \
  do {                                  \
    if (yydebug_)                       \
      yy_reduce_print_ (Rule);          \
  } while (false)

# define YY_STACK_PRINT()               \
  do {                                  \
    if (yydebug_)                       \
      yy_stack_print_ ();                \
  } while (false)

#else // !YYDEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YYUSE (Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void> (0)
# define YY_STACK_PRINT()                static_cast<void> (0)

#endif // !YYDEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)

#line 33 "parser.yy"
namespace pdm { namespace parser {
#line 143 "parser.tab.cc"

  /// Build a parser object.
  parser::parser (pdm::source::Source* source_yyarg, pdm::parser::Lexer* lexer_yyarg, pdm::ast::Manager* mgr_yyarg, pdm::ast::Script** returnp_yyarg)
#if YYDEBUG
    : yydebug_ (false),
      yycdebug_ (&std::cerr),
#else
    :
#endif
      source (source_yyarg),
      lexer (lexer_yyarg),
      mgr (mgr_yyarg),
      returnp (returnp_yyarg)
  {}

  parser::~parser ()
  {}

  parser::syntax_error::~syntax_error () YY_NOEXCEPT YY_NOTHROW
  {}

  /*---------------.
  | symbol kinds.  |
  `---------------*/

  // basic_symbol.
  template <typename Base>
  parser::basic_symbol<Base>::basic_symbol (const basic_symbol& that)
    : Base (that)
    , value ()
    , location (that.location)
  {
    switch (this->kind ())
    {
      case symbol_kind::S_VID: // "<val_id>"
      case symbol_kind::S_TID: // "<TypeId>"
      case symbol_kind::S_HOLE: // "<__42__>"
      case symbol_kind::S_DINT_LIT: // "42"
      case symbol_kind::S_XINT_LIT: // "0x2a"
      case symbol_kind::S_FLOAT_LIT: // "4.2"
      case symbol_kind::S_DQSTRING_LIT: // "\"dq-string-literal\""
      case symbol_kind::S_SQSTRING_LIT: // "'sq-string-literal'"
      case symbol_kind::S_tid: // tid
      case symbol_kind::S_vid: // vid
      case symbol_kind::S_floatl: // floatl
      case symbol_kind::S_stringl: // stringl
        value.copy< TokenInfo > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_mulBinaryOp: // mulBinaryOp
      case symbol_kind::S_addBinaryOp: // addBinaryOp
      case symbol_kind::S_cmpBinaryOp: // cmpBinaryOp
      case symbol_kind::S_eqBinaryOp: // eqBinaryOp
        value.copy< pdm::ast::BinaryOperator > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_enum_field: // enum_field
        value.copy< pdm::ast::EnumStmt::Field* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr: // expr
      case symbol_kind::S_parenExpr: // parenExpr
      case symbol_kind::S_unitExpr: // unitExpr
      case symbol_kind::S_vparenExpr: // vparenExpr
      case symbol_kind::S_vtupleExpr: // vtupleExpr
      case symbol_kind::S_vstructExpr: // vstructExpr
      case symbol_kind::S_primaryExpr: // primaryExpr
      case symbol_kind::S_int_expr: // int_expr
      case symbol_kind::S_ifThenElseExpr: // ifThenElseExpr
      case symbol_kind::S_chainExpr: // chainExpr
      case symbol_kind::S_vlambdaExpr: // vlambdaExpr
      case symbol_kind::S_postfixExpr: // postfixExpr
      case symbol_kind::S_tcall_exp: // tcall_exp
      case symbol_kind::S_vcall_exp: // vcall_exp
      case symbol_kind::S_dot_name_exp: // dot_name_exp
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
      case symbol_kind::S_type_query_exp: // type_query_exp
        value.copy< pdm::ast::Exp* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_lpattern: // lpattern
      case symbol_kind::S_lpattern_naked: // lpattern_naked
        value.copy< pdm::ast::LPattern* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_lpatternField: // lpatternField
        value.copy< pdm::ast::LPattern::Field* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_script: // script
        value.copy< pdm::ast::Script* > (YY_MOVE (that.value));
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
      case symbol_kind::S_extern_stmt: // extern_stmt
        value.copy< pdm::ast::Stmt* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_vstructExprField: // vstructExprField
        value.copy< pdm::ast::StructExp::Field* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_structTypespecField: // structTypespecField
        value.copy< pdm::ast::StructTypespec::Field* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_ttarg: // ttarg
      case symbol_kind::S_vtarg: // vtarg
        value.copy< pdm::ast::TArg* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_tpattern: // tpattern
        value.copy< pdm::ast::TPattern* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_tpatternField: // tpatternField
        value.copy< pdm::ast::TPattern::Field* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_type_query_op: // type_query_op
        value.copy< pdm::ast::TypeQueryKind > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_typespec: // typespec
      case symbol_kind::S_primaryTypespec: // primaryTypespec
      case symbol_kind::S_parenTypespec: // parenTypespec
      case symbol_kind::S_tupleTypespec: // tupleTypespec
      case symbol_kind::S_mod_prefix_tid: // mod_prefix_tid
      case symbol_kind::S_fn_typespec: // fn_typespec
      case symbol_kind::S_postfixTypespec: // postfixTypespec
      case symbol_kind::S_ttcall: // ttcall
      case symbol_kind::S_tdot: // tdot
      case symbol_kind::S_unaryTypespec: // unaryTypespec
      case symbol_kind::S_long_typespec: // long_typespec
      case symbol_kind::S_structTypespec: // structTypespec
        value.copy< pdm::ast::Typespec* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_unaryOp: // unaryOp
        value.copy< pdm::ast::UnaryOperator > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_vpattern: // vpattern
        value.copy< pdm::ast::VPattern* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_vpatternField: // vpatternField
        value.copy< pdm::ast::VPattern::Field* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_enum_field_pl: // enum_field_pl
      case symbol_kind::S_unprefixed_enum_field_pl: // unprefixed_enum_field_pl
        value.copy< std::vector<pdm::ast::EnumStmt::Field*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_cl1: // expr_cl1
      case symbol_kind::S_expr_cl2: // expr_cl2
      case symbol_kind::S_expr_sl: // expr_sl
        value.copy< std::vector<pdm::ast::Exp*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_lpatternField_cl: // lpatternField_cl
        value.copy< std::vector<pdm::ast::LPattern::Field*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_scriptContent: // scriptContent
      case symbol_kind::S_moduleContent: // moduleContent
      case symbol_kind::S_chainPrefix: // chainPrefix
        value.copy< std::vector<pdm::ast::Stmt*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stringls: // stringls
        value.copy< std::vector<pdm::ast::StringExp::Piece> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_vstructExprField_cl: // vstructExprField_cl
        value.copy< std::vector<pdm::ast::StructExp::Field*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_structTypespecField_cl: // structTypespecField_cl
        value.copy< std::vector<pdm::ast::StructTypespec::Field*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_ttarg_cl: // ttarg_cl
      case symbol_kind::S_vtarg_cl: // vtarg_cl
        value.copy< std::vector<pdm::ast::TArg*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_tpattern_seq: // tpattern_seq
        value.copy< std::vector<pdm::ast::TPattern*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_tpatternField_cl: // tpatternField_cl
        value.copy< std::vector<pdm::ast::TPattern::Field*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_typespec_cl1: // typespec_cl1
      case symbol_kind::S_typespec_cl2: // typespec_cl2
        value.copy< std::vector<pdm::ast::Typespec*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_vpatternField_cl: // vpatternField_cl
        value.copy< std::vector<pdm::ast::VPattern::Field*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_mod_prefix: // mod_prefix
        value.copy< std::vector<pdm::intern::String> > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

  }



  template <typename Base>
  parser::symbol_kind_type
  parser::basic_symbol<Base>::type_get () const YY_NOEXCEPT
  {
    return this->kind ();
  }

  template <typename Base>
  bool
  parser::basic_symbol<Base>::empty () const YY_NOEXCEPT
  {
    return this->kind () == symbol_kind::S_YYEMPTY;
  }

  template <typename Base>
  void
  parser::basic_symbol<Base>::move (basic_symbol& s)
  {
    super_type::move (s);
    switch (this->kind ())
    {
      case symbol_kind::S_VID: // "<val_id>"
      case symbol_kind::S_TID: // "<TypeId>"
      case symbol_kind::S_HOLE: // "<__42__>"
      case symbol_kind::S_DINT_LIT: // "42"
      case symbol_kind::S_XINT_LIT: // "0x2a"
      case symbol_kind::S_FLOAT_LIT: // "4.2"
      case symbol_kind::S_DQSTRING_LIT: // "\"dq-string-literal\""
      case symbol_kind::S_SQSTRING_LIT: // "'sq-string-literal'"
      case symbol_kind::S_tid: // tid
      case symbol_kind::S_vid: // vid
      case symbol_kind::S_floatl: // floatl
      case symbol_kind::S_stringl: // stringl
        value.move< TokenInfo > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_mulBinaryOp: // mulBinaryOp
      case symbol_kind::S_addBinaryOp: // addBinaryOp
      case symbol_kind::S_cmpBinaryOp: // cmpBinaryOp
      case symbol_kind::S_eqBinaryOp: // eqBinaryOp
        value.move< pdm::ast::BinaryOperator > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_enum_field: // enum_field
        value.move< pdm::ast::EnumStmt::Field* > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_expr: // expr
      case symbol_kind::S_parenExpr: // parenExpr
      case symbol_kind::S_unitExpr: // unitExpr
      case symbol_kind::S_vparenExpr: // vparenExpr
      case symbol_kind::S_vtupleExpr: // vtupleExpr
      case symbol_kind::S_vstructExpr: // vstructExpr
      case symbol_kind::S_primaryExpr: // primaryExpr
      case symbol_kind::S_int_expr: // int_expr
      case symbol_kind::S_ifThenElseExpr: // ifThenElseExpr
      case symbol_kind::S_chainExpr: // chainExpr
      case symbol_kind::S_vlambdaExpr: // vlambdaExpr
      case symbol_kind::S_postfixExpr: // postfixExpr
      case symbol_kind::S_tcall_exp: // tcall_exp
      case symbol_kind::S_vcall_exp: // vcall_exp
      case symbol_kind::S_dot_name_exp: // dot_name_exp
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
      case symbol_kind::S_type_query_exp: // type_query_exp
        value.move< pdm::ast::Exp* > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_lpattern: // lpattern
      case symbol_kind::S_lpattern_naked: // lpattern_naked
        value.move< pdm::ast::LPattern* > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_lpatternField: // lpatternField
        value.move< pdm::ast::LPattern::Field* > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_script: // script
        value.move< pdm::ast::Script* > (YY_MOVE (s.value));
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
      case symbol_kind::S_extern_stmt: // extern_stmt
        value.move< pdm::ast::Stmt* > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_vstructExprField: // vstructExprField
        value.move< pdm::ast::StructExp::Field* > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_structTypespecField: // structTypespecField
        value.move< pdm::ast::StructTypespec::Field* > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_ttarg: // ttarg
      case symbol_kind::S_vtarg: // vtarg
        value.move< pdm::ast::TArg* > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_tpattern: // tpattern
        value.move< pdm::ast::TPattern* > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_tpatternField: // tpatternField
        value.move< pdm::ast::TPattern::Field* > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_type_query_op: // type_query_op
        value.move< pdm::ast::TypeQueryKind > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_typespec: // typespec
      case symbol_kind::S_primaryTypespec: // primaryTypespec
      case symbol_kind::S_parenTypespec: // parenTypespec
      case symbol_kind::S_tupleTypespec: // tupleTypespec
      case symbol_kind::S_mod_prefix_tid: // mod_prefix_tid
      case symbol_kind::S_fn_typespec: // fn_typespec
      case symbol_kind::S_postfixTypespec: // postfixTypespec
      case symbol_kind::S_ttcall: // ttcall
      case symbol_kind::S_tdot: // tdot
      case symbol_kind::S_unaryTypespec: // unaryTypespec
      case symbol_kind::S_long_typespec: // long_typespec
      case symbol_kind::S_structTypespec: // structTypespec
        value.move< pdm::ast::Typespec* > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_unaryOp: // unaryOp
        value.move< pdm::ast::UnaryOperator > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_vpattern: // vpattern
        value.move< pdm::ast::VPattern* > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_vpatternField: // vpatternField
        value.move< pdm::ast::VPattern::Field* > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_enum_field_pl: // enum_field_pl
      case symbol_kind::S_unprefixed_enum_field_pl: // unprefixed_enum_field_pl
        value.move< std::vector<pdm::ast::EnumStmt::Field*> > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_expr_cl1: // expr_cl1
      case symbol_kind::S_expr_cl2: // expr_cl2
      case symbol_kind::S_expr_sl: // expr_sl
        value.move< std::vector<pdm::ast::Exp*> > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_lpatternField_cl: // lpatternField_cl
        value.move< std::vector<pdm::ast::LPattern::Field*> > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_scriptContent: // scriptContent
      case symbol_kind::S_moduleContent: // moduleContent
      case symbol_kind::S_chainPrefix: // chainPrefix
        value.move< std::vector<pdm::ast::Stmt*> > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_stringls: // stringls
        value.move< std::vector<pdm::ast::StringExp::Piece> > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_vstructExprField_cl: // vstructExprField_cl
        value.move< std::vector<pdm::ast::StructExp::Field*> > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_structTypespecField_cl: // structTypespecField_cl
        value.move< std::vector<pdm::ast::StructTypespec::Field*> > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_ttarg_cl: // ttarg_cl
      case symbol_kind::S_vtarg_cl: // vtarg_cl
        value.move< std::vector<pdm::ast::TArg*> > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_tpattern_seq: // tpattern_seq
        value.move< std::vector<pdm::ast::TPattern*> > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_tpatternField_cl: // tpatternField_cl
        value.move< std::vector<pdm::ast::TPattern::Field*> > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_typespec_cl1: // typespec_cl1
      case symbol_kind::S_typespec_cl2: // typespec_cl2
        value.move< std::vector<pdm::ast::Typespec*> > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_vpatternField_cl: // vpatternField_cl
        value.move< std::vector<pdm::ast::VPattern::Field*> > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_mod_prefix: // mod_prefix
        value.move< std::vector<pdm::intern::String> > (YY_MOVE (s.value));
        break;

      default:
        break;
    }

    location = YY_MOVE (s.location);
  }

  // by_kind.
  parser::by_kind::by_kind ()
    : kind_ (symbol_kind::S_YYEMPTY)
  {}

#if 201103L <= YY_CPLUSPLUS
  parser::by_kind::by_kind (by_kind&& that)
    : kind_ (that.kind_)
  {
    that.clear ();
  }
#endif

  parser::by_kind::by_kind (const by_kind& that)
    : kind_ (that.kind_)
  {}

  parser::by_kind::by_kind (token_kind_type t)
    : kind_ (yytranslate_ (t))
  {}

  void
  parser::by_kind::clear ()
  {
    kind_ = symbol_kind::S_YYEMPTY;
  }

  void
  parser::by_kind::move (by_kind& that)
  {
    kind_ = that.kind_;
    that.clear ();
  }

  parser::symbol_kind_type
  parser::by_kind::kind () const YY_NOEXCEPT
  {
    return kind_;
  }

  parser::symbol_kind_type
  parser::by_kind::type_get () const YY_NOEXCEPT
  {
    return this->kind ();
  }


  // by_state.
  parser::by_state::by_state () YY_NOEXCEPT
    : state (empty_state)
  {}

  parser::by_state::by_state (const by_state& that) YY_NOEXCEPT
    : state (that.state)
  {}

  void
  parser::by_state::clear () YY_NOEXCEPT
  {
    state = empty_state;
  }

  void
  parser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  parser::by_state::by_state (state_type s) YY_NOEXCEPT
    : state (s)
  {}

  parser::symbol_kind_type
  parser::by_state::kind () const YY_NOEXCEPT
  {
    if (state == empty_state)
      return symbol_kind::S_YYEMPTY;
    else
      return YY_CAST (symbol_kind_type, yystos_[+state]);
  }

  parser::stack_symbol_type::stack_symbol_type ()
  {}

  parser::stack_symbol_type::stack_symbol_type (YY_RVREF (stack_symbol_type) that)
    : super_type (YY_MOVE (that.state), YY_MOVE (that.location))
  {
    switch (that.kind ())
    {
      case symbol_kind::S_VID: // "<val_id>"
      case symbol_kind::S_TID: // "<TypeId>"
      case symbol_kind::S_HOLE: // "<__42__>"
      case symbol_kind::S_DINT_LIT: // "42"
      case symbol_kind::S_XINT_LIT: // "0x2a"
      case symbol_kind::S_FLOAT_LIT: // "4.2"
      case symbol_kind::S_DQSTRING_LIT: // "\"dq-string-literal\""
      case symbol_kind::S_SQSTRING_LIT: // "'sq-string-literal'"
      case symbol_kind::S_tid: // tid
      case symbol_kind::S_vid: // vid
      case symbol_kind::S_floatl: // floatl
      case symbol_kind::S_stringl: // stringl
        value.YY_MOVE_OR_COPY< TokenInfo > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_mulBinaryOp: // mulBinaryOp
      case symbol_kind::S_addBinaryOp: // addBinaryOp
      case symbol_kind::S_cmpBinaryOp: // cmpBinaryOp
      case symbol_kind::S_eqBinaryOp: // eqBinaryOp
        value.YY_MOVE_OR_COPY< pdm::ast::BinaryOperator > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_enum_field: // enum_field
        value.YY_MOVE_OR_COPY< pdm::ast::EnumStmt::Field* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr: // expr
      case symbol_kind::S_parenExpr: // parenExpr
      case symbol_kind::S_unitExpr: // unitExpr
      case symbol_kind::S_vparenExpr: // vparenExpr
      case symbol_kind::S_vtupleExpr: // vtupleExpr
      case symbol_kind::S_vstructExpr: // vstructExpr
      case symbol_kind::S_primaryExpr: // primaryExpr
      case symbol_kind::S_int_expr: // int_expr
      case symbol_kind::S_ifThenElseExpr: // ifThenElseExpr
      case symbol_kind::S_chainExpr: // chainExpr
      case symbol_kind::S_vlambdaExpr: // vlambdaExpr
      case symbol_kind::S_postfixExpr: // postfixExpr
      case symbol_kind::S_tcall_exp: // tcall_exp
      case symbol_kind::S_vcall_exp: // vcall_exp
      case symbol_kind::S_dot_name_exp: // dot_name_exp
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
      case symbol_kind::S_type_query_exp: // type_query_exp
        value.YY_MOVE_OR_COPY< pdm::ast::Exp* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_lpattern: // lpattern
      case symbol_kind::S_lpattern_naked: // lpattern_naked
        value.YY_MOVE_OR_COPY< pdm::ast::LPattern* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_lpatternField: // lpatternField
        value.YY_MOVE_OR_COPY< pdm::ast::LPattern::Field* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_script: // script
        value.YY_MOVE_OR_COPY< pdm::ast::Script* > (YY_MOVE (that.value));
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
      case symbol_kind::S_extern_stmt: // extern_stmt
        value.YY_MOVE_OR_COPY< pdm::ast::Stmt* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_vstructExprField: // vstructExprField
        value.YY_MOVE_OR_COPY< pdm::ast::StructExp::Field* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_structTypespecField: // structTypespecField
        value.YY_MOVE_OR_COPY< pdm::ast::StructTypespec::Field* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_ttarg: // ttarg
      case symbol_kind::S_vtarg: // vtarg
        value.YY_MOVE_OR_COPY< pdm::ast::TArg* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_tpattern: // tpattern
        value.YY_MOVE_OR_COPY< pdm::ast::TPattern* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_tpatternField: // tpatternField
        value.YY_MOVE_OR_COPY< pdm::ast::TPattern::Field* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_type_query_op: // type_query_op
        value.YY_MOVE_OR_COPY< pdm::ast::TypeQueryKind > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_typespec: // typespec
      case symbol_kind::S_primaryTypespec: // primaryTypespec
      case symbol_kind::S_parenTypespec: // parenTypespec
      case symbol_kind::S_tupleTypespec: // tupleTypespec
      case symbol_kind::S_mod_prefix_tid: // mod_prefix_tid
      case symbol_kind::S_fn_typespec: // fn_typespec
      case symbol_kind::S_postfixTypespec: // postfixTypespec
      case symbol_kind::S_ttcall: // ttcall
      case symbol_kind::S_tdot: // tdot
      case symbol_kind::S_unaryTypespec: // unaryTypespec
      case symbol_kind::S_long_typespec: // long_typespec
      case symbol_kind::S_structTypespec: // structTypespec
        value.YY_MOVE_OR_COPY< pdm::ast::Typespec* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_unaryOp: // unaryOp
        value.YY_MOVE_OR_COPY< pdm::ast::UnaryOperator > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_vpattern: // vpattern
        value.YY_MOVE_OR_COPY< pdm::ast::VPattern* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_vpatternField: // vpatternField
        value.YY_MOVE_OR_COPY< pdm::ast::VPattern::Field* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_enum_field_pl: // enum_field_pl
      case symbol_kind::S_unprefixed_enum_field_pl: // unprefixed_enum_field_pl
        value.YY_MOVE_OR_COPY< std::vector<pdm::ast::EnumStmt::Field*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_cl1: // expr_cl1
      case symbol_kind::S_expr_cl2: // expr_cl2
      case symbol_kind::S_expr_sl: // expr_sl
        value.YY_MOVE_OR_COPY< std::vector<pdm::ast::Exp*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_lpatternField_cl: // lpatternField_cl
        value.YY_MOVE_OR_COPY< std::vector<pdm::ast::LPattern::Field*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_scriptContent: // scriptContent
      case symbol_kind::S_moduleContent: // moduleContent
      case symbol_kind::S_chainPrefix: // chainPrefix
        value.YY_MOVE_OR_COPY< std::vector<pdm::ast::Stmt*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stringls: // stringls
        value.YY_MOVE_OR_COPY< std::vector<pdm::ast::StringExp::Piece> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_vstructExprField_cl: // vstructExprField_cl
        value.YY_MOVE_OR_COPY< std::vector<pdm::ast::StructExp::Field*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_structTypespecField_cl: // structTypespecField_cl
        value.YY_MOVE_OR_COPY< std::vector<pdm::ast::StructTypespec::Field*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_ttarg_cl: // ttarg_cl
      case symbol_kind::S_vtarg_cl: // vtarg_cl
        value.YY_MOVE_OR_COPY< std::vector<pdm::ast::TArg*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_tpattern_seq: // tpattern_seq
        value.YY_MOVE_OR_COPY< std::vector<pdm::ast::TPattern*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_tpatternField_cl: // tpatternField_cl
        value.YY_MOVE_OR_COPY< std::vector<pdm::ast::TPattern::Field*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_typespec_cl1: // typespec_cl1
      case symbol_kind::S_typespec_cl2: // typespec_cl2
        value.YY_MOVE_OR_COPY< std::vector<pdm::ast::Typespec*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_vpatternField_cl: // vpatternField_cl
        value.YY_MOVE_OR_COPY< std::vector<pdm::ast::VPattern::Field*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_mod_prefix: // mod_prefix
        value.YY_MOVE_OR_COPY< std::vector<pdm::intern::String> > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

#if 201103L <= YY_CPLUSPLUS
    // that is emptied.
    that.state = empty_state;
#endif
  }

  parser::stack_symbol_type::stack_symbol_type (state_type s, YY_MOVE_REF (symbol_type) that)
    : super_type (s, YY_MOVE (that.location))
  {
    switch (that.kind ())
    {
      case symbol_kind::S_VID: // "<val_id>"
      case symbol_kind::S_TID: // "<TypeId>"
      case symbol_kind::S_HOLE: // "<__42__>"
      case symbol_kind::S_DINT_LIT: // "42"
      case symbol_kind::S_XINT_LIT: // "0x2a"
      case symbol_kind::S_FLOAT_LIT: // "4.2"
      case symbol_kind::S_DQSTRING_LIT: // "\"dq-string-literal\""
      case symbol_kind::S_SQSTRING_LIT: // "'sq-string-literal'"
      case symbol_kind::S_tid: // tid
      case symbol_kind::S_vid: // vid
      case symbol_kind::S_floatl: // floatl
      case symbol_kind::S_stringl: // stringl
        value.move< TokenInfo > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_mulBinaryOp: // mulBinaryOp
      case symbol_kind::S_addBinaryOp: // addBinaryOp
      case symbol_kind::S_cmpBinaryOp: // cmpBinaryOp
      case symbol_kind::S_eqBinaryOp: // eqBinaryOp
        value.move< pdm::ast::BinaryOperator > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_enum_field: // enum_field
        value.move< pdm::ast::EnumStmt::Field* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr: // expr
      case symbol_kind::S_parenExpr: // parenExpr
      case symbol_kind::S_unitExpr: // unitExpr
      case symbol_kind::S_vparenExpr: // vparenExpr
      case symbol_kind::S_vtupleExpr: // vtupleExpr
      case symbol_kind::S_vstructExpr: // vstructExpr
      case symbol_kind::S_primaryExpr: // primaryExpr
      case symbol_kind::S_int_expr: // int_expr
      case symbol_kind::S_ifThenElseExpr: // ifThenElseExpr
      case symbol_kind::S_chainExpr: // chainExpr
      case symbol_kind::S_vlambdaExpr: // vlambdaExpr
      case symbol_kind::S_postfixExpr: // postfixExpr
      case symbol_kind::S_tcall_exp: // tcall_exp
      case symbol_kind::S_vcall_exp: // vcall_exp
      case symbol_kind::S_dot_name_exp: // dot_name_exp
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
      case symbol_kind::S_type_query_exp: // type_query_exp
        value.move< pdm::ast::Exp* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_lpattern: // lpattern
      case symbol_kind::S_lpattern_naked: // lpattern_naked
        value.move< pdm::ast::LPattern* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_lpatternField: // lpatternField
        value.move< pdm::ast::LPattern::Field* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_script: // script
        value.move< pdm::ast::Script* > (YY_MOVE (that.value));
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
      case symbol_kind::S_extern_stmt: // extern_stmt
        value.move< pdm::ast::Stmt* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_vstructExprField: // vstructExprField
        value.move< pdm::ast::StructExp::Field* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_structTypespecField: // structTypespecField
        value.move< pdm::ast::StructTypespec::Field* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_ttarg: // ttarg
      case symbol_kind::S_vtarg: // vtarg
        value.move< pdm::ast::TArg* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_tpattern: // tpattern
        value.move< pdm::ast::TPattern* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_tpatternField: // tpatternField
        value.move< pdm::ast::TPattern::Field* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_type_query_op: // type_query_op
        value.move< pdm::ast::TypeQueryKind > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_typespec: // typespec
      case symbol_kind::S_primaryTypespec: // primaryTypespec
      case symbol_kind::S_parenTypespec: // parenTypespec
      case symbol_kind::S_tupleTypespec: // tupleTypespec
      case symbol_kind::S_mod_prefix_tid: // mod_prefix_tid
      case symbol_kind::S_fn_typespec: // fn_typespec
      case symbol_kind::S_postfixTypespec: // postfixTypespec
      case symbol_kind::S_ttcall: // ttcall
      case symbol_kind::S_tdot: // tdot
      case symbol_kind::S_unaryTypespec: // unaryTypespec
      case symbol_kind::S_long_typespec: // long_typespec
      case symbol_kind::S_structTypespec: // structTypespec
        value.move< pdm::ast::Typespec* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_unaryOp: // unaryOp
        value.move< pdm::ast::UnaryOperator > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_vpattern: // vpattern
        value.move< pdm::ast::VPattern* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_vpatternField: // vpatternField
        value.move< pdm::ast::VPattern::Field* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_enum_field_pl: // enum_field_pl
      case symbol_kind::S_unprefixed_enum_field_pl: // unprefixed_enum_field_pl
        value.move< std::vector<pdm::ast::EnumStmt::Field*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_cl1: // expr_cl1
      case symbol_kind::S_expr_cl2: // expr_cl2
      case symbol_kind::S_expr_sl: // expr_sl
        value.move< std::vector<pdm::ast::Exp*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_lpatternField_cl: // lpatternField_cl
        value.move< std::vector<pdm::ast::LPattern::Field*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_scriptContent: // scriptContent
      case symbol_kind::S_moduleContent: // moduleContent
      case symbol_kind::S_chainPrefix: // chainPrefix
        value.move< std::vector<pdm::ast::Stmt*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stringls: // stringls
        value.move< std::vector<pdm::ast::StringExp::Piece> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_vstructExprField_cl: // vstructExprField_cl
        value.move< std::vector<pdm::ast::StructExp::Field*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_structTypespecField_cl: // structTypespecField_cl
        value.move< std::vector<pdm::ast::StructTypespec::Field*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_ttarg_cl: // ttarg_cl
      case symbol_kind::S_vtarg_cl: // vtarg_cl
        value.move< std::vector<pdm::ast::TArg*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_tpattern_seq: // tpattern_seq
        value.move< std::vector<pdm::ast::TPattern*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_tpatternField_cl: // tpatternField_cl
        value.move< std::vector<pdm::ast::TPattern::Field*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_typespec_cl1: // typespec_cl1
      case symbol_kind::S_typespec_cl2: // typespec_cl2
        value.move< std::vector<pdm::ast::Typespec*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_vpatternField_cl: // vpatternField_cl
        value.move< std::vector<pdm::ast::VPattern::Field*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_mod_prefix: // mod_prefix
        value.move< std::vector<pdm::intern::String> > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

    // that is emptied.
    that.kind_ = symbol_kind::S_YYEMPTY;
  }

#if YY_CPLUSPLUS < 201103L
  parser::stack_symbol_type&
  parser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
    switch (that.kind ())
    {
      case symbol_kind::S_VID: // "<val_id>"
      case symbol_kind::S_TID: // "<TypeId>"
      case symbol_kind::S_HOLE: // "<__42__>"
      case symbol_kind::S_DINT_LIT: // "42"
      case symbol_kind::S_XINT_LIT: // "0x2a"
      case symbol_kind::S_FLOAT_LIT: // "4.2"
      case symbol_kind::S_DQSTRING_LIT: // "\"dq-string-literal\""
      case symbol_kind::S_SQSTRING_LIT: // "'sq-string-literal'"
      case symbol_kind::S_tid: // tid
      case symbol_kind::S_vid: // vid
      case symbol_kind::S_floatl: // floatl
      case symbol_kind::S_stringl: // stringl
        value.copy< TokenInfo > (that.value);
        break;

      case symbol_kind::S_mulBinaryOp: // mulBinaryOp
      case symbol_kind::S_addBinaryOp: // addBinaryOp
      case symbol_kind::S_cmpBinaryOp: // cmpBinaryOp
      case symbol_kind::S_eqBinaryOp: // eqBinaryOp
        value.copy< pdm::ast::BinaryOperator > (that.value);
        break;

      case symbol_kind::S_enum_field: // enum_field
        value.copy< pdm::ast::EnumStmt::Field* > (that.value);
        break;

      case symbol_kind::S_expr: // expr
      case symbol_kind::S_parenExpr: // parenExpr
      case symbol_kind::S_unitExpr: // unitExpr
      case symbol_kind::S_vparenExpr: // vparenExpr
      case symbol_kind::S_vtupleExpr: // vtupleExpr
      case symbol_kind::S_vstructExpr: // vstructExpr
      case symbol_kind::S_primaryExpr: // primaryExpr
      case symbol_kind::S_int_expr: // int_expr
      case symbol_kind::S_ifThenElseExpr: // ifThenElseExpr
      case symbol_kind::S_chainExpr: // chainExpr
      case symbol_kind::S_vlambdaExpr: // vlambdaExpr
      case symbol_kind::S_postfixExpr: // postfixExpr
      case symbol_kind::S_tcall_exp: // tcall_exp
      case symbol_kind::S_vcall_exp: // vcall_exp
      case symbol_kind::S_dot_name_exp: // dot_name_exp
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
      case symbol_kind::S_type_query_exp: // type_query_exp
        value.copy< pdm::ast::Exp* > (that.value);
        break;

      case symbol_kind::S_lpattern: // lpattern
      case symbol_kind::S_lpattern_naked: // lpattern_naked
        value.copy< pdm::ast::LPattern* > (that.value);
        break;

      case symbol_kind::S_lpatternField: // lpatternField
        value.copy< pdm::ast::LPattern::Field* > (that.value);
        break;

      case symbol_kind::S_script: // script
        value.copy< pdm::ast::Script* > (that.value);
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
      case symbol_kind::S_extern_stmt: // extern_stmt
        value.copy< pdm::ast::Stmt* > (that.value);
        break;

      case symbol_kind::S_vstructExprField: // vstructExprField
        value.copy< pdm::ast::StructExp::Field* > (that.value);
        break;

      case symbol_kind::S_structTypespecField: // structTypespecField
        value.copy< pdm::ast::StructTypespec::Field* > (that.value);
        break;

      case symbol_kind::S_ttarg: // ttarg
      case symbol_kind::S_vtarg: // vtarg
        value.copy< pdm::ast::TArg* > (that.value);
        break;

      case symbol_kind::S_tpattern: // tpattern
        value.copy< pdm::ast::TPattern* > (that.value);
        break;

      case symbol_kind::S_tpatternField: // tpatternField
        value.copy< pdm::ast::TPattern::Field* > (that.value);
        break;

      case symbol_kind::S_type_query_op: // type_query_op
        value.copy< pdm::ast::TypeQueryKind > (that.value);
        break;

      case symbol_kind::S_typespec: // typespec
      case symbol_kind::S_primaryTypespec: // primaryTypespec
      case symbol_kind::S_parenTypespec: // parenTypespec
      case symbol_kind::S_tupleTypespec: // tupleTypespec
      case symbol_kind::S_mod_prefix_tid: // mod_prefix_tid
      case symbol_kind::S_fn_typespec: // fn_typespec
      case symbol_kind::S_postfixTypespec: // postfixTypespec
      case symbol_kind::S_ttcall: // ttcall
      case symbol_kind::S_tdot: // tdot
      case symbol_kind::S_unaryTypespec: // unaryTypespec
      case symbol_kind::S_long_typespec: // long_typespec
      case symbol_kind::S_structTypespec: // structTypespec
        value.copy< pdm::ast::Typespec* > (that.value);
        break;

      case symbol_kind::S_unaryOp: // unaryOp
        value.copy< pdm::ast::UnaryOperator > (that.value);
        break;

      case symbol_kind::S_vpattern: // vpattern
        value.copy< pdm::ast::VPattern* > (that.value);
        break;

      case symbol_kind::S_vpatternField: // vpatternField
        value.copy< pdm::ast::VPattern::Field* > (that.value);
        break;

      case symbol_kind::S_enum_field_pl: // enum_field_pl
      case symbol_kind::S_unprefixed_enum_field_pl: // unprefixed_enum_field_pl
        value.copy< std::vector<pdm::ast::EnumStmt::Field*> > (that.value);
        break;

      case symbol_kind::S_expr_cl1: // expr_cl1
      case symbol_kind::S_expr_cl2: // expr_cl2
      case symbol_kind::S_expr_sl: // expr_sl
        value.copy< std::vector<pdm::ast::Exp*> > (that.value);
        break;

      case symbol_kind::S_lpatternField_cl: // lpatternField_cl
        value.copy< std::vector<pdm::ast::LPattern::Field*> > (that.value);
        break;

      case symbol_kind::S_scriptContent: // scriptContent
      case symbol_kind::S_moduleContent: // moduleContent
      case symbol_kind::S_chainPrefix: // chainPrefix
        value.copy< std::vector<pdm::ast::Stmt*> > (that.value);
        break;

      case symbol_kind::S_stringls: // stringls
        value.copy< std::vector<pdm::ast::StringExp::Piece> > (that.value);
        break;

      case symbol_kind::S_vstructExprField_cl: // vstructExprField_cl
        value.copy< std::vector<pdm::ast::StructExp::Field*> > (that.value);
        break;

      case symbol_kind::S_structTypespecField_cl: // structTypespecField_cl
        value.copy< std::vector<pdm::ast::StructTypespec::Field*> > (that.value);
        break;

      case symbol_kind::S_ttarg_cl: // ttarg_cl
      case symbol_kind::S_vtarg_cl: // vtarg_cl
        value.copy< std::vector<pdm::ast::TArg*> > (that.value);
        break;

      case symbol_kind::S_tpattern_seq: // tpattern_seq
        value.copy< std::vector<pdm::ast::TPattern*> > (that.value);
        break;

      case symbol_kind::S_tpatternField_cl: // tpatternField_cl
        value.copy< std::vector<pdm::ast::TPattern::Field*> > (that.value);
        break;

      case symbol_kind::S_typespec_cl1: // typespec_cl1
      case symbol_kind::S_typespec_cl2: // typespec_cl2
        value.copy< std::vector<pdm::ast::Typespec*> > (that.value);
        break;

      case symbol_kind::S_vpatternField_cl: // vpatternField_cl
        value.copy< std::vector<pdm::ast::VPattern::Field*> > (that.value);
        break;

      case symbol_kind::S_mod_prefix: // mod_prefix
        value.copy< std::vector<pdm::intern::String> > (that.value);
        break;

      default:
        break;
    }

    location = that.location;
    return *this;
  }

  parser::stack_symbol_type&
  parser::stack_symbol_type::operator= (stack_symbol_type& that)
  {
    state = that.state;
    switch (that.kind ())
    {
      case symbol_kind::S_VID: // "<val_id>"
      case symbol_kind::S_TID: // "<TypeId>"
      case symbol_kind::S_HOLE: // "<__42__>"
      case symbol_kind::S_DINT_LIT: // "42"
      case symbol_kind::S_XINT_LIT: // "0x2a"
      case symbol_kind::S_FLOAT_LIT: // "4.2"
      case symbol_kind::S_DQSTRING_LIT: // "\"dq-string-literal\""
      case symbol_kind::S_SQSTRING_LIT: // "'sq-string-literal'"
      case symbol_kind::S_tid: // tid
      case symbol_kind::S_vid: // vid
      case symbol_kind::S_floatl: // floatl
      case symbol_kind::S_stringl: // stringl
        value.move< TokenInfo > (that.value);
        break;

      case symbol_kind::S_mulBinaryOp: // mulBinaryOp
      case symbol_kind::S_addBinaryOp: // addBinaryOp
      case symbol_kind::S_cmpBinaryOp: // cmpBinaryOp
      case symbol_kind::S_eqBinaryOp: // eqBinaryOp
        value.move< pdm::ast::BinaryOperator > (that.value);
        break;

      case symbol_kind::S_enum_field: // enum_field
        value.move< pdm::ast::EnumStmt::Field* > (that.value);
        break;

      case symbol_kind::S_expr: // expr
      case symbol_kind::S_parenExpr: // parenExpr
      case symbol_kind::S_unitExpr: // unitExpr
      case symbol_kind::S_vparenExpr: // vparenExpr
      case symbol_kind::S_vtupleExpr: // vtupleExpr
      case symbol_kind::S_vstructExpr: // vstructExpr
      case symbol_kind::S_primaryExpr: // primaryExpr
      case symbol_kind::S_int_expr: // int_expr
      case symbol_kind::S_ifThenElseExpr: // ifThenElseExpr
      case symbol_kind::S_chainExpr: // chainExpr
      case symbol_kind::S_vlambdaExpr: // vlambdaExpr
      case symbol_kind::S_postfixExpr: // postfixExpr
      case symbol_kind::S_tcall_exp: // tcall_exp
      case symbol_kind::S_vcall_exp: // vcall_exp
      case symbol_kind::S_dot_name_exp: // dot_name_exp
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
      case symbol_kind::S_type_query_exp: // type_query_exp
        value.move< pdm::ast::Exp* > (that.value);
        break;

      case symbol_kind::S_lpattern: // lpattern
      case symbol_kind::S_lpattern_naked: // lpattern_naked
        value.move< pdm::ast::LPattern* > (that.value);
        break;

      case symbol_kind::S_lpatternField: // lpatternField
        value.move< pdm::ast::LPattern::Field* > (that.value);
        break;

      case symbol_kind::S_script: // script
        value.move< pdm::ast::Script* > (that.value);
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
      case symbol_kind::S_extern_stmt: // extern_stmt
        value.move< pdm::ast::Stmt* > (that.value);
        break;

      case symbol_kind::S_vstructExprField: // vstructExprField
        value.move< pdm::ast::StructExp::Field* > (that.value);
        break;

      case symbol_kind::S_structTypespecField: // structTypespecField
        value.move< pdm::ast::StructTypespec::Field* > (that.value);
        break;

      case symbol_kind::S_ttarg: // ttarg
      case symbol_kind::S_vtarg: // vtarg
        value.move< pdm::ast::TArg* > (that.value);
        break;

      case symbol_kind::S_tpattern: // tpattern
        value.move< pdm::ast::TPattern* > (that.value);
        break;

      case symbol_kind::S_tpatternField: // tpatternField
        value.move< pdm::ast::TPattern::Field* > (that.value);
        break;

      case symbol_kind::S_type_query_op: // type_query_op
        value.move< pdm::ast::TypeQueryKind > (that.value);
        break;

      case symbol_kind::S_typespec: // typespec
      case symbol_kind::S_primaryTypespec: // primaryTypespec
      case symbol_kind::S_parenTypespec: // parenTypespec
      case symbol_kind::S_tupleTypespec: // tupleTypespec
      case symbol_kind::S_mod_prefix_tid: // mod_prefix_tid
      case symbol_kind::S_fn_typespec: // fn_typespec
      case symbol_kind::S_postfixTypespec: // postfixTypespec
      case symbol_kind::S_ttcall: // ttcall
      case symbol_kind::S_tdot: // tdot
      case symbol_kind::S_unaryTypespec: // unaryTypespec
      case symbol_kind::S_long_typespec: // long_typespec
      case symbol_kind::S_structTypespec: // structTypespec
        value.move< pdm::ast::Typespec* > (that.value);
        break;

      case symbol_kind::S_unaryOp: // unaryOp
        value.move< pdm::ast::UnaryOperator > (that.value);
        break;

      case symbol_kind::S_vpattern: // vpattern
        value.move< pdm::ast::VPattern* > (that.value);
        break;

      case symbol_kind::S_vpatternField: // vpatternField
        value.move< pdm::ast::VPattern::Field* > (that.value);
        break;

      case symbol_kind::S_enum_field_pl: // enum_field_pl
      case symbol_kind::S_unprefixed_enum_field_pl: // unprefixed_enum_field_pl
        value.move< std::vector<pdm::ast::EnumStmt::Field*> > (that.value);
        break;

      case symbol_kind::S_expr_cl1: // expr_cl1
      case symbol_kind::S_expr_cl2: // expr_cl2
      case symbol_kind::S_expr_sl: // expr_sl
        value.move< std::vector<pdm::ast::Exp*> > (that.value);
        break;

      case symbol_kind::S_lpatternField_cl: // lpatternField_cl
        value.move< std::vector<pdm::ast::LPattern::Field*> > (that.value);
        break;

      case symbol_kind::S_scriptContent: // scriptContent
      case symbol_kind::S_moduleContent: // moduleContent
      case symbol_kind::S_chainPrefix: // chainPrefix
        value.move< std::vector<pdm::ast::Stmt*> > (that.value);
        break;

      case symbol_kind::S_stringls: // stringls
        value.move< std::vector<pdm::ast::StringExp::Piece> > (that.value);
        break;

      case symbol_kind::S_vstructExprField_cl: // vstructExprField_cl
        value.move< std::vector<pdm::ast::StructExp::Field*> > (that.value);
        break;

      case symbol_kind::S_structTypespecField_cl: // structTypespecField_cl
        value.move< std::vector<pdm::ast::StructTypespec::Field*> > (that.value);
        break;

      case symbol_kind::S_ttarg_cl: // ttarg_cl
      case symbol_kind::S_vtarg_cl: // vtarg_cl
        value.move< std::vector<pdm::ast::TArg*> > (that.value);
        break;

      case symbol_kind::S_tpattern_seq: // tpattern_seq
        value.move< std::vector<pdm::ast::TPattern*> > (that.value);
        break;

      case symbol_kind::S_tpatternField_cl: // tpatternField_cl
        value.move< std::vector<pdm::ast::TPattern::Field*> > (that.value);
        break;

      case symbol_kind::S_typespec_cl1: // typespec_cl1
      case symbol_kind::S_typespec_cl2: // typespec_cl2
        value.move< std::vector<pdm::ast::Typespec*> > (that.value);
        break;

      case symbol_kind::S_vpatternField_cl: // vpatternField_cl
        value.move< std::vector<pdm::ast::VPattern::Field*> > (that.value);
        break;

      case symbol_kind::S_mod_prefix: // mod_prefix
        value.move< std::vector<pdm::intern::String> > (that.value);
        break;

      default:
        break;
    }

    location = that.location;
    // that is emptied.
    that.state = empty_state;
    return *this;
  }
#endif

  template <typename Base>
  void
  parser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);
  }

#if YYDEBUG
  template <typename Base>
  void
  parser::yy_print_ (std::ostream& yyo, const basic_symbol<Base>& yysym) const
  {
    std::ostream& yyoutput = yyo;
    YYUSE (yyoutput);
    if (yysym.empty ())
      yyo << "empty symbol";
    else
      {
        symbol_kind_type yykind = yysym.kind ();
        yyo << (yykind < YYNTOKENS ? "token" : "nterm")
            << ' ' << yysym.name () << " ("
            << yysym.location << ": ";
        YYUSE (yykind);
        yyo << ')';
      }
  }
#endif

  void
  parser::yypush_ (const char* m, YY_MOVE_REF (stack_symbol_type) sym)
  {
    if (m)
      YY_SYMBOL_PRINT (m, sym);
    yystack_.push (YY_MOVE (sym));
  }

  void
  parser::yypush_ (const char* m, state_type s, YY_MOVE_REF (symbol_type) sym)
  {
#if 201103L <= YY_CPLUSPLUS
    yypush_ (m, stack_symbol_type (s, std::move (sym)));
#else
    stack_symbol_type ss (s, sym);
    yypush_ (m, ss);
#endif
  }

  void
  parser::yypop_ (int n)
  {
    yystack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
  parser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  parser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  parser::debug_level_type
  parser::debug_level () const
  {
    return yydebug_;
  }

  void
  parser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // YYDEBUG

  parser::state_type
  parser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - YYNTOKENS] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - YYNTOKENS];
  }

  bool
  parser::yy_pact_value_is_default_ (int yyvalue)
  {
    return yyvalue == yypact_ninf_;
  }

  bool
  parser::yy_table_value_is_error_ (int yyvalue)
  {
    return yyvalue == yytable_ninf_;
  }

  int
  parser::operator() ()
  {
    return parse ();
  }

  int
  parser::parse ()
  {
    int yyn;
    /// Length of the RHS of the rule being reduced.
    int yylen = 0;

    // Error handling.
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// The lookahead symbol.
    symbol_type yyla;

    /// The locations where the error started and ended.
    stack_symbol_type yyerror_range[3];

    /// The return value of parse ().
    int yyresult;

#if YY_EXCEPTIONS
    try
#endif // YY_EXCEPTIONS
      {
    YYCDEBUG << "Starting parse\n";


    /* Initialize the stack.  The initial state will be set in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystack_.clear ();
    yypush_ (YY_NULLPTR, 0, YY_MOVE (yyla));

  /*-----------------------------------------------.
  | yynewstate -- push a new symbol on the stack.  |
  `-----------------------------------------------*/
  yynewstate:
    YYCDEBUG << "Entering state " << int (yystack_[0].state) << '\n';
    YY_STACK_PRINT ();

    // Accept?
    if (yystack_[0].state == yyfinal_)
      YYACCEPT;

    goto yybackup;


  /*-----------.
  | yybackup.  |
  `-----------*/
  yybackup:
    // Try to take a decision without lookahead.
    yyn = yypact_[+yystack_[0].state];
    if (yy_pact_value_is_default_ (yyn))
      goto yydefault;

    // Read a lookahead token.
    if (yyla.empty ())
      {
        YYCDEBUG << "Reading a token\n";
#if YY_EXCEPTIONS
        try
#endif // YY_EXCEPTIONS
          {
            yyla.kind_ = yytranslate_ (yylex (&yyla.value, &yyla.location, source, lexer));
          }
#if YY_EXCEPTIONS
        catch (const syntax_error& yyexc)
          {
            YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
            error (yyexc);
            goto yyerrlab1;
          }
#endif // YY_EXCEPTIONS
      }
    YY_SYMBOL_PRINT ("Next token is", yyla);

    if (yyla.kind () == symbol_kind::S_YYerror)
    {
      // The scanner already issued an error message, process directly
      // to error recovery.  But do not keep the error token as
      // lookahead, it is too special and may lead us to an endless
      // loop in error recovery. */
      yyla.kind_ = symbol_kind::S_YYUNDEF;
      goto yyerrlab1;
    }

    /* If the proper action on seeing token YYLA.TYPE is to reduce or
       to detect an error, take that action.  */
    yyn += yyla.kind ();
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yyla.kind ())
      {
        goto yydefault;
      }

    // Reduce or error.
    yyn = yytable_[yyn];
    if (yyn <= 0)
      {
        if (yy_table_value_is_error_ (yyn))
          goto yyerrlab;
        yyn = -yyn;
        goto yyreduce;
      }

    // Count tokens shifted since error; after three, turn off error status.
    if (yyerrstatus_)
      --yyerrstatus_;

    // Shift the lookahead token.
    yypush_ ("Shifting", state_type (yyn), YY_MOVE (yyla));
    goto yynewstate;


  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[+yystack_[0].state];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;


  /*-----------------------------.
  | yyreduce -- do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    {
      stack_symbol_type yylhs;
      yylhs.state = yy_lr_goto_state_ (yystack_[yylen].state, yyr1_[yyn]);
      /* Variants are always initialized to an empty instance of the
         correct type. The default '$$ = $1' action is NOT applied
         when using variants.  */
      switch (yyr1_[yyn])
    {
      case symbol_kind::S_VID: // "<val_id>"
      case symbol_kind::S_TID: // "<TypeId>"
      case symbol_kind::S_HOLE: // "<__42__>"
      case symbol_kind::S_DINT_LIT: // "42"
      case symbol_kind::S_XINT_LIT: // "0x2a"
      case symbol_kind::S_FLOAT_LIT: // "4.2"
      case symbol_kind::S_DQSTRING_LIT: // "\"dq-string-literal\""
      case symbol_kind::S_SQSTRING_LIT: // "'sq-string-literal'"
      case symbol_kind::S_tid: // tid
      case symbol_kind::S_vid: // vid
      case symbol_kind::S_floatl: // floatl
      case symbol_kind::S_stringl: // stringl
        yylhs.value.emplace< TokenInfo > ();
        break;

      case symbol_kind::S_mulBinaryOp: // mulBinaryOp
      case symbol_kind::S_addBinaryOp: // addBinaryOp
      case symbol_kind::S_cmpBinaryOp: // cmpBinaryOp
      case symbol_kind::S_eqBinaryOp: // eqBinaryOp
        yylhs.value.emplace< pdm::ast::BinaryOperator > ();
        break;

      case symbol_kind::S_enum_field: // enum_field
        yylhs.value.emplace< pdm::ast::EnumStmt::Field* > ();
        break;

      case symbol_kind::S_expr: // expr
      case symbol_kind::S_parenExpr: // parenExpr
      case symbol_kind::S_unitExpr: // unitExpr
      case symbol_kind::S_vparenExpr: // vparenExpr
      case symbol_kind::S_vtupleExpr: // vtupleExpr
      case symbol_kind::S_vstructExpr: // vstructExpr
      case symbol_kind::S_primaryExpr: // primaryExpr
      case symbol_kind::S_int_expr: // int_expr
      case symbol_kind::S_ifThenElseExpr: // ifThenElseExpr
      case symbol_kind::S_chainExpr: // chainExpr
      case symbol_kind::S_vlambdaExpr: // vlambdaExpr
      case symbol_kind::S_postfixExpr: // postfixExpr
      case symbol_kind::S_tcall_exp: // tcall_exp
      case symbol_kind::S_vcall_exp: // vcall_exp
      case symbol_kind::S_dot_name_exp: // dot_name_exp
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
      case symbol_kind::S_type_query_exp: // type_query_exp
        yylhs.value.emplace< pdm::ast::Exp* > ();
        break;

      case symbol_kind::S_lpattern: // lpattern
      case symbol_kind::S_lpattern_naked: // lpattern_naked
        yylhs.value.emplace< pdm::ast::LPattern* > ();
        break;

      case symbol_kind::S_lpatternField: // lpatternField
        yylhs.value.emplace< pdm::ast::LPattern::Field* > ();
        break;

      case symbol_kind::S_script: // script
        yylhs.value.emplace< pdm::ast::Script* > ();
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
      case symbol_kind::S_extern_stmt: // extern_stmt
        yylhs.value.emplace< pdm::ast::Stmt* > ();
        break;

      case symbol_kind::S_vstructExprField: // vstructExprField
        yylhs.value.emplace< pdm::ast::StructExp::Field* > ();
        break;

      case symbol_kind::S_structTypespecField: // structTypespecField
        yylhs.value.emplace< pdm::ast::StructTypespec::Field* > ();
        break;

      case symbol_kind::S_ttarg: // ttarg
      case symbol_kind::S_vtarg: // vtarg
        yylhs.value.emplace< pdm::ast::TArg* > ();
        break;

      case symbol_kind::S_tpattern: // tpattern
        yylhs.value.emplace< pdm::ast::TPattern* > ();
        break;

      case symbol_kind::S_tpatternField: // tpatternField
        yylhs.value.emplace< pdm::ast::TPattern::Field* > ();
        break;

      case symbol_kind::S_type_query_op: // type_query_op
        yylhs.value.emplace< pdm::ast::TypeQueryKind > ();
        break;

      case symbol_kind::S_typespec: // typespec
      case symbol_kind::S_primaryTypespec: // primaryTypespec
      case symbol_kind::S_parenTypespec: // parenTypespec
      case symbol_kind::S_tupleTypespec: // tupleTypespec
      case symbol_kind::S_mod_prefix_tid: // mod_prefix_tid
      case symbol_kind::S_fn_typespec: // fn_typespec
      case symbol_kind::S_postfixTypespec: // postfixTypespec
      case symbol_kind::S_ttcall: // ttcall
      case symbol_kind::S_tdot: // tdot
      case symbol_kind::S_unaryTypespec: // unaryTypespec
      case symbol_kind::S_long_typespec: // long_typespec
      case symbol_kind::S_structTypespec: // structTypespec
        yylhs.value.emplace< pdm::ast::Typespec* > ();
        break;

      case symbol_kind::S_unaryOp: // unaryOp
        yylhs.value.emplace< pdm::ast::UnaryOperator > ();
        break;

      case symbol_kind::S_vpattern: // vpattern
        yylhs.value.emplace< pdm::ast::VPattern* > ();
        break;

      case symbol_kind::S_vpatternField: // vpatternField
        yylhs.value.emplace< pdm::ast::VPattern::Field* > ();
        break;

      case symbol_kind::S_enum_field_pl: // enum_field_pl
      case symbol_kind::S_unprefixed_enum_field_pl: // unprefixed_enum_field_pl
        yylhs.value.emplace< std::vector<pdm::ast::EnumStmt::Field*> > ();
        break;

      case symbol_kind::S_expr_cl1: // expr_cl1
      case symbol_kind::S_expr_cl2: // expr_cl2
      case symbol_kind::S_expr_sl: // expr_sl
        yylhs.value.emplace< std::vector<pdm::ast::Exp*> > ();
        break;

      case symbol_kind::S_lpatternField_cl: // lpatternField_cl
        yylhs.value.emplace< std::vector<pdm::ast::LPattern::Field*> > ();
        break;

      case symbol_kind::S_scriptContent: // scriptContent
      case symbol_kind::S_moduleContent: // moduleContent
      case symbol_kind::S_chainPrefix: // chainPrefix
        yylhs.value.emplace< std::vector<pdm::ast::Stmt*> > ();
        break;

      case symbol_kind::S_stringls: // stringls
        yylhs.value.emplace< std::vector<pdm::ast::StringExp::Piece> > ();
        break;

      case symbol_kind::S_vstructExprField_cl: // vstructExprField_cl
        yylhs.value.emplace< std::vector<pdm::ast::StructExp::Field*> > ();
        break;

      case symbol_kind::S_structTypespecField_cl: // structTypespecField_cl
        yylhs.value.emplace< std::vector<pdm::ast::StructTypespec::Field*> > ();
        break;

      case symbol_kind::S_ttarg_cl: // ttarg_cl
      case symbol_kind::S_vtarg_cl: // vtarg_cl
        yylhs.value.emplace< std::vector<pdm::ast::TArg*> > ();
        break;

      case symbol_kind::S_tpattern_seq: // tpattern_seq
        yylhs.value.emplace< std::vector<pdm::ast::TPattern*> > ();
        break;

      case symbol_kind::S_tpatternField_cl: // tpatternField_cl
        yylhs.value.emplace< std::vector<pdm::ast::TPattern::Field*> > ();
        break;

      case symbol_kind::S_typespec_cl1: // typespec_cl1
      case symbol_kind::S_typespec_cl2: // typespec_cl2
        yylhs.value.emplace< std::vector<pdm::ast::Typespec*> > ();
        break;

      case symbol_kind::S_vpatternField_cl: // vpatternField_cl
        yylhs.value.emplace< std::vector<pdm::ast::VPattern::Field*> > ();
        break;

      case symbol_kind::S_mod_prefix: // mod_prefix
        yylhs.value.emplace< std::vector<pdm::intern::String> > ();
        break;

      default:
        break;
    }


      // Default location.
      {
        stack_type::slice range (yystack_, yylen);
        YYLLOC_DEFAULT (yylhs.location, range, yylen);
        yyerror_range[1].location = yylhs.location;
      }

      // Perform the reduction.
      YY_REDUCE_PRINT (yyn);
#if YY_EXCEPTIONS
      try
#endif // YY_EXCEPTIONS
        {
          switch (yyn)
            {
  case 2: // script: scriptContent
#line 293 "parser.yy"
                    { yylhs.value.as < pdm::ast::Script* > () = mgr->new_script(source, yylhs.location, std::move(yystack_[0].value.as < std::vector<pdm::ast::Stmt*> > ())); *returnp = yylhs.value.as < pdm::ast::Script* > (); }
#line 2015 "parser.tab.cc"
    break;

  case 3: // scriptContent: scriptContentStmt ";"
#line 296 "parser.yy"
                                                    { yylhs.value.as < std::vector<pdm::ast::Stmt*> > ().push_back(yystack_[1].value.as < pdm::ast::Stmt* > ()); }
#line 2021 "parser.tab.cc"
    break;

  case 4: // scriptContent: scriptContent scriptContentStmt ";"
#line 297 "parser.yy"
                                                    { yylhs.value.as < std::vector<pdm::ast::Stmt*> > () = std::move(yystack_[2].value.as < std::vector<pdm::ast::Stmt*> > ()); yylhs.value.as < std::vector<pdm::ast::Stmt*> > ().push_back(yystack_[1].value.as < pdm::ast::Stmt* > ()); }
#line 2027 "parser.tab.cc"
    break;

  case 5: // scriptContentStmt: mod_stmt
#line 300 "parser.yy"
      { yylhs.value.as < pdm::ast::Stmt* > () = yystack_[0].value.as < pdm::ast::Stmt* > (); }
#line 2033 "parser.tab.cc"
    break;

  case 6: // mod_stmt: "mod" "<val_id>" "{" moduleContent "}"
#line 308 "parser.yy"
                                                { yylhs.value.as < pdm::ast::Stmt* > () = mgr->new_mod_stmt(yylhs.location, yystack_[3].value.as < TokenInfo > ().ID_intstr, std::move(yystack_[1].value.as < std::vector<pdm::ast::Stmt*> > ())); }
#line 2039 "parser.tab.cc"
    break;

  case 7: // moduleContent: moduleContentStmt ";"
#line 311 "parser.yy"
                                                    { yylhs.value.as < std::vector<pdm::ast::Stmt*> > ().push_back(yystack_[1].value.as < pdm::ast::Stmt* > ()); }
#line 2045 "parser.tab.cc"
    break;

  case 8: // moduleContent: moduleContent moduleContentStmt ";"
#line 312 "parser.yy"
                                                    { yylhs.value.as < std::vector<pdm::ast::Stmt*> > () = std::move(yystack_[2].value.as < std::vector<pdm::ast::Stmt*> > ()); yylhs.value.as < std::vector<pdm::ast::Stmt*> > ().push_back(yystack_[1].value.as < pdm::ast::Stmt* > ()); }
#line 2051 "parser.tab.cc"
    break;

  case 9: // chainPrefixStmt: constStmt
#line 320 "parser.yy"
      { yylhs.value.as < pdm::ast::Stmt* > () = yystack_[0].value.as < pdm::ast::Stmt* > (); }
#line 2057 "parser.tab.cc"
    break;

  case 10: // chainPrefixStmt: letStmt
#line 321 "parser.yy"
      { yylhs.value.as < pdm::ast::Stmt* > () = yystack_[0].value.as < pdm::ast::Stmt* > (); }
#line 2063 "parser.tab.cc"
    break;

  case 11: // chainPrefixStmt: varStmt
#line 322 "parser.yy"
      { yylhs.value.as < pdm::ast::Stmt* > () = yystack_[0].value.as < pdm::ast::Stmt* > (); }
#line 2069 "parser.tab.cc"
    break;

  case 12: // chainPrefixStmt: setStmt
#line 323 "parser.yy"
      { yylhs.value.as < pdm::ast::Stmt* > () = yystack_[0].value.as < pdm::ast::Stmt* > (); }
#line 2075 "parser.tab.cc"
    break;

  case 13: // chainPrefixStmt: discardStmt
#line 324 "parser.yy"
      { yylhs.value.as < pdm::ast::Stmt* > () = yystack_[0].value.as < pdm::ast::Stmt* > (); }
#line 2081 "parser.tab.cc"
    break;

  case 14: // constStmt: "const" lpattern_naked "=" expr
#line 327 "parser.yy"
                                        { yylhs.value.as < pdm::ast::Stmt* > () = mgr->new_const_stmt(yylhs.location, yystack_[2].value.as < pdm::ast::LPattern* > (), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2087 "parser.tab.cc"
    break;

  case 15: // letStmt: "let" lpattern_naked "=" expr
#line 330 "parser.yy"
                                        { yylhs.value.as < pdm::ast::Stmt* > () = mgr->new_let_stmt(yylhs.location, yystack_[2].value.as < pdm::ast::LPattern* > (), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2093 "parser.tab.cc"
    break;

  case 16: // varStmt: "var" lpattern_naked "=" expr
#line 333 "parser.yy"
                                        { yylhs.value.as < pdm::ast::Stmt* > () = mgr->new_var_stmt(yylhs.location, yystack_[2].value.as < pdm::ast::LPattern* > (), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2099 "parser.tab.cc"
    break;

  case 17: // setStmt: "set" expr "=" expr
#line 336 "parser.yy"
                              { yylhs.value.as < pdm::ast::Stmt* > () = mgr->new_set_stmt(yylhs.location, yystack_[2].value.as < pdm::ast::Exp* > (), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2105 "parser.tab.cc"
    break;

  case 18: // discardStmt: expr
#line 339 "parser.yy"
              { yylhs.value.as < pdm::ast::Stmt* > () = mgr->new_discard_stmt(yylhs.location, yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2111 "parser.tab.cc"
    break;

  case 19: // moduleContentStmt: fn_stmt
#line 343 "parser.yy"
      { yylhs.value.as < pdm::ast::Stmt* > () = yystack_[0].value.as < pdm::ast::Stmt* > (); }
#line 2117 "parser.tab.cc"
    break;

  case 20: // moduleContentStmt: type_stmt
#line 344 "parser.yy"
      { yylhs.value.as < pdm::ast::Stmt* > () = yystack_[0].value.as < pdm::ast::Stmt* > (); }
#line 2123 "parser.tab.cc"
    break;

  case 21: // moduleContentStmt: enum_stmt
#line 345 "parser.yy"
      { yylhs.value.as < pdm::ast::Stmt* > () = yystack_[0].value.as < pdm::ast::Stmt* > (); }
#line 2129 "parser.tab.cc"
    break;

  case 22: // moduleContentStmt: typeclass_stmt
#line 346 "parser.yy"
      { yylhs.value.as < pdm::ast::Stmt* > () = yystack_[0].value.as < pdm::ast::Stmt* > (); }
#line 2135 "parser.tab.cc"
    break;

  case 23: // moduleContentStmt: importStmt
#line 347 "parser.yy"
      { yylhs.value.as < pdm::ast::Stmt* > () = yystack_[0].value.as < pdm::ast::Stmt* > (); }
#line 2141 "parser.tab.cc"
    break;

  case 24: // moduleContentStmt: mod_stmt
#line 348 "parser.yy"
      { yylhs.value.as < pdm::ast::Stmt* > () = yystack_[0].value.as < pdm::ast::Stmt* > (); }
#line 2147 "parser.tab.cc"
    break;

  case 25: // moduleContentStmt: using_stmt
#line 349 "parser.yy"
      { yylhs.value.as < pdm::ast::Stmt* > () = yystack_[0].value.as < pdm::ast::Stmt* > (); }
#line 2153 "parser.tab.cc"
    break;

  case 26: // moduleContentStmt: extern_stmt
#line 350 "parser.yy"
      { yylhs.value.as < pdm::ast::Stmt* > () = yystack_[0].value.as < pdm::ast::Stmt* > (); }
#line 2159 "parser.tab.cc"
    break;

  case 27: // fn_stmt: "fn" vid vpattern "->" typespec "=" parenExpr
#line 353 "parser.yy"
                                                                      { yylhs.value.as < pdm::ast::Stmt* > () = mgr->new_fn_stmt(yylhs.location, yystack_[5].value.as < TokenInfo > ().ID_intstr, std::move(std::vector<ast::TPattern*>{}), yystack_[4].value.as < pdm::ast::VPattern* > (), yystack_[2].value.as < pdm::ast::Typespec* > (), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2165 "parser.tab.cc"
    break;

  case 28: // fn_stmt: "fn" vid tpattern_seq vpattern "->" typespec "=" parenExpr
#line 354 "parser.yy"
                                                                      { yylhs.value.as < pdm::ast::Stmt* > () = mgr->new_fn_stmt(yylhs.location, yystack_[6].value.as < TokenInfo > ().ID_intstr, std::move(yystack_[5].value.as < std::vector<pdm::ast::TPattern*> > ()), yystack_[4].value.as < pdm::ast::VPattern* > (), yystack_[2].value.as < pdm::ast::Typespec* > (), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2171 "parser.tab.cc"
    break;

  case 29: // fn_stmt: "fn" vid vpattern "=" parenExpr
#line 355 "parser.yy"
                                                                      { yylhs.value.as < pdm::ast::Stmt* > () = mgr->new_fn_stmt(yylhs.location, yystack_[3].value.as < TokenInfo > ().ID_intstr, std::move(std::vector<ast::TPattern*>{}), yystack_[2].value.as < pdm::ast::VPattern* > (), nullptr, yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2177 "parser.tab.cc"
    break;

  case 30: // fn_stmt: "fn" vid tpattern_seq vpattern "=" parenExpr
#line 356 "parser.yy"
                                                                      { yylhs.value.as < pdm::ast::Stmt* > () = mgr->new_fn_stmt(yylhs.location, yystack_[4].value.as < TokenInfo > ().ID_intstr, std::move(yystack_[3].value.as < std::vector<pdm::ast::TPattern*> > ()), yystack_[2].value.as < pdm::ast::VPattern* > (), nullptr, yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2183 "parser.tab.cc"
    break;

  case 31: // type_stmt: "type" tid "=" long_typespec
#line 359 "parser.yy"
                                                    { yylhs.value.as < pdm::ast::Stmt* > () = mgr->new_type_stmt(yylhs.location, yystack_[2].value.as < TokenInfo > ().ID_intstr, std::move(std::vector<ast::TPattern*>{}), yystack_[0].value.as < pdm::ast::Typespec* > ()); }
#line 2189 "parser.tab.cc"
    break;

  case 32: // type_stmt: "type" tid tpattern_seq "=" long_typespec
#line 360 "parser.yy"
                                                    { yylhs.value.as < pdm::ast::Stmt* > () = mgr->new_type_stmt(yylhs.location, yystack_[3].value.as < TokenInfo > ().ID_intstr, std::move(yystack_[2].value.as < std::vector<pdm::ast::TPattern*> > ()), yystack_[0].value.as < pdm::ast::Typespec* > ()); }
#line 2195 "parser.tab.cc"
    break;

  case 33: // enum_stmt: "enum" tid enum_field_pl
#line 363 "parser.yy"
                                    { yylhs.value.as < pdm::ast::Stmt* > () = mgr->new_enum_stmt(yylhs.location, yystack_[1].value.as < TokenInfo > ().ID_intstr, std::move(yystack_[0].value.as < std::vector<pdm::ast::EnumStmt::Field*> > ())); }
#line 2201 "parser.tab.cc"
    break;

  case 34: // enum_field_pl: "|" unprefixed_enum_field_pl
#line 366 "parser.yy"
                                    { yylhs.value.as < std::vector<pdm::ast::EnumStmt::Field*> > () = std::move(yystack_[0].value.as < std::vector<pdm::ast::EnumStmt::Field*> > ()); }
#line 2207 "parser.tab.cc"
    break;

  case 35: // enum_field_pl: unprefixed_enum_field_pl
#line 367 "parser.yy"
                                    { yylhs.value.as < std::vector<pdm::ast::EnumStmt::Field*> > () = std::move(yystack_[0].value.as < std::vector<pdm::ast::EnumStmt::Field*> > ()); }
#line 2213 "parser.tab.cc"
    break;

  case 36: // unprefixed_enum_field_pl: enum_field
#line 370 "parser.yy"
                                                { yylhs.value.as < std::vector<pdm::ast::EnumStmt::Field*> > ().push_back(yystack_[0].value.as < pdm::ast::EnumStmt::Field* > ()); }
#line 2219 "parser.tab.cc"
    break;

  case 37: // unprefixed_enum_field_pl: unprefixed_enum_field_pl "|" enum_field
#line 371 "parser.yy"
                                                { yylhs.value.as < std::vector<pdm::ast::EnumStmt::Field*> > () = std::move(yystack_[2].value.as < std::vector<pdm::ast::EnumStmt::Field*> > ()); yylhs.value.as < std::vector<pdm::ast::EnumStmt::Field*> > ().push_back(yystack_[0].value.as < pdm::ast::EnumStmt::Field* > ()); }
#line 2225 "parser.tab.cc"
    break;

  case 38: // enum_field: tid
#line 374 "parser.yy"
                                     { yylhs.value.as < pdm::ast::EnumStmt::Field* > () = mgr->new_enum_stmt_field(yystack_[0].value.as < TokenInfo > ().ID_intstr, std::move(std::vector<ast::Typespec*>{}), false); }
#line 2231 "parser.tab.cc"
    break;

  case 39: // enum_field: tid "(" ")"
#line 375 "parser.yy"
                                     { yylhs.value.as < pdm::ast::EnumStmt::Field* > () = mgr->new_enum_stmt_field(yystack_[2].value.as < TokenInfo > ().ID_intstr, std::move(std::vector<ast::Typespec*>{}), true); }
#line 2237 "parser.tab.cc"
    break;

  case 40: // enum_field: tid "(" typespec_cl1 ")"
#line 376 "parser.yy"
                                     { yylhs.value.as < pdm::ast::EnumStmt::Field* > () = mgr->new_enum_stmt_field(yystack_[3].value.as < TokenInfo > ().ID_intstr, std::move(yystack_[1].value.as < std::vector<pdm::ast::Typespec*> > ()), true); }
#line 2243 "parser.tab.cc"
    break;

  case 41: // typeclass_stmt: "typeclass" tid "<" tid typespec ">" "=" "{" expr_sl "}"
#line 379 "parser.yy"
                                                                                        { 
        yylhs.value.as < pdm::ast::Stmt* > () = mgr->new_typeclass_stmt(yylhs.location, yystack_[8].value.as < TokenInfo > ().ID_intstr, yystack_[6].value.as < TokenInfo > ().ID_intstr, yystack_[5].value.as < pdm::ast::Typespec* > (), std::move(std::vector<ast::TPattern*>{}), std::move(yystack_[1].value.as < std::vector<pdm::ast::Exp*> > ())); 
      }
#line 2251 "parser.tab.cc"
    break;

  case 42: // typeclass_stmt: "typeclass" tid "<" tid typespec ">" tpattern_seq "=" "{" expr_sl "}"
#line 382 "parser.yy"
                                                                                        { 
        yylhs.value.as < pdm::ast::Stmt* > () = mgr->new_typeclass_stmt(yylhs.location, yystack_[9].value.as < TokenInfo > ().ID_intstr, yystack_[7].value.as < TokenInfo > ().ID_intstr, yystack_[6].value.as < pdm::ast::Typespec* > (), std::move(yystack_[4].value.as < std::vector<pdm::ast::TPattern*> > ()), std::move(yystack_[1].value.as < std::vector<pdm::ast::Exp*> > ())); 
      }
#line 2259 "parser.tab.cc"
    break;

  case 43: // using_stmt: "using" parenExpr
#line 388 "parser.yy"
                         { yylhs.value.as < pdm::ast::Stmt* > () = mgr->new_using_stmt(yylhs.location, yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2265 "parser.tab.cc"
    break;

  case 44: // importStmt: "import" vid "from" stringl "type" stringl
#line 392 "parser.yy"
                                                       { yylhs.value.as < pdm::ast::Stmt* > () = mgr->new_import_stmt(yylhs.location, yystack_[4].value.as < TokenInfo > ().ID_intstr, *yystack_[2].value.as < TokenInfo > ().String_utf8string, *yystack_[0].value.as < TokenInfo > ().String_utf8string); }
#line 2271 "parser.tab.cc"
    break;

  case 45: // extern_stmt: "extern" vid "from" expr
#line 396 "parser.yy"
                                    { yylhs.value.as < pdm::ast::Stmt* > () = mgr->new_extern_stmt(yylhs.location, yystack_[2].value.as < TokenInfo > ().ID_intstr, yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2277 "parser.tab.cc"
    break;

  case 46: // tid: "<TypeId>"
#line 403 "parser.yy"
     { yylhs.value.as < TokenInfo > () = yystack_[0].value.as < TokenInfo > (); }
#line 2283 "parser.tab.cc"
    break;

  case 47: // vid: "<val_id>"
#line 404 "parser.yy"
     { yylhs.value.as < TokenInfo > () = yystack_[0].value.as < TokenInfo > (); }
#line 2289 "parser.tab.cc"
    break;

  case 48: // floatl: "4.2"
#line 406 "parser.yy"
      { yylhs.value.as < TokenInfo > () = yystack_[0].value.as < TokenInfo > (); }
#line 2295 "parser.tab.cc"
    break;

  case 49: // stringl: "'sq-string-literal'"
#line 409 "parser.yy"
      { yylhs.value.as < TokenInfo > () = yystack_[0].value.as < TokenInfo > (); }
#line 2301 "parser.tab.cc"
    break;

  case 50: // stringl: "\"dq-string-literal\""
#line 410 "parser.yy"
      { yylhs.value.as < TokenInfo > () = yystack_[0].value.as < TokenInfo > (); }
#line 2307 "parser.tab.cc"
    break;

  case 51: // expr: type_query_exp
#line 417 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2313 "parser.tab.cc"
    break;

  case 52: // expr_cl1: expr
#line 420 "parser.yy"
                             { yylhs.value.as < std::vector<pdm::ast::Exp*> > ().push_back(yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2319 "parser.tab.cc"
    break;

  case 53: // expr_cl1: expr_cl1 "," expr
#line 421 "parser.yy"
                             { yylhs.value.as < std::vector<pdm::ast::Exp*> > () = std::move(yystack_[2].value.as < std::vector<pdm::ast::Exp*> > ()); yylhs.value.as < std::vector<pdm::ast::Exp*> > ().push_back(yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2325 "parser.tab.cc"
    break;

  case 54: // expr_cl2: expr "," expr
#line 424 "parser.yy"
                             { yylhs.value.as < std::vector<pdm::ast::Exp*> > ().reserve(2); yylhs.value.as < std::vector<pdm::ast::Exp*> > ().push_back(yystack_[2].value.as < pdm::ast::Exp* > ()); yylhs.value.as < std::vector<pdm::ast::Exp*> > ().push_back(yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2331 "parser.tab.cc"
    break;

  case 55: // expr_cl2: expr_cl2 "," expr
#line 425 "parser.yy"
                             { yylhs.value.as < std::vector<pdm::ast::Exp*> > () = std::move(yystack_[2].value.as < std::vector<pdm::ast::Exp*> > ()); yylhs.value.as < std::vector<pdm::ast::Exp*> > ().push_back(yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2337 "parser.tab.cc"
    break;

  case 56: // expr_sl: expr ";"
#line 428 "parser.yy"
                             { yylhs.value.as < std::vector<pdm::ast::Exp*> > ().push_back(yystack_[1].value.as < pdm::ast::Exp* > ()); }
#line 2343 "parser.tab.cc"
    break;

  case 57: // expr_sl: expr_sl expr ";"
#line 429 "parser.yy"
                             { yylhs.value.as < std::vector<pdm::ast::Exp*> > () = std::move(yystack_[2].value.as < std::vector<pdm::ast::Exp*> > ()); yylhs.value.as < std::vector<pdm::ast::Exp*> > ().push_back(yystack_[1].value.as < pdm::ast::Exp* > ()); }
#line 2349 "parser.tab.cc"
    break;

  case 58: // parenExpr: unitExpr
#line 433 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2355 "parser.tab.cc"
    break;

  case 59: // parenExpr: vparenExpr
#line 434 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2361 "parser.tab.cc"
    break;

  case 60: // parenExpr: vtupleExpr
#line 435 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2367 "parser.tab.cc"
    break;

  case 61: // parenExpr: vstructExpr
#line 436 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2373 "parser.tab.cc"
    break;

  case 62: // parenExpr: chainExpr
#line 437 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2379 "parser.tab.cc"
    break;

  case 63: // unitExpr: "(" ")"
#line 440 "parser.yy"
                        { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_unit_exp(yylhs.location); }
#line 2385 "parser.tab.cc"
    break;

  case 64: // unitExpr: "{" "}"
#line 441 "parser.yy"
                        { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_unit_exp(yylhs.location); }
#line 2391 "parser.tab.cc"
    break;

  case 65: // vparenExpr: "(" expr ")"
#line 444 "parser.yy"
                          { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_paren_exp(yylhs.location, yystack_[1].value.as < pdm::ast::Exp* > ()); }
#line 2397 "parser.tab.cc"
    break;

  case 66: // vtupleExpr: "(" expr "," ")"
#line 447 "parser.yy"
                                   { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_tuple_exp(yylhs.location, std::move(std::vector(1,yystack_[2].value.as < pdm::ast::Exp* > ()))); }
#line 2403 "parser.tab.cc"
    break;

  case 67: // vtupleExpr: "(" expr_cl2 ")"
#line 448 "parser.yy"
                                   { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_tuple_exp(yylhs.location, std::move(yystack_[1].value.as < std::vector<pdm::ast::Exp*> > ())); }
#line 2409 "parser.tab.cc"
    break;

  case 68: // vstructExpr: "{" vstructExprField_cl "}"
#line 451 "parser.yy"
                                            { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_struct_exp(yylhs.location, std::move(yystack_[1].value.as < std::vector<pdm::ast::StructExp::Field*> > ())); }
#line 2415 "parser.tab.cc"
    break;

  case 69: // primaryExpr: parenExpr
#line 454 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2421 "parser.tab.cc"
    break;

  case 70: // primaryExpr: vid
#line 455 "parser.yy"
                     { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_id_exp(yylhs.location, yystack_[0].value.as < TokenInfo > ().ID_intstr); }
#line 2427 "parser.tab.cc"
    break;

  case 71: // primaryExpr: int_expr
#line 456 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2433 "parser.tab.cc"
    break;

  case 72: // primaryExpr: floatl
#line 457 "parser.yy"
                     { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_float_exp(yylhs.location, yystack_[0].value.as < TokenInfo > ().Float); }
#line 2439 "parser.tab.cc"
    break;

  case 73: // primaryExpr: stringls
#line 458 "parser.yy"
                     { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_string_exp(yylhs.location, std::move(yystack_[0].value.as < std::vector<pdm::ast::StringExp::Piece> > ())); }
#line 2445 "parser.tab.cc"
    break;

  case 74: // primaryExpr: ifThenElseExpr
#line 459 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2451 "parser.tab.cc"
    break;

  case 75: // primaryExpr: vlambdaExpr
#line 460 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2457 "parser.tab.cc"
    break;

  case 76: // int_expr: "42"
#line 463 "parser.yy"
                { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_int_exp(yylhs.location, yystack_[0].value.as < TokenInfo > ().Int, ast::IntExp::Base::Dec); }
#line 2463 "parser.tab.cc"
    break;

  case 77: // int_expr: "0x2a"
#line 464 "parser.yy"
                { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_int_exp(yylhs.location, yystack_[0].value.as < TokenInfo > ().Int, ast::IntExp::Base::Hex); }
#line 2469 "parser.tab.cc"
    break;

  case 78: // stringls: "'sq-string-literal'"
#line 467 "parser.yy"
                             { yylhs.value.as < std::vector<pdm::ast::StringExp::Piece> > ().emplace_back(yylhs.location, *yystack_[0].value.as < TokenInfo > ().String_utf8string, ast::StringExp::QuoteKind::SingleQuote); }
#line 2475 "parser.tab.cc"
    break;

  case 79: // stringls: "\"dq-string-literal\""
#line 468 "parser.yy"
                             { yylhs.value.as < std::vector<pdm::ast::StringExp::Piece> > ().emplace_back(yylhs.location, *yystack_[0].value.as < TokenInfo > ().String_utf8string, ast::StringExp::QuoteKind::DoubleQuote); }
#line 2481 "parser.tab.cc"
    break;

  case 80: // stringls: stringls "'sq-string-literal'"
#line 469 "parser.yy"
                             { yylhs.value.as < std::vector<pdm::ast::StringExp::Piece> > () = std::move(yystack_[1].value.as < std::vector<pdm::ast::StringExp::Piece> > ()); yylhs.value.as < std::vector<pdm::ast::StringExp::Piece> > ().emplace_back(yystack_[0].location, *yystack_[0].value.as < TokenInfo > ().String_utf8string, ast::StringExp::QuoteKind::SingleQuote); }
#line 2487 "parser.tab.cc"
    break;

  case 81: // stringls: stringls "\"dq-string-literal\""
#line 470 "parser.yy"
                             { yylhs.value.as < std::vector<pdm::ast::StringExp::Piece> > () = std::move(yystack_[1].value.as < std::vector<pdm::ast::StringExp::Piece> > ()); yylhs.value.as < std::vector<pdm::ast::StringExp::Piece> > ().emplace_back(yystack_[0].location, *yystack_[0].value.as < TokenInfo > ().String_utf8string, ast::StringExp::QuoteKind::DoubleQuote); }
#line 2493 "parser.tab.cc"
    break;

  case 82: // ifThenElseExpr: "if" parenExpr "then" parenExpr
#line 473 "parser.yy"
                                                             { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_if_exp(yylhs.location, yystack_[2].value.as < pdm::ast::Exp* > (), yystack_[0].value.as < pdm::ast::Exp* > (), nullptr); }
#line 2499 "parser.tab.cc"
    break;

  case 83: // ifThenElseExpr: "if" parenExpr "then" parenExpr "else" primaryExpr
#line 474 "parser.yy"
                                                             { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_if_exp(yylhs.location, yystack_[4].value.as < pdm::ast::Exp* > (), yystack_[2].value.as < pdm::ast::Exp* > (), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2505 "parser.tab.cc"
    break;

  case 84: // chainExpr: "{" expr "}"
#line 477 "parser.yy"
                                          { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_chain_exp(yylhs.location, std::move(std::vector<ast::Stmt*>{}), yystack_[1].value.as < pdm::ast::Exp* > ()); }
#line 2511 "parser.tab.cc"
    break;

  case 85: // chainExpr: "{" chainPrefix "}"
#line 478 "parser.yy"
                                          { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_chain_exp(yylhs.location, std::move(yystack_[1].value.as < std::vector<pdm::ast::Stmt*> > ()), nullptr); }
#line 2517 "parser.tab.cc"
    break;

  case 86: // chainExpr: "{" chainPrefix expr "}"
#line 479 "parser.yy"
                                          { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_chain_exp(yylhs.location, std::move(yystack_[2].value.as < std::vector<pdm::ast::Stmt*> > ()), yystack_[1].value.as < pdm::ast::Exp* > ()); }
#line 2523 "parser.tab.cc"
    break;

  case 87: // chainPrefix: chainPrefixStmt ";"
#line 482 "parser.yy"
                                             { yylhs.value.as < std::vector<pdm::ast::Stmt*> > ().push_back(yystack_[1].value.as < pdm::ast::Stmt* > ()); }
#line 2529 "parser.tab.cc"
    break;

  case 88: // chainPrefix: chainPrefix chainPrefixStmt ";"
#line 483 "parser.yy"
                                             { yylhs.value.as < std::vector<pdm::ast::Stmt*> > () = std::move(yystack_[2].value.as < std::vector<pdm::ast::Stmt*> > ()); yylhs.value.as < std::vector<pdm::ast::Stmt*> > ().push_back(yystack_[1].value.as < pdm::ast::Stmt* > ()); }
#line 2535 "parser.tab.cc"
    break;

  case 89: // vlambdaExpr: "fn" vpattern "=" parenExpr
#line 486 "parser.yy"
                                      { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_lambda_exp(yylhs.location, yystack_[2].value.as < pdm::ast::VPattern* > (), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2541 "parser.tab.cc"
    break;

  case 90: // postfixExpr: primaryExpr
#line 490 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2547 "parser.tab.cc"
    break;

  case 91: // postfixExpr: tcall_exp
#line 491 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2553 "parser.tab.cc"
    break;

  case 92: // postfixExpr: vcall_exp
#line 492 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2559 "parser.tab.cc"
    break;

  case 93: // postfixExpr: dot_name_exp
#line 493 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2565 "parser.tab.cc"
    break;

  case 94: // postfixExpr: dotIxExpr
#line 494 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2571 "parser.tab.cc"
    break;

  case 95: // tcall_exp: postfixExpr "[" vtarg_cl "]"
#line 497 "parser.yy"
                                          { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_tcall_exp(yylhs.location, yystack_[3].value.as < pdm::ast::Exp* > (), std::move(yystack_[1].value.as < std::vector<pdm::ast::TArg*> > ())); }
#line 2577 "parser.tab.cc"
    break;

  case 96: // vcall_exp: postfixExpr "(" ")"
#line 500 "parser.yy"
                                           { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_vcall_exp(yylhs.location, yystack_[2].value.as < pdm::ast::Exp* > (), std::move(std::vector<ast::Exp*>{})); }
#line 2583 "parser.tab.cc"
    break;

  case 97: // vcall_exp: postfixExpr "(" expr_cl1 ")"
#line 501 "parser.yy"
                                           { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_vcall_exp(yylhs.location, yystack_[3].value.as < pdm::ast::Exp* > (), std::move(yystack_[1].value.as < std::vector<pdm::ast::Exp*> > ())); }
#line 2589 "parser.tab.cc"
    break;

  case 98: // dot_name_exp: postfixExpr "." "<val_id>"
#line 504 "parser.yy"
                            { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_dot_name_exp(yylhs.location, yystack_[2].value.as < pdm::ast::Exp* > (), yystack_[0].value.as < TokenInfo > ().ID_intstr, ast::DotNameExp::RhsHint::LhsStruct); }
#line 2595 "parser.tab.cc"
    break;

  case 99: // dot_name_exp: postfixExpr "." "<TypeId>"
#line 505 "parser.yy"
                            { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_dot_name_exp(yylhs.location, yystack_[2].value.as < pdm::ast::Exp* > (), yystack_[0].value.as < TokenInfo > ().ID_intstr, ast::DotNameExp::RhsHint::LhsEnum); }
#line 2601 "parser.tab.cc"
    break;

  case 100: // dot_name_exp: postfixExpr "->" "<val_id>"
#line 506 "parser.yy"
                            { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_dot_name_exp(yylhs.location, yystack_[2].value.as < pdm::ast::Exp* > (), yystack_[0].value.as < TokenInfo > ().ID_intstr, ast::DotNameExp::RhsHint::LhsStructPtr); }
#line 2607 "parser.tab.cc"
    break;

  case 101: // dot_name_exp: postfixExpr "->" "<TypeId>"
#line 507 "parser.yy"
                            { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_dot_name_exp(yylhs.location, yystack_[2].value.as < pdm::ast::Exp* > (), yystack_[0].value.as < TokenInfo > ().ID_intstr, ast::DotNameExp::RhsHint::LhsEnumPtr); }
#line 2613 "parser.tab.cc"
    break;

  case 102: // dotIxExpr: postfixExpr "." int_expr
#line 510 "parser.yy"
                                    { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_dot_index_exp(yylhs.location, yystack_[2].value.as < pdm::ast::Exp* > (), yystack_[0].value.as < pdm::ast::Exp* > (), ast::DotIndexExp::RhsHint::LhsNotPtr); }
#line 2619 "parser.tab.cc"
    break;

  case 103: // dotIxExpr: postfixExpr "." parenExpr
#line 511 "parser.yy"
                                    { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_dot_index_exp(yylhs.location, yystack_[2].value.as < pdm::ast::Exp* > (), yystack_[0].value.as < pdm::ast::Exp* > (), ast::DotIndexExp::RhsHint::LhsNotPtr); }
#line 2625 "parser.tab.cc"
    break;

  case 104: // dotIxExpr: postfixExpr "->" int_expr
#line 512 "parser.yy"
                                    { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_dot_index_exp(yylhs.location, yystack_[2].value.as < pdm::ast::Exp* > (), yystack_[0].value.as < pdm::ast::Exp* > (), ast::DotIndexExp::RhsHint::LhsPtr); }
#line 2631 "parser.tab.cc"
    break;

  case 105: // dotIxExpr: postfixExpr "->" parenExpr
#line 513 "parser.yy"
                                    { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_dot_index_exp(yylhs.location, yystack_[2].value.as < pdm::ast::Exp* > (), yystack_[0].value.as < pdm::ast::Exp* > (), ast::DotIndexExp::RhsHint::LhsPtr); }
#line 2637 "parser.tab.cc"
    break;

  case 106: // unaryExpr: postfixExpr
#line 517 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2643 "parser.tab.cc"
    break;

  case 107: // unaryExpr: unaryOp unaryExpr
#line 518 "parser.yy"
                            { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_unary_exp(yylhs.location, yystack_[1].value.as < pdm::ast::UnaryOperator > (), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2649 "parser.tab.cc"
    break;

  case 108: // unaryOp: "+"
#line 521 "parser.yy"
                 { yylhs.value.as < pdm::ast::UnaryOperator > () = ast::UnaryOperator::Plus; }
#line 2655 "parser.tab.cc"
    break;

  case 109: // unaryOp: "-"
#line 522 "parser.yy"
                 { yylhs.value.as < pdm::ast::UnaryOperator > () = ast::UnaryOperator::Minus; }
#line 2661 "parser.tab.cc"
    break;

  case 110: // unaryOp: "*"
#line 523 "parser.yy"
                 { yylhs.value.as < pdm::ast::UnaryOperator > () = ast::UnaryOperator::DeRef; }
#line 2667 "parser.tab.cc"
    break;

  case 111: // unaryOp: "^"
#line 524 "parser.yy"
                 { yylhs.value.as < pdm::ast::UnaryOperator > () = ast::UnaryOperator::GetRef; }
#line 2673 "parser.tab.cc"
    break;

  case 112: // unaryOp: "not"
#line 525 "parser.yy"
                 { yylhs.value.as < pdm::ast::UnaryOperator > () = ast::UnaryOperator::Not; }
#line 2679 "parser.tab.cc"
    break;

  case 113: // binaryExpr: orBinaryExpr
#line 529 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2685 "parser.tab.cc"
    break;

  case 114: // mulBinaryOp: "*"
#line 532 "parser.yy"
                 { yylhs.value.as < pdm::ast::BinaryOperator > () = ast::BinaryOperator::Mul; }
#line 2691 "parser.tab.cc"
    break;

  case 115: // mulBinaryOp: "/"
#line 533 "parser.yy"
                 { yylhs.value.as < pdm::ast::BinaryOperator > () = ast::BinaryOperator::Div; }
#line 2697 "parser.tab.cc"
    break;

  case 116: // mulBinaryOp: "%"
#line 534 "parser.yy"
                 { yylhs.value.as < pdm::ast::BinaryOperator > () = ast::BinaryOperator::Rem; }
#line 2703 "parser.tab.cc"
    break;

  case 117: // mulBinaryExpr: unaryExpr
#line 537 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2709 "parser.tab.cc"
    break;

  case 118: // mulBinaryExpr: mulBinaryExpr mulBinaryOp unaryExpr
#line 538 "parser.yy"
                                            { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_binary_exp(yylhs.location, yystack_[1].value.as < pdm::ast::BinaryOperator > (), yystack_[2].value.as < pdm::ast::Exp* > (), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2715 "parser.tab.cc"
    break;

  case 119: // addBinaryOp: "+"
#line 541 "parser.yy"
             { yylhs.value.as < pdm::ast::BinaryOperator > () = ast::BinaryOperator::Add; }
#line 2721 "parser.tab.cc"
    break;

  case 120: // addBinaryOp: "-"
#line 542 "parser.yy"
             { yylhs.value.as < pdm::ast::BinaryOperator > () = ast::BinaryOperator::Subtract; }
#line 2727 "parser.tab.cc"
    break;

  case 121: // addBinaryExpr: mulBinaryExpr
#line 545 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2733 "parser.tab.cc"
    break;

  case 122: // addBinaryExpr: addBinaryExpr addBinaryOp mulBinaryExpr
#line 546 "parser.yy"
                                                { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_binary_exp(yylhs.location, yystack_[1].value.as < pdm::ast::BinaryOperator > (), yystack_[2].value.as < pdm::ast::Exp* > (), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2739 "parser.tab.cc"
    break;

  case 123: // cmpBinaryOp: "<"
#line 549 "parser.yy"
                { yylhs.value.as < pdm::ast::BinaryOperator > () = ast::BinaryOperator::Less; }
#line 2745 "parser.tab.cc"
    break;

  case 124: // cmpBinaryOp: "<="
#line 550 "parser.yy"
                { yylhs.value.as < pdm::ast::BinaryOperator > () = ast::BinaryOperator::LessOrEq; }
#line 2751 "parser.tab.cc"
    break;

  case 125: // cmpBinaryOp: ">"
#line 551 "parser.yy"
                { yylhs.value.as < pdm::ast::BinaryOperator > () = ast::BinaryOperator::Greater; }
#line 2757 "parser.tab.cc"
    break;

  case 126: // cmpBinaryOp: ">="
#line 552 "parser.yy"
                { yylhs.value.as < pdm::ast::BinaryOperator > () = ast::BinaryOperator::GreaterOrEq; }
#line 2763 "parser.tab.cc"
    break;

  case 127: // cmpBinaryExpr: addBinaryExpr
#line 555 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2769 "parser.tab.cc"
    break;

  case 128: // cmpBinaryExpr: cmpBinaryExpr cmpBinaryOp addBinaryExpr
#line 556 "parser.yy"
                                                { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_binary_exp(yylhs.location, yystack_[1].value.as < pdm::ast::BinaryOperator > (), yystack_[2].value.as < pdm::ast::Exp* > (), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2775 "parser.tab.cc"
    break;

  case 129: // eqBinaryOp: "=="
#line 559 "parser.yy"
                 { yylhs.value.as < pdm::ast::BinaryOperator > () = ast::BinaryOperator::Equals; }
#line 2781 "parser.tab.cc"
    break;

  case 130: // eqBinaryOp: "!="
#line 560 "parser.yy"
                 { yylhs.value.as < pdm::ast::BinaryOperator > () = ast::BinaryOperator::NotEquals; }
#line 2787 "parser.tab.cc"
    break;

  case 131: // eqBinaryExpr: cmpBinaryExpr
#line 563 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2793 "parser.tab.cc"
    break;

  case 132: // eqBinaryExpr: eqBinaryExpr eqBinaryOp cmpBinaryExpr
#line 564 "parser.yy"
                                            { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_binary_exp(yylhs.location, yystack_[1].value.as < pdm::ast::BinaryOperator > (), yystack_[2].value.as < pdm::ast::Exp* > (), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2799 "parser.tab.cc"
    break;

  case 133: // andBinaryExpr: eqBinaryExpr
#line 567 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2805 "parser.tab.cc"
    break;

  case 134: // andBinaryExpr: andBinaryExpr "and" eqBinaryExpr
#line 568 "parser.yy"
                                         { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_binary_exp(yylhs.location, ast::BinaryOperator::And, yystack_[2].value.as < pdm::ast::Exp* > (), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2811 "parser.tab.cc"
    break;

  case 135: // xorBinaryExpr: andBinaryExpr
#line 571 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2817 "parser.tab.cc"
    break;

  case 136: // xorBinaryExpr: xorBinaryExpr "xor" andBinaryExpr
#line 572 "parser.yy"
                                         { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_binary_exp(yylhs.location, ast::BinaryOperator::XOr, yystack_[2].value.as < pdm::ast::Exp* > (), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2823 "parser.tab.cc"
    break;

  case 137: // orBinaryExpr: xorBinaryExpr
#line 575 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2829 "parser.tab.cc"
    break;

  case 138: // orBinaryExpr: orBinaryExpr "or" xorBinaryExpr
#line 576 "parser.yy"
                                         { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_binary_exp(yylhs.location, ast::BinaryOperator::Or, yystack_[2].value.as < pdm::ast::Exp* > (), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2835 "parser.tab.cc"
    break;

  case 139: // type_query_exp: binaryExpr
#line 580 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2841 "parser.tab.cc"
    break;

  case 140: // type_query_exp: typespec type_query_op typespec
#line 581 "parser.yy"
                                        { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_type_query_exp(yylhs.location, yystack_[1].value.as < pdm::ast::TypeQueryKind > (), yystack_[2].value.as < pdm::ast::Typespec* > (), yystack_[0].value.as < pdm::ast::Typespec* > ()); }
#line 2847 "parser.tab.cc"
    break;

  case 141: // type_query_op: ":<"
#line 584 "parser.yy"
                    { yylhs.value.as < pdm::ast::TypeQueryKind > () = ast::TypeQueryKind::LhsSubtypesRhs; }
#line 2853 "parser.tab.cc"
    break;

  case 142: // type_query_op: ">:"
#line 585 "parser.yy"
                    { yylhs.value.as < pdm::ast::TypeQueryKind > () = ast::TypeQueryKind::LhsSupertypesRhs; }
#line 2859 "parser.tab.cc"
    break;

  case 143: // type_query_op: "::"
#line 586 "parser.yy"
                    { yylhs.value.as < pdm::ast::TypeQueryKind > () = ast::TypeQueryKind::LhsEqualsRhs; }
#line 2865 "parser.tab.cc"
    break;

  case 144: // typespec: unaryTypespec
#line 594 "parser.yy"
      { yylhs.value.as < pdm::ast::Typespec* > () = yystack_[0].value.as < pdm::ast::Typespec* > (); }
#line 2871 "parser.tab.cc"
    break;

  case 145: // typespec_cl1: typespec
#line 597 "parser.yy"
                                  { yylhs.value.as < std::vector<pdm::ast::Typespec*> > ().push_back(yystack_[0].value.as < pdm::ast::Typespec* > ()); }
#line 2877 "parser.tab.cc"
    break;

  case 146: // typespec_cl1: typespec_cl1 "," typespec
#line 598 "parser.yy"
                                  { yylhs.value.as < std::vector<pdm::ast::Typespec*> > () = std::move(yystack_[2].value.as < std::vector<pdm::ast::Typespec*> > ()); yylhs.value.as < std::vector<pdm::ast::Typespec*> > ().push_back(yystack_[0].value.as < pdm::ast::Typespec* > ()); }
#line 2883 "parser.tab.cc"
    break;

  case 147: // typespec_cl2: typespec "," typespec
#line 601 "parser.yy"
                                  { yylhs.value.as < std::vector<pdm::ast::Typespec*> > ().reserve(2); yylhs.value.as < std::vector<pdm::ast::Typespec*> > ().push_back(yystack_[2].value.as < pdm::ast::Typespec* > ()); yylhs.value.as < std::vector<pdm::ast::Typespec*> > ().push_back(yystack_[0].value.as < pdm::ast::Typespec* > ()); }
#line 2889 "parser.tab.cc"
    break;

  case 148: // typespec_cl2: typespec_cl2 "," typespec
#line 602 "parser.yy"
                                  { yylhs.value.as < std::vector<pdm::ast::Typespec*> > () = std::move(yystack_[2].value.as < std::vector<pdm::ast::Typespec*> > ()); yylhs.value.as < std::vector<pdm::ast::Typespec*> > ().push_back(yystack_[0].value.as < pdm::ast::Typespec* > ()); }
#line 2895 "parser.tab.cc"
    break;

  case 149: // structTypespecField: vid typespec
#line 606 "parser.yy"
                                  { yylhs.value.as < pdm::ast::StructTypespec::Field* > () = mgr->new_struct_typespec_field(yylhs.location, yystack_[1].value.as < TokenInfo > ().ID_intstr, yystack_[0].value.as < pdm::ast::Typespec* > ()); }
#line 2901 "parser.tab.cc"
    break;

  case 150: // structTypespecField_cl: structTypespecField
#line 609 "parser.yy"
                                                        { yylhs.value.as < std::vector<pdm::ast::StructTypespec::Field*> > ().push_back(yystack_[0].value.as < pdm::ast::StructTypespec::Field* > ()); }
#line 2907 "parser.tab.cc"
    break;

  case 151: // structTypespecField_cl: structTypespecField_cl "," structTypespecField
#line 610 "parser.yy"
                                                        { yylhs.value.as < std::vector<pdm::ast::StructTypespec::Field*> > () = std::move(yystack_[2].value.as < std::vector<pdm::ast::StructTypespec::Field*> > ()); yylhs.value.as < std::vector<pdm::ast::StructTypespec::Field*> > ().push_back(yystack_[0].value.as < pdm::ast::StructTypespec::Field* > ()); }
#line 2913 "parser.tab.cc"
    break;

  case 152: // primaryTypespec: tid
#line 614 "parser.yy"
                        { yylhs.value.as < pdm::ast::Typespec* > () = mgr->new_id_typespec(yylhs.location, yystack_[0].value.as < TokenInfo > ().ID_intstr); }
#line 2919 "parser.tab.cc"
    break;

  case 153: // primaryTypespec: parenTypespec
#line 615 "parser.yy"
      { yylhs.value.as < pdm::ast::Typespec* > () = yystack_[0].value.as < pdm::ast::Typespec* > (); }
#line 2925 "parser.tab.cc"
    break;

  case 154: // primaryTypespec: tupleTypespec
#line 616 "parser.yy"
      { yylhs.value.as < pdm::ast::Typespec* > () = yystack_[0].value.as < pdm::ast::Typespec* > (); }
#line 2931 "parser.tab.cc"
    break;

  case 155: // primaryTypespec: mod_prefix_tid
#line 617 "parser.yy"
      { yylhs.value.as < pdm::ast::Typespec* > () = yystack_[0].value.as < pdm::ast::Typespec* > (); }
#line 2937 "parser.tab.cc"
    break;

  case 156: // primaryTypespec: fn_typespec
#line 618 "parser.yy"
      { yylhs.value.as < pdm::ast::Typespec* > () = yystack_[0].value.as < pdm::ast::Typespec* > (); }
#line 2943 "parser.tab.cc"
    break;

  case 157: // parenTypespec: "(" typespec ")"
#line 621 "parser.yy"
                                { yylhs.value.as < pdm::ast::Typespec* > () = mgr->new_paren_typespec(yylhs.location, yystack_[1].value.as < pdm::ast::Typespec* > ()); }
#line 2949 "parser.tab.cc"
    break;

  case 158: // tupleTypespec: "(" typespec "," ")"
#line 624 "parser.yy"
                                    { yylhs.value.as < pdm::ast::Typespec* > () = mgr->new_tuple_typespec(yylhs.location, std::move(std::vector(1,yystack_[2].value.as < pdm::ast::Typespec* > ()))); }
#line 2955 "parser.tab.cc"
    break;

  case 159: // tupleTypespec: "(" typespec_cl2 ")"
#line 625 "parser.yy"
                                    { yylhs.value.as < pdm::ast::Typespec* > () = mgr->new_tuple_typespec(yylhs.location, std::move(yystack_[1].value.as < std::vector<pdm::ast::Typespec*> > ())); }
#line 2961 "parser.tab.cc"
    break;

  case 160: // mod_prefix_tid: mod_prefix tid
#line 628 "parser.yy"
                            { yylhs.value.as < pdm::ast::Typespec* > () = mgr->new_dot_name_typespec_with_mod_prefix(yylhs.location, std::move(yystack_[1].value.as < std::vector<pdm::intern::String> > ()), yystack_[0].value.as < TokenInfo > ().ID_intstr); }
#line 2967 "parser.tab.cc"
    break;

  case 161: // mod_prefix: vid "."
#line 631 "parser.yy"
                            { yylhs.value.as < std::vector<pdm::intern::String> > ().push_back(yystack_[1].value.as < TokenInfo > ().ID_intstr); }
#line 2973 "parser.tab.cc"
    break;

  case 162: // mod_prefix: mod_prefix vid "."
#line 632 "parser.yy"
                            { yylhs.value.as < std::vector<pdm::intern::String> > () = std::move(yystack_[2].value.as < std::vector<pdm::intern::String> > ()); }
#line 2979 "parser.tab.cc"
    break;

  case 163: // fn_typespec: "Fn" vpattern primaryTypespec
#line 635 "parser.yy"
                                      { yylhs.value.as < pdm::ast::Typespec* > () = mgr->new_fn_typespec(yylhs.location, std::move(yystack_[1].value.as < pdm::ast::VPattern* > ()), yystack_[0].value.as < pdm::ast::Typespec* > ()); }
#line 2985 "parser.tab.cc"
    break;

  case 164: // postfixTypespec: primaryTypespec
#line 639 "parser.yy"
      { yylhs.value.as < pdm::ast::Typespec* > () = yystack_[0].value.as < pdm::ast::Typespec* > (); }
#line 2991 "parser.tab.cc"
    break;

  case 165: // postfixTypespec: ttcall
#line 640 "parser.yy"
      { yylhs.value.as < pdm::ast::Typespec* > () = yystack_[0].value.as < pdm::ast::Typespec* > (); }
#line 2997 "parser.tab.cc"
    break;

  case 166: // postfixTypespec: tdot
#line 641 "parser.yy"
      { yylhs.value.as < pdm::ast::Typespec* > () = yystack_[0].value.as < pdm::ast::Typespec* > (); }
#line 3003 "parser.tab.cc"
    break;

  case 167: // ttcall: postfixTypespec "[" ttarg_cl "]"
#line 644 "parser.yy"
                                              { yylhs.value.as < pdm::ast::Typespec* > () = mgr->new_tcall_typespec(yylhs.location, yystack_[3].value.as < pdm::ast::Typespec* > (), std::move(yystack_[1].value.as < std::vector<pdm::ast::TArg*> > ())); }
#line 3009 "parser.tab.cc"
    break;

  case 168: // tdot: postfixTypespec "." "<val_id>"
#line 646 "parser.yy"
                                { yylhs.value.as < pdm::ast::Typespec* > () = mgr->new_dot_name_typespec_with_type_prefix(yylhs.location, yystack_[2].value.as < pdm::ast::Typespec* > (), yystack_[0].value.as < TokenInfo > ().ID_intstr); }
#line 3015 "parser.tab.cc"
    break;

  case 169: // unaryTypespec: postfixTypespec
#line 650 "parser.yy"
      { yylhs.value.as < pdm::ast::Typespec* > () = yystack_[0].value.as < pdm::ast::Typespec* > (); }
#line 3021 "parser.tab.cc"
    break;

  case 170: // unaryTypespec: "&" unaryTypespec
#line 651 "parser.yy"
                                 { yylhs.value.as < pdm::ast::Typespec* > () = mgr->new_ptr_typespec(yylhs.location,yystack_[0].value.as < pdm::ast::Typespec* > ()); }
#line 3027 "parser.tab.cc"
    break;

  case 171: // long_typespec: unaryTypespec
#line 655 "parser.yy"
      { yylhs.value.as < pdm::ast::Typespec* > () = yystack_[0].value.as < pdm::ast::Typespec* > (); }
#line 3033 "parser.tab.cc"
    break;

  case 172: // long_typespec: structTypespec
#line 656 "parser.yy"
      { yylhs.value.as < pdm::ast::Typespec* > () = yystack_[0].value.as < pdm::ast::Typespec* > (); }
#line 3039 "parser.tab.cc"
    break;

  case 173: // structTypespec: "{" structTypespecField_cl "}"
#line 659 "parser.yy"
                                            { yylhs.value.as < pdm::ast::Typespec* > () = mgr->new_struct_typespec(yylhs.location, std::move(yystack_[1].value.as < std::vector<pdm::ast::StructTypespec::Field*> > ())); }
#line 3045 "parser.tab.cc"
    break;

  case 174: // ttarg: typespec
#line 663 "parser.yy"
                { yylhs.value.as < pdm::ast::TArg* > () = mgr->new_targ_typespec(yylhs.location,yystack_[0].value.as < pdm::ast::Typespec* > ()); }
#line 3051 "parser.tab.cc"
    break;

  case 175: // ttarg: expr
#line 664 "parser.yy"
                { yylhs.value.as < pdm::ast::TArg* > () = mgr->new_targ_exp(yylhs.location,yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 3057 "parser.tab.cc"
    break;

  case 176: // ttarg_cl: ttarg
#line 667 "parser.yy"
                            { yylhs.value.as < std::vector<pdm::ast::TArg*> > ().push_back(yystack_[0].value.as < pdm::ast::TArg* > ()); }
#line 3063 "parser.tab.cc"
    break;

  case 177: // ttarg_cl: ttarg_cl "," ttarg
#line 668 "parser.yy"
                            { yylhs.value.as < std::vector<pdm::ast::TArg*> > () = std::move(yystack_[2].value.as < std::vector<pdm::ast::TArg*> > ()); yylhs.value.as < std::vector<pdm::ast::TArg*> > ().push_back(yystack_[0].value.as < pdm::ast::TArg* > ()); }
#line 3069 "parser.tab.cc"
    break;

  case 178: // vtarg: typespec
#line 673 "parser.yy"
               { yylhs.value.as < pdm::ast::TArg* > () = mgr->new_targ_typespec(yylhs.location, yystack_[0].value.as < pdm::ast::Typespec* > ()); }
#line 3075 "parser.tab.cc"
    break;

  case 179: // vtarg: expr
#line 674 "parser.yy"
               { yylhs.value.as < pdm::ast::TArg* > () = mgr->new_targ_exp(yylhs.location, yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 3081 "parser.tab.cc"
    break;

  case 180: // vtarg_cl: vtarg
#line 677 "parser.yy"
                             { yylhs.value.as < std::vector<pdm::ast::TArg*> > ().push_back(yystack_[0].value.as < pdm::ast::TArg* > ()); }
#line 3087 "parser.tab.cc"
    break;

  case 181: // vtarg_cl: vtarg_cl "," vtarg
#line 678 "parser.yy"
                             { yylhs.value.as < std::vector<pdm::ast::TArg*> > () = std::move(yystack_[2].value.as < std::vector<pdm::ast::TArg*> > ()); yylhs.value.as < std::vector<pdm::ast::TArg*> > ().push_back(yystack_[0].value.as < pdm::ast::TArg* > ()); }
#line 3093 "parser.tab.cc"
    break;

  case 182: // vstructExprField: vid "=" expr
#line 686 "parser.yy"
                    { yylhs.value.as < pdm::ast::StructExp::Field* > () = mgr->new_struct_exp_field(yylhs.location, yystack_[2].value.as < TokenInfo > ().ID_intstr, yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 3099 "parser.tab.cc"
    break;

  case 183: // vpatternField: vid typespec
#line 689 "parser.yy"
                   { yylhs.value.as < pdm::ast::VPattern::Field* > () = mgr->new_vpattern_field(yylhs.location, yystack_[1].value.as < TokenInfo > ().ID_intstr, yystack_[0].value.as < pdm::ast::Typespec* > ()); }
#line 3105 "parser.tab.cc"
    break;

  case 184: // lpatternField: vid typespec
#line 692 "parser.yy"
                    { yylhs.value.as < pdm::ast::LPattern::Field* > () = mgr->new_lpattern_field(yylhs.location, ast::LPattern::FieldKind::IdTypespecPair, yystack_[1].value.as < TokenInfo > ().ID_intstr, yystack_[0].value.as < pdm::ast::Typespec* > ()); }
#line 3111 "parser.tab.cc"
    break;

  case 185: // lpatternField: vid
#line 693 "parser.yy"
                    { yylhs.value.as < pdm::ast::LPattern::Field* > () = mgr->new_lpattern_field(yylhs.location, ast::LPattern::FieldKind::IdSingleton, yystack_[0].value.as < TokenInfo > ().ID_intstr); }
#line 3117 "parser.tab.cc"
    break;

  case 186: // tpatternField: vid typespec
#line 696 "parser.yy"
                    { yylhs.value.as < pdm::ast::TPattern::Field* > () = mgr->new_tpattern_field(yylhs.location, ast::TPattern::FieldKind::Value, yystack_[1].value.as < TokenInfo > ().ID_intstr, yystack_[0].value.as < pdm::ast::Typespec* > ()); }
#line 3123 "parser.tab.cc"
    break;

  case 187: // tpatternField: tid typespec
#line 697 "parser.yy"
                    { yylhs.value.as < pdm::ast::TPattern::Field* > () = mgr->new_tpattern_field(yylhs.location, ast::TPattern::FieldKind::Type, yystack_[1].value.as < TokenInfo > ().ID_intstr, yystack_[0].value.as < pdm::ast::Typespec* > ()); }
#line 3129 "parser.tab.cc"
    break;

  case 188: // lpattern: "(" lpatternField_cl ")"
#line 701 "parser.yy"
                                      { yylhs.value.as < pdm::ast::LPattern* > () = mgr->new_lpattern(yylhs.location, std::move(yystack_[1].value.as < std::vector<pdm::ast::LPattern::Field*> > ())); }
#line 3135 "parser.tab.cc"
    break;

  case 189: // lpattern: "(" ")"
#line 702 "parser.yy"
                                      { yylhs.value.as < pdm::ast::LPattern* > () = mgr->new_lpattern(yylhs.location, std::move(std::vector<ast::LPattern::Field*>{})); }
#line 3141 "parser.tab.cc"
    break;

  case 190: // lpattern_naked: lpatternField
#line 705 "parser.yy"
                                      { yylhs.value.as < pdm::ast::LPattern* > () = mgr->new_lpattern(yylhs.location, std::move(std::vector<ast::LPattern::Field*>{1,yystack_[0].value.as < pdm::ast::LPattern::Field* > ()})); }
#line 3147 "parser.tab.cc"
    break;

  case 191: // lpattern_naked: lpattern
#line 706 "parser.yy"
      { yylhs.value.as < pdm::ast::LPattern* > () = yystack_[0].value.as < pdm::ast::LPattern* > (); }
#line 3153 "parser.tab.cc"
    break;

  case 192: // vpattern: "(" vpatternField_cl ")"
#line 709 "parser.yy"
                                      { yylhs.value.as < pdm::ast::VPattern* > () = mgr->new_vpattern(yylhs.location, std::move(yystack_[1].value.as < std::vector<pdm::ast::VPattern::Field*> > ())); }
#line 3159 "parser.tab.cc"
    break;

  case 193: // vpattern: "(" ")"
#line 710 "parser.yy"
                                      { yylhs.value.as < pdm::ast::VPattern* > () = mgr->new_vpattern(yylhs.location, std::move(std::vector<ast::VPattern::Field*>{})); }
#line 3165 "parser.tab.cc"
    break;

  case 194: // tpattern: "[" tpatternField_cl "]"
#line 713 "parser.yy"
                                              { yylhs.value.as < pdm::ast::TPattern* > () = mgr->new_tpattern(yylhs.location, std::move(yystack_[1].value.as < std::vector<pdm::ast::TPattern::Field*> > ()), false); }
#line 3171 "parser.tab.cc"
    break;

  case 195: // tpattern: "!" "[" tpatternField_cl "]"
#line 714 "parser.yy"
                                              { yylhs.value.as < pdm::ast::TPattern* > () = mgr->new_tpattern(yylhs.location, std::move(std::vector<ast::TPattern::Field*>{}), true); }
#line 3177 "parser.tab.cc"
    break;

  case 196: // vpatternField_cl: vpatternField
#line 718 "parser.yy"
                                             { yylhs.value.as < std::vector<pdm::ast::VPattern::Field*> > ().push_back(yystack_[0].value.as < pdm::ast::VPattern::Field* > ()); }
#line 3183 "parser.tab.cc"
    break;

  case 197: // vpatternField_cl: vpatternField_cl "," vpatternField
#line 719 "parser.yy"
                                             { yylhs.value.as < std::vector<pdm::ast::VPattern::Field*> > () = std::move(yystack_[2].value.as < std::vector<pdm::ast::VPattern::Field*> > ()); yylhs.value.as < std::vector<pdm::ast::VPattern::Field*> > ().push_back(yystack_[0].value.as < pdm::ast::VPattern::Field* > ()); }
#line 3189 "parser.tab.cc"
    break;

  case 198: // lpatternField_cl: lpatternField
#line 722 "parser.yy"
                                             { yylhs.value.as < std::vector<pdm::ast::LPattern::Field*> > ().push_back(yystack_[0].value.as < pdm::ast::LPattern::Field* > ()); }
#line 3195 "parser.tab.cc"
    break;

  case 199: // lpatternField_cl: lpatternField_cl "," lpatternField
#line 723 "parser.yy"
                                             { yylhs.value.as < std::vector<pdm::ast::LPattern::Field*> > () = std::move(yystack_[2].value.as < std::vector<pdm::ast::LPattern::Field*> > ()); yylhs.value.as < std::vector<pdm::ast::LPattern::Field*> > ().push_back(yystack_[0].value.as < pdm::ast::LPattern::Field* > ()); }
#line 3201 "parser.tab.cc"
    break;

  case 200: // tpatternField_cl: tpatternField
#line 726 "parser.yy"
                                             { yylhs.value.as < std::vector<pdm::ast::TPattern::Field*> > ().push_back(yystack_[0].value.as < pdm::ast::TPattern::Field* > ()); }
#line 3207 "parser.tab.cc"
    break;

  case 201: // tpatternField_cl: tpatternField_cl "," tpatternField
#line 727 "parser.yy"
                                             { yylhs.value.as < std::vector<pdm::ast::TPattern::Field*> > () = std::move(yystack_[2].value.as < std::vector<pdm::ast::TPattern::Field*> > ()); yylhs.value.as < std::vector<pdm::ast::TPattern::Field*> > ().push_back(yystack_[0].value.as < pdm::ast::TPattern::Field* > ()); }
#line 3213 "parser.tab.cc"
    break;

  case 202: // vstructExprField_cl: vstructExprField
#line 730 "parser.yy"
                                                    { yylhs.value.as < std::vector<pdm::ast::StructExp::Field*> > ().push_back(yystack_[0].value.as < pdm::ast::StructExp::Field* > ()); }
#line 3219 "parser.tab.cc"
    break;

  case 203: // vstructExprField_cl: vstructExprField_cl "," vstructExprField
#line 731 "parser.yy"
                                                    { yylhs.value.as < std::vector<pdm::ast::StructExp::Field*> > () = std::move(yystack_[2].value.as < std::vector<pdm::ast::StructExp::Field*> > ()); yylhs.value.as < std::vector<pdm::ast::StructExp::Field*> > ().push_back(yystack_[0].value.as < pdm::ast::StructExp::Field* > ()); }
#line 3225 "parser.tab.cc"
    break;

  case 204: // tpattern_seq: tpattern
#line 735 "parser.yy"
                             { yylhs.value.as < std::vector<pdm::ast::TPattern*> > ().push_back(yystack_[0].value.as < pdm::ast::TPattern* > ()); }
#line 3231 "parser.tab.cc"
    break;

  case 205: // tpattern_seq: tpattern_seq tpattern
#line 736 "parser.yy"
                             { yylhs.value.as < std::vector<pdm::ast::TPattern*> > () = std::move(yystack_[1].value.as < std::vector<pdm::ast::TPattern*> > ()); yylhs.value.as < std::vector<pdm::ast::TPattern*> > ().push_back(yystack_[0].value.as < pdm::ast::TPattern* > ()); }
#line 3237 "parser.tab.cc"
    break;


#line 3241 "parser.tab.cc"

            default:
              break;
            }
        }
#if YY_EXCEPTIONS
      catch (const syntax_error& yyexc)
        {
          YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
          error (yyexc);
          YYERROR;
        }
#endif // YY_EXCEPTIONS
      YY_SYMBOL_PRINT ("-> $$ =", yylhs);
      yypop_ (yylen);
      yylen = 0;

      // Shift the result of the reduction.
      yypush_ (YY_NULLPTR, YY_MOVE (yylhs));
    }
    goto yynewstate;


  /*--------------------------------------.
  | yyerrlab -- here on detecting error.  |
  `--------------------------------------*/
  yyerrlab:
    // If not already recovering from an error, report this error.
    if (!yyerrstatus_)
      {
        ++yynerrs_;
        std::string msg = YY_("syntax error");
        error (yyla.location, YY_MOVE (msg));
      }


    yyerror_range[1].location = yyla.location;
    if (yyerrstatus_ == 3)
      {
        /* If just tried and failed to reuse lookahead token after an
           error, discard it.  */

        // Return failure if at end of input.
        if (yyla.kind () == symbol_kind::S_YYEOF)
          YYABORT;
        else if (!yyla.empty ())
          {
            yy_destroy_ ("Error: discarding", yyla);
            yyla.clear ();
          }
      }

    // Else will try to reuse lookahead token after shifting the error token.
    goto yyerrlab1;


  /*---------------------------------------------------.
  | yyerrorlab -- error raised explicitly by YYERROR.  |
  `---------------------------------------------------*/
  yyerrorlab:
    /* Pacify compilers when the user code never invokes YYERROR and
       the label yyerrorlab therefore never appears in user code.  */
    if (false)
      YYERROR;

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    YY_STACK_PRINT ();
    goto yyerrlab1;


  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;   // Each real token shifted decrements this.
    // Pop stack until we find a state that shifts the error token.
    for (;;)
      {
        yyn = yypact_[+yystack_[0].state];
        if (!yy_pact_value_is_default_ (yyn))
          {
            yyn += symbol_kind::S_YYerror;
            if (0 <= yyn && yyn <= yylast_
                && yycheck_[yyn] == symbol_kind::S_YYerror)
              {
                yyn = yytable_[yyn];
                if (0 < yyn)
                  break;
              }
          }

        // Pop the current state because it cannot handle the error token.
        if (yystack_.size () == 1)
          YYABORT;

        yyerror_range[1].location = yystack_[0].location;
        yy_destroy_ ("Error: popping", yystack_[0]);
        yypop_ ();
        YY_STACK_PRINT ();
      }
    {
      stack_symbol_type error_token;

      yyerror_range[2].location = yyla.location;
      YYLLOC_DEFAULT (error_token.location, yyerror_range, 2);

      // Shift the error token.
      error_token.state = state_type (yyn);
      yypush_ ("Shifting", YY_MOVE (error_token));
    }
    goto yynewstate;


  /*-------------------------------------.
  | yyacceptlab -- YYACCEPT comes here.  |
  `-------------------------------------*/
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;


  /*-----------------------------------.
  | yyabortlab -- YYABORT comes here.  |
  `-----------------------------------*/
  yyabortlab:
    yyresult = 1;
    goto yyreturn;


  /*-----------------------------------------------------.
  | yyreturn -- parsing is finished, return the result.  |
  `-----------------------------------------------------*/
  yyreturn:
    if (!yyla.empty ())
      yy_destroy_ ("Cleanup: discarding lookahead", yyla);

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    YY_STACK_PRINT ();
    while (1 < yystack_.size ())
      {
        yy_destroy_ ("Cleanup: popping", yystack_[0]);
        yypop_ ();
      }

    return yyresult;
  }
#if YY_EXCEPTIONS
    catch (...)
      {
        YYCDEBUG << "Exception caught: cleaning lookahead and stack\n";
        // Do not try to display the values of the reclaimed symbols,
        // as their printers might throw an exception.
        if (!yyla.empty ())
          yy_destroy_ (YY_NULLPTR, yyla);

        while (1 < yystack_.size ())
          {
            yy_destroy_ (YY_NULLPTR, yystack_[0]);
            yypop_ ();
          }
        throw;
      }
#endif // YY_EXCEPTIONS
  }

  void
  parser::error (const syntax_error& yyexc)
  {
    error (yyexc.location, yyexc.what ());
  }

#if YYDEBUG || 0
  const char *
  parser::symbol_name (symbol_kind_type yysymbol)
  {
    return yytname_[yysymbol];
  }
#endif // #if YYDEBUG || 0





  const short parser::yypact_ninf_ = -177;

  const signed char parser::yytable_ninf_ = -1;

  const short
  parser::yypact_[] =
  {
      64,    23,    53,    64,    39,  -177,    41,  -177,    71,  -177,
     631,  -177,     8,    94,    94,    94,   111,   111,   111,  -177,
     611,    73,  -177,  -177,  -177,  -177,  -177,  -177,  -177,   412,
     330,  -177,  -177,  -177,  -177,  -177,  -177,  -177,   107,   150,
      54,  -177,    51,     4,    74,  -177,   155,  -177,     8,   140,
     140,  -177,  -177,  -177,  -177,  -177,  -177,   412,  -177,  -177,
    -177,  -177,  -177,    16,  -177,   170,  -177,   148,   149,  -177,
    -177,  -177,   176,  -177,  -177,   135,  -177,  -177,  -177,  -177,
    -177,   217,  -177,   103,   189,   182,   196,   190,   191,   198,
    -177,    67,  -177,  -177,  -177,  -177,   254,  -177,    60,  -177,
    -177,  -177,    18,    18,    18,   577,  -177,   194,  -177,  -177,
    -177,  -177,  -177,   -16,   184,   379,  -177,    83,   232,   577,
       6,   254,   185,   -14,  -177,    54,    13,    57,   111,  -177,
     201,  -177,   206,   111,  -177,   259,   216,    29,    26,   151,
      16,   170,  -177,  -177,   445,  -177,   577,  -177,  -177,  -177,
      40,   478,   577,    70,  -177,  -177,  -177,  -177,  -177,   217,
    -177,  -177,   217,  -177,  -177,  -177,  -177,   217,  -177,  -177,
     217,   217,   217,   217,  -177,  -177,  -177,    16,  -177,   238,
     270,   577,     9,    16,  -177,  -177,   219,   227,   231,   236,
    -177,   577,  -177,  -177,   255,   249,    94,  -177,  -177,  -177,
     273,  -177,  -177,    16,  -177,   154,    16,    16,  -177,    46,
     254,    16,     8,   -10,  -177,    94,  -177,  -177,  -177,    13,
     201,   111,    19,    16,     8,     8,  -177,    21,  -177,    16,
    -177,   157,  -177,  -177,  -177,  -177,  -177,  -177,  -177,  -177,
    -177,   159,  -177,    67,  -177,   100,  -177,  -177,  -177,  -177,
    -177,   103,   189,   182,   196,   190,   191,  -177,  -177,  -177,
    -177,    67,  -177,   110,  -177,  -177,   162,  -177,   577,   577,
     577,   577,  -177,  -177,  -177,   241,  -177,   232,  -177,    94,
    -177,  -177,  -177,   254,  -177,   139,   242,  -177,    16,     8,
      16,  -177,   142,  -177,  -177,  -177,  -177,   165,   245,   289,
    -177,  -177,  -177,  -177,   577,  -177,   577,  -177,   577,  -177,
      94,  -177,  -177,  -177,  -177,  -177,  -177,  -177,  -177,  -177,
       8,   247,  -177,  -177,    94,  -177,    16,  -177,    88,   125,
    -177,  -177,  -177,  -177,  -177,     8,  -177,  -177,   260,   106,
    -177,  -177,   577,   261,   269,   511,   577,  -177,  -177,   272,
     544,  -177,  -177
  };

  const unsigned char
  parser::yydefact_[] =
  {
       0,     0,     0,     2,     0,     5,     0,     1,     0,     3,
       0,     4,     0,     0,     0,     0,     0,     0,     0,    24,
       0,     0,    19,    20,    21,    22,    25,    23,    26,     0,
       0,    43,    58,    59,    60,    61,    62,    47,     0,     0,
       0,    46,     0,     0,     0,     6,     0,     7,     0,     0,
       0,   112,    76,    77,    48,    79,    78,     0,    63,   110,
     108,   109,   111,     0,   152,    70,    72,     0,     0,    69,
      90,    71,    73,    74,    75,   106,    91,    92,    93,    94,
     117,     0,   139,   121,   127,   131,   133,   135,   137,   113,
      51,     0,   164,   153,   154,   155,     0,   156,   169,   165,
     166,   144,     0,     0,     0,     0,    64,     0,     9,    10,
      11,    12,    13,    70,    18,     0,   202,     0,     0,     0,
       0,     0,     0,     0,   204,     0,     0,     0,     0,    33,
      35,    36,    38,     0,     8,     0,     0,     0,     0,     0,
       0,     0,   170,   161,     0,    65,     0,    67,    81,    80,
       0,     0,     0,     0,    70,   107,   114,   115,   116,     0,
     119,   120,     0,   123,   124,   125,   126,     0,   129,   130,
       0,     0,     0,     0,   143,   141,   142,     0,   160,     0,
       0,     0,     0,   185,   190,   191,     0,     0,     0,     0,
      87,     0,    84,    85,     0,    18,     0,    68,    50,    49,
       0,    45,   193,     0,   196,     0,     0,     0,   200,     0,
       0,     0,     0,     0,   205,     0,   171,    31,   172,     0,
      34,     0,     0,     0,     0,     0,   163,     0,   157,     0,
     159,     0,    66,    54,    55,    98,    99,   103,   102,    96,
      52,     0,   179,   178,   180,     0,   100,   101,   105,   104,
     118,   122,   128,   132,   134,   136,   138,   140,   162,   168,
     175,   174,   176,     0,   189,   198,     0,   184,     0,     0,
       0,     0,   182,    88,    86,     0,   203,     0,   183,     0,
     192,   187,   186,     0,   194,     0,     0,    29,     0,     0,
       0,   150,     0,    32,    37,    39,   145,     0,     0,    82,
      89,   158,   147,   148,     0,    97,     0,    95,     0,   167,
       0,   188,    14,    15,    16,    17,    44,   197,   201,   195,
       0,     0,    30,   149,     0,   173,     0,    40,     0,     0,
      53,   181,   177,   199,    27,     0,   151,   146,     0,     0,
      83,    28,     0,     0,     0,     0,     0,    56,    41,     0,
       0,    57,    42
  };

  const short
  parser::yypgoto_[] =
  {
    -177,  -177,  -177,   308,    28,  -177,   197,  -177,  -177,  -177,
    -177,  -177,   293,  -177,  -177,  -177,  -177,   187,    95,  -177,
    -177,  -177,  -177,    11,     0,  -177,    42,   -28,  -177,  -177,
     -26,   -12,  -177,  -177,  -177,  -177,    -8,   101,  -177,  -177,
    -177,  -177,  -177,  -177,  -177,  -177,  -177,  -177,   -74,  -177,
    -177,  -177,   163,  -177,   160,  -177,   158,  -177,   161,   164,
     167,  -177,  -177,  -177,    78,  -177,  -177,     7,  -177,   193,
    -177,  -177,  -177,  -177,  -177,  -177,  -177,  -177,   -59,   116,
    -177,    31,  -177,    35,  -177,   141,    63,  -176,    61,  -177,
     166,   -39,  -122,  -177,  -177,   133,  -177,   -41
  };

  const short
  parser::yydefgoto_[] =
  {
      -1,     2,     3,     4,     5,    20,   107,   108,   109,   110,
     111,   112,    21,    22,    23,    24,   129,   130,   131,    25,
      26,    27,    28,    64,    65,    66,   200,    67,   241,    68,
     345,    69,    32,    33,    34,    35,    70,    71,    72,    73,
      36,   115,    74,    75,    76,    77,    78,    79,    80,    81,
      82,   159,    83,   162,    84,   167,    85,   170,    86,    87,
      88,    89,    90,   177,    91,   297,   139,   291,   292,    92,
      93,    94,    95,    96,    97,    98,    99,   100,   101,   217,
     218,   262,   263,   244,   245,   116,   204,   184,   208,   185,
     186,   123,   124,   205,   266,   209,   117,   125
  };

  const short
  parser::yytable_[] =
  {
      31,   127,   114,   214,   142,   214,   265,   155,    41,    37,
     136,   137,    37,    38,    39,    40,    37,    41,   143,    37,
      41,    37,    37,    41,    37,    41,     6,    42,    43,    44,
     113,   211,    37,    41,    50,   288,   135,    50,    19,   191,
      50,   212,    50,   235,   236,   289,   202,    29,    19,   264,
      50,    30,   140,     7,   132,   140,   215,   182,   140,   295,
     140,   301,   227,   141,   174,   128,   228,   216,   140,    52,
      53,     1,    63,   246,   247,    63,     9,   189,    63,    29,
      63,   154,   283,    30,    10,   250,   213,   195,   284,   175,
     176,   201,   121,   120,   180,   121,   179,    37,   121,    52,
      53,   181,   183,   183,   183,   174,   126,   178,    11,    29,
      47,   122,   219,    30,   122,    41,   233,   122,   234,   196,
     203,   207,   118,   240,   242,   133,   141,   197,    37,   121,
     175,   176,   206,    48,   333,   138,   306,   141,   237,   132,
     141,   248,   307,   338,   223,    49,   308,   121,   122,   156,
     157,   158,   309,   260,    52,    53,    54,    55,    56,   154,
     216,   343,   154,   272,    29,   119,   122,   154,    30,   150,
     154,   154,   154,   154,   151,   283,   152,   141,   324,   120,
     153,   319,   183,   141,   144,   146,   325,   229,   145,   147,
     279,   230,   134,   227,   280,   304,   275,   228,   310,   305,
     287,   326,   311,   141,   143,   327,   141,   141,   148,   149,
     207,   141,   299,   300,   171,   290,   172,   214,   231,   141,
      37,   206,   141,   141,   173,    48,   210,   141,   192,   141,
     243,   190,   132,   163,   164,   165,   166,    49,   160,   161,
     312,   313,   314,   315,    51,   222,    52,    53,    54,    55,
      56,   238,   168,   169,   249,   257,    29,    37,    41,   261,
      30,   267,   221,    59,   198,   199,    60,    61,   224,   187,
     188,   225,   258,   259,   268,    62,   330,   322,   242,   203,
     260,   278,   269,   207,   281,   282,   270,   339,   141,   286,
     141,   271,   273,   274,   206,   277,   191,   320,   328,   329,
     296,   298,   335,   342,   346,   302,   347,   303,   334,   351,
     183,     8,   194,    46,   344,   220,   294,   349,   344,   316,
     350,   340,   349,   341,   290,   251,   141,   252,   253,   154,
     226,   336,   254,    37,    41,   293,   255,   276,    48,   332,
     256,   331,   317,   285,   318,     0,   102,   103,   104,   105,
      49,    50,     0,     0,     0,     0,     0,    51,     0,    52,
      53,    54,    55,    56,     0,     0,   321,     0,   323,    57,
       0,     0,     0,    30,   106,     0,    59,     0,     0,    60,
      61,     0,    37,    41,   243,     0,   261,    48,    62,    63,
       0,     0,     0,     0,     0,   102,   103,   104,   105,    49,
      50,     0,     0,     0,   337,     0,    51,     0,    52,    53,
      54,    55,    56,     0,     0,    37,    41,     0,    57,     0,
      48,     0,    30,   193,     0,    59,     0,     0,    60,    61,
       0,     0,    49,    50,     0,     0,     0,    62,    63,    51,
       0,    52,    53,    54,    55,    56,     0,     0,    37,    41,
       0,    57,    58,    48,     0,    30,     0,     0,    59,     0,
       0,    60,    61,     0,     0,    49,    50,     0,     0,     0,
      62,    63,    51,     0,    52,    53,    54,    55,    56,     0,
       0,    37,    41,     0,    57,   232,    48,     0,    30,     0,
       0,    59,     0,     0,    60,    61,     0,     0,    49,    50,
       0,     0,     0,    62,    63,    51,     0,    52,    53,    54,
      55,    56,     0,     0,    37,    41,     0,    57,   239,    48,
       0,    30,     0,     0,    59,     0,     0,    60,    61,     0,
       0,    49,    50,     0,     0,     0,    62,    63,    51,     0,
      52,    53,    54,    55,    56,     0,     0,    37,    41,     0,
      57,     0,    48,     0,    30,   348,     0,    59,     0,     0,
      60,    61,     0,     0,    49,    50,     0,     0,     0,    62,
      63,    51,     0,    52,    53,    54,    55,    56,     0,     0,
      37,    41,     0,    57,     0,    48,     0,    30,   352,     0,
      59,     0,     0,    60,    61,     0,     0,    49,    50,     0,
       0,     0,    62,    63,    51,     0,    52,    53,    54,    55,
      56,     0,     0,     0,     0,     0,    57,    12,     1,     0,
      30,     0,     0,    59,    13,    14,    60,    61,     0,     0,
       0,    15,     0,    16,    17,    62,    63,    12,     1,    18,
       0,     0,     0,     0,    13,    14,     0,     0,     0,     0,
       0,    15,     0,    16,    17,    45,     0,     0,     0,    18
  };

  const short
  parser::yycheck_[] =
  {
      12,    42,    30,   125,    63,   127,   182,    81,     4,     3,
      49,    50,     3,    13,    14,    15,     3,     4,    34,     3,
       4,     3,     3,     4,     3,     4,     3,    16,    17,    18,
      30,    45,     3,     4,    21,    45,    48,    21,    10,    55,
      21,    55,    21,     3,     4,    55,    40,    39,    20,    40,
      21,    43,    39,     0,    43,    39,    43,    39,    39,    40,
      39,    40,    36,    63,    38,    61,    40,   126,    39,    29,
      30,     7,    59,     3,     4,    59,    37,   105,    59,    39,
      59,    81,    36,    43,    43,   159,   125,   115,    42,    63,
      64,   119,    41,    39,    34,    41,    96,     3,    41,    29,
      30,    41,   102,   103,   104,    38,    55,    96,    37,    39,
      37,    60,    55,    43,    60,     4,   144,    60,   146,    36,
     120,   121,    15,   151,   152,    51,   126,    44,     3,    41,
      63,    64,   121,     8,   310,    57,    36,   137,   150,   128,
     140,   153,    42,    55,   133,    20,    36,    41,    60,    46,
      47,    48,    42,   181,    29,    30,    31,    32,    33,   159,
     219,    55,   162,   191,    39,    15,    60,   167,    43,    34,
     170,   171,   172,   173,    39,    36,    41,   177,    36,    39,
      45,    42,   182,   183,    36,    36,    44,    36,    40,    40,
      36,    40,    37,    36,    40,    36,   196,    40,    36,    40,
     212,    36,    40,   203,    34,    40,   206,   207,    32,    33,
     210,   211,   224,   225,    24,   215,    25,   339,   140,   219,
       3,   210,   222,   223,    26,     8,    41,   227,    44,   229,
     152,    37,   221,    51,    52,    53,    54,    20,    49,    50,
     268,   269,   270,   271,    27,    39,    29,    30,    31,    32,
      33,   150,    56,    57,   153,   177,    39,     3,     4,   181,
      43,   183,    61,    46,    32,    33,    49,    50,     9,   103,
     104,    55,    34,     3,    55,    58,   304,   289,   306,   279,
     308,   203,    55,   283,   206,   207,    55,   328,   288,   211,
     290,    55,    37,    44,   283,    22,    55,    55,    53,    10,
     222,   223,    55,    43,    43,   227,    37,   229,   320,    37,
     310,     3,   115,    20,   342,   128,   221,   345,   346,   277,
     346,   329,   350,   335,   324,   162,   326,   167,   170,   329,
     137,   324,   171,     3,     4,   219,   172,   196,     8,   308,
     173,   306,   279,   210,   283,    -1,    16,    17,    18,    19,
      20,    21,    -1,    -1,    -1,    -1,    -1,    27,    -1,    29,
      30,    31,    32,    33,    -1,    -1,   288,    -1,   290,    39,
      -1,    -1,    -1,    43,    44,    -1,    46,    -1,    -1,    49,
      50,    -1,     3,     4,   306,    -1,   308,     8,    58,    59,
      -1,    -1,    -1,    -1,    -1,    16,    17,    18,    19,    20,
      21,    -1,    -1,    -1,   326,    -1,    27,    -1,    29,    30,
      31,    32,    33,    -1,    -1,     3,     4,    -1,    39,    -1,
       8,    -1,    43,    44,    -1,    46,    -1,    -1,    49,    50,
      -1,    -1,    20,    21,    -1,    -1,    -1,    58,    59,    27,
      -1,    29,    30,    31,    32,    33,    -1,    -1,     3,     4,
      -1,    39,    40,     8,    -1,    43,    -1,    -1,    46,    -1,
      -1,    49,    50,    -1,    -1,    20,    21,    -1,    -1,    -1,
      58,    59,    27,    -1,    29,    30,    31,    32,    33,    -1,
      -1,     3,     4,    -1,    39,    40,     8,    -1,    43,    -1,
      -1,    46,    -1,    -1,    49,    50,    -1,    -1,    20,    21,
      -1,    -1,    -1,    58,    59,    27,    -1,    29,    30,    31,
      32,    33,    -1,    -1,     3,     4,    -1,    39,    40,     8,
      -1,    43,    -1,    -1,    46,    -1,    -1,    49,    50,    -1,
      -1,    20,    21,    -1,    -1,    -1,    58,    59,    27,    -1,
      29,    30,    31,    32,    33,    -1,    -1,     3,     4,    -1,
      39,    -1,     8,    -1,    43,    44,    -1,    46,    -1,    -1,
      49,    50,    -1,    -1,    20,    21,    -1,    -1,    -1,    58,
      59,    27,    -1,    29,    30,    31,    32,    33,    -1,    -1,
       3,     4,    -1,    39,    -1,     8,    -1,    43,    44,    -1,
      46,    -1,    -1,    49,    50,    -1,    -1,    20,    21,    -1,
      -1,    -1,    58,    59,    27,    -1,    29,    30,    31,    32,
      33,    -1,    -1,    -1,    -1,    -1,    39,     6,     7,    -1,
      43,    -1,    -1,    46,    13,    14,    49,    50,    -1,    -1,
      -1,    20,    -1,    22,    23,    58,    59,     6,     7,    28,
      -1,    -1,    -1,    -1,    13,    14,    -1,    -1,    -1,    -1,
      -1,    20,    -1,    22,    23,    44,    -1,    -1,    -1,    28
  };

  const unsigned char
  parser::yystos_[] =
  {
       0,     7,    67,    68,    69,    70,     3,     0,    69,    37,
      43,    37,     6,    13,    14,    20,    22,    23,    28,    70,
      71,    78,    79,    80,    81,    85,    86,    87,    88,    39,
      43,    97,    98,    99,   100,   101,   106,     3,    90,    90,
      90,     4,    89,    89,    89,    44,    78,    37,     8,    20,
      21,    27,    29,    30,    31,    32,    33,    39,    40,    46,
      49,    50,    58,    59,    89,    90,    91,    93,    95,    97,
     102,   103,   104,   105,   108,   109,   110,   111,   112,   113,
     114,   115,   116,   118,   120,   122,   124,   125,   126,   127,
     128,   130,   135,   136,   137,   138,   139,   140,   141,   142,
     143,   144,    16,    17,    18,    19,    44,    72,    73,    74,
      75,    76,    77,    90,    93,   107,   151,   162,    15,    15,
      39,    41,    60,   157,   158,   163,    55,   163,    61,    82,
      83,    84,    89,    51,    37,    97,   157,   157,   130,   132,
      39,    90,   144,    34,    36,    40,    36,    40,    32,    33,
      34,    39,    41,    45,    90,   114,    46,    47,    48,   117,
      49,    50,   119,    51,    52,    53,    54,   121,    56,    57,
     123,    24,    25,    26,    38,    63,    64,   129,    89,    90,
      34,    41,    39,    90,   153,   155,   156,   156,   156,    93,
      37,    55,    44,    44,    72,    93,    36,    44,    32,    33,
      92,    93,    40,    90,   152,   159,    89,    90,   154,   161,
      41,    45,    55,   157,   158,    43,   144,   145,   146,    55,
      83,    61,    39,    89,     9,    55,   135,    36,    40,    36,
      40,   130,    40,    93,    93,     3,     4,    97,   103,    40,
      93,    94,    93,   130,   149,   150,     3,     4,    97,   103,
     114,   118,   120,   122,   124,   125,   126,   130,    34,     3,
      93,   130,   147,   148,    40,   153,   160,   130,    55,    55,
      55,    55,    93,    37,    44,    90,   151,    22,   130,    36,
      40,   130,   130,    36,    42,   161,   130,    97,    45,    55,
      90,   133,   134,   145,    84,    40,   130,   131,   130,    97,
      97,    40,   130,   130,    36,    40,    36,    42,    36,    42,
      36,    40,    93,    93,    93,    93,    92,   152,   154,    42,
      55,   130,    97,   130,    36,    44,    36,    40,    53,    10,
      93,   149,   147,   153,    97,    55,   133,   130,    55,   163,
     102,    97,    43,    55,    93,    96,    43,    37,    44,    93,
      96,    37,    44
  };

  const unsigned char
  parser::yyr1_[] =
  {
       0,    66,    67,    68,    68,    69,    70,    71,    71,    72,
      72,    72,    72,    72,    73,    74,    75,    76,    77,    78,
      78,    78,    78,    78,    78,    78,    78,    79,    79,    79,
      79,    80,    80,    81,    82,    82,    83,    83,    84,    84,
      84,    85,    85,    86,    87,    88,    89,    90,    91,    92,
      92,    93,    94,    94,    95,    95,    96,    96,    97,    97,
      97,    97,    97,    98,    98,    99,   100,   100,   101,   102,
     102,   102,   102,   102,   102,   102,   103,   103,   104,   104,
     104,   104,   105,   105,   106,   106,   106,   107,   107,   108,
     109,   109,   109,   109,   109,   110,   111,   111,   112,   112,
     112,   112,   113,   113,   113,   113,   114,   114,   115,   115,
     115,   115,   115,   116,   117,   117,   117,   118,   118,   119,
     119,   120,   120,   121,   121,   121,   121,   122,   122,   123,
     123,   124,   124,   125,   125,   126,   126,   127,   127,   128,
     128,   129,   129,   129,   130,   131,   131,   132,   132,   133,
     134,   134,   135,   135,   135,   135,   135,   136,   137,   137,
     138,   139,   139,   140,   141,   141,   141,   142,   143,   144,
     144,   145,   145,   146,   147,   147,   148,   148,   149,   149,
     150,   150,   151,   152,   153,   153,   154,   154,   155,   155,
     156,   156,   157,   157,   158,   158,   159,   159,   160,   160,
     161,   161,   162,   162,   163,   163
  };

  const signed char
  parser::yyr2_[] =
  {
       0,     2,     1,     2,     3,     1,     5,     2,     3,     1,
       1,     1,     1,     1,     4,     4,     4,     4,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     7,     8,     5,
       6,     4,     5,     3,     2,     1,     1,     3,     1,     3,
       4,    10,    11,     2,     6,     4,     1,     1,     1,     1,
       1,     1,     1,     3,     3,     3,     2,     3,     1,     1,
       1,     1,     1,     2,     2,     3,     4,     3,     3,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       2,     2,     4,     6,     3,     3,     4,     2,     3,     4,
       1,     1,     1,     1,     1,     4,     3,     4,     3,     3,
       3,     3,     3,     3,     3,     3,     1,     2,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     3,     1,
       1,     1,     3,     1,     1,     1,     1,     1,     3,     1,
       1,     1,     3,     1,     3,     1,     3,     1,     3,     1,
       3,     1,     1,     1,     1,     1,     3,     3,     3,     2,
       1,     3,     1,     1,     1,     1,     1,     3,     4,     3,
       2,     2,     3,     3,     1,     1,     1,     4,     3,     1,
       2,     1,     1,     3,     1,     1,     1,     3,     1,     1,
       1,     3,     3,     2,     2,     1,     2,     2,     3,     2,
       1,     1,     3,     2,     3,     4,     1,     3,     1,     3,
       1,     3,     1,     3,     1,     2
  };


#if YYDEBUG
  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a YYNTOKENS, nonterminals.
  const char*
  const parser::yytname_[] =
  {
  "\"end of file\"", "error", "\"invalid token\"", "\"<val_id>\"",
  "\"<TypeId>\"", "\"<__42__>\"", "\"using\"", "\"mod\"", "\"if\"",
  "\"then\"", "\"else\"", "\"match\"", "\"with\"", "\"import\"",
  "\"extern\"", "\"from\"", "\"const\"", "\"let\"", "\"var\"", "\"set\"",
  "\"fn\"", "\"Fn\"", "\"type\"", "\"enum\"", "\"and\"", "\"xor\"",
  "\"or\"", "\"not\"", "\"typeclass\"", "\"42\"", "\"0x2a\"", "\"4.2\"",
  "\"\\\"dq-string-literal\\\"\"", "\"'sq-string-literal'\"", "\".\"",
  "\":\"", "\",\"", "\";\"", "\"::\"", "\"(\"", "\")\"", "\"[\"", "\"]\"",
  "\"{\"", "\"}\"", "\"->\"", "\"*\"", "\"/\"", "\"%\"", "\"+\"", "\"-\"",
  "\"<\"", "\"<=\"", "\">\"", "\">=\"", "\"=\"", "\"==\"", "\"!=\"",
  "\"^\"", "\"&\"", "\"!\"", "\"|\"", "\"EOS\"", "\":<\"", "\">:\"",
  "\"<null>\"", "$accept", "script", "scriptContent", "scriptContentStmt",
  "mod_stmt", "moduleContent", "chainPrefixStmt", "constStmt", "letStmt",
  "varStmt", "setStmt", "discardStmt", "moduleContentStmt", "fn_stmt",
  "type_stmt", "enum_stmt", "enum_field_pl", "unprefixed_enum_field_pl",
  "enum_field", "typeclass_stmt", "using_stmt", "importStmt",
  "extern_stmt", "tid", "vid", "floatl", "stringl", "expr", "expr_cl1",
  "expr_cl2", "expr_sl", "parenExpr", "unitExpr", "vparenExpr",
  "vtupleExpr", "vstructExpr", "primaryExpr", "int_expr", "stringls",
  "ifThenElseExpr", "chainExpr", "chainPrefix", "vlambdaExpr",
  "postfixExpr", "tcall_exp", "vcall_exp", "dot_name_exp", "dotIxExpr",
  "unaryExpr", "unaryOp", "binaryExpr", "mulBinaryOp", "mulBinaryExpr",
  "addBinaryOp", "addBinaryExpr", "cmpBinaryOp", "cmpBinaryExpr",
  "eqBinaryOp", "eqBinaryExpr", "andBinaryExpr", "xorBinaryExpr",
  "orBinaryExpr", "type_query_exp", "type_query_op", "typespec",
  "typespec_cl1", "typespec_cl2", "structTypespecField",
  "structTypespecField_cl", "primaryTypespec", "parenTypespec",
  "tupleTypespec", "mod_prefix_tid", "mod_prefix", "fn_typespec",
  "postfixTypespec", "ttcall", "tdot", "unaryTypespec", "long_typespec",
  "structTypespec", "ttarg", "ttarg_cl", "vtarg", "vtarg_cl",
  "vstructExprField", "vpatternField", "lpatternField", "tpatternField",
  "lpattern", "lpattern_naked", "vpattern", "tpattern", "vpatternField_cl",
  "lpatternField_cl", "tpatternField_cl", "vstructExprField_cl",
  "tpattern_seq", YY_NULLPTR
  };
#endif


#if YYDEBUG
  const short
  parser::yyrline_[] =
  {
       0,   293,   293,   296,   297,   300,   308,   311,   312,   320,
     321,   322,   323,   324,   327,   330,   333,   336,   339,   343,
     344,   345,   346,   347,   348,   349,   350,   353,   354,   355,
     356,   359,   360,   363,   366,   367,   370,   371,   374,   375,
     376,   379,   382,   388,   392,   396,   403,   404,   406,   409,
     410,   417,   420,   421,   424,   425,   428,   429,   433,   434,
     435,   436,   437,   440,   441,   444,   447,   448,   451,   454,
     455,   456,   457,   458,   459,   460,   463,   464,   467,   468,
     469,   470,   473,   474,   477,   478,   479,   482,   483,   486,
     490,   491,   492,   493,   494,   497,   500,   501,   504,   505,
     506,   507,   510,   511,   512,   513,   517,   518,   521,   522,
     523,   524,   525,   529,   532,   533,   534,   537,   538,   541,
     542,   545,   546,   549,   550,   551,   552,   555,   556,   559,
     560,   563,   564,   567,   568,   571,   572,   575,   576,   580,
     581,   584,   585,   586,   594,   597,   598,   601,   602,   606,
     609,   610,   614,   615,   616,   617,   618,   621,   624,   625,
     628,   631,   632,   635,   639,   640,   641,   644,   646,   650,
     651,   655,   656,   659,   663,   664,   667,   668,   673,   674,
     677,   678,   686,   689,   692,   693,   696,   697,   701,   702,
     705,   706,   709,   710,   713,   714,   718,   719,   722,   723,
     726,   727,   730,   731,   735,   736
  };

  void
  parser::yy_stack_print_ () const
  {
    *yycdebug_ << "Stack now";
    for (stack_type::const_iterator
           i = yystack_.begin (),
           i_end = yystack_.end ();
         i != i_end; ++i)
      *yycdebug_ << ' ' << int (i->state);
    *yycdebug_ << '\n';
  }

  void
  parser::yy_reduce_print_ (int yyrule) const
  {
    int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    // Print the symbols being reduced, and their result.
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
               << " (line " << yylno << "):\n";
    // The symbols being reduced.
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
                       yystack_[(yynrhs) - (yyi + 1)]);
  }
#endif // YYDEBUG

  parser::symbol_kind_type
  parser::yytranslate_ (int t)
  {
    // YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to
    // TOKEN-NUM as returned by yylex.
    static
    const signed char
    translate_table[] =
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
      65
    };
    // Last valid token kind.
    const int code_max = 320;

    if (t <= 0)
      return symbol_kind::S_YYEOF;
    else if (t <= code_max)
      return YY_CAST (symbol_kind_type, translate_table[t]);
    else
      return symbol_kind::S_YYUNDEF;
  }

#line 33 "parser.yy"
} } // pdm::parser
#line 3936 "parser.tab.cc"

#line 739 "parser.yy"


#include <stdio.h>

// #include "lexer.h"

// #include "useful.h"
// #include "source.h"
// #include "ast.h"

// RawAstNode* ParseScript(Source* source) {
//     // TODO: implement me from `parser.c`
//     AstNode* out = NULL;
//     int result = yyparse(source, &out);
//     if (result == 0) {
//         return out;
//     } else {
//         COMPILER_ERROR("yyparse == 0 <=> error");
//         return NULL;
//     }
// }

namespace pdm::parser {

    ast::Script* parse_script(ast::Manager* manager, source::Source* source) {
        Lexer lexer;
        if (!lexer.setup(source)) {
            return nullptr;
        }

        ast::Script* out = nullptr;
        pdm::parser::parser yyparser{source, &lexer, manager, &out};
        // yyparser.set_debug_level(pdm::DEBUG);
        int result = yyparser.parse();
        if (result == 0) {
            return out;
        } else {
            return nullptr;
        }
    }

}

int yylex(pdm::parser::parser::semantic_type* semval, pdm::source::Loc* llocp, pdm::source::Source* source, pdm::parser::Lexer* lexer) {
    // see:
    // https://www.gnu.org/software/bison/manual/html_node/Calling-Convention.html
    
    pdm::parser::TokenInfo info;

    llocp->source(source);
    int tk = lexer->lex_one_token(&info, llocp);
    semval->as<pdm::parser::TokenInfo>() = info;

    if (pdm::DEBUG) {
        // DebugPrintToken("YYLEX:", tk, info, llocp);
    }
    if (tk == Tk::EOS) {
        return Tk::YYEOF;
    } else {
        return tk;
    }
}
