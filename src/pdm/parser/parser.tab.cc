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
#line 68 "parser.yy"

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

#line 22 "parser.yy"
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

      case symbol_kind::S_lpattern: // lpattern
      case symbol_kind::S_lpattern_naked: // lpattern_naked
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
      case symbol_kind::S_dot_typespec: // dot_typespec
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

      case symbol_kind::S_lpattern: // lpattern
      case symbol_kind::S_lpattern_naked: // lpattern_naked
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
      case symbol_kind::S_dot_typespec: // dot_typespec
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

      case symbol_kind::S_lpattern: // lpattern
      case symbol_kind::S_lpattern_naked: // lpattern_naked
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
      case symbol_kind::S_dot_typespec: // dot_typespec
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

      case symbol_kind::S_lpattern: // lpattern
      case symbol_kind::S_lpattern_naked: // lpattern_naked
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
      case symbol_kind::S_dot_typespec: // dot_typespec
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

      case symbol_kind::S_lpattern: // lpattern
      case symbol_kind::S_lpattern_naked: // lpattern_naked
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
      case symbol_kind::S_dot_typespec: // dot_typespec
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

      case symbol_kind::S_lpattern: // lpattern
      case symbol_kind::S_lpattern_naked: // lpattern_naked
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
      case symbol_kind::S_dot_typespec: // dot_typespec
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

      case symbol_kind::S_lpattern: // lpattern
      case symbol_kind::S_lpattern_naked: // lpattern_naked
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
      case symbol_kind::S_dot_typespec: // dot_typespec
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
#line 290 "parser.yy"
                    { yylhs.value.as < pdm::ast::Script* > () = mgr->new_script(source, yylhs.location, std::move(yystack_[0].value.as < std::vector<pdm::ast::Stmt*> > ())); *returnp = yylhs.value.as < pdm::ast::Script* > (); }
#line 2099 "parser.tab.cc"
    break;

  case 3: // scriptContent: scriptContentStmt ";"
#line 293 "parser.yy"
                                                    { yylhs.value.as < std::vector<pdm::ast::Stmt*> > ().push_back(yystack_[1].value.as < pdm::ast::Stmt* > ()); }
#line 2105 "parser.tab.cc"
    break;

  case 4: // scriptContent: scriptContent scriptContentStmt ";"
#line 294 "parser.yy"
                                                    { yylhs.value.as < std::vector<pdm::ast::Stmt*> > () = std::move(yystack_[2].value.as < std::vector<pdm::ast::Stmt*> > ()); yylhs.value.as < std::vector<pdm::ast::Stmt*> > ().push_back(yystack_[1].value.as < pdm::ast::Stmt* > ()); }
#line 2111 "parser.tab.cc"
    break;

  case 5: // scriptContentStmt: mod_stmt
#line 297 "parser.yy"
      { yylhs.value.as < pdm::ast::Stmt* > () = yystack_[0].value.as < pdm::ast::Stmt* > (); }
#line 2117 "parser.tab.cc"
    break;

  case 6: // scriptContentStmt: import_stmt
#line 298 "parser.yy"
      { yylhs.value.as < pdm::ast::Stmt* > () = yystack_[0].value.as < pdm::ast::Stmt* > (); }
#line 2123 "parser.tab.cc"
    break;

  case 7: // scriptContentStmt: extern_stmt
#line 299 "parser.yy"
      { yylhs.value.as < pdm::ast::Stmt* > () = yystack_[0].value.as < pdm::ast::Stmt* > (); }
#line 2129 "parser.tab.cc"
    break;

  case 8: // mod_stmt: "mod" "<val_id>" "{" moduleContent "}"
#line 307 "parser.yy"
                                                { yylhs.value.as < pdm::ast::Stmt* > () = mgr->new_mod_stmt(yylhs.location, yystack_[3].value.as < TokenInfo > ().ID_intstr, std::move(yystack_[1].value.as < std::vector<pdm::ast::Stmt*> > ())); }
#line 2135 "parser.tab.cc"
    break;

  case 9: // moduleContent: moduleContentStmt ";"
#line 310 "parser.yy"
                                                    { yylhs.value.as < std::vector<pdm::ast::Stmt*> > ().push_back(yystack_[1].value.as < pdm::ast::Stmt* > ()); }
#line 2141 "parser.tab.cc"
    break;

  case 10: // moduleContent: moduleContent moduleContentStmt ";"
#line 311 "parser.yy"
                                                    { yylhs.value.as < std::vector<pdm::ast::Stmt*> > () = std::move(yystack_[2].value.as < std::vector<pdm::ast::Stmt*> > ()); yylhs.value.as < std::vector<pdm::ast::Stmt*> > ().push_back(yystack_[1].value.as < pdm::ast::Stmt* > ()); }
#line 2147 "parser.tab.cc"
    break;

  case 11: // chain_prefix_stmt: const_stmt
#line 319 "parser.yy"
      { yylhs.value.as < pdm::ast::Stmt* > () = yystack_[0].value.as < pdm::ast::Stmt* > (); }
#line 2153 "parser.tab.cc"
    break;

  case 12: // chain_prefix_stmt: val_stmt
#line 320 "parser.yy"
      { yylhs.value.as < pdm::ast::Stmt* > () = yystack_[0].value.as < pdm::ast::Stmt* > (); }
#line 2159 "parser.tab.cc"
    break;

  case 13: // chain_prefix_stmt: var_stmt
#line 321 "parser.yy"
      { yylhs.value.as < pdm::ast::Stmt* > () = yystack_[0].value.as < pdm::ast::Stmt* > (); }
#line 2165 "parser.tab.cc"
    break;

  case 14: // chain_prefix_stmt: set_stmt
#line 322 "parser.yy"
      { yylhs.value.as < pdm::ast::Stmt* > () = yystack_[0].value.as < pdm::ast::Stmt* > (); }
#line 2171 "parser.tab.cc"
    break;

  case 15: // chain_prefix_stmt: discard_stmt
#line 323 "parser.yy"
      { yylhs.value.as < pdm::ast::Stmt* > () = yystack_[0].value.as < pdm::ast::Stmt* > (); }
#line 2177 "parser.tab.cc"
    break;

  case 16: // const_stmt: "const" lpattern_naked "=" expr
