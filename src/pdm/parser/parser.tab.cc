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
      case symbol_kind::S_long_type_spec: // long_type_spec
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

      case symbol_kind::S_type_query_exp_sl: // type_query_exp_sl
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
      case symbol_kind::S_long_type_spec: // long_type_spec
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

      case symbol_kind::S_type_query_exp_sl: // type_query_exp_sl
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
      case symbol_kind::S_long_type_spec: // long_type_spec
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

      case symbol_kind::S_type_query_exp_sl: // type_query_exp_sl
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
      case symbol_kind::S_long_type_spec: // long_type_spec
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

      case symbol_kind::S_type_query_exp_sl: // type_query_exp_sl
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
      case symbol_kind::S_long_type_spec: // long_type_spec
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

      case symbol_kind::S_type_query_exp_sl: // type_query_exp_sl
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
      case symbol_kind::S_long_type_spec: // long_type_spec
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

      case symbol_kind::S_type_query_exp_sl: // type_query_exp_sl
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
      case symbol_kind::S_long_type_spec: // long_type_spec
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

      case symbol_kind::S_type_query_exp_sl: // type_query_exp_sl
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
#line 271 "parser.yy"
                                      {
    yylhs.value.as < pdm::ast::Script* > () = mgr->new_script(source, yylhs.location, std::move(yystack_[1].value.as < std::vector<pdm::ast::HeaderStmt*> > ()), std::move(yystack_[0].value.as < std::vector<pdm::ast::Script::Field*> > ()));

    // setting the returnp here => this is the node parser returns.  
    *returnp = yylhs.value.as < pdm::ast::Script* > (); 
}
#line 2237 "parser.tab.cc"
    break;

  case 3: // script_header: %empty
#line 279 "parser.yy"
                                                    { yylhs.value.as < std::vector<pdm::ast::HeaderStmt*> > ().reserve(16); }
#line 2243 "parser.tab.cc"
    break;

  case 4: // script_header: script_header script_header_stmt ";"
#line 280 "parser.yy"
                                                    { yylhs.value.as < std::vector<pdm::ast::HeaderStmt*> > () = std::move(yystack_[2].value.as < std::vector<pdm::ast::HeaderStmt*> > ()); yylhs.value.as < std::vector<pdm::ast::HeaderStmt*> > ().push_back(yystack_[1].value.as < pdm::ast::HeaderStmt* > ()); }
#line 2249 "parser.tab.cc"
    break;

  case 5: // script_header_stmt: import_stmt
#line 283 "parser.yy"
      { yylhs.value.as < pdm::ast::HeaderStmt* > () = yystack_[0].value.as < pdm::ast::HeaderStmt* > (); }
#line 2255 "parser.tab.cc"
    break;

  case 6: // script_field: "mod" vid mod_exp
#line 287 "parser.yy"
                          { yylhs.value.as < pdm::ast::Script::Field* > () = mgr->new_script_field(yylhs.location, yystack_[1].value.as < TokenInfo > ().ID_intstr, yystack_[0].value.as < pdm::ast::ModExp* > ()); }
#line 2261 "parser.tab.cc"
    break;

  case 7: // script_field_sl: script_field ";"
#line 290 "parser.yy"
                                                { yylhs.value.as < std::vector<pdm::ast::Script::Field*> > ().push_back(yystack_[1].value.as < pdm::ast::Script::Field* > ()); }
#line 2267 "parser.tab.cc"
    break;

  case 8: // script_field_sl: script_field_sl script_field ";"
#line 291 "parser.yy"
                                                { yylhs.value.as < std::vector<pdm::ast::Script::Field*> > () = std::move(yystack_[2].value.as < std::vector<pdm::ast::Script::Field*> > ()); yylhs.value.as < std::vector<pdm::ast::Script::Field*> > ().push_back(yystack_[1].value.as < pdm::ast::Script::Field* > ()); }
#line 2273 "parser.tab.cc"
    break;

  case 9: // mod_exp: "{" mod_field_sl "}"
#line 299 "parser.yy"
                                              { yylhs.value.as < pdm::ast::ModExp* > () = mgr->new_mod_exp(yylhs.location, nullptr, std::move(yystack_[1].value.as < std::vector<pdm::ast::ModExp::Field*> > ())); }
#line 2279 "parser.tab.cc"
    break;

  case 10: // mod_exp: tpattern "{" mod_field_sl "}"
#line 300 "parser.yy"
                                              { yylhs.value.as < pdm::ast::ModExp* > () = mgr->new_mod_exp(yylhs.location, yystack_[3].value.as < pdm::ast::TPattern* > (), std::move(yystack_[1].value.as < std::vector<pdm::ast::ModExp::Field*> > ())); }
#line 2285 "parser.tab.cc"
    break;

  case 11: // mod_exp: "{" "}"
#line 301 "parser.yy"
                                              { yylhs.value.as < pdm::ast::ModExp* > () = mgr->new_mod_exp(yylhs.location, nullptr, std::move(std::vector<ast::ModExp::Field*>{})); }
#line 2291 "parser.tab.cc"
    break;

  case 12: // mod_exp: tpattern "{" "}"
#line 302 "parser.yy"
                                              { yylhs.value.as < pdm::ast::ModExp* > () = mgr->new_mod_exp(yylhs.location, yystack_[2].value.as < pdm::ast::TPattern* > (), std::move(std::vector<ast::ModExp::Field*>{})); }
#line 2297 "parser.tab.cc"
    break;

  case 13: // mod_field_sl: mod_field ";"
#line 305 "parser.yy"
                                        { yylhs.value.as < std::vector<pdm::ast::ModExp::Field*> > ().push_back(yystack_[1].value.as < pdm::ast::ModExp::Field* > ()); }
#line 2303 "parser.tab.cc"
    break;

  case 14: // mod_field_sl: mod_field_sl mod_field ";"
#line 306 "parser.yy"
                                        { yylhs.value.as < std::vector<pdm::ast::ModExp::Field*> > () = std::move(yystack_[2].value.as < std::vector<pdm::ast::ModExp::Field*> > ()); yylhs.value.as < std::vector<pdm::ast::ModExp::Field*> > ().push_back(yystack_[1].value.as < pdm::ast::ModExp::Field* > ()); }
#line 2309 "parser.tab.cc"
    break;

  case 15: // mod_field: vid "::" long_exp
