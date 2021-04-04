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
#line 278 "parser.yy"
                                      {
    yylhs.value.as < pdm::ast::Script* > () = mgr->new_script(source, yylhs.location, std::move(yystack_[1].value.as < std::vector<pdm::ast::HeaderStmt*> > ()), std::move(yystack_[0].value.as < std::vector<pdm::ast::Script::Field*> > ()));

    // setting the returnp here => this is the node parser returns.  
    *returnp = yylhs.value.as < pdm::ast::Script* > (); 
}
#line 2314 "parser.tab.cc"
    break;

  case 3: // script_header: %empty
#line 286 "parser.yy"
                                                    { yylhs.value.as < std::vector<pdm::ast::HeaderStmt*> > ().reserve(16); }
#line 2320 "parser.tab.cc"
    break;

  case 4: // script_header: script_header script_header_stmt ";"
#line 287 "parser.yy"
                                                    { yylhs.value.as < std::vector<pdm::ast::HeaderStmt*> > () = std::move(yystack_[2].value.as < std::vector<pdm::ast::HeaderStmt*> > ()); yylhs.value.as < std::vector<pdm::ast::HeaderStmt*> > ().push_back(yystack_[1].value.as < pdm::ast::HeaderStmt* > ()); }
#line 2326 "parser.tab.cc"
    break;

  case 5: // script_header_stmt: import_stmt
#line 290 "parser.yy"
      { yylhs.value.as < pdm::ast::HeaderStmt* > () = yystack_[0].value.as < pdm::ast::HeaderStmt* > (); }
#line 2332 "parser.tab.cc"
    break;

  case 6: // script_field: "mod" vid native_mod_exp
#line 294 "parser.yy"
                                 { yylhs.value.as < pdm::ast::Script::Field* > () = mgr->new_script_field(yylhs.location, yystack_[1].value.as < TokenInfo > ().ID_intstr, yystack_[0].value.as < pdm::ast::BaseModExp* > ()); }
#line 2338 "parser.tab.cc"
    break;

  case 7: // script_field_sl: script_field ";"
#line 297 "parser.yy"
                                                { yylhs.value.as < std::vector<pdm::ast::Script::Field*> > ().push_back(yystack_[1].value.as < pdm::ast::Script::Field* > ()); }
#line 2344 "parser.tab.cc"
    break;

  case 8: // script_field_sl: script_field_sl script_field ";"
#line 298 "parser.yy"
                                                { yylhs.value.as < std::vector<pdm::ast::Script::Field*> > () = std::move(yystack_[2].value.as < std::vector<pdm::ast::Script::Field*> > ()); yylhs.value.as < std::vector<pdm::ast::Script::Field*> > ().push_back(yystack_[1].value.as < pdm::ast::Script::Field* > ()); }
#line 2350 "parser.tab.cc"
    break;

  case 9: // native_mod_exp: "{" mod_field_sl "}"
#line 306 "parser.yy"
                                              { yylhs.value.as < pdm::ast::BaseModExp* > () = mgr->new_native_mod_exp(yylhs.location, nullptr, std::move(yystack_[1].value.as < std::vector<pdm::ast::BaseModExp::Field*> > ())); }
#line 2356 "parser.tab.cc"
    break;

  case 10: // native_mod_exp: tpattern "{" mod_field_sl "}"
#line 307 "parser.yy"
                                              { yylhs.value.as < pdm::ast::BaseModExp* > () = mgr->new_native_mod_exp(yylhs.location, yystack_[3].value.as < pdm::ast::TPattern* > (), std::move(yystack_[1].value.as < std::vector<pdm::ast::BaseModExp::Field*> > ())); }
#line 2362 "parser.tab.cc"
    break;

  case 11: // native_mod_exp: "{" "}"
#line 308 "parser.yy"
                                              { yylhs.value.as < pdm::ast::BaseModExp* > () = mgr->new_native_mod_exp(yylhs.location, nullptr, std::move(std::vector<ast::BaseModExp::Field*>{})); }
#line 2368 "parser.tab.cc"
    break;

  case 12: // native_mod_exp: tpattern "{" "}"
#line 309 "parser.yy"
                                              { yylhs.value.as < pdm::ast::BaseModExp* > () = mgr->new_native_mod_exp(yylhs.location, yystack_[2].value.as < pdm::ast::TPattern* > (), std::move(std::vector<ast::BaseModExp::Field*>{})); }
#line 2374 "parser.tab.cc"
    break;

  case 13: // mod_field_sl: mod_field ";"
#line 312 "parser.yy"
                                        { yylhs.value.as < std::vector<pdm::ast::BaseModExp::Field*> > ().push_back(yystack_[1].value.as < pdm::ast::BaseModExp::Field* > ()); }
#line 2380 "parser.tab.cc"
    break;

  case 14: // mod_field_sl: mod_field_sl mod_field ";"
#line 313 "parser.yy"
                                        { yylhs.value.as < std::vector<pdm::ast::BaseModExp::Field*> > () = std::move(yystack_[2].value.as < std::vector<pdm::ast::BaseModExp::Field*> > ()); yylhs.value.as < std::vector<pdm::ast::BaseModExp::Field*> > ().push_back(yystack_[1].value.as < pdm::ast::BaseModExp::Field* > ()); }
#line 2386 "parser.tab.cc"
    break;

  case 15: // mod_field: "let" vid "=" long_exp
