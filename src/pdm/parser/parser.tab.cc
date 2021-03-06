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
#line 44 "parser.yy"

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

#line 11 "parser.yy"
namespace pdm { namespace parser {
#line 143 "parser.tab.cc"

  /// Build a parser object.
  parser::parser (pdm::source::ISource* source_yyarg, pdm::parser::Lexer* lexer_yyarg, pdm::ast::Manager* mgr_yyarg, pdm::ast::Script** returnp_yyarg)
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
        value.copy< TokenInfo > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_mul_binary_op: // mul_binary_op
      case symbol_kind::S_add_binary_op: // add_binary_op
      case symbol_kind::S_cmp_binary_op: // cmp_binary_op
      case symbol_kind::S_eq_binary_op: // eq_binary_op
        value.copy< pdm::ast::BinaryOperator > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_class_spec: // class_spec
      case symbol_kind::S_primary_class_spec: // primary_class_spec
      case symbol_kind::S_mod_prefix_cid_class_spec: // mod_prefix_cid_class_spec
      case symbol_kind::S_class_exp_class_spec: // class_exp_class_spec
        value.copy< pdm::ast::ClassSpec* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_enum_type_spec_field: // enum_type_spec_field
        value.copy< pdm::ast::EnumTypeSpec::Field* > (YY_MOVE (that.value));
        break;

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
        value.copy< pdm::ast::Exp* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_fn_type_spec: // fn_type_spec
        value.copy< pdm::ast::FnTypeSpec* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_script_header_stmt: // script_header_stmt
      case symbol_kind::S_import_stmt: // import_stmt
        value.copy< pdm::ast::HeaderStmt* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_destructured_lpattern: // destructured_lpattern
      case symbol_kind::S_lpattern: // lpattern
        value.copy< pdm::ast::LPattern* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_lpattern_field: // lpattern_field
        value.copy< pdm::ast::LPattern::Field* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_mod_prefix: // mod_prefix
        value.copy< pdm::ast::ModAddress* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_mod_exp: // mod_exp
        value.copy< pdm::ast::ModExp* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_mod_field: // mod_field
        value.copy< pdm::ast::ModExp::Field* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_script: // script
        value.copy< pdm::ast::Script* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_script_field: // script_field
        value.copy< pdm::ast::Script::Field* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_chain_prefix_stmt: // chain_prefix_stmt
      case symbol_kind::S_const_stmt: // const_stmt
      case symbol_kind::S_val_stmt: // val_stmt
      case symbol_kind::S_var_stmt: // var_stmt
      case symbol_kind::S_set_stmt: // set_stmt
      case symbol_kind::S_discard_stmt: // discard_stmt
        value.copy< pdm::ast::Stmt* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_struct_exp_field: // struct_exp_field
        value.copy< pdm::ast::StructExp::Field* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_struct_type_spec_field: // struct_type_spec_field
        value.copy< pdm::ast::StructTypeSpec::Field* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_targ: // targ
        value.copy< pdm::ast::TArg* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_tpattern: // tpattern
        value.copy< pdm::ast::TPattern* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_tpattern_field: // tpattern_field
        value.copy< pdm::ast::TPattern::Field* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_type_query_exp: // type_query_exp
        value.copy< pdm::ast::TypeQueryExp* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_type_query_op: // type_query_op
        value.copy< pdm::ast::TypeQueryKind > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_type_spec: // type_spec
      case symbol_kind::S_mod_prefix_tid: // mod_prefix_tid
      case symbol_kind::S_tuple_type_spec: // tuple_type_spec
      case symbol_kind::S_array_type_spec: // array_type_spec
      case symbol_kind::S_struct_type_spec: // struct_type_spec
      case symbol_kind::S_enum_type_spec: // enum_type_spec
        value.copy< pdm::ast::TypeSpec* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_unary_op: // unary_op
        value.copy< pdm::ast::UnaryOperator > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_varg: // varg
        value.copy< pdm::ast::VArg* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_vpattern: // vpattern
        value.copy< pdm::ast::VPattern* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_vpattern_field: // vpattern_field
        value.copy< pdm::ast::VPattern::Field* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_enum_type_spec_field_cl: // enum_type_spec_field_cl
        value.copy< std::vector<pdm::ast::EnumTypeSpec::Field*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_cl2: // expr_cl2
        value.copy< std::vector<pdm::ast::Exp*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_script_header: // script_header
        value.copy< std::vector<pdm::ast::HeaderStmt*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_lpattern_field_cl: // lpattern_field_cl
        value.copy< std::vector<pdm::ast::LPattern::Field*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_mod_field_sl: // mod_field_sl
        value.copy< std::vector<pdm::ast::ModExp::Field*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_script_field_sl: // script_field_sl
        value.copy< std::vector<pdm::ast::Script::Field*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_chain_prefix: // chain_prefix
        value.copy< std::vector<pdm::ast::Stmt*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stringls: // stringls
        value.copy< std::vector<pdm::ast::StringExp::Piece> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_struct_exp_field_cl: // struct_exp_field_cl
        value.copy< std::vector<pdm::ast::StructExp::Field*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_struct_type_spec_field_cl: // struct_type_spec_field_cl
        value.copy< std::vector<pdm::ast::StructTypeSpec::Field*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_targ_cl: // targ_cl
        value.copy< std::vector<pdm::ast::TArg*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_tpattern_field_cl1: // tpattern_field_cl1
        value.copy< std::vector<pdm::ast::TPattern::Field*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_type_query_exp_sl0: // type_query_exp_sl0
        value.copy< std::vector<pdm::ast::TypeQueryExp*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_type_spec_cl2: // type_spec_cl2
        value.copy< std::vector<pdm::ast::TypeSpec*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_varg_cl: // varg_cl
        value.copy< std::vector<pdm::ast::VArg*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_vpattern_field_cl: // vpattern_field_cl
        value.copy< std::vector<pdm::ast::VPattern::Field*> > (YY_MOVE (that.value));
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
        value.move< TokenInfo > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_mul_binary_op: // mul_binary_op
      case symbol_kind::S_add_binary_op: // add_binary_op
      case symbol_kind::S_cmp_binary_op: // cmp_binary_op
      case symbol_kind::S_eq_binary_op: // eq_binary_op
        value.move< pdm::ast::BinaryOperator > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_class_spec: // class_spec
      case symbol_kind::S_primary_class_spec: // primary_class_spec
      case symbol_kind::S_mod_prefix_cid_class_spec: // mod_prefix_cid_class_spec
      case symbol_kind::S_class_exp_class_spec: // class_exp_class_spec
        value.move< pdm::ast::ClassSpec* > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_enum_type_spec_field: // enum_type_spec_field
        value.move< pdm::ast::EnumTypeSpec::Field* > (YY_MOVE (s.value));
        break;

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
        value.move< pdm::ast::Exp* > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_fn_type_spec: // fn_type_spec
        value.move< pdm::ast::FnTypeSpec* > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_script_header_stmt: // script_header_stmt
      case symbol_kind::S_import_stmt: // import_stmt
        value.move< pdm::ast::HeaderStmt* > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_destructured_lpattern: // destructured_lpattern
      case symbol_kind::S_lpattern: // lpattern
        value.move< pdm::ast::LPattern* > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_lpattern_field: // lpattern_field
        value.move< pdm::ast::LPattern::Field* > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_mod_prefix: // mod_prefix
        value.move< pdm::ast::ModAddress* > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_mod_exp: // mod_exp
        value.move< pdm::ast::ModExp* > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_mod_field: // mod_field
        value.move< pdm::ast::ModExp::Field* > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_script: // script
        value.move< pdm::ast::Script* > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_script_field: // script_field
        value.move< pdm::ast::Script::Field* > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_chain_prefix_stmt: // chain_prefix_stmt
      case symbol_kind::S_const_stmt: // const_stmt
      case symbol_kind::S_val_stmt: // val_stmt
      case symbol_kind::S_var_stmt: // var_stmt
      case symbol_kind::S_set_stmt: // set_stmt
      case symbol_kind::S_discard_stmt: // discard_stmt
        value.move< pdm::ast::Stmt* > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_struct_exp_field: // struct_exp_field
        value.move< pdm::ast::StructExp::Field* > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_struct_type_spec_field: // struct_type_spec_field
        value.move< pdm::ast::StructTypeSpec::Field* > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_targ: // targ
        value.move< pdm::ast::TArg* > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_tpattern: // tpattern
        value.move< pdm::ast::TPattern* > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_tpattern_field: // tpattern_field
        value.move< pdm::ast::TPattern::Field* > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_type_query_exp: // type_query_exp
        value.move< pdm::ast::TypeQueryExp* > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_type_query_op: // type_query_op
        value.move< pdm::ast::TypeQueryKind > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_type_spec: // type_spec
      case symbol_kind::S_mod_prefix_tid: // mod_prefix_tid
      case symbol_kind::S_tuple_type_spec: // tuple_type_spec
      case symbol_kind::S_array_type_spec: // array_type_spec
      case symbol_kind::S_struct_type_spec: // struct_type_spec
      case symbol_kind::S_enum_type_spec: // enum_type_spec
        value.move< pdm::ast::TypeSpec* > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_unary_op: // unary_op
        value.move< pdm::ast::UnaryOperator > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_varg: // varg
        value.move< pdm::ast::VArg* > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_vpattern: // vpattern
        value.move< pdm::ast::VPattern* > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_vpattern_field: // vpattern_field
        value.move< pdm::ast::VPattern::Field* > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_enum_type_spec_field_cl: // enum_type_spec_field_cl
        value.move< std::vector<pdm::ast::EnumTypeSpec::Field*> > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_expr_cl2: // expr_cl2
        value.move< std::vector<pdm::ast::Exp*> > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_script_header: // script_header
        value.move< std::vector<pdm::ast::HeaderStmt*> > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_lpattern_field_cl: // lpattern_field_cl
        value.move< std::vector<pdm::ast::LPattern::Field*> > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_mod_field_sl: // mod_field_sl
        value.move< std::vector<pdm::ast::ModExp::Field*> > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_script_field_sl: // script_field_sl
        value.move< std::vector<pdm::ast::Script::Field*> > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_chain_prefix: // chain_prefix
        value.move< std::vector<pdm::ast::Stmt*> > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_stringls: // stringls
        value.move< std::vector<pdm::ast::StringExp::Piece> > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_struct_exp_field_cl: // struct_exp_field_cl
        value.move< std::vector<pdm::ast::StructExp::Field*> > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_struct_type_spec_field_cl: // struct_type_spec_field_cl
        value.move< std::vector<pdm::ast::StructTypeSpec::Field*> > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_targ_cl: // targ_cl
        value.move< std::vector<pdm::ast::TArg*> > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_tpattern_field_cl1: // tpattern_field_cl1
        value.move< std::vector<pdm::ast::TPattern::Field*> > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_type_query_exp_sl0: // type_query_exp_sl0
        value.move< std::vector<pdm::ast::TypeQueryExp*> > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_type_spec_cl2: // type_spec_cl2
        value.move< std::vector<pdm::ast::TypeSpec*> > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_varg_cl: // varg_cl
        value.move< std::vector<pdm::ast::VArg*> > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_vpattern_field_cl: // vpattern_field_cl
        value.move< std::vector<pdm::ast::VPattern::Field*> > (YY_MOVE (s.value));
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
        value.YY_MOVE_OR_COPY< TokenInfo > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_mul_binary_op: // mul_binary_op
      case symbol_kind::S_add_binary_op: // add_binary_op
      case symbol_kind::S_cmp_binary_op: // cmp_binary_op
      case symbol_kind::S_eq_binary_op: // eq_binary_op
        value.YY_MOVE_OR_COPY< pdm::ast::BinaryOperator > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_class_spec: // class_spec
      case symbol_kind::S_primary_class_spec: // primary_class_spec
      case symbol_kind::S_mod_prefix_cid_class_spec: // mod_prefix_cid_class_spec
      case symbol_kind::S_class_exp_class_spec: // class_exp_class_spec
        value.YY_MOVE_OR_COPY< pdm::ast::ClassSpec* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_enum_type_spec_field: // enum_type_spec_field
        value.YY_MOVE_OR_COPY< pdm::ast::EnumTypeSpec::Field* > (YY_MOVE (that.value));
        break;

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
        value.YY_MOVE_OR_COPY< pdm::ast::Exp* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_fn_type_spec: // fn_type_spec
        value.YY_MOVE_OR_COPY< pdm::ast::FnTypeSpec* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_script_header_stmt: // script_header_stmt
      case symbol_kind::S_import_stmt: // import_stmt
        value.YY_MOVE_OR_COPY< pdm::ast::HeaderStmt* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_destructured_lpattern: // destructured_lpattern
      case symbol_kind::S_lpattern: // lpattern
        value.YY_MOVE_OR_COPY< pdm::ast::LPattern* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_lpattern_field: // lpattern_field
        value.YY_MOVE_OR_COPY< pdm::ast::LPattern::Field* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_mod_prefix: // mod_prefix
        value.YY_MOVE_OR_COPY< pdm::ast::ModAddress* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_mod_exp: // mod_exp
        value.YY_MOVE_OR_COPY< pdm::ast::ModExp* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_mod_field: // mod_field
        value.YY_MOVE_OR_COPY< pdm::ast::ModExp::Field* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_script: // script
        value.YY_MOVE_OR_COPY< pdm::ast::Script* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_script_field: // script_field
        value.YY_MOVE_OR_COPY< pdm::ast::Script::Field* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_chain_prefix_stmt: // chain_prefix_stmt
      case symbol_kind::S_const_stmt: // const_stmt
      case symbol_kind::S_val_stmt: // val_stmt
      case symbol_kind::S_var_stmt: // var_stmt
      case symbol_kind::S_set_stmt: // set_stmt
      case symbol_kind::S_discard_stmt: // discard_stmt
        value.YY_MOVE_OR_COPY< pdm::ast::Stmt* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_struct_exp_field: // struct_exp_field
        value.YY_MOVE_OR_COPY< pdm::ast::StructExp::Field* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_struct_type_spec_field: // struct_type_spec_field
        value.YY_MOVE_OR_COPY< pdm::ast::StructTypeSpec::Field* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_targ: // targ
        value.YY_MOVE_OR_COPY< pdm::ast::TArg* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_tpattern: // tpattern
        value.YY_MOVE_OR_COPY< pdm::ast::TPattern* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_tpattern_field: // tpattern_field
        value.YY_MOVE_OR_COPY< pdm::ast::TPattern::Field* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_type_query_exp: // type_query_exp
        value.YY_MOVE_OR_COPY< pdm::ast::TypeQueryExp* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_type_query_op: // type_query_op
        value.YY_MOVE_OR_COPY< pdm::ast::TypeQueryKind > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_type_spec: // type_spec
      case symbol_kind::S_mod_prefix_tid: // mod_prefix_tid
      case symbol_kind::S_tuple_type_spec: // tuple_type_spec
      case symbol_kind::S_array_type_spec: // array_type_spec
      case symbol_kind::S_struct_type_spec: // struct_type_spec
      case symbol_kind::S_enum_type_spec: // enum_type_spec
        value.YY_MOVE_OR_COPY< pdm::ast::TypeSpec* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_unary_op: // unary_op
        value.YY_MOVE_OR_COPY< pdm::ast::UnaryOperator > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_varg: // varg
        value.YY_MOVE_OR_COPY< pdm::ast::VArg* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_vpattern: // vpattern
        value.YY_MOVE_OR_COPY< pdm::ast::VPattern* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_vpattern_field: // vpattern_field
        value.YY_MOVE_OR_COPY< pdm::ast::VPattern::Field* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_enum_type_spec_field_cl: // enum_type_spec_field_cl
        value.YY_MOVE_OR_COPY< std::vector<pdm::ast::EnumTypeSpec::Field*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_cl2: // expr_cl2
        value.YY_MOVE_OR_COPY< std::vector<pdm::ast::Exp*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_script_header: // script_header
        value.YY_MOVE_OR_COPY< std::vector<pdm::ast::HeaderStmt*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_lpattern_field_cl: // lpattern_field_cl
        value.YY_MOVE_OR_COPY< std::vector<pdm::ast::LPattern::Field*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_mod_field_sl: // mod_field_sl
        value.YY_MOVE_OR_COPY< std::vector<pdm::ast::ModExp::Field*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_script_field_sl: // script_field_sl
        value.YY_MOVE_OR_COPY< std::vector<pdm::ast::Script::Field*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_chain_prefix: // chain_prefix
        value.YY_MOVE_OR_COPY< std::vector<pdm::ast::Stmt*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stringls: // stringls
        value.YY_MOVE_OR_COPY< std::vector<pdm::ast::StringExp::Piece> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_struct_exp_field_cl: // struct_exp_field_cl
        value.YY_MOVE_OR_COPY< std::vector<pdm::ast::StructExp::Field*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_struct_type_spec_field_cl: // struct_type_spec_field_cl
        value.YY_MOVE_OR_COPY< std::vector<pdm::ast::StructTypeSpec::Field*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_targ_cl: // targ_cl
        value.YY_MOVE_OR_COPY< std::vector<pdm::ast::TArg*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_tpattern_field_cl1: // tpattern_field_cl1
        value.YY_MOVE_OR_COPY< std::vector<pdm::ast::TPattern::Field*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_type_query_exp_sl0: // type_query_exp_sl0
        value.YY_MOVE_OR_COPY< std::vector<pdm::ast::TypeQueryExp*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_type_spec_cl2: // type_spec_cl2
        value.YY_MOVE_OR_COPY< std::vector<pdm::ast::TypeSpec*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_varg_cl: // varg_cl
        value.YY_MOVE_OR_COPY< std::vector<pdm::ast::VArg*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_vpattern_field_cl: // vpattern_field_cl
        value.YY_MOVE_OR_COPY< std::vector<pdm::ast::VPattern::Field*> > (YY_MOVE (that.value));
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
        value.move< TokenInfo > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_mul_binary_op: // mul_binary_op
      case symbol_kind::S_add_binary_op: // add_binary_op
      case symbol_kind::S_cmp_binary_op: // cmp_binary_op
      case symbol_kind::S_eq_binary_op: // eq_binary_op
        value.move< pdm::ast::BinaryOperator > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_class_spec: // class_spec
      case symbol_kind::S_primary_class_spec: // primary_class_spec
      case symbol_kind::S_mod_prefix_cid_class_spec: // mod_prefix_cid_class_spec
      case symbol_kind::S_class_exp_class_spec: // class_exp_class_spec
        value.move< pdm::ast::ClassSpec* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_enum_type_spec_field: // enum_type_spec_field
        value.move< pdm::ast::EnumTypeSpec::Field* > (YY_MOVE (that.value));
        break;

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
        value.move< pdm::ast::Exp* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_fn_type_spec: // fn_type_spec
        value.move< pdm::ast::FnTypeSpec* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_script_header_stmt: // script_header_stmt
      case symbol_kind::S_import_stmt: // import_stmt
        value.move< pdm::ast::HeaderStmt* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_destructured_lpattern: // destructured_lpattern
      case symbol_kind::S_lpattern: // lpattern
        value.move< pdm::ast::LPattern* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_lpattern_field: // lpattern_field
        value.move< pdm::ast::LPattern::Field* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_mod_prefix: // mod_prefix
        value.move< pdm::ast::ModAddress* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_mod_exp: // mod_exp
        value.move< pdm::ast::ModExp* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_mod_field: // mod_field
        value.move< pdm::ast::ModExp::Field* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_script: // script
        value.move< pdm::ast::Script* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_script_field: // script_field
        value.move< pdm::ast::Script::Field* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_chain_prefix_stmt: // chain_prefix_stmt
      case symbol_kind::S_const_stmt: // const_stmt
      case symbol_kind::S_val_stmt: // val_stmt
      case symbol_kind::S_var_stmt: // var_stmt
      case symbol_kind::S_set_stmt: // set_stmt
      case symbol_kind::S_discard_stmt: // discard_stmt
        value.move< pdm::ast::Stmt* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_struct_exp_field: // struct_exp_field
        value.move< pdm::ast::StructExp::Field* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_struct_type_spec_field: // struct_type_spec_field
        value.move< pdm::ast::StructTypeSpec::Field* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_targ: // targ
        value.move< pdm::ast::TArg* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_tpattern: // tpattern
        value.move< pdm::ast::TPattern* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_tpattern_field: // tpattern_field
        value.move< pdm::ast::TPattern::Field* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_type_query_exp: // type_query_exp
        value.move< pdm::ast::TypeQueryExp* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_type_query_op: // type_query_op
        value.move< pdm::ast::TypeQueryKind > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_type_spec: // type_spec
      case symbol_kind::S_mod_prefix_tid: // mod_prefix_tid
      case symbol_kind::S_tuple_type_spec: // tuple_type_spec
      case symbol_kind::S_array_type_spec: // array_type_spec
      case symbol_kind::S_struct_type_spec: // struct_type_spec
      case symbol_kind::S_enum_type_spec: // enum_type_spec
        value.move< pdm::ast::TypeSpec* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_unary_op: // unary_op
        value.move< pdm::ast::UnaryOperator > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_varg: // varg
        value.move< pdm::ast::VArg* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_vpattern: // vpattern
        value.move< pdm::ast::VPattern* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_vpattern_field: // vpattern_field
        value.move< pdm::ast::VPattern::Field* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_enum_type_spec_field_cl: // enum_type_spec_field_cl
        value.move< std::vector<pdm::ast::EnumTypeSpec::Field*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_cl2: // expr_cl2
        value.move< std::vector<pdm::ast::Exp*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_script_header: // script_header
        value.move< std::vector<pdm::ast::HeaderStmt*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_lpattern_field_cl: // lpattern_field_cl
        value.move< std::vector<pdm::ast::LPattern::Field*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_mod_field_sl: // mod_field_sl
        value.move< std::vector<pdm::ast::ModExp::Field*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_script_field_sl: // script_field_sl
        value.move< std::vector<pdm::ast::Script::Field*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_chain_prefix: // chain_prefix
        value.move< std::vector<pdm::ast::Stmt*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stringls: // stringls
        value.move< std::vector<pdm::ast::StringExp::Piece> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_struct_exp_field_cl: // struct_exp_field_cl
        value.move< std::vector<pdm::ast::StructExp::Field*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_struct_type_spec_field_cl: // struct_type_spec_field_cl
        value.move< std::vector<pdm::ast::StructTypeSpec::Field*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_targ_cl: // targ_cl
        value.move< std::vector<pdm::ast::TArg*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_tpattern_field_cl1: // tpattern_field_cl1
        value.move< std::vector<pdm::ast::TPattern::Field*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_type_query_exp_sl0: // type_query_exp_sl0
        value.move< std::vector<pdm::ast::TypeQueryExp*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_type_spec_cl2: // type_spec_cl2
        value.move< std::vector<pdm::ast::TypeSpec*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_varg_cl: // varg_cl
        value.move< std::vector<pdm::ast::VArg*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_vpattern_field_cl: // vpattern_field_cl
        value.move< std::vector<pdm::ast::VPattern::Field*> > (YY_MOVE (that.value));
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
        value.copy< TokenInfo > (that.value);
        break;

