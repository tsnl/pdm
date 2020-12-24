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

#line 22 "parser.yy"
namespace pdm { namespace parser {
#line 137 "parser.tab.cc"

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
      case symbol_kind::S_DINT_LIT: // "42"
      case symbol_kind::S_XINT_LIT: // "0x2a"
      case symbol_kind::S_FLOAT_LIT: // "4.2"
      case symbol_kind::S_DQSTRING_LIT: // "\"dq-string-literal\""
      case symbol_kind::S_SQSTRING_LIT: // "'sq-string-literal'"
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

      case symbol_kind::S_VID: // "<val_id>"
      case symbol_kind::S_TID: // "<TypeId>"
      case symbol_kind::S_HOLE: // "<__42__>"
      case symbol_kind::S_tid: // tid
      case symbol_kind::S_vid: // vid
      case symbol_kind::S_floatl: // floatl
      case symbol_kind::S_stringl: // stringl
        value.copy< pdm::parser::TokenInfo > (YY_MOVE (that.value));
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
        value.copy< std::vector<pdm::ast::Script*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_moduleContent: // moduleContent
      case symbol_kind::S_chainPrefix: // chainPrefix
        value.copy< std::vector<pdm::ast::Stmt*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stringls: // stringls
        value.copy< std::vector<pdm::ast::StringExp::Piece*> > (YY_MOVE (that.value));
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
      case symbol_kind::S_DINT_LIT: // "42"
      case symbol_kind::S_XINT_LIT: // "0x2a"
      case symbol_kind::S_FLOAT_LIT: // "4.2"
      case symbol_kind::S_DQSTRING_LIT: // "\"dq-string-literal\""
      case symbol_kind::S_SQSTRING_LIT: // "'sq-string-literal'"
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

      case symbol_kind::S_VID: // "<val_id>"
      case symbol_kind::S_TID: // "<TypeId>"
      case symbol_kind::S_HOLE: // "<__42__>"
      case symbol_kind::S_tid: // tid
      case symbol_kind::S_vid: // vid
      case symbol_kind::S_floatl: // floatl
      case symbol_kind::S_stringl: // stringl
        value.move< pdm::parser::TokenInfo > (YY_MOVE (s.value));
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
        value.move< std::vector<pdm::ast::Script*> > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_moduleContent: // moduleContent
      case symbol_kind::S_chainPrefix: // chainPrefix
        value.move< std::vector<pdm::ast::Stmt*> > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_stringls: // stringls
        value.move< std::vector<pdm::ast::StringExp::Piece*> > (YY_MOVE (s.value));
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
      case symbol_kind::S_DINT_LIT: // "42"
      case symbol_kind::S_XINT_LIT: // "0x2a"
      case symbol_kind::S_FLOAT_LIT: // "4.2"
      case symbol_kind::S_DQSTRING_LIT: // "\"dq-string-literal\""
      case symbol_kind::S_SQSTRING_LIT: // "'sq-string-literal'"
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

      case symbol_kind::S_VID: // "<val_id>"
      case symbol_kind::S_TID: // "<TypeId>"
      case symbol_kind::S_HOLE: // "<__42__>"
      case symbol_kind::S_tid: // tid
      case symbol_kind::S_vid: // vid
      case symbol_kind::S_floatl: // floatl
      case symbol_kind::S_stringl: // stringl
        value.YY_MOVE_OR_COPY< pdm::parser::TokenInfo > (YY_MOVE (that.value));
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
        value.YY_MOVE_OR_COPY< std::vector<pdm::ast::Script*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_moduleContent: // moduleContent
      case symbol_kind::S_chainPrefix: // chainPrefix
        value.YY_MOVE_OR_COPY< std::vector<pdm::ast::Stmt*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stringls: // stringls
        value.YY_MOVE_OR_COPY< std::vector<pdm::ast::StringExp::Piece*> > (YY_MOVE (that.value));
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
      case symbol_kind::S_DINT_LIT: // "42"
      case symbol_kind::S_XINT_LIT: // "0x2a"
      case symbol_kind::S_FLOAT_LIT: // "4.2"
      case symbol_kind::S_DQSTRING_LIT: // "\"dq-string-literal\""
      case symbol_kind::S_SQSTRING_LIT: // "'sq-string-literal'"
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

      case symbol_kind::S_VID: // "<val_id>"
      case symbol_kind::S_TID: // "<TypeId>"
      case symbol_kind::S_HOLE: // "<__42__>"
      case symbol_kind::S_tid: // tid
      case symbol_kind::S_vid: // vid
      case symbol_kind::S_floatl: // floatl
      case symbol_kind::S_stringl: // stringl
        value.move< pdm::parser::TokenInfo > (YY_MOVE (that.value));
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
        value.move< std::vector<pdm::ast::Script*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_moduleContent: // moduleContent
      case symbol_kind::S_chainPrefix: // chainPrefix
        value.move< std::vector<pdm::ast::Stmt*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stringls: // stringls
        value.move< std::vector<pdm::ast::StringExp::Piece*> > (YY_MOVE (that.value));
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
      case symbol_kind::S_DINT_LIT: // "42"
      case symbol_kind::S_XINT_LIT: // "0x2a"
      case symbol_kind::S_FLOAT_LIT: // "4.2"
      case symbol_kind::S_DQSTRING_LIT: // "\"dq-string-literal\""
      case symbol_kind::S_SQSTRING_LIT: // "'sq-string-literal'"
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

      case symbol_kind::S_VID: // "<val_id>"
      case symbol_kind::S_TID: // "<TypeId>"
      case symbol_kind::S_HOLE: // "<__42__>"
      case symbol_kind::S_tid: // tid
      case symbol_kind::S_vid: // vid
      case symbol_kind::S_floatl: // floatl
      case symbol_kind::S_stringl: // stringl
        value.copy< pdm::parser::TokenInfo > (that.value);
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
        value.copy< std::vector<pdm::ast::Script*> > (that.value);
        break;

      case symbol_kind::S_moduleContent: // moduleContent
      case symbol_kind::S_chainPrefix: // chainPrefix
        value.copy< std::vector<pdm::ast::Stmt*> > (that.value);
        break;

      case symbol_kind::S_stringls: // stringls
        value.copy< std::vector<pdm::ast::StringExp::Piece*> > (that.value);
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
      case symbol_kind::S_DINT_LIT: // "42"
      case symbol_kind::S_XINT_LIT: // "0x2a"
      case symbol_kind::S_FLOAT_LIT: // "4.2"
      case symbol_kind::S_DQSTRING_LIT: // "\"dq-string-literal\""
      case symbol_kind::S_SQSTRING_LIT: // "'sq-string-literal'"
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

      case symbol_kind::S_VID: // "<val_id>"
      case symbol_kind::S_TID: // "<TypeId>"
      case symbol_kind::S_HOLE: // "<__42__>"
      case symbol_kind::S_tid: // tid
      case symbol_kind::S_vid: // vid
      case symbol_kind::S_floatl: // floatl
      case symbol_kind::S_stringl: // stringl
        value.move< pdm::parser::TokenInfo > (that.value);
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
        value.move< std::vector<pdm::ast::Script*> > (that.value);
        break;

      case symbol_kind::S_moduleContent: // moduleContent
      case symbol_kind::S_chainPrefix: // chainPrefix
        value.move< std::vector<pdm::ast::Stmt*> > (that.value);
        break;

      case symbol_kind::S_stringls: // stringls
        value.move< std::vector<pdm::ast::StringExp::Piece*> > (that.value);
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
      case symbol_kind::S_DINT_LIT: // "42"
      case symbol_kind::S_XINT_LIT: // "0x2a"
      case symbol_kind::S_FLOAT_LIT: // "4.2"
      case symbol_kind::S_DQSTRING_LIT: // "\"dq-string-literal\""
      case symbol_kind::S_SQSTRING_LIT: // "'sq-string-literal'"
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

      case symbol_kind::S_VID: // "<val_id>"
      case symbol_kind::S_TID: // "<TypeId>"
      case symbol_kind::S_HOLE: // "<__42__>"
      case symbol_kind::S_tid: // tid
      case symbol_kind::S_vid: // vid
      case symbol_kind::S_floatl: // floatl
      case symbol_kind::S_stringl: // stringl
        yylhs.value.emplace< pdm::parser::TokenInfo > ();
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
        yylhs.value.emplace< std::vector<pdm::ast::Script*> > ();
        break;

      case symbol_kind::S_moduleContent: // moduleContent
      case symbol_kind::S_chainPrefix: // chainPrefix
        yylhs.value.emplace< std::vector<pdm::ast::Stmt*> > ();
        break;

      case symbol_kind::S_stringls: // stringls
        yylhs.value.emplace< std::vector<pdm::ast::StringExp::Piece*> > ();
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
#line 301 "parser.yy"
                    { yylhs.value.as < pdm::ast::Script* > () = mgr->new_script(source, yylhs.location, std::move(yystack_[0].value.as < std::vector<pdm::ast::Script*> > ())); *returnp = yylhs.value.as < pdm::ast::Script* > (); }
#line 1995 "parser.tab.cc"
    break;

  case 3: // scriptContent: scriptContentStmt ";"
#line 304 "parser.yy"
                                                    { yylhs.value.as < std::vector<pdm::ast::Script*> > ().push_back(yystack_[1].value.as < pdm::ast::Stmt* > ()); }
#line 2001 "parser.tab.cc"
    break;

  case 4: // scriptContent: scriptContent scriptContentStmt ";"
#line 305 "parser.yy"
                                                    { yylhs.value.as < std::vector<pdm::ast::Script*> > () = std::move(yystack_[2].value.as < std::vector<pdm::ast::Script*> > ()); yylhs.value.as < std::vector<pdm::ast::Script*> > ().push_back(yystack_[1].value.as < pdm::ast::Stmt* > ()); }
#line 2007 "parser.tab.cc"
    break;

  case 5: // scriptContentStmt: mod_stmt
#line 308 "parser.yy"
      { yylhs.value.as < pdm::ast::Stmt* > () = yystack_[0].value.as < pdm::ast::Stmt* > (); }
#line 2013 "parser.tab.cc"
    break;

  case 6: // mod_stmt: "mod" "<val_id>" "{" moduleContent "}"
#line 316 "parser.yy"
                                                { yylhs.value.as < pdm::ast::Stmt* > () = mgr->new_mod_stmt(yylhs.location, yystack_[3].value.as < pdm::parser::TokenInfo > ().ID_intstr, std::move(yystack_[1].value.as < std::vector<pdm::ast::Stmt*> > ())); }
#line 2019 "parser.tab.cc"
    break;

  case 7: // moduleContent: moduleContentStmt ";"
#line 319 "parser.yy"
                                                    { yylhs.value.as < std::vector<pdm::ast::Stmt*> > ().push_back(yystack_[1].value.as < pdm::ast::Stmt* > ()); }
#line 2025 "parser.tab.cc"
    break;

  case 8: // moduleContent: moduleContent moduleContentStmt ";"
#line 320 "parser.yy"
                                                    { yylhs.value.as < std::vector<pdm::ast::Stmt*> > () = std::move(yystack_[2].value.as < std::vector<pdm::ast::Stmt*> > ()); yylhs.value.as < std::vector<pdm::ast::Stmt*> > ().push_back(yystack_[1].value.as < pdm::ast::Stmt* > ()); }
#line 2031 "parser.tab.cc"
    break;

  case 9: // chainPrefixStmt: constStmt
#line 328 "parser.yy"
      { yylhs.value.as < pdm::ast::Stmt* > () = yystack_[0].value.as < pdm::ast::Stmt* > (); }
#line 2037 "parser.tab.cc"
    break;

  case 10: // chainPrefixStmt: letStmt
#line 329 "parser.yy"
      { yylhs.value.as < pdm::ast::Stmt* > () = yystack_[0].value.as < pdm::ast::Stmt* > (); }
#line 2043 "parser.tab.cc"
    break;