#line 326 "parser.yy"
                                        { yylhs.value.as < pdm::ast::Stmt* > () = mgr->new_const_stmt(yylhs.location, yystack_[2].value.as < pdm::ast::LPattern* > (), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2183 "parser.tab.cc"
    break;

  case 17: // val_stmt: "val" lpattern_naked "=" expr
#line 329 "parser.yy"
                                        { yylhs.value.as < pdm::ast::Stmt* > () = mgr->new_val_stmt(yylhs.location, yystack_[2].value.as < pdm::ast::LPattern* > (), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2189 "parser.tab.cc"
    break;

  case 18: // var_stmt: "var" lpattern_naked "=" expr
#line 332 "parser.yy"
                                        { yylhs.value.as < pdm::ast::Stmt* > () = mgr->new_var_stmt(yylhs.location, yystack_[2].value.as < pdm::ast::LPattern* > (), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2195 "parser.tab.cc"
    break;

  case 19: // set_stmt: "set" expr "=" expr
#line 335 "parser.yy"
                              { yylhs.value.as < pdm::ast::Stmt* > () = mgr->new_set_stmt(yylhs.location, yystack_[2].value.as < pdm::ast::Exp* > (), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2201 "parser.tab.cc"
    break;

  case 20: // discard_stmt: "discard" expr
#line 338 "parser.yy"
                        { yylhs.value.as < pdm::ast::Stmt* > () = mgr->new_discard_stmt(yylhs.location, yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2207 "parser.tab.cc"
    break;

  case 21: // moduleContentStmt: fn_stmt
#line 342 "parser.yy"
      { yylhs.value.as < pdm::ast::Stmt* > () = yystack_[0].value.as < pdm::ast::Stmt* > (); }
#line 2213 "parser.tab.cc"
    break;

  case 22: // moduleContentStmt: type_stmt
#line 343 "parser.yy"
      { yylhs.value.as < pdm::ast::Stmt* > () = yystack_[0].value.as < pdm::ast::Stmt* > (); }
#line 2219 "parser.tab.cc"
    break;

  case 23: // moduleContentStmt: enum_stmt
#line 344 "parser.yy"
      { yylhs.value.as < pdm::ast::Stmt* > () = yystack_[0].value.as < pdm::ast::Stmt* > (); }
#line 2225 "parser.tab.cc"
    break;

  case 24: // moduleContentStmt: typeclass_stmt
#line 345 "parser.yy"
      { yylhs.value.as < pdm::ast::Stmt* > () = yystack_[0].value.as < pdm::ast::Stmt* > (); }
#line 2231 "parser.tab.cc"
    break;

  case 25: // moduleContentStmt: import_stmt
#line 346 "parser.yy"
      { yylhs.value.as < pdm::ast::Stmt* > () = yystack_[0].value.as < pdm::ast::Stmt* > (); }
#line 2237 "parser.tab.cc"
    break;

  case 26: // moduleContentStmt: mod_stmt
#line 347 "parser.yy"
      { yylhs.value.as < pdm::ast::Stmt* > () = yystack_[0].value.as < pdm::ast::Stmt* > (); }
#line 2243 "parser.tab.cc"
    break;

  case 27: // moduleContentStmt: using_stmt
#line 348 "parser.yy"
      { yylhs.value.as < pdm::ast::Stmt* > () = yystack_[0].value.as < pdm::ast::Stmt* > (); }
#line 2249 "parser.tab.cc"
    break;

  case 28: // moduleContentStmt: extern_stmt
#line 349 "parser.yy"
      { yylhs.value.as < pdm::ast::Stmt* > () = yystack_[0].value.as < pdm::ast::Stmt* > (); }
#line 2255 "parser.tab.cc"
    break;

  case 29: // fn_stmt: "fn" vid vpattern "->" typespec "=" bracketed_exp
#line 352 "parser.yy"
                                                                          { yylhs.value.as < pdm::ast::Stmt* > () = mgr->new_fn_stmt(yylhs.location, yystack_[5].value.as < TokenInfo > ().ID_intstr, std::move(std::vector<ast::TPattern*>{}), yystack_[4].value.as < pdm::ast::VPattern* > (), yystack_[2].value.as < pdm::ast::Typespec* > (), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2261 "parser.tab.cc"
    break;

  case 30: // fn_stmt: "fn" vid tpattern_seq vpattern "->" typespec "=" bracketed_exp
#line 353 "parser.yy"
                                                                          { yylhs.value.as < pdm::ast::Stmt* > () = mgr->new_fn_stmt(yylhs.location, yystack_[6].value.as < TokenInfo > ().ID_intstr, std::move(yystack_[5].value.as < std::vector<pdm::ast::TPattern*> > ()), yystack_[4].value.as < pdm::ast::VPattern* > (), yystack_[2].value.as < pdm::ast::Typespec* > (), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2267 "parser.tab.cc"
    break;

  case 31: // fn_stmt: "fn" vid vpattern "=" bracketed_exp
#line 354 "parser.yy"
                                                                          { yylhs.value.as < pdm::ast::Stmt* > () = mgr->new_fn_stmt(yylhs.location, yystack_[3].value.as < TokenInfo > ().ID_intstr, std::move(std::vector<ast::TPattern*>{}), yystack_[2].value.as < pdm::ast::VPattern* > (), nullptr, yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2273 "parser.tab.cc"
    break;

  case 32: // fn_stmt: "fn" vid tpattern_seq vpattern "=" bracketed_exp
#line 355 "parser.yy"
                                                                          { yylhs.value.as < pdm::ast::Stmt* > () = mgr->new_fn_stmt(yylhs.location, yystack_[4].value.as < TokenInfo > ().ID_intstr, std::move(yystack_[3].value.as < std::vector<pdm::ast::TPattern*> > ()), yystack_[2].value.as < pdm::ast::VPattern* > (), nullptr, yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2279 "parser.tab.cc"
    break;

  case 33: // type_stmt: "type" tid "=" long_typespec
#line 358 "parser.yy"
                                                    { yylhs.value.as < pdm::ast::Stmt* > () = mgr->new_type_stmt(yylhs.location, yystack_[2].value.as < TokenInfo > ().ID_intstr, std::move(std::vector<ast::TPattern*>{}), yystack_[0].value.as < pdm::ast::Typespec* > ()); }
#line 2285 "parser.tab.cc"
    break;

  case 34: // type_stmt: "type" tid tpattern_seq "=" long_typespec
#line 359 "parser.yy"
                                                    { yylhs.value.as < pdm::ast::Stmt* > () = mgr->new_type_stmt(yylhs.location, yystack_[3].value.as < TokenInfo > ().ID_intstr, std::move(yystack_[2].value.as < std::vector<pdm::ast::TPattern*> > ()), yystack_[0].value.as < pdm::ast::Typespec* > ()); }
#line 2291 "parser.tab.cc"
    break;

  case 35: // enum_stmt: "type" tid enum_field_pl
#line 362 "parser.yy"
                                    { yylhs.value.as < pdm::ast::Stmt* > () = mgr->new_enum_stmt(yylhs.location, yystack_[1].value.as < TokenInfo > ().ID_intstr, std::move(yystack_[0].value.as < std::vector<pdm::ast::EnumStmt::Field*> > ())); }
#line 2297 "parser.tab.cc"
    break;

  case 36: // enum_field_pl: "|" unprefixed_enum_field_pl
#line 365 "parser.yy"
                                    { yylhs.value.as < std::vector<pdm::ast::EnumStmt::Field*> > () = std::move(yystack_[0].value.as < std::vector<pdm::ast::EnumStmt::Field*> > ()); }
#line 2303 "parser.tab.cc"
    break;

  case 37: // unprefixed_enum_field_pl: enum_field
#line 368 "parser.yy"
                                                { yylhs.value.as < std::vector<pdm::ast::EnumStmt::Field*> > ().push_back(yystack_[0].value.as < pdm::ast::EnumStmt::Field* > ()); }
#line 2309 "parser.tab.cc"
    break;

  case 38: // unprefixed_enum_field_pl: unprefixed_enum_field_pl "|" enum_field
#line 369 "parser.yy"
                                                { yylhs.value.as < std::vector<pdm::ast::EnumStmt::Field*> > () = std::move(yystack_[2].value.as < std::vector<pdm::ast::EnumStmt::Field*> > ()); yylhs.value.as < std::vector<pdm::ast::EnumStmt::Field*> > ().push_back(yystack_[0].value.as < pdm::ast::EnumStmt::Field* > ()); }
#line 2315 "parser.tab.cc"
    break;

  case 39: // enum_field: tid
#line 372 "parser.yy"
                                     { yylhs.value.as < pdm::ast::EnumStmt::Field* > () = mgr->new_enum_stmt_field(yylhs.location, yystack_[0].value.as < TokenInfo > ().ID_intstr, std::move(std::vector<ast::Typespec*>{}), false); }
#line 2321 "parser.tab.cc"
    break;

  case 40: // enum_field: tid "(" ")"
#line 373 "parser.yy"
                                     { yylhs.value.as < pdm::ast::EnumStmt::Field* > () = mgr->new_enum_stmt_field(yylhs.location, yystack_[2].value.as < TokenInfo > ().ID_intstr, std::move(std::vector<ast::Typespec*>{}), true); }
#line 2327 "parser.tab.cc"
    break;

  case 41: // enum_field: tid "(" typespec_cl1 ")"
#line 374 "parser.yy"
                                     { yylhs.value.as < pdm::ast::EnumStmt::Field* > () = mgr->new_enum_stmt_field(yylhs.location, yystack_[3].value.as < TokenInfo > ().ID_intstr, std::move(yystack_[1].value.as < std::vector<pdm::ast::Typespec*> > ()), true); }
#line 2333 "parser.tab.cc"
    break;

  case 42: // typeclass_stmt: "typeclass" tid "<" tid typespec ">" "=" "{" type_query_exp_sl "}"
#line 377 "parser.yy"
                                                                                                  { 
        yylhs.value.as < pdm::ast::Stmt* > () = mgr->new_typeclass_stmt(yylhs.location, yystack_[8].value.as < TokenInfo > ().ID_intstr, yystack_[6].value.as < TokenInfo > ().ID_intstr, yystack_[5].value.as < pdm::ast::Typespec* > (), std::move(std::vector<ast::TPattern*>{}), std::move(yystack_[1].value.as < std::vector<pdm::ast::TypeQueryExp*> > ())); 
      }
#line 2341 "parser.tab.cc"
    break;

  case 43: // typeclass_stmt: "typeclass" tid "<" tid typespec ">" tpattern_seq "=" "{" type_query_exp_sl "}"
#line 380 "parser.yy"
                                                                                                  { 
        yylhs.value.as < pdm::ast::Stmt* > () = mgr->new_typeclass_stmt(yylhs.location, yystack_[9].value.as < TokenInfo > ().ID_intstr, yystack_[7].value.as < TokenInfo > ().ID_intstr, yystack_[6].value.as < pdm::ast::Typespec* > (), std::move(yystack_[4].value.as < std::vector<pdm::ast::TPattern*> > ()), std::move(yystack_[1].value.as < std::vector<pdm::ast::TypeQueryExp*> > ())); 
      }
#line 2349 "parser.tab.cc"
    break;

  case 44: // using_stmt: "using" vid "." "*"
#line 385 "parser.yy"
                                        { yylhs.value.as < pdm::ast::Stmt* > () = mgr->new_using_stmt(yylhs.location, yystack_[2].value.as < TokenInfo > ().ID_intstr, ""); }
#line 2355 "parser.tab.cc"
    break;

  case 45: // using_stmt: "using" vid "." vid "*"
#line 386 "parser.yy"
                                        { yylhs.value.as < pdm::ast::Stmt* > () = mgr->new_using_stmt(yylhs.location, yystack_[3].value.as < TokenInfo > ().ID_intstr, yystack_[1].value.as < TokenInfo > ().ID_intstr.content()); }
#line 2361 "parser.tab.cc"
    break;

  case 46: // import_stmt: "import" vid "from" stringl "type" stringl
#line 389 "parser.yy"
                                                       { yylhs.value.as < pdm::ast::Stmt* > () = mgr->new_import_stmt(yylhs.location, yystack_[4].value.as < TokenInfo > ().ID_intstr, *yystack_[2].value.as < TokenInfo > ().String_utf8string, *yystack_[0].value.as < TokenInfo > ().String_utf8string); }
#line 2367 "parser.tab.cc"
    break;

  case 47: // extern_stmt: "extern" vid "from" expr
#line 392 "parser.yy"
                                    { yylhs.value.as < pdm::ast::Stmt* > () = mgr->new_extern_stmt(yylhs.location, yystack_[2].value.as < TokenInfo > ().ID_intstr, yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2373 "parser.tab.cc"
    break;

  case 48: // tid: "<TypeId>"
#line 399 "parser.yy"
     { yylhs.value.as < TokenInfo > () = yystack_[0].value.as < TokenInfo > (); }
#line 2379 "parser.tab.cc"
    break;

  case 49: // vid: "<val_id>"
#line 400 "parser.yy"
     { yylhs.value.as < TokenInfo > () = yystack_[0].value.as < TokenInfo > (); }
#line 2385 "parser.tab.cc"
    break;

  case 50: // floatl: "4.2"
#line 402 "parser.yy"
      { yylhs.value.as < TokenInfo > () = yystack_[0].value.as < TokenInfo > (); }
#line 2391 "parser.tab.cc"
    break;

  case 51: // stringl: "'sq-string-literal'"
#line 405 "parser.yy"
      { yylhs.value.as < TokenInfo > () = yystack_[0].value.as < TokenInfo > (); }
#line 2397 "parser.tab.cc"
    break;

  case 52: // stringl: "\"dq-string-literal\""
#line 406 "parser.yy"
      { yylhs.value.as < TokenInfo > () = yystack_[0].value.as < TokenInfo > (); }
#line 2403 "parser.tab.cc"
    break;

  case 53: // expr: binary_exp
#line 413 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2409 "parser.tab.cc"
    break;

  case 55: // long_exp: expr
#line 417 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2415 "parser.tab.cc"
    break;

  case 56: // expr_cl2: expr "," expr
#line 420 "parser.yy"
                             { yylhs.value.as < std::vector<pdm::ast::Exp*> > ().reserve(2); yylhs.value.as < std::vector<pdm::ast::Exp*> > ().push_back(yystack_[2].value.as < pdm::ast::Exp* > ()); yylhs.value.as < std::vector<pdm::ast::Exp*> > ().push_back(yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2421 "parser.tab.cc"
    break;

  case 57: // expr_cl2: expr_cl2 "," expr
#line 421 "parser.yy"
                             { yylhs.value.as < std::vector<pdm::ast::Exp*> > () = std::move(yystack_[2].value.as < std::vector<pdm::ast::Exp*> > ()); yylhs.value.as < std::vector<pdm::ast::Exp*> > ().push_back(yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2427 "parser.tab.cc"
    break;

  case 58: // type_query_exp_sl: type_query_exp ";"
#line 424 "parser.yy"
                                       { yylhs.value.as < std::vector<pdm::ast::TypeQueryExp*> > ().push_back(yystack_[1].value.as < pdm::ast::TypeQueryExp* > ()); }
#line 2433 "parser.tab.cc"
    break;

  case 59: // type_query_exp_sl: type_query_exp_sl type_query_exp ";"
#line 425 "parser.yy"
                                                 { yylhs.value.as < std::vector<pdm::ast::TypeQueryExp*> > () = std::move(yystack_[2].value.as < std::vector<pdm::ast::TypeQueryExp*> > ()); yylhs.value.as < std::vector<pdm::ast::TypeQueryExp*> > ().push_back(yystack_[1].value.as < pdm::ast::TypeQueryExp* > ()); }
#line 2439 "parser.tab.cc"
    break;

  case 60: // bracketed_exp: unit_exp
#line 429 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2445 "parser.tab.cc"
    break;

  case 61: // bracketed_exp: paren_exp
#line 430 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2451 "parser.tab.cc"
    break;

  case 62: // bracketed_exp: vtupleExpr
#line 431 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2457 "parser.tab.cc"
    break;

  case 63: // bracketed_exp: vstructExpr
#line 432 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2463 "parser.tab.cc"
    break;

  case 64: // bracketed_exp: chain_exp
#line 433 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2469 "parser.tab.cc"
    break;

  case 65: // unit_exp: "(" ")"
#line 436 "parser.yy"
                        { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_unit_exp(yylhs.location); }
#line 2475 "parser.tab.cc"
    break;

  case 66: // unit_exp: "{" "}"
#line 437 "parser.yy"
                        { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_unit_exp(yylhs.location); }
#line 2481 "parser.tab.cc"
    break;

  case 67: // paren_exp: "(" long_exp ")"
#line 440 "parser.yy"
                              { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_paren_exp(yylhs.location, yystack_[1].value.as < pdm::ast::Exp* > ()); }
#line 2487 "parser.tab.cc"
    break;

  case 68: // vtupleExpr: "(" expr "," ")"
#line 443 "parser.yy"
                                   { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_tuple_exp(yylhs.location, std::move(std::vector(1,yystack_[2].value.as < pdm::ast::Exp* > ()))); }
#line 2493 "parser.tab.cc"
    break;

  case 69: // vtupleExpr: "(" expr_cl2 ")"
#line 444 "parser.yy"
                                   { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_tuple_exp(yylhs.location, std::move(yystack_[1].value.as < std::vector<pdm::ast::Exp*> > ())); }
#line 2499 "parser.tab.cc"
    break;

  case 70: // vstructExpr: "{" struct_exp_field_cl "}"
#line 447 "parser.yy"
                                            { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_struct_exp(yylhs.location, std::move(yystack_[1].value.as < std::vector<pdm::ast::StructExp::Field*> > ())); }
#line 2505 "parser.tab.cc"
    break;

  case 71: // primary_exp: bracketed_exp
#line 450 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2511 "parser.tab.cc"
    break;

  case 72: // primary_exp: vid
#line 451 "parser.yy"
                     { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_id_exp(yylhs.location, yystack_[0].value.as < TokenInfo > ().ID_intstr); }
#line 2517 "parser.tab.cc"
    break;

  case 73: // primary_exp: int_expr
#line 452 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2523 "parser.tab.cc"
    break;

  case 74: // primary_exp: floatl
#line 453 "parser.yy"
                     { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_float_exp(yylhs.location, yystack_[0].value.as < TokenInfo > ().Float); }
#line 2529 "parser.tab.cc"
    break;

  case 75: // primary_exp: stringls
#line 454 "parser.yy"
                     { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_string_exp(yylhs.location, std::move(yystack_[0].value.as < std::vector<pdm::ast::StringExp::Piece> > ())); }
#line 2535 "parser.tab.cc"
    break;

  case 76: // primary_exp: if_exp
#line 455 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2541 "parser.tab.cc"
    break;

  case 77: // primary_exp: lambda_exp
#line 456 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2547 "parser.tab.cc"
    break;

  case 78: // int_expr: "42"
#line 459 "parser.yy"
                { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_int_exp(yylhs.location, yystack_[0].value.as < TokenInfo > ().Int, ast::IntExp::Base::Dec); }
#line 2553 "parser.tab.cc"
    break;

  case 79: // int_expr: "0x2a"
#line 460 "parser.yy"
                { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_int_exp(yylhs.location, yystack_[0].value.as < TokenInfo > ().Int, ast::IntExp::Base::Hex); }
#line 2559 "parser.tab.cc"
    break;

  case 80: // stringls: "'sq-string-literal'"
#line 463 "parser.yy"
                             { yylhs.value.as < std::vector<pdm::ast::StringExp::Piece> > ().emplace_back(yylhs.location, *yystack_[0].value.as < TokenInfo > ().String_utf8string, ast::StringExp::QuoteKind::SingleQuote); }
#line 2565 "parser.tab.cc"
    break;

  case 81: // stringls: "\"dq-string-literal\""
#line 464 "parser.yy"
                             { yylhs.value.as < std::vector<pdm::ast::StringExp::Piece> > ().emplace_back(yylhs.location, *yystack_[0].value.as < TokenInfo > ().String_utf8string, ast::StringExp::QuoteKind::DoubleQuote); }
#line 2571 "parser.tab.cc"
    break;

  case 82: // stringls: stringls "'sq-string-literal'"
#line 465 "parser.yy"
                             { yylhs.value.as < std::vector<pdm::ast::StringExp::Piece> > () = std::move(yystack_[1].value.as < std::vector<pdm::ast::StringExp::Piece> > ()); yylhs.value.as < std::vector<pdm::ast::StringExp::Piece> > ().emplace_back(yystack_[0].location, *yystack_[0].value.as < TokenInfo > ().String_utf8string, ast::StringExp::QuoteKind::SingleQuote); }
#line 2577 "parser.tab.cc"
    break;

  case 83: // stringls: stringls "\"dq-string-literal\""
#line 466 "parser.yy"
                             { yylhs.value.as < std::vector<pdm::ast::StringExp::Piece> > () = std::move(yystack_[1].value.as < std::vector<pdm::ast::StringExp::Piece> > ()); yylhs.value.as < std::vector<pdm::ast::StringExp::Piece> > ().emplace_back(yystack_[0].location, *yystack_[0].value.as < TokenInfo > ().String_utf8string, ast::StringExp::QuoteKind::DoubleQuote); }
#line 2583 "parser.tab.cc"
    break;

  case 84: // if_exp: "if" bracketed_exp "then" bracketed_exp
#line 469 "parser.yy"
                                                                        { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_if_exp(yylhs.location, yystack_[2].value.as < pdm::ast::Exp* > (), yystack_[0].value.as < pdm::ast::Exp* > (), nullptr); }
#line 2589 "parser.tab.cc"
    break;

  case 85: // if_exp: "if" bracketed_exp "then" bracketed_exp "else" primary_exp
#line 470 "parser.yy"
                                                                        { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_if_exp(yylhs.location, yystack_[4].value.as < pdm::ast::Exp* > (), yystack_[2].value.as < pdm::ast::Exp* > (), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2595 "parser.tab.cc"
    break;

  case 86: // chain_exp: "{" expr "}"
#line 473 "parser.yy"
                                          { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_chain_exp(yylhs.location, std::move(std::vector<ast::Stmt*>{}), yystack_[1].value.as < pdm::ast::Exp* > ()); }
#line 2601 "parser.tab.cc"
    break;

  case 87: // chain_exp: "{" chain_prefix "}"
#line 474 "parser.yy"
                                           { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_chain_exp(yylhs.location, std::move(yystack_[1].value.as < std::vector<pdm::ast::Stmt*> > ()), nullptr); }
#line 2607 "parser.tab.cc"
    break;

  case 88: // chain_exp: "{" chain_prefix expr "}"
#line 475 "parser.yy"
                                           { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_chain_exp(yylhs.location, std::move(yystack_[2].value.as < std::vector<pdm::ast::Stmt*> > ()), yystack_[1].value.as < pdm::ast::Exp* > ()); }
#line 2613 "parser.tab.cc"
    break;

  case 89: // chain_prefix: chain_prefix_stmt ";"
#line 478 "parser.yy"
                                               { yylhs.value.as < std::vector<pdm::ast::Stmt*> > ().push_back(yystack_[1].value.as < pdm::ast::Stmt* > ()); }
#line 2619 "parser.tab.cc"
    break;

  case 90: // chain_prefix: chain_prefix chain_prefix_stmt ";"
#line 479 "parser.yy"
                                                { yylhs.value.as < std::vector<pdm::ast::Stmt*> > () = std::move(yystack_[2].value.as < std::vector<pdm::ast::Stmt*> > ()); yylhs.value.as < std::vector<pdm::ast::Stmt*> > ().push_back(yystack_[1].value.as < pdm::ast::Stmt* > ()); }
#line 2625 "parser.tab.cc"
    break;

  case 91: // lambda_exp: "fn" vpattern "=" bracketed_exp
#line 482 "parser.yy"
                                          { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_lambda_exp(yylhs.location, yystack_[2].value.as < pdm::ast::VPattern* > (), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2631 "parser.tab.cc"
    break;

  case 92: // postfix_exp: primary_exp
#line 486 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2637 "parser.tab.cc"
    break;

  case 93: // postfix_exp: tcall_exp
#line 487 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2643 "parser.tab.cc"
    break;

  case 94: // postfix_exp: vcall_exp
#line 488 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2649 "parser.tab.cc"
    break;

  case 95: // postfix_exp: dot_name_exp
#line 489 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2655 "parser.tab.cc"
    break;

  case 96: // postfix_exp: dot_index_exp
#line 490 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2661 "parser.tab.cc"
    break;

  case 97: // tcall_exp: postfix_exp "[" targ_cl "]"
#line 493 "parser.yy"
                                         { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_tcall_exp(yylhs.location, yystack_[3].value.as < pdm::ast::Exp* > (), std::move(yystack_[1].value.as < std::vector<pdm::ast::TArg*> > ())); }
#line 2667 "parser.tab.cc"
    break;

  case 98: // vcall_exp: postfix_exp "(" ")"
#line 496 "parser.yy"
                                            { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_vcall_exp(yylhs.location, yystack_[2].value.as < pdm::ast::Exp* > (), std::move(std::vector<ast::VArg*>{})); }
#line 2673 "parser.tab.cc"
    break;

  case 99: // vcall_exp: postfix_exp "(" varg_cl ")"
#line 497 "parser.yy"
                                            { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_vcall_exp(yylhs.location, yystack_[3].value.as < pdm::ast::Exp* > (), std::move(yystack_[1].value.as < std::vector<pdm::ast::VArg*> > ())); }
#line 2679 "parser.tab.cc"
    break;

  case 100: // dot_name_exp: postfix_exp "." "<val_id>"
#line 500 "parser.yy"
                            { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_dot_name_exp(yylhs.location, yystack_[2].value.as < pdm::ast::Exp* > (), yystack_[0].value.as < TokenInfo > ().ID_intstr, ast::DotNameExp::RhsHint::LhsStruct); }
#line 2685 "parser.tab.cc"
    break;

  case 101: // dot_name_exp: postfix_exp "." "<TypeId>"
#line 501 "parser.yy"
                            { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_dot_name_exp(yylhs.location, yystack_[2].value.as < pdm::ast::Exp* > (), yystack_[0].value.as < TokenInfo > ().ID_intstr, ast::DotNameExp::RhsHint::LhsEnum); }
#line 2691 "parser.tab.cc"
    break;

  case 102: // dot_index_exp: postfix_exp "." int_expr
#line 504 "parser.yy"
                                    { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_dot_index_exp(yylhs.location, yystack_[2].value.as < pdm::ast::Exp* > (), yystack_[0].value.as < pdm::ast::Exp* > (), ast::DotIndexExp::RhsHint::LhsNotPtr); }
#line 2697 "parser.tab.cc"
    break;

  case 103: // dot_index_exp: postfix_exp "." bracketed_exp
#line 505 "parser.yy"
                                    { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_dot_index_exp(yylhs.location, yystack_[2].value.as < pdm::ast::Exp* > (), yystack_[0].value.as < pdm::ast::Exp* > (), ast::DotIndexExp::RhsHint::LhsNotPtr); }
#line 2703 "parser.tab.cc"
    break;

  case 104: // unary_exp: postfix_exp
#line 509 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2709 "parser.tab.cc"
    break;

  case 105: // unary_exp: unary_op unary_exp
#line 510 "parser.yy"
                             { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_unary_exp(yylhs.location, yystack_[1].value.as < pdm::ast::UnaryOperator > (), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2715 "parser.tab.cc"
    break;

  case 106: // unary_op: "+"
#line 513 "parser.yy"
                 { yylhs.value.as < pdm::ast::UnaryOperator > () = ast::UnaryOperator::Plus; }
#line 2721 "parser.tab.cc"
    break;

  case 107: // unary_op: "-"
#line 514 "parser.yy"
                 { yylhs.value.as < pdm::ast::UnaryOperator > () = ast::UnaryOperator::Minus; }
#line 2727 "parser.tab.cc"
    break;

  case 108: // unary_op: "*"
#line 515 "parser.yy"
                 { yylhs.value.as < pdm::ast::UnaryOperator > () = ast::UnaryOperator::DeRef; }
#line 2733 "parser.tab.cc"
    break;

  case 109: // unary_op: "^"
#line 516 "parser.yy"
                 { yylhs.value.as < pdm::ast::UnaryOperator > () = ast::UnaryOperator::GetRef; }
#line 2739 "parser.tab.cc"
    break;

  case 110: // unary_op: "not"
#line 517 "parser.yy"
                 { yylhs.value.as < pdm::ast::UnaryOperator > () = ast::UnaryOperator::Not; }
#line 2745 "parser.tab.cc"
    break;

  case 111: // binary_exp: or_binary_exp
#line 521 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2751 "parser.tab.cc"
    break;

  case 112: // mul_binary_op: "*"
#line 524 "parser.yy"
                 { yylhs.value.as < pdm::ast::BinaryOperator > () = ast::BinaryOperator::Mul; }
#line 2757 "parser.tab.cc"
    break;

  case 113: // mul_binary_op: "/"
#line 525 "parser.yy"
                 { yylhs.value.as < pdm::ast::BinaryOperator > () = ast::BinaryOperator::Div; }
#line 2763 "parser.tab.cc"
    break;

  case 114: // mul_binary_op: "%"
#line 526 "parser.yy"
                 { yylhs.value.as < pdm::ast::BinaryOperator > () = ast::BinaryOperator::Rem; }
#line 2769 "parser.tab.cc"
    break;

  case 115: // mul_binary_exp: unary_exp
#line 529 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2775 "parser.tab.cc"
    break;

  case 116: // mul_binary_exp: mul_binary_exp mul_binary_op unary_exp
#line 530 "parser.yy"
                                               { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_binary_exp(yylhs.location, yystack_[1].value.as < pdm::ast::BinaryOperator > (), yystack_[2].value.as < pdm::ast::Exp* > (), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2781 "parser.tab.cc"
    break;

  case 117: // add_binary_op: "+"
#line 533 "parser.yy"
             { yylhs.value.as < pdm::ast::BinaryOperator > () = ast::BinaryOperator::Add; }
#line 2787 "parser.tab.cc"
    break;

  case 118: // add_binary_op: "-"
#line 534 "parser.yy"
             { yylhs.value.as < pdm::ast::BinaryOperator > () = ast::BinaryOperator::Subtract; }
#line 2793 "parser.tab.cc"
    break;

  case 119: // add_binary_exp: mul_binary_exp
#line 537 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2799 "parser.tab.cc"
    break;

  case 120: // add_binary_exp: add_binary_exp add_binary_op mul_binary_exp
#line 538 "parser.yy"
                                                    { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_binary_exp(yylhs.location, yystack_[1].value.as < pdm::ast::BinaryOperator > (), yystack_[2].value.as < pdm::ast::Exp* > (), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2805 "parser.tab.cc"
    break;

  case 121: // cmp_binary_op: "<"
#line 541 "parser.yy"
                { yylhs.value.as < pdm::ast::BinaryOperator > () = ast::BinaryOperator::Less; }
#line 2811 "parser.tab.cc"
    break;

  case 122: // cmp_binary_op: "<="
#line 542 "parser.yy"
                { yylhs.value.as < pdm::ast::BinaryOperator > () = ast::BinaryOperator::LessOrEq; }
#line 2817 "parser.tab.cc"
    break;

  case 123: // cmp_binary_op: ">"
#line 543 "parser.yy"
                { yylhs.value.as < pdm::ast::BinaryOperator > () = ast::BinaryOperator::Greater; }
#line 2823 "parser.tab.cc"
    break;

  case 124: // cmp_binary_op: ">="
#line 544 "parser.yy"
                { yylhs.value.as < pdm::ast::BinaryOperator > () = ast::BinaryOperator::GreaterOrEq; }
#line 2829 "parser.tab.cc"
    break;

  case 125: // cmp_binary_exp: add_binary_exp
#line 547 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2835 "parser.tab.cc"
    break;

  case 126: // cmp_binary_exp: cmp_binary_exp cmp_binary_op add_binary_exp
#line 548 "parser.yy"
                                                    { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_binary_exp(yylhs.location, yystack_[1].value.as < pdm::ast::BinaryOperator > (), yystack_[2].value.as < pdm::ast::Exp* > (), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2841 "parser.tab.cc"
    break;

  case 127: // eq_binary_op: "=="
#line 551 "parser.yy"
                 { yylhs.value.as < pdm::ast::BinaryOperator > () = ast::BinaryOperator::Equals; }
#line 2847 "parser.tab.cc"
    break;

  case 128: // eq_binary_op: "!="
#line 552 "parser.yy"
                 { yylhs.value.as < pdm::ast::BinaryOperator > () = ast::BinaryOperator::NotEquals; }
#line 2853 "parser.tab.cc"
    break;

  case 129: // eq_binary_exp: cmp_binary_exp
#line 555 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2859 "parser.tab.cc"
    break;

  case 130: // eq_binary_exp: eq_binary_exp eq_binary_op cmp_binary_exp
#line 556 "parser.yy"
                                                { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_binary_exp(yylhs.location, yystack_[1].value.as < pdm::ast::BinaryOperator > (), yystack_[2].value.as < pdm::ast::Exp* > (), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2865 "parser.tab.cc"
    break;

  case 131: // and_binary_exp: eq_binary_exp
#line 559 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2871 "parser.tab.cc"
    break;

  case 132: // and_binary_exp: and_binary_exp "and" eq_binary_exp
#line 560 "parser.yy"
                                           { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_binary_exp(yylhs.location, ast::BinaryOperator::And, yystack_[2].value.as < pdm::ast::Exp* > (), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2877 "parser.tab.cc"
    break;

  case 133: // xor_binary_exp: and_binary_exp
#line 563 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2883 "parser.tab.cc"
    break;

  case 134: // xor_binary_exp: xor_binary_exp "xor" and_binary_exp
#line 564 "parser.yy"
                                           { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_binary_exp(yylhs.location, ast::BinaryOperator::XOr, yystack_[2].value.as < pdm::ast::Exp* > (), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2889 "parser.tab.cc"
    break;

  case 135: // or_binary_exp: xor_binary_exp
#line 567 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2895 "parser.tab.cc"
    break;

  case 136: // or_binary_exp: or_binary_exp "or" xor_binary_exp
#line 568 "parser.yy"
                                           { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_binary_exp(yylhs.location, ast::BinaryOperator::Or, yystack_[2].value.as < pdm::ast::Exp* > (), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2901 "parser.tab.cc"
    break;

  case 137: // type_query_exp: typespec type_query_op typespec
#line 572 "parser.yy"
                                        { yylhs.value.as < pdm::ast::TypeQueryExp* > () = mgr->new_type_query_exp(yylhs.location, yystack_[1].value.as < pdm::ast::TypeQueryKind > (), yystack_[2].value.as < pdm::ast::Typespec* > (), yystack_[0].value.as < pdm::ast::Typespec* > ()); }
#line 2907 "parser.tab.cc"
    break;

  case 138: // type_query_op: ":<"
#line 575 "parser.yy"
                    { yylhs.value.as < pdm::ast::TypeQueryKind > () = ast::TypeQueryKind::LhsSubtypesRhs; }
#line 2913 "parser.tab.cc"
    break;

  case 139: // type_query_op: ">:"
#line 576 "parser.yy"
                    { yylhs.value.as < pdm::ast::TypeQueryKind > () = ast::TypeQueryKind::LhsSupertypesRhs; }
#line 2919 "parser.tab.cc"
    break;

  case 140: // type_query_op: "::"
#line 577 "parser.yy"
                    { yylhs.value.as < pdm::ast::TypeQueryKind > () = ast::TypeQueryKind::LhsEqualsRhs; }
#line 2925 "parser.tab.cc"
    break;

  case 141: // typespec: unary_typespec
#line 585 "parser.yy"
      { yylhs.value.as < pdm::ast::Typespec* > () = yystack_[0].value.as < pdm::ast::Typespec* > (); }
#line 2931 "parser.tab.cc"
    break;

  case 142: // typespec_cl1: typespec
#line 588 "parser.yy"
                                  { yylhs.value.as < std::vector<pdm::ast::Typespec*> > ().push_back(yystack_[0].value.as < pdm::ast::Typespec* > ()); }
#line 2937 "parser.tab.cc"
    break;

  case 143: // typespec_cl1: typespec_cl1 "," typespec
#line 589 "parser.yy"
                                  { yylhs.value.as < std::vector<pdm::ast::Typespec*> > () = std::move(yystack_[2].value.as < std::vector<pdm::ast::Typespec*> > ()); yylhs.value.as < std::vector<pdm::ast::Typespec*> > ().push_back(yystack_[0].value.as < pdm::ast::Typespec* > ()); }
#line 2943 "parser.tab.cc"
    break;

  case 144: // typespec_cl2: typespec "," typespec
#line 592 "parser.yy"
                                  { yylhs.value.as < std::vector<pdm::ast::Typespec*> > ().reserve(2); yylhs.value.as < std::vector<pdm::ast::Typespec*> > ().push_back(yystack_[2].value.as < pdm::ast::Typespec* > ()); yylhs.value.as < std::vector<pdm::ast::Typespec*> > ().push_back(yystack_[0].value.as < pdm::ast::Typespec* > ()); }
#line 2949 "parser.tab.cc"
    break;

  case 145: // typespec_cl2: typespec_cl2 "," typespec
#line 593 "parser.yy"
                                  { yylhs.value.as < std::vector<pdm::ast::Typespec*> > () = std::move(yystack_[2].value.as < std::vector<pdm::ast::Typespec*> > ()); yylhs.value.as < std::vector<pdm::ast::Typespec*> > ().push_back(yystack_[0].value.as < pdm::ast::Typespec* > ()); }
#line 2955 "parser.tab.cc"
    break;

  case 146: // struct_typespec_field: vid typespec
#line 597 "parser.yy"
                                  { yylhs.value.as < pdm::ast::StructTypespec::Field* > () = mgr->new_struct_typespec_field(yylhs.location, yystack_[1].value.as < TokenInfo > ().ID_intstr, yystack_[0].value.as < pdm::ast::Typespec* > ()); }
#line 2961 "parser.tab.cc"
    break;

  case 147: // struct_typespec_field_cl: struct_typespec_field
#line 600 "parser.yy"
                                                          { yylhs.value.as < std::vector<pdm::ast::StructTypespec::Field*> > ().push_back(yystack_[0].value.as < pdm::ast::StructTypespec::Field* > ()); }
#line 2967 "parser.tab.cc"
    break;

  case 148: // struct_typespec_field_cl: struct_typespec_field_cl "," struct_typespec_field
#line 601 "parser.yy"
                                                            { yylhs.value.as < std::vector<pdm::ast::StructTypespec::Field*> > () = std::move(yystack_[2].value.as < std::vector<pdm::ast::StructTypespec::Field*> > ()); yylhs.value.as < std::vector<pdm::ast::StructTypespec::Field*> > ().push_back(yystack_[0].value.as < pdm::ast::StructTypespec::Field* > ()); }
#line 2973 "parser.tab.cc"
    break;

  case 149: // primary_typespec: tid
#line 605 "parser.yy"
                        { yylhs.value.as < pdm::ast::Typespec* > () = mgr->new_id_typespec(yylhs.location, yystack_[0].value.as < TokenInfo > ().ID_intstr); }
#line 2979 "parser.tab.cc"
    break;

  case 150: // primary_typespec: paren_typespec
#line 606 "parser.yy"
      { yylhs.value.as < pdm::ast::Typespec* > () = yystack_[0].value.as < pdm::ast::Typespec* > (); }
#line 2985 "parser.tab.cc"
    break;

  case 151: // primary_typespec: tuple_typespec
#line 607 "parser.yy"
      { yylhs.value.as < pdm::ast::Typespec* > () = yystack_[0].value.as < pdm::ast::Typespec* > (); }
#line 2991 "parser.tab.cc"
    break;

  case 152: // primary_typespec: mod_prefix_tid
#line 608 "parser.yy"
      { yylhs.value.as < pdm::ast::Typespec* > () = yystack_[0].value.as < pdm::ast::Typespec* > (); }
#line 2997 "parser.tab.cc"
    break;

  case 153: // primary_typespec: fn_typespec
#line 609 "parser.yy"
      { yylhs.value.as < pdm::ast::Typespec* > () = yystack_[0].value.as < pdm::ast::Typespec* > (); }
#line 3003 "parser.tab.cc"
    break;

  case 154: // paren_typespec: "(" typespec ")"
#line 612 "parser.yy"
                                { yylhs.value.as < pdm::ast::Typespec* > () = mgr->new_paren_typespec(yylhs.location, yystack_[1].value.as < pdm::ast::Typespec* > ()); }
#line 3009 "parser.tab.cc"
    break;

  case 155: // tuple_typespec: "(" typespec "," ")"
#line 615 "parser.yy"
                                    { yylhs.value.as < pdm::ast::Typespec* > () = mgr->new_tuple_typespec(yylhs.location, std::move(std::vector(1,yystack_[2].value.as < pdm::ast::Typespec* > ()))); }
#line 3015 "parser.tab.cc"
    break;

  case 156: // tuple_typespec: "(" typespec_cl2 ")"
#line 616 "parser.yy"
                                    { yylhs.value.as < pdm::ast::Typespec* > () = mgr->new_tuple_typespec(yylhs.location, std::move(yystack_[1].value.as < std::vector<pdm::ast::Typespec*> > ())); }
#line 3021 "parser.tab.cc"
    break;

  case 157: // mod_prefix_tid: mod_prefix tid
#line 619 "parser.yy"
                            { yylhs.value.as < pdm::ast::Typespec* > () = mgr->new_dot_name_typespec_with_mod_prefix(yylhs.location, std::move(yystack_[1].value.as < std::vector<pdm::intern::String> > ()), yystack_[0].value.as < TokenInfo > ().ID_intstr); }
#line 3027 "parser.tab.cc"
    break;

  case 158: // mod_prefix: vid "."
#line 622 "parser.yy"
                            { yylhs.value.as < std::vector<pdm::intern::String> > ().push_back(yystack_[1].value.as < TokenInfo > ().ID_intstr); }
#line 3033 "parser.tab.cc"
    break;

  case 159: // mod_prefix: mod_prefix vid "."
#line 623 "parser.yy"
                            { yylhs.value.as < std::vector<pdm::intern::String> > () = std::move(yystack_[2].value.as < std::vector<pdm::intern::String> > ()); }
#line 3039 "parser.tab.cc"
    break;

  case 160: // fn_typespec: "Fn" vpattern primary_typespec
#line 626 "parser.yy"
                                       { yylhs.value.as < pdm::ast::Typespec* > () = mgr->new_fn_typespec(yylhs.location, std::move(yystack_[1].value.as < pdm::ast::VPattern* > ()), yystack_[0].value.as < pdm::ast::Typespec* > ()); }
#line 3045 "parser.tab.cc"
    break;

  case 161: // postfix_typespec: primary_typespec
#line 630 "parser.yy"
      { yylhs.value.as < pdm::ast::Typespec* > () = yystack_[0].value.as < pdm::ast::Typespec* > (); }
#line 3051 "parser.tab.cc"
    break;

  case 162: // postfix_typespec: tcall_typespec
#line 631 "parser.yy"
      { yylhs.value.as < pdm::ast::Typespec* > () = yystack_[0].value.as < pdm::ast::Typespec* > (); }
#line 3057 "parser.tab.cc"
    break;

  case 163: // postfix_typespec: dot_typespec
#line 632 "parser.yy"
      { yylhs.value.as < pdm::ast::Typespec* > () = yystack_[0].value.as < pdm::ast::Typespec* > (); }
#line 3063 "parser.tab.cc"
    break;

  case 164: // tcall_typespec: postfix_typespec "[" targ_cl "]"
#line 635 "parser.yy"
                                              { yylhs.value.as < pdm::ast::Typespec* > () = mgr->new_tcall_typespec(yylhs.location, yystack_[3].value.as < pdm::ast::Typespec* > (), std::move(yystack_[1].value.as < std::vector<pdm::ast::TArg*> > ())); }
#line 3069 "parser.tab.cc"
    break;

  case 165: // dot_typespec: postfix_typespec "." "<val_id>"
#line 637 "parser.yy"
                                         { yylhs.value.as < pdm::ast::Typespec* > () = mgr->new_dot_name_typespec_with_type_prefix(yylhs.location, yystack_[2].value.as < pdm::ast::Typespec* > (), yystack_[0].value.as < TokenInfo > ().ID_intstr); }
#line 3075 "parser.tab.cc"
    break;

  case 166: // unary_typespec: postfix_typespec
#line 641 "parser.yy"
      { yylhs.value.as < pdm::ast::Typespec* > () = yystack_[0].value.as < pdm::ast::Typespec* > (); }
#line 3081 "parser.tab.cc"
    break;

  case 167: // long_typespec: unary_typespec
#line 645 "parser.yy"
      { yylhs.value.as < pdm::ast::Typespec* > () = yystack_[0].value.as < pdm::ast::Typespec* > (); }
#line 3087 "parser.tab.cc"
    break;

  case 168: // long_typespec: struct_typespec
#line 646 "parser.yy"
      { yylhs.value.as < pdm::ast::Typespec* > () = yystack_[0].value.as < pdm::ast::Typespec* > (); }
#line 3093 "parser.tab.cc"
    break;

  case 169: // struct_typespec: "{" struct_typespec_field_cl "}"
#line 649 "parser.yy"
                                              { yylhs.value.as < pdm::ast::Typespec* > () = mgr->new_struct_typespec(yylhs.location, std::move(yystack_[1].value.as < std::vector<pdm::ast::StructTypespec::Field*> > ())); }
#line 3099 "parser.tab.cc"
    break;

  case 170: // targ: typespec
#line 652 "parser.yy"
               { yylhs.value.as < pdm::ast::TArg* > () = mgr->new_targ_typespec(yylhs.location, yystack_[0].value.as < pdm::ast::Typespec* > ()); }
#line 3105 "parser.tab.cc"
    break;

  case 171: // targ: expr
#line 653 "parser.yy"
               { yylhs.value.as < pdm::ast::TArg* > () = mgr->new_targ_exp(yylhs.location, yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 3111 "parser.tab.cc"
    break;

  case 172: // targ_cl: targ
#line 656 "parser.yy"
                            { yylhs.value.as < std::vector<pdm::ast::TArg*> > ().push_back(yystack_[0].value.as < pdm::ast::TArg* > ()); }
#line 3117 "parser.tab.cc"
    break;

  case 173: // targ_cl: targ_cl "," targ
#line 657 "parser.yy"
                            { yylhs.value.as < std::vector<pdm::ast::TArg*> > () = std::move(yystack_[2].value.as < std::vector<pdm::ast::TArg*> > ()); yylhs.value.as < std::vector<pdm::ast::TArg*> > ().push_back(yystack_[0].value.as < pdm::ast::TArg* > ()); }
#line 3123 "parser.tab.cc"
    break;

  case 174: // varg: expr
#line 659 "parser.yy"
                            { yylhs.value.as < pdm::ast::VArg* > () = mgr->new_varg(yylhs.location, yystack_[0].value.as < pdm::ast::Exp* > (), ast::VArgKind::In); }
#line 3129 "parser.tab.cc"
    break;

  case 175: // varg: "out" expr
#line 660 "parser.yy"
                            { yylhs.value.as < pdm::ast::VArg* > () = mgr->new_varg(yylhs.location, yystack_[0].value.as < pdm::ast::Exp* > (), ast::VArgKind::Out); }
#line 3135 "parser.tab.cc"
    break;

  case 176: // varg: "inout" expr
#line 661 "parser.yy"
                            { yylhs.value.as < pdm::ast::VArg* > () = mgr->new_varg(yylhs.location, yystack_[0].value.as < pdm::ast::Exp* > (), ast::VArgKind::InOut); }
#line 3141 "parser.tab.cc"
    break;

  case 177: // varg_cl: varg
#line 664 "parser.yy"
                            { yylhs.value.as < std::vector<pdm::ast::VArg*> > ().push_back(yystack_[0].value.as < pdm::ast::VArg* > ()); }
#line 3147 "parser.tab.cc"
    break;

  case 178: // varg_cl: varg_cl "," varg
#line 665 "parser.yy"
                            { yylhs.value.as < std::vector<pdm::ast::VArg*> > () = std::move(yystack_[2].value.as < std::vector<pdm::ast::VArg*> > ()); yylhs.value.as < std::vector<pdm::ast::VArg*> > ().push_back(yystack_[0].value.as < pdm::ast::VArg* > ()); }
#line 3153 "parser.tab.cc"
    break;

  case 179: // struct_exp_field: vid "=" expr
#line 673 "parser.yy"
                    { yylhs.value.as < pdm::ast::StructExp::Field* > () = mgr->new_struct_exp_field(yylhs.location, yystack_[2].value.as < TokenInfo > ().ID_intstr, yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 3159 "parser.tab.cc"
    break;

  case 180: // vpattern_field: vid typespec
#line 676 "parser.yy"
                            { yylhs.value.as < pdm::ast::VPattern::Field* > () = mgr->new_vpattern_field(yylhs.location, yystack_[1].value.as < TokenInfo > ().ID_intstr, yystack_[0].value.as < pdm::ast::Typespec* > (), ast::VArgKind::In); }
#line 3165 "parser.tab.cc"
    break;

  case 181: // vpattern_field: "out" vid typespec
#line 677 "parser.yy"
                            { yylhs.value.as < pdm::ast::VPattern::Field* > () = mgr->new_vpattern_field(yylhs.location, yystack_[1].value.as < TokenInfo > ().ID_intstr, yystack_[0].value.as < pdm::ast::Typespec* > (), ast::VArgKind::Out); }
#line 3171 "parser.tab.cc"
    break;

  case 182: // vpattern_field: "inout" vid typespec
#line 678 "parser.yy"
                            { yylhs.value.as < pdm::ast::VPattern::Field* > () = mgr->new_vpattern_field(yylhs.location, yystack_[1].value.as < TokenInfo > ().ID_intstr, yystack_[0].value.as < pdm::ast::Typespec* > (), ast::VArgKind::InOut); }
#line 3177 "parser.tab.cc"
    break;

  case 183: // lpattern_field: vid typespec
#line 681 "parser.yy"
                    { yylhs.value.as < pdm::ast::LPattern::Field* > () = mgr->new_lpattern_field(yylhs.location, ast::LPattern::FieldKind::IdTypespecPair, yystack_[1].value.as < TokenInfo > ().ID_intstr, yystack_[0].value.as < pdm::ast::Typespec* > ()); }
#line 3183 "parser.tab.cc"
    break;

  case 184: // lpattern_field: vid
#line 682 "parser.yy"
                    { yylhs.value.as < pdm::ast::LPattern::Field* > () = mgr->new_lpattern_field(yylhs.location, ast::LPattern::FieldKind::IdSingleton, yystack_[0].value.as < TokenInfo > ().ID_intstr); }
#line 3189 "parser.tab.cc"
    break;

  case 185: // tpattern_field: vid typespec
#line 685 "parser.yy"
                    { yylhs.value.as < pdm::ast::TPattern::Field* > () = mgr->new_tpattern_field(yylhs.location, ast::TPattern::FieldKind::Value, yystack_[1].value.as < TokenInfo > ().ID_intstr, yystack_[0].value.as < pdm::ast::Typespec* > ()); }
#line 3195 "parser.tab.cc"
    break;

  case 186: // tpattern_field: tid typespec
#line 686 "parser.yy"
                    { yylhs.value.as < pdm::ast::TPattern::Field* > () = mgr->new_tpattern_field(yylhs.location, ast::TPattern::FieldKind::Type, yystack_[1].value.as < TokenInfo > ().ID_intstr, yystack_[0].value.as < pdm::ast::Typespec* > ()); }
#line 3201 "parser.tab.cc"
    break;

  case 187: // lpattern: "(" lpattern_field_cl ")"
#line 690 "parser.yy"
                                       { yylhs.value.as < pdm::ast::LPattern* > () = mgr->new_lpattern(yylhs.location, std::move(yystack_[1].value.as < std::vector<pdm::ast::LPattern::Field*> > ())); }
#line 3207 "parser.tab.cc"
    break;

  case 188: // lpattern: "(" ")"
#line 691 "parser.yy"
                                       { yylhs.value.as < pdm::ast::LPattern* > () = mgr->new_lpattern(yylhs.location, std::move(std::vector<ast::LPattern::Field*>{})); }
#line 3213 "parser.tab.cc"
    break;

  case 189: // lpattern_naked: lpattern_field
#line 694 "parser.yy"
                                       { yylhs.value.as < pdm::ast::LPattern* > () = mgr->new_lpattern(yylhs.location, std::move(std::vector<ast::LPattern::Field*>{1,yystack_[0].value.as < pdm::ast::LPattern::Field* > ()})); }
#line 3219 "parser.tab.cc"
    break;

  case 190: // lpattern_naked: lpattern
#line 695 "parser.yy"
      { yylhs.value.as < pdm::ast::LPattern* > () = yystack_[0].value.as < pdm::ast::LPattern* > (); }
#line 3225 "parser.tab.cc"
    break;

  case 191: // vpattern: "(" vpattern_field_cl ")"
#line 698 "parser.yy"
                                       { yylhs.value.as < pdm::ast::VPattern* > () = mgr->new_vpattern(yylhs.location, std::move(yystack_[1].value.as < std::vector<pdm::ast::VPattern::Field*> > ())); }
#line 3231 "parser.tab.cc"
    break;

  case 192: // vpattern: "(" ")"
#line 699 "parser.yy"
                                      { yylhs.value.as < pdm::ast::VPattern* > () = mgr->new_vpattern(yylhs.location, std::move(std::vector<ast::VPattern::Field*>{})); }
#line 3237 "parser.tab.cc"
    break;

  case 193: // tpattern: "[" tpattern_field_cl "]"
#line 702 "parser.yy"
                                               { yylhs.value.as < pdm::ast::TPattern* > () = mgr->new_tpattern(yylhs.location, std::move(yystack_[1].value.as < std::vector<pdm::ast::TPattern::Field*> > ()), false); }
#line 3243 "parser.tab.cc"
    break;

  case 194: // tpattern: "!" "[" tpattern_field_cl "]"
#line 703 "parser.yy"
                                               { yylhs.value.as < pdm::ast::TPattern* > () = mgr->new_tpattern(yylhs.location, std::move(yystack_[1].value.as < std::vector<pdm::ast::TPattern::Field*> > ()), true); }
#line 3249 "parser.tab.cc"
    break;

  case 195: // vpattern_field_cl: vpattern_field
#line 707 "parser.yy"
                                              { yylhs.value.as < std::vector<pdm::ast::VPattern::Field*> > ().push_back(yystack_[0].value.as < pdm::ast::VPattern::Field* > ()); }
#line 3255 "parser.tab.cc"
    break;

  case 196: // vpattern_field_cl: vpattern_field_cl "," vpattern_field
#line 708 "parser.yy"
                                               { yylhs.value.as < std::vector<pdm::ast::VPattern::Field*> > () = std::move(yystack_[2].value.as < std::vector<pdm::ast::VPattern::Field*> > ()); yylhs.value.as < std::vector<pdm::ast::VPattern::Field*> > ().push_back(yystack_[0].value.as < pdm::ast::VPattern::Field* > ()); }
#line 3261 "parser.tab.cc"
    break;

  case 197: // lpattern_field_cl: lpattern_field
#line 711 "parser.yy"
                                              { yylhs.value.as < std::vector<pdm::ast::LPattern::Field*> > ().push_back(yystack_[0].value.as < pdm::ast::LPattern::Field* > ()); }
#line 3267 "parser.tab.cc"
    break;

  case 198: // lpattern_field_cl: lpattern_field_cl "," lpattern_field
#line 712 "parser.yy"
                                               { yylhs.value.as < std::vector<pdm::ast::LPattern::Field*> > () = std::move(yystack_[2].value.as < std::vector<pdm::ast::LPattern::Field*> > ()); yylhs.value.as < std::vector<pdm::ast::LPattern::Field*> > ().push_back(yystack_[0].value.as < pdm::ast::LPattern::Field* > ()); }
#line 3273 "parser.tab.cc"
    break;

  case 199: // tpattern_field_cl: tpattern_field
#line 715 "parser.yy"
                                              { yylhs.value.as < std::vector<pdm::ast::TPattern::Field*> > ().push_back(yystack_[0].value.as < pdm::ast::TPattern::Field* > ()); }
#line 3279 "parser.tab.cc"
    break;

  case 200: // tpattern_field_cl: tpattern_field_cl "," tpattern_field
#line 716 "parser.yy"
                                               { yylhs.value.as < std::vector<pdm::ast::TPattern::Field*> > () = std::move(yystack_[2].value.as < std::vector<pdm::ast::TPattern::Field*> > ()); yylhs.value.as < std::vector<pdm::ast::TPattern::Field*> > ().push_back(yystack_[0].value.as < pdm::ast::TPattern::Field* > ()); }
#line 3285 "parser.tab.cc"
    break;

  case 201: // struct_exp_field_cl: struct_exp_field
#line 719 "parser.yy"
                                                    { yylhs.value.as < std::vector<pdm::ast::StructExp::Field*> > ().push_back(yystack_[0].value.as < pdm::ast::StructExp::Field* > ()); }
#line 3291 "parser.tab.cc"
    break;

  case 202: // struct_exp_field_cl: struct_exp_field_cl "," struct_exp_field
#line 720 "parser.yy"
                                                    { yylhs.value.as < std::vector<pdm::ast::StructExp::Field*> > () = std::move(yystack_[2].value.as < std::vector<pdm::ast::StructExp::Field*> > ()); yylhs.value.as < std::vector<pdm::ast::StructExp::Field*> > ().push_back(yystack_[0].value.as < pdm::ast::StructExp::Field* > ()); }
#line 3297 "parser.tab.cc"
    break;

  case 203: // tpattern_seq: tpattern
#line 724 "parser.yy"
                             { yylhs.value.as < std::vector<pdm::ast::TPattern*> > ().push_back(yystack_[0].value.as < pdm::ast::TPattern* > ()); }
#line 3303 "parser.tab.cc"
    break;

  case 204: // tpattern_seq: tpattern_seq tpattern
#line 725 "parser.yy"
                             { yylhs.value.as < std::vector<pdm::ast::TPattern*> > () = std::move(yystack_[1].value.as < std::vector<pdm::ast::TPattern*> > ()); yylhs.value.as < std::vector<pdm::ast::TPattern*> > ().push_back(yystack_[0].value.as < pdm::ast::TPattern* > ()); }
#line 3309 "parser.tab.cc"
    break;


#line 3313 "parser.tab.cc"

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





  const short parser::yypact_ninf_ = -183;

  const signed char parser::yytable_ninf_ = -1;

  const short
  parser::yypact_[] =
  {
     211,    11,    55,    55,    75,   211,    49,  -183,  -183,  -183,
      41,  -183,    84,    87,  -183,   109,  -183,   199,    -8,   565,
    -183,    55,    55,   113,   113,  -183,   148,   132,  -183,  -183,
    -183,  -183,  -183,  -183,  -183,  -183,  -183,   112,    29,   154,
    -183,  -183,  -183,  -183,  -183,  -183,   390,    20,  -183,  -183,
    -183,  -183,  -183,  -183,  -183,  -183,  -183,  -183,  -183,  -183,
    -183,  -183,   252,  -183,  -183,  -183,   234,  -183,  -183,  -183,
    -183,  -183,   565,  -183,   251,   245,   225,   250,   151,   153,
     182,   178,   -28,  -183,    47,   184,  -183,   196,  -183,    -8,
     237,   136,   192,   154,   390,  -183,  -183,   219,   214,   224,
     185,  -183,   -18,  -183,  -183,  -183,  -183,   307,  -183,   149,
    -183,  -183,  -183,    38,    38,    38,   565,   565,  -183,   235,
    -183,  -183,  -183,  -183,  -183,   227,   230,   340,  -183,   -17,
    -183,  -183,    28,   425,   460,  -183,  -183,  -183,  -183,   565,
    -183,  -183,   565,  -183,  -183,  -183,  -183,   565,  -183,  -183,
     565,   565,   565,   565,     9,   307,   239,   -14,  -183,   -28,
     104,   113,  -183,   -27,   113,  -183,  -183,    29,    55,    55,
    -183,   179,  -183,   190,    29,   179,    53,   202,  -183,   530,
    -183,   565,  -183,  -183,  -183,  -183,   179,  -183,   232,   288,
     460,    14,   179,  -183,  -183,   236,   255,   257,   259,  -183,
    -183,   565,  -183,  -183,   278,   274,    55,  -183,  -183,  -183,
    -183,  -183,   565,   565,  -183,  -183,  -183,   203,  -183,  -183,
    -183,    78,  -183,   251,   245,   225,   250,   151,   153,  -183,
     273,   179,   179,  -183,   155,   307,   179,    29,   129,  -183,
     179,    55,   219,  -183,  -183,  -183,   260,  -183,   281,   104,
     179,   314,   179,   179,  -183,   169,  -183,  -183,  -183,    79,
    -183,   179,  -183,  -183,  -183,  -183,  -183,  -183,  -183,   164,
    -183,  -183,   216,  -183,   565,   565,   565,   565,  -183,  -183,
    -183,   227,  -183,  -183,  -183,   495,  -183,   460,  -183,  -183,
    -183,  -183,   307,  -183,   172,   268,  -183,   179,    29,   222,
     179,  -183,   141,   113,   139,  -183,   271,    95,  -183,  -183,
    -183,  -183,  -183,  -183,  -183,    55,  -183,  -183,  -183,  -183,
    -183,  -183,  -183,  -183,  -183,    29,   272,  -183,  -183,    55,
    -183,  -183,  -183,  -183,   229,    94,  -183,  -183,  -183,    29,
    -183,   179,  -183,   283,   160,  -183,  -183,   179,   285,    21,
     292,   179,  -183,   293,  -183,    60,  -183,  -183
  };

  const unsigned char
  parser::yydefact_[] =
  {
       0,     0,     0,     0,     0,     2,     0,     5,     6,     7,
       0,    49,     0,     0,     1,     0,     3,     0,     0,     0,
       4,     0,     0,     0,     0,    26,     0,     0,    21,    22,
      23,    24,    27,    25,    28,    52,    51,     0,     0,     0,
     110,    78,    79,    50,    81,    80,     0,     0,   108,   106,
     107,   109,    72,    74,    47,    71,    60,    61,    62,    63,
      92,    73,    75,    76,    64,    77,   104,    93,    94,    95,
      96,   115,     0,    53,   119,   125,   129,   131,   133,   135,
     111,     0,     0,    48,     0,     0,     8,     0,     9,     0,
       0,     0,     0,     0,     0,    65,   149,    72,    55,     0,
       0,    54,     0,   161,   150,   151,   152,     0,   153,   166,
     162,   163,   141,     0,     0,     0,     0,     0,    66,     0,
      11,    12,    13,    14,    15,    72,     0,     0,   201,     0,
      83,    82,     0,     0,     0,   105,   112,   113,   114,     0,
     117,   118,     0,   121,   122,   123,   124,     0,   127,   128,
       0,     0,     0,     0,     0,     0,     0,     0,   203,     0,
       0,     0,    35,     0,     0,    10,    46,     0,     0,     0,
     192,     0,   195,     0,     0,     0,     0,     0,   158,     0,
      67,     0,    69,   140,   138,   139,     0,   157,     0,     0,
       0,     0,   184,   189,   190,     0,     0,     0,     0,    20,
      89,     0,    86,    87,     0,     0,     0,    70,   100,   101,
     103,   102,     0,     0,    98,   174,   177,     0,   171,   170,
     172,     0,   116,   120,   126,   130,   132,   134,   136,    44,
       0,     0,     0,   199,     0,     0,     0,     0,     0,   204,
       0,     0,     0,   167,    33,   168,    36,    37,    39,     0,
       0,    84,     0,     0,   180,     0,   191,    91,   160,     0,
     154,     0,   156,    68,    56,    57,   137,   159,   165,     0,
     188,   197,     0,   183,     0,     0,     0,     0,   179,    90,
      88,     0,   202,   175,   176,     0,    99,     0,    97,    45,
     186,   185,     0,   193,     0,     0,    31,     0,     0,     0,
       0,   147,     0,     0,     0,    34,     0,     0,   181,   182,
     196,   155,   144,   145,   164,     0,   187,    16,    17,    18,
      19,   178,   173,   200,   194,     0,     0,    32,   146,     0,
     169,    38,    40,   142,     0,     0,    85,   198,    29,     0,
     148,     0,    41,     0,     0,    30,   143,     0,     0,     0,
       0,     0,    42,     0,    58,     0,    59,    43
  };

  const short
  parser::yypgoto_[] =
  {
    -183,  -183,  -183,   330,    68,  -183,   209,  -183,  -183,  -183,
    -183,  -183,   311,  -183,  -183,  -183,  -183,  -183,    37,  -183,
    -183,    97,   133,   -20,    -2,  -183,   261,    30,  -183,  -183,
     -10,   -36,  -183,  -183,  -183,  -183,    39,   212,  -183,  -183,
    -183,  -183,  -183,  -183,  -183,  -183,  -183,  -183,   -61,  -183,
    -183,  -183,   220,  -183,   217,  -183,   201,  -183,   218,   213,
     215,  -183,   -86,  -183,   102,  -183,  -183,    48,  -183,   205,
    -183,  -183,  -183,  -183,  -183,  -183,  -183,  -183,  -152,   118,
    -183,    89,   188,    98,  -183,   173,   127,  -182,    92,  -183,
     204,   -75,  -153,  -183,  -183,   152,  -183,   -79
  };

  const short
  parser::yydefgoto_[] =
  {
      -1,     4,     5,     6,     7,    26,   119,   120,   121,   122,
     123,   124,    27,    28,    29,    30,   162,   246,   247,    31,
      32,     8,     9,    96,    52,    53,    37,   218,    99,   100,
     349,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      64,   127,    65,    66,    67,    68,    69,    70,    71,    72,
      73,   139,    74,   142,    75,   147,    76,   150,    77,    78,
      79,    80,   101,   186,   102,   334,   177,   301,   302,   103,
     104,   105,   106,   107,   108,   109,   110,   111,   112,   244,
     245,   220,   221,   216,   217,   128,   172,   193,   233,   194,
     195,    92,   158,   173,   272,   234,   129,   159
  };

  const short
  parser::yytable_[] =
  {
      12,    13,    90,    84,    85,   163,   239,   157,   243,   271,
     239,   135,    11,    91,    10,   155,   155,    11,   175,    81,
      82,   206,   183,    11,    11,    83,    35,    36,    38,   207,
     249,   208,   209,   236,   156,   156,   113,   114,   115,   116,
      39,    11,    93,   237,    97,   125,    40,   184,   185,    54,
     117,    41,    42,    43,    44,    45,   270,   229,    11,    41,
      42,    46,   240,    11,    83,    47,   118,   352,    48,    46,
      46,    49,    50,    47,    47,    14,    98,   126,   222,   191,
      51,    93,    11,    83,   238,    25,    17,   187,    16,   171,
     155,   259,    97,   183,    25,   260,   210,   243,    11,    18,
      93,   240,    19,    38,   160,   188,   357,    11,    83,   156,
     161,   192,   192,   192,    33,    39,   287,    83,   184,   185,
     240,   311,   288,    33,    98,    93,    41,    42,    43,    44,
      45,   251,    97,   337,    89,   231,    46,   155,   257,    11,
      47,   248,    11,    83,   250,   240,   198,   199,    20,   241,
      34,   343,   230,   232,    21,     1,   156,   205,   242,    34,
      93,     2,     3,   215,   168,   169,   252,   253,    22,   242,
      23,    88,    11,   242,   151,    24,   297,   152,   170,   329,
     240,   332,    11,    83,   242,   189,   298,   330,    97,   192,
     242,   239,   190,   292,    86,    91,   176,   168,   169,   293,
      93,   296,   287,   155,   281,    21,     1,   153,   314,   264,
     292,   265,     2,     3,   154,   231,   324,   348,     1,    22,
     240,    23,   156,   181,     2,     3,    24,   182,   255,   242,
     242,   278,   256,   232,   242,   165,   219,   164,   242,   300,
     261,   285,   283,   284,   262,   286,   167,   242,   242,   174,
     242,   242,   179,   171,   315,   178,   344,   242,   316,   242,
     259,   350,   327,   353,   260,   350,   180,   341,   267,   353,
     132,   342,   231,   254,   200,   133,   202,   134,   143,   144,
     145,   146,   235,   248,   201,    97,   130,   131,   266,   338,
     232,   268,   219,   274,   273,   242,   140,   141,   242,   136,
     137,   138,   242,   345,   317,   318,   319,   320,   148,   149,
      11,    83,   275,   192,   276,   215,   277,   279,   196,   197,
     280,   289,   304,   303,   307,   325,   335,   300,   347,   339,
     351,   354,   356,   290,   291,    15,   204,    87,   295,   242,
     331,   355,   299,    11,   211,   242,   336,   242,    38,   242,
     166,   225,   306,   242,   308,   309,   113,   114,   115,   116,
      39,   312,   223,   313,   224,   227,    40,   305,   228,   226,
     117,    41,    42,    43,    44,    45,   322,   340,   269,   282,
     258,    46,   310,   321,   323,    47,   203,   294,    48,   219,
       0,    49,    50,    11,    83,     0,     0,     0,    38,   326,
      51,     0,   328,     0,     0,     0,   333,     0,     0,     0,
      39,    93,     0,     0,     0,     0,    40,     0,     0,     0,
       0,    41,    42,    43,    44,    45,     0,     0,    11,     0,
       0,    94,    95,    38,     0,    47,     0,     0,    48,     0,
       0,    49,    50,   346,     0,    39,     0,     0,     0,     0,
      51,    40,     0,   212,   213,     0,    41,    42,    43,    44,
      45,     0,     0,    11,    83,     0,    46,   214,    38,     0,
      47,     0,     0,    48,     0,     0,    49,    50,     0,     0,
      39,    93,     0,     0,     0,    51,    40,     0,     0,     0,
       0,    41,    42,    43,    44,    45,     0,     0,    11,     0,
       0,    94,     0,    38,     0,    47,     0,     0,    48,     0,
       0,    49,    50,     0,     0,    39,     0,     0,     0,     0,
      51,    40,     0,   212,   213,     0,    41,    42,    43,    44,
      45,     0,     0,    11,     0,     0,    46,     0,    38,     0,
      47,     0,     0,    48,     0,     0,    49,    50,     0,     0,
      39,     0,     0,     0,     0,    51,    40,     0,     0,     0,
       0,    41,    42,    43,    44,    45,     0,     0,    11,     0,
       0,    46,   263,    38,     0,    47,     0,     0,    48,     0,
       0,    49,    50,     0,     0,    39,     0,     0,     0,     0,
      51,    40,     0,     0,     0,     0,    41,    42,    43,    44,
      45,     0,     0,     0,     0,     0,    46,     0,     0,     0,
      47,     0,     0,    48,     0,     0,    49,    50,     0,     0,
       0,     0,     0,     0,     0,    51
  };

  const short
  parser::yycheck_[] =
  {
       2,     3,    38,    23,    24,    84,   159,    82,   160,   191,
     163,    72,     3,    41,     3,    43,    43,     3,    93,    21,
      22,    38,    40,     3,     3,     4,    34,    35,     8,    46,
      57,     3,     4,    47,    62,    62,    16,    17,    18,    19,
      20,     3,    21,    57,    46,    47,    26,    65,    66,    19,
      30,    31,    32,    33,    34,    35,    42,    48,     3,    31,
      32,    41,    41,     3,     4,    45,    46,    46,    48,    41,
      41,    51,    52,    45,    45,     0,    46,    47,   139,    41,
      60,    21,     3,     4,   159,    17,    45,   107,    39,    91,
      43,    38,    94,    40,    26,    42,   132,   249,     3,    15,
      21,    41,    15,     8,    57,   107,    46,     3,     4,    62,
      63,   113,   114,   115,    17,    20,    38,     4,    65,    66,
      41,    42,    44,    26,    94,    21,    31,    32,    33,    34,
      35,   167,   134,   315,    22,   155,    41,    43,   174,     3,
      45,   161,     3,     4,   164,    41,   116,   117,    39,    45,
      17,    57,   154,   155,     6,     7,    62,   127,   160,    26,
      21,    13,    14,   133,    28,    29,   168,   169,    20,   171,
      22,    39,     3,   175,    23,    27,    47,    24,    42,    38,
      41,    42,     3,     4,   186,    36,    57,    46,   190,   191,
     192,   344,    43,    38,    46,    41,    94,    28,    29,    44,
      21,   237,    38,    43,   206,     6,     7,    25,    44,   179,
      38,   181,    13,    14,    36,   235,    44,    57,     7,    20,
      41,    22,    62,    38,    13,    14,    27,    42,    38,   231,
     232,   201,    42,   235,   236,    39,   134,    53,   240,   241,
      38,    38,   212,   213,    42,    42,     9,   249,   250,    57,
     252,   253,    38,   255,    38,    36,   335,   259,    42,   261,
      38,   347,   298,   349,    42,   351,    42,    38,    36,   355,
      36,    42,   292,   171,    39,    41,    46,    43,    53,    54,
      55,    56,    43,   303,    57,   287,    34,    35,   186,   325,
     292,     3,   190,    57,   192,   297,    51,    52,   300,    48,
      49,    50,   304,   339,   274,   275,   276,   277,    58,    59,
       3,     4,    57,   315,    57,   285,    57,    39,   114,   115,
      46,    48,    41,    63,    10,    57,    55,   329,    45,    57,
      45,    39,    39,   231,   232,     5,   127,    26,   236,   341,
     303,   351,   240,     3,   132,   347,   307,   349,     8,   351,
      89,   150,   250,   355,   252,   253,    16,    17,    18,    19,
      20,   259,   142,   261,   147,   152,    26,   249,   153,   151,
      30,    31,    32,    33,    34,    35,   287,   329,   190,   206,
     175,    41,   255,   285,   292,    45,    46,   235,    48,   287,
      -1,    51,    52,     3,     4,    -1,    -1,    -1,     8,   297,
      60,    -1,   300,    -1,    -1,    -1,   304,    -1,    -1,    -1,
      20,    21,    -1,    -1,    -1,    -1,    26,    -1,    -1,    -1,
      -1,    31,    32,    33,    34,    35,    -1,    -1,     3,    -1,
      -1,    41,    42,     8,    -1,    45,    -1,    -1,    48,    -1,
      -1,    51,    52,   341,    -1,    20,    -1,    -1,    -1,    -1,
      60,    26,    -1,    28,    29,    -1,    31,    32,    33,    34,
      35,    -1,    -1,     3,     4,    -1,    41,    42,     8,    -1,
      45,    -1,    -1,    48,    -1,    -1,    51,    52,    -1,    -1,
      20,    21,    -1,    -1,    -1,    60,    26,    -1,    -1,    -1,
      -1,    31,    32,    33,    34,    35,    -1,    -1,     3,    -1,
      -1,    41,    -1,     8,    -1,    45,    -1,    -1,    48,    -1,
      -1,    51,    52,    -1,    -1,    20,    -1,    -1,    -1,    -1,
      60,    26,    -1,    28,    29,    -1,    31,    32,    33,    34,
      35,    -1,    -1,     3,    -1,    -1,    41,    -1,     8,    -1,
      45,    -1,    -1,    48,    -1,    -1,    51,    52,    -1,    -1,
      20,    -1,    -1,    -1,    -1,    60,    26,    -1,    -1,    -1,
      -1,    31,    32,    33,    34,    35,    -1,    -1,     3,    -1,
      -1,    41,    42,     8,    -1,    45,    -1,    -1,    48,    -1,
      -1,    51,    52,    -1,    -1,    20,    -1,    -1,    -1,    -1,
      60,    26,    -1,    -1,    -1,    -1,    31,    32,    33,    34,
      35,    -1,    -1,    -1,    -1,    -1,    41,    -1,    -1,    -1,
      45,    -1,    -1,    48,    -1,    -1,    51,    52,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    60
  };

  const unsigned char
  parser::yystos_[] =
  {
       0,     7,    13,    14,    69,    70,    71,    72,    89,    90,
       3,     3,    92,    92,     0,    71,    39,    45,    15,    15,
      39,     6,    20,    22,    27,    72,    73,    80,    81,    82,
      83,    87,    88,    89,    90,    34,    35,    94,     8,    20,
      26,    31,    32,    33,    34,    35,    41,    45,    48,    51,
      52,    60,    92,    93,    95,    99,   100,   101,   102,   103,
     104,   105,   106,   107,   108,   110,   111,   112,   113,   114,
     115,   116,   117,   118,   120,   122,   124,   126,   127,   128,
     129,    92,    92,     4,    91,    91,    46,    80,    39,    22,
      99,    41,   159,    21,    41,    42,    91,    92,    95,    96,
      97,   130,   132,   137,   138,   139,   140,   141,   142,   143,
     144,   145,   146,    16,    17,    18,    19,    30,    46,    74,
      75,    76,    77,    78,    79,    92,    95,   109,   153,   164,
      34,    35,    36,    41,    43,   116,    48,    49,    50,   119,
      51,    52,   121,    53,    54,    55,    56,   123,    58,    59,
     125,    23,    24,    25,    36,    43,    62,   159,   160,   165,
      57,    63,    84,   165,    53,    39,    94,     9,    28,    29,
      42,    92,   154,   161,    57,   159,   132,   134,    36,    38,
      42,    38,    42,    40,    65,    66,   131,    91,    92,    36,
      43,    41,    92,   155,   157,   158,   158,   158,    95,    95,
      39,    57,    46,    46,    74,    95,    38,    46,     3,     4,
      99,   105,    28,    29,    42,    95,   151,   152,    95,   132,
     149,   150,   116,   120,   122,   124,   126,   127,   128,    48,
      92,    91,    92,   156,   163,    43,    47,    57,   159,   160,
      41,    45,    92,   146,   147,   148,    85,    86,    91,    57,
      91,    99,    92,    92,   132,    38,    42,    99,   137,    38,
      42,    38,    42,    42,    95,    95,   132,    36,     3,   150,
      42,   155,   162,   132,    57,    57,    57,    57,    95,    39,
      46,    92,   153,    95,    95,    38,    42,    38,    44,    48,
     132,   132,    38,    44,   163,   132,    99,    47,    57,   132,
      92,   135,   136,    63,    41,   147,   132,    10,   132,   132,
     154,    42,   132,   132,    44,    38,    42,    95,    95,    95,
      95,   151,   149,   156,    44,    57,   132,    99,   132,    38,
      46,    86,    42,   132,   133,    55,   104,   155,    99,    57,
     135,    38,    42,    57,   165,    99,   132,    45,    57,    98,
     130,    45,    46,   130,    39,    98,    39,    46
  };

  const unsigned char
  parser::yyr1_[] =
  {
       0,    68,    69,    70,    70,    71,    71,    71,    72,    73,
      73,    74,    74,    74,    74,    74,    75,    76,    77,    78,
      79,    80,    80,    80,    80,    80,    80,    80,    80,    81,
      81,    81,    81,    82,    82,    83,    84,    85,    85,    86,
      86,    86,    87,    87,    88,    88,    89,    90,    91,    92,
      93,    94,    94,    95,    96,    96,    97,    97,    98,    98,
      99,    99,    99,    99,    99,   100,   100,   101,   102,   102,
     103,   104,   104,   104,   104,   104,   104,   104,   105,   105,
     106,   106,   106,   106,   107,   107,   108,   108,   108,   109,
     109,   110,   111,   111,   111,   111,   111,   112,   113,   113,
     114,   114,   115,   115,   116,   116,   117,   117,   117,   117,
     117,   118,   119,   119,   119,   120,   120,   121,   121,   122,
     122,   123,   123,   123,   123,   124,   124,   125,   125,   126,
     126,   127,   127,   128,   128,   129,   129,   130,   131,   131,
     131,   132,   133,   133,   134,   134,   135,   136,   136,   137,
     137,   137,   137,   137,   138,   139,   139,   140,   141,   141,
     142,   143,   143,   143,   144,   145,   146,   147,   147,   148,
     149,   149,   150,   150,   151,   151,   151,   152,   152,   153,
     154,   154,   154,   155,   155,   156,   156,   157,   157,   158,
     158,   159,   159,   160,   160,   161,   161,   162,   162,   163,
     163,   164,   164,   165,   165
  };

  const signed char
  parser::yyr2_[] =
  {
       0,     2,     1,     2,     3,     1,     1,     1,     5,     2,
       3,     1,     1,     1,     1,     1,     4,     4,     4,     4,
       2,     1,     1,     1,     1,     1,     1,     1,     1,     7,
       8,     5,     6,     4,     5,     3,     2,     1,     3,     1,
       3,     4,    10,    11,     4,     5,     6,     4,     1,     1,
       1,     1,     1,     1,     1,     1,     3,     3,     2,     3,
       1,     1,     1,     1,     1,     2,     2,     3,     4,     3,
       3,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     2,     2,     4,     6,     3,     3,     4,     2,
       3,     4,     1,     1,     1,     1,     1,     4,     3,     4,
       3,     3,     3,     3,     1,     2,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     3,     1,     1,     1,
       3,     1,     1,     1,     1,     1,     3,     1,     1,     1,
       3,     1,     3,     1,     3,     1,     3,     3,     1,     1,
       1,     1,     1,     3,     3,     3,     2,     1,     3,     1,
       1,     1,     1,     1,     3,     4,     3,     2,     2,     3,
       3,     1,     1,     1,     4,     3,     1,     1,     1,     3,
       1,     1,     1,     3,     1,     2,     2,     1,     3,     3,
       2,     3,     3,     2,     1,     2,     2,     3,     2,     1,
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
  "\"fn\"", "\"Fn\"", "\"type\"", "\"and\"", "\"xor\"", "\"or\"",
  "\"not\"", "\"typeclass\"", "\"out\"", "\"inout\"", "\"discard\"",
  "\"42\"", "\"0x2a\"", "\"4.2\"", "\"\\\"dq-string-literal\\\"\"",
  "\"'sq-string-literal'\"", "\".\"", "\":\"", "\",\"", "\";\"", "\"::\"",
  "\"(\"", "\")\"", "\"[\"", "\"]\"", "\"{\"", "\"}\"", "\"->\"", "\"*\"",
  "\"/\"", "\"%\"", "\"+\"", "\"-\"", "\"<\"", "\"<=\"", "\">\"", "\">=\"",
  "\"=\"", "\"==\"", "\"!=\"", "\"^\"", "\"&\"", "\"!\"", "\"|\"",
  "\"EOS\"", "\":<\"", "\">:\"", "\"<null>\"", "$accept", "script",
  "scriptContent", "scriptContentStmt", "mod_stmt", "moduleContent",
  "chain_prefix_stmt", "const_stmt", "val_stmt", "var_stmt", "set_stmt",
  "discard_stmt", "moduleContentStmt", "fn_stmt", "type_stmt", "enum_stmt",
  "enum_field_pl", "unprefixed_enum_field_pl", "enum_field",
  "typeclass_stmt", "using_stmt", "import_stmt", "extern_stmt", "tid",
  "vid", "floatl", "stringl", "expr", "long_exp", "expr_cl2",
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
  "tuple_typespec", "mod_prefix_tid", "mod_prefix", "fn_typespec",
  "postfix_typespec", "tcall_typespec", "dot_typespec", "unary_typespec",
  "long_typespec", "struct_typespec", "targ", "targ_cl", "varg", "varg_cl",
  "struct_exp_field", "vpattern_field", "lpattern_field", "tpattern_field",
  "lpattern", "lpattern_naked", "vpattern", "tpattern",
  "vpattern_field_cl", "lpattern_field_cl", "tpattern_field_cl",
  "struct_exp_field_cl", "tpattern_seq", YY_NULLPTR
  };
#endif


#if YYDEBUG
  const short
  parser::yyrline_[] =
  {
       0,   290,   290,   293,   294,   297,   298,   299,   307,   310,
     311,   319,   320,   321,   322,   323,   326,   329,   332,   335,
     338,   342,   343,   344,   345,   346,   347,   348,   349,   352,
     353,   354,   355,   358,   359,   362,   365,   368,   369,   372,
     373,   374,   377,   380,   385,   386,   389,   392,   399,   400,
     402,   405,   406,   413,   416,   417,   420,   421,   424,   425,
     429,   430,   431,   432,   433,   436,   437,   440,   443,   444,
     447,   450,   451,   452,   453,   454,   455,   456,   459,   460,
     463,   464,   465,   466,   469,   470,   473,   474,   475,   478,
     479,   482,   486,   487,   488,   489,   490,   493,   496,   497,
     500,   501,   504,   505,   509,   510,   513,   514,   515,   516,
     517,   521,   524,   525,   526,   529,   530,   533,   534,   537,
     538,   541,   542,   543,   544,   547,   548,   551,   552,   555,
     556,   559,   560,   563,   564,   567,   568,   572,   575,   576,
     577,   585,   588,   589,   592,   593,   597,   600,   601,   605,
     606,   607,   608,   609,   612,   615,   616,   619,   622,   623,
     626,   630,   631,   632,   635,   637,   641,   645,   646,   649,
     652,   653,   656,   657,   659,   660,   661,   664,   665,   673,
     676,   677,   678,   681,   682,   685,   686,   690,   691,   694,
     695,   698,   699,   702,   703,   707,   708,   711,   712,   715,
     716,   719,   720,   724,   725
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
      65,    66,    67
    };
    // Last valid token kind.
    const int code_max = 322;

    if (t <= 0)
      return symbol_kind::S_YYEOF;
    else if (t <= code_max)
      return YY_CAST (symbol_kind_type, translate_table[t]);
    else
      return symbol_kind::S_YYUNDEF;
  }

#line 22 "parser.yy"
} } // pdm::parser
#line 4003 "parser.tab.cc"

#line 728 "parser.yy"


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
