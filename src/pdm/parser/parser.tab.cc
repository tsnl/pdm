// A Bison parser, made by GNU Bison 3.7.6.

// Skeleton implementation for Bison LALR(1) parsers in C++

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

// DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
// especially those whose name start with YY_ or yy_.  They are
// private implementation details that can be changed or removed.



// First part of user prologue.
#line 43 "parser.yy"

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
# define YY_SYMBOL_PRINT(Title, Symbol)  YY_USE (Symbol)
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

      case symbol_kind::S_import_field_group: // import_field_group
        value.copy< ast::ImportStmt::FieldGroup* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_native_mod_exp: // native_mod_exp
        value.copy< pdm::ast::BaseModExp* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_mod_field: // mod_field
        value.copy< pdm::ast::BaseModExp::Field* > (YY_MOVE (that.value));
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

      case symbol_kind::S_import_field_cl1: // import_field_cl1
        value.copy< std::vector<ast::ImportStmt::Field*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_import_field_group_sl0: // import_field_group_sl0
        value.copy< std::vector<ast::ImportStmt::FieldGroup*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_mod_field_sl: // mod_field_sl
        value.copy< std::vector<pdm::ast::BaseModExp::Field*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_enum_type_spec_field_cl: // enum_type_spec_field_cl
        value.copy< std::vector<pdm::ast::EnumTypeSpec::Field*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_mut_expr_cl1: // mut_expr_cl1
      case symbol_kind::S_expr_cl2: // expr_cl2
        value.copy< std::vector<pdm::ast::Exp*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_script_header: // script_header
        value.copy< std::vector<pdm::ast::HeaderStmt*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_lpattern_field_cl: // lpattern_field_cl
        value.copy< std::vector<pdm::ast::LPattern::Field*> > (YY_MOVE (that.value));
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

      case symbol_kind::S_import_field_group: // import_field_group
        value.move< ast::ImportStmt::FieldGroup* > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_native_mod_exp: // native_mod_exp
        value.move< pdm::ast::BaseModExp* > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_mod_field: // mod_field
        value.move< pdm::ast::BaseModExp::Field* > (YY_MOVE (s.value));
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

      case symbol_kind::S_import_field_cl1: // import_field_cl1
        value.move< std::vector<ast::ImportStmt::Field*> > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_import_field_group_sl0: // import_field_group_sl0
        value.move< std::vector<ast::ImportStmt::FieldGroup*> > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_mod_field_sl: // mod_field_sl
        value.move< std::vector<pdm::ast::BaseModExp::Field*> > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_enum_type_spec_field_cl: // enum_type_spec_field_cl
        value.move< std::vector<pdm::ast::EnumTypeSpec::Field*> > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_mut_expr_cl1: // mut_expr_cl1
      case symbol_kind::S_expr_cl2: // expr_cl2
        value.move< std::vector<pdm::ast::Exp*> > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_script_header: // script_header
        value.move< std::vector<pdm::ast::HeaderStmt*> > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_lpattern_field_cl: // lpattern_field_cl
        value.move< std::vector<pdm::ast::LPattern::Field*> > (YY_MOVE (s.value));
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
  parser::by_kind::clear () YY_NOEXCEPT
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

      case symbol_kind::S_import_field_group: // import_field_group
        value.YY_MOVE_OR_COPY< ast::ImportStmt::FieldGroup* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_native_mod_exp: // native_mod_exp
        value.YY_MOVE_OR_COPY< pdm::ast::BaseModExp* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_mod_field: // mod_field
        value.YY_MOVE_OR_COPY< pdm::ast::BaseModExp::Field* > (YY_MOVE (that.value));
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

      case symbol_kind::S_import_field_cl1: // import_field_cl1
        value.YY_MOVE_OR_COPY< std::vector<ast::ImportStmt::Field*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_import_field_group_sl0: // import_field_group_sl0
        value.YY_MOVE_OR_COPY< std::vector<ast::ImportStmt::FieldGroup*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_mod_field_sl: // mod_field_sl
        value.YY_MOVE_OR_COPY< std::vector<pdm::ast::BaseModExp::Field*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_enum_type_spec_field_cl: // enum_type_spec_field_cl
        value.YY_MOVE_OR_COPY< std::vector<pdm::ast::EnumTypeSpec::Field*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_mut_expr_cl1: // mut_expr_cl1
      case symbol_kind::S_expr_cl2: // expr_cl2
        value.YY_MOVE_OR_COPY< std::vector<pdm::ast::Exp*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_script_header: // script_header
        value.YY_MOVE_OR_COPY< std::vector<pdm::ast::HeaderStmt*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_lpattern_field_cl: // lpattern_field_cl
        value.YY_MOVE_OR_COPY< std::vector<pdm::ast::LPattern::Field*> > (YY_MOVE (that.value));
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

      case symbol_kind::S_import_field_group: // import_field_group
        value.move< ast::ImportStmt::FieldGroup* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_native_mod_exp: // native_mod_exp
        value.move< pdm::ast::BaseModExp* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_mod_field: // mod_field
        value.move< pdm::ast::BaseModExp::Field* > (YY_MOVE (that.value));
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

      case symbol_kind::S_import_field_cl1: // import_field_cl1
        value.move< std::vector<ast::ImportStmt::Field*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_import_field_group_sl0: // import_field_group_sl0
        value.move< std::vector<ast::ImportStmt::FieldGroup*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_mod_field_sl: // mod_field_sl
        value.move< std::vector<pdm::ast::BaseModExp::Field*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_enum_type_spec_field_cl: // enum_type_spec_field_cl
        value.move< std::vector<pdm::ast::EnumTypeSpec::Field*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_mut_expr_cl1: // mut_expr_cl1
      case symbol_kind::S_expr_cl2: // expr_cl2
        value.move< std::vector<pdm::ast::Exp*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_script_header: // script_header
        value.move< std::vector<pdm::ast::HeaderStmt*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_lpattern_field_cl: // lpattern_field_cl
        value.move< std::vector<pdm::ast::LPattern::Field*> > (YY_MOVE (that.value));
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

      case symbol_kind::S_import_field_group: // import_field_group
        value.copy< ast::ImportStmt::FieldGroup* > (that.value);
        break;

      case symbol_kind::S_native_mod_exp: // native_mod_exp
        value.copy< pdm::ast::BaseModExp* > (that.value);
        break;

      case symbol_kind::S_mod_field: // mod_field
        value.copy< pdm::ast::BaseModExp::Field* > (that.value);
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

      case symbol_kind::S_import_field_cl1: // import_field_cl1
        value.copy< std::vector<ast::ImportStmt::Field*> > (that.value);
        break;

      case symbol_kind::S_import_field_group_sl0: // import_field_group_sl0
        value.copy< std::vector<ast::ImportStmt::FieldGroup*> > (that.value);
        break;

      case symbol_kind::S_mod_field_sl: // mod_field_sl
        value.copy< std::vector<pdm::ast::BaseModExp::Field*> > (that.value);
        break;

      case symbol_kind::S_enum_type_spec_field_cl: // enum_type_spec_field_cl
        value.copy< std::vector<pdm::ast::EnumTypeSpec::Field*> > (that.value);
        break;

      case symbol_kind::S_mut_expr_cl1: // mut_expr_cl1
      case symbol_kind::S_expr_cl2: // expr_cl2
        value.copy< std::vector<pdm::ast::Exp*> > (that.value);
        break;

      case symbol_kind::S_script_header: // script_header
        value.copy< std::vector<pdm::ast::HeaderStmt*> > (that.value);
        break;

      case symbol_kind::S_lpattern_field_cl: // lpattern_field_cl
        value.copy< std::vector<pdm::ast::LPattern::Field*> > (that.value);
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

      case symbol_kind::S_import_field_group: // import_field_group
        value.move< ast::ImportStmt::FieldGroup* > (that.value);
        break;

      case symbol_kind::S_native_mod_exp: // native_mod_exp
        value.move< pdm::ast::BaseModExp* > (that.value);
        break;

      case symbol_kind::S_mod_field: // mod_field
        value.move< pdm::ast::BaseModExp::Field* > (that.value);
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

      case symbol_kind::S_import_field_cl1: // import_field_cl1
        value.move< std::vector<ast::ImportStmt::Field*> > (that.value);
        break;

      case symbol_kind::S_import_field_group_sl0: // import_field_group_sl0
        value.move< std::vector<ast::ImportStmt::FieldGroup*> > (that.value);
        break;

      case symbol_kind::S_mod_field_sl: // mod_field_sl
        value.move< std::vector<pdm::ast::BaseModExp::Field*> > (that.value);
        break;

      case symbol_kind::S_enum_type_spec_field_cl: // enum_type_spec_field_cl
        value.move< std::vector<pdm::ast::EnumTypeSpec::Field*> > (that.value);
        break;

      case symbol_kind::S_mut_expr_cl1: // mut_expr_cl1
      case symbol_kind::S_expr_cl2: // expr_cl2
        value.move< std::vector<pdm::ast::Exp*> > (that.value);
        break;

      case symbol_kind::S_script_header: // script_header
        value.move< std::vector<pdm::ast::HeaderStmt*> > (that.value);
        break;

      case symbol_kind::S_lpattern_field_cl: // lpattern_field_cl
        value.move< std::vector<pdm::ast::LPattern::Field*> > (that.value);
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
    YY_USE (yyoutput);
    if (yysym.empty ())
      yyo << "empty symbol";
    else
      {
        symbol_kind_type yykind = yysym.kind ();
        yyo << (yykind < YYNTOKENS ? "token" : "nterm")
            << ' ' << yysym.name () << " ("
            << yysym.location << ": ";
        YY_USE (yykind);
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

      case symbol_kind::S_import_field_group: // import_field_group
        yylhs.value.emplace< ast::ImportStmt::FieldGroup* > ();
        break;

      case symbol_kind::S_native_mod_exp: // native_mod_exp
        yylhs.value.emplace< pdm::ast::BaseModExp* > ();
        break;

      case symbol_kind::S_mod_field: // mod_field
        yylhs.value.emplace< pdm::ast::BaseModExp::Field* > ();
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

      case symbol_kind::S_import_field_cl1: // import_field_cl1
        yylhs.value.emplace< std::vector<ast::ImportStmt::Field*> > ();
        break;

      case symbol_kind::S_import_field_group_sl0: // import_field_group_sl0
        yylhs.value.emplace< std::vector<ast::ImportStmt::FieldGroup*> > ();
        break;

      case symbol_kind::S_mod_field_sl: // mod_field_sl
        yylhs.value.emplace< std::vector<pdm::ast::BaseModExp::Field*> > ();
        break;

      case symbol_kind::S_enum_type_spec_field_cl: // enum_type_spec_field_cl
        yylhs.value.emplace< std::vector<pdm::ast::EnumTypeSpec::Field*> > ();
        break;

      case symbol_kind::S_mut_expr_cl1: // mut_expr_cl1
      case symbol_kind::S_expr_cl2: // expr_cl2
        yylhs.value.emplace< std::vector<pdm::ast::Exp*> > ();
        break;

      case symbol_kind::S_script_header: // script_header
        yylhs.value.emplace< std::vector<pdm::ast::HeaderStmt*> > ();
        break;

      case symbol_kind::S_lpattern_field_cl: // lpattern_field_cl
        yylhs.value.emplace< std::vector<pdm::ast::LPattern::Field*> > ();
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
#line 281 "parser.yy"
                                      {
    yylhs.value.as < pdm::ast::Script* > () = mgr->new_script(source, yylhs.location, std::move(yystack_[1].value.as < std::vector<pdm::ast::HeaderStmt*> > ()), std::move(yystack_[0].value.as < std::vector<pdm::ast::Script::Field*> > ()));

    // setting the returnp here => this is the node parser returns.  
    *returnp = yylhs.value.as < pdm::ast::Script* > (); 
}
#line 2328 "parser.tab.cc"
    break;

  case 3: // script_header: %empty
#line 289 "parser.yy"
                                                    { yylhs.value.as < std::vector<pdm::ast::HeaderStmt*> > ().reserve(16); }
#line 2334 "parser.tab.cc"
    break;

  case 4: // script_header: script_header script_header_stmt ";"
#line 290 "parser.yy"
                                                    { yylhs.value.as < std::vector<pdm::ast::HeaderStmt*> > () = std::move(yystack_[2].value.as < std::vector<pdm::ast::HeaderStmt*> > ()); yylhs.value.as < std::vector<pdm::ast::HeaderStmt*> > ().push_back(yystack_[1].value.as < pdm::ast::HeaderStmt* > ()); }
#line 2340 "parser.tab.cc"
    break;

  case 5: // script_header_stmt: import_stmt
#line 293 "parser.yy"
      { yylhs.value.as < pdm::ast::HeaderStmt* > () = yystack_[0].value.as < pdm::ast::HeaderStmt* > (); }
#line 2346 "parser.tab.cc"
    break;

  case 6: // script_field: "mod" vid native_mod_exp
#line 297 "parser.yy"
                                 { yylhs.value.as < pdm::ast::Script::Field* > () = mgr->new_script_field(yylhs.location, yystack_[1].value.as < TokenInfo > ().ID_intstr, yystack_[0].value.as < pdm::ast::BaseModExp* > ()); }
#line 2352 "parser.tab.cc"
    break;

  case 7: // script_field_sl: script_field ";"
#line 300 "parser.yy"
                                                { yylhs.value.as < std::vector<pdm::ast::Script::Field*> > ().push_back(yystack_[1].value.as < pdm::ast::Script::Field* > ()); }
#line 2358 "parser.tab.cc"
    break;

  case 8: // script_field_sl: script_field_sl script_field ";"
#line 301 "parser.yy"
                                                { yylhs.value.as < std::vector<pdm::ast::Script::Field*> > () = std::move(yystack_[2].value.as < std::vector<pdm::ast::Script::Field*> > ()); yylhs.value.as < std::vector<pdm::ast::Script::Field*> > ().push_back(yystack_[1].value.as < pdm::ast::Script::Field* > ()); }
#line 2364 "parser.tab.cc"
    break;

  case 9: // native_mod_exp: "{" mod_field_sl "}"
#line 309 "parser.yy"
                                              { yylhs.value.as < pdm::ast::BaseModExp* > () = mgr->new_native_mod_exp(yylhs.location, nullptr, std::move(yystack_[1].value.as < std::vector<pdm::ast::BaseModExp::Field*> > ())); }
#line 2370 "parser.tab.cc"
    break;

  case 10: // native_mod_exp: tpattern "{" mod_field_sl "}"
#line 310 "parser.yy"
                                              { yylhs.value.as < pdm::ast::BaseModExp* > () = mgr->new_native_mod_exp(yylhs.location, yystack_[3].value.as < pdm::ast::TPattern* > (), std::move(yystack_[1].value.as < std::vector<pdm::ast::BaseModExp::Field*> > ())); }
#line 2376 "parser.tab.cc"
    break;

  case 11: // native_mod_exp: "{" "}"
#line 311 "parser.yy"
                                              { yylhs.value.as < pdm::ast::BaseModExp* > () = mgr->new_native_mod_exp(yylhs.location, nullptr, std::move(std::vector<ast::BaseModExp::Field*>{})); }
#line 2382 "parser.tab.cc"
    break;

  case 12: // native_mod_exp: tpattern "{" "}"
#line 312 "parser.yy"
                                              { yylhs.value.as < pdm::ast::BaseModExp* > () = mgr->new_native_mod_exp(yylhs.location, yystack_[2].value.as < pdm::ast::TPattern* > (), std::move(std::vector<ast::BaseModExp::Field*>{})); }
#line 2388 "parser.tab.cc"
    break;

  case 13: // mod_field_sl: mod_field ";"
#line 315 "parser.yy"
                                        { yylhs.value.as < std::vector<pdm::ast::BaseModExp::Field*> > ().push_back(yystack_[1].value.as < pdm::ast::BaseModExp::Field* > ()); }
#line 2394 "parser.tab.cc"
    break;

  case 14: // mod_field_sl: mod_field_sl mod_field ";"
#line 316 "parser.yy"
                                        { yylhs.value.as < std::vector<pdm::ast::BaseModExp::Field*> > () = std::move(yystack_[2].value.as < std::vector<pdm::ast::BaseModExp::Field*> > ()); yylhs.value.as < std::vector<pdm::ast::BaseModExp::Field*> > ().push_back(yystack_[1].value.as < pdm::ast::BaseModExp::Field* > ()); }
#line 2400 "parser.tab.cc"
    break;

  case 15: // mod_field: "let" vid "=" long_exp
#line 319 "parser.yy"
                                  { yylhs.value.as < pdm::ast::BaseModExp::Field* > () = mgr->new_value_field_for_mod_exp(yylhs.location, yystack_[2].value.as < TokenInfo > ().ID_intstr, yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2406 "parser.tab.cc"
    break;

  case 16: // mod_field: "let" tid "=" type_spec
#line 320 "parser.yy"
                                  { yylhs.value.as < pdm::ast::BaseModExp::Field* > () = mgr->new_type_field_for_mod_exp(yylhs.location, yystack_[2].value.as < TokenInfo > ().ID_intstr, yystack_[0].value.as < pdm::ast::TypeSpec* > ()); }
#line 2412 "parser.tab.cc"
    break;

  case 17: // mod_field: "let" cid "=" class_spec
#line 321 "parser.yy"
                                  { yylhs.value.as < pdm::ast::BaseModExp::Field* > () = mgr->new_class_field_for_mod_exp(yylhs.location, yystack_[2].value.as < TokenInfo > ().ID_intstr, yystack_[0].value.as < pdm::ast::ClassSpec* > ()); }
#line 2418 "parser.tab.cc"
    break;

  case 18: // mod_field: "mod" vid native_mod_exp
#line 322 "parser.yy"
                                  { yylhs.value.as < pdm::ast::BaseModExp::Field* > () = mgr->new_mod_field_for_mod_exp(yylhs.location, yystack_[1].value.as < TokenInfo > ().ID_intstr, yystack_[0].value.as < pdm::ast::BaseModExp* > ()); }
#line 2424 "parser.tab.cc"
    break;

  case 19: // mod_field: "let" vid vpattern type_spec "=" bracketed_exp
#line 323 "parser.yy"
                                                       {
        auto desugared_type_spec = mgr->new_fn_type_spec(yylhs.location, yystack_[3].value.as < pdm::ast::VPattern* > (), yystack_[2].value.as < pdm::ast::TypeSpec* > ());
        auto desugared_exp = mgr->new_lambda_exp(yylhs.location, desugared_type_spec, yystack_[0].value.as < pdm::ast::Exp* > ());
        yylhs.value.as < pdm::ast::BaseModExp::Field* > () = mgr->new_value_field_for_mod_exp(yylhs.location, yystack_[4].value.as < TokenInfo > ().ID_intstr, desugared_exp);
      }
#line 2434 "parser.tab.cc"
    break;

  case 20: // mod_field: "let" cid "(" tid class_spec ")" "=" "{" type_query_exp_sl0 "}"
#line 328 "parser.yy"
                                                                                    {
         auto class_spec = mgr->new_class_exp_class_spec(yylhs.location, yystack_[6].value.as < TokenInfo > ().ID_intstr, yystack_[5].value.as < pdm::ast::ClassSpec* > (), std::move(yystack_[1].value.as < std::vector<pdm::ast::TypeQueryExp*> > ()));
         yylhs.value.as < pdm::ast::BaseModExp::Field* > () = mgr->new_class_field_for_mod_exp(yylhs.location, yystack_[8].value.as < TokenInfo > ().ID_intstr, class_spec);
      }
#line 2443 "parser.tab.cc"
    break;

  case 21: // import_stmt: "imports" "{" import_field_group_sl0 "}"
#line 339 "parser.yy"
                                                      {
        yylhs.value.as < pdm::ast::HeaderStmt* > () = mgr->new_import_stmt(yylhs.location, std::move(yystack_[1].value.as < std::vector<ast::ImportStmt::FieldGroup*> > ()));
      }
#line 2451 "parser.tab.cc"
    break;

  case 22: // import_field_group_sl0: %empty
#line 344 "parser.yy"
             {}
#line 2457 "parser.tab.cc"
    break;

  case 23: // import_field_group_sl0: import_field_group_sl0 import_field_group ";"
#line 345 "parser.yy"
                                                           { yylhs.value.as < std::vector<ast::ImportStmt::FieldGroup*> > () = std::move(yystack_[2].value.as < std::vector<ast::ImportStmt::FieldGroup*> > ()); yylhs.value.as < std::vector<ast::ImportStmt::FieldGroup*> > ().push_back(yystack_[1].value.as < ast::ImportStmt::FieldGroup* > ()); }
#line 2463 "parser.tab.cc"
    break;

  case 24: // import_field_group: import_field_cl1 "from" stringl
#line 348 "parser.yy"
                                         { yylhs.value.as < ast::ImportStmt::FieldGroup* > () = mgr->new_import_field_group(yylhs.location, std::move(yystack_[2].value.as < std::vector<ast::ImportStmt::Field*> > ()), *yystack_[0].value.as < TokenInfo > ().String_utf8string); }
#line 2469 "parser.tab.cc"
    break;

  case 25: // import_field_cl1: vid
#line 351 "parser.yy"
                                    { yylhs.value.as < std::vector<ast::ImportStmt::Field*> > ().push_back(mgr->new_import_field(yystack_[0].location, yystack_[0].value.as < TokenInfo > ().ID_intstr)); }
#line 2475 "parser.tab.cc"
    break;

  case 26: // import_field_cl1: import_field_cl1 "," vid
#line 352 "parser.yy"
                                    { yylhs.value.as < std::vector<ast::ImportStmt::Field*> > () = std::move(yystack_[2].value.as < std::vector<ast::ImportStmt::Field*> > ()); yylhs.value.as < std::vector<ast::ImportStmt::Field*> > ().push_back(mgr->new_import_field(yystack_[0].location, yystack_[0].value.as < TokenInfo > ().ID_intstr)); }
#line 2481 "parser.tab.cc"
    break;

  case 27: // chain_prefix_stmt: const_stmt
#line 356 "parser.yy"
      { yylhs.value.as < pdm::ast::Stmt* > () = yystack_[0].value.as < pdm::ast::Stmt* > (); }
#line 2487 "parser.tab.cc"
    break;

  case 28: // chain_prefix_stmt: val_stmt
#line 357 "parser.yy"
      { yylhs.value.as < pdm::ast::Stmt* > () = yystack_[0].value.as < pdm::ast::Stmt* > (); }
#line 2493 "parser.tab.cc"
    break;

  case 29: // chain_prefix_stmt: var_stmt
#line 358 "parser.yy"
      { yylhs.value.as < pdm::ast::Stmt* > () = yystack_[0].value.as < pdm::ast::Stmt* > (); }
#line 2499 "parser.tab.cc"
    break;

  case 30: // chain_prefix_stmt: set_stmt
#line 359 "parser.yy"
      { yylhs.value.as < pdm::ast::Stmt* > () = yystack_[0].value.as < pdm::ast::Stmt* > (); }
#line 2505 "parser.tab.cc"
    break;

  case 31: // chain_prefix_stmt: discard_stmt
#line 360 "parser.yy"
      { yylhs.value.as < pdm::ast::Stmt* > () = yystack_[0].value.as < pdm::ast::Stmt* > (); }
#line 2511 "parser.tab.cc"
    break;

  case 32: // const_stmt: "const" lpattern "=" expr
#line 363 "parser.yy"
                                  { yylhs.value.as < pdm::ast::Stmt* > () = mgr->new_const_stmt(yylhs.location, yystack_[2].value.as < pdm::ast::LPattern* > (), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2517 "parser.tab.cc"
    break;

  case 33: // val_stmt: "val" lpattern "=" expr
#line 366 "parser.yy"
                                  { yylhs.value.as < pdm::ast::Stmt* > () = mgr->new_val_stmt(yylhs.location, yystack_[2].value.as < pdm::ast::LPattern* > (), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2523 "parser.tab.cc"
    break;

  case 34: // var_stmt: "var" lpattern "=" expr
#line 369 "parser.yy"
                                  { yylhs.value.as < pdm::ast::Stmt* > () = mgr->new_var_stmt(yylhs.location, yystack_[2].value.as < pdm::ast::LPattern* > (), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2529 "parser.tab.cc"
    break;

  case 35: // set_stmt: "set" mut_expr "=" expr
#line 372 "parser.yy"
                                  { yylhs.value.as < pdm::ast::Stmt* > () = mgr->new_set_stmt(yylhs.location, yystack_[2].value.as < pdm::ast::Exp* > (), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2535 "parser.tab.cc"
    break;

  case 36: // discard_stmt: "discard" expr
#line 375 "parser.yy"
                        { yylhs.value.as < pdm::ast::Stmt* > () = mgr->new_discard_stmt(yylhs.location, yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2541 "parser.tab.cc"
    break;

  case 37: // tid: "TypeId"
#line 382 "parser.yy"
     { yylhs.value.as < TokenInfo > () = yystack_[0].value.as < TokenInfo > (); }
#line 2547 "parser.tab.cc"
    break;

  case 38: // vid: "val_id"
#line 383 "parser.yy"
     { yylhs.value.as < TokenInfo > () = yystack_[0].value.as < TokenInfo > (); }
#line 2553 "parser.tab.cc"
    break;

  case 39: // cid: "CLS_ID"
#line 384 "parser.yy"
     { yylhs.value.as < TokenInfo > () = yystack_[0].value.as < TokenInfo > (); }
#line 2559 "parser.tab.cc"
    break;

  case 40: // floatl: "4.2"
#line 387 "parser.yy"
      { yylhs.value.as < TokenInfo > () = yystack_[0].value.as < TokenInfo > (); }
#line 2565 "parser.tab.cc"
    break;

  case 41: // stringl: "'sq-string-literal'"
#line 390 "parser.yy"
      { yylhs.value.as < TokenInfo > () = yystack_[0].value.as < TokenInfo > (); }
#line 2571 "parser.tab.cc"
    break;

  case 42: // stringl: "\"dq-string-literal\""
#line 391 "parser.yy"
      { yylhs.value.as < TokenInfo > () = yystack_[0].value.as < TokenInfo > (); }
#line 2577 "parser.tab.cc"
    break;

  case 43: // mod_prefix: vid ":"
#line 394 "parser.yy"
                                                  { yylhs.value.as < pdm::ast::ModAddress* > () = mgr->new_mod_address(yylhs.location, nullptr, yystack_[1].value.as < TokenInfo > ().ID_intstr, std::move(std::vector<ast::TArg*>{})); }
#line 2583 "parser.tab.cc"
    break;

  case 44: // mod_prefix: vid "[" targ_cl "]" ":"
#line 395 "parser.yy"
                                                  { yylhs.value.as < pdm::ast::ModAddress* > () = mgr->new_mod_address(yylhs.location, nullptr, yystack_[4].value.as < TokenInfo > ().ID_intstr, std::move(yystack_[2].value.as < std::vector<pdm::ast::TArg*> > ())); }
#line 2589 "parser.tab.cc"
    break;

  case 45: // mod_prefix: mod_prefix vid ":"
#line 396 "parser.yy"
                                                  { yylhs.value.as < pdm::ast::ModAddress* > () = mgr->new_mod_address(yylhs.location, yystack_[2].value.as < pdm::ast::ModAddress* > (), yystack_[1].value.as < TokenInfo > ().ID_intstr, std::move(std::vector<ast::TArg*>{})); }
#line 2595 "parser.tab.cc"
    break;

  case 46: // mod_prefix: mod_prefix vid "[" targ_cl "]" ":"
#line 397 "parser.yy"
                                                  { yylhs.value.as < pdm::ast::ModAddress* > () = mgr->new_mod_address(yylhs.location, yystack_[5].value.as < pdm::ast::ModAddress* > (), yystack_[4].value.as < TokenInfo > ().ID_intstr, std::move(yystack_[2].value.as < std::vector<pdm::ast::TArg*> > ())); }
#line 2601 "parser.tab.cc"
    break;

  case 47: // mut_expr: vid
#line 405 "parser.yy"
                                    { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_id_exp(yylhs.location, yystack_[0].value.as < TokenInfo > ().ID_intstr); }
#line 2607 "parser.tab.cc"
    break;

  case 48: // mut_expr: "(" mut_expr_cl1 ")"
#line 406 "parser.yy"
                                    { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_tuple_exp(yylhs.location, std::move(yystack_[1].value.as < std::vector<pdm::ast::Exp*> > ())); }
#line 2613 "parser.tab.cc"
    break;

  case 49: // mut_expr_cl1: mut_expr
#line 409 "parser.yy"
                                    { yylhs.value.as < std::vector<pdm::ast::Exp*> > ().push_back(yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2619 "parser.tab.cc"
    break;

  case 50: // mut_expr_cl1: mut_expr_cl1 "," mut_expr
#line 410 "parser.yy"
                                    { yylhs.value.as < std::vector<pdm::ast::Exp*> > () = std::move(yystack_[2].value.as < std::vector<pdm::ast::Exp*> > ()); yylhs.value.as < std::vector<pdm::ast::Exp*> > ().push_back(yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2625 "parser.tab.cc"
    break;

  case 51: // expr: binary_exp
#line 413 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2631 "parser.tab.cc"
    break;

  case 52: // long_exp: expr
#line 416 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2637 "parser.tab.cc"
    break;

  case 53: // long_exp: lambda_exp
#line 417 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2643 "parser.tab.cc"
    break;

  case 54: // expr_cl2: expr "," expr
#line 429 "parser.yy"
                             { yylhs.value.as < std::vector<pdm::ast::Exp*> > ().reserve(2); yylhs.value.as < std::vector<pdm::ast::Exp*> > ().push_back(yystack_[2].value.as < pdm::ast::Exp* > ()); yylhs.value.as < std::vector<pdm::ast::Exp*> > ().push_back(yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2649 "parser.tab.cc"
    break;

  case 55: // expr_cl2: expr_cl2 "," expr
#line 430 "parser.yy"
                             { yylhs.value.as < std::vector<pdm::ast::Exp*> > () = std::move(yystack_[2].value.as < std::vector<pdm::ast::Exp*> > ()); yylhs.value.as < std::vector<pdm::ast::Exp*> > ().push_back(yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2655 "parser.tab.cc"
    break;

  case 56: // type_query_exp_sl0: %empty
#line 433 "parser.yy"
                                                  {}
#line 2661 "parser.tab.cc"
    break;

  case 57: // type_query_exp_sl0: type_query_exp_sl0 type_query_exp ";"
#line 434 "parser.yy"
                                                  { yylhs.value.as < std::vector<pdm::ast::TypeQueryExp*> > () = std::move(yystack_[2].value.as < std::vector<pdm::ast::TypeQueryExp*> > ()); yylhs.value.as < std::vector<pdm::ast::TypeQueryExp*> > ().push_back(yystack_[1].value.as < pdm::ast::TypeQueryExp* > ()); }
#line 2667 "parser.tab.cc"
    break;

  case 58: // bracketed_exp: paren_exp
#line 438 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2673 "parser.tab.cc"
    break;

  case 59: // bracketed_exp: vtupleExpr
#line 439 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2679 "parser.tab.cc"
    break;

  case 60: // bracketed_exp: vstructExpr
#line 440 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2685 "parser.tab.cc"
    break;

  case 61: // bracketed_exp: chain_exp
#line 441 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2691 "parser.tab.cc"
    break;

  case 62: // paren_exp: "(" long_exp ")"
#line 452 "parser.yy"
                              { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_paren_exp(yylhs.location, yystack_[1].value.as < pdm::ast::Exp* > ()); }
#line 2697 "parser.tab.cc"
    break;

  case 63: // vtupleExpr: "(" ")"
#line 455 "parser.yy"
                                   { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_tuple_exp(yylhs.location, std::move(std::vector<ast::Exp*>())); }
#line 2703 "parser.tab.cc"
    break;

  case 64: // vtupleExpr: "(" expr "," ")"
#line 456 "parser.yy"
                                   { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_tuple_exp(yylhs.location, std::move(std::vector(1,yystack_[2].value.as < pdm::ast::Exp* > ()))); }
#line 2709 "parser.tab.cc"
    break;

  case 65: // vtupleExpr: "(" expr_cl2 ")"
#line 457 "parser.yy"
                                   { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_tuple_exp(yylhs.location, std::move(yystack_[1].value.as < std::vector<pdm::ast::Exp*> > ())); }
#line 2715 "parser.tab.cc"
    break;

  case 66: // vstructExpr: "{" struct_exp_field_cl "}"
#line 460 "parser.yy"
                                            { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_struct_exp(yylhs.location, std::move(yystack_[1].value.as < std::vector<pdm::ast::StructExp::Field*> > ())); }
#line 2721 "parser.tab.cc"
    break;

  case 67: // primary_exp: bracketed_exp
#line 463 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2727 "parser.tab.cc"
    break;

  case 68: // primary_exp: vid
#line 464 "parser.yy"
                     { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_id_exp(yylhs.location, yystack_[0].value.as < TokenInfo > ().ID_intstr); }
#line 2733 "parser.tab.cc"
    break;

  case 69: // primary_exp: int_expr
#line 465 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2739 "parser.tab.cc"
    break;

  case 70: // primary_exp: floatl
#line 466 "parser.yy"
                     { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_float_exp(yylhs.location, yystack_[0].value.as < TokenInfo > ().Float); }
#line 2745 "parser.tab.cc"
    break;

  case 71: // primary_exp: stringls
#line 467 "parser.yy"
                     { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_string_exp(yylhs.location, std::move(yystack_[0].value.as < std::vector<pdm::ast::StringExp::Piece> > ())); }
#line 2751 "parser.tab.cc"
    break;

  case 72: // primary_exp: if_exp
#line 468 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2757 "parser.tab.cc"
    break;

  case 73: // primary_exp: mod_prefix vid
#line 469 "parser.yy"
                        { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_module_dot_name_exp(yylhs.location, yystack_[1].value.as < pdm::ast::ModAddress* > (), yystack_[0].value.as < TokenInfo > ().ID_intstr); }
#line 2763 "parser.tab.cc"
    break;

  case 74: // int_expr: "42"
#line 472 "parser.yy"
                { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_int_exp(yylhs.location, yystack_[0].value.as < TokenInfo > ().Int, ast::IntExp::Base::Dec, false); }
#line 2769 "parser.tab.cc"
    break;

  case 75: // int_expr: "0x2a"
#line 473 "parser.yy"
                { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_int_exp(yylhs.location, yystack_[0].value.as < TokenInfo > ().Int, ast::IntExp::Base::Hex, false); }
#line 2775 "parser.tab.cc"
    break;

  case 76: // int_expr: "42u"
#line 474 "parser.yy"
                         { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_int_exp(yylhs.location, yystack_[0].value.as < TokenInfo > ().Int, ast::IntExp::Base::Dec, true); }
#line 2781 "parser.tab.cc"
    break;

  case 77: // int_expr: "0x2Au"
#line 475 "parser.yy"
                         { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_int_exp(yylhs.location, yystack_[0].value.as < TokenInfo > ().Int, ast::IntExp::Base::Hex, true); }
#line 2787 "parser.tab.cc"
    break;

  case 78: // stringls: "'sq-string-literal'"
#line 478 "parser.yy"
                             { yylhs.value.as < std::vector<pdm::ast::StringExp::Piece> > ().emplace_back(yylhs.location, *yystack_[0].value.as < TokenInfo > ().String_utf8string, ast::StringExp::QuoteKind::SingleQuote); }
#line 2793 "parser.tab.cc"
    break;

  case 79: // stringls: "\"dq-string-literal\""
#line 479 "parser.yy"
                             { yylhs.value.as < std::vector<pdm::ast::StringExp::Piece> > ().emplace_back(yylhs.location, *yystack_[0].value.as < TokenInfo > ().String_utf8string, ast::StringExp::QuoteKind::DoubleQuote); }
#line 2799 "parser.tab.cc"
    break;

  case 80: // stringls: stringls "'sq-string-literal'"
#line 480 "parser.yy"
                             { yylhs.value.as < std::vector<pdm::ast::StringExp::Piece> > () = std::move(yystack_[1].value.as < std::vector<pdm::ast::StringExp::Piece> > ()); yylhs.value.as < std::vector<pdm::ast::StringExp::Piece> > ().emplace_back(yystack_[0].location, *yystack_[0].value.as < TokenInfo > ().String_utf8string, ast::StringExp::QuoteKind::SingleQuote); }
#line 2805 "parser.tab.cc"
    break;

  case 81: // stringls: stringls "\"dq-string-literal\""
#line 481 "parser.yy"
                             { yylhs.value.as < std::vector<pdm::ast::StringExp::Piece> > () = std::move(yystack_[1].value.as < std::vector<pdm::ast::StringExp::Piece> > ()); yylhs.value.as < std::vector<pdm::ast::StringExp::Piece> > ().emplace_back(yystack_[0].location, *yystack_[0].value.as < TokenInfo > ().String_utf8string, ast::StringExp::QuoteKind::DoubleQuote); }
#line 2811 "parser.tab.cc"
    break;

  case 82: // if_exp: "if" bracketed_exp bracketed_exp
#line 484 "parser.yy"
                                                                { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_if_exp(yylhs.location, yystack_[1].value.as < pdm::ast::Exp* > (), yystack_[0].value.as < pdm::ast::Exp* > (), nullptr); }
#line 2817 "parser.tab.cc"
    break;

  case 83: // if_exp: "if" bracketed_exp bracketed_exp "else" primary_exp
#line 485 "parser.yy"
                                                                { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_if_exp(yylhs.location, yystack_[3].value.as < pdm::ast::Exp* > (), yystack_[2].value.as < pdm::ast::Exp* > (), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2823 "parser.tab.cc"
    break;

  case 84: // chain_exp: "{" "}"
#line 488 "parser.yy"
                                               { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_chain_exp(yylhs.location, std::move(std::vector<ast::Stmt*>{}), nullptr); }
#line 2829 "parser.tab.cc"
    break;

  case 85: // chain_exp: "{" long_exp "}"
#line 489 "parser.yy"
                                               { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_chain_exp(yylhs.location, std::move(std::vector<ast::Stmt*>{}), yystack_[1].value.as < pdm::ast::Exp* > ()); }
#line 2835 "parser.tab.cc"
    break;

  case 86: // chain_exp: "{" chain_prefix "}"
#line 490 "parser.yy"
                                               { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_chain_exp(yylhs.location, std::move(yystack_[1].value.as < std::vector<pdm::ast::Stmt*> > ()), nullptr); }
#line 2841 "parser.tab.cc"
    break;

  case 87: // chain_exp: "{" chain_prefix long_exp "}"
#line 491 "parser.yy"
                                               { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_chain_exp(yylhs.location, std::move(yystack_[2].value.as < std::vector<pdm::ast::Stmt*> > ()), yystack_[1].value.as < pdm::ast::Exp* > ()); }
#line 2847 "parser.tab.cc"
    break;

  case 88: // chain_prefix: chain_prefix_stmt ";"
#line 494 "parser.yy"
                                                { yylhs.value.as < std::vector<pdm::ast::Stmt*> > ().push_back(yystack_[1].value.as < pdm::ast::Stmt* > ()); }
#line 2853 "parser.tab.cc"
    break;

  case 89: // chain_prefix: chain_prefix chain_prefix_stmt ";"
#line 495 "parser.yy"
                                                { yylhs.value.as < std::vector<pdm::ast::Stmt*> > () = std::move(yystack_[2].value.as < std::vector<pdm::ast::Stmt*> > ()); yylhs.value.as < std::vector<pdm::ast::Stmt*> > ().push_back(yystack_[1].value.as < pdm::ast::Stmt* > ()); }
#line 2859 "parser.tab.cc"
    break;

  case 90: // lambda_exp: fn_type_spec bracketed_exp
#line 498 "parser.yy"
                                   { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_lambda_exp(yylhs.location, yystack_[1].value.as < pdm::ast::FnTypeSpec* > (), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2865 "parser.tab.cc"
    break;

  case 91: // postfix_exp: primary_exp
#line 502 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2871 "parser.tab.cc"
    break;

  case 92: // postfix_exp: vcall_exp
#line 503 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2877 "parser.tab.cc"
    break;

  case 93: // postfix_exp: dot_name_exp
#line 504 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2883 "parser.tab.cc"
    break;

  case 94: // postfix_exp: dot_index_exp
#line 505 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2889 "parser.tab.cc"
    break;

  case 95: // vcall_exp: postfix_exp "(" ")"
#line 508 "parser.yy"
                                            { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_vcall_exp(yylhs.location, yystack_[2].value.as < pdm::ast::Exp* > (), std::move(std::vector<ast::VArg*>{})); }
#line 2895 "parser.tab.cc"
    break;

  case 96: // vcall_exp: postfix_exp "(" varg_cl ")"
#line 509 "parser.yy"
                                            { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_vcall_exp(yylhs.location, yystack_[3].value.as < pdm::ast::Exp* > (), std::move(yystack_[1].value.as < std::vector<pdm::ast::VArg*> > ())); }
#line 2901 "parser.tab.cc"
    break;

  case 97: // dot_name_exp: postfix_exp "." "val_id"
#line 512 "parser.yy"
                                                { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_struct_dot_name_exp(yylhs.location, yystack_[2].value.as < pdm::ast::Exp* > (), yystack_[0].value.as < TokenInfo > ().ID_intstr); }
#line 2907 "parser.tab.cc"
    break;

  case 98: // dot_name_exp: type_spec "::" "TypeId"
#line 513 "parser.yy"
                                                    { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_enum_dot_name_exp(yylhs.location, yystack_[2].value.as < pdm::ast::TypeSpec* > (), yystack_[0].value.as < TokenInfo > ().ID_intstr, nullptr); }
#line 2913 "parser.tab.cc"
    break;

  case 99: // dot_name_exp: type_spec "::" "TypeId" "using" paren_exp
#line 514 "parser.yy"
                                                    { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_enum_dot_name_exp(yylhs.location, yystack_[4].value.as < pdm::ast::TypeSpec* > (), yystack_[2].value.as < TokenInfo > ().ID_intstr, yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2919 "parser.tab.cc"
    break;

  case 100: // dot_index_exp: postfix_exp "." int_expr
#line 517 "parser.yy"
                                    { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_dot_index_exp(yylhs.location, yystack_[2].value.as < pdm::ast::Exp* > (), yystack_[0].value.as < pdm::ast::Exp* > (), ast::DotIndexExp::RhsHint::LhsNotPtr); }
#line 2925 "parser.tab.cc"
    break;

  case 101: // dot_index_exp: postfix_exp "." bracketed_exp
#line 518 "parser.yy"
                                    { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_dot_index_exp(yylhs.location, yystack_[2].value.as < pdm::ast::Exp* > (), yystack_[0].value.as < pdm::ast::Exp* > (), ast::DotIndexExp::RhsHint::LhsNotPtr); }
#line 2931 "parser.tab.cc"
    break;

  case 102: // unary_exp: postfix_exp
#line 522 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2937 "parser.tab.cc"
    break;

  case 103: // unary_exp: unary_op unary_exp
#line 523 "parser.yy"
                             { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_unary_exp(yylhs.location, yystack_[1].value.as < pdm::ast::UnaryOperator > (), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2943 "parser.tab.cc"
    break;

  case 104: // unary_op: "+"
#line 526 "parser.yy"
                 { yylhs.value.as < pdm::ast::UnaryOperator > () = ast::UnaryOperator::Plus; }
#line 2949 "parser.tab.cc"
    break;

  case 105: // unary_op: "-"
#line 527 "parser.yy"
                 { yylhs.value.as < pdm::ast::UnaryOperator > () = ast::UnaryOperator::Minus; }
#line 2955 "parser.tab.cc"
    break;

  case 106: // unary_op: "not"
#line 528 "parser.yy"
                 { yylhs.value.as < pdm::ast::UnaryOperator > () = ast::UnaryOperator::Not; }
#line 2961 "parser.tab.cc"
    break;

  case 107: // binary_exp: or_binary_exp
#line 532 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2967 "parser.tab.cc"
    break;

  case 108: // mul_binary_op: "*"
#line 535 "parser.yy"
                 { yylhs.value.as < pdm::ast::BinaryOperator > () = ast::BinaryOperator::Mul; }
#line 2973 "parser.tab.cc"
    break;

  case 109: // mul_binary_op: "/"
#line 536 "parser.yy"
                 { yylhs.value.as < pdm::ast::BinaryOperator > () = ast::BinaryOperator::Div; }
#line 2979 "parser.tab.cc"
    break;

  case 110: // mul_binary_op: "%"
#line 537 "parser.yy"
                 { yylhs.value.as < pdm::ast::BinaryOperator > () = ast::BinaryOperator::Rem; }
#line 2985 "parser.tab.cc"
    break;

  case 111: // mul_binary_exp: unary_exp
#line 540 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2991 "parser.tab.cc"
    break;

  case 112: // mul_binary_exp: mul_binary_exp mul_binary_op unary_exp
#line 541 "parser.yy"
                                               { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_binary_exp(yylhs.location, yystack_[1].value.as < pdm::ast::BinaryOperator > (), yystack_[2].value.as < pdm::ast::Exp* > (), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2997 "parser.tab.cc"
    break;

  case 113: // add_binary_op: "+"
#line 544 "parser.yy"
             { yylhs.value.as < pdm::ast::BinaryOperator > () = ast::BinaryOperator::Add; }
#line 3003 "parser.tab.cc"
    break;

  case 114: // add_binary_op: "-"
#line 545 "parser.yy"
             { yylhs.value.as < pdm::ast::BinaryOperator > () = ast::BinaryOperator::Subtract; }
#line 3009 "parser.tab.cc"
    break;

  case 115: // add_binary_exp: mul_binary_exp
#line 548 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 3015 "parser.tab.cc"
    break;

  case 116: // add_binary_exp: add_binary_exp add_binary_op mul_binary_exp
#line 549 "parser.yy"
                                                    { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_binary_exp(yylhs.location, yystack_[1].value.as < pdm::ast::BinaryOperator > (), yystack_[2].value.as < pdm::ast::Exp* > (), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 3021 "parser.tab.cc"
    break;

  case 117: // cmp_binary_op: "<"
#line 552 "parser.yy"
                { yylhs.value.as < pdm::ast::BinaryOperator > () = ast::BinaryOperator::Less; }
#line 3027 "parser.tab.cc"
    break;

  case 118: // cmp_binary_op: "<="
#line 553 "parser.yy"
                { yylhs.value.as < pdm::ast::BinaryOperator > () = ast::BinaryOperator::LessOrEq; }
#line 3033 "parser.tab.cc"
    break;

  case 119: // cmp_binary_op: ">"
#line 554 "parser.yy"
                { yylhs.value.as < pdm::ast::BinaryOperator > () = ast::BinaryOperator::Greater; }
#line 3039 "parser.tab.cc"
    break;

  case 120: // cmp_binary_op: ">="
#line 555 "parser.yy"
                { yylhs.value.as < pdm::ast::BinaryOperator > () = ast::BinaryOperator::GreaterOrEq; }
#line 3045 "parser.tab.cc"
    break;

  case 121: // cmp_binary_exp: add_binary_exp
#line 558 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 3051 "parser.tab.cc"
    break;

  case 122: // cmp_binary_exp: cmp_binary_exp cmp_binary_op add_binary_exp
#line 559 "parser.yy"
                                                    { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_binary_exp(yylhs.location, yystack_[1].value.as < pdm::ast::BinaryOperator > (), yystack_[2].value.as < pdm::ast::Exp* > (), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 3057 "parser.tab.cc"
    break;

  case 123: // eq_binary_op: "=="
#line 562 "parser.yy"
                 { yylhs.value.as < pdm::ast::BinaryOperator > () = ast::BinaryOperator::Equals; }
#line 3063 "parser.tab.cc"
    break;

  case 124: // eq_binary_op: "!="
#line 563 "parser.yy"
                 { yylhs.value.as < pdm::ast::BinaryOperator > () = ast::BinaryOperator::NotEquals; }
#line 3069 "parser.tab.cc"
    break;

  case 125: // eq_binary_exp: cmp_binary_exp
#line 566 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 3075 "parser.tab.cc"
    break;

  case 126: // eq_binary_exp: eq_binary_exp eq_binary_op cmp_binary_exp
#line 567 "parser.yy"
                                                { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_binary_exp(yylhs.location, yystack_[1].value.as < pdm::ast::BinaryOperator > (), yystack_[2].value.as < pdm::ast::Exp* > (), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 3081 "parser.tab.cc"
    break;

  case 127: // and_binary_exp: eq_binary_exp
#line 570 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 3087 "parser.tab.cc"
    break;

  case 128: // and_binary_exp: and_binary_exp "and" eq_binary_exp
#line 571 "parser.yy"
                                           { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_binary_exp(yylhs.location, ast::BinaryOperator::And, yystack_[2].value.as < pdm::ast::Exp* > (), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 3093 "parser.tab.cc"
    break;

  case 129: // xor_binary_exp: and_binary_exp
#line 574 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 3099 "parser.tab.cc"
    break;

  case 130: // xor_binary_exp: xor_binary_exp "xor" and_binary_exp
#line 575 "parser.yy"
                                           { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_binary_exp(yylhs.location, ast::BinaryOperator::XOr, yystack_[2].value.as < pdm::ast::Exp* > (), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 3105 "parser.tab.cc"
    break;

  case 131: // or_binary_exp: xor_binary_exp
#line 578 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 3111 "parser.tab.cc"
    break;

  case 132: // or_binary_exp: or_binary_exp "or" xor_binary_exp
#line 579 "parser.yy"
                                           { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_binary_exp(yylhs.location, ast::BinaryOperator::Or, yystack_[2].value.as < pdm::ast::Exp* > (), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 3117 "parser.tab.cc"
    break;

  case 133: // type_query_exp: type_spec type_query_op type_spec
#line 583 "parser.yy"
                                          { yylhs.value.as < pdm::ast::TypeQueryExp* > () = mgr->new_type_query_exp(yylhs.location, yystack_[1].value.as < pdm::ast::TypeQueryKind > (), yystack_[2].value.as < pdm::ast::TypeSpec* > (), yystack_[0].value.as < pdm::ast::TypeSpec* > ()); }
#line 3123 "parser.tab.cc"
    break;

  case 134: // type_query_op: ":<"
#line 586 "parser.yy"
                    { yylhs.value.as < pdm::ast::TypeQueryKind > () = ast::TypeQueryKind::LhsSubtypesRhs; }
#line 3129 "parser.tab.cc"
    break;

  case 135: // type_query_op: ">:"
#line 587 "parser.yy"
                    { yylhs.value.as < pdm::ast::TypeQueryKind > () = ast::TypeQueryKind::LhsSupertypesRhs; }
#line 3135 "parser.tab.cc"
    break;

  case 136: // type_query_op: "=="
#line 588 "parser.yy"
                    { yylhs.value.as < pdm::ast::TypeQueryKind > () = ast::TypeQueryKind::LhsEqualsRhs; }
#line 3141 "parser.tab.cc"
    break;

  case 137: // type_spec_cl2: type_spec "," type_spec
#line 603 "parser.yy"
                                    { yylhs.value.as < std::vector<pdm::ast::TypeSpec*> > ().reserve(2); yylhs.value.as < std::vector<pdm::ast::TypeSpec*> > ().push_back(yystack_[2].value.as < pdm::ast::TypeSpec* > ()); yylhs.value.as < std::vector<pdm::ast::TypeSpec*> > ().push_back(yystack_[0].value.as < pdm::ast::TypeSpec* > ()); }
#line 3147 "parser.tab.cc"
    break;

  case 138: // type_spec_cl2: type_spec_cl2 "," type_spec
#line 604 "parser.yy"
                                    { yylhs.value.as < std::vector<pdm::ast::TypeSpec*> > () = std::move(yystack_[2].value.as < std::vector<pdm::ast::TypeSpec*> > ()); yylhs.value.as < std::vector<pdm::ast::TypeSpec*> > ().push_back(yystack_[0].value.as < pdm::ast::TypeSpec* > ()); }
#line 3153 "parser.tab.cc"
    break;

  case 139: // type_spec: tid
#line 608 "parser.yy"
                        { yylhs.value.as < pdm::ast::TypeSpec* > () = mgr->new_id_type_spec(yylhs.location, yystack_[0].value.as < TokenInfo > ().ID_intstr); }
#line 3159 "parser.tab.cc"
    break;

  case 140: // type_spec: mod_prefix_tid
#line 609 "parser.yy"
      { yylhs.value.as < pdm::ast::TypeSpec* > () = yystack_[0].value.as < pdm::ast::TypeSpec* > (); }
#line 3165 "parser.tab.cc"
    break;

  case 141: // type_spec: tuple_type_spec
#line 610 "parser.yy"
      { yylhs.value.as < pdm::ast::TypeSpec* > () = yystack_[0].value.as < pdm::ast::TypeSpec* > (); }
#line 3171 "parser.tab.cc"
    break;

  case 142: // type_spec: array_type_spec
#line 611 "parser.yy"
      { yylhs.value.as < pdm::ast::TypeSpec* > () = yystack_[0].value.as < pdm::ast::TypeSpec* > (); }
#line 3177 "parser.tab.cc"
    break;

  case 143: // type_spec: struct_type_spec
#line 612 "parser.yy"
      { yylhs.value.as < pdm::ast::TypeSpec* > () = yystack_[0].value.as < pdm::ast::TypeSpec* > (); }
#line 3183 "parser.tab.cc"
    break;

  case 144: // type_spec: enum_type_spec
#line 613 "parser.yy"
      { yylhs.value.as < pdm::ast::TypeSpec* > () = yystack_[0].value.as < pdm::ast::TypeSpec* > (); }
#line 3189 "parser.tab.cc"
    break;

  case 145: // type_spec: fn_type_spec
#line 614 "parser.yy"
                    { yylhs.value.as < pdm::ast::TypeSpec* > () = dynamic_cast<ast::TypeSpec*>(yystack_[0].value.as < pdm::ast::FnTypeSpec* > ()); }
#line 3195 "parser.tab.cc"
    break;

  case 146: // mod_prefix_tid: mod_prefix tid
#line 618 "parser.yy"
                            { yylhs.value.as < pdm::ast::TypeSpec* > () = mgr->new_ma_type_spec(yylhs.location, yystack_[1].value.as < pdm::ast::ModAddress* > (), yystack_[0].value.as < TokenInfo > ().ID_intstr); }
#line 3201 "parser.tab.cc"
    break;

  case 147: // tuple_type_spec: "{" type_spec "}"
#line 622 "parser.yy"
                                   { yylhs.value.as < pdm::ast::TypeSpec* > () = mgr->new_tuple_type_spec(yylhs.location, std::move(std::vector(1,yystack_[1].value.as < pdm::ast::TypeSpec* > ()))); }
#line 3207 "parser.tab.cc"
    break;

  case 148: // tuple_type_spec: "{" type_spec_cl2 "}"
#line 623 "parser.yy"
                                   { yylhs.value.as < pdm::ast::TypeSpec* > () = mgr->new_tuple_type_spec(yylhs.location, std::move(yystack_[1].value.as < std::vector<pdm::ast::TypeSpec*> > ())); }
#line 3213 "parser.tab.cc"
    break;

  case 149: // array_type_spec: "[" type_spec "*" expr "]"
#line 626 "parser.yy"
                                                { yylhs.value.as < pdm::ast::TypeSpec* > () = nullptr; }
#line 3219 "parser.tab.cc"
    break;

  case 150: // struct_type_spec: "{" struct_type_spec_field_cl "}"
#line 630 "parser.yy"
                                               { yylhs.value.as < pdm::ast::TypeSpec* > () = mgr->new_struct_type_spec(yylhs.location, std::move(yystack_[1].value.as < std::vector<pdm::ast::StructTypeSpec::Field*> > ())); }
#line 3225 "parser.tab.cc"
    break;

  case 151: // struct_type_spec_field_cl: struct_type_spec_field
#line 633 "parser.yy"
                                                              { yylhs.value.as < std::vector<pdm::ast::StructTypeSpec::Field*> > ().push_back(yystack_[0].value.as < pdm::ast::StructTypeSpec::Field* > ()); }
#line 3231 "parser.tab.cc"
    break;

  case 152: // struct_type_spec_field_cl: struct_type_spec_field_cl "," struct_type_spec_field
#line 634 "parser.yy"
                                                              { yylhs.value.as < std::vector<pdm::ast::StructTypeSpec::Field*> > () = std::move(yystack_[2].value.as < std::vector<pdm::ast::StructTypeSpec::Field*> > ()); yylhs.value.as < std::vector<pdm::ast::StructTypeSpec::Field*> > ().push_back(yystack_[0].value.as < pdm::ast::StructTypeSpec::Field* > ()); }
#line 3237 "parser.tab.cc"
    break;

  case 153: // struct_type_spec_field: vid type_spec
#line 637 "parser.yy"
                                    { yylhs.value.as < pdm::ast::StructTypeSpec::Field* > () = mgr->new_struct_type_spec_field(yylhs.location, yystack_[1].value.as < TokenInfo > ().ID_intstr, yystack_[0].value.as < pdm::ast::TypeSpec* > ()); }
#line 3243 "parser.tab.cc"
    break;

  case 154: // enum_type_spec_field: tid
#line 641 "parser.yy"
                        { yylhs.value.as < pdm::ast::EnumTypeSpec::Field* > () = mgr->new_enum_type_spec_field(yylhs.location, yystack_[0].value.as < TokenInfo > ().ID_intstr, nullptr); }
#line 3249 "parser.tab.cc"
    break;

  case 155: // enum_type_spec_field: tid type_spec
#line 642 "parser.yy"
                        { yylhs.value.as < pdm::ast::EnumTypeSpec::Field* > () = mgr->new_enum_type_spec_field(yylhs.location, yystack_[1].value.as < TokenInfo > ().ID_intstr, yystack_[0].value.as < pdm::ast::TypeSpec* > ()); }
#line 3255 "parser.tab.cc"
    break;

  case 156: // enum_type_spec_field_cl: enum_type_spec_field
#line 645 "parser.yy"
                                                            { yylhs.value.as < std::vector<pdm::ast::EnumTypeSpec::Field*> > ().push_back(yystack_[0].value.as < pdm::ast::EnumTypeSpec::Field* > ()); }
#line 3261 "parser.tab.cc"
    break;

  case 157: // enum_type_spec_field_cl: enum_type_spec_field_cl "," enum_type_spec_field
#line 646 "parser.yy"
                                                            { yylhs.value.as < std::vector<pdm::ast::EnumTypeSpec::Field*> > () = std::move(yystack_[2].value.as < std::vector<pdm::ast::EnumTypeSpec::Field*> > ()); yylhs.value.as < std::vector<pdm::ast::EnumTypeSpec::Field*> > ().push_back(yystack_[0].value.as < pdm::ast::EnumTypeSpec::Field* > ()); }
#line 3267 "parser.tab.cc"
    break;

  case 158: // enum_type_spec: "enum" "{" enum_type_spec_field_cl "}"
#line 649 "parser.yy"
                                                        { yylhs.value.as < pdm::ast::TypeSpec* > () = mgr->new_enum_type_spec(yylhs.location, std::move(yystack_[1].value.as < std::vector<pdm::ast::EnumTypeSpec::Field*> > ())); }
#line 3273 "parser.tab.cc"
    break;

  case 159: // fn_type_spec: "anonymous_fn" vpattern type_spec
#line 652 "parser.yy"
                               { yylhs.value.as < pdm::ast::FnTypeSpec* > () = mgr->new_fn_type_spec(yylhs.location, yystack_[1].value.as < pdm::ast::VPattern* > (), yystack_[0].value.as < pdm::ast::TypeSpec* > ()); }
#line 3279 "parser.tab.cc"
    break;

  case 160: // targ: type_spec
#line 655 "parser.yy"
                { yylhs.value.as < pdm::ast::TArg* > () = mgr->new_targ_type_spec(yylhs.location, yystack_[0].value.as < pdm::ast::TypeSpec* > ()); }
#line 3285 "parser.tab.cc"
    break;

  case 161: // targ: expr
#line 656 "parser.yy"
               { yylhs.value.as < pdm::ast::TArg* > () = mgr->new_targ_exp(yylhs.location, yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 3291 "parser.tab.cc"
    break;

  case 162: // targ_cl: targ
#line 659 "parser.yy"
                            { yylhs.value.as < std::vector<pdm::ast::TArg*> > ().push_back(yystack_[0].value.as < pdm::ast::TArg* > ()); }
#line 3297 "parser.tab.cc"
    break;

  case 163: // targ_cl: targ_cl "," targ
#line 660 "parser.yy"
                            { yylhs.value.as < std::vector<pdm::ast::TArg*> > () = std::move(yystack_[2].value.as < std::vector<pdm::ast::TArg*> > ()); yylhs.value.as < std::vector<pdm::ast::TArg*> > ().push_back(yystack_[0].value.as < pdm::ast::TArg* > ()); }
#line 3303 "parser.tab.cc"
    break;

  case 164: // varg: expr
#line 662 "parser.yy"
                            { yylhs.value.as < pdm::ast::VArg* > () = mgr->new_varg(yylhs.location, yystack_[0].value.as < pdm::ast::Exp* > (), ast::VArgAccessSpec::In); }
#line 3309 "parser.tab.cc"
    break;

  case 165: // varg: "out" mut_expr
#line 663 "parser.yy"
                            { yylhs.value.as < pdm::ast::VArg* > () = mgr->new_varg(yylhs.location, yystack_[0].value.as < pdm::ast::Exp* > (), ast::VArgAccessSpec::Out); }
#line 3315 "parser.tab.cc"
    break;

  case 166: // varg: "inout" mut_expr
#line 664 "parser.yy"
                            { yylhs.value.as < pdm::ast::VArg* > () = mgr->new_varg(yylhs.location, yystack_[0].value.as < pdm::ast::Exp* > (), ast::VArgAccessSpec::InOut); }
#line 3321 "parser.tab.cc"
    break;

  case 167: // varg_cl: varg
#line 667 "parser.yy"
                            { yylhs.value.as < std::vector<pdm::ast::VArg*> > ().push_back(yystack_[0].value.as < pdm::ast::VArg* > ()); }
#line 3327 "parser.tab.cc"
    break;

  case 168: // varg_cl: varg_cl "," varg
#line 668 "parser.yy"
                            { yylhs.value.as < std::vector<pdm::ast::VArg*> > () = std::move(yystack_[2].value.as < std::vector<pdm::ast::VArg*> > ()); yylhs.value.as < std::vector<pdm::ast::VArg*> > ().push_back(yystack_[0].value.as < pdm::ast::VArg* > ()); }
#line 3333 "parser.tab.cc"
    break;

  case 169: // class_spec: primary_class_spec
#line 678 "parser.yy"
      { yylhs.value.as < pdm::ast::ClassSpec* > () = yystack_[0].value.as < pdm::ast::ClassSpec* > (); }
#line 3339 "parser.tab.cc"
    break;

  case 170: // primary_class_spec: cid
#line 681 "parser.yy"
                        { yylhs.value.as < pdm::ast::ClassSpec* > () = mgr->new_id_class_spec(yylhs.location, yystack_[0].value.as < TokenInfo > ().ID_intstr); }
#line 3345 "parser.tab.cc"
    break;

  case 171: // primary_class_spec: mod_prefix_cid_class_spec
#line 682 "parser.yy"
      { yylhs.value.as < pdm::ast::ClassSpec* > () = yystack_[0].value.as < pdm::ast::ClassSpec* > (); }
#line 3351 "parser.tab.cc"
    break;

  case 172: // primary_class_spec: class_exp_class_spec
#line 683 "parser.yy"
      { yylhs.value.as < pdm::ast::ClassSpec* > () = yystack_[0].value.as < pdm::ast::ClassSpec* > (); }
#line 3357 "parser.tab.cc"
    break;

  case 173: // mod_prefix_cid_class_spec: mod_prefix cid
#line 686 "parser.yy"
                        { yylhs.value.as < pdm::ast::ClassSpec* > () = mgr->new_ma_class_spec(yylhs.location, std::move(yystack_[1].value.as < pdm::ast::ModAddress* > ()), yystack_[0].value.as < TokenInfo > ().ID_intstr); }
#line 3363 "parser.tab.cc"
    break;

  case 174: // class_exp_class_spec: "typeclass" "(" tid class_spec ")" "{" type_query_exp_sl0 "}"
#line 691 "parser.yy"
                                                                                 {
            yylhs.value.as < pdm::ast::ClassSpec* > () = mgr->new_class_exp_class_spec(yylhs.location, yystack_[5].value.as < TokenInfo > ().ID_intstr, yystack_[4].value.as < pdm::ast::ClassSpec* > (), std::move(yystack_[1].value.as < std::vector<pdm::ast::TypeQueryExp*> > ()));
        }
#line 3371 "parser.tab.cc"
    break;

  case 175: // struct_exp_field: vid "=" expr
#line 701 "parser.yy"
                    { yylhs.value.as < pdm::ast::StructExp::Field* > () = mgr->new_struct_exp_field(yylhs.location, yystack_[2].value.as < TokenInfo > ().ID_intstr, yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 3377 "parser.tab.cc"
    break;

  case 176: // vpattern_field: vid type_spec
#line 704 "parser.yy"
                             { yylhs.value.as < pdm::ast::VPattern::Field* > () = mgr->new_vpattern_field(yylhs.location, yystack_[1].value.as < TokenInfo > ().ID_intstr, yystack_[0].value.as < pdm::ast::TypeSpec* > (), ast::VArgAccessSpec::In); }
#line 3383 "parser.tab.cc"
    break;

  case 177: // vpattern_field: "out" vid type_spec
#line 705 "parser.yy"
                             { yylhs.value.as < pdm::ast::VPattern::Field* > () = mgr->new_vpattern_field(yylhs.location, yystack_[1].value.as < TokenInfo > ().ID_intstr, yystack_[0].value.as < pdm::ast::TypeSpec* > (), ast::VArgAccessSpec::Out); }
#line 3389 "parser.tab.cc"
    break;

  case 178: // vpattern_field: "inout" vid type_spec
#line 706 "parser.yy"
                             { yylhs.value.as < pdm::ast::VPattern::Field* > () = mgr->new_vpattern_field(yylhs.location, yystack_[1].value.as < TokenInfo > ().ID_intstr, yystack_[0].value.as < pdm::ast::TypeSpec* > (), ast::VArgAccessSpec::InOut); }
#line 3395 "parser.tab.cc"
    break;

  case 179: // lpattern_field: vid type_spec
#line 709 "parser.yy"
                     { yylhs.value.as < pdm::ast::LPattern::Field* > () = mgr->new_lpattern_field(yylhs.location, ast::LPattern::FieldKind::IdTypeSpecPair, yystack_[1].value.as < TokenInfo > ().ID_intstr, yystack_[0].value.as < pdm::ast::TypeSpec* > ()); }
#line 3401 "parser.tab.cc"
    break;

  case 180: // lpattern_field: vid
#line 710 "parser.yy"
                    { yylhs.value.as < pdm::ast::LPattern::Field* > () = mgr->new_lpattern_field(yylhs.location, ast::LPattern::FieldKind::IdSingleton, yystack_[0].value.as < TokenInfo > ().ID_intstr); }
#line 3407 "parser.tab.cc"
    break;

  case 181: // tpattern_field: vid type_spec
#line 713 "parser.yy"
                      { yylhs.value.as < pdm::ast::TPattern::Field* > () = mgr->new_value_tpattern_field(yylhs.location, yystack_[1].value.as < TokenInfo > ().ID_intstr, yystack_[0].value.as < pdm::ast::TypeSpec* > ()); }
#line 3413 "parser.tab.cc"
    break;

  case 182: // tpattern_field: tid class_spec
#line 714 "parser.yy"
                      { yylhs.value.as < pdm::ast::TPattern::Field* > () = mgr->new_type_tpattern_field(yylhs.location, yystack_[1].value.as < TokenInfo > ().ID_intstr, yystack_[0].value.as < pdm::ast::ClassSpec* > ()); }
#line 3419 "parser.tab.cc"
    break;

  case 183: // destructured_lpattern: "{" lpattern_field_cl "}"
#line 718 "parser.yy"
                                       { yylhs.value.as < pdm::ast::LPattern* > () = mgr->new_lpattern(yylhs.location, std::move(yystack_[1].value.as < std::vector<pdm::ast::LPattern::Field*> > ()), true); }
#line 3425 "parser.tab.cc"
    break;

  case 184: // lpattern: lpattern_field
#line 721 "parser.yy"
                        { yylhs.value.as < pdm::ast::LPattern* > () = mgr->new_lpattern(yylhs.location, std::move(std::vector<ast::LPattern::Field*>{1,yystack_[0].value.as < pdm::ast::LPattern::Field* > ()}), false); }
#line 3431 "parser.tab.cc"
    break;

  case 185: // lpattern: destructured_lpattern
#line 722 "parser.yy"
      { yylhs.value.as < pdm::ast::LPattern* > () = yystack_[0].value.as < pdm::ast::LPattern* > (); }
#line 3437 "parser.tab.cc"
    break;

  case 186: // vpattern: "(" vpattern_field_cl ")"
#line 725 "parser.yy"
                                       { yylhs.value.as < pdm::ast::VPattern* > () = mgr->new_vpattern(yylhs.location, std::move(yystack_[1].value.as < std::vector<pdm::ast::VPattern::Field*> > ())); }
#line 3443 "parser.tab.cc"
    break;

  case 187: // vpattern: "(" ")"
#line 726 "parser.yy"
                                       { yylhs.value.as < pdm::ast::VPattern* > () = mgr->new_vpattern(yylhs.location, std::move(std::vector<ast::VPattern::Field*>{})); }
#line 3449 "parser.tab.cc"
    break;

  case 188: // tpattern: "[" tpattern_field_cl1 "]"
#line 729 "parser.yy"
                                        { yylhs.value.as < pdm::ast::TPattern* > () = mgr->new_tpattern(yylhs.location, std::move(yystack_[1].value.as < std::vector<pdm::ast::TPattern::Field*> > ()), false); }
#line 3455 "parser.tab.cc"
    break;

  case 189: // vpattern_field_cl: vpattern_field
#line 733 "parser.yy"
                                              { yylhs.value.as < std::vector<pdm::ast::VPattern::Field*> > ().push_back(yystack_[0].value.as < pdm::ast::VPattern::Field* > ()); }
#line 3461 "parser.tab.cc"
    break;

  case 190: // vpattern_field_cl: vpattern_field_cl "," vpattern_field
#line 734 "parser.yy"
                                               { yylhs.value.as < std::vector<pdm::ast::VPattern::Field*> > () = std::move(yystack_[2].value.as < std::vector<pdm::ast::VPattern::Field*> > ()); yylhs.value.as < std::vector<pdm::ast::VPattern::Field*> > ().push_back(yystack_[0].value.as < pdm::ast::VPattern::Field* > ()); }
#line 3467 "parser.tab.cc"
    break;

  case 191: // lpattern_field_cl: lpattern_field
#line 737 "parser.yy"
                                               { yylhs.value.as < std::vector<pdm::ast::LPattern::Field*> > ().push_back(yystack_[0].value.as < pdm::ast::LPattern::Field* > ()); }
#line 3473 "parser.tab.cc"
    break;

  case 192: // lpattern_field_cl: lpattern_field_cl "," lpattern_field
#line 738 "parser.yy"
                                               { yylhs.value.as < std::vector<pdm::ast::LPattern::Field*> > () = std::move(yystack_[2].value.as < std::vector<pdm::ast::LPattern::Field*> > ()); yylhs.value.as < std::vector<pdm::ast::LPattern::Field*> > ().push_back(yystack_[0].value.as < pdm::ast::LPattern::Field* > ()); }
#line 3479 "parser.tab.cc"
    break;

  case 193: // tpattern_field_cl1: tpattern_field
#line 741 "parser.yy"
                                              { yylhs.value.as < std::vector<pdm::ast::TPattern::Field*> > ().push_back(yystack_[0].value.as < pdm::ast::TPattern::Field* > ()); }
#line 3485 "parser.tab.cc"
    break;

  case 194: // tpattern_field_cl1: tpattern_field_cl1 "," tpattern_field
#line 742 "parser.yy"
                                                { yylhs.value.as < std::vector<pdm::ast::TPattern::Field*> > () = std::move(yystack_[2].value.as < std::vector<pdm::ast::TPattern::Field*> > ()); yylhs.value.as < std::vector<pdm::ast::TPattern::Field*> > ().push_back(yystack_[0].value.as < pdm::ast::TPattern::Field* > ()); }
#line 3491 "parser.tab.cc"
    break;

  case 195: // struct_exp_field_cl: struct_exp_field
#line 745 "parser.yy"
                                                    { yylhs.value.as < std::vector<pdm::ast::StructExp::Field*> > ().push_back(yystack_[0].value.as < pdm::ast::StructExp::Field* > ()); }
#line 3497 "parser.tab.cc"
    break;

  case 196: // struct_exp_field_cl: struct_exp_field_cl "," struct_exp_field
#line 746 "parser.yy"
                                                    { yylhs.value.as < std::vector<pdm::ast::StructExp::Field*> > () = std::move(yystack_[2].value.as < std::vector<pdm::ast::StructExp::Field*> > ()); yylhs.value.as < std::vector<pdm::ast::StructExp::Field*> > ().push_back(yystack_[0].value.as < pdm::ast::StructExp::Field* > ()); }
#line 3503 "parser.tab.cc"
    break;


#line 3507 "parser.tab.cc"

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





  const short parser::yypact_ninf_ = -251;

  const signed char parser::yytable_ninf_ = -1;

  const short
  parser::yypact_[] =
  {
    -251,    36,    87,  -251,    15,    96,    44,   158,    46,  -251,
    -251,   119,  -251,  -251,  -251,   167,    63,    27,  -251,   110,
       4,  -251,  -251,   156,   200,  -251,    65,    15,   181,  -251,
      38,   178,    99,  -251,   184,    -9,  -251,  -251,   189,    82,
    -251,   263,  -251,  -251,  -251,  -251,   196,   197,   200,   200,
    -251,    63,  -251,  -251,  -251,  -251,  -251,  -251,  -251,    63,
    -251,   119,   195,    21,    55,  -251,   239,  -251,  -251,   102,
    -251,   246,    15,   287,  -251,   598,    83,  -251,   287,    12,
     200,   241,   188,    59,    62,   128,  -251,  -251,  -251,  -251,
     200,   598,   200,   287,   156,  -251,  -251,  -251,  -251,  -251,
    -251,   156,   191,  -251,  -251,  -251,  -251,  -251,  -251,  -251,
    -251,   531,   356,  -251,  -251,    82,  -251,    63,  -251,  -251,
    -251,  -251,  -251,  -251,  -251,   259,  -251,  -251,   193,  -251,
    -251,  -251,  -251,   598,  -251,   223,   245,   231,   240,   274,
     284,   285,   265,  -251,   169,  -251,   598,   200,  -251,   142,
      15,    15,  -251,   200,  -251,   206,  -251,   598,   598,  -251,
     200,  -251,   200,  -251,    15,  -251,  -251,  -251,  -251,  -251,
     265,   191,   249,   156,  -251,   261,   356,   191,  -251,   269,
     266,   211,     2,     2,     2,    14,   598,  -251,   270,  -251,
    -251,  -251,  -251,  -251,   116,   264,   410,   152,  -251,   147,
      83,  -251,  -251,    98,   464,  -251,  -251,  -251,  -251,   598,
    -251,  -251,   598,  -251,  -251,  -251,  -251,   598,  -251,  -251,
     598,   598,   598,   598,   318,   598,   286,   171,  -251,   287,
    -251,   200,   200,  -251,    18,  -251,   278,   151,  -251,  -251,
     200,  -251,  -251,   191,   283,   281,   -13,   322,   574,  -251,
     598,  -251,    15,   200,  -251,  -251,   271,   273,   275,    14,
    -251,   276,  -251,  -251,   598,  -251,  -251,   295,   289,    15,
    -251,  -251,  -251,  -251,    14,    14,  -251,  -251,  -251,   212,
    -251,   223,   245,   231,   240,   274,   284,   339,  -251,  -251,
     301,  -251,  -251,  -251,  -251,  -251,  -251,   282,  -251,   234,
    -251,  -251,  -251,  -251,   162,  -251,   598,   598,   598,  -251,
     213,   598,  -251,  -251,  -251,   288,  -251,  -251,  -251,   507,
    -251,   299,  -251,   296,    48,    15,  -251,    15,  -251,  -251,
    -251,  -251,    14,  -251,  -251,  -251,   598,  -251,  -251,  -251,
     303,    57,  -251,  -251,   141,  -251,  -251,  -251,  -251,   200,
    -251,  -251
  };

  const unsigned char
  parser::yydefact_[] =
  {
       3,     0,     0,     1,     0,     0,     0,     0,     2,     5,
      38,     0,    22,     4,     7,     0,     0,     0,     6,     0,
       0,     8,    37,     0,     0,   193,     0,     0,     0,    11,
       0,     0,     0,    21,     0,     0,    25,    39,     0,     0,
     170,     0,   182,   169,   171,   172,     0,     0,     0,     0,
     139,     0,   181,   140,   141,   142,   143,   144,   145,     0,
     188,     0,     0,     0,     0,     9,     0,    13,    12,     0,
      23,     0,     0,     0,    43,     0,     0,   173,     0,     0,
       0,     0,     0,     0,     0,     0,   151,   146,   194,    18,
       0,     0,     0,     0,     0,    14,    10,    42,    41,    24,
      26,     0,     0,   106,    74,    75,    76,    77,    40,    79,
      78,     0,     0,   104,   105,    68,    70,     0,   161,    67,
      58,    59,    60,    91,    69,    71,    72,    61,   102,    92,
      93,    94,   111,     0,    51,   115,   121,   125,   127,   129,
     131,   107,   160,   162,     0,    45,     0,   154,   156,     0,
       0,     0,   187,     0,   189,     0,   159,     0,     0,   153,
       0,   148,     0,   147,     0,   150,    16,    52,    15,    53,
       0,   145,     0,     0,    17,     0,     0,     0,    63,    52,
       0,     0,     0,     0,     0,     0,     0,    84,     0,    27,
      28,    29,    30,    31,    68,     0,     0,     0,   195,     0,
      73,    81,    80,     0,     0,   103,   108,   109,   110,     0,
     113,   114,     0,   117,   118,   119,   120,     0,   123,   124,
       0,     0,     0,     0,     0,     0,     0,     0,   155,     0,
     158,     0,     0,   176,     0,   186,     0,   160,   138,   137,
       0,   152,    90,     0,     0,     0,    68,    82,     0,    62,
       0,    65,     0,   180,   184,   185,     0,     0,     0,     0,
      47,     0,    36,    88,     0,    85,    86,     0,     0,     0,
      66,    97,   101,   100,     0,     0,    95,   164,   167,     0,
     112,   116,   122,   126,   128,   130,   132,    98,   163,    44,
       0,   157,   177,   178,   190,   149,    19,     0,    56,     0,
      64,    54,    55,   191,     0,   179,     0,     0,     0,    49,
       0,     0,   175,    89,    87,     0,   196,   165,   166,     0,
      96,     0,    46,     0,     0,     0,    83,     0,   183,    32,
      33,    34,     0,    48,    35,   168,     0,    99,    56,   174,
       0,     0,   192,    50,     0,    57,   136,   134,   135,     0,
      20,   133
  };

  const short
  parser::yypgoto_[] =
  {
    -251,  -251,  -251,  -251,   344,  -251,   292,   323,     0,  -251,
    -251,  -251,  -251,   160,  -251,  -251,  -251,  -251,  -251,     6,
      -4,   -15,  -251,  -251,   -20,  -234,  -251,    19,   -85,  -251,
      20,   -88,    40,  -251,  -251,    58,   159,  -251,  -251,  -251,
    -251,  -251,  -251,  -251,  -251,  -251,  -124,  -251,  -251,  -251,
     153,  -251,   146,  -251,   149,  -251,   154,   145,   150,  -251,
    -251,  -251,  -251,   139,  -251,  -251,  -251,  -251,  -251,   208,
     155,  -251,  -251,   -80,   157,   228,    64,  -251,   -93,  -251,
    -251,  -251,   117,   168,  -250,   328,  -251,   126,   326,  -251,
    -251,  -251,  -251,  -251
  };

  const short
  parser::yydefgoto_[] =
  {
       0,     1,     2,     6,     7,     8,    18,    30,    31,     9,
      20,    34,    35,   188,   189,   190,   191,   192,   193,    50,
     115,    40,   116,    99,   117,   261,   310,   167,   180,   181,
     324,   119,   120,   121,   122,   123,   124,   125,   126,   127,
     196,   169,   128,   129,   130,   131,   132,   133,   134,   209,
     135,   212,   136,   217,   137,   220,   138,   139,   140,   141,
     340,   349,    83,   170,    53,    54,    55,    56,    85,    86,
     148,   149,    57,    58,   143,   144,   278,   279,    42,    43,
      44,    45,   198,   154,   254,    25,   255,   256,    80,    19,
     155,   304,    26,   199
  };

  const short
  parser::yytable_[] =
  {
      11,   174,   303,    41,    51,    10,   168,    10,   175,   205,
      71,   171,    24,    64,   177,    10,    36,    10,    10,    39,
      39,    10,    23,    61,    63,   309,    77,   195,    51,    51,
      66,   171,   171,    74,    62,    27,     3,    76,    72,    75,
     317,   318,   150,   151,    39,    82,    27,    76,   150,   151,
      28,    10,    22,   264,     4,    24,   252,    87,    46,    33,
      51,    28,    51,   152,   259,    23,    10,    22,   100,    66,
      51,    79,    51,    47,    41,   153,    39,   342,    39,   101,
     244,    41,    29,   242,   147,   280,    39,    91,    39,   247,
      39,   195,    13,    65,   118,     4,   171,    39,   343,   173,
      48,   271,    49,   339,     5,    93,   160,    27,   194,   162,
      27,   268,    59,   200,   161,   272,   171,   163,    60,    10,
      22,    94,    28,    87,   346,    28,    46,    51,    74,   145,
     179,   347,   348,    51,    75,   146,   104,   105,   106,   107,
      51,    47,    51,    39,    10,    22,   231,   232,   111,    39,
      12,    46,   176,    41,    68,   296,    39,    96,    39,    10,
     240,    37,    74,    52,    32,   118,    47,    38,   158,    39,
      49,    16,   246,    17,    51,   164,   236,   118,   253,   253,
     253,   260,   264,   165,    10,    22,    37,    81,    84,   229,
      39,    10,    22,    48,   269,    49,   350,   230,    46,   162,
     224,   224,   270,    10,    22,   262,    14,   163,   157,   327,
      46,    51,    51,    47,   142,    21,   225,   328,   225,   156,
      51,   159,   226,   277,   290,    47,    67,    39,    39,   166,
     153,   172,    70,    51,    74,   147,    39,    10,   203,    73,
     158,   111,    49,   204,   118,   176,   102,    79,   253,    39,
      78,   197,    48,   234,    49,   260,   171,   235,   250,   319,
     332,    90,   251,   320,   333,   315,    10,   301,    37,   302,
     260,   260,   104,   105,   106,   107,   108,   109,   110,   325,
     206,   207,   208,   312,   111,   142,   228,    95,   176,    97,
      98,    22,   233,   213,   214,   215,   216,   237,   157,   238,
     221,   239,   201,   202,    51,   210,   211,   218,   219,   257,
     258,   222,   245,   223,   224,   243,   248,   249,   263,   265,
      39,   200,   287,   253,    51,   329,   330,   331,   260,    51,
     334,   295,   289,   159,   297,   298,   299,   306,   277,   307,
      39,   308,   311,   313,   314,    39,   321,   322,   323,   336,
     338,   345,    15,    89,   264,    69,   267,   326,   344,    10,
      22,   337,   273,   282,   142,   281,    46,   285,   102,   283,
     292,   293,   241,   286,   227,   284,   182,   183,   184,   159,
     185,    47,   288,   335,   291,   103,   316,    88,   186,    92,
       0,     0,   305,     0,   104,   105,   106,   107,   108,   109,
     110,     0,   294,     0,     0,     0,   111,     0,    48,     0,
     112,   187,     0,    10,    22,     0,   113,   114,     0,     0,
      46,     0,   102,     0,     0,     0,     0,     0,     0,     0,
     182,   183,   184,     0,   185,    47,     0,     0,     0,   103,
       0,     0,   186,     0,     0,     0,     0,     0,   104,   105,
     106,   107,   108,   109,   110,     0,     0,     0,     0,     0,
     111,     0,    48,   341,   112,   266,     0,    10,    22,     0,
     113,   114,     0,     0,    46,     0,   102,     0,     0,     0,
       0,     0,     0,   341,     0,     0,     0,     0,   351,    47,
       0,     0,     0,   103,   274,   275,     0,     0,     0,     0,
       0,     0,   104,   105,   106,   107,   108,   109,   110,     0,
      10,    22,     0,     0,   111,   276,    48,    46,   112,   102,
       0,     0,     0,     0,   113,   114,     0,     0,     0,     0,
       0,     0,    47,     0,    10,    22,   103,   274,   275,     0,
       0,    46,     0,   102,     0,   104,   105,   106,   107,   108,
     109,   110,     0,     0,     0,     0,    47,   111,     0,    48,
     103,   112,     0,     0,     0,     0,     0,   113,   114,   104,
     105,   106,   107,   108,   109,   110,     0,    10,    22,     0,
       0,   111,   178,    48,    46,   112,   102,     0,     0,     0,
       0,   113,   114,     0,     0,     0,     0,     0,     0,    47,
       0,    10,    22,   103,     0,     0,     0,     0,    46,     0,
     102,     0,   104,   105,   106,   107,   108,   109,   110,     0,
       0,     0,     0,    47,   111,   300,    48,   103,   112,     0,
       0,     0,     0,     0,   113,   114,   104,   105,   106,   107,
     108,   109,   110,     0,     0,     0,     0,     0,   111,     0,
      48,     0,   112,     0,     0,     0,     0,     0,   113,   114
  };

  const short
  parser::yycheck_[] =
  {
       4,    94,   252,    23,    24,     3,    91,     3,   101,   133,
      19,    91,    16,    28,   102,     3,    20,     3,     3,    23,
      24,     3,    16,    27,    28,   259,    41,   112,    48,    49,
      30,   111,   112,    46,    28,     8,     0,    41,    47,    52,
     274,   275,    30,    31,    48,    49,     8,    51,    30,    31,
      23,     3,     4,    66,     8,    59,    54,    51,    10,    55,
      80,    23,    82,    51,    50,    59,     3,     4,    72,    69,
      90,    50,    92,    25,    94,    79,    80,   327,    82,    73,
     173,   101,    55,   171,    78,   209,    90,    66,    92,   177,
      94,   176,    48,    55,    75,     8,   176,   101,   332,    93,
      52,     3,    54,    55,    17,    50,    47,     8,   112,    47,
       8,   196,    47,   117,    55,   203,   196,    55,    53,     3,
       4,    66,    23,   117,    67,    23,    10,   147,    46,    46,
     111,    74,    75,   153,    52,    52,    38,    39,    40,    41,
     160,    25,   162,   147,     3,     4,   150,   151,    50,   153,
      54,    10,    54,   173,    55,   243,   160,    55,   162,     3,
     164,     5,    46,    24,    54,   146,    25,    11,    52,   173,
      54,    52,   176,    54,   194,    47,   157,   158,   182,   183,
     184,   185,    66,    55,     3,     4,     5,    48,    49,    47,
     194,     3,     4,    52,    47,    54,    55,    55,    10,    47,
      49,    49,    55,     3,     4,   186,    48,    55,    57,    47,
      10,   231,   232,    25,    75,    48,    47,    55,    47,    80,
     240,    82,    53,   204,    53,    25,    48,   231,   232,    90,
     234,    92,    48,   253,    46,   229,   240,     3,    45,    50,
      52,    50,    54,    50,   225,    54,    12,    50,   252,   253,
      54,   112,    52,    47,    54,   259,   336,    51,    47,    47,
      47,    66,    51,    51,    51,   269,     3,   248,     5,   250,
     274,   275,    38,    39,    40,    41,    42,    43,    44,   299,
      57,    58,    59,   264,    50,   146,   147,    48,    54,    43,
      44,     4,   153,    62,    63,    64,    65,   158,    57,   160,
      26,   162,    43,    44,   324,    60,    61,    67,    68,   183,
     184,    27,    51,    28,    49,    66,    47,    51,    48,    55,
     324,   325,     4,   327,   344,   306,   307,   308,   332,   349,
     311,    53,    46,   194,    51,    54,    14,    66,   319,    66,
     344,    66,    66,    48,    55,   349,     7,    46,    66,    50,
      54,    48,     8,    61,    66,    32,   196,   299,   338,     3,
       4,   321,   203,   217,   225,   212,    10,   222,    12,   220,
     231,   232,   164,   223,   146,   221,    20,    21,    22,   240,
      24,    25,   225,   319,   229,    29,   269,    59,    32,    63,
      -1,    -1,   253,    -1,    38,    39,    40,    41,    42,    43,
      44,    -1,   234,    -1,    -1,    -1,    50,    -1,    52,    -1,
      54,    55,    -1,     3,     4,    -1,    60,    61,    -1,    -1,
      10,    -1,    12,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      20,    21,    22,    -1,    24,    25,    -1,    -1,    -1,    29,
      -1,    -1,    32,    -1,    -1,    -1,    -1,    -1,    38,    39,
      40,    41,    42,    43,    44,    -1,    -1,    -1,    -1,    -1,
      50,    -1,    52,   324,    54,    55,    -1,     3,     4,    -1,
      60,    61,    -1,    -1,    10,    -1,    12,    -1,    -1,    -1,
      -1,    -1,    -1,   344,    -1,    -1,    -1,    -1,   349,    25,
      -1,    -1,    -1,    29,    30,    31,    -1,    -1,    -1,    -1,
      -1,    -1,    38,    39,    40,    41,    42,    43,    44,    -1,
       3,     4,    -1,    -1,    50,    51,    52,    10,    54,    12,
      -1,    -1,    -1,    -1,    60,    61,    -1,    -1,    -1,    -1,
      -1,    -1,    25,    -1,     3,     4,    29,    30,    31,    -1,
      -1,    10,    -1,    12,    -1,    38,    39,    40,    41,    42,
      43,    44,    -1,    -1,    -1,    -1,    25,    50,    -1,    52,
      29,    54,    -1,    -1,    -1,    -1,    -1,    60,    61,    38,
      39,    40,    41,    42,    43,    44,    -1,     3,     4,    -1,
      -1,    50,    51,    52,    10,    54,    12,    -1,    -1,    -1,
      -1,    60,    61,    -1,    -1,    -1,    -1,    -1,    -1,    25,
      -1,     3,     4,    29,    -1,    -1,    -1,    -1,    10,    -1,
      12,    -1,    38,    39,    40,    41,    42,    43,    44,    -1,
      -1,    -1,    -1,    25,    50,    51,    52,    29,    54,    -1,
      -1,    -1,    -1,    -1,    60,    61,    38,    39,    40,    41,
      42,    43,    44,    -1,    -1,    -1,    -1,    -1,    50,    -1,
      52,    -1,    54,    -1,    -1,    -1,    -1,    -1,    60,    61
  };

  const unsigned char
  parser::yystos_[] =
  {
       0,    78,    79,     0,     8,    17,    80,    81,    82,    86,
       3,    97,    54,    48,    48,    81,    52,    54,    83,   166,
      87,    48,     4,    96,    97,   162,   169,     8,    23,    55,
      84,    85,    54,    55,    88,    89,    97,     5,    11,    97,
      98,   101,   155,   156,   157,   158,    10,    25,    52,    54,
      96,   101,   140,   141,   142,   143,   144,   149,   150,    47,
      53,    97,    96,    97,    98,    55,    85,    48,    55,    84,
      48,    19,    47,    50,    46,    52,    97,    98,    54,    50,
     165,   140,    97,   139,   140,   145,   146,    96,   162,    83,
      66,    66,   165,    50,    66,    48,    55,    43,    44,   100,
      97,    96,    12,    29,    38,    39,    40,    41,    42,    43,
      44,    50,    54,    60,    61,    97,    99,   101,   104,   108,
     109,   110,   111,   112,   113,   114,   115,   116,   119,   120,
     121,   122,   123,   124,   125,   127,   129,   131,   133,   134,
     135,   136,   140,   151,   152,    46,    52,    96,   147,   148,
      30,    31,    51,    97,   160,   167,   140,    57,    52,   140,
      47,    55,    47,    55,    47,    55,   140,   104,   105,   118,
     140,   150,   140,    96,   155,   155,    54,   108,    51,   104,
     105,   106,    20,    21,    22,    24,    32,    55,    90,    91,
      92,    93,    94,    95,    97,   105,   117,   140,   159,   170,
      97,    43,    44,    45,    50,   123,    57,    58,    59,   126,
      60,    61,   128,    62,    63,    64,    65,   130,    67,    68,
     132,    26,    27,    28,    49,    47,    53,   152,   140,    47,
      55,    97,    97,   140,    47,    51,   104,   140,   140,   140,
      97,   146,   108,    66,   155,    51,    97,   108,    47,    51,
      47,    51,    54,    97,   161,   163,   164,   164,   164,    50,
      97,   102,   104,    48,    66,    55,    55,    90,   105,    47,
      55,     3,   108,   113,    30,    31,    51,   104,   153,   154,
     123,   127,   129,   131,   133,   134,   135,     4,   151,    46,
      53,   147,   140,   140,   160,    53,   108,    51,    54,    14,
      51,   104,   104,   161,   168,   140,    66,    66,    66,   102,
     103,    66,   104,    48,    55,    97,   159,   102,   102,    47,
      51,     7,    46,    66,   107,   101,   112,    47,    55,   104,
     104,   104,    47,    51,   104,   153,    50,   109,    54,    55,
     137,   140,   161,   102,   107,    48,    67,    74,    75,   138,
      55,   140
  };

  const unsigned char
  parser::yyr1_[] =
  {
       0,    77,    78,    79,    79,    80,    81,    82,    82,    83,
      83,    83,    83,    84,    84,    85,    85,    85,    85,    85,
      85,    86,    87,    87,    88,    89,    89,    90,    90,    90,
      90,    90,    91,    92,    93,    94,    95,    96,    97,    98,
      99,   100,   100,   101,   101,   101,   101,   102,   102,   103,
     103,   104,   105,   105,   106,   106,   107,   107,   108,   108,
     108,   108,   109,   110,   110,   110,   111,   112,   112,   112,
     112,   112,   112,   112,   113,   113,   113,   113,   114,   114,
     114,   114,   115,   115,   116,   116,   116,   116,   117,   117,
     118,   119,   119,   119,   119,   120,   120,   121,   121,   121,
     122,   122,   123,   123,   124,   124,   124,   125,   126,   126,
     126,   127,   127,   128,   128,   129,   129,   130,   130,   130,
     130,   131,   131,   132,   132,   133,   133,   134,   134,   135,
     135,   136,   136,   137,   138,   138,   138,   139,   139,   140,
     140,   140,   140,   140,   140,   140,   141,   142,   142,   143,
     144,   145,   145,   146,   147,   147,   148,   148,   149,   150,
     151,   151,   152,   152,   153,   153,   153,   154,   154,   155,
     156,   156,   156,   157,   158,   159,   160,   160,   160,   161,
     161,   162,   162,   163,   164,   164,   165,   165,   166,   167,
     167,   168,   168,   169,   169,   170,   170
  };

  const signed char
  parser::yyr2_[] =
  {
       0,     2,     2,     0,     3,     1,     3,     2,     3,     3,
       4,     2,     3,     2,     3,     4,     4,     4,     3,     6,
      10,     4,     0,     3,     3,     1,     3,     1,     1,     1,
       1,     1,     4,     4,     4,     4,     2,     1,     1,     1,
       1,     1,     1,     2,     5,     3,     6,     1,     3,     1,
       3,     1,     1,     1,     3,     3,     0,     3,     1,     1,
       1,     1,     3,     2,     4,     3,     3,     1,     1,     1,
       1,     1,     1,     2,     1,     1,     1,     1,     1,     1,
       2,     2,     3,     5,     2,     3,     3,     4,     2,     3,
       2,     1,     1,     1,     1,     3,     4,     3,     3,     5,
       3,     3,     1,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     3,     1,     1,     1,     3,     1,     1,     1,
       1,     1,     3,     1,     1,     1,     3,     1,     3,     1,
       3,     1,     3,     3,     1,     1,     1,     3,     3,     1,
       1,     1,     1,     1,     1,     1,     2,     3,     3,     5,
       3,     1,     3,     2,     1,     2,     1,     3,     4,     3,
       1,     1,     1,     3,     1,     2,     2,     1,     3,     1,
       1,     1,     1,     2,     8,     3,     2,     3,     3,     2,
       1,     2,     2,     3,     1,     1,     3,     2,     3,     1,
       3,     1,     3,     1,     3,     1,     3
  };


#if YYDEBUG
  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a YYNTOKENS, nonterminals.
  const char*
  const parser::yytname_[] =
  {
  "\"end of file\"", "error", "\"invalid token\"", "\"val_id\"",
  "\"TypeId\"", "\"CLS_ID\"", "\"__42__\"", "\"using\"", "\"mod\"",
  "\"struct\"", "\"enum\"", "\"typeclass\"", "\"if\"", "\"then\"",
  "\"else\"", "\"match\"", "\"with\"", "\"imports\"", "\"extern\"",
  "\"from\"", "\"const\"", "\"val\"", "\"var\"", "\"let\"", "\"set\"",
  "\"anonymous_fn\"", "\"and\"", "\"xor\"", "\"or\"", "\"not\"", "\"out\"",
  "\"inout\"", "\"discard\"", "\"as\"", "\"for\"", "\"CORE_PROFILE\"",
  "\"BROWSER_PROFILE\"", "\"NATIVE_PROFILE\"", "\"42\"", "\"0x2a\"",
  "\"42u\"", "\"0x2Au\"", "\"4.2\"", "\"\\\"dq-string-literal\\\"\"",
  "\"'sq-string-literal'\"", "\".\"", "\":\"", "\",\"", "\";\"", "\"::\"",
  "\"(\"", "\")\"", "\"[\"", "\"]\"", "\"{\"", "\"}\"", "\"->\"", "\"*\"",
  "\"/\"", "\"%\"", "\"+\"", "\"-\"", "\"<\"", "\"<=\"", "\">\"", "\">=\"",
  "\"=\"", "\"==\"", "\"!=\"", "\"^\"", "\"&\"", "\"!\"", "\"|\"",
  "\"EOS\"", "\":<\"", "\">:\"", "\"<null>\"", "$accept", "script",
  "script_header", "script_header_stmt", "script_field", "script_field_sl",
  "native_mod_exp", "mod_field_sl", "mod_field", "import_stmt",
  "import_field_group_sl0", "import_field_group", "import_field_cl1",
  "chain_prefix_stmt", "const_stmt", "val_stmt", "var_stmt", "set_stmt",
  "discard_stmt", "tid", "vid", "cid", "floatl", "stringl", "mod_prefix",
  "mut_expr", "mut_expr_cl1", "expr", "long_exp", "expr_cl2",
  "type_query_exp_sl0", "bracketed_exp", "paren_exp", "vtupleExpr",
  "vstructExpr", "primary_exp", "int_expr", "stringls", "if_exp",
  "chain_exp", "chain_prefix", "lambda_exp", "postfix_exp", "vcall_exp",
  "dot_name_exp", "dot_index_exp", "unary_exp", "unary_op", "binary_exp",
  "mul_binary_op", "mul_binary_exp", "add_binary_op", "add_binary_exp",
  "cmp_binary_op", "cmp_binary_exp", "eq_binary_op", "eq_binary_exp",
  "and_binary_exp", "xor_binary_exp", "or_binary_exp", "type_query_exp",
  "type_query_op", "type_spec_cl2", "type_spec", "mod_prefix_tid",
  "tuple_type_spec", "array_type_spec", "struct_type_spec",
  "struct_type_spec_field_cl", "struct_type_spec_field",
  "enum_type_spec_field", "enum_type_spec_field_cl", "enum_type_spec",
  "fn_type_spec", "targ", "targ_cl", "varg", "varg_cl", "class_spec",
  "primary_class_spec", "mod_prefix_cid_class_spec",
  "class_exp_class_spec", "struct_exp_field", "vpattern_field",
  "lpattern_field", "tpattern_field", "destructured_lpattern", "lpattern",
  "vpattern", "tpattern", "vpattern_field_cl", "lpattern_field_cl",
  "tpattern_field_cl1", "struct_exp_field_cl", YY_NULLPTR
  };
#endif


#if YYDEBUG
  const short
  parser::yyrline_[] =
  {
       0,   281,   281,   289,   290,   293,   297,   300,   301,   309,
     310,   311,   312,   315,   316,   319,   320,   321,   322,   323,
     328,   339,   344,   345,   348,   351,   352,   356,   357,   358,
     359,   360,   363,   366,   369,   372,   375,   382,   383,   384,
     387,   390,   391,   394,   395,   396,   397,   405,   406,   409,
     410,   413,   416,   417,   429,   430,   433,   434,   438,   439,
     440,   441,   452,   455,   456,   457,   460,   463,   464,   465,
     466,   467,   468,   469,   472,   473,   474,   475,   478,   479,
     480,   481,   484,   485,   488,   489,   490,   491,   494,   495,
     498,   502,   503,   504,   505,   508,   509,   512,   513,   514,
     517,   518,   522,   523,   526,   527,   528,   532,   535,   536,
     537,   540,   541,   544,   545,   548,   549,   552,   553,   554,
     555,   558,   559,   562,   563,   566,   567,   570,   571,   574,
     575,   578,   579,   583,   586,   587,   588,   603,   604,   608,
     609,   610,   611,   612,   613,   614,   618,   622,   623,   626,
     630,   633,   634,   637,   641,   642,   645,   646,   649,   652,
     655,   656,   659,   660,   662,   663,   664,   667,   668,   678,
     681,   682,   683,   686,   691,   701,   704,   705,   706,   709,
     710,   713,   714,   718,   721,   722,   725,   726,   729,   733,
     734,   737,   738,   741,   742,   745,   746
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
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76
    };
    // Last valid token kind.
    const int code_max = 331;

    if (t <= 0)
      return symbol_kind::S_YYEOF;
    else if (t <= code_max)
      return YY_CAST (symbol_kind_type, translate_table[t]);
    else
      return symbol_kind::S_YYUNDEF;
  }

#line 11 "parser.yy"
} } // pdm::parser
#line 4203 "parser.tab.cc"

#line 749 "parser.yy"


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

    ast::Script* parse_script(ast::Manager* manager, source::LocalScriptSource* source) {
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
        // std::cout << "YACC error: " << message << " at " << loc << std::endl;
    }

}

int yylex (
    pdm::parser::parser::semantic_type* semval,
    pdm::source::Loc* llocp,
    pdm::source::ISource* source,
    pdm::parser::Lexer* lexer
) {
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