#line 316 "parser.yy"
                                  { yylhs.value.as < pdm::ast::BaseModExp::Field* > () = mgr->new_value_field_for_mod_exp(yylhs.location, yystack_[2].value.as < TokenInfo > ().ID_intstr, yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2392 "parser.tab.cc"
    break;

  case 16: // mod_field: "let" tid "=" type_spec
#line 317 "parser.yy"
                                  { yylhs.value.as < pdm::ast::BaseModExp::Field* > () = mgr->new_type_field_for_mod_exp(yylhs.location, yystack_[2].value.as < TokenInfo > ().ID_intstr, yystack_[0].value.as < pdm::ast::TypeSpec* > ()); }
#line 2398 "parser.tab.cc"
    break;

  case 17: // mod_field: "let" cid "=" class_spec
#line 318 "parser.yy"
                                  { yylhs.value.as < pdm::ast::BaseModExp::Field* > () = mgr->new_class_field_for_mod_exp(yylhs.location, yystack_[2].value.as < TokenInfo > ().ID_intstr, yystack_[0].value.as < pdm::ast::ClassSpec* > ()); }
#line 2404 "parser.tab.cc"
    break;

  case 18: // mod_field: "mod" vid native_mod_exp
#line 319 "parser.yy"
                                  { yylhs.value.as < pdm::ast::BaseModExp::Field* > () = mgr->new_mod_field_for_mod_exp(yylhs.location, yystack_[1].value.as < TokenInfo > ().ID_intstr, yystack_[0].value.as < pdm::ast::BaseModExp* > ()); }
#line 2410 "parser.tab.cc"
    break;

  case 19: // mod_field: "let" vid vpattern type_spec "=" bracketed_exp
#line 320 "parser.yy"
                                                       {
        auto desugared_type_spec = mgr->new_fn_type_spec(yylhs.location, yystack_[3].value.as < pdm::ast::VPattern* > (), yystack_[2].value.as < pdm::ast::TypeSpec* > ());
        auto desugared_exp = mgr->new_lambda_exp(yylhs.location, desugared_type_spec, yystack_[0].value.as < pdm::ast::Exp* > ());
        yylhs.value.as < pdm::ast::BaseModExp::Field* > () = mgr->new_value_field_for_mod_exp(yylhs.location, yystack_[4].value.as < TokenInfo > ().ID_intstr, desugared_exp);
      }
#line 2420 "parser.tab.cc"
    break;

  case 20: // mod_field: "let" cid "(" tid class_spec ")" "=" "{" type_query_exp_sl0 "}"
#line 325 "parser.yy"
                                                                                    {
         auto class_spec = mgr->new_class_exp_class_spec(yylhs.location, yystack_[6].value.as < TokenInfo > ().ID_intstr, yystack_[5].value.as < pdm::ast::ClassSpec* > (), std::move(yystack_[1].value.as < std::vector<pdm::ast::TypeQueryExp*> > ()));
         yylhs.value.as < pdm::ast::BaseModExp::Field* > () = mgr->new_class_field_for_mod_exp(yylhs.location, yystack_[8].value.as < TokenInfo > ().ID_intstr, class_spec);
      }
#line 2429 "parser.tab.cc"
    break;

  case 21: // import_stmt: "imports" "{" import_field_group_sl0 "}"
#line 336 "parser.yy"
                                                      {
        yylhs.value.as < pdm::ast::HeaderStmt* > () = mgr->new_import_stmt(yylhs.location, std::move(yystack_[1].value.as < std::vector<ast::ImportStmt::FieldGroup*> > ()));
      }
#line 2437 "parser.tab.cc"
    break;

  case 22: // import_field_group_sl0: %empty
#line 341 "parser.yy"
             {}
#line 2443 "parser.tab.cc"
    break;

  case 23: // import_field_group_sl0: import_field_group_sl0 import_field_group ";"
#line 342 "parser.yy"
                                                           { yylhs.value.as < std::vector<ast::ImportStmt::FieldGroup*> > () = std::move(yystack_[2].value.as < std::vector<ast::ImportStmt::FieldGroup*> > ()); yylhs.value.as < std::vector<ast::ImportStmt::FieldGroup*> > ().push_back(yystack_[1].value.as < ast::ImportStmt::FieldGroup* > ()); }
#line 2449 "parser.tab.cc"
    break;

  case 24: // import_field_group: import_field_cl1 "from" stringl
#line 345 "parser.yy"
                                         { yylhs.value.as < ast::ImportStmt::FieldGroup* > () = mgr->new_import_field_group(yylhs.location, std::move(yystack_[2].value.as < std::vector<ast::ImportStmt::Field*> > ()), *yystack_[0].value.as < TokenInfo > ().String_utf8string); }
#line 2455 "parser.tab.cc"
    break;

  case 25: // import_field_cl1: vid
#line 348 "parser.yy"
                                    { yylhs.value.as < std::vector<ast::ImportStmt::Field*> > ().push_back(mgr->new_import_field(yystack_[0].location, yystack_[0].value.as < TokenInfo > ().ID_intstr)); }
#line 2461 "parser.tab.cc"
    break;

  case 26: // import_field_cl1: import_field_cl1 "," vid
#line 349 "parser.yy"
                                    { yylhs.value.as < std::vector<ast::ImportStmt::Field*> > () = std::move(yystack_[2].value.as < std::vector<ast::ImportStmt::Field*> > ()); yylhs.value.as < std::vector<ast::ImportStmt::Field*> > ().push_back(mgr->new_import_field(yystack_[0].location, yystack_[0].value.as < TokenInfo > ().ID_intstr)); }
#line 2467 "parser.tab.cc"
    break;

  case 27: // chain_prefix_stmt: const_stmt
#line 353 "parser.yy"
      { yylhs.value.as < pdm::ast::Stmt* > () = yystack_[0].value.as < pdm::ast::Stmt* > (); }
#line 2473 "parser.tab.cc"
    break;

  case 28: // chain_prefix_stmt: val_stmt
#line 354 "parser.yy"
      { yylhs.value.as < pdm::ast::Stmt* > () = yystack_[0].value.as < pdm::ast::Stmt* > (); }
#line 2479 "parser.tab.cc"
    break;

  case 29: // chain_prefix_stmt: var_stmt
#line 355 "parser.yy"
      { yylhs.value.as < pdm::ast::Stmt* > () = yystack_[0].value.as < pdm::ast::Stmt* > (); }
#line 2485 "parser.tab.cc"
    break;

  case 30: // chain_prefix_stmt: set_stmt
#line 356 "parser.yy"
      { yylhs.value.as < pdm::ast::Stmt* > () = yystack_[0].value.as < pdm::ast::Stmt* > (); }
#line 2491 "parser.tab.cc"
    break;

  case 31: // chain_prefix_stmt: discard_stmt
#line 357 "parser.yy"
      { yylhs.value.as < pdm::ast::Stmt* > () = yystack_[0].value.as < pdm::ast::Stmt* > (); }
#line 2497 "parser.tab.cc"
    break;

  case 32: // const_stmt: "const" lpattern "=" expr
#line 360 "parser.yy"
                                  { yylhs.value.as < pdm::ast::Stmt* > () = mgr->new_const_stmt(yylhs.location, yystack_[2].value.as < pdm::ast::LPattern* > (), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2503 "parser.tab.cc"
    break;

  case 33: // val_stmt: "val" lpattern "=" expr
#line 363 "parser.yy"
                                  { yylhs.value.as < pdm::ast::Stmt* > () = mgr->new_val_stmt(yylhs.location, yystack_[2].value.as < pdm::ast::LPattern* > (), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2509 "parser.tab.cc"
    break;

  case 34: // var_stmt: "var" lpattern "=" expr
#line 366 "parser.yy"
                                  { yylhs.value.as < pdm::ast::Stmt* > () = mgr->new_var_stmt(yylhs.location, yystack_[2].value.as < pdm::ast::LPattern* > (), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2515 "parser.tab.cc"
    break;

  case 35: // set_stmt: "set" expr "=" expr
#line 369 "parser.yy"
                              { yylhs.value.as < pdm::ast::Stmt* > () = mgr->new_set_stmt(yylhs.location, yystack_[2].value.as < pdm::ast::Exp* > (), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2521 "parser.tab.cc"
    break;

  case 36: // discard_stmt: "discard" expr
#line 372 "parser.yy"
                        { yylhs.value.as < pdm::ast::Stmt* > () = mgr->new_discard_stmt(yylhs.location, yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2527 "parser.tab.cc"
    break;

  case 37: // tid: "TypeId"
#line 379 "parser.yy"
     { yylhs.value.as < TokenInfo > () = yystack_[0].value.as < TokenInfo > (); }
#line 2533 "parser.tab.cc"
    break;

  case 38: // vid: "val_id"
#line 380 "parser.yy"
     { yylhs.value.as < TokenInfo > () = yystack_[0].value.as < TokenInfo > (); }
#line 2539 "parser.tab.cc"
    break;

  case 39: // cid: "CLS_ID"
#line 381 "parser.yy"
     { yylhs.value.as < TokenInfo > () = yystack_[0].value.as < TokenInfo > (); }
#line 2545 "parser.tab.cc"
    break;

  case 40: // floatl: "4.2"
#line 384 "parser.yy"
      { yylhs.value.as < TokenInfo > () = yystack_[0].value.as < TokenInfo > (); }
#line 2551 "parser.tab.cc"
    break;

  case 41: // stringl: "'sq-string-literal'"
#line 387 "parser.yy"
      { yylhs.value.as < TokenInfo > () = yystack_[0].value.as < TokenInfo > (); }
#line 2557 "parser.tab.cc"
    break;

  case 42: // stringl: "\"dq-string-literal\""
#line 388 "parser.yy"
      { yylhs.value.as < TokenInfo > () = yystack_[0].value.as < TokenInfo > (); }
#line 2563 "parser.tab.cc"
    break;

  case 43: // mod_prefix: vid "::"
#line 391 "parser.yy"
                                                      { yylhs.value.as < pdm::ast::ModAddress* > () = mgr->new_mod_address(yylhs.location, nullptr, yystack_[1].value.as < TokenInfo > ().ID_intstr, std::move(std::vector<ast::TArg*>{})); }
#line 2569 "parser.tab.cc"
    break;

  case 44: // mod_prefix: vid "[" targ_cl "]" "::"
#line 392 "parser.yy"
                                                      { yylhs.value.as < pdm::ast::ModAddress* > () = mgr->new_mod_address(yylhs.location, nullptr, yystack_[4].value.as < TokenInfo > ().ID_intstr, std::move(yystack_[2].value.as < std::vector<pdm::ast::TArg*> > ())); }
#line 2575 "parser.tab.cc"
    break;

  case 45: // mod_prefix: mod_prefix vid "::"
#line 393 "parser.yy"
                                                      { yylhs.value.as < pdm::ast::ModAddress* > () = mgr->new_mod_address(yylhs.location, yystack_[2].value.as < pdm::ast::ModAddress* > (), yystack_[1].value.as < TokenInfo > ().ID_intstr, std::move(std::vector<ast::TArg*>{})); }
#line 2581 "parser.tab.cc"
    break;

  case 46: // mod_prefix: mod_prefix vid "[" targ_cl "]" "::"
#line 394 "parser.yy"
                                                      { yylhs.value.as < pdm::ast::ModAddress* > () = mgr->new_mod_address(yylhs.location, yystack_[5].value.as < pdm::ast::ModAddress* > (), yystack_[4].value.as < TokenInfo > ().ID_intstr, std::move(yystack_[2].value.as < std::vector<pdm::ast::TArg*> > ())); }
#line 2587 "parser.tab.cc"
    break;

  case 47: // expr: binary_exp
#line 401 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2593 "parser.tab.cc"
    break;

  case 48: // long_exp: expr
#line 404 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2599 "parser.tab.cc"
    break;

  case 49: // long_exp: lambda_exp
#line 405 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2605 "parser.tab.cc"
    break;

  case 50: // expr_cl2: expr "," expr
#line 417 "parser.yy"
                             { yylhs.value.as < std::vector<pdm::ast::Exp*> > ().reserve(2); yylhs.value.as < std::vector<pdm::ast::Exp*> > ().push_back(yystack_[2].value.as < pdm::ast::Exp* > ()); yylhs.value.as < std::vector<pdm::ast::Exp*> > ().push_back(yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2611 "parser.tab.cc"
    break;

  case 51: // expr_cl2: expr_cl2 "," expr
#line 418 "parser.yy"
                             { yylhs.value.as < std::vector<pdm::ast::Exp*> > () = std::move(yystack_[2].value.as < std::vector<pdm::ast::Exp*> > ()); yylhs.value.as < std::vector<pdm::ast::Exp*> > ().push_back(yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2617 "parser.tab.cc"
    break;

  case 52: // type_query_exp_sl0: %empty
#line 421 "parser.yy"
                                                  {}
#line 2623 "parser.tab.cc"
    break;

  case 53: // type_query_exp_sl0: type_query_exp_sl0 type_query_exp ";"
#line 422 "parser.yy"
                                                  { yylhs.value.as < std::vector<pdm::ast::TypeQueryExp*> > () = std::move(yystack_[2].value.as < std::vector<pdm::ast::TypeQueryExp*> > ()); yylhs.value.as < std::vector<pdm::ast::TypeQueryExp*> > ().push_back(yystack_[1].value.as < pdm::ast::TypeQueryExp* > ()); }
#line 2629 "parser.tab.cc"
    break;

  case 54: // bracketed_exp: paren_exp
#line 426 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2635 "parser.tab.cc"
    break;

  case 55: // bracketed_exp: vtupleExpr
#line 427 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2641 "parser.tab.cc"
    break;

  case 56: // bracketed_exp: vstructExpr
#line 428 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2647 "parser.tab.cc"
    break;

  case 57: // bracketed_exp: chain_exp
#line 429 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2653 "parser.tab.cc"
    break;

  case 58: // paren_exp: "(" long_exp ")"
#line 440 "parser.yy"
                              { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_paren_exp(yylhs.location, yystack_[1].value.as < pdm::ast::Exp* > ()); }
#line 2659 "parser.tab.cc"
    break;

  case 59: // vtupleExpr: "(" ")"
#line 443 "parser.yy"
                                   { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_tuple_exp(yylhs.location, std::move(std::vector<ast::Exp*>())); }
#line 2665 "parser.tab.cc"
    break;

  case 60: // vtupleExpr: "(" expr "," ")"
#line 444 "parser.yy"
                                   { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_tuple_exp(yylhs.location, std::move(std::vector(1,yystack_[2].value.as < pdm::ast::Exp* > ()))); }
#line 2671 "parser.tab.cc"
    break;

  case 61: // vtupleExpr: "(" expr_cl2 ")"
#line 445 "parser.yy"
                                   { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_tuple_exp(yylhs.location, std::move(yystack_[1].value.as < std::vector<pdm::ast::Exp*> > ())); }
#line 2677 "parser.tab.cc"
    break;

  case 62: // vstructExpr: "{" struct_exp_field_cl "}"
#line 448 "parser.yy"
                                            { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_struct_exp(yylhs.location, std::move(yystack_[1].value.as < std::vector<pdm::ast::StructExp::Field*> > ())); }
#line 2683 "parser.tab.cc"
    break;

  case 63: // primary_exp: bracketed_exp
#line 451 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2689 "parser.tab.cc"
    break;

  case 64: // primary_exp: vid
#line 452 "parser.yy"
                     { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_id_exp(yylhs.location, yystack_[0].value.as < TokenInfo > ().ID_intstr); }
#line 2695 "parser.tab.cc"
    break;

  case 65: // primary_exp: int_expr
#line 453 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2701 "parser.tab.cc"
    break;

  case 66: // primary_exp: floatl
#line 454 "parser.yy"
                     { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_float_exp(yylhs.location, yystack_[0].value.as < TokenInfo > ().Float); }
#line 2707 "parser.tab.cc"
    break;

  case 67: // primary_exp: stringls
#line 455 "parser.yy"
                     { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_string_exp(yylhs.location, std::move(yystack_[0].value.as < std::vector<pdm::ast::StringExp::Piece> > ())); }
#line 2713 "parser.tab.cc"
    break;

  case 68: // primary_exp: if_exp
#line 456 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2719 "parser.tab.cc"
    break;

  case 69: // primary_exp: mod_prefix vid
#line 457 "parser.yy"
                        { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_module_dot_name_exp(yylhs.location, yystack_[1].value.as < pdm::ast::ModAddress* > (), yystack_[0].value.as < TokenInfo > ().ID_intstr); }
#line 2725 "parser.tab.cc"
    break;

  case 70: // int_expr: "42"
#line 460 "parser.yy"
                { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_int_exp(yylhs.location, yystack_[0].value.as < TokenInfo > ().Int, ast::IntExp::Base::Dec, false); }
#line 2731 "parser.tab.cc"
    break;

  case 71: // int_expr: "0x2a"
#line 461 "parser.yy"
                { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_int_exp(yylhs.location, yystack_[0].value.as < TokenInfo > ().Int, ast::IntExp::Base::Hex, false); }
#line 2737 "parser.tab.cc"
    break;

  case 72: // int_expr: "42u"
#line 462 "parser.yy"
                         { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_int_exp(yylhs.location, yystack_[0].value.as < TokenInfo > ().Int, ast::IntExp::Base::Dec, true); }
#line 2743 "parser.tab.cc"
    break;

  case 73: // int_expr: "0x2Au"
#line 463 "parser.yy"
                         { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_int_exp(yylhs.location, yystack_[0].value.as < TokenInfo > ().Int, ast::IntExp::Base::Hex, true); }
#line 2749 "parser.tab.cc"
    break;

  case 74: // stringls: "'sq-string-literal'"
#line 466 "parser.yy"
                             { yylhs.value.as < std::vector<pdm::ast::StringExp::Piece> > ().emplace_back(yylhs.location, *yystack_[0].value.as < TokenInfo > ().String_utf8string, ast::StringExp::QuoteKind::SingleQuote); }
#line 2755 "parser.tab.cc"
    break;

  case 75: // stringls: "\"dq-string-literal\""
#line 467 "parser.yy"
                             { yylhs.value.as < std::vector<pdm::ast::StringExp::Piece> > ().emplace_back(yylhs.location, *yystack_[0].value.as < TokenInfo > ().String_utf8string, ast::StringExp::QuoteKind::DoubleQuote); }
#line 2761 "parser.tab.cc"
    break;

  case 76: // stringls: stringls "'sq-string-literal'"
#line 468 "parser.yy"
                             { yylhs.value.as < std::vector<pdm::ast::StringExp::Piece> > () = std::move(yystack_[1].value.as < std::vector<pdm::ast::StringExp::Piece> > ()); yylhs.value.as < std::vector<pdm::ast::StringExp::Piece> > ().emplace_back(yystack_[0].location, *yystack_[0].value.as < TokenInfo > ().String_utf8string, ast::StringExp::QuoteKind::SingleQuote); }
#line 2767 "parser.tab.cc"
    break;

  case 77: // stringls: stringls "\"dq-string-literal\""
#line 469 "parser.yy"
                             { yylhs.value.as < std::vector<pdm::ast::StringExp::Piece> > () = std::move(yystack_[1].value.as < std::vector<pdm::ast::StringExp::Piece> > ()); yylhs.value.as < std::vector<pdm::ast::StringExp::Piece> > ().emplace_back(yystack_[0].location, *yystack_[0].value.as < TokenInfo > ().String_utf8string, ast::StringExp::QuoteKind::DoubleQuote); }
#line 2773 "parser.tab.cc"
    break;

  case 78: // if_exp: "if" bracketed_exp bracketed_exp
#line 472 "parser.yy"
                                                                { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_if_exp(yylhs.location, yystack_[1].value.as < pdm::ast::Exp* > (), yystack_[0].value.as < pdm::ast::Exp* > (), nullptr); }
#line 2779 "parser.tab.cc"
    break;

  case 79: // if_exp: "if" bracketed_exp bracketed_exp "else" primary_exp
#line 473 "parser.yy"
                                                                { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_if_exp(yylhs.location, yystack_[3].value.as < pdm::ast::Exp* > (), yystack_[2].value.as < pdm::ast::Exp* > (), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2785 "parser.tab.cc"
    break;

  case 80: // chain_exp: "{" "}"
#line 476 "parser.yy"
                                               { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_chain_exp(yylhs.location, std::move(std::vector<ast::Stmt*>{}), nullptr); }
#line 2791 "parser.tab.cc"
    break;

  case 81: // chain_exp: "{" long_exp "}"
#line 477 "parser.yy"
                                               { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_chain_exp(yylhs.location, std::move(std::vector<ast::Stmt*>{}), yystack_[1].value.as < pdm::ast::Exp* > ()); }
#line 2797 "parser.tab.cc"
    break;

  case 82: // chain_exp: "{" chain_prefix "}"
#line 478 "parser.yy"
                                               { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_chain_exp(yylhs.location, std::move(yystack_[1].value.as < std::vector<pdm::ast::Stmt*> > ()), nullptr); }
#line 2803 "parser.tab.cc"
    break;

  case 83: // chain_exp: "{" chain_prefix long_exp "}"
#line 479 "parser.yy"
                                               { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_chain_exp(yylhs.location, std::move(yystack_[2].value.as < std::vector<pdm::ast::Stmt*> > ()), yystack_[1].value.as < pdm::ast::Exp* > ()); }
#line 2809 "parser.tab.cc"
    break;

  case 84: // chain_prefix: chain_prefix_stmt ";"
#line 482 "parser.yy"
                                                { yylhs.value.as < std::vector<pdm::ast::Stmt*> > ().push_back(yystack_[1].value.as < pdm::ast::Stmt* > ()); }
#line 2815 "parser.tab.cc"
    break;

  case 85: // chain_prefix: chain_prefix chain_prefix_stmt ";"
#line 483 "parser.yy"
                                                { yylhs.value.as < std::vector<pdm::ast::Stmt*> > () = std::move(yystack_[2].value.as < std::vector<pdm::ast::Stmt*> > ()); yylhs.value.as < std::vector<pdm::ast::Stmt*> > ().push_back(yystack_[1].value.as < pdm::ast::Stmt* > ()); }
#line 2821 "parser.tab.cc"
    break;

  case 86: // lambda_exp: fn_type_spec bracketed_exp
#line 486 "parser.yy"
                                   { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_lambda_exp(yylhs.location, yystack_[1].value.as < pdm::ast::FnTypeSpec* > (), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2827 "parser.tab.cc"
    break;

  case 87: // postfix_exp: primary_exp
#line 490 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2833 "parser.tab.cc"
    break;

  case 88: // postfix_exp: vcall_exp
#line 491 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2839 "parser.tab.cc"
    break;

  case 89: // postfix_exp: dot_name_exp
#line 492 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2845 "parser.tab.cc"
    break;

  case 90: // postfix_exp: dot_index_exp
#line 493 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2851 "parser.tab.cc"
    break;

  case 91: // vcall_exp: postfix_exp "(" ")"
#line 496 "parser.yy"
                                            { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_vcall_exp(yylhs.location, yystack_[2].value.as < pdm::ast::Exp* > (), std::move(std::vector<ast::VArg*>{})); }
#line 2857 "parser.tab.cc"
    break;

  case 92: // vcall_exp: postfix_exp "(" varg_cl ")"
#line 497 "parser.yy"
                                            { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_vcall_exp(yylhs.location, yystack_[3].value.as < pdm::ast::Exp* > (), std::move(yystack_[1].value.as < std::vector<pdm::ast::VArg*> > ())); }
#line 2863 "parser.tab.cc"
    break;

  case 93: // dot_name_exp: postfix_exp "." "val_id"
#line 500 "parser.yy"
                                                { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_struct_dot_name_exp(yylhs.location, yystack_[2].value.as < pdm::ast::Exp* > (), yystack_[0].value.as < TokenInfo > ().ID_intstr); }
#line 2869 "parser.tab.cc"
    break;

  case 94: // dot_name_exp: type_spec "::" "TypeId"
#line 501 "parser.yy"
                                                    { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_enum_dot_name_exp(yylhs.location, yystack_[2].value.as < pdm::ast::TypeSpec* > (), yystack_[0].value.as < TokenInfo > ().ID_intstr, nullptr); }
#line 2875 "parser.tab.cc"
    break;

  case 95: // dot_name_exp: type_spec "::" "TypeId" "using" paren_exp
#line 502 "parser.yy"
                                                    { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_enum_dot_name_exp(yylhs.location, yystack_[4].value.as < pdm::ast::TypeSpec* > (), yystack_[2].value.as < TokenInfo > ().ID_intstr, yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2881 "parser.tab.cc"
    break;

  case 96: // dot_index_exp: postfix_exp "." int_expr
#line 505 "parser.yy"
                                    { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_dot_index_exp(yylhs.location, yystack_[2].value.as < pdm::ast::Exp* > (), yystack_[0].value.as < pdm::ast::Exp* > (), ast::DotIndexExp::RhsHint::LhsNotPtr); }
#line 2887 "parser.tab.cc"
    break;

  case 97: // dot_index_exp: postfix_exp "." bracketed_exp
#line 506 "parser.yy"
                                    { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_dot_index_exp(yylhs.location, yystack_[2].value.as < pdm::ast::Exp* > (), yystack_[0].value.as < pdm::ast::Exp* > (), ast::DotIndexExp::RhsHint::LhsNotPtr); }
#line 2893 "parser.tab.cc"
    break;

  case 98: // unary_exp: postfix_exp
#line 510 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2899 "parser.tab.cc"
    break;

  case 99: // unary_exp: unary_op unary_exp
#line 511 "parser.yy"
                             { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_unary_exp(yylhs.location, yystack_[1].value.as < pdm::ast::UnaryOperator > (), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2905 "parser.tab.cc"
    break;

  case 100: // unary_op: "+"
#line 514 "parser.yy"
                 { yylhs.value.as < pdm::ast::UnaryOperator > () = ast::UnaryOperator::Plus; }
#line 2911 "parser.tab.cc"
    break;

  case 101: // unary_op: "-"
#line 515 "parser.yy"
                 { yylhs.value.as < pdm::ast::UnaryOperator > () = ast::UnaryOperator::Minus; }
#line 2917 "parser.tab.cc"
    break;

  case 102: // unary_op: "not"
#line 516 "parser.yy"
                 { yylhs.value.as < pdm::ast::UnaryOperator > () = ast::UnaryOperator::Not; }
#line 2923 "parser.tab.cc"
    break;

  case 103: // binary_exp: or_binary_exp
#line 520 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2929 "parser.tab.cc"
    break;

  case 104: // mul_binary_op: "*"
#line 523 "parser.yy"
                 { yylhs.value.as < pdm::ast::BinaryOperator > () = ast::BinaryOperator::Mul; }
#line 2935 "parser.tab.cc"
    break;

  case 105: // mul_binary_op: "/"
#line 524 "parser.yy"
                 { yylhs.value.as < pdm::ast::BinaryOperator > () = ast::BinaryOperator::Div; }
#line 2941 "parser.tab.cc"
    break;

  case 106: // mul_binary_op: "%"
#line 525 "parser.yy"
                 { yylhs.value.as < pdm::ast::BinaryOperator > () = ast::BinaryOperator::Rem; }
#line 2947 "parser.tab.cc"
    break;

  case 107: // mul_binary_exp: unary_exp
#line 528 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2953 "parser.tab.cc"
    break;

  case 108: // mul_binary_exp: mul_binary_exp mul_binary_op unary_exp
#line 529 "parser.yy"
                                               { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_binary_exp(yylhs.location, yystack_[1].value.as < pdm::ast::BinaryOperator > (), yystack_[2].value.as < pdm::ast::Exp* > (), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2959 "parser.tab.cc"
    break;

  case 109: // add_binary_op: "+"
#line 532 "parser.yy"
             { yylhs.value.as < pdm::ast::BinaryOperator > () = ast::BinaryOperator::Add; }
#line 2965 "parser.tab.cc"
    break;

  case 110: // add_binary_op: "-"
#line 533 "parser.yy"
             { yylhs.value.as < pdm::ast::BinaryOperator > () = ast::BinaryOperator::Subtract; }
#line 2971 "parser.tab.cc"
    break;

  case 111: // add_binary_exp: mul_binary_exp
#line 536 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2977 "parser.tab.cc"
    break;

  case 112: // add_binary_exp: add_binary_exp add_binary_op mul_binary_exp
#line 537 "parser.yy"
                                                    { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_binary_exp(yylhs.location, yystack_[1].value.as < pdm::ast::BinaryOperator > (), yystack_[2].value.as < pdm::ast::Exp* > (), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2983 "parser.tab.cc"
    break;

  case 113: // cmp_binary_op: "<"
#line 540 "parser.yy"
                { yylhs.value.as < pdm::ast::BinaryOperator > () = ast::BinaryOperator::Less; }
#line 2989 "parser.tab.cc"
    break;

  case 114: // cmp_binary_op: "<="
#line 541 "parser.yy"
                { yylhs.value.as < pdm::ast::BinaryOperator > () = ast::BinaryOperator::LessOrEq; }
#line 2995 "parser.tab.cc"
    break;

  case 115: // cmp_binary_op: ">"
#line 542 "parser.yy"
                { yylhs.value.as < pdm::ast::BinaryOperator > () = ast::BinaryOperator::Greater; }
#line 3001 "parser.tab.cc"
    break;

  case 116: // cmp_binary_op: ">="
#line 543 "parser.yy"
                { yylhs.value.as < pdm::ast::BinaryOperator > () = ast::BinaryOperator::GreaterOrEq; }
#line 3007 "parser.tab.cc"
    break;

  case 117: // cmp_binary_exp: add_binary_exp
#line 546 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 3013 "parser.tab.cc"
    break;

  case 118: // cmp_binary_exp: cmp_binary_exp cmp_binary_op add_binary_exp
#line 547 "parser.yy"
                                                    { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_binary_exp(yylhs.location, yystack_[1].value.as < pdm::ast::BinaryOperator > (), yystack_[2].value.as < pdm::ast::Exp* > (), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 3019 "parser.tab.cc"
    break;

  case 119: // eq_binary_op: "=="
#line 550 "parser.yy"
                 { yylhs.value.as < pdm::ast::BinaryOperator > () = ast::BinaryOperator::Equals; }
#line 3025 "parser.tab.cc"
    break;

  case 120: // eq_binary_op: "!="
#line 551 "parser.yy"
                 { yylhs.value.as < pdm::ast::BinaryOperator > () = ast::BinaryOperator::NotEquals; }
#line 3031 "parser.tab.cc"
    break;

  case 121: // eq_binary_exp: cmp_binary_exp
#line 554 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 3037 "parser.tab.cc"
    break;

  case 122: // eq_binary_exp: eq_binary_exp eq_binary_op cmp_binary_exp
#line 555 "parser.yy"
                                                { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_binary_exp(yylhs.location, yystack_[1].value.as < pdm::ast::BinaryOperator > (), yystack_[2].value.as < pdm::ast::Exp* > (), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 3043 "parser.tab.cc"
    break;

  case 123: // and_binary_exp: eq_binary_exp
#line 558 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 3049 "parser.tab.cc"
    break;

  case 124: // and_binary_exp: and_binary_exp "and" eq_binary_exp
#line 559 "parser.yy"
                                           { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_binary_exp(yylhs.location, ast::BinaryOperator::And, yystack_[2].value.as < pdm::ast::Exp* > (), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 3055 "parser.tab.cc"
    break;

  case 125: // xor_binary_exp: and_binary_exp
#line 562 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 3061 "parser.tab.cc"
    break;

  case 126: // xor_binary_exp: xor_binary_exp "xor" and_binary_exp
#line 563 "parser.yy"
                                           { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_binary_exp(yylhs.location, ast::BinaryOperator::XOr, yystack_[2].value.as < pdm::ast::Exp* > (), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 3067 "parser.tab.cc"
    break;

  case 127: // or_binary_exp: xor_binary_exp
#line 566 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 3073 "parser.tab.cc"
    break;

  case 128: // or_binary_exp: or_binary_exp "or" xor_binary_exp
#line 567 "parser.yy"
                                           { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_binary_exp(yylhs.location, ast::BinaryOperator::Or, yystack_[2].value.as < pdm::ast::Exp* > (), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 3079 "parser.tab.cc"
    break;

  case 129: // type_query_exp: type_spec type_query_op type_spec
#line 571 "parser.yy"
                                          { yylhs.value.as < pdm::ast::TypeQueryExp* > () = mgr->new_type_query_exp(yylhs.location, yystack_[1].value.as < pdm::ast::TypeQueryKind > (), yystack_[2].value.as < pdm::ast::TypeSpec* > (), yystack_[0].value.as < pdm::ast::TypeSpec* > ()); }
#line 3085 "parser.tab.cc"
    break;

  case 130: // type_query_op: ":<"
#line 574 "parser.yy"
                    { yylhs.value.as < pdm::ast::TypeQueryKind > () = ast::TypeQueryKind::LhsSubtypesRhs; }
#line 3091 "parser.tab.cc"
    break;

  case 131: // type_query_op: ">:"
#line 575 "parser.yy"
                    { yylhs.value.as < pdm::ast::TypeQueryKind > () = ast::TypeQueryKind::LhsSupertypesRhs; }
#line 3097 "parser.tab.cc"
    break;

  case 132: // type_query_op: "=="
#line 576 "parser.yy"
                    { yylhs.value.as < pdm::ast::TypeQueryKind > () = ast::TypeQueryKind::LhsEqualsRhs; }
#line 3103 "parser.tab.cc"
    break;

  case 133: // type_spec_cl2: type_spec "," type_spec
#line 591 "parser.yy"
                                    { yylhs.value.as < std::vector<pdm::ast::TypeSpec*> > ().reserve(2); yylhs.value.as < std::vector<pdm::ast::TypeSpec*> > ().push_back(yystack_[2].value.as < pdm::ast::TypeSpec* > ()); yylhs.value.as < std::vector<pdm::ast::TypeSpec*> > ().push_back(yystack_[0].value.as < pdm::ast::TypeSpec* > ()); }
#line 3109 "parser.tab.cc"
    break;

  case 134: // type_spec_cl2: type_spec_cl2 "," type_spec
#line 592 "parser.yy"
                                    { yylhs.value.as < std::vector<pdm::ast::TypeSpec*> > () = std::move(yystack_[2].value.as < std::vector<pdm::ast::TypeSpec*> > ()); yylhs.value.as < std::vector<pdm::ast::TypeSpec*> > ().push_back(yystack_[0].value.as < pdm::ast::TypeSpec* > ()); }
#line 3115 "parser.tab.cc"
    break;

  case 135: // type_spec: tid
#line 596 "parser.yy"
                        { yylhs.value.as < pdm::ast::TypeSpec* > () = mgr->new_id_type_spec(yylhs.location, yystack_[0].value.as < TokenInfo > ().ID_intstr); }
#line 3121 "parser.tab.cc"
    break;

  case 136: // type_spec: mod_prefix_tid
#line 597 "parser.yy"
      { yylhs.value.as < pdm::ast::TypeSpec* > () = yystack_[0].value.as < pdm::ast::TypeSpec* > (); }
#line 3127 "parser.tab.cc"
    break;

  case 137: // type_spec: tuple_type_spec
#line 598 "parser.yy"
      { yylhs.value.as < pdm::ast::TypeSpec* > () = yystack_[0].value.as < pdm::ast::TypeSpec* > (); }
#line 3133 "parser.tab.cc"
    break;

  case 138: // type_spec: array_type_spec
#line 599 "parser.yy"
      { yylhs.value.as < pdm::ast::TypeSpec* > () = yystack_[0].value.as < pdm::ast::TypeSpec* > (); }
#line 3139 "parser.tab.cc"
    break;

  case 139: // type_spec: struct_type_spec
#line 600 "parser.yy"
      { yylhs.value.as < pdm::ast::TypeSpec* > () = yystack_[0].value.as < pdm::ast::TypeSpec* > (); }
#line 3145 "parser.tab.cc"
    break;

  case 140: // type_spec: enum_type_spec
#line 601 "parser.yy"
      { yylhs.value.as < pdm::ast::TypeSpec* > () = yystack_[0].value.as < pdm::ast::TypeSpec* > (); }
#line 3151 "parser.tab.cc"
    break;

  case 141: // type_spec: fn_type_spec
#line 602 "parser.yy"
                    { yylhs.value.as < pdm::ast::TypeSpec* > () = dynamic_cast<ast::TypeSpec*>(yystack_[0].value.as < pdm::ast::FnTypeSpec* > ()); }
#line 3157 "parser.tab.cc"
    break;

  case 142: // mod_prefix_tid: mod_prefix tid
#line 606 "parser.yy"
                            { yylhs.value.as < pdm::ast::TypeSpec* > () = mgr->new_ma_type_spec(yylhs.location, yystack_[1].value.as < pdm::ast::ModAddress* > (), yystack_[0].value.as < TokenInfo > ().ID_intstr); }
#line 3163 "parser.tab.cc"
    break;

  case 143: // tuple_type_spec: "{" type_spec "}"
#line 610 "parser.yy"
                                   { yylhs.value.as < pdm::ast::TypeSpec* > () = mgr->new_tuple_type_spec(yylhs.location, std::move(std::vector(1,yystack_[1].value.as < pdm::ast::TypeSpec* > ()))); }
#line 3169 "parser.tab.cc"
    break;

  case 144: // tuple_type_spec: "{" type_spec_cl2 "}"
#line 611 "parser.yy"
                                   { yylhs.value.as < pdm::ast::TypeSpec* > () = mgr->new_tuple_type_spec(yylhs.location, std::move(yystack_[1].value.as < std::vector<pdm::ast::TypeSpec*> > ())); }
#line 3175 "parser.tab.cc"
    break;

  case 145: // array_type_spec: "[" type_spec "*" expr "]"
#line 614 "parser.yy"
                                                { yylhs.value.as < pdm::ast::TypeSpec* > () = nullptr; }
#line 3181 "parser.tab.cc"
    break;

  case 146: // struct_type_spec: "{" struct_type_spec_field_cl "}"
#line 618 "parser.yy"
                                               { yylhs.value.as < pdm::ast::TypeSpec* > () = mgr->new_struct_type_spec(yylhs.location, std::move(yystack_[1].value.as < std::vector<pdm::ast::StructTypeSpec::Field*> > ())); }
#line 3187 "parser.tab.cc"
    break;

  case 147: // struct_type_spec_field_cl: struct_type_spec_field
#line 621 "parser.yy"
                                                              { yylhs.value.as < std::vector<pdm::ast::StructTypeSpec::Field*> > ().push_back(yystack_[0].value.as < pdm::ast::StructTypeSpec::Field* > ()); }
#line 3193 "parser.tab.cc"
    break;

  case 148: // struct_type_spec_field_cl: struct_type_spec_field_cl "," struct_type_spec_field
#line 622 "parser.yy"
                                                              { yylhs.value.as < std::vector<pdm::ast::StructTypeSpec::Field*> > () = std::move(yystack_[2].value.as < std::vector<pdm::ast::StructTypeSpec::Field*> > ()); yylhs.value.as < std::vector<pdm::ast::StructTypeSpec::Field*> > ().push_back(yystack_[0].value.as < pdm::ast::StructTypeSpec::Field* > ()); }
#line 3199 "parser.tab.cc"
    break;

  case 149: // struct_type_spec_field: vid type_spec
#line 625 "parser.yy"
                                    { yylhs.value.as < pdm::ast::StructTypeSpec::Field* > () = mgr->new_struct_type_spec_field(yylhs.location, yystack_[1].value.as < TokenInfo > ().ID_intstr, yystack_[0].value.as < pdm::ast::TypeSpec* > ()); }
#line 3205 "parser.tab.cc"
    break;

  case 150: // enum_type_spec_field: tid
#line 629 "parser.yy"
                        { yylhs.value.as < pdm::ast::EnumTypeSpec::Field* > () = mgr->new_enum_type_spec_field(yylhs.location, yystack_[0].value.as < TokenInfo > ().ID_intstr, nullptr); }
#line 3211 "parser.tab.cc"
    break;

  case 151: // enum_type_spec_field: tid type_spec
#line 630 "parser.yy"
                        { yylhs.value.as < pdm::ast::EnumTypeSpec::Field* > () = mgr->new_enum_type_spec_field(yylhs.location, yystack_[1].value.as < TokenInfo > ().ID_intstr, yystack_[0].value.as < pdm::ast::TypeSpec* > ()); }
#line 3217 "parser.tab.cc"
    break;

  case 152: // enum_type_spec_field_cl: enum_type_spec_field
#line 633 "parser.yy"
                                                            { yylhs.value.as < std::vector<pdm::ast::EnumTypeSpec::Field*> > ().push_back(yystack_[0].value.as < pdm::ast::EnumTypeSpec::Field* > ()); }
#line 3223 "parser.tab.cc"
    break;

  case 153: // enum_type_spec_field_cl: enum_type_spec_field_cl "," enum_type_spec_field
#line 634 "parser.yy"
                                                            { yylhs.value.as < std::vector<pdm::ast::EnumTypeSpec::Field*> > () = std::move(yystack_[2].value.as < std::vector<pdm::ast::EnumTypeSpec::Field*> > ()); yylhs.value.as < std::vector<pdm::ast::EnumTypeSpec::Field*> > ().push_back(yystack_[0].value.as < pdm::ast::EnumTypeSpec::Field* > ()); }
#line 3229 "parser.tab.cc"
    break;

  case 154: // enum_type_spec: "enum" "{" enum_type_spec_field_cl "}"
#line 637 "parser.yy"
                                                        { yylhs.value.as < pdm::ast::TypeSpec* > () = mgr->new_enum_type_spec(yylhs.location, std::move(yystack_[1].value.as < std::vector<pdm::ast::EnumTypeSpec::Field*> > ())); }
#line 3235 "parser.tab.cc"
    break;

  case 155: // fn_type_spec: "anonymous_fn" vpattern type_spec
#line 640 "parser.yy"
                               { yylhs.value.as < pdm::ast::FnTypeSpec* > () = mgr->new_fn_type_spec(yylhs.location, yystack_[1].value.as < pdm::ast::VPattern* > (), yystack_[0].value.as < pdm::ast::TypeSpec* > ()); }
#line 3241 "parser.tab.cc"
    break;

  case 156: // targ: type_spec
#line 643 "parser.yy"
                { yylhs.value.as < pdm::ast::TArg* > () = mgr->new_targ_type_spec(yylhs.location, yystack_[0].value.as < pdm::ast::TypeSpec* > ()); }
#line 3247 "parser.tab.cc"
    break;

  case 157: // targ: expr
#line 644 "parser.yy"
               { yylhs.value.as < pdm::ast::TArg* > () = mgr->new_targ_exp(yylhs.location, yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 3253 "parser.tab.cc"
    break;

  case 158: // targ_cl: targ
#line 647 "parser.yy"
                            { yylhs.value.as < std::vector<pdm::ast::TArg*> > ().push_back(yystack_[0].value.as < pdm::ast::TArg* > ()); }
#line 3259 "parser.tab.cc"
    break;

  case 159: // targ_cl: targ_cl "," targ
#line 648 "parser.yy"
                            { yylhs.value.as < std::vector<pdm::ast::TArg*> > () = std::move(yystack_[2].value.as < std::vector<pdm::ast::TArg*> > ()); yylhs.value.as < std::vector<pdm::ast::TArg*> > ().push_back(yystack_[0].value.as < pdm::ast::TArg* > ()); }
#line 3265 "parser.tab.cc"
    break;

  case 160: // varg: expr
#line 650 "parser.yy"
                            { yylhs.value.as < pdm::ast::VArg* > () = mgr->new_varg(yylhs.location, yystack_[0].value.as < pdm::ast::Exp* > (), ast::VArgAccessSpec::In); }
#line 3271 "parser.tab.cc"
    break;

  case 161: // varg: "out" expr
#line 651 "parser.yy"
                            { yylhs.value.as < pdm::ast::VArg* > () = mgr->new_varg(yylhs.location, yystack_[0].value.as < pdm::ast::Exp* > (), ast::VArgAccessSpec::Out); }
#line 3277 "parser.tab.cc"
    break;

  case 162: // varg: "inout" expr
#line 652 "parser.yy"
                            { yylhs.value.as < pdm::ast::VArg* > () = mgr->new_varg(yylhs.location, yystack_[0].value.as < pdm::ast::Exp* > (), ast::VArgAccessSpec::InOut); }
#line 3283 "parser.tab.cc"
    break;

  case 163: // varg_cl: varg
#line 655 "parser.yy"
                            { yylhs.value.as < std::vector<pdm::ast::VArg*> > ().push_back(yystack_[0].value.as < pdm::ast::VArg* > ()); }
#line 3289 "parser.tab.cc"
    break;

  case 164: // varg_cl: varg_cl "," varg
#line 656 "parser.yy"
                            { yylhs.value.as < std::vector<pdm::ast::VArg*> > () = std::move(yystack_[2].value.as < std::vector<pdm::ast::VArg*> > ()); yylhs.value.as < std::vector<pdm::ast::VArg*> > ().push_back(yystack_[0].value.as < pdm::ast::VArg* > ()); }
#line 3295 "parser.tab.cc"
    break;

  case 165: // class_spec: primary_class_spec
#line 666 "parser.yy"
      { yylhs.value.as < pdm::ast::ClassSpec* > () = yystack_[0].value.as < pdm::ast::ClassSpec* > (); }
#line 3301 "parser.tab.cc"
    break;

  case 166: // primary_class_spec: cid
#line 669 "parser.yy"
                        { yylhs.value.as < pdm::ast::ClassSpec* > () = mgr->new_id_class_spec(yylhs.location, yystack_[0].value.as < TokenInfo > ().ID_intstr); }
#line 3307 "parser.tab.cc"
    break;

  case 167: // primary_class_spec: mod_prefix_cid_class_spec
#line 670 "parser.yy"
      { yylhs.value.as < pdm::ast::ClassSpec* > () = yystack_[0].value.as < pdm::ast::ClassSpec* > (); }
#line 3313 "parser.tab.cc"
    break;

  case 168: // primary_class_spec: class_exp_class_spec
#line 671 "parser.yy"
      { yylhs.value.as < pdm::ast::ClassSpec* > () = yystack_[0].value.as < pdm::ast::ClassSpec* > (); }
#line 3319 "parser.tab.cc"
    break;

  case 169: // mod_prefix_cid_class_spec: mod_prefix cid
#line 674 "parser.yy"
                        { yylhs.value.as < pdm::ast::ClassSpec* > () = mgr->new_ma_class_spec(yylhs.location, std::move(yystack_[1].value.as < pdm::ast::ModAddress* > ()), yystack_[0].value.as < TokenInfo > ().ID_intstr); }
#line 3325 "parser.tab.cc"
    break;

  case 170: // class_exp_class_spec: "typeclass" "(" tid class_spec ")" "{" type_query_exp_sl0 "}"
#line 679 "parser.yy"
                                                                                 {
            yylhs.value.as < pdm::ast::ClassSpec* > () = mgr->new_class_exp_class_spec(yylhs.location, yystack_[5].value.as < TokenInfo > ().ID_intstr, yystack_[4].value.as < pdm::ast::ClassSpec* > (), std::move(yystack_[1].value.as < std::vector<pdm::ast::TypeQueryExp*> > ()));
        }
#line 3333 "parser.tab.cc"
    break;

  case 171: // struct_exp_field: vid "=" expr
#line 689 "parser.yy"
                    { yylhs.value.as < pdm::ast::StructExp::Field* > () = mgr->new_struct_exp_field(yylhs.location, yystack_[2].value.as < TokenInfo > ().ID_intstr, yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 3339 "parser.tab.cc"
    break;

  case 172: // vpattern_field: vid type_spec
#line 692 "parser.yy"
                             { yylhs.value.as < pdm::ast::VPattern::Field* > () = mgr->new_vpattern_field(yylhs.location, yystack_[1].value.as < TokenInfo > ().ID_intstr, yystack_[0].value.as < pdm::ast::TypeSpec* > (), ast::VArgAccessSpec::In); }
#line 3345 "parser.tab.cc"
    break;

  case 173: // vpattern_field: "out" vid type_spec
#line 693 "parser.yy"
                             { yylhs.value.as < pdm::ast::VPattern::Field* > () = mgr->new_vpattern_field(yylhs.location, yystack_[1].value.as < TokenInfo > ().ID_intstr, yystack_[0].value.as < pdm::ast::TypeSpec* > (), ast::VArgAccessSpec::Out); }
#line 3351 "parser.tab.cc"
    break;

  case 174: // vpattern_field: "inout" vid type_spec
#line 694 "parser.yy"
                             { yylhs.value.as < pdm::ast::VPattern::Field* > () = mgr->new_vpattern_field(yylhs.location, yystack_[1].value.as < TokenInfo > ().ID_intstr, yystack_[0].value.as < pdm::ast::TypeSpec* > (), ast::VArgAccessSpec::InOut); }
#line 3357 "parser.tab.cc"
    break;

  case 175: // lpattern_field: vid type_spec
#line 697 "parser.yy"
                     { yylhs.value.as < pdm::ast::LPattern::Field* > () = mgr->new_lpattern_field(yylhs.location, ast::LPattern::FieldKind::IdTypeSpecPair, yystack_[1].value.as < TokenInfo > ().ID_intstr, yystack_[0].value.as < pdm::ast::TypeSpec* > ()); }
#line 3363 "parser.tab.cc"
    break;

  case 176: // lpattern_field: vid
#line 698 "parser.yy"
                    { yylhs.value.as < pdm::ast::LPattern::Field* > () = mgr->new_lpattern_field(yylhs.location, ast::LPattern::FieldKind::IdSingleton, yystack_[0].value.as < TokenInfo > ().ID_intstr); }
#line 3369 "parser.tab.cc"
    break;

  case 177: // tpattern_field: vid type_spec
#line 701 "parser.yy"
                      { yylhs.value.as < pdm::ast::TPattern::Field* > () = mgr->new_value_tpattern_field(yylhs.location, yystack_[1].value.as < TokenInfo > ().ID_intstr, yystack_[0].value.as < pdm::ast::TypeSpec* > ()); }
#line 3375 "parser.tab.cc"
    break;

  case 178: // tpattern_field: tid class_spec
#line 702 "parser.yy"
                      { yylhs.value.as < pdm::ast::TPattern::Field* > () = mgr->new_type_tpattern_field(yylhs.location, yystack_[1].value.as < TokenInfo > ().ID_intstr, yystack_[0].value.as < pdm::ast::ClassSpec* > ()); }
#line 3381 "parser.tab.cc"
    break;

  case 179: // destructured_lpattern: "{" lpattern_field_cl "}"
#line 706 "parser.yy"
                                       { yylhs.value.as < pdm::ast::LPattern* > () = mgr->new_lpattern(yylhs.location, std::move(yystack_[1].value.as < std::vector<pdm::ast::LPattern::Field*> > ()), true); }
#line 3387 "parser.tab.cc"
    break;

  case 180: // lpattern: lpattern_field
#line 709 "parser.yy"
                        { yylhs.value.as < pdm::ast::LPattern* > () = mgr->new_lpattern(yylhs.location, std::move(std::vector<ast::LPattern::Field*>{1,yystack_[0].value.as < pdm::ast::LPattern::Field* > ()}), false); }
#line 3393 "parser.tab.cc"
    break;

  case 181: // lpattern: destructured_lpattern
#line 710 "parser.yy"
      { yylhs.value.as < pdm::ast::LPattern* > () = yystack_[0].value.as < pdm::ast::LPattern* > (); }
#line 3399 "parser.tab.cc"
    break;

  case 182: // vpattern: "(" vpattern_field_cl ")"
#line 713 "parser.yy"
                                       { yylhs.value.as < pdm::ast::VPattern* > () = mgr->new_vpattern(yylhs.location, std::move(yystack_[1].value.as < std::vector<pdm::ast::VPattern::Field*> > ())); }
#line 3405 "parser.tab.cc"
    break;

  case 183: // vpattern: "(" ")"
#line 714 "parser.yy"
                                       { yylhs.value.as < pdm::ast::VPattern* > () = mgr->new_vpattern(yylhs.location, std::move(std::vector<ast::VPattern::Field*>{})); }
#line 3411 "parser.tab.cc"
    break;

  case 184: // tpattern: "[" tpattern_field_cl1 "]"
#line 717 "parser.yy"
                                        { yylhs.value.as < pdm::ast::TPattern* > () = mgr->new_tpattern(yylhs.location, std::move(yystack_[1].value.as < std::vector<pdm::ast::TPattern::Field*> > ()), false); }
#line 3417 "parser.tab.cc"
    break;

  case 185: // vpattern_field_cl: vpattern_field
#line 721 "parser.yy"
                                              { yylhs.value.as < std::vector<pdm::ast::VPattern::Field*> > ().push_back(yystack_[0].value.as < pdm::ast::VPattern::Field* > ()); }
#line 3423 "parser.tab.cc"
    break;

  case 186: // vpattern_field_cl: vpattern_field_cl "," vpattern_field
#line 722 "parser.yy"
                                               { yylhs.value.as < std::vector<pdm::ast::VPattern::Field*> > () = std::move(yystack_[2].value.as < std::vector<pdm::ast::VPattern::Field*> > ()); yylhs.value.as < std::vector<pdm::ast::VPattern::Field*> > ().push_back(yystack_[0].value.as < pdm::ast::VPattern::Field* > ()); }
#line 3429 "parser.tab.cc"
    break;

  case 187: // lpattern_field_cl: lpattern_field
#line 725 "parser.yy"
                                               { yylhs.value.as < std::vector<pdm::ast::LPattern::Field*> > ().push_back(yystack_[0].value.as < pdm::ast::LPattern::Field* > ()); }
#line 3435 "parser.tab.cc"
    break;

  case 188: // lpattern_field_cl: lpattern_field_cl "," lpattern_field
#line 726 "parser.yy"
                                               { yylhs.value.as < std::vector<pdm::ast::LPattern::Field*> > () = std::move(yystack_[2].value.as < std::vector<pdm::ast::LPattern::Field*> > ()); yylhs.value.as < std::vector<pdm::ast::LPattern::Field*> > ().push_back(yystack_[0].value.as < pdm::ast::LPattern::Field* > ()); }
#line 3441 "parser.tab.cc"
    break;

  case 189: // tpattern_field_cl1: tpattern_field
#line 729 "parser.yy"
                                              { yylhs.value.as < std::vector<pdm::ast::TPattern::Field*> > ().push_back(yystack_[0].value.as < pdm::ast::TPattern::Field* > ()); }
#line 3447 "parser.tab.cc"
    break;

  case 190: // tpattern_field_cl1: tpattern_field_cl1 "," tpattern_field
#line 730 "parser.yy"
                                                { yylhs.value.as < std::vector<pdm::ast::TPattern::Field*> > () = std::move(yystack_[2].value.as < std::vector<pdm::ast::TPattern::Field*> > ()); yylhs.value.as < std::vector<pdm::ast::TPattern::Field*> > ().push_back(yystack_[0].value.as < pdm::ast::TPattern::Field* > ()); }
#line 3453 "parser.tab.cc"
    break;

  case 191: // struct_exp_field_cl: struct_exp_field
#line 733 "parser.yy"
                                                    { yylhs.value.as < std::vector<pdm::ast::StructExp::Field*> > ().push_back(yystack_[0].value.as < pdm::ast::StructExp::Field* > ()); }
#line 3459 "parser.tab.cc"
    break;

  case 192: // struct_exp_field_cl: struct_exp_field_cl "," struct_exp_field
#line 734 "parser.yy"
                                                    { yylhs.value.as < std::vector<pdm::ast::StructExp::Field*> > () = std::move(yystack_[2].value.as < std::vector<pdm::ast::StructExp::Field*> > ()); yylhs.value.as < std::vector<pdm::ast::StructExp::Field*> > ().push_back(yystack_[0].value.as < pdm::ast::StructExp::Field* > ()); }
#line 3465 "parser.tab.cc"
    break;


#line 3469 "parser.tab.cc"

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





  const short parser::yypact_ninf_ = -250;

  const signed char parser::yytable_ninf_ = -1;

  const short
  parser::yypact_[] =
  {
    -250,   119,    14,  -250,     8,    76,   159,   169,   213,  -250,
    -250,    85,  -250,  -250,  -250,   186,    48,     9,  -250,   200,
      -1,  -250,  -250,   148,   181,  -250,    88,     8,   254,  -250,
      17,   189,    30,  -250,   207,    -6,  -250,  -250,   211,   149,
    -250,   219,  -250,  -250,  -250,  -250,   208,   214,   181,   181,
    -250,    48,  -250,  -250,  -250,  -250,  -250,  -250,  -250,    48,
    -250,    85,   210,   -32,   -20,  -250,   230,  -250,  -250,    34,
    -250,   111,     8,   275,  -250,   585,   160,  -250,   275,    36,
     181,   227,   228,   -12,    47,    73,  -250,  -250,  -250,  -250,
     181,   585,   181,   275,   148,  -250,  -250,  -250,  -250,  -250,
    -250,   148,    64,  -250,  -250,  -250,  -250,  -250,  -250,  -250,
    -250,   518,   344,  -250,  -250,   149,  -250,    48,  -250,  -250,
    -250,  -250,  -250,  -250,  -250,   196,  -250,  -250,    54,  -250,
    -250,  -250,  -250,   585,  -250,   215,   183,   206,   179,   259,
     260,   258,   250,  -250,   136,  -250,   585,   181,  -250,    77,
       8,     8,  -250,   181,  -250,   -18,  -250,   585,   585,  -250,
     181,  -250,   181,  -250,     8,  -250,  -250,  -250,  -250,  -250,
     250,    64,   234,   148,  -250,   251,   344,    64,  -250,   261,
     262,   152,     7,     7,     7,   585,   585,  -250,   257,  -250,
    -250,  -250,  -250,  -250,    11,   246,   398,   145,  -250,    87,
     160,  -250,  -250,   123,   451,  -250,  -250,  -250,  -250,   585,
    -250,  -250,   585,  -250,  -250,  -250,  -250,   585,  -250,  -250,
     585,   585,   585,   585,   305,   585,   263,   140,  -250,   275,
    -250,   181,   181,  -250,    92,  -250,   267,   108,  -250,  -250,
     181,  -250,  -250,    64,   264,   256,    44,   300,   561,  -250,
     585,  -250,     8,   181,  -250,  -250,   255,   265,   268,   269,
    -250,  -250,   585,  -250,  -250,   276,   270,     8,  -250,  -250,
    -250,  -250,   585,   585,  -250,  -250,  -250,   168,  -250,   215,
     183,   206,   179,   259,   260,   316,  -250,  -250,   277,  -250,
    -250,  -250,  -250,  -250,  -250,   271,  -250,   253,  -250,  -250,
    -250,  -250,   121,  -250,   585,   585,   585,   585,  -250,  -250,
    -250,   273,  -250,  -250,  -250,   494,  -250,   280,  -250,   282,
      46,     8,  -250,     8,  -250,  -250,  -250,  -250,  -250,  -250,
     585,  -250,  -250,  -250,   279,    -5,  -250,   171,  -250,  -250,
    -250,  -250,   181,  -250,  -250
  };

  const unsigned char
  parser::yydefact_[] =
  {
       3,     0,     0,     1,     0,     0,     0,     0,     2,     5,
      38,     0,    22,     4,     7,     0,     0,     0,     6,     0,
       0,     8,    37,     0,     0,   189,     0,     0,     0,    11,
       0,     0,     0,    21,     0,     0,    25,    39,     0,     0,
     166,     0,   178,   165,   167,   168,     0,     0,     0,     0,
     135,     0,   177,   136,   137,   138,   139,   140,   141,     0,
     184,     0,     0,     0,     0,     9,     0,    13,    12,     0,
      23,     0,     0,     0,    43,     0,     0,   169,     0,     0,
       0,     0,     0,     0,     0,     0,   147,   142,   190,    18,
       0,     0,     0,     0,     0,    14,    10,    42,    41,    24,
      26,     0,     0,   102,    70,    71,    72,    73,    40,    75,
      74,     0,     0,   100,   101,    64,    66,     0,   157,    63,
      54,    55,    56,    87,    65,    67,    68,    57,    98,    88,
      89,    90,   107,     0,    47,   111,   117,   121,   123,   125,
     127,   103,   156,   158,     0,    45,     0,   150,   152,     0,
       0,     0,   183,     0,   185,     0,   155,     0,     0,   149,
       0,   144,     0,   143,     0,   146,    16,    48,    15,    49,
       0,   141,     0,     0,    17,     0,     0,     0,    59,    48,
       0,     0,     0,     0,     0,     0,     0,    80,     0,    27,
      28,    29,    30,    31,    64,     0,     0,     0,   191,     0,
      69,    77,    76,     0,     0,    99,   104,   105,   106,     0,
     109,   110,     0,   113,   114,   115,   116,     0,   119,   120,
       0,     0,     0,     0,     0,     0,     0,     0,   151,     0,
     154,     0,     0,   172,     0,   182,     0,   156,   134,   133,
       0,   148,    86,     0,     0,     0,    64,    78,     0,    58,
       0,    61,     0,   176,   180,   181,     0,     0,     0,     0,
      36,    84,     0,    81,    82,     0,     0,     0,    62,    93,
      97,    96,     0,     0,    91,   160,   163,     0,   108,   112,
     118,   122,   124,   126,   128,    94,   159,    44,     0,   153,
     173,   174,   186,   145,    19,     0,    52,     0,    60,    50,
      51,   187,     0,   175,     0,     0,     0,     0,   171,    85,
      83,     0,   192,   161,   162,     0,    92,     0,    46,     0,
       0,     0,    79,     0,   179,    32,    33,    34,    35,   164,
       0,    95,    52,   170,     0,     0,   188,     0,    53,   132,
     130,   131,     0,    20,   129
  };

  const short
  parser::yypgoto_[] =
  {
    -250,  -250,  -250,  -250,   332,  -250,   281,   309,   -21,  -250,
    -250,  -250,  -250,   147,  -250,  -250,  -250,  -250,  -250,    93,
      -4,    75,  -250,  -250,    35,    56,   -84,  -250,    12,   -98,
      28,  -250,  -250,    49,   146,  -250,  -250,  -250,  -250,  -250,
    -250,  -250,  -250,  -250,  -128,  -250,  -250,  -250,   138,  -250,
     134,  -250,   132,  -250,   137,   131,   144,  -250,  -250,  -250,
    -250,    58,  -250,  -250,  -250,  -250,  -250,   193,   130,  -250,
    -250,   -85,   150,   224,    59,  -250,   -93,  -250,  -250,  -250,
     112,   155,  -249,   321,  -250,    67,   318,  -250,  -250,  -250,
    -250,  -250
  };

  const short
  parser::yydefgoto_[] =
  {
       0,     1,     2,     6,     7,     8,    18,    30,    31,     9,
      20,    34,    35,   188,   189,   190,   191,   192,   193,    50,
     115,    40,   116,    99,   117,   167,   180,   181,   320,   119,
     120,   121,   122,   123,   124,   125,   126,   127,   196,   169,
     128,   129,   130,   131,   132,   133,   134,   209,   135,   212,
     136,   217,   137,   220,   138,   139,   140,   141,   334,   342,
      83,   170,    53,    54,    55,    56,    85,    86,   148,   149,
      57,    58,   143,   144,   276,   277,    42,    43,    44,    45,
     198,   154,   254,    25,   255,   256,    80,    19,   155,   302,
      26,   199
  };

  const short
  parser::yytable_[] =
  {
      11,   174,    10,   301,   177,   205,   171,   168,   175,    66,
      10,    10,    24,    71,    10,    22,    36,    27,    79,    39,
      39,    46,     4,    61,    63,    27,   171,   171,   195,   234,
      93,     5,    28,   235,    91,   160,    47,    76,    27,    10,
      28,    72,    27,   161,    39,    82,    94,    76,    66,    10,
      22,    10,    22,    28,    33,    24,    46,    28,    41,    51,
      74,   252,   339,   158,    29,    49,   150,   151,   100,   340,
     341,    47,    65,   242,   336,   153,    39,   262,    39,   247,
     244,   278,    52,    51,    51,    68,    39,   152,    39,    96,
      39,   171,   195,    74,   162,    10,    75,    39,    48,   203,
      49,   333,   163,    64,   204,   270,    81,    84,   194,    23,
     262,   171,   266,   200,   111,    51,    77,    51,   176,     3,
     164,    62,   150,   151,   229,    51,   269,    51,   165,    41,
      12,   118,   230,   142,   267,    59,    41,    16,   156,    17,
     159,    60,   268,    39,    87,   294,   231,   232,   166,    39,
     172,    10,    23,    37,    97,    98,    39,   224,    39,    38,
     240,   104,   105,   106,   107,   157,   101,   179,   323,    39,
     197,   147,   246,   111,    10,    22,   324,   176,   253,   253,
     253,    46,    51,   225,    10,    22,   173,   225,    51,   226,
      39,    46,   162,   288,   224,    51,    47,    51,    74,   250,
     163,    75,   118,   251,   142,   228,    47,    13,    41,   145,
      87,   233,   146,   236,   118,   315,   237,    14,   238,   316,
     239,     4,    10,    48,    37,    49,   343,    39,    39,    51,
     153,    10,    22,    48,    21,    49,    39,    67,    46,   201,
     202,   259,   260,   210,   211,   171,   218,   219,   253,    39,
     257,   258,   159,    47,    32,    70,    10,    10,    22,    37,
     275,    73,    78,   311,    79,   102,    51,    51,   213,   214,
     215,   216,   206,   207,   208,    51,    90,    74,    95,    22,
     158,   118,    49,   142,   157,   221,   223,   222,    51,   290,
     291,   104,   105,   106,   107,   108,   109,   110,   159,   224,
     243,   263,   245,   111,   299,   261,   300,   176,   248,   285,
     296,   303,   287,   249,   297,   295,    39,   200,   308,   253,
     293,   304,   147,   317,   309,   310,   318,   338,   313,   314,
     330,   305,   321,    39,   306,   307,   332,   319,    39,   262,
      15,    69,    89,   265,   337,   331,   322,    10,    22,   271,
     279,   280,   281,   283,    46,    51,   102,   241,   282,   289,
     325,   326,   327,   328,   182,   183,   184,   284,   185,    47,
     227,   275,    51,   103,   329,   286,   186,    51,   335,   312,
      88,    92,   104,   105,   106,   107,   108,   109,   110,   292,
       0,     0,     0,     0,   111,   335,    48,     0,   112,   187,
     344,    10,    22,     0,   113,   114,     0,     0,    46,     0,
     102,     0,     0,     0,     0,     0,     0,     0,   182,   183,
     184,     0,   185,    47,     0,     0,     0,   103,     0,     0,
     186,     0,     0,     0,     0,     0,   104,   105,   106,   107,
     108,   109,   110,     0,     0,     0,     0,     0,   111,     0,
      48,     0,   112,   264,    10,    22,     0,     0,   113,   114,
       0,    46,     0,   102,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    47,     0,     0,     0,
     103,   272,   273,     0,     0,     0,     0,     0,     0,   104,
     105,   106,   107,   108,   109,   110,     0,    10,    22,     0,
       0,   111,   274,    48,    46,   112,   102,     0,     0,     0,
       0,   113,   114,     0,     0,     0,     0,     0,     0,    47,
       0,    10,    22,   103,   272,   273,     0,     0,    46,     0,
     102,     0,   104,   105,   106,   107,   108,   109,   110,     0,
       0,     0,     0,    47,   111,     0,    48,   103,   112,     0,
       0,     0,     0,     0,   113,   114,   104,   105,   106,   107,
     108,   109,   110,     0,    10,    22,     0,     0,   111,   178,
      48,    46,   112,   102,     0,     0,     0,     0,   113,   114,
       0,     0,     0,     0,     0,     0,    47,     0,    10,    22,
     103,     0,     0,     0,     0,    46,     0,   102,     0,   104,
     105,   106,   107,   108,   109,   110,     0,     0,     0,     0,
      47,   111,   298,    48,   103,   112,     0,     0,     0,     0,
       0,   113,   114,   104,   105,   106,   107,   108,   109,   110,
       0,     0,     0,     0,     0,   111,     0,    48,     0,   112,
       0,     0,     0,     0,     0,   113,   114
  };

  const short
  parser::yycheck_[] =
  {
       4,    94,     3,   252,   102,   133,    91,    91,   101,    30,
       3,     3,    16,    19,     3,     4,    20,     8,    50,    23,
      24,    10,     8,    27,    28,     8,   111,   112,   112,    47,
      50,    17,    23,    51,    66,    47,    25,    41,     8,     3,
      23,    47,     8,    55,    48,    49,    66,    51,    69,     3,
       4,     3,     4,    23,    55,    59,    10,    23,    23,    24,
      49,    54,    67,    52,    55,    54,    30,    31,    72,    74,
      75,    25,    55,   171,   323,    79,    80,    66,    82,   177,
     173,   209,    24,    48,    49,    55,    90,    51,    92,    55,
      94,   176,   176,    49,    47,     3,    52,   101,    52,    45,
      54,    55,    55,    28,    50,   203,    48,    49,   112,    16,
      66,   196,   196,   117,    50,    80,    41,    82,    54,     0,
      47,    28,    30,    31,    47,    90,     3,    92,    55,    94,
      54,    75,    55,    75,    47,    47,   101,    52,    80,    54,
      82,    53,    55,   147,    51,   243,   150,   151,    90,   153,
      92,     3,    59,     5,    43,    44,   160,    49,   162,    11,
     164,    38,    39,    40,    41,    57,    73,   111,    47,   173,
     112,    78,   176,    50,     3,     4,    55,    54,   182,   183,
     184,    10,   147,    47,     3,     4,    93,    47,   153,    53,
     194,    10,    47,    53,    49,   160,    25,   162,    49,    47,
      55,    52,   146,    51,   146,   147,    25,    48,   173,    49,
     117,   153,    52,   157,   158,    47,   158,    48,   160,    51,
     162,     8,     3,    52,     5,    54,    55,   231,   232,   194,
     234,     3,     4,    52,    48,    54,   240,    48,    10,    43,
      44,   185,   186,    60,    61,   330,    67,    68,   252,   253,
     183,   184,   194,    25,    54,    48,     3,     3,     4,     5,
     204,    50,    54,   267,    50,    12,   231,   232,    62,    63,
      64,    65,    57,    58,    59,   240,    66,    49,    48,     4,
      52,   225,    54,   225,    57,    26,    28,    27,   253,   231,
     232,    38,    39,    40,    41,    42,    43,    44,   240,    49,
      66,    55,    51,    50,   248,    48,   250,    54,    47,     4,
      54,   253,    49,    51,    14,    51,   320,   321,   262,   323,
      53,    66,   229,     7,    48,    55,    49,    48,   272,   273,
      50,    66,   297,   337,    66,    66,    54,    66,   342,    66,
       8,    32,    61,   196,   332,   317,   297,     3,     4,   203,
     212,   217,   220,   222,    10,   320,    12,   164,   221,   229,
     304,   305,   306,   307,    20,    21,    22,   223,    24,    25,
     146,   315,   337,    29,   315,   225,    32,   342,   320,   267,
      59,    63,    38,    39,    40,    41,    42,    43,    44,   234,
      -1,    -1,    -1,    -1,    50,   337,    52,    -1,    54,    55,
     342,     3,     4,    -1,    60,    61,    -1,    -1,    10,    -1,
      12,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    20,    21,
      22,    -1,    24,    25,    -1,    -1,    -1,    29,    -1,    -1,
      32,    -1,    -1,    -1,    -1,    -1,    38,    39,    40,    41,
      42,    43,    44,    -1,    -1,    -1,    -1,    -1,    50,    -1,
      52,    -1,    54,    55,     3,     4,    -1,    -1,    60,    61,
      -1,    10,    -1,    12,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    25,    -1,    -1,    -1,
      29,    30,    31,    -1,    -1,    -1,    -1,    -1,    -1,    38,
      39,    40,    41,    42,    43,    44,    -1,     3,     4,    -1,
      -1,    50,    51,    52,    10,    54,    12,    -1,    -1,    -1,
      -1,    60,    61,    -1,    -1,    -1,    -1,    -1,    -1,    25,
      -1,     3,     4,    29,    30,    31,    -1,    -1,    10,    -1,
      12,    -1,    38,    39,    40,    41,    42,    43,    44,    -1,
      -1,    -1,    -1,    25,    50,    -1,    52,    29,    54,    -1,
      -1,    -1,    -1,    -1,    60,    61,    38,    39,    40,    41,
      42,    43,    44,    -1,     3,     4,    -1,    -1,    50,    51,
      52,    10,    54,    12,    -1,    -1,    -1,    -1,    60,    61,
      -1,    -1,    -1,    -1,    -1,    -1,    25,    -1,     3,     4,
      29,    -1,    -1,    -1,    -1,    10,    -1,    12,    -1,    38,
      39,    40,    41,    42,    43,    44,    -1,    -1,    -1,    -1,
      25,    50,    51,    52,    29,    54,    -1,    -1,    -1,    -1,
      -1,    60,    61,    38,    39,    40,    41,    42,    43,    44,
      -1,    -1,    -1,    -1,    -1,    50,    -1,    52,    -1,    54,
      -1,    -1,    -1,    -1,    -1,    60,    61
  };

  const unsigned char
  parser::yystos_[] =
  {
       0,    78,    79,     0,     8,    17,    80,    81,    82,    86,
       3,    97,    54,    48,    48,    81,    52,    54,    83,   164,
      87,    48,     4,    96,    97,   160,   167,     8,    23,    55,
      84,    85,    54,    55,    88,    89,    97,     5,    11,    97,
      98,   101,   153,   154,   155,   156,    10,    25,    52,    54,
      96,   101,   138,   139,   140,   141,   142,   147,   148,    47,
      53,    97,    96,    97,    98,    55,    85,    48,    55,    84,
      48,    19,    47,    50,    49,    52,    97,    98,    54,    50,
     163,   138,    97,   137,   138,   143,   144,    96,   160,    83,
      66,    66,   163,    50,    66,    48,    55,    43,    44,   100,
      97,    96,    12,    29,    38,    39,    40,    41,    42,    43,
      44,    50,    54,    60,    61,    97,    99,   101,   102,   106,
     107,   108,   109,   110,   111,   112,   113,   114,   117,   118,
     119,   120,   121,   122,   123,   125,   127,   129,   131,   132,
     133,   134,   138,   149,   150,    49,    52,    96,   145,   146,
      30,    31,    51,    97,   158,   165,   138,    57,    52,   138,
      47,    55,    47,    55,    47,    55,   138,   102,   103,   116,
     138,   148,   138,    96,   153,   153,    54,   106,    51,   102,
     103,   104,    20,    21,    22,    24,    32,    55,    90,    91,
      92,    93,    94,    95,    97,   103,   115,   138,   157,   168,
      97,    43,    44,    45,    50,   121,    57,    58,    59,   124,
      60,    61,   126,    62,    63,    64,    65,   128,    67,    68,
     130,    26,    27,    28,    49,    47,    53,   150,   138,    47,
      55,    97,    97,   138,    47,    51,   102,   138,   138,   138,
      97,   144,   106,    66,   153,    51,    97,   106,    47,    51,
      47,    51,    54,    97,   159,   161,   162,   162,   162,   102,
     102,    48,    66,    55,    55,    90,   103,    47,    55,     3,
     106,   111,    30,    31,    51,   102,   151,   152,   121,   125,
     127,   129,   131,   132,   133,     4,   149,    49,    53,   145,
     138,   138,   158,    53,   106,    51,    54,    14,    51,   102,
     102,   159,   166,   138,    66,    66,    66,    66,   102,    48,
      55,    97,   157,   102,   102,    47,    51,     7,    49,    66,
     105,   101,   110,    47,    55,   102,   102,   102,   102,   151,
      50,   107,    54,    55,   135,   138,   159,   105,    48,    67,
      74,    75,   136,    55,   138
  };

  const unsigned char
  parser::yyr1_[] =
  {
       0,    77,    78,    79,    79,    80,    81,    82,    82,    83,
      83,    83,    83,    84,    84,    85,    85,    85,    85,    85,
      85,    86,    87,    87,    88,    89,    89,    90,    90,    90,
      90,    90,    91,    92,    93,    94,    95,    96,    97,    98,
      99,   100,   100,   101,   101,   101,   101,   102,   103,   103,
     104,   104,   105,   105,   106,   106,   106,   106,   107,   108,
     108,   108,   109,   110,   110,   110,   110,   110,   110,   110,
     111,   111,   111,   111,   112,   112,   112,   112,   113,   113,
     114,   114,   114,   114,   115,   115,   116,   117,   117,   117,
     117,   118,   118,   119,   119,   119,   120,   120,   121,   121,
     122,   122,   122,   123,   124,   124,   124,   125,   125,   126,
     126,   127,   127,   128,   128,   128,   128,   129,   129,   130,
     130,   131,   131,   132,   132,   133,   133,   134,   134,   135,
     136,   136,   136,   137,   137,   138,   138,   138,   138,   138,
     138,   138,   139,   140,   140,   141,   142,   143,   143,   144,
     145,   145,   146,   146,   147,   148,   149,   149,   150,   150,
     151,   151,   151,   152,   152,   153,   154,   154,   154,   155,
     156,   157,   158,   158,   158,   159,   159,   160,   160,   161,
     162,   162,   163,   163,   164,   165,   165,   166,   166,   167,
     167,   168,   168
  };

  const signed char
  parser::yyr2_[] =
  {
       0,     2,     2,     0,     3,     1,     3,     2,     3,     3,
       4,     2,     3,     2,     3,     4,     4,     4,     3,     6,
      10,     4,     0,     3,     3,     1,     3,     1,     1,     1,
       1,     1,     4,     4,     4,     4,     2,     1,     1,     1,
       1,     1,     1,     2,     5,     3,     6,     1,     1,     1,
       3,     3,     0,     3,     1,     1,     1,     1,     3,     2,
       4,     3,     3,     1,     1,     1,     1,     1,     1,     2,
       1,     1,     1,     1,     1,     1,     2,     2,     3,     5,
       2,     3,     3,     4,     2,     3,     2,     1,     1,     1,
       1,     3,     4,     3,     3,     5,     3,     3,     1,     2,
       1,     1,     1,     1,     1,     1,     1,     1,     3,     1,
       1,     1,     3,     1,     1,     1,     1,     1,     3,     1,
       1,     1,     3,     1,     3,     1,     3,     1,     3,     3,
       1,     1,     1,     3,     3,     1,     1,     1,     1,     1,
       1,     1,     2,     3,     3,     5,     3,     1,     3,     2,
       1,     2,     1,     3,     4,     3,     1,     1,     1,     3,
       1,     2,     2,     1,     3,     1,     1,     1,     1,     2,
       8,     3,     2,     3,     3,     2,     1,     2,     2,     3,
       1,     1,     3,     2,     3,     1,     3,     1,     3,     1,
       3,     1,     3
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
  "expr", "long_exp", "expr_cl2", "type_query_exp_sl0", "bracketed_exp",
  "paren_exp", "vtupleExpr", "vstructExpr", "primary_exp", "int_expr",
  "stringls", "if_exp", "chain_exp", "chain_prefix", "lambda_exp",
  "postfix_exp", "vcall_exp", "dot_name_exp", "dot_index_exp", "unary_exp",
  "unary_op", "binary_exp", "mul_binary_op", "mul_binary_exp",
  "add_binary_op", "add_binary_exp", "cmp_binary_op", "cmp_binary_exp",
  "eq_binary_op", "eq_binary_exp", "and_binary_exp", "xor_binary_exp",
  "or_binary_exp", "type_query_exp", "type_query_op", "type_spec_cl2",
  "type_spec", "mod_prefix_tid", "tuple_type_spec", "array_type_spec",
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
       0,   278,   278,   286,   287,   290,   294,   297,   298,   306,
     307,   308,   309,   312,   313,   316,   317,   318,   319,   320,
     325,   336,   341,   342,   345,   348,   349,   353,   354,   355,
     356,   357,   360,   363,   366,   369,   372,   379,   380,   381,
     384,   387,   388,   391,   392,   393,   394,   401,   404,   405,
     417,   418,   421,   422,   426,   427,   428,   429,   440,   443,
     444,   445,   448,   451,   452,   453,   454,   455,   456,   457,
     460,   461,   462,   463,   466,   467,   468,   469,   472,   473,
     476,   477,   478,   479,   482,   483,   486,   490,   491,   492,
     493,   496,   497,   500,   501,   502,   505,   506,   510,   511,
     514,   515,   516,   520,   523,   524,   525,   528,   529,   532,
     533,   536,   537,   540,   541,   542,   543,   546,   547,   550,
     551,   554,   555,   558,   559,   562,   563,   566,   567,   571,
     574,   575,   576,   591,   592,   596,   597,   598,   599,   600,
     601,   602,   606,   610,   611,   614,   618,   621,   622,   625,
     629,   630,   633,   634,   637,   640,   643,   644,   647,   648,
     650,   651,   652,   655,   656,   666,   669,   670,   671,   674,
     679,   689,   692,   693,   694,   697,   698,   701,   702,   706,
     709,   710,   713,   714,   717,   721,   722,   725,   726,   729,
     730,   733,   734
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
#line 4160 "parser.tab.cc"

#line 737 "parser.yy"


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
