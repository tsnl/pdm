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
#line 66 "parser.yy"

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

#line 19 "parser.yy"
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

      case symbol_kind::S_mul_binary_op: // mul_binary_op
      case symbol_kind::S_add_binary_op: // add_binary_op
      case symbol_kind::S_cmp_binary_op: // cmp_binary_op
      case symbol_kind::S_eq_binary_op: // eq_binary_op
        value.copy< pdm::ast::BinaryOperator > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_class_spec: // class_spec
      case symbol_kind::S_primary_class_spec: // primary_class_spec
      case symbol_kind::S_postfix_class_spec: // postfix_class_spec
        value.copy< pdm::ast::ClassSpec* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr: // expr
      case symbol_kind::S_long_exp: // long_exp
      case symbol_kind::S_bracketed_exp: // bracketed_exp
      case symbol_kind::S_unit_exp: // unit_exp
      case symbol_kind::S_paren_exp: // paren_exp
      case symbol_kind::S_vtupleExpr: // vtupleExpr
      case symbol_kind::S_vstructExpr: // vstructExpr
      case symbol_kind::S_primary_exp: // primary_exp
      case symbol_kind::S_int_expr: // int_expr
      case symbol_kind::S_if_exp: // if_exp
      case symbol_kind::S_chain_exp: // chain_exp
      case symbol_kind::S_lambda_exp: // lambda_exp
      case symbol_kind::S_postfix_exp: // postfix_exp
      case symbol_kind::S_tcall_exp: // tcall_exp
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

      case symbol_kind::S_destructured_lpattern: // destructured_lpattern
      case symbol_kind::S_lpattern: // lpattern
        value.copy< pdm::ast::LPattern* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_lpattern_field: // lpattern_field
        value.copy< pdm::ast::LPattern::Field* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_sub_mod_stmt: // sub_mod_stmt
      case symbol_kind::S_mod_content_stmt: // mod_content_stmt
      case symbol_kind::S_mod_val_stmt: // mod_val_stmt
      case symbol_kind::S_mod_type_stmt: // mod_type_stmt
      case symbol_kind::S_mod_enum_stmt: // mod_enum_stmt
      case symbol_kind::S_mod_typeclass_stmt: // mod_typeclass_stmt
        value.copy< pdm::ast::ModContentStmt* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_enum_field: // enum_field
        value.copy< pdm::ast::ModEnumStmt::Field* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_script_body_stmt: // script_body_stmt
      case symbol_kind::S_top_mod_stmt: // top_mod_stmt
        value.copy< pdm::ast::ModStmt* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_script: // script
        value.copy< pdm::ast::Script* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_script_head_stmt: // script_head_stmt
      case symbol_kind::S_import_stmt: // import_stmt
      case symbol_kind::S_extern_stmt: // extern_stmt
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
      case symbol_kind::S_primary_type_spec: // primary_type_spec
      case symbol_kind::S_paren_type_spec: // paren_type_spec
      case symbol_kind::S_tuple_type_spec: // tuple_type_spec
      case symbol_kind::S_mod_prefix_tid: // mod_prefix_tid
      case symbol_kind::S_fn_type_spec: // fn_type_spec
      case symbol_kind::S_postfix_type_spec: // postfix_type_spec
      case symbol_kind::S_tcall_type_spec: // tcall_type_spec
      case symbol_kind::S_unary_type_spec: // unary_type_spec
      case symbol_kind::S_long_type_spec: // long_type_spec
      case symbol_kind::S_struct_type_spec: // struct_type_spec
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

      case symbol_kind::S_expr_cl0: // expr_cl0
      case symbol_kind::S_expr_cl2: // expr_cl2
        value.copy< std::vector<pdm::ast::Exp*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_lpattern_field_cl: // lpattern_field_cl
        value.copy< std::vector<pdm::ast::LPattern::Field*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_mod_content: // mod_content
        value.copy< std::vector<pdm::ast::ModContentStmt*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_enum_field_pl: // enum_field_pl
      case symbol_kind::S_unprefixed_enum_field_pl: // unprefixed_enum_field_pl
        value.copy< std::vector<pdm::ast::ModEnumStmt::Field*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_script_body: // script_body
        value.copy< std::vector<pdm::ast::ModStmt*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_script_head: // script_head
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

      case symbol_kind::S_tpattern_seq: // tpattern_seq
        value.copy< std::vector<pdm::ast::TPattern*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_tpattern_field_cl: // tpattern_field_cl
        value.copy< std::vector<pdm::ast::TPattern::Field*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_type_query_exp_sl: // type_query_exp_sl
        value.copy< std::vector<pdm::ast::TypeQueryExp*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_type_spec_cl1: // type_spec_cl1
      case symbol_kind::S_type_spec_cl2: // type_spec_cl2
        value.copy< std::vector<pdm::ast::TypeSpec*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_varg_cl: // varg_cl
        value.copy< std::vector<pdm::ast::VArg*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_vpattern_field_cl: // vpattern_field_cl
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

      case symbol_kind::S_mul_binary_op: // mul_binary_op
      case symbol_kind::S_add_binary_op: // add_binary_op
      case symbol_kind::S_cmp_binary_op: // cmp_binary_op
      case symbol_kind::S_eq_binary_op: // eq_binary_op
        value.move< pdm::ast::BinaryOperator > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_class_spec: // class_spec
      case symbol_kind::S_primary_class_spec: // primary_class_spec
      case symbol_kind::S_postfix_class_spec: // postfix_class_spec
        value.move< pdm::ast::ClassSpec* > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_expr: // expr
      case symbol_kind::S_long_exp: // long_exp
      case symbol_kind::S_bracketed_exp: // bracketed_exp
      case symbol_kind::S_unit_exp: // unit_exp
      case symbol_kind::S_paren_exp: // paren_exp
      case symbol_kind::S_vtupleExpr: // vtupleExpr
      case symbol_kind::S_vstructExpr: // vstructExpr
      case symbol_kind::S_primary_exp: // primary_exp
      case symbol_kind::S_int_expr: // int_expr
      case symbol_kind::S_if_exp: // if_exp
      case symbol_kind::S_chain_exp: // chain_exp
      case symbol_kind::S_lambda_exp: // lambda_exp
      case symbol_kind::S_postfix_exp: // postfix_exp
      case symbol_kind::S_tcall_exp: // tcall_exp
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

      case symbol_kind::S_destructured_lpattern: // destructured_lpattern
      case symbol_kind::S_lpattern: // lpattern
        value.move< pdm::ast::LPattern* > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_lpattern_field: // lpattern_field
        value.move< pdm::ast::LPattern::Field* > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_sub_mod_stmt: // sub_mod_stmt
      case symbol_kind::S_mod_content_stmt: // mod_content_stmt
      case symbol_kind::S_mod_val_stmt: // mod_val_stmt
      case symbol_kind::S_mod_type_stmt: // mod_type_stmt
      case symbol_kind::S_mod_enum_stmt: // mod_enum_stmt
      case symbol_kind::S_mod_typeclass_stmt: // mod_typeclass_stmt
        value.move< pdm::ast::ModContentStmt* > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_enum_field: // enum_field
        value.move< pdm::ast::ModEnumStmt::Field* > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_script_body_stmt: // script_body_stmt
      case symbol_kind::S_top_mod_stmt: // top_mod_stmt
        value.move< pdm::ast::ModStmt* > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_script: // script
        value.move< pdm::ast::Script* > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_script_head_stmt: // script_head_stmt
      case symbol_kind::S_import_stmt: // import_stmt
      case symbol_kind::S_extern_stmt: // extern_stmt
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
      case symbol_kind::S_primary_type_spec: // primary_type_spec
      case symbol_kind::S_paren_type_spec: // paren_type_spec
      case symbol_kind::S_tuple_type_spec: // tuple_type_spec
      case symbol_kind::S_mod_prefix_tid: // mod_prefix_tid
      case symbol_kind::S_fn_type_spec: // fn_type_spec
      case symbol_kind::S_postfix_type_spec: // postfix_type_spec
      case symbol_kind::S_tcall_type_spec: // tcall_type_spec
      case symbol_kind::S_unary_type_spec: // unary_type_spec
      case symbol_kind::S_long_type_spec: // long_type_spec
      case symbol_kind::S_struct_type_spec: // struct_type_spec
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

      case symbol_kind::S_expr_cl0: // expr_cl0
      case symbol_kind::S_expr_cl2: // expr_cl2
        value.move< std::vector<pdm::ast::Exp*> > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_lpattern_field_cl: // lpattern_field_cl
        value.move< std::vector<pdm::ast::LPattern::Field*> > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_mod_content: // mod_content
        value.move< std::vector<pdm::ast::ModContentStmt*> > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_enum_field_pl: // enum_field_pl
      case symbol_kind::S_unprefixed_enum_field_pl: // unprefixed_enum_field_pl
        value.move< std::vector<pdm::ast::ModEnumStmt::Field*> > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_script_body: // script_body
        value.move< std::vector<pdm::ast::ModStmt*> > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_script_head: // script_head
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

      case symbol_kind::S_tpattern_seq: // tpattern_seq
        value.move< std::vector<pdm::ast::TPattern*> > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_tpattern_field_cl: // tpattern_field_cl
        value.move< std::vector<pdm::ast::TPattern::Field*> > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_type_query_exp_sl: // type_query_exp_sl
        value.move< std::vector<pdm::ast::TypeQueryExp*> > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_type_spec_cl1: // type_spec_cl1
      case symbol_kind::S_type_spec_cl2: // type_spec_cl2
        value.move< std::vector<pdm::ast::TypeSpec*> > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_varg_cl: // varg_cl
        value.move< std::vector<pdm::ast::VArg*> > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_vpattern_field_cl: // vpattern_field_cl
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

      case symbol_kind::S_mul_binary_op: // mul_binary_op
      case symbol_kind::S_add_binary_op: // add_binary_op
      case symbol_kind::S_cmp_binary_op: // cmp_binary_op
      case symbol_kind::S_eq_binary_op: // eq_binary_op
        value.YY_MOVE_OR_COPY< pdm::ast::BinaryOperator > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_class_spec: // class_spec
      case symbol_kind::S_primary_class_spec: // primary_class_spec
      case symbol_kind::S_postfix_class_spec: // postfix_class_spec
        value.YY_MOVE_OR_COPY< pdm::ast::ClassSpec* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr: // expr
      case symbol_kind::S_long_exp: // long_exp
      case symbol_kind::S_bracketed_exp: // bracketed_exp
      case symbol_kind::S_unit_exp: // unit_exp
      case symbol_kind::S_paren_exp: // paren_exp
      case symbol_kind::S_vtupleExpr: // vtupleExpr
      case symbol_kind::S_vstructExpr: // vstructExpr
      case symbol_kind::S_primary_exp: // primary_exp
      case symbol_kind::S_int_expr: // int_expr
      case symbol_kind::S_if_exp: // if_exp
      case symbol_kind::S_chain_exp: // chain_exp
      case symbol_kind::S_lambda_exp: // lambda_exp
      case symbol_kind::S_postfix_exp: // postfix_exp
      case symbol_kind::S_tcall_exp: // tcall_exp
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

      case symbol_kind::S_destructured_lpattern: // destructured_lpattern
      case symbol_kind::S_lpattern: // lpattern
        value.YY_MOVE_OR_COPY< pdm::ast::LPattern* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_lpattern_field: // lpattern_field
        value.YY_MOVE_OR_COPY< pdm::ast::LPattern::Field* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_sub_mod_stmt: // sub_mod_stmt
      case symbol_kind::S_mod_content_stmt: // mod_content_stmt
      case symbol_kind::S_mod_val_stmt: // mod_val_stmt
      case symbol_kind::S_mod_type_stmt: // mod_type_stmt
      case symbol_kind::S_mod_enum_stmt: // mod_enum_stmt
      case symbol_kind::S_mod_typeclass_stmt: // mod_typeclass_stmt
        value.YY_MOVE_OR_COPY< pdm::ast::ModContentStmt* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_enum_field: // enum_field
        value.YY_MOVE_OR_COPY< pdm::ast::ModEnumStmt::Field* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_script_body_stmt: // script_body_stmt
      case symbol_kind::S_top_mod_stmt: // top_mod_stmt
        value.YY_MOVE_OR_COPY< pdm::ast::ModStmt* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_script: // script
        value.YY_MOVE_OR_COPY< pdm::ast::Script* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_script_head_stmt: // script_head_stmt
      case symbol_kind::S_import_stmt: // import_stmt
      case symbol_kind::S_extern_stmt: // extern_stmt
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
      case symbol_kind::S_primary_type_spec: // primary_type_spec
      case symbol_kind::S_paren_type_spec: // paren_type_spec
      case symbol_kind::S_tuple_type_spec: // tuple_type_spec
      case symbol_kind::S_mod_prefix_tid: // mod_prefix_tid
      case symbol_kind::S_fn_type_spec: // fn_type_spec
      case symbol_kind::S_postfix_type_spec: // postfix_type_spec
      case symbol_kind::S_tcall_type_spec: // tcall_type_spec
      case symbol_kind::S_unary_type_spec: // unary_type_spec
      case symbol_kind::S_long_type_spec: // long_type_spec
      case symbol_kind::S_struct_type_spec: // struct_type_spec
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

      case symbol_kind::S_expr_cl0: // expr_cl0
      case symbol_kind::S_expr_cl2: // expr_cl2
        value.YY_MOVE_OR_COPY< std::vector<pdm::ast::Exp*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_lpattern_field_cl: // lpattern_field_cl
        value.YY_MOVE_OR_COPY< std::vector<pdm::ast::LPattern::Field*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_mod_content: // mod_content
        value.YY_MOVE_OR_COPY< std::vector<pdm::ast::ModContentStmt*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_enum_field_pl: // enum_field_pl
      case symbol_kind::S_unprefixed_enum_field_pl: // unprefixed_enum_field_pl
        value.YY_MOVE_OR_COPY< std::vector<pdm::ast::ModEnumStmt::Field*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_script_body: // script_body
        value.YY_MOVE_OR_COPY< std::vector<pdm::ast::ModStmt*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_script_head: // script_head
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

      case symbol_kind::S_tpattern_seq: // tpattern_seq
        value.YY_MOVE_OR_COPY< std::vector<pdm::ast::TPattern*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_tpattern_field_cl: // tpattern_field_cl
        value.YY_MOVE_OR_COPY< std::vector<pdm::ast::TPattern::Field*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_type_query_exp_sl: // type_query_exp_sl
        value.YY_MOVE_OR_COPY< std::vector<pdm::ast::TypeQueryExp*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_type_spec_cl1: // type_spec_cl1
      case symbol_kind::S_type_spec_cl2: // type_spec_cl2
        value.YY_MOVE_OR_COPY< std::vector<pdm::ast::TypeSpec*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_varg_cl: // varg_cl
        value.YY_MOVE_OR_COPY< std::vector<pdm::ast::VArg*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_vpattern_field_cl: // vpattern_field_cl
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

      case symbol_kind::S_mul_binary_op: // mul_binary_op
      case symbol_kind::S_add_binary_op: // add_binary_op
      case symbol_kind::S_cmp_binary_op: // cmp_binary_op
      case symbol_kind::S_eq_binary_op: // eq_binary_op
        value.move< pdm::ast::BinaryOperator > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_class_spec: // class_spec
      case symbol_kind::S_primary_class_spec: // primary_class_spec
      case symbol_kind::S_postfix_class_spec: // postfix_class_spec
        value.move< pdm::ast::ClassSpec* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr: // expr
      case symbol_kind::S_long_exp: // long_exp
      case symbol_kind::S_bracketed_exp: // bracketed_exp
      case symbol_kind::S_unit_exp: // unit_exp
      case symbol_kind::S_paren_exp: // paren_exp
      case symbol_kind::S_vtupleExpr: // vtupleExpr
      case symbol_kind::S_vstructExpr: // vstructExpr
      case symbol_kind::S_primary_exp: // primary_exp
      case symbol_kind::S_int_expr: // int_expr
      case symbol_kind::S_if_exp: // if_exp
      case symbol_kind::S_chain_exp: // chain_exp
      case symbol_kind::S_lambda_exp: // lambda_exp
      case symbol_kind::S_postfix_exp: // postfix_exp
      case symbol_kind::S_tcall_exp: // tcall_exp
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

      case symbol_kind::S_destructured_lpattern: // destructured_lpattern
      case symbol_kind::S_lpattern: // lpattern
        value.move< pdm::ast::LPattern* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_lpattern_field: // lpattern_field
        value.move< pdm::ast::LPattern::Field* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_sub_mod_stmt: // sub_mod_stmt
      case symbol_kind::S_mod_content_stmt: // mod_content_stmt
      case symbol_kind::S_mod_val_stmt: // mod_val_stmt
      case symbol_kind::S_mod_type_stmt: // mod_type_stmt
      case symbol_kind::S_mod_enum_stmt: // mod_enum_stmt
      case symbol_kind::S_mod_typeclass_stmt: // mod_typeclass_stmt
        value.move< pdm::ast::ModContentStmt* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_enum_field: // enum_field
        value.move< pdm::ast::ModEnumStmt::Field* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_script_body_stmt: // script_body_stmt
      case symbol_kind::S_top_mod_stmt: // top_mod_stmt
        value.move< pdm::ast::ModStmt* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_script: // script
        value.move< pdm::ast::Script* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_script_head_stmt: // script_head_stmt
      case symbol_kind::S_import_stmt: // import_stmt
      case symbol_kind::S_extern_stmt: // extern_stmt
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
      case symbol_kind::S_primary_type_spec: // primary_type_spec
      case symbol_kind::S_paren_type_spec: // paren_type_spec
      case symbol_kind::S_tuple_type_spec: // tuple_type_spec
      case symbol_kind::S_mod_prefix_tid: // mod_prefix_tid
      case symbol_kind::S_fn_type_spec: // fn_type_spec
      case symbol_kind::S_postfix_type_spec: // postfix_type_spec
      case symbol_kind::S_tcall_type_spec: // tcall_type_spec
      case symbol_kind::S_unary_type_spec: // unary_type_spec
      case symbol_kind::S_long_type_spec: // long_type_spec
      case symbol_kind::S_struct_type_spec: // struct_type_spec
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

      case symbol_kind::S_expr_cl0: // expr_cl0
      case symbol_kind::S_expr_cl2: // expr_cl2
        value.move< std::vector<pdm::ast::Exp*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_lpattern_field_cl: // lpattern_field_cl
        value.move< std::vector<pdm::ast::LPattern::Field*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_mod_content: // mod_content
        value.move< std::vector<pdm::ast::ModContentStmt*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_enum_field_pl: // enum_field_pl
      case symbol_kind::S_unprefixed_enum_field_pl: // unprefixed_enum_field_pl
        value.move< std::vector<pdm::ast::ModEnumStmt::Field*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_script_body: // script_body
        value.move< std::vector<pdm::ast::ModStmt*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_script_head: // script_head
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

      case symbol_kind::S_tpattern_seq: // tpattern_seq
        value.move< std::vector<pdm::ast::TPattern*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_tpattern_field_cl: // tpattern_field_cl
        value.move< std::vector<pdm::ast::TPattern::Field*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_type_query_exp_sl: // type_query_exp_sl
        value.move< std::vector<pdm::ast::TypeQueryExp*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_type_spec_cl1: // type_spec_cl1
      case symbol_kind::S_type_spec_cl2: // type_spec_cl2
        value.move< std::vector<pdm::ast::TypeSpec*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_varg_cl: // varg_cl
        value.move< std::vector<pdm::ast::VArg*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_vpattern_field_cl: // vpattern_field_cl
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

      case symbol_kind::S_mul_binary_op: // mul_binary_op
      case symbol_kind::S_add_binary_op: // add_binary_op
      case symbol_kind::S_cmp_binary_op: // cmp_binary_op
      case symbol_kind::S_eq_binary_op: // eq_binary_op
        value.copy< pdm::ast::BinaryOperator > (that.value);
        break;

      case symbol_kind::S_class_spec: // class_spec
      case symbol_kind::S_primary_class_spec: // primary_class_spec
      case symbol_kind::S_postfix_class_spec: // postfix_class_spec
        value.copy< pdm::ast::ClassSpec* > (that.value);
        break;

      case symbol_kind::S_expr: // expr
      case symbol_kind::S_long_exp: // long_exp
      case symbol_kind::S_bracketed_exp: // bracketed_exp
      case symbol_kind::S_unit_exp: // unit_exp
      case symbol_kind::S_paren_exp: // paren_exp
      case symbol_kind::S_vtupleExpr: // vtupleExpr
      case symbol_kind::S_vstructExpr: // vstructExpr
      case symbol_kind::S_primary_exp: // primary_exp
      case symbol_kind::S_int_expr: // int_expr
      case symbol_kind::S_if_exp: // if_exp
      case symbol_kind::S_chain_exp: // chain_exp
      case symbol_kind::S_lambda_exp: // lambda_exp
      case symbol_kind::S_postfix_exp: // postfix_exp
      case symbol_kind::S_tcall_exp: // tcall_exp
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

      case symbol_kind::S_destructured_lpattern: // destructured_lpattern
      case symbol_kind::S_lpattern: // lpattern
        value.copy< pdm::ast::LPattern* > (that.value);
        break;

      case symbol_kind::S_lpattern_field: // lpattern_field
        value.copy< pdm::ast::LPattern::Field* > (that.value);
        break;

      case symbol_kind::S_sub_mod_stmt: // sub_mod_stmt
      case symbol_kind::S_mod_content_stmt: // mod_content_stmt
      case symbol_kind::S_mod_val_stmt: // mod_val_stmt
      case symbol_kind::S_mod_type_stmt: // mod_type_stmt
      case symbol_kind::S_mod_enum_stmt: // mod_enum_stmt
      case symbol_kind::S_mod_typeclass_stmt: // mod_typeclass_stmt
        value.copy< pdm::ast::ModContentStmt* > (that.value);
        break;

      case symbol_kind::S_enum_field: // enum_field
        value.copy< pdm::ast::ModEnumStmt::Field* > (that.value);
        break;

      case symbol_kind::S_script_body_stmt: // script_body_stmt
      case symbol_kind::S_top_mod_stmt: // top_mod_stmt
        value.copy< pdm::ast::ModStmt* > (that.value);
        break;

      case symbol_kind::S_script: // script
        value.copy< pdm::ast::Script* > (that.value);
        break;

      case symbol_kind::S_script_head_stmt: // script_head_stmt
      case symbol_kind::S_import_stmt: // import_stmt
      case symbol_kind::S_extern_stmt: // extern_stmt
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
      case symbol_kind::S_primary_type_spec: // primary_type_spec
      case symbol_kind::S_paren_type_spec: // paren_type_spec
      case symbol_kind::S_tuple_type_spec: // tuple_type_spec
      case symbol_kind::S_mod_prefix_tid: // mod_prefix_tid
      case symbol_kind::S_fn_type_spec: // fn_type_spec
      case symbol_kind::S_postfix_type_spec: // postfix_type_spec
      case symbol_kind::S_tcall_type_spec: // tcall_type_spec
      case symbol_kind::S_unary_type_spec: // unary_type_spec
      case symbol_kind::S_long_type_spec: // long_type_spec
      case symbol_kind::S_struct_type_spec: // struct_type_spec
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

      case symbol_kind::S_expr_cl0: // expr_cl0
      case symbol_kind::S_expr_cl2: // expr_cl2
        value.copy< std::vector<pdm::ast::Exp*> > (that.value);
        break;

      case symbol_kind::S_lpattern_field_cl: // lpattern_field_cl
        value.copy< std::vector<pdm::ast::LPattern::Field*> > (that.value);
        break;

      case symbol_kind::S_mod_content: // mod_content
        value.copy< std::vector<pdm::ast::ModContentStmt*> > (that.value);
        break;

      case symbol_kind::S_enum_field_pl: // enum_field_pl
      case symbol_kind::S_unprefixed_enum_field_pl: // unprefixed_enum_field_pl
        value.copy< std::vector<pdm::ast::ModEnumStmt::Field*> > (that.value);
        break;

      case symbol_kind::S_script_body: // script_body
        value.copy< std::vector<pdm::ast::ModStmt*> > (that.value);
        break;

      case symbol_kind::S_script_head: // script_head
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

      case symbol_kind::S_tpattern_seq: // tpattern_seq
        value.copy< std::vector<pdm::ast::TPattern*> > (that.value);
        break;

      case symbol_kind::S_tpattern_field_cl: // tpattern_field_cl
        value.copy< std::vector<pdm::ast::TPattern::Field*> > (that.value);
        break;

      case symbol_kind::S_type_query_exp_sl: // type_query_exp_sl
        value.copy< std::vector<pdm::ast::TypeQueryExp*> > (that.value);
        break;

      case symbol_kind::S_type_spec_cl1: // type_spec_cl1
      case symbol_kind::S_type_spec_cl2: // type_spec_cl2
        value.copy< std::vector<pdm::ast::TypeSpec*> > (that.value);
        break;

      case symbol_kind::S_varg_cl: // varg_cl
        value.copy< std::vector<pdm::ast::VArg*> > (that.value);
        break;

      case symbol_kind::S_vpattern_field_cl: // vpattern_field_cl
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

      case symbol_kind::S_mul_binary_op: // mul_binary_op
      case symbol_kind::S_add_binary_op: // add_binary_op
      case symbol_kind::S_cmp_binary_op: // cmp_binary_op
      case symbol_kind::S_eq_binary_op: // eq_binary_op
        value.move< pdm::ast::BinaryOperator > (that.value);
        break;

      case symbol_kind::S_class_spec: // class_spec
      case symbol_kind::S_primary_class_spec: // primary_class_spec
      case symbol_kind::S_postfix_class_spec: // postfix_class_spec
        value.move< pdm::ast::ClassSpec* > (that.value);
        break;

      case symbol_kind::S_expr: // expr
      case symbol_kind::S_long_exp: // long_exp
      case symbol_kind::S_bracketed_exp: // bracketed_exp
      case symbol_kind::S_unit_exp: // unit_exp
      case symbol_kind::S_paren_exp: // paren_exp
      case symbol_kind::S_vtupleExpr: // vtupleExpr
      case symbol_kind::S_vstructExpr: // vstructExpr
      case symbol_kind::S_primary_exp: // primary_exp
      case symbol_kind::S_int_expr: // int_expr
      case symbol_kind::S_if_exp: // if_exp
      case symbol_kind::S_chain_exp: // chain_exp
      case symbol_kind::S_lambda_exp: // lambda_exp
      case symbol_kind::S_postfix_exp: // postfix_exp
      case symbol_kind::S_tcall_exp: // tcall_exp
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

      case symbol_kind::S_destructured_lpattern: // destructured_lpattern
      case symbol_kind::S_lpattern: // lpattern
        value.move< pdm::ast::LPattern* > (that.value);
        break;

      case symbol_kind::S_lpattern_field: // lpattern_field
        value.move< pdm::ast::LPattern::Field* > (that.value);
        break;

      case symbol_kind::S_sub_mod_stmt: // sub_mod_stmt
      case symbol_kind::S_mod_content_stmt: // mod_content_stmt
      case symbol_kind::S_mod_val_stmt: // mod_val_stmt
      case symbol_kind::S_mod_type_stmt: // mod_type_stmt
      case symbol_kind::S_mod_enum_stmt: // mod_enum_stmt
      case symbol_kind::S_mod_typeclass_stmt: // mod_typeclass_stmt
        value.move< pdm::ast::ModContentStmt* > (that.value);
        break;

      case symbol_kind::S_enum_field: // enum_field
        value.move< pdm::ast::ModEnumStmt::Field* > (that.value);
        break;

      case symbol_kind::S_script_body_stmt: // script_body_stmt
      case symbol_kind::S_top_mod_stmt: // top_mod_stmt
        value.move< pdm::ast::ModStmt* > (that.value);
        break;

      case symbol_kind::S_script: // script
        value.move< pdm::ast::Script* > (that.value);
        break;

      case symbol_kind::S_script_head_stmt: // script_head_stmt
      case symbol_kind::S_import_stmt: // import_stmt
      case symbol_kind::S_extern_stmt: // extern_stmt
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
      case symbol_kind::S_primary_type_spec: // primary_type_spec
      case symbol_kind::S_paren_type_spec: // paren_type_spec
      case symbol_kind::S_tuple_type_spec: // tuple_type_spec
      case symbol_kind::S_mod_prefix_tid: // mod_prefix_tid
      case symbol_kind::S_fn_type_spec: // fn_type_spec
      case symbol_kind::S_postfix_type_spec: // postfix_type_spec
      case symbol_kind::S_tcall_type_spec: // tcall_type_spec
      case symbol_kind::S_unary_type_spec: // unary_type_spec
      case symbol_kind::S_long_type_spec: // long_type_spec
      case symbol_kind::S_struct_type_spec: // struct_type_spec
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

      case symbol_kind::S_expr_cl0: // expr_cl0
      case symbol_kind::S_expr_cl2: // expr_cl2
        value.move< std::vector<pdm::ast::Exp*> > (that.value);
        break;

      case symbol_kind::S_lpattern_field_cl: // lpattern_field_cl
        value.move< std::vector<pdm::ast::LPattern::Field*> > (that.value);
        break;

      case symbol_kind::S_mod_content: // mod_content
        value.move< std::vector<pdm::ast::ModContentStmt*> > (that.value);
        break;

      case symbol_kind::S_enum_field_pl: // enum_field_pl
      case symbol_kind::S_unprefixed_enum_field_pl: // unprefixed_enum_field_pl
        value.move< std::vector<pdm::ast::ModEnumStmt::Field*> > (that.value);
        break;

      case symbol_kind::S_script_body: // script_body
        value.move< std::vector<pdm::ast::ModStmt*> > (that.value);
        break;

      case symbol_kind::S_script_head: // script_head
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

      case symbol_kind::S_tpattern_seq: // tpattern_seq
        value.move< std::vector<pdm::ast::TPattern*> > (that.value);
        break;

      case symbol_kind::S_tpattern_field_cl: // tpattern_field_cl
        value.move< std::vector<pdm::ast::TPattern::Field*> > (that.value);
        break;

      case symbol_kind::S_type_query_exp_sl: // type_query_exp_sl
        value.move< std::vector<pdm::ast::TypeQueryExp*> > (that.value);
        break;

      case symbol_kind::S_type_spec_cl1: // type_spec_cl1
      case symbol_kind::S_type_spec_cl2: // type_spec_cl2
        value.move< std::vector<pdm::ast::TypeSpec*> > (that.value);
        break;

      case symbol_kind::S_varg_cl: // varg_cl
        value.move< std::vector<pdm::ast::VArg*> > (that.value);
        break;

      case symbol_kind::S_vpattern_field_cl: // vpattern_field_cl
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

      case symbol_kind::S_mul_binary_op: // mul_binary_op
      case symbol_kind::S_add_binary_op: // add_binary_op
      case symbol_kind::S_cmp_binary_op: // cmp_binary_op
      case symbol_kind::S_eq_binary_op: // eq_binary_op
        yylhs.value.emplace< pdm::ast::BinaryOperator > ();
        break;

      case symbol_kind::S_class_spec: // class_spec
      case symbol_kind::S_primary_class_spec: // primary_class_spec
      case symbol_kind::S_postfix_class_spec: // postfix_class_spec
        yylhs.value.emplace< pdm::ast::ClassSpec* > ();
        break;

      case symbol_kind::S_expr: // expr
      case symbol_kind::S_long_exp: // long_exp
      case symbol_kind::S_bracketed_exp: // bracketed_exp
      case symbol_kind::S_unit_exp: // unit_exp
      case symbol_kind::S_paren_exp: // paren_exp
      case symbol_kind::S_vtupleExpr: // vtupleExpr
      case symbol_kind::S_vstructExpr: // vstructExpr
      case symbol_kind::S_primary_exp: // primary_exp
      case symbol_kind::S_int_expr: // int_expr
      case symbol_kind::S_if_exp: // if_exp
      case symbol_kind::S_chain_exp: // chain_exp
      case symbol_kind::S_lambda_exp: // lambda_exp
      case symbol_kind::S_postfix_exp: // postfix_exp
      case symbol_kind::S_tcall_exp: // tcall_exp
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

      case symbol_kind::S_destructured_lpattern: // destructured_lpattern
      case symbol_kind::S_lpattern: // lpattern
        yylhs.value.emplace< pdm::ast::LPattern* > ();
        break;

      case symbol_kind::S_lpattern_field: // lpattern_field
        yylhs.value.emplace< pdm::ast::LPattern::Field* > ();
        break;

      case symbol_kind::S_sub_mod_stmt: // sub_mod_stmt
      case symbol_kind::S_mod_content_stmt: // mod_content_stmt
      case symbol_kind::S_mod_val_stmt: // mod_val_stmt
      case symbol_kind::S_mod_type_stmt: // mod_type_stmt
      case symbol_kind::S_mod_enum_stmt: // mod_enum_stmt
      case symbol_kind::S_mod_typeclass_stmt: // mod_typeclass_stmt
        yylhs.value.emplace< pdm::ast::ModContentStmt* > ();
        break;

      case symbol_kind::S_enum_field: // enum_field
        yylhs.value.emplace< pdm::ast::ModEnumStmt::Field* > ();
        break;

      case symbol_kind::S_script_body_stmt: // script_body_stmt
      case symbol_kind::S_top_mod_stmt: // top_mod_stmt
        yylhs.value.emplace< pdm::ast::ModStmt* > ();
        break;

      case symbol_kind::S_script: // script
        yylhs.value.emplace< pdm::ast::Script* > ();
        break;

      case symbol_kind::S_script_head_stmt: // script_head_stmt
      case symbol_kind::S_import_stmt: // import_stmt
      case symbol_kind::S_extern_stmt: // extern_stmt
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
      case symbol_kind::S_primary_type_spec: // primary_type_spec
      case symbol_kind::S_paren_type_spec: // paren_type_spec
      case symbol_kind::S_tuple_type_spec: // tuple_type_spec
      case symbol_kind::S_mod_prefix_tid: // mod_prefix_tid
      case symbol_kind::S_fn_type_spec: // fn_type_spec
      case symbol_kind::S_postfix_type_spec: // postfix_type_spec
      case symbol_kind::S_tcall_type_spec: // tcall_type_spec
      case symbol_kind::S_unary_type_spec: // unary_type_spec
      case symbol_kind::S_long_type_spec: // long_type_spec
      case symbol_kind::S_struct_type_spec: // struct_type_spec
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

      case symbol_kind::S_expr_cl0: // expr_cl0
      case symbol_kind::S_expr_cl2: // expr_cl2
        yylhs.value.emplace< std::vector<pdm::ast::Exp*> > ();
        break;

      case symbol_kind::S_lpattern_field_cl: // lpattern_field_cl
        yylhs.value.emplace< std::vector<pdm::ast::LPattern::Field*> > ();
        break;

      case symbol_kind::S_mod_content: // mod_content
        yylhs.value.emplace< std::vector<pdm::ast::ModContentStmt*> > ();
        break;

      case symbol_kind::S_enum_field_pl: // enum_field_pl
      case symbol_kind::S_unprefixed_enum_field_pl: // unprefixed_enum_field_pl
        yylhs.value.emplace< std::vector<pdm::ast::ModEnumStmt::Field*> > ();
        break;

      case symbol_kind::S_script_body: // script_body
        yylhs.value.emplace< std::vector<pdm::ast::ModStmt*> > ();
        break;

      case symbol_kind::S_script_head: // script_head
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

      case symbol_kind::S_tpattern_seq: // tpattern_seq
        yylhs.value.emplace< std::vector<pdm::ast::TPattern*> > ();
        break;

      case symbol_kind::S_tpattern_field_cl: // tpattern_field_cl
        yylhs.value.emplace< std::vector<pdm::ast::TPattern::Field*> > ();
        break;

      case symbol_kind::S_type_query_exp_sl: // type_query_exp_sl
        yylhs.value.emplace< std::vector<pdm::ast::TypeQueryExp*> > ();
        break;

      case symbol_kind::S_type_spec_cl1: // type_spec_cl1
      case symbol_kind::S_type_spec_cl2: // type_spec_cl2
        yylhs.value.emplace< std::vector<pdm::ast::TypeSpec*> > ();
        break;

      case symbol_kind::S_varg_cl: // varg_cl
        yylhs.value.emplace< std::vector<pdm::ast::VArg*> > ();
        break;

      case symbol_kind::S_vpattern_field_cl: // vpattern_field_cl
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
  case 2: // script: script_head script_body
