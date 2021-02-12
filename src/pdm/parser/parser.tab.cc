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
#line 2244 "parser.tab.cc"
    break;

  case 3: // script_head: %empty
#line 297 "parser.yy"
                                                { yylhs.value.as < std::vector<pdm::ast::Stmt*> > ().reserve(16); }
#line 2250 "parser.tab.cc"
    break;

  case 4: // script_head: script_head script_head_stmt ";"
#line 298 "parser.yy"
                                                { yylhs.value.as < std::vector<pdm::ast::Stmt*> > () = std::move(yystack_[2].value.as < std::vector<pdm::ast::Stmt*> > ()); yylhs.value.as < std::vector<pdm::ast::Stmt*> > ().push_back(yystack_[1].value.as < pdm::ast::Stmt* > ()); }
#line 2256 "parser.tab.cc"
    break;

  case 5: // script_head_stmt: import_stmt
#line 301 "parser.yy"
      { yylhs.value.as < pdm::ast::Stmt* > () = yystack_[0].value.as < pdm::ast::Stmt* > (); }
#line 2262 "parser.tab.cc"
    break;

  case 6: // script_head_stmt: extern_stmt
#line 302 "parser.yy"
      { yylhs.value.as < pdm::ast::Stmt* > () = yystack_[0].value.as < pdm::ast::Stmt* > (); }
#line 2268 "parser.tab.cc"
    break;

  case 7: // script_body: %empty
#line 306 "parser.yy"
                                              { yylhs.value.as < std::vector<pdm::ast::ModStmt*> > ().reserve(16); }
#line 2274 "parser.tab.cc"
    break;

  case 8: // script_body: script_body script_body_stmt ";"
#line 307 "parser.yy"
                                              { yylhs.value.as < std::vector<pdm::ast::ModStmt*> > () = std::move(yystack_[2].value.as < std::vector<pdm::ast::ModStmt*> > ()); yylhs.value.as < std::vector<pdm::ast::ModStmt*> > ().push_back(yystack_[1].value.as < pdm::ast::ModStmt* > ()); }
#line 2280 "parser.tab.cc"
    break;

  case 9: // script_body_stmt: top_mod_stmt
#line 310 "parser.yy"
      { yylhs.value.as < pdm::ast::ModStmt* > () = yystack_[0].value.as < pdm::ast::ModStmt* > (); }
#line 2286 "parser.tab.cc"
    break;

  case 10: // top_mod_stmt: "module" "<TypeId>" "{" mod_content "}"
#line 318 "parser.yy"
                                              { yylhs.value.as < pdm::ast::ModStmt* > () = mgr->new_mod_stmt(yylhs.location, yystack_[3].value.as < TokenInfo > ().ID_intstr, std::move(std::vector<ast::TPattern*>{}), std::move(yystack_[1].value.as < std::vector<pdm::ast::ModContentStmt*> > ())); }
#line 2292 "parser.tab.cc"
    break;

  case 11: // sub_mod_stmt: "sub" "<TypeId>" "{" mod_content "}"
#line 321 "parser.yy"
                                                           { yylhs.value.as < pdm::ast::ModContentStmt* > () = mgr->new_mod_stmt(yylhs.location, yystack_[3].value.as < TokenInfo > ().ID_intstr, std::move(std::vector<ast::TPattern*>{}), std::move(yystack_[1].value.as < std::vector<pdm::ast::ModContentStmt*> > ())); }
#line 2298 "parser.tab.cc"
    break;

  case 12: // sub_mod_stmt: "sub" "<TypeId>" tpattern_seq "{" mod_content "}"
#line 322 "parser.yy"
                                                           { yylhs.value.as < pdm::ast::ModContentStmt* > () = mgr->new_mod_stmt(yylhs.location, yystack_[4].value.as < TokenInfo > ().ID_intstr, std::move(yystack_[3].value.as < std::vector<pdm::ast::TPattern*> > ()), std::move(yystack_[1].value.as < std::vector<pdm::ast::ModContentStmt*> > ())); }
#line 2304 "parser.tab.cc"
    break;

  case 13: // mod_content: mod_content_stmt ";"
#line 325 "parser.yy"
                                                { yylhs.value.as < std::vector<pdm::ast::ModContentStmt*> > ().push_back(yystack_[1].value.as < pdm::ast::ModContentStmt* > ()); }
#line 2310 "parser.tab.cc"
    break;

  case 14: // mod_content: mod_content mod_content_stmt ";"
#line 326 "parser.yy"
                                                { yylhs.value.as < std::vector<pdm::ast::ModContentStmt*> > () = std::move(yystack_[2].value.as < std::vector<pdm::ast::ModContentStmt*> > ()); yylhs.value.as < std::vector<pdm::ast::ModContentStmt*> > ().push_back(yystack_[1].value.as < pdm::ast::ModContentStmt* > ()); }
#line 2316 "parser.tab.cc"
    break;

  case 15: // mod_content_stmt: mod_val_stmt
#line 334 "parser.yy"
      { yylhs.value.as < pdm::ast::ModContentStmt* > () = yystack_[0].value.as < pdm::ast::ModContentStmt* > (); }
#line 2322 "parser.tab.cc"
    break;

  case 16: // mod_content_stmt: mod_type_stmt
#line 335 "parser.yy"
      { yylhs.value.as < pdm::ast::ModContentStmt* > () = yystack_[0].value.as < pdm::ast::ModContentStmt* > (); }
#line 2328 "parser.tab.cc"
    break;

  case 17: // mod_content_stmt: mod_enum_stmt
#line 336 "parser.yy"
      { yylhs.value.as < pdm::ast::ModContentStmt* > () = yystack_[0].value.as < pdm::ast::ModContentStmt* > (); }
#line 2334 "parser.tab.cc"
    break;

  case 18: // mod_content_stmt: mod_typeclass_stmt
#line 337 "parser.yy"
      { yylhs.value.as < pdm::ast::ModContentStmt* > () = yystack_[0].value.as < pdm::ast::ModContentStmt* > (); }
#line 2340 "parser.tab.cc"
    break;

  case 19: // mod_content_stmt: sub_mod_stmt
#line 338 "parser.yy"
      { yylhs.value.as < pdm::ast::ModContentStmt* > () = yystack_[0].value.as < pdm::ast::ModContentStmt* > (); }
#line 2346 "parser.tab.cc"
    break;

  case 20: // mod_val_stmt: vid "=" expr
