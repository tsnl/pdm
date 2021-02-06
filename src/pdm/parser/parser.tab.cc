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
      case symbol_kind::S_UNSIGNED_DINT_LIT: // "42u"
      case symbol_kind::S_UNSIGNED_XINT_LIT: // "0x2Au"
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
      case symbol_kind::S_UNSIGNED_DINT_LIT: // "42u"
      case symbol_kind::S_UNSIGNED_XINT_LIT: // "0x2Au"
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
      case symbol_kind::S_UNSIGNED_DINT_LIT: // "42u"
      case symbol_kind::S_UNSIGNED_XINT_LIT: // "0x2Au"
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
      case symbol_kind::S_UNSIGNED_DINT_LIT: // "42u"
      case symbol_kind::S_UNSIGNED_XINT_LIT: // "0x2Au"
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
      case symbol_kind::S_UNSIGNED_DINT_LIT: // "42u"
      case symbol_kind::S_UNSIGNED_XINT_LIT: // "0x2Au"
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
      case symbol_kind::S_UNSIGNED_DINT_LIT: // "42u"
      case symbol_kind::S_UNSIGNED_XINT_LIT: // "0x2Au"
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
      case symbol_kind::S_UNSIGNED_DINT_LIT: // "42u"
      case symbol_kind::S_UNSIGNED_XINT_LIT: // "0x2Au"
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
#line 289 "parser.yy"
                                { 
    yylhs.value.as < pdm::ast::Script* > () = mgr->new_script(source, yylhs.location, std::move(yystack_[1].value.as < std::vector<pdm::ast::Stmt*> > ()), std::move(yystack_[0].value.as < std::vector<pdm::ast::ModStmt*> > ())); 

    // setting the returnp here => this is the node parser returns.  
    *returnp = yylhs.value.as < pdm::ast::Script* > (); 
}
#line 2258 "parser.tab.cc"
    break;

  case 3: // script_head: %empty
#line 297 "parser.yy"
                                                { yylhs.value.as < std::vector<pdm::ast::Stmt*> > ().reserve(16); }
#line 2264 "parser.tab.cc"
    break;

  case 4: // script_head: script_head script_head_stmt ";"
#line 298 "parser.yy"
                                                { yylhs.value.as < std::vector<pdm::ast::Stmt*> > () = std::move(yystack_[2].value.as < std::vector<pdm::ast::Stmt*> > ()); yylhs.value.as < std::vector<pdm::ast::Stmt*> > ().push_back(yystack_[1].value.as < pdm::ast::Stmt* > ()); }
#line 2270 "parser.tab.cc"
    break;

  case 5: // script_head_stmt: import_stmt
#line 301 "parser.yy"
      { yylhs.value.as < pdm::ast::Stmt* > () = yystack_[0].value.as < pdm::ast::Stmt* > (); }
#line 2276 "parser.tab.cc"
    break;

  case 6: // script_head_stmt: extern_stmt
#line 302 "parser.yy"
      { yylhs.value.as < pdm::ast::Stmt* > () = yystack_[0].value.as < pdm::ast::Stmt* > (); }
#line 2282 "parser.tab.cc"
    break;

  case 7: // script_body: %empty
#line 306 "parser.yy"
                                              { yylhs.value.as < std::vector<pdm::ast::ModStmt*> > ().reserve(16); }
#line 2288 "parser.tab.cc"
    break;

  case 8: // script_body: script_body script_body_stmt ";"
#line 307 "parser.yy"
                                              { yylhs.value.as < std::vector<pdm::ast::ModStmt*> > () = std::move(yystack_[2].value.as < std::vector<pdm::ast::ModStmt*> > ()); yylhs.value.as < std::vector<pdm::ast::ModStmt*> > ().push_back(yystack_[1].value.as < pdm::ast::ModStmt* > ()); }
#line 2294 "parser.tab.cc"
    break;

  case 9: // script_body_stmt: top_mod_stmt
#line 310 "parser.yy"
      { yylhs.value.as < pdm::ast::ModStmt* > () = yystack_[0].value.as < pdm::ast::ModStmt* > (); }
#line 2300 "parser.tab.cc"
    break;

  case 10: // top_mod_stmt: "module" "<TypeId>" "{" mod_content "}"
#line 318 "parser.yy"
                                              { yylhs.value.as < pdm::ast::ModStmt* > () = mgr->new_mod_stmt(yylhs.location, yystack_[3].value.as < TokenInfo > ().ID_intstr, std::move(std::vector<ast::TPattern*>{}), std::move(yystack_[1].value.as < std::vector<pdm::ast::ModContentStmt*> > ())); }
#line 2306 "parser.tab.cc"
    break;

  case 11: // sub_mod_stmt: "sub" "<TypeId>" "{" mod_content "}"
#line 321 "parser.yy"
                                                           { yylhs.value.as < pdm::ast::ModContentStmt* > () = mgr->new_mod_stmt(yylhs.location, yystack_[3].value.as < TokenInfo > ().ID_intstr, std::move(std::vector<ast::TPattern*>{}), std::move(yystack_[1].value.as < std::vector<pdm::ast::ModContentStmt*> > ())); }
#line 2312 "parser.tab.cc"
    break;

  case 12: // sub_mod_stmt: "sub" "<TypeId>" tpattern_seq "{" mod_content "}"
#line 322 "parser.yy"
                                                           { yylhs.value.as < pdm::ast::ModContentStmt* > () = mgr->new_mod_stmt(yylhs.location, yystack_[4].value.as < TokenInfo > ().ID_intstr, std::move(yystack_[3].value.as < std::vector<pdm::ast::TPattern*> > ()), std::move(yystack_[1].value.as < std::vector<pdm::ast::ModContentStmt*> > ())); }
#line 2318 "parser.tab.cc"
    break;

  case 13: // mod_content: mod_content_stmt ";"
#line 325 "parser.yy"
                                                { yylhs.value.as < std::vector<pdm::ast::ModContentStmt*> > ().push_back(yystack_[1].value.as < pdm::ast::ModContentStmt* > ()); }
#line 2324 "parser.tab.cc"
    break;

  case 14: // mod_content: mod_content mod_content_stmt ";"
#line 326 "parser.yy"
                                                { yylhs.value.as < std::vector<pdm::ast::ModContentStmt*> > () = std::move(yystack_[2].value.as < std::vector<pdm::ast::ModContentStmt*> > ()); yylhs.value.as < std::vector<pdm::ast::ModContentStmt*> > ().push_back(yystack_[1].value.as < pdm::ast::ModContentStmt* > ()); }
#line 2330 "parser.tab.cc"
    break;

  case 15: // mod_content_stmt: mod_val_stmt
#line 334 "parser.yy"
      { yylhs.value.as < pdm::ast::ModContentStmt* > () = yystack_[0].value.as < pdm::ast::ModContentStmt* > (); }
#line 2336 "parser.tab.cc"
    break;

  case 16: // mod_content_stmt: mod_type_stmt
#line 335 "parser.yy"
      { yylhs.value.as < pdm::ast::ModContentStmt* > () = yystack_[0].value.as < pdm::ast::ModContentStmt* > (); }
#line 2342 "parser.tab.cc"
    break;

  case 17: // mod_content_stmt: mod_enum_stmt
#line 336 "parser.yy"
      { yylhs.value.as < pdm::ast::ModContentStmt* > () = yystack_[0].value.as < pdm::ast::ModContentStmt* > (); }
#line 2348 "parser.tab.cc"
    break;

  case 18: // mod_content_stmt: mod_typeclass_stmt
#line 337 "parser.yy"
      { yylhs.value.as < pdm::ast::ModContentStmt* > () = yystack_[0].value.as < pdm::ast::ModContentStmt* > (); }
#line 2354 "parser.tab.cc"
    break;

  case 19: // mod_content_stmt: sub_mod_stmt
#line 338 "parser.yy"
      { yylhs.value.as < pdm::ast::ModContentStmt* > () = yystack_[0].value.as < pdm::ast::ModContentStmt* > (); }
#line 2360 "parser.tab.cc"
    break;

  case 20: // mod_val_stmt: vid "=" expr