#line 288 "parser.yy"
                                { 
    yylhs.value.as < pdm::ast::Script* > () = mgr->new_script(source, yylhs.location, std::move(yystack_[1].value.as < std::vector<pdm::ast::Stmt*> > ()), std::move(yystack_[0].value.as < std::vector<pdm::ast::ModStmt*> > ())); 

    // setting the returnp here => this is the node parser returns.  
    *returnp = yylhs.value.as < pdm::ast::Script* > (); 
}
#line 2244 "parser.tab.cc"
    break;

  case 3: // script_head: %empty
#line 296 "parser.yy"
                                                { yylhs.value.as < std::vector<pdm::ast::Stmt*> > ().reserve(16); }
#line 2250 "parser.tab.cc"
    break;

  case 4: // script_head: script_head script_head_stmt ";"
#line 297 "parser.yy"
                                                { yylhs.value.as < std::vector<pdm::ast::Stmt*> > () = std::move(yystack_[2].value.as < std::vector<pdm::ast::Stmt*> > ()); yylhs.value.as < std::vector<pdm::ast::Stmt*> > ().push_back(yystack_[1].value.as < pdm::ast::Stmt* > ()); }
#line 2256 "parser.tab.cc"
    break;

  case 5: // script_head_stmt: import_stmt
#line 300 "parser.yy"
      { yylhs.value.as < pdm::ast::Stmt* > () = yystack_[0].value.as < pdm::ast::Stmt* > (); }
