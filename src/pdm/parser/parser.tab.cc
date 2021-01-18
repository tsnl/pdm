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

      case symbol_kind::S_enum_field: // enum_field
        value.copy< pdm::ast::EnumStmt::Field* > (YY_MOVE (that.value));
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

      case symbol_kind::S_script: // script
        value.copy< pdm::ast::Script* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_scriptContentStmt: // scriptContentStmt
      case symbol_kind::S_mod_stmt: // mod_stmt
      case symbol_kind::S_chain_prefix_stmt: // chain_prefix_stmt
      case symbol_kind::S_const_stmt: // const_stmt
      case symbol_kind::S_val_stmt: // val_stmt
      case symbol_kind::S_var_stmt: // var_stmt
      case symbol_kind::S_set_stmt: // set_stmt
      case symbol_kind::S_discard_stmt: // discard_stmt
      case symbol_kind::S_moduleContentStmt: // moduleContentStmt
      case symbol_kind::S_fn_stmt: // fn_stmt
      case symbol_kind::S_type_stmt: // type_stmt
      case symbol_kind::S_enum_stmt: // enum_stmt
      case symbol_kind::S_typeclass_stmt: // typeclass_stmt
      case symbol_kind::S_using_stmt: // using_stmt
      case symbol_kind::S_import_stmt: // import_stmt
      case symbol_kind::S_extern_stmt: // extern_stmt
        value.copy< pdm::ast::Stmt* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_struct_exp_field: // struct_exp_field
        value.copy< pdm::ast::StructExp::Field* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_struct_typespec_field: // struct_typespec_field
        value.copy< pdm::ast::StructTypespec::Field* > (YY_MOVE (that.value));
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
        value.copy< pdm::ast::Typespec* > (YY_MOVE (that.value));
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

      case symbol_kind::S_enum_field_pl: // enum_field_pl
      case symbol_kind::S_unprefixed_enum_field_pl: // unprefixed_enum_field_pl
        value.copy< std::vector<pdm::ast::EnumStmt::Field*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_cl0: // expr_cl0
      case symbol_kind::S_expr_cl2: // expr_cl2
        value.copy< std::vector<pdm::ast::Exp*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_lpattern_field_cl: // lpattern_field_cl
        value.copy< std::vector<pdm::ast::LPattern::Field*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_scriptContent: // scriptContent
      case symbol_kind::S_moduleContent: // moduleContent
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
        value.copy< std::vector<pdm::ast::StructTypespec::Field*> > (YY_MOVE (that.value));
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
        value.copy< std::vector<pdm::ast::Typespec*> > (YY_MOVE (that.value));
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

      case symbol_kind::S_enum_field: // enum_field
        value.move< pdm::ast::EnumStmt::Field* > (YY_MOVE (s.value));
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

      case symbol_kind::S_script: // script
        value.move< pdm::ast::Script* > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_scriptContentStmt: // scriptContentStmt
      case symbol_kind::S_mod_stmt: // mod_stmt
      case symbol_kind::S_chain_prefix_stmt: // chain_prefix_stmt
      case symbol_kind::S_const_stmt: // const_stmt
      case symbol_kind::S_val_stmt: // val_stmt
      case symbol_kind::S_var_stmt: // var_stmt
      case symbol_kind::S_set_stmt: // set_stmt
      case symbol_kind::S_discard_stmt: // discard_stmt
      case symbol_kind::S_moduleContentStmt: // moduleContentStmt
      case symbol_kind::S_fn_stmt: // fn_stmt
      case symbol_kind::S_type_stmt: // type_stmt
      case symbol_kind::S_enum_stmt: // enum_stmt
      case symbol_kind::S_typeclass_stmt: // typeclass_stmt
      case symbol_kind::S_using_stmt: // using_stmt
      case symbol_kind::S_import_stmt: // import_stmt
      case symbol_kind::S_extern_stmt: // extern_stmt
        value.move< pdm::ast::Stmt* > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_struct_exp_field: // struct_exp_field
        value.move< pdm::ast::StructExp::Field* > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_struct_typespec_field: // struct_typespec_field
        value.move< pdm::ast::StructTypespec::Field* > (YY_MOVE (s.value));
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
        value.move< pdm::ast::Typespec* > (YY_MOVE (s.value));
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

      case symbol_kind::S_enum_field_pl: // enum_field_pl
      case symbol_kind::S_unprefixed_enum_field_pl: // unprefixed_enum_field_pl
        value.move< std::vector<pdm::ast::EnumStmt::Field*> > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_expr_cl0: // expr_cl0
      case symbol_kind::S_expr_cl2: // expr_cl2
        value.move< std::vector<pdm::ast::Exp*> > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_lpattern_field_cl: // lpattern_field_cl
        value.move< std::vector<pdm::ast::LPattern::Field*> > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_scriptContent: // scriptContent
      case symbol_kind::S_moduleContent: // moduleContent
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
        value.move< std::vector<pdm::ast::StructTypespec::Field*> > (YY_MOVE (s.value));
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
        value.move< std::vector<pdm::ast::Typespec*> > (YY_MOVE (s.value));
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

      case symbol_kind::S_enum_field: // enum_field
        value.YY_MOVE_OR_COPY< pdm::ast::EnumStmt::Field* > (YY_MOVE (that.value));
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

      case symbol_kind::S_script: // script
        value.YY_MOVE_OR_COPY< pdm::ast::Script* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_scriptContentStmt: // scriptContentStmt
      case symbol_kind::S_mod_stmt: // mod_stmt
      case symbol_kind::S_chain_prefix_stmt: // chain_prefix_stmt
      case symbol_kind::S_const_stmt: // const_stmt
      case symbol_kind::S_val_stmt: // val_stmt
      case symbol_kind::S_var_stmt: // var_stmt
      case symbol_kind::S_set_stmt: // set_stmt
      case symbol_kind::S_discard_stmt: // discard_stmt
      case symbol_kind::S_moduleContentStmt: // moduleContentStmt
      case symbol_kind::S_fn_stmt: // fn_stmt
      case symbol_kind::S_type_stmt: // type_stmt
      case symbol_kind::S_enum_stmt: // enum_stmt
      case symbol_kind::S_typeclass_stmt: // typeclass_stmt
      case symbol_kind::S_using_stmt: // using_stmt
      case symbol_kind::S_import_stmt: // import_stmt
      case symbol_kind::S_extern_stmt: // extern_stmt
        value.YY_MOVE_OR_COPY< pdm::ast::Stmt* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_struct_exp_field: // struct_exp_field
        value.YY_MOVE_OR_COPY< pdm::ast::StructExp::Field* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_struct_typespec_field: // struct_typespec_field
        value.YY_MOVE_OR_COPY< pdm::ast::StructTypespec::Field* > (YY_MOVE (that.value));
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
        value.YY_MOVE_OR_COPY< pdm::ast::Typespec* > (YY_MOVE (that.value));
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

      case symbol_kind::S_enum_field_pl: // enum_field_pl
      case symbol_kind::S_unprefixed_enum_field_pl: // unprefixed_enum_field_pl
        value.YY_MOVE_OR_COPY< std::vector<pdm::ast::EnumStmt::Field*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_cl0: // expr_cl0
      case symbol_kind::S_expr_cl2: // expr_cl2
        value.YY_MOVE_OR_COPY< std::vector<pdm::ast::Exp*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_lpattern_field_cl: // lpattern_field_cl
        value.YY_MOVE_OR_COPY< std::vector<pdm::ast::LPattern::Field*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_scriptContent: // scriptContent
      case symbol_kind::S_moduleContent: // moduleContent
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
        value.YY_MOVE_OR_COPY< std::vector<pdm::ast::StructTypespec::Field*> > (YY_MOVE (that.value));
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
        value.YY_MOVE_OR_COPY< std::vector<pdm::ast::Typespec*> > (YY_MOVE (that.value));
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

      case symbol_kind::S_enum_field: // enum_field
        value.move< pdm::ast::EnumStmt::Field* > (YY_MOVE (that.value));
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

      case symbol_kind::S_script: // script
        value.move< pdm::ast::Script* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_scriptContentStmt: // scriptContentStmt
      case symbol_kind::S_mod_stmt: // mod_stmt
      case symbol_kind::S_chain_prefix_stmt: // chain_prefix_stmt
      case symbol_kind::S_const_stmt: // const_stmt
      case symbol_kind::S_val_stmt: // val_stmt
      case symbol_kind::S_var_stmt: // var_stmt
      case symbol_kind::S_set_stmt: // set_stmt
      case symbol_kind::S_discard_stmt: // discard_stmt
      case symbol_kind::S_moduleContentStmt: // moduleContentStmt
      case symbol_kind::S_fn_stmt: // fn_stmt
      case symbol_kind::S_type_stmt: // type_stmt
      case symbol_kind::S_enum_stmt: // enum_stmt
      case symbol_kind::S_typeclass_stmt: // typeclass_stmt
      case symbol_kind::S_using_stmt: // using_stmt
      case symbol_kind::S_import_stmt: // import_stmt
      case symbol_kind::S_extern_stmt: // extern_stmt
        value.move< pdm::ast::Stmt* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_struct_exp_field: // struct_exp_field
        value.move< pdm::ast::StructExp::Field* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_struct_typespec_field: // struct_typespec_field
        value.move< pdm::ast::StructTypespec::Field* > (YY_MOVE (that.value));
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
        value.move< pdm::ast::Typespec* > (YY_MOVE (that.value));
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

      case symbol_kind::S_enum_field_pl: // enum_field_pl
      case symbol_kind::S_unprefixed_enum_field_pl: // unprefixed_enum_field_pl
        value.move< std::vector<pdm::ast::EnumStmt::Field*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_cl0: // expr_cl0
      case symbol_kind::S_expr_cl2: // expr_cl2
        value.move< std::vector<pdm::ast::Exp*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_lpattern_field_cl: // lpattern_field_cl
        value.move< std::vector<pdm::ast::LPattern::Field*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_scriptContent: // scriptContent
      case symbol_kind::S_moduleContent: // moduleContent
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
        value.move< std::vector<pdm::ast::StructTypespec::Field*> > (YY_MOVE (that.value));
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
        value.move< std::vector<pdm::ast::Typespec*> > (YY_MOVE (that.value));
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

      case symbol_kind::S_enum_field: // enum_field
        value.copy< pdm::ast::EnumStmt::Field* > (that.value);
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

      case symbol_kind::S_script: // script
        value.copy< pdm::ast::Script* > (that.value);
        break;

      case symbol_kind::S_scriptContentStmt: // scriptContentStmt
      case symbol_kind::S_mod_stmt: // mod_stmt
      case symbol_kind::S_chain_prefix_stmt: // chain_prefix_stmt
      case symbol_kind::S_const_stmt: // const_stmt
      case symbol_kind::S_val_stmt: // val_stmt
      case symbol_kind::S_var_stmt: // var_stmt
      case symbol_kind::S_set_stmt: // set_stmt
      case symbol_kind::S_discard_stmt: // discard_stmt
      case symbol_kind::S_moduleContentStmt: // moduleContentStmt
      case symbol_kind::S_fn_stmt: // fn_stmt
      case symbol_kind::S_type_stmt: // type_stmt
      case symbol_kind::S_enum_stmt: // enum_stmt
      case symbol_kind::S_typeclass_stmt: // typeclass_stmt
      case symbol_kind::S_using_stmt: // using_stmt
      case symbol_kind::S_import_stmt: // import_stmt
      case symbol_kind::S_extern_stmt: // extern_stmt
        value.copy< pdm::ast::Stmt* > (that.value);
        break;

      case symbol_kind::S_struct_exp_field: // struct_exp_field
        value.copy< pdm::ast::StructExp::Field* > (that.value);
        break;

      case symbol_kind::S_struct_typespec_field: // struct_typespec_field
        value.copy< pdm::ast::StructTypespec::Field* > (that.value);
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
        value.copy< pdm::ast::Typespec* > (that.value);
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

      case symbol_kind::S_enum_field_pl: // enum_field_pl
      case symbol_kind::S_unprefixed_enum_field_pl: // unprefixed_enum_field_pl
        value.copy< std::vector<pdm::ast::EnumStmt::Field*> > (that.value);
        break;

      case symbol_kind::S_expr_cl0: // expr_cl0
      case symbol_kind::S_expr_cl2: // expr_cl2
        value.copy< std::vector<pdm::ast::Exp*> > (that.value);
        break;

      case symbol_kind::S_lpattern_field_cl: // lpattern_field_cl
        value.copy< std::vector<pdm::ast::LPattern::Field*> > (that.value);
        break;

      case symbol_kind::S_scriptContent: // scriptContent
      case symbol_kind::S_moduleContent: // moduleContent
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
        value.copy< std::vector<pdm::ast::StructTypespec::Field*> > (that.value);
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
        value.copy< std::vector<pdm::ast::Typespec*> > (that.value);
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

      case symbol_kind::S_enum_field: // enum_field
        value.move< pdm::ast::EnumStmt::Field* > (that.value);
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

      case symbol_kind::S_script: // script
        value.move< pdm::ast::Script* > (that.value);
        break;

      case symbol_kind::S_scriptContentStmt: // scriptContentStmt
      case symbol_kind::S_mod_stmt: // mod_stmt
      case symbol_kind::S_chain_prefix_stmt: // chain_prefix_stmt
      case symbol_kind::S_const_stmt: // const_stmt
      case symbol_kind::S_val_stmt: // val_stmt
      case symbol_kind::S_var_stmt: // var_stmt
      case symbol_kind::S_set_stmt: // set_stmt
      case symbol_kind::S_discard_stmt: // discard_stmt
      case symbol_kind::S_moduleContentStmt: // moduleContentStmt
      case symbol_kind::S_fn_stmt: // fn_stmt
      case symbol_kind::S_type_stmt: // type_stmt
      case symbol_kind::S_enum_stmt: // enum_stmt
      case symbol_kind::S_typeclass_stmt: // typeclass_stmt
      case symbol_kind::S_using_stmt: // using_stmt
      case symbol_kind::S_import_stmt: // import_stmt
      case symbol_kind::S_extern_stmt: // extern_stmt
        value.move< pdm::ast::Stmt* > (that.value);
        break;

      case symbol_kind::S_struct_exp_field: // struct_exp_field
        value.move< pdm::ast::StructExp::Field* > (that.value);
        break;

      case symbol_kind::S_struct_typespec_field: // struct_typespec_field
        value.move< pdm::ast::StructTypespec::Field* > (that.value);
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
        value.move< pdm::ast::Typespec* > (that.value);
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

      case symbol_kind::S_enum_field_pl: // enum_field_pl
      case symbol_kind::S_unprefixed_enum_field_pl: // unprefixed_enum_field_pl
        value.move< std::vector<pdm::ast::EnumStmt::Field*> > (that.value);
        break;

      case symbol_kind::S_expr_cl0: // expr_cl0
      case symbol_kind::S_expr_cl2: // expr_cl2
        value.move< std::vector<pdm::ast::Exp*> > (that.value);
        break;

      case symbol_kind::S_lpattern_field_cl: // lpattern_field_cl
        value.move< std::vector<pdm::ast::LPattern::Field*> > (that.value);
        break;

      case symbol_kind::S_scriptContent: // scriptContent
      case symbol_kind::S_moduleContent: // moduleContent
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
        value.move< std::vector<pdm::ast::StructTypespec::Field*> > (that.value);
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
        value.move< std::vector<pdm::ast::Typespec*> > (that.value);
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

      case symbol_kind::S_enum_field: // enum_field
        yylhs.value.emplace< pdm::ast::EnumStmt::Field* > ();
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

      case symbol_kind::S_script: // script
        yylhs.value.emplace< pdm::ast::Script* > ();
        break;

      case symbol_kind::S_scriptContentStmt: // scriptContentStmt
      case symbol_kind::S_mod_stmt: // mod_stmt
      case symbol_kind::S_chain_prefix_stmt: // chain_prefix_stmt
      case symbol_kind::S_const_stmt: // const_stmt
      case symbol_kind::S_val_stmt: // val_stmt
      case symbol_kind::S_var_stmt: // var_stmt
      case symbol_kind::S_set_stmt: // set_stmt
      case symbol_kind::S_discard_stmt: // discard_stmt
      case symbol_kind::S_moduleContentStmt: // moduleContentStmt
      case symbol_kind::S_fn_stmt: // fn_stmt
      case symbol_kind::S_type_stmt: // type_stmt
      case symbol_kind::S_enum_stmt: // enum_stmt
      case symbol_kind::S_typeclass_stmt: // typeclass_stmt
      case symbol_kind::S_using_stmt: // using_stmt
      case symbol_kind::S_import_stmt: // import_stmt
      case symbol_kind::S_extern_stmt: // extern_stmt
        yylhs.value.emplace< pdm::ast::Stmt* > ();
        break;

      case symbol_kind::S_struct_exp_field: // struct_exp_field
        yylhs.value.emplace< pdm::ast::StructExp::Field* > ();
        break;

      case symbol_kind::S_struct_typespec_field: // struct_typespec_field
        yylhs.value.emplace< pdm::ast::StructTypespec::Field* > ();
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
        yylhs.value.emplace< pdm::ast::Typespec* > ();
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

      case symbol_kind::S_enum_field_pl: // enum_field_pl
      case symbol_kind::S_unprefixed_enum_field_pl: // unprefixed_enum_field_pl
        yylhs.value.emplace< std::vector<pdm::ast::EnumStmt::Field*> > ();
        break;

      case symbol_kind::S_expr_cl0: // expr_cl0
      case symbol_kind::S_expr_cl2: // expr_cl2
        yylhs.value.emplace< std::vector<pdm::ast::Exp*> > ();
        break;

      case symbol_kind::S_lpattern_field_cl: // lpattern_field_cl
        yylhs.value.emplace< std::vector<pdm::ast::LPattern::Field*> > ();
        break;

      case symbol_kind::S_scriptContent: // scriptContent
      case symbol_kind::S_moduleContent: // moduleContent
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
        yylhs.value.emplace< std::vector<pdm::ast::StructTypespec::Field*> > ();
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
        yylhs.value.emplace< std::vector<pdm::ast::Typespec*> > ();
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
#line 2099 "parser.tab.cc"
    break;

  case 3: // scriptContent: scriptContentStmt ";"
