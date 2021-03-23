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

      case symbol_kind::S_import_field_group: // import_field_group
        value.copy< ast::ImportStmt::FieldGroup* > (YY_MOVE (that.value));
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

      case symbol_kind::S_using_tpattern: // using_tpattern
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

      case symbol_kind::S_import_field_group: // import_field_group
        value.move< ast::ImportStmt::FieldGroup* > (YY_MOVE (s.value));
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

      case symbol_kind::S_using_tpattern: // using_tpattern
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

      case symbol_kind::S_import_field_group: // import_field_group
        value.YY_MOVE_OR_COPY< ast::ImportStmt::FieldGroup* > (YY_MOVE (that.value));
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

      case symbol_kind::S_using_tpattern: // using_tpattern
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

      case symbol_kind::S_import_field_group: // import_field_group
        value.move< ast::ImportStmt::FieldGroup* > (YY_MOVE (that.value));
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

      case symbol_kind::S_using_tpattern: // using_tpattern
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

      case symbol_kind::S_import_field_group: // import_field_group
        value.copy< ast::ImportStmt::FieldGroup* > (that.value);
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

      case symbol_kind::S_using_tpattern: // using_tpattern
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

      case symbol_kind::S_import_field_group: // import_field_group
        value.move< ast::ImportStmt::FieldGroup* > (that.value);
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

      case symbol_kind::S_using_tpattern: // using_tpattern
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

      case symbol_kind::S_import_field_group: // import_field_group
        yylhs.value.emplace< ast::ImportStmt::FieldGroup* > ();
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

      case symbol_kind::S_using_tpattern: // using_tpattern
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
#line 279 "parser.yy"
                                      {
    yylhs.value.as < pdm::ast::Script* > () = mgr->new_script(source, yylhs.location, std::move(yystack_[1].value.as < std::vector<pdm::ast::HeaderStmt*> > ()), std::move(yystack_[0].value.as < std::vector<pdm::ast::Script::Field*> > ()));

    // setting the returnp here => this is the node parser returns.  
    *returnp = yylhs.value.as < pdm::ast::Script* > (); 
}
#line 2321 "parser.tab.cc"
    break;

  case 3: // script_header: %empty
#line 287 "parser.yy"
                                                    { yylhs.value.as < std::vector<pdm::ast::HeaderStmt*> > ().reserve(16); }
#line 2327 "parser.tab.cc"
    break;

  case 4: // script_header: script_header script_header_stmt ";"
#line 288 "parser.yy"
                                                    { yylhs.value.as < std::vector<pdm::ast::HeaderStmt*> > () = std::move(yystack_[2].value.as < std::vector<pdm::ast::HeaderStmt*> > ()); yylhs.value.as < std::vector<pdm::ast::HeaderStmt*> > ().push_back(yystack_[1].value.as < pdm::ast::HeaderStmt* > ()); }
#line 2333 "parser.tab.cc"
    break;

  case 5: // script_header_stmt: import_stmt
#line 291 "parser.yy"
      { yylhs.value.as < pdm::ast::HeaderStmt* > () = yystack_[0].value.as < pdm::ast::HeaderStmt* > (); }
#line 2339 "parser.tab.cc"
    break;

  case 6: // script_field: "mod" vid mod_exp
#line 295 "parser.yy"
                          { yylhs.value.as < pdm::ast::Script::Field* > () = mgr->new_script_field(yylhs.location, yystack_[1].value.as < TokenInfo > ().ID_intstr, yystack_[0].value.as < pdm::ast::ModExp* > ()); }
#line 2345 "parser.tab.cc"
    break;

  case 7: // script_field_sl: script_field ";"
#line 298 "parser.yy"
                                                { yylhs.value.as < std::vector<pdm::ast::Script::Field*> > ().push_back(yystack_[1].value.as < pdm::ast::Script::Field* > ()); }
#line 2351 "parser.tab.cc"
    break;

  case 8: // script_field_sl: script_field_sl script_field ";"
#line 299 "parser.yy"
                                                { yylhs.value.as < std::vector<pdm::ast::Script::Field*> > () = std::move(yystack_[2].value.as < std::vector<pdm::ast::Script::Field*> > ()); yylhs.value.as < std::vector<pdm::ast::Script::Field*> > ().push_back(yystack_[1].value.as < pdm::ast::Script::Field* > ()); }
#line 2357 "parser.tab.cc"
    break;

  case 9: // mod_exp: "{" mod_field_sl "}"
#line 307 "parser.yy"
                                                    { yylhs.value.as < pdm::ast::ModExp* > () = mgr->new_mod_exp(yylhs.location, nullptr, std::move(yystack_[1].value.as < std::vector<pdm::ast::ModExp::Field*> > ())); }
#line 2363 "parser.tab.cc"
    break;

  case 10: // mod_exp: "{" using_tpattern mod_field_sl "}"
#line 308 "parser.yy"
                                                    { yylhs.value.as < pdm::ast::ModExp* > () = mgr->new_mod_exp(yylhs.location, yystack_[2].value.as < pdm::ast::TPattern* > (), std::move(yystack_[1].value.as < std::vector<pdm::ast::ModExp::Field*> > ())); }
#line 2369 "parser.tab.cc"
    break;

  case 11: // mod_exp: "{" "}"
#line 309 "parser.yy"
                                                    { yylhs.value.as < pdm::ast::ModExp* > () = mgr->new_mod_exp(yylhs.location, nullptr, std::move(std::vector<ast::ModExp::Field*>{})); }
#line 2375 "parser.tab.cc"
    break;

  case 12: // mod_exp: "{" using_tpattern "}"
#line 310 "parser.yy"
                                                    { yylhs.value.as < pdm::ast::ModExp* > () = mgr->new_mod_exp(yylhs.location, yystack_[1].value.as < pdm::ast::TPattern* > (), std::move(std::vector<ast::ModExp::Field*>{})); }
#line 2381 "parser.tab.cc"
    break;

  case 13: // mod_field_sl: mod_field ";"
#line 313 "parser.yy"
                                        { yylhs.value.as < std::vector<pdm::ast::ModExp::Field*> > ().push_back(yystack_[1].value.as < pdm::ast::ModExp::Field* > ()); }
#line 2387 "parser.tab.cc"
    break;

  case 14: // mod_field_sl: mod_field_sl mod_field ";"
#line 314 "parser.yy"
                                        { yylhs.value.as < std::vector<pdm::ast::ModExp::Field*> > () = std::move(yystack_[2].value.as < std::vector<pdm::ast::ModExp::Field*> > ()); yylhs.value.as < std::vector<pdm::ast::ModExp::Field*> > ().push_back(yystack_[1].value.as < pdm::ast::ModExp::Field* > ()); }
#line 2393 "parser.tab.cc"
    break;

  case 15: // mod_field: vid "=" long_exp