#line 2262 "parser.tab.cc"
    break;

  case 6: // script_head_stmt: extern_stmt
#line 301 "parser.yy"
      { yylhs.value.as < pdm::ast::Stmt* > () = yystack_[0].value.as < pdm::ast::Stmt* > (); }
#line 2268 "parser.tab.cc"
    break;

  case 7: // script_body: %empty
#line 305 "parser.yy"
                                    { yylhs.value.as < std::vector<pdm::ast::ModStmt*> > ().reserve(16); }
#line 2274 "parser.tab.cc"
    break;

  case 8: // script_body: script_body script_body_stmt
#line 306 "parser.yy"
                                    { yylhs.value.as < std::vector<pdm::ast::ModStmt*> > () = std::move(yystack_[1].value.as < std::vector<pdm::ast::ModStmt*> > ()); yylhs.value.as < std::vector<pdm::ast::ModStmt*> > ().push_back(yystack_[0].value.as < pdm::ast::ModStmt* > ()); }
#line 2280 "parser.tab.cc"
    break;

  case 9: // script_body_stmt: top_mod_stmt
#line 309 "parser.yy"
      { yylhs.value.as < pdm::ast::ModStmt* > () = yystack_[0].value.as < pdm::ast::ModStmt* > (); }
#line 2286 "parser.tab.cc"
    break;

  case 10: // top_mod_stmt: "---" "module" "<TypeId>" "---" mod_content
#line 317 "parser.yy"
                                                        { yylhs.value.as < pdm::ast::ModStmt* > () = mgr->new_mod_stmt(yylhs.location, yystack_[2].value.as < TokenInfo > ().ID_intstr, std::move(std::vector<ast::TPattern*>{}), std::move(yystack_[0].value.as < std::vector<pdm::ast::ModContentStmt*> > ())); }
#line 2292 "parser.tab.cc"
    break;

  case 11: // sub_mod_stmt: "sub" "<TypeId>" "{" mod_content "}"
#line 320 "parser.yy"
                                                           { yylhs.value.as < pdm::ast::ModContentStmt* > () = mgr->new_mod_stmt(yylhs.location, yystack_[3].value.as < TokenInfo > ().ID_intstr, std::move(std::vector<ast::TPattern*>{}), std::move(yystack_[1].value.as < std::vector<pdm::ast::ModContentStmt*> > ())); }
#line 2298 "parser.tab.cc"
    break;

  case 12: // sub_mod_stmt: "sub" "<TypeId>" tpattern_seq "{" mod_content "}"
#line 321 "parser.yy"
                                                           { yylhs.value.as < pdm::ast::ModContentStmt* > () = mgr->new_mod_stmt(yylhs.location, yystack_[4].value.as < TokenInfo > ().ID_intstr, std::move(yystack_[3].value.as < std::vector<pdm::ast::TPattern*> > ()), std::move(yystack_[1].value.as < std::vector<pdm::ast::ModContentStmt*> > ())); }
#line 2304 "parser.tab.cc"
    break;

  case 13: // mod_content: mod_content_stmt ";"
#line 324 "parser.yy"
                                                { yylhs.value.as < std::vector<pdm::ast::ModContentStmt*> > ().push_back(yystack_[1].value.as < pdm::ast::ModContentStmt* > ()); }
#line 2310 "parser.tab.cc"
    break;

  case 14: // mod_content: mod_content mod_content_stmt ";"
#line 325 "parser.yy"
                                                { yylhs.value.as < std::vector<pdm::ast::ModContentStmt*> > () = std::move(yystack_[2].value.as < std::vector<pdm::ast::ModContentStmt*> > ()); yylhs.value.as < std::vector<pdm::ast::ModContentStmt*> > ().push_back(yystack_[1].value.as < pdm::ast::ModContentStmt* > ()); }
#line 2316 "parser.tab.cc"
    break;

  case 15: // mod_content_stmt: mod_val_stmt
#line 333 "parser.yy"
      { yylhs.value.as < pdm::ast::ModContentStmt* > () = yystack_[0].value.as < pdm::ast::ModContentStmt* > (); }
#line 2322 "parser.tab.cc"
    break;

  case 16: // mod_content_stmt: mod_type_stmt
#line 334 "parser.yy"
      { yylhs.value.as < pdm::ast::ModContentStmt* > () = yystack_[0].value.as < pdm::ast::ModContentStmt* > (); }
#line 2328 "parser.tab.cc"
    break;

  case 17: // mod_content_stmt: mod_enum_stmt
#line 335 "parser.yy"
      { yylhs.value.as < pdm::ast::ModContentStmt* > () = yystack_[0].value.as < pdm::ast::ModContentStmt* > (); }
#line 2334 "parser.tab.cc"
    break;

  case 18: // mod_content_stmt: mod_typeclass_stmt
#line 336 "parser.yy"
      { yylhs.value.as < pdm::ast::ModContentStmt* > () = yystack_[0].value.as < pdm::ast::ModContentStmt* > (); }
#line 2340 "parser.tab.cc"
    break;

  case 19: // mod_content_stmt: sub_mod_stmt
#line 337 "parser.yy"
      { yylhs.value.as < pdm::ast::ModContentStmt* > () = yystack_[0].value.as < pdm::ast::ModContentStmt* > (); }
#line 2346 "parser.tab.cc"
    break;

  case 20: // mod_val_stmt: vid "=" expr