#line 341 "parser.yy"
                                    { yylhs.value.as < pdm::ast::ModContentStmt* > () = mgr->new_internal_mod_val_stmt(yylhs.location, yystack_[2].value.as < TokenInfo > ().ID_intstr, std::move(std::vector<ast::TPattern*>{}), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2352 "parser.tab.cc"
    break;

  case 21: // mod_val_stmt: vid tpattern_seq "=" expr
#line 342 "parser.yy"
                                    { yylhs.value.as < pdm::ast::ModContentStmt* > () = mgr->new_internal_mod_val_stmt(yylhs.location, yystack_[3].value.as < TokenInfo > ().ID_intstr, std::move(yystack_[2].value.as < std::vector<pdm::ast::TPattern*> > ()), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2358 "parser.tab.cc"
    break;

  case 22: // mod_val_stmt: vid type_spec "from" tid stringl
#line 343 "parser.yy"
                                                      { yylhs.value.as < pdm::ast::ModContentStmt* > () = mgr->new_external_mod_val_stmt(yylhs.location, yystack_[4].value.as < TokenInfo > ().ID_intstr, std::move(std::vector<ast::TPattern*>{}), yystack_[3].value.as < pdm::ast::TypeSpec* > (), yystack_[1].value.as < TokenInfo > ().ID_intstr, *yystack_[0].value.as < TokenInfo > ().String_utf8string); }
#line 2364 "parser.tab.cc"
    break;

  case 23: // mod_val_stmt: vid tpattern_seq type_spec "from" tid stringl
#line 344 "parser.yy"
                                                      { yylhs.value.as < pdm::ast::ModContentStmt* > () = mgr->new_external_mod_val_stmt(yylhs.location, yystack_[5].value.as < TokenInfo > ().ID_intstr, std::move(yystack_[4].value.as < std::vector<pdm::ast::TPattern*> > ()), yystack_[3].value.as < pdm::ast::TypeSpec* > (), yystack_[1].value.as < TokenInfo > ().ID_intstr, *yystack_[0].value.as < TokenInfo > ().String_utf8string); }
#line 2370 "parser.tab.cc"
    break;

  case 24: // mod_type_stmt: tid "=" long_type_spec
#line 347 "parser.yy"
                                             { yylhs.value.as < pdm::ast::ModContentStmt* > () = mgr->new_mod_type_stmt(yylhs.location, yystack_[2].value.as < TokenInfo > ().ID_intstr, std::move(std::vector<ast::TPattern*>{}), yystack_[0].value.as < pdm::ast::TypeSpec* > ()); }
#line 2376 "parser.tab.cc"
    break;

  case 25: // mod_type_stmt: tid tpattern_seq "=" long_type_spec
#line 348 "parser.yy"
                                             { yylhs.value.as < pdm::ast::ModContentStmt* > () = mgr->new_mod_type_stmt(yylhs.location, yystack_[3].value.as < TokenInfo > ().ID_intstr, std::move(yystack_[2].value.as < std::vector<pdm::ast::TPattern*> > ()), yystack_[0].value.as < pdm::ast::TypeSpec* > ()); }
#line 2382 "parser.tab.cc"
    break;

  case 26: // mod_enum_stmt: tid enum_field_pl
#line 351 "parser.yy"
                                        { yylhs.value.as < pdm::ast::ModContentStmt* > () = mgr->new_mod_enum_stmt(yylhs.location, yystack_[1].value.as < TokenInfo > ().ID_intstr, std::move(std::vector<ast::TPattern*>{}), std::move(yystack_[0].value.as < std::vector<pdm::ast::ModEnumStmt::Field*> > ())); }
#line 2388 "parser.tab.cc"
    break;

  case 27: // mod_enum_stmt: tid tpattern_seq enum_field_pl
#line 352 "parser.yy"
                                        { yylhs.value.as < pdm::ast::ModContentStmt* > () = mgr->new_mod_enum_stmt(yylhs.location, yystack_[2].value.as < TokenInfo > ().ID_intstr, std::move(yystack_[1].value.as < std::vector<pdm::ast::TPattern*> > ()), std::move(yystack_[0].value.as < std::vector<pdm::ast::ModEnumStmt::Field*> > ())); }
#line 2394 "parser.tab.cc"
    break;

  case 28: // enum_field_pl: "|" unprefixed_enum_field_pl
#line 355 "parser.yy"
                                    { yylhs.value.as < std::vector<pdm::ast::ModEnumStmt::Field*> > () = std::move(yystack_[0].value.as < std::vector<pdm::ast::ModEnumStmt::Field*> > ()); }
#line 2400 "parser.tab.cc"
    break;

  case 29: // unprefixed_enum_field_pl: enum_field
#line 358 "parser.yy"
                                                { yylhs.value.as < std::vector<pdm::ast::ModEnumStmt::Field*> > ().push_back(yystack_[0].value.as < pdm::ast::ModEnumStmt::Field* > ()); }
#line 2406 "parser.tab.cc"
    break;

  case 30: // unprefixed_enum_field_pl: unprefixed_enum_field_pl "|" enum_field
#line 359 "parser.yy"
                                                { yylhs.value.as < std::vector<pdm::ast::ModEnumStmt::Field*> > () = std::move(yystack_[2].value.as < std::vector<pdm::ast::ModEnumStmt::Field*> > ()); yylhs.value.as < std::vector<pdm::ast::ModEnumStmt::Field*> > ().push_back(yystack_[0].value.as < pdm::ast::ModEnumStmt::Field* > ()); }
#line 2412 "parser.tab.cc"
    break;

  case 31: // enum_field: tid
#line 362 "parser.yy"
                        { yylhs.value.as < pdm::ast::ModEnumStmt::Field* > () = mgr->new_enum_stmt_field(yylhs.location, yystack_[0].value.as < TokenInfo > ().ID_intstr, nullptr); }
#line 2418 "parser.tab.cc"
    break;

  case 32: // enum_field: tid type_spec
#line 363 "parser.yy"
                        { yylhs.value.as < pdm::ast::ModEnumStmt::Field* > () = mgr->new_enum_stmt_field(yylhs.location, yystack_[1].value.as < TokenInfo > ().ID_intstr, yystack_[0].value.as < pdm::ast::TypeSpec* > ()); }
#line 2424 "parser.tab.cc"
    break;

  case 33: // mod_typeclass_stmt: tid ":-" "<" tid class_spec ">" "{" type_query_exp_sl "}"
#line 366 "parser.yy"
                                                                                             { 
        yylhs.value.as < pdm::ast::ModContentStmt* > () = mgr->new_mod_typeclass_stmt(yylhs.location, yystack_[8].value.as < TokenInfo > ().ID_intstr, yystack_[5].value.as < TokenInfo > ().ID_intstr, yystack_[4].value.as < pdm::ast::ClassSpec* > (), std::move(std::vector<ast::TPattern*>{}), std::move(yystack_[1].value.as < std::vector<pdm::ast::TypeQueryExp*> > ())); 
      }
#line 2432 "parser.tab.cc"
    break;

  case 34: // mod_typeclass_stmt: tid tpattern_seq ":-" "<" tid class_spec ">" "{" type_query_exp_sl "}"
#line 369 "parser.yy"
                                                                                             { 
        yylhs.value.as < pdm::ast::ModContentStmt* > () = mgr->new_mod_typeclass_stmt(yylhs.location, yystack_[9].value.as < TokenInfo > ().ID_intstr, yystack_[5].value.as < TokenInfo > ().ID_intstr, yystack_[4].value.as < pdm::ast::ClassSpec* > (), std::move(yystack_[8].value.as < std::vector<pdm::ast::TPattern*> > ()), std::move(yystack_[1].value.as < std::vector<pdm::ast::TypeQueryExp*> > ())); 
      }
#line 2440 "parser.tab.cc"
    break;

  case 35: // import_stmt: "import" tid "from" stringl "type" stringl
#line 375 "parser.yy"
                                                       { yylhs.value.as < pdm::ast::Stmt* > () = mgr->new_import_stmt(yylhs.location, yystack_[4].value.as < TokenInfo > ().ID_intstr, *yystack_[2].value.as < TokenInfo > ().String_utf8string, *yystack_[0].value.as < TokenInfo > ().String_utf8string); }
#line 2446 "parser.tab.cc"
    break;

  case 36: // extern_stmt: "extern" tid "from" expr
#line 378 "parser.yy"
                                    { yylhs.value.as < pdm::ast::Stmt* > () = mgr->new_extern_stmt(yylhs.location, yystack_[2].value.as < TokenInfo > ().ID_intstr, yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2452 "parser.tab.cc"
    break;

  case 37: // chain_prefix_stmt: const_stmt
#line 382 "parser.yy"
      { yylhs.value.as < pdm::ast::Stmt* > () = yystack_[0].value.as < pdm::ast::Stmt* > (); }
#line 2458 "parser.tab.cc"
    break;

  case 38: // chain_prefix_stmt: val_stmt
#line 383 "parser.yy"
      { yylhs.value.as < pdm::ast::Stmt* > () = yystack_[0].value.as < pdm::ast::Stmt* > (); }
#line 2464 "parser.tab.cc"
    break;

  case 39: // chain_prefix_stmt: var_stmt
#line 384 "parser.yy"
      { yylhs.value.as < pdm::ast::Stmt* > () = yystack_[0].value.as < pdm::ast::Stmt* > (); }
#line 2470 "parser.tab.cc"
    break;

  case 40: // chain_prefix_stmt: set_stmt
#line 385 "parser.yy"
      { yylhs.value.as < pdm::ast::Stmt* > () = yystack_[0].value.as < pdm::ast::Stmt* > (); }
#line 2476 "parser.tab.cc"
    break;

  case 41: // chain_prefix_stmt: discard_stmt
#line 386 "parser.yy"
      { yylhs.value.as < pdm::ast::Stmt* > () = yystack_[0].value.as < pdm::ast::Stmt* > (); }
#line 2482 "parser.tab.cc"
    break;

  case 42: // const_stmt: "const" lpattern "=" expr
#line 389 "parser.yy"
                                  { yylhs.value.as < pdm::ast::Stmt* > () = mgr->new_const_stmt(yylhs.location, yystack_[2].value.as < pdm::ast::LPattern* > (), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2488 "parser.tab.cc"
    break;

  case 43: // val_stmt: "val" lpattern "=" expr
#line 392 "parser.yy"
                                  { yylhs.value.as < pdm::ast::Stmt* > () = mgr->new_val_stmt(yylhs.location, yystack_[2].value.as < pdm::ast::LPattern* > (), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2494 "parser.tab.cc"
    break;

  case 44: // var_stmt: "var" lpattern "=" expr
#line 395 "parser.yy"
                                  { yylhs.value.as < pdm::ast::Stmt* > () = mgr->new_var_stmt(yylhs.location, yystack_[2].value.as < pdm::ast::LPattern* > (), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2500 "parser.tab.cc"
    break;

  case 45: // set_stmt: "set" expr "=" expr
#line 398 "parser.yy"
                              { yylhs.value.as < pdm::ast::Stmt* > () = mgr->new_set_stmt(yylhs.location, yystack_[2].value.as < pdm::ast::Exp* > (), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2506 "parser.tab.cc"
    break;

  case 46: // discard_stmt: "discard" expr
#line 401 "parser.yy"
                        { yylhs.value.as < pdm::ast::Stmt* > () = mgr->new_discard_stmt(yylhs.location, yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2512 "parser.tab.cc"
    break;

  case 47: // tid: "<TypeId>"
#line 408 "parser.yy"
     { yylhs.value.as < TokenInfo > () = yystack_[0].value.as < TokenInfo > (); }
#line 2518 "parser.tab.cc"
    break;

  case 48: // vid: "<val_id>"
#line 409 "parser.yy"
     { yylhs.value.as < TokenInfo > () = yystack_[0].value.as < TokenInfo > (); }
#line 2524 "parser.tab.cc"
    break;

  case 49: // floatl: "4.2"
#line 411 "parser.yy"
      { yylhs.value.as < TokenInfo > () = yystack_[0].value.as < TokenInfo > (); }
#line 2530 "parser.tab.cc"
    break;

  case 50: // stringl: "'sq-string-literal'"
#line 414 "parser.yy"
      { yylhs.value.as < TokenInfo > () = yystack_[0].value.as < TokenInfo > (); }
#line 2536 "parser.tab.cc"
    break;

  case 51: // stringl: "\"dq-string-literal\""
#line 415 "parser.yy"
      { yylhs.value.as < TokenInfo > () = yystack_[0].value.as < TokenInfo > (); }
#line 2542 "parser.tab.cc"
    break;

  case 52: // mod_prefix: tid ":"
#line 418 "parser.yy"
                              { yylhs.value.as < std::vector<pdm::intern::String> > ().push_back(yystack_[1].value.as < TokenInfo > ().ID_intstr); }
#line 2548 "parser.tab.cc"
    break;

  case 53: // mod_prefix: mod_prefix vid ":"
#line 419 "parser.yy"
                              { yylhs.value.as < std::vector<pdm::intern::String> > () = std::move(yystack_[2].value.as < std::vector<pdm::intern::String> > ()); }
#line 2554 "parser.tab.cc"
    break;

  case 54: // expr: binary_exp
#line 426 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2560 "parser.tab.cc"
    break;

  case 55: // long_exp: expr
#line 429 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2566 "parser.tab.cc"
    break;

  case 56: // expr_cl2: expr "," expr
#line 437 "parser.yy"
                             { yylhs.value.as < std::vector<pdm::ast::Exp*> > ().reserve(2); yylhs.value.as < std::vector<pdm::ast::Exp*> > ().push_back(yystack_[2].value.as < pdm::ast::Exp* > ()); yylhs.value.as < std::vector<pdm::ast::Exp*> > ().push_back(yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2572 "parser.tab.cc"
    break;

  case 57: // expr_cl2: expr_cl2 "," expr
#line 438 "parser.yy"
                             { yylhs.value.as < std::vector<pdm::ast::Exp*> > () = std::move(yystack_[2].value.as < std::vector<pdm::ast::Exp*> > ()); yylhs.value.as < std::vector<pdm::ast::Exp*> > ().push_back(yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2578 "parser.tab.cc"
    break;

  case 58: // type_query_exp_sl: type_query_exp ";"
#line 441 "parser.yy"
                                       { yylhs.value.as < std::vector<pdm::ast::TypeQueryExp*> > ().push_back(yystack_[1].value.as < pdm::ast::TypeQueryExp* > ()); }
#line 2584 "parser.tab.cc"
    break;

  case 59: // type_query_exp_sl: type_query_exp_sl type_query_exp ";"
#line 442 "parser.yy"
                                                 { yylhs.value.as < std::vector<pdm::ast::TypeQueryExp*> > () = std::move(yystack_[2].value.as < std::vector<pdm::ast::TypeQueryExp*> > ()); yylhs.value.as < std::vector<pdm::ast::TypeQueryExp*> > ().push_back(yystack_[1].value.as < pdm::ast::TypeQueryExp* > ()); }
#line 2590 "parser.tab.cc"
    break;

  case 60: // bracketed_exp: unit_exp
#line 446 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2596 "parser.tab.cc"
    break;

  case 61: // bracketed_exp: paren_exp
#line 447 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2602 "parser.tab.cc"
    break;

  case 62: // bracketed_exp: vtupleExpr
#line 448 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2608 "parser.tab.cc"
    break;

  case 63: // bracketed_exp: vstructExpr
#line 449 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2614 "parser.tab.cc"
    break;

  case 64: // bracketed_exp: chain_exp
#line 450 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2620 "parser.tab.cc"
    break;

  case 65: // unit_exp: "(" ")"
#line 453 "parser.yy"
                        { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_unit_exp(yylhs.location); }
#line 2626 "parser.tab.cc"
    break;

  case 66: // unit_exp: "{" "}"
#line 454 "parser.yy"
                        { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_unit_exp(yylhs.location); }
#line 2632 "parser.tab.cc"
    break;

  case 67: // paren_exp: "(" long_exp ")"
#line 457 "parser.yy"
                              { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_paren_exp(yylhs.location, yystack_[1].value.as < pdm::ast::Exp* > ()); }
#line 2638 "parser.tab.cc"
    break;

  case 68: // vtupleExpr: "(" expr "," ")"
#line 460 "parser.yy"
                                   { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_tuple_exp(yylhs.location, std::move(std::vector(1,yystack_[2].value.as < pdm::ast::Exp* > ()))); }
#line 2644 "parser.tab.cc"
    break;

  case 69: // vtupleExpr: "(" expr_cl2 ")"
#line 461 "parser.yy"
                                   { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_tuple_exp(yylhs.location, std::move(yystack_[1].value.as < std::vector<pdm::ast::Exp*> > ())); }
#line 2650 "parser.tab.cc"
    break;

  case 70: // vstructExpr: "{" struct_exp_field_cl "}"
#line 464 "parser.yy"
                                            { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_struct_exp(yylhs.location, std::move(yystack_[1].value.as < std::vector<pdm::ast::StructExp::Field*> > ())); }
#line 2656 "parser.tab.cc"
    break;

  case 71: // primary_exp: bracketed_exp
#line 467 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2662 "parser.tab.cc"
    break;

  case 72: // primary_exp: vid
#line 468 "parser.yy"
                     { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_id_exp(yylhs.location, yystack_[0].value.as < TokenInfo > ().ID_intstr); }
#line 2668 "parser.tab.cc"
    break;

  case 73: // primary_exp: int_expr
#line 469 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2674 "parser.tab.cc"
    break;

  case 74: // primary_exp: floatl
#line 470 "parser.yy"
                     { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_float_exp(yylhs.location, yystack_[0].value.as < TokenInfo > ().Float); }
#line 2680 "parser.tab.cc"
    break;

  case 75: // primary_exp: stringls
#line 471 "parser.yy"
                     { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_string_exp(yylhs.location, std::move(yystack_[0].value.as < std::vector<pdm::ast::StringExp::Piece> > ())); }
#line 2686 "parser.tab.cc"
    break;

  case 76: // primary_exp: if_exp
#line 472 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2692 "parser.tab.cc"
    break;

  case 77: // primary_exp: lambda_exp
#line 473 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2698 "parser.tab.cc"
    break;

  case 78: // int_expr: "42"
#line 476 "parser.yy"
                { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_int_exp(yylhs.location, yystack_[0].value.as < TokenInfo > ().Int, ast::IntExp::Base::Dec, false); }
#line 2704 "parser.tab.cc"
    break;

  case 79: // int_expr: "0x2a"
#line 477 "parser.yy"
                { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_int_exp(yylhs.location, yystack_[0].value.as < TokenInfo > ().Int, ast::IntExp::Base::Hex, false); }
#line 2710 "parser.tab.cc"
    break;

  case 80: // int_expr: "42u"
#line 478 "parser.yy"
                         { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_int_exp(yylhs.location, yystack_[0].value.as < TokenInfo > ().Int, ast::IntExp::Base::Dec, true); }
#line 2716 "parser.tab.cc"
    break;

  case 81: // int_expr: "0x2Au"
#line 479 "parser.yy"
                         { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_int_exp(yylhs.location, yystack_[0].value.as < TokenInfo > ().Int, ast::IntExp::Base::Hex, true); }
#line 2722 "parser.tab.cc"
    break;

  case 82: // stringls: "'sq-string-literal'"
#line 482 "parser.yy"
                             { yylhs.value.as < std::vector<pdm::ast::StringExp::Piece> > ().emplace_back(yylhs.location, *yystack_[0].value.as < TokenInfo > ().String_utf8string, ast::StringExp::QuoteKind::SingleQuote); }
#line 2728 "parser.tab.cc"
    break;

  case 83: // stringls: "\"dq-string-literal\""
#line 483 "parser.yy"
                             { yylhs.value.as < std::vector<pdm::ast::StringExp::Piece> > ().emplace_back(yylhs.location, *yystack_[0].value.as < TokenInfo > ().String_utf8string, ast::StringExp::QuoteKind::DoubleQuote); }
#line 2734 "parser.tab.cc"
    break;

  case 84: // stringls: stringls "'sq-string-literal'"
#line 484 "parser.yy"
                             { yylhs.value.as < std::vector<pdm::ast::StringExp::Piece> > () = std::move(yystack_[1].value.as < std::vector<pdm::ast::StringExp::Piece> > ()); yylhs.value.as < std::vector<pdm::ast::StringExp::Piece> > ().emplace_back(yystack_[0].location, *yystack_[0].value.as < TokenInfo > ().String_utf8string, ast::StringExp::QuoteKind::SingleQuote); }
#line 2740 "parser.tab.cc"
    break;

  case 85: // stringls: stringls "\"dq-string-literal\""
#line 485 "parser.yy"
                             { yylhs.value.as < std::vector<pdm::ast::StringExp::Piece> > () = std::move(yystack_[1].value.as < std::vector<pdm::ast::StringExp::Piece> > ()); yylhs.value.as < std::vector<pdm::ast::StringExp::Piece> > ().emplace_back(yystack_[0].location, *yystack_[0].value.as < TokenInfo > ().String_utf8string, ast::StringExp::QuoteKind::DoubleQuote); }
#line 2746 "parser.tab.cc"
    break;

  case 86: // if_exp: "if" bracketed_exp "then" bracketed_exp
#line 488 "parser.yy"
                                                                        { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_if_exp(yylhs.location, yystack_[2].value.as < pdm::ast::Exp* > (), yystack_[0].value.as < pdm::ast::Exp* > (), nullptr); }
#line 2752 "parser.tab.cc"
    break;

  case 87: // if_exp: "if" bracketed_exp "then" bracketed_exp "else" primary_exp
#line 489 "parser.yy"
                                                                        { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_if_exp(yylhs.location, yystack_[4].value.as < pdm::ast::Exp* > (), yystack_[2].value.as < pdm::ast::Exp* > (), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2758 "parser.tab.cc"
    break;

  case 88: // chain_exp: "{" expr "}"
#line 492 "parser.yy"
                                          { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_chain_exp(yylhs.location, std::move(std::vector<ast::Stmt*>{}), yystack_[1].value.as < pdm::ast::Exp* > ()); }
#line 2764 "parser.tab.cc"
    break;

  case 89: // chain_exp: "{" chain_prefix "}"
#line 493 "parser.yy"
                                           { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_chain_exp(yylhs.location, std::move(yystack_[1].value.as < std::vector<pdm::ast::Stmt*> > ()), nullptr); }
#line 2770 "parser.tab.cc"
    break;

  case 90: // chain_exp: "{" chain_prefix expr "}"
#line 494 "parser.yy"
                                           { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_chain_exp(yylhs.location, std::move(yystack_[2].value.as < std::vector<pdm::ast::Stmt*> > ()), yystack_[1].value.as < pdm::ast::Exp* > ()); }
#line 2776 "parser.tab.cc"
    break;

  case 91: // chain_prefix: chain_prefix_stmt ";"
#line 497 "parser.yy"
                                               { yylhs.value.as < std::vector<pdm::ast::Stmt*> > ().push_back(yystack_[1].value.as < pdm::ast::Stmt* > ()); }
#line 2782 "parser.tab.cc"
    break;

  case 92: // chain_prefix: chain_prefix chain_prefix_stmt ";"
#line 498 "parser.yy"
                                                { yylhs.value.as < std::vector<pdm::ast::Stmt*> > () = std::move(yystack_[2].value.as < std::vector<pdm::ast::Stmt*> > ()); yylhs.value.as < std::vector<pdm::ast::Stmt*> > ().push_back(yystack_[1].value.as < pdm::ast::Stmt* > ()); }
#line 2788 "parser.tab.cc"
    break;

  case 93: // lambda_exp: "fn" vpattern bracketed_exp
#line 501 "parser.yy"
                                                    { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_lambda_exp(yylhs.location, yystack_[1].value.as < pdm::ast::VPattern* > (), nullptr, yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2794 "parser.tab.cc"
    break;

  case 94: // lambda_exp: "fn" vpattern "->" type_spec bracketed_exp
#line 502 "parser.yy"
                                                     { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_lambda_exp(yylhs.location, yystack_[3].value.as < pdm::ast::VPattern* > (), yystack_[1].value.as < pdm::ast::TypeSpec* > (), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2800 "parser.tab.cc"
    break;

  case 95: // postfix_exp: primary_exp
#line 506 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2806 "parser.tab.cc"
    break;

  case 96: // postfix_exp: tcall_exp
#line 507 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2812 "parser.tab.cc"
    break;

  case 97: // postfix_exp: vcall_exp
#line 508 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2818 "parser.tab.cc"
    break;

  case 98: // postfix_exp: dot_name_exp
#line 509 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2824 "parser.tab.cc"
    break;

  case 99: // postfix_exp: dot_index_exp
#line 510 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2830 "parser.tab.cc"
    break;

  case 100: // tcall_exp: postfix_exp "[" targ_cl "]"
#line 513 "parser.yy"
                                         { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_tcall_exp(yylhs.location, yystack_[3].value.as < pdm::ast::Exp* > (), std::move(yystack_[1].value.as < std::vector<pdm::ast::TArg*> > ())); }
#line 2836 "parser.tab.cc"
    break;

  case 101: // vcall_exp: postfix_exp "(" ")"
#line 516 "parser.yy"
                                            { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_vcall_exp(yylhs.location, yystack_[2].value.as < pdm::ast::Exp* > (), std::move(std::vector<ast::VArg*>{})); }
#line 2842 "parser.tab.cc"
    break;

  case 102: // vcall_exp: postfix_exp "(" varg_cl ")"
#line 517 "parser.yy"
                                            { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_vcall_exp(yylhs.location, yystack_[3].value.as < pdm::ast::Exp* > (), std::move(yystack_[1].value.as < std::vector<pdm::ast::VArg*> > ())); }
#line 2848 "parser.tab.cc"
    break;

  case 103: // dot_name_exp: postfix_exp "." "<val_id>"
#line 520 "parser.yy"
                                                { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_struct_dot_name_exp(yylhs.location, yystack_[2].value.as < pdm::ast::Exp* > (), yystack_[0].value.as < TokenInfo > ().ID_intstr); }
#line 2854 "parser.tab.cc"
    break;

  case 104: // dot_name_exp: type_spec "." "<TypeId>"
#line 521 "parser.yy"
                                                { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_enum_dot_name_exp(yylhs.location, yystack_[2].value.as < pdm::ast::TypeSpec* > (), yystack_[0].value.as < TokenInfo > ().ID_intstr, nullptr); }
#line 2860 "parser.tab.cc"
    break;

  case 105: // dot_name_exp: type_spec "." "<TypeId>" "using" paren_exp
#line 522 "parser.yy"
                                                { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_enum_dot_name_exp(yylhs.location, yystack_[4].value.as < pdm::ast::TypeSpec* > (), yystack_[2].value.as < TokenInfo > ().ID_intstr, yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2866 "parser.tab.cc"
    break;

  case 106: // dot_name_exp: mod_prefix "<val_id>"
#line 523 "parser.yy"
                                                { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_module_dot_exp(yylhs.location, std::move(yystack_[1].value.as < std::vector<pdm::intern::String> > ()), yystack_[0].value.as < TokenInfo > ().ID_intstr); }
#line 2872 "parser.tab.cc"
    break;

  case 107: // dot_index_exp: postfix_exp "." int_expr
#line 526 "parser.yy"
                                    { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_dot_index_exp(yylhs.location, yystack_[2].value.as < pdm::ast::Exp* > (), yystack_[0].value.as < pdm::ast::Exp* > (), ast::DotIndexExp::RhsHint::LhsNotPtr); }
#line 2878 "parser.tab.cc"
    break;

  case 108: // dot_index_exp: postfix_exp "." bracketed_exp
#line 527 "parser.yy"
                                    { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_dot_index_exp(yylhs.location, yystack_[2].value.as < pdm::ast::Exp* > (), yystack_[0].value.as < pdm::ast::Exp* > (), ast::DotIndexExp::RhsHint::LhsNotPtr); }
#line 2884 "parser.tab.cc"
    break;

  case 109: // unary_exp: postfix_exp
#line 531 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2890 "parser.tab.cc"
    break;

  case 110: // unary_exp: unary_op unary_exp
#line 532 "parser.yy"
                             { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_unary_exp(yylhs.location, yystack_[1].value.as < pdm::ast::UnaryOperator > (), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2896 "parser.tab.cc"
    break;

  case 111: // unary_op: "+"
#line 535 "parser.yy"
                 { yylhs.value.as < pdm::ast::UnaryOperator > () = ast::UnaryOperator::Plus; }
#line 2902 "parser.tab.cc"
    break;

  case 112: // unary_op: "-"
#line 536 "parser.yy"
                 { yylhs.value.as < pdm::ast::UnaryOperator > () = ast::UnaryOperator::Minus; }
#line 2908 "parser.tab.cc"
    break;

  case 113: // unary_op: "not"
#line 537 "parser.yy"
                 { yylhs.value.as < pdm::ast::UnaryOperator > () = ast::UnaryOperator::Not; }
#line 2914 "parser.tab.cc"
    break;

  case 114: // binary_exp: or_binary_exp
#line 541 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2920 "parser.tab.cc"
    break;

  case 115: // mul_binary_op: "*"
#line 544 "parser.yy"
                 { yylhs.value.as < pdm::ast::BinaryOperator > () = ast::BinaryOperator::Mul; }
#line 2926 "parser.tab.cc"
    break;

  case 116: // mul_binary_op: "/"
#line 545 "parser.yy"
                 { yylhs.value.as < pdm::ast::BinaryOperator > () = ast::BinaryOperator::Div; }
#line 2932 "parser.tab.cc"
    break;

  case 117: // mul_binary_op: "%"
#line 546 "parser.yy"
                 { yylhs.value.as < pdm::ast::BinaryOperator > () = ast::BinaryOperator::Rem; }
#line 2938 "parser.tab.cc"
    break;

  case 118: // mul_binary_exp: unary_exp
#line 549 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2944 "parser.tab.cc"
    break;

  case 119: // mul_binary_exp: mul_binary_exp mul_binary_op unary_exp
#line 550 "parser.yy"
                                               { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_binary_exp(yylhs.location, yystack_[1].value.as < pdm::ast::BinaryOperator > (), yystack_[2].value.as < pdm::ast::Exp* > (), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2950 "parser.tab.cc"
    break;

  case 120: // add_binary_op: "+"
#line 553 "parser.yy"
             { yylhs.value.as < pdm::ast::BinaryOperator > () = ast::BinaryOperator::Add; }
#line 2956 "parser.tab.cc"
    break;

  case 121: // add_binary_op: "-"
#line 554 "parser.yy"
             { yylhs.value.as < pdm::ast::BinaryOperator > () = ast::BinaryOperator::Subtract; }
#line 2962 "parser.tab.cc"
    break;

  case 122: // add_binary_exp: mul_binary_exp
#line 557 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2968 "parser.tab.cc"
    break;

  case 123: // add_binary_exp: add_binary_exp add_binary_op mul_binary_exp
#line 558 "parser.yy"
                                                    { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_binary_exp(yylhs.location, yystack_[1].value.as < pdm::ast::BinaryOperator > (), yystack_[2].value.as < pdm::ast::Exp* > (), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2974 "parser.tab.cc"
    break;

  case 124: // cmp_binary_op: "<"
#line 561 "parser.yy"
                { yylhs.value.as < pdm::ast::BinaryOperator > () = ast::BinaryOperator::Less; }
#line 2980 "parser.tab.cc"
    break;

  case 125: // cmp_binary_op: "<="
#line 562 "parser.yy"
                { yylhs.value.as < pdm::ast::BinaryOperator > () = ast::BinaryOperator::LessOrEq; }
#line 2986 "parser.tab.cc"
    break;

  case 126: // cmp_binary_op: ">"
#line 563 "parser.yy"
                { yylhs.value.as < pdm::ast::BinaryOperator > () = ast::BinaryOperator::Greater; }
#line 2992 "parser.tab.cc"
    break;

  case 127: // cmp_binary_op: ">="
#line 564 "parser.yy"
                { yylhs.value.as < pdm::ast::BinaryOperator > () = ast::BinaryOperator::GreaterOrEq; }
#line 2998 "parser.tab.cc"
    break;

  case 128: // cmp_binary_exp: add_binary_exp
#line 567 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 3004 "parser.tab.cc"
    break;

  case 129: // cmp_binary_exp: cmp_binary_exp cmp_binary_op add_binary_exp
#line 568 "parser.yy"
                                                    { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_binary_exp(yylhs.location, yystack_[1].value.as < pdm::ast::BinaryOperator > (), yystack_[2].value.as < pdm::ast::Exp* > (), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 3010 "parser.tab.cc"
    break;

  case 130: // eq_binary_op: "=="
#line 571 "parser.yy"
                 { yylhs.value.as < pdm::ast::BinaryOperator > () = ast::BinaryOperator::Equals; }
#line 3016 "parser.tab.cc"
    break;

  case 131: // eq_binary_op: "!="
#line 572 "parser.yy"
                 { yylhs.value.as < pdm::ast::BinaryOperator > () = ast::BinaryOperator::NotEquals; }
#line 3022 "parser.tab.cc"
    break;

  case 132: // eq_binary_exp: cmp_binary_exp
#line 575 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 3028 "parser.tab.cc"
    break;

  case 133: // eq_binary_exp: eq_binary_exp eq_binary_op cmp_binary_exp
#line 576 "parser.yy"
                                                { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_binary_exp(yylhs.location, yystack_[1].value.as < pdm::ast::BinaryOperator > (), yystack_[2].value.as < pdm::ast::Exp* > (), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 3034 "parser.tab.cc"
    break;

  case 134: // and_binary_exp: eq_binary_exp
#line 579 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 3040 "parser.tab.cc"
    break;

  case 135: // and_binary_exp: and_binary_exp "and" eq_binary_exp
#line 580 "parser.yy"
                                           { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_binary_exp(yylhs.location, ast::BinaryOperator::And, yystack_[2].value.as < pdm::ast::Exp* > (), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 3046 "parser.tab.cc"
    break;

  case 136: // xor_binary_exp: and_binary_exp
#line 583 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 3052 "parser.tab.cc"
    break;

  case 137: // xor_binary_exp: xor_binary_exp "xor" and_binary_exp
#line 584 "parser.yy"
                                           { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_binary_exp(yylhs.location, ast::BinaryOperator::XOr, yystack_[2].value.as < pdm::ast::Exp* > (), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 3058 "parser.tab.cc"
    break;

  case 138: // or_binary_exp: xor_binary_exp
#line 587 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 3064 "parser.tab.cc"
    break;

  case 139: // or_binary_exp: or_binary_exp "or" xor_binary_exp
#line 588 "parser.yy"
                                           { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_binary_exp(yylhs.location, ast::BinaryOperator::Or, yystack_[2].value.as < pdm::ast::Exp* > (), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 3070 "parser.tab.cc"
    break;

  case 140: // type_query_exp: type_spec type_query_op long_type_spec
#line 592 "parser.yy"
                                               { yylhs.value.as < pdm::ast::TypeQueryExp* > () = mgr->new_type_query_exp(yylhs.location, yystack_[1].value.as < pdm::ast::TypeQueryKind > (), yystack_[2].value.as < pdm::ast::TypeSpec* > (), yystack_[0].value.as < pdm::ast::TypeSpec* > ()); }
#line 3076 "parser.tab.cc"
    break;

  case 141: // type_query_op: ":<"
#line 595 "parser.yy"
                    { yylhs.value.as < pdm::ast::TypeQueryKind > () = ast::TypeQueryKind::LhsSubtypesRhs; }
#line 3082 "parser.tab.cc"
    break;

  case 142: // type_query_op: ">:"
#line 596 "parser.yy"
                    { yylhs.value.as < pdm::ast::TypeQueryKind > () = ast::TypeQueryKind::LhsSupertypesRhs; }
#line 3088 "parser.tab.cc"
    break;

  case 143: // type_query_op: "::"
#line 597 "parser.yy"
                    { yylhs.value.as < pdm::ast::TypeQueryKind > () = ast::TypeQueryKind::LhsEqualsRhs; }
#line 3094 "parser.tab.cc"
    break;

  case 144: // type_spec: unary_type_spec
#line 605 "parser.yy"
      { yylhs.value.as < pdm::ast::TypeSpec* > () = yystack_[0].value.as < pdm::ast::TypeSpec* > (); }
#line 3100 "parser.tab.cc"
    break;

  case 145: // type_spec_cl2: type_spec "," type_spec
#line 616 "parser.yy"
                                    { yylhs.value.as < std::vector<pdm::ast::TypeSpec*> > ().reserve(2); yylhs.value.as < std::vector<pdm::ast::TypeSpec*> > ().push_back(yystack_[2].value.as < pdm::ast::TypeSpec* > ()); yylhs.value.as < std::vector<pdm::ast::TypeSpec*> > ().push_back(yystack_[0].value.as < pdm::ast::TypeSpec* > ()); }
#line 3106 "parser.tab.cc"
    break;

  case 146: // type_spec_cl2: type_spec_cl2 "," type_spec
#line 617 "parser.yy"
                                    { yylhs.value.as < std::vector<pdm::ast::TypeSpec*> > () = std::move(yystack_[2].value.as < std::vector<pdm::ast::TypeSpec*> > ()); yylhs.value.as < std::vector<pdm::ast::TypeSpec*> > ().push_back(yystack_[0].value.as < pdm::ast::TypeSpec* > ()); }
#line 3112 "parser.tab.cc"
    break;

  case 147: // struct_type_spec_field: vid type_spec
#line 621 "parser.yy"
                                   { yylhs.value.as < pdm::ast::StructTypeSpec::Field* > () = mgr->new_struct_type_spec_field(yylhs.location, yystack_[1].value.as < TokenInfo > ().ID_intstr, yystack_[0].value.as < pdm::ast::TypeSpec* > ()); }
#line 3118 "parser.tab.cc"
    break;

  case 148: // struct_type_spec_field_cl: struct_type_spec_field
#line 624 "parser.yy"
                                                           { yylhs.value.as < std::vector<pdm::ast::StructTypeSpec::Field*> > ().push_back(yystack_[0].value.as < pdm::ast::StructTypeSpec::Field* > ()); }
#line 3124 "parser.tab.cc"
    break;

  case 149: // struct_type_spec_field_cl: struct_type_spec_field_cl "," struct_type_spec_field
#line 625 "parser.yy"
                                                              { yylhs.value.as < std::vector<pdm::ast::StructTypeSpec::Field*> > () = std::move(yystack_[2].value.as < std::vector<pdm::ast::StructTypeSpec::Field*> > ()); yylhs.value.as < std::vector<pdm::ast::StructTypeSpec::Field*> > ().push_back(yystack_[0].value.as < pdm::ast::StructTypeSpec::Field* > ()); }
#line 3130 "parser.tab.cc"
    break;

  case 150: // primary_type_spec: tid
#line 629 "parser.yy"
                        { yylhs.value.as < pdm::ast::TypeSpec* > () = mgr->new_id_type_spec(yylhs.location, yystack_[0].value.as < TokenInfo > ().ID_intstr); }
#line 3136 "parser.tab.cc"
    break;

  case 151: // primary_type_spec: paren_type_spec
#line 630 "parser.yy"
      { yylhs.value.as < pdm::ast::TypeSpec* > () = yystack_[0].value.as < pdm::ast::TypeSpec* > (); }
#line 3142 "parser.tab.cc"
    break;

  case 152: // primary_type_spec: tuple_type_spec
#line 631 "parser.yy"
      { yylhs.value.as < pdm::ast::TypeSpec* > () = yystack_[0].value.as < pdm::ast::TypeSpec* > (); }
#line 3148 "parser.tab.cc"
    break;

  case 153: // primary_type_spec: mod_prefix_tid
#line 632 "parser.yy"
      { yylhs.value.as < pdm::ast::TypeSpec* > () = yystack_[0].value.as < pdm::ast::TypeSpec* > (); }
#line 3154 "parser.tab.cc"
    break;

  case 154: // primary_type_spec: fn_type_spec
#line 633 "parser.yy"
      { yylhs.value.as < pdm::ast::TypeSpec* > () = yystack_[0].value.as < pdm::ast::TypeSpec* > (); }
#line 3160 "parser.tab.cc"
    break;

  case 155: // paren_type_spec: "(" type_spec ")"
#line 636 "parser.yy"
                                 { yylhs.value.as < pdm::ast::TypeSpec* > () = mgr->new_paren_type_spec(yylhs.location, yystack_[1].value.as < pdm::ast::TypeSpec* > ()); }
#line 3166 "parser.tab.cc"
    break;

  case 156: // tuple_type_spec: "(" type_spec "," ")"
#line 639 "parser.yy"
                                     { yylhs.value.as < pdm::ast::TypeSpec* > () = mgr->new_tuple_type_spec(yylhs.location, std::move(std::vector(1,yystack_[2].value.as < pdm::ast::TypeSpec* > ()))); }
#line 3172 "parser.tab.cc"
    break;

  case 157: // tuple_type_spec: "(" type_spec_cl2 ")"
#line 640 "parser.yy"
                                     { yylhs.value.as < pdm::ast::TypeSpec* > () = mgr->new_tuple_type_spec(yylhs.location, std::move(yystack_[1].value.as < std::vector<pdm::ast::TypeSpec*> > ())); }
#line 3178 "parser.tab.cc"
    break;

  case 158: // mod_prefix_tid: mod_prefix tid
#line 643 "parser.yy"
                            { yylhs.value.as < pdm::ast::TypeSpec* > () = mgr->new_dot_name_type_spec_with_mod_prefix(yylhs.location, std::move(yystack_[1].value.as < std::vector<pdm::intern::String> > ()), yystack_[0].value.as < TokenInfo > ().ID_intstr); }
#line 3184 "parser.tab.cc"
    break;

  case 159: // fn_type_spec: "Fn" vpattern primary_type_spec
#line 646 "parser.yy"
                                        { yylhs.value.as < pdm::ast::TypeSpec* > () = mgr->new_fn_type_spec(yylhs.location, std::move(yystack_[1].value.as < pdm::ast::VPattern* > ()), yystack_[0].value.as < pdm::ast::TypeSpec* > ()); }
#line 3190 "parser.tab.cc"
    break;

  case 160: // postfix_type_spec: primary_type_spec
#line 650 "parser.yy"
      { yylhs.value.as < pdm::ast::TypeSpec* > () = yystack_[0].value.as < pdm::ast::TypeSpec* > (); }
#line 3196 "parser.tab.cc"
    break;

  case 161: // postfix_type_spec: tcall_type_spec
#line 651 "parser.yy"
      { yylhs.value.as < pdm::ast::TypeSpec* > () = yystack_[0].value.as < pdm::ast::TypeSpec* > (); }
#line 3202 "parser.tab.cc"
    break;

  case 162: // tcall_type_spec: postfix_type_spec "[" targ_cl "]"
#line 654 "parser.yy"
                                               { yylhs.value.as < pdm::ast::TypeSpec* > () = mgr->new_tcall_type_spec(yylhs.location, yystack_[3].value.as < pdm::ast::TypeSpec* > (), std::move(yystack_[1].value.as < std::vector<pdm::ast::TArg*> > ())); }
#line 3208 "parser.tab.cc"
    break;

  case 163: // unary_type_spec: postfix_type_spec
#line 658 "parser.yy"
      { yylhs.value.as < pdm::ast::TypeSpec* > () = yystack_[0].value.as < pdm::ast::TypeSpec* > (); }
#line 3214 "parser.tab.cc"
    break;

  case 164: // long_type_spec: unary_type_spec
#line 662 "parser.yy"
      { yylhs.value.as < pdm::ast::TypeSpec* > () = yystack_[0].value.as < pdm::ast::TypeSpec* > (); }
#line 3220 "parser.tab.cc"
    break;

  case 165: // long_type_spec: struct_type_spec
#line 663 "parser.yy"
      { yylhs.value.as < pdm::ast::TypeSpec* > () = yystack_[0].value.as < pdm::ast::TypeSpec* > (); }
#line 3226 "parser.tab.cc"
    break;

  case 166: // struct_type_spec: "{" struct_type_spec_field_cl "}"
#line 666 "parser.yy"
                                               { yylhs.value.as < pdm::ast::TypeSpec* > () = mgr->new_struct_type_spec(yylhs.location, std::move(yystack_[1].value.as < std::vector<pdm::ast::StructTypeSpec::Field*> > ())); }
#line 3232 "parser.tab.cc"
    break;

  case 167: // targ: type_spec
#line 669 "parser.yy"
                { yylhs.value.as < pdm::ast::TArg* > () = mgr->new_targ_type_spec(yylhs.location, yystack_[0].value.as < pdm::ast::TypeSpec* > ()); }
#line 3238 "parser.tab.cc"
    break;

  case 168: // targ: expr
#line 670 "parser.yy"
               { yylhs.value.as < pdm::ast::TArg* > () = mgr->new_targ_exp(yylhs.location, yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 3244 "parser.tab.cc"
    break;

  case 169: // targ_cl: targ
#line 673 "parser.yy"
                            { yylhs.value.as < std::vector<pdm::ast::TArg*> > ().push_back(yystack_[0].value.as < pdm::ast::TArg* > ()); }
#line 3250 "parser.tab.cc"
    break;

  case 170: // targ_cl: targ_cl "," targ
#line 674 "parser.yy"
                            { yylhs.value.as < std::vector<pdm::ast::TArg*> > () = std::move(yystack_[2].value.as < std::vector<pdm::ast::TArg*> > ()); yylhs.value.as < std::vector<pdm::ast::TArg*> > ().push_back(yystack_[0].value.as < pdm::ast::TArg* > ()); }
#line 3256 "parser.tab.cc"
    break;

  case 171: // varg: expr
#line 676 "parser.yy"
                            { yylhs.value.as < pdm::ast::VArg* > () = mgr->new_varg(yylhs.location, yystack_[0].value.as < pdm::ast::Exp* > (), ast::VArgAccessSpec::In); }
#line 3262 "parser.tab.cc"
    break;

  case 172: // varg: "out" expr
#line 677 "parser.yy"
                            { yylhs.value.as < pdm::ast::VArg* > () = mgr->new_varg(yylhs.location, yystack_[0].value.as < pdm::ast::Exp* > (), ast::VArgAccessSpec::Out); }
#line 3268 "parser.tab.cc"
    break;

  case 173: // varg: "inout" expr
#line 678 "parser.yy"
                            { yylhs.value.as < pdm::ast::VArg* > () = mgr->new_varg(yylhs.location, yystack_[0].value.as < pdm::ast::Exp* > (), ast::VArgAccessSpec::InOut); }
#line 3274 "parser.tab.cc"
    break;

  case 174: // varg_cl: varg
#line 681 "parser.yy"
                            { yylhs.value.as < std::vector<pdm::ast::VArg*> > ().push_back(yystack_[0].value.as < pdm::ast::VArg* > ()); }
#line 3280 "parser.tab.cc"
    break;

  case 175: // varg_cl: varg_cl "," varg
#line 682 "parser.yy"
                            { yylhs.value.as < std::vector<pdm::ast::VArg*> > () = std::move(yystack_[2].value.as < std::vector<pdm::ast::VArg*> > ()); yylhs.value.as < std::vector<pdm::ast::VArg*> > ().push_back(yystack_[0].value.as < pdm::ast::VArg* > ()); }
#line 3286 "parser.tab.cc"
    break;

  case 176: // class_spec: postfix_class_spec
#line 692 "parser.yy"
      { yylhs.value.as < pdm::ast::ClassSpec* > () = yystack_[0].value.as < pdm::ast::ClassSpec* > (); }
#line 3292 "parser.tab.cc"
    break;

  case 177: // primary_class_spec: tid
#line 695 "parser.yy"
            { yylhs.value.as < pdm::ast::ClassSpec* > () = mgr->new_id_class_spec(yylhs.location, yystack_[0].value.as < TokenInfo > ().ID_intstr); }
#line 3298 "parser.tab.cc"
    break;

  case 178: // postfix_class_spec: primary_class_spec
#line 698 "parser.yy"
      { yylhs.value.as < pdm::ast::ClassSpec* > () = yystack_[0].value.as < pdm::ast::ClassSpec* > (); }
#line 3304 "parser.tab.cc"
    break;

  case 179: // postfix_class_spec: postfix_class_spec "[" targ_cl "]"
#line 699 "parser.yy"
                                                { yylhs.value.as < pdm::ast::ClassSpec* > () = mgr->new_tcall_class_spec(yylhs.location, yystack_[3].value.as < pdm::ast::ClassSpec* > (), std::move(yystack_[1].value.as < std::vector<pdm::ast::TArg*> > ())); }
#line 3310 "parser.tab.cc"
    break;

  case 180: // struct_exp_field: vid "=" expr
#line 707 "parser.yy"
                    { yylhs.value.as < pdm::ast::StructExp::Field* > () = mgr->new_struct_exp_field(yylhs.location, yystack_[2].value.as < TokenInfo > ().ID_intstr, yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 3316 "parser.tab.cc"
    break;

  case 181: // vpattern_field: vid type_spec
#line 710 "parser.yy"
                             { yylhs.value.as < pdm::ast::VPattern::Field* > () = mgr->new_vpattern_field(yylhs.location, yystack_[1].value.as < TokenInfo > ().ID_intstr, yystack_[0].value.as < pdm::ast::TypeSpec* > (), ast::VArgAccessSpec::In); }
#line 3322 "parser.tab.cc"
    break;

  case 182: // vpattern_field: "out" vid type_spec
#line 711 "parser.yy"
                             { yylhs.value.as < pdm::ast::VPattern::Field* > () = mgr->new_vpattern_field(yylhs.location, yystack_[1].value.as < TokenInfo > ().ID_intstr, yystack_[0].value.as < pdm::ast::TypeSpec* > (), ast::VArgAccessSpec::Out); }
#line 3328 "parser.tab.cc"
    break;

  case 183: // vpattern_field: "inout" vid type_spec
#line 712 "parser.yy"
                             { yylhs.value.as < pdm::ast::VPattern::Field* > () = mgr->new_vpattern_field(yylhs.location, yystack_[1].value.as < TokenInfo > ().ID_intstr, yystack_[0].value.as < pdm::ast::TypeSpec* > (), ast::VArgAccessSpec::InOut); }
#line 3334 "parser.tab.cc"
    break;

  case 184: // lpattern_field: vid type_spec
#line 715 "parser.yy"
                     { yylhs.value.as < pdm::ast::LPattern::Field* > () = mgr->new_lpattern_field(yylhs.location, ast::LPattern::FieldKind::IdTypeSpecPair, yystack_[1].value.as < TokenInfo > ().ID_intstr, yystack_[0].value.as < pdm::ast::TypeSpec* > ()); }
#line 3340 "parser.tab.cc"
    break;

  case 185: // lpattern_field: vid
#line 716 "parser.yy"
                    { yylhs.value.as < pdm::ast::LPattern::Field* > () = mgr->new_lpattern_field(yylhs.location, ast::LPattern::FieldKind::IdSingleton, yystack_[0].value.as < TokenInfo > ().ID_intstr); }
#line 3346 "parser.tab.cc"
    break;

  case 186: // tpattern_field: vid type_spec
#line 719 "parser.yy"
                      { yylhs.value.as < pdm::ast::TPattern::Field* > () = mgr->new_tpattern_field(yylhs.location, ast::TPattern::FieldKind::Value, yystack_[1].value.as < TokenInfo > ().ID_intstr, yystack_[0].value.as < pdm::ast::TypeSpec* > ()); }
#line 3352 "parser.tab.cc"
    break;

  case 187: // tpattern_field: tid class_spec
#line 720 "parser.yy"
                      { yylhs.value.as < pdm::ast::TPattern::Field* > () = mgr->new_tpattern_field(yylhs.location, ast::TPattern::FieldKind::Type, yystack_[1].value.as < TokenInfo > ().ID_intstr, yystack_[0].value.as < pdm::ast::ClassSpec* > ()); }
#line 3358 "parser.tab.cc"
    break;

  case 188: // destructured_lpattern: "(" lpattern_field_cl ")"
#line 724 "parser.yy"
                                          { yylhs.value.as < pdm::ast::LPattern* > () = mgr->new_lpattern(yylhs.location, std::move(yystack_[1].value.as < std::vector<pdm::ast::LPattern::Field*> > ()), true); }
#line 3364 "parser.tab.cc"
    break;

  case 189: // lpattern: lpattern_field
#line 728 "parser.yy"
                        { yylhs.value.as < pdm::ast::LPattern* > () = mgr->new_lpattern(yylhs.location, std::move(std::vector<ast::LPattern::Field*>{1,yystack_[0].value.as < pdm::ast::LPattern::Field* > ()}), false); }
#line 3370 "parser.tab.cc"
    break;

  case 190: // lpattern: destructured_lpattern
#line 729 "parser.yy"
      { yylhs.value.as < pdm::ast::LPattern* > () = yystack_[0].value.as < pdm::ast::LPattern* > (); }
#line 3376 "parser.tab.cc"
    break;

  case 191: // vpattern: "(" vpattern_field_cl ")"
#line 732 "parser.yy"
                                       { yylhs.value.as < pdm::ast::VPattern* > () = mgr->new_vpattern(yylhs.location, std::move(yystack_[1].value.as < std::vector<pdm::ast::VPattern::Field*> > ())); }
#line 3382 "parser.tab.cc"
    break;

  case 192: // vpattern: "(" ")"
#line 733 "parser.yy"
                                       { yylhs.value.as < pdm::ast::VPattern* > () = mgr->new_vpattern(yylhs.location, std::move(std::vector<ast::VPattern::Field*>{})); }
#line 3388 "parser.tab.cc"
    break;

  case 193: // tpattern: "[" tpattern_field_cl "]"
#line 736 "parser.yy"
                                               { yylhs.value.as < pdm::ast::TPattern* > () = mgr->new_tpattern(yylhs.location, std::move(yystack_[1].value.as < std::vector<pdm::ast::TPattern::Field*> > ()), false); }
#line 3394 "parser.tab.cc"
    break;

  case 194: // tpattern: "!" "[" tpattern_field_cl "]"
#line 737 "parser.yy"
                                               { yylhs.value.as < pdm::ast::TPattern* > () = mgr->new_tpattern(yylhs.location, std::move(yystack_[1].value.as < std::vector<pdm::ast::TPattern::Field*> > ()), true); }
#line 3400 "parser.tab.cc"
    break;

  case 195: // vpattern_field_cl: vpattern_field
#line 741 "parser.yy"
                                              { yylhs.value.as < std::vector<pdm::ast::VPattern::Field*> > ().push_back(yystack_[0].value.as < pdm::ast::VPattern::Field* > ()); }
#line 3406 "parser.tab.cc"
    break;

  case 196: // vpattern_field_cl: vpattern_field_cl "," vpattern_field
#line 742 "parser.yy"
                                               { yylhs.value.as < std::vector<pdm::ast::VPattern::Field*> > () = std::move(yystack_[2].value.as < std::vector<pdm::ast::VPattern::Field*> > ()); yylhs.value.as < std::vector<pdm::ast::VPattern::Field*> > ().push_back(yystack_[0].value.as < pdm::ast::VPattern::Field* > ()); }
#line 3412 "parser.tab.cc"
    break;

  case 197: // lpattern_field_cl: lpattern_field
#line 745 "parser.yy"
                                              { yylhs.value.as < std::vector<pdm::ast::LPattern::Field*> > ().push_back(yystack_[0].value.as < pdm::ast::LPattern::Field* > ()); }
#line 3418 "parser.tab.cc"
    break;

  case 198: // lpattern_field_cl: lpattern_field_cl "," lpattern_field
#line 746 "parser.yy"
                                               { yylhs.value.as < std::vector<pdm::ast::LPattern::Field*> > () = std::move(yystack_[2].value.as < std::vector<pdm::ast::LPattern::Field*> > ()); yylhs.value.as < std::vector<pdm::ast::LPattern::Field*> > ().push_back(yystack_[0].value.as < pdm::ast::LPattern::Field* > ()); }
#line 3424 "parser.tab.cc"
    break;

  case 199: // tpattern_field_cl: tpattern_field
#line 749 "parser.yy"
                                              { yylhs.value.as < std::vector<pdm::ast::TPattern::Field*> > ().push_back(yystack_[0].value.as < pdm::ast::TPattern::Field* > ()); }
#line 3430 "parser.tab.cc"
    break;

  case 200: // tpattern_field_cl: tpattern_field_cl "," tpattern_field
#line 750 "parser.yy"
                                               { yylhs.value.as < std::vector<pdm::ast::TPattern::Field*> > () = std::move(yystack_[2].value.as < std::vector<pdm::ast::TPattern::Field*> > ()); yylhs.value.as < std::vector<pdm::ast::TPattern::Field*> > ().push_back(yystack_[0].value.as < pdm::ast::TPattern::Field* > ()); }
#line 3436 "parser.tab.cc"
    break;

  case 201: // struct_exp_field_cl: struct_exp_field
#line 753 "parser.yy"
                                                    { yylhs.value.as < std::vector<pdm::ast::StructExp::Field*> > ().push_back(yystack_[0].value.as < pdm::ast::StructExp::Field* > ()); }
#line 3442 "parser.tab.cc"
    break;

  case 202: // struct_exp_field_cl: struct_exp_field_cl "," struct_exp_field
#line 754 "parser.yy"
                                                    { yylhs.value.as < std::vector<pdm::ast::StructExp::Field*> > () = std::move(yystack_[2].value.as < std::vector<pdm::ast::StructExp::Field*> > ()); yylhs.value.as < std::vector<pdm::ast::StructExp::Field*> > ().push_back(yystack_[0].value.as < pdm::ast::StructExp::Field* > ()); }
#line 3448 "parser.tab.cc"
    break;

  case 203: // tpattern_seq: tpattern
#line 758 "parser.yy"
                             { yylhs.value.as < std::vector<pdm::ast::TPattern*> > ().push_back(yystack_[0].value.as < pdm::ast::TPattern* > ()); }
#line 3454 "parser.tab.cc"
    break;

  case 204: // tpattern_seq: tpattern_seq tpattern
#line 759 "parser.yy"
                             { yylhs.value.as < std::vector<pdm::ast::TPattern*> > () = std::move(yystack_[1].value.as < std::vector<pdm::ast::TPattern*> > ()); yylhs.value.as < std::vector<pdm::ast::TPattern*> > ().push_back(yystack_[0].value.as < pdm::ast::TPattern* > ()); }
#line 3460 "parser.tab.cc"
    break;


#line 3464 "parser.tab.cc"

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





  const short parser::yypact_ninf_ = -305;

  const signed char parser::yytable_ninf_ = -49;

  const short
  parser::yypact_[] =
  {
    -305,    24,   129,  -305,    30,    30,    -7,    39,  -305,  -305,
    -305,    82,    90,  -305,    51,    65,  -305,   177,   624,    72,
    -305,  -305,  -305,   132,  -305,   122,    69,    69,  -305,  -305,
    -305,  -305,  -305,  -305,  -305,  -305,   548,   393,  -305,  -305,
      95,  -305,  -305,   226,  -305,  -305,  -305,  -305,  -305,  -305,
    -305,  -305,   196,  -305,  -305,  -305,    85,  -305,  -305,  -305,
    -305,  -305,   624,  -305,   130,   119,   191,   178,   139,   165,
     167,   168,  -305,  -305,  -305,  -305,  -305,   184,  -305,  -305,
     194,   177,   548,   195,    59,   136,    89,  -305,   176,   180,
     158,    87,   161,    46,    46,    46,   624,   624,  -305,   203,
    -305,  -305,  -305,  -305,  -305,   197,   189,   436,  -305,     8,
    -305,   211,  -305,   219,  -305,  -305,    66,   473,   624,  -305,
    -305,  -305,  -305,   624,  -305,  -305,   624,  -305,  -305,  -305,
    -305,   624,  -305,  -305,   624,   624,   624,   624,   258,   624,
     259,  -305,    11,   221,  -305,  -305,  -305,  -305,   102,     6,
    -305,   122,   262,   262,  -305,    89,  -305,   164,    89,  -305,
      89,   241,  -305,   586,  -305,   624,  -305,    36,  -305,    89,
    -305,   262,    89,  -305,  -305,   205,   208,   213,   214,  -305,
    -305,   624,  -305,  -305,   229,   228,   262,  -305,  -305,  -305,
    -305,  -305,   624,   624,  -305,  -305,  -305,   171,  -305,   168,
    -305,   -15,  -305,   130,   119,   191,   178,   139,   165,   273,
      -5,   -21,  -305,   240,  -305,   241,    64,   237,    30,   230,
    -305,  -305,   112,   624,   269,     9,   275,    89,    89,  -305,
     115,  -305,   122,   179,  -305,  -305,  -305,  -305,  -305,  -305,
    -305,   181,  -305,   624,   624,   624,   624,  -305,  -305,  -305,
     197,  -305,  -305,  -305,   511,  -305,   624,  -305,   243,  -305,
     194,    73,  -305,    30,    89,  -305,   106,   262,  -305,  -305,
    -305,   241,   222,  -305,    89,    30,    64,   233,  -305,  -305,
    -305,    30,   624,   276,   316,  -305,  -305,  -305,  -305,   262,
    -305,  -305,  -305,  -305,  -305,  -305,  -305,   624,  -305,    14,
     194,  -305,  -305,  -305,   244,  -305,   241,  -305,    89,  -305,
      53,   124,    30,  -305,    30,  -305,    30,   177,  -305,    30,
    -305,  -305,  -305,  -305,    27,   624,  -305,  -305,   262,  -305,
    -305,  -305,   235,    30,  -305,   177,  -305,   144,  -305,   249,
     242,  -305,  -305,    89,   250,    21,   257,   -23,    89,  -305,
     261,  -305,  -305,  -305,  -305,    64,    34,  -305,  -305,  -305
  };

  const unsigned char
  parser::yydefact_[] =
  {
       3,     0,     7,     1,     0,     0,     0,     2,     5,     6,
      47,     0,     0,     4,     0,     0,     9,     0,     0,     0,
       8,    51,    50,     0,    48,     0,     0,     0,   113,    78,
      79,    80,    81,    49,    83,    82,     0,     0,   111,   112,
     150,    72,    74,     0,    36,    71,    60,    61,    62,    63,
      95,    73,    75,    76,    64,    77,   109,    96,    97,    98,
      99,   118,     0,    54,   122,   128,   132,   134,   136,   138,
     114,     0,   160,   151,   152,   153,   154,   163,   161,   144,
       0,     0,     0,     0,     0,     0,     0,    65,    55,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    66,     0,
      37,    38,    39,    40,    41,    72,     0,     0,   201,     0,
      52,   106,   158,     0,    85,    84,     0,     0,     0,   110,
     115,   116,   117,     0,   120,   121,     0,   124,   125,   126,
     127,     0,   130,   131,     0,     0,     0,     0,     0,     0,
       0,    19,     0,     0,    15,    16,    17,    18,     0,     0,
      35,     0,     0,     0,   192,     0,   195,     0,     0,    93,
       0,     0,   159,     0,    67,     0,    69,     0,   155,     0,
     157,     0,   185,   189,   190,     0,     0,     0,     0,    46,
      91,     0,    88,    89,     0,     0,     0,    70,    53,   103,
     108,   107,     0,     0,   101,   171,   174,     0,   168,   167,
     169,     0,   119,   123,   129,   133,   135,   137,   139,   104,
       0,     0,    10,     0,    13,     0,     0,     0,     0,     0,
      26,   203,     0,     0,     0,     0,    86,     0,     0,   181,
       0,   191,     0,     0,    68,    56,    57,   156,   145,   146,
     197,     0,   184,     0,     0,     0,     0,   180,    92,    90,
       0,   202,   172,   173,     0,   102,     0,   100,     0,   162,
       0,     0,    14,     0,     0,   199,     0,     0,   164,    24,
     165,     0,    28,    29,    31,     0,     0,     0,    27,   204,
      20,     0,     0,     0,     0,   182,   183,   196,    94,     0,
     188,    42,    43,    44,    45,   175,   170,     0,   105,     0,
       0,   177,   187,   178,   176,   186,     0,   193,     0,   148,
       0,     0,     0,    32,     0,    25,     0,     0,    21,     0,
      87,   198,    55,    11,     0,     0,   200,   147,     0,   166,
     194,    30,     0,     0,    22,     0,    12,     0,   149,     0,
       0,    23,   179,     0,     0,     0,     0,     0,     0,    33,
       0,    58,   143,   141,   142,     0,     0,    59,   140,    34
  };

  const short
  parser::yypgoto_[] =
  {
    -305,  -305,  -305,  -305,  -305,  -305,  -305,  -305,  -240,  -134,
    -305,  -305,  -305,    84,  -305,    -3,  -305,  -305,  -305,   200,
    -305,  -305,  -305,  -305,  -305,    -4,    67,  -305,   -74,   -75,
     140,  -305,  -305,   -34,   -20,  -305,    60,  -305,  -305,    33,
     206,  -305,  -305,  -305,  -305,  -305,  -305,  -305,  -305,  -305,
    -305,   -50,  -305,  -305,  -305,   202,  -305,   192,  -305,   201,
    -305,   204,   190,   193,  -305,  -304,  -305,   -32,  -305,     3,
    -305,   254,  -305,  -305,  -305,  -305,  -305,  -305,  -213,  -267,
    -305,    80,  -137,    88,  -305,  -291,  -305,  -305,   155,   113,
    -165,    38,  -305,   160,   318,  -106,  -305,  -305,    75,  -305,
    -133
  };

  const short
  parser::yydefgoto_[] =
  {
      -1,     1,     2,     6,     7,    15,    16,   141,   142,   143,
     144,   145,   146,   220,   272,   273,   147,     8,     9,    99,
     100,   101,   102,   103,   104,    40,    41,    42,    23,    43,
     198,    89,    90,   345,    45,    46,    47,    48,    49,    50,
      51,    52,    53,    54,   107,    55,    56,    57,    58,    59,
      60,    61,    62,    63,   123,    64,   126,    65,   131,    66,
     134,    67,    68,    69,    70,   346,   355,    71,    92,   309,
     310,    72,    73,    74,    75,    76,    77,    78,    79,   269,
     270,   200,   201,   196,   197,   302,   303,   304,   108,   156,
     173,   265,   174,   175,    85,   221,   157,   241,   266,   109,
     222
  };

  const short
  parser::yytable_[] =
  {
      11,    12,   210,   268,    91,    83,   240,   150,   213,   315,
      10,   161,   119,    10,    24,    10,   225,    24,    10,   140,
     299,   352,   140,   332,     3,    10,   215,   256,   260,    27,
      24,    10,    27,   257,    10,   140,    13,   256,    10,   112,
      10,   350,   340,   259,    27,   217,    14,   353,   354,    24,
     186,   160,   350,   215,   160,    19,   215,    27,   187,    27,
     324,   212,    24,   268,   323,   159,   160,   223,    10,   189,
     282,   349,   217,   202,   161,   217,   148,   336,   261,   160,
     161,   160,   237,   161,   359,   161,   199,    27,   358,   152,
     153,   171,   161,    10,   161,   328,   190,   161,    17,    29,
      30,    31,    32,   329,   105,   154,    18,   199,    20,   160,
     113,    82,    27,   267,    84,    37,   279,   224,    24,   279,
     215,    80,   300,   229,   321,   116,   232,   138,   233,   167,
     117,   226,   118,   168,   160,   238,   110,   239,   148,   217,
     242,   161,   268,     4,     5,   152,   153,   149,   306,   215,
     161,   155,   161,   161,   307,   279,    81,   112,    44,   215,
     172,   172,   172,   216,   135,   213,   306,    82,   217,   218,
     219,    37,   330,   276,   124,   125,    88,   106,   217,   218,
     277,    82,   120,   121,   122,    37,   256,   158,   337,   161,
     213,   136,   342,   283,   137,   285,   286,    24,    10,   161,
     165,   161,   140,   169,   166,   151,   230,   170,   138,   149,
     231,   263,   288,   254,   274,    21,    22,   255,   163,   227,
     228,   167,    88,   289,   199,   168,   164,   290,   113,   111,
      10,   139,   305,   161,   114,   115,   178,   179,   172,   182,
     132,   133,   313,   334,    24,    10,   180,   185,   127,   128,
     129,   130,   -48,   250,   176,   177,   148,   195,   181,   301,
     188,   341,   209,   211,   214,    24,   243,   263,   161,   244,
     161,   314,   248,   161,   245,   246,   327,   317,   249,   258,
     161,   161,   264,   262,   271,   281,   284,   275,   297,   312,
     316,   325,   319,   199,   339,   148,   148,   155,   343,   348,
     351,   344,   263,   235,   357,   236,   278,   184,   274,   331,
     301,   347,   333,   347,   356,   335,   347,   320,   298,    24,
     148,   247,   191,   204,   347,    25,   207,   149,   203,   301,
     208,   338,   252,   253,   308,   205,   296,    26,   264,   206,
     162,   251,   295,   287,   326,    86,   311,     0,     0,    29,
      30,    31,    32,    33,    34,    35,   172,     0,     0,     0,
       0,    82,     0,   280,     0,    37,   149,   149,     0,     0,
       0,     0,     0,   264,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   291,   292,   293,   294,     0,     0,     0,
       0,   149,     0,     0,   195,   308,    24,    10,     0,     0,
       0,     0,    25,     0,     0,     0,     0,     0,     0,     0,
      93,    94,    95,    96,    26,     0,    27,     0,     0,     0,
       0,    28,   318,     0,     0,    97,    29,    30,    31,    32,
      33,    34,    35,     0,     0,     0,     0,   322,    36,    24,
      10,     0,    37,    98,     0,    25,     0,     0,    38,    39,
       0,     0,     0,    93,    94,    95,    96,    26,     0,    27,
       0,     0,     0,     0,    28,     0,     0,     0,    97,    29,
      30,    31,    32,    33,    34,    35,    24,    10,     0,     0,
       0,    36,    25,     0,     0,    37,   183,     0,     0,     0,
       0,    38,    39,     0,    26,     0,    27,     0,     0,     0,
       0,    28,     0,   192,   193,     0,    29,    30,    31,    32,
      33,    34,    35,     0,    24,    10,     0,     0,    36,   194,
      25,     0,    37,     0,     0,     0,     0,     0,    38,    39,
       0,     0,    26,     0,    27,     0,     0,     0,     0,    28,
       0,   192,   193,     0,    29,    30,    31,    32,    33,    34,
      35,    24,    10,     0,     0,     0,    36,    25,     0,     0,
      37,     0,     0,     0,     0,     0,    38,    39,     0,    26,
       0,    27,     0,     0,     0,     0,    28,     0,     0,     0,
       0,    29,    30,    31,    32,    33,    34,    35,     0,    24,
      10,     0,     0,    36,    87,    25,     0,    37,     0,     0,
       0,     0,     0,    38,    39,     0,     0,    26,     0,    27,
       0,     0,     0,     0,    28,     0,     0,     0,     0,    29,
      30,    31,    32,    33,    34,    35,     0,    24,    10,     0,
       0,    36,   234,    25,     0,    37,     0,     0,     0,     0,
       0,    38,    39,     0,     0,    26,     0,    27,     0,     0,
       0,     0,    28,     0,     0,     0,     0,    29,    30,    31,
      32,    33,    34,    35,     0,     0,     0,     0,     0,    36,
       0,     0,     0,    37,     0,     0,     0,     0,     0,    38,
      39
  };

  const short
  parser::yycheck_[] =
  {
       4,     5,   139,   216,    36,    25,   171,    81,   142,   276,
       4,    86,    62,     4,     3,     4,   149,     3,     4,     8,
     260,    44,     8,   314,     0,     4,    47,    42,    49,    23,
       3,     4,    23,    48,     4,     8,    43,    42,     4,    43,
       4,   345,   333,    48,    23,    66,     7,    70,    71,     3,
      42,    45,   356,    47,    45,     4,    47,    23,    50,    23,
     300,    50,     3,   276,    50,    85,    45,    61,     4,     3,
      61,    50,    66,   123,   149,    66,    80,    50,   211,    45,
     155,    45,    46,   158,    50,   160,   118,    23,   355,    30,
      31,    45,   167,     4,   169,    42,   116,   172,    16,    33,
      34,    35,    36,    50,    37,    46,    16,   139,    43,    45,
      43,    45,    23,    49,    45,    49,   222,   149,     3,   225,
      47,    49,    49,   155,   289,    40,   158,    40,   160,    42,
      45,   151,    47,    46,    45,   167,    41,   169,   142,    66,
     172,   216,   355,    14,    15,    30,    31,    80,    42,    47,
     225,    84,   227,   228,    48,   261,    24,   161,    18,    47,
      93,    94,    95,    61,    25,   299,    42,    45,    66,    67,
      68,    49,    48,    61,    55,    56,    36,    37,    66,    67,
      68,    45,    52,    53,    54,    49,    42,    51,   325,   264,
     324,    26,    48,   225,    27,   227,   228,     3,     4,   274,
      42,   276,     8,    42,    46,    10,    42,    46,    40,   142,
      46,   215,   232,    42,   218,    38,    39,    46,    42,   152,
     153,    42,    82,    42,   256,    46,    46,    46,   161,     3,
       4,    47,   264,   308,    38,    39,    96,    97,   171,    50,
      62,    63,   274,   317,     3,     4,    43,   107,    57,    58,
      59,    60,    41,   186,    94,    95,   260,   117,    61,   263,
      41,   335,     4,     4,    43,     3,    61,   271,   343,    61,
     345,   275,    43,   348,    61,    61,   308,   281,    50,     6,
     355,   356,   215,    43,    47,    16,    11,    57,    45,    67,
      57,    47,    16,   325,    59,   299,   300,   230,    49,    49,
      43,    59,   306,   163,    43,   165,   222,   107,   312,   312,
     314,   343,   316,   345,   348,   319,   348,   284,   258,     3,
     324,   181,   116,   131,   356,     9,   136,   260,   126,   333,
     137,   328,   192,   193,   267,   134,   256,    21,   271,   135,
      86,   186,   254,   230,   306,    27,   271,    -1,    -1,    33,
      34,    35,    36,    37,    38,    39,   289,    -1,    -1,    -1,
      -1,    45,    -1,   223,    -1,    49,   299,   300,    -1,    -1,
      -1,    -1,    -1,   306,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   243,   244,   245,   246,    -1,    -1,    -1,
      -1,   324,    -1,    -1,   254,   328,     3,     4,    -1,    -1,
      -1,    -1,     9,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      17,    18,    19,    20,    21,    -1,    23,    -1,    -1,    -1,
      -1,    28,   282,    -1,    -1,    32,    33,    34,    35,    36,
      37,    38,    39,    -1,    -1,    -1,    -1,   297,    45,     3,
       4,    -1,    49,    50,    -1,     9,    -1,    -1,    55,    56,
      -1,    -1,    -1,    17,    18,    19,    20,    21,    -1,    23,
      -1,    -1,    -1,    -1,    28,    -1,    -1,    -1,    32,    33,
      34,    35,    36,    37,    38,    39,     3,     4,    -1,    -1,
      -1,    45,     9,    -1,    -1,    49,    50,    -1,    -1,    -1,
      -1,    55,    56,    -1,    21,    -1,    23,    -1,    -1,    -1,
      -1,    28,    -1,    30,    31,    -1,    33,    34,    35,    36,
      37,    38,    39,    -1,     3,     4,    -1,    -1,    45,    46,
       9,    -1,    49,    -1,    -1,    -1,    -1,    -1,    55,    56,
      -1,    -1,    21,    -1,    23,    -1,    -1,    -1,    -1,    28,
      -1,    30,    31,    -1,    33,    34,    35,    36,    37,    38,
      39,     3,     4,    -1,    -1,    -1,    45,     9,    -1,    -1,
      49,    -1,    -1,    -1,    -1,    -1,    55,    56,    -1,    21,
      -1,    23,    -1,    -1,    -1,    -1,    28,    -1,    -1,    -1,
      -1,    33,    34,    35,    36,    37,    38,    39,    -1,     3,
       4,    -1,    -1,    45,    46,     9,    -1,    49,    -1,    -1,
      -1,    -1,    -1,    55,    56,    -1,    -1,    21,    -1,    23,
      -1,    -1,    -1,    -1,    28,    -1,    -1,    -1,    -1,    33,
      34,    35,    36,    37,    38,    39,    -1,     3,     4,    -1,
      -1,    45,    46,     9,    -1,    49,    -1,    -1,    -1,    -1,
      -1,    55,    56,    -1,    -1,    21,    -1,    23,    -1,    -1,
      -1,    -1,    28,    -1,    -1,    -1,    -1,    33,    34,    35,
      36,    37,    38,    39,    -1,    -1,    -1,    -1,    -1,    45,
      -1,    -1,    -1,    49,    -1,    -1,    -1,    -1,    -1,    55,
      56
  };

  const unsigned char
  parser::yystos_[] =
  {
       0,    74,    75,     0,    14,    15,    76,    77,    90,    91,
       4,    98,    98,    43,     7,    78,    79,    16,    16,     4,
      43,    38,    39,   101,     3,     9,    21,    23,    28,    33,
      34,    35,    36,    37,    38,    39,    45,    49,    55,    56,
      98,    99,   100,   102,   103,   107,   108,   109,   110,   111,
     112,   113,   114,   115,   116,   118,   119,   120,   121,   122,
     123,   124,   125,   126,   128,   130,   132,   134,   135,   136,
     137,   140,   144,   145,   146,   147,   148,   149,   150,   151,
      49,    24,    45,   107,    45,   167,   167,    46,   103,   104,
     105,   140,   141,    17,    18,    19,    20,    32,    50,    92,
      93,    94,    95,    96,    97,    99,   103,   117,   161,   172,
      41,     3,    98,    99,    38,    39,    40,    45,    47,   124,
      52,    53,    54,   127,    55,    56,   129,    57,    58,    59,
      60,   131,    62,    63,   133,    25,    26,    27,    40,    47,
       8,    80,    81,    82,    83,    84,    85,    89,    98,    99,
     101,    10,    30,    31,    46,    99,   162,   169,    51,   107,
      45,   102,   144,    42,    46,    42,    46,    42,    46,    42,
      46,    45,    99,   163,   165,   166,   166,   166,   103,   103,
      43,    61,    50,    50,    92,   103,    42,    50,    41,     3,
     107,   113,    30,    31,    46,   103,   156,   157,   103,   140,
     154,   155,   124,   128,   130,   132,   134,   135,   136,     4,
     155,     4,    50,    82,    43,    47,    61,    66,    67,    68,
      86,   168,   173,    61,   140,   173,   107,    99,    99,   140,
      42,    46,   140,   140,    46,   103,   103,    46,   140,   140,
     163,   170,   140,    61,    61,    61,    61,   103,    43,    50,
      99,   161,   103,   103,    42,    46,    42,    48,     6,    48,
      49,   173,    43,    98,    99,   164,   171,    49,   151,   152,
     153,    47,    87,    88,    98,    57,    61,    68,    86,   168,
     103,    16,    61,   140,    11,   140,   140,   162,   107,    42,
      46,   103,   103,   103,   103,   156,   154,    45,   109,    81,
      49,    98,   158,   159,   160,   140,    42,    48,    99,   142,
     143,   171,    67,   140,    98,   152,    57,    98,   103,    16,
     112,   163,   103,    50,    81,    47,   164,   140,    42,    50,
      48,    88,   158,    98,   101,    98,    50,   155,   142,    59,
     158,   101,    48,    49,    59,   106,   138,   140,    49,    50,
     138,    43,    44,    70,    71,   139,   106,    43,   152,    50
  };

  const unsigned char
  parser::yyr1_[] =
  {
       0,    73,    74,    75,    75,    76,    76,    77,    77,    78,
      79,    80,    80,    81,    81,    82,    82,    82,    82,    82,
      83,    83,    83,    83,    84,    84,    85,    85,    86,    87,
      87,    88,    88,    89,    89,    90,    91,    92,    92,    92,
      92,    92,    93,    94,    95,    96,    97,    98,    99,   100,
     101,   101,   102,   102,   103,   104,   105,   105,   106,   106,
     107,   107,   107,   107,   107,   108,   108,   109,   110,   110,
     111,   112,   112,   112,   112,   112,   112,   112,   113,   113,
     113,   113,   114,   114,   114,   114,   115,   115,   116,   116,
     116,   117,   117,   118,   118,   119,   119,   119,   119,   119,
     120,   121,   121,   122,   122,   122,   122,   123,   123,   124,
     124,   125,   125,   125,   126,   127,   127,   127,   128,   128,
     129,   129,   130,   130,   131,   131,   131,   131,   132,   132,
     133,   133,   134,   134,   135,   135,   136,   136,   137,   137,
     138,   139,   139,   139,   140,   141,   141,   142,   143,   143,
     144,   144,   144,   144,   144,   145,   146,   146,   147,   148,
     149,   149,   150,   151,   152,   152,   153,   154,   154,   155,
     155,   156,   156,   156,   157,   157,   158,   159,   160,   160,
     161,   162,   162,   162,   163,   163,   164,   164,   165,   166,
     166,   167,   167,   168,   168,   169,   169,   170,   170,   171,
     171,   172,   172,   173,   173
  };

  const signed char
  parser::yyr2_[] =
  {
       0,     2,     2,     0,     3,     1,     1,     0,     3,     1,
       5,     5,     6,     2,     3,     1,     1,     1,     1,     1,
       3,     4,     5,     6,     3,     4,     2,     3,     2,     1,
       3,     1,     2,     9,    10,     6,     4,     1,     1,     1,
       1,     1,     4,     4,     4,     4,     2,     1,     1,     1,
       1,     1,     2,     3,     1,     1,     3,     3,     2,     3,
       1,     1,     1,     1,     1,     2,     2,     3,     4,     3,
       3,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     2,     2,     4,     6,     3,     3,
       4,     2,     3,     3,     5,     1,     1,     1,     1,     1,
       4,     3,     4,     3,     3,     5,     2,     3,     3,     1,
       2,     1,     1,     1,     1,     1,     1,     1,     1,     3,
       1,     1,     1,     3,     1,     1,     1,     1,     1,     3,
       1,     1,     1,     3,     1,     3,     1,     3,     1,     3,
       3,     1,     1,     1,     1,     3,     3,     2,     1,     3,
       1,     1,     1,     1,     1,     3,     4,     3,     2,     3,
       1,     1,     4,     1,     1,     1,     3,     1,     1,     1,
       3,     1,     2,     2,     1,     3,     1,     1,     1,     4,
       3,     2,     3,     3,     2,     1,     2,     2,     3,     1,
       1,     3,     2,     3,     4,     1,     3,     1,     3,     1,
       3,     1,     3,     1,     2
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
  "floatl", "stringl", "mod_prefix", "expr", "long_exp", "expr_cl2",
  "type_query_exp_sl", "bracketed_exp", "unit_exp", "paren_exp",
  "vtupleExpr", "vstructExpr", "primary_exp", "int_expr", "stringls",
  "if_exp", "chain_exp", "chain_prefix", "lambda_exp", "postfix_exp",
  "tcall_exp", "vcall_exp", "dot_name_exp", "dot_index_exp", "unary_exp",
  "unary_op", "binary_exp", "mul_binary_op", "mul_binary_exp",
  "add_binary_op", "add_binary_exp", "cmp_binary_op", "cmp_binary_exp",
  "eq_binary_op", "eq_binary_exp", "and_binary_exp", "xor_binary_exp",
  "or_binary_exp", "type_query_exp", "type_query_op", "type_spec",
  "type_spec_cl2", "struct_type_spec_field", "struct_type_spec_field_cl",
  "primary_type_spec", "paren_type_spec", "tuple_type_spec",
  "mod_prefix_tid", "fn_type_spec", "postfix_type_spec", "tcall_type_spec",
  "unary_type_spec", "long_type_spec", "struct_type_spec", "targ",
  "targ_cl", "varg", "varg_cl", "class_spec", "primary_class_spec",
  "postfix_class_spec", "struct_exp_field", "vpattern_field",
  "lpattern_field", "tpattern_field", "destructured_lpattern", "lpattern",
  "vpattern", "tpattern", "vpattern_field_cl", "lpattern_field_cl",
  "tpattern_field_cl", "struct_exp_field_cl", "tpattern_seq", YY_NULLPTR
  };
#endif


#if YYDEBUG
  const short
  parser::yyrline_[] =
  {
       0,   289,   289,   297,   298,   301,   302,   306,   307,   310,
     318,   321,   322,   325,   326,   334,   335,   336,   337,   338,
     341,   342,   343,   344,   347,   348,   351,   352,   355,   358,
     359,   362,   363,   366,   369,   375,   378,   382,   383,   384,
     385,   386,   389,   392,   395,   398,   401,   408,   409,   411,
     414,   415,   418,   419,   426,   429,   437,   438,   441,   442,
     446,   447,   448,   449,   450,   453,   454,   457,   460,   461,
     464,   467,   468,   469,   470,   471,   472,   473,   476,   477,
     478,   479,   482,   483,   484,   485,   488,   489,   492,   493,
     494,   497,   498,   501,   502,   506,   507,   508,   509,   510,
     513,   516,   517,   520,   521,   522,   523,   526,   527,   531,
     532,   535,   536,   537,   541,   544,   545,   546,   549,   550,
     553,   554,   557,   558,   561,   562,   563,   564,   567,   568,
     571,   572,   575,   576,   579,   580,   583,   584,   587,   588,
     592,   595,   596,   597,   605,   616,   617,   621,   624,   625,
     629,   630,   631,   632,   633,   636,   639,   640,   643,   646,
     650,   651,   654,   658,   662,   663,   666,   669,   670,   673,
     674,   676,   677,   678,   681,   682,   692,   695,   698,   699,
     707,   710,   711,   712,   715,   716,   719,   720,   724,   728,
     729,   732,   733,   736,   737,   741,   742,   745,   746,   749,
     750,   753,   754,   758,   759
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
#line 4170 "parser.tab.cc"

#line 762 "parser.yy"


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
