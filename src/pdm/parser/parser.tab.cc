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
#line 65 "parser.yy"

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

      case symbol_kind::S_mod_stmt: // mod_stmt
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

      case symbol_kind::S_script: // script
        value.copy< pdm::ast::Script* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_scriptContentStmt: // scriptContentStmt
      case symbol_kind::S_top_mod_stmt: // top_mod_stmt
      case symbol_kind::S_chain_prefix_stmt: // chain_prefix_stmt
      case symbol_kind::S_const_stmt: // const_stmt
      case symbol_kind::S_val_stmt: // val_stmt
      case symbol_kind::S_var_stmt: // var_stmt
      case symbol_kind::S_set_stmt: // set_stmt
      case symbol_kind::S_discard_stmt: // discard_stmt
      case symbol_kind::S_using_stmt: // using_stmt
      case symbol_kind::S_import_stmt: // import_stmt
      case symbol_kind::S_extern_stmt: // extern_stmt
        value.copy< pdm::ast::Stmt* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_struct_exp_field: // struct_exp_field
        value.copy< pdm::ast::StructExp::Field* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_struct_typespec_field: // struct_typespec_field
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

      case symbol_kind::S_typespec: // typespec
      case symbol_kind::S_primary_typespec: // primary_typespec
      case symbol_kind::S_paren_typespec: // paren_typespec
      case symbol_kind::S_tuple_typespec: // tuple_typespec
      case symbol_kind::S_mod_prefix_tid: // mod_prefix_tid
      case symbol_kind::S_fn_typespec: // fn_typespec
      case symbol_kind::S_postfix_typespec: // postfix_typespec
      case symbol_kind::S_tcall_typespec: // tcall_typespec
      case symbol_kind::S_unary_typespec: // unary_typespec
      case symbol_kind::S_long_typespec: // long_typespec
      case symbol_kind::S_struct_typespec: // struct_typespec
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

      case symbol_kind::S_scriptContent: // scriptContent
      case symbol_kind::S_chain_prefix: // chain_prefix
        value.copy< std::vector<pdm::ast::Stmt*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stringls: // stringls
        value.copy< std::vector<pdm::ast::StringExp::Piece> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_struct_exp_field_cl: // struct_exp_field_cl
        value.copy< std::vector<pdm::ast::StructExp::Field*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_struct_typespec_field_cl: // struct_typespec_field_cl
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

      case symbol_kind::S_typespec_cl1: // typespec_cl1
      case symbol_kind::S_typespec_cl2: // typespec_cl2
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

      case symbol_kind::S_mod_stmt: // mod_stmt
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

      case symbol_kind::S_script: // script
        value.move< pdm::ast::Script* > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_scriptContentStmt: // scriptContentStmt
      case symbol_kind::S_top_mod_stmt: // top_mod_stmt
      case symbol_kind::S_chain_prefix_stmt: // chain_prefix_stmt
      case symbol_kind::S_const_stmt: // const_stmt
      case symbol_kind::S_val_stmt: // val_stmt
      case symbol_kind::S_var_stmt: // var_stmt
      case symbol_kind::S_set_stmt: // set_stmt
      case symbol_kind::S_discard_stmt: // discard_stmt
      case symbol_kind::S_using_stmt: // using_stmt
      case symbol_kind::S_import_stmt: // import_stmt
      case symbol_kind::S_extern_stmt: // extern_stmt
        value.move< pdm::ast::Stmt* > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_struct_exp_field: // struct_exp_field
        value.move< pdm::ast::StructExp::Field* > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_struct_typespec_field: // struct_typespec_field
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

      case symbol_kind::S_typespec: // typespec
      case symbol_kind::S_primary_typespec: // primary_typespec
      case symbol_kind::S_paren_typespec: // paren_typespec
      case symbol_kind::S_tuple_typespec: // tuple_typespec
      case symbol_kind::S_mod_prefix_tid: // mod_prefix_tid
      case symbol_kind::S_fn_typespec: // fn_typespec
      case symbol_kind::S_postfix_typespec: // postfix_typespec
      case symbol_kind::S_tcall_typespec: // tcall_typespec
      case symbol_kind::S_unary_typespec: // unary_typespec
      case symbol_kind::S_long_typespec: // long_typespec
      case symbol_kind::S_struct_typespec: // struct_typespec
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

      case symbol_kind::S_scriptContent: // scriptContent
      case symbol_kind::S_chain_prefix: // chain_prefix
        value.move< std::vector<pdm::ast::Stmt*> > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_stringls: // stringls
        value.move< std::vector<pdm::ast::StringExp::Piece> > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_struct_exp_field_cl: // struct_exp_field_cl
        value.move< std::vector<pdm::ast::StructExp::Field*> > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_struct_typespec_field_cl: // struct_typespec_field_cl
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

      case symbol_kind::S_typespec_cl1: // typespec_cl1
      case symbol_kind::S_typespec_cl2: // typespec_cl2
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

      case symbol_kind::S_mod_stmt: // mod_stmt
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

      case symbol_kind::S_script: // script
        value.YY_MOVE_OR_COPY< pdm::ast::Script* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_scriptContentStmt: // scriptContentStmt
      case symbol_kind::S_top_mod_stmt: // top_mod_stmt
      case symbol_kind::S_chain_prefix_stmt: // chain_prefix_stmt
      case symbol_kind::S_const_stmt: // const_stmt
      case symbol_kind::S_val_stmt: // val_stmt
      case symbol_kind::S_var_stmt: // var_stmt
      case symbol_kind::S_set_stmt: // set_stmt
      case symbol_kind::S_discard_stmt: // discard_stmt
      case symbol_kind::S_using_stmt: // using_stmt
      case symbol_kind::S_import_stmt: // import_stmt
      case symbol_kind::S_extern_stmt: // extern_stmt
        value.YY_MOVE_OR_COPY< pdm::ast::Stmt* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_struct_exp_field: // struct_exp_field
        value.YY_MOVE_OR_COPY< pdm::ast::StructExp::Field* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_struct_typespec_field: // struct_typespec_field
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

      case symbol_kind::S_typespec: // typespec
      case symbol_kind::S_primary_typespec: // primary_typespec
      case symbol_kind::S_paren_typespec: // paren_typespec
      case symbol_kind::S_tuple_typespec: // tuple_typespec
      case symbol_kind::S_mod_prefix_tid: // mod_prefix_tid
      case symbol_kind::S_fn_typespec: // fn_typespec
      case symbol_kind::S_postfix_typespec: // postfix_typespec
      case symbol_kind::S_tcall_typespec: // tcall_typespec
      case symbol_kind::S_unary_typespec: // unary_typespec
      case symbol_kind::S_long_typespec: // long_typespec
      case symbol_kind::S_struct_typespec: // struct_typespec
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

      case symbol_kind::S_scriptContent: // scriptContent
      case symbol_kind::S_chain_prefix: // chain_prefix
        value.YY_MOVE_OR_COPY< std::vector<pdm::ast::Stmt*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stringls: // stringls
        value.YY_MOVE_OR_COPY< std::vector<pdm::ast::StringExp::Piece> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_struct_exp_field_cl: // struct_exp_field_cl
        value.YY_MOVE_OR_COPY< std::vector<pdm::ast::StructExp::Field*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_struct_typespec_field_cl: // struct_typespec_field_cl
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

      case symbol_kind::S_typespec_cl1: // typespec_cl1
      case symbol_kind::S_typespec_cl2: // typespec_cl2
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

      case symbol_kind::S_mod_stmt: // mod_stmt
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

      case symbol_kind::S_script: // script
        value.move< pdm::ast::Script* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_scriptContentStmt: // scriptContentStmt
      case symbol_kind::S_top_mod_stmt: // top_mod_stmt
      case symbol_kind::S_chain_prefix_stmt: // chain_prefix_stmt
      case symbol_kind::S_const_stmt: // const_stmt
      case symbol_kind::S_val_stmt: // val_stmt
      case symbol_kind::S_var_stmt: // var_stmt
      case symbol_kind::S_set_stmt: // set_stmt
      case symbol_kind::S_discard_stmt: // discard_stmt
      case symbol_kind::S_using_stmt: // using_stmt
      case symbol_kind::S_import_stmt: // import_stmt
      case symbol_kind::S_extern_stmt: // extern_stmt
        value.move< pdm::ast::Stmt* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_struct_exp_field: // struct_exp_field
        value.move< pdm::ast::StructExp::Field* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_struct_typespec_field: // struct_typespec_field
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

      case symbol_kind::S_typespec: // typespec
      case symbol_kind::S_primary_typespec: // primary_typespec
      case symbol_kind::S_paren_typespec: // paren_typespec
      case symbol_kind::S_tuple_typespec: // tuple_typespec
      case symbol_kind::S_mod_prefix_tid: // mod_prefix_tid
      case symbol_kind::S_fn_typespec: // fn_typespec
      case symbol_kind::S_postfix_typespec: // postfix_typespec
      case symbol_kind::S_tcall_typespec: // tcall_typespec
      case symbol_kind::S_unary_typespec: // unary_typespec
      case symbol_kind::S_long_typespec: // long_typespec
      case symbol_kind::S_struct_typespec: // struct_typespec
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

      case symbol_kind::S_scriptContent: // scriptContent
      case symbol_kind::S_chain_prefix: // chain_prefix
        value.move< std::vector<pdm::ast::Stmt*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stringls: // stringls
        value.move< std::vector<pdm::ast::StringExp::Piece> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_struct_exp_field_cl: // struct_exp_field_cl
        value.move< std::vector<pdm::ast::StructExp::Field*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_struct_typespec_field_cl: // struct_typespec_field_cl
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

      case symbol_kind::S_typespec_cl1: // typespec_cl1
      case symbol_kind::S_typespec_cl2: // typespec_cl2
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

      case symbol_kind::S_mod_stmt: // mod_stmt
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

      case symbol_kind::S_script: // script
        value.copy< pdm::ast::Script* > (that.value);
        break;

      case symbol_kind::S_scriptContentStmt: // scriptContentStmt
      case symbol_kind::S_top_mod_stmt: // top_mod_stmt
      case symbol_kind::S_chain_prefix_stmt: // chain_prefix_stmt
      case symbol_kind::S_const_stmt: // const_stmt
      case symbol_kind::S_val_stmt: // val_stmt
      case symbol_kind::S_var_stmt: // var_stmt
      case symbol_kind::S_set_stmt: // set_stmt
      case symbol_kind::S_discard_stmt: // discard_stmt
      case symbol_kind::S_using_stmt: // using_stmt
      case symbol_kind::S_import_stmt: // import_stmt
      case symbol_kind::S_extern_stmt: // extern_stmt
        value.copy< pdm::ast::Stmt* > (that.value);
        break;

      case symbol_kind::S_struct_exp_field: // struct_exp_field
        value.copy< pdm::ast::StructExp::Field* > (that.value);
        break;

      case symbol_kind::S_struct_typespec_field: // struct_typespec_field
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

      case symbol_kind::S_typespec: // typespec
      case symbol_kind::S_primary_typespec: // primary_typespec
      case symbol_kind::S_paren_typespec: // paren_typespec
      case symbol_kind::S_tuple_typespec: // tuple_typespec
      case symbol_kind::S_mod_prefix_tid: // mod_prefix_tid
      case symbol_kind::S_fn_typespec: // fn_typespec
      case symbol_kind::S_postfix_typespec: // postfix_typespec
      case symbol_kind::S_tcall_typespec: // tcall_typespec
      case symbol_kind::S_unary_typespec: // unary_typespec
      case symbol_kind::S_long_typespec: // long_typespec
      case symbol_kind::S_struct_typespec: // struct_typespec
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

      case symbol_kind::S_scriptContent: // scriptContent
      case symbol_kind::S_chain_prefix: // chain_prefix
        value.copy< std::vector<pdm::ast::Stmt*> > (that.value);
        break;

      case symbol_kind::S_stringls: // stringls
        value.copy< std::vector<pdm::ast::StringExp::Piece> > (that.value);
        break;

      case symbol_kind::S_struct_exp_field_cl: // struct_exp_field_cl
        value.copy< std::vector<pdm::ast::StructExp::Field*> > (that.value);
        break;

      case symbol_kind::S_struct_typespec_field_cl: // struct_typespec_field_cl
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

      case symbol_kind::S_typespec_cl1: // typespec_cl1
      case symbol_kind::S_typespec_cl2: // typespec_cl2
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

      case symbol_kind::S_mod_stmt: // mod_stmt
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

      case symbol_kind::S_script: // script
        value.move< pdm::ast::Script* > (that.value);
        break;

      case symbol_kind::S_scriptContentStmt: // scriptContentStmt
      case symbol_kind::S_top_mod_stmt: // top_mod_stmt
      case symbol_kind::S_chain_prefix_stmt: // chain_prefix_stmt
      case symbol_kind::S_const_stmt: // const_stmt
      case symbol_kind::S_val_stmt: // val_stmt
      case symbol_kind::S_var_stmt: // var_stmt
      case symbol_kind::S_set_stmt: // set_stmt
      case symbol_kind::S_discard_stmt: // discard_stmt
      case symbol_kind::S_using_stmt: // using_stmt
      case symbol_kind::S_import_stmt: // import_stmt
      case symbol_kind::S_extern_stmt: // extern_stmt
        value.move< pdm::ast::Stmt* > (that.value);
        break;

      case symbol_kind::S_struct_exp_field: // struct_exp_field
        value.move< pdm::ast::StructExp::Field* > (that.value);
        break;

      case symbol_kind::S_struct_typespec_field: // struct_typespec_field
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

      case symbol_kind::S_typespec: // typespec
      case symbol_kind::S_primary_typespec: // primary_typespec
      case symbol_kind::S_paren_typespec: // paren_typespec
      case symbol_kind::S_tuple_typespec: // tuple_typespec
      case symbol_kind::S_mod_prefix_tid: // mod_prefix_tid
      case symbol_kind::S_fn_typespec: // fn_typespec
      case symbol_kind::S_postfix_typespec: // postfix_typespec
      case symbol_kind::S_tcall_typespec: // tcall_typespec
      case symbol_kind::S_unary_typespec: // unary_typespec
      case symbol_kind::S_long_typespec: // long_typespec
      case symbol_kind::S_struct_typespec: // struct_typespec
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

      case symbol_kind::S_scriptContent: // scriptContent
      case symbol_kind::S_chain_prefix: // chain_prefix
        value.move< std::vector<pdm::ast::Stmt*> > (that.value);
        break;

      case symbol_kind::S_stringls: // stringls
        value.move< std::vector<pdm::ast::StringExp::Piece> > (that.value);
        break;

      case symbol_kind::S_struct_exp_field_cl: // struct_exp_field_cl
        value.move< std::vector<pdm::ast::StructExp::Field*> > (that.value);
        break;

      case symbol_kind::S_struct_typespec_field_cl: // struct_typespec_field_cl
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

      case symbol_kind::S_typespec_cl1: // typespec_cl1
      case symbol_kind::S_typespec_cl2: // typespec_cl2
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

      case symbol_kind::S_mod_stmt: // mod_stmt
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

      case symbol_kind::S_script: // script
        yylhs.value.emplace< pdm::ast::Script* > ();
        break;

      case symbol_kind::S_scriptContentStmt: // scriptContentStmt
      case symbol_kind::S_top_mod_stmt: // top_mod_stmt
      case symbol_kind::S_chain_prefix_stmt: // chain_prefix_stmt
      case symbol_kind::S_const_stmt: // const_stmt
      case symbol_kind::S_val_stmt: // val_stmt
      case symbol_kind::S_var_stmt: // var_stmt
      case symbol_kind::S_set_stmt: // set_stmt
      case symbol_kind::S_discard_stmt: // discard_stmt
      case symbol_kind::S_using_stmt: // using_stmt
      case symbol_kind::S_import_stmt: // import_stmt
      case symbol_kind::S_extern_stmt: // extern_stmt
        yylhs.value.emplace< pdm::ast::Stmt* > ();
        break;

      case symbol_kind::S_struct_exp_field: // struct_exp_field
        yylhs.value.emplace< pdm::ast::StructExp::Field* > ();
        break;

      case symbol_kind::S_struct_typespec_field: // struct_typespec_field
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

      case symbol_kind::S_typespec: // typespec
      case symbol_kind::S_primary_typespec: // primary_typespec
      case symbol_kind::S_paren_typespec: // paren_typespec
      case symbol_kind::S_tuple_typespec: // tuple_typespec
      case symbol_kind::S_mod_prefix_tid: // mod_prefix_tid
      case symbol_kind::S_fn_typespec: // fn_typespec
      case symbol_kind::S_postfix_typespec: // postfix_typespec
      case symbol_kind::S_tcall_typespec: // tcall_typespec
      case symbol_kind::S_unary_typespec: // unary_typespec
      case symbol_kind::S_long_typespec: // long_typespec
      case symbol_kind::S_struct_typespec: // struct_typespec
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

      case symbol_kind::S_scriptContent: // scriptContent
      case symbol_kind::S_chain_prefix: // chain_prefix
        yylhs.value.emplace< std::vector<pdm::ast::Stmt*> > ();
        break;

      case symbol_kind::S_stringls: // stringls
        yylhs.value.emplace< std::vector<pdm::ast::StringExp::Piece> > ();
        break;

      case symbol_kind::S_struct_exp_field_cl: // struct_exp_field_cl
        yylhs.value.emplace< std::vector<pdm::ast::StructExp::Field*> > ();
        break;

      case symbol_kind::S_struct_typespec_field_cl: // struct_typespec_field_cl
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

      case symbol_kind::S_typespec_cl1: // typespec_cl1
      case symbol_kind::S_typespec_cl2: // typespec_cl2
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
  case 2: // script: scriptContent