      case symbol_kind::S_mul_binary_op: // mul_binary_op
      case symbol_kind::S_add_binary_op: // add_binary_op
      case symbol_kind::S_cmp_binary_op: // cmp_binary_op
      case symbol_kind::S_eq_binary_op: // eq_binary_op
        value.copy< pdm::ast::BinaryOperator > (that.value);
        break;

      case symbol_kind::S_class_spec: // class_spec
      case symbol_kind::S_primary_class_spec: // primary_class_spec
      case symbol_kind::S_mod_prefix_cid_class_spec: // mod_prefix_cid_class_spec
      case symbol_kind::S_class_exp_class_spec: // class_exp_class_spec
        value.copy< pdm::ast::ClassSpec* > (that.value);
        break;

      case symbol_kind::S_enum_type_spec_field: // enum_type_spec_field
        value.copy< pdm::ast::EnumTypeSpec::Field* > (that.value);
        break;

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
        value.copy< pdm::ast::Exp* > (that.value);
        break;

      case symbol_kind::S_fn_type_spec: // fn_type_spec
        value.copy< pdm::ast::FnTypeSpec* > (that.value);
        break;

      case symbol_kind::S_script_header_stmt: // script_header_stmt
      case symbol_kind::S_import_stmt: // import_stmt
        value.copy< pdm::ast::HeaderStmt* > (that.value);
        break;

      case symbol_kind::S_destructured_lpattern: // destructured_lpattern
      case symbol_kind::S_lpattern: // lpattern
        value.copy< pdm::ast::LPattern* > (that.value);
        break;

      case symbol_kind::S_lpattern_field: // lpattern_field
        value.copy< pdm::ast::LPattern::Field* > (that.value);
        break;

      case symbol_kind::S_mod_prefix: // mod_prefix
        value.copy< pdm::ast::ModAddress* > (that.value);
        break;

      case symbol_kind::S_mod_exp: // mod_exp
        value.copy< pdm::ast::ModExp* > (that.value);
        break;

      case symbol_kind::S_mod_field: // mod_field
        value.copy< pdm::ast::ModExp::Field* > (that.value);
        break;

      case symbol_kind::S_script: // script
        value.copy< pdm::ast::Script* > (that.value);
        break;

      case symbol_kind::S_script_field: // script_field
        value.copy< pdm::ast::Script::Field* > (that.value);
        break;

      case symbol_kind::S_chain_prefix_stmt: // chain_prefix_stmt
      case symbol_kind::S_const_stmt: // const_stmt
      case symbol_kind::S_val_stmt: // val_stmt
      case symbol_kind::S_var_stmt: // var_stmt
      case symbol_kind::S_set_stmt: // set_stmt
      case symbol_kind::S_discard_stmt: // discard_stmt
        value.copy< pdm::ast::Stmt* > (that.value);
        break;

      case symbol_kind::S_struct_exp_field: // struct_exp_field
        value.copy< pdm::ast::StructExp::Field* > (that.value);
        break;

      case symbol_kind::S_struct_type_spec_field: // struct_type_spec_field
        value.copy< pdm::ast::StructTypeSpec::Field* > (that.value);
        break;

      case symbol_kind::S_targ: // targ
        value.copy< pdm::ast::TArg* > (that.value);
        break;

      case symbol_kind::S_tpattern: // tpattern
        value.copy< pdm::ast::TPattern* > (that.value);
        break;

      case symbol_kind::S_tpattern_field: // tpattern_field
        value.copy< pdm::ast::TPattern::Field* > (that.value);
        break;

      case symbol_kind::S_type_query_exp: // type_query_exp
        value.copy< pdm::ast::TypeQueryExp* > (that.value);
        break;

      case symbol_kind::S_type_query_op: // type_query_op
        value.copy< pdm::ast::TypeQueryKind > (that.value);
        break;

      case symbol_kind::S_type_spec: // type_spec
      case symbol_kind::S_mod_prefix_tid: // mod_prefix_tid
      case symbol_kind::S_tuple_type_spec: // tuple_type_spec
      case symbol_kind::S_array_type_spec: // array_type_spec
      case symbol_kind::S_struct_type_spec: // struct_type_spec
      case symbol_kind::S_enum_type_spec: // enum_type_spec
        value.copy< pdm::ast::TypeSpec* > (that.value);
        break;

      case symbol_kind::S_unary_op: // unary_op
        value.copy< pdm::ast::UnaryOperator > (that.value);
        break;

      case symbol_kind::S_varg: // varg
        value.copy< pdm::ast::VArg* > (that.value);
        break;

      case symbol_kind::S_vpattern: // vpattern
        value.copy< pdm::ast::VPattern* > (that.value);
        break;

      case symbol_kind::S_vpattern_field: // vpattern_field
        value.copy< pdm::ast::VPattern::Field* > (that.value);
        break;

      case symbol_kind::S_enum_type_spec_field_cl: // enum_type_spec_field_cl
        value.copy< std::vector<pdm::ast::EnumTypeSpec::Field*> > (that.value);
        break;

      case symbol_kind::S_expr_cl2: // expr_cl2
        value.copy< std::vector<pdm::ast::Exp*> > (that.value);
        break;

      case symbol_kind::S_script_header: // script_header
        value.copy< std::vector<pdm::ast::HeaderStmt*> > (that.value);
        break;

      case symbol_kind::S_lpattern_field_cl: // lpattern_field_cl
        value.copy< std::vector<pdm::ast::LPattern::Field*> > (that.value);
        break;

      case symbol_kind::S_mod_field_sl: // mod_field_sl
        value.copy< std::vector<pdm::ast::ModExp::Field*> > (that.value);
        break;

      case symbol_kind::S_script_field_sl: // script_field_sl
        value.copy< std::vector<pdm::ast::Script::Field*> > (that.value);
        break;

      case symbol_kind::S_chain_prefix: // chain_prefix
        value.copy< std::vector<pdm::ast::Stmt*> > (that.value);
        break;

      case symbol_kind::S_stringls: // stringls
        value.copy< std::vector<pdm::ast::StringExp::Piece> > (that.value);
        break;

      case symbol_kind::S_struct_exp_field_cl: // struct_exp_field_cl
        value.copy< std::vector<pdm::ast::StructExp::Field*> > (that.value);
        break;

      case symbol_kind::S_struct_type_spec_field_cl: // struct_type_spec_field_cl
        value.copy< std::vector<pdm::ast::StructTypeSpec::Field*> > (that.value);
        break;

      case symbol_kind::S_targ_cl: // targ_cl
        value.copy< std::vector<pdm::ast::TArg*> > (that.value);
        break;

      case symbol_kind::S_tpattern_field_cl1: // tpattern_field_cl1
        value.copy< std::vector<pdm::ast::TPattern::Field*> > (that.value);
        break;

      case symbol_kind::S_type_query_exp_sl0: // type_query_exp_sl0
        value.copy< std::vector<pdm::ast::TypeQueryExp*> > (that.value);
        break;

      case symbol_kind::S_type_spec_cl2: // type_spec_cl2
        value.copy< std::vector<pdm::ast::TypeSpec*> > (that.value);
        break;

      case symbol_kind::S_varg_cl: // varg_cl
        value.copy< std::vector<pdm::ast::VArg*> > (that.value);
        break;

      case symbol_kind::S_vpattern_field_cl: // vpattern_field_cl
        value.copy< std::vector<pdm::ast::VPattern::Field*> > (that.value);
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
        value.move< TokenInfo > (that.value);
        break;

      case symbol_kind::S_mul_binary_op: // mul_binary_op
      case symbol_kind::S_add_binary_op: // add_binary_op
      case symbol_kind::S_cmp_binary_op: // cmp_binary_op
      case symbol_kind::S_eq_binary_op: // eq_binary_op
        value.move< pdm::ast::BinaryOperator > (that.value);
        break;

      case symbol_kind::S_class_spec: // class_spec
      case symbol_kind::S_primary_class_spec: // primary_class_spec
      case symbol_kind::S_mod_prefix_cid_class_spec: // mod_prefix_cid_class_spec
      case symbol_kind::S_class_exp_class_spec: // class_exp_class_spec
        value.move< pdm::ast::ClassSpec* > (that.value);
        break;

      case symbol_kind::S_enum_type_spec_field: // enum_type_spec_field
        value.move< pdm::ast::EnumTypeSpec::Field* > (that.value);
        break;

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
        value.move< pdm::ast::Exp* > (that.value);
        break;

      case symbol_kind::S_fn_type_spec: // fn_type_spec
        value.move< pdm::ast::FnTypeSpec* > (that.value);
        break;

      case symbol_kind::S_script_header_stmt: // script_header_stmt
      case symbol_kind::S_import_stmt: // import_stmt
        value.move< pdm::ast::HeaderStmt* > (that.value);
        break;

      case symbol_kind::S_destructured_lpattern: // destructured_lpattern
      case symbol_kind::S_lpattern: // lpattern
        value.move< pdm::ast::LPattern* > (that.value);
        break;

      case symbol_kind::S_lpattern_field: // lpattern_field
        value.move< pdm::ast::LPattern::Field* > (that.value);
        break;

      case symbol_kind::S_mod_prefix: // mod_prefix
        value.move< pdm::ast::ModAddress* > (that.value);
        break;

      case symbol_kind::S_mod_exp: // mod_exp
        value.move< pdm::ast::ModExp* > (that.value);
        break;

      case symbol_kind::S_mod_field: // mod_field
        value.move< pdm::ast::ModExp::Field* > (that.value);
        break;

      case symbol_kind::S_script: // script
        value.move< pdm::ast::Script* > (that.value);
        break;

      case symbol_kind::S_script_field: // script_field
        value.move< pdm::ast::Script::Field* > (that.value);
        break;

      case symbol_kind::S_chain_prefix_stmt: // chain_prefix_stmt
      case symbol_kind::S_const_stmt: // const_stmt
      case symbol_kind::S_val_stmt: // val_stmt
      case symbol_kind::S_var_stmt: // var_stmt
      case symbol_kind::S_set_stmt: // set_stmt
      case symbol_kind::S_discard_stmt: // discard_stmt
        value.move< pdm::ast::Stmt* > (that.value);
        break;

      case symbol_kind::S_struct_exp_field: // struct_exp_field
        value.move< pdm::ast::StructExp::Field* > (that.value);
        break;