#line 291 "parser.yy"
                                                    { yylhs.value.as < std::vector<pdm::ast::Stmt*> > ().push_back(yystack_[1].value.as < pdm::ast::Stmt* > ()); }
#line 2105 "parser.tab.cc"
    break;

  case 4: // scriptContent: scriptContent scriptContentStmt ";"
#line 292 "parser.yy"
                                                    { yylhs.value.as < std::vector<pdm::ast::Stmt*> > () = std::move(yystack_[2].value.as < std::vector<pdm::ast::Stmt*> > ()); yylhs.value.as < std::vector<pdm::ast::Stmt*> > ().push_back(yystack_[1].value.as < pdm::ast::Stmt* > ()); }
#line 2111 "parser.tab.cc"
    break;

  case 5: // scriptContentStmt: mod_stmt
#line 295 "parser.yy"
      { yylhs.value.as < pdm::ast::Stmt* > () = yystack_[0].value.as < pdm::ast::Stmt* > (); }
#line 2117 "parser.tab.cc"
    break;

  case 6: // scriptContentStmt: import_stmt
#line 296 "parser.yy"
      { yylhs.value.as < pdm::ast::Stmt* > () = yystack_[0].value.as < pdm::ast::Stmt* > (); }
#line 2123 "parser.tab.cc"
    break;

  case 7: // scriptContentStmt: extern_stmt
#line 297 "parser.yy"
      { yylhs.value.as < pdm::ast::Stmt* > () = yystack_[0].value.as < pdm::ast::Stmt* > (); }
#line 2129 "parser.tab.cc"
    break;

  case 8: // mod_stmt: "mod" "<TypeId>" "{" moduleContent "}"
#line 305 "parser.yy"
                                                { yylhs.value.as < pdm::ast::Stmt* > () = mgr->new_mod_stmt(yylhs.location, yystack_[3].value.as < TokenInfo > ().ID_intstr, std::move(yystack_[1].value.as < std::vector<pdm::ast::Stmt*> > ())); }
#line 2135 "parser.tab.cc"
    break;

  case 9: // moduleContent: moduleContentStmt ";"
#line 308 "parser.yy"
                                                    { yylhs.value.as < std::vector<pdm::ast::Stmt*> > ().push_back(yystack_[1].value.as < pdm::ast::Stmt* > ()); }
#line 2141 "parser.tab.cc"
    break;

  case 10: // moduleContent: moduleContent moduleContentStmt ";"
#line 309 "parser.yy"
                                                    { yylhs.value.as < std::vector<pdm::ast::Stmt*> > () = std::move(yystack_[2].value.as < std::vector<pdm::ast::Stmt*> > ()); yylhs.value.as < std::vector<pdm::ast::Stmt*> > ().push_back(yystack_[1].value.as < pdm::ast::Stmt* > ()); }
#line 2147 "parser.tab.cc"
    break;

  case 11: // chain_prefix_stmt: const_stmt
#line 317 "parser.yy"
      { yylhs.value.as < pdm::ast::Stmt* > () = yystack_[0].value.as < pdm::ast::Stmt* > (); }
#line 2153 "parser.tab.cc"
    break;

  case 12: // chain_prefix_stmt: val_stmt
#line 318 "parser.yy"
      { yylhs.value.as < pdm::ast::Stmt* > () = yystack_[0].value.as < pdm::ast::Stmt* > (); }
#line 2159 "parser.tab.cc"
    break;

  case 13: // chain_prefix_stmt: var_stmt
#line 319 "parser.yy"
      { yylhs.value.as < pdm::ast::Stmt* > () = yystack_[0].value.as < pdm::ast::Stmt* > (); }
#line 2165 "parser.tab.cc"
    break;

  case 14: // chain_prefix_stmt: set_stmt
#line 320 "parser.yy"
      { yylhs.value.as < pdm::ast::Stmt* > () = yystack_[0].value.as < pdm::ast::Stmt* > (); }
#line 2171 "parser.tab.cc"
    break;

  case 15: // chain_prefix_stmt: discard_stmt
#line 321 "parser.yy"
      { yylhs.value.as < pdm::ast::Stmt* > () = yystack_[0].value.as < pdm::ast::Stmt* > (); }
#line 2177 "parser.tab.cc"
    break;

  case 16: // const_stmt: "const" lpattern "=" expr