#line 341 "parser.yy"
                                    { yylhs.value.as < pdm::ast::ModContentStmt* > () = mgr->new_internal_mod_val_stmt(yylhs.location, yystack_[2].value.as < TokenInfo > ().ID_intstr, std::move(std::vector<ast::TPattern*>{}), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2366 "parser.tab.cc"
    break;

  case 21: // mod_val_stmt: vid tpattern_seq "=" expr
#line 342 "parser.yy"
                                    { yylhs.value.as < pdm::ast::ModContentStmt* > () = mgr->new_internal_mod_val_stmt(yylhs.location, yystack_[3].value.as < TokenInfo > ().ID_intstr, std::move(yystack_[2].value.as < std::vector<pdm::ast::TPattern*> > ()), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2372 "parser.tab.cc"
    break;

  case 22: // mod_val_stmt: vid type_spec "from" tid stringl
#line 343 "parser.yy"
                                                      { yylhs.value.as < pdm::ast::ModContentStmt* > () = mgr->new_external_mod_val_stmt(yylhs.location, yystack_[4].value.as < TokenInfo > ().ID_intstr, std::move(std::vector<ast::TPattern*>{}), yystack_[3].value.as < pdm::ast::TypeSpec* > (), yystack_[1].value.as < TokenInfo > ().ID_intstr, *yystack_[0].value.as < TokenInfo > ().String_utf8string); }
#line 2378 "parser.tab.cc"
    break;

  case 23: // mod_val_stmt: vid tpattern_seq type_spec "from" tid stringl
#line 344 "parser.yy"
                                                      { yylhs.value.as < pdm::ast::ModContentStmt* > () = mgr->new_external_mod_val_stmt(yylhs.location, yystack_[5].value.as < TokenInfo > ().ID_intstr, std::move(yystack_[4].value.as < std::vector<pdm::ast::TPattern*> > ()), yystack_[3].value.as < pdm::ast::TypeSpec* > (), yystack_[1].value.as < TokenInfo > ().ID_intstr, *yystack_[0].value.as < TokenInfo > ().String_utf8string); }
#line 2384 "parser.tab.cc"
    break;

  case 24: // mod_type_stmt: tid "=" long_type_spec
#line 347 "parser.yy"
                                             { yylhs.value.as < pdm::ast::ModContentStmt* > () = mgr->new_mod_type_stmt(yylhs.location, yystack_[2].value.as < TokenInfo > ().ID_intstr, std::move(std::vector<ast::TPattern*>{}), yystack_[0].value.as < pdm::ast::TypeSpec* > ()); }
#line 2390 "parser.tab.cc"
    break;

  case 25: // mod_type_stmt: tid tpattern_seq "=" long_type_spec
#line 348 "parser.yy"
                                             { yylhs.value.as < pdm::ast::ModContentStmt* > () = mgr->new_mod_type_stmt(yylhs.location, yystack_[3].value.as < TokenInfo > ().ID_intstr, std::move(yystack_[2].value.as < std::vector<pdm::ast::TPattern*> > ()), yystack_[0].value.as < pdm::ast::TypeSpec* > ()); }
#line 2396 "parser.tab.cc"
    break;

  case 26: // mod_enum_stmt: tid enum_field_pl
#line 351 "parser.yy"
                                        { yylhs.value.as < pdm::ast::ModContentStmt* > () = mgr->new_mod_enum_stmt(yylhs.location, yystack_[1].value.as < TokenInfo > ().ID_intstr, std::move(std::vector<ast::TPattern*>{}), std::move(yystack_[0].value.as < std::vector<pdm::ast::ModEnumStmt::Field*> > ())); }
#line 2402 "parser.tab.cc"
    break;

  case 27: // mod_enum_stmt: tid tpattern_seq enum_field_pl
#line 352 "parser.yy"
                                        { yylhs.value.as < pdm::ast::ModContentStmt* > () = mgr->new_mod_enum_stmt(yylhs.location, yystack_[2].value.as < TokenInfo > ().ID_intstr, std::move(yystack_[1].value.as < std::vector<pdm::ast::TPattern*> > ()), std::move(yystack_[0].value.as < std::vector<pdm::ast::ModEnumStmt::Field*> > ())); }
#line 2408 "parser.tab.cc"
    break;

  case 28: // enum_field_pl: "|" unprefixed_enum_field_pl
#line 355 "parser.yy"
                                    { yylhs.value.as < std::vector<pdm::ast::ModEnumStmt::Field*> > () = std::move(yystack_[0].value.as < std::vector<pdm::ast::ModEnumStmt::Field*> > ()); }
#line 2414 "parser.tab.cc"
    break;

  case 29: // unprefixed_enum_field_pl: enum_field
#line 358 "parser.yy"
                                                { yylhs.value.as < std::vector<pdm::ast::ModEnumStmt::Field*> > ().push_back(yystack_[0].value.as < pdm::ast::ModEnumStmt::Field* > ()); }
#line 2420 "parser.tab.cc"
    break;

  case 30: // unprefixed_enum_field_pl: unprefixed_enum_field_pl "|" enum_field
#line 359 "parser.yy"
                                                { yylhs.value.as < std::vector<pdm::ast::ModEnumStmt::Field*> > () = std::move(yystack_[2].value.as < std::vector<pdm::ast::ModEnumStmt::Field*> > ()); yylhs.value.as < std::vector<pdm::ast::ModEnumStmt::Field*> > ().push_back(yystack_[0].value.as < pdm::ast::ModEnumStmt::Field* > ()); }
#line 2426 "parser.tab.cc"
    break;

  case 31: // enum_field: tid
#line 362 "parser.yy"
                                     { yylhs.value.as < pdm::ast::ModEnumStmt::Field* > () = mgr->new_enum_stmt_field(yylhs.location, yystack_[0].value.as < TokenInfo > ().ID_intstr, std::move(std::vector<ast::TypeSpec*>{}), false); }
#line 2432 "parser.tab.cc"
    break;

  case 32: // enum_field: tid "(" ")"
#line 363 "parser.yy"
                                     { yylhs.value.as < pdm::ast::ModEnumStmt::Field* > () = mgr->new_enum_stmt_field(yylhs.location, yystack_[2].value.as < TokenInfo > ().ID_intstr, std::move(std::vector<ast::TypeSpec*>{}), true); }
#line 2438 "parser.tab.cc"
    break;

  case 33: // enum_field: tid "(" type_spec_cl1 ")"
#line 364 "parser.yy"
                                      { yylhs.value.as < pdm::ast::ModEnumStmt::Field* > () = mgr->new_enum_stmt_field(yylhs.location, yystack_[3].value.as < TokenInfo > ().ID_intstr, std::move(yystack_[1].value.as < std::vector<pdm::ast::TypeSpec*> > ()), true); }
#line 2444 "parser.tab.cc"
    break;

  case 34: // mod_typeclass_stmt: tid ":-" "<" tid class_spec ">" "{" type_query_exp_sl "}"
#line 367 "parser.yy"
                                                                                             { 
        yylhs.value.as < pdm::ast::ModContentStmt* > () = mgr->new_mod_typeclass_stmt(yylhs.location, yystack_[8].value.as < TokenInfo > ().ID_intstr, yystack_[5].value.as < TokenInfo > ().ID_intstr, yystack_[4].value.as < pdm::ast::ClassSpec* > (), std::move(std::vector<ast::TPattern*>{}), std::move(yystack_[1].value.as < std::vector<pdm::ast::TypeQueryExp*> > ())); 
      }
#line 2452 "parser.tab.cc"
    break;

  case 35: // mod_typeclass_stmt: tid tpattern_seq ":-" "<" tid class_spec ">" "{" type_query_exp_sl "}"
#line 370 "parser.yy"
                                                                                             { 
        yylhs.value.as < pdm::ast::ModContentStmt* > () = mgr->new_mod_typeclass_stmt(yylhs.location, yystack_[9].value.as < TokenInfo > ().ID_intstr, yystack_[5].value.as < TokenInfo > ().ID_intstr, yystack_[4].value.as < pdm::ast::ClassSpec* > (), std::move(yystack_[8].value.as < std::vector<pdm::ast::TPattern*> > ()), std::move(yystack_[1].value.as < std::vector<pdm::ast::TypeQueryExp*> > ())); 
      }
#line 2460 "parser.tab.cc"
    break;

  case 36: // import_stmt: "import" tid "from" stringl "type" stringl
#line 376 "parser.yy"
                                                       { yylhs.value.as < pdm::ast::Stmt* > () = mgr->new_import_stmt(yylhs.location, yystack_[4].value.as < TokenInfo > ().ID_intstr, *yystack_[2].value.as < TokenInfo > ().String_utf8string, *yystack_[0].value.as < TokenInfo > ().String_utf8string); }
#line 2466 "parser.tab.cc"
    break;

  case 37: // extern_stmt: "extern" tid "from" expr
#line 379 "parser.yy"
                                    { yylhs.value.as < pdm::ast::Stmt* > () = mgr->new_extern_stmt(yylhs.location, yystack_[2].value.as < TokenInfo > ().ID_intstr, yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2472 "parser.tab.cc"
    break;

  case 38: // chain_prefix_stmt: const_stmt
#line 383 "parser.yy"
      { yylhs.value.as < pdm::ast::Stmt* > () = yystack_[0].value.as < pdm::ast::Stmt* > (); }
#line 2478 "parser.tab.cc"
    break;

  case 39: // chain_prefix_stmt: val_stmt
#line 384 "parser.yy"
      { yylhs.value.as < pdm::ast::Stmt* > () = yystack_[0].value.as < pdm::ast::Stmt* > (); }
#line 2484 "parser.tab.cc"
    break;

  case 40: // chain_prefix_stmt: var_stmt
#line 385 "parser.yy"
      { yylhs.value.as < pdm::ast::Stmt* > () = yystack_[0].value.as < pdm::ast::Stmt* > (); }
#line 2490 "parser.tab.cc"
    break;

  case 41: // chain_prefix_stmt: set_stmt
#line 386 "parser.yy"
      { yylhs.value.as < pdm::ast::Stmt* > () = yystack_[0].value.as < pdm::ast::Stmt* > (); }
#line 2496 "parser.tab.cc"
    break;

  case 42: // chain_prefix_stmt: discard_stmt
#line 387 "parser.yy"
      { yylhs.value.as < pdm::ast::Stmt* > () = yystack_[0].value.as < pdm::ast::Stmt* > (); }
#line 2502 "parser.tab.cc"
    break;

  case 43: // const_stmt: "const" lpattern "=" expr
#line 390 "parser.yy"
                                  { yylhs.value.as < pdm::ast::Stmt* > () = mgr->new_const_stmt(yylhs.location, yystack_[2].value.as < pdm::ast::LPattern* > (), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2508 "parser.tab.cc"
    break;

  case 44: // val_stmt: "val" lpattern "=" expr
#line 393 "parser.yy"
                                  { yylhs.value.as < pdm::ast::Stmt* > () = mgr->new_val_stmt(yylhs.location, yystack_[2].value.as < pdm::ast::LPattern* > (), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2514 "parser.tab.cc"
    break;

  case 45: // var_stmt: "var" lpattern "=" expr
#line 396 "parser.yy"
                                  { yylhs.value.as < pdm::ast::Stmt* > () = mgr->new_var_stmt(yylhs.location, yystack_[2].value.as < pdm::ast::LPattern* > (), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2520 "parser.tab.cc"
    break;

  case 46: // set_stmt: "set" expr "=" expr
#line 399 "parser.yy"
                              { yylhs.value.as < pdm::ast::Stmt* > () = mgr->new_set_stmt(yylhs.location, yystack_[2].value.as < pdm::ast::Exp* > (), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2526 "parser.tab.cc"
    break;

  case 47: // discard_stmt: "discard" expr
#line 402 "parser.yy"
                        { yylhs.value.as < pdm::ast::Stmt* > () = mgr->new_discard_stmt(yylhs.location, yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2532 "parser.tab.cc"
    break;

  case 48: // tid: "<TypeId>"
#line 409 "parser.yy"
     { yylhs.value.as < TokenInfo > () = yystack_[0].value.as < TokenInfo > (); }
#line 2538 "parser.tab.cc"
    break;

  case 49: // vid: "<val_id>"
#line 410 "parser.yy"
     { yylhs.value.as < TokenInfo > () = yystack_[0].value.as < TokenInfo > (); }
#line 2544 "parser.tab.cc"
    break;

  case 50: // floatl: "4.2"
#line 412 "parser.yy"
      { yylhs.value.as < TokenInfo > () = yystack_[0].value.as < TokenInfo > (); }
#line 2550 "parser.tab.cc"
    break;

  case 51: // stringl: "'sq-string-literal'"
#line 415 "parser.yy"
      { yylhs.value.as < TokenInfo > () = yystack_[0].value.as < TokenInfo > (); }
#line 2556 "parser.tab.cc"
    break;

  case 52: // stringl: "\"dq-string-literal\""
#line 416 "parser.yy"
      { yylhs.value.as < TokenInfo > () = yystack_[0].value.as < TokenInfo > (); }
#line 2562 "parser.tab.cc"
    break;

  case 53: // mod_prefix: tid ":"
#line 419 "parser.yy"
                              { yylhs.value.as < std::vector<pdm::intern::String> > ().push_back(yystack_[1].value.as < TokenInfo > ().ID_intstr); }
#line 2568 "parser.tab.cc"
    break;

  case 54: // mod_prefix: mod_prefix vid ":"
#line 420 "parser.yy"
                              { yylhs.value.as < std::vector<pdm::intern::String> > () = std::move(yystack_[2].value.as < std::vector<pdm::intern::String> > ()); }
#line 2574 "parser.tab.cc"
    break;

  case 55: // expr: binary_exp
#line 427 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2580 "parser.tab.cc"
    break;

  case 56: // long_exp: expr
#line 430 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2586 "parser.tab.cc"
    break;

  case 57: // expr_cl0: %empty
#line 434 "parser.yy"
                             {}
#line 2592 "parser.tab.cc"
    break;

  case 58: // expr_cl0: expr_cl0 "," expr
#line 435 "parser.yy"
                             { yylhs.value.as < std::vector<pdm::ast::Exp*> > () = std::move(yystack_[2].value.as < std::vector<pdm::ast::Exp*> > ()); yylhs.value.as < std::vector<pdm::ast::Exp*> > ().push_back(yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2598 "parser.tab.cc"
    break;

  case 59: // expr_cl2: expr "," expr
#line 438 "parser.yy"
                             { yylhs.value.as < std::vector<pdm::ast::Exp*> > ().reserve(2); yylhs.value.as < std::vector<pdm::ast::Exp*> > ().push_back(yystack_[2].value.as < pdm::ast::Exp* > ()); yylhs.value.as < std::vector<pdm::ast::Exp*> > ().push_back(yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2604 "parser.tab.cc"
    break;

  case 60: // expr_cl2: expr_cl2 "," expr
#line 439 "parser.yy"
                             { yylhs.value.as < std::vector<pdm::ast::Exp*> > () = std::move(yystack_[2].value.as < std::vector<pdm::ast::Exp*> > ()); yylhs.value.as < std::vector<pdm::ast::Exp*> > ().push_back(yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2610 "parser.tab.cc"
    break;

  case 61: // type_query_exp_sl: type_query_exp ";"
#line 442 "parser.yy"
                                       { yylhs.value.as < std::vector<pdm::ast::TypeQueryExp*> > ().push_back(yystack_[1].value.as < pdm::ast::TypeQueryExp* > ()); }
#line 2616 "parser.tab.cc"
    break;

  case 62: // type_query_exp_sl: type_query_exp_sl type_query_exp ";"
#line 443 "parser.yy"
                                                 { yylhs.value.as < std::vector<pdm::ast::TypeQueryExp*> > () = std::move(yystack_[2].value.as < std::vector<pdm::ast::TypeQueryExp*> > ()); yylhs.value.as < std::vector<pdm::ast::TypeQueryExp*> > ().push_back(yystack_[1].value.as < pdm::ast::TypeQueryExp* > ()); }
#line 2622 "parser.tab.cc"
    break;

  case 63: // bracketed_exp: unit_exp
#line 447 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2628 "parser.tab.cc"
    break;

  case 64: // bracketed_exp: paren_exp
#line 448 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2634 "parser.tab.cc"
    break;

  case 65: // bracketed_exp: vtupleExpr
#line 449 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2640 "parser.tab.cc"
    break;

  case 66: // bracketed_exp: vstructExpr
#line 450 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2646 "parser.tab.cc"
    break;

  case 67: // bracketed_exp: chain_exp
#line 451 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2652 "parser.tab.cc"
    break;

  case 68: // unit_exp: "(" ")"
#line 454 "parser.yy"
                        { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_unit_exp(yylhs.location); }
#line 2658 "parser.tab.cc"
    break;

  case 69: // unit_exp: "{" "}"
#line 455 "parser.yy"
                        { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_unit_exp(yylhs.location); }
#line 2664 "parser.tab.cc"
    break;

  case 70: // paren_exp: "(" long_exp ")"
#line 458 "parser.yy"
                              { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_paren_exp(yylhs.location, yystack_[1].value.as < pdm::ast::Exp* > ()); }
#line 2670 "parser.tab.cc"
    break;

  case 71: // vtupleExpr: "(" expr "," ")"
#line 461 "parser.yy"
                                   { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_tuple_exp(yylhs.location, std::move(std::vector(1,yystack_[2].value.as < pdm::ast::Exp* > ()))); }
#line 2676 "parser.tab.cc"
    break;

  case 72: // vtupleExpr: "(" expr_cl2 ")"
#line 462 "parser.yy"
                                   { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_tuple_exp(yylhs.location, std::move(yystack_[1].value.as < std::vector<pdm::ast::Exp*> > ())); }
#line 2682 "parser.tab.cc"
    break;

  case 73: // vstructExpr: "{" struct_exp_field_cl "}"
#line 465 "parser.yy"
                                            { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_struct_exp(yylhs.location, std::move(yystack_[1].value.as < std::vector<pdm::ast::StructExp::Field*> > ())); }
#line 2688 "parser.tab.cc"
    break;

  case 74: // primary_exp: bracketed_exp
#line 468 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2694 "parser.tab.cc"
    break;

  case 75: // primary_exp: vid
#line 469 "parser.yy"
                     { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_id_exp(yylhs.location, yystack_[0].value.as < TokenInfo > ().ID_intstr); }
#line 2700 "parser.tab.cc"
    break;

  case 76: // primary_exp: int_expr
#line 470 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2706 "parser.tab.cc"
    break;

  case 77: // primary_exp: floatl
#line 471 "parser.yy"
                     { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_float_exp(yylhs.location, yystack_[0].value.as < TokenInfo > ().Float); }
#line 2712 "parser.tab.cc"
    break;

  case 78: // primary_exp: stringls
#line 472 "parser.yy"
                     { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_string_exp(yylhs.location, std::move(yystack_[0].value.as < std::vector<pdm::ast::StringExp::Piece> > ())); }
#line 2718 "parser.tab.cc"
    break;

  case 79: // primary_exp: if_exp
#line 473 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2724 "parser.tab.cc"
    break;

  case 80: // primary_exp: lambda_exp
#line 474 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2730 "parser.tab.cc"
    break;

  case 81: // int_expr: "42"
#line 477 "parser.yy"
                { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_int_exp(yylhs.location, yystack_[0].value.as < TokenInfo > ().Int, ast::IntExp::Base::Dec, false); }
#line 2736 "parser.tab.cc"
    break;

  case 82: // int_expr: "0x2a"
#line 478 "parser.yy"
                { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_int_exp(yylhs.location, yystack_[0].value.as < TokenInfo > ().Int, ast::IntExp::Base::Hex, false); }
#line 2742 "parser.tab.cc"
    break;

  case 83: // int_expr: "42u"
#line 479 "parser.yy"
                         { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_int_exp(yylhs.location, yystack_[0].value.as < TokenInfo > ().Int, ast::IntExp::Base::Dec, true); }
#line 2748 "parser.tab.cc"
    break;

  case 84: // int_expr: "0x2Au"
#line 480 "parser.yy"
                         { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_int_exp(yylhs.location, yystack_[0].value.as < TokenInfo > ().Int, ast::IntExp::Base::Hex, true); }
#line 2754 "parser.tab.cc"
    break;

  case 85: // stringls: "'sq-string-literal'"
#line 483 "parser.yy"
                             { yylhs.value.as < std::vector<pdm::ast::StringExp::Piece> > ().emplace_back(yylhs.location, *yystack_[0].value.as < TokenInfo > ().String_utf8string, ast::StringExp::QuoteKind::SingleQuote); }
#line 2760 "parser.tab.cc"
    break;

  case 86: // stringls: "\"dq-string-literal\""
#line 484 "parser.yy"
                             { yylhs.value.as < std::vector<pdm::ast::StringExp::Piece> > ().emplace_back(yylhs.location, *yystack_[0].value.as < TokenInfo > ().String_utf8string, ast::StringExp::QuoteKind::DoubleQuote); }
#line 2766 "parser.tab.cc"
    break;

  case 87: // stringls: stringls "'sq-string-literal'"
#line 485 "parser.yy"
                             { yylhs.value.as < std::vector<pdm::ast::StringExp::Piece> > () = std::move(yystack_[1].value.as < std::vector<pdm::ast::StringExp::Piece> > ()); yylhs.value.as < std::vector<pdm::ast::StringExp::Piece> > ().emplace_back(yystack_[0].location, *yystack_[0].value.as < TokenInfo > ().String_utf8string, ast::StringExp::QuoteKind::SingleQuote); }
#line 2772 "parser.tab.cc"
    break;

  case 88: // stringls: stringls "\"dq-string-literal\""
#line 486 "parser.yy"
                             { yylhs.value.as < std::vector<pdm::ast::StringExp::Piece> > () = std::move(yystack_[1].value.as < std::vector<pdm::ast::StringExp::Piece> > ()); yylhs.value.as < std::vector<pdm::ast::StringExp::Piece> > ().emplace_back(yystack_[0].location, *yystack_[0].value.as < TokenInfo > ().String_utf8string, ast::StringExp::QuoteKind::DoubleQuote); }
#line 2778 "parser.tab.cc"
    break;

  case 89: // if_exp: "if" bracketed_exp "then" bracketed_exp
#line 489 "parser.yy"
                                                                        { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_if_exp(yylhs.location, yystack_[2].value.as < pdm::ast::Exp* > (), yystack_[0].value.as < pdm::ast::Exp* > (), nullptr); }
#line 2784 "parser.tab.cc"
    break;

  case 90: // if_exp: "if" bracketed_exp "then" bracketed_exp "else" primary_exp
#line 490 "parser.yy"
                                                                        { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_if_exp(yylhs.location, yystack_[4].value.as < pdm::ast::Exp* > (), yystack_[2].value.as < pdm::ast::Exp* > (), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2790 "parser.tab.cc"
    break;

  case 91: // chain_exp: "{" expr "}"
#line 493 "parser.yy"
                                          { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_chain_exp(yylhs.location, std::move(std::vector<ast::Stmt*>{}), yystack_[1].value.as < pdm::ast::Exp* > ()); }
#line 2796 "parser.tab.cc"
    break;

  case 92: // chain_exp: "{" chain_prefix "}"
#line 494 "parser.yy"
                                           { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_chain_exp(yylhs.location, std::move(yystack_[1].value.as < std::vector<pdm::ast::Stmt*> > ()), nullptr); }
#line 2802 "parser.tab.cc"
    break;

  case 93: // chain_exp: "{" chain_prefix expr "}"
#line 495 "parser.yy"
                                           { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_chain_exp(yylhs.location, std::move(yystack_[2].value.as < std::vector<pdm::ast::Stmt*> > ()), yystack_[1].value.as < pdm::ast::Exp* > ()); }
#line 2808 "parser.tab.cc"
    break;

  case 94: // chain_prefix: chain_prefix_stmt ";"
#line 498 "parser.yy"
                                               { yylhs.value.as < std::vector<pdm::ast::Stmt*> > ().push_back(yystack_[1].value.as < pdm::ast::Stmt* > ()); }
#line 2814 "parser.tab.cc"
    break;

  case 95: // chain_prefix: chain_prefix chain_prefix_stmt ";"
#line 499 "parser.yy"
                                                { yylhs.value.as < std::vector<pdm::ast::Stmt*> > () = std::move(yystack_[2].value.as < std::vector<pdm::ast::Stmt*> > ()); yylhs.value.as < std::vector<pdm::ast::Stmt*> > ().push_back(yystack_[1].value.as < pdm::ast::Stmt* > ()); }
#line 2820 "parser.tab.cc"
    break;

  case 96: // lambda_exp: "fn" vpattern bracketed_exp
#line 502 "parser.yy"
                                                    { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_lambda_exp(yylhs.location, yystack_[1].value.as < pdm::ast::VPattern* > (), nullptr, yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2826 "parser.tab.cc"
    break;

  case 97: // lambda_exp: "fn" vpattern "->" type_spec bracketed_exp
#line 503 "parser.yy"
                                                     { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_lambda_exp(yylhs.location, yystack_[3].value.as < pdm::ast::VPattern* > (), yystack_[1].value.as < pdm::ast::TypeSpec* > (), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2832 "parser.tab.cc"
    break;

  case 98: // postfix_exp: primary_exp
#line 507 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2838 "parser.tab.cc"
    break;

  case 99: // postfix_exp: tcall_exp
#line 508 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2844 "parser.tab.cc"
    break;

  case 100: // postfix_exp: vcall_exp
#line 509 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2850 "parser.tab.cc"
    break;

  case 101: // postfix_exp: dot_name_exp
#line 510 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2856 "parser.tab.cc"
    break;

  case 102: // postfix_exp: dot_index_exp
#line 511 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2862 "parser.tab.cc"
    break;

  case 103: // tcall_exp: postfix_exp "[" targ_cl "]"
#line 514 "parser.yy"
                                         { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_tcall_exp(yylhs.location, yystack_[3].value.as < pdm::ast::Exp* > (), std::move(yystack_[1].value.as < std::vector<pdm::ast::TArg*> > ())); }
#line 2868 "parser.tab.cc"
    break;

  case 104: // vcall_exp: postfix_exp "(" ")"
#line 517 "parser.yy"
                                            { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_vcall_exp(yylhs.location, yystack_[2].value.as < pdm::ast::Exp* > (), std::move(std::vector<ast::VArg*>{})); }
#line 2874 "parser.tab.cc"
    break;

  case 105: // vcall_exp: postfix_exp "(" varg_cl ")"
#line 518 "parser.yy"
                                            { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_vcall_exp(yylhs.location, yystack_[3].value.as < pdm::ast::Exp* > (), std::move(yystack_[1].value.as < std::vector<pdm::ast::VArg*> > ())); }
#line 2880 "parser.tab.cc"
    break;

  case 106: // dot_name_exp: postfix_exp "." "<val_id>"
#line 521 "parser.yy"
                                                    { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_struct_dot_name_exp(yylhs.location, yystack_[2].value.as < pdm::ast::Exp* > (), yystack_[0].value.as < TokenInfo > ().ID_intstr); }
#line 2886 "parser.tab.cc"
    break;

  case 107: // dot_name_exp: postfix_exp "." "<TypeId>" "(" expr_cl0 ")"
#line 522 "parser.yy"
                                                    { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_enum_dot_name_exp(yylhs.location, yystack_[5].value.as < pdm::ast::Exp* > (), yystack_[3].value.as < TokenInfo > ().ID_intstr, std::move(yystack_[1].value.as < std::vector<pdm::ast::Exp*> > ())); }
#line 2892 "parser.tab.cc"
    break;

  case 108: // dot_name_exp: mod_prefix "<val_id>"
#line 523 "parser.yy"
                       { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_module_dot_exp(yylhs.location, std::move(yystack_[1].value.as < std::vector<pdm::intern::String> > ()), yystack_[0].value.as < TokenInfo > ().ID_intstr); }
#line 2898 "parser.tab.cc"
    break;

  case 109: // dot_index_exp: postfix_exp "." int_expr
#line 526 "parser.yy"
                                    { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_dot_index_exp(yylhs.location, yystack_[2].value.as < pdm::ast::Exp* > (), yystack_[0].value.as < pdm::ast::Exp* > (), ast::DotIndexExp::RhsHint::LhsNotPtr); }
#line 2904 "parser.tab.cc"
    break;

  case 110: // dot_index_exp: postfix_exp "." bracketed_exp
#line 527 "parser.yy"
                                    { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_dot_index_exp(yylhs.location, yystack_[2].value.as < pdm::ast::Exp* > (), yystack_[0].value.as < pdm::ast::Exp* > (), ast::DotIndexExp::RhsHint::LhsNotPtr); }
#line 2910 "parser.tab.cc"
    break;

  case 111: // unary_exp: postfix_exp
#line 531 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2916 "parser.tab.cc"
    break;

  case 112: // unary_exp: unary_op unary_exp
#line 532 "parser.yy"
                             { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_unary_exp(yylhs.location, yystack_[1].value.as < pdm::ast::UnaryOperator > (), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2922 "parser.tab.cc"
    break;

  case 113: // unary_op: "+"
#line 535 "parser.yy"
                 { yylhs.value.as < pdm::ast::UnaryOperator > () = ast::UnaryOperator::Plus; }
#line 2928 "parser.tab.cc"
    break;

  case 114: // unary_op: "-"
#line 536 "parser.yy"
                 { yylhs.value.as < pdm::ast::UnaryOperator > () = ast::UnaryOperator::Minus; }
#line 2934 "parser.tab.cc"
    break;

  case 115: // unary_op: "not"
#line 537 "parser.yy"
                 { yylhs.value.as < pdm::ast::UnaryOperator > () = ast::UnaryOperator::Not; }
#line 2940 "parser.tab.cc"
    break;

  case 116: // binary_exp: or_binary_exp
#line 541 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2946 "parser.tab.cc"
    break;

  case 117: // mul_binary_op: "*"
#line 544 "parser.yy"
                 { yylhs.value.as < pdm::ast::BinaryOperator > () = ast::BinaryOperator::Mul; }
#line 2952 "parser.tab.cc"
    break;

  case 118: // mul_binary_op: "/"
#line 545 "parser.yy"
                 { yylhs.value.as < pdm::ast::BinaryOperator > () = ast::BinaryOperator::Div; }
#line 2958 "parser.tab.cc"
    break;

  case 119: // mul_binary_op: "%"
#line 546 "parser.yy"
                 { yylhs.value.as < pdm::ast::BinaryOperator > () = ast::BinaryOperator::Rem; }
#line 2964 "parser.tab.cc"
    break;

  case 120: // mul_binary_exp: unary_exp
#line 549 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2970 "parser.tab.cc"
    break;

  case 121: // mul_binary_exp: mul_binary_exp mul_binary_op unary_exp
#line 550 "parser.yy"
                                               { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_binary_exp(yylhs.location, yystack_[1].value.as < pdm::ast::BinaryOperator > (), yystack_[2].value.as < pdm::ast::Exp* > (), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2976 "parser.tab.cc"
    break;

  case 122: // add_binary_op: "+"
#line 553 "parser.yy"
             { yylhs.value.as < pdm::ast::BinaryOperator > () = ast::BinaryOperator::Add; }
#line 2982 "parser.tab.cc"
    break;

  case 123: // add_binary_op: "-"
#line 554 "parser.yy"
             { yylhs.value.as < pdm::ast::BinaryOperator > () = ast::BinaryOperator::Subtract; }
#line 2988 "parser.tab.cc"
    break;

  case 124: // add_binary_exp: mul_binary_exp
#line 557 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2994 "parser.tab.cc"
    break;

  case 125: // add_binary_exp: add_binary_exp add_binary_op mul_binary_exp
#line 558 "parser.yy"
                                                    { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_binary_exp(yylhs.location, yystack_[1].value.as < pdm::ast::BinaryOperator > (), yystack_[2].value.as < pdm::ast::Exp* > (), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 3000 "parser.tab.cc"
    break;

  case 126: // cmp_binary_op: "<"
#line 561 "parser.yy"
                { yylhs.value.as < pdm::ast::BinaryOperator > () = ast::BinaryOperator::Less; }
#line 3006 "parser.tab.cc"
    break;

  case 127: // cmp_binary_op: "<="
#line 562 "parser.yy"
                { yylhs.value.as < pdm::ast::BinaryOperator > () = ast::BinaryOperator::LessOrEq; }
#line 3012 "parser.tab.cc"
    break;

  case 128: // cmp_binary_op: ">"
#line 563 "parser.yy"
                { yylhs.value.as < pdm::ast::BinaryOperator > () = ast::BinaryOperator::Greater; }
#line 3018 "parser.tab.cc"
    break;

  case 129: // cmp_binary_op: ">="
#line 564 "parser.yy"
                { yylhs.value.as < pdm::ast::BinaryOperator > () = ast::BinaryOperator::GreaterOrEq; }
#line 3024 "parser.tab.cc"
    break;

  case 130: // cmp_binary_exp: add_binary_exp
#line 567 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 3030 "parser.tab.cc"
    break;

  case 131: // cmp_binary_exp: cmp_binary_exp cmp_binary_op add_binary_exp
#line 568 "parser.yy"
                                                    { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_binary_exp(yylhs.location, yystack_[1].value.as < pdm::ast::BinaryOperator > (), yystack_[2].value.as < pdm::ast::Exp* > (), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 3036 "parser.tab.cc"
    break;

  case 132: // eq_binary_op: "=="
#line 571 "parser.yy"
                 { yylhs.value.as < pdm::ast::BinaryOperator > () = ast::BinaryOperator::Equals; }
#line 3042 "parser.tab.cc"
    break;

  case 133: // eq_binary_op: "!="
#line 572 "parser.yy"
                 { yylhs.value.as < pdm::ast::BinaryOperator > () = ast::BinaryOperator::NotEquals; }
#line 3048 "parser.tab.cc"
    break;

  case 134: // eq_binary_exp: cmp_binary_exp
#line 575 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 3054 "parser.tab.cc"
    break;

  case 135: // eq_binary_exp: eq_binary_exp eq_binary_op cmp_binary_exp
#line 576 "parser.yy"
                                                { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_binary_exp(yylhs.location, yystack_[1].value.as < pdm::ast::BinaryOperator > (), yystack_[2].value.as < pdm::ast::Exp* > (), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 3060 "parser.tab.cc"
    break;

  case 136: // and_binary_exp: eq_binary_exp
#line 579 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 3066 "parser.tab.cc"
    break;

  case 137: // and_binary_exp: and_binary_exp "and" eq_binary_exp
#line 580 "parser.yy"
                                           { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_binary_exp(yylhs.location, ast::BinaryOperator::And, yystack_[2].value.as < pdm::ast::Exp* > (), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 3072 "parser.tab.cc"
    break;

  case 138: // xor_binary_exp: and_binary_exp
#line 583 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 3078 "parser.tab.cc"
    break;

  case 139: // xor_binary_exp: xor_binary_exp "xor" and_binary_exp
#line 584 "parser.yy"
                                           { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_binary_exp(yylhs.location, ast::BinaryOperator::XOr, yystack_[2].value.as < pdm::ast::Exp* > (), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 3084 "parser.tab.cc"
    break;

  case 140: // or_binary_exp: xor_binary_exp
#line 587 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 3090 "parser.tab.cc"
    break;

  case 141: // or_binary_exp: or_binary_exp "or" xor_binary_exp
#line 588 "parser.yy"
                                           { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_binary_exp(yylhs.location, ast::BinaryOperator::Or, yystack_[2].value.as < pdm::ast::Exp* > (), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 3096 "parser.tab.cc"
    break;

  case 142: // type_query_exp: type_spec type_query_op long_type_spec
#line 592 "parser.yy"
                                               { yylhs.value.as < pdm::ast::TypeQueryExp* > () = mgr->new_type_query_exp(yylhs.location, yystack_[1].value.as < pdm::ast::TypeQueryKind > (), yystack_[2].value.as < pdm::ast::TypeSpec* > (), yystack_[0].value.as < pdm::ast::TypeSpec* > ()); }
#line 3102 "parser.tab.cc"
    break;

  case 143: // type_query_op: ":<"
#line 595 "parser.yy"
                    { yylhs.value.as < pdm::ast::TypeQueryKind > () = ast::TypeQueryKind::LhsSubtypesRhs; }
#line 3108 "parser.tab.cc"
    break;

  case 144: // type_query_op: ">:"
#line 596 "parser.yy"
                    { yylhs.value.as < pdm::ast::TypeQueryKind > () = ast::TypeQueryKind::LhsSupertypesRhs; }
#line 3114 "parser.tab.cc"
    break;

  case 145: // type_query_op: "::"
#line 597 "parser.yy"
                    { yylhs.value.as < pdm::ast::TypeQueryKind > () = ast::TypeQueryKind::LhsEqualsRhs; }
#line 3120 "parser.tab.cc"
    break;

  case 146: // type_spec: unary_type_spec
#line 605 "parser.yy"
      { yylhs.value.as < pdm::ast::TypeSpec* > () = yystack_[0].value.as < pdm::ast::TypeSpec* > (); }
#line 3126 "parser.tab.cc"
    break;

  case 147: // type_spec_cl1: type_spec
#line 608 "parser.yy"
                                   { yylhs.value.as < std::vector<pdm::ast::TypeSpec*> > ().push_back(yystack_[0].value.as < pdm::ast::TypeSpec* > ()); }
#line 3132 "parser.tab.cc"
    break;

  case 148: // type_spec_cl1: type_spec_cl1 "," type_spec
#line 609 "parser.yy"
                                    { yylhs.value.as < std::vector<pdm::ast::TypeSpec*> > () = std::move(yystack_[2].value.as < std::vector<pdm::ast::TypeSpec*> > ()); yylhs.value.as < std::vector<pdm::ast::TypeSpec*> > ().push_back(yystack_[0].value.as < pdm::ast::TypeSpec* > ()); }
#line 3138 "parser.tab.cc"
    break;

  case 149: // type_spec_cl2: type_spec "," type_spec
#line 612 "parser.yy"
                                    { yylhs.value.as < std::vector<pdm::ast::TypeSpec*> > ().reserve(2); yylhs.value.as < std::vector<pdm::ast::TypeSpec*> > ().push_back(yystack_[2].value.as < pdm::ast::TypeSpec* > ()); yylhs.value.as < std::vector<pdm::ast::TypeSpec*> > ().push_back(yystack_[0].value.as < pdm::ast::TypeSpec* > ()); }
#line 3144 "parser.tab.cc"
    break;

  case 150: // type_spec_cl2: type_spec_cl2 "," type_spec
#line 613 "parser.yy"
                                    { yylhs.value.as < std::vector<pdm::ast::TypeSpec*> > () = std::move(yystack_[2].value.as < std::vector<pdm::ast::TypeSpec*> > ()); yylhs.value.as < std::vector<pdm::ast::TypeSpec*> > ().push_back(yystack_[0].value.as < pdm::ast::TypeSpec* > ()); }
#line 3150 "parser.tab.cc"
    break;

  case 151: // struct_type_spec_field: vid type_spec
#line 617 "parser.yy"
                                   { yylhs.value.as < pdm::ast::StructTypeSpec::Field* > () = mgr->new_struct_type_spec_field(yylhs.location, yystack_[1].value.as < TokenInfo > ().ID_intstr, yystack_[0].value.as < pdm::ast::TypeSpec* > ()); }
#line 3156 "parser.tab.cc"
    break;

  case 152: // struct_type_spec_field_cl: struct_type_spec_field
#line 620 "parser.yy"
                                                           { yylhs.value.as < std::vector<pdm::ast::StructTypeSpec::Field*> > ().push_back(yystack_[0].value.as < pdm::ast::StructTypeSpec::Field* > ()); }
#line 3162 "parser.tab.cc"
    break;

  case 153: // struct_type_spec_field_cl: struct_type_spec_field_cl "," struct_type_spec_field
#line 621 "parser.yy"
                                                              { yylhs.value.as < std::vector<pdm::ast::StructTypeSpec::Field*> > () = std::move(yystack_[2].value.as < std::vector<pdm::ast::StructTypeSpec::Field*> > ()); yylhs.value.as < std::vector<pdm::ast::StructTypeSpec::Field*> > ().push_back(yystack_[0].value.as < pdm::ast::StructTypeSpec::Field* > ()); }
#line 3168 "parser.tab.cc"
    break;

  case 154: // primary_type_spec: tid
#line 625 "parser.yy"
                        { yylhs.value.as < pdm::ast::TypeSpec* > () = mgr->new_id_type_spec(yylhs.location, yystack_[0].value.as < TokenInfo > ().ID_intstr); }
#line 3174 "parser.tab.cc"
    break;

  case 155: // primary_type_spec: paren_type_spec
#line 626 "parser.yy"
      { yylhs.value.as < pdm::ast::TypeSpec* > () = yystack_[0].value.as < pdm::ast::TypeSpec* > (); }
#line 3180 "parser.tab.cc"
    break;

  case 156: // primary_type_spec: tuple_type_spec
#line 627 "parser.yy"
      { yylhs.value.as < pdm::ast::TypeSpec* > () = yystack_[0].value.as < pdm::ast::TypeSpec* > (); }
#line 3186 "parser.tab.cc"
    break;

  case 157: // primary_type_spec: mod_prefix_tid
#line 628 "parser.yy"
      { yylhs.value.as < pdm::ast::TypeSpec* > () = yystack_[0].value.as < pdm::ast::TypeSpec* > (); }
#line 3192 "parser.tab.cc"
    break;

  case 158: // primary_type_spec: fn_type_spec
#line 629 "parser.yy"
      { yylhs.value.as < pdm::ast::TypeSpec* > () = yystack_[0].value.as < pdm::ast::TypeSpec* > (); }
#line 3198 "parser.tab.cc"
    break;

  case 159: // paren_type_spec: "(" type_spec ")"
#line 632 "parser.yy"
                                 { yylhs.value.as < pdm::ast::TypeSpec* > () = mgr->new_paren_type_spec(yylhs.location, yystack_[1].value.as < pdm::ast::TypeSpec* > ()); }
#line 3204 "parser.tab.cc"
    break;

  case 160: // tuple_type_spec: "(" type_spec "," ")"
#line 635 "parser.yy"
                                     { yylhs.value.as < pdm::ast::TypeSpec* > () = mgr->new_tuple_type_spec(yylhs.location, std::move(std::vector(1,yystack_[2].value.as < pdm::ast::TypeSpec* > ()))); }
#line 3210 "parser.tab.cc"
    break;

  case 161: // tuple_type_spec: "(" type_spec_cl2 ")"
#line 636 "parser.yy"
                                     { yylhs.value.as < pdm::ast::TypeSpec* > () = mgr->new_tuple_type_spec(yylhs.location, std::move(yystack_[1].value.as < std::vector<pdm::ast::TypeSpec*> > ())); }
#line 3216 "parser.tab.cc"
    break;

  case 162: // mod_prefix_tid: mod_prefix tid
#line 639 "parser.yy"
                            { yylhs.value.as < pdm::ast::TypeSpec* > () = mgr->new_dot_name_type_spec_with_mod_prefix(yylhs.location, std::move(yystack_[1].value.as < std::vector<pdm::intern::String> > ()), yystack_[0].value.as < TokenInfo > ().ID_intstr); }
#line 3222 "parser.tab.cc"
    break;

  case 163: // fn_type_spec: "Fn" vpattern primary_type_spec
#line 642 "parser.yy"
                                        { yylhs.value.as < pdm::ast::TypeSpec* > () = mgr->new_fn_type_spec(yylhs.location, std::move(yystack_[1].value.as < pdm::ast::VPattern* > ()), yystack_[0].value.as < pdm::ast::TypeSpec* > ()); }
#line 3228 "parser.tab.cc"
    break;

  case 164: // postfix_type_spec: primary_type_spec
#line 646 "parser.yy"
      { yylhs.value.as < pdm::ast::TypeSpec* > () = yystack_[0].value.as < pdm::ast::TypeSpec* > (); }
#line 3234 "parser.tab.cc"
    break;

  case 165: // postfix_type_spec: tcall_type_spec
#line 647 "parser.yy"
      { yylhs.value.as < pdm::ast::TypeSpec* > () = yystack_[0].value.as < pdm::ast::TypeSpec* > (); }
#line 3240 "parser.tab.cc"
    break;

  case 166: // tcall_type_spec: postfix_type_spec "[" targ_cl "]"
#line 650 "parser.yy"
                                               { yylhs.value.as < pdm::ast::TypeSpec* > () = mgr->new_tcall_type_spec(yylhs.location, yystack_[3].value.as < pdm::ast::TypeSpec* > (), std::move(yystack_[1].value.as < std::vector<pdm::ast::TArg*> > ())); }
#line 3246 "parser.tab.cc"
    break;

  case 167: // unary_type_spec: postfix_type_spec
#line 654 "parser.yy"
      { yylhs.value.as < pdm::ast::TypeSpec* > () = yystack_[0].value.as < pdm::ast::TypeSpec* > (); }
#line 3252 "parser.tab.cc"
    break;

  case 168: // long_type_spec: unary_type_spec
#line 658 "parser.yy"
      { yylhs.value.as < pdm::ast::TypeSpec* > () = yystack_[0].value.as < pdm::ast::TypeSpec* > (); }
#line 3258 "parser.tab.cc"
    break;

  case 169: // long_type_spec: struct_type_spec
#line 659 "parser.yy"
      { yylhs.value.as < pdm::ast::TypeSpec* > () = yystack_[0].value.as < pdm::ast::TypeSpec* > (); }
#line 3264 "parser.tab.cc"
    break;

  case 170: // struct_type_spec: "{" struct_type_spec_field_cl "}"
#line 662 "parser.yy"
                                               { yylhs.value.as < pdm::ast::TypeSpec* > () = mgr->new_struct_type_spec(yylhs.location, std::move(yystack_[1].value.as < std::vector<pdm::ast::StructTypeSpec::Field*> > ())); }
#line 3270 "parser.tab.cc"
    break;

  case 171: // targ: type_spec
#line 665 "parser.yy"
                { yylhs.value.as < pdm::ast::TArg* > () = mgr->new_targ_type_spec(yylhs.location, yystack_[0].value.as < pdm::ast::TypeSpec* > ()); }
#line 3276 "parser.tab.cc"
    break;

  case 172: // targ: expr
#line 666 "parser.yy"
               { yylhs.value.as < pdm::ast::TArg* > () = mgr->new_targ_exp(yylhs.location, yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 3282 "parser.tab.cc"
    break;

  case 173: // targ_cl: targ
#line 669 "parser.yy"
                            { yylhs.value.as < std::vector<pdm::ast::TArg*> > ().push_back(yystack_[0].value.as < pdm::ast::TArg* > ()); }
#line 3288 "parser.tab.cc"
    break;

  case 174: // targ_cl: targ_cl "," targ
#line 670 "parser.yy"
                            { yylhs.value.as < std::vector<pdm::ast::TArg*> > () = std::move(yystack_[2].value.as < std::vector<pdm::ast::TArg*> > ()); yylhs.value.as < std::vector<pdm::ast::TArg*> > ().push_back(yystack_[0].value.as < pdm::ast::TArg* > ()); }
#line 3294 "parser.tab.cc"
    break;

  case 175: // varg: expr
#line 672 "parser.yy"
                            { yylhs.value.as < pdm::ast::VArg* > () = mgr->new_varg(yylhs.location, yystack_[0].value.as < pdm::ast::Exp* > (), ast::VArgAccessSpec::In); }
#line 3300 "parser.tab.cc"
    break;

  case 176: // varg: "out" expr
#line 673 "parser.yy"
                            { yylhs.value.as < pdm::ast::VArg* > () = mgr->new_varg(yylhs.location, yystack_[0].value.as < pdm::ast::Exp* > (), ast::VArgAccessSpec::Out); }
#line 3306 "parser.tab.cc"
    break;

  case 177: // varg: "inout" expr
#line 674 "parser.yy"
                            { yylhs.value.as < pdm::ast::VArg* > () = mgr->new_varg(yylhs.location, yystack_[0].value.as < pdm::ast::Exp* > (), ast::VArgAccessSpec::InOut); }
#line 3312 "parser.tab.cc"
    break;

  case 178: // varg_cl: varg
#line 677 "parser.yy"
                            { yylhs.value.as < std::vector<pdm::ast::VArg*> > ().push_back(yystack_[0].value.as < pdm::ast::VArg* > ()); }
#line 3318 "parser.tab.cc"
    break;

  case 179: // varg_cl: varg_cl "," varg
#line 678 "parser.yy"
                            { yylhs.value.as < std::vector<pdm::ast::VArg*> > () = std::move(yystack_[2].value.as < std::vector<pdm::ast::VArg*> > ()); yylhs.value.as < std::vector<pdm::ast::VArg*> > ().push_back(yystack_[0].value.as < pdm::ast::VArg* > ()); }
#line 3324 "parser.tab.cc"
    break;

  case 180: // class_spec: postfix_class_spec
#line 688 "parser.yy"
      { yylhs.value.as < pdm::ast::ClassSpec* > () = yystack_[0].value.as < pdm::ast::ClassSpec* > (); }
#line 3330 "parser.tab.cc"
    break;

  case 181: // primary_class_spec: tid
#line 691 "parser.yy"
            { yylhs.value.as < pdm::ast::ClassSpec* > () = mgr->new_id_class_spec(yylhs.location, yystack_[0].value.as < TokenInfo > ().ID_intstr); }
#line 3336 "parser.tab.cc"
    break;

  case 182: // postfix_class_spec: primary_class_spec
#line 694 "parser.yy"
      { yylhs.value.as < pdm::ast::ClassSpec* > () = yystack_[0].value.as < pdm::ast::ClassSpec* > (); }
#line 3342 "parser.tab.cc"
    break;

  case 183: // postfix_class_spec: postfix_class_spec "[" targ_cl "]"
#line 695 "parser.yy"
                                                { yylhs.value.as < pdm::ast::ClassSpec* > () = mgr->new_tcall_class_spec(yylhs.location, yystack_[3].value.as < pdm::ast::ClassSpec* > (), std::move(yystack_[1].value.as < std::vector<pdm::ast::TArg*> > ())); }
#line 3348 "parser.tab.cc"
    break;

  case 184: // struct_exp_field: vid "=" expr
#line 703 "parser.yy"
                    { yylhs.value.as < pdm::ast::StructExp::Field* > () = mgr->new_struct_exp_field(yylhs.location, yystack_[2].value.as < TokenInfo > ().ID_intstr, yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 3354 "parser.tab.cc"
    break;

  case 185: // vpattern_field: vid type_spec
#line 706 "parser.yy"
                             { yylhs.value.as < pdm::ast::VPattern::Field* > () = mgr->new_vpattern_field(yylhs.location, yystack_[1].value.as < TokenInfo > ().ID_intstr, yystack_[0].value.as < pdm::ast::TypeSpec* > (), ast::VArgAccessSpec::In); }
#line 3360 "parser.tab.cc"
    break;

  case 186: // vpattern_field: "out" vid type_spec
#line 707 "parser.yy"
                             { yylhs.value.as < pdm::ast::VPattern::Field* > () = mgr->new_vpattern_field(yylhs.location, yystack_[1].value.as < TokenInfo > ().ID_intstr, yystack_[0].value.as < pdm::ast::TypeSpec* > (), ast::VArgAccessSpec::Out); }
#line 3366 "parser.tab.cc"
    break;

  case 187: // vpattern_field: "inout" vid type_spec
#line 708 "parser.yy"
                             { yylhs.value.as < pdm::ast::VPattern::Field* > () = mgr->new_vpattern_field(yylhs.location, yystack_[1].value.as < TokenInfo > ().ID_intstr, yystack_[0].value.as < pdm::ast::TypeSpec* > (), ast::VArgAccessSpec::InOut); }
#line 3372 "parser.tab.cc"
    break;

  case 188: // lpattern_field: vid type_spec
#line 711 "parser.yy"
                     { yylhs.value.as < pdm::ast::LPattern::Field* > () = mgr->new_lpattern_field(yylhs.location, ast::LPattern::FieldKind::IdTypeSpecPair, yystack_[1].value.as < TokenInfo > ().ID_intstr, yystack_[0].value.as < pdm::ast::TypeSpec* > ()); }
#line 3378 "parser.tab.cc"
    break;

  case 189: // lpattern_field: vid
#line 712 "parser.yy"
                    { yylhs.value.as < pdm::ast::LPattern::Field* > () = mgr->new_lpattern_field(yylhs.location, ast::LPattern::FieldKind::IdSingleton, yystack_[0].value.as < TokenInfo > ().ID_intstr); }
#line 3384 "parser.tab.cc"
    break;

  case 190: // tpattern_field: vid type_spec
#line 715 "parser.yy"
                      { yylhs.value.as < pdm::ast::TPattern::Field* > () = mgr->new_tpattern_field(yylhs.location, ast::TPattern::FieldKind::Value, yystack_[1].value.as < TokenInfo > ().ID_intstr, yystack_[0].value.as < pdm::ast::TypeSpec* > ()); }
#line 3390 "parser.tab.cc"
    break;

  case 191: // tpattern_field: tid class_spec
#line 716 "parser.yy"
                      { yylhs.value.as < pdm::ast::TPattern::Field* > () = mgr->new_tpattern_field(yylhs.location, ast::TPattern::FieldKind::Type, yystack_[1].value.as < TokenInfo > ().ID_intstr, yystack_[0].value.as < pdm::ast::ClassSpec* > ()); }
#line 3396 "parser.tab.cc"
    break;

  case 192: // destructured_lpattern: "(" lpattern_field_cl ")"
#line 720 "parser.yy"
                                          { yylhs.value.as < pdm::ast::LPattern* > () = mgr->new_lpattern(yylhs.location, std::move(yystack_[1].value.as < std::vector<pdm::ast::LPattern::Field*> > ()), true); }
#line 3402 "parser.tab.cc"
    break;

  case 193: // lpattern: lpattern_field
#line 724 "parser.yy"
                        { yylhs.value.as < pdm::ast::LPattern* > () = mgr->new_lpattern(yylhs.location, std::move(std::vector<ast::LPattern::Field*>{1,yystack_[0].value.as < pdm::ast::LPattern::Field* > ()}), false); }
#line 3408 "parser.tab.cc"
    break;

  case 194: // lpattern: destructured_lpattern
#line 725 "parser.yy"
      { yylhs.value.as < pdm::ast::LPattern* > () = yystack_[0].value.as < pdm::ast::LPattern* > (); }
#line 3414 "parser.tab.cc"
    break;

  case 195: // vpattern: "(" vpattern_field_cl ")"
#line 728 "parser.yy"
                                       { yylhs.value.as < pdm::ast::VPattern* > () = mgr->new_vpattern(yylhs.location, std::move(yystack_[1].value.as < std::vector<pdm::ast::VPattern::Field*> > ())); }
#line 3420 "parser.tab.cc"
    break;

  case 196: // vpattern: "(" ")"
#line 729 "parser.yy"
                                       { yylhs.value.as < pdm::ast::VPattern* > () = mgr->new_vpattern(yylhs.location, std::move(std::vector<ast::VPattern::Field*>{})); }
#line 3426 "parser.tab.cc"
    break;

  case 197: // tpattern: "[" tpattern_field_cl "]"
#line 732 "parser.yy"
                                               { yylhs.value.as < pdm::ast::TPattern* > () = mgr->new_tpattern(yylhs.location, std::move(yystack_[1].value.as < std::vector<pdm::ast::TPattern::Field*> > ()), false); }
#line 3432 "parser.tab.cc"
    break;

  case 198: // tpattern: "!" "[" tpattern_field_cl "]"
#line 733 "parser.yy"
                                               { yylhs.value.as < pdm::ast::TPattern* > () = mgr->new_tpattern(yylhs.location, std::move(yystack_[1].value.as < std::vector<pdm::ast::TPattern::Field*> > ()), true); }
#line 3438 "parser.tab.cc"
    break;

  case 199: // vpattern_field_cl: vpattern_field
#line 737 "parser.yy"
                                              { yylhs.value.as < std::vector<pdm::ast::VPattern::Field*> > ().push_back(yystack_[0].value.as < pdm::ast::VPattern::Field* > ()); }
#line 3444 "parser.tab.cc"
    break;

  case 200: // vpattern_field_cl: vpattern_field_cl "," vpattern_field
#line 738 "parser.yy"
                                               { yylhs.value.as < std::vector<pdm::ast::VPattern::Field*> > () = std::move(yystack_[2].value.as < std::vector<pdm::ast::VPattern::Field*> > ()); yylhs.value.as < std::vector<pdm::ast::VPattern::Field*> > ().push_back(yystack_[0].value.as < pdm::ast::VPattern::Field* > ()); }
#line 3450 "parser.tab.cc"
    break;

  case 201: // lpattern_field_cl: lpattern_field
#line 741 "parser.yy"
                                              { yylhs.value.as < std::vector<pdm::ast::LPattern::Field*> > ().push_back(yystack_[0].value.as < pdm::ast::LPattern::Field* > ()); }
#line 3456 "parser.tab.cc"
    break;

  case 202: // lpattern_field_cl: lpattern_field_cl "," lpattern_field
#line 742 "parser.yy"
                                               { yylhs.value.as < std::vector<pdm::ast::LPattern::Field*> > () = std::move(yystack_[2].value.as < std::vector<pdm::ast::LPattern::Field*> > ()); yylhs.value.as < std::vector<pdm::ast::LPattern::Field*> > ().push_back(yystack_[0].value.as < pdm::ast::LPattern::Field* > ()); }
#line 3462 "parser.tab.cc"
    break;

  case 203: // tpattern_field_cl: tpattern_field
#line 745 "parser.yy"
                                              { yylhs.value.as < std::vector<pdm::ast::TPattern::Field*> > ().push_back(yystack_[0].value.as < pdm::ast::TPattern::Field* > ()); }
#line 3468 "parser.tab.cc"
    break;

  case 204: // tpattern_field_cl: tpattern_field_cl "," tpattern_field
#line 746 "parser.yy"
                                               { yylhs.value.as < std::vector<pdm::ast::TPattern::Field*> > () = std::move(yystack_[2].value.as < std::vector<pdm::ast::TPattern::Field*> > ()); yylhs.value.as < std::vector<pdm::ast::TPattern::Field*> > ().push_back(yystack_[0].value.as < pdm::ast::TPattern::Field* > ()); }
#line 3474 "parser.tab.cc"
    break;

  case 205: // struct_exp_field_cl: struct_exp_field
#line 749 "parser.yy"
                                                    { yylhs.value.as < std::vector<pdm::ast::StructExp::Field*> > ().push_back(yystack_[0].value.as < pdm::ast::StructExp::Field* > ()); }
#line 3480 "parser.tab.cc"
    break;

  case 206: // struct_exp_field_cl: struct_exp_field_cl "," struct_exp_field
#line 750 "parser.yy"
                                                    { yylhs.value.as < std::vector<pdm::ast::StructExp::Field*> > () = std::move(yystack_[2].value.as < std::vector<pdm::ast::StructExp::Field*> > ()); yylhs.value.as < std::vector<pdm::ast::StructExp::Field*> > ().push_back(yystack_[0].value.as < pdm::ast::StructExp::Field* > ()); }
#line 3486 "parser.tab.cc"
    break;

  case 207: // tpattern_seq: tpattern
#line 754 "parser.yy"
                             { yylhs.value.as < std::vector<pdm::ast::TPattern*> > ().push_back(yystack_[0].value.as < pdm::ast::TPattern* > ()); }
#line 3492 "parser.tab.cc"
    break;

  case 208: // tpattern_seq: tpattern_seq tpattern
#line 755 "parser.yy"
                             { yylhs.value.as < std::vector<pdm::ast::TPattern*> > () = std::move(yystack_[1].value.as < std::vector<pdm::ast::TPattern*> > ()); yylhs.value.as < std::vector<pdm::ast::TPattern*> > ().push_back(yystack_[0].value.as < pdm::ast::TPattern* > ()); }
#line 3498 "parser.tab.cc"
    break;


#line 3502 "parser.tab.cc"

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





  const short parser::yypact_ninf_ = -263;

  const signed char parser::yytable_ninf_ = -50;

  const short
  parser::yypact_[] =
  {
    -263,    14,    12,  -263,    25,    25,    -1,    40,  -263,  -263,
    -263,    70,    79,  -263,   118,   104,  -263,    72,   741,   115,
    -263,  -263,  -263,   129,  -263,   -32,    97,  -263,  -263,  -263,
    -263,  -263,  -263,  -263,  -263,   628,   427,  -263,  -263,   153,
    -263,  -263,   206,  -263,  -263,  -263,  -263,  -263,  -263,  -263,
    -263,    93,  -263,  -263,  -263,     3,  -263,  -263,  -263,  -263,
    -263,   741,  -263,   234,   178,   222,   196,   182,   221,   195,
     213,    72,   244,    61,   130,  -263,   223,   230,   121,     7,
       7,     7,   741,   741,  -263,   241,  -263,  -263,  -263,  -263,
    -263,   216,   245,   516,  -263,    56,  -263,   250,   256,  -263,
    -263,   105,   553,   666,  -263,  -263,  -263,  -263,   741,  -263,
    -263,   741,  -263,  -263,  -263,  -263,   741,  -263,  -263,   741,
     741,   741,   741,   296,  -263,    17,   258,  -263,  -263,  -263,
    -263,   124,     8,  -263,   -32,   304,   304,  -263,    11,  -263,
     138,    11,  -263,   703,  -263,   741,  -263,   304,    11,  -263,
    -263,   249,   251,   252,   253,  -263,  -263,   741,  -263,  -263,
     268,   267,   304,  -263,  -263,  -263,   276,  -263,  -263,   741,
     741,  -263,  -263,  -263,   172,    97,   352,   153,   265,  -263,
    -263,  -263,  -263,  -263,  -263,  -263,   275,  -263,  -263,  -263,
      78,  -263,   234,   178,   222,   196,   182,   221,    99,  -263,
     280,  -263,   269,    26,   277,    25,   270,  -263,  -263,   158,
      11,   741,   269,   309,    15,   315,    11,    11,  -263,    94,
    -263,   -32,  -263,  -263,  -263,  -263,   181,  -263,   741,   741,
     741,   741,  -263,  -263,  -263,   216,  -263,  -263,  -263,  -263,
     591,  -263,    11,   190,   193,  -263,   666,   666,  -263,   213,
     102,  -263,    25,    11,  -263,   114,   304,  -263,  -263,  -263,
     269,   262,  -263,   285,    25,    26,   279,  -263,  -263,  -263,
      25,   741,   316,   778,  -263,  -263,  -263,  -263,   304,  -263,
    -263,  -263,  -263,  -263,   204,  -263,  -263,    73,  -263,    11,
    -263,   135,  -263,    20,   213,  -263,  -263,  -263,   286,  -263,
     269,  -263,    11,  -263,    62,   140,    25,    90,    25,  -263,
      25,    72,  -263,    25,  -263,  -263,   741,  -263,  -263,  -263,
    -263,  -263,  -263,    29,   666,  -263,  -263,   304,  -263,  -263,
    -263,  -263,  -263,   211,   278,    25,  -263,    72,  -263,  -263,
     145,  -263,    11,  -263,   290,   281,  -263,  -263,  -263,    11,
     292,    18,   291,    44,    11,  -263,   299,  -263,  -263,  -263,
    -263,    26,    55,  -263,  -263,  -263
  };

  const unsigned char
  parser::yydefact_[] =
  {
       3,     0,     7,     1,     0,     0,     0,     2,     5,     6,
      48,     0,     0,     4,     0,     0,     9,     0,     0,     0,
       8,    52,    51,     0,    49,     0,     0,   115,    81,    82,
      83,    84,    50,    86,    85,     0,     0,   113,   114,     0,
      75,    77,     0,    37,    74,    63,    64,    65,    66,    98,
      76,    78,    79,    67,    80,   111,    99,   100,   101,   102,
     120,     0,    55,   124,   130,   134,   136,   138,   140,   116,
       0,     0,     0,     0,     0,    68,    56,     0,     0,     0,
       0,     0,     0,     0,    69,     0,    38,    39,    40,    41,
      42,    75,     0,     0,   205,     0,    53,   108,     0,    88,
      87,     0,     0,     0,   112,   117,   118,   119,     0,   122,
     123,     0,   126,   127,   128,   129,     0,   132,   133,     0,
       0,     0,     0,     0,    19,     0,     0,    15,    16,    17,
      18,     0,     0,    36,     0,     0,     0,   196,     0,   199,
       0,     0,    96,     0,    70,     0,    72,     0,   189,   193,
     194,     0,     0,     0,     0,    47,    94,     0,    91,    92,
       0,     0,     0,    73,    54,   106,     0,   110,   109,     0,
       0,   104,   175,   178,     0,     0,     0,   154,     0,   172,
     171,   164,   155,   156,   157,   158,   167,   165,   146,   173,
       0,   121,   125,   131,   135,   137,   139,   141,     0,    10,
       0,    13,     0,     0,     0,     0,     0,    26,   207,     0,
       0,     0,     0,     0,     0,    89,     0,     0,   185,     0,
     195,     0,    71,    59,    60,   201,     0,   188,     0,     0,
       0,     0,   184,    95,    93,     0,   206,    57,   176,   177,
       0,   105,     0,     0,     0,   162,     0,     0,   103,     0,
       0,    14,     0,     0,   203,     0,     0,   168,    24,   169,
       0,    28,    29,    31,     0,     0,     0,    27,   208,    20,
       0,     0,     0,     0,   186,   187,   200,    97,     0,   192,
      43,    44,    45,    46,     0,   179,   163,     0,   159,     0,
     161,     0,   174,     0,     0,   181,   191,   182,   180,   190,
       0,   197,     0,   152,     0,     0,     0,     0,     0,    25,
       0,     0,    21,     0,    90,   202,     0,   107,   160,   149,
     150,   166,    11,     0,     0,   204,   151,     0,   170,   198,
      30,    32,   147,     0,     0,     0,    22,     0,    58,    12,
       0,   153,     0,    33,     0,     0,    23,   183,   148,     0,
       0,     0,     0,     0,     0,    34,     0,    61,   145,   143,
     144,     0,     0,    62,   142,    35
  };

  const short
  parser::yypgoto_[] =
  {
    -263,  -263,  -263,  -263,  -263,  -263,  -263,  -263,  -209,  -120,
    -263,  -263,  -263,   137,  -263,    38,  -263,  -263,  -263,   255,
    -263,  -263,  -263,  -263,  -263,    -4,   116,  -263,   -67,   -87,
       0,  -263,  -263,  -263,    -5,   -17,  -263,  -263,  -263,  -263,
      80,   259,  -263,  -263,  -263,  -263,  -263,  -263,  -263,  -263,
    -263,  -263,   -50,  -263,  -263,  -263,   240,  -263,   236,  -263,
     235,  -263,   239,   242,   246,  -263,  -261,  -263,   167,  -263,
    -263,    35,  -263,   122,  -263,  -263,  -263,  -263,  -263,  -263,
    -200,  -258,  -263,   119,  -237,   127,  -263,  -262,  -263,  -263,
     207,   151,  -145,    71,  -263,   212,   199,  -170,  -263,  -263,
     132,  -263,  -126
  };

  const short
  parser::yydefgoto_[] =
  {
      -1,     1,     2,     6,     7,    15,    16,   124,   125,   126,
     127,   128,   129,   207,   261,   262,   130,     8,     9,    85,
      86,    87,    88,    89,    90,    39,    40,    41,    23,    42,
     179,    77,   284,    78,   351,    44,    45,    46,    47,    48,
      49,    50,    51,    52,    53,    93,    54,    55,    56,    57,
      58,    59,    60,    61,    62,   108,    63,   111,    64,   116,
      65,   119,    66,    67,    68,    69,   352,   361,   180,   333,
     244,   303,   304,   181,   182,   183,   184,   185,   186,   187,
     188,   258,   259,   189,   190,   173,   174,   296,   297,   298,
      94,   139,   149,   254,   150,   151,    74,   208,   140,   226,
     255,    95,   209
  };

  const short
  parser::yytable_[] =
  {
      11,    12,   225,   257,   133,   200,   214,   309,    72,   291,
      24,   104,    10,    35,     3,    10,   178,    36,    43,    10,
      24,    10,    10,    24,    10,   123,     4,     5,   123,    10,
      10,   175,    24,    10,   175,    76,    92,   123,   175,   268,
     293,   175,    13,   101,   268,   212,   334,    14,   102,   175,
     103,   212,   147,   210,   212,   202,   210,   142,   191,    10,
     210,   212,   202,   210,    24,   257,   131,   199,   355,   211,
     322,   210,   250,   345,   204,   256,   271,    10,   175,   339,
     268,   204,   154,   155,   167,   323,    17,   340,   358,   178,
     356,   135,   136,   161,    10,    18,   175,    24,   162,   177,
     210,   356,   172,   364,   327,   365,   163,   137,   165,   166,
      21,    22,   328,   175,   359,   360,   212,   215,   210,   318,
     247,   131,    19,   212,   135,   136,   248,   212,   177,   212,
     212,    99,   100,   315,   177,   210,   331,   177,    28,    29,
      30,    31,    73,   223,   177,   224,   202,    20,   249,   202,
      35,   294,    91,    71,    36,   212,   300,   232,    98,   178,
     178,   257,   301,   145,    70,   204,   212,   146,   204,   238,
     239,   202,   177,   200,   245,    35,    76,   247,   212,    36,
     219,   141,   300,   321,   220,   203,   132,   247,   329,   138,
     204,   205,   206,   347,    96,   148,   148,   148,   252,   177,
     212,   263,   212,   200,   277,   202,   177,   120,   245,    97,
     177,   269,   177,   177,   240,   212,    24,    10,   241,   265,
     212,   123,   122,   278,   204,   205,   266,   279,   280,   281,
     282,   283,   287,   109,   110,   289,   288,   178,   177,   290,
     172,   132,   177,   177,   336,   131,   316,   121,   295,   177,
     317,   216,   217,   342,   134,   212,   252,   343,   117,   118,
     308,   177,   212,   148,   212,   143,   311,   212,    97,    10,
     346,   312,    24,    10,   212,   212,   144,   157,   235,   112,
     113,   114,   115,   177,   156,   177,   105,   106,   107,   131,
     131,   -49,   152,   153,    98,   158,   252,   164,   177,   213,
     198,   201,   263,   177,   295,   218,   335,    24,   221,   337,
     228,   233,   229,   230,   231,   227,   338,   234,   253,   131,
     177,   237,   246,   251,   260,   270,   273,   264,    98,   306,
     307,   295,   313,   324,   357,   138,   310,   344,   177,   349,
     350,   354,   363,   243,   330,   177,   267,   177,   160,   362,
     177,   192,   193,   314,   194,    24,    10,   177,   177,   195,
     168,    25,   341,   196,   286,   132,   292,   285,   197,   236,
     276,   325,   302,    26,   242,   175,   253,   243,     0,     0,
      27,   272,     0,   274,   275,    28,    29,    30,    31,    32,
      33,    34,   305,     0,   148,     0,     0,   176,    75,     0,
       0,    36,     0,     0,     0,     0,     0,    37,    38,   132,
     132,     0,     0,     0,     0,     0,   253,     0,     0,     0,
     299,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      24,    10,     0,     0,     0,     0,    25,     0,     0,   132,
       0,     0,     0,   302,    79,    80,    81,    82,    26,     0,
       0,     0,     0,     0,   319,    27,   320,     0,     0,    83,
      28,    29,    30,    31,    32,    33,    34,     0,     0,   326,
       0,     0,    35,     0,   332,     0,    36,    84,     0,     0,
       0,     0,    37,    38,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   348,
       0,     0,     0,     0,     0,     0,   353,     0,   353,    24,
      10,   353,     0,     0,     0,    25,     0,     0,     0,   353,
       0,     0,     0,    79,    80,    81,    82,    26,     0,     0,
       0,     0,     0,     0,    27,     0,     0,     0,    83,    28,
      29,    30,    31,    32,    33,    34,    24,    10,     0,     0,
       0,    35,    25,     0,     0,    36,   159,     0,     0,     0,
       0,    37,    38,     0,    26,     0,     0,     0,     0,     0,
       0,    27,     0,   169,   170,     0,    28,    29,    30,    31,
      32,    33,    34,     0,    24,    10,     0,     0,    35,   171,
      25,     0,    36,     0,     0,     0,     0,     0,    37,    38,
       0,     0,    26,     0,     0,     0,     0,     0,     0,    27,
       0,   169,   170,     0,    28,    29,    30,    31,    32,    33,
      34,    24,    10,     0,     0,     0,    35,    25,     0,     0,
      36,     0,     0,     0,     0,     0,    37,    38,     0,    26,
       0,     0,     0,     0,     0,     0,    27,     0,     0,     0,
       0,    28,    29,    30,    31,    32,    33,    34,     0,    24,
      10,     0,     0,    35,    75,    25,     0,    36,     0,     0,
       0,     0,     0,    37,    38,     0,     0,    26,     0,   175,
       0,     0,     0,     0,    27,     0,     0,     0,     0,    28,
      29,    30,    31,    32,    33,    34,    24,    10,     0,     0,
       0,   176,    25,     0,     0,    36,     0,     0,     0,     0,
       0,    37,    38,     0,    26,     0,     0,     0,     0,     0,
       0,    27,     0,     0,     0,     0,    28,    29,    30,    31,
      32,    33,    34,     0,    24,    10,     0,     0,    35,   222,
      25,     0,    36,     0,     0,     0,     0,     0,    37,    38,
       0,     0,    26,     0,     0,     0,     0,     0,     0,    27,
       0,     0,     0,     0,    28,    29,    30,    31,    32,    33,
      34,    24,     0,     0,     0,     0,    35,    25,     0,     0,
      36,     0,     0,     0,     0,     0,    37,    38,     0,    26,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    28,    29,    30,    31,    32,    33,    34,     0,     0,
       0,     0,     0,    35,     0,     0,     0,    36
  };

  const short
  parser::yycheck_[] =
  {
       4,     5,   147,   203,    71,   125,   132,   265,    25,   246,
       3,    61,     4,    45,     0,     4,   103,    49,    18,     4,
       3,     4,     4,     3,     4,     8,    14,    15,     8,     4,
       4,    23,     3,     4,    23,    35,    36,     8,    23,   209,
     249,    23,    43,    40,   214,   132,   308,     7,    45,    23,
      47,   138,    45,    45,   141,    47,    45,    74,   108,     4,
      45,   148,    47,    45,     3,   265,    70,    50,    50,    61,
      50,    45,   198,   335,    66,    49,    61,     4,    23,    50,
     250,    66,    82,    83,   101,   294,    16,   324,    44,   176,
     351,    30,    31,    93,     4,    16,    23,     3,    42,   103,
      45,   362,   102,   361,    42,    50,    50,    46,     3,     4,
      38,    39,    50,    23,    70,    71,   203,   134,    45,    46,
      42,   125,     4,   210,    30,    31,    48,   214,   132,   216,
     217,    38,    39,   278,   138,    45,    46,   141,    33,    34,
      35,    36,    45,   143,   148,   145,    47,    43,    49,    47,
      45,    49,    36,    24,    49,   242,    42,   157,    42,   246,
     247,   361,    48,    42,    49,    66,   253,    46,    66,   169,
     170,    47,   176,   293,   178,    45,   176,    42,   265,    49,
      42,    51,    42,    48,    46,    61,    70,    42,    48,    73,
      66,    67,    68,    48,    41,    79,    80,    81,   202,   203,
     287,   205,   289,   323,   221,    47,   210,    25,   212,     3,
     214,   211,   216,   217,    42,   302,     3,     4,    46,    61,
     307,     8,    27,    42,    66,    67,    68,    46,   228,   229,
     230,   231,    42,    55,    56,    42,    46,   324,   242,    46,
     240,   125,   246,   247,   311,   249,    42,    26,   252,   253,
      46,   135,   136,    42,    10,   342,   260,    46,    62,    63,
     264,   265,   349,   147,   351,    42,   270,   354,     3,     4,
     337,   271,     3,     4,   361,   362,    46,    61,   162,    57,
      58,    59,    60,   287,    43,   289,    52,    53,    54,   293,
     294,    41,    80,    81,   178,    50,   300,    41,   302,   132,
       4,    43,   306,   307,   308,   138,   310,     3,   141,   313,
      61,    43,    61,    61,    61,   148,   316,    50,   202,   323,
     324,    45,    47,    43,    47,    16,    11,    57,   212,    67,
      45,   335,    16,    47,    43,   219,    57,    59,   342,    49,
      59,    49,    43,   176,   306,   349,   209,   351,    93,   354,
     354,   111,   116,   273,   119,     3,     4,   361,   362,   120,
     101,     9,   327,   121,   242,   249,   247,   240,   122,   162,
     219,   300,   256,    21,   175,    23,   260,   210,    -1,    -1,
      28,   214,    -1,   216,   217,    33,    34,    35,    36,    37,
      38,    39,   260,    -1,   278,    -1,    -1,    45,    46,    -1,
      -1,    49,    -1,    -1,    -1,    -1,    -1,    55,    56,   293,
     294,    -1,    -1,    -1,    -1,    -1,   300,    -1,    -1,    -1,
     253,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
       3,     4,    -1,    -1,    -1,    -1,     9,    -1,    -1,   323,
      -1,    -1,    -1,   327,    17,    18,    19,    20,    21,    -1,
      -1,    -1,    -1,    -1,   287,    28,   289,    -1,    -1,    32,
      33,    34,    35,    36,    37,    38,    39,    -1,    -1,   302,
      -1,    -1,    45,    -1,   307,    -1,    49,    50,    -1,    -1,
      -1,    -1,    55,    56,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   342,
      -1,    -1,    -1,    -1,    -1,    -1,   349,    -1,   351,     3,
       4,   354,    -1,    -1,    -1,     9,    -1,    -1,    -1,   362,
      -1,    -1,    -1,    17,    18,    19,    20,    21,    -1,    -1,
      -1,    -1,    -1,    -1,    28,    -1,    -1,    -1,    32,    33,
      34,    35,    36,    37,    38,    39,     3,     4,    -1,    -1,
      -1,    45,     9,    -1,    -1,    49,    50,    -1,    -1,    -1,
      -1,    55,    56,    -1,    21,    -1,    -1,    -1,    -1,    -1,
      -1,    28,    -1,    30,    31,    -1,    33,    34,    35,    36,
      37,    38,    39,    -1,     3,     4,    -1,    -1,    45,    46,
       9,    -1,    49,    -1,    -1,    -1,    -1,    -1,    55,    56,
      -1,    -1,    21,    -1,    -1,    -1,    -1,    -1,    -1,    28,
      -1,    30,    31,    -1,    33,    34,    35,    36,    37,    38,
      39,     3,     4,    -1,    -1,    -1,    45,     9,    -1,    -1,
      49,    -1,    -1,    -1,    -1,    -1,    55,    56,    -1,    21,
      -1,    -1,    -1,    -1,    -1,    -1,    28,    -1,    -1,    -1,
      -1,    33,    34,    35,    36,    37,    38,    39,    -1,     3,
       4,    -1,    -1,    45,    46,     9,    -1,    49,    -1,    -1,
      -1,    -1,    -1,    55,    56,    -1,    -1,    21,    -1,    23,
      -1,    -1,    -1,    -1,    28,    -1,    -1,    -1,    -1,    33,
      34,    35,    36,    37,    38,    39,     3,     4,    -1,    -1,
      -1,    45,     9,    -1,    -1,    49,    -1,    -1,    -1,    -1,
      -1,    55,    56,    -1,    21,    -1,    -1,    -1,    -1,    -1,
      -1,    28,    -1,    -1,    -1,    -1,    33,    34,    35,    36,
      37,    38,    39,    -1,     3,     4,    -1,    -1,    45,    46,
       9,    -1,    49,    -1,    -1,    -1,    -1,    -1,    55,    56,
      -1,    -1,    21,    -1,    -1,    -1,    -1,    -1,    -1,    28,
      -1,    -1,    -1,    -1,    33,    34,    35,    36,    37,    38,
      39,     3,    -1,    -1,    -1,    -1,    45,     9,    -1,    -1,
      49,    -1,    -1,    -1,    -1,    -1,    55,    56,    -1,    21,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    33,    34,    35,    36,    37,    38,    39,    -1,    -1,
      -1,    -1,    -1,    45,    -1,    -1,    -1,    49
  };

  const unsigned char
  parser::yystos_[] =
  {
       0,    74,    75,     0,    14,    15,    76,    77,    90,    91,
       4,    98,    98,    43,     7,    78,    79,    16,    16,     4,
      43,    38,    39,   101,     3,     9,    21,    28,    33,    34,
      35,    36,    37,    38,    39,    45,    49,    55,    56,    98,
      99,   100,   102,   103,   108,   109,   110,   111,   112,   113,
     114,   115,   116,   117,   119,   120,   121,   122,   123,   124,
     125,   126,   127,   129,   131,   133,   135,   136,   137,   138,
      49,    24,   108,    45,   169,    46,   103,   104,   106,    17,
      18,    19,    20,    32,    50,    92,    93,    94,    95,    96,
      97,    99,   103,   118,   163,   174,    41,     3,    99,    38,
      39,    40,    45,    47,   125,    52,    53,    54,   128,    55,
      56,   130,    57,    58,    59,    60,   132,    62,    63,   134,
      25,    26,    27,     8,    80,    81,    82,    83,    84,    85,
      89,    98,    99,   101,    10,    30,    31,    46,    99,   164,
     171,    51,   108,    42,    46,    42,    46,    45,    99,   165,
     167,   168,   168,   168,   103,   103,    43,    61,    50,    50,
      92,   103,    42,    50,    41,     3,     4,   108,   114,    30,
      31,    46,   103,   158,   159,    23,    45,    98,   102,   103,
     141,   146,   147,   148,   149,   150,   151,   152,   153,   156,
     157,   125,   129,   131,   133,   135,   136,   137,     4,    50,
      82,    43,    47,    61,    66,    67,    68,    86,   170,   175,
      45,    61,   102,   141,   175,   108,    99,    99,   141,    42,
      46,   141,    46,   103,   103,   165,   172,   141,    61,    61,
      61,    61,   103,    43,    50,    99,   163,    45,   103,   103,
      42,    46,   169,   141,   143,    98,    47,    42,    48,    49,
     175,    43,    98,    99,   166,   173,    49,   153,   154,   155,
      47,    87,    88,    98,    57,    61,    68,    86,   170,   103,
      16,    61,   141,    11,   141,   141,   164,   108,    42,    46,
     103,   103,   103,   103,   105,   158,   146,    42,    46,    42,
      46,   157,   156,    81,    49,    98,   160,   161,   162,   141,
      42,    48,    99,   144,   145,   173,    67,    45,    98,   154,
      57,    98,   103,    16,   113,   165,    42,    46,    46,   141,
     141,    48,    50,    81,    47,   166,   141,    42,    50,    48,
      88,    46,   141,   142,   160,    98,   101,    98,   103,    50,
     157,   144,    42,    46,    59,   160,   101,    48,   141,    49,
      59,   107,   139,   141,    49,    50,   139,    43,    44,    70,
      71,   140,   107,    43,   154,    50
  };

  const unsigned char
  parser::yyr1_[] =
  {
       0,    73,    74,    75,    75,    76,    76,    77,    77,    78,
      79,    80,    80,    81,    81,    82,    82,    82,    82,    82,
      83,    83,    83,    83,    84,    84,    85,    85,    86,    87,
      87,    88,    88,    88,    89,    89,    90,    91,    92,    92,
      92,    92,    92,    93,    94,    95,    96,    97,    98,    99,
     100,   101,   101,   102,   102,   103,   104,   105,   105,   106,
     106,   107,   107,   108,   108,   108,   108,   108,   109,   109,
     110,   111,   111,   112,   113,   113,   113,   113,   113,   113,
     113,   114,   114,   114,   114,   115,   115,   115,   115,   116,
     116,   117,   117,   117,   118,   118,   119,   119,   120,   120,
     120,   120,   120,   121,   122,   122,   123,   123,   123,   124,
     124,   125,   125,   126,   126,   126,   127,   128,   128,   128,
     129,   129,   130,   130,   131,   131,   132,   132,   132,   132,
     133,   133,   134,   134,   135,   135,   136,   136,   137,   137,
     138,   138,   139,   140,   140,   140,   141,   142,   142,   143,
     143,   144,   145,   145,   146,   146,   146,   146,   146,   147,
     148,   148,   149,   150,   151,   151,   152,   153,   154,   154,
     155,   156,   156,   157,   157,   158,   158,   158,   159,   159,
     160,   161,   162,   162,   163,   164,   164,   164,   165,   165,
     166,   166,   167,   168,   168,   169,   169,   170,   170,   171,
     171,   172,   172,   173,   173,   174,   174,   175,   175
  };

  const signed char
  parser::yyr2_[] =
  {
       0,     2,     2,     0,     3,     1,     1,     0,     3,     1,
       5,     5,     6,     2,     3,     1,     1,     1,     1,     1,
       3,     4,     5,     6,     3,     4,     2,     3,     2,     1,
       3,     1,     3,     4,     9,    10,     6,     4,     1,     1,
       1,     1,     1,     4,     4,     4,     4,     2,     1,     1,
       1,     1,     1,     2,     3,     1,     1,     0,     3,     3,
       3,     2,     3,     1,     1,     1,     1,     1,     2,     2,
       3,     4,     3,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     2,     2,     4,
       6,     3,     3,     4,     2,     3,     3,     5,     1,     1,
       1,     1,     1,     4,     3,     4,     3,     6,     2,     3,
       3,     1,     2,     1,     1,     1,     1,     1,     1,     1,
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
  "\"discard\"", "\"42\"", "\"0x2a\"", "\"42u\"", "\"0x2Au\"", "\"4.2\"",
  "\"\\\"dq-string-literal\\\"\"", "\"'sq-string-literal'\"", "\".\"",
  "\":\"", "\",\"", "\";\"", "\"::\"", "\"(\"", "\")\"", "\"[\"", "\"]\"",
  "\"{\"", "\"}\"", "\"->\"", "\"*\"", "\"/\"", "\"%\"", "\"+\"", "\"-\"",
  "\"<\"", "\"<=\"", "\">\"", "\">=\"", "\"=\"", "\"==\"", "\"!=\"",
  "\"^\"", "\"&\"", "\"!\"", "\"|\"", "\":-\"", "\"EOS\"", "\":<\"",
  "\">:\"", "\"<null>\"", "$accept", "script", "script_head",
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
       0,   289,   289,   297,   298,   301,   302,   306,   307,   310,
     318,   321,   322,   325,   326,   334,   335,   336,   337,   338,
     341,   342,   343,   344,   347,   348,   351,   352,   355,   358,
     359,   362,   363,   364,   367,   370,   376,   379,   383,   384,
     385,   386,   387,   390,   393,   396,   399,   402,   409,   410,
     412,   415,   416,   419,   420,   427,   430,   434,   435,   438,
     439,   442,   443,   447,   448,   449,   450,   451,   454,   455,
     458,   461,   462,   465,   468,   469,   470,   471,   472,   473,
     474,   477,   478,   479,   480,   483,   484,   485,   486,   489,
     490,   493,   494,   495,   498,   499,   502,   503,   507,   508,
     509,   510,   511,   514,   517,   518,   521,   522,   523,   526,
     527,   531,   532,   535,   536,   537,   541,   544,   545,   546,
     549,   550,   553,   554,   557,   558,   561,   562,   563,   564,
     567,   568,   571,   572,   575,   576,   579,   580,   583,   584,
     587,   588,   592,   595,   596,   597,   605,   608,   609,   612,
     613,   617,   620,   621,   625,   626,   627,   628,   629,   632,
     635,   636,   639,   642,   646,   647,   650,   654,   658,   659,
     662,   665,   666,   669,   670,   672,   673,   674,   677,   678,
     688,   691,   694,   695,   703,   706,   707,   708,   711,   712,
     715,   716,   720,   724,   725,   728,   729,   732,   733,   737,
     738,   741,   742,   745,   746,   749,   750,   754,   755
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

#line 19 "parser.yy"
} } // pdm::parser
#line 4240 "parser.tab.cc"

#line 758 "parser.yy"


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