      case symbol_kind::S_struct_type_spec_field: // struct_type_spec_field
        value.move< pdm::ast::StructTypeSpec::Field* > (that.value);
        break;

      case symbol_kind::S_targ: // targ
        value.move< pdm::ast::TArg* > (that.value);
        break;

      case symbol_kind::S_tpattern: // tpattern
        value.move< pdm::ast::TPattern* > (that.value);
        break;

      case symbol_kind::S_tpattern_field: // tpattern_field
        value.move< pdm::ast::TPattern::Field* > (that.value);
        break;

      case symbol_kind::S_type_query_exp: // type_query_exp
        value.move< pdm::ast::TypeQueryExp* > (that.value);
        break;

      case symbol_kind::S_type_query_op: // type_query_op
        value.move< pdm::ast::TypeQueryKind > (that.value);
        break;

      case symbol_kind::S_type_spec: // type_spec
      case symbol_kind::S_mod_prefix_tid: // mod_prefix_tid
      case symbol_kind::S_tuple_type_spec: // tuple_type_spec
      case symbol_kind::S_array_type_spec: // array_type_spec
      case symbol_kind::S_struct_type_spec: // struct_type_spec
      case symbol_kind::S_enum_type_spec: // enum_type_spec
        value.move< pdm::ast::TypeSpec* > (that.value);
        break;

      case symbol_kind::S_unary_op: // unary_op
        value.move< pdm::ast::UnaryOperator > (that.value);
        break;

      case symbol_kind::S_varg: // varg
        value.move< pdm::ast::VArg* > (that.value);
        break;

      case symbol_kind::S_vpattern: // vpattern
        value.move< pdm::ast::VPattern* > (that.value);
        break;

      case symbol_kind::S_vpattern_field: // vpattern_field
        value.move< pdm::ast::VPattern::Field* > (that.value);
        break;

      case symbol_kind::S_enum_type_spec_field_cl: // enum_type_spec_field_cl
        value.move< std::vector<pdm::ast::EnumTypeSpec::Field*> > (that.value);
        break;

      case symbol_kind::S_expr_cl2: // expr_cl2
        value.move< std::vector<pdm::ast::Exp*> > (that.value);
        break;

      case symbol_kind::S_script_header: // script_header
        value.move< std::vector<pdm::ast::HeaderStmt*> > (that.value);
        break;

      case symbol_kind::S_lpattern_field_cl: // lpattern_field_cl
        value.move< std::vector<pdm::ast::LPattern::Field*> > (that.value);
        break;

      case symbol_kind::S_mod_field_sl: // mod_field_sl
        value.move< std::vector<pdm::ast::ModExp::Field*> > (that.value);
        break;

      case symbol_kind::S_script_field_sl: // script_field_sl
        value.move< std::vector<pdm::ast::Script::Field*> > (that.value);
        break;

      case symbol_kind::S_chain_prefix: // chain_prefix
        value.move< std::vector<pdm::ast::Stmt*> > (that.value);
        break;

      case symbol_kind::S_stringls: // stringls
        value.move< std::vector<pdm::ast::StringExp::Piece> > (that.value);
        break;

      case symbol_kind::S_struct_exp_field_cl: // struct_exp_field_cl
        value.move< std::vector<pdm::ast::StructExp::Field*> > (that.value);
        break;

      case symbol_kind::S_struct_type_spec_field_cl: // struct_type_spec_field_cl
        value.move< std::vector<pdm::ast::StructTypeSpec::Field*> > (that.value);
        break;

      case symbol_kind::S_targ_cl: // targ_cl
        value.move< std::vector<pdm::ast::TArg*> > (that.value);
        break;

      case symbol_kind::S_tpattern_field_cl1: // tpattern_field_cl1
        value.move< std::vector<pdm::ast::TPattern::Field*> > (that.value);
        break;

      case symbol_kind::S_type_query_exp_sl0: // type_query_exp_sl0
        value.move< std::vector<pdm::ast::TypeQueryExp*> > (that.value);
        break;

      case symbol_kind::S_type_spec_cl2: // type_spec_cl2
        value.move< std::vector<pdm::ast::TypeSpec*> > (that.value);
        break;

      case symbol_kind::S_varg_cl: // varg_cl
        value.move< std::vector<pdm::ast::VArg*> > (that.value);
        break;

      case symbol_kind::S_vpattern_field_cl: // vpattern_field_cl
        value.move< std::vector<pdm::ast::VPattern::Field*> > (that.value);
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
        yylhs.value.emplace< TokenInfo > ();
        break;

      case symbol_kind::S_mul_binary_op: // mul_binary_op
      case symbol_kind::S_add_binary_op: // add_binary_op
      case symbol_kind::S_cmp_binary_op: // cmp_binary_op
      case symbol_kind::S_eq_binary_op: // eq_binary_op
        yylhs.value.emplace< pdm::ast::BinaryOperator > ();
        break;

      case symbol_kind::S_class_spec: // class_spec
      case symbol_kind::S_primary_class_spec: // primary_class_spec
      case symbol_kind::S_mod_prefix_cid_class_spec: // mod_prefix_cid_class_spec
      case symbol_kind::S_class_exp_class_spec: // class_exp_class_spec
        yylhs.value.emplace< pdm::ast::ClassSpec* > ();
        break;

      case symbol_kind::S_enum_type_spec_field: // enum_type_spec_field
        yylhs.value.emplace< pdm::ast::EnumTypeSpec::Field* > ();
        break;

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
        yylhs.value.emplace< pdm::ast::Exp* > ();
        break;

      case symbol_kind::S_fn_type_spec: // fn_type_spec
        yylhs.value.emplace< pdm::ast::FnTypeSpec* > ();
        break;

      case symbol_kind::S_script_header_stmt: // script_header_stmt
      case symbol_kind::S_import_stmt: // import_stmt
        yylhs.value.emplace< pdm::ast::HeaderStmt* > ();
        break;

      case symbol_kind::S_destructured_lpattern: // destructured_lpattern
      case symbol_kind::S_lpattern: // lpattern
        yylhs.value.emplace< pdm::ast::LPattern* > ();
        break;

      case symbol_kind::S_lpattern_field: // lpattern_field
        yylhs.value.emplace< pdm::ast::LPattern::Field* > ();
        break;

      case symbol_kind::S_mod_prefix: // mod_prefix
        yylhs.value.emplace< pdm::ast::ModAddress* > ();
        break;

      case symbol_kind::S_mod_exp: // mod_exp
        yylhs.value.emplace< pdm::ast::ModExp* > ();
        break;

      case symbol_kind::S_mod_field: // mod_field
        yylhs.value.emplace< pdm::ast::ModExp::Field* > ();
        break;

      case symbol_kind::S_script: // script
        yylhs.value.emplace< pdm::ast::Script* > ();
        break;

      case symbol_kind::S_script_field: // script_field
        yylhs.value.emplace< pdm::ast::Script::Field* > ();
        break;

      case symbol_kind::S_chain_prefix_stmt: // chain_prefix_stmt
      case symbol_kind::S_const_stmt: // const_stmt
      case symbol_kind::S_val_stmt: // val_stmt
      case symbol_kind::S_var_stmt: // var_stmt
      case symbol_kind::S_set_stmt: // set_stmt
      case symbol_kind::S_discard_stmt: // discard_stmt
        yylhs.value.emplace< pdm::ast::Stmt* > ();
        break;

      case symbol_kind::S_struct_exp_field: // struct_exp_field
        yylhs.value.emplace< pdm::ast::StructExp::Field* > ();
        break;

      case symbol_kind::S_struct_type_spec_field: // struct_type_spec_field
        yylhs.value.emplace< pdm::ast::StructTypeSpec::Field* > ();
        break;

      case symbol_kind::S_targ: // targ
        yylhs.value.emplace< pdm::ast::TArg* > ();
        break;

      case symbol_kind::S_tpattern: // tpattern
        yylhs.value.emplace< pdm::ast::TPattern* > ();
        break;

      case symbol_kind::S_tpattern_field: // tpattern_field
        yylhs.value.emplace< pdm::ast::TPattern::Field* > ();
        break;

      case symbol_kind::S_type_query_exp: // type_query_exp
        yylhs.value.emplace< pdm::ast::TypeQueryExp* > ();
        break;

      case symbol_kind::S_type_query_op: // type_query_op
        yylhs.value.emplace< pdm::ast::TypeQueryKind > ();
        break;

      case symbol_kind::S_type_spec: // type_spec
      case symbol_kind::S_mod_prefix_tid: // mod_prefix_tid
      case symbol_kind::S_tuple_type_spec: // tuple_type_spec
      case symbol_kind::S_array_type_spec: // array_type_spec
      case symbol_kind::S_struct_type_spec: // struct_type_spec
      case symbol_kind::S_enum_type_spec: // enum_type_spec
        yylhs.value.emplace< pdm::ast::TypeSpec* > ();
        break;

      case symbol_kind::S_unary_op: // unary_op
        yylhs.value.emplace< pdm::ast::UnaryOperator > ();
        break;

      case symbol_kind::S_varg: // varg
        yylhs.value.emplace< pdm::ast::VArg* > ();
        break;

      case symbol_kind::S_vpattern: // vpattern
        yylhs.value.emplace< pdm::ast::VPattern* > ();
        break;

      case symbol_kind::S_vpattern_field: // vpattern_field
        yylhs.value.emplace< pdm::ast::VPattern::Field* > ();
        break;

      case symbol_kind::S_enum_type_spec_field_cl: // enum_type_spec_field_cl
        yylhs.value.emplace< std::vector<pdm::ast::EnumTypeSpec::Field*> > ();
        break;

      case symbol_kind::S_expr_cl2: // expr_cl2
        yylhs.value.emplace< std::vector<pdm::ast::Exp*> > ();
        break;

      case symbol_kind::S_script_header: // script_header
        yylhs.value.emplace< std::vector<pdm::ast::HeaderStmt*> > ();
        break;

      case symbol_kind::S_lpattern_field_cl: // lpattern_field_cl
        yylhs.value.emplace< std::vector<pdm::ast::LPattern::Field*> > ();
        break;

      case symbol_kind::S_mod_field_sl: // mod_field_sl
        yylhs.value.emplace< std::vector<pdm::ast::ModExp::Field*> > ();
        break;

      case symbol_kind::S_script_field_sl: // script_field_sl
        yylhs.value.emplace< std::vector<pdm::ast::Script::Field*> > ();
        break;

      case symbol_kind::S_chain_prefix: // chain_prefix
        yylhs.value.emplace< std::vector<pdm::ast::Stmt*> > ();
        break;

      case symbol_kind::S_stringls: // stringls
        yylhs.value.emplace< std::vector<pdm::ast::StringExp::Piece> > ();
        break;

      case symbol_kind::S_struct_exp_field_cl: // struct_exp_field_cl
        yylhs.value.emplace< std::vector<pdm::ast::StructExp::Field*> > ();
        break;

      case symbol_kind::S_struct_type_spec_field_cl: // struct_type_spec_field_cl
        yylhs.value.emplace< std::vector<pdm::ast::StructTypeSpec::Field*> > ();
        break;

      case symbol_kind::S_targ_cl: // targ_cl
        yylhs.value.emplace< std::vector<pdm::ast::TArg*> > ();
        break;

      case symbol_kind::S_tpattern_field_cl1: // tpattern_field_cl1
        yylhs.value.emplace< std::vector<pdm::ast::TPattern::Field*> > ();
        break;

      case symbol_kind::S_type_query_exp_sl0: // type_query_exp_sl0
        yylhs.value.emplace< std::vector<pdm::ast::TypeQueryExp*> > ();
        break;

      case symbol_kind::S_type_spec_cl2: // type_spec_cl2
        yylhs.value.emplace< std::vector<pdm::ast::TypeSpec*> > ();
        break;

      case symbol_kind::S_varg_cl: // varg_cl
        yylhs.value.emplace< std::vector<pdm::ast::VArg*> > ();
        break;

      case symbol_kind::S_vpattern_field_cl: // vpattern_field_cl
        yylhs.value.emplace< std::vector<pdm::ast::VPattern::Field*> > ();
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
  case 2: // script: script_header script_field_sl
#line 273 "parser.yy"
                                      {
    yylhs.value.as < pdm::ast::Script* > () = mgr->new_script(source, yylhs.location, std::move(yystack_[1].value.as < std::vector<pdm::ast::HeaderStmt*> > ()), std::move(yystack_[0].value.as < std::vector<pdm::ast::Script::Field*> > ()));

    // setting the returnp here => this is the node parser returns.  
    *returnp = yylhs.value.as < pdm::ast::Script* > (); 
}
#line 2230 "parser.tab.cc"
    break;

  case 3: // script_header: %empty
#line 281 "parser.yy"
                                                    { yylhs.value.as < std::vector<pdm::ast::HeaderStmt*> > ().reserve(16); }
#line 2236 "parser.tab.cc"
    break;

  case 4: // script_header: script_header script_header_stmt ";"
#line 282 "parser.yy"
                                                    { yylhs.value.as < std::vector<pdm::ast::HeaderStmt*> > () = std::move(yystack_[2].value.as < std::vector<pdm::ast::HeaderStmt*> > ()); yylhs.value.as < std::vector<pdm::ast::HeaderStmt*> > ().push_back(yystack_[1].value.as < pdm::ast::HeaderStmt* > ()); }
#line 2242 "parser.tab.cc"
    break;

  case 5: // script_header_stmt: import_stmt
#line 285 "parser.yy"
      { yylhs.value.as < pdm::ast::HeaderStmt* > () = yystack_[0].value.as < pdm::ast::HeaderStmt* > (); }
#line 2248 "parser.tab.cc"
    break;

  case 6: // script_field: "mod" vid mod_exp
#line 289 "parser.yy"
                          { yylhs.value.as < pdm::ast::Script::Field* > () = mgr->new_script_field(yylhs.location, yystack_[1].value.as < TokenInfo > ().ID_intstr, yystack_[0].value.as < pdm::ast::ModExp* > ()); }
#line 2254 "parser.tab.cc"
    break;

  case 7: // script_field_sl: script_field ";"
#line 292 "parser.yy"
                                                { yylhs.value.as < std::vector<pdm::ast::Script::Field*> > ().push_back(yystack_[1].value.as < pdm::ast::Script::Field* > ()); }
#line 2260 "parser.tab.cc"
    break;

  case 8: // script_field_sl: script_field_sl script_field ";"
#line 293 "parser.yy"
                                                { yylhs.value.as < std::vector<pdm::ast::Script::Field*> > () = std::move(yystack_[2].value.as < std::vector<pdm::ast::Script::Field*> > ()); yylhs.value.as < std::vector<pdm::ast::Script::Field*> > ().push_back(yystack_[1].value.as < pdm::ast::Script::Field* > ()); }
#line 2266 "parser.tab.cc"
    break;

  case 9: // mod_exp: "{" mod_field_sl "}"
#line 301 "parser.yy"
                                              { yylhs.value.as < pdm::ast::ModExp* > () = mgr->new_mod_exp(yylhs.location, nullptr, std::move(yystack_[1].value.as < std::vector<pdm::ast::ModExp::Field*> > ())); }
#line 2272 "parser.tab.cc"
    break;

  case 10: // mod_exp: tpattern "{" mod_field_sl "}"
#line 302 "parser.yy"
                                              { yylhs.value.as < pdm::ast::ModExp* > () = mgr->new_mod_exp(yylhs.location, yystack_[3].value.as < pdm::ast::TPattern* > (), std::move(yystack_[1].value.as < std::vector<pdm::ast::ModExp::Field*> > ())); }
#line 2278 "parser.tab.cc"
    break;

  case 11: // mod_exp: "{" "}"
#line 303 "parser.yy"
                                              { yylhs.value.as < pdm::ast::ModExp* > () = mgr->new_mod_exp(yylhs.location, nullptr, std::move(std::vector<ast::ModExp::Field*>{})); }
#line 2284 "parser.tab.cc"
    break;

  case 12: // mod_exp: tpattern "{" "}"
#line 304 "parser.yy"
                                              { yylhs.value.as < pdm::ast::ModExp* > () = mgr->new_mod_exp(yylhs.location, yystack_[2].value.as < pdm::ast::TPattern* > (), std::move(std::vector<ast::ModExp::Field*>{})); }
#line 2290 "parser.tab.cc"
    break;

  case 13: // mod_field_sl: mod_field ";"
#line 307 "parser.yy"
                                        { yylhs.value.as < std::vector<pdm::ast::ModExp::Field*> > ().push_back(yystack_[1].value.as < pdm::ast::ModExp::Field* > ()); }
#line 2296 "parser.tab.cc"
    break;