#line 324 "parser.yy"
                                  { yylhs.value.as < pdm::ast::Stmt* > () = mgr->new_const_stmt(yylhs.location, yystack_[2].value.as < pdm::ast::LPattern* > (), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2183 "parser.tab.cc"
    break;

  case 17: // val_stmt: "val" lpattern "=" expr
#line 327 "parser.yy"
                                  { yylhs.value.as < pdm::ast::Stmt* > () = mgr->new_val_stmt(yylhs.location, yystack_[2].value.as < pdm::ast::LPattern* > (), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2189 "parser.tab.cc"
    break;

  case 18: // var_stmt: "var" lpattern "=" expr
#line 330 "parser.yy"
                                  { yylhs.value.as < pdm::ast::Stmt* > () = mgr->new_var_stmt(yylhs.location, yystack_[2].value.as < pdm::ast::LPattern* > (), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2195 "parser.tab.cc"
    break;

  case 19: // set_stmt: "set" expr "=" expr
#line 333 "parser.yy"
                              { yylhs.value.as < pdm::ast::Stmt* > () = mgr->new_set_stmt(yylhs.location, yystack_[2].value.as < pdm::ast::Exp* > (), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2201 "parser.tab.cc"
    break;

  case 20: // discard_stmt: "discard" expr
#line 336 "parser.yy"
                        { yylhs.value.as < pdm::ast::Stmt* > () = mgr->new_discard_stmt(yylhs.location, yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2207 "parser.tab.cc"
    break;

  case 21: // moduleContentStmt: fn_stmt
#line 340 "parser.yy"
      { yylhs.value.as < pdm::ast::Stmt* > () = yystack_[0].value.as < pdm::ast::Stmt* > (); }
#line 2213 "parser.tab.cc"
    break;

  case 22: // moduleContentStmt: type_stmt
#line 341 "parser.yy"
      { yylhs.value.as < pdm::ast::Stmt* > () = yystack_[0].value.as < pdm::ast::Stmt* > (); }
#line 2219 "parser.tab.cc"
    break;

  case 23: // moduleContentStmt: enum_stmt
#line 342 "parser.yy"
      { yylhs.value.as < pdm::ast::Stmt* > () = yystack_[0].value.as < pdm::ast::Stmt* > (); }
#line 2225 "parser.tab.cc"
    break;

  case 24: // moduleContentStmt: typeclass_stmt
#line 343 "parser.yy"
      { yylhs.value.as < pdm::ast::Stmt* > () = yystack_[0].value.as < pdm::ast::Stmt* > (); }
#line 2231 "parser.tab.cc"
    break;

  case 25: // moduleContentStmt: import_stmt
#line 344 "parser.yy"
      { yylhs.value.as < pdm::ast::Stmt* > () = yystack_[0].value.as < pdm::ast::Stmt* > (); }
#line 2237 "parser.tab.cc"
    break;

  case 26: // moduleContentStmt: mod_stmt
#line 345 "parser.yy"
      { yylhs.value.as < pdm::ast::Stmt* > () = yystack_[0].value.as < pdm::ast::Stmt* > (); }
#line 2243 "parser.tab.cc"
    break;

  case 27: // moduleContentStmt: using_stmt
#line 346 "parser.yy"
      { yylhs.value.as < pdm::ast::Stmt* > () = yystack_[0].value.as < pdm::ast::Stmt* > (); }
#line 2249 "parser.tab.cc"
    break;

  case 28: // moduleContentStmt: extern_stmt
#line 347 "parser.yy"
      { yylhs.value.as < pdm::ast::Stmt* > () = yystack_[0].value.as < pdm::ast::Stmt* > (); }
#line 2255 "parser.tab.cc"
    break;

  case 29: // fn_stmt: "fn" vid vpattern "->" typespec "=" bracketed_exp
#line 350 "parser.yy"
                                                                          { yylhs.value.as < pdm::ast::Stmt* > () = mgr->new_fn_stmt(yylhs.location, yystack_[5].value.as < TokenInfo > ().ID_intstr, std::move(std::vector<ast::TPattern*>{}), yystack_[4].value.as < pdm::ast::VPattern* > (), yystack_[2].value.as < pdm::ast::Typespec* > (), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2261 "parser.tab.cc"
    break;

  case 30: // fn_stmt: "fn" vid tpattern_seq vpattern "->" typespec "=" bracketed_exp
#line 351 "parser.yy"
                                                                          { yylhs.value.as < pdm::ast::Stmt* > () = mgr->new_fn_stmt(yylhs.location, yystack_[6].value.as < TokenInfo > ().ID_intstr, std::move(yystack_[5].value.as < std::vector<pdm::ast::TPattern*> > ()), yystack_[4].value.as < pdm::ast::VPattern* > (), yystack_[2].value.as < pdm::ast::Typespec* > (), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2267 "parser.tab.cc"
    break;

  case 31: // fn_stmt: "fn" vid vpattern "=" bracketed_exp
#line 352 "parser.yy"
                                                                          { yylhs.value.as < pdm::ast::Stmt* > () = mgr->new_fn_stmt(yylhs.location, yystack_[3].value.as < TokenInfo > ().ID_intstr, std::move(std::vector<ast::TPattern*>{}), yystack_[2].value.as < pdm::ast::VPattern* > (), nullptr, yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2273 "parser.tab.cc"
    break;

  case 32: // fn_stmt: "fn" vid tpattern_seq vpattern "=" bracketed_exp
#line 353 "parser.yy"
                                                                          { yylhs.value.as < pdm::ast::Stmt* > () = mgr->new_fn_stmt(yylhs.location, yystack_[4].value.as < TokenInfo > ().ID_intstr, std::move(yystack_[3].value.as < std::vector<pdm::ast::TPattern*> > ()), yystack_[2].value.as < pdm::ast::VPattern* > (), nullptr, yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2279 "parser.tab.cc"
    break;

  case 33: // type_stmt: "type" tid "=" long_typespec
#line 356 "parser.yy"
                                                    { yylhs.value.as < pdm::ast::Stmt* > () = mgr->new_type_stmt(yylhs.location, yystack_[2].value.as < TokenInfo > ().ID_intstr, std::move(std::vector<ast::TPattern*>{}), yystack_[0].value.as < pdm::ast::Typespec* > ()); }
#line 2285 "parser.tab.cc"
    break;

  case 34: // type_stmt: "type" tid tpattern_seq "=" long_typespec
#line 357 "parser.yy"
                                                    { yylhs.value.as < pdm::ast::Stmt* > () = mgr->new_type_stmt(yylhs.location, yystack_[3].value.as < TokenInfo > ().ID_intstr, std::move(yystack_[2].value.as < std::vector<pdm::ast::TPattern*> > ()), yystack_[0].value.as < pdm::ast::Typespec* > ()); }
#line 2291 "parser.tab.cc"
    break;

  case 35: // enum_stmt: "type" tid enum_field_pl
#line 360 "parser.yy"
                                                { yylhs.value.as < pdm::ast::Stmt* > () = mgr->new_enum_stmt(yylhs.location, yystack_[1].value.as < TokenInfo > ().ID_intstr, std::move(std::vector<ast::TPattern*>{}), std::move(yystack_[0].value.as < std::vector<pdm::ast::EnumStmt::Field*> > ())); }
#line 2297 "parser.tab.cc"
    break;

  case 36: // enum_stmt: "type" tid tpattern_seq enum_field_pl
#line 361 "parser.yy"
                                                { yylhs.value.as < pdm::ast::Stmt* > () = mgr->new_enum_stmt(yylhs.location, yystack_[2].value.as < TokenInfo > ().ID_intstr, std::move(yystack_[1].value.as < std::vector<pdm::ast::TPattern*> > ()), std::move(yystack_[0].value.as < std::vector<pdm::ast::EnumStmt::Field*> > ())); }
#line 2303 "parser.tab.cc"
    break;

  case 37: // enum_field_pl: "|" unprefixed_enum_field_pl
#line 364 "parser.yy"
                                    { yylhs.value.as < std::vector<pdm::ast::EnumStmt::Field*> > () = std::move(yystack_[0].value.as < std::vector<pdm::ast::EnumStmt::Field*> > ()); }
#line 2309 "parser.tab.cc"
    break;

  case 38: // unprefixed_enum_field_pl: enum_field
#line 367 "parser.yy"
                                                { yylhs.value.as < std::vector<pdm::ast::EnumStmt::Field*> > ().push_back(yystack_[0].value.as < pdm::ast::EnumStmt::Field* > ()); }
#line 2315 "parser.tab.cc"
    break;

  case 39: // unprefixed_enum_field_pl: unprefixed_enum_field_pl "|" enum_field
#line 368 "parser.yy"
                                                { yylhs.value.as < std::vector<pdm::ast::EnumStmt::Field*> > () = std::move(yystack_[2].value.as < std::vector<pdm::ast::EnumStmt::Field*> > ()); yylhs.value.as < std::vector<pdm::ast::EnumStmt::Field*> > ().push_back(yystack_[0].value.as < pdm::ast::EnumStmt::Field* > ()); }
#line 2321 "parser.tab.cc"
    break;

  case 40: // enum_field: tid
#line 371 "parser.yy"
                                     { yylhs.value.as < pdm::ast::EnumStmt::Field* > () = mgr->new_enum_stmt_field(yylhs.location, yystack_[0].value.as < TokenInfo > ().ID_intstr, std::move(std::vector<ast::Typespec*>{}), false); }
#line 2327 "parser.tab.cc"
    break;

  case 41: // enum_field: tid "(" ")"
#line 372 "parser.yy"
                                     { yylhs.value.as < pdm::ast::EnumStmt::Field* > () = mgr->new_enum_stmt_field(yylhs.location, yystack_[2].value.as < TokenInfo > ().ID_intstr, std::move(std::vector<ast::Typespec*>{}), true); }
#line 2333 "parser.tab.cc"
    break;

  case 42: // enum_field: tid "(" typespec_cl1 ")"
#line 373 "parser.yy"
                                     { yylhs.value.as < pdm::ast::EnumStmt::Field* > () = mgr->new_enum_stmt_field(yylhs.location, yystack_[3].value.as < TokenInfo > ().ID_intstr, std::move(yystack_[1].value.as < std::vector<pdm::ast::Typespec*> > ()), true); }
#line 2339 "parser.tab.cc"
    break;

  case 43: // typeclass_stmt: "typeclass" tid "<" tid typespec ">" "=" "{" type_query_exp_sl "}"
#line 376 "parser.yy"
                                                                                                  { 
        yylhs.value.as < pdm::ast::Stmt* > () = mgr->new_typeclass_stmt(yylhs.location, yystack_[8].value.as < TokenInfo > ().ID_intstr, yystack_[6].value.as < TokenInfo > ().ID_intstr, yystack_[5].value.as < pdm::ast::Typespec* > (), std::move(std::vector<ast::TPattern*>{}), std::move(yystack_[1].value.as < std::vector<pdm::ast::TypeQueryExp*> > ())); 
      }
#line 2347 "parser.tab.cc"
    break;

  case 44: // typeclass_stmt: "typeclass" tid "<" tid typespec ">" tpattern_seq "=" "{" type_query_exp_sl "}"
#line 379 "parser.yy"
                                                                                                  { 
        yylhs.value.as < pdm::ast::Stmt* > () = mgr->new_typeclass_stmt(yylhs.location, yystack_[9].value.as < TokenInfo > ().ID_intstr, yystack_[7].value.as < TokenInfo > ().ID_intstr, yystack_[6].value.as < pdm::ast::Typespec* > (), std::move(yystack_[4].value.as < std::vector<pdm::ast::TPattern*> > ()), std::move(yystack_[1].value.as < std::vector<pdm::ast::TypeQueryExp*> > ())); 
      }
#line 2355 "parser.tab.cc"
    break;

  case 45: // using_stmt: "using" vid "." "*"
#line 384 "parser.yy"
                                        { yylhs.value.as < pdm::ast::Stmt* > () = mgr->new_using_stmt(yylhs.location, yystack_[2].value.as < TokenInfo > ().ID_intstr, ""); }
#line 2361 "parser.tab.cc"
    break;

  case 46: // using_stmt: "using" vid "." vid "*"
#line 385 "parser.yy"
                                        { yylhs.value.as < pdm::ast::Stmt* > () = mgr->new_using_stmt(yylhs.location, yystack_[3].value.as < TokenInfo > ().ID_intstr, yystack_[1].value.as < TokenInfo > ().ID_intstr.content()); }
#line 2367 "parser.tab.cc"
    break;

  case 47: // import_stmt: "import" tid "from" stringl "type" stringl
#line 388 "parser.yy"
                                                       { yylhs.value.as < pdm::ast::Stmt* > () = mgr->new_import_stmt(yylhs.location, yystack_[4].value.as < TokenInfo > ().ID_intstr, *yystack_[2].value.as < TokenInfo > ().String_utf8string, *yystack_[0].value.as < TokenInfo > ().String_utf8string); }
#line 2373 "parser.tab.cc"
    break;

  case 48: // extern_stmt: "extern" vid "from" expr
#line 391 "parser.yy"
                                    { yylhs.value.as < pdm::ast::Stmt* > () = mgr->new_extern_stmt(yylhs.location, yystack_[2].value.as < TokenInfo > ().ID_intstr, yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2379 "parser.tab.cc"
    break;

  case 49: // tid: "<TypeId>"
#line 398 "parser.yy"
     { yylhs.value.as < TokenInfo > () = yystack_[0].value.as < TokenInfo > (); }
#line 2385 "parser.tab.cc"
    break;

  case 50: // vid: "<val_id>"
#line 399 "parser.yy"
     { yylhs.value.as < TokenInfo > () = yystack_[0].value.as < TokenInfo > (); }
#line 2391 "parser.tab.cc"
    break;

  case 51: // floatl: "4.2"
#line 401 "parser.yy"
      { yylhs.value.as < TokenInfo > () = yystack_[0].value.as < TokenInfo > (); }
#line 2397 "parser.tab.cc"
    break;

  case 52: // stringl: "'sq-string-literal'"
#line 404 "parser.yy"
      { yylhs.value.as < TokenInfo > () = yystack_[0].value.as < TokenInfo > (); }
#line 2403 "parser.tab.cc"
    break;

  case 53: // stringl: "\"dq-string-literal\""
#line 405 "parser.yy"
      { yylhs.value.as < TokenInfo > () = yystack_[0].value.as < TokenInfo > (); }
#line 2409 "parser.tab.cc"
    break;

  case 54: // mod_prefix: tid ":"
#line 408 "parser.yy"
                              { yylhs.value.as < std::vector<pdm::intern::String> > ().push_back(yystack_[1].value.as < TokenInfo > ().ID_intstr); }
#line 2415 "parser.tab.cc"
    break;

  case 55: // mod_prefix: mod_prefix vid ":"
#line 409 "parser.yy"
                              { yylhs.value.as < std::vector<pdm::intern::String> > () = std::move(yystack_[2].value.as < std::vector<pdm::intern::String> > ()); }
#line 2421 "parser.tab.cc"
    break;

  case 56: // expr: binary_exp
#line 416 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2427 "parser.tab.cc"
    break;

  case 57: // long_exp: expr
#line 419 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2433 "parser.tab.cc"
    break;

  case 58: // expr_cl0: %empty
#line 423 "parser.yy"
                             {}
#line 2439 "parser.tab.cc"
    break;

  case 59: // expr_cl0: expr_cl0 "," expr
#line 424 "parser.yy"
                             { yylhs.value.as < std::vector<pdm::ast::Exp*> > () = std::move(yystack_[2].value.as < std::vector<pdm::ast::Exp*> > ()); yylhs.value.as < std::vector<pdm::ast::Exp*> > ().push_back(yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2445 "parser.tab.cc"
    break;

  case 60: // expr_cl2: expr "," expr
#line 427 "parser.yy"
                             { yylhs.value.as < std::vector<pdm::ast::Exp*> > ().reserve(2); yylhs.value.as < std::vector<pdm::ast::Exp*> > ().push_back(yystack_[2].value.as < pdm::ast::Exp* > ()); yylhs.value.as < std::vector<pdm::ast::Exp*> > ().push_back(yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2451 "parser.tab.cc"
    break;

  case 61: // expr_cl2: expr_cl2 "," expr
#line 428 "parser.yy"
                             { yylhs.value.as < std::vector<pdm::ast::Exp*> > () = std::move(yystack_[2].value.as < std::vector<pdm::ast::Exp*> > ()); yylhs.value.as < std::vector<pdm::ast::Exp*> > ().push_back(yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2457 "parser.tab.cc"
    break;

  case 62: // type_query_exp_sl: type_query_exp ";"
#line 431 "parser.yy"
                                       { yylhs.value.as < std::vector<pdm::ast::TypeQueryExp*> > ().push_back(yystack_[1].value.as < pdm::ast::TypeQueryExp* > ()); }
#line 2463 "parser.tab.cc"
    break;

  case 63: // type_query_exp_sl: type_query_exp_sl type_query_exp ";"
#line 432 "parser.yy"
                                                 { yylhs.value.as < std::vector<pdm::ast::TypeQueryExp*> > () = std::move(yystack_[2].value.as < std::vector<pdm::ast::TypeQueryExp*> > ()); yylhs.value.as < std::vector<pdm::ast::TypeQueryExp*> > ().push_back(yystack_[1].value.as < pdm::ast::TypeQueryExp* > ()); }
#line 2469 "parser.tab.cc"
    break;

  case 64: // bracketed_exp: unit_exp
#line 436 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2475 "parser.tab.cc"
    break;

  case 65: // bracketed_exp: paren_exp
#line 437 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2481 "parser.tab.cc"
    break;

  case 66: // bracketed_exp: vtupleExpr
#line 438 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2487 "parser.tab.cc"
    break;

  case 67: // bracketed_exp: vstructExpr
#line 439 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2493 "parser.tab.cc"
    break;

  case 68: // bracketed_exp: chain_exp
#line 440 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2499 "parser.tab.cc"
    break;

  case 69: // unit_exp: "(" ")"
#line 443 "parser.yy"
                        { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_unit_exp(yylhs.location); }
#line 2505 "parser.tab.cc"
    break;

  case 70: // unit_exp: "{" "}"
#line 444 "parser.yy"
                        { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_unit_exp(yylhs.location); }
#line 2511 "parser.tab.cc"
    break;

  case 71: // paren_exp: "(" long_exp ")"
#line 447 "parser.yy"
                              { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_paren_exp(yylhs.location, yystack_[1].value.as < pdm::ast::Exp* > ()); }
#line 2517 "parser.tab.cc"
    break;

  case 72: // vtupleExpr: "(" expr "," ")"
#line 450 "parser.yy"
                                   { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_tuple_exp(yylhs.location, std::move(std::vector(1,yystack_[2].value.as < pdm::ast::Exp* > ()))); }
#line 2523 "parser.tab.cc"
    break;

  case 73: // vtupleExpr: "(" expr_cl2 ")"
#line 451 "parser.yy"
                                   { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_tuple_exp(yylhs.location, std::move(yystack_[1].value.as < std::vector<pdm::ast::Exp*> > ())); }
#line 2529 "parser.tab.cc"
    break;

  case 74: // vstructExpr: "{" struct_exp_field_cl "}"
#line 454 "parser.yy"
                                            { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_struct_exp(yylhs.location, std::move(yystack_[1].value.as < std::vector<pdm::ast::StructExp::Field*> > ())); }
#line 2535 "parser.tab.cc"
    break;

  case 75: // primary_exp: bracketed_exp
#line 457 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2541 "parser.tab.cc"
    break;

  case 76: // primary_exp: vid
#line 458 "parser.yy"
                     { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_id_exp(yylhs.location, yystack_[0].value.as < TokenInfo > ().ID_intstr); }
#line 2547 "parser.tab.cc"
    break;

  case 77: // primary_exp: int_expr
#line 459 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2553 "parser.tab.cc"
    break;

  case 78: // primary_exp: floatl
#line 460 "parser.yy"
                     { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_float_exp(yylhs.location, yystack_[0].value.as < TokenInfo > ().Float); }
#line 2559 "parser.tab.cc"
    break;

  case 79: // primary_exp: stringls
#line 461 "parser.yy"
                     { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_string_exp(yylhs.location, std::move(yystack_[0].value.as < std::vector<pdm::ast::StringExp::Piece> > ())); }
#line 2565 "parser.tab.cc"
    break;

  case 80: // primary_exp: if_exp
#line 462 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2571 "parser.tab.cc"
    break;

  case 81: // primary_exp: lambda_exp
#line 463 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2577 "parser.tab.cc"
    break;

  case 82: // int_expr: "42"
#line 466 "parser.yy"
                { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_int_exp(yylhs.location, yystack_[0].value.as < TokenInfo > ().Int, ast::IntExp::Base::Dec); }
#line 2583 "parser.tab.cc"
    break;

  case 83: // int_expr: "0x2a"
#line 467 "parser.yy"
                { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_int_exp(yylhs.location, yystack_[0].value.as < TokenInfo > ().Int, ast::IntExp::Base::Hex); }
#line 2589 "parser.tab.cc"
    break;

  case 84: // stringls: "'sq-string-literal'"
#line 470 "parser.yy"
                             { yylhs.value.as < std::vector<pdm::ast::StringExp::Piece> > ().emplace_back(yylhs.location, *yystack_[0].value.as < TokenInfo > ().String_utf8string, ast::StringExp::QuoteKind::SingleQuote); }
#line 2595 "parser.tab.cc"
    break;

  case 85: // stringls: "\"dq-string-literal\""
#line 471 "parser.yy"
                             { yylhs.value.as < std::vector<pdm::ast::StringExp::Piece> > ().emplace_back(yylhs.location, *yystack_[0].value.as < TokenInfo > ().String_utf8string, ast::StringExp::QuoteKind::DoubleQuote); }
#line 2601 "parser.tab.cc"
    break;

  case 86: // stringls: stringls "'sq-string-literal'"
#line 472 "parser.yy"
                             { yylhs.value.as < std::vector<pdm::ast::StringExp::Piece> > () = std::move(yystack_[1].value.as < std::vector<pdm::ast::StringExp::Piece> > ()); yylhs.value.as < std::vector<pdm::ast::StringExp::Piece> > ().emplace_back(yystack_[0].location, *yystack_[0].value.as < TokenInfo > ().String_utf8string, ast::StringExp::QuoteKind::SingleQuote); }
#line 2607 "parser.tab.cc"
    break;

  case 87: // stringls: stringls "\"dq-string-literal\""
#line 473 "parser.yy"
                             { yylhs.value.as < std::vector<pdm::ast::StringExp::Piece> > () = std::move(yystack_[1].value.as < std::vector<pdm::ast::StringExp::Piece> > ()); yylhs.value.as < std::vector<pdm::ast::StringExp::Piece> > ().emplace_back(yystack_[0].location, *yystack_[0].value.as < TokenInfo > ().String_utf8string, ast::StringExp::QuoteKind::DoubleQuote); }
#line 2613 "parser.tab.cc"
    break;

  case 88: // if_exp: "if" bracketed_exp "then" bracketed_exp
#line 476 "parser.yy"
                                                                        { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_if_exp(yylhs.location, yystack_[2].value.as < pdm::ast::Exp* > (), yystack_[0].value.as < pdm::ast::Exp* > (), nullptr); }
#line 2619 "parser.tab.cc"
    break;

  case 89: // if_exp: "if" bracketed_exp "then" bracketed_exp "else" primary_exp
#line 477 "parser.yy"
                                                                        { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_if_exp(yylhs.location, yystack_[4].value.as < pdm::ast::Exp* > (), yystack_[2].value.as < pdm::ast::Exp* > (), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2625 "parser.tab.cc"
    break;

  case 90: // chain_exp: "{" expr "}"
#line 480 "parser.yy"
                                          { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_chain_exp(yylhs.location, std::move(std::vector<ast::Stmt*>{}), yystack_[1].value.as < pdm::ast::Exp* > ()); }
#line 2631 "parser.tab.cc"
    break;

  case 91: // chain_exp: "{" chain_prefix "}"
#line 481 "parser.yy"
                                           { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_chain_exp(yylhs.location, std::move(yystack_[1].value.as < std::vector<pdm::ast::Stmt*> > ()), nullptr); }
#line 2637 "parser.tab.cc"
    break;

  case 92: // chain_exp: "{" chain_prefix expr "}"
#line 482 "parser.yy"
                                           { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_chain_exp(yylhs.location, std::move(yystack_[2].value.as < std::vector<pdm::ast::Stmt*> > ()), yystack_[1].value.as < pdm::ast::Exp* > ()); }
#line 2643 "parser.tab.cc"
    break;

  case 93: // chain_prefix: chain_prefix_stmt ";"
#line 485 "parser.yy"
                                               { yylhs.value.as < std::vector<pdm::ast::Stmt*> > ().push_back(yystack_[1].value.as < pdm::ast::Stmt* > ()); }
#line 2649 "parser.tab.cc"
    break;

  case 94: // chain_prefix: chain_prefix chain_prefix_stmt ";"
#line 486 "parser.yy"
                                                { yylhs.value.as < std::vector<pdm::ast::Stmt*> > () = std::move(yystack_[2].value.as < std::vector<pdm::ast::Stmt*> > ()); yylhs.value.as < std::vector<pdm::ast::Stmt*> > ().push_back(yystack_[1].value.as < pdm::ast::Stmt* > ()); }
#line 2655 "parser.tab.cc"
    break;

  case 95: // lambda_exp: "lambda" vpattern "=" bracketed_exp
#line 489 "parser.yy"
                                              { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_lambda_exp(yylhs.location, yystack_[2].value.as < pdm::ast::VPattern* > (), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2661 "parser.tab.cc"
    break;

  case 96: // postfix_exp: primary_exp
#line 493 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2667 "parser.tab.cc"
    break;

  case 97: // postfix_exp: tcall_exp
#line 494 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2673 "parser.tab.cc"
    break;

  case 98: // postfix_exp: vcall_exp
#line 495 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2679 "parser.tab.cc"
    break;

  case 99: // postfix_exp: dot_name_exp
#line 496 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2685 "parser.tab.cc"
    break;

  case 100: // postfix_exp: dot_index_exp
#line 497 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2691 "parser.tab.cc"
    break;

  case 101: // tcall_exp: postfix_exp "[" targ_cl "]"
#line 500 "parser.yy"
                                         { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_tcall_exp(yylhs.location, yystack_[3].value.as < pdm::ast::Exp* > (), std::move(yystack_[1].value.as < std::vector<pdm::ast::TArg*> > ())); }
#line 2697 "parser.tab.cc"
    break;

  case 102: // vcall_exp: postfix_exp "(" ")"
#line 503 "parser.yy"
                                            { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_vcall_exp(yylhs.location, yystack_[2].value.as < pdm::ast::Exp* > (), std::move(std::vector<ast::VArg*>{})); }
#line 2703 "parser.tab.cc"
    break;

  case 103: // vcall_exp: postfix_exp "(" varg_cl ")"
#line 504 "parser.yy"
                                            { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_vcall_exp(yylhs.location, yystack_[3].value.as < pdm::ast::Exp* > (), std::move(yystack_[1].value.as < std::vector<pdm::ast::VArg*> > ())); }
#line 2709 "parser.tab.cc"
    break;

  case 104: // dot_name_exp: postfix_exp "." "<val_id>"
#line 507 "parser.yy"
                                                    { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_struct_dot_name_exp(yylhs.location, yystack_[2].value.as < pdm::ast::Exp* > (), yystack_[0].value.as < TokenInfo > ().ID_intstr); }
#line 2715 "parser.tab.cc"
    break;

  case 105: // dot_name_exp: postfix_exp "." "<TypeId>" "(" expr_cl0 ")"
#line 508 "parser.yy"
                                                    { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_enum_dot_name_exp(yylhs.location, yystack_[5].value.as < pdm::ast::Exp* > (), yystack_[3].value.as < TokenInfo > ().ID_intstr, std::move(yystack_[1].value.as < std::vector<pdm::ast::Exp*> > ())); }
#line 2721 "parser.tab.cc"
    break;

  case 106: // dot_name_exp: mod_prefix "<val_id>"
#line 509 "parser.yy"
                       { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_module_dot_exp(yylhs.location, std::move(yystack_[1].value.as < std::vector<pdm::intern::String> > ()), yystack_[0].value.as < TokenInfo > ().ID_intstr); }
#line 2727 "parser.tab.cc"
    break;

  case 107: // dot_index_exp: postfix_exp "." int_expr
#line 512 "parser.yy"
                                    { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_dot_index_exp(yylhs.location, yystack_[2].value.as < pdm::ast::Exp* > (), yystack_[0].value.as < pdm::ast::Exp* > (), ast::DotIndexExp::RhsHint::LhsNotPtr); }
#line 2733 "parser.tab.cc"
    break;

  case 108: // dot_index_exp: postfix_exp "." bracketed_exp
#line 513 "parser.yy"
                                    { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_dot_index_exp(yylhs.location, yystack_[2].value.as < pdm::ast::Exp* > (), yystack_[0].value.as < pdm::ast::Exp* > (), ast::DotIndexExp::RhsHint::LhsNotPtr); }
#line 2739 "parser.tab.cc"
    break;

  case 109: // unary_exp: postfix_exp
#line 517 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2745 "parser.tab.cc"
    break;

  case 110: // unary_exp: unary_op unary_exp
#line 518 "parser.yy"
                             { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_unary_exp(yylhs.location, yystack_[1].value.as < pdm::ast::UnaryOperator > (), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2751 "parser.tab.cc"
    break;

  case 111: // unary_op: "+"
#line 521 "parser.yy"
                 { yylhs.value.as < pdm::ast::UnaryOperator > () = ast::UnaryOperator::Plus; }
#line 2757 "parser.tab.cc"
    break;

  case 112: // unary_op: "-"
#line 522 "parser.yy"
                 { yylhs.value.as < pdm::ast::UnaryOperator > () = ast::UnaryOperator::Minus; }
#line 2763 "parser.tab.cc"
    break;

  case 113: // unary_op: "*"
#line 523 "parser.yy"
                 { yylhs.value.as < pdm::ast::UnaryOperator > () = ast::UnaryOperator::DeRef; }
#line 2769 "parser.tab.cc"
    break;

  case 114: // unary_op: "^"
#line 524 "parser.yy"
                 { yylhs.value.as < pdm::ast::UnaryOperator > () = ast::UnaryOperator::GetRef; }
#line 2775 "parser.tab.cc"
    break;

  case 115: // unary_op: "not"
#line 525 "parser.yy"
                 { yylhs.value.as < pdm::ast::UnaryOperator > () = ast::UnaryOperator::Not; }
#line 2781 "parser.tab.cc"
    break;

  case 116: // binary_exp: or_binary_exp
#line 529 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2787 "parser.tab.cc"
    break;

  case 117: // mul_binary_op: "*"
#line 532 "parser.yy"
                 { yylhs.value.as < pdm::ast::BinaryOperator > () = ast::BinaryOperator::Mul; }
#line 2793 "parser.tab.cc"
    break;

  case 118: // mul_binary_op: "/"
#line 533 "parser.yy"
                 { yylhs.value.as < pdm::ast::BinaryOperator > () = ast::BinaryOperator::Div; }
#line 2799 "parser.tab.cc"
    break;

  case 119: // mul_binary_op: "%"
#line 534 "parser.yy"
                 { yylhs.value.as < pdm::ast::BinaryOperator > () = ast::BinaryOperator::Rem; }
#line 2805 "parser.tab.cc"
    break;

  case 120: // mul_binary_exp: unary_exp
#line 537 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2811 "parser.tab.cc"
    break;

  case 121: // mul_binary_exp: mul_binary_exp mul_binary_op unary_exp
#line 538 "parser.yy"
                                               { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_binary_exp(yylhs.location, yystack_[1].value.as < pdm::ast::BinaryOperator > (), yystack_[2].value.as < pdm::ast::Exp* > (), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2817 "parser.tab.cc"
    break;

  case 122: // add_binary_op: "+"
#line 541 "parser.yy"
             { yylhs.value.as < pdm::ast::BinaryOperator > () = ast::BinaryOperator::Add; }
#line 2823 "parser.tab.cc"
    break;

  case 123: // add_binary_op: "-"
#line 542 "parser.yy"
             { yylhs.value.as < pdm::ast::BinaryOperator > () = ast::BinaryOperator::Subtract; }
#line 2829 "parser.tab.cc"
    break;

  case 124: // add_binary_exp: mul_binary_exp
#line 545 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2835 "parser.tab.cc"
    break;

  case 125: // add_binary_exp: add_binary_exp add_binary_op mul_binary_exp
#line 546 "parser.yy"
                                                    { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_binary_exp(yylhs.location, yystack_[1].value.as < pdm::ast::BinaryOperator > (), yystack_[2].value.as < pdm::ast::Exp* > (), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2841 "parser.tab.cc"
    break;

  case 126: // cmp_binary_op: "<"
#line 549 "parser.yy"
                { yylhs.value.as < pdm::ast::BinaryOperator > () = ast::BinaryOperator::Less; }
#line 2847 "parser.tab.cc"
    break;

  case 127: // cmp_binary_op: "<="
#line 550 "parser.yy"
                { yylhs.value.as < pdm::ast::BinaryOperator > () = ast::BinaryOperator::LessOrEq; }
#line 2853 "parser.tab.cc"
    break;

  case 128: // cmp_binary_op: ">"
#line 551 "parser.yy"
                { yylhs.value.as < pdm::ast::BinaryOperator > () = ast::BinaryOperator::Greater; }
#line 2859 "parser.tab.cc"
    break;

  case 129: // cmp_binary_op: ">="
#line 552 "parser.yy"
                { yylhs.value.as < pdm::ast::BinaryOperator > () = ast::BinaryOperator::GreaterOrEq; }
#line 2865 "parser.tab.cc"
    break;

  case 130: // cmp_binary_exp: add_binary_exp
#line 555 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2871 "parser.tab.cc"
    break;

  case 131: // cmp_binary_exp: cmp_binary_exp cmp_binary_op add_binary_exp
#line 556 "parser.yy"
                                                    { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_binary_exp(yylhs.location, yystack_[1].value.as < pdm::ast::BinaryOperator > (), yystack_[2].value.as < pdm::ast::Exp* > (), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2877 "parser.tab.cc"
    break;

  case 132: // eq_binary_op: "=="
#line 559 "parser.yy"
                 { yylhs.value.as < pdm::ast::BinaryOperator > () = ast::BinaryOperator::Equals; }
#line 2883 "parser.tab.cc"
    break;

  case 133: // eq_binary_op: "!="
#line 560 "parser.yy"
                 { yylhs.value.as < pdm::ast::BinaryOperator > () = ast::BinaryOperator::NotEquals; }
#line 2889 "parser.tab.cc"
    break;

  case 134: // eq_binary_exp: cmp_binary_exp
#line 563 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2895 "parser.tab.cc"
    break;

  case 135: // eq_binary_exp: eq_binary_exp eq_binary_op cmp_binary_exp
#line 564 "parser.yy"
                                                { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_binary_exp(yylhs.location, yystack_[1].value.as < pdm::ast::BinaryOperator > (), yystack_[2].value.as < pdm::ast::Exp* > (), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2901 "parser.tab.cc"
    break;

  case 136: // and_binary_exp: eq_binary_exp
#line 567 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2907 "parser.tab.cc"
    break;

  case 137: // and_binary_exp: and_binary_exp "and" eq_binary_exp
#line 568 "parser.yy"
                                           { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_binary_exp(yylhs.location, ast::BinaryOperator::And, yystack_[2].value.as < pdm::ast::Exp* > (), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2913 "parser.tab.cc"
    break;

  case 138: // xor_binary_exp: and_binary_exp
#line 571 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2919 "parser.tab.cc"
    break;

  case 139: // xor_binary_exp: xor_binary_exp "xor" and_binary_exp
#line 572 "parser.yy"
                                           { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_binary_exp(yylhs.location, ast::BinaryOperator::XOr, yystack_[2].value.as < pdm::ast::Exp* > (), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2925 "parser.tab.cc"
    break;

  case 140: // or_binary_exp: xor_binary_exp
#line 575 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2931 "parser.tab.cc"
    break;

  case 141: // or_binary_exp: or_binary_exp "or" xor_binary_exp
#line 576 "parser.yy"
                                           { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_binary_exp(yylhs.location, ast::BinaryOperator::Or, yystack_[2].value.as < pdm::ast::Exp* > (), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2937 "parser.tab.cc"
    break;

  case 142: // type_query_exp: typespec type_query_op typespec
#line 580 "parser.yy"
                                        { yylhs.value.as < pdm::ast::TypeQueryExp* > () = mgr->new_type_query_exp(yylhs.location, yystack_[1].value.as < pdm::ast::TypeQueryKind > (), yystack_[2].value.as < pdm::ast::Typespec* > (), yystack_[0].value.as < pdm::ast::Typespec* > ()); }
#line 2943 "parser.tab.cc"
    break;

  case 143: // type_query_op: ":<"
#line 583 "parser.yy"
                    { yylhs.value.as < pdm::ast::TypeQueryKind > () = ast::TypeQueryKind::LhsSubtypesRhs; }
#line 2949 "parser.tab.cc"
    break;

  case 144: // type_query_op: ">:"
#line 584 "parser.yy"
                    { yylhs.value.as < pdm::ast::TypeQueryKind > () = ast::TypeQueryKind::LhsSupertypesRhs; }
#line 2955 "parser.tab.cc"
    break;

  case 145: // type_query_op: "::"
#line 585 "parser.yy"
                    { yylhs.value.as < pdm::ast::TypeQueryKind > () = ast::TypeQueryKind::LhsEqualsRhs; }
#line 2961 "parser.tab.cc"
    break;

  case 146: // typespec: unary_typespec
#line 593 "parser.yy"
      { yylhs.value.as < pdm::ast::Typespec* > () = yystack_[0].value.as < pdm::ast::Typespec* > (); }
#line 2967 "parser.tab.cc"
    break;

  case 147: // typespec_cl1: typespec
#line 596 "parser.yy"
                                  { yylhs.value.as < std::vector<pdm::ast::Typespec*> > ().push_back(yystack_[0].value.as < pdm::ast::Typespec* > ()); }
#line 2973 "parser.tab.cc"
    break;

  case 148: // typespec_cl1: typespec_cl1 "," typespec
#line 597 "parser.yy"
                                  { yylhs.value.as < std::vector<pdm::ast::Typespec*> > () = std::move(yystack_[2].value.as < std::vector<pdm::ast::Typespec*> > ()); yylhs.value.as < std::vector<pdm::ast::Typespec*> > ().push_back(yystack_[0].value.as < pdm::ast::Typespec* > ()); }
#line 2979 "parser.tab.cc"
    break;

  case 149: // typespec_cl2: typespec "," typespec
#line 600 "parser.yy"
                                  { yylhs.value.as < std::vector<pdm::ast::Typespec*> > ().reserve(2); yylhs.value.as < std::vector<pdm::ast::Typespec*> > ().push_back(yystack_[2].value.as < pdm::ast::Typespec* > ()); yylhs.value.as < std::vector<pdm::ast::Typespec*> > ().push_back(yystack_[0].value.as < pdm::ast::Typespec* > ()); }
#line 2985 "parser.tab.cc"
    break;

  case 150: // typespec_cl2: typespec_cl2 "," typespec
#line 601 "parser.yy"
                                  { yylhs.value.as < std::vector<pdm::ast::Typespec*> > () = std::move(yystack_[2].value.as < std::vector<pdm::ast::Typespec*> > ()); yylhs.value.as < std::vector<pdm::ast::Typespec*> > ().push_back(yystack_[0].value.as < pdm::ast::Typespec* > ()); }
#line 2991 "parser.tab.cc"
    break;

  case 151: // struct_typespec_field: vid typespec
#line 605 "parser.yy"
                                  { yylhs.value.as < pdm::ast::StructTypespec::Field* > () = mgr->new_struct_typespec_field(yylhs.location, yystack_[1].value.as < TokenInfo > ().ID_intstr, yystack_[0].value.as < pdm::ast::Typespec* > ()); }
#line 2997 "parser.tab.cc"
    break;

  case 152: // struct_typespec_field_cl: struct_typespec_field
#line 608 "parser.yy"
                                                          { yylhs.value.as < std::vector<pdm::ast::StructTypespec::Field*> > ().push_back(yystack_[0].value.as < pdm::ast::StructTypespec::Field* > ()); }
#line 3003 "parser.tab.cc"
    break;

  case 153: // struct_typespec_field_cl: struct_typespec_field_cl "," struct_typespec_field
#line 609 "parser.yy"
                                                            { yylhs.value.as < std::vector<pdm::ast::StructTypespec::Field*> > () = std::move(yystack_[2].value.as < std::vector<pdm::ast::StructTypespec::Field*> > ()); yylhs.value.as < std::vector<pdm::ast::StructTypespec::Field*> > ().push_back(yystack_[0].value.as < pdm::ast::StructTypespec::Field* > ()); }
#line 3009 "parser.tab.cc"
    break;

  case 154: // primary_typespec: tid
#line 613 "parser.yy"
                        { yylhs.value.as < pdm::ast::Typespec* > () = mgr->new_id_typespec(yylhs.location, yystack_[0].value.as < TokenInfo > ().ID_intstr); }
#line 3015 "parser.tab.cc"
    break;

  case 155: // primary_typespec: paren_typespec
#line 614 "parser.yy"
      { yylhs.value.as < pdm::ast::Typespec* > () = yystack_[0].value.as < pdm::ast::Typespec* > (); }
#line 3021 "parser.tab.cc"
    break;

  case 156: // primary_typespec: tuple_typespec
#line 615 "parser.yy"
      { yylhs.value.as < pdm::ast::Typespec* > () = yystack_[0].value.as < pdm::ast::Typespec* > (); }
#line 3027 "parser.tab.cc"
    break;

  case 157: // primary_typespec: mod_prefix_tid
#line 616 "parser.yy"
      { yylhs.value.as < pdm::ast::Typespec* > () = yystack_[0].value.as < pdm::ast::Typespec* > (); }
#line 3033 "parser.tab.cc"
    break;

  case 158: // primary_typespec: fn_typespec
#line 617 "parser.yy"
      { yylhs.value.as < pdm::ast::Typespec* > () = yystack_[0].value.as < pdm::ast::Typespec* > (); }
#line 3039 "parser.tab.cc"
    break;

  case 159: // paren_typespec: "(" typespec ")"
#line 620 "parser.yy"
                                { yylhs.value.as < pdm::ast::Typespec* > () = mgr->new_paren_typespec(yylhs.location, yystack_[1].value.as < pdm::ast::Typespec* > ()); }
#line 3045 "parser.tab.cc"
    break;

  case 160: // tuple_typespec: "(" typespec "," ")"
#line 623 "parser.yy"
                                    { yylhs.value.as < pdm::ast::Typespec* > () = mgr->new_tuple_typespec(yylhs.location, std::move(std::vector(1,yystack_[2].value.as < pdm::ast::Typespec* > ()))); }
#line 3051 "parser.tab.cc"
    break;

  case 161: // tuple_typespec: "(" typespec_cl2 ")"
#line 624 "parser.yy"
                                    { yylhs.value.as < pdm::ast::Typespec* > () = mgr->new_tuple_typespec(yylhs.location, std::move(yystack_[1].value.as < std::vector<pdm::ast::Typespec*> > ())); }
#line 3057 "parser.tab.cc"
    break;

  case 162: // mod_prefix_tid: mod_prefix tid
#line 627 "parser.yy"
                            { yylhs.value.as < pdm::ast::Typespec* > () = mgr->new_dot_name_typespec_with_mod_prefix(yylhs.location, std::move(yystack_[1].value.as < std::vector<pdm::intern::String> > ()), yystack_[0].value.as < TokenInfo > ().ID_intstr); }
#line 3063 "parser.tab.cc"
    break;

  case 163: // fn_typespec: "Fn" vpattern primary_typespec
#line 630 "parser.yy"
                                       { yylhs.value.as < pdm::ast::Typespec* > () = mgr->new_fn_typespec(yylhs.location, std::move(yystack_[1].value.as < pdm::ast::VPattern* > ()), yystack_[0].value.as < pdm::ast::Typespec* > ()); }
#line 3069 "parser.tab.cc"
    break;

  case 164: // postfix_typespec: primary_typespec
#line 634 "parser.yy"
      { yylhs.value.as < pdm::ast::Typespec* > () = yystack_[0].value.as < pdm::ast::Typespec* > (); }
#line 3075 "parser.tab.cc"
    break;

  case 165: // postfix_typespec: tcall_typespec
#line 635 "parser.yy"
      { yylhs.value.as < pdm::ast::Typespec* > () = yystack_[0].value.as < pdm::ast::Typespec* > (); }
#line 3081 "parser.tab.cc"
    break;

  case 166: // tcall_typespec: postfix_typespec "[" targ_cl "]"
#line 638 "parser.yy"
                                              { yylhs.value.as < pdm::ast::Typespec* > () = mgr->new_tcall_typespec(yylhs.location, yystack_[3].value.as < pdm::ast::Typespec* > (), std::move(yystack_[1].value.as < std::vector<pdm::ast::TArg*> > ())); }
#line 3087 "parser.tab.cc"
    break;

  case 167: // unary_typespec: postfix_typespec
#line 642 "parser.yy"
      { yylhs.value.as < pdm::ast::Typespec* > () = yystack_[0].value.as < pdm::ast::Typespec* > (); }
#line 3093 "parser.tab.cc"
    break;

  case 168: // long_typespec: unary_typespec
#line 646 "parser.yy"
      { yylhs.value.as < pdm::ast::Typespec* > () = yystack_[0].value.as < pdm::ast::Typespec* > (); }
#line 3099 "parser.tab.cc"
    break;

  case 169: // long_typespec: struct_typespec
#line 647 "parser.yy"
      { yylhs.value.as < pdm::ast::Typespec* > () = yystack_[0].value.as < pdm::ast::Typespec* > (); }
#line 3105 "parser.tab.cc"
    break;

  case 170: // struct_typespec: "{" struct_typespec_field_cl "}"
#line 650 "parser.yy"
                                              { yylhs.value.as < pdm::ast::Typespec* > () = mgr->new_struct_typespec(yylhs.location, std::move(yystack_[1].value.as < std::vector<pdm::ast::StructTypespec::Field*> > ())); }
#line 3111 "parser.tab.cc"
    break;

  case 171: // targ: typespec
#line 653 "parser.yy"
               { yylhs.value.as < pdm::ast::TArg* > () = mgr->new_targ_typespec(yylhs.location, yystack_[0].value.as < pdm::ast::Typespec* > ()); }
#line 3117 "parser.tab.cc"
    break;

  case 172: // targ: expr
#line 654 "parser.yy"
               { yylhs.value.as < pdm::ast::TArg* > () = mgr->new_targ_exp(yylhs.location, yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 3123 "parser.tab.cc"
    break;

  case 173: // targ_cl: targ
#line 657 "parser.yy"
                            { yylhs.value.as < std::vector<pdm::ast::TArg*> > ().push_back(yystack_[0].value.as < pdm::ast::TArg* > ()); }
#line 3129 "parser.tab.cc"
    break;

  case 174: // targ_cl: targ_cl "," targ
#line 658 "parser.yy"
                            { yylhs.value.as < std::vector<pdm::ast::TArg*> > () = std::move(yystack_[2].value.as < std::vector<pdm::ast::TArg*> > ()); yylhs.value.as < std::vector<pdm::ast::TArg*> > ().push_back(yystack_[0].value.as < pdm::ast::TArg* > ()); }
#line 3135 "parser.tab.cc"
    break;

  case 175: // varg: expr
#line 660 "parser.yy"
                            { yylhs.value.as < pdm::ast::VArg* > () = mgr->new_varg(yylhs.location, yystack_[0].value.as < pdm::ast::Exp* > (), ast::VArgAccessSpec::In); }
#line 3141 "parser.tab.cc"
    break;

  case 176: // varg: "out" expr
#line 661 "parser.yy"
                            { yylhs.value.as < pdm::ast::VArg* > () = mgr->new_varg(yylhs.location, yystack_[0].value.as < pdm::ast::Exp* > (), ast::VArgAccessSpec::Out); }
#line 3147 "parser.tab.cc"
    break;

  case 177: // varg: "inout" expr
#line 662 "parser.yy"
                            { yylhs.value.as < pdm::ast::VArg* > () = mgr->new_varg(yylhs.location, yystack_[0].value.as < pdm::ast::Exp* > (), ast::VArgAccessSpec::InOut); }
#line 3153 "parser.tab.cc"
    break;

  case 178: // varg_cl: varg
#line 665 "parser.yy"
                            { yylhs.value.as < std::vector<pdm::ast::VArg*> > ().push_back(yystack_[0].value.as < pdm::ast::VArg* > ()); }
#line 3159 "parser.tab.cc"
    break;

  case 179: // varg_cl: varg_cl "," varg
#line 666 "parser.yy"
                            { yylhs.value.as < std::vector<pdm::ast::VArg*> > () = std::move(yystack_[2].value.as < std::vector<pdm::ast::VArg*> > ()); yylhs.value.as < std::vector<pdm::ast::VArg*> > ().push_back(yystack_[0].value.as < pdm::ast::VArg* > ()); }
#line 3165 "parser.tab.cc"
    break;

  case 180: // struct_exp_field: vid "=" expr
#line 674 "parser.yy"
                    { yylhs.value.as < pdm::ast::StructExp::Field* > () = mgr->new_struct_exp_field(yylhs.location, yystack_[2].value.as < TokenInfo > ().ID_intstr, yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 3171 "parser.tab.cc"
    break;

  case 181: // vpattern_field: vid typespec
#line 677 "parser.yy"
                            { yylhs.value.as < pdm::ast::VPattern::Field* > () = mgr->new_vpattern_field(yylhs.location, yystack_[1].value.as < TokenInfo > ().ID_intstr, yystack_[0].value.as < pdm::ast::Typespec* > (), ast::VArgAccessSpec::In); }
#line 3177 "parser.tab.cc"
    break;

  case 182: // vpattern_field: "out" vid typespec
#line 678 "parser.yy"
                            { yylhs.value.as < pdm::ast::VPattern::Field* > () = mgr->new_vpattern_field(yylhs.location, yystack_[1].value.as < TokenInfo > ().ID_intstr, yystack_[0].value.as < pdm::ast::Typespec* > (), ast::VArgAccessSpec::Out); }
#line 3183 "parser.tab.cc"
    break;

  case 183: // vpattern_field: "inout" vid typespec
#line 679 "parser.yy"
                            { yylhs.value.as < pdm::ast::VPattern::Field* > () = mgr->new_vpattern_field(yylhs.location, yystack_[1].value.as < TokenInfo > ().ID_intstr, yystack_[0].value.as < pdm::ast::Typespec* > (), ast::VArgAccessSpec::InOut); }
#line 3189 "parser.tab.cc"
    break;

  case 184: // lpattern_field: vid typespec
#line 682 "parser.yy"
                    { yylhs.value.as < pdm::ast::LPattern::Field* > () = mgr->new_lpattern_field(yylhs.location, ast::LPattern::FieldKind::IdTypespecPair, yystack_[1].value.as < TokenInfo > ().ID_intstr, yystack_[0].value.as < pdm::ast::Typespec* > ()); }
#line 3195 "parser.tab.cc"
    break;

  case 185: // lpattern_field: vid
#line 683 "parser.yy"
                    { yylhs.value.as < pdm::ast::LPattern::Field* > () = mgr->new_lpattern_field(yylhs.location, ast::LPattern::FieldKind::IdSingleton, yystack_[0].value.as < TokenInfo > ().ID_intstr); }
#line 3201 "parser.tab.cc"
    break;

  case 186: // tpattern_field: vid typespec
#line 686 "parser.yy"
                    { yylhs.value.as < pdm::ast::TPattern::Field* > () = mgr->new_tpattern_field(yylhs.location, ast::TPattern::FieldKind::Value, yystack_[1].value.as < TokenInfo > ().ID_intstr, yystack_[0].value.as < pdm::ast::Typespec* > ()); }
#line 3207 "parser.tab.cc"
    break;

  case 187: // tpattern_field: tid typespec
#line 687 "parser.yy"
                    { yylhs.value.as < pdm::ast::TPattern::Field* > () = mgr->new_tpattern_field(yylhs.location, ast::TPattern::FieldKind::Type, yystack_[1].value.as < TokenInfo > ().ID_intstr, yystack_[0].value.as < pdm::ast::Typespec* > ()); }
#line 3213 "parser.tab.cc"
    break;

  case 188: // destructured_lpattern: "(" lpattern_field_cl ")"
#line 691 "parser.yy"
                                          { yylhs.value.as < pdm::ast::LPattern* > () = mgr->new_lpattern(yylhs.location, std::move(yystack_[1].value.as < std::vector<pdm::ast::LPattern::Field*> > ()), true); }
#line 3219 "parser.tab.cc"
    break;

  case 189: // lpattern: lpattern_field
#line 695 "parser.yy"
                        { yylhs.value.as < pdm::ast::LPattern* > () = mgr->new_lpattern(yylhs.location, std::move(std::vector<ast::LPattern::Field*>{1,yystack_[0].value.as < pdm::ast::LPattern::Field* > ()}), false); }
#line 3225 "parser.tab.cc"
    break;

  case 190: // lpattern: destructured_lpattern
#line 696 "parser.yy"
      { yylhs.value.as < pdm::ast::LPattern* > () = yystack_[0].value.as < pdm::ast::LPattern* > (); }
#line 3231 "parser.tab.cc"
    break;

  case 191: // vpattern: "(" vpattern_field_cl ")"
#line 699 "parser.yy"
                                       { yylhs.value.as < pdm::ast::VPattern* > () = mgr->new_vpattern(yylhs.location, std::move(yystack_[1].value.as < std::vector<pdm::ast::VPattern::Field*> > ())); }
#line 3237 "parser.tab.cc"
    break;

  case 192: // vpattern: "(" ")"
#line 700 "parser.yy"
                                       { yylhs.value.as < pdm::ast::VPattern* > () = mgr->new_vpattern(yylhs.location, std::move(std::vector<ast::VPattern::Field*>{})); }
#line 3243 "parser.tab.cc"
    break;

  case 193: // tpattern: "[" tpattern_field_cl "]"
#line 703 "parser.yy"
                                               { yylhs.value.as < pdm::ast::TPattern* > () = mgr->new_tpattern(yylhs.location, std::move(yystack_[1].value.as < std::vector<pdm::ast::TPattern::Field*> > ()), false); }
#line 3249 "parser.tab.cc"
    break;

  case 194: // tpattern: "!" "[" tpattern_field_cl "]"
#line 704 "parser.yy"
                                               { yylhs.value.as < pdm::ast::TPattern* > () = mgr->new_tpattern(yylhs.location, std::move(yystack_[1].value.as < std::vector<pdm::ast::TPattern::Field*> > ()), true); }
#line 3255 "parser.tab.cc"
    break;

  case 195: // vpattern_field_cl: vpattern_field
#line 708 "parser.yy"
                                              { yylhs.value.as < std::vector<pdm::ast::VPattern::Field*> > ().push_back(yystack_[0].value.as < pdm::ast::VPattern::Field* > ()); }
#line 3261 "parser.tab.cc"
    break;

  case 196: // vpattern_field_cl: vpattern_field_cl "," vpattern_field
#line 709 "parser.yy"
                                               { yylhs.value.as < std::vector<pdm::ast::VPattern::Field*> > () = std::move(yystack_[2].value.as < std::vector<pdm::ast::VPattern::Field*> > ()); yylhs.value.as < std::vector<pdm::ast::VPattern::Field*> > ().push_back(yystack_[0].value.as < pdm::ast::VPattern::Field* > ()); }
#line 3267 "parser.tab.cc"
    break;

  case 197: // lpattern_field_cl: lpattern_field
#line 712 "parser.yy"
                                              { yylhs.value.as < std::vector<pdm::ast::LPattern::Field*> > ().push_back(yystack_[0].value.as < pdm::ast::LPattern::Field* > ()); }
#line 3273 "parser.tab.cc"
    break;

  case 198: // lpattern_field_cl: lpattern_field_cl "," lpattern_field
#line 713 "parser.yy"
                                               { yylhs.value.as < std::vector<pdm::ast::LPattern::Field*> > () = std::move(yystack_[2].value.as < std::vector<pdm::ast::LPattern::Field*> > ()); yylhs.value.as < std::vector<pdm::ast::LPattern::Field*> > ().push_back(yystack_[0].value.as < pdm::ast::LPattern::Field* > ()); }
#line 3279 "parser.tab.cc"
    break;

  case 199: // tpattern_field_cl: tpattern_field
#line 716 "parser.yy"
                                              { yylhs.value.as < std::vector<pdm::ast::TPattern::Field*> > ().push_back(yystack_[0].value.as < pdm::ast::TPattern::Field* > ()); }
#line 3285 "parser.tab.cc"
    break;

  case 200: // tpattern_field_cl: tpattern_field_cl "," tpattern_field
#line 717 "parser.yy"
                                               { yylhs.value.as < std::vector<pdm::ast::TPattern::Field*> > () = std::move(yystack_[2].value.as < std::vector<pdm::ast::TPattern::Field*> > ()); yylhs.value.as < std::vector<pdm::ast::TPattern::Field*> > ().push_back(yystack_[0].value.as < pdm::ast::TPattern::Field* > ()); }
#line 3291 "parser.tab.cc"
    break;

  case 201: // struct_exp_field_cl: struct_exp_field
#line 720 "parser.yy"
                                                    { yylhs.value.as < std::vector<pdm::ast::StructExp::Field*> > ().push_back(yystack_[0].value.as < pdm::ast::StructExp::Field* > ()); }
#line 3297 "parser.tab.cc"
    break;

  case 202: // struct_exp_field_cl: struct_exp_field_cl "," struct_exp_field
#line 721 "parser.yy"
                                                    { yylhs.value.as < std::vector<pdm::ast::StructExp::Field*> > () = std::move(yystack_[2].value.as < std::vector<pdm::ast::StructExp::Field*> > ()); yylhs.value.as < std::vector<pdm::ast::StructExp::Field*> > ().push_back(yystack_[0].value.as < pdm::ast::StructExp::Field* > ()); }
#line 3303 "parser.tab.cc"
    break;

  case 203: // tpattern_seq: tpattern
#line 725 "parser.yy"
                             { yylhs.value.as < std::vector<pdm::ast::TPattern*> > ().push_back(yystack_[0].value.as < pdm::ast::TPattern* > ()); }
#line 3309 "parser.tab.cc"
    break;

  case 204: // tpattern_seq: tpattern_seq tpattern
#line 726 "parser.yy"
                             { yylhs.value.as < std::vector<pdm::ast::TPattern*> > () = std::move(yystack_[1].value.as < std::vector<pdm::ast::TPattern*> > ()); yylhs.value.as < std::vector<pdm::ast::TPattern*> > ().push_back(yystack_[0].value.as < pdm::ast::TPattern* > ()); }
#line 3315 "parser.tab.cc"
    break;


#line 3319 "parser.tab.cc"

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





  const short parser::yypact_ninf_ = -333;

  const signed char parser::yytable_ninf_ = -51;

  const short
  parser::yypact_[] =
  {
     193,    27,    29,    80,    92,   193,    46,  -333,  -333,  -333,
      53,  -333,    91,  -333,   107,  -333,    84,  -333,   159,   121,
     751,  -333,    80,    80,    29,    29,  -333,    62,   101,  -333,
    -333,  -333,  -333,  -333,  -333,  -333,  -333,  -333,   160,   -26,
     151,  -333,  -333,  -333,  -333,  -333,  -333,   644,   455,  -333,
    -333,  -333,  -333,   172,  -333,  -333,   195,  -333,  -333,  -333,
    -333,  -333,  -333,  -333,  -333,   191,  -333,  -333,  -333,   126,
    -333,  -333,  -333,  -333,  -333,   751,  -333,   196,   184,   187,
     192,   177,   199,   206,   201,   -25,    86,   194,  -333,   210,
    -333,   121,   253,    41,   208,  -333,   228,   230,    82,    18,
      18,    18,   751,   751,  -333,   234,  -333,  -333,  -333,  -333,
    -333,   217,   229,   502,  -333,     9,  -333,   240,   241,  -333,
    -333,    32,   537,   680,  -333,  -333,  -333,  -333,   751,  -333,
    -333,   751,  -333,  -333,  -333,  -333,   751,  -333,  -333,   751,
     751,   751,   751,     6,   255,   236,   -21,  -333,   -25,     8,
      29,  -333,   111,    29,  -333,  -333,   -26,    80,    80,  -333,
      73,  -333,   142,   -26,   715,  -333,   751,  -333,    80,    73,
    -333,  -333,   225,   226,   231,   232,  -333,  -333,   751,  -333,
    -333,   248,   244,    80,  -333,  -333,  -333,   252,  -333,  -333,
     751,   751,  -333,  -333,  -333,   173,   151,   573,   172,   257,
    -333,  -333,  -333,  -333,  -333,  -333,  -333,   251,  -333,  -333,
    -333,   114,  -333,   196,   184,   187,   192,   177,   199,  -333,
     247,    73,    73,  -333,   145,   255,    73,   -26,    65,  -333,
      73,    80,   255,  -333,  -333,  -333,   235,  -333,   256,     8,
    -333,    73,   292,    73,    73,  -333,    78,  -333,  -333,  -333,
    -333,  -333,  -333,   174,  -333,   751,   751,   751,   751,  -333,
    -333,  -333,   217,  -333,  -333,  -333,  -333,   609,  -333,    73,
     176,   179,  -333,   680,   680,  -333,  -333,  -333,  -333,   255,
    -333,   164,   245,  -333,    73,   -26,    73,  -333,    40,    29,
      76,  -333,   249,     7,  -333,  -333,  -333,    80,  -333,  -333,
    -333,  -333,  -333,   182,  -333,  -333,    90,  -333,    73,  -333,
     169,  -333,  -333,  -333,   -26,   246,  -333,  -333,    80,  -333,
    -333,  -333,  -333,   190,    47,  -333,  -333,   751,  -333,  -333,
    -333,  -333,  -333,  -333,   -26,  -333,    73,  -333,   261,   133,
    -333,  -333,  -333,    73,   262,    10,   269,    22,    73,  -333,
     271,  -333,  -333,  -333,  -333,    73,    25,  -333,  -333,  -333
  };

  const unsigned char
  parser::yydefact_[] =
  {
       0,     0,     0,     0,     0,     2,     0,     5,     6,     7,
       0,    49,     0,    50,     0,     1,     0,     3,     0,     0,
       0,     4,     0,     0,     0,     0,    26,     0,     0,    21,
      22,    23,    24,    27,    25,    28,    53,    52,     0,     0,
       0,   115,    82,    83,    51,    85,    84,     0,     0,   113,
     111,   112,   114,     0,    76,    78,     0,    48,    75,    64,
      65,    66,    67,    96,    77,    79,    80,    68,    81,   109,
      97,    98,    99,   100,   120,     0,    56,   124,   130,   134,
     136,   138,   140,   116,     0,     0,     0,     0,     8,     0,
       9,     0,     0,     0,     0,    69,    57,     0,     0,     0,
       0,     0,     0,     0,    70,     0,    11,    12,    13,    14,
      15,    76,     0,     0,   201,     0,    54,   106,     0,    87,
      86,     0,     0,     0,   110,   117,   118,   119,     0,   122,
     123,     0,   126,   127,   128,   129,     0,   132,   133,     0,
       0,     0,     0,     0,     0,     0,     0,   203,     0,     0,
       0,    35,     0,     0,    10,    47,     0,     0,     0,   192,
       0,   195,     0,     0,     0,    71,     0,    73,     0,   185,
     189,   190,     0,     0,     0,     0,    20,    93,     0,    90,
      91,     0,     0,     0,    74,    55,   104,     0,   108,   107,
       0,     0,   102,   175,   178,     0,     0,     0,   154,     0,
     172,   171,   164,   155,   156,   157,   158,   167,   165,   146,
     173,     0,   121,   125,   131,   135,   137,   139,   141,    45,
       0,     0,     0,   199,     0,     0,     0,     0,     0,   204,
       0,     0,     0,   168,    33,   169,    37,    38,    40,     0,
      36,     0,    88,     0,     0,   181,     0,   191,    95,    72,
      60,    61,   197,     0,   184,     0,     0,     0,     0,   180,
      94,    92,     0,   202,    58,   176,   177,     0,   103,     0,
       0,     0,   162,     0,     0,   101,    46,   187,   186,     0,
     193,     0,     0,    31,     0,     0,     0,   152,     0,     0,
       0,    34,     0,     0,   182,   183,   196,     0,   188,    16,
      17,    18,    19,     0,   179,   163,     0,   159,     0,   161,
       0,   174,   200,   194,     0,     0,    32,   151,     0,   170,
      39,    41,   147,     0,     0,    89,   198,     0,   105,   160,
     149,   150,   166,    29,     0,   153,     0,    42,     0,     0,
      59,    30,   148,     0,     0,     0,     0,     0,     0,    43,
       0,    62,   145,   143,   144,     0,     0,    63,   142,    44
  };

  const short
  parser::yypgoto_[] =
  {
    -333,  -333,  -333,   308,   125,  -333,   203,  -333,  -333,  -333,
    -333,  -333,   290,  -333,  -333,  -333,   166,  -333,    30,  -333,
    -333,   127,   140,    -2,     3,  -333,   233,    71,    14,  -333,
    -333,  -333,   -22,   -28,  -333,  -333,  -333,  -333,    34,   202,
    -333,  -333,  -333,  -333,  -333,  -333,  -333,  -333,  -333,  -333,
     -70,  -333,  -333,  -333,   189,  -333,   197,  -333,   198,  -333,
     188,   205,   200,  -333,  -332,  -333,   162,  -333,  -333,    11,
    -333,    61,  -333,  -333,  -333,  -333,  -333,  -333,  -142,    93,
    -333,    60,    63,    68,  -333,   155,    97,  -166,    69,  -333,
     163,   -82,  -144,  -333,  -333,   122,  -333,   -85
  };

  const short
  parser::yydefgoto_[] =
  {
      -1,     4,     5,     6,     7,    27,   105,   106,   107,   108,
     109,   110,    28,    29,    30,    31,   151,   236,   237,    32,
      33,     8,     9,   198,    54,    55,    38,    56,   200,    97,
     303,    98,   345,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,   113,    68,    69,    70,    71,    72,    73,
      74,    75,    76,   128,    77,   131,    78,   136,    79,   139,
      80,    81,    82,    83,   346,   355,   347,   323,   271,   287,
     288,   202,   203,   204,   205,   206,   207,   208,   209,   234,
     235,   210,   211,   194,   195,   114,   161,   170,   223,   171,
     172,    94,   147,   162,   253,   224,   115,   148
  };

  const short
  parser::yytable_[] =
  {
      12,   152,   252,   146,   229,   124,    14,   233,   229,    13,
      13,    92,    11,   350,    11,    39,    47,    93,    53,   144,
      48,    13,    86,    87,   350,    84,    85,   226,    40,    11,
     196,    10,   196,    11,    57,   186,   187,   227,   145,    42,
      43,    44,    45,    46,    13,    53,    53,   196,   183,    47,
     230,   111,   230,    48,   231,   219,   184,   349,   212,   118,
     168,    96,   112,   352,    42,    43,   228,   230,    22,     1,
     157,   158,   359,    53,    47,     2,     3,    11,    48,   318,
      11,    13,    23,    13,   159,    24,    17,   319,   353,   354,
      25,   144,    15,   188,    11,   196,   160,   233,   196,    18,
      53,    53,   169,   169,   169,   338,    19,   157,   158,    88,
     145,    53,   196,   284,   269,   230,   175,   176,   230,   321,
      53,   166,    20,   285,    21,   167,    53,   182,   242,    53,
     144,   326,   230,   329,    53,   248,   193,    53,    53,    53,
      53,    90,   221,    26,   149,    34,   220,   222,   238,   145,
     150,   241,    26,   274,    34,   144,    36,    37,    35,   275,
     243,   244,    53,   121,    53,    22,     1,    35,   122,   239,
     123,   169,     2,     3,   145,   150,    53,   144,   250,    23,
     251,   246,    24,    91,   279,   247,   262,    25,    53,    53,
     280,   344,   259,    93,   199,   229,   145,   272,   117,   283,
       1,   140,   118,   279,   265,   266,     2,     3,   274,   313,
     116,    96,   267,   297,   332,   306,   268,   298,   308,   307,
     232,   327,   309,   221,   141,   328,   119,   120,   222,   336,
     272,   232,   142,   337,   286,   118,   129,   130,   143,   339,
     232,   132,   133,   134,   135,   125,   126,   127,   153,   160,
     154,   137,   138,    53,    53,    53,    53,   316,    13,    11,
     117,    11,   156,   173,   174,    53,   163,   164,   199,   299,
     300,   301,   302,   165,   177,   178,   179,   221,   -50,   185,
     225,   193,   222,   255,   256,   201,   333,   238,   260,   257,
     258,   261,   232,   232,   264,   273,   276,   232,   290,   289,
     169,   232,   293,   314,   334,   324,   341,   343,   348,   351,
     232,   357,   232,    16,   232,   232,   181,    89,   240,   320,
     213,   286,   245,   189,   155,    53,   356,   325,   216,   335,
     305,   254,   291,   214,   311,   304,   310,   215,   263,     0,
     232,   340,   218,   296,   199,   199,   217,   281,   312,     0,
       0,     0,     0,     0,     0,   232,     0,   232,     0,   270,
       0,   232,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   232,     0,   232,
       0,     0,     0,   277,   278,     0,     0,     0,   282,     0,
       0,     0,   270,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   292,     0,   294,   295,   232,     0,     0,
       0,     0,     0,     0,   232,     0,   232,     0,     0,   232,
       0,     0,     0,     0,     0,     0,   232,   232,     0,     0,
       0,     0,     0,     0,     0,   201,   201,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   315,     0,   317,     0,
       0,     0,   322,     0,     0,     0,     0,     0,    13,    11,
       0,     0,     0,    39,     0,     0,     0,     0,   330,     0,
     331,    99,   100,   101,   102,     0,    40,     0,     0,     0,
       0,     0,    41,     0,     0,     0,   103,    42,    43,    44,
      45,    46,     0,     0,     0,     0,     0,    47,   342,     0,
       0,    48,   104,     0,    49,    13,    11,    50,    51,     0,
      39,     0,     0,     0,     0,     0,    52,   358,    99,   100,
     101,   102,     0,    40,     0,     0,     0,     0,     0,    41,
       0,     0,     0,   103,    42,    43,    44,    45,    46,     0,
      13,    11,     0,     0,    47,    39,     0,     0,    48,   180,
       0,    49,     0,     0,    50,    51,     0,     0,    40,     0,
       0,     0,     0,    52,    41,     0,   190,   191,     0,    42,
      43,    44,    45,    46,     0,     0,    13,    11,     0,    47,
     192,    39,     0,    48,     0,     0,    49,     0,     0,    50,
      51,     0,     0,     0,    40,   196,     0,     0,    52,     0,
      41,     0,     0,     0,     0,    42,    43,    44,    45,    46,
       0,     0,    13,    11,     0,   197,    95,    39,     0,    48,
       0,     0,    49,     0,     0,    50,    51,     0,     0,     0,
      40,     0,     0,     0,    52,     0,    41,     0,   190,   191,
       0,    42,    43,    44,    45,    46,     0,    13,    11,     0,
       0,    47,    39,     0,     0,    48,     0,     0,    49,     0,
       0,    50,    51,     0,     0,    40,     0,     0,     0,     0,
      52,    41,     0,     0,     0,     0,    42,    43,    44,    45,
      46,     0,     0,    13,    11,     0,    47,    95,    39,     0,
      48,     0,     0,    49,     0,     0,    50,    51,     0,     0,
       0,    40,   196,     0,     0,    52,     0,    41,     0,     0,
       0,     0,    42,    43,    44,    45,    46,     0,    13,    11,
       0,     0,   197,    39,     0,     0,    48,     0,     0,    49,
       0,     0,    50,    51,     0,     0,    40,     0,     0,     0,
       0,    52,    41,     0,     0,     0,     0,    42,    43,    44,
      45,    46,     0,     0,    13,    11,     0,    47,   249,    39,
       0,    48,     0,     0,    49,     0,     0,    50,    51,     0,
       0,     0,    40,     0,     0,     0,    52,     0,    41,     0,
       0,     0,     0,    42,    43,    44,    45,    46,     0,     0,
       0,     0,     0,    47,     0,     0,     0,    48,     0,     0,
      49,     0,     0,    50,    51,     0,     0,     0,     0,     0,
       0,     0,    52
  };

  const short
  parser::yycheck_[] =
  {
       2,    86,   168,    85,   148,    75,     3,   149,   152,     3,
       3,    39,     4,   345,     4,     8,    42,    42,    20,    44,
      46,     3,    24,    25,   356,    22,    23,    48,    21,     4,
      22,     4,    22,     4,    20,     3,     4,    58,    63,    32,
      33,    34,    35,    36,     3,    47,    48,    22,    39,    42,
      42,    48,    42,    46,    46,    49,    47,    47,   128,    56,
      42,    47,    48,    41,    32,    33,   148,    42,     6,     7,
      29,    30,    47,    75,    42,    13,    14,     4,    46,    39,
       4,     3,    20,     3,    43,    23,    40,    47,    66,    67,
      28,    44,     0,   121,     4,    22,    93,   239,    22,    46,
     102,   103,    99,   100,   101,    58,    15,    29,    30,    47,
      63,   113,    22,    48,   196,    42,   102,   103,    42,    43,
     122,    39,    15,    58,    40,    43,   128,   113,   156,   131,
      44,   297,    42,    43,   136,   163,   122,   139,   140,   141,
     142,    40,   144,    18,    58,    18,   143,   144,   150,    63,
      64,   153,    27,    39,    27,    44,    35,    36,    18,    45,
     157,   158,   164,    37,   166,     6,     7,    27,    42,    58,
      44,   168,    13,    14,    63,    64,   178,    44,   164,    20,
     166,    39,    23,    23,    39,    43,   183,    28,   190,   191,
      45,    58,   178,    42,   123,   339,    63,   199,     3,   227,
       7,    24,   199,    39,   190,   191,    13,    14,    39,    45,
      38,   197,    39,    39,    45,    39,    43,    43,    39,    43,
     149,    39,    43,   225,    25,    43,    35,    36,   225,    39,
     232,   160,    26,    43,   231,   232,    52,    53,    37,   324,
     169,    54,    55,    56,    57,    49,    50,    51,    54,   246,
      40,    59,    60,   255,   256,   257,   258,   285,     3,     4,
       3,     4,     9,   100,   101,   267,    58,    39,   197,   255,
     256,   257,   258,    43,    40,    58,    47,   279,    38,    38,
      44,   267,   279,    58,    58,   123,   314,   289,    40,    58,
      58,    47,   221,   222,    42,    44,    49,   226,    42,    64,
     297,   230,    10,    58,    58,    56,   334,    46,    46,    40,
     239,    40,   241,     5,   243,   244,   113,    27,   152,   289,
     131,   318,   160,   121,    91,   327,   348,   293,   140,   318,
     269,   169,   239,   136,   274,   267,   273,   139,   183,    -1,
     269,   327,   142,   246,   273,   274,   141,   225,   279,    -1,
      -1,    -1,    -1,    -1,    -1,   284,    -1,   286,    -1,   197,
      -1,   290,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   306,    -1,   308,
      -1,    -1,    -1,   221,   222,    -1,    -1,    -1,   226,    -1,
      -1,    -1,   230,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   241,    -1,   243,   244,   336,    -1,    -1,
      -1,    -1,    -1,    -1,   343,    -1,   345,    -1,    -1,   348,
      -1,    -1,    -1,    -1,    -1,    -1,   355,   356,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   273,   274,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   284,    -1,   286,    -1,
      -1,    -1,   290,    -1,    -1,    -1,    -1,    -1,     3,     4,
      -1,    -1,    -1,     8,    -1,    -1,    -1,    -1,   306,    -1,
     308,    16,    17,    18,    19,    -1,    21,    -1,    -1,    -1,
      -1,    -1,    27,    -1,    -1,    -1,    31,    32,    33,    34,
      35,    36,    -1,    -1,    -1,    -1,    -1,    42,   336,    -1,
      -1,    46,    47,    -1,    49,     3,     4,    52,    53,    -1,
       8,    -1,    -1,    -1,    -1,    -1,    61,   355,    16,    17,
      18,    19,    -1,    21,    -1,    -1,    -1,    -1,    -1,    27,
      -1,    -1,    -1,    31,    32,    33,    34,    35,    36,    -1,
       3,     4,    -1,    -1,    42,     8,    -1,    -1,    46,    47,
      -1,    49,    -1,    -1,    52,    53,    -1,    -1,    21,    -1,
      -1,    -1,    -1,    61,    27,    -1,    29,    30,    -1,    32,
      33,    34,    35,    36,    -1,    -1,     3,     4,    -1,    42,
      43,     8,    -1,    46,    -1,    -1,    49,    -1,    -1,    52,
      53,    -1,    -1,    -1,    21,    22,    -1,    -1,    61,    -1,
      27,    -1,    -1,    -1,    -1,    32,    33,    34,    35,    36,
      -1,    -1,     3,     4,    -1,    42,    43,     8,    -1,    46,
      -1,    -1,    49,    -1,    -1,    52,    53,    -1,    -1,    -1,
      21,    -1,    -1,    -1,    61,    -1,    27,    -1,    29,    30,
      -1,    32,    33,    34,    35,    36,    -1,     3,     4,    -1,
      -1,    42,     8,    -1,    -1,    46,    -1,    -1,    49,    -1,
      -1,    52,    53,    -1,    -1,    21,    -1,    -1,    -1,    -1,
      61,    27,    -1,    -1,    -1,    -1,    32,    33,    34,    35,
      36,    -1,    -1,     3,     4,    -1,    42,    43,     8,    -1,
      46,    -1,    -1,    49,    -1,    -1,    52,    53,    -1,    -1,
      -1,    21,    22,    -1,    -1,    61,    -1,    27,    -1,    -1,
      -1,    -1,    32,    33,    34,    35,    36,    -1,     3,     4,
      -1,    -1,    42,     8,    -1,    -1,    46,    -1,    -1,    49,
      -1,    -1,    52,    53,    -1,    -1,    21,    -1,    -1,    -1,
      -1,    61,    27,    -1,    -1,    -1,    -1,    32,    33,    34,
      35,    36,    -1,    -1,     3,     4,    -1,    42,    43,     8,
      -1,    46,    -1,    -1,    49,    -1,    -1,    52,    53,    -1,
      -1,    -1,    21,    -1,    -1,    -1,    61,    -1,    27,    -1,
      -1,    -1,    -1,    32,    33,    34,    35,    36,    -1,    -1,
      -1,    -1,    -1,    42,    -1,    -1,    -1,    46,    -1,    -1,
      49,    -1,    -1,    52,    53,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    61
  };

  const unsigned char
  parser::yystos_[] =
  {
       0,     7,    13,    14,    70,    71,    72,    73,    90,    91,
       4,     4,    92,     3,    93,     0,    72,    40,    46,    15,
      15,    40,     6,    20,    23,    28,    73,    74,    81,    82,
      83,    84,    88,    89,    90,    91,    35,    36,    95,     8,
      21,    27,    32,    33,    34,    35,    36,    42,    46,    49,
      52,    53,    61,    92,    93,    94,    96,    97,   102,   103,
     104,   105,   106,   107,   108,   109,   110,   111,   113,   114,
     115,   116,   117,   118,   119,   120,   121,   123,   125,   127,
     129,   130,   131,   132,    93,    93,    92,    92,    47,    81,
      40,    23,   102,    42,   160,    43,    97,    98,   100,    16,
      17,    18,    19,    31,    47,    75,    76,    77,    78,    79,
      80,    93,    97,   112,   154,   165,    38,     3,    93,    35,
      36,    37,    42,    44,   119,    49,    50,    51,   122,    52,
      53,   124,    54,    55,    56,    57,   126,    59,    60,   128,
      24,    25,    26,    37,    44,    63,   160,   161,   166,    58,
      64,    85,   166,    54,    40,    95,     9,    29,    30,    43,
      93,   155,   162,    58,    39,    43,    39,    43,    42,    93,
     156,   158,   159,   159,   159,    97,    97,    40,    58,    47,
      47,    75,    97,    39,    47,    38,     3,     4,   102,   108,
      29,    30,    43,    97,   152,   153,    22,    42,    92,    96,
      97,   135,   140,   141,   142,   143,   144,   145,   146,   147,
     150,   151,   119,   123,   125,   127,   129,   130,   131,    49,
      93,    92,    93,   157,   164,    44,    48,    58,   160,   161,
      42,    46,    96,   147,   148,   149,    86,    87,    92,    58,
      85,    92,   102,    93,    93,   135,    39,    43,   102,    43,
      97,    97,   156,   163,   135,    58,    58,    58,    58,    97,
      40,    47,    93,   154,    42,    97,    97,    39,    43,   160,
     135,   137,    92,    44,    39,    45,    49,   135,   135,    39,
      45,   164,   135,   102,    48,    58,    93,   138,   139,    64,
      42,   148,   135,    10,   135,   135,   155,    39,    43,    97,
      97,    97,    97,    99,   152,   140,    39,    43,    39,    43,
     151,   150,   157,    45,    58,   135,   102,   135,    39,    47,
      87,    43,   135,   136,    56,   107,   156,    39,    43,    43,
     135,   135,    45,   102,    58,   138,    39,    43,    58,   166,
      97,   102,   135,    46,    58,   101,   133,   135,    46,    47,
     133,    40,    41,    66,    67,   134,   101,    40,   135,    47
  };

  const unsigned char
  parser::yyr1_[] =
  {
       0,    69,    70,    71,    71,    72,    72,    72,    73,    74,
      74,    75,    75,    75,    75,    75,    76,    77,    78,    79,
      80,    81,    81,    81,    81,    81,    81,    81,    81,    82,
      82,    82,    82,    83,    83,    84,    84,    85,    86,    86,
      87,    87,    87,    88,    88,    89,    89,    90,    91,    92,
      93,    94,    95,    95,    96,    96,    97,    98,    99,    99,
     100,   100,   101,   101,   102,   102,   102,   102,   102,   103,
     103,   104,   105,   105,   106,   107,   107,   107,   107,   107,
     107,   107,   108,   108,   109,   109,   109,   109,   110,   110,
     111,   111,   111,   112,   112,   113,   114,   114,   114,   114,
     114,   115,   116,   116,   117,   117,   117,   118,   118,   119,
     119,   120,   120,   120,   120,   120,   121,   122,   122,   122,
     123,   123,   124,   124,   125,   125,   126,   126,   126,   126,
     127,   127,   128,   128,   129,   129,   130,   130,   131,   131,
     132,   132,   133,   134,   134,   134,   135,   136,   136,   137,
     137,   138,   139,   139,   140,   140,   140,   140,   140,   141,
     142,   142,   143,   144,   145,   145,   146,   147,   148,   148,
     149,   150,   150,   151,   151,   152,   152,   152,   153,   153,
     154,   155,   155,   155,   156,   156,   157,   157,   158,   159,
     159,   160,   160,   161,   161,   162,   162,   163,   163,   164,
     164,   165,   165,   166,   166
  };

  const signed char
  parser::yyr2_[] =
  {
       0,     2,     1,     2,     3,     1,     1,     1,     5,     2,
       3,     1,     1,     1,     1,     1,     4,     4,     4,     4,
       2,     1,     1,     1,     1,     1,     1,     1,     1,     7,
       8,     5,     6,     4,     5,     3,     4,     2,     1,     3,
       1,     3,     4,    10,    11,     4,     5,     6,     4,     1,
       1,     1,     1,     1,     2,     3,     1,     1,     0,     3,
       3,     3,     2,     3,     1,     1,     1,     1,     1,     2,
       2,     3,     4,     3,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     2,     2,     4,     6,
       3,     3,     4,     2,     3,     4,     1,     1,     1,     1,
       1,     4,     3,     4,     3,     6,     2,     3,     3,     1,
       2,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     3,     1,     1,     1,     3,     1,     1,     1,     1,
       1,     3,     1,     1,     1,     3,     1,     3,     1,     3,
       1,     3,     3,     1,     1,     1,     1,     1,     3,     3,
       3,     2,     1,     3,     1,     1,     1,     1,     1,     3,
       4,     3,     2,     3,     1,     1,     4,     1,     1,     1,
       3,     1,     1,     1,     3,     1,     2,     2,     1,     3,
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
  "mod_stmt", "moduleContent", "chain_prefix_stmt", "const_stmt",
  "val_stmt", "var_stmt", "set_stmt", "discard_stmt", "moduleContentStmt",
  "fn_stmt", "type_stmt", "enum_stmt", "enum_field_pl",
  "unprefixed_enum_field_pl", "enum_field", "typeclass_stmt", "using_stmt",
  "import_stmt", "extern_stmt", "tid", "vid", "floatl", "stringl",
  "mod_prefix", "expr", "long_exp", "expr_cl0", "expr_cl2",
  "type_query_exp_sl", "bracketed_exp", "unit_exp", "paren_exp",
  "vtupleExpr", "vstructExpr", "primary_exp", "int_expr", "stringls",
  "if_exp", "chain_exp", "chain_prefix", "lambda_exp", "postfix_exp",
  "tcall_exp", "vcall_exp", "dot_name_exp", "dot_index_exp", "unary_exp",
  "unary_op", "binary_exp", "mul_binary_op", "mul_binary_exp",
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
       0,   288,   288,   291,   292,   295,   296,   297,   305,   308,
     309,   317,   318,   319,   320,   321,   324,   327,   330,   333,
     336,   340,   341,   342,   343,   344,   345,   346,   347,   350,
     351,   352,   353,   356,   357,   360,   361,   364,   367,   368,
     371,   372,   373,   376,   379,   384,   385,   388,   391,   398,
     399,   401,   404,   405,   408,   409,   416,   419,   423,   424,
     427,   428,   431,   432,   436,   437,   438,   439,   440,   443,
     444,   447,   450,   451,   454,   457,   458,   459,   460,   461,
     462,   463,   466,   467,   470,   471,   472,   473,   476,   477,
     480,   481,   482,   485,   486,   489,   493,   494,   495,   496,
     497,   500,   503,   504,   507,   508,   509,   512,   513,   517,
     518,   521,   522,   523,   524,   525,   529,   532,   533,   534,
     537,   538,   541,   542,   545,   546,   549,   550,   551,   552,
     555,   556,   559,   560,   563,   564,   567,   568,   571,   572,
     575,   576,   580,   583,   584,   585,   593,   596,   597,   600,
     601,   605,   608,   609,   613,   614,   615,   616,   617,   620,
     623,   624,   627,   630,   634,   635,   638,   642,   646,   647,
     650,   653,   654,   657,   658,   660,   661,   662,   665,   666,
     674,   677,   678,   679,   682,   683,   686,   687,   691,   695,
     696,   699,   700,   703,   704,   708,   709,   712,   713,   716,
     717,   720,   721,   725,   726
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
#line 4048 "parser.tab.cc"

#line 729 "parser.yy"


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