#line 288 "parser.yy"
                    { yylhs.value.as < pdm::ast::Script* > () = mgr->new_script(source, yylhs.location, std::move(yystack_[0].value.as < std::vector<pdm::ast::Stmt*> > ())); *returnp = yylhs.value.as < pdm::ast::Script* > (); }
#line 2148 "parser.tab.cc"
    break;

  case 3: // scriptContent: scriptContentStmt ";"
#line 291 "parser.yy"
                                                    { yylhs.value.as < std::vector<pdm::ast::Stmt*> > ().push_back(yystack_[1].value.as < pdm::ast::Stmt* > ()); }
#line 2154 "parser.tab.cc"
    break;

  case 4: // scriptContent: scriptContent scriptContentStmt ";"
#line 292 "parser.yy"
                                                    { yylhs.value.as < std::vector<pdm::ast::Stmt*> > () = std::move(yystack_[2].value.as < std::vector<pdm::ast::Stmt*> > ()); yylhs.value.as < std::vector<pdm::ast::Stmt*> > ().push_back(yystack_[1].value.as < pdm::ast::Stmt* > ()); }
#line 2160 "parser.tab.cc"
    break;

  case 5: // scriptContentStmt: top_mod_stmt
#line 295 "parser.yy"
      { yylhs.value.as < pdm::ast::Stmt* > () = yystack_[0].value.as < pdm::ast::Stmt* > (); }
#line 2166 "parser.tab.cc"
    break;

  case 6: // scriptContentStmt: import_stmt
#line 296 "parser.yy"
      { yylhs.value.as < pdm::ast::Stmt* > () = yystack_[0].value.as < pdm::ast::Stmt* > (); }
#line 2172 "parser.tab.cc"
    break;

  case 7: // scriptContentStmt: extern_stmt
#line 297 "parser.yy"
      { yylhs.value.as < pdm::ast::Stmt* > () = yystack_[0].value.as < pdm::ast::Stmt* > (); }
#line 2178 "parser.tab.cc"
    break;

  case 8: // scriptContentStmt: using_stmt
#line 298 "parser.yy"
      { yylhs.value.as < pdm::ast::Stmt* > () = yystack_[0].value.as < pdm::ast::Stmt* > (); }
#line 2184 "parser.tab.cc"
    break;

  case 9: // top_mod_stmt: "mod" "<TypeId>" "{" mod_content "}"
#line 306 "parser.yy"
                                              { yylhs.value.as < pdm::ast::Stmt* > () = mgr->new_mod_stmt(yylhs.location, yystack_[3].value.as < TokenInfo > ().ID_intstr, std::move(std::vector<ast::TPattern*>{}), std::move(yystack_[1].value.as < std::vector<pdm::ast::ModContentStmt*> > ())); }
#line 2190 "parser.tab.cc"
    break;

  case 10: // mod_stmt: top_mod_stmt
#line 309 "parser.yy"
                                                           { yylhs.value.as < pdm::ast::ModContentStmt* > () = dynamic_cast<ast::ModContentStmt*>(yystack_[0].value.as < pdm::ast::Stmt* > ()); }
#line 2196 "parser.tab.cc"
    break;

  case 11: // mod_stmt: "mod" "<TypeId>" tpattern_seq "{" mod_content "}"
#line 310 "parser.yy"
                                                           { yylhs.value.as < pdm::ast::ModContentStmt* > () = mgr->new_mod_stmt(yylhs.location, yystack_[4].value.as < TokenInfo > ().ID_intstr, std::move(yystack_[3].value.as < std::vector<pdm::ast::TPattern*> > ()), std::move(yystack_[1].value.as < std::vector<pdm::ast::ModContentStmt*> > ())); }
#line 2202 "parser.tab.cc"
    break;

  case 12: // mod_content: mod_content_stmt ";"
#line 313 "parser.yy"
                                                { yylhs.value.as < std::vector<pdm::ast::ModContentStmt*> > ().push_back(yystack_[1].value.as < pdm::ast::ModContentStmt* > ()); }
#line 2208 "parser.tab.cc"
    break;

  case 13: // mod_content: mod_content mod_content_stmt ";"
#line 314 "parser.yy"
                                                { yylhs.value.as < std::vector<pdm::ast::ModContentStmt*> > () = std::move(yystack_[2].value.as < std::vector<pdm::ast::ModContentStmt*> > ()); yylhs.value.as < std::vector<pdm::ast::ModContentStmt*> > ().push_back(yystack_[1].value.as < pdm::ast::ModContentStmt* > ()); }
#line 2214 "parser.tab.cc"
    break;

  case 14: // chain_prefix_stmt: const_stmt
#line 322 "parser.yy"
      { yylhs.value.as < pdm::ast::Stmt* > () = yystack_[0].value.as < pdm::ast::Stmt* > (); }
#line 2220 "parser.tab.cc"
    break;

  case 15: // chain_prefix_stmt: val_stmt
#line 323 "parser.yy"
      { yylhs.value.as < pdm::ast::Stmt* > () = yystack_[0].value.as < pdm::ast::Stmt* > (); }
#line 2226 "parser.tab.cc"
    break;

  case 16: // chain_prefix_stmt: var_stmt
#line 324 "parser.yy"
      { yylhs.value.as < pdm::ast::Stmt* > () = yystack_[0].value.as < pdm::ast::Stmt* > (); }
#line 2232 "parser.tab.cc"
    break;

  case 17: // chain_prefix_stmt: set_stmt
#line 325 "parser.yy"
      { yylhs.value.as < pdm::ast::Stmt* > () = yystack_[0].value.as < pdm::ast::Stmt* > (); }
#line 2238 "parser.tab.cc"
    break;

  case 18: // chain_prefix_stmt: discard_stmt
#line 326 "parser.yy"
      { yylhs.value.as < pdm::ast::Stmt* > () = yystack_[0].value.as < pdm::ast::Stmt* > (); }
#line 2244 "parser.tab.cc"
    break;

  case 19: // const_stmt: "const" lpattern "=" expr