  case 14: // mod_field_sl: mod_field_sl mod_field ";"
#line 308 "parser.yy"
                                        { yylhs.value.as < std::vector<pdm::ast::ModExp::Field*> > () = std::move(yystack_[2].value.as < std::vector<pdm::ast::ModExp::Field*> > ()); yylhs.value.as < std::vector<pdm::ast::ModExp::Field*> > ().push_back(yystack_[1].value.as < pdm::ast::ModExp::Field* > ()); }
#line 2302 "parser.tab.cc"
    break;

  case 15: // mod_field: vid "=" long_exp
#line 311 "parser.yy"
                           { yylhs.value.as < pdm::ast::ModExp::Field* > () = mgr->new_value_mod_field(yylhs.location, yystack_[2].value.as < TokenInfo > ().ID_intstr, yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2308 "parser.tab.cc"
    break;

  case 16: // mod_field: tid "=" type_spec
#line 312 "parser.yy"
                           { yylhs.value.as < pdm::ast::ModExp::Field* > () = mgr->new_type_mod_field(yylhs.location, yystack_[2].value.as < TokenInfo > ().ID_intstr, yystack_[0].value.as < pdm::ast::TypeSpec* > ()); }
#line 2314 "parser.tab.cc"
    break;

  case 17: // mod_field: cid "=" class_spec
#line 313 "parser.yy"
                           { yylhs.value.as < pdm::ast::ModExp::Field* > () = mgr->new_class_mod_field(yylhs.location, yystack_[2].value.as < TokenInfo > ().ID_intstr, yystack_[0].value.as < pdm::ast::ClassSpec* > ()); }
#line 2320 "parser.tab.cc"
    break;

  case 18: // mod_field: "mod" vid mod_exp
#line 314 "parser.yy"
                           { yylhs.value.as < pdm::ast::ModExp::Field* > () = mgr->new_mod_mod_field(yylhs.location, yystack_[1].value.as < TokenInfo > ().ID_intstr, yystack_[0].value.as < pdm::ast::ModExp* > ()); }
#line 2326 "parser.tab.cc"
    break;

  case 19: // import_stmt: "mod" vid "from" stringl "as" stringl
#line 322 "parser.yy"
                                                  { yylhs.value.as < pdm::ast::HeaderStmt* > () = mgr->new_import_stmt(yylhs.location, yystack_[4].value.as < TokenInfo > ().ID_intstr, *yystack_[2].value.as < TokenInfo > ().String_utf8string, *yystack_[0].value.as < TokenInfo > ().String_utf8string); }
#line 2332 "parser.tab.cc"
    break;

  case 20: // chain_prefix_stmt: const_stmt
#line 326 "parser.yy"
      { yylhs.value.as < pdm::ast::Stmt* > () = yystack_[0].value.as < pdm::ast::Stmt* > (); }
#line 2338 "parser.tab.cc"
    break;

  case 21: // chain_prefix_stmt: val_stmt
#line 327 "parser.yy"
      { yylhs.value.as < pdm::ast::Stmt* > () = yystack_[0].value.as < pdm::ast::Stmt* > (); }
#line 2344 "parser.tab.cc"
    break;

  case 22: // chain_prefix_stmt: var_stmt
#line 328 "parser.yy"
      { yylhs.value.as < pdm::ast::Stmt* > () = yystack_[0].value.as < pdm::ast::Stmt* > (); }
#line 2350 "parser.tab.cc"
    break;

  case 23: // chain_prefix_stmt: set_stmt
#line 329 "parser.yy"
      { yylhs.value.as < pdm::ast::Stmt* > () = yystack_[0].value.as < pdm::ast::Stmt* > (); }
#line 2356 "parser.tab.cc"
    break;

  case 24: // chain_prefix_stmt: discard_stmt
#line 330 "parser.yy"
      { yylhs.value.as < pdm::ast::Stmt* > () = yystack_[0].value.as < pdm::ast::Stmt* > (); }
#line 2362 "parser.tab.cc"
    break;

  case 25: // const_stmt: "const" lpattern "=" expr
#line 333 "parser.yy"
                                  { yylhs.value.as < pdm::ast::Stmt* > () = mgr->new_const_stmt(yylhs.location, yystack_[2].value.as < pdm::ast::LPattern* > (), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2368 "parser.tab.cc"
    break;

  case 26: // val_stmt: "val" lpattern "=" expr
#line 336 "parser.yy"
                                  { yylhs.value.as < pdm::ast::Stmt* > () = mgr->new_val_stmt(yylhs.location, yystack_[2].value.as < pdm::ast::LPattern* > (), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2374 "parser.tab.cc"
    break;

  case 27: // var_stmt: "var" lpattern "=" expr
#line 339 "parser.yy"
                                  { yylhs.value.as < pdm::ast::Stmt* > () = mgr->new_var_stmt(yylhs.location, yystack_[2].value.as < pdm::ast::LPattern* > (), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2380 "parser.tab.cc"
    break;

  case 28: // set_stmt: "set" expr "=" expr
#line 342 "parser.yy"
                              { yylhs.value.as < pdm::ast::Stmt* > () = mgr->new_set_stmt(yylhs.location, yystack_[2].value.as < pdm::ast::Exp* > (), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2386 "parser.tab.cc"
    break;

  case 29: // discard_stmt: "discard" expr
#line 345 "parser.yy"
                        { yylhs.value.as < pdm::ast::Stmt* > () = mgr->new_discard_stmt(yylhs.location, yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2392 "parser.tab.cc"
    break;

  case 30: // tid: "TypeId"
#line 352 "parser.yy"
     { yylhs.value.as < TokenInfo > () = yystack_[0].value.as < TokenInfo > (); }
#line 2398 "parser.tab.cc"
    break;

  case 31: // vid: "val_id"
#line 353 "parser.yy"
     { yylhs.value.as < TokenInfo > () = yystack_[0].value.as < TokenInfo > (); }
#line 2404 "parser.tab.cc"
    break;

  case 32: // cid: "CLS_ID"
#line 354 "parser.yy"
     { yylhs.value.as < TokenInfo > () = yystack_[0].value.as < TokenInfo > (); }
#line 2410 "parser.tab.cc"
    break;

  case 33: // floatl: "4.2"
#line 357 "parser.yy"
      { yylhs.value.as < TokenInfo > () = yystack_[0].value.as < TokenInfo > (); }
#line 2416 "parser.tab.cc"
    break;

  case 34: // stringl: "'sq-string-literal'"
#line 360 "parser.yy"
      { yylhs.value.as < TokenInfo > () = yystack_[0].value.as < TokenInfo > (); }
#line 2422 "parser.tab.cc"
    break;

  case 35: // stringl: "\"dq-string-literal\""
#line 361 "parser.yy"
      { yylhs.value.as < TokenInfo > () = yystack_[0].value.as < TokenInfo > (); }
#line 2428 "parser.tab.cc"
    break;

  case 36: // mod_prefix: vid "::"
#line 364 "parser.yy"
                                                      { yylhs.value.as < pdm::ast::ModAddress* > () = mgr->new_mod_address(yylhs.location, nullptr, yystack_[1].value.as < TokenInfo > ().ID_intstr, std::move(std::vector<ast::TArg*>{})); }
#line 2434 "parser.tab.cc"
    break;

  case 37: // mod_prefix: vid "[" targ_cl "]" "::"
#line 365 "parser.yy"
                                                      { yylhs.value.as < pdm::ast::ModAddress* > () = mgr->new_mod_address(yylhs.location, nullptr, yystack_[4].value.as < TokenInfo > ().ID_intstr, std::move(yystack_[2].value.as < std::vector<pdm::ast::TArg*> > ())); }
#line 2440 "parser.tab.cc"
    break;

  case 38: // mod_prefix: mod_prefix vid "::"
#line 366 "parser.yy"
                                                      { yylhs.value.as < pdm::ast::ModAddress* > () = mgr->new_mod_address(yylhs.location, yystack_[2].value.as < pdm::ast::ModAddress* > (), yystack_[1].value.as < TokenInfo > ().ID_intstr, std::move(std::vector<ast::TArg*>{})); }
#line 2446 "parser.tab.cc"
    break;

  case 39: // mod_prefix: mod_prefix vid "[" targ_cl "]" "::"
#line 367 "parser.yy"
                                                      { yylhs.value.as < pdm::ast::ModAddress* > () = mgr->new_mod_address(yylhs.location, yystack_[5].value.as < pdm::ast::ModAddress* > (), yystack_[4].value.as < TokenInfo > ().ID_intstr, std::move(yystack_[2].value.as < std::vector<pdm::ast::TArg*> > ())); }
#line 2452 "parser.tab.cc"
    break;

  case 40: // expr: binary_exp
#line 374 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2458 "parser.tab.cc"
    break;

  case 41: // long_exp: expr
#line 377 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2464 "parser.tab.cc"
    break;

  case 42: // long_exp: lambda_exp
#line 378 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2470 "parser.tab.cc"
    break;

  case 43: // expr_cl2: expr "," expr
#line 390 "parser.yy"
                             { yylhs.value.as < std::vector<pdm::ast::Exp*> > ().reserve(2); yylhs.value.as < std::vector<pdm::ast::Exp*> > ().push_back(yystack_[2].value.as < pdm::ast::Exp* > ()); yylhs.value.as < std::vector<pdm::ast::Exp*> > ().push_back(yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2476 "parser.tab.cc"
    break;

  case 44: // expr_cl2: expr_cl2 "," expr
#line 391 "parser.yy"
                             { yylhs.value.as < std::vector<pdm::ast::Exp*> > () = std::move(yystack_[2].value.as < std::vector<pdm::ast::Exp*> > ()); yylhs.value.as < std::vector<pdm::ast::Exp*> > ().push_back(yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2482 "parser.tab.cc"
    break;

  case 45: // type_query_exp_sl0: %empty
#line 394 "parser.yy"
                                                  {}
#line 2488 "parser.tab.cc"
    break;

  case 46: // type_query_exp_sl0: type_query_exp_sl0 type_query_exp ";"
#line 395 "parser.yy"
                                                  { yylhs.value.as < std::vector<pdm::ast::TypeQueryExp*> > () = std::move(yystack_[2].value.as < std::vector<pdm::ast::TypeQueryExp*> > ()); yylhs.value.as < std::vector<pdm::ast::TypeQueryExp*> > ().push_back(yystack_[1].value.as < pdm::ast::TypeQueryExp* > ()); }
#line 2494 "parser.tab.cc"
    break;

  case 47: // bracketed_exp: paren_exp
#line 399 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2500 "parser.tab.cc"
    break;

  case 48: // bracketed_exp: vtupleExpr
#line 400 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2506 "parser.tab.cc"
    break;

  case 49: // bracketed_exp: vstructExpr
#line 401 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2512 "parser.tab.cc"
    break;

  case 50: // bracketed_exp: chain_exp
#line 402 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2518 "parser.tab.cc"
    break;

  case 51: // paren_exp: "(" long_exp ")"
#line 413 "parser.yy"
                              { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_paren_exp(yylhs.location, yystack_[1].value.as < pdm::ast::Exp* > ()); }
#line 2524 "parser.tab.cc"
    break;

  case 52: // vtupleExpr: "(" ")"
#line 416 "parser.yy"
                                   { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_tuple_exp(yylhs.location, std::move(std::vector<ast::Exp*>())); }
#line 2530 "parser.tab.cc"
    break;

  case 53: // vtupleExpr: "(" expr "," ")"
#line 417 "parser.yy"
                                   { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_tuple_exp(yylhs.location, std::move(std::vector(1,yystack_[2].value.as < pdm::ast::Exp* > ()))); }
#line 2536 "parser.tab.cc"
    break;

  case 54: // vtupleExpr: "(" expr_cl2 ")"
#line 418 "parser.yy"
                                   { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_tuple_exp(yylhs.location, std::move(yystack_[1].value.as < std::vector<pdm::ast::Exp*> > ())); }
#line 2542 "parser.tab.cc"
    break;

  case 55: // vstructExpr: "{" struct_exp_field_cl "}"
#line 421 "parser.yy"
                                            { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_struct_exp(yylhs.location, std::move(yystack_[1].value.as < std::vector<pdm::ast::StructExp::Field*> > ())); }
#line 2548 "parser.tab.cc"
    break;

  case 56: // primary_exp: bracketed_exp
#line 424 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2554 "parser.tab.cc"
    break;

  case 57: // primary_exp: vid
#line 425 "parser.yy"
                     { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_id_exp(yylhs.location, yystack_[0].value.as < TokenInfo > ().ID_intstr); }
#line 2560 "parser.tab.cc"
    break;

  case 58: // primary_exp: int_expr
#line 426 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2566 "parser.tab.cc"
    break;

  case 59: // primary_exp: floatl
#line 427 "parser.yy"
                     { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_float_exp(yylhs.location, yystack_[0].value.as < TokenInfo > ().Float); }
#line 2572 "parser.tab.cc"
    break;

  case 60: // primary_exp: stringls
#line 428 "parser.yy"
                     { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_string_exp(yylhs.location, std::move(yystack_[0].value.as < std::vector<pdm::ast::StringExp::Piece> > ())); }
#line 2578 "parser.tab.cc"
    break;

  case 61: // primary_exp: if_exp
#line 429 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2584 "parser.tab.cc"
    break;

  case 62: // primary_exp: mod_prefix vid
#line 430 "parser.yy"
                        { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_module_dot_name_exp(yylhs.location, yystack_[1].value.as < pdm::ast::ModAddress* > (), yystack_[0].value.as < TokenInfo > ().ID_intstr); }
#line 2590 "parser.tab.cc"
    break;

  case 63: // int_expr: "42"
#line 433 "parser.yy"
                { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_int_exp(yylhs.location, yystack_[0].value.as < TokenInfo > ().Int, ast::IntExp::Base::Dec, false); }
#line 2596 "parser.tab.cc"
    break;

  case 64: // int_expr: "0x2a"
#line 434 "parser.yy"
                { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_int_exp(yylhs.location, yystack_[0].value.as < TokenInfo > ().Int, ast::IntExp::Base::Hex, false); }
#line 2602 "parser.tab.cc"
    break;

  case 65: // int_expr: "42u"
#line 435 "parser.yy"
                         { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_int_exp(yylhs.location, yystack_[0].value.as < TokenInfo > ().Int, ast::IntExp::Base::Dec, true); }
#line 2608 "parser.tab.cc"
    break;

  case 66: // int_expr: "0x2Au"
#line 436 "parser.yy"
                         { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_int_exp(yylhs.location, yystack_[0].value.as < TokenInfo > ().Int, ast::IntExp::Base::Hex, true); }
#line 2614 "parser.tab.cc"
    break;

  case 67: // stringls: "'sq-string-literal'"
#line 439 "parser.yy"
                             { yylhs.value.as < std::vector<pdm::ast::StringExp::Piece> > ().emplace_back(yylhs.location, *yystack_[0].value.as < TokenInfo > ().String_utf8string, ast::StringExp::QuoteKind::SingleQuote); }
#line 2620 "parser.tab.cc"
    break;

  case 68: // stringls: "\"dq-string-literal\""
#line 440 "parser.yy"
                             { yylhs.value.as < std::vector<pdm::ast::StringExp::Piece> > ().emplace_back(yylhs.location, *yystack_[0].value.as < TokenInfo > ().String_utf8string, ast::StringExp::QuoteKind::DoubleQuote); }
#line 2626 "parser.tab.cc"
    break;

  case 69: // stringls: stringls "'sq-string-literal'"
#line 441 "parser.yy"
                             { yylhs.value.as < std::vector<pdm::ast::StringExp::Piece> > () = std::move(yystack_[1].value.as < std::vector<pdm::ast::StringExp::Piece> > ()); yylhs.value.as < std::vector<pdm::ast::StringExp::Piece> > ().emplace_back(yystack_[0].location, *yystack_[0].value.as < TokenInfo > ().String_utf8string, ast::StringExp::QuoteKind::SingleQuote); }
#line 2632 "parser.tab.cc"
    break;

  case 70: // stringls: stringls "\"dq-string-literal\""
#line 442 "parser.yy"
                             { yylhs.value.as < std::vector<pdm::ast::StringExp::Piece> > () = std::move(yystack_[1].value.as < std::vector<pdm::ast::StringExp::Piece> > ()); yylhs.value.as < std::vector<pdm::ast::StringExp::Piece> > ().emplace_back(yystack_[0].location, *yystack_[0].value.as < TokenInfo > ().String_utf8string, ast::StringExp::QuoteKind::DoubleQuote); }
#line 2638 "parser.tab.cc"
    break;

  case 71: // if_exp: "if" bracketed_exp "then" bracketed_exp
#line 445 "parser.yy"
                                                                        { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_if_exp(yylhs.location, yystack_[2].value.as < pdm::ast::Exp* > (), yystack_[0].value.as < pdm::ast::Exp* > (), nullptr); }
#line 2644 "parser.tab.cc"
    break;

  case 72: // if_exp: "if" bracketed_exp "then" bracketed_exp "else" primary_exp
#line 446 "parser.yy"
                                                                        { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_if_exp(yylhs.location, yystack_[4].value.as < pdm::ast::Exp* > (), yystack_[2].value.as < pdm::ast::Exp* > (), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2650 "parser.tab.cc"
    break;

  case 73: // chain_exp: "{" "}"
#line 449 "parser.yy"
                                               { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_chain_exp(yylhs.location, std::move(std::vector<ast::Stmt*>{}), nullptr); }
#line 2656 "parser.tab.cc"
    break;

  case 74: // chain_exp: "{" long_exp "}"
#line 450 "parser.yy"
                                               { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_chain_exp(yylhs.location, std::move(std::vector<ast::Stmt*>{}), yystack_[1].value.as < pdm::ast::Exp* > ()); }
#line 2662 "parser.tab.cc"
    break;

  case 75: // chain_exp: "{" chain_prefix "}"
#line 451 "parser.yy"
                                               { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_chain_exp(yylhs.location, std::move(yystack_[1].value.as < std::vector<pdm::ast::Stmt*> > ()), nullptr); }
#line 2668 "parser.tab.cc"
    break;

  case 76: // chain_exp: "{" chain_prefix long_exp "}"
#line 452 "parser.yy"
                                               { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_chain_exp(yylhs.location, std::move(yystack_[2].value.as < std::vector<pdm::ast::Stmt*> > ()), yystack_[1].value.as < pdm::ast::Exp* > ()); }
#line 2674 "parser.tab.cc"
    break;

  case 77: // chain_prefix: chain_prefix_stmt ";"
#line 455 "parser.yy"
                                                { yylhs.value.as < std::vector<pdm::ast::Stmt*> > ().push_back(yystack_[1].value.as < pdm::ast::Stmt* > ()); }
#line 2680 "parser.tab.cc"
    break;

  case 78: // chain_prefix: chain_prefix chain_prefix_stmt ";"
#line 456 "parser.yy"
                                                { yylhs.value.as < std::vector<pdm::ast::Stmt*> > () = std::move(yystack_[2].value.as < std::vector<pdm::ast::Stmt*> > ()); yylhs.value.as < std::vector<pdm::ast::Stmt*> > ().push_back(yystack_[1].value.as < pdm::ast::Stmt* > ()); }
#line 2686 "parser.tab.cc"
    break;

  case 79: // lambda_exp: fn_type_spec bracketed_exp
#line 459 "parser.yy"
                                   { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_lambda_exp(yylhs.location, yystack_[1].value.as < pdm::ast::FnTypeSpec* > (), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2692 "parser.tab.cc"
    break;

  case 80: // postfix_exp: primary_exp
#line 463 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2698 "parser.tab.cc"
    break;

  case 81: // postfix_exp: vcall_exp
#line 464 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2704 "parser.tab.cc"
    break;

  case 82: // postfix_exp: dot_name_exp
#line 465 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2710 "parser.tab.cc"
    break;

  case 83: // postfix_exp: dot_index_exp
#line 466 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2716 "parser.tab.cc"
    break;

  case 84: // vcall_exp: postfix_exp "(" ")"
#line 469 "parser.yy"
                                            { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_vcall_exp(yylhs.location, yystack_[2].value.as < pdm::ast::Exp* > (), std::move(std::vector<ast::VArg*>{})); }
#line 2722 "parser.tab.cc"
    break;

  case 85: // vcall_exp: postfix_exp "(" varg_cl ")"
#line 470 "parser.yy"
                                            { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_vcall_exp(yylhs.location, yystack_[3].value.as < pdm::ast::Exp* > (), std::move(yystack_[1].value.as < std::vector<pdm::ast::VArg*> > ())); }
#line 2728 "parser.tab.cc"
    break;

  case 86: // dot_name_exp: postfix_exp "." "val_id"
#line 473 "parser.yy"
                                                { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_struct_dot_name_exp(yylhs.location, yystack_[2].value.as < pdm::ast::Exp* > (), yystack_[0].value.as < TokenInfo > ().ID_intstr); }
#line 2734 "parser.tab.cc"
    break;

  case 87: // dot_name_exp: type_spec "::" "TypeId"
#line 474 "parser.yy"
                                                    { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_enum_dot_name_exp(yylhs.location, yystack_[2].value.as < pdm::ast::TypeSpec* > (), yystack_[0].value.as < TokenInfo > ().ID_intstr, nullptr); }
#line 2740 "parser.tab.cc"
    break;

  case 88: // dot_name_exp: type_spec "::" "TypeId" "using" paren_exp
#line 475 "parser.yy"
                                                    { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_enum_dot_name_exp(yylhs.location, yystack_[4].value.as < pdm::ast::TypeSpec* > (), yystack_[2].value.as < TokenInfo > ().ID_intstr, yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2746 "parser.tab.cc"
    break;

  case 89: // dot_index_exp: postfix_exp "." int_expr
#line 478 "parser.yy"
                                    { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_dot_index_exp(yylhs.location, yystack_[2].value.as < pdm::ast::Exp* > (), yystack_[0].value.as < pdm::ast::Exp* > (), ast::DotIndexExp::RhsHint::LhsNotPtr); }
#line 2752 "parser.tab.cc"
    break;

  case 90: // dot_index_exp: postfix_exp "." bracketed_exp
#line 479 "parser.yy"
                                    { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_dot_index_exp(yylhs.location, yystack_[2].value.as < pdm::ast::Exp* > (), yystack_[0].value.as < pdm::ast::Exp* > (), ast::DotIndexExp::RhsHint::LhsNotPtr); }
#line 2758 "parser.tab.cc"
    break;

  case 91: // unary_exp: postfix_exp
#line 483 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2764 "parser.tab.cc"
    break;

  case 92: // unary_exp: unary_op unary_exp
#line 484 "parser.yy"
                             { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_unary_exp(yylhs.location, yystack_[1].value.as < pdm::ast::UnaryOperator > (), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2770 "parser.tab.cc"
    break;

  case 93: // unary_op: "+"
#line 487 "parser.yy"
                 { yylhs.value.as < pdm::ast::UnaryOperator > () = ast::UnaryOperator::Plus; }
#line 2776 "parser.tab.cc"
    break;

  case 94: // unary_op: "-"
#line 488 "parser.yy"
                 { yylhs.value.as < pdm::ast::UnaryOperator > () = ast::UnaryOperator::Minus; }
#line 2782 "parser.tab.cc"
    break;

  case 95: // unary_op: "not"
#line 489 "parser.yy"
                 { yylhs.value.as < pdm::ast::UnaryOperator > () = ast::UnaryOperator::Not; }
#line 2788 "parser.tab.cc"
    break;

  case 96: // binary_exp: or_binary_exp
#line 493 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2794 "parser.tab.cc"
    break;

  case 97: // mul_binary_op: "*"
#line 496 "parser.yy"
                 { yylhs.value.as < pdm::ast::BinaryOperator > () = ast::BinaryOperator::Mul; }
#line 2800 "parser.tab.cc"
    break;

  case 98: // mul_binary_op: "/"
#line 497 "parser.yy"
                 { yylhs.value.as < pdm::ast::BinaryOperator > () = ast::BinaryOperator::Div; }
#line 2806 "parser.tab.cc"
    break;

  case 99: // mul_binary_op: "%"
#line 498 "parser.yy"
                 { yylhs.value.as < pdm::ast::BinaryOperator > () = ast::BinaryOperator::Rem; }
#line 2812 "parser.tab.cc"
    break;

  case 100: // mul_binary_exp: unary_exp
#line 501 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2818 "parser.tab.cc"
    break;

  case 101: // mul_binary_exp: mul_binary_exp mul_binary_op unary_exp
#line 502 "parser.yy"
                                               { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_binary_exp(yylhs.location, yystack_[1].value.as < pdm::ast::BinaryOperator > (), yystack_[2].value.as < pdm::ast::Exp* > (), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2824 "parser.tab.cc"
    break;

  case 102: // add_binary_op: "+"
#line 505 "parser.yy"
             { yylhs.value.as < pdm::ast::BinaryOperator > () = ast::BinaryOperator::Add; }
#line 2830 "parser.tab.cc"
    break;

  case 103: // add_binary_op: "-"
#line 506 "parser.yy"
             { yylhs.value.as < pdm::ast::BinaryOperator > () = ast::BinaryOperator::Subtract; }
#line 2836 "parser.tab.cc"
    break;

  case 104: // add_binary_exp: mul_binary_exp
#line 509 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2842 "parser.tab.cc"
    break;

  case 105: // add_binary_exp: add_binary_exp add_binary_op mul_binary_exp
#line 510 "parser.yy"
                                                    { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_binary_exp(yylhs.location, yystack_[1].value.as < pdm::ast::BinaryOperator > (), yystack_[2].value.as < pdm::ast::Exp* > (), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2848 "parser.tab.cc"
    break;

  case 106: // cmp_binary_op: "<"
#line 513 "parser.yy"
                { yylhs.value.as < pdm::ast::BinaryOperator > () = ast::BinaryOperator::Less; }
#line 2854 "parser.tab.cc"
    break;

  case 107: // cmp_binary_op: "<="
#line 514 "parser.yy"
                { yylhs.value.as < pdm::ast::BinaryOperator > () = ast::BinaryOperator::LessOrEq; }
#line 2860 "parser.tab.cc"
    break;

  case 108: // cmp_binary_op: ">"
#line 515 "parser.yy"
                { yylhs.value.as < pdm::ast::BinaryOperator > () = ast::BinaryOperator::Greater; }
#line 2866 "parser.tab.cc"
    break;

  case 109: // cmp_binary_op: ">="
#line 516 "parser.yy"
                { yylhs.value.as < pdm::ast::BinaryOperator > () = ast::BinaryOperator::GreaterOrEq; }
#line 2872 "parser.tab.cc"
    break;

  case 110: // cmp_binary_exp: add_binary_exp
#line 519 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2878 "parser.tab.cc"
    break;

  case 111: // cmp_binary_exp: cmp_binary_exp cmp_binary_op add_binary_exp
#line 520 "parser.yy"
                                                    { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_binary_exp(yylhs.location, yystack_[1].value.as < pdm::ast::BinaryOperator > (), yystack_[2].value.as < pdm::ast::Exp* > (), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2884 "parser.tab.cc"
    break;

  case 112: // eq_binary_op: "=="
#line 523 "parser.yy"
                 { yylhs.value.as < pdm::ast::BinaryOperator > () = ast::BinaryOperator::Equals; }
#line 2890 "parser.tab.cc"
    break;

  case 113: // eq_binary_op: "!="
#line 524 "parser.yy"
                 { yylhs.value.as < pdm::ast::BinaryOperator > () = ast::BinaryOperator::NotEquals; }
#line 2896 "parser.tab.cc"
    break;

  case 114: // eq_binary_exp: cmp_binary_exp
#line 527 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2902 "parser.tab.cc"
    break;

  case 115: // eq_binary_exp: eq_binary_exp eq_binary_op cmp_binary_exp
#line 528 "parser.yy"
                                                { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_binary_exp(yylhs.location, yystack_[1].value.as < pdm::ast::BinaryOperator > (), yystack_[2].value.as < pdm::ast::Exp* > (), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2908 "parser.tab.cc"
    break;

  case 116: // and_binary_exp: eq_binary_exp
#line 531 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2914 "parser.tab.cc"
    break;

  case 117: // and_binary_exp: and_binary_exp "and" eq_binary_exp
#line 532 "parser.yy"
                                           { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_binary_exp(yylhs.location, ast::BinaryOperator::And, yystack_[2].value.as < pdm::ast::Exp* > (), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2920 "parser.tab.cc"
    break;

  case 118: // xor_binary_exp: and_binary_exp
#line 535 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2926 "parser.tab.cc"
    break;

  case 119: // xor_binary_exp: xor_binary_exp "xor" and_binary_exp
#line 536 "parser.yy"
                                           { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_binary_exp(yylhs.location, ast::BinaryOperator::XOr, yystack_[2].value.as < pdm::ast::Exp* > (), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2932 "parser.tab.cc"
    break;

  case 120: // or_binary_exp: xor_binary_exp
#line 539 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2938 "parser.tab.cc"
    break;

  case 121: // or_binary_exp: or_binary_exp "or" xor_binary_exp
#line 540 "parser.yy"
                                           { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_binary_exp(yylhs.location, ast::BinaryOperator::Or, yystack_[2].value.as < pdm::ast::Exp* > (), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2944 "parser.tab.cc"
    break;

  case 122: // type_query_exp: type_spec type_query_op type_spec
#line 544 "parser.yy"
                                          { yylhs.value.as < pdm::ast::TypeQueryExp* > () = mgr->new_type_query_exp(yylhs.location, yystack_[1].value.as < pdm::ast::TypeQueryKind > (), yystack_[2].value.as < pdm::ast::TypeSpec* > (), yystack_[0].value.as < pdm::ast::TypeSpec* > ()); }
#line 2950 "parser.tab.cc"
    break;

  case 123: // type_query_op: ":<"
#line 547 "parser.yy"
                    { yylhs.value.as < pdm::ast::TypeQueryKind > () = ast::TypeQueryKind::LhsSubtypesRhs; }
#line 2956 "parser.tab.cc"
    break;

  case 124: // type_query_op: ">:"
#line 548 "parser.yy"
                    { yylhs.value.as < pdm::ast::TypeQueryKind > () = ast::TypeQueryKind::LhsSupertypesRhs; }
#line 2962 "parser.tab.cc"
    break;

  case 125: // type_query_op: "=="
#line 549 "parser.yy"
                    { yylhs.value.as < pdm::ast::TypeQueryKind > () = ast::TypeQueryKind::LhsEqualsRhs; }
#line 2968 "parser.tab.cc"
    break;

  case 126: // type_spec_cl2: type_spec "," type_spec
#line 564 "parser.yy"
                                    { yylhs.value.as < std::vector<pdm::ast::TypeSpec*> > ().reserve(2); yylhs.value.as < std::vector<pdm::ast::TypeSpec*> > ().push_back(yystack_[2].value.as < pdm::ast::TypeSpec* > ()); yylhs.value.as < std::vector<pdm::ast::TypeSpec*> > ().push_back(yystack_[0].value.as < pdm::ast::TypeSpec* > ()); }
#line 2974 "parser.tab.cc"
    break;

  case 127: // type_spec_cl2: type_spec_cl2 "," type_spec
#line 565 "parser.yy"
                                    { yylhs.value.as < std::vector<pdm::ast::TypeSpec*> > () = std::move(yystack_[2].value.as < std::vector<pdm::ast::TypeSpec*> > ()); yylhs.value.as < std::vector<pdm::ast::TypeSpec*> > ().push_back(yystack_[0].value.as < pdm::ast::TypeSpec* > ()); }
#line 2980 "parser.tab.cc"
    break;

  case 128: // type_spec: tid
#line 569 "parser.yy"
                        { yylhs.value.as < pdm::ast::TypeSpec* > () = mgr->new_id_type_spec(yylhs.location, yystack_[0].value.as < TokenInfo > ().ID_intstr); }
#line 2986 "parser.tab.cc"
    break;

  case 129: // type_spec: mod_prefix_tid
#line 570 "parser.yy"
      { yylhs.value.as < pdm::ast::TypeSpec* > () = yystack_[0].value.as < pdm::ast::TypeSpec* > (); }
#line 2992 "parser.tab.cc"
    break;

  case 130: // type_spec: tuple_type_spec
#line 571 "parser.yy"
      { yylhs.value.as < pdm::ast::TypeSpec* > () = yystack_[0].value.as < pdm::ast::TypeSpec* > (); }
#line 2998 "parser.tab.cc"
    break;

  case 131: // type_spec: array_type_spec
#line 572 "parser.yy"
      { yylhs.value.as < pdm::ast::TypeSpec* > () = yystack_[0].value.as < pdm::ast::TypeSpec* > (); }
#line 3004 "parser.tab.cc"
    break;

  case 132: // type_spec: struct_type_spec
#line 573 "parser.yy"
      { yylhs.value.as < pdm::ast::TypeSpec* > () = yystack_[0].value.as < pdm::ast::TypeSpec* > (); }
#line 3010 "parser.tab.cc"
    break;

  case 133: // type_spec: enum_type_spec
#line 574 "parser.yy"
      { yylhs.value.as < pdm::ast::TypeSpec* > () = yystack_[0].value.as < pdm::ast::TypeSpec* > (); }
#line 3016 "parser.tab.cc"
    break;

  case 134: // type_spec: fn_type_spec
#line 575 "parser.yy"
                    { yylhs.value.as < pdm::ast::TypeSpec* > () = dynamic_cast<ast::TypeSpec*>(yystack_[0].value.as < pdm::ast::FnTypeSpec* > ()); }
#line 3022 "parser.tab.cc"
    break;

  case 135: // mod_prefix_tid: mod_prefix tid
#line 579 "parser.yy"
                            { yylhs.value.as < pdm::ast::TypeSpec* > () = mgr->new_ma_type_spec(yylhs.location, yystack_[1].value.as < pdm::ast::ModAddress* > (), yystack_[0].value.as < TokenInfo > ().ID_intstr); }
#line 3028 "parser.tab.cc"
    break;

  case 136: // tuple_type_spec: "{" type_spec "}"
#line 583 "parser.yy"
                                   { yylhs.value.as < pdm::ast::TypeSpec* > () = mgr->new_tuple_type_spec(yylhs.location, std::move(std::vector(1,yystack_[1].value.as < pdm::ast::TypeSpec* > ()))); }
#line 3034 "parser.tab.cc"
    break;

  case 137: // tuple_type_spec: "{" type_spec_cl2 "}"
#line 584 "parser.yy"
                                   { yylhs.value.as < pdm::ast::TypeSpec* > () = mgr->new_tuple_type_spec(yylhs.location, std::move(yystack_[1].value.as < std::vector<pdm::ast::TypeSpec*> > ())); }
#line 3040 "parser.tab.cc"
    break;

  case 138: // array_type_spec: "[" type_spec "*" expr "]"
#line 587 "parser.yy"
                                                { yylhs.value.as < pdm::ast::TypeSpec* > () = nullptr; }
#line 3046 "parser.tab.cc"
    break;

  case 139: // struct_type_spec: "{" struct_type_spec_field_cl "}"
#line 591 "parser.yy"
                                               { yylhs.value.as < pdm::ast::TypeSpec* > () = mgr->new_struct_type_spec(yylhs.location, std::move(yystack_[1].value.as < std::vector<pdm::ast::StructTypeSpec::Field*> > ())); }
#line 3052 "parser.tab.cc"
    break;

  case 140: // struct_type_spec_field_cl: struct_type_spec_field
#line 594 "parser.yy"
                                                              { yylhs.value.as < std::vector<pdm::ast::StructTypeSpec::Field*> > ().push_back(yystack_[0].value.as < pdm::ast::StructTypeSpec::Field* > ()); }
#line 3058 "parser.tab.cc"
    break;

  case 141: // struct_type_spec_field_cl: struct_type_spec_field_cl "," struct_type_spec_field
#line 595 "parser.yy"
                                                              { yylhs.value.as < std::vector<pdm::ast::StructTypeSpec::Field*> > () = std::move(yystack_[2].value.as < std::vector<pdm::ast::StructTypeSpec::Field*> > ()); yylhs.value.as < std::vector<pdm::ast::StructTypeSpec::Field*> > ().push_back(yystack_[0].value.as < pdm::ast::StructTypeSpec::Field* > ()); }
#line 3064 "parser.tab.cc"
    break;

  case 142: // struct_type_spec_field: vid type_spec
#line 598 "parser.yy"
                                    { yylhs.value.as < pdm::ast::StructTypeSpec::Field* > () = mgr->new_struct_type_spec_field(yylhs.location, yystack_[1].value.as < TokenInfo > ().ID_intstr, yystack_[0].value.as < pdm::ast::TypeSpec* > ()); }
#line 3070 "parser.tab.cc"
    break;

  case 143: // enum_type_spec_field: tid
#line 602 "parser.yy"
                        { yylhs.value.as < pdm::ast::EnumTypeSpec::Field* > () = mgr->new_enum_type_spec_field(yylhs.location, yystack_[0].value.as < TokenInfo > ().ID_intstr, nullptr); }
#line 3076 "parser.tab.cc"
    break;

  case 144: // enum_type_spec_field: tid type_spec
#line 603 "parser.yy"
                        { yylhs.value.as < pdm::ast::EnumTypeSpec::Field* > () = mgr->new_enum_type_spec_field(yylhs.location, yystack_[1].value.as < TokenInfo > ().ID_intstr, yystack_[0].value.as < pdm::ast::TypeSpec* > ()); }
#line 3082 "parser.tab.cc"
    break;

  case 145: // enum_type_spec_field_cl: enum_type_spec_field
#line 606 "parser.yy"
                                                            { yylhs.value.as < std::vector<pdm::ast::EnumTypeSpec::Field*> > ().push_back(yystack_[0].value.as < pdm::ast::EnumTypeSpec::Field* > ()); }
#line 3088 "parser.tab.cc"
    break;

  case 146: // enum_type_spec_field_cl: enum_type_spec_field_cl "," enum_type_spec_field
#line 607 "parser.yy"
                                                            { yylhs.value.as < std::vector<pdm::ast::EnumTypeSpec::Field*> > () = std::move(yystack_[2].value.as < std::vector<pdm::ast::EnumTypeSpec::Field*> > ()); yylhs.value.as < std::vector<pdm::ast::EnumTypeSpec::Field*> > ().push_back(yystack_[0].value.as < pdm::ast::EnumTypeSpec::Field* > ()); }
#line 3094 "parser.tab.cc"
    break;

  case 147: // enum_type_spec: "enum" "{" enum_type_spec_field_cl "}"
#line 610 "parser.yy"
                                                        { yylhs.value.as < pdm::ast::TypeSpec* > () = mgr->new_enum_type_spec(yylhs.location, std::move(yystack_[1].value.as < std::vector<pdm::ast::EnumTypeSpec::Field*> > ())); }
#line 3100 "parser.tab.cc"
    break;

  case 148: // fn_type_spec: "fn" vpattern "->" type_spec
#line 614 "parser.yy"
                                     { yylhs.value.as < pdm::ast::FnTypeSpec* > () = mgr->new_fn_type_spec(yylhs.location, std::move(yystack_[2].value.as < pdm::ast::VPattern* > ()), yystack_[0].value.as < pdm::ast::TypeSpec* > ()); }
#line 3106 "parser.tab.cc"
    break;

  case 149: // targ: type_spec
#line 618 "parser.yy"
                { yylhs.value.as < pdm::ast::TArg* > () = mgr->new_targ_type_spec(yylhs.location, yystack_[0].value.as < pdm::ast::TypeSpec* > ()); }
#line 3112 "parser.tab.cc"
    break;

  case 150: // targ: expr
#line 619 "parser.yy"
               { yylhs.value.as < pdm::ast::TArg* > () = mgr->new_targ_exp(yylhs.location, yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 3118 "parser.tab.cc"
    break;

  case 151: // targ_cl: targ
#line 622 "parser.yy"
                            { yylhs.value.as < std::vector<pdm::ast::TArg*> > ().push_back(yystack_[0].value.as < pdm::ast::TArg* > ()); }
#line 3124 "parser.tab.cc"
    break;

  case 152: // targ_cl: targ_cl "," targ
#line 623 "parser.yy"
                            { yylhs.value.as < std::vector<pdm::ast::TArg*> > () = std::move(yystack_[2].value.as < std::vector<pdm::ast::TArg*> > ()); yylhs.value.as < std::vector<pdm::ast::TArg*> > ().push_back(yystack_[0].value.as < pdm::ast::TArg* > ()); }
#line 3130 "parser.tab.cc"
    break;

  case 153: // varg: expr
#line 625 "parser.yy"
                            { yylhs.value.as < pdm::ast::VArg* > () = mgr->new_varg(yylhs.location, yystack_[0].value.as < pdm::ast::Exp* > (), ast::VArgAccessSpec::In); }
#line 3136 "parser.tab.cc"
    break;

  case 154: // varg: "out" expr
#line 626 "parser.yy"
                            { yylhs.value.as < pdm::ast::VArg* > () = mgr->new_varg(yylhs.location, yystack_[0].value.as < pdm::ast::Exp* > (), ast::VArgAccessSpec::Out); }
#line 3142 "parser.tab.cc"
    break;

  case 155: // varg: "inout" expr
#line 627 "parser.yy"
                            { yylhs.value.as < pdm::ast::VArg* > () = mgr->new_varg(yylhs.location, yystack_[0].value.as < pdm::ast::Exp* > (), ast::VArgAccessSpec::InOut); }
#line 3148 "parser.tab.cc"
    break;

  case 156: // varg_cl: varg
#line 630 "parser.yy"
                            { yylhs.value.as < std::vector<pdm::ast::VArg*> > ().push_back(yystack_[0].value.as < pdm::ast::VArg* > ()); }
#line 3154 "parser.tab.cc"
    break;

  case 157: // varg_cl: varg_cl "," varg
#line 631 "parser.yy"
                            { yylhs.value.as < std::vector<pdm::ast::VArg*> > () = std::move(yystack_[2].value.as < std::vector<pdm::ast::VArg*> > ()); yylhs.value.as < std::vector<pdm::ast::VArg*> > ().push_back(yystack_[0].value.as < pdm::ast::VArg* > ()); }
#line 3160 "parser.tab.cc"
    break;

  case 158: // class_spec: primary_class_spec
#line 641 "parser.yy"
      { yylhs.value.as < pdm::ast::ClassSpec* > () = yystack_[0].value.as < pdm::ast::ClassSpec* > (); }
#line 3166 "parser.tab.cc"
    break;

  case 159: // primary_class_spec: cid
#line 644 "parser.yy"
                        { yylhs.value.as < pdm::ast::ClassSpec* > () = mgr->new_id_class_spec(yylhs.location, yystack_[0].value.as < TokenInfo > ().ID_intstr); }
#line 3172 "parser.tab.cc"
    break;

  case 160: // primary_class_spec: mod_prefix_cid_class_spec
#line 645 "parser.yy"
      { yylhs.value.as < pdm::ast::ClassSpec* > () = yystack_[0].value.as < pdm::ast::ClassSpec* > (); }
#line 3178 "parser.tab.cc"
    break;

  case 161: // primary_class_spec: class_exp_class_spec
#line 646 "parser.yy"
      { yylhs.value.as < pdm::ast::ClassSpec* > () = yystack_[0].value.as < pdm::ast::ClassSpec* > (); }
#line 3184 "parser.tab.cc"
    break;

  case 162: // mod_prefix_cid_class_spec: mod_prefix cid
#line 649 "parser.yy"
                        { yylhs.value.as < pdm::ast::ClassSpec* > () = mgr->new_ma_class_spec(yylhs.location, std::move(yystack_[1].value.as < pdm::ast::ModAddress* > ()), yystack_[0].value.as < TokenInfo > ().ID_intstr); }
#line 3190 "parser.tab.cc"
    break;

  case 163: // class_exp_class_spec: "cls" "[" tid class_spec "]" "{" type_query_exp_sl0 "}"
#line 654 "parser.yy"
                                                                           {
            yylhs.value.as < pdm::ast::ClassSpec* > () = mgr->new_class_exp_class_spec(yylhs.location, yystack_[5].value.as < TokenInfo > ().ID_intstr, yystack_[4].value.as < pdm::ast::ClassSpec* > (), std::move(yystack_[1].value.as < std::vector<pdm::ast::TypeQueryExp*> > ()));
        }
#line 3198 "parser.tab.cc"
    break;

  case 164: // struct_exp_field: vid ":" expr
#line 664 "parser.yy"
                     { yylhs.value.as < pdm::ast::StructExp::Field* > () = mgr->new_struct_exp_field(yylhs.location, yystack_[2].value.as < TokenInfo > ().ID_intstr, yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 3204 "parser.tab.cc"
    break;

  case 165: // vpattern_field: vid type_spec
#line 667 "parser.yy"
                             { yylhs.value.as < pdm::ast::VPattern::Field* > () = mgr->new_vpattern_field(yylhs.location, yystack_[1].value.as < TokenInfo > ().ID_intstr, yystack_[0].value.as < pdm::ast::TypeSpec* > (), ast::VArgAccessSpec::In); }
#line 3210 "parser.tab.cc"
    break;

  case 166: // vpattern_field: "out" vid type_spec
#line 668 "parser.yy"
                             { yylhs.value.as < pdm::ast::VPattern::Field* > () = mgr->new_vpattern_field(yylhs.location, yystack_[1].value.as < TokenInfo > ().ID_intstr, yystack_[0].value.as < pdm::ast::TypeSpec* > (), ast::VArgAccessSpec::Out); }
#line 3216 "parser.tab.cc"
    break;

  case 167: // vpattern_field: "inout" vid type_spec
#line 669 "parser.yy"
                             { yylhs.value.as < pdm::ast::VPattern::Field* > () = mgr->new_vpattern_field(yylhs.location, yystack_[1].value.as < TokenInfo > ().ID_intstr, yystack_[0].value.as < pdm::ast::TypeSpec* > (), ast::VArgAccessSpec::InOut); }
#line 3222 "parser.tab.cc"
    break;

  case 168: // lpattern_field: vid type_spec
#line 672 "parser.yy"
                     { yylhs.value.as < pdm::ast::LPattern::Field* > () = mgr->new_lpattern_field(yylhs.location, ast::LPattern::FieldKind::IdTypeSpecPair, yystack_[1].value.as < TokenInfo > ().ID_intstr, yystack_[0].value.as < pdm::ast::TypeSpec* > ()); }
#line 3228 "parser.tab.cc"
    break;

  case 169: // lpattern_field: vid
#line 673 "parser.yy"
                    { yylhs.value.as < pdm::ast::LPattern::Field* > () = mgr->new_lpattern_field(yylhs.location, ast::LPattern::FieldKind::IdSingleton, yystack_[0].value.as < TokenInfo > ().ID_intstr); }
#line 3234 "parser.tab.cc"
    break;

  case 170: // tpattern_field: vid type_spec
#line 676 "parser.yy"
                      { yylhs.value.as < pdm::ast::TPattern::Field* > () = mgr->new_value_tpattern_field(yylhs.location, yystack_[1].value.as < TokenInfo > ().ID_intstr, yystack_[0].value.as < pdm::ast::TypeSpec* > ()); }
#line 3240 "parser.tab.cc"
    break;

  case 171: // tpattern_field: tid class_spec
#line 677 "parser.yy"
                      { yylhs.value.as < pdm::ast::TPattern::Field* > () = mgr->new_type_tpattern_field(yylhs.location, yystack_[1].value.as < TokenInfo > ().ID_intstr, yystack_[0].value.as < pdm::ast::ClassSpec* > ()); }
#line 3246 "parser.tab.cc"
    break;

  case 172: // destructured_lpattern: "{" lpattern_field_cl "}"
#line 681 "parser.yy"
                                       { yylhs.value.as < pdm::ast::LPattern* > () = mgr->new_lpattern(yylhs.location, std::move(yystack_[1].value.as < std::vector<pdm::ast::LPattern::Field*> > ()), true); }
#line 3252 "parser.tab.cc"
    break;

  case 173: // lpattern: lpattern_field
#line 684 "parser.yy"
                        { yylhs.value.as < pdm::ast::LPattern* > () = mgr->new_lpattern(yylhs.location, std::move(std::vector<ast::LPattern::Field*>{1,yystack_[0].value.as < pdm::ast::LPattern::Field* > ()}), false); }
#line 3258 "parser.tab.cc"
    break;

  case 174: // lpattern: destructured_lpattern
#line 685 "parser.yy"
      { yylhs.value.as < pdm::ast::LPattern* > () = yystack_[0].value.as < pdm::ast::LPattern* > (); }
#line 3264 "parser.tab.cc"
    break;

  case 175: // vpattern: "(" vpattern_field_cl ")"
#line 688 "parser.yy"
                                       { yylhs.value.as < pdm::ast::VPattern* > () = mgr->new_vpattern(yylhs.location, std::move(yystack_[1].value.as < std::vector<pdm::ast::VPattern::Field*> > ())); }
#line 3270 "parser.tab.cc"
    break;

  case 176: // vpattern: "(" ")"
#line 689 "parser.yy"
                                       { yylhs.value.as < pdm::ast::VPattern* > () = mgr->new_vpattern(yylhs.location, std::move(std::vector<ast::VPattern::Field*>{})); }
#line 3276 "parser.tab.cc"
    break;

  case 177: // tpattern: "[" tpattern_field_cl1 "]"
#line 692 "parser.yy"
                                        { yylhs.value.as < pdm::ast::TPattern* > () = mgr->new_tpattern(yylhs.location, std::move(yystack_[1].value.as < std::vector<pdm::ast::TPattern::Field*> > ()), false); }
#line 3282 "parser.tab.cc"
    break;

  case 178: // vpattern_field_cl: vpattern_field
#line 696 "parser.yy"
                                              { yylhs.value.as < std::vector<pdm::ast::VPattern::Field*> > ().push_back(yystack_[0].value.as < pdm::ast::VPattern::Field* > ()); }
#line 3288 "parser.tab.cc"
    break;

  case 179: // vpattern_field_cl: vpattern_field_cl "," vpattern_field
#line 697 "parser.yy"
                                               { yylhs.value.as < std::vector<pdm::ast::VPattern::Field*> > () = std::move(yystack_[2].value.as < std::vector<pdm::ast::VPattern::Field*> > ()); yylhs.value.as < std::vector<pdm::ast::VPattern::Field*> > ().push_back(yystack_[0].value.as < pdm::ast::VPattern::Field* > ()); }
#line 3294 "parser.tab.cc"
    break;

  case 180: // lpattern_field_cl: lpattern_field
#line 700 "parser.yy"
                                               { yylhs.value.as < std::vector<pdm::ast::LPattern::Field*> > ().push_back(yystack_[0].value.as < pdm::ast::LPattern::Field* > ()); }
#line 3300 "parser.tab.cc"
    break;

  case 181: // lpattern_field_cl: lpattern_field_cl "," lpattern_field
#line 701 "parser.yy"
                                               { yylhs.value.as < std::vector<pdm::ast::LPattern::Field*> > () = std::move(yystack_[2].value.as < std::vector<pdm::ast::LPattern::Field*> > ()); yylhs.value.as < std::vector<pdm::ast::LPattern::Field*> > ().push_back(yystack_[0].value.as < pdm::ast::LPattern::Field* > ()); }
#line 3306 "parser.tab.cc"
    break;

  case 182: // tpattern_field_cl1: tpattern_field
#line 704 "parser.yy"
                                              { yylhs.value.as < std::vector<pdm::ast::TPattern::Field*> > ().push_back(yystack_[0].value.as < pdm::ast::TPattern::Field* > ()); }
#line 3312 "parser.tab.cc"
    break;

  case 183: // tpattern_field_cl1: tpattern_field_cl1 "," tpattern_field
#line 705 "parser.yy"
                                                { yylhs.value.as < std::vector<pdm::ast::TPattern::Field*> > () = std::move(yystack_[2].value.as < std::vector<pdm::ast::TPattern::Field*> > ()); yylhs.value.as < std::vector<pdm::ast::TPattern::Field*> > ().push_back(yystack_[0].value.as < pdm::ast::TPattern::Field* > ()); }
#line 3318 "parser.tab.cc"
    break;

  case 184: // struct_exp_field_cl: struct_exp_field
#line 708 "parser.yy"
                                                    { yylhs.value.as < std::vector<pdm::ast::StructExp::Field*> > ().push_back(yystack_[0].value.as < pdm::ast::StructExp::Field* > ()); }
#line 3324 "parser.tab.cc"
    break;

  case 185: // struct_exp_field_cl: struct_exp_field_cl "," struct_exp_field
#line 709 "parser.yy"
                                                    { yylhs.value.as < std::vector<pdm::ast::StructExp::Field*> > () = std::move(yystack_[2].value.as < std::vector<pdm::ast::StructExp::Field*> > ()); yylhs.value.as < std::vector<pdm::ast::StructExp::Field*> > ().push_back(yystack_[0].value.as < pdm::ast::StructExp::Field* > ()); }
#line 3330 "parser.tab.cc"
    break;


#line 3334 "parser.tab.cc"

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





  const short parser::yypact_ninf_ = -239;

  const signed char parser::yytable_ninf_ = -1;

  const short
  parser::yypact_[] =
  {
    -239,    14,    50,  -239,    59,    23,    71,    97,  -239,  -239,
      36,  -239,  -239,    59,    80,   -11,   248,    13,  -239,    90,
      49,  -239,  -239,  -239,   119,  -239,    21,   206,  -239,   125,
    -239,    59,  -239,    56,   116,   110,   115,   141,    86,   -11,
     122,    -6,  -239,    78,  -239,  -239,  -239,  -239,   169,   186,
     206,   206,  -239,   248,  -239,  -239,  -239,  -239,  -239,  -239,
    -239,   248,  -239,    49,  -239,   200,  -239,   206,   609,    21,
    -239,   132,  -239,   228,  -239,   609,   175,  -239,   228,   184,
     211,   214,   179,   -25,   -20,    -2,  -239,  -239,  -239,  -239,
    -239,  -239,   -37,  -239,  -239,  -239,  -239,  -239,  -239,  -239,
    -239,   527,   343,  -239,  -239,    -6,  -239,   248,  -239,  -239,
    -239,  -239,  -239,  -239,  -239,  -239,   212,  -239,  -239,  -239,
      31,  -239,  -239,  -239,  -239,   609,  -239,   188,   204,   177,
     205,   234,   246,   251,   232,   -37,  -239,  -239,    21,  -239,
     232,  -239,   130,  -239,   609,   206,  -239,    66,    59,    59,
    -239,   206,  -239,    84,   206,   609,   609,  -239,   206,  -239,
     206,  -239,    59,  -239,   343,   267,  -239,   236,   233,   162,
       2,     2,     2,   609,   609,  -239,   238,  -239,  -239,  -239,
    -239,  -239,   149,   242,   394,    65,  -239,    93,   175,  -239,
    -239,   271,   445,  -239,  -239,  -239,  -239,   609,  -239,  -239,
     609,  -239,  -239,  -239,  -239,   609,  -239,  -239,   609,   609,
     609,   609,   281,  -239,   245,   609,   240,   143,  -239,   228,
    -239,   206,   206,  -239,   101,  -239,  -239,   247,   108,  -239,
    -239,   206,  -239,   148,   -37,   568,  -239,   609,  -239,    59,
     206,  -239,  -239,   235,   237,   249,   250,  -239,  -239,   609,
    -239,  -239,   260,   244,    59,  -239,  -239,  -239,  -239,   609,
     609,  -239,  -239,  -239,   170,  -239,   188,   204,   177,   205,
     234,   246,   308,   264,  -239,  -239,   273,  -239,  -239,  -239,
    -239,  -239,   304,  -239,  -239,  -239,  -239,   112,  -239,   609,
     609,   609,   609,  -239,  -239,  -239,   277,  -239,  -239,  -239,
     486,  -239,   276,  -239,  -239,   252,    59,  -239,  -239,  -239,
    -239,  -239,  -239,   609,  -239,    32,    59,  -239,  -239,  -239,
     279,    51,  -239,  -239,  -239,  -239,   206,  -239
  };

  const unsigned char
  parser::yydefact_[] =
  {
       3,     0,     0,     1,     0,     0,     0,     2,     5,    31,
       0,     4,     7,     0,     0,     0,     0,     0,     6,     0,
       0,     8,    35,    34,     0,    30,     0,     0,   182,     0,
      32,     0,    11,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   159,     0,   171,   158,   160,   161,     0,     0,
       0,     0,   128,     0,   170,   129,   130,   131,   132,   133,
     134,     0,   177,     0,     9,     0,    13,     0,     0,     0,
      12,     0,    19,     0,    36,     0,     0,   162,     0,     0,
       0,     0,     0,     0,     0,     0,   140,   135,   183,    18,
      14,    16,     0,    95,    63,    64,    65,    66,    33,    68,
      67,     0,     0,    93,    94,    57,    59,     0,    41,    15,
      56,    47,    48,    49,    80,    58,    60,    61,    50,    42,
      91,    81,    82,    83,   100,     0,    40,   104,   110,   114,
     116,   118,   120,    96,     0,   134,    17,    10,     0,   150,
     149,   151,     0,    38,     0,   143,   145,     0,     0,     0,
     176,     0,   178,     0,     0,     0,     0,   142,     0,   137,
       0,   136,     0,   139,     0,     0,    52,    41,     0,     0,
       0,     0,     0,     0,     0,    73,     0,    20,    21,    22,
      23,    24,    57,     0,     0,     0,   184,     0,    62,    70,
      69,     0,     0,    92,    97,    98,    99,     0,   102,   103,
       0,   106,   107,   108,   109,     0,   112,   113,     0,     0,
       0,     0,     0,    79,     0,     0,     0,     0,   144,     0,
     147,     0,     0,   165,     0,   175,   148,     0,   149,   127,
     126,     0,   141,    57,     0,     0,    51,     0,    54,     0,
     169,   173,   174,     0,     0,     0,     0,    29,    77,     0,
      74,    75,     0,     0,     0,    55,    86,    90,    89,     0,
       0,    84,   153,   156,     0,   101,   105,   111,   115,   117,
     119,   121,    87,     0,   152,    37,     0,   146,   166,   167,
     179,   138,    71,    53,    43,    44,   180,     0,   168,     0,
       0,     0,     0,   164,    78,    76,     0,   185,   154,   155,
       0,    85,     0,    45,    39,     0,     0,   172,    25,    26,
      27,    28,   157,     0,    88,     0,     0,    72,   181,   163,
       0,     0,    46,   125,   123,   124,     0,   122
  };

  const short
  parser::yypgoto_[] =
  {
    -239,  -239,  -239,  -239,   319,  -239,   266,   292,   -23,  -239,
     150,  -239,  -239,  -239,  -239,  -239,    54,    -4,   -24,  -239,
     293,    26,    68,   -62,  -239,  -239,   -85,    33,  -239,  -239,
      28,   145,  -239,  -239,  -239,  -239,  -239,  -239,  -239,  -239,
    -239,  -117,  -239,  -239,  -239,   137,  -239,   133,  -239,   131,
    -239,   134,   135,   129,  -239,  -239,  -239,  -239,    46,  -239,
    -239,  -239,  -239,  -239,   180,   151,  -239,  -239,   -64,   136,
     210,    44,  -239,   -66,  -239,  -239,  -239,    94,   126,  -238,
     288,  -239,   104,  -239,  -239,  -239,  -239,  -239,  -239
  };

  const short
  parser::yydefgoto_[] =
  {
      -1,     1,     2,     5,     6,     7,    18,    33,    34,     8,
     176,   177,   178,   179,   180,   181,    52,   105,    37,   106,
      24,   107,   108,   168,   169,   315,   110,   111,   112,   113,
     114,   115,   116,   117,   118,   184,   119,   120,   121,   122,
     123,   124,   125,   126,   197,   127,   200,   128,   205,   129,
     208,   130,   131,   132,   133,   320,   326,    83,   134,    55,
      56,    57,    58,    85,    86,   146,   147,    59,    60,   141,
     142,   263,   264,    44,    45,    46,    47,   186,   152,   241,
      28,   242,   243,    80,    19,   153,   287,    29,   187
  };

  const short
  parser::yytable_[] =
  {
      10,   286,    42,   136,   135,     9,   109,   165,   193,    20,
      65,   101,    27,    36,     3,   164,     9,    25,    30,    77,
     158,    31,    41,    41,     9,   160,    30,    63,   159,    36,
      22,    23,    40,   161,    36,     9,    25,   135,   135,    76,
     183,    74,    48,   162,    75,    42,    41,    82,    65,    76,
     213,   163,    43,    53,   239,    15,    49,    27,     4,     9,
      25,    30,     9,    41,    31,    41,    32,    36,   318,    11,
      26,    35,   214,    54,   191,   151,    53,    53,    41,   192,
     265,     9,    50,    30,    51,   319,    16,    35,    17,     9,
      25,    30,    35,    53,    31,    43,    81,    84,   182,    16,
     135,    17,   183,   188,     9,    13,   257,    87,    53,    64,
     160,   219,   212,    91,    42,    26,   323,    12,   161,   220,
     135,   140,   253,   324,   325,    35,    21,   138,   157,   224,
     148,   149,   145,   225,    41,     9,    25,    30,   254,    70,
      31,    41,    38,   139,   221,   222,   255,    41,   185,   282,
      41,    39,     9,    25,    41,   212,    41,   306,   231,    48,
     233,    87,    66,   155,    43,   307,   240,   240,   240,   167,
      61,    53,    73,    49,    67,   215,    62,    53,    41,    68,
      53,   216,     9,    25,    53,   137,    53,     9,   215,    48,
     140,   218,   249,   249,   276,    74,    74,   223,    75,   156,
     226,    51,   228,    49,   229,    69,   230,   237,    53,     9,
      25,   238,   139,   148,   149,   300,    48,    41,    41,   301,
     151,    78,   143,   227,   139,   144,    74,    41,   157,   156,
      49,    51,    25,   150,    79,   240,    41,   201,   202,   203,
     204,   246,   247,   194,   195,   196,    90,    53,    53,   135,
     296,     9,    25,   189,   190,     9,    50,    53,    51,   209,
     262,   140,   198,   199,    92,   154,    53,   278,   279,   155,
     206,   207,   210,   145,   256,   244,   245,   157,   211,   212,
     234,   235,   236,   139,   248,   272,   288,   275,    94,    95,
      96,    97,    98,    99,   100,   250,   273,   295,   281,   289,
     101,   290,   240,   284,   164,   285,   294,    94,    95,    96,
      97,    41,   188,   291,   292,   302,   303,   293,   305,   101,
     304,   249,    41,   164,   313,   322,    14,   298,   299,    89,
      71,   316,    72,   317,   252,   314,   258,   266,   267,   268,
     271,    53,   232,   269,   312,   270,     9,    25,   297,    88,
     280,   274,    53,    48,   217,    92,     0,   308,   309,   310,
     311,   321,     0,   170,   171,   172,   173,    49,   262,     0,
     277,    93,   327,     0,   174,     0,     0,     0,     0,    94,
      95,    96,    97,    98,    99,   100,     0,     0,     0,     0,
       0,   101,     0,    50,     0,   102,   175,     9,    25,     0,
       0,   103,   104,     0,    48,     0,    92,     0,     0,     0,
       0,     0,     0,     0,   170,   171,   172,   173,    49,     0,
       0,     0,    93,     0,     0,   174,     0,     0,     0,     0,
      94,    95,    96,    97,    98,    99,   100,     0,     0,     0,
       0,     0,   101,     0,    50,     0,   102,   251,     9,    25,
       0,     0,   103,   104,     0,    48,     0,    92,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    49,
       0,     0,     0,    93,   259,   260,     0,     0,     0,     0,
       0,    94,    95,    96,    97,    98,    99,   100,     0,     9,
      25,     0,     0,   101,   261,    50,    48,   102,    92,     0,
       0,     0,     0,   103,   104,     0,     0,     0,     0,     0,
      49,     0,     0,     0,    93,   259,   260,     0,     0,     0,
       0,     0,    94,    95,    96,    97,    98,    99,   100,     0,
       9,    25,     0,     0,   101,     0,    50,    48,   102,    92,
       0,     0,     0,     0,   103,   104,     0,     0,     0,     0,
       0,    49,     0,     0,     0,    93,     0,     0,     0,     0,
       0,     0,     0,    94,    95,    96,    97,    98,    99,   100,
       0,     9,    25,     0,     0,   101,   166,    50,    48,   102,
      92,     0,     0,     0,     0,   103,   104,     0,     0,     0,
       0,     0,    49,     0,     0,     0,    93,     0,     0,     0,
       0,     0,     0,     0,    94,    95,    96,    97,    98,    99,
     100,     0,     9,    25,     0,     0,   101,   283,    50,    48,
     102,    92,     0,     0,     0,     0,   103,   104,     0,     0,
       0,     0,     0,    49,     0,     0,     0,    93,     0,     0,
       0,     0,     0,     0,     0,    94,    95,    96,    97,    98,
      99,   100,     0,     0,     0,     0,     0,   101,     0,    50,
       0,   102,     0,     0,     0,     0,     0,   103,   104
  };

  const short
  parser::yycheck_[] =
  {
       4,   239,    26,    69,    68,     3,    68,    92,   125,    13,
      33,    48,    16,    17,     0,    52,     3,     4,     5,    43,
      45,     8,    26,    27,     3,    45,     5,    31,    53,    33,
      41,    42,    11,    53,    38,     3,     4,   101,   102,    43,
     102,    47,    10,    45,    50,    69,    50,    51,    71,    53,
     135,    53,    26,    27,    52,    19,    24,    61,     8,     3,
       4,     5,     3,    67,     8,    69,    53,    71,   306,    46,
      16,    17,   138,    27,    43,    79,    50,    51,    82,    48,
     197,     3,    50,     5,    52,    53,    50,    33,    52,     3,
       4,     5,    38,    67,     8,    69,    50,    51,   102,    50,
     164,    52,   164,   107,     3,     8,   191,    53,    82,    53,
      45,    45,    47,    67,   138,    61,    65,    46,    53,    53,
     184,    75,   184,    72,    73,    71,    46,    73,    82,    45,
      29,    30,    78,    49,   138,     3,     4,     5,    45,    53,
       8,   145,    52,    75,   148,   149,    53,   151,   102,   234,
     154,    32,     3,     4,   158,    47,   160,    45,   162,    10,
     164,   107,    46,    55,   138,    53,   170,   171,   172,   101,
      45,   145,    50,    24,    64,    45,    51,   151,   182,    64,
     154,    51,     3,     4,   158,    53,   160,     3,    45,    10,
     144,   145,    44,    44,    51,    47,    47,   151,    50,    50,
     154,    52,   156,    24,   158,    64,   160,    45,   182,     3,
       4,    49,   144,    29,    30,    45,    10,   221,   222,    49,
     224,    52,    47,   155,   156,    50,    47,   231,   182,    50,
      24,    52,     4,    49,    48,   239,   240,    60,    61,    62,
      63,   173,   174,    55,    56,    57,    46,   221,   222,   313,
     254,     3,     4,    41,    42,     3,    50,   231,    52,    25,
     192,   215,    58,    59,    12,    54,   240,   221,   222,    55,
      65,    66,    26,   219,     3,   171,   172,   231,    27,    47,
      13,    45,    49,   215,    46,     4,   240,    47,    36,    37,
      38,    39,    40,    41,    42,    53,    51,    53,    51,    64,
      48,    64,   306,   235,    52,   237,    46,    36,    37,    38,
      39,   315,   316,    64,    64,     7,    52,   249,    14,    48,
      47,    44,   326,    52,    48,    46,     7,   259,   260,    63,
      38,   305,    39,   305,   184,   302,   191,   200,   205,   208,
     211,   315,   162,   209,   300,   210,     3,     4,   254,    61,
     224,   215,   326,    10,   144,    12,    -1,   289,   290,   291,
     292,   315,    -1,    20,    21,    22,    23,    24,   300,    -1,
     219,    28,   326,    -1,    31,    -1,    -1,    -1,    -1,    36,
      37,    38,    39,    40,    41,    42,    -1,    -1,    -1,    -1,
      -1,    48,    -1,    50,    -1,    52,    53,     3,     4,    -1,
      -1,    58,    59,    -1,    10,    -1,    12,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    20,    21,    22,    23,    24,    -1,
      -1,    -1,    28,    -1,    -1,    31,    -1,    -1,    -1,    -1,
      36,    37,    38,    39,    40,    41,    42,    -1,    -1,    -1,
      -1,    -1,    48,    -1,    50,    -1,    52,    53,     3,     4,
      -1,    -1,    58,    59,    -1,    10,    -1,    12,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    24,
      -1,    -1,    -1,    28,    29,    30,    -1,    -1,    -1,    -1,
      -1,    36,    37,    38,    39,    40,    41,    42,    -1,     3,
       4,    -1,    -1,    48,    49,    50,    10,    52,    12,    -1,
      -1,    -1,    -1,    58,    59,    -1,    -1,    -1,    -1,    -1,
      24,    -1,    -1,    -1,    28,    29,    30,    -1,    -1,    -1,
      -1,    -1,    36,    37,    38,    39,    40,    41,    42,    -1,
       3,     4,    -1,    -1,    48,    -1,    50,    10,    52,    12,
      -1,    -1,    -1,    -1,    58,    59,    -1,    -1,    -1,    -1,
      -1,    24,    -1,    -1,    -1,    28,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    36,    37,    38,    39,    40,    41,    42,
      -1,     3,     4,    -1,    -1,    48,    49,    50,    10,    52,
      12,    -1,    -1,    -1,    -1,    58,    59,    -1,    -1,    -1,
      -1,    -1,    24,    -1,    -1,    -1,    28,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    36,    37,    38,    39,    40,    41,
      42,    -1,     3,     4,    -1,    -1,    48,    49,    50,    10,
      52,    12,    -1,    -1,    -1,    -1,    58,    59,    -1,    -1,
      -1,    -1,    -1,    24,    -1,    -1,    -1,    28,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    36,    37,    38,    39,    40,
      41,    42,    -1,    -1,    -1,    -1,    -1,    48,    -1,    50,
      -1,    52,    -1,    -1,    -1,    -1,    -1,    58,    59
  };

  const unsigned char
  parser::yystos_[] =
  {
       0,    76,    77,     0,     8,    78,    79,    80,    84,     3,
      92,    46,    46,     8,    79,    19,    50,    52,    81,   159,
      92,    46,    41,    42,    95,     4,    91,    92,   155,   162,
       5,     8,    53,    82,    83,    91,    92,    93,    52,    32,
      11,    92,    93,    96,   148,   149,   150,   151,    10,    24,
      50,    52,    91,    96,   133,   134,   135,   136,   137,   142,
     143,    45,    51,    92,    53,    83,    46,    64,    64,    64,
      53,    82,    95,    50,    47,    50,    92,    93,    52,    48,
     158,   133,    92,   132,   133,   138,   139,    91,   155,    81,
      46,   133,    12,    28,    36,    37,    38,    39,    40,    41,
      42,    48,    52,    58,    59,    92,    94,    96,    97,    98,
     101,   102,   103,   104,   105,   106,   107,   108,   109,   111,
     112,   113,   114,   115,   116,   117,   118,   120,   122,   124,
     126,   127,   128,   129,   133,   143,   148,    53,    91,    97,
     133,   144,   145,    47,    50,    91,   140,   141,    29,    30,
      49,    92,   153,   160,    54,    55,    50,   133,    45,    53,
      45,    53,    45,    53,    52,   101,    49,    97,    98,    99,
      20,    21,    22,    23,    31,    53,    85,    86,    87,    88,
      89,    90,    92,    98,   110,   133,   152,   163,    92,    41,
      42,    43,    48,   116,    55,    56,    57,   119,    58,    59,
     121,    60,    61,    62,    63,   123,    65,    66,   125,    25,
      26,    27,    47,   101,   148,    45,    51,   145,   133,    45,
      53,    92,    92,   133,    45,    49,   133,    97,   133,   133,
     133,    92,   139,    92,    13,    45,    49,    45,    49,    52,
      92,   154,   156,   157,   157,   157,    97,    97,    46,    44,
      53,    53,    85,    98,    45,    53,     3,   101,   106,    29,
      30,    49,    97,   146,   147,   116,   120,   122,   124,   126,
     127,   128,     4,    51,   144,    47,    51,   140,   133,   133,
     153,    51,   101,    49,    97,    97,   154,   161,   133,    64,
      64,    64,    64,    97,    46,    53,    92,   152,    97,    97,
      45,    49,     7,    52,    47,    14,    45,    53,    97,    97,
      97,    97,   146,    48,   102,   100,    96,   105,   154,    53,
     130,   133,    46,    65,    72,    73,   131,   133
  };

  const unsigned char
  parser::yyr1_[] =
  {
       0,    75,    76,    77,    77,    78,    79,    80,    80,    81,
      81,    81,    81,    82,    82,    83,    83,    83,    83,    84,
      85,    85,    85,    85,    85,    86,    87,    88,    89,    90,
      91,    92,    93,    94,    95,    95,    96,    96,    96,    96,
      97,    98,    98,    99,    99,   100,   100,   101,   101,   101,
     101,   102,   103,   103,   103,   104,   105,   105,   105,   105,
     105,   105,   105,   106,   106,   106,   106,   107,   107,   107,
     107,   108,   108,   109,   109,   109,   109,   110,   110,   111,
     112,   112,   112,   112,   113,   113,   114,   114,   114,   115,
     115,   116,   116,   117,   117,   117,   118,   119,   119,   119,
     120,   120,   121,   121,   122,   122,   123,   123,   123,   123,
     124,   124,   125,   125,   126,   126,   127,   127,   128,   128,
     129,   129,   130,   131,   131,   131,   132,   132,   133,   133,
     133,   133,   133,   133,   133,   134,   135,   135,   136,   137,
     138,   138,   139,   140,   140,   141,   141,   142,   143,   144,
     144,   145,   145,   146,   146,   146,   147,   147,   148,   149,
     149,   149,   150,   151,   152,   153,   153,   153,   154,   154,
     155,   155,   156,   157,   157,   158,   158,   159,   160,   160,
     161,   161,   162,   162,   163,   163
  };

  const signed char
  parser::yyr2_[] =
  {
       0,     2,     2,     0,     3,     1,     3,     2,     3,     3,
       4,     2,     3,     2,     3,     3,     3,     3,     3,     6,
       1,     1,     1,     1,     1,     4,     4,     4,     4,     2,
       1,     1,     1,     1,     1,     1,     2,     5,     3,     6,
       1,     1,     1,     3,     3,     0,     3,     1,     1,     1,
       1,     3,     2,     4,     3,     3,     1,     1,     1,     1,
       1,     1,     2,     1,     1,     1,     1,     1,     1,     2,
       2,     4,     6,     2,     3,     3,     4,     2,     3,     2,
       1,     1,     1,     1,     3,     4,     3,     3,     5,     3,
       3,     1,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     3,     1,     1,     1,     3,     1,     1,     1,     1,
       1,     3,     1,     1,     1,     3,     1,     3,     1,     3,
       1,     3,     3,     1,     1,     1,     3,     3,     1,     1,
       1,     1,     1,     1,     1,     2,     3,     3,     5,     3,
       1,     3,     2,     1,     2,     1,     3,     4,     4,     1,
       1,     1,     3,     1,     2,     2,     1,     3,     1,     1,
       1,     1,     2,     8,     3,     2,     3,     3,     2,     1,
       2,     2,     3,     1,     1,     3,     2,     3,     1,     3,
       1,     3,     1,     3,     1,     3
  };


#if YYDEBUG
  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a YYNTOKENS, nonterminals.
  const char*
  const parser::yytname_[] =
  {
  "\"end of file\"", "error", "\"invalid token\"", "\"val_id\"",
  "\"TypeId\"", "\"CLS_ID\"", "\"__42__\"", "\"using\"", "\"mod\"",
  "\"struct\"", "\"enum\"", "\"cls\"", "\"if\"", "\"then\"", "\"else\"",
  "\"match\"", "\"with\"", "\"import\"", "\"extern\"", "\"from\"",
  "\"const\"", "\"val\"", "\"var\"", "\"set\"", "\"fn\"", "\"and\"",
  "\"xor\"", "\"or\"", "\"not\"", "\"out\"", "\"inout\"", "\"discard\"",
  "\"as\"", "\"CORE_PROFILE\"", "\"BROWSER_PROFILE\"",
  "\"NATIVE_PROFILE\"", "\"42\"", "\"0x2a\"", "\"42u\"", "\"0x2Au\"",
  "\"4.2\"", "\"\\\"dq-string-literal\\\"\"", "\"'sq-string-literal'\"",
  "\".\"", "\":\"", "\",\"", "\";\"", "\"::\"", "\"(\"", "\")\"", "\"[\"",
  "\"]\"", "\"{\"", "\"}\"", "\"->\"", "\"*\"", "\"/\"", "\"%\"", "\"+\"",
  "\"-\"", "\"<\"", "\"<=\"", "\">\"", "\">=\"", "\"=\"", "\"==\"",
  "\"!=\"", "\"^\"", "\"&\"", "\"!\"", "\"|\"", "\"EOS\"", "\":<\"",
  "\">:\"", "\"<null>\"", "$accept", "script", "script_header",
  "script_header_stmt", "script_field", "script_field_sl", "mod_exp",
  "mod_field_sl", "mod_field", "import_stmt", "chain_prefix_stmt",
  "const_stmt", "val_stmt", "var_stmt", "set_stmt", "discard_stmt", "tid",
  "vid", "cid", "floatl", "stringl", "mod_prefix", "expr", "long_exp",
  "expr_cl2", "type_query_exp_sl0", "bracketed_exp", "paren_exp",
  "vtupleExpr", "vstructExpr", "primary_exp", "int_expr", "stringls",
  "if_exp", "chain_exp", "chain_prefix", "lambda_exp", "postfix_exp",
  "vcall_exp", "dot_name_exp", "dot_index_exp", "unary_exp", "unary_op",
  "binary_exp", "mul_binary_op", "mul_binary_exp", "add_binary_op",
  "add_binary_exp", "cmp_binary_op", "cmp_binary_exp", "eq_binary_op",
  "eq_binary_exp", "and_binary_exp", "xor_binary_exp", "or_binary_exp",
  "type_query_exp", "type_query_op", "type_spec_cl2", "type_spec",
  "mod_prefix_tid", "tuple_type_spec", "array_type_spec",
  "struct_type_spec", "struct_type_spec_field_cl",
  "struct_type_spec_field", "enum_type_spec_field",
  "enum_type_spec_field_cl", "enum_type_spec", "fn_type_spec", "targ",
  "targ_cl", "varg", "varg_cl", "class_spec", "primary_class_spec",
  "mod_prefix_cid_class_spec", "class_exp_class_spec", "struct_exp_field",
  "vpattern_field", "lpattern_field", "tpattern_field",
  "destructured_lpattern", "lpattern", "vpattern", "tpattern",
  "vpattern_field_cl", "lpattern_field_cl", "tpattern_field_cl1",
  "struct_exp_field_cl", YY_NULLPTR
  };
#endif


#if YYDEBUG
  const short
  parser::yyrline_[] =
  {
       0,   273,   273,   281,   282,   285,   289,   292,   293,   301,
     302,   303,   304,   307,   308,   311,   312,   313,   314,   322,
     326,   327,   328,   329,   330,   333,   336,   339,   342,   345,
     352,   353,   354,   357,   360,   361,   364,   365,   366,   367,
     374,   377,   378,   390,   391,   394,   395,   399,   400,   401,
     402,   413,   416,   417,   418,   421,   424,   425,   426,   427,
     428,   429,   430,   433,   434,   435,   436,   439,   440,   441,
     442,   445,   446,   449,   450,   451,   452,   455,   456,   459,
     463,   464,   465,   466,   469,   470,   473,   474,   475,   478,
     479,   483,   484,   487,   488,   489,   493,   496,   497,   498,
     501,   502,   505,   506,   509,   510,   513,   514,   515,   516,
     519,   520,   523,   524,   527,   528,   531,   532,   535,   536,
     539,   540,   544,   547,   548,   549,   564,   565,   569,   570,
     571,   572,   573,   574,   575,   579,   583,   584,   587,   591,
     594,   595,   598,   602,   603,   606,   607,   610,   614,   618,
     619,   622,   623,   625,   626,   627,   630,   631,   641,   644,
     645,   646,   649,   654,   664,   667,   668,   669,   672,   673,
     676,   677,   681,   684,   685,   688,   689,   692,   696,   697,
     700,   701,   704,   705,   708,   709
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
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74
    };
    // Last valid token kind.
    const int code_max = 329;

    if (t <= 0)
      return symbol_kind::S_YYEOF;
    else if (t <= code_max)
      return YY_CAST (symbol_kind_type, translate_table[t]);
    else
      return symbol_kind::S_YYUNDEF;
  }

#line 11 "parser.yy"
} } // pdm::parser
#line 4016 "parser.tab.cc"

#line 712 "parser.yy"


#include <iostream>

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

    ast::Script* parse_script(ast::Manager* manager, source::ISource* source) {
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

    void parser::error(source::Loc const& const_loc, std::string const& message) {
        source::Loc loc = const_loc;
        loc.source(source);

        std::vector<feedback::Note*> notes{1}; {
            std::string desc0 = "Occurred here...";
            notes[0] = new feedback::SourceLocNote(std::move(desc0), loc);
        };
        std::string message_copy = message;
        std::string desc;
        feedback::post(new pdm::feedback::Letter(
            feedback::Severity::Error, 
            std::move(message_copy),
            std::move(desc),
            std::move(notes)
        ));
        std::cout << "YACC error: " << message << " at " << loc << std::endl;
    }

}

int yylex(pdm::parser::parser::semantic_type* semval, pdm::source::Loc* llocp, pdm::source::ISource* source, pdm::parser::Lexer* lexer) {
    // see:
    // https://www.gnu.org/software/bison/manual/html_node/Calling-Convention.html
    
    pdm::parser::TokenInfo info;

    int tk = lexer->lex_one_token(&info, llocp);
    semval->as<pdm::parser::TokenInfo>() = info;

    bool const print_token_info = false;
    if (pdm::DEBUG && print_token_info) {
        debug_print_token("YYLEX:", tk, &info, llocp);
    }
    if (tk == Tk::EOS) {
        return Tk::YYEOF;
    } else {
        return tk;
    }
}


/* see docs on define "api.pure" "full"...
 * - %define Summary
 *     https://www.gnu.org/software/bison/manual/html_node/_0025define-Summary.html 
 * - A Pure (Reentrant) Parser
 *     https://www.gnu.org/software/bison/manual/html_node/Pure-Decl.html
 * - Calling Conventions for Pure Parsers 
 *     https://www.gnu.org/software/bison/manual/html_node/Pure-Calling.html
 */

/* see this on using C++ variants for Bison:
 *   https://www.gnu.org/software/bison/manual/html_node/A-Simple-C_002b_002b-Example.html
 */