#line 309 "parser.yy"
                                    { yylhs.value.as < pdm::ast::ModExp::Field* > () = mgr->new_value_mod_field(yylhs.location, yystack_[2].value.as < TokenInfo > ().ID_intstr, yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2315 "parser.tab.cc"
    break;

  case 16: // mod_field: tid "::" long_type_spec
#line 310 "parser.yy"
                                         { yylhs.value.as < pdm::ast::ModExp::Field* > () = mgr->new_type_mod_field(yylhs.location, yystack_[2].value.as < TokenInfo > ().ID_intstr, yystack_[0].value.as < pdm::ast::TypeSpec* > ()); }
#line 2321 "parser.tab.cc"
    break;

  case 17: // mod_field: cid "::" class_exp_class_spec
#line 311 "parser.yy"
                                         { yylhs.value.as < pdm::ast::ModExp::Field* > () = mgr->new_class_mod_field(yylhs.location, yystack_[2].value.as < TokenInfo > ().ID_intstr, yystack_[0].value.as < pdm::ast::ClassSpec* > ()); }
#line 2327 "parser.tab.cc"
    break;

  case 18: // mod_field: "mod" vid mod_exp
#line 312 "parser.yy"
                                    { yylhs.value.as < pdm::ast::ModExp::Field* > () = mgr->new_mod_mod_field(yylhs.location, yystack_[1].value.as < TokenInfo > ().ID_intstr, yystack_[0].value.as < pdm::ast::ModExp* > ()); }
#line 2333 "parser.tab.cc"
    break;

  case 19: // import_stmt: "mod" vid "from" stringl "as" stringl
#line 320 "parser.yy"
                                                  { yylhs.value.as < pdm::ast::HeaderStmt* > () = mgr->new_import_stmt(yylhs.location, yystack_[4].value.as < TokenInfo > ().ID_intstr, *yystack_[2].value.as < TokenInfo > ().String_utf8string, *yystack_[0].value.as < TokenInfo > ().String_utf8string); }
#line 2339 "parser.tab.cc"
    break;

  case 20: // chain_prefix_stmt: const_stmt
#line 324 "parser.yy"
      { yylhs.value.as < pdm::ast::Stmt* > () = yystack_[0].value.as < pdm::ast::Stmt* > (); }
#line 2345 "parser.tab.cc"
    break;

  case 21: // chain_prefix_stmt: val_stmt
#line 325 "parser.yy"
      { yylhs.value.as < pdm::ast::Stmt* > () = yystack_[0].value.as < pdm::ast::Stmt* > (); }
#line 2351 "parser.tab.cc"
    break;

  case 22: // chain_prefix_stmt: var_stmt
#line 326 "parser.yy"
      { yylhs.value.as < pdm::ast::Stmt* > () = yystack_[0].value.as < pdm::ast::Stmt* > (); }
#line 2357 "parser.tab.cc"
    break;

  case 23: // chain_prefix_stmt: set_stmt
#line 327 "parser.yy"
      { yylhs.value.as < pdm::ast::Stmt* > () = yystack_[0].value.as < pdm::ast::Stmt* > (); }
#line 2363 "parser.tab.cc"
    break;

  case 24: // chain_prefix_stmt: discard_stmt
#line 328 "parser.yy"
      { yylhs.value.as < pdm::ast::Stmt* > () = yystack_[0].value.as < pdm::ast::Stmt* > (); }
#line 2369 "parser.tab.cc"
    break;

  case 25: // const_stmt: "const" lpattern "=" expr
#line 331 "parser.yy"
                                  { yylhs.value.as < pdm::ast::Stmt* > () = mgr->new_const_stmt(yylhs.location, yystack_[2].value.as < pdm::ast::LPattern* > (), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2375 "parser.tab.cc"
    break;

  case 26: // val_stmt: "val" lpattern "=" expr
#line 334 "parser.yy"
                                  { yylhs.value.as < pdm::ast::Stmt* > () = mgr->new_val_stmt(yylhs.location, yystack_[2].value.as < pdm::ast::LPattern* > (), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2381 "parser.tab.cc"
    break;

  case 27: // var_stmt: "var" lpattern "=" expr
#line 337 "parser.yy"
                                  { yylhs.value.as < pdm::ast::Stmt* > () = mgr->new_var_stmt(yylhs.location, yystack_[2].value.as < pdm::ast::LPattern* > (), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2387 "parser.tab.cc"
    break;

  case 28: // set_stmt: "set" expr "=" expr
#line 340 "parser.yy"
                              { yylhs.value.as < pdm::ast::Stmt* > () = mgr->new_set_stmt(yylhs.location, yystack_[2].value.as < pdm::ast::Exp* > (), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2393 "parser.tab.cc"
    break;

  case 29: // discard_stmt: "discard" expr
#line 343 "parser.yy"
                        { yylhs.value.as < pdm::ast::Stmt* > () = mgr->new_discard_stmt(yylhs.location, yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2399 "parser.tab.cc"
    break;

  case 30: // tid: "TypeId"
#line 350 "parser.yy"
     { yylhs.value.as < TokenInfo > () = yystack_[0].value.as < TokenInfo > (); }
#line 2405 "parser.tab.cc"
    break;

  case 31: // vid: "val_id"
#line 351 "parser.yy"
     { yylhs.value.as < TokenInfo > () = yystack_[0].value.as < TokenInfo > (); }
#line 2411 "parser.tab.cc"
    break;

  case 32: // cid: "CLS_ID"
#line 352 "parser.yy"
     { yylhs.value.as < TokenInfo > () = yystack_[0].value.as < TokenInfo > (); }
#line 2417 "parser.tab.cc"
    break;

  case 33: // floatl: "4.2"
#line 355 "parser.yy"
      { yylhs.value.as < TokenInfo > () = yystack_[0].value.as < TokenInfo > (); }
#line 2423 "parser.tab.cc"
    break;

  case 34: // stringl: "'sq-string-literal'"
#line 358 "parser.yy"
      { yylhs.value.as < TokenInfo > () = yystack_[0].value.as < TokenInfo > (); }
#line 2429 "parser.tab.cc"
    break;

  case 35: // stringl: "\"dq-string-literal\""
#line 359 "parser.yy"
      { yylhs.value.as < TokenInfo > () = yystack_[0].value.as < TokenInfo > (); }
#line 2435 "parser.tab.cc"
    break;

  case 36: // mod_prefix: vid "::"
#line 362 "parser.yy"
                                                      { yylhs.value.as < pdm::ast::ModAddress* > () = mgr->new_mod_address(yylhs.location, nullptr, yystack_[1].value.as < TokenInfo > ().ID_intstr, std::move(std::vector<ast::TArg*>{})); }
#line 2441 "parser.tab.cc"
    break;

  case 37: // mod_prefix: vid "[" targ_cl "]" "::"
#line 363 "parser.yy"
                                                      { yylhs.value.as < pdm::ast::ModAddress* > () = mgr->new_mod_address(yylhs.location, nullptr, yystack_[4].value.as < TokenInfo > ().ID_intstr, std::move(yystack_[2].value.as < std::vector<pdm::ast::TArg*> > ())); }
#line 2447 "parser.tab.cc"
    break;

  case 38: // mod_prefix: mod_prefix vid "::"
#line 364 "parser.yy"
                                                      { yylhs.value.as < pdm::ast::ModAddress* > () = mgr->new_mod_address(yylhs.location, yystack_[2].value.as < pdm::ast::ModAddress* > (), yystack_[1].value.as < TokenInfo > ().ID_intstr, std::move(std::vector<ast::TArg*>{})); }
#line 2453 "parser.tab.cc"
    break;

  case 39: // mod_prefix: mod_prefix vid "[" targ_cl "]" "::"
#line 365 "parser.yy"
                                                      { yylhs.value.as < pdm::ast::ModAddress* > () = mgr->new_mod_address(yylhs.location, yystack_[5].value.as < pdm::ast::ModAddress* > (), yystack_[4].value.as < TokenInfo > ().ID_intstr, std::move(yystack_[2].value.as < std::vector<pdm::ast::TArg*> > ())); }
#line 2459 "parser.tab.cc"
    break;

  case 40: // expr: binary_exp
#line 372 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2465 "parser.tab.cc"
    break;

  case 41: // long_exp: expr
#line 375 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2471 "parser.tab.cc"
    break;

  case 42: // long_exp: lambda_exp
#line 376 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2477 "parser.tab.cc"
    break;

  case 43: // expr_cl2: expr "," expr
#line 388 "parser.yy"
                             { yylhs.value.as < std::vector<pdm::ast::Exp*> > ().reserve(2); yylhs.value.as < std::vector<pdm::ast::Exp*> > ().push_back(yystack_[2].value.as < pdm::ast::Exp* > ()); yylhs.value.as < std::vector<pdm::ast::Exp*> > ().push_back(yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2483 "parser.tab.cc"
    break;

  case 44: // expr_cl2: expr_cl2 "," expr
#line 389 "parser.yy"
                             { yylhs.value.as < std::vector<pdm::ast::Exp*> > () = std::move(yystack_[2].value.as < std::vector<pdm::ast::Exp*> > ()); yylhs.value.as < std::vector<pdm::ast::Exp*> > ().push_back(yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2489 "parser.tab.cc"
    break;

  case 45: // type_query_exp_sl: type_query_exp ";"
#line 392 "parser.yy"
                                       { yylhs.value.as < std::vector<pdm::ast::TypeQueryExp*> > ().push_back(yystack_[1].value.as < pdm::ast::TypeQueryExp* > ()); }
#line 2495 "parser.tab.cc"
    break;

  case 46: // type_query_exp_sl: type_query_exp_sl type_query_exp ";"
#line 393 "parser.yy"
                                                 { yylhs.value.as < std::vector<pdm::ast::TypeQueryExp*> > () = std::move(yystack_[2].value.as < std::vector<pdm::ast::TypeQueryExp*> > ()); yylhs.value.as < std::vector<pdm::ast::TypeQueryExp*> > ().push_back(yystack_[1].value.as < pdm::ast::TypeQueryExp* > ()); }
#line 2501 "parser.tab.cc"
    break;

  case 47: // bracketed_exp: paren_exp
#line 397 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2507 "parser.tab.cc"
    break;

  case 48: // bracketed_exp: vtupleExpr
#line 398 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2513 "parser.tab.cc"
    break;

  case 49: // bracketed_exp: vstructExpr
#line 399 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2519 "parser.tab.cc"
    break;

  case 50: // bracketed_exp: chain_exp
#line 400 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2525 "parser.tab.cc"
    break;

  case 51: // paren_exp: "(" long_exp ")"
#line 411 "parser.yy"
                              { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_paren_exp(yylhs.location, yystack_[1].value.as < pdm::ast::Exp* > ()); }
#line 2531 "parser.tab.cc"
    break;

  case 52: // vtupleExpr: "(" ")"
#line 414 "parser.yy"
                                   { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_tuple_exp(yylhs.location, std::move(std::vector<ast::Exp*>())); }
#line 2537 "parser.tab.cc"
    break;

  case 53: // vtupleExpr: "(" expr "," ")"
#line 415 "parser.yy"
                                   { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_tuple_exp(yylhs.location, std::move(std::vector(1,yystack_[2].value.as < pdm::ast::Exp* > ()))); }
#line 2543 "parser.tab.cc"
    break;

  case 54: // vtupleExpr: "(" expr_cl2 ")"
#line 416 "parser.yy"
                                   { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_tuple_exp(yylhs.location, std::move(yystack_[1].value.as < std::vector<pdm::ast::Exp*> > ())); }
#line 2549 "parser.tab.cc"
    break;

  case 55: // vstructExpr: "{" struct_exp_field_cl "}"
#line 419 "parser.yy"
                                            { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_struct_exp(yylhs.location, std::move(yystack_[1].value.as < std::vector<pdm::ast::StructExp::Field*> > ())); }
#line 2555 "parser.tab.cc"
    break;

  case 56: // primary_exp: bracketed_exp
#line 422 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2561 "parser.tab.cc"
    break;

  case 57: // primary_exp: vid
#line 423 "parser.yy"
                     { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_id_exp(yylhs.location, yystack_[0].value.as < TokenInfo > ().ID_intstr); }
#line 2567 "parser.tab.cc"
    break;

  case 58: // primary_exp: int_expr
#line 424 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2573 "parser.tab.cc"
    break;

  case 59: // primary_exp: floatl
#line 425 "parser.yy"
                     { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_float_exp(yylhs.location, yystack_[0].value.as < TokenInfo > ().Float); }
#line 2579 "parser.tab.cc"
    break;

  case 60: // primary_exp: stringls
#line 426 "parser.yy"
                     { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_string_exp(yylhs.location, std::move(yystack_[0].value.as < std::vector<pdm::ast::StringExp::Piece> > ())); }
#line 2585 "parser.tab.cc"
    break;

  case 61: // primary_exp: if_exp
#line 427 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2591 "parser.tab.cc"
    break;

  case 62: // primary_exp: mod_prefix vid
#line 428 "parser.yy"
                        { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_module_dot_name_exp(yylhs.location, yystack_[1].value.as < pdm::ast::ModAddress* > (), yystack_[0].value.as < TokenInfo > ().ID_intstr); }
#line 2597 "parser.tab.cc"
    break;

  case 63: // int_expr: "42"
#line 431 "parser.yy"
                { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_int_exp(yylhs.location, yystack_[0].value.as < TokenInfo > ().Int, ast::IntExp::Base::Dec, false); }
#line 2603 "parser.tab.cc"
    break;

  case 64: // int_expr: "0x2a"
#line 432 "parser.yy"
                { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_int_exp(yylhs.location, yystack_[0].value.as < TokenInfo > ().Int, ast::IntExp::Base::Hex, false); }
#line 2609 "parser.tab.cc"
    break;

  case 65: // int_expr: "42u"
#line 433 "parser.yy"
                         { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_int_exp(yylhs.location, yystack_[0].value.as < TokenInfo > ().Int, ast::IntExp::Base::Dec, true); }
#line 2615 "parser.tab.cc"
    break;

  case 66: // int_expr: "0x2Au"
#line 434 "parser.yy"
                         { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_int_exp(yylhs.location, yystack_[0].value.as < TokenInfo > ().Int, ast::IntExp::Base::Hex, true); }
#line 2621 "parser.tab.cc"
    break;

  case 67: // stringls: "'sq-string-literal'"
#line 437 "parser.yy"
                             { yylhs.value.as < std::vector<pdm::ast::StringExp::Piece> > ().emplace_back(yylhs.location, *yystack_[0].value.as < TokenInfo > ().String_utf8string, ast::StringExp::QuoteKind::SingleQuote); }
#line 2627 "parser.tab.cc"
    break;

  case 68: // stringls: "\"dq-string-literal\""
#line 438 "parser.yy"
                             { yylhs.value.as < std::vector<pdm::ast::StringExp::Piece> > ().emplace_back(yylhs.location, *yystack_[0].value.as < TokenInfo > ().String_utf8string, ast::StringExp::QuoteKind::DoubleQuote); }
#line 2633 "parser.tab.cc"
    break;

  case 69: // stringls: stringls "'sq-string-literal'"
#line 439 "parser.yy"
                             { yylhs.value.as < std::vector<pdm::ast::StringExp::Piece> > () = std::move(yystack_[1].value.as < std::vector<pdm::ast::StringExp::Piece> > ()); yylhs.value.as < std::vector<pdm::ast::StringExp::Piece> > ().emplace_back(yystack_[0].location, *yystack_[0].value.as < TokenInfo > ().String_utf8string, ast::StringExp::QuoteKind::SingleQuote); }
#line 2639 "parser.tab.cc"
    break;

  case 70: // stringls: stringls "\"dq-string-literal\""
#line 440 "parser.yy"
                             { yylhs.value.as < std::vector<pdm::ast::StringExp::Piece> > () = std::move(yystack_[1].value.as < std::vector<pdm::ast::StringExp::Piece> > ()); yylhs.value.as < std::vector<pdm::ast::StringExp::Piece> > ().emplace_back(yystack_[0].location, *yystack_[0].value.as < TokenInfo > ().String_utf8string, ast::StringExp::QuoteKind::DoubleQuote); }
#line 2645 "parser.tab.cc"
    break;

  case 71: // if_exp: "if" bracketed_exp "then" bracketed_exp
#line 443 "parser.yy"
                                                                        { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_if_exp(yylhs.location, yystack_[2].value.as < pdm::ast::Exp* > (), yystack_[0].value.as < pdm::ast::Exp* > (), nullptr); }
#line 2651 "parser.tab.cc"
    break;

  case 72: // if_exp: "if" bracketed_exp "then" bracketed_exp "else" primary_exp
#line 444 "parser.yy"
                                                                        { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_if_exp(yylhs.location, yystack_[4].value.as < pdm::ast::Exp* > (), yystack_[2].value.as < pdm::ast::Exp* > (), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2657 "parser.tab.cc"
    break;

  case 73: // chain_exp: "{" long_exp "}"
#line 447 "parser.yy"
                                               { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_chain_exp(yylhs.location, std::move(std::vector<ast::Stmt*>{}), yystack_[1].value.as < pdm::ast::Exp* > ()); }
#line 2663 "parser.tab.cc"
    break;

  case 74: // chain_exp: "{" chain_prefix "}"
#line 448 "parser.yy"
                                               { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_chain_exp(yylhs.location, std::move(yystack_[1].value.as < std::vector<pdm::ast::Stmt*> > ()), nullptr); }
#line 2669 "parser.tab.cc"
    break;

  case 75: // chain_exp: "{" chain_prefix long_exp "}"
#line 449 "parser.yy"
                                               { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_chain_exp(yylhs.location, std::move(yystack_[2].value.as < std::vector<pdm::ast::Stmt*> > ()), yystack_[1].value.as < pdm::ast::Exp* > ()); }
#line 2675 "parser.tab.cc"
    break;

  case 76: // chain_prefix: chain_prefix_stmt ";"
#line 452 "parser.yy"
                                                { yylhs.value.as < std::vector<pdm::ast::Stmt*> > ().push_back(yystack_[1].value.as < pdm::ast::Stmt* > ()); }
#line 2681 "parser.tab.cc"
    break;

  case 77: // chain_prefix: chain_prefix chain_prefix_stmt ";"
#line 453 "parser.yy"
                                                { yylhs.value.as < std::vector<pdm::ast::Stmt*> > () = std::move(yystack_[2].value.as < std::vector<pdm::ast::Stmt*> > ()); yylhs.value.as < std::vector<pdm::ast::Stmt*> > ().push_back(yystack_[1].value.as < pdm::ast::Stmt* > ()); }
#line 2687 "parser.tab.cc"
    break;

  case 78: // lambda_exp: fn_type_spec bracketed_exp
#line 456 "parser.yy"
                                   { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_lambda_exp(yylhs.location, yystack_[1].value.as < pdm::ast::FnTypeSpec* > (), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2693 "parser.tab.cc"
    break;

  case 79: // postfix_exp: primary_exp
#line 460 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2699 "parser.tab.cc"
    break;

  case 80: // postfix_exp: vcall_exp
#line 461 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2705 "parser.tab.cc"
    break;

  case 81: // postfix_exp: dot_name_exp
#line 462 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2711 "parser.tab.cc"
    break;

  case 82: // postfix_exp: dot_index_exp
#line 463 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2717 "parser.tab.cc"
    break;

  case 83: // vcall_exp: postfix_exp "(" ")"
#line 466 "parser.yy"
                                            { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_vcall_exp(yylhs.location, yystack_[2].value.as < pdm::ast::Exp* > (), std::move(std::vector<ast::VArg*>{})); }
#line 2723 "parser.tab.cc"
    break;

  case 84: // vcall_exp: postfix_exp "(" varg_cl ")"
#line 467 "parser.yy"
                                            { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_vcall_exp(yylhs.location, yystack_[3].value.as < pdm::ast::Exp* > (), std::move(yystack_[1].value.as < std::vector<pdm::ast::VArg*> > ())); }
#line 2729 "parser.tab.cc"
    break;

  case 85: // dot_name_exp: postfix_exp "." "val_id"
#line 470 "parser.yy"
                                                { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_struct_dot_name_exp(yylhs.location, yystack_[2].value.as < pdm::ast::Exp* > (), yystack_[0].value.as < TokenInfo > ().ID_intstr); }
#line 2735 "parser.tab.cc"
    break;

  case 86: // dot_name_exp: type_spec "::" "TypeId"
#line 471 "parser.yy"
                                                    { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_enum_dot_name_exp(yylhs.location, yystack_[2].value.as < pdm::ast::TypeSpec* > (), yystack_[0].value.as < TokenInfo > ().ID_intstr, nullptr); }
#line 2741 "parser.tab.cc"
    break;

  case 87: // dot_name_exp: type_spec "::" "TypeId" "using" paren_exp
#line 472 "parser.yy"
                                                    { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_enum_dot_name_exp(yylhs.location, yystack_[4].value.as < pdm::ast::TypeSpec* > (), yystack_[2].value.as < TokenInfo > ().ID_intstr, yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2747 "parser.tab.cc"
    break;

  case 88: // dot_index_exp: postfix_exp "." int_expr
#line 475 "parser.yy"
                                    { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_dot_index_exp(yylhs.location, yystack_[2].value.as < pdm::ast::Exp* > (), yystack_[0].value.as < pdm::ast::Exp* > (), ast::DotIndexExp::RhsHint::LhsNotPtr); }
#line 2753 "parser.tab.cc"
    break;

  case 89: // dot_index_exp: postfix_exp "." bracketed_exp
#line 476 "parser.yy"
                                    { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_dot_index_exp(yylhs.location, yystack_[2].value.as < pdm::ast::Exp* > (), yystack_[0].value.as < pdm::ast::Exp* > (), ast::DotIndexExp::RhsHint::LhsNotPtr); }
#line 2759 "parser.tab.cc"
    break;

  case 90: // unary_exp: postfix_exp
#line 480 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2765 "parser.tab.cc"
    break;

  case 91: // unary_exp: unary_op unary_exp
#line 481 "parser.yy"
                             { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_unary_exp(yylhs.location, yystack_[1].value.as < pdm::ast::UnaryOperator > (), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2771 "parser.tab.cc"
    break;

  case 92: // unary_op: "+"
#line 484 "parser.yy"
                 { yylhs.value.as < pdm::ast::UnaryOperator > () = ast::UnaryOperator::Plus; }
#line 2777 "parser.tab.cc"
    break;

  case 93: // unary_op: "-"
#line 485 "parser.yy"
                 { yylhs.value.as < pdm::ast::UnaryOperator > () = ast::UnaryOperator::Minus; }
#line 2783 "parser.tab.cc"
    break;

  case 94: // unary_op: "not"
#line 486 "parser.yy"
                 { yylhs.value.as < pdm::ast::UnaryOperator > () = ast::UnaryOperator::Not; }
#line 2789 "parser.tab.cc"
    break;

  case 95: // binary_exp: or_binary_exp
#line 490 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2795 "parser.tab.cc"
    break;

  case 96: // mul_binary_op: "*"
#line 493 "parser.yy"
                 { yylhs.value.as < pdm::ast::BinaryOperator > () = ast::BinaryOperator::Mul; }
#line 2801 "parser.tab.cc"
    break;

  case 97: // mul_binary_op: "/"
#line 494 "parser.yy"
                 { yylhs.value.as < pdm::ast::BinaryOperator > () = ast::BinaryOperator::Div; }
#line 2807 "parser.tab.cc"
    break;

  case 98: // mul_binary_op: "%"
#line 495 "parser.yy"
                 { yylhs.value.as < pdm::ast::BinaryOperator > () = ast::BinaryOperator::Rem; }
#line 2813 "parser.tab.cc"
    break;

  case 99: // mul_binary_exp: unary_exp
#line 498 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2819 "parser.tab.cc"
    break;

  case 100: // mul_binary_exp: mul_binary_exp mul_binary_op unary_exp
#line 499 "parser.yy"
                                               { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_binary_exp(yylhs.location, yystack_[1].value.as < pdm::ast::BinaryOperator > (), yystack_[2].value.as < pdm::ast::Exp* > (), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2825 "parser.tab.cc"
    break;

  case 101: // add_binary_op: "+"
#line 502 "parser.yy"
             { yylhs.value.as < pdm::ast::BinaryOperator > () = ast::BinaryOperator::Add; }
#line 2831 "parser.tab.cc"
    break;

  case 102: // add_binary_op: "-"
#line 503 "parser.yy"
             { yylhs.value.as < pdm::ast::BinaryOperator > () = ast::BinaryOperator::Subtract; }
#line 2837 "parser.tab.cc"
    break;

  case 103: // add_binary_exp: mul_binary_exp
#line 506 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2843 "parser.tab.cc"
    break;

  case 104: // add_binary_exp: add_binary_exp add_binary_op mul_binary_exp
#line 507 "parser.yy"
                                                    { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_binary_exp(yylhs.location, yystack_[1].value.as < pdm::ast::BinaryOperator > (), yystack_[2].value.as < pdm::ast::Exp* > (), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2849 "parser.tab.cc"
    break;

  case 105: // cmp_binary_op: "<"
#line 510 "parser.yy"
                { yylhs.value.as < pdm::ast::BinaryOperator > () = ast::BinaryOperator::Less; }
#line 2855 "parser.tab.cc"
    break;

  case 106: // cmp_binary_op: "<="
#line 511 "parser.yy"
                { yylhs.value.as < pdm::ast::BinaryOperator > () = ast::BinaryOperator::LessOrEq; }
#line 2861 "parser.tab.cc"
    break;

  case 107: // cmp_binary_op: ">"
#line 512 "parser.yy"
                { yylhs.value.as < pdm::ast::BinaryOperator > () = ast::BinaryOperator::Greater; }
#line 2867 "parser.tab.cc"
    break;

  case 108: // cmp_binary_op: ">="
#line 513 "parser.yy"
                { yylhs.value.as < pdm::ast::BinaryOperator > () = ast::BinaryOperator::GreaterOrEq; }
#line 2873 "parser.tab.cc"
    break;

  case 109: // cmp_binary_exp: add_binary_exp
#line 516 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2879 "parser.tab.cc"
    break;

  case 110: // cmp_binary_exp: cmp_binary_exp cmp_binary_op add_binary_exp
#line 517 "parser.yy"
                                                    { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_binary_exp(yylhs.location, yystack_[1].value.as < pdm::ast::BinaryOperator > (), yystack_[2].value.as < pdm::ast::Exp* > (), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2885 "parser.tab.cc"
    break;

  case 111: // eq_binary_op: "=="
#line 520 "parser.yy"
                 { yylhs.value.as < pdm::ast::BinaryOperator > () = ast::BinaryOperator::Equals; }
#line 2891 "parser.tab.cc"
    break;

  case 112: // eq_binary_op: "!="
#line 521 "parser.yy"
                 { yylhs.value.as < pdm::ast::BinaryOperator > () = ast::BinaryOperator::NotEquals; }
#line 2897 "parser.tab.cc"
    break;

  case 113: // eq_binary_exp: cmp_binary_exp
#line 524 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2903 "parser.tab.cc"
    break;

  case 114: // eq_binary_exp: eq_binary_exp eq_binary_op cmp_binary_exp
#line 525 "parser.yy"
                                                { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_binary_exp(yylhs.location, yystack_[1].value.as < pdm::ast::BinaryOperator > (), yystack_[2].value.as < pdm::ast::Exp* > (), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2909 "parser.tab.cc"
    break;

  case 115: // and_binary_exp: eq_binary_exp
#line 528 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2915 "parser.tab.cc"
    break;

  case 116: // and_binary_exp: and_binary_exp "and" eq_binary_exp
#line 529 "parser.yy"
                                           { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_binary_exp(yylhs.location, ast::BinaryOperator::And, yystack_[2].value.as < pdm::ast::Exp* > (), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2921 "parser.tab.cc"
    break;

  case 117: // xor_binary_exp: and_binary_exp
#line 532 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2927 "parser.tab.cc"
    break;

  case 118: // xor_binary_exp: xor_binary_exp "xor" and_binary_exp
#line 533 "parser.yy"
                                           { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_binary_exp(yylhs.location, ast::BinaryOperator::XOr, yystack_[2].value.as < pdm::ast::Exp* > (), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2933 "parser.tab.cc"
    break;

  case 119: // or_binary_exp: xor_binary_exp
#line 536 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2939 "parser.tab.cc"
    break;

  case 120: // or_binary_exp: or_binary_exp "or" xor_binary_exp
#line 537 "parser.yy"
                                           { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_binary_exp(yylhs.location, ast::BinaryOperator::Or, yystack_[2].value.as < pdm::ast::Exp* > (), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2945 "parser.tab.cc"
    break;

  case 121: // type_query_exp: type_spec type_query_op type_spec
#line 541 "parser.yy"
                                          { yylhs.value.as < pdm::ast::TypeQueryExp* > () = mgr->new_type_query_exp(yylhs.location, yystack_[1].value.as < pdm::ast::TypeQueryKind > (), yystack_[2].value.as < pdm::ast::TypeSpec* > (), yystack_[0].value.as < pdm::ast::TypeSpec* > ()); }
#line 2951 "parser.tab.cc"
    break;

  case 122: // type_query_op: ":<"
#line 544 "parser.yy"
                    { yylhs.value.as < pdm::ast::TypeQueryKind > () = ast::TypeQueryKind::LhsSubtypesRhs; }
#line 2957 "parser.tab.cc"
    break;

  case 123: // type_query_op: ">:"
#line 545 "parser.yy"
                    { yylhs.value.as < pdm::ast::TypeQueryKind > () = ast::TypeQueryKind::LhsSupertypesRhs; }
#line 2963 "parser.tab.cc"
    break;

  case 124: // type_query_op: "=="
#line 546 "parser.yy"
                    { yylhs.value.as < pdm::ast::TypeQueryKind > () = ast::TypeQueryKind::LhsEqualsRhs; }
#line 2969 "parser.tab.cc"
    break;

  case 125: // type_spec_cl2: type_spec "," type_spec
#line 561 "parser.yy"
                                    { yylhs.value.as < std::vector<pdm::ast::TypeSpec*> > ().reserve(2); yylhs.value.as < std::vector<pdm::ast::TypeSpec*> > ().push_back(yystack_[2].value.as < pdm::ast::TypeSpec* > ()); yylhs.value.as < std::vector<pdm::ast::TypeSpec*> > ().push_back(yystack_[0].value.as < pdm::ast::TypeSpec* > ()); }
#line 2975 "parser.tab.cc"
    break;

  case 126: // type_spec_cl2: type_spec_cl2 "," type_spec
#line 562 "parser.yy"
                                    { yylhs.value.as < std::vector<pdm::ast::TypeSpec*> > () = std::move(yystack_[2].value.as < std::vector<pdm::ast::TypeSpec*> > ()); yylhs.value.as < std::vector<pdm::ast::TypeSpec*> > ().push_back(yystack_[0].value.as < pdm::ast::TypeSpec* > ()); }
#line 2981 "parser.tab.cc"
    break;

  case 127: // type_spec: tid
#line 566 "parser.yy"
                        { yylhs.value.as < pdm::ast::TypeSpec* > () = mgr->new_id_type_spec(yylhs.location, yystack_[0].value.as < TokenInfo > ().ID_intstr); }
#line 2987 "parser.tab.cc"
    break;

  case 128: // type_spec: mod_prefix_tid
#line 567 "parser.yy"
      { yylhs.value.as < pdm::ast::TypeSpec* > () = yystack_[0].value.as < pdm::ast::TypeSpec* > (); }
#line 2993 "parser.tab.cc"
    break;

  case 129: // type_spec: tuple_type_spec
#line 568 "parser.yy"
      { yylhs.value.as < pdm::ast::TypeSpec* > () = yystack_[0].value.as < pdm::ast::TypeSpec* > (); }
#line 2999 "parser.tab.cc"
    break;

  case 130: // type_spec: array_type_spec
#line 569 "parser.yy"
      { yylhs.value.as < pdm::ast::TypeSpec* > () = yystack_[0].value.as < pdm::ast::TypeSpec* > (); }
#line 3005 "parser.tab.cc"
    break;

  case 131: // long_type_spec: type_spec
#line 572 "parser.yy"
      { yylhs.value.as < pdm::ast::TypeSpec* > () = yystack_[0].value.as < pdm::ast::TypeSpec* > (); }
#line 3011 "parser.tab.cc"
    break;

  case 132: // long_type_spec: struct_type_spec
#line 573 "parser.yy"
      { yylhs.value.as < pdm::ast::TypeSpec* > () = yystack_[0].value.as < pdm::ast::TypeSpec* > (); }
#line 3017 "parser.tab.cc"
    break;

  case 133: // long_type_spec: enum_type_spec
#line 574 "parser.yy"
      { yylhs.value.as < pdm::ast::TypeSpec* > () = yystack_[0].value.as < pdm::ast::TypeSpec* > (); }
#line 3023 "parser.tab.cc"
    break;

  case 134: // long_type_spec: fn_type_spec
#line 575 "parser.yy"
                    { yylhs.value.as < pdm::ast::TypeSpec* > () = dynamic_cast<ast::TypeSpec*>(yystack_[0].value.as < pdm::ast::FnTypeSpec* > ()); }
#line 3029 "parser.tab.cc"
    break;

  case 135: // mod_prefix_tid: mod_prefix tid
#line 579 "parser.yy"
                            { yylhs.value.as < pdm::ast::TypeSpec* > () = mgr->new_ma_type_spec(yylhs.location, yystack_[1].value.as < pdm::ast::ModAddress* > (), yystack_[0].value.as < TokenInfo > ().ID_intstr); }
#line 3035 "parser.tab.cc"
    break;

  case 136: // tuple_type_spec: "{" type_spec "}"
#line 583 "parser.yy"
                                   { yylhs.value.as < pdm::ast::TypeSpec* > () = mgr->new_tuple_type_spec(yylhs.location, std::move(std::vector(1,yystack_[1].value.as < pdm::ast::TypeSpec* > ()))); }
#line 3041 "parser.tab.cc"
    break;

  case 137: // tuple_type_spec: "{" type_spec_cl2 "}"
#line 584 "parser.yy"
                                   { yylhs.value.as < pdm::ast::TypeSpec* > () = mgr->new_tuple_type_spec(yylhs.location, std::move(yystack_[1].value.as < std::vector<pdm::ast::TypeSpec*> > ())); }
#line 3047 "parser.tab.cc"
    break;

  case 138: // array_type_spec: "[" type_spec "*" expr "]"
#line 587 "parser.yy"
                                                { yylhs.value.as < pdm::ast::TypeSpec* > () = nullptr; }
#line 3053 "parser.tab.cc"
    break;

  case 139: // struct_type_spec: "{" struct_type_spec_field_cl "}"
#line 591 "parser.yy"
                                               { yylhs.value.as < pdm::ast::TypeSpec* > () = mgr->new_struct_type_spec(yylhs.location, std::move(yystack_[1].value.as < std::vector<pdm::ast::StructTypeSpec::Field*> > ())); }
#line 3059 "parser.tab.cc"
    break;

  case 140: // struct_type_spec_field_cl: struct_type_spec_field
#line 594 "parser.yy"
                                                              { yylhs.value.as < std::vector<pdm::ast::StructTypeSpec::Field*> > ().push_back(yystack_[0].value.as < pdm::ast::StructTypeSpec::Field* > ()); }
#line 3065 "parser.tab.cc"
    break;

  case 141: // struct_type_spec_field_cl: struct_type_spec_field_cl "," struct_type_spec_field
#line 595 "parser.yy"
                                                              { yylhs.value.as < std::vector<pdm::ast::StructTypeSpec::Field*> > () = std::move(yystack_[2].value.as < std::vector<pdm::ast::StructTypeSpec::Field*> > ()); yylhs.value.as < std::vector<pdm::ast::StructTypeSpec::Field*> > ().push_back(yystack_[0].value.as < pdm::ast::StructTypeSpec::Field* > ()); }
#line 3071 "parser.tab.cc"
    break;

  case 142: // struct_type_spec_field: vid long_type_spec
#line 598 "parser.yy"
                                         { yylhs.value.as < pdm::ast::StructTypeSpec::Field* > () = mgr->new_struct_type_spec_field(yylhs.location, yystack_[1].value.as < TokenInfo > ().ID_intstr, yystack_[0].value.as < pdm::ast::TypeSpec* > ()); }
#line 3077 "parser.tab.cc"
    break;

  case 143: // enum_type_spec_field: tid
#line 602 "parser.yy"
                             { yylhs.value.as < pdm::ast::EnumTypeSpec::Field* > () = mgr->new_enum_type_spec_field(yylhs.location, yystack_[0].value.as < TokenInfo > ().ID_intstr, nullptr); }
#line 3083 "parser.tab.cc"
    break;

  case 144: // enum_type_spec_field: tid long_type_spec
#line 603 "parser.yy"
                             { yylhs.value.as < pdm::ast::EnumTypeSpec::Field* > () = mgr->new_enum_type_spec_field(yylhs.location, yystack_[1].value.as < TokenInfo > ().ID_intstr, yystack_[0].value.as < pdm::ast::TypeSpec* > ()); }
#line 3089 "parser.tab.cc"
    break;

  case 145: // enum_type_spec_field_cl: enum_type_spec_field
#line 606 "parser.yy"
                                                            { yylhs.value.as < std::vector<pdm::ast::EnumTypeSpec::Field*> > ().push_back(yystack_[0].value.as < pdm::ast::EnumTypeSpec::Field* > ()); }
#line 3095 "parser.tab.cc"
    break;

  case 146: // enum_type_spec_field_cl: enum_type_spec_field_cl "," enum_type_spec_field
#line 607 "parser.yy"
                                                            { yylhs.value.as < std::vector<pdm::ast::EnumTypeSpec::Field*> > () = std::move(yystack_[2].value.as < std::vector<pdm::ast::EnumTypeSpec::Field*> > ()); yylhs.value.as < std::vector<pdm::ast::EnumTypeSpec::Field*> > ().push_back(yystack_[0].value.as < pdm::ast::EnumTypeSpec::Field* > ()); }
#line 3101 "parser.tab.cc"
    break;

  case 147: // enum_type_spec: "enum" "{" enum_type_spec_field_cl "}"
#line 610 "parser.yy"
                                                        { yylhs.value.as < pdm::ast::TypeSpec* > () = mgr->new_enum_type_spec(yylhs.location, std::move(yystack_[1].value.as < std::vector<pdm::ast::EnumTypeSpec::Field*> > ())); }
#line 3107 "parser.tab.cc"
    break;

  case 148: // fn_type_spec: vpattern "->" type_spec
#line 614 "parser.yy"
                               { yylhs.value.as < pdm::ast::FnTypeSpec* > () = mgr->new_fn_type_spec(yylhs.location, std::move(yystack_[2].value.as < pdm::ast::VPattern* > ()), yystack_[0].value.as < pdm::ast::TypeSpec* > ()); }
#line 3113 "parser.tab.cc"
    break;

  case 149: // targ: type_spec
#line 618 "parser.yy"
                { yylhs.value.as < pdm::ast::TArg* > () = mgr->new_targ_type_spec(yylhs.location, yystack_[0].value.as < pdm::ast::TypeSpec* > ()); }
#line 3119 "parser.tab.cc"
    break;

  case 150: // targ: expr
#line 619 "parser.yy"
               { yylhs.value.as < pdm::ast::TArg* > () = mgr->new_targ_exp(yylhs.location, yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 3125 "parser.tab.cc"
    break;

  case 151: // targ_cl: targ
#line 622 "parser.yy"
                            { yylhs.value.as < std::vector<pdm::ast::TArg*> > ().push_back(yystack_[0].value.as < pdm::ast::TArg* > ()); }
#line 3131 "parser.tab.cc"
    break;

  case 152: // targ_cl: targ_cl "," targ
#line 623 "parser.yy"
                            { yylhs.value.as < std::vector<pdm::ast::TArg*> > () = std::move(yystack_[2].value.as < std::vector<pdm::ast::TArg*> > ()); yylhs.value.as < std::vector<pdm::ast::TArg*> > ().push_back(yystack_[0].value.as < pdm::ast::TArg* > ()); }
#line 3137 "parser.tab.cc"
    break;

  case 153: // varg: expr
#line 625 "parser.yy"
                            { yylhs.value.as < pdm::ast::VArg* > () = mgr->new_varg(yylhs.location, yystack_[0].value.as < pdm::ast::Exp* > (), ast::VArgAccessSpec::In); }
#line 3143 "parser.tab.cc"
    break;

  case 154: // varg: "out" expr
#line 626 "parser.yy"
                            { yylhs.value.as < pdm::ast::VArg* > () = mgr->new_varg(yylhs.location, yystack_[0].value.as < pdm::ast::Exp* > (), ast::VArgAccessSpec::Out); }
#line 3149 "parser.tab.cc"
    break;

  case 155: // varg: "inout" expr
#line 627 "parser.yy"
                            { yylhs.value.as < pdm::ast::VArg* > () = mgr->new_varg(yylhs.location, yystack_[0].value.as < pdm::ast::Exp* > (), ast::VArgAccessSpec::InOut); }
#line 3155 "parser.tab.cc"
    break;

  case 156: // varg_cl: varg
#line 630 "parser.yy"
                            { yylhs.value.as < std::vector<pdm::ast::VArg*> > ().push_back(yystack_[0].value.as < pdm::ast::VArg* > ()); }
#line 3161 "parser.tab.cc"
    break;

  case 157: // varg_cl: varg_cl "," varg
#line 631 "parser.yy"
                            { yylhs.value.as < std::vector<pdm::ast::VArg*> > () = std::move(yystack_[2].value.as < std::vector<pdm::ast::VArg*> > ()); yylhs.value.as < std::vector<pdm::ast::VArg*> > ().push_back(yystack_[0].value.as < pdm::ast::VArg* > ()); }
#line 3167 "parser.tab.cc"
    break;

  case 158: // class_spec: primary_class_spec
#line 641 "parser.yy"
      { yylhs.value.as < pdm::ast::ClassSpec* > () = yystack_[0].value.as < pdm::ast::ClassSpec* > (); }
#line 3173 "parser.tab.cc"
    break;

  case 159: // primary_class_spec: cid
#line 644 "parser.yy"
                        { yylhs.value.as < pdm::ast::ClassSpec* > () = mgr->new_id_class_spec(yylhs.location, yystack_[0].value.as < TokenInfo > ().ID_intstr); }
#line 3179 "parser.tab.cc"
    break;

  case 160: // primary_class_spec: mod_prefix_cid_class_spec
#line 645 "parser.yy"
      { yylhs.value.as < pdm::ast::ClassSpec* > () = yystack_[0].value.as < pdm::ast::ClassSpec* > (); }
#line 3185 "parser.tab.cc"
    break;

  case 161: // primary_class_spec: class_exp_class_spec
#line 646 "parser.yy"
      { yylhs.value.as < pdm::ast::ClassSpec* > () = yystack_[0].value.as < pdm::ast::ClassSpec* > (); }
#line 3191 "parser.tab.cc"
    break;

  case 162: // mod_prefix_cid_class_spec: mod_prefix cid
#line 649 "parser.yy"
                        { yylhs.value.as < pdm::ast::ClassSpec* > () = mgr->new_ma_class_spec(yylhs.location, std::move(yystack_[1].value.as < pdm::ast::ModAddress* > ()), yystack_[0].value.as < TokenInfo > ().ID_intstr); }
#line 3197 "parser.tab.cc"
    break;

  case 163: // class_exp_class_spec: "cls" "(" tid class_spec ")" "{" type_query_exp_sl "}"
#line 654 "parser.yy"
                                                                              { yylhs.value.as < pdm::ast::ClassSpec* > () = nullptr; }
#line 3203 "parser.tab.cc"
    break;

  case 164: // struct_exp_field: vid ":" expr
#line 662 "parser.yy"
                     { yylhs.value.as < pdm::ast::StructExp::Field* > () = mgr->new_struct_exp_field(yylhs.location, yystack_[2].value.as < TokenInfo > ().ID_intstr, yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 3209 "parser.tab.cc"
    break;

  case 165: // vpattern_field: vid type_spec
#line 665 "parser.yy"
                             { yylhs.value.as < pdm::ast::VPattern::Field* > () = mgr->new_vpattern_field(yylhs.location, yystack_[1].value.as < TokenInfo > ().ID_intstr, yystack_[0].value.as < pdm::ast::TypeSpec* > (), ast::VArgAccessSpec::In); }
#line 3215 "parser.tab.cc"
    break;

  case 166: // vpattern_field: "out" vid type_spec
#line 666 "parser.yy"
                             { yylhs.value.as < pdm::ast::VPattern::Field* > () = mgr->new_vpattern_field(yylhs.location, yystack_[1].value.as < TokenInfo > ().ID_intstr, yystack_[0].value.as < pdm::ast::TypeSpec* > (), ast::VArgAccessSpec::Out); }
#line 3221 "parser.tab.cc"
    break;

  case 167: // vpattern_field: "inout" vid type_spec
#line 667 "parser.yy"
                             { yylhs.value.as < pdm::ast::VPattern::Field* > () = mgr->new_vpattern_field(yylhs.location, yystack_[1].value.as < TokenInfo > ().ID_intstr, yystack_[0].value.as < pdm::ast::TypeSpec* > (), ast::VArgAccessSpec::InOut); }
#line 3227 "parser.tab.cc"
    break;

  case 168: // lpattern_field: vid type_spec
#line 670 "parser.yy"
                     { yylhs.value.as < pdm::ast::LPattern::Field* > () = mgr->new_lpattern_field(yylhs.location, ast::LPattern::FieldKind::IdTypeSpecPair, yystack_[1].value.as < TokenInfo > ().ID_intstr, yystack_[0].value.as < pdm::ast::TypeSpec* > ()); }
#line 3233 "parser.tab.cc"
    break;

  case 169: // lpattern_field: vid
#line 671 "parser.yy"
                    { yylhs.value.as < pdm::ast::LPattern::Field* > () = mgr->new_lpattern_field(yylhs.location, ast::LPattern::FieldKind::IdSingleton, yystack_[0].value.as < TokenInfo > ().ID_intstr); }
#line 3239 "parser.tab.cc"
    break;

  case 170: // tpattern_field: vid type_spec
#line 674 "parser.yy"
                      { yylhs.value.as < pdm::ast::TPattern::Field* > () = mgr->new_value_tpattern_field(yylhs.location, yystack_[1].value.as < TokenInfo > ().ID_intstr, yystack_[0].value.as < pdm::ast::TypeSpec* > ()); }
#line 3245 "parser.tab.cc"
    break;

  case 171: // tpattern_field: tid class_spec
#line 675 "parser.yy"
                      { yylhs.value.as < pdm::ast::TPattern::Field* > () = mgr->new_type_tpattern_field(yylhs.location, yystack_[1].value.as < TokenInfo > ().ID_intstr, yystack_[0].value.as < pdm::ast::ClassSpec* > ()); }
#line 3251 "parser.tab.cc"
    break;

  case 172: // destructured_lpattern: "{" lpattern_field_cl "}"
#line 679 "parser.yy"
                                       { yylhs.value.as < pdm::ast::LPattern* > () = mgr->new_lpattern(yylhs.location, std::move(yystack_[1].value.as < std::vector<pdm::ast::LPattern::Field*> > ()), true); }
#line 3257 "parser.tab.cc"
    break;

  case 173: // lpattern: lpattern_field
#line 682 "parser.yy"
                        { yylhs.value.as < pdm::ast::LPattern* > () = mgr->new_lpattern(yylhs.location, std::move(std::vector<ast::LPattern::Field*>{1,yystack_[0].value.as < pdm::ast::LPattern::Field* > ()}), false); }
#line 3263 "parser.tab.cc"
    break;

  case 174: // lpattern: destructured_lpattern
#line 683 "parser.yy"
      { yylhs.value.as < pdm::ast::LPattern* > () = yystack_[0].value.as < pdm::ast::LPattern* > (); }
#line 3269 "parser.tab.cc"
    break;

  case 175: // vpattern: "(" vpattern_field_cl ")"
#line 686 "parser.yy"
                                       { yylhs.value.as < pdm::ast::VPattern* > () = mgr->new_vpattern(yylhs.location, std::move(yystack_[1].value.as < std::vector<pdm::ast::VPattern::Field*> > ())); }
#line 3275 "parser.tab.cc"
    break;

  case 176: // vpattern: "(" ")"
#line 687 "parser.yy"
                                       { yylhs.value.as < pdm::ast::VPattern* > () = mgr->new_vpattern(yylhs.location, std::move(std::vector<ast::VPattern::Field*>{})); }
#line 3281 "parser.tab.cc"
    break;

  case 177: // tpattern: "[" tpattern_field_cl1 "]"
#line 690 "parser.yy"
                                        { yylhs.value.as < pdm::ast::TPattern* > () = mgr->new_tpattern(yylhs.location, std::move(yystack_[1].value.as < std::vector<pdm::ast::TPattern::Field*> > ()), false); }
#line 3287 "parser.tab.cc"
    break;

  case 178: // vpattern_field_cl: vpattern_field
#line 694 "parser.yy"
                                              { yylhs.value.as < std::vector<pdm::ast::VPattern::Field*> > ().push_back(yystack_[0].value.as < pdm::ast::VPattern::Field* > ()); }
#line 3293 "parser.tab.cc"
    break;

  case 179: // vpattern_field_cl: vpattern_field_cl "," vpattern_field
#line 695 "parser.yy"
                                               { yylhs.value.as < std::vector<pdm::ast::VPattern::Field*> > () = std::move(yystack_[2].value.as < std::vector<pdm::ast::VPattern::Field*> > ()); yylhs.value.as < std::vector<pdm::ast::VPattern::Field*> > ().push_back(yystack_[0].value.as < pdm::ast::VPattern::Field* > ()); }
#line 3299 "parser.tab.cc"
    break;

  case 180: // lpattern_field_cl: lpattern_field
#line 698 "parser.yy"
                                               { yylhs.value.as < std::vector<pdm::ast::LPattern::Field*> > ().push_back(yystack_[0].value.as < pdm::ast::LPattern::Field* > ()); }
#line 3305 "parser.tab.cc"
    break;

  case 181: // lpattern_field_cl: lpattern_field_cl "," lpattern_field
#line 699 "parser.yy"
                                               { yylhs.value.as < std::vector<pdm::ast::LPattern::Field*> > () = std::move(yystack_[2].value.as < std::vector<pdm::ast::LPattern::Field*> > ()); yylhs.value.as < std::vector<pdm::ast::LPattern::Field*> > ().push_back(yystack_[0].value.as < pdm::ast::LPattern::Field* > ()); }
#line 3311 "parser.tab.cc"
    break;

  case 182: // tpattern_field_cl1: tpattern_field
#line 702 "parser.yy"
                                              { yylhs.value.as < std::vector<pdm::ast::TPattern::Field*> > ().push_back(yystack_[0].value.as < pdm::ast::TPattern::Field* > ()); }
#line 3317 "parser.tab.cc"
    break;

  case 183: // tpattern_field_cl1: tpattern_field_cl1 "," tpattern_field
#line 703 "parser.yy"
                                                { yylhs.value.as < std::vector<pdm::ast::TPattern::Field*> > () = std::move(yystack_[2].value.as < std::vector<pdm::ast::TPattern::Field*> > ()); yylhs.value.as < std::vector<pdm::ast::TPattern::Field*> > ().push_back(yystack_[0].value.as < pdm::ast::TPattern::Field* > ()); }
#line 3323 "parser.tab.cc"
    break;

  case 184: // struct_exp_field_cl: struct_exp_field
#line 706 "parser.yy"
                                                    { yylhs.value.as < std::vector<pdm::ast::StructExp::Field*> > ().push_back(yystack_[0].value.as < pdm::ast::StructExp::Field* > ()); }
#line 3329 "parser.tab.cc"
    break;

  case 185: // struct_exp_field_cl: struct_exp_field_cl "," struct_exp_field
#line 707 "parser.yy"
                                                    { yylhs.value.as < std::vector<pdm::ast::StructExp::Field*> > () = std::move(yystack_[2].value.as < std::vector<pdm::ast::StructExp::Field*> > ()); yylhs.value.as < std::vector<pdm::ast::StructExp::Field*> > ().push_back(yystack_[0].value.as < pdm::ast::StructExp::Field* > ()); }
#line 3335 "parser.tab.cc"
    break;


#line 3339 "parser.tab.cc"

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





  const short parser::yypact_ninf_ = -230;

  const short parser::yytable_ninf_ = -177;

  const short
  parser::yypact_[] =
  {
    -230,    11,   111,  -230,   119,    94,   137,   183,  -230,  -230,
      77,  -230,  -230,   119,   149,    26,    78,    13,  -230,   136,
     -20,  -230,  -230,  -230,   187,  -230,   103,   140,  -230,    74,
    -230,   119,  -230,    32,   174,   181,   196,   200,    64,    26,
     182,    84,  -230,   147,  -230,  -230,  -230,  -230,   140,   140,
    -230,    78,  -230,  -230,  -230,  -230,    78,  -230,   -20,  -230,
     210,  -230,    53,   582,   238,  -230,    82,  -230,   255,  -230,
     611,   216,  -230,   212,   -36,    73,  -230,  -230,  -230,  -230,
     222,   226,   140,  -230,  -230,  -230,  -230,  -230,   229,   146,
    -230,  -230,  -230,  -230,  -230,  -230,  -230,  -230,   437,   398,
    -230,  -230,    84,  -230,    78,  -230,  -230,  -230,  -230,  -230,
    -230,  -230,  -230,   167,  -230,  -230,  -230,    61,  -230,  -230,
    -230,  -230,   611,  -230,   221,    56,   227,   148,   252,   256,
     251,   237,   146,  -230,  -230,   103,   524,  -230,   237,  -230,
      98,  -230,   611,   611,   140,  -230,   140,  -230,   255,   119,
     119,  -230,   140,  -230,    -1,   205,    85,  -230,   140,   398,
     276,   239,    89,   247,   245,   178,    38,    38,    38,   611,
     611,   253,  -230,  -230,  -230,  -230,  -230,   185,   244,   338,
     127,  -230,   110,   216,  -230,  -230,   234,   466,  -230,  -230,
    -230,  -230,   611,  -230,  -230,   611,  -230,  -230,  -230,  -230,
     611,  -230,  -230,   611,   611,   611,   611,   292,  -230,   254,
    -230,   611,   257,   116,   249,  -230,  -230,    53,  -230,   132,
     140,   140,  -230,    30,  -230,   611,  -230,   119,  -230,  -230,
     146,   553,  -230,   611,  -230,   119,   140,  -230,  -230,   243,
     248,   250,   258,  -230,  -230,   611,  -230,  -230,   262,   263,
     119,  -230,  -230,  -230,  -230,   611,   611,  -230,  -230,  -230,
     193,  -230,   221,    56,   227,   148,   252,   256,   300,   259,
    -230,  -230,   270,  -230,  -230,   255,  -230,  -230,  -230,  -230,
     142,    53,  -230,   285,  -230,  -230,  -230,  -230,   154,  -230,
     611,   611,   611,   611,  -230,  -230,  -230,   275,  -230,  -230,
    -230,   495,  -230,   272,   140,  -230,  -230,   164,   119,  -230,
    -230,  -230,  -230,  -230,  -230,   582,  -230,    70,   277,   -39,
     119,  -230,  -230,  -230,   278,  -230,  -230,  -230,  -230,   140,
    -230,  -230
  };

  const unsigned char
  parser::yydefact_[] =
  {
       3,     0,     0,     1,     0,     0,     0,     2,     5,    31,
       0,     4,     7,     0,     0,     0,     0,     0,     6,     0,
       0,     8,    35,    34,     0,    30,     0,     0,   182,     0,
      32,     0,    11,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   159,     0,   171,   158,   160,   161,     0,     0,
     127,     0,   170,   128,   129,   130,     0,   177,     0,     9,
       0,    13,     0,     0,     0,    12,     0,    19,     0,    36,
       0,     0,   162,     0,     0,     0,   135,   183,    18,    14,
       0,     0,     0,   131,    16,   132,   133,   134,     0,     0,
      94,    63,    64,    65,    66,    33,    68,    67,     0,     0,
      92,    93,    57,    59,     0,    41,    15,    56,    47,    48,
      49,    79,    58,    60,    61,    50,    42,    90,    80,    81,
      82,    99,     0,    40,   103,   109,   113,   115,   117,   119,
      95,     0,     0,    17,    10,     0,     0,   150,   149,   151,
       0,    38,     0,     0,     0,   137,     0,   136,     0,     0,
       0,   176,     0,   178,     0,     0,     0,   140,     0,     0,
       0,    52,    57,    41,     0,     0,     0,     0,     0,     0,
       0,     0,    20,    21,    22,    23,    24,    57,     0,     0,
       0,   184,     0,    62,    70,    69,     0,     0,    91,    96,
      97,    98,     0,   101,   102,     0,   105,   106,   107,   108,
       0,   111,   112,     0,     0,     0,     0,     0,    78,     0,
      52,     0,     0,     0,     0,   126,   125,   143,   145,     0,
       0,     0,   165,     0,   175,     0,   142,     0,   139,   148,
       0,     0,    51,     0,    54,     0,   169,   173,   174,     0,
       0,     0,     0,    29,    76,     0,    73,    74,     0,     0,
       0,    55,    85,    89,    88,     0,     0,    83,   153,   156,
       0,   100,   104,   110,   114,   116,   118,   120,    86,     0,
     152,    37,     0,   138,   144,     0,   147,   166,   167,   179,
     149,     0,   141,    71,    53,    43,    44,   180,     0,   168,
       0,     0,     0,     0,   164,    77,    75,     0,   185,   154,
     155,     0,    84,     0,     0,    39,   146,     0,     0,   172,
      25,    26,    27,    28,   157,     0,    87,     0,     0,     0,
       0,    72,   181,   163,     0,    45,   124,   122,   123,     0,
      46,   121
  };

  const short
  parser::yypgoto_[] =
  {
    -230,  -230,  -230,  -230,   312,  -230,   265,   286,    -7,  -230,
     151,  -230,  -230,  -230,  -230,  -230,   -13,    -4,   -24,  -230,
     288,    22,   124,   -49,  -230,  -230,   -81,    25,  -230,  -230,
      29,   152,  -230,  -230,  -230,  -230,  -230,  -230,  -230,  -230,
    -230,  -112,  -230,  -230,  -230,   138,  -230,   134,  -230,   129,
    -230,   133,   135,   139,  -230,    31,  -230,  -230,    27,   -61,
    -230,  -230,  -230,  -230,  -230,   120,    68,  -230,  -230,   -57,
     141,   204,    52,  -230,   219,  -230,  -230,   298,   113,   143,
    -229,   308,  -230,    67,  -230,  -230,  -230,  -230,  -230,  -230
  };

  const short
  parser::yydefgoto_[] =
  {
      -1,     1,     2,     5,     6,     7,    18,    33,    34,     8,
     171,   172,   173,   174,   175,   176,    50,   102,    37,   103,
      24,   104,   105,   164,   165,   317,   107,   108,   109,   110,
     111,   112,   113,   114,   115,   179,   116,   117,   118,   119,
     120,   121,   122,   123,   192,   124,   195,   125,   200,   126,
     203,   127,   128,   129,   130,   318,   329,    74,   131,   226,
      53,    54,    55,    85,   156,   157,   218,   219,    86,   132,
     139,   140,   259,   260,    44,    45,    46,    47,   181,   153,
     237,    28,   238,   239,    88,    19,   154,   288,    29,   182
  };

  const short
  parser::yytable_[] =
  {
      10,    84,    42,    26,    35,    87,   287,   144,   160,    20,
     188,     3,    27,    36,   106,   145,     9,    25,    30,    72,
      35,    31,    41,    41,   326,    35,    60,    58,    16,    36,
      17,   327,   328,     9,    36,     9,    25,    30,    76,    71,
      31,     9,   223,    26,    41,    41,   224,    71,    43,    51,
     178,   208,    27,    35,    52,   135,     9,    25,    41,    60,
     149,   150,    36,    80,    32,    22,    23,     9,    25,    30,
      51,    51,    31,     9,    25,    73,    75,   152,   155,   322,
     261,     9,    25,    59,    51,     9,    25,    30,   235,    83,
      31,    76,     9,    25,   162,   177,    15,   138,    87,    81,
     183,    48,   186,    82,    51,   253,     9,   187,    30,    75,
     178,    42,   193,   194,    40,    65,   146,    56,    48,     4,
      49,   323,     9,    57,   147,    16,   180,    17,   227,    69,
     249,    41,    70,   134,    69,   217,   228,   225,    11,    49,
      41,   211,    41,     9,    25,   220,   221,   212,    41,   283,
       9,    41,    30,   250,    41,   177,   274,    43,    41,   211,
      87,   251,   236,   236,   236,   272,    51,     9,    51,   138,
     146,   215,   207,   216,    51,   275,    89,    51,   147,   222,
      51,    12,    83,   276,    51,   229,    38,   207,    48,   222,
      49,    13,   136,    21,   137,   143,   159,   308,    91,    92,
      93,    94,    95,    96,    97,   309,   184,   185,     9,    25,
     136,   201,   202,    41,   159,    80,    41,    41,    61,   152,
      39,   233,   163,   281,    87,   234,    62,   245,    68,     9,
      69,   236,    41,    70,   240,   241,   301,   252,   138,    51,
     302,    63,    51,    51,    83,    64,   297,   277,   278,    40,
      69,    81,   280,   225,    79,    82,   149,   150,    51,    25,
     163,   141,   217,   289,   142,   143,   137,   214,    91,    92,
      93,    94,   148,   151,   189,   190,   191,    41,   204,   206,
     136,   158,   207,   205,   159,   196,   197,   198,   199,   230,
     231,  -176,   232,   242,   243,   246,   268,   244,   273,   307,
      41,   269,   271,    51,   236,   290,   295,   303,    83,   304,
     291,   258,   292,    41,   296,   305,   183,   245,   315,    14,
     293,   325,   330,    78,    66,    41,    51,    67,   316,   320,
     248,   319,   264,   262,   263,   137,   321,   265,   254,    51,
     266,     9,    25,   306,   319,   267,   213,   282,   324,   137,
      89,    51,   270,   314,   209,   285,   331,   286,   166,   167,
     168,   169,   133,   298,    77,     0,   279,    90,     0,   294,
     170,     0,    91,    92,    93,    94,    95,    96,    97,   299,
     300,     0,     0,     0,    98,     0,    48,     0,    99,   247,
       0,     0,     0,     0,   100,   101,     0,     0,     0,     0,
       0,     9,    25,     0,     0,     0,     0,     0,     0,     0,
      89,     0,     0,     0,   310,   311,   312,   313,   166,   167,
     168,   169,     0,     0,     0,   258,     0,    90,     0,     0,
     170,     0,    91,    92,    93,    94,    95,    96,    97,     0,
       9,    25,     0,     0,    98,     0,    48,     0,    99,    89,
       0,     0,     0,     0,   100,   101,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    90,   149,   150,     9,
      25,    91,    92,    93,    94,    95,    96,    97,    89,     0,
       0,     0,     0,    98,   161,    48,     0,    99,     0,     0,
       0,     0,     0,   100,   101,    90,   255,   256,     9,    25,
      91,    92,    93,    94,    95,    96,    97,    89,     0,     0,
       0,     0,   136,   257,    48,     0,    99,     0,     0,     0,
       0,     0,   100,   101,    90,   255,   256,     9,    25,    91,
      92,    93,    94,    95,    96,    97,    89,     0,     0,     0,
       0,   136,     0,    48,     0,    99,     0,     0,     0,     0,
       0,   100,   101,    90,     0,     0,     9,    25,    91,    92,
      93,    94,    95,    96,    97,    89,     0,     0,     0,     0,
      98,   210,    48,     0,    99,     0,     0,     0,     0,     0,
     100,   101,    90,     0,     0,     9,    25,    91,    92,    93,
      94,    95,    96,    97,    89,     0,     0,     0,     0,   136,
     284,    48,     0,    99,     0,     0,     0,     0,     0,   100,
     101,    90,     0,     0,     9,    25,    91,    92,    93,    94,
      95,    96,    97,    89,     0,     0,     0,     0,    98,     0,
      48,     0,    99,     0,     0,     0,     0,     0,   100,   101,
      90,     0,     0,     0,     0,    91,    92,    93,    94,    95,
      96,    97,     0,     0,     0,     0,     0,   136,     0,    48,
       0,    99,     0,     0,     0,     0,     0,   100,   101
  };

  const short
  parser::yycheck_[] =
  {
       4,    62,    26,    16,    17,    62,   235,    43,    89,    13,
     122,     0,    16,    17,    63,    51,     3,     4,     5,    43,
      33,     8,    26,    27,    63,    38,    33,    31,    48,    33,
      50,    70,    71,     3,    38,     3,     4,     5,    51,    43,
       8,     3,    43,    56,    48,    49,    47,    51,    26,    27,
      99,   132,    56,    66,    27,    68,     3,     4,    62,    66,
      30,    31,    66,    10,    51,    39,    40,     3,     4,     5,
      48,    49,     8,     3,     4,    48,    49,    81,    82,   308,
     192,     3,     4,    51,    62,     3,     4,     5,    50,    62,
       8,   104,     3,     4,    98,    99,    19,    70,   155,    46,
     104,    48,    41,    50,    82,   186,     3,    46,     5,    82,
     159,   135,    56,    57,    11,    51,    43,    43,    48,     8,
      50,    51,     3,    49,    51,    48,    99,    50,    43,    45,
     179,   135,    48,    51,    45,   148,    51,    48,    44,    50,
     144,    43,   146,     3,     4,   149,   150,    49,   152,   230,
       3,   155,     5,    43,   158,   159,   217,   135,   162,    43,
     217,    51,   166,   167,   168,    49,   144,     3,   146,   142,
      43,   144,    45,   146,   152,    43,    12,   155,    51,   152,
     158,    44,   155,    51,   162,   158,    50,    45,    48,   162,
      50,     8,    46,    44,    70,    53,    50,    43,    34,    35,
      36,    37,    38,    39,    40,    51,    39,    40,     3,     4,
      46,    63,    64,   217,    50,    10,   220,   221,    44,   223,
      33,    43,    98,   227,   281,    47,    45,    42,    46,     3,
      45,   235,   236,    48,   167,   168,    43,     3,   211,   217,
      47,    45,   220,   221,   217,    45,   250,   220,   221,    11,
      45,    46,   225,    48,    44,    50,    30,    31,   236,     4,
     136,    45,   275,   236,    48,    53,   142,   143,    34,    35,
      36,    37,    50,    47,    53,    54,    55,   281,    26,    28,
      46,    52,    45,    27,    50,    58,    59,    60,    61,    13,
      43,    52,    47,   169,   170,    51,     4,    44,    49,    14,
     304,    47,    45,   281,   308,    62,    44,     7,   281,    50,
      62,   187,    62,   317,    51,    45,   320,    42,    46,     7,
      62,    44,    44,    58,    38,   329,   304,    39,   303,   307,
     179,   304,   203,   195,   200,   211,   307,   204,   186,   317,
     205,     3,     4,   275,   317,   206,   142,   227,   317,   225,
      12,   329,   211,   301,   135,   231,   329,   233,    20,    21,
      22,    23,    64,   250,    56,    -1,   223,    29,    -1,   245,
      32,    -1,    34,    35,    36,    37,    38,    39,    40,   255,
     256,    -1,    -1,    -1,    46,    -1,    48,    -1,    50,    51,
      -1,    -1,    -1,    -1,    56,    57,    -1,    -1,    -1,    -1,
      -1,     3,     4,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      12,    -1,    -1,    -1,   290,   291,   292,   293,    20,    21,
      22,    23,    -1,    -1,    -1,   301,    -1,    29,    -1,    -1,
      32,    -1,    34,    35,    36,    37,    38,    39,    40,    -1,
       3,     4,    -1,    -1,    46,    -1,    48,    -1,    50,    12,
      -1,    -1,    -1,    -1,    56,    57,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    29,    30,    31,     3,
       4,    34,    35,    36,    37,    38,    39,    40,    12,    -1,
      -1,    -1,    -1,    46,    47,    48,    -1,    50,    -1,    -1,
      -1,    -1,    -1,    56,    57,    29,    30,    31,     3,     4,
      34,    35,    36,    37,    38,    39,    40,    12,    -1,    -1,
      -1,    -1,    46,    47,    48,    -1,    50,    -1,    -1,    -1,
      -1,    -1,    56,    57,    29,    30,    31,     3,     4,    34,
      35,    36,    37,    38,    39,    40,    12,    -1,    -1,    -1,
      -1,    46,    -1,    48,    -1,    50,    -1,    -1,    -1,    -1,
      -1,    56,    57,    29,    -1,    -1,     3,     4,    34,    35,
      36,    37,    38,    39,    40,    12,    -1,    -1,    -1,    -1,
      46,    47,    48,    -1,    50,    -1,    -1,    -1,    -1,    -1,
      56,    57,    29,    -1,    -1,     3,     4,    34,    35,    36,
      37,    38,    39,    40,    12,    -1,    -1,    -1,    -1,    46,
      47,    48,    -1,    50,    -1,    -1,    -1,    -1,    -1,    56,
      57,    29,    -1,    -1,     3,     4,    34,    35,    36,    37,
      38,    39,    40,    12,    -1,    -1,    -1,    -1,    46,    -1,
      48,    -1,    50,    -1,    -1,    -1,    -1,    -1,    56,    57,
      29,    -1,    -1,    -1,    -1,    34,    35,    36,    37,    38,
      39,    40,    -1,    -1,    -1,    -1,    -1,    46,    -1,    48,
      -1,    50,    -1,    -1,    -1,    -1,    -1,    56,    57
  };

  const unsigned char
  parser::yystos_[] =
  {
       0,    74,    75,     0,     8,    76,    77,    78,    82,     3,
      90,    44,    44,     8,    77,    19,    48,    50,    79,   158,
      90,    44,    39,    40,    93,     4,    89,    90,   154,   161,
       5,     8,    51,    80,    81,    89,    90,    91,    50,    33,
      11,    90,    91,    94,   147,   148,   149,   150,    48,    50,
      89,    94,   131,   133,   134,   135,    43,    49,    90,    51,
      81,    44,    45,    45,    45,    51,    80,    93,    46,    45,
      48,    90,    91,   131,   130,   131,    89,   154,    79,    44,
      10,    46,    50,   131,   132,   136,   141,   142,   157,    12,
      29,    34,    35,    36,    37,    38,    39,    40,    46,    50,
      56,    57,    90,    92,    94,    95,    96,    99,   100,   101,
     102,   103,   104,   105,   106,   107,   109,   110,   111,   112,
     113,   114,   115,   116,   118,   120,   122,   124,   125,   126,
     127,   131,   142,   150,    51,    89,    46,    95,   131,   143,
     144,    45,    48,    53,    43,    51,    43,    51,    50,    30,
      31,    47,    90,   152,   159,    90,   137,   138,    52,    50,
      99,    47,    90,    95,    96,    97,    20,    21,    22,    23,
      32,    83,    84,    85,    86,    87,    88,    90,    96,   108,
     131,   151,   162,    90,    39,    40,    41,    46,   114,    53,
      54,    55,   117,    56,    57,   119,    58,    59,    60,    61,
     121,    63,    64,   123,    26,    27,    28,    45,    99,   147,
      47,    43,    49,   144,    95,   131,   131,    89,   139,   140,
      90,    90,   131,    43,    47,    48,   132,    43,    51,   131,
      13,    43,    47,    43,    47,    50,    90,   153,   155,   156,
     156,   156,    95,    95,    44,    42,    51,    51,    83,    96,
      43,    51,     3,    99,   104,    30,    31,    47,    95,   145,
     146,   114,   118,   120,   122,   124,   125,   126,     4,    47,
     143,    45,    49,    49,   132,    43,    51,   131,   131,   152,
     131,    90,   138,    99,    47,    95,    95,   153,   160,   131,
      62,    62,    62,    62,    95,    44,    51,    90,   151,    95,
      95,    43,    47,     7,    50,    45,   139,    14,    43,    51,
      95,    95,    95,    95,   145,    46,   100,    98,   128,   131,
      94,   103,   153,    51,   128,    44,    63,    70,    71,   129,
      44,   131
  };

  const unsigned char
  parser::yyr1_[] =
  {
       0,    73,    74,    75,    75,    76,    77,    78,    78,    79,
      79,    79,    79,    80,    80,    81,    81,    81,    81,    82,
      83,    83,    83,    83,    83,    84,    85,    86,    87,    88,
      89,    90,    91,    92,    93,    93,    94,    94,    94,    94,
      95,    96,    96,    97,    97,    98,    98,    99,    99,    99,
      99,   100,   101,   101,   101,   102,   103,   103,   103,   103,
     103,   103,   103,   104,   104,   104,   104,   105,   105,   105,
     105,   106,   106,   107,   107,   107,   108,   108,   109,   110,
     110,   110,   110,   111,   111,   112,   112,   112,   113,   113,
     114,   114,   115,   115,   115,   116,   117,   117,   117,   118,
     118,   119,   119,   120,   120,   121,   121,   121,   121,   122,
     122,   123,   123,   124,   124,   125,   125,   126,   126,   127,
     127,   128,   129,   129,   129,   130,   130,   131,   131,   131,
     131,   132,   132,   132,   132,   133,   134,   134,   135,   136,
     137,   137,   138,   139,   139,   140,   140,   141,   142,   143,
     143,   144,   144,   145,   145,   145,   146,   146,   147,   148,
     148,   148,   149,   150,   151,   152,   152,   152,   153,   153,
     154,   154,   155,   156,   156,   157,   157,   158,   159,   159,
     160,   160,   161,   161,   162,   162
  };

  const signed char
  parser::yyr2_[] =
  {
       0,     2,     2,     0,     3,     1,     3,     2,     3,     3,
       4,     2,     3,     2,     3,     3,     3,     3,     3,     6,
       1,     1,     1,     1,     1,     4,     4,     4,     4,     2,
       1,     1,     1,     1,     1,     1,     2,     5,     3,     6,
       1,     1,     1,     3,     3,     2,     3,     1,     1,     1,
       1,     3,     2,     4,     3,     3,     1,     1,     1,     1,
       1,     1,     2,     1,     1,     1,     1,     1,     1,     2,
       2,     4,     6,     3,     3,     4,     2,     3,     2,     1,
       1,     1,     1,     3,     4,     3,     3,     5,     3,     3,
       1,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       3,     1,     1,     1,     3,     1,     1,     1,     1,     1,
       3,     1,     1,     1,     3,     1,     3,     1,     3,     1,
       3,     3,     1,     1,     1,     3,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     2,     3,     3,     5,     3,
       1,     3,     2,     1,     2,     1,     3,     4,     3,     1,
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
  "\"const\"", "\"val\"", "\"var\"", "\"set\"", "\"func\"", "\"lambda\"",
  "\"and\"", "\"xor\"", "\"or\"", "\"not\"", "\"out\"", "\"inout\"",
  "\"discard\"", "\"as\"", "\"42\"", "\"0x2a\"", "\"42u\"", "\"0x2Au\"",
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
  "expr_cl2", "type_query_exp_sl", "bracketed_exp", "paren_exp",
  "vtupleExpr", "vstructExpr", "primary_exp", "int_expr", "stringls",
  "if_exp", "chain_exp", "chain_prefix", "lambda_exp", "postfix_exp",
  "vcall_exp", "dot_name_exp", "dot_index_exp", "unary_exp", "unary_op",
  "binary_exp", "mul_binary_op", "mul_binary_exp", "add_binary_op",
  "add_binary_exp", "cmp_binary_op", "cmp_binary_exp", "eq_binary_op",
  "eq_binary_exp", "and_binary_exp", "xor_binary_exp", "or_binary_exp",
  "type_query_exp", "type_query_op", "type_spec_cl2", "type_spec",
  "long_type_spec", "mod_prefix_tid", "tuple_type_spec", "array_type_spec",
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
       0,   271,   271,   279,   280,   283,   287,   290,   291,   299,
     300,   301,   302,   305,   306,   309,   310,   311,   312,   320,
     324,   325,   326,   327,   328,   331,   334,   337,   340,   343,
     350,   351,   352,   355,   358,   359,   362,   363,   364,   365,
     372,   375,   376,   388,   389,   392,   393,   397,   398,   399,
     400,   411,   414,   415,   416,   419,   422,   423,   424,   425,
     426,   427,   428,   431,   432,   433,   434,   437,   438,   439,
     440,   443,   444,   447,   448,   449,   452,   453,   456,   460,
     461,   462,   463,   466,   467,   470,   471,   472,   475,   476,
     480,   481,   484,   485,   486,   490,   493,   494,   495,   498,
     499,   502,   503,   506,   507,   510,   511,   512,   513,   516,
     517,   520,   521,   524,   525,   528,   529,   532,   533,   536,
     537,   541,   544,   545,   546,   561,   562,   566,   567,   568,
     569,   572,   573,   574,   575,   579,   583,   584,   587,   591,
     594,   595,   598,   602,   603,   606,   607,   610,   614,   618,
     619,   622,   623,   625,   626,   627,   630,   631,   641,   644,
     645,   646,   649,   654,   662,   665,   666,   667,   670,   671,
     674,   675,   679,   682,   683,   686,   687,   690,   694,   695,
     698,   699,   702,   703,   706,   707
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
      65,    66,    67,    68,    69,    70,    71,    72
    };
    // Last valid token kind.
    const int code_max = 327;

    if (t <= 0)
      return symbol_kind::S_YYEOF;
    else if (t <= code_max)
      return YY_CAST (symbol_kind_type, translate_table[t]);
    else
      return symbol_kind::S_YYUNDEF;
  }

#line 11 "parser.yy"
} } // pdm::parser
#line 4023 "parser.tab.cc"

#line 710 "parser.yy"


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

int yylex(pdm::parser::parser::semantic_type* semval, pdm::source::Loc* llocp, pdm::source::Source* source, pdm::parser::Lexer* lexer) {
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