  case 11: // chainPrefixStmt: varStmt
#line 330 "parser.yy"
      { yylhs.value.as < pdm::ast::Stmt* > () = yystack_[0].value.as < pdm::ast::Stmt* > (); }
#line 2049 "parser.tab.cc"
    break;

  case 12: // chainPrefixStmt: setStmt
#line 331 "parser.yy"
      { yylhs.value.as < pdm::ast::Stmt* > () = yystack_[0].value.as < pdm::ast::Stmt* > (); }
#line 2055 "parser.tab.cc"
    break;

  case 13: // chainPrefixStmt: discardStmt
#line 332 "parser.yy"
      { yylhs.value.as < pdm::ast::Stmt* > () = yystack_[0].value.as < pdm::ast::Stmt* > (); }
#line 2061 "parser.tab.cc"
    break;

  case 14: // constStmt: "const" lpattern_naked "=" expr
#line 335 "parser.yy"
                                        { yylhs.value.as < pdm::ast::Stmt* > () = mgr->new_const_stmt(yylhs.location, yystack_[2].value.as < pdm::ast::LPattern* > (), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2067 "parser.tab.cc"
    break;

  case 15: // letStmt: "let" lpattern_naked "=" expr
#line 338 "parser.yy"
                                        { yylhs.value.as < pdm::ast::Stmt* > () = mgr->new_let_stmt(yylhs.location, yystack_[2].value.as < pdm::ast::LPattern* > (), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2073 "parser.tab.cc"
    break;

  case 16: // varStmt: "var" lpattern_naked "=" expr
#line 341 "parser.yy"
                                        { yylhs.value.as < pdm::ast::Stmt* > () = mgr->new_var_stmt(yylhs.location, yystack_[2].value.as < pdm::ast::LPattern* > (), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2079 "parser.tab.cc"
    break;

  case 17: // setStmt: "set" expr "=" expr
#line 344 "parser.yy"
                              { yylhs.value.as < pdm::ast::Stmt* > () = mgr->new_set_stmt(yylhs.location, yystack_[2].value.as < pdm::ast::Exp* > (), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2085 "parser.tab.cc"
    break;

  case 18: // discardStmt: expr
#line 347 "parser.yy"
              { yylhs.value.as < pdm::ast::Stmt* > () = mgr->new_discard_stmt(yylhs.location, yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2091 "parser.tab.cc"
    break;

  case 19: // moduleContentStmt: fn_stmt
#line 351 "parser.yy"
      { yylhs.value.as < pdm::ast::Stmt* > () = yystack_[0].value.as < pdm::ast::Stmt* > (); }
#line 2097 "parser.tab.cc"
    break;

  case 20: // moduleContentStmt: type_stmt
#line 352 "parser.yy"
      { yylhs.value.as < pdm::ast::Stmt* > () = yystack_[0].value.as < pdm::ast::Stmt* > (); }
#line 2103 "parser.tab.cc"
    break;

  case 21: // moduleContentStmt: enum_stmt
#line 353 "parser.yy"
      { yylhs.value.as < pdm::ast::Stmt* > () = yystack_[0].value.as < pdm::ast::Stmt* > (); }
#line 2109 "parser.tab.cc"
    break;

  case 22: // moduleContentStmt: typeclass_stmt
#line 354 "parser.yy"
      { yylhs.value.as < pdm::ast::Stmt* > () = yystack_[0].value.as < pdm::ast::Stmt* > (); }
#line 2115 "parser.tab.cc"
    break;

  case 23: // moduleContentStmt: importStmt
#line 355 "parser.yy"
      { yylhs.value.as < pdm::ast::Stmt* > () = yystack_[0].value.as < pdm::ast::Stmt* > (); }
#line 2121 "parser.tab.cc"
    break;

  case 24: // moduleContentStmt: mod_stmt
#line 356 "parser.yy"
      { yylhs.value.as < pdm::ast::Stmt* > () = yystack_[0].value.as < pdm::ast::Stmt* > (); }
#line 2127 "parser.tab.cc"
    break;

  case 25: // moduleContentStmt: using_stmt
#line 357 "parser.yy"
      { yylhs.value.as < pdm::ast::Stmt* > () = yystack_[0].value.as < pdm::ast::Stmt* > (); }
#line 2133 "parser.tab.cc"
    break;

  case 26: // fn_stmt: "fn" vid vpattern "->" typespec "=" parenExpr
#line 360 "parser.yy"
                                                                      { yylhs.value.as < pdm::ast::Stmt* > () = mgr->new_fn_stmt(yylhs.location, yystack_[5].value.as < pdm::parser::TokenInfo > ().ID_intstr, std::move({}), yystack_[4].value.as < pdm::ast::VPattern* > (), yystack_[2].value.as < pdm::ast::Typespec* > (), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2139 "parser.tab.cc"
    break;

  case 27: // fn_stmt: "fn" vid tpattern_seq vpattern "->" typespec "=" parenExpr
#line 361 "parser.yy"
                                                                      { yylhs.value.as < pdm::ast::Stmt* > () = mgr->new_fn_stmt(yylhs.location, yystack_[6].value.as < pdm::parser::TokenInfo > ().ID_intstr, std::move(yystack_[5].value.as < std::vector<pdm::ast::TPattern*> > ()), yystack_[4].value.as < pdm::ast::VPattern* > (), yystack_[2].value.as < pdm::ast::Typespec* > (), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2145 "parser.tab.cc"
    break;

  case 28: // fn_stmt: "fn" vid vpattern "=" parenExpr
#line 362 "parser.yy"
                                                                      { yylhs.value.as < pdm::ast::Stmt* > () = mgr->new_fn_stmt(yylhs.location, yystack_[3].value.as < pdm::parser::TokenInfo > ().ID_intstr, std::move({}), yystack_[2].value.as < pdm::ast::VPattern* > (), nullptr, yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2151 "parser.tab.cc"
    break;

  case 29: // fn_stmt: "fn" vid tpattern_seq vpattern "=" parenExpr
#line 363 "parser.yy"
                                                                      { yylhs.value.as < pdm::ast::Stmt* > () = mgr->new_fn_stmt(yylhs.location, yystack_[4].value.as < pdm::parser::TokenInfo > ().ID_intstr, std::move(yystack_[3].value.as < std::vector<pdm::ast::TPattern*> > ()), yystack_[2].value.as < pdm::ast::VPattern* > (), nullptr, yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2157 "parser.tab.cc"
    break;

  case 30: // type_stmt: "type" tid "=" long_typespec
#line 366 "parser.yy"
                                                    { yylhs.value.as < pdm::ast::Stmt* > () = mgr->new_type_stmt(yylhs.location, yystack_[2].value.as < pdm::parser::TokenInfo > ().ID_intstr, std::move({}), yystack_[0].value.as < pdm::ast::Typespec* > ()); }
#line 2163 "parser.tab.cc"
    break;

  case 31: // type_stmt: "type" tid tpattern_seq "=" long_typespec
#line 367 "parser.yy"
                                                    { yylhs.value.as < pdm::ast::Stmt* > () = mgr->new_type_stmt(yylhs.location, yystack_[3].value.as < pdm::parser::TokenInfo > ().ID_intstr, std::move(yystack_[2].value.as < std::vector<pdm::ast::TPattern*> > ()), yystack_[0].value.as < pdm::ast::Typespec* > ()); }
#line 2169 "parser.tab.cc"
    break;

  case 32: // enum_stmt: "enum" tid enum_field_pl
#line 370 "parser.yy"
                                    { yylhs.value.as < pdm::ast::Stmt* > () = mgr->new_enum_stmt(yylhs.location, yystack_[1].value.as < pdm::parser::TokenInfo > ().ID_intstr, std::move(yystack_[0].value.as < std::vector<pdm::ast::EnumStmt::Field*> > ())); }
#line 2175 "parser.tab.cc"
    break;

  case 33: // enum_field_pl: "|" unprefixed_enum_field_pl
#line 373 "parser.yy"
                                    { yylhs.value.as < std::vector<pdm::ast::EnumStmt::Field*> > () = std::move(yystack_[0].value.as < std::vector<pdm::ast::EnumStmt::Field*> > ()); }
#line 2181 "parser.tab.cc"
    break;

  case 34: // enum_field_pl: unprefixed_enum_field_pl
#line 374 "parser.yy"
                                    { yylhs.value.as < std::vector<pdm::ast::EnumStmt::Field*> > () = std::move(yystack_[0].value.as < std::vector<pdm::ast::EnumStmt::Field*> > ()); }
#line 2187 "parser.tab.cc"
    break;

  case 35: // unprefixed_enum_field_pl: enum_field
#line 377 "parser.yy"
                                                { yylhs.value.as < std::vector<pdm::ast::EnumStmt::Field*> > ().push_back(yystack_[0].value.as < pdm::ast::EnumStmt::Field* > ()); }
#line 2193 "parser.tab.cc"
    break;

  case 36: // unprefixed_enum_field_pl: unprefixed_enum_field_pl "|" enum_field
#line 378 "parser.yy"
                                                { yylhs.value.as < std::vector<pdm::ast::EnumStmt::Field*> > () = std::move(yystack_[2].value.as < std::vector<pdm::ast::EnumStmt::Field*> > ()); yylhs.value.as < std::vector<pdm::ast::EnumStmt::Field*> > ().push_back(yystack_[0].value.as < pdm::ast::EnumStmt::Field* > ()); }
#line 2199 "parser.tab.cc"
    break;

  case 37: // enum_field: tid
#line 381 "parser.yy"
                                     { yylhs.value.as < pdm::ast::EnumStmt::Field* > () = mgr->new_enum_stmt_field(yystack_[0].value.as < pdm::parser::TokenInfo > ().ID_intstr, std::move({}), false); }
#line 2205 "parser.tab.cc"
    break;

  case 38: // enum_field: tid "(" ")"
#line 382 "parser.yy"
                                     { yylhs.value.as < pdm::ast::EnumStmt::Field* > () = mgr->new_enum_stmt_field(yystack_[2].value.as < pdm::parser::TokenInfo > ().ID_intstr, std::move({}), true); }
#line 2211 "parser.tab.cc"
    break;

  case 39: // enum_field: tid "(" typespec_cl1 ")"
#line 383 "parser.yy"
                                     { yylhs.value.as < pdm::ast::EnumStmt::Field* > () = mgr->new_enum_stmt_field(yystack_[3].value.as < pdm::parser::TokenInfo > ().ID_intstr, std::move(yystack_[1].value.as < std::vector<pdm::ast::Typespec*> > ()), true); }
#line 2217 "parser.tab.cc"
    break;

  case 40: // typeclass_stmt: "typeclass" tid "<" tid typespec ">" "=" "{" expr_sl "}"
#line 386 "parser.yy"
                                                                                        { 
        yylhs.value.as < pdm::ast::Stmt* > () = mgr->new_typeclass_stmt(yylhs.location, yystack_[8].value.as < pdm::parser::TokenInfo > ().ID_intstr, yystack_[6].value.as < pdm::parser::TokenInfo > ().ID_intstr, yystack_[5].value.as < pdm::ast::Typespec* > (), std::move({}), std::move(yystack_[1].value.as < std::vector<pdm::ast::Exp*> > ())); 
      }
#line 2225 "parser.tab.cc"
    break;

  case 41: // typeclass_stmt: "typeclass" tid "<" tid typespec ">" tpattern_seq "=" "{" expr_sl "}"
#line 389 "parser.yy"
                                                                                        { 
        yylhs.value.as < pdm::ast::Stmt* > () = mgr->new_typeclass_stmt(yylhs.location, yystack_[9].value.as < pdm::parser::TokenInfo > ().ID_intstr, yystack_[7].value.as < pdm::parser::TokenInfo > ().ID_intstr, yystack_[6].value.as < pdm::ast::Typespec* > (), std::move(yystack_[4].value.as < std::vector<pdm::ast::TPattern*> > ()), std::move(yystack_[1].value.as < std::vector<pdm::ast::Exp*> > ())); 
      }
#line 2233 "parser.tab.cc"
    break;

  case 42: // using_stmt: "using" parenExpr
#line 395 "parser.yy"
                         { yylhs.value.as < pdm::ast::Stmt* > () = mgr->new_using_stmt(yylhs.location, yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2239 "parser.tab.cc"
    break;

  case 43: // importStmt: "import" vid "from" expr "type" expr
#line 399 "parser.yy"
                                                 { yylhs.value.as < pdm::ast::Stmt* > () = mgr->new_import_stmt(yylhs.location, yystack_[4].value.as < pdm::parser::TokenInfo > ().ID_intstr, yystack_[2].value.as < pdm::ast::Exp* > (), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2245 "parser.tab.cc"
    break;

  case 44: // tid: "<TypeId>"
#line 406 "parser.yy"
     { yylhs.value.as < pdm::parser::TokenInfo > () = yystack_[0].value.as < pdm::parser::TokenInfo > (); }
#line 2251 "parser.tab.cc"
    break;

  case 45: // vid: "<val_id>"
#line 407 "parser.yy"
     { yylhs.value.as < pdm::parser::TokenInfo > () = yystack_[0].value.as < pdm::parser::TokenInfo > (); }
#line 2257 "parser.tab.cc"
    break;

  case 49: // expr: binaryExpr
#line 420 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2263 "parser.tab.cc"
    break;

  case 50: // expr_cl1: expr
#line 423 "parser.yy"
                             { yylhs.value.as < std::vector<pdm::ast::Exp*> > ().push_back(yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2269 "parser.tab.cc"
    break;

  case 51: // expr_cl1: expr_cl1 "," expr
#line 424 "parser.yy"
                             { yylhs.value.as < std::vector<pdm::ast::Exp*> > () = std::move(yystack_[2].value.as < std::vector<pdm::ast::Exp*> > ()); yylhs.value.as < std::vector<pdm::ast::Exp*> > ().push_back(yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2275 "parser.tab.cc"
    break;

  case 52: // expr_cl2: expr "," expr
#line 427 "parser.yy"
                             { yylhs.value.as < std::vector<pdm::ast::Exp*> > ().reserve(2); yylhs.value.as < std::vector<pdm::ast::Exp*> > ().push_back(yystack_[2].value.as < pdm::ast::Exp* > ()); yylhs.value.as < std::vector<pdm::ast::Exp*> > ().push_back(yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2281 "parser.tab.cc"
    break;

  case 53: // expr_cl2: expr_cl2 "," expr
#line 428 "parser.yy"
                             { yylhs.value.as < std::vector<pdm::ast::Exp*> > () = std::move(yystack_[2].value.as < std::vector<pdm::ast::Exp*> > ()); yylhs.value.as < std::vector<pdm::ast::Exp*> > ().push_back(yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2287 "parser.tab.cc"
    break;

  case 54: // expr_sl: expr ";"
#line 431 "parser.yy"
                             { yylhs.value.as < std::vector<pdm::ast::Exp*> > ().push_back(yystack_[1].value.as < pdm::ast::Exp* > ()); }
#line 2293 "parser.tab.cc"
    break;

  case 55: // expr_sl: expr_sl expr ";"
#line 432 "parser.yy"
                             { yylhs.value.as < std::vector<pdm::ast::Exp*> > () = std::move(yystack_[2].value.as < std::vector<pdm::ast::Exp*> > ()); yylhs.value.as < std::vector<pdm::ast::Exp*> > ().push_back(yystack_[1].value.as < pdm::ast::Exp* > ()); }
#line 2299 "parser.tab.cc"
    break;

  case 56: // parenExpr: unitExpr
#line 436 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2305 "parser.tab.cc"
    break;

  case 57: // parenExpr: vparenExpr
#line 437 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2311 "parser.tab.cc"
    break;

  case 58: // parenExpr: vtupleExpr
#line 438 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2317 "parser.tab.cc"
    break;

  case 59: // parenExpr: vstructExpr
#line 439 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2323 "parser.tab.cc"
    break;

  case 60: // parenExpr: chainExpr
#line 440 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2329 "parser.tab.cc"
    break;

  case 63: // primaryExpr: parenExpr
#line 447 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2335 "parser.tab.cc"
    break;

  case 64: // primaryExpr: vid
#line 448 "parser.yy"
                     { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_id_exp(yylhs.location, yystack_[0].value.as < pdm::parser::TokenInfo > ().ID_intstr); }
#line 2341 "parser.tab.cc"
    break;

  case 65: // primaryExpr: int_expr
#line 449 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2347 "parser.tab.cc"
    break;

  case 66: // primaryExpr: floatl
#line 450 "parser.yy"
                     { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_float_exp(yylhs.location, yystack_[0].value.as < pdm::parser::TokenInfo > ().Float); }
#line 2353 "parser.tab.cc"
    break;

  case 67: // primaryExpr: stringls
#line 451 "parser.yy"
                     { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_string_exp(yylhs.location, std::move(yystack_[0].value.as < std::vector<pdm::ast::StringExp::Piece*> > ())); }
#line 2359 "parser.tab.cc"
    break;

  case 68: // primaryExpr: ifThenElseExpr
#line 452 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2365 "parser.tab.cc"
    break;

  case 69: // primaryExpr: vlambdaExpr
#line 453 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2371 "parser.tab.cc"
    break;

  case 70: // int_expr: "42"
#line 456 "parser.yy"
                { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_int_exp(yylhs.location, yystack_[0].value.as < TokenInfo > ().Int, IntExp::Base::Dec); }
#line 2377 "parser.tab.cc"
    break;

  case 71: // int_expr: "0x2a"
#line 457 "parser.yy"
                { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_int_exp(yylhs.location, yystack_[0].value.as < TokenInfo > ().Int, IntExp::Base::Hex); }
#line 2383 "parser.tab.cc"
    break;

  case 72: // stringls: stringl
#line 460 "parser.yy"
                        { yylhs.value.as < std::vector<pdm::ast::StringExp::Piece*> > ().emplace_back(yystack_[0].location, *yystack_[0].value.as < pdm::parser::TokenInfo > ().String_utf8string); }
#line 2389 "parser.tab.cc"
    break;

  case 73: // stringls: stringls stringl
#line 461 "parser.yy"
                        { yylhs.value.as < std::vector<pdm::ast::StringExp::Piece*> > () = std::move(yystack_[1].value.as < std::vector<pdm::ast::StringExp::Piece*> > ()); yylhs.value.as < std::vector<pdm::ast::StringExp::Piece*> > ().emplace_back(yystack_[0].location, yystack_[0].value.as < pdm::parser::TokenInfo > ().String_utf8string); }
#line 2395 "parser.tab.cc"
    break;

  case 74: // vparenExpr: "(" expr ")"
#line 464 "parser.yy"
                          { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_paren_exp(yylhs.location, yystack_[1].value.as < pdm::ast::Exp* > ()); }
#line 2401 "parser.tab.cc"
    break;

  case 75: // vtupleExpr: "(" expr "," ")"
#line 467 "parser.yy"
                                   { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_tuple_exp(yylhs.location, std::move(std::vector(1,yystack_[2].value.as < pdm::ast::Exp* > ()))); }
#line 2407 "parser.tab.cc"
    break;

  case 76: // vtupleExpr: "(" expr_cl2 ")"
#line 468 "parser.yy"
                                   { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_tuple_exp(yylhs.location, std::move(yystack_[1].value.as < std::vector<pdm::ast::Exp*> > ())); }
#line 2413 "parser.tab.cc"
    break;

  case 77: // vstructExpr: "{" vstructExprField_cl "}"
#line 471 "parser.yy"
                                            { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_struct_exp(yylhs.location, std::move(yystack_[1].value.as < std::vector<pdm::ast::StructExp::Field*> > ())); }
#line 2419 "parser.tab.cc"
    break;

  case 78: // ifThenElseExpr: "if" parenExpr "then" parenExpr
#line 474 "parser.yy"
                                                             { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_if_exp(yylhs.location, yystack_[2].value.as < pdm::ast::Exp* > (), yystack_[0].value.as < pdm::ast::Exp* > (), nullptr); }
#line 2425 "parser.tab.cc"
    break;

  case 79: // ifThenElseExpr: "if" parenExpr "then" parenExpr "else" primaryExpr
#line 475 "parser.yy"
                                                             { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_if_exp(yylhs.location, yystack_[4].value.as < pdm::ast::Exp* > (), yystack_[2].value.as < pdm::ast::Exp* > (), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2431 "parser.tab.cc"
    break;

  case 80: // chainExpr: "{" expr "}"
#line 478 "parser.yy"
                                          { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_chain_exp(yylhs.location, std::move({}), yystack_[1].value.as < pdm::ast::Exp* > ()); }
#line 2437 "parser.tab.cc"
    break;

  case 81: // chainExpr: "{" chainPrefix "}"
#line 479 "parser.yy"
                                          { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_chain_exp(yylhs.location, std::move(yystack_[1].value.as < std::vector<pdm::ast::Stmt*> > ()), nullptr); }
#line 2443 "parser.tab.cc"
    break;

  case 82: // chainExpr: "{" chainPrefix expr "}"
#line 480 "parser.yy"
                                          { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_chain_exp(yylhs.location, std::move(yystack_[2].value.as < std::vector<pdm::ast::Stmt*> > ()), yystack_[1].value.as < pdm::ast::Exp* > ()); }
#line 2449 "parser.tab.cc"
    break;

  case 83: // chainPrefix: chainPrefixStmt ";"
#line 483 "parser.yy"
                                             { yylhs.value.as < std::vector<pdm::ast::Stmt*> > ().push_back(yystack_[1].value.as < pdm::ast::Stmt* > ()); }
#line 2455 "parser.tab.cc"
    break;

  case 84: // chainPrefix: chainPrefix chainPrefixStmt ";"
#line 484 "parser.yy"
                                             { yylhs.value.as < std::vector<pdm::ast::Stmt*> > () = std::move(yystack_[2].value.as < std::vector<pdm::ast::Stmt*> > ()); yylhs.value.as < std::vector<pdm::ast::Stmt*> > ().push_back(yystack_[1].value.as < pdm::ast::Stmt* > ()); }
#line 2461 "parser.tab.cc"
    break;

  case 85: // vlambdaExpr: "fn" lpattern "=" parenExpr
#line 487 "parser.yy"
                                      { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_lambda_exp(yylhs.location, yystack_[2].value.as < pdm::ast::LPattern* > (), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2467 "parser.tab.cc"
    break;

  case 86: // postfixExpr: primaryExpr
#line 491 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2473 "parser.tab.cc"
    break;

  case 87: // postfixExpr: vtcallExpr
#line 492 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2479 "parser.tab.cc"
    break;

  case 88: // postfixExpr: vvcallExpr
#line 493 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2485 "parser.tab.cc"
    break;

  case 89: // postfixExpr: dotNmExpr
#line 494 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2491 "parser.tab.cc"
    break;

  case 90: // postfixExpr: dotIxExpr
#line 495 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2497 "parser.tab.cc"
    break;

  case 91: // vtcallExpr: postfixExpr "[" vtarg_cl "]"
#line 498 "parser.yy"
                                          { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_tcall_exp(yylhs.location, yystack_[3].value.as < pdm::ast::Exp* > (), std::move(yystack_[1].value.as < std::vector<pdm::ast::TArg*> > ())); }
#line 2503 "parser.tab.cc"
    break;

  case 92: // vvcallExpr: postfixExpr "(" ")"
#line 501 "parser.yy"
                                           { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_vcall_exp(yylhs.location, yystack_[2].value.as < pdm::ast::Exp* > (), std::move(std::vector<ast::Exp*>{})); }
#line 2509 "parser.tab.cc"
    break;

  case 93: // vvcallExpr: postfixExpr "(" expr_cl1 ")"
#line 502 "parser.yy"
                                           { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_vcall_exp(yylhs.location, yystack_[3].value.as < pdm::ast::Exp* > (), std::move(yystack_[1].value.as < std::vector<pdm::ast::Exp*> > ())); }
#line 2515 "parser.tab.cc"
    break;

  case 94: // dotNmExpr: postfixExpr "." "<val_id>"
#line 505 "parser.yy"
                            { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_dot_name_exp(yylhs.location, yystack_[2].value.as < pdm::ast::Exp* > (), yystack_[0].value.as < pdm::parser::TokenInfo > ().ID_intstr, ast::DotNameExp::RhsHint::LhsStruct); }
#line 2521 "parser.tab.cc"
    break;

  case 95: // dotNmExpr: postfixExpr "." "<TypeId>"
#line 506 "parser.yy"
                            { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_dot_name_exp(yylhs.location, yystack_[2].value.as < pdm::ast::Exp* > (), yystack_[0].value.as < pdm::parser::TokenInfo > ().ID_intstr, ast::DotNameExp::RhsHint::LhsEnum); }
#line 2527 "parser.tab.cc"
    break;

  case 96: // dotIxExpr: postfixExpr "." int_expr
#line 509 "parser.yy"
                                            { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_dot_index_exp(yylhs.location, yystack_[2].value.as < pdm::ast::Exp* > (), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2533 "parser.tab.cc"
    break;

  case 97: // dotIxExpr: postfixExpr "." "(" expr ")"
#line 510 "parser.yy"
                                            { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_dot_index_exp(yylhs.location, yystack_[4].value.as < pdm::ast::Exp* > (), yystack_[1].value.as < pdm::ast::Exp* > ()); }
#line 2539 "parser.tab.cc"
    break;

  case 98: // unaryExpr: postfixExpr
#line 514 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2545 "parser.tab.cc"
    break;

  case 99: // unaryExpr: unaryOp unaryExpr
#line 515 "parser.yy"
                            { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_unary_exp(yylhs.location, yystack_[1].value.as < pdm::ast::UnaryOperator > (), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2551 "parser.tab.cc"
    break;

  case 100: // unaryOp: "+"
#line 518 "parser.yy"
                 { yylhs.value.as < pdm::ast::UnaryOperator > () = ast::UnaryOperator::Plus; }
#line 2557 "parser.tab.cc"
    break;

  case 101: // unaryOp: "-"
#line 519 "parser.yy"
                 { yylhs.value.as < pdm::ast::UnaryOperator > () = ast::UnaryOperator::Minus; }
#line 2563 "parser.tab.cc"
    break;

  case 102: // unaryOp: "*"
#line 520 "parser.yy"
                 { yylhs.value.as < pdm::ast::UnaryOperator > () = ast::UnaryOperator::DeRef; }
#line 2569 "parser.tab.cc"
    break;

  case 103: // unaryOp: "^"
#line 521 "parser.yy"
                 { yylhs.value.as < pdm::ast::UnaryOperator > () = ast::UnaryOperator::GetRef; }
#line 2575 "parser.tab.cc"
    break;

  case 104: // unaryOp: "not"
#line 522 "parser.yy"
                 { yylhs.value.as < pdm::ast::UnaryOperator > () = ast::UnaryOperator::Not; }
#line 2581 "parser.tab.cc"
    break;

  case 105: // binaryExpr: orBinaryExpr
#line 526 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2587 "parser.tab.cc"
    break;

  case 106: // mulBinaryOp: "*"
#line 529 "parser.yy"
                 { yylhs.value.as < pdm::ast::BinaryOperator > () = ast::BinaryOperator::Mul; }
#line 2593 "parser.tab.cc"
    break;

  case 107: // mulBinaryOp: "/"
#line 530 "parser.yy"
                 { yylhs.value.as < pdm::ast::BinaryOperator > () = ast::BinaryOperator::Div; }
#line 2599 "parser.tab.cc"
    break;

  case 108: // mulBinaryOp: "%"
#line 531 "parser.yy"
                 { yylhs.value.as < pdm::ast::BinaryOperator > () = ast::BinaryOperator::Rem; }
#line 2605 "parser.tab.cc"
    break;

  case 109: // mulBinaryExpr: unaryExpr
#line 534 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2611 "parser.tab.cc"
    break;

  case 110: // mulBinaryExpr: mulBinaryExpr mulBinaryOp unaryExpr
#line 535 "parser.yy"
                                            { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_binary_exp(yylhs.location, yystack_[1].value.as < pdm::ast::BinaryOperator > (), yystack_[2].value.as < pdm::ast::Exp* > (), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2617 "parser.tab.cc"
    break;

  case 111: // addBinaryOp: "+"
#line 538 "parser.yy"
             { yylhs.value.as < pdm::ast::BinaryOperator > () = ast::BinaryOperator::Add; }
#line 2623 "parser.tab.cc"
    break;

  case 112: // addBinaryOp: "-"
#line 539 "parser.yy"
             { yylhs.value.as < pdm::ast::BinaryOperator > () = ast::BinaryOperator::Subtract; }
#line 2629 "parser.tab.cc"
    break;

  case 113: // addBinaryExpr: mulBinaryExpr
#line 542 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2635 "parser.tab.cc"
    break;

  case 114: // addBinaryExpr: addBinaryExpr addBinaryOp mulBinaryExpr
#line 543 "parser.yy"
                                                { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_binary_exp(yylhs.location, yystack_[1].value.as < pdm::ast::BinaryOperator > (), yystack_[2].value.as < pdm::ast::Exp* > (), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2641 "parser.tab.cc"
    break;

  case 115: // cmpBinaryOp: "<"
#line 546 "parser.yy"
                { yylhs.value.as < pdm::ast::BinaryOperator > () = BOP_LTHAN; }
#line 2647 "parser.tab.cc"
    break;

  case 116: // cmpBinaryOp: "<="
#line 547 "parser.yy"
                { yylhs.value.as < pdm::ast::BinaryOperator > () = BOP_LETHAN; }
#line 2653 "parser.tab.cc"
    break;

  case 117: // cmpBinaryOp: ">"
#line 548 "parser.yy"
                { yylhs.value.as < pdm::ast::BinaryOperator > () = BOP_GTHAN; }
#line 2659 "parser.tab.cc"
    break;

  case 118: // cmpBinaryOp: ">="
#line 549 "parser.yy"
                { yylhs.value.as < pdm::ast::BinaryOperator > () = BOP_GETHAN; }
#line 2665 "parser.tab.cc"
    break;

  case 119: // cmpBinaryExpr: addBinaryExpr
#line 552 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2671 "parser.tab.cc"
    break;

  case 120: // cmpBinaryExpr: cmpBinaryExpr cmpBinaryOp addBinaryExpr
#line 553 "parser.yy"
                                                { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_binary_exp(yylhs.location, yystack_[1].value.as < pdm::ast::BinaryOperator > (), yystack_[2].value.as < pdm::ast::Exp* > (), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2677 "parser.tab.cc"
    break;

  case 121: // eqBinaryOp: "=="
#line 556 "parser.yy"
                 { yylhs.value.as < pdm::ast::BinaryOperator > () = BOP_EQUALS; }
#line 2683 "parser.tab.cc"
    break;

  case 122: // eqBinaryOp: "!="
#line 557 "parser.yy"
                 { yylhs.value.as < pdm::ast::BinaryOperator > () = BOP_NEQUALS; }
#line 2689 "parser.tab.cc"
    break;

  case 123: // eqBinaryExpr: cmpBinaryExpr
#line 560 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2695 "parser.tab.cc"
    break;

  case 124: // eqBinaryExpr: eqBinaryExpr eqBinaryOp cmpBinaryExpr
#line 561 "parser.yy"
                                            { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_binary_exp(yylhs.location, yystack_[1].value.as < pdm::ast::BinaryOperator > (), yystack_[2].value.as < pdm::ast::Exp* > (), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2701 "parser.tab.cc"
    break;

  case 125: // andBinaryExpr: eqBinaryExpr
#line 564 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2707 "parser.tab.cc"
    break;

  case 126: // andBinaryExpr: andBinaryExpr "and" eqBinaryExpr
#line 565 "parser.yy"
                                         { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_binary_exp(yylhs.location, BOP_AND, yystack_[2].value.as < pdm::ast::Exp* > (), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2713 "parser.tab.cc"
    break;

  case 127: // xorBinaryExpr: andBinaryExpr
#line 568 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2719 "parser.tab.cc"
    break;

  case 128: // xorBinaryExpr: xorBinaryExpr "xor" andBinaryExpr
#line 569 "parser.yy"
                                         { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_binary_exp(yylhs.location, BOP_XOR, yystack_[2].value.as < pdm::ast::Exp* > (), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2725 "parser.tab.cc"
    break;

  case 129: // orBinaryExpr: xorBinaryExpr
#line 572 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2731 "parser.tab.cc"
    break;

  case 130: // orBinaryExpr: orBinaryExpr "or" xorBinaryExpr
#line 573 "parser.yy"
                                         { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_binary_exp(yylhs.location, BOP_OR, yystack_[2].value.as < pdm::ast::Exp* > (), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2737 "parser.tab.cc"
    break;

  case 131: // typespec: unaryTypespec
#line 581 "parser.yy"
      { yylhs.value.as < pdm::ast::Typespec* > () = yystack_[0].value.as < pdm::ast::Typespec* > (); }
#line 2743 "parser.tab.cc"
    break;

  case 132: // typespec_cl1: typespec
#line 584 "parser.yy"
                                  { yylhs.value.as < std::vector<pdm::ast::Typespec*> > ().push_back(yystack_[0].value.as < pdm::ast::Typespec* > ()); }
#line 2749 "parser.tab.cc"
    break;

  case 133: // typespec_cl1: typespec_cl1 "," typespec
#line 585 "parser.yy"
                                  { yylhs.value.as < std::vector<pdm::ast::Typespec*> > () = std::move(yystack_[2].value.as < std::vector<pdm::ast::Typespec*> > ()); yylhs.value.as < std::vector<pdm::ast::Typespec*> > ().push_back(yystack_[0].value.as < pdm::ast::Typespec* > ()); }
#line 2755 "parser.tab.cc"
    break;

  case 134: // typespec_cl2: typespec "," typespec
#line 588 "parser.yy"
                                  { yylhs.value.as < std::vector<pdm::ast::Typespec*> > ().reserve(2); yylhs.value.as < std::vector<pdm::ast::Typespec*> > ().push_back(yystack_[2].value.as < pdm::ast::Typespec* > ()); yylhs.value.as < std::vector<pdm::ast::Typespec*> > ().push_back(yystack_[0].value.as < pdm::ast::Typespec* > ()); }
#line 2761 "parser.tab.cc"
    break;

  case 135: // typespec_cl2: typespec_cl2 "," typespec
#line 589 "parser.yy"
                                  { yylhs.value.as < std::vector<pdm::ast::Typespec*> > () = std::move(yystack_[2].value.as < std::vector<pdm::ast::Typespec*> > ()); yylhs.value.as < std::vector<pdm::ast::Typespec*> > ().push_back(yystack_[0].value.as < pdm::ast::Typespec* > ()); }
#line 2767 "parser.tab.cc"
    break;

  case 136: // structTypespecField: vid typespec
#line 593 "parser.yy"
                                  { yylhs.value.as < pdm::ast::StructTypespec::Field* > () = mgr->new_struct_typespec_field(yylhs.location, yystack_[1].value.as < pdm::parser::TokenInfo > ().ID_intstr, yystack_[0].value.as < pdm::ast::Typespec* > ()); }
#line 2773 "parser.tab.cc"
    break;

  case 137: // structTypespecField_cl: structTypespecField
#line 596 "parser.yy"
                                                        { yylhs.value.as < std::vector<pdm::ast::StructTypespec::Field*> > ().push_back(yystack_[0].value.as < pdm::ast::StructTypespec::Field* > ()); }
#line 2779 "parser.tab.cc"
    break;

  case 138: // structTypespecField_cl: structTypespecField_cl "," structTypespecField
#line 597 "parser.yy"
                                                        { yylhs.value.as < std::vector<pdm::ast::StructTypespec::Field*> > () = std::move(yystack_[2].value.as < std::vector<pdm::ast::StructTypespec::Field*> > ()); yylhs.value.as < std::vector<pdm::ast::StructTypespec::Field*> > ().push_back(yystack_[0].value.as < pdm::ast::StructTypespec::Field* > ()); }
#line 2785 "parser.tab.cc"
    break;

  case 139: // primaryTypespec: tid
#line 601 "parser.yy"
                        { yylhs.value.as < pdm::ast::Typespec* > () = mgr->new_id_typespec(yylhs.location, yystack_[0].value.as < pdm::parser::TokenInfo > ().ID_intstr); }
#line 2791 "parser.tab.cc"
    break;

  case 140: // primaryTypespec: tupleTypespec
#line 602 "parser.yy"
      { yylhs.value.as < pdm::ast::Typespec* > () = yystack_[0].value.as < pdm::ast::Typespec* > (); }
#line 2797 "parser.tab.cc"
    break;

  case 141: // primaryTypespec: mod_prefix_tid
#line 603 "parser.yy"
      { yylhs.value.as < pdm::ast::Typespec* > () = yystack_[0].value.as < pdm::ast::Typespec* > (); }
#line 2803 "parser.tab.cc"
    break;

  case 142: // tupleTypespec: "(" typespec "," ")"
#line 606 "parser.yy"
                                    { yylhs.value.as < pdm::ast::Typespec* > () = mgr->new_tuple_typespec(yylhs.location, std::move(std::vector(1,yystack_[2].value.as < pdm::ast::Typespec* > ()))); }
#line 2809 "parser.tab.cc"
    break;

  case 143: // tupleTypespec: "(" typespec_cl2 ")"
#line 607 "parser.yy"
                                    { yylhs.value.as < pdm::ast::Typespec* > () = mgr->new_tuple_typespec(yylhs.location, std::move(yystack_[1].value.as < std::vector<pdm::ast::Typespec*> > ())); }
#line 2815 "parser.tab.cc"
    break;

  case 144: // mod_prefix_tid: mod_prefix tid
#line 610 "parser.yy"
                            { yylhs.value.as < pdm::ast::Typespec* > () = mgr->new_dot_name_typespec_with_mod_prefix(yylhs.location, std::move(yystack_[1].value.as < std::vector<pdm::intern::String> > ()), yystack_[0].value.as < pdm::parser::TokenInfo > ().ID_intstr); }
#line 2821 "parser.tab.cc"
    break;

  case 145: // mod_prefix: vid "."
#line 613 "parser.yy"
                            { yylhs.value.as < std::vector<pdm::intern::String> > ().push_back(yystack_[1].value.as < pdm::parser::TokenInfo > ().ID_intstr); }
#line 2827 "parser.tab.cc"
    break;

  case 146: // mod_prefix: mod_prefix vid "."
#line 614 "parser.yy"
                            { yylhs.value.as < std::vector<pdm::intern::String> > () = std::move(yystack_[2].value.as < std::vector<pdm::intern::String> > ()); }
#line 2833 "parser.tab.cc"
    break;

  case 147: // postfixTypespec: primaryTypespec
#line 618 "parser.yy"
      { yylhs.value.as < pdm::ast::Typespec* > () = yystack_[0].value.as < pdm::ast::Typespec* > (); }
#line 2839 "parser.tab.cc"
    break;

  case 148: // postfixTypespec: ttcall
#line 619 "parser.yy"
      { yylhs.value.as < pdm::ast::Typespec* > () = yystack_[0].value.as < pdm::ast::Typespec* > (); }
#line 2845 "parser.tab.cc"
    break;

  case 149: // postfixTypespec: tdot
#line 620 "parser.yy"
      { yylhs.value.as < pdm::ast::Typespec* > () = yystack_[0].value.as < pdm::ast::Typespec* > (); }
#line 2851 "parser.tab.cc"
    break;

  case 150: // ttcall: postfixTypespec "[" ttarg_cl "]"
#line 623 "parser.yy"
                                              { yylhs.value.as < pdm::ast::Typespec* > () = mgr->new_tcall_typespec(yylhs.location, yystack_[3].value.as < pdm::ast::Typespec* > (), std::move(yystack_[1].value.as < std::vector<pdm::ast::TArg*> > ())); }
#line 2857 "parser.tab.cc"
    break;

  case 151: // tdot: postfixTypespec "." "<val_id>"
#line 625 "parser.yy"
                                { yylhs.value.as < pdm::ast::Typespec* > () = mgr->new_dot_name_typespec_with_type_prefix(yylhs.location, yystack_[2].value.as < pdm::ast::Typespec* > (), yystack_[0].value.as < pdm::parser::TokenInfo > ().ID_intstr); }
#line 2863 "parser.tab.cc"
    break;

  case 152: // unaryTypespec: postfixTypespec
#line 629 "parser.yy"
      { yylhs.value.as < pdm::ast::Typespec* > () = yystack_[0].value.as < pdm::ast::Typespec* > (); }
#line 2869 "parser.tab.cc"
    break;

  case 153: // unaryTypespec: "&" unaryTypespec
#line 630 "parser.yy"
                                 { yylhs.value.as < pdm::ast::Typespec* > () = mgr->new_ptr_typespec(yylhs.location,yystack_[0].value.as < pdm::ast::Typespec* > ()); }
#line 2875 "parser.tab.cc"
    break;

  case 154: // long_typespec: unaryTypespec
#line 634 "parser.yy"
      { yylhs.value.as < pdm::ast::Typespec* > () = yystack_[0].value.as < pdm::ast::Typespec* > (); }
#line 2881 "parser.tab.cc"
    break;

  case 155: // long_typespec: structTypespec
#line 635 "parser.yy"
      { yylhs.value.as < pdm::ast::Typespec* > () = yystack_[0].value.as < pdm::ast::Typespec* > (); }
#line 2887 "parser.tab.cc"
    break;

  case 156: // structTypespec: "{" structTypespecField_cl "}"
#line 638 "parser.yy"
                                            { yylhs.value.as < pdm::ast::Typespec* > () = mgr->new_struct_typespec(yylhs.location, std::move(yystack_[1].value.as < std::vector<pdm::ast::StructTypespec::Field*> > ())); }
#line 2893 "parser.tab.cc"
    break;

  case 157: // ttarg: typespec
#line 642 "parser.yy"
                { yylhs.value.as < pdm::ast::TArg* > () = mgr->new_targ(yylhs.location, ) }
#line 2899 "parser.tab.cc"
    break;

  case 158: // ttarg: expr
#line 643 "parser.yy"
                { yylhs.value.as < pdm::ast::TArg* > () = NewAstVal2Type(yylhs.location,yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2905 "parser.tab.cc"
    break;

  case 159: // ttarg_cl: ttarg
#line 646 "parser.yy"
                                { yylhs.value.as < std::vector<pdm::ast::TArg*> > () = NULL; sb_push(yylhs.value.as < std::vector<pdm::ast::TArg*> > (),yystack_[0].value.as < pdm::ast::TArg* > ()); }
#line 2911 "parser.tab.cc"
    break;

  case 160: // ttarg_cl: ttarg_cl "," ttarg
#line 647 "parser.yy"
                             { yylhs.value.as < std::vector<pdm::ast::TArg*> > () = yystack_[2].value.as < std::vector<pdm::ast::TArg*> > (); sb_push(yylhs.value.as < std::vector<pdm::ast::TArg*> > (),yystack_[0].value.as < pdm::ast::TArg* > ()); }
#line 2917 "parser.tab.cc"
    break;

  case 161: // vtarg: typespec
#line 652 "parser.yy"
               { yylhs.value.as < pdm::ast::TArg* > () = NewAstType2Val(yylhs.location,yystack_[0].value.as < pdm::ast::Typespec* > ()); }
#line 2923 "parser.tab.cc"
    break;

  case 163: // vtarg_cl: vtarg
#line 656 "parser.yy"
                                { yylhs.value.as < std::vector<pdm::ast::TArg*> > () = NULL; sb_push(yylhs.value.as < std::vector<pdm::ast::TArg*> > (),yystack_[0].value.as < pdm::ast::TArg* > ()); }
#line 2929 "parser.tab.cc"
    break;

  case 164: // vtarg_cl: vtarg_cl "," vtarg
#line 657 "parser.yy"
                             { yylhs.value.as < std::vector<pdm::ast::TArg*> > () = yystack_[2].value.as < std::vector<pdm::ast::TArg*> > (); sb_push(yylhs.value.as < std::vector<pdm::ast::TArg*> > (),yystack_[0].value.as < pdm::ast::TArg* > ()); }
#line 2935 "parser.tab.cc"
    break;

  case 165: // vstructExprField: vid "=" expr
#line 665 "parser.yy"
                    { yylhs.value.as < pdm::ast::StructExp::Field* > () = mgr->new_struct_exp_field(yylhs.location, yystack_[2].value.as < pdm::parser::TokenInfo > ().ID_intstr, yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2941 "parser.tab.cc"
    break;

  case 166: // vpatternField: vid typespec
#line 668 "parser.yy"
                   { yylhs.value.as < pdm::ast::VPattern::Field* > () = mgr->new_vpattern_field(yylhs.location, yystack_[1].value.as < pdm::parser::TokenInfo > ().ID_intstr, yystack_[0].value.as < pdm::ast::Typespec* > ()); }
#line 2947 "parser.tab.cc"
    break;

  case 167: // lpatternField: vid typespec
#line 671 "parser.yy"
                    { yylhs.value.as < pdm::ast::LPattern::Field* > () = mgr->new_lpattern_field(yylhs.location, ast::LPattern::FieldKind::IdTypespecPair, yystack_[1].value.as < pdm::parser::TokenInfo > ().ID_intstr, yystack_[0].value.as < pdm::ast::Typespec* > ()); }
#line 2953 "parser.tab.cc"
    break;

  case 168: // lpatternField: vid
#line 672 "parser.yy"
                    { yylhs.value.as < pdm::ast::LPattern::Field* > () = mgr->new_lpattern_field(yylhs.location, ast::LPattern::FieldKind::IdSingleton, yystack_[0].value.as < pdm::parser::TokenInfo > ().ID_intstr); }
#line 2959 "parser.tab.cc"
    break;

  case 169: // tpatternField: vid typespec
#line 675 "parser.yy"
                    { yylhs.value.as < pdm::ast::TPattern::Field* > () = mgr->new_tpattern_field(yylhs.location, ast::TPattern::FieldKind::Val, yystack_[1].value.as < pdm::parser::TokenInfo > ().ID_intstr, yystack_[0].value.as < pdm::ast::Typespec* > ()); }
#line 2965 "parser.tab.cc"
    break;

  case 170: // tpatternField: tid typespec
#line 676 "parser.yy"
                    { yylhs.value.as < pdm::ast::TPattern::Field* > () = mgr->new_tpattern_field(yylhs.location, ast::TPattern::FieldKind::Type, yystack_[1].value.as < pdm::parser::TokenInfo > ().ID_intstr, yystack_[0].value.as < pdm::ast::Typespec* > ()); }
#line 2971 "parser.tab.cc"
    break;

  case 171: // lpattern: "(" lpatternField_cl ")"
#line 680 "parser.yy"
                                      { yylhs.value.as < pdm::ast::LPattern* > () = mgr->new_lpattern(yylhs.location, std::move(yystack_[1].value.as < std::vector<pdm::ast::LPattern::Field*> > ())); }
#line 2977 "parser.tab.cc"
    break;

  case 172: // lpattern: "(" ")"
#line 681 "parser.yy"
                                      { yylhs.value.as < pdm::ast::LPattern* > () = mgr->new_lpattern(yylhs.location, std::move(std::vector<ast::LPattern::Field*>{})); }
#line 2983 "parser.tab.cc"
    break;

  case 173: // lpattern_naked: lpatternField
#line 684 "parser.yy"
                                      { yylhs.value.as < pdm::ast::LPattern* > () = mgr->new_lpattern(yylhs.location, std::move(std::vector<ast::LPattern::Field*>{1,yystack_[0].value.as < pdm::ast::LPattern::Field* > ()})); }
#line 2989 "parser.tab.cc"
    break;

  case 174: // lpattern_naked: lpattern
#line 685 "parser.yy"
      { yylhs.value.as < pdm::ast::LPattern* > () = yystack_[0].value.as < pdm::ast::LPattern* > (); }
#line 2995 "parser.tab.cc"
    break;

  case 175: // vpattern: "(" vpatternField_cl ")"
#line 688 "parser.yy"
                                      { yylhs.value.as < pdm::ast::VPattern* > () = mgr->new_vpattern(yylhs.location, std::move(yystack_[1].value.as < std::vector<pdm::ast::VPattern::Field*> > ())); }
#line 3001 "parser.tab.cc"
    break;

  case 176: // vpattern: "(" ")"
#line 689 "parser.yy"
                                      { yylhs.value.as < pdm::ast::VPattern* > () = mgr->new_vpattern(yylhs.location, std::move(std::vector<ast::VPattern::Field*>{})); }
#line 3007 "parser.tab.cc"
    break;

  case 177: // tpattern: "[" tpatternField_cl "]"
#line 692 "parser.yy"
                                              { yylhs.value.as < pdm::ast::TPattern* > () = mgr->new_tpattern(yylhs.location, std::move(yystack_[1].value.as < std::vector<pdm::ast::TPattern::Field*> > ()), false); }
#line 3013 "parser.tab.cc"
    break;

  case 178: // tpattern: "!" "[" tpatternField_cl "]"
#line 693 "parser.yy"
                                              { yylhs.value.as < pdm::ast::TPattern* > () = mgr->new_tpattern(yylhs.location, std::move(std::vector<ast::TPattern::Field*>{}), true); }
#line 3019 "parser.tab.cc"
    break;

  case 179: // vpatternField_cl: vpatternField
#line 697 "parser.yy"
                                             { yylhs.value.as < std::vector<pdm::ast::VPattern::Field*> > ().push_back(yystack_[0].value.as < pdm::ast::VPattern::Field* > ()); }
#line 3025 "parser.tab.cc"
    break;

  case 180: // vpatternField_cl: vpatternField_cl "," vpatternField
#line 698 "parser.yy"
                                             { yylhs.value.as < std::vector<pdm::ast::VPattern::Field*> > () = std::move(yystack_[2].value.as < std::vector<pdm::ast::VPattern::Field*> > ()); yylhs.value.as < std::vector<pdm::ast::VPattern::Field*> > ().push_back(yystack_[0].value.as < pdm::ast::VPattern::Field* > ()); }
#line 3031 "parser.tab.cc"
    break;

  case 181: // lpatternField_cl: lpatternField
#line 701 "parser.yy"
                                             { yylhs.value.as < std::vector<pdm::ast::LPattern::Field*> > ().push_back(yystack_[0].value.as < pdm::ast::LPattern::Field* > ()); }
#line 3037 "parser.tab.cc"
    break;

  case 182: // lpatternField_cl: lpatternField_cl "," lpatternField
#line 702 "parser.yy"
                                             { yylhs.value.as < std::vector<pdm::ast::LPattern::Field*> > () = std::move(yystack_[2].value.as < std::vector<pdm::ast::LPattern::Field*> > ()); yylhs.value.as < std::vector<pdm::ast::LPattern::Field*> > ().push_back(yystack_[0].value.as < pdm::ast::LPattern::Field* > ()); }
#line 3043 "parser.tab.cc"
    break;

  case 183: // tpatternField_cl: tpatternField
#line 705 "parser.yy"
                                             { yylhs.value.as < std::vector<pdm::ast::TPattern::Field*> > ().push_back(yystack_[0].value.as < pdm::ast::TPattern::Field* > ()); }
#line 3049 "parser.tab.cc"
    break;

  case 184: // tpatternField_cl: tpatternField_cl "," tpatternField
#line 706 "parser.yy"
                                             { yylhs.value.as < std::vector<pdm::ast::TPattern::Field*> > () = std::move(yystack_[2].value.as < std::vector<pdm::ast::TPattern::Field*> > ()); yylhs.value.as < std::vector<pdm::ast::TPattern::Field*> > ().push_back(yystack_[0].value.as < pdm::ast::TPattern::Field* > ()); }
#line 3055 "parser.tab.cc"
    break;

  case 185: // vstructExprField_cl: vstructExprField
#line 709 "parser.yy"
                                                    { yylhs.value.as < std::vector<pdm::ast::StructExp::Field*> > ().push_back(yystack_[0].value.as < pdm::ast::StructExp::Field* > ()); }
#line 3061 "parser.tab.cc"
    break;

  case 186: // vstructExprField_cl: vstructExprField_cl "," vstructExprField
#line 710 "parser.yy"
                                                    { yylhs.value.as < std::vector<pdm::ast::StructExp::Field*> > () = std::move(yystack_[2].value.as < std::vector<pdm::ast::StructExp::Field*> > ()); yylhs.value.as < std::vector<pdm::ast::StructExp::Field*> > ().push_back(yystack_[0].value.as < pdm::ast::StructExp::Field* > ()); }
#line 3067 "parser.tab.cc"
    break;

  case 187: // tpattern_seq: tpattern
#line 714 "parser.yy"
                             { yylhs.value.as < std::vector<pdm::ast::TPattern*> > ().push_back(yystack_[0].value.as < pdm::ast::TPattern* > ()); }
#line 3073 "parser.tab.cc"
    break;

  case 188: // tpattern_seq: tpattern_seq tpattern
#line 715 "parser.yy"
                             { yylhs.value.as < std::vector<pdm::ast::TPattern*> > () = std::move(yystack_[1].value.as < std::vector<pdm::ast::TPattern*> > ()); yylhs.value.as < std::vector<pdm::ast::TPattern*> > ().push_back(yystack_[0].value.as < pdm::ast::TPattern* > ()); }
#line 3079 "parser.tab.cc"
    break;


#line 3083 "parser.tab.cc"

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





  const signed char parser::yypact_ninf_ = -113;

  const signed char parser::yytable_ninf_ = -1;

  const short
  parser::yypact_[] =
  {
       1,     7,    37,     1,    30,  -113,    38,  -113,    32,  -113,
     248,  -113,    93,    91,    91,    92,    92,    92,  -113,   129,
      64,  -113,  -113,  -113,  -113,  -113,  -113,   407,   342,  -113,
    -113,  -113,  -113,  -113,  -113,  -113,   107,   -18,  -113,    34,
       5,    58,  -113,   111,  -113,    93,   127,  -113,  -113,  -113,
    -113,  -113,  -113,  -113,  -113,  -113,  -113,  -113,  -113,  -113,
    -113,   122,   146,  -113,  -113,  -113,   102,  -113,  -113,   120,
    -113,  -113,  -113,  -113,  -113,   563,  -113,   180,    96,   226,
     124,   139,   144,   148,    17,    17,    17,   563,  -113,   160,
    -113,  -113,  -113,  -113,  -113,   151,   159,   377,  -113,   -11,
     563,     8,   214,   149,   -29,  -113,   -18,    45,    66,    92,
    -113,   171,  -113,   191,    92,  -113,   205,    12,   179,   439,
    -113,   563,  -113,  -113,    53,   471,   307,  -113,  -113,  -113,
    -113,   563,  -113,  -113,   563,  -113,  -113,  -113,  -113,   563,
    -113,  -113,   563,   563,   563,   563,    31,  -113,  -113,   181,
     183,   185,   187,  -113,   563,  -113,  -113,   198,   200,    91,
    -113,   225,  -113,    31,  -113,   147,    31,    31,  -113,    26,
     214,    31,    93,   -27,  -113,    31,    91,    31,  -113,   215,
    -113,  -113,  -113,   214,    -7,  -113,  -113,  -113,  -113,  -113,
      45,   171,    92,    71,    31,    93,  -113,  -113,   153,    93,
    -113,  -113,  -113,  -113,  -113,   563,  -113,  -113,  -113,   169,
      14,   215,  -113,  -113,  -113,  -113,    70,  -113,   180,    96,
     226,   124,   139,   144,  -113,   563,   563,   563,   563,  -113,
    -113,  -113,   151,  -113,   563,  -113,    91,  -113,  -113,  -113,
     214,  -113,    80,   193,  -113,    31,    93,   217,   177,    31,
    -113,    61,  -113,  -113,  -113,   220,   254,   307,  -113,  -113,
    -113,  -113,   178,   207,   249,    91,  -113,  -113,   224,   563,
    -113,   307,  -113,  -113,  -113,  -113,  -113,  -113,  -113,  -113,
    -113,    93,   210,  -113,    74,    31,  -113,  -113,    91,  -113,
    -113,  -113,  -113,  -113,  -113,    83,    31,  -113,   115,   110,
    -113,  -113,  -113,  -113,  -113,    93,  -113,  -113,  -113,  -113,
     307,  -113,  -113,   230,   155,  -113,  -113,  -113,   563,   232,
     244,   503,   563,  -113,  -113,   245,   533,  -113,  -113
  };

  const unsigned char
  parser::yydefact_[] =
  {
       0,     0,     0,     2,     0,     5,     0,     1,     0,     3,
       0,     4,     0,     0,     0,     0,     0,     0,    24,     0,
       0,    19,    20,    21,    22,    25,    23,     0,     0,    42,
      56,    57,    58,    59,    60,    45,     0,     0,    44,     0,
       0,     0,     6,     0,     7,     0,     0,   104,    70,    71,
      46,    48,    47,    61,   102,   100,   101,   103,    64,    66,
      72,     0,     0,    63,    86,    65,    67,    68,    69,    98,
      87,    88,    89,    90,   109,     0,    49,   113,   119,   123,
     125,   127,   129,   105,     0,     0,     0,     0,    62,     0,
       9,    10,    11,    12,    13,    64,    18,     0,   185,     0,
       0,     0,     0,     0,     0,   187,     0,     0,     0,     0,
      32,    34,    35,    37,     0,     8,     0,     0,     0,     0,
      74,     0,    76,    73,     0,     0,     0,    99,   106,   107,
     108,     0,   111,   112,     0,   115,   116,   117,   118,     0,
     121,   122,     0,     0,     0,     0,   168,   173,   174,     0,
       0,     0,     0,    83,     0,    80,    81,     0,    18,     0,
      77,     0,   176,     0,   179,     0,     0,     0,   183,     0,
       0,     0,     0,     0,   188,     0,     0,     0,   139,     0,
     147,   140,   141,     0,   152,   148,   149,   154,    30,   155,
       0,    33,     0,     0,     0,     0,   172,   181,     0,     0,
      75,    52,    53,    94,    95,     0,    96,    92,    50,     0,
       0,    64,   162,   161,   131,   163,     0,   110,   114,   120,
     124,   126,   128,   130,   167,     0,     0,     0,     0,   165,
      84,    82,     0,   186,     0,   166,     0,   175,   170,   169,
       0,   177,     0,     0,    28,     0,     0,     0,     0,     0,
     137,     0,   153,   145,   144,     0,     0,     0,    31,    36,
      38,   132,     0,     0,    78,     0,   171,    85,     0,     0,
      93,     0,    91,    14,    15,    16,    17,    43,   180,   184,
     178,     0,     0,    29,     0,     0,   143,   136,     0,   156,
     146,   151,   158,   157,   159,     0,     0,    39,     0,     0,
     182,    97,    51,   164,    26,     0,   142,   134,   135,   138,
       0,   150,   133,     0,     0,    79,    27,   160,     0,     0,
       0,     0,     0,    54,    40,     0,     0,    55,    41
  };

  const short
  parser::yypgoto_[] =
  {
    -113,  -113,  -113,   262,    28,  -113,   184,  -113,  -113,  -113,
    -113,  -113,   266,  -113,  -113,  -113,  -113,   182,    94,  -113,
    -113,  -113,    13,    -1,  -113,   222,   -28,  -113,  -113,   -33,
      -9,  -113,    -2,   168,  -113,  -113,  -113,  -113,  -113,  -113,
    -113,  -113,  -113,  -113,  -113,  -113,  -113,   -68,  -113,  -113,
    -113,   165,  -113,   161,  -113,   162,  -113,   163,   158,   167,
    -113,    56,  -113,  -113,    15,  -113,  -113,  -113,  -113,  -113,
    -113,  -113,  -113,  -101,   117,  -113,     4,  -113,    46,  -113,
     157,    72,  -112,    78,   273,   135,   216,  -104,  -113,  -113,
     150,  -113,   -38
  };

  const short
  parser::yydefgoto_[] =
  {
      -1,     2,     3,     4,     5,    19,    89,    90,    91,    92,
      93,    94,    20,    21,    22,    23,   110,   111,   112,    24,
      25,    26,   178,    58,    59,    60,    61,   209,    62,   321,
      63,    30,    64,    65,    66,    31,    32,    33,    67,    34,
      97,    68,    69,    70,    71,    72,    73,    74,    75,    76,
     131,    77,   134,    78,   139,    79,   142,    80,    81,    82,
      83,   213,   262,   248,   250,   251,   180,   181,   182,   183,
     184,   185,   186,   214,   188,   189,   294,   295,   215,   216,
      98,   164,   147,   168,   148,   149,   104,   105,   165,   198,
     169,    99,   106
  };

  const short
  parser::yytable_[] =
  {
      96,   108,   174,    29,   174,   197,   187,   127,     1,    38,
       6,    35,    36,    37,   171,    35,   245,    35,    38,   101,
      35,   102,    45,   159,   172,   256,   246,    95,    39,    40,
      41,   160,   257,    46,    35,    38,   116,     7,    18,    47,
     103,    48,    49,    50,    51,    52,   162,    18,    35,    38,
     196,   210,    53,   113,   117,    28,   203,   204,    54,   152,
     240,    55,    56,   217,   109,     9,   241,    11,   175,   158,
      57,   177,   161,   102,    35,    38,   252,    35,    38,    10,
      48,    49,   175,   146,   146,   146,   176,   107,   177,   187,
     205,   201,   103,   202,    35,   288,    38,   208,   212,    44,
     163,   167,   177,   289,   271,   102,   179,   114,   175,   260,
     272,   175,   306,    35,   240,   166,   146,   310,    45,   190,
     280,   100,   113,   311,   103,   211,   229,   194,   177,    46,
      27,   177,    51,    52,    28,    12,     1,    48,    49,    50,
      51,    52,    13,   132,   133,   179,   115,    27,    14,    15,
      16,    28,   124,   300,   102,    17,   119,   125,   232,   126,
     120,   143,   179,   244,   117,   179,   179,   144,   313,   167,
     179,    42,   145,   103,   179,   249,   179,   268,   140,   141,
     121,   236,   255,   166,   122,   237,   264,   265,   170,   179,
     267,   266,   179,   179,   102,   153,   254,   273,   274,   275,
     276,   155,   224,   269,   154,   113,   277,   270,   319,   211,
     174,   285,   296,   103,   195,   286,   297,    35,    38,   235,
     150,   151,   238,   239,   128,   129,   130,   243,   193,   292,
     192,   247,   199,   230,   225,   163,   226,   283,   227,   167,
     228,   302,   231,   212,   179,   234,   281,   253,   179,   261,
     263,   284,   290,   166,    12,     1,   211,   291,   298,   299,
     314,    13,   301,   305,   146,     8,   247,    14,    15,    16,
     211,   318,   304,   322,    17,   135,   136,   137,   138,   323,
     327,   157,   292,   179,   179,    43,   259,   249,   123,   326,
     320,   191,   206,   325,   320,   179,   316,   315,   325,   218,
     219,   282,   222,   309,   220,   287,   221,   258,   278,   211,
      35,    38,   223,   293,   317,    45,   233,   303,   279,   118,
     242,     0,   173,     0,     0,     0,    46,     0,     0,     0,
       0,     0,    47,     0,    48,    49,    50,    51,    52,     0,
     307,   308,     0,     0,   210,    35,     0,     0,    28,     0,
      45,    54,   312,     0,    55,    56,     0,    84,    85,    86,
      87,    46,     0,    57,   177,     0,   293,    47,     0,    48,
      49,    50,    51,    52,     0,     0,     0,     0,     0,    27,
      35,     0,     0,    28,    88,    45,    54,     0,     0,    55,
      56,     0,    84,    85,    86,    87,    46,     0,    57,     0,
       0,     0,    47,     0,    48,    49,    50,    51,    52,     0,
      35,     0,     0,     0,    27,    45,     0,     0,    28,   156,
       0,    54,     0,     0,    55,    56,    46,     0,     0,     0,
       0,     0,    47,    57,    48,    49,    50,    51,    52,     0,
       0,     0,    35,     0,    27,    53,     0,    45,    28,     0,
       0,    54,     0,     0,    55,    56,     0,     0,    46,     0,
       0,     0,     0,    57,    47,     0,    48,    49,    50,    51,
      52,     0,     0,     0,    35,     0,    27,   200,     0,    45,
      28,     0,     0,    54,     0,     0,    55,    56,     0,     0,
      46,     0,     0,     0,     0,    57,    47,     0,    48,    49,
      50,    51,    52,     0,     0,     0,    35,     0,    27,   207,
       0,    45,    28,     0,     0,    54,     0,     0,    55,    56,
       0,     0,    46,     0,     0,     0,     0,    57,    47,     0,
      48,    49,    50,    51,    52,     0,    35,     0,     0,     0,
      27,    45,     0,     0,    28,   324,     0,    54,     0,     0,
      55,    56,    46,     0,     0,     0,     0,     0,    47,    57,
      48,    49,    50,    51,    52,     0,    35,     0,     0,     0,
      27,    45,     0,     0,    28,   328,     0,    54,     0,     0,
      55,    56,    46,     0,     0,     0,     0,     0,    47,    57,
      48,    49,    50,    51,    52,     0,     0,     0,     0,     0,
      27,     0,     0,     0,    28,     0,     0,    54,     0,     0,
      55,    56,     0,     0,     0,     0,     0,     0,     0,    57
  };

  const short
  parser::yycheck_[] =
  {
      28,    39,   106,    12,   108,   117,   107,    75,     7,     4,
       3,     3,    13,    14,    43,     3,    43,     3,     4,    37,
       3,    39,     8,    34,    53,    32,    53,    28,    15,    16,
      17,    42,    39,    19,     3,     4,    45,     0,    10,    25,
      58,    27,    28,    29,    30,    31,    38,    19,     3,     4,
      38,    37,    38,    40,    37,    41,     3,     4,    44,    87,
      34,    47,    48,   131,    59,    35,    40,    35,    37,    97,
      56,    57,   100,    39,     3,     4,   177,     3,     4,    41,
      27,    28,    37,    84,    85,    86,    41,    53,    57,   190,
      37,   119,    58,   121,     3,    34,     4,   125,   126,    35,
     101,   102,    57,    42,    34,    39,   107,    49,    37,    38,
      40,    37,    38,     3,    34,   102,   117,    34,     8,    53,
      40,    14,   109,    40,    58,   126,   154,   114,    57,    19,
      37,    57,    30,    31,    41,     6,     7,    27,    28,    29,
      30,    31,    13,    47,    48,   146,    35,    37,    19,    20,
      21,    41,    32,   265,    39,    26,    34,    37,   159,    39,
      38,    22,   163,   172,    37,   166,   167,    23,    53,   170,
     171,    42,    24,    58,   175,   176,   177,   205,    54,    55,
      34,    34,   183,   170,    38,    38,   195,    34,    39,   190,
     199,    38,   193,   194,    39,    35,   183,   225,   226,   227,
     228,    42,   146,    34,    53,   192,   234,    38,    53,   210,
     314,    34,    34,    58,     9,    38,    38,     3,     4,   163,
      85,    86,   166,   167,    44,    45,    46,   171,    37,   257,
      59,   175,    53,    35,    53,   236,    53,   246,    53,   240,
      53,   269,    42,   271,   245,    20,    53,    32,   249,   193,
     194,    34,    32,   240,     6,     7,   257,     3,    51,    10,
     298,    13,    38,    53,   265,     3,   210,    19,    20,    21,
     271,    41,   281,    41,    26,    49,    50,    51,    52,    35,
      35,    97,   310,   284,   285,    19,   192,   288,    66,   322,
     318,   109,   124,   321,   322,   296,   305,   299,   326,   134,
     139,   245,   144,   288,   142,   249,   143,   190,   236,   310,
       3,     4,   145,   257,   310,     8,   159,   271,   240,    46,
     170,    -1,   106,    -1,    -1,    -1,    19,    -1,    -1,    -1,
      -1,    -1,    25,    -1,    27,    28,    29,    30,    31,    -1,
     284,   285,    -1,    -1,    37,     3,    -1,    -1,    41,    -1,
       8,    44,   296,    -1,    47,    48,    -1,    15,    16,    17,
      18,    19,    -1,    56,    57,    -1,   310,    25,    -1,    27,
      28,    29,    30,    31,    -1,    -1,    -1,    -1,    -1,    37,
       3,    -1,    -1,    41,    42,     8,    44,    -1,    -1,    47,
      48,    -1,    15,    16,    17,    18,    19,    -1,    56,    -1,
      -1,    -1,    25,    -1,    27,    28,    29,    30,    31,    -1,
       3,    -1,    -1,    -1,    37,     8,    -1,    -1,    41,    42,
      -1,    44,    -1,    -1,    47,    48,    19,    -1,    -1,    -1,
      -1,    -1,    25,    56,    27,    28,    29,    30,    31,    -1,
      -1,    -1,     3,    -1,    37,    38,    -1,     8,    41,    -1,
      -1,    44,    -1,    -1,    47,    48,    -1,    -1,    19,    -1,
      -1,    -1,    -1,    56,    25,    -1,    27,    28,    29,    30,
      31,    -1,    -1,    -1,     3,    -1,    37,    38,    -1,     8,
      41,    -1,    -1,    44,    -1,    -1,    47,    48,    -1,    -1,
      19,    -1,    -1,    -1,    -1,    56,    25,    -1,    27,    28,
      29,    30,    31,    -1,    -1,    -1,     3,    -1,    37,    38,
      -1,     8,    41,    -1,    -1,    44,    -1,    -1,    47,    48,
      -1,    -1,    19,    -1,    -1,    -1,    -1,    56,    25,    -1,
      27,    28,    29,    30,    31,    -1,     3,    -1,    -1,    -1,
      37,     8,    -1,    -1,    41,    42,    -1,    44,    -1,    -1,
      47,    48,    19,    -1,    -1,    -1,    -1,    -1,    25,    56,
      27,    28,    29,    30,    31,    -1,     3,    -1,    -1,    -1,
      37,     8,    -1,    -1,    41,    42,    -1,    44,    -1,    -1,
      47,    48,    19,    -1,    -1,    -1,    -1,    -1,    25,    56,
      27,    28,    29,    30,    31,    -1,    -1,    -1,    -1,    -1,
      37,    -1,    -1,    -1,    41,    -1,    -1,    44,    -1,    -1,
      47,    48,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    56
  };

  const unsigned char
  parser::yystos_[] =
  {
       0,     7,    63,    64,    65,    66,     3,     0,    65,    35,
      41,    35,     6,    13,    19,    20,    21,    26,    66,    67,
      74,    75,    76,    77,    81,    82,    83,    37,    41,    92,
      93,    97,    98,    99,   101,     3,    85,    85,     4,    84,
      84,    84,    42,    74,    35,     8,    19,    25,    27,    28,
      29,    30,    31,    38,    44,    47,    48,    56,    85,    86,
      87,    88,    90,    92,    94,    95,    96,   100,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   113,   115,   117,
     119,   120,   121,   122,    15,    16,    17,    18,    42,    68,
      69,    70,    71,    72,    73,    85,    88,   102,   142,   153,
      14,    37,    39,    58,   148,   149,   154,    53,   154,    59,
      78,    79,    80,    84,    49,    35,    92,    37,   146,    34,
      38,    34,    38,    87,    32,    37,    39,   109,    44,    45,
      46,   112,    47,    48,   114,    49,    50,    51,    52,   116,
      54,    55,   118,    22,    23,    24,    85,   144,   146,   147,
     147,   147,    88,    35,    53,    42,    42,    68,    88,    34,
      42,    88,    38,    85,   143,   150,    84,    85,   145,   152,
      39,    43,    53,   148,   149,    37,    41,    57,    84,    85,
     128,   129,   130,   131,   132,   133,   134,   135,   136,   137,
      53,    79,    59,    37,    84,     9,    38,   144,   151,    53,
      38,    88,    88,     3,     4,    37,    95,    38,    88,    89,
      37,    85,    88,   123,   135,   140,   141,   109,   113,   115,
     117,   119,   120,   121,   123,    53,    53,    53,    53,    88,
      35,    42,    85,   142,    20,   123,    34,    38,   123,   123,
      34,    40,   152,   123,    92,    43,    53,   123,   125,    85,
     126,   127,   135,    32,    84,    85,    32,    39,   136,    80,
      38,   123,   124,   123,    92,    34,    38,    92,    88,    34,
      38,    34,    40,    88,    88,    88,    88,    88,   143,   145,
      40,    53,   123,    92,    34,    34,    38,   123,    34,    42,
      32,     3,    88,   123,   138,   139,    34,    38,    51,    10,
     144,    38,    88,   140,    92,    53,    38,   123,   123,   126,
      34,    40,   123,    53,   154,    94,    92,   138,    41,    53,
      88,    91,    41,    35,    42,    88,    91,    35,    42
  };

  const unsigned char
  parser::yyr1_[] =
  {
       0,    62,    63,    64,    64,    65,    66,    67,    67,    68,
      68,    68,    68,    68,    69,    70,    71,    72,    73,    74,
      74,    74,    74,    74,    74,    74,    75,    75,    75,    75,
      76,    76,    77,    78,    78,    79,    79,    80,    80,    80,
      81,    81,    82,    83,    84,    85,    86,    87,    87,    88,
      89,    89,    90,    90,    91,    91,    92,    92,    92,    92,
      92,    93,    93,    94,    94,    94,    94,    94,    94,    94,
      95,    95,    96,    96,    97,    98,    98,    99,   100,   100,
     101,   101,   101,   102,   102,   103,   104,   104,   104,   104,
     104,   105,   106,   106,   107,   107,   108,   108,   109,   109,
     110,   110,   110,   110,   110,   111,   112,   112,   112,   113,
     113,   114,   114,   115,   115,   116,   116,   116,   116,   117,
     117,   118,   118,   119,   119,   120,   120,   121,   121,   122,
     122,   123,   124,   124,   125,   125,   126,   127,   127,   128,
     128,   128,   129,   129,   130,   131,   131,   132,   132,   132,
     133,   134,   135,   135,   136,   136,   137,   138,   138,   139,
     139,   140,   140,   141,   141,   142,   143,   144,   144,   145,
     145,   146,   146,   147,   147,   148,   148,   149,   149,   150,
     150,   151,   151,   152,   152,   153,   153,   154,   154
  };

  const signed char
  parser::yyr2_[] =
  {
       0,     2,     1,     2,     3,     1,     5,     2,     3,     1,
       1,     1,     1,     1,     4,     4,     4,     4,     1,     1,
       1,     1,     1,     1,     1,     1,     7,     8,     5,     6,
       4,     5,     3,     2,     1,     1,     3,     1,     3,     4,
      10,    11,     2,     6,     1,     1,     1,     1,     1,     1,
       1,     3,     3,     3,     2,     3,     1,     1,     1,     1,
       1,     2,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     2,     3,     4,     3,     3,     4,     6,
       3,     3,     4,     2,     3,     4,     1,     1,     1,     1,
       1,     4,     3,     4,     3,     3,     3,     5,     1,     2,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       3,     1,     1,     1,     3,     1,     1,     1,     1,     1,
       3,     1,     1,     1,     3,     1,     3,     1,     3,     1,
       3,     1,     1,     3,     3,     3,     2,     1,     3,     1,
       1,     1,     4,     3,     2,     2,     3,     1,     1,     1,
       4,     3,     1,     2,     1,     1,     3,     1,     1,     1,
       3,     1,     1,     1,     3,     3,     2,     2,     1,     2,
       2,     3,     2,     1,     1,     3,     2,     3,     4,     1,
       3,     1,     3,     1,     3,     1,     3,     1,     2
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
  "\"from\"", "\"const\"", "\"let\"", "\"var\"", "\"set\"", "\"fn\"",
  "\"type\"", "\"enum\"", "\"and\"", "\"xor\"", "\"or\"", "\"not\"",
  "\"typeclass\"", "\"42\"", "\"0x2a\"", "\"4.2\"",
  "\"\\\"dq-string-literal\\\"\"", "\"'sq-string-literal'\"", "\".\"",
  "\":\"", "\",\"", "\";\"", "\"::\"", "\"(\"", "\")\"", "\"[\"", "\"]\"",
  "\"{\"", "\"}\"", "\"->\"", "\"*\"", "\"/\"", "\"%\"", "\"+\"", "\"-\"",
  "\"<\"", "\"<=\"", "\">\"", "\">=\"", "\"=\"", "\"==\"", "\"!=\"",
  "\"^\"", "\"&\"", "\"!\"", "\"|\"", "\"EOS\"", "\"<null>\"", "$accept",
  "script", "scriptContent", "scriptContentStmt", "mod_stmt",
  "moduleContent", "chainPrefixStmt", "constStmt", "letStmt", "varStmt",
  "setStmt", "discardStmt", "moduleContentStmt", "fn_stmt", "type_stmt",
  "enum_stmt", "enum_field_pl", "unprefixed_enum_field_pl", "enum_field",
  "typeclass_stmt", "using_stmt", "importStmt", "tid", "vid", "floatl",
  "stringl", "expr", "expr_cl1", "expr_cl2", "expr_sl", "parenExpr",
  "unitExpr", "primaryExpr", "int_expr", "stringls", "vparenExpr",
  "vtupleExpr", "vstructExpr", "ifThenElseExpr", "chainExpr",
  "chainPrefix", "vlambdaExpr", "postfixExpr", "vtcallExpr", "vvcallExpr",
  "dotNmExpr", "dotIxExpr", "unaryExpr", "unaryOp", "binaryExpr",
  "mulBinaryOp", "mulBinaryExpr", "addBinaryOp", "addBinaryExpr",
  "cmpBinaryOp", "cmpBinaryExpr", "eqBinaryOp", "eqBinaryExpr",
  "andBinaryExpr", "xorBinaryExpr", "orBinaryExpr", "typespec",
  "typespec_cl1", "typespec_cl2", "structTypespecField",
  "structTypespecField_cl", "primaryTypespec", "tupleTypespec",
  "mod_prefix_tid", "mod_prefix", "postfixTypespec", "ttcall", "tdot",
  "unaryTypespec", "long_typespec", "structTypespec", "ttarg", "ttarg_cl",
  "vtarg", "vtarg_cl", "vstructExprField", "vpatternField",
  "lpatternField", "tpatternField", "lpattern", "lpattern_naked",
  "vpattern", "tpattern", "vpatternField_cl", "lpatternField_cl",
  "tpatternField_cl", "vstructExprField_cl", "tpattern_seq", YY_NULLPTR
  };
#endif


#if YYDEBUG
  const short
  parser::yyrline_[] =
  {
       0,   301,   301,   304,   305,   308,   316,   319,   320,   328,
     329,   330,   331,   332,   335,   338,   341,   344,   347,   351,
     352,   353,   354,   355,   356,   357,   360,   361,   362,   363,
     366,   367,   370,   373,   374,   377,   378,   381,   382,   383,
     386,   389,   395,   399,   406,   407,   409,   412,   413,   420,
     423,   424,   427,   428,   431,   432,   436,   437,   438,   439,
     440,   443,   444,   447,   448,   449,   450,   451,   452,   453,
     456,   457,   460,   461,   464,   467,   468,   471,   474,   475,
     478,   479,   480,   483,   484,   487,   491,   492,   493,   494,
     495,   498,   501,   502,   505,   506,   509,   510,   514,   515,
     518,   519,   520,   521,   522,   526,   529,   530,   531,   534,
     535,   538,   539,   542,   543,   546,   547,   548,   549,   552,
     553,   556,   557,   560,   561,   564,   565,   568,   569,   572,
     573,   581,   584,   585,   588,   589,   593,   596,   597,   601,
     602,   603,   606,   607,   610,   613,   614,   618,   619,   620,
     623,   625,   629,   630,   634,   635,   638,   642,   643,   646,
     647,   652,   653,   656,   657,   665,   668,   671,   672,   675,
     676,   680,   681,   684,   685,   688,   689,   692,   693,   697,
     698,   701,   702,   705,   706,   709,   710,   714,   715
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
      55,    56,    57,    58,    59,    60,    61
    };
    // Last valid token kind.
    const int code_max = 316;

    if (t <= 0)
      return symbol_kind::S_YYEOF;
    else if (t <= code_max)
      return YY_CAST (symbol_kind_type, translate_table[t]);
    else
      return symbol_kind::S_YYUNDEF;
  }

#line 22 "parser.yy"
} } // pdm::parser
#line 3752 "parser.tab.cc"

#line 718 "parser.yy"


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


ast::Script* parse_script(ast::Manager* manager, source::Source* source) {
    Lexer lexer;
    if (!lexer.setup(source)) {
        return nullptr;
    }

    ast::Script* out = nullptr;
    int result = yyparse(source, &lexer, manager, &out);
    if (result == 0) {
        return out;
    } else {
        return nullptr;
    }
}

// int yylex (YYSTYPE *lvalp) {
//     /* TODO: Put value onto Bison stack. */
//     return NULL;
// }

int yylex(TokenInfo* info, source::Loc* llocp, source::Source* source, parser::Lexer* lexer) {
    // see:
    // https://www.gnu.org/software/bison/manual/html_node/Calling-Convention.html
    
    llocp->source(source);
    int tk = lexer->lex_one_token(info, llocp);
    llocp->source(source);

    if (pdm::DEBUG) {
        // DebugPrintToken("YYLEX:", tk, info, llocp);
    }
    if (tk == EOS) {
        return YYEOF;
    } else {
        return tk;
    }
}

// void yyerror(YYLTYPE* llocp, Source* source, ast::* returnp, char const* message) {
//     Loc loc = FirstLocOfSpan(*llocp);
//     FeedbackNote* note = CreateFeedbackNote("here...", loc, NULL);
//     PostFeedback(
//         FBK_ERROR, note,
//         "Parser error: %s", message
//     );
// }