#line 317 "parser.yy"
                           { yylhs.value.as < pdm::ast::ModExp::Field* > () = mgr->new_value_mod_field(yylhs.location, yystack_[2].value.as < TokenInfo > ().ID_intstr, yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2399 "parser.tab.cc"
    break;

  case 16: // mod_field: tid "=" type_spec
#line 318 "parser.yy"
                           { yylhs.value.as < pdm::ast::ModExp::Field* > () = mgr->new_type_mod_field(yylhs.location, yystack_[2].value.as < TokenInfo > ().ID_intstr, yystack_[0].value.as < pdm::ast::TypeSpec* > ()); }
#line 2405 "parser.tab.cc"
    break;

  case 17: // mod_field: cid "=" class_spec
#line 319 "parser.yy"
                           { yylhs.value.as < pdm::ast::ModExp::Field* > () = mgr->new_class_mod_field(yylhs.location, yystack_[2].value.as < TokenInfo > ().ID_intstr, yystack_[0].value.as < pdm::ast::ClassSpec* > ()); }
#line 2411 "parser.tab.cc"
    break;

  case 18: // mod_field: "mod" vid mod_exp
#line 320 "parser.yy"
                           { yylhs.value.as < pdm::ast::ModExp::Field* > () = mgr->new_mod_mod_field(yylhs.location, yystack_[1].value.as < TokenInfo > ().ID_intstr, yystack_[0].value.as < pdm::ast::ModExp* > ()); }
#line 2417 "parser.tab.cc"
    break;

  case 19: // using_tpattern: "using" tpattern ";"
#line 323 "parser.yy"
                                    { yylhs.value.as < pdm::ast::TPattern* > () = yystack_[1].value.as < pdm::ast::TPattern* > (); }
#line 2423 "parser.tab.cc"
    break;

  case 20: // import_stmt: "imports" "{" import_field_group_sl0 "}"
#line 331 "parser.yy"
                                                      {
        yylhs.value.as < pdm::ast::HeaderStmt* > () = mgr->new_import_stmt(yylhs.location, std::move(yystack_[1].value.as < std::vector<ast::ImportStmt::FieldGroup*> > ()));
      }
#line 2431 "parser.tab.cc"
    break;

  case 21: // import_field_group_sl0: %empty
#line 336 "parser.yy"
             {}
#line 2437 "parser.tab.cc"
    break;

  case 22: // import_field_group_sl0: import_field_group_sl0 import_field_group ";"
#line 337 "parser.yy"
                                                           { yylhs.value.as < std::vector<ast::ImportStmt::FieldGroup*> > () = std::move(yystack_[2].value.as < std::vector<ast::ImportStmt::FieldGroup*> > ()); yylhs.value.as < std::vector<ast::ImportStmt::FieldGroup*> > ().push_back(yystack_[1].value.as < ast::ImportStmt::FieldGroup* > ()); }
#line 2443 "parser.tab.cc"
    break;

  case 23: // import_field_group: import_field_cl1 "from" stringl
#line 340 "parser.yy"
                                         { yylhs.value.as < ast::ImportStmt::FieldGroup* > () = mgr->new_import_field_group(yylhs.location, std::move(yystack_[2].value.as < std::vector<ast::ImportStmt::Field*> > ()), *yystack_[0].value.as < TokenInfo > ().String_utf8string); }
#line 2449 "parser.tab.cc"
    break;

  case 24: // import_field_cl1: vid
#line 343 "parser.yy"
                                    { yylhs.value.as < std::vector<ast::ImportStmt::Field*> > ().push_back(mgr->new_import_field(yystack_[0].location, yystack_[0].value.as < TokenInfo > ().ID_intstr)); }
#line 2455 "parser.tab.cc"
    break;

  case 25: // import_field_cl1: import_field_cl1 "," vid
#line 344 "parser.yy"
                                    { yylhs.value.as < std::vector<ast::ImportStmt::Field*> > () = std::move(yystack_[2].value.as < std::vector<ast::ImportStmt::Field*> > ()); yylhs.value.as < std::vector<ast::ImportStmt::Field*> > ().push_back(mgr->new_import_field(yystack_[0].location, yystack_[0].value.as < TokenInfo > ().ID_intstr)); }
#line 2461 "parser.tab.cc"
    break;

  case 26: // chain_prefix_stmt: const_stmt
#line 348 "parser.yy"
      { yylhs.value.as < pdm::ast::Stmt* > () = yystack_[0].value.as < pdm::ast::Stmt* > (); }
#line 2467 "parser.tab.cc"
    break;

  case 27: // chain_prefix_stmt: val_stmt
#line 349 "parser.yy"
      { yylhs.value.as < pdm::ast::Stmt* > () = yystack_[0].value.as < pdm::ast::Stmt* > (); }
#line 2473 "parser.tab.cc"
    break;

  case 28: // chain_prefix_stmt: var_stmt
#line 350 "parser.yy"
      { yylhs.value.as < pdm::ast::Stmt* > () = yystack_[0].value.as < pdm::ast::Stmt* > (); }
#line 2479 "parser.tab.cc"
    break;

  case 29: // chain_prefix_stmt: set_stmt
#line 351 "parser.yy"
      { yylhs.value.as < pdm::ast::Stmt* > () = yystack_[0].value.as < pdm::ast::Stmt* > (); }
#line 2485 "parser.tab.cc"
    break;

  case 30: // chain_prefix_stmt: discard_stmt
#line 352 "parser.yy"
      { yylhs.value.as < pdm::ast::Stmt* > () = yystack_[0].value.as < pdm::ast::Stmt* > (); }
#line 2491 "parser.tab.cc"
    break;

  case 31: // const_stmt: "const" lpattern "=" expr
#line 355 "parser.yy"
                                  { yylhs.value.as < pdm::ast::Stmt* > () = mgr->new_const_stmt(yylhs.location, yystack_[2].value.as < pdm::ast::LPattern* > (), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2497 "parser.tab.cc"
    break;

  case 32: // val_stmt: "val" lpattern "=" expr
#line 358 "parser.yy"
                                  { yylhs.value.as < pdm::ast::Stmt* > () = mgr->new_val_stmt(yylhs.location, yystack_[2].value.as < pdm::ast::LPattern* > (), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2503 "parser.tab.cc"
    break;

  case 33: // var_stmt: "var" lpattern "=" expr
#line 361 "parser.yy"
                                  { yylhs.value.as < pdm::ast::Stmt* > () = mgr->new_var_stmt(yylhs.location, yystack_[2].value.as < pdm::ast::LPattern* > (), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2509 "parser.tab.cc"
    break;

  case 34: // set_stmt: "set" expr "=" expr
#line 364 "parser.yy"
                              { yylhs.value.as < pdm::ast::Stmt* > () = mgr->new_set_stmt(yylhs.location, yystack_[2].value.as < pdm::ast::Exp* > (), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2515 "parser.tab.cc"
    break;

  case 35: // discard_stmt: "discard" expr
#line 367 "parser.yy"
                        { yylhs.value.as < pdm::ast::Stmt* > () = mgr->new_discard_stmt(yylhs.location, yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2521 "parser.tab.cc"
    break;

  case 36: // tid: "TypeId"
#line 374 "parser.yy"
     { yylhs.value.as < TokenInfo > () = yystack_[0].value.as < TokenInfo > (); }
#line 2527 "parser.tab.cc"
    break;

  case 37: // vid: "val_id"
#line 375 "parser.yy"
     { yylhs.value.as < TokenInfo > () = yystack_[0].value.as < TokenInfo > (); }
#line 2533 "parser.tab.cc"
    break;

  case 38: // cid: "CLS_ID"
#line 376 "parser.yy"
     { yylhs.value.as < TokenInfo > () = yystack_[0].value.as < TokenInfo > (); }
#line 2539 "parser.tab.cc"
    break;

  case 39: // floatl: "4.2"
#line 379 "parser.yy"
      { yylhs.value.as < TokenInfo > () = yystack_[0].value.as < TokenInfo > (); }
#line 2545 "parser.tab.cc"
    break;

  case 40: // stringl: "'sq-string-literal'"
#line 382 "parser.yy"
      { yylhs.value.as < TokenInfo > () = yystack_[0].value.as < TokenInfo > (); }
#line 2551 "parser.tab.cc"
    break;

  case 41: // stringl: "\"dq-string-literal\""
#line 383 "parser.yy"
      { yylhs.value.as < TokenInfo > () = yystack_[0].value.as < TokenInfo > (); }
#line 2557 "parser.tab.cc"
    break;

  case 42: // mod_prefix: vid "::"
#line 386 "parser.yy"
                                                      { yylhs.value.as < pdm::ast::ModAddress* > () = mgr->new_mod_address(yylhs.location, nullptr, yystack_[1].value.as < TokenInfo > ().ID_intstr, std::move(std::vector<ast::TArg*>{})); }
#line 2563 "parser.tab.cc"
    break;

  case 43: // mod_prefix: vid "[" targ_cl "]" "::"
#line 387 "parser.yy"
                                                      { yylhs.value.as < pdm::ast::ModAddress* > () = mgr->new_mod_address(yylhs.location, nullptr, yystack_[4].value.as < TokenInfo > ().ID_intstr, std::move(yystack_[2].value.as < std::vector<pdm::ast::TArg*> > ())); }
#line 2569 "parser.tab.cc"
    break;

  case 44: // mod_prefix: mod_prefix vid "::"
#line 388 "parser.yy"
                                                      { yylhs.value.as < pdm::ast::ModAddress* > () = mgr->new_mod_address(yylhs.location, yystack_[2].value.as < pdm::ast::ModAddress* > (), yystack_[1].value.as < TokenInfo > ().ID_intstr, std::move(std::vector<ast::TArg*>{})); }
#line 2575 "parser.tab.cc"
    break;

  case 45: // mod_prefix: mod_prefix vid "[" targ_cl "]" "::"
#line 389 "parser.yy"
                                                      { yylhs.value.as < pdm::ast::ModAddress* > () = mgr->new_mod_address(yylhs.location, yystack_[5].value.as < pdm::ast::ModAddress* > (), yystack_[4].value.as < TokenInfo > ().ID_intstr, std::move(yystack_[2].value.as < std::vector<pdm::ast::TArg*> > ())); }
#line 2581 "parser.tab.cc"
    break;

  case 46: // expr: binary_exp
#line 396 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2587 "parser.tab.cc"
    break;

  case 47: // long_exp: expr
#line 399 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2593 "parser.tab.cc"
    break;

  case 48: // long_exp: lambda_exp
#line 400 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2599 "parser.tab.cc"
    break;

  case 49: // expr_cl2: expr "," expr
#line 412 "parser.yy"
                             { yylhs.value.as < std::vector<pdm::ast::Exp*> > ().reserve(2); yylhs.value.as < std::vector<pdm::ast::Exp*> > ().push_back(yystack_[2].value.as < pdm::ast::Exp* > ()); yylhs.value.as < std::vector<pdm::ast::Exp*> > ().push_back(yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2605 "parser.tab.cc"
    break;

  case 50: // expr_cl2: expr_cl2 "," expr
#line 413 "parser.yy"
                             { yylhs.value.as < std::vector<pdm::ast::Exp*> > () = std::move(yystack_[2].value.as < std::vector<pdm::ast::Exp*> > ()); yylhs.value.as < std::vector<pdm::ast::Exp*> > ().push_back(yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2611 "parser.tab.cc"
    break;

  case 51: // type_query_exp_sl0: %empty
#line 416 "parser.yy"
                                                  {}
#line 2617 "parser.tab.cc"
    break;

  case 52: // type_query_exp_sl0: type_query_exp_sl0 type_query_exp ";"
#line 417 "parser.yy"
                                                  { yylhs.value.as < std::vector<pdm::ast::TypeQueryExp*> > () = std::move(yystack_[2].value.as < std::vector<pdm::ast::TypeQueryExp*> > ()); yylhs.value.as < std::vector<pdm::ast::TypeQueryExp*> > ().push_back(yystack_[1].value.as < pdm::ast::TypeQueryExp* > ()); }
#line 2623 "parser.tab.cc"
    break;

  case 53: // bracketed_exp: paren_exp
#line 421 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2629 "parser.tab.cc"
    break;

  case 54: // bracketed_exp: vtupleExpr
#line 422 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2635 "parser.tab.cc"
    break;

  case 55: // bracketed_exp: vstructExpr
#line 423 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2641 "parser.tab.cc"
    break;

  case 56: // bracketed_exp: chain_exp
#line 424 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2647 "parser.tab.cc"
    break;

  case 57: // paren_exp: "(" long_exp ")"
#line 435 "parser.yy"
                              { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_paren_exp(yylhs.location, yystack_[1].value.as < pdm::ast::Exp* > ()); }
#line 2653 "parser.tab.cc"
    break;

  case 58: // vtupleExpr: "(" ")"
#line 438 "parser.yy"
                                   { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_tuple_exp(yylhs.location, std::move(std::vector<ast::Exp*>())); }
#line 2659 "parser.tab.cc"
    break;

  case 59: // vtupleExpr: "(" expr "," ")"
#line 439 "parser.yy"
                                   { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_tuple_exp(yylhs.location, std::move(std::vector(1,yystack_[2].value.as < pdm::ast::Exp* > ()))); }
#line 2665 "parser.tab.cc"
    break;

  case 60: // vtupleExpr: "(" expr_cl2 ")"
#line 440 "parser.yy"
                                   { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_tuple_exp(yylhs.location, std::move(yystack_[1].value.as < std::vector<pdm::ast::Exp*> > ())); }
#line 2671 "parser.tab.cc"
    break;

  case 61: // vstructExpr: "{" struct_exp_field_cl "}"
#line 443 "parser.yy"
                                            { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_struct_exp(yylhs.location, std::move(yystack_[1].value.as < std::vector<pdm::ast::StructExp::Field*> > ())); }
#line 2677 "parser.tab.cc"
    break;

  case 62: // primary_exp: bracketed_exp
#line 446 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2683 "parser.tab.cc"
    break;

  case 63: // primary_exp: vid
#line 447 "parser.yy"
                     { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_id_exp(yylhs.location, yystack_[0].value.as < TokenInfo > ().ID_intstr); }
#line 2689 "parser.tab.cc"
    break;

  case 64: // primary_exp: int_expr
#line 448 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2695 "parser.tab.cc"
    break;

  case 65: // primary_exp: floatl
#line 449 "parser.yy"
                     { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_float_exp(yylhs.location, yystack_[0].value.as < TokenInfo > ().Float); }
#line 2701 "parser.tab.cc"
    break;

  case 66: // primary_exp: stringls
#line 450 "parser.yy"
                     { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_string_exp(yylhs.location, std::move(yystack_[0].value.as < std::vector<pdm::ast::StringExp::Piece> > ())); }
#line 2707 "parser.tab.cc"
    break;

  case 67: // primary_exp: if_exp
#line 451 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2713 "parser.tab.cc"
    break;

  case 68: // primary_exp: mod_prefix vid
#line 452 "parser.yy"
                        { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_module_dot_name_exp(yylhs.location, yystack_[1].value.as < pdm::ast::ModAddress* > (), yystack_[0].value.as < TokenInfo > ().ID_intstr); }
#line 2719 "parser.tab.cc"
    break;

  case 69: // int_expr: "42"
#line 455 "parser.yy"
                { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_int_exp(yylhs.location, yystack_[0].value.as < TokenInfo > ().Int, ast::IntExp::Base::Dec, false); }
#line 2725 "parser.tab.cc"
    break;

  case 70: // int_expr: "0x2a"
#line 456 "parser.yy"
                { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_int_exp(yylhs.location, yystack_[0].value.as < TokenInfo > ().Int, ast::IntExp::Base::Hex, false); }
#line 2731 "parser.tab.cc"
    break;

  case 71: // int_expr: "42u"
#line 457 "parser.yy"
                         { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_int_exp(yylhs.location, yystack_[0].value.as < TokenInfo > ().Int, ast::IntExp::Base::Dec, true); }
#line 2737 "parser.tab.cc"
    break;

  case 72: // int_expr: "0x2Au"
#line 458 "parser.yy"
                         { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_int_exp(yylhs.location, yystack_[0].value.as < TokenInfo > ().Int, ast::IntExp::Base::Hex, true); }
#line 2743 "parser.tab.cc"
    break;

  case 73: // stringls: "'sq-string-literal'"
#line 461 "parser.yy"
                             { yylhs.value.as < std::vector<pdm::ast::StringExp::Piece> > ().emplace_back(yylhs.location, *yystack_[0].value.as < TokenInfo > ().String_utf8string, ast::StringExp::QuoteKind::SingleQuote); }
#line 2749 "parser.tab.cc"
    break;

  case 74: // stringls: "\"dq-string-literal\""
#line 462 "parser.yy"
                             { yylhs.value.as < std::vector<pdm::ast::StringExp::Piece> > ().emplace_back(yylhs.location, *yystack_[0].value.as < TokenInfo > ().String_utf8string, ast::StringExp::QuoteKind::DoubleQuote); }
#line 2755 "parser.tab.cc"
    break;

  case 75: // stringls: stringls "'sq-string-literal'"
#line 463 "parser.yy"
                             { yylhs.value.as < std::vector<pdm::ast::StringExp::Piece> > () = std::move(yystack_[1].value.as < std::vector<pdm::ast::StringExp::Piece> > ()); yylhs.value.as < std::vector<pdm::ast::StringExp::Piece> > ().emplace_back(yystack_[0].location, *yystack_[0].value.as < TokenInfo > ().String_utf8string, ast::StringExp::QuoteKind::SingleQuote); }
#line 2761 "parser.tab.cc"
    break;

  case 76: // stringls: stringls "\"dq-string-literal\""
#line 464 "parser.yy"
                             { yylhs.value.as < std::vector<pdm::ast::StringExp::Piece> > () = std::move(yystack_[1].value.as < std::vector<pdm::ast::StringExp::Piece> > ()); yylhs.value.as < std::vector<pdm::ast::StringExp::Piece> > ().emplace_back(yystack_[0].location, *yystack_[0].value.as < TokenInfo > ().String_utf8string, ast::StringExp::QuoteKind::DoubleQuote); }
#line 2767 "parser.tab.cc"
    break;

  case 77: // if_exp: "if" bracketed_exp bracketed_exp
#line 467 "parser.yy"
                                                                { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_if_exp(yylhs.location, yystack_[1].value.as < pdm::ast::Exp* > (), yystack_[0].value.as < pdm::ast::Exp* > (), nullptr); }
#line 2773 "parser.tab.cc"
    break;

  case 78: // if_exp: "if" bracketed_exp bracketed_exp "else" primary_exp
#line 468 "parser.yy"
                                                                { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_if_exp(yylhs.location, yystack_[3].value.as < pdm::ast::Exp* > (), yystack_[2].value.as < pdm::ast::Exp* > (), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2779 "parser.tab.cc"
    break;

  case 79: // chain_exp: "{" "}"
#line 471 "parser.yy"
                                               { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_chain_exp(yylhs.location, std::move(std::vector<ast::Stmt*>{}), nullptr); }
#line 2785 "parser.tab.cc"
    break;

  case 80: // chain_exp: "{" long_exp "}"
#line 472 "parser.yy"
                                               { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_chain_exp(yylhs.location, std::move(std::vector<ast::Stmt*>{}), yystack_[1].value.as < pdm::ast::Exp* > ()); }
#line 2791 "parser.tab.cc"
    break;

  case 81: // chain_exp: "{" chain_prefix "}"
#line 473 "parser.yy"
                                               { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_chain_exp(yylhs.location, std::move(yystack_[1].value.as < std::vector<pdm::ast::Stmt*> > ()), nullptr); }
#line 2797 "parser.tab.cc"
    break;

  case 82: // chain_exp: "{" chain_prefix long_exp "}"
#line 474 "parser.yy"
                                               { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_chain_exp(yylhs.location, std::move(yystack_[2].value.as < std::vector<pdm::ast::Stmt*> > ()), yystack_[1].value.as < pdm::ast::Exp* > ()); }
#line 2803 "parser.tab.cc"
    break;

  case 83: // chain_prefix: chain_prefix_stmt ";"
#line 477 "parser.yy"
                                                { yylhs.value.as < std::vector<pdm::ast::Stmt*> > ().push_back(yystack_[1].value.as < pdm::ast::Stmt* > ()); }
#line 2809 "parser.tab.cc"
    break;

  case 84: // chain_prefix: chain_prefix chain_prefix_stmt ";"
#line 478 "parser.yy"
                                                { yylhs.value.as < std::vector<pdm::ast::Stmt*> > () = std::move(yystack_[2].value.as < std::vector<pdm::ast::Stmt*> > ()); yylhs.value.as < std::vector<pdm::ast::Stmt*> > ().push_back(yystack_[1].value.as < pdm::ast::Stmt* > ()); }
#line 2815 "parser.tab.cc"
    break;

  case 85: // lambda_exp: fn_type_spec bracketed_exp
#line 481 "parser.yy"
                                   { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_lambda_exp(yylhs.location, yystack_[1].value.as < pdm::ast::FnTypeSpec* > (), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2821 "parser.tab.cc"
    break;

  case 86: // postfix_exp: primary_exp
#line 485 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2827 "parser.tab.cc"
    break;

  case 87: // postfix_exp: vcall_exp
#line 486 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2833 "parser.tab.cc"
    break;

  case 88: // postfix_exp: dot_name_exp
#line 487 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2839 "parser.tab.cc"
    break;

  case 89: // postfix_exp: dot_index_exp
#line 488 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2845 "parser.tab.cc"
    break;

  case 90: // vcall_exp: postfix_exp "(" ")"
#line 491 "parser.yy"
                                            { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_vcall_exp(yylhs.location, yystack_[2].value.as < pdm::ast::Exp* > (), std::move(std::vector<ast::VArg*>{})); }
#line 2851 "parser.tab.cc"
    break;

  case 91: // vcall_exp: postfix_exp "(" varg_cl ")"
#line 492 "parser.yy"
                                            { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_vcall_exp(yylhs.location, yystack_[3].value.as < pdm::ast::Exp* > (), std::move(yystack_[1].value.as < std::vector<pdm::ast::VArg*> > ())); }
#line 2857 "parser.tab.cc"
    break;

  case 92: // dot_name_exp: postfix_exp "." "val_id"
#line 495 "parser.yy"
                                                { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_struct_dot_name_exp(yylhs.location, yystack_[2].value.as < pdm::ast::Exp* > (), yystack_[0].value.as < TokenInfo > ().ID_intstr); }
#line 2863 "parser.tab.cc"
    break;

  case 93: // dot_name_exp: type_spec "::" "TypeId"
#line 496 "parser.yy"
                                                    { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_enum_dot_name_exp(yylhs.location, yystack_[2].value.as < pdm::ast::TypeSpec* > (), yystack_[0].value.as < TokenInfo > ().ID_intstr, nullptr); }
#line 2869 "parser.tab.cc"
    break;

  case 94: // dot_name_exp: type_spec "::" "TypeId" "using" paren_exp
#line 497 "parser.yy"
                                                    { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_enum_dot_name_exp(yylhs.location, yystack_[4].value.as < pdm::ast::TypeSpec* > (), yystack_[2].value.as < TokenInfo > ().ID_intstr, yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2875 "parser.tab.cc"
    break;

  case 95: // dot_index_exp: postfix_exp "." int_expr
#line 500 "parser.yy"
                                    { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_dot_index_exp(yylhs.location, yystack_[2].value.as < pdm::ast::Exp* > (), yystack_[0].value.as < pdm::ast::Exp* > (), ast::DotIndexExp::RhsHint::LhsNotPtr); }
#line 2881 "parser.tab.cc"
    break;

  case 96: // dot_index_exp: postfix_exp "." bracketed_exp
#line 501 "parser.yy"
                                    { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_dot_index_exp(yylhs.location, yystack_[2].value.as < pdm::ast::Exp* > (), yystack_[0].value.as < pdm::ast::Exp* > (), ast::DotIndexExp::RhsHint::LhsNotPtr); }
#line 2887 "parser.tab.cc"
    break;

  case 97: // unary_exp: postfix_exp
#line 505 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2893 "parser.tab.cc"
    break;

  case 98: // unary_exp: unary_op unary_exp
#line 506 "parser.yy"
                             { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_unary_exp(yylhs.location, yystack_[1].value.as < pdm::ast::UnaryOperator > (), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2899 "parser.tab.cc"
    break;

  case 99: // unary_op: "+"
#line 509 "parser.yy"
                 { yylhs.value.as < pdm::ast::UnaryOperator > () = ast::UnaryOperator::Plus; }
#line 2905 "parser.tab.cc"
    break;

  case 100: // unary_op: "-"
#line 510 "parser.yy"
                 { yylhs.value.as < pdm::ast::UnaryOperator > () = ast::UnaryOperator::Minus; }
#line 2911 "parser.tab.cc"
    break;

  case 101: // unary_op: "not"
#line 511 "parser.yy"
                 { yylhs.value.as < pdm::ast::UnaryOperator > () = ast::UnaryOperator::Not; }
#line 2917 "parser.tab.cc"
    break;

  case 102: // binary_exp: or_binary_exp
#line 515 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2923 "parser.tab.cc"
    break;

  case 103: // mul_binary_op: "*"
#line 518 "parser.yy"
                 { yylhs.value.as < pdm::ast::BinaryOperator > () = ast::BinaryOperator::Mul; }
#line 2929 "parser.tab.cc"
    break;

  case 104: // mul_binary_op: "/"
#line 519 "parser.yy"
                 { yylhs.value.as < pdm::ast::BinaryOperator > () = ast::BinaryOperator::Div; }
#line 2935 "parser.tab.cc"
    break;

  case 105: // mul_binary_op: "%"
#line 520 "parser.yy"
                 { yylhs.value.as < pdm::ast::BinaryOperator > () = ast::BinaryOperator::Rem; }
#line 2941 "parser.tab.cc"
    break;

  case 106: // mul_binary_exp: unary_exp
#line 523 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2947 "parser.tab.cc"
    break;

  case 107: // mul_binary_exp: mul_binary_exp mul_binary_op unary_exp
#line 524 "parser.yy"
                                               { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_binary_exp(yylhs.location, yystack_[1].value.as < pdm::ast::BinaryOperator > (), yystack_[2].value.as < pdm::ast::Exp* > (), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2953 "parser.tab.cc"
    break;

  case 108: // add_binary_op: "+"
#line 527 "parser.yy"
             { yylhs.value.as < pdm::ast::BinaryOperator > () = ast::BinaryOperator::Add; }
#line 2959 "parser.tab.cc"
    break;

  case 109: // add_binary_op: "-"
#line 528 "parser.yy"
             { yylhs.value.as < pdm::ast::BinaryOperator > () = ast::BinaryOperator::Subtract; }
#line 2965 "parser.tab.cc"
    break;

  case 110: // add_binary_exp: mul_binary_exp
#line 531 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2971 "parser.tab.cc"
    break;

  case 111: // add_binary_exp: add_binary_exp add_binary_op mul_binary_exp
#line 532 "parser.yy"
                                                    { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_binary_exp(yylhs.location, yystack_[1].value.as < pdm::ast::BinaryOperator > (), yystack_[2].value.as < pdm::ast::Exp* > (), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2977 "parser.tab.cc"
    break;

  case 112: // cmp_binary_op: "<"
#line 535 "parser.yy"
                { yylhs.value.as < pdm::ast::BinaryOperator > () = ast::BinaryOperator::Less; }
#line 2983 "parser.tab.cc"
    break;

  case 113: // cmp_binary_op: "<="
#line 536 "parser.yy"
                { yylhs.value.as < pdm::ast::BinaryOperator > () = ast::BinaryOperator::LessOrEq; }
#line 2989 "parser.tab.cc"
    break;

  case 114: // cmp_binary_op: ">"
#line 537 "parser.yy"
                { yylhs.value.as < pdm::ast::BinaryOperator > () = ast::BinaryOperator::Greater; }
#line 2995 "parser.tab.cc"
    break;

  case 115: // cmp_binary_op: ">="
#line 538 "parser.yy"
                { yylhs.value.as < pdm::ast::BinaryOperator > () = ast::BinaryOperator::GreaterOrEq; }
#line 3001 "parser.tab.cc"
    break;

  case 116: // cmp_binary_exp: add_binary_exp
#line 541 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 3007 "parser.tab.cc"
    break;

  case 117: // cmp_binary_exp: cmp_binary_exp cmp_binary_op add_binary_exp
#line 542 "parser.yy"
                                                    { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_binary_exp(yylhs.location, yystack_[1].value.as < pdm::ast::BinaryOperator > (), yystack_[2].value.as < pdm::ast::Exp* > (), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 3013 "parser.tab.cc"
    break;

  case 118: // eq_binary_op: "=="
#line 545 "parser.yy"
                 { yylhs.value.as < pdm::ast::BinaryOperator > () = ast::BinaryOperator::Equals; }
#line 3019 "parser.tab.cc"
    break;

  case 119: // eq_binary_op: "!="
#line 546 "parser.yy"
                 { yylhs.value.as < pdm::ast::BinaryOperator > () = ast::BinaryOperator::NotEquals; }
#line 3025 "parser.tab.cc"
    break;

  case 120: // eq_binary_exp: cmp_binary_exp
#line 549 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 3031 "parser.tab.cc"
    break;

  case 121: // eq_binary_exp: eq_binary_exp eq_binary_op cmp_binary_exp
#line 550 "parser.yy"
                                                { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_binary_exp(yylhs.location, yystack_[1].value.as < pdm::ast::BinaryOperator > (), yystack_[2].value.as < pdm::ast::Exp* > (), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 3037 "parser.tab.cc"
    break;

  case 122: // and_binary_exp: eq_binary_exp
#line 553 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 3043 "parser.tab.cc"
    break;

  case 123: // and_binary_exp: and_binary_exp "and" eq_binary_exp
#line 554 "parser.yy"
                                           { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_binary_exp(yylhs.location, ast::BinaryOperator::And, yystack_[2].value.as < pdm::ast::Exp* > (), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 3049 "parser.tab.cc"
    break;

  case 124: // xor_binary_exp: and_binary_exp
#line 557 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 3055 "parser.tab.cc"
    break;

  case 125: // xor_binary_exp: xor_binary_exp "xor" and_binary_exp
#line 558 "parser.yy"
                                           { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_binary_exp(yylhs.location, ast::BinaryOperator::XOr, yystack_[2].value.as < pdm::ast::Exp* > (), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 3061 "parser.tab.cc"
    break;

  case 126: // or_binary_exp: xor_binary_exp
#line 561 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 3067 "parser.tab.cc"
    break;

  case 127: // or_binary_exp: or_binary_exp "or" xor_binary_exp
#line 562 "parser.yy"
                                           { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_binary_exp(yylhs.location, ast::BinaryOperator::Or, yystack_[2].value.as < pdm::ast::Exp* > (), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 3073 "parser.tab.cc"
    break;

  case 128: // type_query_exp: type_spec type_query_op type_spec
#line 566 "parser.yy"
                                          { yylhs.value.as < pdm::ast::TypeQueryExp* > () = mgr->new_type_query_exp(yylhs.location, yystack_[1].value.as < pdm::ast::TypeQueryKind > (), yystack_[2].value.as < pdm::ast::TypeSpec* > (), yystack_[0].value.as < pdm::ast::TypeSpec* > ()); }
#line 3079 "parser.tab.cc"
    break;

  case 129: // type_query_op: ":<"
#line 569 "parser.yy"
                    { yylhs.value.as < pdm::ast::TypeQueryKind > () = ast::TypeQueryKind::LhsSubtypesRhs; }
#line 3085 "parser.tab.cc"
    break;

  case 130: // type_query_op: ">:"
#line 570 "parser.yy"
                    { yylhs.value.as < pdm::ast::TypeQueryKind > () = ast::TypeQueryKind::LhsSupertypesRhs; }
#line 3091 "parser.tab.cc"
    break;

  case 131: // type_query_op: "=="
#line 571 "parser.yy"
                    { yylhs.value.as < pdm::ast::TypeQueryKind > () = ast::TypeQueryKind::LhsEqualsRhs; }
#line 3097 "parser.tab.cc"
    break;

  case 132: // type_spec_cl2: type_spec "," type_spec
#line 586 "parser.yy"
                                    { yylhs.value.as < std::vector<pdm::ast::TypeSpec*> > ().reserve(2); yylhs.value.as < std::vector<pdm::ast::TypeSpec*> > ().push_back(yystack_[2].value.as < pdm::ast::TypeSpec* > ()); yylhs.value.as < std::vector<pdm::ast::TypeSpec*> > ().push_back(yystack_[0].value.as < pdm::ast::TypeSpec* > ()); }
#line 3103 "parser.tab.cc"
    break;

  case 133: // type_spec_cl2: type_spec_cl2 "," type_spec
#line 587 "parser.yy"
                                    { yylhs.value.as < std::vector<pdm::ast::TypeSpec*> > () = std::move(yystack_[2].value.as < std::vector<pdm::ast::TypeSpec*> > ()); yylhs.value.as < std::vector<pdm::ast::TypeSpec*> > ().push_back(yystack_[0].value.as < pdm::ast::TypeSpec* > ()); }
#line 3109 "parser.tab.cc"
    break;

  case 134: // type_spec: tid
#line 591 "parser.yy"
                        { yylhs.value.as < pdm::ast::TypeSpec* > () = mgr->new_id_type_spec(yylhs.location, yystack_[0].value.as < TokenInfo > ().ID_intstr); }
#line 3115 "parser.tab.cc"
    break;

  case 135: // type_spec: mod_prefix_tid
#line 592 "parser.yy"
      { yylhs.value.as < pdm::ast::TypeSpec* > () = yystack_[0].value.as < pdm::ast::TypeSpec* > (); }
#line 3121 "parser.tab.cc"
    break;

  case 136: // type_spec: tuple_type_spec
#line 593 "parser.yy"
      { yylhs.value.as < pdm::ast::TypeSpec* > () = yystack_[0].value.as < pdm::ast::TypeSpec* > (); }
#line 3127 "parser.tab.cc"
    break;

  case 137: // type_spec: array_type_spec
#line 594 "parser.yy"
      { yylhs.value.as < pdm::ast::TypeSpec* > () = yystack_[0].value.as < pdm::ast::TypeSpec* > (); }
#line 3133 "parser.tab.cc"
    break;

  case 138: // type_spec: struct_type_spec
#line 595 "parser.yy"
      { yylhs.value.as < pdm::ast::TypeSpec* > () = yystack_[0].value.as < pdm::ast::TypeSpec* > (); }
#line 3139 "parser.tab.cc"
    break;

  case 139: // type_spec: enum_type_spec
#line 596 "parser.yy"
      { yylhs.value.as < pdm::ast::TypeSpec* > () = yystack_[0].value.as < pdm::ast::TypeSpec* > (); }
#line 3145 "parser.tab.cc"
    break;

  case 140: // type_spec: fn_type_spec
#line 597 "parser.yy"
                    { yylhs.value.as < pdm::ast::TypeSpec* > () = dynamic_cast<ast::TypeSpec*>(yystack_[0].value.as < pdm::ast::FnTypeSpec* > ()); }
#line 3151 "parser.tab.cc"
    break;

  case 141: // mod_prefix_tid: mod_prefix tid
#line 601 "parser.yy"
                            { yylhs.value.as < pdm::ast::TypeSpec* > () = mgr->new_ma_type_spec(yylhs.location, yystack_[1].value.as < pdm::ast::ModAddress* > (), yystack_[0].value.as < TokenInfo > ().ID_intstr); }
#line 3157 "parser.tab.cc"
    break;

  case 142: // tuple_type_spec: "{" type_spec "}"
#line 605 "parser.yy"
                                   { yylhs.value.as < pdm::ast::TypeSpec* > () = mgr->new_tuple_type_spec(yylhs.location, std::move(std::vector(1,yystack_[1].value.as < pdm::ast::TypeSpec* > ()))); }
#line 3163 "parser.tab.cc"
    break;

  case 143: // tuple_type_spec: "{" type_spec_cl2 "}"
#line 606 "parser.yy"
                                   { yylhs.value.as < pdm::ast::TypeSpec* > () = mgr->new_tuple_type_spec(yylhs.location, std::move(yystack_[1].value.as < std::vector<pdm::ast::TypeSpec*> > ())); }
#line 3169 "parser.tab.cc"
    break;

  case 144: // array_type_spec: "[" type_spec "*" expr "]"
#line 609 "parser.yy"
                                                { yylhs.value.as < pdm::ast::TypeSpec* > () = nullptr; }
#line 3175 "parser.tab.cc"
    break;

  case 145: // struct_type_spec: "{" struct_type_spec_field_cl "}"
#line 613 "parser.yy"
                                               { yylhs.value.as < pdm::ast::TypeSpec* > () = mgr->new_struct_type_spec(yylhs.location, std::move(yystack_[1].value.as < std::vector<pdm::ast::StructTypeSpec::Field*> > ())); }
#line 3181 "parser.tab.cc"
    break;

  case 146: // struct_type_spec_field_cl: struct_type_spec_field
#line 616 "parser.yy"
                                                              { yylhs.value.as < std::vector<pdm::ast::StructTypeSpec::Field*> > ().push_back(yystack_[0].value.as < pdm::ast::StructTypeSpec::Field* > ()); }
#line 3187 "parser.tab.cc"
    break;

  case 147: // struct_type_spec_field_cl: struct_type_spec_field_cl "," struct_type_spec_field
#line 617 "parser.yy"
                                                              { yylhs.value.as < std::vector<pdm::ast::StructTypeSpec::Field*> > () = std::move(yystack_[2].value.as < std::vector<pdm::ast::StructTypeSpec::Field*> > ()); yylhs.value.as < std::vector<pdm::ast::StructTypeSpec::Field*> > ().push_back(yystack_[0].value.as < pdm::ast::StructTypeSpec::Field* > ()); }
#line 3193 "parser.tab.cc"
    break;

  case 148: // struct_type_spec_field: vid type_spec
#line 620 "parser.yy"
                                    { yylhs.value.as < pdm::ast::StructTypeSpec::Field* > () = mgr->new_struct_type_spec_field(yylhs.location, yystack_[1].value.as < TokenInfo > ().ID_intstr, yystack_[0].value.as < pdm::ast::TypeSpec* > ()); }
#line 3199 "parser.tab.cc"
    break;

  case 149: // enum_type_spec_field: tid
#line 624 "parser.yy"
                        { yylhs.value.as < pdm::ast::EnumTypeSpec::Field* > () = mgr->new_enum_type_spec_field(yylhs.location, yystack_[0].value.as < TokenInfo > ().ID_intstr, nullptr); }
#line 3205 "parser.tab.cc"
    break;

  case 150: // enum_type_spec_field: tid type_spec
#line 625 "parser.yy"
                        { yylhs.value.as < pdm::ast::EnumTypeSpec::Field* > () = mgr->new_enum_type_spec_field(yylhs.location, yystack_[1].value.as < TokenInfo > ().ID_intstr, yystack_[0].value.as < pdm::ast::TypeSpec* > ()); }
#line 3211 "parser.tab.cc"
    break;

  case 151: // enum_type_spec_field_cl: enum_type_spec_field
#line 628 "parser.yy"
                                                            { yylhs.value.as < std::vector<pdm::ast::EnumTypeSpec::Field*> > ().push_back(yystack_[0].value.as < pdm::ast::EnumTypeSpec::Field* > ()); }
#line 3217 "parser.tab.cc"
    break;

  case 152: // enum_type_spec_field_cl: enum_type_spec_field_cl "," enum_type_spec_field
#line 629 "parser.yy"
                                                            { yylhs.value.as < std::vector<pdm::ast::EnumTypeSpec::Field*> > () = std::move(yystack_[2].value.as < std::vector<pdm::ast::EnumTypeSpec::Field*> > ()); yylhs.value.as < std::vector<pdm::ast::EnumTypeSpec::Field*> > ().push_back(yystack_[0].value.as < pdm::ast::EnumTypeSpec::Field* > ()); }
#line 3223 "parser.tab.cc"
    break;

  case 153: // enum_type_spec: "enum" "{" enum_type_spec_field_cl "}"
#line 632 "parser.yy"
                                                        { yylhs.value.as < pdm::ast::TypeSpec* > () = mgr->new_enum_type_spec(yylhs.location, std::move(yystack_[1].value.as < std::vector<pdm::ast::EnumTypeSpec::Field*> > ())); }
#line 3229 "parser.tab.cc"
    break;

  case 154: // fn_type_spec: "fn" vpattern type_spec
#line 635 "parser.yy"
                               { yylhs.value.as < pdm::ast::FnTypeSpec* > () = mgr->new_fn_type_spec(yylhs.location, std::move(yystack_[1].value.as < pdm::ast::VPattern* > ()), yystack_[0].value.as < pdm::ast::TypeSpec* > ()); }
#line 3235 "parser.tab.cc"
    break;

  case 155: // targ: type_spec
#line 638 "parser.yy"
                { yylhs.value.as < pdm::ast::TArg* > () = mgr->new_targ_type_spec(yylhs.location, yystack_[0].value.as < pdm::ast::TypeSpec* > ()); }
#line 3241 "parser.tab.cc"
    break;

  case 156: // targ: expr
#line 639 "parser.yy"
               { yylhs.value.as < pdm::ast::TArg* > () = mgr->new_targ_exp(yylhs.location, yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 3247 "parser.tab.cc"
    break;

  case 157: // targ_cl: targ
#line 642 "parser.yy"
                            { yylhs.value.as < std::vector<pdm::ast::TArg*> > ().push_back(yystack_[0].value.as < pdm::ast::TArg* > ()); }
#line 3253 "parser.tab.cc"
    break;

  case 158: // targ_cl: targ_cl "," targ
#line 643 "parser.yy"
                            { yylhs.value.as < std::vector<pdm::ast::TArg*> > () = std::move(yystack_[2].value.as < std::vector<pdm::ast::TArg*> > ()); yylhs.value.as < std::vector<pdm::ast::TArg*> > ().push_back(yystack_[0].value.as < pdm::ast::TArg* > ()); }
#line 3259 "parser.tab.cc"
    break;

  case 159: // varg: expr
#line 645 "parser.yy"
                            { yylhs.value.as < pdm::ast::VArg* > () = mgr->new_varg(yylhs.location, yystack_[0].value.as < pdm::ast::Exp* > (), ast::VArgAccessSpec::In); }
#line 3265 "parser.tab.cc"
    break;

  case 160: // varg: "out" expr
#line 646 "parser.yy"
                            { yylhs.value.as < pdm::ast::VArg* > () = mgr->new_varg(yylhs.location, yystack_[0].value.as < pdm::ast::Exp* > (), ast::VArgAccessSpec::Out); }
#line 3271 "parser.tab.cc"
    break;

  case 161: // varg: "inout" expr
#line 647 "parser.yy"
                            { yylhs.value.as < pdm::ast::VArg* > () = mgr->new_varg(yylhs.location, yystack_[0].value.as < pdm::ast::Exp* > (), ast::VArgAccessSpec::InOut); }
#line 3277 "parser.tab.cc"
    break;

  case 162: // varg_cl: varg
#line 650 "parser.yy"
                            { yylhs.value.as < std::vector<pdm::ast::VArg*> > ().push_back(yystack_[0].value.as < pdm::ast::VArg* > ()); }
#line 3283 "parser.tab.cc"
    break;

  case 163: // varg_cl: varg_cl "," varg
#line 651 "parser.yy"
                            { yylhs.value.as < std::vector<pdm::ast::VArg*> > () = std::move(yystack_[2].value.as < std::vector<pdm::ast::VArg*> > ()); yylhs.value.as < std::vector<pdm::ast::VArg*> > ().push_back(yystack_[0].value.as < pdm::ast::VArg* > ()); }
#line 3289 "parser.tab.cc"
    break;

  case 164: // class_spec: primary_class_spec
#line 661 "parser.yy"
      { yylhs.value.as < pdm::ast::ClassSpec* > () = yystack_[0].value.as < pdm::ast::ClassSpec* > (); }
#line 3295 "parser.tab.cc"
    break;

  case 165: // primary_class_spec: cid
#line 664 "parser.yy"
                        { yylhs.value.as < pdm::ast::ClassSpec* > () = mgr->new_id_class_spec(yylhs.location, yystack_[0].value.as < TokenInfo > ().ID_intstr); }
#line 3301 "parser.tab.cc"
    break;

  case 166: // primary_class_spec: mod_prefix_cid_class_spec
#line 665 "parser.yy"
      { yylhs.value.as < pdm::ast::ClassSpec* > () = yystack_[0].value.as < pdm::ast::ClassSpec* > (); }
#line 3307 "parser.tab.cc"
    break;

  case 167: // primary_class_spec: class_exp_class_spec
#line 666 "parser.yy"
      { yylhs.value.as < pdm::ast::ClassSpec* > () = yystack_[0].value.as < pdm::ast::ClassSpec* > (); }
#line 3313 "parser.tab.cc"
    break;

  case 168: // mod_prefix_cid_class_spec: mod_prefix cid
#line 669 "parser.yy"
                        { yylhs.value.as < pdm::ast::ClassSpec* > () = mgr->new_ma_class_spec(yylhs.location, std::move(yystack_[1].value.as < pdm::ast::ModAddress* > ()), yystack_[0].value.as < TokenInfo > ().ID_intstr); }
#line 3319 "parser.tab.cc"
    break;

  case 169: // class_exp_class_spec: "typeclass" "(" tid class_spec ")" "{" type_query_exp_sl0 "}"
#line 674 "parser.yy"
                                                                                 {
            yylhs.value.as < pdm::ast::ClassSpec* > () = mgr->new_class_exp_class_spec(yylhs.location, yystack_[5].value.as < TokenInfo > ().ID_intstr, yystack_[4].value.as < pdm::ast::ClassSpec* > (), std::move(yystack_[1].value.as < std::vector<pdm::ast::TypeQueryExp*> > ()));
        }
#line 3327 "parser.tab.cc"
    break;

  case 170: // struct_exp_field: vid "=" expr
#line 684 "parser.yy"
                    { yylhs.value.as < pdm::ast::StructExp::Field* > () = mgr->new_struct_exp_field(yylhs.location, yystack_[2].value.as < TokenInfo > ().ID_intstr, yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 3333 "parser.tab.cc"
    break;

  case 171: // vpattern_field: vid type_spec
#line 687 "parser.yy"
                             { yylhs.value.as < pdm::ast::VPattern::Field* > () = mgr->new_vpattern_field(yylhs.location, yystack_[1].value.as < TokenInfo > ().ID_intstr, yystack_[0].value.as < pdm::ast::TypeSpec* > (), ast::VArgAccessSpec::In); }
#line 3339 "parser.tab.cc"
    break;

  case 172: // vpattern_field: "out" vid type_spec
#line 688 "parser.yy"
                             { yylhs.value.as < pdm::ast::VPattern::Field* > () = mgr->new_vpattern_field(yylhs.location, yystack_[1].value.as < TokenInfo > ().ID_intstr, yystack_[0].value.as < pdm::ast::TypeSpec* > (), ast::VArgAccessSpec::Out); }
#line 3345 "parser.tab.cc"
    break;

  case 173: // vpattern_field: "inout" vid type_spec
#line 689 "parser.yy"
                             { yylhs.value.as < pdm::ast::VPattern::Field* > () = mgr->new_vpattern_field(yylhs.location, yystack_[1].value.as < TokenInfo > ().ID_intstr, yystack_[0].value.as < pdm::ast::TypeSpec* > (), ast::VArgAccessSpec::InOut); }
#line 3351 "parser.tab.cc"
    break;

  case 174: // lpattern_field: vid type_spec
#line 692 "parser.yy"
                     { yylhs.value.as < pdm::ast::LPattern::Field* > () = mgr->new_lpattern_field(yylhs.location, ast::LPattern::FieldKind::IdTypeSpecPair, yystack_[1].value.as < TokenInfo > ().ID_intstr, yystack_[0].value.as < pdm::ast::TypeSpec* > ()); }
#line 3357 "parser.tab.cc"
    break;

  case 175: // lpattern_field: vid
#line 693 "parser.yy"
                    { yylhs.value.as < pdm::ast::LPattern::Field* > () = mgr->new_lpattern_field(yylhs.location, ast::LPattern::FieldKind::IdSingleton, yystack_[0].value.as < TokenInfo > ().ID_intstr); }
#line 3363 "parser.tab.cc"
    break;

  case 176: // tpattern_field: vid type_spec
#line 696 "parser.yy"
                      { yylhs.value.as < pdm::ast::TPattern::Field* > () = mgr->new_value_tpattern_field(yylhs.location, yystack_[1].value.as < TokenInfo > ().ID_intstr, yystack_[0].value.as < pdm::ast::TypeSpec* > ()); }
#line 3369 "parser.tab.cc"
    break;

  case 177: // tpattern_field: tid class_spec
#line 697 "parser.yy"
                      { yylhs.value.as < pdm::ast::TPattern::Field* > () = mgr->new_type_tpattern_field(yylhs.location, yystack_[1].value.as < TokenInfo > ().ID_intstr, yystack_[0].value.as < pdm::ast::ClassSpec* > ()); }
#line 3375 "parser.tab.cc"
    break;

  case 178: // destructured_lpattern: "{" lpattern_field_cl "}"
#line 701 "parser.yy"
                                       { yylhs.value.as < pdm::ast::LPattern* > () = mgr->new_lpattern(yylhs.location, std::move(yystack_[1].value.as < std::vector<pdm::ast::LPattern::Field*> > ()), true); }
#line 3381 "parser.tab.cc"
    break;

  case 179: // lpattern: lpattern_field
#line 704 "parser.yy"
                        { yylhs.value.as < pdm::ast::LPattern* > () = mgr->new_lpattern(yylhs.location, std::move(std::vector<ast::LPattern::Field*>{1,yystack_[0].value.as < pdm::ast::LPattern::Field* > ()}), false); }
#line 3387 "parser.tab.cc"
    break;

  case 180: // lpattern: destructured_lpattern
#line 705 "parser.yy"
      { yylhs.value.as < pdm::ast::LPattern* > () = yystack_[0].value.as < pdm::ast::LPattern* > (); }
#line 3393 "parser.tab.cc"
    break;

  case 181: // vpattern: "(" vpattern_field_cl ")"
#line 708 "parser.yy"
                                       { yylhs.value.as < pdm::ast::VPattern* > () = mgr->new_vpattern(yylhs.location, std::move(yystack_[1].value.as < std::vector<pdm::ast::VPattern::Field*> > ())); }
#line 3399 "parser.tab.cc"
    break;

  case 182: // vpattern: "(" ")"
#line 709 "parser.yy"
                                       { yylhs.value.as < pdm::ast::VPattern* > () = mgr->new_vpattern(yylhs.location, std::move(std::vector<ast::VPattern::Field*>{})); }
#line 3405 "parser.tab.cc"
    break;

  case 183: // tpattern: "[" tpattern_field_cl1 "]"
#line 712 "parser.yy"
                                        { yylhs.value.as < pdm::ast::TPattern* > () = mgr->new_tpattern(yylhs.location, std::move(yystack_[1].value.as < std::vector<pdm::ast::TPattern::Field*> > ()), false); }
#line 3411 "parser.tab.cc"
    break;

  case 184: // vpattern_field_cl: vpattern_field
#line 716 "parser.yy"
                                              { yylhs.value.as < std::vector<pdm::ast::VPattern::Field*> > ().push_back(yystack_[0].value.as < pdm::ast::VPattern::Field* > ()); }
#line 3417 "parser.tab.cc"
    break;

  case 185: // vpattern_field_cl: vpattern_field_cl "," vpattern_field
#line 717 "parser.yy"
                                               { yylhs.value.as < std::vector<pdm::ast::VPattern::Field*> > () = std::move(yystack_[2].value.as < std::vector<pdm::ast::VPattern::Field*> > ()); yylhs.value.as < std::vector<pdm::ast::VPattern::Field*> > ().push_back(yystack_[0].value.as < pdm::ast::VPattern::Field* > ()); }
#line 3423 "parser.tab.cc"
    break;

  case 186: // lpattern_field_cl: lpattern_field
#line 720 "parser.yy"
                                               { yylhs.value.as < std::vector<pdm::ast::LPattern::Field*> > ().push_back(yystack_[0].value.as < pdm::ast::LPattern::Field* > ()); }
#line 3429 "parser.tab.cc"
    break;

  case 187: // lpattern_field_cl: lpattern_field_cl "," lpattern_field
#line 721 "parser.yy"
                                               { yylhs.value.as < std::vector<pdm::ast::LPattern::Field*> > () = std::move(yystack_[2].value.as < std::vector<pdm::ast::LPattern::Field*> > ()); yylhs.value.as < std::vector<pdm::ast::LPattern::Field*> > ().push_back(yystack_[0].value.as < pdm::ast::LPattern::Field* > ()); }
#line 3435 "parser.tab.cc"
    break;

  case 188: // tpattern_field_cl1: tpattern_field
#line 724 "parser.yy"
                                              { yylhs.value.as < std::vector<pdm::ast::TPattern::Field*> > ().push_back(yystack_[0].value.as < pdm::ast::TPattern::Field* > ()); }
#line 3441 "parser.tab.cc"
    break;

  case 189: // tpattern_field_cl1: tpattern_field_cl1 "," tpattern_field
#line 725 "parser.yy"
                                                { yylhs.value.as < std::vector<pdm::ast::TPattern::Field*> > () = std::move(yystack_[2].value.as < std::vector<pdm::ast::TPattern::Field*> > ()); yylhs.value.as < std::vector<pdm::ast::TPattern::Field*> > ().push_back(yystack_[0].value.as < pdm::ast::TPattern::Field* > ()); }
#line 3447 "parser.tab.cc"
    break;

  case 190: // struct_exp_field_cl: struct_exp_field
#line 728 "parser.yy"
                                                    { yylhs.value.as < std::vector<pdm::ast::StructExp::Field*> > ().push_back(yystack_[0].value.as < pdm::ast::StructExp::Field* > ()); }
#line 3453 "parser.tab.cc"
    break;

  case 191: // struct_exp_field_cl: struct_exp_field_cl "," struct_exp_field
#line 729 "parser.yy"
                                                    { yylhs.value.as < std::vector<pdm::ast::StructExp::Field*> > () = std::move(yystack_[2].value.as < std::vector<pdm::ast::StructExp::Field*> > ()); yylhs.value.as < std::vector<pdm::ast::StructExp::Field*> > ().push_back(yystack_[0].value.as < pdm::ast::StructExp::Field* > ()); }
#line 3459 "parser.tab.cc"
    break;


#line 3463 "parser.tab.cc"

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





  const short parser::yypact_ninf_ = -226;

  const signed char parser::yytable_ninf_ = -1;

  const short
  parser::yypact_[] =
  {
    -226,    28,     3,  -226,    63,    19,     2,    38,   108,  -226,
    -226,    82,  -226,  -226,  -226,   115,    29,  -226,     7,  -226,
    -226,  -226,   133,    63,  -226,    87,   126,   118,   138,   143,
     153,  -226,   190,    -6,  -226,    93,   200,    82,  -226,   209,
    -226,  -226,   160,   239,   621,    13,  -226,   148,    63,    13,
     239,  -226,    66,  -226,  -226,  -226,  -226,   174,   211,   239,
     239,  -226,    36,    93,  -226,  -226,  -226,  -226,  -226,  -226,
    -226,   134,  -226,  -226,  -226,  -226,  -226,  -226,  -226,  -226,
     537,   347,  -226,  -226,    36,  -226,    93,  -226,  -226,  -226,
    -226,  -226,  -226,  -226,  -226,   158,  -226,  -226,  -226,   122,
    -226,  -226,  -226,  -226,   621,  -226,   177,   181,   189,   178,
     240,   241,   242,   218,   134,   219,  -226,   150,  -226,  -226,
    -226,  -226,  -226,  -226,  -226,  -226,  -226,  -226,    93,  -226,
     267,   182,   239,   216,   146,   -24,    48,    54,  -226,  -226,
     621,  -226,    85,   347,   134,  -226,   229,   226,   156,     4,
       4,     4,   621,   621,  -226,   231,  -226,  -226,  -226,  -226,
    -226,    50,   225,   401,   -19,  -226,    83,    85,  -226,  -226,
     140,   453,  -226,  -226,  -226,  -226,   621,  -226,  -226,   621,
    -226,  -226,  -226,  -226,   621,  -226,  -226,   621,   621,   621,
     621,   279,  -226,   267,  -226,  -226,   239,  -226,   105,    63,
      63,  -226,   239,  -226,   175,  -226,   621,   621,  -226,   239,
    -226,   239,  -226,    63,  -226,  -226,   218,  -226,    92,  -226,
     621,    -1,   273,   579,  -226,   621,  -226,    63,   239,  -226,
    -226,   223,   224,   228,   230,  -226,  -226,   621,  -226,  -226,
     244,   243,    63,  -226,  -226,  -226,  -226,   621,   621,  -226,
    -226,  -226,   180,  -226,   177,   181,   189,   178,   240,   241,
     289,    13,  -226,   267,  -226,   239,   239,  -226,    90,  -226,
     246,   -31,  -226,  -226,   239,  -226,   621,   252,   136,   645,
    -226,  -226,  -226,  -226,   121,  -226,   621,   621,   621,   621,
    -226,  -226,  -226,   236,  -226,  -226,  -226,   495,  -226,   253,
     254,  -226,  -226,  -226,  -226,  -226,  -226,  -226,   255,    63,
    -226,    63,  -226,  -226,  -226,  -226,  -226,  -226,   621,  -226,
     257,  -226,  -226,  -226,   107,  -226,   259,    33,  -226,  -226,
    -226,  -226,   239,  -226
  };

  const unsigned char
  parser::yydefact_[] =
  {
       3,     0,     0,     1,     0,     0,     0,     0,     2,     5,
      37,     0,    21,     4,     7,     0,     0,     6,     0,     8,
      36,    38,     0,     0,    11,     0,     0,     0,     0,     0,
       0,    20,     0,     0,    24,     0,     0,     0,     9,     0,
      13,    12,     0,     0,     0,     0,    22,     0,     0,     0,
       0,   188,     0,    19,    18,    14,    10,     0,     0,     0,
       0,   134,     0,     0,    16,   135,   136,   137,   138,   139,
     140,     0,   101,    69,    70,    71,    72,    39,    74,    73,
       0,     0,    99,   100,    63,    65,     0,    47,    15,    62,
      53,    54,    55,    86,    64,    66,    67,    56,    48,    97,
      87,    88,    89,   106,     0,    46,   110,   116,   120,   122,
     124,   126,   102,     0,   140,     0,   165,     0,    17,   164,
     166,   167,    41,    40,    23,    25,   177,   176,     0,   183,
       0,     0,     0,     0,     0,     0,     0,     0,   146,    42,
       0,   141,     0,     0,     0,    58,    47,     0,     0,     0,
       0,     0,     0,     0,    79,     0,    26,    27,    28,    29,
      30,    63,     0,     0,     0,   190,     0,    68,    76,    75,
       0,     0,    98,   103,   104,   105,     0,   108,   109,     0,
     112,   113,   114,   115,     0,   118,   119,     0,     0,     0,
       0,     0,    85,     0,   168,   189,   149,   151,     0,     0,
       0,   182,     0,   184,     0,   154,     0,     0,   148,     0,
     143,     0,   142,     0,   145,   156,   155,   157,     0,    44,
       0,    63,    77,     0,    57,     0,    60,     0,   175,   179,
     180,     0,     0,     0,     0,    35,    83,     0,    80,    81,
       0,     0,     0,    61,    92,    96,    95,     0,     0,    90,
     159,   162,     0,   107,   111,   117,   121,   123,   125,   127,
      93,     0,   150,     0,   153,     0,     0,   171,     0,   181,
       0,   155,   133,   132,     0,   147,     0,     0,     0,     0,
      59,    49,    50,   186,     0,   174,     0,     0,     0,     0,
     170,    84,    82,     0,   191,   160,   161,     0,    91,     0,
       0,   152,   172,   173,   185,   144,   158,    43,     0,     0,
      78,     0,   178,    31,    32,    33,    34,   163,     0,    94,
       0,    45,   187,    51,     0,   169,     0,     0,    52,   131,
     129,   130,     0,   128
  };

  const short
  parser::yypgoto_[] =
  {
    -226,  -226,  -226,  -226,   300,  -226,   274,   287,   -16,  -226,
    -226,  -226,  -226,  -226,   152,  -226,  -226,  -226,  -226,  -226,
      46,    -4,   -41,  -226,  -226,    20,   106,   -29,  -226,  -226,
     -66,    17,  -226,  -226,    39,   147,  -226,  -226,  -226,  -226,
    -226,  -226,  -226,  -226,  -226,  -101,  -226,  -226,  -226,   142,
    -226,   135,  -226,   137,  -226,   139,   141,   132,  -226,  -226,
    -226,  -226,     8,  -226,  -226,  -226,  -226,  -226,   110,    62,
    -226,  -226,   -38,    57,   114,    40,  -226,   -48,  -226,  -226,
    -226,    94,    67,  -225,   210,  -226,   104,  -226,  -226,  -226,
    -226,  -226,  -226
  };

  const short
  parser::yydefgoto_[] =
  {
      -1,     1,     2,     6,     7,     8,    17,    25,    26,    27,
       9,    18,    32,    33,   155,   156,   157,   158,   159,   160,
      61,    84,    30,    85,   124,    86,    87,   147,   148,   324,
      89,    90,    91,    92,    93,    94,    95,    96,    97,   163,
      98,    99,   100,   101,   102,   103,   104,   105,   176,   106,
     179,   107,   184,   108,   187,   109,   110,   111,   112,   326,
     332,   135,   113,    65,    66,    67,    68,   137,   138,   197,
     198,    69,    70,   217,   218,   251,   252,   118,   119,   120,
     121,   165,   203,   229,    51,   230,   231,   132,    36,   204,
     284,    52,   166
  };

  const short
  parser::yytable_[] =
  {
      11,   126,   283,   172,   116,   144,   114,    10,   116,    39,
      10,     4,    29,    47,    34,    88,    10,   191,    21,    37,
       5,    29,   209,    29,   115,   206,    39,   211,     3,   191,
     210,    50,    10,    20,    21,   212,    22,    23,    29,    62,
      48,    62,   114,   114,   125,    62,    62,   139,   192,    13,
     140,    64,   162,    10,    20,    62,   134,   227,   127,   142,
      57,    31,    28,    63,   237,   117,    10,   133,   136,   117,
      63,    28,    12,    28,    58,   253,   194,   161,   222,    63,
      63,    49,   167,    24,   139,    14,   322,   140,    28,   164,
      10,    20,    21,    10,   211,    23,    10,    20,   139,   329,
     213,   207,   212,    60,   245,   114,   330,   331,   214,   141,
      10,    20,   128,   142,   162,   237,     4,    57,   129,   199,
     200,    10,    20,    21,    50,   114,    23,   202,    62,   242,
      62,    58,   141,   219,   241,    16,   220,   243,   276,   221,
     205,    38,   208,   244,   277,   228,   228,   228,   216,    10,
      20,   263,    63,    10,    63,    21,    57,    62,    59,   264,
      60,   325,    19,    10,    20,    21,   170,   311,    23,   208,
      58,   171,    41,    40,    49,   312,   196,    73,    74,    75,
      76,    63,   276,    80,    35,    10,   146,   143,   308,    80,
     122,   123,    62,   143,   139,   265,   266,   207,    62,    60,
     168,   169,   225,    43,   262,    62,   226,    62,    44,   274,
     267,   199,   200,   300,    56,   271,    63,   272,    45,   273,
     116,   268,    63,   228,    62,   269,   297,   130,   216,    63,
     298,    63,   201,   173,   174,   175,   285,    46,   293,   261,
     177,   178,    10,    20,   185,   186,   215,    53,    63,    57,
     180,   181,   182,   183,   232,   233,    55,    62,   234,   235,
     131,    62,    62,    58,   202,   188,   191,   189,   193,   190,
      62,    20,   206,   302,   303,   223,   224,   250,   236,   238,
     114,   117,   208,   260,   216,    63,    63,   279,   286,   287,
      59,   291,    60,   288,    63,   289,   299,   292,   305,   309,
     307,   237,   318,   321,   320,   167,   328,   228,    15,   196,
     323,    54,   270,   215,    42,   240,   319,   246,   310,   255,
      62,   254,   259,   275,   256,   301,   215,   257,    62,   281,
     258,   282,   327,   306,   278,   304,   294,   317,   195,     0,
     333,     0,     0,   290,    63,     0,     0,     0,     0,     0,
      10,    20,    63,   295,   296,     0,     0,    57,     0,    71,
       0,     0,     0,     0,     0,     0,     0,   149,   150,   151,
     152,    58,     0,     0,     0,    72,     0,     0,   153,     0,
       0,     0,   215,     0,    73,    74,    75,    76,    77,    78,
      79,     0,   313,   314,   315,   316,    80,     0,    59,     0,
      81,   154,     0,   250,    10,    20,    82,    83,     0,     0,
       0,    57,     0,    71,     0,     0,     0,     0,     0,     0,
       0,   149,   150,   151,   152,    58,     0,     0,     0,    72,
       0,     0,   153,     0,     0,     0,     0,     0,    73,    74,
      75,    76,    77,    78,    79,     0,     0,     0,     0,     0,
      80,     0,    59,     0,    81,   239,    10,    20,     0,     0,
      82,    83,     0,    57,     0,    71,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    58,     0,     0,
       0,    72,   247,   248,     0,     0,     0,     0,     0,     0,
      73,    74,    75,    76,    77,    78,    79,     0,    10,    20,
       0,     0,    80,   249,    59,    57,    81,    71,     0,     0,
       0,     0,    82,    83,     0,     0,     0,     0,     0,    58,
       0,     0,     0,    72,   247,   248,     0,     0,     0,     0,
       0,     0,    73,    74,    75,    76,    77,    78,    79,     0,
      10,    20,     0,     0,    80,     0,    59,    57,    81,    71,
       0,     0,     0,     0,    82,    83,     0,     0,     0,     0,
       0,    58,     0,     0,     0,    72,     0,     0,     0,     0,
       0,     0,     0,     0,    73,    74,    75,    76,    77,    78,
      79,     0,    10,    20,     0,     0,    80,   145,    59,    57,
      81,    71,     0,     0,     0,     0,    82,    83,     0,     0,
       0,     0,     0,    58,     0,     0,     0,    72,     0,     0,
       0,     0,     0,     0,     0,     0,    73,    74,    75,    76,
      77,    78,    79,     0,    10,    20,     0,     0,    80,   280,
      59,    57,    81,    71,     0,     0,     0,     0,    82,    83,
       0,     0,     0,     0,     0,    58,     0,     0,    10,    72,
       0,     0,     0,     0,     0,     0,     0,    71,    73,    74,
      75,    76,    77,    78,    79,     0,     0,     0,     0,     0,
      80,     0,    59,     0,    81,     0,     0,     0,     0,     0,
      82,    83,    73,    74,    75,    76,    77,    78,    79,     0,
       0,     0,     0,     0,    80,     0,     0,     0,   143
  };

  const short
  parser::yycheck_[] =
  {
       4,    49,   227,   104,    45,    71,    44,     3,    49,    25,
       3,     8,    16,    19,    18,    44,     3,    48,     5,    23,
      17,    25,    46,    27,    11,    56,    42,    46,     0,    48,
      54,    35,     3,     4,     5,    54,     7,     8,    42,    43,
      46,    45,    80,    81,    48,    49,    50,    48,   114,    47,
      51,    43,    81,     3,     4,    59,    60,    53,    50,    63,
      10,    54,    16,    43,    65,    45,     3,    59,    60,    49,
      50,    25,    53,    27,    24,   176,   117,    81,   144,    59,
      60,    35,    86,    54,    48,    47,   311,    51,    42,    81,
       3,     4,     5,     3,    46,     8,     3,     4,    48,    66,
      46,    51,    54,    53,   170,   143,    73,    74,    54,    63,
       3,     4,    46,   117,   143,    65,     8,    10,    52,    29,
      30,     3,     4,     5,   128,   163,     8,   131,   132,    46,
     134,    24,    86,    48,   163,    53,    51,    54,    46,   143,
     132,    54,   134,     3,    52,   149,   150,   151,   140,     3,
       4,    46,   132,     3,   134,     5,    10,   161,    51,    54,
      53,    54,    47,     3,     4,     5,    44,    46,     8,   161,
      24,    49,    54,    47,   128,    54,   130,    37,    38,    39,
      40,   161,    46,    49,    51,     3,    80,    53,    52,    49,
      42,    43,   196,    53,    48,   199,   200,    51,   202,    53,
      42,    43,    46,    65,   196,   209,    50,   211,    65,   213,
     202,    29,    30,   261,    54,   207,   196,   209,    65,   211,
     261,    46,   202,   227,   228,    50,    46,    53,   220,   209,
      50,   211,    50,    56,    57,    58,   228,    47,   242,   193,
      59,    60,     3,     4,    66,    67,   140,    47,   228,    10,
      61,    62,    63,    64,   150,   151,    47,   261,   152,   153,
      49,   265,   266,    24,   268,    25,    48,    26,    49,    27,
     274,     4,    56,   265,   266,    46,    50,   171,    47,    54,
     318,   261,   274,     4,   276,   265,   266,    14,    65,    65,
      51,    47,    53,    65,   274,    65,     7,    54,    52,   279,
      48,    65,    49,    48,    50,   309,    47,   311,     8,   263,
      53,    37,   206,   207,    27,   163,   299,   170,   279,   184,
     324,   179,   190,   213,   187,   263,   220,   188,   332,   223,
     189,   225,   324,   276,   220,   268,   242,   297,   128,    -1,
     332,    -1,    -1,   237,   324,    -1,    -1,    -1,    -1,    -1,
       3,     4,   332,   247,   248,    -1,    -1,    10,    -1,    12,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    20,    21,    22,
      23,    24,    -1,    -1,    -1,    28,    -1,    -1,    31,    -1,
      -1,    -1,   276,    -1,    37,    38,    39,    40,    41,    42,
      43,    -1,   286,   287,   288,   289,    49,    -1,    51,    -1,
      53,    54,    -1,   297,     3,     4,    59,    60,    -1,    -1,
      -1,    10,    -1,    12,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    20,    21,    22,    23,    24,    -1,    -1,    -1,    28,
      -1,    -1,    31,    -1,    -1,    -1,    -1,    -1,    37,    38,
      39,    40,    41,    42,    43,    -1,    -1,    -1,    -1,    -1,
      49,    -1,    51,    -1,    53,    54,     3,     4,    -1,    -1,
      59,    60,    -1,    10,    -1,    12,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    24,    -1,    -1,
      -1,    28,    29,    30,    -1,    -1,    -1,    -1,    -1,    -1,
      37,    38,    39,    40,    41,    42,    43,    -1,     3,     4,
      -1,    -1,    49,    50,    51,    10,    53,    12,    -1,    -1,
      -1,    -1,    59,    60,    -1,    -1,    -1,    -1,    -1,    24,
      -1,    -1,    -1,    28,    29,    30,    -1,    -1,    -1,    -1,
      -1,    -1,    37,    38,    39,    40,    41,    42,    43,    -1,
       3,     4,    -1,    -1,    49,    -1,    51,    10,    53,    12,
      -1,    -1,    -1,    -1,    59,    60,    -1,    -1,    -1,    -1,
      -1,    24,    -1,    -1,    -1,    28,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    37,    38,    39,    40,    41,    42,
      43,    -1,     3,     4,    -1,    -1,    49,    50,    51,    10,
      53,    12,    -1,    -1,    -1,    -1,    59,    60,    -1,    -1,
      -1,    -1,    -1,    24,    -1,    -1,    -1,    28,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    37,    38,    39,    40,
      41,    42,    43,    -1,     3,     4,    -1,    -1,    49,    50,
      51,    10,    53,    12,    -1,    -1,    -1,    -1,    59,    60,
      -1,    -1,    -1,    -1,    -1,    24,    -1,    -1,     3,    28,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    12,    37,    38,
      39,    40,    41,    42,    43,    -1,    -1,    -1,    -1,    -1,
      49,    -1,    51,    -1,    53,    -1,    -1,    -1,    -1,    -1,
      59,    60,    37,    38,    39,    40,    41,    42,    43,    -1,
      -1,    -1,    -1,    -1,    49,    -1,    -1,    -1,    53
  };

  const unsigned char
  parser::yystos_[] =
  {
       0,    77,    78,     0,     8,    17,    79,    80,    81,    86,
       3,    97,    53,    47,    47,    80,    53,    82,    87,    47,
       4,     5,     7,     8,    54,    83,    84,    85,    96,    97,
      98,    54,    88,    89,    97,    51,   164,    97,    54,    84,
      47,    54,    83,    65,    65,    65,    47,    19,    46,    96,
      97,   160,   167,    47,    82,    47,    54,    10,    24,    51,
      53,    96,    97,   101,   138,   139,   140,   141,   142,   147,
     148,    12,    28,    37,    38,    39,    40,    41,    42,    43,
      49,    53,    59,    60,    97,    99,   101,   102,   103,   106,
     107,   108,   109,   110,   111,   112,   113,   114,   116,   117,
     118,   119,   120,   121,   122,   123,   125,   127,   129,   131,
     132,   133,   134,   138,   148,    11,    98,   101,   153,   154,
     155,   156,    42,    43,   100,    97,   153,   138,    46,    52,
      53,    49,   163,   138,    97,   137,   138,   143,   144,    48,
      51,    96,    97,    53,   106,    50,   102,   103,   104,    20,
      21,    22,    23,    31,    54,    90,    91,    92,    93,    94,
      95,    97,   103,   115,   138,   157,   168,    97,    42,    43,
      44,    49,   121,    56,    57,    58,   124,    59,    60,   126,
      61,    62,    63,    64,   128,    66,    67,   130,    25,    26,
      27,    48,   106,    49,    98,   160,    96,   145,   146,    29,
      30,    50,    97,   158,   165,   138,    56,    51,   138,    46,
      54,    46,    54,    46,    54,   102,   138,   149,   150,    48,
      51,    97,   106,    46,    50,    46,    50,    53,    97,   159,
     161,   162,   162,   162,   102,   102,    47,    65,    54,    54,
      90,   103,    46,    54,     3,   106,   111,    29,    30,    50,
     102,   151,   152,   121,   125,   127,   129,   131,   132,   133,
       4,    96,   138,    46,    54,    97,    97,   138,    46,    50,
     102,   138,   138,   138,    97,   144,    46,    52,   150,    14,
      50,   102,   102,   159,   166,   138,    65,    65,    65,    65,
     102,    47,    54,    97,   157,   102,   102,    46,    50,     7,
     153,   145,   138,   138,   158,    52,   149,    48,    52,   101,
     110,    46,    54,   102,   102,   102,   102,   151,    49,   107,
      50,    48,   159,    53,   105,    54,   135,   138,    47,    66,
      73,    74,   136,   138
  };

  const unsigned char
  parser::yyr1_[] =
  {
       0,    76,    77,    78,    78,    79,    80,    81,    81,    82,
      82,    82,    82,    83,    83,    84,    84,    84,    84,    85,
      86,    87,    87,    88,    89,    89,    90,    90,    90,    90,
      90,    91,    92,    93,    94,    95,    96,    97,    98,    99,
     100,   100,   101,   101,   101,   101,   102,   103,   103,   104,
     104,   105,   105,   106,   106,   106,   106,   107,   108,   108,
     108,   109,   110,   110,   110,   110,   110,   110,   110,   111,
     111,   111,   111,   112,   112,   112,   112,   113,   113,   114,
     114,   114,   114,   115,   115,   116,   117,   117,   117,   117,
     118,   118,   119,   119,   119,   120,   120,   121,   121,   122,
     122,   122,   123,   124,   124,   124,   125,   125,   126,   126,
     127,   127,   128,   128,   128,   128,   129,   129,   130,   130,
     131,   131,   132,   132,   133,   133,   134,   134,   135,   136,
     136,   136,   137,   137,   138,   138,   138,   138,   138,   138,
     138,   139,   140,   140,   141,   142,   143,   143,   144,   145,
     145,   146,   146,   147,   148,   149,   149,   150,   150,   151,
     151,   151,   152,   152,   153,   154,   154,   154,   155,   156,
     157,   158,   158,   158,   159,   159,   160,   160,   161,   162,
     162,   163,   163,   164,   165,   165,   166,   166,   167,   167,
     168,   168
  };

  const signed char
  parser::yyr2_[] =
  {
       0,     2,     2,     0,     3,     1,     3,     2,     3,     3,
       4,     2,     3,     2,     3,     3,     3,     3,     3,     3,
       4,     0,     3,     3,     1,     3,     1,     1,     1,     1,
       1,     4,     4,     4,     4,     2,     1,     1,     1,     1,
       1,     1,     2,     5,     3,     6,     1,     1,     1,     3,
       3,     0,     3,     1,     1,     1,     1,     3,     2,     4,
       3,     3,     1,     1,     1,     1,     1,     1,     2,     1,
       1,     1,     1,     1,     1,     2,     2,     3,     5,     2,
       3,     3,     4,     2,     3,     2,     1,     1,     1,     1,
       3,     4,     3,     3,     5,     3,     3,     1,     2,     1,
       1,     1,     1,     1,     1,     1,     1,     3,     1,     1,
       1,     3,     1,     1,     1,     1,     1,     3,     1,     1,
       1,     3,     1,     3,     1,     3,     1,     3,     3,     1,
       1,     1,     3,     3,     1,     1,     1,     1,     1,     1,
       1,     2,     3,     3,     5,     3,     1,     3,     2,     1,
       2,     1,     3,     4,     3,     1,     1,     1,     3,     1,
       2,     2,     1,     3,     1,     1,     1,     1,     2,     8,
       3,     2,     3,     3,     2,     1,     2,     2,     3,     1,
       1,     3,     2,     3,     1,     3,     1,     3,     1,     3,
       1,     3
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
  "\"else\"", "\"match\"", "\"with\"", "\"imports\"", "\"package-content\"",
  "\"from\"", "\"const\"", "\"val\"", "\"var\"", "\"set\"", "\"fn\"",
  "\"and\"", "\"xor\"", "\"or\"", "\"not\"", "\"out\"", "\"inout\"",
  "\"discard\"", "\"as\"", "\"for\"", "\"CORE_PROFILE\"",
  "\"BROWSER_PROFILE\"", "\"NATIVE_PROFILE\"", "\"42\"", "\"0x2a\"",
  "\"42u\"", "\"0x2Au\"", "\"4.2\"", "\"\\\"dq-string-literal\\\"\"",
  "\"'sq-string-literal'\"", "\".\"", "\":\"", "\",\"", "\";\"", "\"::\"",
  "\"(\"", "\")\"", "\"[\"", "\"]\"", "\"{\"", "\"}\"", "\"->\"", "\"*\"",
  "\"/\"", "\"%\"", "\"+\"", "\"-\"", "\"<\"", "\"<=\"", "\">\"", "\">=\"",
  "\"=\"", "\"==\"", "\"!=\"", "\"^\"", "\"&\"", "\"!\"", "\"|\"",
  "\"EOS\"", "\":<\"", "\">:\"", "\"<null>\"", "$accept", "script",
  "script_header", "script_header_stmt", "script_field", "script_field_sl",
  "mod_exp", "mod_field_sl", "mod_field", "using_tpattern", "import_stmt",
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
       0,   279,   279,   287,   288,   291,   295,   298,   299,   307,
     308,   309,   310,   313,   314,   317,   318,   319,   320,   323,
     331,   336,   337,   340,   343,   344,   348,   349,   350,   351,
     352,   355,   358,   361,   364,   367,   374,   375,   376,   379,
     382,   383,   386,   387,   388,   389,   396,   399,   400,   412,
     413,   416,   417,   421,   422,   423,   424,   435,   438,   439,
     440,   443,   446,   447,   448,   449,   450,   451,   452,   455,
     456,   457,   458,   461,   462,   463,   464,   467,   468,   471,
     472,   473,   474,   477,   478,   481,   485,   486,   487,   488,
     491,   492,   495,   496,   497,   500,   501,   505,   506,   509,
     510,   511,   515,   518,   519,   520,   523,   524,   527,   528,
     531,   532,   535,   536,   537,   538,   541,   542,   545,   546,
     549,   550,   553,   554,   557,   558,   561,   562,   566,   569,
     570,   571,   586,   587,   591,   592,   593,   594,   595,   596,
     597,   601,   605,   606,   609,   613,   616,   617,   620,   624,
     625,   628,   629,   632,   635,   638,   639,   642,   643,   645,
     646,   647,   650,   651,   661,   664,   665,   666,   669,   674,
     684,   687,   688,   689,   692,   693,   696,   697,   701,   704,
     705,   708,   709,   712,   716,   717,   720,   721,   724,   725,
     728,   729
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
      75
    };
    // Last valid token kind.
    const int code_max = 330;

    if (t <= 0)
      return symbol_kind::S_YYEOF;
    else if (t <= code_max)
      return YY_CAST (symbol_kind_type, translate_table[t]);
    else
      return symbol_kind::S_YYUNDEF;
  }

#line 11 "parser.yy"
} } // pdm::parser
#line 4161 "parser.tab.cc"

#line 732 "parser.yy"


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