#line 329 "parser.yy"
                                  { yylhs.value.as < pdm::ast::Stmt* > () = mgr->new_const_stmt(yylhs.location, yystack_[2].value.as < pdm::ast::LPattern* > (), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2250 "parser.tab.cc"
    break;

  case 20: // val_stmt: "val" lpattern "=" expr
#line 332 "parser.yy"
                                  { yylhs.value.as < pdm::ast::Stmt* > () = mgr->new_val_stmt(yylhs.location, yystack_[2].value.as < pdm::ast::LPattern* > (), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2256 "parser.tab.cc"
    break;

  case 21: // var_stmt: "var" lpattern "=" expr
#line 335 "parser.yy"
                                  { yylhs.value.as < pdm::ast::Stmt* > () = mgr->new_var_stmt(yylhs.location, yystack_[2].value.as < pdm::ast::LPattern* > (), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2262 "parser.tab.cc"
    break;

  case 22: // set_stmt: "set" expr "=" expr
#line 338 "parser.yy"
                              { yylhs.value.as < pdm::ast::Stmt* > () = mgr->new_set_stmt(yylhs.location, yystack_[2].value.as < pdm::ast::Exp* > (), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2268 "parser.tab.cc"
    break;

  case 23: // discard_stmt: "discard" expr
#line 341 "parser.yy"
                        { yylhs.value.as < pdm::ast::Stmt* > () = mgr->new_discard_stmt(yylhs.location, yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2274 "parser.tab.cc"
    break;

  case 24: // mod_content_stmt: mod_val_stmt
#line 345 "parser.yy"
      { yylhs.value.as < pdm::ast::ModContentStmt* > () = yystack_[0].value.as < pdm::ast::ModContentStmt* > (); }
#line 2280 "parser.tab.cc"
    break;

  case 25: // mod_content_stmt: mod_type_stmt
#line 346 "parser.yy"
      { yylhs.value.as < pdm::ast::ModContentStmt* > () = yystack_[0].value.as < pdm::ast::ModContentStmt* > (); }
#line 2286 "parser.tab.cc"
    break;

  case 26: // mod_content_stmt: mod_enum_stmt
#line 347 "parser.yy"
      { yylhs.value.as < pdm::ast::ModContentStmt* > () = yystack_[0].value.as < pdm::ast::ModContentStmt* > (); }
#line 2292 "parser.tab.cc"
    break;

  case 27: // mod_content_stmt: mod_typeclass_stmt
#line 348 "parser.yy"
      { yylhs.value.as < pdm::ast::ModContentStmt* > () = yystack_[0].value.as < pdm::ast::ModContentStmt* > (); }
#line 2298 "parser.tab.cc"
    break;

  case 28: // mod_content_stmt: mod_stmt
#line 349 "parser.yy"
      { yylhs.value.as < pdm::ast::ModContentStmt* > () = yystack_[0].value.as < pdm::ast::ModContentStmt* > (); }
#line 2304 "parser.tab.cc"
    break;

  case 29: // mod_val_stmt: vid "=" expr
#line 352 "parser.yy"
                                    { yylhs.value.as < pdm::ast::ModContentStmt* > () = mgr->new_internal_mod_val_stmt(yylhs.location, yystack_[2].value.as < TokenInfo > ().ID_intstr, std::move(std::vector<ast::TPattern*>{}), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2310 "parser.tab.cc"
    break;

  case 30: // mod_val_stmt: vid tpattern_seq "=" expr
#line 353 "parser.yy"
                                    { yylhs.value.as < pdm::ast::ModContentStmt* > () = mgr->new_internal_mod_val_stmt(yylhs.location, yystack_[3].value.as < TokenInfo > ().ID_intstr, std::move(yystack_[2].value.as < std::vector<pdm::ast::TPattern*> > ()), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2316 "parser.tab.cc"
    break;

  case 31: // mod_val_stmt: vid typespec "from" tid stringl
#line 354 "parser.yy"
                                                     { yylhs.value.as < pdm::ast::ModContentStmt* > () = mgr->new_external_mod_val_stmt(yylhs.location, yystack_[4].value.as < TokenInfo > ().ID_intstr, std::move(std::vector<ast::TPattern*>{}), yystack_[3].value.as < pdm::ast::TypeSpec* > (), yystack_[1].value.as < TokenInfo > ().ID_intstr, *yystack_[0].value.as < TokenInfo > ().String_utf8string); }
#line 2322 "parser.tab.cc"
    break;

  case 32: // mod_val_stmt: vid tpattern_seq typespec "from" tid stringl
#line 355 "parser.yy"
                                                     { yylhs.value.as < pdm::ast::ModContentStmt* > () = mgr->new_external_mod_val_stmt(yylhs.location, yystack_[5].value.as < TokenInfo > ().ID_intstr, std::move(yystack_[4].value.as < std::vector<pdm::ast::TPattern*> > ()), yystack_[3].value.as < pdm::ast::TypeSpec* > (), yystack_[1].value.as < TokenInfo > ().ID_intstr, *yystack_[0].value.as < TokenInfo > ().String_utf8string); }
#line 2328 "parser.tab.cc"
    break;

  case 33: // mod_type_stmt: tid "=" long_typespec
#line 358 "parser.yy"
                                            { yylhs.value.as < pdm::ast::ModContentStmt* > () = mgr->new_mod_type_stmt(yylhs.location, yystack_[2].value.as < TokenInfo > ().ID_intstr, std::move(std::vector<ast::TPattern*>{}), yystack_[0].value.as < pdm::ast::TypeSpec* > ()); }
#line 2334 "parser.tab.cc"
    break;

  case 34: // mod_type_stmt: tid tpattern_seq "=" long_typespec
#line 359 "parser.yy"
                                            { yylhs.value.as < pdm::ast::ModContentStmt* > () = mgr->new_mod_type_stmt(yylhs.location, yystack_[3].value.as < TokenInfo > ().ID_intstr, std::move(yystack_[2].value.as < std::vector<pdm::ast::TPattern*> > ()), yystack_[0].value.as < pdm::ast::TypeSpec* > ()); }
#line 2340 "parser.tab.cc"
    break;

  case 35: // mod_enum_stmt: tid enum_field_pl
#line 362 "parser.yy"
                                        { yylhs.value.as < pdm::ast::ModContentStmt* > () = mgr->new_mod_enum_stmt(yylhs.location, yystack_[1].value.as < TokenInfo > ().ID_intstr, std::move(std::vector<ast::TPattern*>{}), std::move(yystack_[0].value.as < std::vector<pdm::ast::ModEnumStmt::Field*> > ())); }
#line 2346 "parser.tab.cc"
    break;

  case 36: // mod_enum_stmt: tid tpattern_seq enum_field_pl
#line 363 "parser.yy"
                                        { yylhs.value.as < pdm::ast::ModContentStmt* > () = mgr->new_mod_enum_stmt(yylhs.location, yystack_[2].value.as < TokenInfo > ().ID_intstr, std::move(yystack_[1].value.as < std::vector<pdm::ast::TPattern*> > ()), std::move(yystack_[0].value.as < std::vector<pdm::ast::ModEnumStmt::Field*> > ())); }
#line 2352 "parser.tab.cc"
    break;

  case 37: // enum_field_pl: "|" unprefixed_enum_field_pl
#line 366 "parser.yy"
                                    { yylhs.value.as < std::vector<pdm::ast::ModEnumStmt::Field*> > () = std::move(yystack_[0].value.as < std::vector<pdm::ast::ModEnumStmt::Field*> > ()); }
#line 2358 "parser.tab.cc"
    break;

  case 38: // unprefixed_enum_field_pl: enum_field
#line 369 "parser.yy"
                                                { yylhs.value.as < std::vector<pdm::ast::ModEnumStmt::Field*> > ().push_back(yystack_[0].value.as < pdm::ast::ModEnumStmt::Field* > ()); }
#line 2364 "parser.tab.cc"
    break;

  case 39: // unprefixed_enum_field_pl: unprefixed_enum_field_pl "|" enum_field
#line 370 "parser.yy"
                                                { yylhs.value.as < std::vector<pdm::ast::ModEnumStmt::Field*> > () = std::move(yystack_[2].value.as < std::vector<pdm::ast::ModEnumStmt::Field*> > ()); yylhs.value.as < std::vector<pdm::ast::ModEnumStmt::Field*> > ().push_back(yystack_[0].value.as < pdm::ast::ModEnumStmt::Field* > ()); }
#line 2370 "parser.tab.cc"
    break;

  case 40: // enum_field: tid
#line 373 "parser.yy"
                                     { yylhs.value.as < pdm::ast::ModEnumStmt::Field* > () = mgr->new_enum_stmt_field(yylhs.location, yystack_[0].value.as < TokenInfo > ().ID_intstr, std::move(std::vector<ast::TypeSpec*>{}), false); }
#line 2376 "parser.tab.cc"
    break;

  case 41: // enum_field: tid "(" ")"
#line 374 "parser.yy"
                                     { yylhs.value.as < pdm::ast::ModEnumStmt::Field* > () = mgr->new_enum_stmt_field(yylhs.location, yystack_[2].value.as < TokenInfo > ().ID_intstr, std::move(std::vector<ast::TypeSpec*>{}), true); }
#line 2382 "parser.tab.cc"
    break;

  case 42: // enum_field: tid "(" typespec_cl1 ")"
#line 375 "parser.yy"
                                     { yylhs.value.as < pdm::ast::ModEnumStmt::Field* > () = mgr->new_enum_stmt_field(yylhs.location, yystack_[3].value.as < TokenInfo > ().ID_intstr, std::move(yystack_[1].value.as < std::vector<pdm::ast::TypeSpec*> > ()), true); }
#line 2388 "parser.tab.cc"
    break;

  case 43: // mod_typeclass_stmt: tid "<" tid typespec ">" "=" "{" type_query_exp_sl "}"
#line 378 "parser.yy"
                                                                                     { 
        yylhs.value.as < pdm::ast::ModContentStmt* > () = mgr->new_mod_typeclass_stmt(yylhs.location, yystack_[8].value.as < TokenInfo > ().ID_intstr, yystack_[6].value.as < TokenInfo > ().ID_intstr, yystack_[5].value.as < pdm::ast::TypeSpec* > (), std::move(std::vector<ast::TPattern*>{}), std::move(yystack_[1].value.as < std::vector<pdm::ast::TypeQueryExp*> > ())); 
      }
#line 2396 "parser.tab.cc"
    break;

  case 44: // mod_typeclass_stmt: tid tpattern_seq "<" tid typespec ">" "=" "{" type_query_exp_sl "}"
#line 381 "parser.yy"
                                                                                     { 
        yylhs.value.as < pdm::ast::ModContentStmt* > () = mgr->new_mod_typeclass_stmt(yylhs.location, yystack_[9].value.as < TokenInfo > ().ID_intstr, yystack_[6].value.as < TokenInfo > ().ID_intstr, yystack_[5].value.as < pdm::ast::TypeSpec* > (), std::move(yystack_[8].value.as < std::vector<pdm::ast::TPattern*> > ()), std::move(yystack_[1].value.as < std::vector<pdm::ast::TypeQueryExp*> > ())); 
      }
#line 2404 "parser.tab.cc"
    break;

  case 45: // using_stmt: "using" vid "." "*"
#line 386 "parser.yy"
                                        { yylhs.value.as < pdm::ast::Stmt* > () = mgr->new_using_stmt(yylhs.location, yystack_[2].value.as < TokenInfo > ().ID_intstr, ""); }
#line 2410 "parser.tab.cc"
    break;

  case 46: // using_stmt: "using" vid "." vid "*"
#line 387 "parser.yy"
                                        { yylhs.value.as < pdm::ast::Stmt* > () = mgr->new_using_stmt(yylhs.location, yystack_[3].value.as < TokenInfo > ().ID_intstr, yystack_[1].value.as < TokenInfo > ().ID_intstr.content()); }
#line 2416 "parser.tab.cc"
    break;

  case 47: // import_stmt: "import" tid "from" stringl "type" stringl
#line 390 "parser.yy"
                                                       { yylhs.value.as < pdm::ast::Stmt* > () = mgr->new_import_stmt(yylhs.location, yystack_[4].value.as < TokenInfo > ().ID_intstr, *yystack_[2].value.as < TokenInfo > ().String_utf8string, *yystack_[0].value.as < TokenInfo > ().String_utf8string); }
#line 2422 "parser.tab.cc"
    break;

  case 48: // extern_stmt: "extern" tid "from" expr
#line 393 "parser.yy"
                                    { yylhs.value.as < pdm::ast::Stmt* > () = mgr->new_extern_stmt(yylhs.location, yystack_[2].value.as < TokenInfo > ().ID_intstr, yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2428 "parser.tab.cc"
    break;

  case 49: // tid: "<TypeId>"
#line 400 "parser.yy"
     { yylhs.value.as < TokenInfo > () = yystack_[0].value.as < TokenInfo > (); }
#line 2434 "parser.tab.cc"
    break;

  case 50: // vid: "<val_id>"
#line 401 "parser.yy"
     { yylhs.value.as < TokenInfo > () = yystack_[0].value.as < TokenInfo > (); }
#line 2440 "parser.tab.cc"
    break;

  case 51: // floatl: "4.2"
#line 403 "parser.yy"
      { yylhs.value.as < TokenInfo > () = yystack_[0].value.as < TokenInfo > (); }
#line 2446 "parser.tab.cc"
    break;

  case 52: // stringl: "'sq-string-literal'"
#line 406 "parser.yy"
      { yylhs.value.as < TokenInfo > () = yystack_[0].value.as < TokenInfo > (); }
#line 2452 "parser.tab.cc"
    break;

  case 53: // stringl: "\"dq-string-literal\""
#line 407 "parser.yy"
      { yylhs.value.as < TokenInfo > () = yystack_[0].value.as < TokenInfo > (); }
#line 2458 "parser.tab.cc"
    break;

  case 54: // mod_prefix: tid ":"
#line 410 "parser.yy"
                              { yylhs.value.as < std::vector<pdm::intern::String> > ().push_back(yystack_[1].value.as < TokenInfo > ().ID_intstr); }
#line 2464 "parser.tab.cc"
    break;

  case 55: // mod_prefix: mod_prefix vid ":"
#line 411 "parser.yy"
                              { yylhs.value.as < std::vector<pdm::intern::String> > () = std::move(yystack_[2].value.as < std::vector<pdm::intern::String> > ()); }
#line 2470 "parser.tab.cc"
    break;

  case 56: // expr: binary_exp
#line 418 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2476 "parser.tab.cc"
    break;

  case 57: // long_exp: expr
#line 421 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2482 "parser.tab.cc"
    break;

  case 58: // expr_cl0: %empty
#line 425 "parser.yy"
                             {}
#line 2488 "parser.tab.cc"
    break;

  case 59: // expr_cl0: expr_cl0 "," expr
#line 426 "parser.yy"
                             { yylhs.value.as < std::vector<pdm::ast::Exp*> > () = std::move(yystack_[2].value.as < std::vector<pdm::ast::Exp*> > ()); yylhs.value.as < std::vector<pdm::ast::Exp*> > ().push_back(yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2494 "parser.tab.cc"
    break;

  case 60: // expr_cl2: expr "," expr
#line 429 "parser.yy"
                             { yylhs.value.as < std::vector<pdm::ast::Exp*> > ().reserve(2); yylhs.value.as < std::vector<pdm::ast::Exp*> > ().push_back(yystack_[2].value.as < pdm::ast::Exp* > ()); yylhs.value.as < std::vector<pdm::ast::Exp*> > ().push_back(yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2500 "parser.tab.cc"
    break;

  case 61: // expr_cl2: expr_cl2 "," expr
#line 430 "parser.yy"
                             { yylhs.value.as < std::vector<pdm::ast::Exp*> > () = std::move(yystack_[2].value.as < std::vector<pdm::ast::Exp*> > ()); yylhs.value.as < std::vector<pdm::ast::Exp*> > ().push_back(yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2506 "parser.tab.cc"
    break;

  case 62: // type_query_exp_sl: type_query_exp ";"
#line 433 "parser.yy"
                                       { yylhs.value.as < std::vector<pdm::ast::TypeQueryExp*> > ().push_back(yystack_[1].value.as < pdm::ast::TypeQueryExp* > ()); }
#line 2512 "parser.tab.cc"
    break;

  case 63: // type_query_exp_sl: type_query_exp_sl type_query_exp ";"
#line 434 "parser.yy"
                                                 { yylhs.value.as < std::vector<pdm::ast::TypeQueryExp*> > () = std::move(yystack_[2].value.as < std::vector<pdm::ast::TypeQueryExp*> > ()); yylhs.value.as < std::vector<pdm::ast::TypeQueryExp*> > ().push_back(yystack_[1].value.as < pdm::ast::TypeQueryExp* > ()); }
#line 2518 "parser.tab.cc"
    break;

  case 64: // bracketed_exp: unit_exp
#line 438 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2524 "parser.tab.cc"
    break;

  case 65: // bracketed_exp: paren_exp
#line 439 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2530 "parser.tab.cc"
    break;

  case 66: // bracketed_exp: vtupleExpr
#line 440 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2536 "parser.tab.cc"
    break;

  case 67: // bracketed_exp: vstructExpr
#line 441 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2542 "parser.tab.cc"
    break;

  case 68: // bracketed_exp: chain_exp
#line 442 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2548 "parser.tab.cc"
    break;

  case 69: // unit_exp: "(" ")"
#line 445 "parser.yy"
                        { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_unit_exp(yylhs.location); }
#line 2554 "parser.tab.cc"
    break;

  case 70: // unit_exp: "{" "}"
#line 446 "parser.yy"
                        { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_unit_exp(yylhs.location); }
#line 2560 "parser.tab.cc"
    break;

  case 71: // paren_exp: "(" long_exp ")"
#line 449 "parser.yy"
                              { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_paren_exp(yylhs.location, yystack_[1].value.as < pdm::ast::Exp* > ()); }
#line 2566 "parser.tab.cc"
    break;

  case 72: // vtupleExpr: "(" expr "," ")"
#line 452 "parser.yy"
                                   { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_tuple_exp(yylhs.location, std::move(std::vector(1,yystack_[2].value.as < pdm::ast::Exp* > ()))); }
#line 2572 "parser.tab.cc"
    break;

  case 73: // vtupleExpr: "(" expr_cl2 ")"
#line 453 "parser.yy"
                                   { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_tuple_exp(yylhs.location, std::move(yystack_[1].value.as < std::vector<pdm::ast::Exp*> > ())); }
#line 2578 "parser.tab.cc"
    break;

  case 74: // vstructExpr: "{" struct_exp_field_cl "}"
#line 456 "parser.yy"
                                            { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_struct_exp(yylhs.location, std::move(yystack_[1].value.as < std::vector<pdm::ast::StructExp::Field*> > ())); }
#line 2584 "parser.tab.cc"
    break;

  case 75: // primary_exp: bracketed_exp
#line 459 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2590 "parser.tab.cc"
    break;

  case 76: // primary_exp: vid
#line 460 "parser.yy"
                     { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_id_exp(yylhs.location, yystack_[0].value.as < TokenInfo > ().ID_intstr); }
#line 2596 "parser.tab.cc"
    break;

  case 77: // primary_exp: int_expr
#line 461 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2602 "parser.tab.cc"
    break;

  case 78: // primary_exp: floatl
#line 462 "parser.yy"
                     { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_float_exp(yylhs.location, yystack_[0].value.as < TokenInfo > ().Float); }
#line 2608 "parser.tab.cc"
    break;

  case 79: // primary_exp: stringls
#line 463 "parser.yy"
                     { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_string_exp(yylhs.location, std::move(yystack_[0].value.as < std::vector<pdm::ast::StringExp::Piece> > ())); }
#line 2614 "parser.tab.cc"
    break;

  case 80: // primary_exp: if_exp
#line 464 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2620 "parser.tab.cc"
    break;

  case 81: // primary_exp: lambda_exp
#line 465 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2626 "parser.tab.cc"
    break;

  case 82: // int_expr: "42"
#line 468 "parser.yy"
                { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_int_exp(yylhs.location, yystack_[0].value.as < TokenInfo > ().Int, ast::IntExp::Base::Dec); }
#line 2632 "parser.tab.cc"
    break;

  case 83: // int_expr: "0x2a"
#line 469 "parser.yy"
                { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_int_exp(yylhs.location, yystack_[0].value.as < TokenInfo > ().Int, ast::IntExp::Base::Hex); }
#line 2638 "parser.tab.cc"
    break;

  case 84: // stringls: "'sq-string-literal'"
#line 472 "parser.yy"
                             { yylhs.value.as < std::vector<pdm::ast::StringExp::Piece> > ().emplace_back(yylhs.location, *yystack_[0].value.as < TokenInfo > ().String_utf8string, ast::StringExp::QuoteKind::SingleQuote); }
#line 2644 "parser.tab.cc"
    break;

  case 85: // stringls: "\"dq-string-literal\""
#line 473 "parser.yy"
                             { yylhs.value.as < std::vector<pdm::ast::StringExp::Piece> > ().emplace_back(yylhs.location, *yystack_[0].value.as < TokenInfo > ().String_utf8string, ast::StringExp::QuoteKind::DoubleQuote); }
#line 2650 "parser.tab.cc"
    break;

  case 86: // stringls: stringls "'sq-string-literal'"
#line 474 "parser.yy"
                             { yylhs.value.as < std::vector<pdm::ast::StringExp::Piece> > () = std::move(yystack_[1].value.as < std::vector<pdm::ast::StringExp::Piece> > ()); yylhs.value.as < std::vector<pdm::ast::StringExp::Piece> > ().emplace_back(yystack_[0].location, *yystack_[0].value.as < TokenInfo > ().String_utf8string, ast::StringExp::QuoteKind::SingleQuote); }
#line 2656 "parser.tab.cc"
    break;

  case 87: // stringls: stringls "\"dq-string-literal\""
#line 475 "parser.yy"
                             { yylhs.value.as < std::vector<pdm::ast::StringExp::Piece> > () = std::move(yystack_[1].value.as < std::vector<pdm::ast::StringExp::Piece> > ()); yylhs.value.as < std::vector<pdm::ast::StringExp::Piece> > ().emplace_back(yystack_[0].location, *yystack_[0].value.as < TokenInfo > ().String_utf8string, ast::StringExp::QuoteKind::DoubleQuote); }
#line 2662 "parser.tab.cc"
    break;

  case 88: // if_exp: "if" bracketed_exp "then" bracketed_exp
#line 478 "parser.yy"
                                                                        { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_if_exp(yylhs.location, yystack_[2].value.as < pdm::ast::Exp* > (), yystack_[0].value.as < pdm::ast::Exp* > (), nullptr); }
#line 2668 "parser.tab.cc"
    break;

  case 89: // if_exp: "if" bracketed_exp "then" bracketed_exp "else" primary_exp
#line 479 "parser.yy"
                                                                        { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_if_exp(yylhs.location, yystack_[4].value.as < pdm::ast::Exp* > (), yystack_[2].value.as < pdm::ast::Exp* > (), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2674 "parser.tab.cc"
    break;

  case 90: // chain_exp: "{" expr "}"
#line 482 "parser.yy"
                                          { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_chain_exp(yylhs.location, std::move(std::vector<ast::Stmt*>{}), yystack_[1].value.as < pdm::ast::Exp* > ()); }
#line 2680 "parser.tab.cc"
    break;

  case 91: // chain_exp: "{" chain_prefix "}"
#line 483 "parser.yy"
                                           { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_chain_exp(yylhs.location, std::move(yystack_[1].value.as < std::vector<pdm::ast::Stmt*> > ()), nullptr); }
#line 2686 "parser.tab.cc"
    break;

  case 92: // chain_exp: "{" chain_prefix expr "}"
#line 484 "parser.yy"
                                           { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_chain_exp(yylhs.location, std::move(yystack_[2].value.as < std::vector<pdm::ast::Stmt*> > ()), yystack_[1].value.as < pdm::ast::Exp* > ()); }
#line 2692 "parser.tab.cc"
    break;

  case 93: // chain_prefix: chain_prefix_stmt ";"
#line 487 "parser.yy"
                                               { yylhs.value.as < std::vector<pdm::ast::Stmt*> > ().push_back(yystack_[1].value.as < pdm::ast::Stmt* > ()); }
#line 2698 "parser.tab.cc"
    break;

  case 94: // chain_prefix: chain_prefix chain_prefix_stmt ";"
#line 488 "parser.yy"
                                                { yylhs.value.as < std::vector<pdm::ast::Stmt*> > () = std::move(yystack_[2].value.as < std::vector<pdm::ast::Stmt*> > ()); yylhs.value.as < std::vector<pdm::ast::Stmt*> > ().push_back(yystack_[1].value.as < pdm::ast::Stmt* > ()); }
#line 2704 "parser.tab.cc"
    break;

  case 95: // lambda_exp: "fn" vpattern bracketed_exp
#line 491 "parser.yy"
                                                    { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_lambda_exp(yylhs.location, yystack_[1].value.as < pdm::ast::VPattern* > (), nullptr, yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2710 "parser.tab.cc"
    break;

  case 96: // lambda_exp: "fn" vpattern "->" typespec bracketed_exp
#line 492 "parser.yy"
                                                    { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_lambda_exp(yylhs.location, yystack_[3].value.as < pdm::ast::VPattern* > (), yystack_[1].value.as < pdm::ast::TypeSpec* > (), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2716 "parser.tab.cc"
    break;

  case 97: // postfix_exp: primary_exp
#line 496 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2722 "parser.tab.cc"
    break;

  case 98: // postfix_exp: tcall_exp
#line 497 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2728 "parser.tab.cc"
    break;

  case 99: // postfix_exp: vcall_exp
#line 498 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2734 "parser.tab.cc"
    break;

  case 100: // postfix_exp: dot_name_exp
#line 499 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2740 "parser.tab.cc"
    break;

  case 101: // postfix_exp: dot_index_exp
#line 500 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2746 "parser.tab.cc"
    break;

  case 102: // tcall_exp: postfix_exp "[" targ_cl "]"
#line 503 "parser.yy"
                                         { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_tcall_exp(yylhs.location, yystack_[3].value.as < pdm::ast::Exp* > (), std::move(yystack_[1].value.as < std::vector<pdm::ast::TArg*> > ())); }
#line 2752 "parser.tab.cc"
    break;

  case 103: // vcall_exp: postfix_exp "(" ")"
#line 506 "parser.yy"
                                            { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_vcall_exp(yylhs.location, yystack_[2].value.as < pdm::ast::Exp* > (), std::move(std::vector<ast::VArg*>{})); }
#line 2758 "parser.tab.cc"
    break;

  case 104: // vcall_exp: postfix_exp "(" varg_cl ")"
#line 507 "parser.yy"
                                            { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_vcall_exp(yylhs.location, yystack_[3].value.as < pdm::ast::Exp* > (), std::move(yystack_[1].value.as < std::vector<pdm::ast::VArg*> > ())); }
#line 2764 "parser.tab.cc"
    break;

  case 105: // dot_name_exp: postfix_exp "." "<val_id>"
#line 510 "parser.yy"
                                                    { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_struct_dot_name_exp(yylhs.location, yystack_[2].value.as < pdm::ast::Exp* > (), yystack_[0].value.as < TokenInfo > ().ID_intstr); }
#line 2770 "parser.tab.cc"
    break;

  case 106: // dot_name_exp: postfix_exp "." "<TypeId>" "(" expr_cl0 ")"
#line 511 "parser.yy"
                                                    { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_enum_dot_name_exp(yylhs.location, yystack_[5].value.as < pdm::ast::Exp* > (), yystack_[3].value.as < TokenInfo > ().ID_intstr, std::move(yystack_[1].value.as < std::vector<pdm::ast::Exp*> > ())); }
#line 2776 "parser.tab.cc"
    break;

  case 107: // dot_name_exp: mod_prefix "<val_id>"
#line 512 "parser.yy"
                       { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_module_dot_exp(yylhs.location, std::move(yystack_[1].value.as < std::vector<pdm::intern::String> > ()), yystack_[0].value.as < TokenInfo > ().ID_intstr); }
#line 2782 "parser.tab.cc"
    break;

  case 108: // dot_index_exp: postfix_exp "." int_expr
#line 515 "parser.yy"
                                    { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_dot_index_exp(yylhs.location, yystack_[2].value.as < pdm::ast::Exp* > (), yystack_[0].value.as < pdm::ast::Exp* > (), ast::DotIndexExp::RhsHint::LhsNotPtr); }
#line 2788 "parser.tab.cc"
    break;

  case 109: // dot_index_exp: postfix_exp "." bracketed_exp
#line 516 "parser.yy"
                                    { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_dot_index_exp(yylhs.location, yystack_[2].value.as < pdm::ast::Exp* > (), yystack_[0].value.as < pdm::ast::Exp* > (), ast::DotIndexExp::RhsHint::LhsNotPtr); }
#line 2794 "parser.tab.cc"
    break;

  case 110: // unary_exp: postfix_exp
#line 520 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2800 "parser.tab.cc"
    break;

  case 111: // unary_exp: unary_op unary_exp
#line 521 "parser.yy"
                             { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_unary_exp(yylhs.location, yystack_[1].value.as < pdm::ast::UnaryOperator > (), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2806 "parser.tab.cc"
    break;

  case 112: // unary_op: "+"
#line 524 "parser.yy"
                 { yylhs.value.as < pdm::ast::UnaryOperator > () = ast::UnaryOperator::Plus; }
#line 2812 "parser.tab.cc"
    break;

  case 113: // unary_op: "-"
#line 525 "parser.yy"
                 { yylhs.value.as < pdm::ast::UnaryOperator > () = ast::UnaryOperator::Minus; }
#line 2818 "parser.tab.cc"
    break;

  case 114: // unary_op: "*"
#line 526 "parser.yy"
                 { yylhs.value.as < pdm::ast::UnaryOperator > () = ast::UnaryOperator::DeRef; }
#line 2824 "parser.tab.cc"
    break;

  case 115: // unary_op: "^"
#line 527 "parser.yy"
                 { yylhs.value.as < pdm::ast::UnaryOperator > () = ast::UnaryOperator::GetRef; }
#line 2830 "parser.tab.cc"
    break;

  case 116: // unary_op: "not"
#line 528 "parser.yy"
                 { yylhs.value.as < pdm::ast::UnaryOperator > () = ast::UnaryOperator::Not; }
#line 2836 "parser.tab.cc"
    break;

  case 117: // binary_exp: or_binary_exp
#line 532 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2842 "parser.tab.cc"
    break;

  case 118: // mul_binary_op: "*"
#line 535 "parser.yy"
                 { yylhs.value.as < pdm::ast::BinaryOperator > () = ast::BinaryOperator::Mul; }
#line 2848 "parser.tab.cc"
    break;

  case 119: // mul_binary_op: "/"
#line 536 "parser.yy"
                 { yylhs.value.as < pdm::ast::BinaryOperator > () = ast::BinaryOperator::Div; }
#line 2854 "parser.tab.cc"
    break;

  case 120: // mul_binary_op: "%"
#line 537 "parser.yy"
                 { yylhs.value.as < pdm::ast::BinaryOperator > () = ast::BinaryOperator::Rem; }
#line 2860 "parser.tab.cc"
    break;

  case 121: // mul_binary_exp: unary_exp
#line 540 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2866 "parser.tab.cc"
    break;

  case 122: // mul_binary_exp: mul_binary_exp mul_binary_op unary_exp
#line 541 "parser.yy"
                                               { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_binary_exp(yylhs.location, yystack_[1].value.as < pdm::ast::BinaryOperator > (), yystack_[2].value.as < pdm::ast::Exp* > (), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2872 "parser.tab.cc"
    break;

  case 123: // add_binary_op: "+"
#line 544 "parser.yy"
             { yylhs.value.as < pdm::ast::BinaryOperator > () = ast::BinaryOperator::Add; }
#line 2878 "parser.tab.cc"
    break;

  case 124: // add_binary_op: "-"
#line 545 "parser.yy"
             { yylhs.value.as < pdm::ast::BinaryOperator > () = ast::BinaryOperator::Subtract; }
#line 2884 "parser.tab.cc"
    break;

  case 125: // add_binary_exp: mul_binary_exp
#line 548 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2890 "parser.tab.cc"
    break;

  case 126: // add_binary_exp: add_binary_exp add_binary_op mul_binary_exp
#line 549 "parser.yy"
                                                    { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_binary_exp(yylhs.location, yystack_[1].value.as < pdm::ast::BinaryOperator > (), yystack_[2].value.as < pdm::ast::Exp* > (), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2896 "parser.tab.cc"
    break;

  case 127: // cmp_binary_op: "<"
#line 552 "parser.yy"
                { yylhs.value.as < pdm::ast::BinaryOperator > () = ast::BinaryOperator::Less; }
#line 2902 "parser.tab.cc"
    break;

  case 128: // cmp_binary_op: "<="
#line 553 "parser.yy"
                { yylhs.value.as < pdm::ast::BinaryOperator > () = ast::BinaryOperator::LessOrEq; }
#line 2908 "parser.tab.cc"
    break;

  case 129: // cmp_binary_op: ">"
#line 554 "parser.yy"
                { yylhs.value.as < pdm::ast::BinaryOperator > () = ast::BinaryOperator::Greater; }
#line 2914 "parser.tab.cc"
    break;

  case 130: // cmp_binary_op: ">="
#line 555 "parser.yy"
                { yylhs.value.as < pdm::ast::BinaryOperator > () = ast::BinaryOperator::GreaterOrEq; }
#line 2920 "parser.tab.cc"
    break;

  case 131: // cmp_binary_exp: add_binary_exp
#line 558 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2926 "parser.tab.cc"
    break;

  case 132: // cmp_binary_exp: cmp_binary_exp cmp_binary_op add_binary_exp
#line 559 "parser.yy"
                                                    { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_binary_exp(yylhs.location, yystack_[1].value.as < pdm::ast::BinaryOperator > (), yystack_[2].value.as < pdm::ast::Exp* > (), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2932 "parser.tab.cc"
    break;

  case 133: // eq_binary_op: "=="
#line 562 "parser.yy"
                 { yylhs.value.as < pdm::ast::BinaryOperator > () = ast::BinaryOperator::Equals; }
#line 2938 "parser.tab.cc"
    break;

  case 134: // eq_binary_op: "!="
#line 563 "parser.yy"
                 { yylhs.value.as < pdm::ast::BinaryOperator > () = ast::BinaryOperator::NotEquals; }
#line 2944 "parser.tab.cc"
    break;

  case 135: // eq_binary_exp: cmp_binary_exp
#line 566 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2950 "parser.tab.cc"
    break;

  case 136: // eq_binary_exp: eq_binary_exp eq_binary_op cmp_binary_exp
#line 567 "parser.yy"
                                                { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_binary_exp(yylhs.location, yystack_[1].value.as < pdm::ast::BinaryOperator > (), yystack_[2].value.as < pdm::ast::Exp* > (), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2956 "parser.tab.cc"
    break;

  case 137: // and_binary_exp: eq_binary_exp
#line 570 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2962 "parser.tab.cc"
    break;

  case 138: // and_binary_exp: and_binary_exp "and" eq_binary_exp
#line 571 "parser.yy"
                                           { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_binary_exp(yylhs.location, ast::BinaryOperator::And, yystack_[2].value.as < pdm::ast::Exp* > (), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2968 "parser.tab.cc"
    break;

  case 139: // xor_binary_exp: and_binary_exp
#line 574 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2974 "parser.tab.cc"
    break;

  case 140: // xor_binary_exp: xor_binary_exp "xor" and_binary_exp
#line 575 "parser.yy"
                                           { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_binary_exp(yylhs.location, ast::BinaryOperator::XOr, yystack_[2].value.as < pdm::ast::Exp* > (), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2980 "parser.tab.cc"
    break;

  case 141: // or_binary_exp: xor_binary_exp
#line 578 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2986 "parser.tab.cc"
    break;

  case 142: // or_binary_exp: or_binary_exp "or" xor_binary_exp
#line 579 "parser.yy"
                                           { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_binary_exp(yylhs.location, ast::BinaryOperator::Or, yystack_[2].value.as < pdm::ast::Exp* > (), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2992 "parser.tab.cc"
    break;

  case 143: // type_query_exp: typespec type_query_op typespec
#line 583 "parser.yy"
                                        { yylhs.value.as < pdm::ast::TypeQueryExp* > () = mgr->new_type_query_exp(yylhs.location, yystack_[1].value.as < pdm::ast::TypeQueryKind > (), yystack_[2].value.as < pdm::ast::TypeSpec* > (), yystack_[0].value.as < pdm::ast::TypeSpec* > ()); }
#line 2998 "parser.tab.cc"
    break;

  case 144: // type_query_op: ":<"
#line 586 "parser.yy"
                    { yylhs.value.as < pdm::ast::TypeQueryKind > () = ast::TypeQueryKind::LhsSubtypesRhs; }
#line 3004 "parser.tab.cc"
    break;

  case 145: // type_query_op: ">:"
#line 587 "parser.yy"
                    { yylhs.value.as < pdm::ast::TypeQueryKind > () = ast::TypeQueryKind::LhsSupertypesRhs; }
#line 3010 "parser.tab.cc"
    break;

  case 146: // type_query_op: "::"
#line 588 "parser.yy"
                    { yylhs.value.as < pdm::ast::TypeQueryKind > () = ast::TypeQueryKind::LhsEqualsRhs; }
#line 3016 "parser.tab.cc"
    break;

  case 147: // typespec: unary_typespec
#line 596 "parser.yy"
      { yylhs.value.as < pdm::ast::TypeSpec* > () = yystack_[0].value.as < pdm::ast::TypeSpec* > (); }
#line 3022 "parser.tab.cc"
    break;

  case 148: // typespec_cl1: typespec
#line 599 "parser.yy"
                                  { yylhs.value.as < std::vector<pdm::ast::TypeSpec*> > ().push_back(yystack_[0].value.as < pdm::ast::TypeSpec* > ()); }
#line 3028 "parser.tab.cc"
    break;

  case 149: // typespec_cl1: typespec_cl1 "," typespec
#line 600 "parser.yy"
                                  { yylhs.value.as < std::vector<pdm::ast::TypeSpec*> > () = std::move(yystack_[2].value.as < std::vector<pdm::ast::TypeSpec*> > ()); yylhs.value.as < std::vector<pdm::ast::TypeSpec*> > ().push_back(yystack_[0].value.as < pdm::ast::TypeSpec* > ()); }
#line 3034 "parser.tab.cc"
    break;

  case 150: // typespec_cl2: typespec "," typespec
#line 603 "parser.yy"
                                  { yylhs.value.as < std::vector<pdm::ast::TypeSpec*> > ().reserve(2); yylhs.value.as < std::vector<pdm::ast::TypeSpec*> > ().push_back(yystack_[2].value.as < pdm::ast::TypeSpec* > ()); yylhs.value.as < std::vector<pdm::ast::TypeSpec*> > ().push_back(yystack_[0].value.as < pdm::ast::TypeSpec* > ()); }
#line 3040 "parser.tab.cc"
    break;

  case 151: // typespec_cl2: typespec_cl2 "," typespec
#line 604 "parser.yy"
                                  { yylhs.value.as < std::vector<pdm::ast::TypeSpec*> > () = std::move(yystack_[2].value.as < std::vector<pdm::ast::TypeSpec*> > ()); yylhs.value.as < std::vector<pdm::ast::TypeSpec*> > ().push_back(yystack_[0].value.as < pdm::ast::TypeSpec* > ()); }
#line 3046 "parser.tab.cc"
    break;

  case 152: // struct_typespec_field: vid typespec
#line 608 "parser.yy"
                                  { yylhs.value.as < pdm::ast::StructTypeSpec::Field* > () = mgr->new_struct_typespec_field(yylhs.location, yystack_[1].value.as < TokenInfo > ().ID_intstr, yystack_[0].value.as < pdm::ast::TypeSpec* > ()); }
#line 3052 "parser.tab.cc"
    break;

  case 153: // struct_typespec_field_cl: struct_typespec_field
#line 611 "parser.yy"
                                                          { yylhs.value.as < std::vector<pdm::ast::StructTypeSpec::Field*> > ().push_back(yystack_[0].value.as < pdm::ast::StructTypeSpec::Field* > ()); }
#line 3058 "parser.tab.cc"
    break;

  case 154: // struct_typespec_field_cl: struct_typespec_field_cl "," struct_typespec_field
#line 612 "parser.yy"
                                                            { yylhs.value.as < std::vector<pdm::ast::StructTypeSpec::Field*> > () = std::move(yystack_[2].value.as < std::vector<pdm::ast::StructTypeSpec::Field*> > ()); yylhs.value.as < std::vector<pdm::ast::StructTypeSpec::Field*> > ().push_back(yystack_[0].value.as < pdm::ast::StructTypeSpec::Field* > ()); }
#line 3064 "parser.tab.cc"
    break;

  case 155: // primary_typespec: tid
#line 616 "parser.yy"
                        { yylhs.value.as < pdm::ast::TypeSpec* > () = mgr->new_id_typespec(yylhs.location, yystack_[0].value.as < TokenInfo > ().ID_intstr); }
#line 3070 "parser.tab.cc"
    break;

  case 156: // primary_typespec: paren_typespec
#line 617 "parser.yy"
      { yylhs.value.as < pdm::ast::TypeSpec* > () = yystack_[0].value.as < pdm::ast::TypeSpec* > (); }
#line 3076 "parser.tab.cc"
    break;

  case 157: // primary_typespec: tuple_typespec
#line 618 "parser.yy"
      { yylhs.value.as < pdm::ast::TypeSpec* > () = yystack_[0].value.as < pdm::ast::TypeSpec* > (); }
#line 3082 "parser.tab.cc"
    break;

  case 158: // primary_typespec: mod_prefix_tid
#line 619 "parser.yy"
      { yylhs.value.as < pdm::ast::TypeSpec* > () = yystack_[0].value.as < pdm::ast::TypeSpec* > (); }
#line 3088 "parser.tab.cc"
    break;

  case 159: // primary_typespec: fn_typespec
#line 620 "parser.yy"
      { yylhs.value.as < pdm::ast::TypeSpec* > () = yystack_[0].value.as < pdm::ast::TypeSpec* > (); }
#line 3094 "parser.tab.cc"
    break;

  case 160: // paren_typespec: "(" typespec ")"
#line 623 "parser.yy"
                                { yylhs.value.as < pdm::ast::TypeSpec* > () = mgr->new_paren_typespec(yylhs.location, yystack_[1].value.as < pdm::ast::TypeSpec* > ()); }
#line 3100 "parser.tab.cc"
    break;

  case 161: // tuple_typespec: "(" typespec "," ")"
#line 626 "parser.yy"
                                    { yylhs.value.as < pdm::ast::TypeSpec* > () = mgr->new_tuple_typespec(yylhs.location, std::move(std::vector(1,yystack_[2].value.as < pdm::ast::TypeSpec* > ()))); }
#line 3106 "parser.tab.cc"
    break;

  case 162: // tuple_typespec: "(" typespec_cl2 ")"
#line 627 "parser.yy"
                                    { yylhs.value.as < pdm::ast::TypeSpec* > () = mgr->new_tuple_typespec(yylhs.location, std::move(yystack_[1].value.as < std::vector<pdm::ast::TypeSpec*> > ())); }
#line 3112 "parser.tab.cc"
    break;

  case 163: // mod_prefix_tid: mod_prefix tid
#line 630 "parser.yy"
                            { yylhs.value.as < pdm::ast::TypeSpec* > () = mgr->new_dot_name_typespec_with_mod_prefix(yylhs.location, std::move(yystack_[1].value.as < std::vector<pdm::intern::String> > ()), yystack_[0].value.as < TokenInfo > ().ID_intstr); }
#line 3118 "parser.tab.cc"
    break;

  case 164: // fn_typespec: "Fn" vpattern primary_typespec
#line 633 "parser.yy"
                                       { yylhs.value.as < pdm::ast::TypeSpec* > () = mgr->new_fn_typespec(yylhs.location, std::move(yystack_[1].value.as < pdm::ast::VPattern* > ()), yystack_[0].value.as < pdm::ast::TypeSpec* > ()); }
#line 3124 "parser.tab.cc"
    break;

  case 165: // postfix_typespec: primary_typespec
#line 637 "parser.yy"
      { yylhs.value.as < pdm::ast::TypeSpec* > () = yystack_[0].value.as < pdm::ast::TypeSpec* > (); }
#line 3130 "parser.tab.cc"
    break;

  case 166: // postfix_typespec: tcall_typespec
#line 638 "parser.yy"
      { yylhs.value.as < pdm::ast::TypeSpec* > () = yystack_[0].value.as < pdm::ast::TypeSpec* > (); }
#line 3136 "parser.tab.cc"
    break;

  case 167: // tcall_typespec: postfix_typespec "[" targ_cl "]"
#line 641 "parser.yy"
                                              { yylhs.value.as < pdm::ast::TypeSpec* > () = mgr->new_tcall_typespec(yylhs.location, yystack_[3].value.as < pdm::ast::TypeSpec* > (), std::move(yystack_[1].value.as < std::vector<pdm::ast::TArg*> > ())); }
#line 3142 "parser.tab.cc"
    break;

  case 168: // unary_typespec: postfix_typespec
#line 645 "parser.yy"
      { yylhs.value.as < pdm::ast::TypeSpec* > () = yystack_[0].value.as < pdm::ast::TypeSpec* > (); }
#line 3148 "parser.tab.cc"
    break;

  case 169: // long_typespec: unary_typespec
#line 649 "parser.yy"
      { yylhs.value.as < pdm::ast::TypeSpec* > () = yystack_[0].value.as < pdm::ast::TypeSpec* > (); }
#line 3154 "parser.tab.cc"
    break;

  case 170: // long_typespec: struct_typespec
#line 650 "parser.yy"
      { yylhs.value.as < pdm::ast::TypeSpec* > () = yystack_[0].value.as < pdm::ast::TypeSpec* > (); }
#line 3160 "parser.tab.cc"
    break;

  case 171: // struct_typespec: "{" struct_typespec_field_cl "}"
#line 653 "parser.yy"
                                              { yylhs.value.as < pdm::ast::TypeSpec* > () = mgr->new_struct_typespec(yylhs.location, std::move(yystack_[1].value.as < std::vector<pdm::ast::StructTypeSpec::Field*> > ())); }
#line 3166 "parser.tab.cc"
    break;

  case 172: // targ: typespec
#line 656 "parser.yy"
               { yylhs.value.as < pdm::ast::TArg* > () = mgr->new_targ_typespec(yylhs.location, yystack_[0].value.as < pdm::ast::TypeSpec* > ()); }
#line 3172 "parser.tab.cc"
    break;

  case 173: // targ: expr
#line 657 "parser.yy"
               { yylhs.value.as < pdm::ast::TArg* > () = mgr->new_targ_exp(yylhs.location, yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 3178 "parser.tab.cc"
    break;

  case 174: // targ_cl: targ
#line 660 "parser.yy"
                            { yylhs.value.as < std::vector<pdm::ast::TArg*> > ().push_back(yystack_[0].value.as < pdm::ast::TArg* > ()); }
#line 3184 "parser.tab.cc"
    break;

  case 175: // targ_cl: targ_cl "," targ
#line 661 "parser.yy"
                            { yylhs.value.as < std::vector<pdm::ast::TArg*> > () = std::move(yystack_[2].value.as < std::vector<pdm::ast::TArg*> > ()); yylhs.value.as < std::vector<pdm::ast::TArg*> > ().push_back(yystack_[0].value.as < pdm::ast::TArg* > ()); }
#line 3190 "parser.tab.cc"
    break;

  case 176: // varg: expr
#line 663 "parser.yy"
                            { yylhs.value.as < pdm::ast::VArg* > () = mgr->new_varg(yylhs.location, yystack_[0].value.as < pdm::ast::Exp* > (), ast::VArgAccessSpec::In); }
#line 3196 "parser.tab.cc"
    break;

  case 177: // varg: "out" expr
#line 664 "parser.yy"
                            { yylhs.value.as < pdm::ast::VArg* > () = mgr->new_varg(yylhs.location, yystack_[0].value.as < pdm::ast::Exp* > (), ast::VArgAccessSpec::Out); }
#line 3202 "parser.tab.cc"
    break;

  case 178: // varg: "inout" expr
#line 665 "parser.yy"
                            { yylhs.value.as < pdm::ast::VArg* > () = mgr->new_varg(yylhs.location, yystack_[0].value.as < pdm::ast::Exp* > (), ast::VArgAccessSpec::InOut); }
#line 3208 "parser.tab.cc"
    break;

  case 179: // varg_cl: varg
#line 668 "parser.yy"
                            { yylhs.value.as < std::vector<pdm::ast::VArg*> > ().push_back(yystack_[0].value.as < pdm::ast::VArg* > ()); }
#line 3214 "parser.tab.cc"
    break;

  case 180: // varg_cl: varg_cl "," varg
#line 669 "parser.yy"
                            { yylhs.value.as < std::vector<pdm::ast::VArg*> > () = std::move(yystack_[2].value.as < std::vector<pdm::ast::VArg*> > ()); yylhs.value.as < std::vector<pdm::ast::VArg*> > ().push_back(yystack_[0].value.as < pdm::ast::VArg* > ()); }
#line 3220 "parser.tab.cc"
    break;

  case 181: // struct_exp_field: vid "=" expr
#line 677 "parser.yy"
                    { yylhs.value.as < pdm::ast::StructExp::Field* > () = mgr->new_struct_exp_field(yylhs.location, yystack_[2].value.as < TokenInfo > ().ID_intstr, yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 3226 "parser.tab.cc"
    break;

  case 182: // vpattern_field: vid typespec
#line 680 "parser.yy"
                            { yylhs.value.as < pdm::ast::VPattern::Field* > () = mgr->new_vpattern_field(yylhs.location, yystack_[1].value.as < TokenInfo > ().ID_intstr, yystack_[0].value.as < pdm::ast::TypeSpec* > (), ast::VArgAccessSpec::In); }
#line 3232 "parser.tab.cc"
    break;

  case 183: // vpattern_field: "out" vid typespec
#line 681 "parser.yy"
                            { yylhs.value.as < pdm::ast::VPattern::Field* > () = mgr->new_vpattern_field(yylhs.location, yystack_[1].value.as < TokenInfo > ().ID_intstr, yystack_[0].value.as < pdm::ast::TypeSpec* > (), ast::VArgAccessSpec::Out); }
#line 3238 "parser.tab.cc"
    break;

  case 184: // vpattern_field: "inout" vid typespec
#line 682 "parser.yy"
                            { yylhs.value.as < pdm::ast::VPattern::Field* > () = mgr->new_vpattern_field(yylhs.location, yystack_[1].value.as < TokenInfo > ().ID_intstr, yystack_[0].value.as < pdm::ast::TypeSpec* > (), ast::VArgAccessSpec::InOut); }
#line 3244 "parser.tab.cc"
    break;

  case 185: // lpattern_field: vid typespec
#line 685 "parser.yy"
                    { yylhs.value.as < pdm::ast::LPattern::Field* > () = mgr->new_lpattern_field(yylhs.location, ast::LPattern::FieldKind::IdTypeSpecPair, yystack_[1].value.as < TokenInfo > ().ID_intstr, yystack_[0].value.as < pdm::ast::TypeSpec* > ()); }
#line 3250 "parser.tab.cc"
    break;

  case 186: // lpattern_field: vid
#line 686 "parser.yy"
                    { yylhs.value.as < pdm::ast::LPattern::Field* > () = mgr->new_lpattern_field(yylhs.location, ast::LPattern::FieldKind::IdSingleton, yystack_[0].value.as < TokenInfo > ().ID_intstr); }
#line 3256 "parser.tab.cc"
    break;

  case 187: // tpattern_field: vid typespec
#line 689 "parser.yy"
                    { yylhs.value.as < pdm::ast::TPattern::Field* > () = mgr->new_tpattern_field(yylhs.location, ast::TPattern::FieldKind::Value, yystack_[1].value.as < TokenInfo > ().ID_intstr, yystack_[0].value.as < pdm::ast::TypeSpec* > ()); }
#line 3262 "parser.tab.cc"
    break;

  case 188: // tpattern_field: tid typespec
#line 690 "parser.yy"
                    { yylhs.value.as < pdm::ast::TPattern::Field* > () = mgr->new_tpattern_field(yylhs.location, ast::TPattern::FieldKind::Type, yystack_[1].value.as < TokenInfo > ().ID_intstr, yystack_[0].value.as < pdm::ast::TypeSpec* > ()); }
#line 3268 "parser.tab.cc"
    break;

  case 189: // destructured_lpattern: "(" lpattern_field_cl ")"
#line 694 "parser.yy"
                                          { yylhs.value.as < pdm::ast::LPattern* > () = mgr->new_lpattern(yylhs.location, std::move(yystack_[1].value.as < std::vector<pdm::ast::LPattern::Field*> > ()), true); }
#line 3274 "parser.tab.cc"
    break;

  case 190: // lpattern: lpattern_field
#line 698 "parser.yy"
                        { yylhs.value.as < pdm::ast::LPattern* > () = mgr->new_lpattern(yylhs.location, std::move(std::vector<ast::LPattern::Field*>{1,yystack_[0].value.as < pdm::ast::LPattern::Field* > ()}), false); }
#line 3280 "parser.tab.cc"
    break;

  case 191: // lpattern: destructured_lpattern
#line 699 "parser.yy"
      { yylhs.value.as < pdm::ast::LPattern* > () = yystack_[0].value.as < pdm::ast::LPattern* > (); }
#line 3286 "parser.tab.cc"
    break;

  case 192: // vpattern: "(" vpattern_field_cl ")"
#line 702 "parser.yy"
                                       { yylhs.value.as < pdm::ast::VPattern* > () = mgr->new_vpattern(yylhs.location, std::move(yystack_[1].value.as < std::vector<pdm::ast::VPattern::Field*> > ())); }
#line 3292 "parser.tab.cc"
    break;

  case 193: // vpattern: "(" ")"
#line 703 "parser.yy"
                                       { yylhs.value.as < pdm::ast::VPattern* > () = mgr->new_vpattern(yylhs.location, std::move(std::vector<ast::VPattern::Field*>{})); }
#line 3298 "parser.tab.cc"
    break;

  case 194: // tpattern: "[" tpattern_field_cl "]"
#line 706 "parser.yy"
                                               { yylhs.value.as < pdm::ast::TPattern* > () = mgr->new_tpattern(yylhs.location, std::move(yystack_[1].value.as < std::vector<pdm::ast::TPattern::Field*> > ()), false); }
#line 3304 "parser.tab.cc"
    break;

  case 195: // tpattern: "!" "[" tpattern_field_cl "]"
#line 707 "parser.yy"
                                               { yylhs.value.as < pdm::ast::TPattern* > () = mgr->new_tpattern(yylhs.location, std::move(yystack_[1].value.as < std::vector<pdm::ast::TPattern::Field*> > ()), true); }
#line 3310 "parser.tab.cc"
    break;

  case 196: // vpattern_field_cl: vpattern_field
#line 711 "parser.yy"
                                              { yylhs.value.as < std::vector<pdm::ast::VPattern::Field*> > ().push_back(yystack_[0].value.as < pdm::ast::VPattern::Field* > ()); }
#line 3316 "parser.tab.cc"
    break;

  case 197: // vpattern_field_cl: vpattern_field_cl "," vpattern_field
#line 712 "parser.yy"
                                               { yylhs.value.as < std::vector<pdm::ast::VPattern::Field*> > () = std::move(yystack_[2].value.as < std::vector<pdm::ast::VPattern::Field*> > ()); yylhs.value.as < std::vector<pdm::ast::VPattern::Field*> > ().push_back(yystack_[0].value.as < pdm::ast::VPattern::Field* > ()); }
#line 3322 "parser.tab.cc"
    break;

  case 198: // lpattern_field_cl: lpattern_field
#line 715 "parser.yy"
                                              { yylhs.value.as < std::vector<pdm::ast::LPattern::Field*> > ().push_back(yystack_[0].value.as < pdm::ast::LPattern::Field* > ()); }
#line 3328 "parser.tab.cc"
    break;

  case 199: // lpattern_field_cl: lpattern_field_cl "," lpattern_field
#line 716 "parser.yy"
                                               { yylhs.value.as < std::vector<pdm::ast::LPattern::Field*> > () = std::move(yystack_[2].value.as < std::vector<pdm::ast::LPattern::Field*> > ()); yylhs.value.as < std::vector<pdm::ast::LPattern::Field*> > ().push_back(yystack_[0].value.as < pdm::ast::LPattern::Field* > ()); }
#line 3334 "parser.tab.cc"
    break;

  case 200: // tpattern_field_cl: tpattern_field
#line 719 "parser.yy"
                                              { yylhs.value.as < std::vector<pdm::ast::TPattern::Field*> > ().push_back(yystack_[0].value.as < pdm::ast::TPattern::Field* > ()); }
#line 3340 "parser.tab.cc"
    break;

  case 201: // tpattern_field_cl: tpattern_field_cl "," tpattern_field
#line 720 "parser.yy"
                                               { yylhs.value.as < std::vector<pdm::ast::TPattern::Field*> > () = std::move(yystack_[2].value.as < std::vector<pdm::ast::TPattern::Field*> > ()); yylhs.value.as < std::vector<pdm::ast::TPattern::Field*> > ().push_back(yystack_[0].value.as < pdm::ast::TPattern::Field* > ()); }
#line 3346 "parser.tab.cc"
    break;

  case 202: // struct_exp_field_cl: struct_exp_field
#line 723 "parser.yy"
                                                    { yylhs.value.as < std::vector<pdm::ast::StructExp::Field*> > ().push_back(yystack_[0].value.as < pdm::ast::StructExp::Field* > ()); }
#line 3352 "parser.tab.cc"
    break;

  case 203: // struct_exp_field_cl: struct_exp_field_cl "," struct_exp_field
#line 724 "parser.yy"
                                                    { yylhs.value.as < std::vector<pdm::ast::StructExp::Field*> > () = std::move(yystack_[2].value.as < std::vector<pdm::ast::StructExp::Field*> > ()); yylhs.value.as < std::vector<pdm::ast::StructExp::Field*> > ().push_back(yystack_[0].value.as < pdm::ast::StructExp::Field* > ()); }
#line 3358 "parser.tab.cc"
    break;

  case 204: // tpattern_seq: tpattern
#line 728 "parser.yy"
                             { yylhs.value.as < std::vector<pdm::ast::TPattern*> > ().push_back(yystack_[0].value.as < pdm::ast::TPattern* > ()); }
#line 3364 "parser.tab.cc"
    break;

  case 205: // tpattern_seq: tpattern_seq tpattern
#line 729 "parser.yy"
                             { yylhs.value.as < std::vector<pdm::ast::TPattern*> > () = std::move(yystack_[1].value.as < std::vector<pdm::ast::TPattern*> > ()); yylhs.value.as < std::vector<pdm::ast::TPattern*> > ().push_back(yystack_[0].value.as < pdm::ast::TPattern* > ()); }
#line 3370 "parser.tab.cc"
    break;


#line 3374 "parser.tab.cc"

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





  const short parser::yypact_ninf_ = -339;

  const signed char parser::yytable_ninf_ = -51;

  const short
  parser::yypact_[] =
  {
     211,    11,    39,    42,    42,    55,   211,    17,  -339,  -339,
    -339,  -339,  -339,    25,    38,  -339,    82,    93,  -339,    73,
    -339,     5,   255,   202,   688,  -339,  -339,    84,   114,  -339,
    -339,    13,    96,  -339,  -339,  -339,  -339,   133,     8,  -339,
    -339,   115,    34,   103,  -339,  -339,  -339,  -339,  -339,  -339,
     318,   407,  -339,  -339,  -339,  -339,   146,  -339,  -339,   171,
    -339,  -339,  -339,  -339,  -339,  -339,  -339,  -339,   218,  -339,
    -339,  -339,    65,  -339,  -339,  -339,  -339,  -339,   688,  -339,
     104,   224,   110,   221,   170,   183,   189,  -339,   -12,  -339,
     180,  -339,   267,    42,    22,   179,    42,  -339,  -339,   149,
     103,    23,   688,   146,   267,   215,  -339,  -339,  -339,  -339,
    -339,   207,  -339,  -339,    14,   202,   235,    85,   185,  -339,
     229,   203,    92,    32,    32,    32,   688,   688,  -339,   223,
    -339,  -339,  -339,  -339,  -339,   216,   231,   473,  -339,    57,
    -339,   253,   254,  -339,  -339,    37,   510,   617,  -339,  -339,
    -339,  -339,   688,  -339,  -339,   688,  -339,  -339,  -339,  -339,
     688,  -339,  -339,   688,   688,   688,   688,    54,  -339,    23,
      23,  -339,   -30,    23,    11,  -339,  -339,  -339,   267,   230,
    -339,   256,    42,    22,  -339,  -339,    23,   142,   162,  -339,
    -339,    42,   617,   688,   286,  -339,    34,    11,    11,  -339,
      23,  -339,   167,    23,  -339,   652,  -339,   688,  -339,    11,
      23,  -339,  -339,   244,   247,   249,   252,  -339,  -339,   688,
    -339,  -339,   271,   266,    11,  -339,  -339,  -339,   272,  -339,
    -339,   688,   688,  -339,  -339,  -339,   193,   546,   284,  -339,
    -339,  -339,    -8,  -339,   104,   224,   110,   221,   170,   183,
     255,  -339,  -339,   267,  -339,   259,    23,  -339,    90,   101,
      42,    99,    23,  -339,  -339,   108,  -339,    23,  -339,   202,
     150,  -339,    42,   306,    23,    23,  -339,    56,  -339,    34,
    -339,  -339,  -339,  -339,   200,  -339,   688,   688,   688,   688,
    -339,  -339,  -339,   216,  -339,  -339,  -339,  -339,   582,  -339,
     617,  -339,    35,  -339,   260,  -339,    11,  -339,  -339,  -339,
    -339,  -339,   217,   261,  -339,  -339,  -339,  -339,  -339,   202,
     136,  -339,  -339,  -339,  -339,    11,  -339,  -339,  -339,  -339,
    -339,   222,  -339,  -339,  -339,   273,  -339,    23,  -339,   274,
    -339,  -339,  -339,   688,  -339,    23,  -339,   283,  -339,    45,
     291,    81,    23,  -339,   296,  -339,  -339,  -339,  -339,    23,
      69,  -339,  -339,  -339
  };

  const unsigned char
  parser::yydefact_[] =
  {
       0,     0,     0,     0,     0,     0,     2,     0,     5,     8,
       6,     7,    50,     0,     0,    49,     0,     0,     1,     0,
       3,     0,     0,     0,     0,     4,    45,     0,     0,    10,
      28,     0,     0,    24,    25,    26,    27,     0,     0,    53,
      52,     0,     0,     0,   116,    82,    83,    51,    85,    84,
       0,     0,   114,   112,   113,   115,     0,    76,    78,     0,
      48,    75,    64,    65,    66,    67,    97,    77,    79,    80,
      68,    81,   110,    98,    99,   100,   101,   121,     0,    56,
     125,   131,   135,   137,   139,   141,   117,    46,     0,     9,
       0,    12,     0,     0,     0,     0,     0,    35,   204,     0,
       0,     0,     0,   155,     0,     0,   165,   156,   157,   158,
     159,   168,   166,   147,     0,     0,     0,     0,     0,    69,
      57,     0,     0,     0,     0,     0,     0,     0,    70,     0,
      14,    15,    16,    17,    18,    76,     0,     0,   202,     0,
      54,   107,     0,    87,    86,     0,     0,     0,   111,   118,
     119,   120,     0,   123,   124,     0,   127,   128,   129,   130,
       0,   133,   134,     0,     0,     0,     0,     0,    13,     0,
       0,   200,     0,     0,     0,   169,    33,   170,     0,    37,
      38,    40,     0,     0,    36,   205,     0,     0,     0,    29,
     163,     0,     0,     0,     0,    47,     0,     0,     0,   193,
       0,   196,     0,     0,    95,     0,    71,     0,    73,     0,
     186,   190,   191,     0,     0,     0,     0,    23,    93,     0,
      90,    91,     0,     0,     0,    74,    55,   105,     0,   109,
     108,     0,     0,   103,   176,   179,     0,     0,     0,   173,
     172,   174,     0,   122,   126,   132,   136,   138,   140,   142,
       0,   188,   187,     0,   194,     0,     0,   153,     0,     0,
       0,     0,     0,    34,   164,     0,   160,     0,   162,     0,
       0,    30,     0,    88,     0,     0,   182,     0,   192,     0,
      72,    60,    61,   198,     0,   185,     0,     0,     0,     0,
     181,    94,    92,     0,   203,    58,   177,   178,     0,   104,
       0,   102,     0,   201,     0,   152,     0,   171,   195,    39,
      41,   148,     0,     0,   161,   150,   151,    31,   167,     0,
       0,   183,   184,   197,    96,     0,   189,    19,    20,    21,
      22,     0,   180,   175,    11,     0,   154,     0,    42,     0,
      32,    89,   199,     0,   106,     0,   149,     0,    59,     0,
       0,     0,     0,    43,     0,    62,   146,   144,   145,     0,
       0,    63,   143,    44
  };

  const short
  parser::yypgoto_[] =
  {
    -339,  -339,  -339,   335,   192,  -339,    98,   205,  -339,  -339,
    -339,  -339,  -339,   -29,  -339,  -339,  -339,   250,  -339,    83,
    -339,  -339,  -339,  -339,    -3,     2,  -339,  -110,   120,   198,
    -339,  -339,  -339,     3,   -13,  -339,  -339,  -339,  -339,    36,
     213,  -339,  -339,  -339,  -339,  -339,  -339,  -339,  -339,  -339,
    -339,   -71,  -339,  -339,  -339,   204,  -339,   206,  -339,   199,
    -339,   201,   208,   197,  -339,  -338,  -339,    72,  -339,  -339,
      62,  -339,   188,  -339,  -339,  -339,  -339,  -339,  -339,   -88,
     186,  -339,    75,   191,    79,  -339,   154,   107,  -205,   127,
    -339,   172,   288,   -89,  -339,  -339,   212,  -339,   -25
  };

  const short
  parser::yydefgoto_[] =
  {
      -1,     5,     6,     7,    29,    30,    31,   129,   130,   131,
     132,   133,   134,    32,    33,    34,    35,    97,   179,   180,
      36,     9,    10,    11,   103,    57,    58,    41,    59,   239,
     121,   331,   122,   349,    61,    62,    63,    64,    65,    66,
      67,    68,    69,    70,   137,    71,    72,    73,    74,    75,
      76,    77,    78,    79,   152,    80,   155,    81,   160,    82,
     163,    83,    84,    85,    86,   350,   359,   351,   312,   188,
     257,   258,   106,   107,   108,   109,   110,   111,   112,   113,
     176,   177,   241,   242,   235,   236,   138,   201,   211,   171,
     212,   213,   118,    98,   202,   284,   172,   139,    99
  };

  const short
  parser::yytable_[] =
  {
      16,    17,    90,    13,   283,   195,   175,   148,    12,   253,
     185,   354,    15,   114,    12,   254,    12,    15,    15,    37,
      28,    56,   354,    27,    38,   185,    15,    15,    37,   116,
     100,   300,    92,    38,    22,    12,   100,   301,    12,    15,
     227,   228,    28,    14,   100,   100,    15,    56,    56,    15,
     101,    95,    92,   135,    26,    18,   101,    20,    92,    12,
      89,   142,    21,   167,   101,   101,   102,   100,   174,    45,
      46,    95,   193,    15,   209,    56,    50,    95,   185,    50,
      51,   243,   334,    51,    22,   197,   198,   101,    12,   169,
     173,   100,   353,   181,   170,   175,   224,    23,    92,    56,
     250,   190,   145,    15,   225,   204,   142,   146,    24,   147,
     105,   101,    15,    25,   197,   198,   363,    95,    88,   200,
     342,   100,   356,    56,    56,   210,   210,   210,   199,   306,
     100,   207,   229,    87,    56,   208,    91,   307,   115,    12,
     253,   101,   310,    56,    42,   117,   308,   357,   358,    56,
     101,   314,    56,   149,   150,   151,    43,    56,   104,   317,
      56,    56,    56,    56,   156,   157,   158,   159,    45,    46,
      47,    48,    49,   187,   141,   169,   256,    92,    50,   262,
     170,   265,    51,   273,   140,   266,   194,    93,   269,   300,
      56,    94,     8,    92,   164,   318,    95,    96,     8,   274,
     275,   267,    56,   182,    56,   268,   277,   183,   165,   340,
     278,   210,    95,    96,   104,   166,    56,     1,     2,   240,
     168,   104,    60,   178,     3,     4,   293,    50,    56,    56,
     191,    51,   298,   203,   104,   190,   299,    39,    40,   325,
     142,   251,   252,   326,   196,   255,   206,    37,   120,   136,
     169,   192,    38,   143,   144,   170,   337,   181,    12,    15,
     338,   343,    28,   218,   240,   344,   324,   238,   205,   319,
      12,    15,   276,    90,   219,   279,   153,   154,   220,   200,
     161,   162,   285,    56,    56,    56,    56,   141,    15,   104,
     104,   -50,   226,   104,   260,    56,   214,   215,   261,    37,
     189,   272,   286,   104,    38,   287,   104,   288,   256,   187,
     289,   291,   238,   292,   295,   304,   320,   339,   335,   345,
     104,    12,    15,   104,   216,   217,    42,   210,   305,   352,
     104,   355,   347,   311,   313,   223,   361,   315,    43,   316,
      56,    19,   222,   309,   234,    44,   321,   322,   302,   184,
      45,    46,    47,    48,    49,   360,   341,   238,   230,   244,
      50,   119,   246,   249,    51,   247,   245,    52,   336,   263,
      53,    54,   240,   248,   264,   333,   104,   332,   294,    55,
     303,   104,   104,   270,   323,   104,     0,   104,   186,     0,
     259,   271,     0,     0,   104,   104,     0,     0,     0,     0,
       0,     0,     0,   281,     0,   282,     0,     0,     0,   346,
      12,    15,     0,     0,     0,    42,     0,   290,     0,     0,
     238,     0,     0,   123,   124,   125,   126,    43,     0,   296,
     297,   362,     0,     0,    44,   120,     0,     0,   127,    45,
      46,    47,    48,    49,     0,     0,     0,     0,     0,    50,
       0,     0,     0,    51,   128,     0,    52,   104,     0,    53,
      54,     0,     0,     0,     0,   104,     0,     0,    55,   104,
       0,     0,   104,     0,     0,     0,    12,    15,     0,   104,
     104,    42,     0,     0,   327,   328,   329,   330,     0,   123,
     124,   125,   126,    43,     0,     0,   234,     0,     0,     0,
      44,     0,     0,     0,   127,    45,    46,    47,    48,    49,
       0,     0,     0,    12,    15,    50,     0,     0,    42,    51,
     221,     0,    52,     0,     0,    53,    54,     0,     0,     0,
      43,     0,     0,     0,    55,     0,     0,    44,     0,   231,
     232,   348,    45,    46,    47,    48,    49,     0,     0,    12,
      15,     0,    50,   233,    42,     0,    51,     0,     0,    52,
       0,     0,    53,    54,     0,     0,    43,     0,   100,     0,
       0,    55,     0,    44,     0,     0,     0,     0,    45,    46,
      47,    48,    49,     0,     0,    12,    15,     0,   237,   119,
      42,     0,    51,     0,     0,    52,     0,     0,    53,    54,
       0,     0,    43,     0,     0,     0,     0,    55,     0,    44,
       0,   231,   232,     0,    45,    46,    47,    48,    49,     0,
      12,    15,     0,     0,    50,    42,     0,     0,    51,     0,
       0,    52,     0,     0,    53,    54,     0,    43,     0,   100,
       0,     0,     0,    55,    44,     0,     0,     0,     0,    45,
      46,    47,    48,    49,     0,    12,    15,     0,     0,   237,
      42,     0,     0,    51,     0,     0,    52,     0,     0,    53,
      54,     0,    43,     0,     0,     0,     0,     0,    55,    44,
       0,     0,     0,     0,    45,    46,    47,    48,    49,     0,
       0,    12,    15,     0,    50,   280,    42,     0,    51,     0,
       0,    52,     0,     0,    53,    54,     0,     0,    43,     0,
       0,     0,     0,    55,     0,    44,     0,     0,     0,     0,
      45,    46,    47,    48,    49,     0,     0,     0,     0,     0,
      50,     0,     0,     0,    51,     0,     0,    52,     0,     0,
      53,    54,     0,     0,     0,     0,     0,     0,     0,    55
  };

  const short
  parser::yycheck_[] =
  {
       3,     4,    31,     1,   209,   115,    94,    78,     3,    39,
      99,   349,     4,    38,     3,    45,     3,     4,     4,    22,
       7,    24,   360,    21,    22,   114,     4,     4,    31,    42,
      22,    39,    44,    31,    46,     3,    22,    45,     3,     4,
       3,     4,     7,     4,    22,    22,     4,    50,    51,     4,
      42,    63,    44,    51,    49,     0,    42,    40,    44,     3,
      47,    59,    37,    88,    42,    42,    58,    22,    46,    32,
      33,    63,    58,     4,    42,    78,    42,    63,   167,    42,
      46,   152,    47,    46,    46,    29,    30,    42,     3,    92,
      93,    22,    47,    96,    92,   183,    39,    15,    44,   102,
      46,   104,    37,     4,    47,   118,   104,    42,    15,    44,
      38,    42,     4,    40,    29,    30,    47,    63,     4,   117,
     325,    22,    41,   126,   127,   123,   124,   125,    43,    39,
      22,    39,   145,    49,   137,    43,    40,    47,    23,     3,
      39,    42,    43,   146,     8,    42,    45,    66,    67,   152,
      42,    43,   155,    49,    50,    51,    20,   160,    38,   269,
     163,   164,   165,   166,    54,    55,    56,    57,    32,    33,
      34,    35,    36,   101,     3,   178,   174,    44,    42,   182,
     178,    39,    46,   196,    38,    43,   114,    54,   191,    39,
     193,    58,     0,    44,    24,    45,    63,    64,     6,   197,
     198,    39,   205,    54,   207,    43,    39,    58,    25,   319,
      43,   209,    63,    64,    94,    26,   219,     6,     7,   147,
      40,   101,    24,    44,    13,    14,   224,    42,   231,   232,
      15,    46,    39,    48,   114,   238,    43,    35,    36,    39,
     238,   169,   170,    43,     9,   173,    43,   250,    50,    51,
     253,    44,   250,    35,    36,   253,    39,   260,     3,     4,
      43,    39,     7,    40,   192,    43,   279,   147,    39,   272,
       3,     4,   200,   302,    58,   203,    52,    53,    47,   277,
      59,    60,   210,   286,   287,   288,   289,     3,     4,   169,
     170,    38,    38,   173,    64,   298,   124,   125,    42,   302,
     102,    15,    58,   183,   302,    58,   186,    58,   306,   237,
      58,    40,   192,    47,    42,    56,    10,    56,    58,    46,
     200,     3,     4,   203,   126,   127,     8,   325,   256,    46,
     210,    40,    58,   261,   262,   137,    40,   265,    20,   267,
     343,     6,   137,   260,   146,    27,   274,   275,   250,    99,
      32,    33,    34,    35,    36,   352,   320,   237,   145,   155,
      42,    43,   163,   166,    46,   164,   160,    49,   306,   183,
      52,    53,   300,   165,   186,   300,   256,   298,   224,    61,
     253,   261,   262,   192,   277,   265,    -1,   267,   100,    -1,
     178,   193,    -1,    -1,   274,   275,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   205,    -1,   207,    -1,    -1,    -1,   337,
       3,     4,    -1,    -1,    -1,     8,    -1,   219,    -1,    -1,
     300,    -1,    -1,    16,    17,    18,    19,    20,    -1,   231,
     232,   359,    -1,    -1,    27,   237,    -1,    -1,    31,    32,
      33,    34,    35,    36,    -1,    -1,    -1,    -1,    -1,    42,
      -1,    -1,    -1,    46,    47,    -1,    49,   337,    -1,    52,
      53,    -1,    -1,    -1,    -1,   345,    -1,    -1,    61,   349,
      -1,    -1,   352,    -1,    -1,    -1,     3,     4,    -1,   359,
     360,     8,    -1,    -1,   286,   287,   288,   289,    -1,    16,
      17,    18,    19,    20,    -1,    -1,   298,    -1,    -1,    -1,
      27,    -1,    -1,    -1,    31,    32,    33,    34,    35,    36,
      -1,    -1,    -1,     3,     4,    42,    -1,    -1,     8,    46,
      47,    -1,    49,    -1,    -1,    52,    53,    -1,    -1,    -1,
      20,    -1,    -1,    -1,    61,    -1,    -1,    27,    -1,    29,
      30,   343,    32,    33,    34,    35,    36,    -1,    -1,     3,
       4,    -1,    42,    43,     8,    -1,    46,    -1,    -1,    49,
      -1,    -1,    52,    53,    -1,    -1,    20,    -1,    22,    -1,
      -1,    61,    -1,    27,    -1,    -1,    -1,    -1,    32,    33,
      34,    35,    36,    -1,    -1,     3,     4,    -1,    42,    43,
       8,    -1,    46,    -1,    -1,    49,    -1,    -1,    52,    53,
      -1,    -1,    20,    -1,    -1,    -1,    -1,    61,    -1,    27,
      -1,    29,    30,    -1,    32,    33,    34,    35,    36,    -1,
       3,     4,    -1,    -1,    42,     8,    -1,    -1,    46,    -1,
      -1,    49,    -1,    -1,    52,    53,    -1,    20,    -1,    22,
      -1,    -1,    -1,    61,    27,    -1,    -1,    -1,    -1,    32,
      33,    34,    35,    36,    -1,     3,     4,    -1,    -1,    42,
       8,    -1,    -1,    46,    -1,    -1,    49,    -1,    -1,    52,
      53,    -1,    20,    -1,    -1,    -1,    -1,    -1,    61,    27,
      -1,    -1,    -1,    -1,    32,    33,    34,    35,    36,    -1,
      -1,     3,     4,    -1,    42,    43,     8,    -1,    46,    -1,
      -1,    49,    -1,    -1,    52,    53,    -1,    -1,    20,    -1,
      -1,    -1,    -1,    61,    -1,    27,    -1,    -1,    -1,    -1,
      32,    33,    34,    35,    36,    -1,    -1,    -1,    -1,    -1,
      42,    -1,    -1,    -1,    46,    -1,    -1,    49,    -1,    -1,
      52,    53,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    61
  };

  const unsigned char
  parser::yystos_[] =
  {
       0,     6,     7,    13,    14,    70,    71,    72,    73,    90,
      91,    92,     3,    94,     4,     4,    93,    93,     0,    72,
      40,    37,    46,    15,    15,    40,    49,    94,     7,    73,
      74,    75,    82,    83,    84,    85,    89,    93,    94,    35,
      36,    96,     8,    20,    27,    32,    33,    34,    35,    36,
      42,    46,    49,    52,    53,    61,    93,    94,    95,    97,
      98,   103,   104,   105,   106,   107,   108,   109,   110,   111,
     112,   114,   115,   116,   117,   118,   119,   120,   121,   122,
     124,   126,   128,   130,   131,   132,   133,    49,     4,    47,
      82,    40,    44,    54,    58,    63,    64,    86,   162,   167,
      22,    42,    58,    93,    97,   136,   141,   142,   143,   144,
     145,   146,   147,   148,   167,    23,   103,    42,   161,    43,
      98,    99,   101,    16,    17,    18,    19,    31,    47,    76,
      77,    78,    79,    80,    81,    94,    98,   113,   155,   166,
      38,     3,    94,    35,    36,    37,    42,    44,   120,    49,
      50,    51,   123,    52,    53,   125,    54,    55,    56,    57,
     127,    59,    60,   129,    24,    25,    26,   167,    40,    93,
      94,   158,   165,    93,    46,   148,   149,   150,    44,    87,
      88,    93,    54,    58,    86,   162,   161,   136,   138,    98,
      93,    15,    44,    58,   136,    96,     9,    29,    30,    43,
      94,   156,   163,    48,   103,    39,    43,    39,    43,    42,
      94,   157,   159,   160,   160,   160,    98,    98,    40,    58,
      47,    47,    76,    98,    39,    47,    38,     3,     4,   103,
     109,    29,    30,    43,    98,   153,   154,    42,    97,    98,
     136,   151,   152,   120,   124,   126,   128,   130,   131,   132,
      46,   136,   136,    39,    45,   136,    94,   139,   140,   165,
      64,    42,    93,   149,   141,    39,    43,    39,    43,    93,
     152,    98,    15,   103,    94,    94,   136,    39,    43,   136,
      43,    98,    98,   157,   164,   136,    58,    58,    58,    58,
      98,    40,    47,    94,   155,    42,    98,    98,    39,    43,
      39,    45,    75,   158,    56,   136,    39,    47,    45,    88,
      43,   136,   137,   136,    43,   136,   136,    96,    45,    93,
      10,   136,   136,   156,   103,    39,    43,    98,    98,    98,
      98,   100,   153,   151,    47,    58,   139,    39,    43,    56,
      96,   108,   157,    39,    43,    46,   136,    58,    98,   102,
     134,   136,    46,    47,   134,    40,    41,    66,    67,   135,
     102,    40,   136,    47
  };

  const unsigned char
  parser::yyr1_[] =
  {
       0,    69,    70,    71,    71,    72,    72,    72,    72,    73,
      74,    74,    75,    75,    76,    76,    76,    76,    76,    77,
      78,    79,    80,    81,    82,    82,    82,    82,    82,    83,
      83,    83,    83,    84,    84,    85,    85,    86,    87,    87,
      88,    88,    88,    89,    89,    90,    90,    91,    92,    93,
      94,    95,    96,    96,    97,    97,    98,    99,   100,   100,
     101,   101,   102,   102,   103,   103,   103,   103,   103,   104,
     104,   105,   106,   106,   107,   108,   108,   108,   108,   108,
     108,   108,   109,   109,   110,   110,   110,   110,   111,   111,
     112,   112,   112,   113,   113,   114,   114,   115,   115,   115,
     115,   115,   116,   117,   117,   118,   118,   118,   119,   119,
     120,   120,   121,   121,   121,   121,   121,   122,   123,   123,
     123,   124,   124,   125,   125,   126,   126,   127,   127,   127,
     127,   128,   128,   129,   129,   130,   130,   131,   131,   132,
     132,   133,   133,   134,   135,   135,   135,   136,   137,   137,
     138,   138,   139,   140,   140,   141,   141,   141,   141,   141,
     142,   143,   143,   144,   145,   146,   146,   147,   148,   149,
     149,   150,   151,   151,   152,   152,   153,   153,   153,   154,
     154,   155,   156,   156,   156,   157,   157,   158,   158,   159,
     160,   160,   161,   161,   162,   162,   163,   163,   164,   164,
     165,   165,   166,   166,   167,   167
  };

  const signed char
  parser::yyr2_[] =
  {
       0,     2,     1,     2,     3,     1,     1,     1,     1,     5,
       1,     6,     2,     3,     1,     1,     1,     1,     1,     4,
       4,     4,     4,     2,     1,     1,     1,     1,     1,     3,
       4,     5,     6,     3,     4,     2,     3,     2,     1,     3,
       1,     3,     4,     9,    10,     4,     5,     6,     4,     1,
       1,     1,     1,     1,     2,     3,     1,     1,     0,     3,
       3,     3,     2,     3,     1,     1,     1,     1,     1,     2,
       2,     3,     4,     3,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     2,     2,     4,     6,
       3,     3,     4,     2,     3,     3,     5,     1,     1,     1,
       1,     1,     4,     3,     4,     3,     6,     2,     3,     3,
       1,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     3,     1,     1,     1,     3,     1,     1,     1,
       1,     1,     3,     1,     1,     1,     3,     1,     3,     1,
       3,     1,     3,     3,     1,     1,     1,     1,     1,     3,
       3,     3,     2,     1,     3,     1,     1,     1,     1,     1,
       3,     4,     3,     2,     3,     1,     1,     4,     1,     1,
       1,     3,     1,     1,     1,     3,     1,     2,     2,     1,
       3,     3,     2,     3,     3,     2,     1,     2,     2,     3,
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
  "\"extern\"", "\"from\"", "\"const\"", "\"val\"", "\"var\"", "\"set\"",
  "\"fn\"", "\"lambda\"", "\"Fn\"", "\"type\"", "\"and\"", "\"xor\"",
  "\"or\"", "\"not\"", "\"typeclass\"", "\"out\"", "\"inout\"",
  "\"discard\"", "\"42\"", "\"0x2a\"", "\"4.2\"",
  "\"\\\"dq-string-literal\\\"\"", "\"'sq-string-literal'\"", "\".\"",
  "\":\"", "\",\"", "\";\"", "\"::\"", "\"(\"", "\")\"", "\"[\"", "\"]\"",
  "\"{\"", "\"}\"", "\"->\"", "\"*\"", "\"/\"", "\"%\"", "\"+\"", "\"-\"",
  "\"<\"", "\"<=\"", "\">\"", "\">=\"", "\"=\"", "\"==\"", "\"!=\"",
  "\"^\"", "\"&\"", "\"!\"", "\"|\"", "\"EOS\"", "\":<\"", "\">:\"",
  "\"<null>\"", "$accept", "script", "scriptContent", "scriptContentStmt",
  "top_mod_stmt", "mod_stmt", "mod_content", "chain_prefix_stmt",
  "const_stmt", "val_stmt", "var_stmt", "set_stmt", "discard_stmt",
  "mod_content_stmt", "mod_val_stmt", "mod_type_stmt", "mod_enum_stmt",
  "enum_field_pl", "unprefixed_enum_field_pl", "enum_field",
  "mod_typeclass_stmt", "using_stmt", "import_stmt", "extern_stmt", "tid",
  "vid", "floatl", "stringl", "mod_prefix", "expr", "long_exp", "expr_cl0",
  "expr_cl2", "type_query_exp_sl", "bracketed_exp", "unit_exp",
  "paren_exp", "vtupleExpr", "vstructExpr", "primary_exp", "int_expr",
  "stringls", "if_exp", "chain_exp", "chain_prefix", "lambda_exp",
  "postfix_exp", "tcall_exp", "vcall_exp", "dot_name_exp", "dot_index_exp",
  "unary_exp", "unary_op", "binary_exp", "mul_binary_op", "mul_binary_exp",
  "add_binary_op", "add_binary_exp", "cmp_binary_op", "cmp_binary_exp",
  "eq_binary_op", "eq_binary_exp", "and_binary_exp", "xor_binary_exp",
  "or_binary_exp", "type_query_exp", "type_query_op", "typespec",
  "typespec_cl1", "typespec_cl2", "struct_typespec_field",
  "struct_typespec_field_cl", "primary_typespec", "paren_typespec",
  "tuple_typespec", "mod_prefix_tid", "fn_typespec", "postfix_typespec",
  "tcall_typespec", "unary_typespec", "long_typespec", "struct_typespec",
  "targ", "targ_cl", "varg", "varg_cl", "struct_exp_field",
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
       0,   288,   288,   291,   292,   295,   296,   297,   298,   306,
     309,   310,   313,   314,   322,   323,   324,   325,   326,   329,
     332,   335,   338,   341,   345,   346,   347,   348,   349,   352,
     353,   354,   355,   358,   359,   362,   363,   366,   369,   370,
     373,   374,   375,   378,   381,   386,   387,   390,   393,   400,
     401,   403,   406,   407,   410,   411,   418,   421,   425,   426,
     429,   430,   433,   434,   438,   439,   440,   441,   442,   445,
     446,   449,   452,   453,   456,   459,   460,   461,   462,   463,
     464,   465,   468,   469,   472,   473,   474,   475,   478,   479,
     482,   483,   484,   487,   488,   491,   492,   496,   497,   498,
     499,   500,   503,   506,   507,   510,   511,   512,   515,   516,
     520,   521,   524,   525,   526,   527,   528,   532,   535,   536,
     537,   540,   541,   544,   545,   548,   549,   552,   553,   554,
     555,   558,   559,   562,   563,   566,   567,   570,   571,   574,
     575,   578,   579,   583,   586,   587,   588,   596,   599,   600,
     603,   604,   608,   611,   612,   616,   617,   618,   619,   620,
     623,   626,   627,   630,   633,   637,   638,   641,   645,   649,
     650,   653,   656,   657,   660,   661,   663,   664,   665,   668,
     669,   677,   680,   681,   682,   685,   686,   689,   690,   694,
     698,   699,   702,   703,   706,   707,   711,   712,   715,   716,
     719,   720,   723,   724,   728,   729
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
      65,    66,    67,    68
    };
    // Last valid token kind.
    const int code_max = 323;

    if (t <= 0)
      return symbol_kind::S_YYEOF;
    else if (t <= code_max)
      return YY_CAST (symbol_kind_type, translate_table[t]);
    else
      return symbol_kind::S_YYUNDEF;
  }

#line 19 "parser.yy"
} } // pdm::parser
#line 4092 "parser.tab.cc"

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