#line 340 "parser.yy"
                                    { yylhs.value.as < pdm::ast::ModContentStmt* > () = mgr->new_internal_mod_val_stmt(yylhs.location, yystack_[2].value.as < TokenInfo > ().ID_intstr, std::move(std::vector<ast::TPattern*>{}), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2352 "parser.tab.cc"
    break;

  case 21: // mod_val_stmt: vid tpattern_seq "=" expr
#line 341 "parser.yy"
                                    { yylhs.value.as < pdm::ast::ModContentStmt* > () = mgr->new_internal_mod_val_stmt(yylhs.location, yystack_[3].value.as < TokenInfo > ().ID_intstr, std::move(yystack_[2].value.as < std::vector<pdm::ast::TPattern*> > ()), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2358 "parser.tab.cc"
    break;

  case 22: // mod_val_stmt: vid type_spec "from" tid stringl
#line 342 "parser.yy"
                                                      { yylhs.value.as < pdm::ast::ModContentStmt* > () = mgr->new_external_mod_val_stmt(yylhs.location, yystack_[4].value.as < TokenInfo > ().ID_intstr, std::move(std::vector<ast::TPattern*>{}), yystack_[3].value.as < pdm::ast::TypeSpec* > (), yystack_[1].value.as < TokenInfo > ().ID_intstr, *yystack_[0].value.as < TokenInfo > ().String_utf8string); }
#line 2364 "parser.tab.cc"
    break;

  case 23: // mod_val_stmt: vid tpattern_seq type_spec "from" tid stringl
#line 343 "parser.yy"
                                                      { yylhs.value.as < pdm::ast::ModContentStmt* > () = mgr->new_external_mod_val_stmt(yylhs.location, yystack_[5].value.as < TokenInfo > ().ID_intstr, std::move(yystack_[4].value.as < std::vector<pdm::ast::TPattern*> > ()), yystack_[3].value.as < pdm::ast::TypeSpec* > (), yystack_[1].value.as < TokenInfo > ().ID_intstr, *yystack_[0].value.as < TokenInfo > ().String_utf8string); }
#line 2370 "parser.tab.cc"
    break;

  case 24: // mod_type_stmt: tid "=" long_type_spec
#line 346 "parser.yy"
                                             { yylhs.value.as < pdm::ast::ModContentStmt* > () = mgr->new_mod_type_stmt(yylhs.location, yystack_[2].value.as < TokenInfo > ().ID_intstr, std::move(std::vector<ast::TPattern*>{}), yystack_[0].value.as < pdm::ast::TypeSpec* > ()); }
#line 2376 "parser.tab.cc"
    break;

  case 25: // mod_type_stmt: tid tpattern_seq "=" long_type_spec
#line 347 "parser.yy"
                                             { yylhs.value.as < pdm::ast::ModContentStmt* > () = mgr->new_mod_type_stmt(yylhs.location, yystack_[3].value.as < TokenInfo > ().ID_intstr, std::move(yystack_[2].value.as < std::vector<pdm::ast::TPattern*> > ()), yystack_[0].value.as < pdm::ast::TypeSpec* > ()); }
#line 2382 "parser.tab.cc"
    break;

  case 26: // mod_enum_stmt: tid enum_field_pl
#line 350 "parser.yy"
                                        { yylhs.value.as < pdm::ast::ModContentStmt* > () = mgr->new_mod_enum_stmt(yylhs.location, yystack_[1].value.as < TokenInfo > ().ID_intstr, std::move(std::vector<ast::TPattern*>{}), std::move(yystack_[0].value.as < std::vector<pdm::ast::ModEnumStmt::Field*> > ())); }
#line 2388 "parser.tab.cc"
    break;

  case 27: // mod_enum_stmt: tid tpattern_seq enum_field_pl
#line 351 "parser.yy"
                                        { yylhs.value.as < pdm::ast::ModContentStmt* > () = mgr->new_mod_enum_stmt(yylhs.location, yystack_[2].value.as < TokenInfo > ().ID_intstr, std::move(yystack_[1].value.as < std::vector<pdm::ast::TPattern*> > ()), std::move(yystack_[0].value.as < std::vector<pdm::ast::ModEnumStmt::Field*> > ())); }
#line 2394 "parser.tab.cc"
    break;

  case 28: // enum_field_pl: "|" unprefixed_enum_field_pl
#line 354 "parser.yy"
                                    { yylhs.value.as < std::vector<pdm::ast::ModEnumStmt::Field*> > () = std::move(yystack_[0].value.as < std::vector<pdm::ast::ModEnumStmt::Field*> > ()); }
#line 2400 "parser.tab.cc"
    break;

  case 29: // unprefixed_enum_field_pl: enum_field
#line 357 "parser.yy"
                                                { yylhs.value.as < std::vector<pdm::ast::ModEnumStmt::Field*> > ().push_back(yystack_[0].value.as < pdm::ast::ModEnumStmt::Field* > ()); }
#line 2406 "parser.tab.cc"
    break;

  case 30: // unprefixed_enum_field_pl: unprefixed_enum_field_pl "|" enum_field
#line 358 "parser.yy"
                                                { yylhs.value.as < std::vector<pdm::ast::ModEnumStmt::Field*> > () = std::move(yystack_[2].value.as < std::vector<pdm::ast::ModEnumStmt::Field*> > ()); yylhs.value.as < std::vector<pdm::ast::ModEnumStmt::Field*> > ().push_back(yystack_[0].value.as < pdm::ast::ModEnumStmt::Field* > ()); }
#line 2412 "parser.tab.cc"
    break;

  case 31: // enum_field: tid
#line 361 "parser.yy"
                                     { yylhs.value.as < pdm::ast::ModEnumStmt::Field* > () = mgr->new_enum_stmt_field(yylhs.location, yystack_[0].value.as < TokenInfo > ().ID_intstr, std::move(std::vector<ast::TypeSpec*>{}), false); }
#line 2418 "parser.tab.cc"
    break;

  case 32: // enum_field: tid "(" ")"
#line 362 "parser.yy"
                                     { yylhs.value.as < pdm::ast::ModEnumStmt::Field* > () = mgr->new_enum_stmt_field(yylhs.location, yystack_[2].value.as < TokenInfo > ().ID_intstr, std::move(std::vector<ast::TypeSpec*>{}), true); }
#line 2424 "parser.tab.cc"
    break;

  case 33: // enum_field: tid "(" type_spec_cl1 ")"
#line 363 "parser.yy"
                                      { yylhs.value.as < pdm::ast::ModEnumStmt::Field* > () = mgr->new_enum_stmt_field(yylhs.location, yystack_[3].value.as < TokenInfo > ().ID_intstr, std::move(yystack_[1].value.as < std::vector<pdm::ast::TypeSpec*> > ()), true); }
#line 2430 "parser.tab.cc"
    break;

  case 34: // mod_typeclass_stmt: tid ":-" "<" tid class_spec ">" "{" type_query_exp_sl "}"
#line 366 "parser.yy"
                                                                                             { 
        yylhs.value.as < pdm::ast::ModContentStmt* > () = mgr->new_mod_typeclass_stmt(yylhs.location, yystack_[8].value.as < TokenInfo > ().ID_intstr, yystack_[5].value.as < TokenInfo > ().ID_intstr, yystack_[4].value.as < pdm::ast::ClassSpec* > (), std::move(std::vector<ast::TPattern*>{}), std::move(yystack_[1].value.as < std::vector<pdm::ast::TypeQueryExp*> > ())); 
      }
#line 2438 "parser.tab.cc"
    break;

  case 35: // mod_typeclass_stmt: tid tpattern_seq ":-" "<" tid class_spec ">" "{" type_query_exp_sl "}"
#line 369 "parser.yy"
                                                                                             { 
        yylhs.value.as < pdm::ast::ModContentStmt* > () = mgr->new_mod_typeclass_stmt(yylhs.location, yystack_[9].value.as < TokenInfo > ().ID_intstr, yystack_[5].value.as < TokenInfo > ().ID_intstr, yystack_[4].value.as < pdm::ast::ClassSpec* > (), std::move(yystack_[8].value.as < std::vector<pdm::ast::TPattern*> > ()), std::move(yystack_[1].value.as < std::vector<pdm::ast::TypeQueryExp*> > ())); 
      }
#line 2446 "parser.tab.cc"
    break;

  case 36: // import_stmt: "import" tid "from" stringl "type" stringl
#line 375 "parser.yy"
                                                       { yylhs.value.as < pdm::ast::Stmt* > () = mgr->new_import_stmt(yylhs.location, yystack_[4].value.as < TokenInfo > ().ID_intstr, *yystack_[2].value.as < TokenInfo > ().String_utf8string, *yystack_[0].value.as < TokenInfo > ().String_utf8string); }
#line 2452 "parser.tab.cc"
    break;

  case 37: // extern_stmt: "extern" tid "from" expr
#line 378 "parser.yy"
                                    { yylhs.value.as < pdm::ast::Stmt* > () = mgr->new_extern_stmt(yylhs.location, yystack_[2].value.as < TokenInfo > ().ID_intstr, yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2458 "parser.tab.cc"
    break;

  case 38: // chain_prefix_stmt: const_stmt
#line 382 "parser.yy"
      { yylhs.value.as < pdm::ast::Stmt* > () = yystack_[0].value.as < pdm::ast::Stmt* > (); }
#line 2464 "parser.tab.cc"
    break;

  case 39: // chain_prefix_stmt: val_stmt
#line 383 "parser.yy"
      { yylhs.value.as < pdm::ast::Stmt* > () = yystack_[0].value.as < pdm::ast::Stmt* > (); }
#line 2470 "parser.tab.cc"
    break;

  case 40: // chain_prefix_stmt: var_stmt
#line 384 "parser.yy"
      { yylhs.value.as < pdm::ast::Stmt* > () = yystack_[0].value.as < pdm::ast::Stmt* > (); }
#line 2476 "parser.tab.cc"
    break;

  case 41: // chain_prefix_stmt: set_stmt
#line 385 "parser.yy"
      { yylhs.value.as < pdm::ast::Stmt* > () = yystack_[0].value.as < pdm::ast::Stmt* > (); }
#line 2482 "parser.tab.cc"
    break;

  case 42: // chain_prefix_stmt: discard_stmt
#line 386 "parser.yy"
      { yylhs.value.as < pdm::ast::Stmt* > () = yystack_[0].value.as < pdm::ast::Stmt* > (); }
#line 2488 "parser.tab.cc"
    break;

  case 43: // const_stmt: "const" lpattern "=" expr
#line 389 "parser.yy"
                                  { yylhs.value.as < pdm::ast::Stmt* > () = mgr->new_const_stmt(yylhs.location, yystack_[2].value.as < pdm::ast::LPattern* > (), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2494 "parser.tab.cc"
    break;

  case 44: // val_stmt: "val" lpattern "=" expr
#line 392 "parser.yy"
                                  { yylhs.value.as < pdm::ast::Stmt* > () = mgr->new_val_stmt(yylhs.location, yystack_[2].value.as < pdm::ast::LPattern* > (), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2500 "parser.tab.cc"
    break;

  case 45: // var_stmt: "var" lpattern "=" expr
#line 395 "parser.yy"
                                  { yylhs.value.as < pdm::ast::Stmt* > () = mgr->new_var_stmt(yylhs.location, yystack_[2].value.as < pdm::ast::LPattern* > (), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2506 "parser.tab.cc"
    break;

  case 46: // set_stmt: "set" expr "=" expr
#line 398 "parser.yy"
                              { yylhs.value.as < pdm::ast::Stmt* > () = mgr->new_set_stmt(yylhs.location, yystack_[2].value.as < pdm::ast::Exp* > (), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2512 "parser.tab.cc"
    break;

  case 47: // discard_stmt: "discard" expr
#line 401 "parser.yy"
                        { yylhs.value.as < pdm::ast::Stmt* > () = mgr->new_discard_stmt(yylhs.location, yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2518 "parser.tab.cc"
    break;

  case 48: // tid: "<TypeId>"
#line 408 "parser.yy"
     { yylhs.value.as < TokenInfo > () = yystack_[0].value.as < TokenInfo > (); }
#line 2524 "parser.tab.cc"
    break;

  case 49: // vid: "<val_id>"
#line 409 "parser.yy"
     { yylhs.value.as < TokenInfo > () = yystack_[0].value.as < TokenInfo > (); }
#line 2530 "parser.tab.cc"
    break;

  case 50: // floatl: "4.2"
#line 411 "parser.yy"
      { yylhs.value.as < TokenInfo > () = yystack_[0].value.as < TokenInfo > (); }
#line 2536 "parser.tab.cc"
    break;

  case 51: // stringl: "'sq-string-literal'"
#line 414 "parser.yy"
      { yylhs.value.as < TokenInfo > () = yystack_[0].value.as < TokenInfo > (); }
#line 2542 "parser.tab.cc"
    break;

  case 52: // stringl: "\"dq-string-literal\""
#line 415 "parser.yy"
      { yylhs.value.as < TokenInfo > () = yystack_[0].value.as < TokenInfo > (); }
#line 2548 "parser.tab.cc"
    break;

  case 53: // mod_prefix: tid ":"
#line 418 "parser.yy"
                              { yylhs.value.as < std::vector<pdm::intern::String> > ().push_back(yystack_[1].value.as < TokenInfo > ().ID_intstr); }
#line 2554 "parser.tab.cc"
    break;

  case 54: // mod_prefix: mod_prefix vid ":"
#line 419 "parser.yy"
                              { yylhs.value.as < std::vector<pdm::intern::String> > () = std::move(yystack_[2].value.as < std::vector<pdm::intern::String> > ()); }
#line 2560 "parser.tab.cc"
    break;

  case 55: // expr: binary_exp
#line 426 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2566 "parser.tab.cc"
    break;

  case 56: // long_exp: expr
#line 429 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2572 "parser.tab.cc"
    break;

  case 57: // expr_cl0: %empty
#line 433 "parser.yy"
                             {}
#line 2578 "parser.tab.cc"
    break;

  case 58: // expr_cl0: expr_cl0 "," expr
#line 434 "parser.yy"
                             { yylhs.value.as < std::vector<pdm::ast::Exp*> > () = std::move(yystack_[2].value.as < std::vector<pdm::ast::Exp*> > ()); yylhs.value.as < std::vector<pdm::ast::Exp*> > ().push_back(yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2584 "parser.tab.cc"
    break;

  case 59: // expr_cl2: expr "," expr
#line 437 "parser.yy"
                             { yylhs.value.as < std::vector<pdm::ast::Exp*> > ().reserve(2); yylhs.value.as < std::vector<pdm::ast::Exp*> > ().push_back(yystack_[2].value.as < pdm::ast::Exp* > ()); yylhs.value.as < std::vector<pdm::ast::Exp*> > ().push_back(yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2590 "parser.tab.cc"
    break;

  case 60: // expr_cl2: expr_cl2 "," expr
#line 438 "parser.yy"
                             { yylhs.value.as < std::vector<pdm::ast::Exp*> > () = std::move(yystack_[2].value.as < std::vector<pdm::ast::Exp*> > ()); yylhs.value.as < std::vector<pdm::ast::Exp*> > ().push_back(yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2596 "parser.tab.cc"
    break;

  case 61: // type_query_exp_sl: type_query_exp ";"
#line 441 "parser.yy"
                                       { yylhs.value.as < std::vector<pdm::ast::TypeQueryExp*> > ().push_back(yystack_[1].value.as < pdm::ast::TypeQueryExp* > ()); }
#line 2602 "parser.tab.cc"
    break;

  case 62: // type_query_exp_sl: type_query_exp_sl type_query_exp ";"
#line 442 "parser.yy"
                                                 { yylhs.value.as < std::vector<pdm::ast::TypeQueryExp*> > () = std::move(yystack_[2].value.as < std::vector<pdm::ast::TypeQueryExp*> > ()); yylhs.value.as < std::vector<pdm::ast::TypeQueryExp*> > ().push_back(yystack_[1].value.as < pdm::ast::TypeQueryExp* > ()); }
#line 2608 "parser.tab.cc"
    break;

  case 63: // bracketed_exp: unit_exp
#line 446 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2614 "parser.tab.cc"
    break;

  case 64: // bracketed_exp: paren_exp
#line 447 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2620 "parser.tab.cc"
    break;

  case 65: // bracketed_exp: vtupleExpr
#line 448 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2626 "parser.tab.cc"
    break;

  case 66: // bracketed_exp: vstructExpr
#line 449 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2632 "parser.tab.cc"
    break;

  case 67: // bracketed_exp: chain_exp
#line 450 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2638 "parser.tab.cc"
    break;

  case 68: // unit_exp: "(" ")"
#line 453 "parser.yy"
                        { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_unit_exp(yylhs.location); }
#line 2644 "parser.tab.cc"
    break;

  case 69: // unit_exp: "{" "}"
#line 454 "parser.yy"
                        { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_unit_exp(yylhs.location); }
#line 2650 "parser.tab.cc"
    break;

  case 70: // paren_exp: "(" long_exp ")"
#line 457 "parser.yy"
                              { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_paren_exp(yylhs.location, yystack_[1].value.as < pdm::ast::Exp* > ()); }
#line 2656 "parser.tab.cc"
    break;

  case 71: // vtupleExpr: "(" expr "," ")"
#line 460 "parser.yy"
                                   { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_tuple_exp(yylhs.location, std::move(std::vector(1,yystack_[2].value.as < pdm::ast::Exp* > ()))); }
#line 2662 "parser.tab.cc"
    break;

  case 72: // vtupleExpr: "(" expr_cl2 ")"
#line 461 "parser.yy"
                                   { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_tuple_exp(yylhs.location, std::move(yystack_[1].value.as < std::vector<pdm::ast::Exp*> > ())); }
#line 2668 "parser.tab.cc"
    break;

  case 73: // vstructExpr: "{" struct_exp_field_cl "}"
#line 464 "parser.yy"
                                            { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_struct_exp(yylhs.location, std::move(yystack_[1].value.as < std::vector<pdm::ast::StructExp::Field*> > ())); }
#line 2674 "parser.tab.cc"
    break;

  case 74: // primary_exp: bracketed_exp
#line 467 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2680 "parser.tab.cc"
    break;

  case 75: // primary_exp: vid
#line 468 "parser.yy"
                     { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_id_exp(yylhs.location, yystack_[0].value.as < TokenInfo > ().ID_intstr); }
#line 2686 "parser.tab.cc"
    break;

  case 76: // primary_exp: int_expr
#line 469 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2692 "parser.tab.cc"
    break;

  case 77: // primary_exp: floatl
#line 470 "parser.yy"
                     { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_float_exp(yylhs.location, yystack_[0].value.as < TokenInfo > ().Float); }
#line 2698 "parser.tab.cc"
    break;

  case 78: // primary_exp: stringls
#line 471 "parser.yy"
                     { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_string_exp(yylhs.location, std::move(yystack_[0].value.as < std::vector<pdm::ast::StringExp::Piece> > ())); }
#line 2704 "parser.tab.cc"
    break;

  case 79: // primary_exp: if_exp
#line 472 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2710 "parser.tab.cc"
    break;

  case 80: // primary_exp: lambda_exp
#line 473 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2716 "parser.tab.cc"
    break;

  case 81: // int_expr: "42"
#line 476 "parser.yy"
                { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_int_exp(yylhs.location, yystack_[0].value.as < TokenInfo > ().Int, ast::IntExp::Base::Dec); }
#line 2722 "parser.tab.cc"
    break;

  case 82: // int_expr: "0x2a"
#line 477 "parser.yy"
                { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_int_exp(yylhs.location, yystack_[0].value.as < TokenInfo > ().Int, ast::IntExp::Base::Hex); }
#line 2728 "parser.tab.cc"
    break;

  case 83: // stringls: "'sq-string-literal'"
#line 480 "parser.yy"
                             { yylhs.value.as < std::vector<pdm::ast::StringExp::Piece> > ().emplace_back(yylhs.location, *yystack_[0].value.as < TokenInfo > ().String_utf8string, ast::StringExp::QuoteKind::SingleQuote); }
#line 2734 "parser.tab.cc"
    break;

  case 84: // stringls: "\"dq-string-literal\""
#line 481 "parser.yy"
                             { yylhs.value.as < std::vector<pdm::ast::StringExp::Piece> > ().emplace_back(yylhs.location, *yystack_[0].value.as < TokenInfo > ().String_utf8string, ast::StringExp::QuoteKind::DoubleQuote); }
#line 2740 "parser.tab.cc"
    break;

  case 85: // stringls: stringls "'sq-string-literal'"
#line 482 "parser.yy"
                             { yylhs.value.as < std::vector<pdm::ast::StringExp::Piece> > () = std::move(yystack_[1].value.as < std::vector<pdm::ast::StringExp::Piece> > ()); yylhs.value.as < std::vector<pdm::ast::StringExp::Piece> > ().emplace_back(yystack_[0].location, *yystack_[0].value.as < TokenInfo > ().String_utf8string, ast::StringExp::QuoteKind::SingleQuote); }
#line 2746 "parser.tab.cc"
    break;

  case 86: // stringls: stringls "\"dq-string-literal\""
#line 483 "parser.yy"
                             { yylhs.value.as < std::vector<pdm::ast::StringExp::Piece> > () = std::move(yystack_[1].value.as < std::vector<pdm::ast::StringExp::Piece> > ()); yylhs.value.as < std::vector<pdm::ast::StringExp::Piece> > ().emplace_back(yystack_[0].location, *yystack_[0].value.as < TokenInfo > ().String_utf8string, ast::StringExp::QuoteKind::DoubleQuote); }
#line 2752 "parser.tab.cc"
    break;

  case 87: // if_exp: "if" bracketed_exp "then" bracketed_exp
#line 486 "parser.yy"
                                                                        { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_if_exp(yylhs.location, yystack_[2].value.as < pdm::ast::Exp* > (), yystack_[0].value.as < pdm::ast::Exp* > (), nullptr); }
#line 2758 "parser.tab.cc"
    break;

  case 88: // if_exp: "if" bracketed_exp "then" bracketed_exp "else" primary_exp
#line 487 "parser.yy"
                                                                        { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_if_exp(yylhs.location, yystack_[4].value.as < pdm::ast::Exp* > (), yystack_[2].value.as < pdm::ast::Exp* > (), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2764 "parser.tab.cc"
    break;

  case 89: // chain_exp: "{" expr "}"
#line 490 "parser.yy"
                                          { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_chain_exp(yylhs.location, std::move(std::vector<ast::Stmt*>{}), yystack_[1].value.as < pdm::ast::Exp* > ()); }
#line 2770 "parser.tab.cc"
    break;

  case 90: // chain_exp: "{" chain_prefix "}"
#line 491 "parser.yy"
                                           { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_chain_exp(yylhs.location, std::move(yystack_[1].value.as < std::vector<pdm::ast::Stmt*> > ()), nullptr); }
#line 2776 "parser.tab.cc"
    break;

  case 91: // chain_exp: "{" chain_prefix expr "}"
#line 492 "parser.yy"
                                           { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_chain_exp(yylhs.location, std::move(yystack_[2].value.as < std::vector<pdm::ast::Stmt*> > ()), yystack_[1].value.as < pdm::ast::Exp* > ()); }
#line 2782 "parser.tab.cc"
    break;

  case 92: // chain_prefix: chain_prefix_stmt ";"
#line 495 "parser.yy"
                                               { yylhs.value.as < std::vector<pdm::ast::Stmt*> > ().push_back(yystack_[1].value.as < pdm::ast::Stmt* > ()); }
#line 2788 "parser.tab.cc"
    break;

  case 93: // chain_prefix: chain_prefix chain_prefix_stmt ";"
#line 496 "parser.yy"
                                                { yylhs.value.as < std::vector<pdm::ast::Stmt*> > () = std::move(yystack_[2].value.as < std::vector<pdm::ast::Stmt*> > ()); yylhs.value.as < std::vector<pdm::ast::Stmt*> > ().push_back(yystack_[1].value.as < pdm::ast::Stmt* > ()); }
#line 2794 "parser.tab.cc"
    break;

  case 94: // lambda_exp: "fn" vpattern bracketed_exp
#line 499 "parser.yy"
                                                    { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_lambda_exp(yylhs.location, yystack_[1].value.as < pdm::ast::VPattern* > (), nullptr, yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2800 "parser.tab.cc"
    break;

  case 95: // lambda_exp: "fn" vpattern "->" type_spec bracketed_exp
#line 500 "parser.yy"
                                                     { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_lambda_exp(yylhs.location, yystack_[3].value.as < pdm::ast::VPattern* > (), yystack_[1].value.as < pdm::ast::TypeSpec* > (), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2806 "parser.tab.cc"
    break;

  case 96: // postfix_exp: primary_exp
#line 504 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2812 "parser.tab.cc"
    break;

  case 97: // postfix_exp: tcall_exp
#line 505 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2818 "parser.tab.cc"
    break;

  case 98: // postfix_exp: vcall_exp
#line 506 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2824 "parser.tab.cc"
    break;

  case 99: // postfix_exp: dot_name_exp
#line 507 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2830 "parser.tab.cc"
    break;

  case 100: // postfix_exp: dot_index_exp
#line 508 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2836 "parser.tab.cc"
    break;

  case 101: // tcall_exp: postfix_exp "[" targ_cl "]"
#line 511 "parser.yy"
                                         { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_tcall_exp(yylhs.location, yystack_[3].value.as < pdm::ast::Exp* > (), std::move(yystack_[1].value.as < std::vector<pdm::ast::TArg*> > ())); }
#line 2842 "parser.tab.cc"
    break;

  case 102: // vcall_exp: postfix_exp "(" ")"
#line 514 "parser.yy"
                                            { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_vcall_exp(yylhs.location, yystack_[2].value.as < pdm::ast::Exp* > (), std::move(std::vector<ast::VArg*>{})); }
#line 2848 "parser.tab.cc"
    break;

  case 103: // vcall_exp: postfix_exp "(" varg_cl ")"
#line 515 "parser.yy"
                                            { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_vcall_exp(yylhs.location, yystack_[3].value.as < pdm::ast::Exp* > (), std::move(yystack_[1].value.as < std::vector<pdm::ast::VArg*> > ())); }
#line 2854 "parser.tab.cc"
    break;

  case 104: // dot_name_exp: postfix_exp "." "<val_id>"
#line 518 "parser.yy"
                                                    { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_struct_dot_name_exp(yylhs.location, yystack_[2].value.as < pdm::ast::Exp* > (), yystack_[0].value.as < TokenInfo > ().ID_intstr); }
#line 2860 "parser.tab.cc"
    break;

  case 105: // dot_name_exp: postfix_exp "." "<TypeId>" "(" expr_cl0 ")"
#line 519 "parser.yy"
                                                    { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_enum_dot_name_exp(yylhs.location, yystack_[5].value.as < pdm::ast::Exp* > (), yystack_[3].value.as < TokenInfo > ().ID_intstr, std::move(yystack_[1].value.as < std::vector<pdm::ast::Exp*> > ())); }
#line 2866 "parser.tab.cc"
    break;

  case 106: // dot_name_exp: mod_prefix "<val_id>"
#line 520 "parser.yy"
                       { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_module_dot_exp(yylhs.location, std::move(yystack_[1].value.as < std::vector<pdm::intern::String> > ()), yystack_[0].value.as < TokenInfo > ().ID_intstr); }
#line 2872 "parser.tab.cc"
    break;

  case 107: // dot_index_exp: postfix_exp "." int_expr
#line 523 "parser.yy"
                                    { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_dot_index_exp(yylhs.location, yystack_[2].value.as < pdm::ast::Exp* > (), yystack_[0].value.as < pdm::ast::Exp* > (), ast::DotIndexExp::RhsHint::LhsNotPtr); }
#line 2878 "parser.tab.cc"
    break;

  case 108: // dot_index_exp: postfix_exp "." bracketed_exp
#line 524 "parser.yy"
                                    { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_dot_index_exp(yylhs.location, yystack_[2].value.as < pdm::ast::Exp* > (), yystack_[0].value.as < pdm::ast::Exp* > (), ast::DotIndexExp::RhsHint::LhsNotPtr); }
#line 2884 "parser.tab.cc"
    break;

  case 109: // unary_exp: postfix_exp
#line 528 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2890 "parser.tab.cc"
    break;

  case 110: // unary_exp: unary_op unary_exp
#line 529 "parser.yy"
                             { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_unary_exp(yylhs.location, yystack_[1].value.as < pdm::ast::UnaryOperator > (), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2896 "parser.tab.cc"
    break;

  case 111: // unary_op: "+"
#line 532 "parser.yy"
                 { yylhs.value.as < pdm::ast::UnaryOperator > () = ast::UnaryOperator::Plus; }
#line 2902 "parser.tab.cc"
    break;

  case 112: // unary_op: "-"
#line 533 "parser.yy"
                 { yylhs.value.as < pdm::ast::UnaryOperator > () = ast::UnaryOperator::Minus; }
#line 2908 "parser.tab.cc"
    break;

  case 113: // unary_op: "*"
#line 534 "parser.yy"
                 { yylhs.value.as < pdm::ast::UnaryOperator > () = ast::UnaryOperator::DeRef; }
#line 2914 "parser.tab.cc"
    break;

  case 114: // unary_op: "^"
#line 535 "parser.yy"
                 { yylhs.value.as < pdm::ast::UnaryOperator > () = ast::UnaryOperator::GetRef; }
#line 2920 "parser.tab.cc"
    break;

  case 115: // unary_op: "not"
#line 536 "parser.yy"
                 { yylhs.value.as < pdm::ast::UnaryOperator > () = ast::UnaryOperator::Not; }
#line 2926 "parser.tab.cc"
    break;

  case 116: // binary_exp: or_binary_exp
#line 540 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2932 "parser.tab.cc"
    break;

  case 117: // mul_binary_op: "*"
#line 543 "parser.yy"
                 { yylhs.value.as < pdm::ast::BinaryOperator > () = ast::BinaryOperator::Mul; }
#line 2938 "parser.tab.cc"
    break;

  case 118: // mul_binary_op: "/"
#line 544 "parser.yy"
                 { yylhs.value.as < pdm::ast::BinaryOperator > () = ast::BinaryOperator::Div; }
#line 2944 "parser.tab.cc"
    break;

  case 119: // mul_binary_op: "%"
#line 545 "parser.yy"
                 { yylhs.value.as < pdm::ast::BinaryOperator > () = ast::BinaryOperator::Rem; }
#line 2950 "parser.tab.cc"
    break;

  case 120: // mul_binary_exp: unary_exp
#line 548 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2956 "parser.tab.cc"
    break;

  case 121: // mul_binary_exp: mul_binary_exp mul_binary_op unary_exp
#line 549 "parser.yy"
                                               { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_binary_exp(yylhs.location, yystack_[1].value.as < pdm::ast::BinaryOperator > (), yystack_[2].value.as < pdm::ast::Exp* > (), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2962 "parser.tab.cc"
    break;

  case 122: // add_binary_op: "+"
#line 552 "parser.yy"
             { yylhs.value.as < pdm::ast::BinaryOperator > () = ast::BinaryOperator::Add; }
#line 2968 "parser.tab.cc"
    break;

  case 123: // add_binary_op: "-"
#line 553 "parser.yy"
             { yylhs.value.as < pdm::ast::BinaryOperator > () = ast::BinaryOperator::Subtract; }
#line 2974 "parser.tab.cc"
    break;

  case 124: // add_binary_exp: mul_binary_exp
#line 556 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2980 "parser.tab.cc"
    break;

  case 125: // add_binary_exp: add_binary_exp add_binary_op mul_binary_exp
#line 557 "parser.yy"
                                                    { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_binary_exp(yylhs.location, yystack_[1].value.as < pdm::ast::BinaryOperator > (), yystack_[2].value.as < pdm::ast::Exp* > (), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2986 "parser.tab.cc"
    break;

  case 126: // cmp_binary_op: "<"
#line 560 "parser.yy"
                { yylhs.value.as < pdm::ast::BinaryOperator > () = ast::BinaryOperator::Less; }
#line 2992 "parser.tab.cc"
    break;

  case 127: // cmp_binary_op: "<="
#line 561 "parser.yy"
                { yylhs.value.as < pdm::ast::BinaryOperator > () = ast::BinaryOperator::LessOrEq; }
#line 2998 "parser.tab.cc"
    break;

  case 128: // cmp_binary_op: ">"
#line 562 "parser.yy"
                { yylhs.value.as < pdm::ast::BinaryOperator > () = ast::BinaryOperator::Greater; }
#line 3004 "parser.tab.cc"
    break;

  case 129: // cmp_binary_op: ">="
#line 563 "parser.yy"
                { yylhs.value.as < pdm::ast::BinaryOperator > () = ast::BinaryOperator::GreaterOrEq; }
#line 3010 "parser.tab.cc"
    break;

  case 130: // cmp_binary_exp: add_binary_exp
#line 566 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 3016 "parser.tab.cc"
    break;

  case 131: // cmp_binary_exp: cmp_binary_exp cmp_binary_op add_binary_exp
#line 567 "parser.yy"
                                                    { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_binary_exp(yylhs.location, yystack_[1].value.as < pdm::ast::BinaryOperator > (), yystack_[2].value.as < pdm::ast::Exp* > (), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 3022 "parser.tab.cc"
    break;

  case 132: // eq_binary_op: "=="
#line 570 "parser.yy"
                 { yylhs.value.as < pdm::ast::BinaryOperator > () = ast::BinaryOperator::Equals; }
#line 3028 "parser.tab.cc"
    break;

  case 133: // eq_binary_op: "!="
#line 571 "parser.yy"
                 { yylhs.value.as < pdm::ast::BinaryOperator > () = ast::BinaryOperator::NotEquals; }
#line 3034 "parser.tab.cc"
    break;

  case 134: // eq_binary_exp: cmp_binary_exp
#line 574 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 3040 "parser.tab.cc"
    break;

  case 135: // eq_binary_exp: eq_binary_exp eq_binary_op cmp_binary_exp
#line 575 "parser.yy"
                                                { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_binary_exp(yylhs.location, yystack_[1].value.as < pdm::ast::BinaryOperator > (), yystack_[2].value.as < pdm::ast::Exp* > (), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 3046 "parser.tab.cc"
    break;

  case 136: // and_binary_exp: eq_binary_exp
#line 578 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 3052 "parser.tab.cc"
    break;

  case 137: // and_binary_exp: and_binary_exp "and" eq_binary_exp
#line 579 "parser.yy"
                                           { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_binary_exp(yylhs.location, ast::BinaryOperator::And, yystack_[2].value.as < pdm::ast::Exp* > (), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 3058 "parser.tab.cc"
    break;

  case 138: // xor_binary_exp: and_binary_exp
#line 582 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 3064 "parser.tab.cc"
    break;

  case 139: // xor_binary_exp: xor_binary_exp "xor" and_binary_exp
#line 583 "parser.yy"
                                           { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_binary_exp(yylhs.location, ast::BinaryOperator::XOr, yystack_[2].value.as < pdm::ast::Exp* > (), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 3070 "parser.tab.cc"
    break;

  case 140: // or_binary_exp: xor_binary_exp
#line 586 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 3076 "parser.tab.cc"
    break;

  case 141: // or_binary_exp: or_binary_exp "or" xor_binary_exp
#line 587 "parser.yy"
                                           { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_binary_exp(yylhs.location, ast::BinaryOperator::Or, yystack_[2].value.as < pdm::ast::Exp* > (), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 3082 "parser.tab.cc"
    break;

  case 142: // type_query_exp: type_spec type_query_op long_type_spec
#line 591 "parser.yy"
                                               { yylhs.value.as < pdm::ast::TypeQueryExp* > () = mgr->new_type_query_exp(yylhs.location, yystack_[1].value.as < pdm::ast::TypeQueryKind > (), yystack_[2].value.as < pdm::ast::TypeSpec* > (), yystack_[0].value.as < pdm::ast::TypeSpec* > ()); }
#line 3088 "parser.tab.cc"
    break;

  case 143: // type_query_op: ":<"
#line 594 "parser.yy"
                    { yylhs.value.as < pdm::ast::TypeQueryKind > () = ast::TypeQueryKind::LhsSubtypesRhs; }
#line 3094 "parser.tab.cc"
    break;

  case 144: // type_query_op: ">:"
#line 595 "parser.yy"
                    { yylhs.value.as < pdm::ast::TypeQueryKind > () = ast::TypeQueryKind::LhsSupertypesRhs; }
#line 3100 "parser.tab.cc"
    break;

  case 145: // type_query_op: "::"
#line 596 "parser.yy"
                    { yylhs.value.as < pdm::ast::TypeQueryKind > () = ast::TypeQueryKind::LhsEqualsRhs; }
#line 3106 "parser.tab.cc"
    break;

  case 146: // type_spec: unary_type_spec
#line 604 "parser.yy"
      { yylhs.value.as < pdm::ast::TypeSpec* > () = yystack_[0].value.as < pdm::ast::TypeSpec* > (); }
#line 3112 "parser.tab.cc"
    break;

  case 147: // type_spec_cl1: type_spec
#line 607 "parser.yy"
                                   { yylhs.value.as < std::vector<pdm::ast::TypeSpec*> > ().push_back(yystack_[0].value.as < pdm::ast::TypeSpec* > ()); }
#line 3118 "parser.tab.cc"
    break;

  case 148: // type_spec_cl1: type_spec_cl1 "," type_spec
#line 608 "parser.yy"
                                    { yylhs.value.as < std::vector<pdm::ast::TypeSpec*> > () = std::move(yystack_[2].value.as < std::vector<pdm::ast::TypeSpec*> > ()); yylhs.value.as < std::vector<pdm::ast::TypeSpec*> > ().push_back(yystack_[0].value.as < pdm::ast::TypeSpec* > ()); }
#line 3124 "parser.tab.cc"
    break;

  case 149: // type_spec_cl2: type_spec "," type_spec
#line 611 "parser.yy"
                                    { yylhs.value.as < std::vector<pdm::ast::TypeSpec*> > ().reserve(2); yylhs.value.as < std::vector<pdm::ast::TypeSpec*> > ().push_back(yystack_[2].value.as < pdm::ast::TypeSpec* > ()); yylhs.value.as < std::vector<pdm::ast::TypeSpec*> > ().push_back(yystack_[0].value.as < pdm::ast::TypeSpec* > ()); }
#line 3130 "parser.tab.cc"
    break;

  case 150: // type_spec_cl2: type_spec_cl2 "," type_spec
#line 612 "parser.yy"
                                    { yylhs.value.as < std::vector<pdm::ast::TypeSpec*> > () = std::move(yystack_[2].value.as < std::vector<pdm::ast::TypeSpec*> > ()); yylhs.value.as < std::vector<pdm::ast::TypeSpec*> > ().push_back(yystack_[0].value.as < pdm::ast::TypeSpec* > ()); }
#line 3136 "parser.tab.cc"
    break;

  case 151: // struct_type_spec_field: vid type_spec
#line 616 "parser.yy"
                                   { yylhs.value.as < pdm::ast::StructTypeSpec::Field* > () = mgr->new_struct_type_spec_field(yylhs.location, yystack_[1].value.as < TokenInfo > ().ID_intstr, yystack_[0].value.as < pdm::ast::TypeSpec* > ()); }
#line 3142 "parser.tab.cc"
    break;

  case 152: // struct_type_spec_field_cl: struct_type_spec_field
#line 619 "parser.yy"
                                                           { yylhs.value.as < std::vector<pdm::ast::StructTypeSpec::Field*> > ().push_back(yystack_[0].value.as < pdm::ast::StructTypeSpec::Field* > ()); }
#line 3148 "parser.tab.cc"
    break;

  case 153: // struct_type_spec_field_cl: struct_type_spec_field_cl "," struct_type_spec_field
#line 620 "parser.yy"
                                                              { yylhs.value.as < std::vector<pdm::ast::StructTypeSpec::Field*> > () = std::move(yystack_[2].value.as < std::vector<pdm::ast::StructTypeSpec::Field*> > ()); yylhs.value.as < std::vector<pdm::ast::StructTypeSpec::Field*> > ().push_back(yystack_[0].value.as < pdm::ast::StructTypeSpec::Field* > ()); }
#line 3154 "parser.tab.cc"
    break;

  case 154: // primary_type_spec: tid
#line 624 "parser.yy"
                        { yylhs.value.as < pdm::ast::TypeSpec* > () = mgr->new_id_type_spec(yylhs.location, yystack_[0].value.as < TokenInfo > ().ID_intstr); }
#line 3160 "parser.tab.cc"
    break;

  case 155: // primary_type_spec: paren_type_spec
#line 625 "parser.yy"
      { yylhs.value.as < pdm::ast::TypeSpec* > () = yystack_[0].value.as < pdm::ast::TypeSpec* > (); }
#line 3166 "parser.tab.cc"
    break;

  case 156: // primary_type_spec: tuple_type_spec
#line 626 "parser.yy"
      { yylhs.value.as < pdm::ast::TypeSpec* > () = yystack_[0].value.as < pdm::ast::TypeSpec* > (); }
#line 3172 "parser.tab.cc"
    break;

  case 157: // primary_type_spec: mod_prefix_tid
#line 627 "parser.yy"
      { yylhs.value.as < pdm::ast::TypeSpec* > () = yystack_[0].value.as < pdm::ast::TypeSpec* > (); }
#line 3178 "parser.tab.cc"
    break;

  case 158: // primary_type_spec: fn_type_spec
#line 628 "parser.yy"
      { yylhs.value.as < pdm::ast::TypeSpec* > () = yystack_[0].value.as < pdm::ast::TypeSpec* > (); }
#line 3184 "parser.tab.cc"
    break;

  case 159: // paren_type_spec: "(" type_spec ")"
#line 631 "parser.yy"
                                 { yylhs.value.as < pdm::ast::TypeSpec* > () = mgr->new_paren_type_spec(yylhs.location, yystack_[1].value.as < pdm::ast::TypeSpec* > ()); }
#line 3190 "parser.tab.cc"
    break;

  case 160: // tuple_type_spec: "(" type_spec "," ")"
#line 634 "parser.yy"
                                     { yylhs.value.as < pdm::ast::TypeSpec* > () = mgr->new_tuple_type_spec(yylhs.location, std::move(std::vector(1,yystack_[2].value.as < pdm::ast::TypeSpec* > ()))); }
#line 3196 "parser.tab.cc"
    break;

  case 161: // tuple_type_spec: "(" type_spec_cl2 ")"
#line 635 "parser.yy"
                                     { yylhs.value.as < pdm::ast::TypeSpec* > () = mgr->new_tuple_type_spec(yylhs.location, std::move(yystack_[1].value.as < std::vector<pdm::ast::TypeSpec*> > ())); }
#line 3202 "parser.tab.cc"
    break;

  case 162: // mod_prefix_tid: mod_prefix tid
#line 638 "parser.yy"
                            { yylhs.value.as < pdm::ast::TypeSpec* > () = mgr->new_dot_name_type_spec_with_mod_prefix(yylhs.location, std::move(yystack_[1].value.as < std::vector<pdm::intern::String> > ()), yystack_[0].value.as < TokenInfo > ().ID_intstr); }
#line 3208 "parser.tab.cc"
    break;

  case 163: // fn_type_spec: "Fn" vpattern primary_type_spec
#line 641 "parser.yy"
                                        { yylhs.value.as < pdm::ast::TypeSpec* > () = mgr->new_fn_type_spec(yylhs.location, std::move(yystack_[1].value.as < pdm::ast::VPattern* > ()), yystack_[0].value.as < pdm::ast::TypeSpec* > ()); }
#line 3214 "parser.tab.cc"
    break;

  case 164: // postfix_type_spec: primary_type_spec
#line 645 "parser.yy"
      { yylhs.value.as < pdm::ast::TypeSpec* > () = yystack_[0].value.as < pdm::ast::TypeSpec* > (); }
#line 3220 "parser.tab.cc"
    break;

  case 165: // postfix_type_spec: tcall_type_spec
#line 646 "parser.yy"
      { yylhs.value.as < pdm::ast::TypeSpec* > () = yystack_[0].value.as < pdm::ast::TypeSpec* > (); }
#line 3226 "parser.tab.cc"
    break;

  case 166: // tcall_type_spec: postfix_type_spec "[" targ_cl "]"
#line 649 "parser.yy"
                                               { yylhs.value.as < pdm::ast::TypeSpec* > () = mgr->new_tcall_type_spec(yylhs.location, yystack_[3].value.as < pdm::ast::TypeSpec* > (), std::move(yystack_[1].value.as < std::vector<pdm::ast::TArg*> > ())); }
#line 3232 "parser.tab.cc"
    break;

  case 167: // unary_type_spec: postfix_type_spec
#line 653 "parser.yy"
      { yylhs.value.as < pdm::ast::TypeSpec* > () = yystack_[0].value.as < pdm::ast::TypeSpec* > (); }
#line 3238 "parser.tab.cc"
    break;

  case 168: // long_type_spec: unary_type_spec
#line 657 "parser.yy"
      { yylhs.value.as < pdm::ast::TypeSpec* > () = yystack_[0].value.as < pdm::ast::TypeSpec* > (); }
#line 3244 "parser.tab.cc"
    break;

  case 169: // long_type_spec: struct_type_spec
#line 658 "parser.yy"
      { yylhs.value.as < pdm::ast::TypeSpec* > () = yystack_[0].value.as < pdm::ast::TypeSpec* > (); }
#line 3250 "parser.tab.cc"
    break;

  case 170: // struct_type_spec: "{" struct_type_spec_field_cl "}"
#line 661 "parser.yy"
                                               { yylhs.value.as < pdm::ast::TypeSpec* > () = mgr->new_struct_type_spec(yylhs.location, std::move(yystack_[1].value.as < std::vector<pdm::ast::StructTypeSpec::Field*> > ())); }
#line 3256 "parser.tab.cc"
    break;

  case 171: // targ: type_spec
#line 664 "parser.yy"
                { yylhs.value.as < pdm::ast::TArg* > () = mgr->new_targ_type_spec(yylhs.location, yystack_[0].value.as < pdm::ast::TypeSpec* > ()); }
#line 3262 "parser.tab.cc"
    break;

  case 172: // targ: expr
#line 665 "parser.yy"
               { yylhs.value.as < pdm::ast::TArg* > () = mgr->new_targ_exp(yylhs.location, yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 3268 "parser.tab.cc"
    break;

  case 173: // targ_cl: targ
#line 668 "parser.yy"
                            { yylhs.value.as < std::vector<pdm::ast::TArg*> > ().push_back(yystack_[0].value.as < pdm::ast::TArg* > ()); }
#line 3274 "parser.tab.cc"
    break;

  case 174: // targ_cl: targ_cl "," targ
#line 669 "parser.yy"
                            { yylhs.value.as < std::vector<pdm::ast::TArg*> > () = std::move(yystack_[2].value.as < std::vector<pdm::ast::TArg*> > ()); yylhs.value.as < std::vector<pdm::ast::TArg*> > ().push_back(yystack_[0].value.as < pdm::ast::TArg* > ()); }
#line 3280 "parser.tab.cc"
    break;

  case 175: // varg: expr
#line 671 "parser.yy"
                            { yylhs.value.as < pdm::ast::VArg* > () = mgr->new_varg(yylhs.location, yystack_[0].value.as < pdm::ast::Exp* > (), ast::VArgAccessSpec::In); }
#line 3286 "parser.tab.cc"
    break;

  case 176: // varg: "out" expr
#line 672 "parser.yy"
                            { yylhs.value.as < pdm::ast::VArg* > () = mgr->new_varg(yylhs.location, yystack_[0].value.as < pdm::ast::Exp* > (), ast::VArgAccessSpec::Out); }
#line 3292 "parser.tab.cc"
    break;

  case 177: // varg: "inout" expr
#line 673 "parser.yy"
                            { yylhs.value.as < pdm::ast::VArg* > () = mgr->new_varg(yylhs.location, yystack_[0].value.as < pdm::ast::Exp* > (), ast::VArgAccessSpec::InOut); }
#line 3298 "parser.tab.cc"
    break;

  case 178: // varg_cl: varg
#line 676 "parser.yy"
                            { yylhs.value.as < std::vector<pdm::ast::VArg*> > ().push_back(yystack_[0].value.as < pdm::ast::VArg* > ()); }
#line 3304 "parser.tab.cc"
    break;

  case 179: // varg_cl: varg_cl "," varg
#line 677 "parser.yy"
                            { yylhs.value.as < std::vector<pdm::ast::VArg*> > () = std::move(yystack_[2].value.as < std::vector<pdm::ast::VArg*> > ()); yylhs.value.as < std::vector<pdm::ast::VArg*> > ().push_back(yystack_[0].value.as < pdm::ast::VArg* > ()); }
#line 3310 "parser.tab.cc"
    break;

  case 180: // class_spec: postfix_class_spec
#line 687 "parser.yy"
      { yylhs.value.as < pdm::ast::ClassSpec* > () = yystack_[0].value.as < pdm::ast::ClassSpec* > (); }
#line 3316 "parser.tab.cc"
    break;

  case 181: // primary_class_spec: tid
#line 690 "parser.yy"
            { yylhs.value.as < pdm::ast::ClassSpec* > () = mgr->new_id_class_spec(yylhs.location, yystack_[0].value.as < TokenInfo > ().ID_intstr); }
#line 3322 "parser.tab.cc"
    break;

  case 182: // postfix_class_spec: primary_class_spec
#line 693 "parser.yy"
      { yylhs.value.as < pdm::ast::ClassSpec* > () = yystack_[0].value.as < pdm::ast::ClassSpec* > (); }
#line 3328 "parser.tab.cc"
    break;

  case 183: // postfix_class_spec: postfix_class_spec "[" targ_cl "]"
#line 694 "parser.yy"
                                                { yylhs.value.as < pdm::ast::ClassSpec* > () = mgr->new_tcall_class_spec(yylhs.location, yystack_[3].value.as < pdm::ast::ClassSpec* > (), std::move(yystack_[1].value.as < std::vector<pdm::ast::TArg*> > ())); }
#line 3334 "parser.tab.cc"
    break;

  case 184: // struct_exp_field: vid "=" expr
#line 702 "parser.yy"
                    { yylhs.value.as < pdm::ast::StructExp::Field* > () = mgr->new_struct_exp_field(yylhs.location, yystack_[2].value.as < TokenInfo > ().ID_intstr, yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 3340 "parser.tab.cc"
    break;

  case 185: // vpattern_field: vid type_spec
#line 705 "parser.yy"
                             { yylhs.value.as < pdm::ast::VPattern::Field* > () = mgr->new_vpattern_field(yylhs.location, yystack_[1].value.as < TokenInfo > ().ID_intstr, yystack_[0].value.as < pdm::ast::TypeSpec* > (), ast::VArgAccessSpec::In); }
#line 3346 "parser.tab.cc"
    break;

  case 186: // vpattern_field: "out" vid type_spec
#line 706 "parser.yy"
                             { yylhs.value.as < pdm::ast::VPattern::Field* > () = mgr->new_vpattern_field(yylhs.location, yystack_[1].value.as < TokenInfo > ().ID_intstr, yystack_[0].value.as < pdm::ast::TypeSpec* > (), ast::VArgAccessSpec::Out); }
#line 3352 "parser.tab.cc"
    break;

  case 187: // vpattern_field: "inout" vid type_spec
#line 707 "parser.yy"
                             { yylhs.value.as < pdm::ast::VPattern::Field* > () = mgr->new_vpattern_field(yylhs.location, yystack_[1].value.as < TokenInfo > ().ID_intstr, yystack_[0].value.as < pdm::ast::TypeSpec* > (), ast::VArgAccessSpec::InOut); }
#line 3358 "parser.tab.cc"
    break;

  case 188: // lpattern_field: vid type_spec
#line 710 "parser.yy"
                     { yylhs.value.as < pdm::ast::LPattern::Field* > () = mgr->new_lpattern_field(yylhs.location, ast::LPattern::FieldKind::IdTypeSpecPair, yystack_[1].value.as < TokenInfo > ().ID_intstr, yystack_[0].value.as < pdm::ast::TypeSpec* > ()); }
#line 3364 "parser.tab.cc"
    break;

  case 189: // lpattern_field: vid
#line 711 "parser.yy"
                    { yylhs.value.as < pdm::ast::LPattern::Field* > () = mgr->new_lpattern_field(yylhs.location, ast::LPattern::FieldKind::IdSingleton, yystack_[0].value.as < TokenInfo > ().ID_intstr); }
#line 3370 "parser.tab.cc"
    break;

  case 190: // tpattern_field: vid type_spec
#line 714 "parser.yy"
                      { yylhs.value.as < pdm::ast::TPattern::Field* > () = mgr->new_tpattern_field(yylhs.location, ast::TPattern::FieldKind::Value, yystack_[1].value.as < TokenInfo > ().ID_intstr, yystack_[0].value.as < pdm::ast::TypeSpec* > ()); }
#line 3376 "parser.tab.cc"
    break;

  case 191: // tpattern_field: tid class_spec
#line 715 "parser.yy"
                      { yylhs.value.as < pdm::ast::TPattern::Field* > () = mgr->new_tpattern_field(yylhs.location, ast::TPattern::FieldKind::Type, yystack_[1].value.as < TokenInfo > ().ID_intstr, yystack_[0].value.as < pdm::ast::ClassSpec* > ()); }
#line 3382 "parser.tab.cc"
    break;

  case 192: // destructured_lpattern: "(" lpattern_field_cl ")"
#line 719 "parser.yy"
                                          { yylhs.value.as < pdm::ast::LPattern* > () = mgr->new_lpattern(yylhs.location, std::move(yystack_[1].value.as < std::vector<pdm::ast::LPattern::Field*> > ()), true); }
#line 3388 "parser.tab.cc"
    break;

  case 193: // lpattern: lpattern_field
#line 723 "parser.yy"
                        { yylhs.value.as < pdm::ast::LPattern* > () = mgr->new_lpattern(yylhs.location, std::move(std::vector<ast::LPattern::Field*>{1,yystack_[0].value.as < pdm::ast::LPattern::Field* > ()}), false); }
#line 3394 "parser.tab.cc"
    break;

  case 194: // lpattern: destructured_lpattern
#line 724 "parser.yy"
      { yylhs.value.as < pdm::ast::LPattern* > () = yystack_[0].value.as < pdm::ast::LPattern* > (); }
#line 3400 "parser.tab.cc"
    break;

  case 195: // vpattern: "(" vpattern_field_cl ")"
#line 727 "parser.yy"
                                       { yylhs.value.as < pdm::ast::VPattern* > () = mgr->new_vpattern(yylhs.location, std::move(yystack_[1].value.as < std::vector<pdm::ast::VPattern::Field*> > ())); }
#line 3406 "parser.tab.cc"
    break;

  case 196: // vpattern: "(" ")"
#line 728 "parser.yy"
                                       { yylhs.value.as < pdm::ast::VPattern* > () = mgr->new_vpattern(yylhs.location, std::move(std::vector<ast::VPattern::Field*>{})); }
#line 3412 "parser.tab.cc"
    break;

  case 197: // tpattern: "[" tpattern_field_cl "]"
#line 731 "parser.yy"
                                               { yylhs.value.as < pdm::ast::TPattern* > () = mgr->new_tpattern(yylhs.location, std::move(yystack_[1].value.as < std::vector<pdm::ast::TPattern::Field*> > ()), false); }
#line 3418 "parser.tab.cc"
    break;

  case 198: // tpattern: "!" "[" tpattern_field_cl "]"
#line 732 "parser.yy"
                                               { yylhs.value.as < pdm::ast::TPattern* > () = mgr->new_tpattern(yylhs.location, std::move(yystack_[1].value.as < std::vector<pdm::ast::TPattern::Field*> > ()), true); }
#line 3424 "parser.tab.cc"
    break;

  case 199: // vpattern_field_cl: vpattern_field
#line 736 "parser.yy"
                                              { yylhs.value.as < std::vector<pdm::ast::VPattern::Field*> > ().push_back(yystack_[0].value.as < pdm::ast::VPattern::Field* > ()); }
#line 3430 "parser.tab.cc"
    break;

  case 200: // vpattern_field_cl: vpattern_field_cl "," vpattern_field
#line 737 "parser.yy"
                                               { yylhs.value.as < std::vector<pdm::ast::VPattern::Field*> > () = std::move(yystack_[2].value.as < std::vector<pdm::ast::VPattern::Field*> > ()); yylhs.value.as < std::vector<pdm::ast::VPattern::Field*> > ().push_back(yystack_[0].value.as < pdm::ast::VPattern::Field* > ()); }
#line 3436 "parser.tab.cc"
    break;

  case 201: // lpattern_field_cl: lpattern_field
#line 740 "parser.yy"
                                              { yylhs.value.as < std::vector<pdm::ast::LPattern::Field*> > ().push_back(yystack_[0].value.as < pdm::ast::LPattern::Field* > ()); }
#line 3442 "parser.tab.cc"
    break;

  case 202: // lpattern_field_cl: lpattern_field_cl "," lpattern_field
#line 741 "parser.yy"
                                               { yylhs.value.as < std::vector<pdm::ast::LPattern::Field*> > () = std::move(yystack_[2].value.as < std::vector<pdm::ast::LPattern::Field*> > ()); yylhs.value.as < std::vector<pdm::ast::LPattern::Field*> > ().push_back(yystack_[0].value.as < pdm::ast::LPattern::Field* > ()); }
#line 3448 "parser.tab.cc"
    break;

  case 203: // tpattern_field_cl: tpattern_field
#line 744 "parser.yy"
                                              { yylhs.value.as < std::vector<pdm::ast::TPattern::Field*> > ().push_back(yystack_[0].value.as < pdm::ast::TPattern::Field* > ()); }
#line 3454 "parser.tab.cc"
    break;

  case 204: // tpattern_field_cl: tpattern_field_cl "," tpattern_field
#line 745 "parser.yy"
                                               { yylhs.value.as < std::vector<pdm::ast::TPattern::Field*> > () = std::move(yystack_[2].value.as < std::vector<pdm::ast::TPattern::Field*> > ()); yylhs.value.as < std::vector<pdm::ast::TPattern::Field*> > ().push_back(yystack_[0].value.as < pdm::ast::TPattern::Field* > ()); }
#line 3460 "parser.tab.cc"
    break;

  case 205: // struct_exp_field_cl: struct_exp_field
#line 748 "parser.yy"
                                                    { yylhs.value.as < std::vector<pdm::ast::StructExp::Field*> > ().push_back(yystack_[0].value.as < pdm::ast::StructExp::Field* > ()); }
#line 3466 "parser.tab.cc"
    break;

  case 206: // struct_exp_field_cl: struct_exp_field_cl "," struct_exp_field
#line 749 "parser.yy"
                                                    { yylhs.value.as < std::vector<pdm::ast::StructExp::Field*> > () = std::move(yystack_[2].value.as < std::vector<pdm::ast::StructExp::Field*> > ()); yylhs.value.as < std::vector<pdm::ast::StructExp::Field*> > ().push_back(yystack_[0].value.as < pdm::ast::StructExp::Field* > ()); }
#line 3472 "parser.tab.cc"
    break;

  case 207: // tpattern_seq: tpattern
#line 753 "parser.yy"
                             { yylhs.value.as < std::vector<pdm::ast::TPattern*> > ().push_back(yystack_[0].value.as < pdm::ast::TPattern* > ()); }
#line 3478 "parser.tab.cc"
    break;

  case 208: // tpattern_seq: tpattern_seq tpattern
#line 754 "parser.yy"
                             { yylhs.value.as < std::vector<pdm::ast::TPattern*> > () = std::move(yystack_[1].value.as < std::vector<pdm::ast::TPattern*> > ()); yylhs.value.as < std::vector<pdm::ast::TPattern*> > ().push_back(yystack_[0].value.as < pdm::ast::TPattern* > ()); }
#line 3484 "parser.tab.cc"
    break;


#line 3488 "parser.tab.cc"

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





  const short parser::yypact_ninf_ = -323;

  const signed char parser::yytable_ninf_ = -50;

  const short
  parser::yypact_[] =
  {
    -323,    37,    20,  -323,    38,    38,    39,    32,  -323,  -323,
    -323,    74,   106,  -323,   102,  -323,  -323,   173,   758,   156,
    -323,  -323,   113,  -323,    59,   111,  -323,  -323,  -323,  -323,
    -323,  -323,   686,   532,  -323,  -323,  -323,  -323,   128,  -323,
    -323,   176,  -323,  -323,  -323,  -323,  -323,  -323,  -323,  -323,
     183,  -323,  -323,  -323,   133,  -323,  -323,  -323,  -323,  -323,
     758,  -323,   166,   168,   157,   165,   152,   209,   155,   125,
     173,   231,    89,    42,  -323,   202,   200,    96,    21,    21,
      21,   758,   758,  -323,   204,  -323,  -323,  -323,  -323,  -323,
     188,   207,   580,  -323,   -27,  -323,   213,   217,  -323,  -323,
      28,   469,   367,  -323,  -323,  -323,  -323,   758,  -323,  -323,
     758,  -323,  -323,  -323,  -323,   758,  -323,  -323,   758,   758,
     758,   758,   180,  -323,    59,   245,   245,  -323,    78,  -323,
     145,    78,  -323,   722,  -323,   758,  -323,   245,    78,  -323,
    -323,   198,   203,   206,   210,  -323,  -323,   758,  -323,  -323,
     218,   226,   245,  -323,  -323,  -323,   233,  -323,  -323,   758,
     758,  -323,  -323,  -323,   150,   111,   615,   128,   228,  -323,
    -323,  -323,  -323,  -323,  -323,  -323,   216,  -323,  -323,  -323,
      48,  -323,   166,   168,   157,   165,   152,   209,   273,  -323,
     180,   241,  -323,  -323,  -323,  -323,    93,    10,   276,    78,
      78,    78,   234,  -323,    83,  -323,    59,  -323,  -323,  -323,
    -323,   159,  -323,   758,   758,   758,   758,  -323,  -323,  -323,
     188,  -323,  -323,  -323,  -323,   651,  -323,    78,   160,   161,
    -323,   367,   367,  -323,   101,   243,  -323,   234,    36,   244,
      38,   235,  -323,  -323,   104,   758,   272,    13,   108,  -323,
    -323,  -323,  -323,   245,  -323,  -323,  -323,  -323,  -323,   162,
    -323,  -323,    23,  -323,    78,  -323,    64,  -323,   180,   127,
    -323,    38,    78,  -323,    86,   245,  -323,  -323,  -323,   234,
     227,  -323,   248,    38,    36,   238,  -323,  -323,  -323,    38,
     758,   283,  -323,  -323,   758,  -323,  -323,  -323,  -323,  -323,
      12,   180,  -323,  -323,  -323,   255,  -323,   234,  -323,    78,
    -323,   -10,   107,    38,    72,    38,  -323,    38,   173,  -323,
      38,  -323,  -323,    15,   367,  -323,  -323,   245,  -323,  -323,
    -323,  -323,  -323,   167,   247,    38,  -323,   173,  -323,   110,
    -323,    78,  -323,   259,   260,  -323,  -323,  -323,    78,   271,
      22,   261,    61,    78,  -323,   280,  -323,  -323,  -323,  -323,
      36,    25,  -323,  -323,  -323
  };

  const unsigned char
  parser::yydefact_[] =
  {
       3,     0,     7,     1,     0,     0,     0,     2,     5,     6,
      48,     0,     0,     4,     0,     8,     9,     0,     0,     0,
      52,    51,     0,    49,     0,     0,   115,    81,    82,    50,
      84,    83,     0,     0,   113,   111,   112,   114,     0,    75,
      77,     0,    37,    74,    63,    64,    65,    66,    96,    76,
      78,    79,    67,    80,   109,    97,    98,    99,   100,   120,
       0,    55,   124,   130,   134,   136,   138,   140,   116,     0,
       0,     0,     0,     0,    68,    56,     0,     0,     0,     0,
       0,     0,     0,    69,     0,    38,    39,    40,    41,    42,
      75,     0,     0,   205,     0,    53,   106,     0,    86,    85,
       0,     0,     0,   110,   117,   118,   119,     0,   122,   123,
       0,   126,   127,   128,   129,     0,   132,   133,     0,     0,
       0,     0,     0,    36,     0,     0,     0,   196,     0,   199,
       0,     0,    94,     0,    70,     0,    72,     0,   189,   193,
     194,     0,     0,     0,     0,    47,    92,     0,    89,    90,
       0,     0,     0,    73,    54,   104,     0,   108,   107,     0,
       0,   102,   175,   178,     0,     0,     0,   154,     0,   172,
     171,   164,   155,   156,   157,   158,   167,   165,   146,   173,
       0,   121,   125,   131,   135,   137,   139,   141,     0,    19,
      10,     0,    15,    16,    17,    18,     0,     0,    87,     0,
       0,     0,     0,   185,     0,   195,     0,    71,    59,    60,
     201,     0,   188,     0,     0,     0,     0,   184,    93,    91,
       0,   206,    57,   176,   177,     0,   103,     0,     0,     0,
     162,     0,     0,   101,     0,     0,    13,     0,     0,     0,
       0,     0,    26,   207,     0,     0,     0,     0,     0,   186,
     187,   200,    95,     0,   192,    43,    44,    45,    46,     0,
     179,   163,     0,   159,     0,   161,     0,   174,     0,     0,
      14,     0,     0,   203,     0,     0,   168,    24,   169,     0,
      28,    29,    31,     0,     0,     0,    27,   208,    20,     0,
       0,     0,    88,   202,     0,   105,   160,   149,   150,   166,
       0,     0,   181,   191,   182,   180,   190,     0,   197,     0,
     152,     0,     0,     0,     0,     0,    25,     0,     0,    21,
       0,    58,    11,     0,     0,   204,   151,     0,   170,   198,
      30,    32,   147,     0,     0,     0,    22,     0,    12,     0,
     153,     0,    33,     0,     0,    23,   183,   148,     0,     0,
       0,     0,     0,     0,    34,     0,    61,   145,   143,   144,
       0,     0,    62,   142,    35
  };

  const short
  parser::yypgoto_[] =
  {
    -323,  -323,  -323,  -323,  -323,  -323,  -323,  -323,  -257,  -188,
    -323,  -323,  -323,    79,  -323,    11,  -323,  -323,  -323,   236,
    -323,  -323,  -323,  -323,  -323,    -4,   -29,  -323,   -67,   184,
     148,  -323,  -323,  -323,   -28,   -19,  -323,  -323,  -323,  -323,
      81,   230,  -323,  -323,  -323,  -323,  -323,  -323,  -323,  -323,
    -323,  -323,   -50,  -323,  -323,  -323,   223,  -323,   211,  -323,
     220,  -323,   208,   219,   221,  -323,  -322,  -323,   135,  -323,
    -323,    14,  -323,   116,  -323,  -323,  -323,  -323,  -323,  -323,
    -232,  -276,  -323,   115,  -224,   120,  -323,  -228,  -323,  -323,
     196,   136,  -128,    44,  -323,   174,   187,  -222,  -323,  -323,
      75,  -323,  -156
  };

  const short
  parser::yydefgoto_[] =
  {
      -1,     1,     2,     6,     7,    15,    16,   189,   190,   191,
     192,   193,   194,   242,   280,   281,   195,     8,     9,    84,
      85,    86,    87,    88,    89,    38,    39,    40,    22,    41,
     169,    76,   259,    77,   350,    43,    44,    45,    46,    47,
      48,    49,    50,    51,    52,    92,    53,    54,    55,    56,
      57,    58,    59,    60,    61,   107,    62,   110,    63,   115,
      64,   118,    65,    66,    67,    68,   351,   360,   170,   333,
     229,   310,   311,   171,   172,   173,   174,   175,   176,   177,
     178,   277,   278,   179,   180,   163,   164,   303,   304,   305,
      93,   129,   139,   273,   140,   141,    73,   243,   130,   211,
     274,    94,   244
  };

  const short
  parser::yytable_[] =
  {
      11,    12,   235,   123,    90,    71,   276,   266,   316,   210,
     103,   300,    97,   152,    10,    23,    10,    10,    23,    10,
     188,   153,   287,   188,    23,   287,    10,    10,   355,    10,
     327,   155,   156,   165,     4,     5,   165,     3,   328,   355,
      10,   247,    10,   128,   323,   165,   165,   287,   165,   138,
     138,   138,   276,   201,   132,   237,   201,   181,   237,   165,
     322,    27,    28,   338,   137,   201,   201,   296,   201,   245,
     354,    32,   290,   364,   239,    33,    10,   239,   269,   201,
      13,   157,    10,   275,   363,    32,    23,   334,   232,    33,
      17,   131,    23,   197,   233,   165,   199,   200,   167,    14,
     339,   165,    32,   357,   232,   198,    33,   344,   138,    19,
     299,    23,   235,   125,   126,   201,   331,    24,   196,   125,
     126,   201,    18,   220,   167,   293,   307,   167,   276,    25,
     358,   359,   308,   127,   167,   235,   135,    70,   237,    97,
     136,    27,    28,    29,    30,    31,   237,   307,   268,   237,
     232,    32,   238,   329,    72,    33,   346,   239,   240,   241,
      69,   197,   167,   284,   230,   239,    42,    95,   239,   240,
     285,   100,   237,    97,   301,   128,   101,   119,   102,    96,
      75,    91,   121,    23,    10,   204,   196,   252,   188,   205,
     225,   239,   122,   167,   226,   167,   167,   167,   230,   253,
     262,   264,   294,   254,   263,   265,   295,   341,   272,    20,
      21,   342,   111,   112,   113,   114,   104,   105,   106,    98,
      99,   108,   109,   167,   138,   116,   117,   167,   167,   144,
     145,    96,    10,   271,   167,   120,   282,    23,    10,   197,
     151,   124,   133,   167,   134,   146,   309,   147,    23,   162,
     272,   336,   -49,   142,   143,   148,   154,   213,   167,   218,
     167,   231,   214,   203,   196,   215,   206,   302,   167,   216,
     345,   197,   197,   212,   219,   271,   222,   234,   272,   315,
     167,   208,   236,   209,   270,   318,   168,   248,   289,   279,
     283,   314,   313,   317,   197,   217,   196,   196,   309,   320,
     324,   228,   356,   271,   343,   167,   348,   223,   224,   282,
     167,   302,   202,   335,    75,   202,   337,   349,   353,   196,
     167,   362,   202,   286,   330,   361,   183,   185,   150,   292,
     158,   302,   246,   182,   249,   250,   228,   167,   184,   186,
     251,   340,   187,   261,   167,   260,   167,   267,   221,   167,
     168,   325,   227,     0,   312,     0,   167,   167,     0,     0,
       0,   255,   256,   257,   258,     0,     0,     0,     0,     0,
      23,    10,     0,   162,     0,     0,    24,     0,     0,     0,
       0,   202,   291,   202,   202,   202,     0,     0,    25,     0,
     165,     0,     0,   288,     0,    26,     0,   297,     0,   298,
      27,    28,    29,    30,    31,     0,     0,   306,     0,     0,
     166,   202,     0,     0,    33,   168,   168,    34,     0,     0,
      35,    36,   202,     0,     0,     0,     0,     0,     0,    37,
       0,   202,     0,     0,     0,     0,     0,     0,   319,     0,
       0,     0,   321,     0,   326,     0,   202,     0,   202,   332,
       0,     0,     0,     0,     0,     0,   202,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   202,     0,
       0,     0,    23,    10,     0,     0,   347,     0,    24,     0,
       0,     0,     0,   352,     0,   352,     0,     0,   352,     0,
      25,     0,     0,   202,     0,     0,   352,    26,   202,   159,
     160,     0,    27,    28,    29,    30,    31,     0,   168,     0,
       0,     0,    32,   161,     0,     0,    33,     0,     0,    34,
       0,     0,    35,    36,     0,   202,     0,     0,     0,     0,
       0,    37,   202,     0,   202,    23,    10,   202,     0,     0,
       0,    24,     0,     0,   202,   202,     0,     0,     0,    78,
      79,    80,    81,    25,     0,     0,     0,     0,     0,     0,
      26,     0,     0,     0,    82,    27,    28,    29,    30,    31,
       0,     0,     0,     0,     0,    32,     0,     0,     0,    33,
      83,     0,    34,    23,    10,    35,    36,     0,     0,    24,
       0,     0,     0,     0,    37,     0,     0,    78,    79,    80,
      81,    25,     0,     0,     0,     0,     0,     0,    26,     0,
       0,     0,    82,    27,    28,    29,    30,    31,    23,    10,
       0,     0,     0,    32,    24,     0,     0,    33,   149,     0,
      34,     0,     0,    35,    36,     0,    25,     0,   165,     0,
       0,     0,    37,    26,     0,     0,     0,     0,    27,    28,
      29,    30,    31,     0,    23,    10,     0,     0,   166,    74,
      24,     0,    33,     0,     0,    34,     0,     0,    35,    36,
       0,     0,    25,     0,     0,     0,     0,    37,     0,    26,
       0,   159,   160,     0,    27,    28,    29,    30,    31,    23,
      10,     0,     0,     0,    32,    24,     0,     0,    33,     0,
       0,    34,     0,     0,    35,    36,     0,    25,     0,     0,
       0,     0,     0,    37,    26,     0,     0,     0,     0,    27,
      28,    29,    30,    31,     0,    23,    10,     0,     0,    32,
      74,    24,     0,    33,     0,     0,    34,     0,     0,    35,
      36,     0,     0,    25,     0,     0,     0,     0,    37,     0,
      26,     0,     0,     0,     0,    27,    28,    29,    30,    31,
       0,    23,    10,     0,     0,    32,   207,    24,     0,    33,
       0,     0,    34,     0,     0,    35,    36,     0,     0,    25,
       0,     0,     0,     0,    37,     0,    26,     0,     0,     0,
       0,    27,    28,    29,    30,    31,     0,     0,     0,     0,
       0,    32,     0,     0,     0,    33,     0,     0,    34,     0,
       0,    35,    36,     0,     0,     0,     0,     0,     0,     0,
      37
  };

  const short
  parser::yycheck_[] =
  {
       4,     5,   190,    70,    33,    24,   238,   231,   284,   137,
      60,   268,    41,    40,     4,     3,     4,     4,     3,     4,
       8,    48,   244,     8,     3,   247,     4,     4,   350,     4,
      40,     3,     4,    23,    14,    15,    23,     0,    48,   361,
       4,   197,     4,    72,   301,    23,    23,   269,    23,    78,
      79,    80,   284,    43,    73,    45,    43,   107,    45,    23,
      48,    33,    34,    48,    43,    43,    43,    44,    43,    59,
      48,    43,    59,    48,    64,    47,     4,    64,   234,    43,
      41,   100,     4,    47,   360,    43,     3,   315,    40,    47,
      16,    49,     3,   122,    46,    23,   125,   126,   102,    67,
     324,    23,    43,    42,    40,   124,    47,   335,   137,     7,
      46,     3,   300,    30,    31,    43,    44,     9,   122,    30,
      31,    43,    16,   152,   128,   253,    40,   131,   360,    21,
      69,    70,    46,    44,   138,   323,    40,    24,    45,   168,
      44,    33,    34,    35,    36,    37,    45,    40,    47,    45,
      40,    43,    59,    46,    43,    47,    46,    64,    65,    66,
       4,   190,   166,    59,   168,    64,    18,    39,    64,    65,
      66,    38,    45,   202,    47,   204,    43,    25,    45,     3,
      32,    33,    27,     3,     4,    40,   190,   206,     8,    44,
      40,    64,    67,   197,    44,   199,   200,   201,   202,    40,
      40,    40,    40,    44,    44,    44,    44,    40,   237,    36,
      37,    44,    55,    56,    57,    58,    50,    51,    52,    36,
      37,    53,    54,   227,   253,    60,    61,   231,   232,    81,
      82,     3,     4,   237,   238,    26,   240,     3,     4,   268,
      92,    10,    40,   247,    44,    41,   275,    59,     3,   101,
     279,   318,    39,    79,    80,    48,    39,    59,   262,    41,
     264,    45,    59,   128,   268,    59,   131,   271,   272,    59,
     337,   300,   301,   138,    48,   279,    43,     4,   307,   283,
     284,   133,    41,   135,    41,   289,   102,    11,    16,    45,
      55,    43,    65,    55,   323,   147,   300,   301,   327,    16,
      45,   166,    41,   307,    57,   309,    47,   159,   160,   313,
     314,   315,   128,   317,   166,   131,   320,    57,    47,   323,
     324,    41,   138,   244,   313,   353,   115,   119,    92,   248,
     100,   335,   197,   110,   199,   200,   201,   341,   118,   120,
     204,   327,   121,   227,   348,   225,   350,   232,   152,   353,
     166,   307,   165,    -1,   279,    -1,   360,   361,    -1,    -1,
      -1,   213,   214,   215,   216,    -1,    -1,    -1,    -1,    -1,
       3,     4,    -1,   225,    -1,    -1,     9,    -1,    -1,    -1,
      -1,   197,   247,   199,   200,   201,    -1,    -1,    21,    -1,
      23,    -1,    -1,   245,    -1,    28,    -1,   262,    -1,   264,
      33,    34,    35,    36,    37,    -1,    -1,   272,    -1,    -1,
      43,   227,    -1,    -1,    47,   231,   232,    50,    -1,    -1,
      53,    54,   238,    -1,    -1,    -1,    -1,    -1,    -1,    62,
      -1,   247,    -1,    -1,    -1,    -1,    -1,    -1,   290,    -1,
      -1,    -1,   294,    -1,   309,    -1,   262,    -1,   264,   314,
      -1,    -1,    -1,    -1,    -1,    -1,   272,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   284,    -1,
      -1,    -1,     3,     4,    -1,    -1,   341,    -1,     9,    -1,
      -1,    -1,    -1,   348,    -1,   350,    -1,    -1,   353,    -1,
      21,    -1,    -1,   309,    -1,    -1,   361,    28,   314,    30,
      31,    -1,    33,    34,    35,    36,    37,    -1,   324,    -1,
      -1,    -1,    43,    44,    -1,    -1,    47,    -1,    -1,    50,
      -1,    -1,    53,    54,    -1,   341,    -1,    -1,    -1,    -1,
      -1,    62,   348,    -1,   350,     3,     4,   353,    -1,    -1,
      -1,     9,    -1,    -1,   360,   361,    -1,    -1,    -1,    17,
      18,    19,    20,    21,    -1,    -1,    -1,    -1,    -1,    -1,
      28,    -1,    -1,    -1,    32,    33,    34,    35,    36,    37,
      -1,    -1,    -1,    -1,    -1,    43,    -1,    -1,    -1,    47,
      48,    -1,    50,     3,     4,    53,    54,    -1,    -1,     9,
      -1,    -1,    -1,    -1,    62,    -1,    -1,    17,    18,    19,
      20,    21,    -1,    -1,    -1,    -1,    -1,    -1,    28,    -1,
      -1,    -1,    32,    33,    34,    35,    36,    37,     3,     4,
      -1,    -1,    -1,    43,     9,    -1,    -1,    47,    48,    -1,
      50,    -1,    -1,    53,    54,    -1,    21,    -1,    23,    -1,
      -1,    -1,    62,    28,    -1,    -1,    -1,    -1,    33,    34,
      35,    36,    37,    -1,     3,     4,    -1,    -1,    43,    44,
       9,    -1,    47,    -1,    -1,    50,    -1,    -1,    53,    54,
      -1,    -1,    21,    -1,    -1,    -1,    -1,    62,    -1,    28,
      -1,    30,    31,    -1,    33,    34,    35,    36,    37,     3,
       4,    -1,    -1,    -1,    43,     9,    -1,    -1,    47,    -1,
      -1,    50,    -1,    -1,    53,    54,    -1,    21,    -1,    -1,
      -1,    -1,    -1,    62,    28,    -1,    -1,    -1,    -1,    33,
      34,    35,    36,    37,    -1,     3,     4,    -1,    -1,    43,
      44,     9,    -1,    47,    -1,    -1,    50,    -1,    -1,    53,
      54,    -1,    -1,    21,    -1,    -1,    -1,    -1,    62,    -1,
      28,    -1,    -1,    -1,    -1,    33,    34,    35,    36,    37,
      -1,     3,     4,    -1,    -1,    43,    44,     9,    -1,    47,
      -1,    -1,    50,    -1,    -1,    53,    54,    -1,    -1,    21,
      -1,    -1,    -1,    -1,    62,    -1,    28,    -1,    -1,    -1,
      -1,    33,    34,    35,    36,    37,    -1,    -1,    -1,    -1,
      -1,    43,    -1,    -1,    -1,    47,    -1,    -1,    50,    -1,
      -1,    53,    54,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      62
  };

  const unsigned char
  parser::yystos_[] =
  {
       0,    73,    74,     0,    14,    15,    75,    76,    89,    90,
       4,    97,    97,    41,    67,    77,    78,    16,    16,     7,
      36,    37,   100,     3,     9,    21,    28,    33,    34,    35,
      36,    37,    43,    47,    50,    53,    54,    62,    97,    98,
      99,   101,   102,   107,   108,   109,   110,   111,   112,   113,
     114,   115,   116,   118,   119,   120,   121,   122,   123,   124,
     125,   126,   128,   130,   132,   134,   135,   136,   137,     4,
      24,   107,    43,   168,    44,   102,   103,   105,    17,    18,
      19,    20,    32,    48,    91,    92,    93,    94,    95,    96,
      98,   102,   117,   162,   173,    39,     3,    98,    36,    37,
      38,    43,    45,   124,    50,    51,    52,   127,    53,    54,
     129,    55,    56,    57,    58,   131,    60,    61,   133,    25,
      26,    27,    67,   100,    10,    30,    31,    44,    98,   163,
     170,    49,   107,    40,    44,    40,    44,    43,    98,   164,
     166,   167,   167,   167,   102,   102,    41,    59,    48,    48,
      91,   102,    40,    48,    39,     3,     4,   107,   113,    30,
      31,    44,   102,   157,   158,    23,    43,    97,   101,   102,
     140,   145,   146,   147,   148,   149,   150,   151,   152,   155,
     156,   124,   128,   130,   132,   134,   135,   136,     8,    79,
      80,    81,    82,    83,    84,    88,    97,    98,   107,    98,
      98,    43,   101,   140,    40,    44,   140,    44,   102,   102,
     164,   171,   140,    59,    59,    59,    59,   102,    41,    48,
      98,   162,    43,   102,   102,    40,    44,   168,   140,   142,
      97,    45,    40,    46,     4,    81,    41,    45,    59,    64,
      65,    66,    85,   169,   174,    59,   140,   174,    11,   140,
     140,   163,   107,    40,    44,   102,   102,   102,   102,   104,
     157,   145,    40,    44,    40,    44,   156,   155,    47,   174,
      41,    97,    98,   165,   172,    47,   152,   153,   154,    45,
      86,    87,    97,    55,    59,    66,    85,   169,   102,    16,
      59,   140,   112,   164,    40,    44,    44,   140,   140,    46,
      80,    47,    97,   159,   160,   161,   140,    40,    46,    98,
     143,   144,   172,    65,    43,    97,   153,    55,    97,   102,
      16,   102,    48,    80,    45,   165,   140,    40,    48,    46,
      87,    44,   140,   141,   159,    97,   100,    97,    48,   156,
     143,    40,    44,    57,   159,   100,    46,   140,    47,    57,
     106,   138,   140,    47,    48,   138,    41,    42,    69,    70,
     139,   106,    41,   153,    48
  };

  const unsigned char
  parser::yyr1_[] =
  {
       0,    72,    73,    74,    74,    75,    75,    76,    76,    77,
      78,    79,    79,    80,    80,    81,    81,    81,    81,    81,
      82,    82,    82,    82,    83,    83,    84,    84,    85,    86,
      86,    87,    87,    87,    88,    88,    89,    90,    91,    91,
      91,    91,    91,    92,    93,    94,    95,    96,    97,    98,
      99,   100,   100,   101,   101,   102,   103,   104,   104,   105,
     105,   106,   106,   107,   107,   107,   107,   107,   108,   108,
     109,   110,   110,   111,   112,   112,   112,   112,   112,   112,
     112,   113,   113,   114,   114,   114,   114,   115,   115,   116,
     116,   116,   117,   117,   118,   118,   119,   119,   119,   119,
     119,   120,   121,   121,   122,   122,   122,   123,   123,   124,
     124,   125,   125,   125,   125,   125,   126,   127,   127,   127,
     128,   128,   129,   129,   130,   130,   131,   131,   131,   131,
     132,   132,   133,   133,   134,   134,   135,   135,   136,   136,
     137,   137,   138,   139,   139,   139,   140,   141,   141,   142,
     142,   143,   144,   144,   145,   145,   145,   145,   145,   146,
     147,   147,   148,   149,   150,   150,   151,   152,   153,   153,
     154,   155,   155,   156,   156,   157,   157,   157,   158,   158,
     159,   160,   161,   161,   162,   163,   163,   163,   164,   164,
     165,   165,   166,   167,   167,   168,   168,   169,   169,   170,
     170,   171,   171,   172,   172,   173,   173,   174,   174
  };

  const signed char
  parser::yyr2_[] =
  {
       0,     2,     2,     0,     3,     1,     1,     0,     2,     1,
       5,     5,     6,     2,     3,     1,     1,     1,     1,     1,
       3,     4,     5,     6,     3,     4,     2,     3,     2,     1,
       3,     1,     3,     4,     9,    10,     6,     4,     1,     1,
       1,     1,     1,     4,     4,     4,     4,     2,     1,     1,
       1,     1,     1,     2,     3,     1,     1,     0,     3,     3,
       3,     2,     3,     1,     1,     1,     1,     1,     2,     2,
       3,     4,     3,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     2,     2,     4,     6,     3,
       3,     4,     2,     3,     3,     5,     1,     1,     1,     1,
       1,     4,     3,     4,     3,     6,     2,     3,     3,     1,
       2,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     3,     1,     1,     1,     3,     1,     1,     1,     1,
       1,     3,     1,     1,     1,     3,     1,     3,     1,     3,
       1,     3,     3,     1,     1,     1,     1,     1,     3,     3,
       3,     2,     1,     3,     1,     1,     1,     1,     1,     3,
       4,     3,     2,     3,     1,     1,     4,     1,     1,     1,
       3,     1,     1,     1,     3,     1,     2,     2,     1,     3,
       1,     1,     1,     4,     3,     2,     3,     3,     2,     1,
       2,     2,     3,     1,     1,     3,     2,     3,     4,     1,
       3,     1,     3,     1,     3,     1,     3,     1,     2
  };


#if YYDEBUG
  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a YYNTOKENS, nonterminals.
  const char*
  const parser::yytname_[] =
  {
  "\"end of file\"", "error", "\"invalid token\"", "\"<val_id>\"",
  "\"<TypeId>\"", "\"<__42__>\"", "\"using\"", "\"module\"", "\"sub\"",
  "\"if\"", "\"then\"", "\"else\"", "\"match\"", "\"with\"", "\"import\"",
  "\"extern\"", "\"from\"", "\"const\"", "\"val\"", "\"var\"", "\"set\"",
  "\"fn\"", "\"lambda\"", "\"Fn\"", "\"type\"", "\"and\"", "\"xor\"",
  "\"or\"", "\"not\"", "\"typeclass\"", "\"out\"", "\"inout\"",
  "\"discard\"", "\"42\"", "\"0x2a\"", "\"4.2\"",
  "\"\\\"dq-string-literal\\\"\"", "\"'sq-string-literal'\"", "\".\"",
  "\":\"", "\",\"", "\";\"", "\"::\"", "\"(\"", "\")\"", "\"[\"", "\"]\"",
  "\"{\"", "\"}\"", "\"->\"", "\"*\"", "\"/\"", "\"%\"", "\"+\"", "\"-\"",
  "\"<\"", "\"<=\"", "\">\"", "\">=\"", "\"=\"", "\"==\"", "\"!=\"",
  "\"^\"", "\"&\"", "\"!\"", "\"|\"", "\":-\"", "\"---\"", "\"EOS\"",
  "\":<\"", "\">:\"", "\"<null>\"", "$accept", "script", "script_head",
  "script_head_stmt", "script_body", "script_body_stmt", "top_mod_stmt",
  "sub_mod_stmt", "mod_content", "mod_content_stmt", "mod_val_stmt",
  "mod_type_stmt", "mod_enum_stmt", "enum_field_pl",
  "unprefixed_enum_field_pl", "enum_field", "mod_typeclass_stmt",
  "import_stmt", "extern_stmt", "chain_prefix_stmt", "const_stmt",
  "val_stmt", "var_stmt", "set_stmt", "discard_stmt", "tid", "vid",
  "floatl", "stringl", "mod_prefix", "expr", "long_exp", "expr_cl0",
  "expr_cl2", "type_query_exp_sl", "bracketed_exp", "unit_exp",
  "paren_exp", "vtupleExpr", "vstructExpr", "primary_exp", "int_expr",
  "stringls", "if_exp", "chain_exp", "chain_prefix", "lambda_exp",
  "postfix_exp", "tcall_exp", "vcall_exp", "dot_name_exp", "dot_index_exp",
  "unary_exp", "unary_op", "binary_exp", "mul_binary_op", "mul_binary_exp",
  "add_binary_op", "add_binary_exp", "cmp_binary_op", "cmp_binary_exp",
  "eq_binary_op", "eq_binary_exp", "and_binary_exp", "xor_binary_exp",
  "or_binary_exp", "type_query_exp", "type_query_op", "type_spec",
  "type_spec_cl1", "type_spec_cl2", "struct_type_spec_field",
  "struct_type_spec_field_cl", "primary_type_spec", "paren_type_spec",
  "tuple_type_spec", "mod_prefix_tid", "fn_type_spec", "postfix_type_spec",
  "tcall_type_spec", "unary_type_spec", "long_type_spec",
  "struct_type_spec", "targ", "targ_cl", "varg", "varg_cl", "class_spec",
  "primary_class_spec", "postfix_class_spec", "struct_exp_field",
  "vpattern_field", "lpattern_field", "tpattern_field",
  "destructured_lpattern", "lpattern", "vpattern", "tpattern",
  "vpattern_field_cl", "lpattern_field_cl", "tpattern_field_cl",
  "struct_exp_field_cl", "tpattern_seq", YY_NULLPTR
  };
#endif


#if YYDEBUG
  const short
  parser::yyrline_[] =
  {
       0,   288,   288,   296,   297,   300,   301,   305,   306,   309,
     317,   320,   321,   324,   325,   333,   334,   335,   336,   337,
     340,   341,   342,   343,   346,   347,   350,   351,   354,   357,
     358,   361,   362,   363,   366,   369,   375,   378,   382,   383,
     384,   385,   386,   389,   392,   395,   398,   401,   408,   409,
     411,   414,   415,   418,   419,   426,   429,   433,   434,   437,
     438,   441,   442,   446,   447,   448,   449,   450,   453,   454,
     457,   460,   461,   464,   467,   468,   469,   470,   471,   472,
     473,   476,   477,   480,   481,   482,   483,   486,   487,   490,
     491,   492,   495,   496,   499,   500,   504,   505,   506,   507,
     508,   511,   514,   515,   518,   519,   520,   523,   524,   528,
     529,   532,   533,   534,   535,   536,   540,   543,   544,   545,
     548,   549,   552,   553,   556,   557,   560,   561,   562,   563,
     566,   567,   570,   571,   574,   575,   578,   579,   582,   583,
     586,   587,   591,   594,   595,   596,   604,   607,   608,   611,
     612,   616,   619,   620,   624,   625,   626,   627,   628,   631,
     634,   635,   638,   641,   645,   646,   649,   653,   657,   658,
     661,   664,   665,   668,   669,   671,   672,   673,   676,   677,
     687,   690,   693,   694,   702,   705,   706,   707,   710,   711,
     714,   715,   719,   723,   724,   727,   728,   731,   732,   736,
     737,   740,   741,   744,   745,   748,   749,   753,   754
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
      65,    66,    67,    68,    69,    70,    71
    };
    // Last valid token kind.
    const int code_max = 326;

    if (t <= 0)
      return symbol_kind::S_YYEOF;
    else if (t <= code_max)
      return YY_CAST (symbol_kind_type, translate_table[t]);
    else
      return symbol_kind::S_YYUNDEF;
  }

#line 19 "parser.yy"
} } // pdm::parser
#line 4226 "parser.tab.cc"

#line 757 "parser.yy"


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
