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
#line 80 "parser.yy"

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

#line 33 "parser.yy"
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
      case symbol_kind::S_type_query_exp: // type_query_exp
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
      case symbol_kind::S_importStmt: // importStmt
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
      case symbol_kind::S_expr_sl: // expr_sl
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
      case symbol_kind::S_type_query_exp: // type_query_exp
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
      case symbol_kind::S_importStmt: // importStmt
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
      case symbol_kind::S_expr_sl: // expr_sl
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
      case symbol_kind::S_type_query_exp: // type_query_exp
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
      case symbol_kind::S_importStmt: // importStmt
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
      case symbol_kind::S_expr_sl: // expr_sl
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
      case symbol_kind::S_type_query_exp: // type_query_exp
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
      case symbol_kind::S_importStmt: // importStmt
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
      case symbol_kind::S_expr_sl: // expr_sl
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
      case symbol_kind::S_type_query_exp: // type_query_exp
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
      case symbol_kind::S_importStmt: // importStmt
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
      case symbol_kind::S_expr_sl: // expr_sl
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
      case symbol_kind::S_type_query_exp: // type_query_exp
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
      case symbol_kind::S_importStmt: // importStmt
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
      case symbol_kind::S_expr_sl: // expr_sl
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
      case symbol_kind::S_type_query_exp: // type_query_exp
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
      case symbol_kind::S_importStmt: // importStmt
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
      case symbol_kind::S_expr_sl: // expr_sl
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
#line 302 "parser.yy"
                    { yylhs.value.as < pdm::ast::Script* > () = mgr->new_script(source, yylhs.location, std::move(yystack_[0].value.as < std::vector<pdm::ast::Stmt*> > ())); *returnp = yylhs.value.as < pdm::ast::Script* > (); }
#line 2050 "parser.tab.cc"
    break;

  case 3: // scriptContent: scriptContentStmt ";"
#line 305 "parser.yy"
                                                    { yylhs.value.as < std::vector<pdm::ast::Stmt*> > ().push_back(yystack_[1].value.as < pdm::ast::Stmt* > ()); }
#line 2056 "parser.tab.cc"
    break;

  case 4: // scriptContent: scriptContent scriptContentStmt ";"
#line 306 "parser.yy"
                                                    { yylhs.value.as < std::vector<pdm::ast::Stmt*> > () = std::move(yystack_[2].value.as < std::vector<pdm::ast::Stmt*> > ()); yylhs.value.as < std::vector<pdm::ast::Stmt*> > ().push_back(yystack_[1].value.as < pdm::ast::Stmt* > ()); }
#line 2062 "parser.tab.cc"
    break;

  case 5: // scriptContentStmt: mod_stmt
#line 309 "parser.yy"
      { yylhs.value.as < pdm::ast::Stmt* > () = yystack_[0].value.as < pdm::ast::Stmt* > (); }
#line 2068 "parser.tab.cc"
    break;

  case 6: // mod_stmt: "mod" "<val_id>" "{" moduleContent "}"
#line 317 "parser.yy"
                                                { yylhs.value.as < pdm::ast::Stmt* > () = mgr->new_mod_stmt(yylhs.location, yystack_[3].value.as < TokenInfo > ().ID_intstr, std::move(yystack_[1].value.as < std::vector<pdm::ast::Stmt*> > ())); }
#line 2074 "parser.tab.cc"
    break;

  case 7: // moduleContent: moduleContentStmt ";"
#line 320 "parser.yy"
                                                    { yylhs.value.as < std::vector<pdm::ast::Stmt*> > ().push_back(yystack_[1].value.as < pdm::ast::Stmt* > ()); }
#line 2080 "parser.tab.cc"
    break;

  case 8: // moduleContent: moduleContent moduleContentStmt ";"
#line 321 "parser.yy"
                                                    { yylhs.value.as < std::vector<pdm::ast::Stmt*> > () = std::move(yystack_[2].value.as < std::vector<pdm::ast::Stmt*> > ()); yylhs.value.as < std::vector<pdm::ast::Stmt*> > ().push_back(yystack_[1].value.as < pdm::ast::Stmt* > ()); }
#line 2086 "parser.tab.cc"
    break;

  case 9: // chain_prefix_stmt: const_stmt
#line 329 "parser.yy"
      { yylhs.value.as < pdm::ast::Stmt* > () = yystack_[0].value.as < pdm::ast::Stmt* > (); }
#line 2092 "parser.tab.cc"
    break;

  case 10: // chain_prefix_stmt: val_stmt
#line 330 "parser.yy"
      { yylhs.value.as < pdm::ast::Stmt* > () = yystack_[0].value.as < pdm::ast::Stmt* > (); }
#line 2098 "parser.tab.cc"
    break;

  case 11: // chain_prefix_stmt: var_stmt
#line 331 "parser.yy"
      { yylhs.value.as < pdm::ast::Stmt* > () = yystack_[0].value.as < pdm::ast::Stmt* > (); }
#line 2104 "parser.tab.cc"
    break;

  case 12: // chain_prefix_stmt: set_stmt
#line 332 "parser.yy"
      { yylhs.value.as < pdm::ast::Stmt* > () = yystack_[0].value.as < pdm::ast::Stmt* > (); }
#line 2110 "parser.tab.cc"
    break;

  case 13: // chain_prefix_stmt: discard_stmt
#line 333 "parser.yy"
      { yylhs.value.as < pdm::ast::Stmt* > () = yystack_[0].value.as < pdm::ast::Stmt* > (); }
#line 2116 "parser.tab.cc"
    break;

  case 14: // const_stmt: "const" lpattern_naked "=" expr
#line 336 "parser.yy"
                                        { yylhs.value.as < pdm::ast::Stmt* > () = mgr->new_const_stmt(yylhs.location, yystack_[2].value.as < pdm::ast::LPattern* > (), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2122 "parser.tab.cc"
    break;

  case 15: // val_stmt: "val" lpattern_naked "=" expr
#line 339 "parser.yy"
                                        { yylhs.value.as < pdm::ast::Stmt* > () = mgr->new_val_stmt(yylhs.location, yystack_[2].value.as < pdm::ast::LPattern* > (), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2128 "parser.tab.cc"
    break;

  case 16: // var_stmt: "var" lpattern_naked "=" expr
#line 342 "parser.yy"
                                        { yylhs.value.as < pdm::ast::Stmt* > () = mgr->new_var_stmt(yylhs.location, yystack_[2].value.as < pdm::ast::LPattern* > (), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2134 "parser.tab.cc"
    break;

  case 17: // set_stmt: "set" expr "=" expr
#line 345 "parser.yy"
                              { yylhs.value.as < pdm::ast::Stmt* > () = mgr->new_set_stmt(yylhs.location, yystack_[2].value.as < pdm::ast::Exp* > (), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2140 "parser.tab.cc"
    break;

  case 18: // discard_stmt: expr
#line 348 "parser.yy"
              { yylhs.value.as < pdm::ast::Stmt* > () = mgr->new_discard_stmt(yylhs.location, yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2146 "parser.tab.cc"
    break;

  case 19: // moduleContentStmt: fn_stmt
#line 352 "parser.yy"
      { yylhs.value.as < pdm::ast::Stmt* > () = yystack_[0].value.as < pdm::ast::Stmt* > (); }
#line 2152 "parser.tab.cc"
    break;

  case 20: // moduleContentStmt: type_stmt
#line 353 "parser.yy"
      { yylhs.value.as < pdm::ast::Stmt* > () = yystack_[0].value.as < pdm::ast::Stmt* > (); }
#line 2158 "parser.tab.cc"
    break;

  case 21: // moduleContentStmt: enum_stmt
#line 354 "parser.yy"
      { yylhs.value.as < pdm::ast::Stmt* > () = yystack_[0].value.as < pdm::ast::Stmt* > (); }
#line 2164 "parser.tab.cc"
    break;

  case 22: // moduleContentStmt: typeclass_stmt
#line 355 "parser.yy"
      { yylhs.value.as < pdm::ast::Stmt* > () = yystack_[0].value.as < pdm::ast::Stmt* > (); }
#line 2170 "parser.tab.cc"
    break;

  case 23: // moduleContentStmt: importStmt
#line 356 "parser.yy"
      { yylhs.value.as < pdm::ast::Stmt* > () = yystack_[0].value.as < pdm::ast::Stmt* > (); }
#line 2176 "parser.tab.cc"
    break;

  case 24: // moduleContentStmt: mod_stmt
#line 357 "parser.yy"
      { yylhs.value.as < pdm::ast::Stmt* > () = yystack_[0].value.as < pdm::ast::Stmt* > (); }
#line 2182 "parser.tab.cc"
    break;

  case 25: // moduleContentStmt: using_stmt
#line 358 "parser.yy"
      { yylhs.value.as < pdm::ast::Stmt* > () = yystack_[0].value.as < pdm::ast::Stmt* > (); }
#line 2188 "parser.tab.cc"
    break;

  case 26: // moduleContentStmt: extern_stmt
#line 359 "parser.yy"
      { yylhs.value.as < pdm::ast::Stmt* > () = yystack_[0].value.as < pdm::ast::Stmt* > (); }
#line 2194 "parser.tab.cc"
    break;

  case 27: // fn_stmt: "fn" vid vpattern "->" typespec "=" bracketed_exp
#line 362 "parser.yy"
                                                                          { yylhs.value.as < pdm::ast::Stmt* > () = mgr->new_fn_stmt(yylhs.location, yystack_[5].value.as < TokenInfo > ().ID_intstr, std::move(std::vector<ast::TPattern*>{}), yystack_[4].value.as < pdm::ast::VPattern* > (), yystack_[2].value.as < pdm::ast::Typespec* > (), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2200 "parser.tab.cc"
    break;

  case 28: // fn_stmt: "fn" vid tpattern_seq vpattern "->" typespec "=" bracketed_exp
#line 363 "parser.yy"
                                                                          { yylhs.value.as < pdm::ast::Stmt* > () = mgr->new_fn_stmt(yylhs.location, yystack_[6].value.as < TokenInfo > ().ID_intstr, std::move(yystack_[5].value.as < std::vector<pdm::ast::TPattern*> > ()), yystack_[4].value.as < pdm::ast::VPattern* > (), yystack_[2].value.as < pdm::ast::Typespec* > (), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2206 "parser.tab.cc"
    break;

  case 29: // fn_stmt: "fn" vid vpattern "=" bracketed_exp
#line 364 "parser.yy"
                                                                          { yylhs.value.as < pdm::ast::Stmt* > () = mgr->new_fn_stmt(yylhs.location, yystack_[3].value.as < TokenInfo > ().ID_intstr, std::move(std::vector<ast::TPattern*>{}), yystack_[2].value.as < pdm::ast::VPattern* > (), nullptr, yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2212 "parser.tab.cc"
    break;

  case 30: // fn_stmt: "fn" vid tpattern_seq vpattern "=" bracketed_exp
#line 365 "parser.yy"
                                                                          { yylhs.value.as < pdm::ast::Stmt* > () = mgr->new_fn_stmt(yylhs.location, yystack_[4].value.as < TokenInfo > ().ID_intstr, std::move(yystack_[3].value.as < std::vector<pdm::ast::TPattern*> > ()), yystack_[2].value.as < pdm::ast::VPattern* > (), nullptr, yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2218 "parser.tab.cc"
    break;

  case 31: // type_stmt: "type" tid "=" long_typespec
#line 368 "parser.yy"
                                                    { yylhs.value.as < pdm::ast::Stmt* > () = mgr->new_type_stmt(yylhs.location, yystack_[2].value.as < TokenInfo > ().ID_intstr, std::move(std::vector<ast::TPattern*>{}), yystack_[0].value.as < pdm::ast::Typespec* > ()); }
#line 2224 "parser.tab.cc"
    break;

  case 32: // type_stmt: "type" tid tpattern_seq "=" long_typespec
#line 369 "parser.yy"
                                                    { yylhs.value.as < pdm::ast::Stmt* > () = mgr->new_type_stmt(yylhs.location, yystack_[3].value.as < TokenInfo > ().ID_intstr, std::move(yystack_[2].value.as < std::vector<pdm::ast::TPattern*> > ()), yystack_[0].value.as < pdm::ast::Typespec* > ()); }
#line 2230 "parser.tab.cc"
    break;

  case 33: // enum_stmt: "enum" tid enum_field_pl
#line 372 "parser.yy"
                                    { yylhs.value.as < pdm::ast::Stmt* > () = mgr->new_enum_stmt(yylhs.location, yystack_[1].value.as < TokenInfo > ().ID_intstr, std::move(yystack_[0].value.as < std::vector<pdm::ast::EnumStmt::Field*> > ())); }
#line 2236 "parser.tab.cc"
    break;

  case 34: // enum_field_pl: "|" unprefixed_enum_field_pl
#line 375 "parser.yy"
                                    { yylhs.value.as < std::vector<pdm::ast::EnumStmt::Field*> > () = std::move(yystack_[0].value.as < std::vector<pdm::ast::EnumStmt::Field*> > ()); }
#line 2242 "parser.tab.cc"
    break;

  case 35: // enum_field_pl: unprefixed_enum_field_pl
#line 376 "parser.yy"
                                    { yylhs.value.as < std::vector<pdm::ast::EnumStmt::Field*> > () = std::move(yystack_[0].value.as < std::vector<pdm::ast::EnumStmt::Field*> > ()); }
#line 2248 "parser.tab.cc"
    break;

  case 36: // unprefixed_enum_field_pl: enum_field
#line 379 "parser.yy"
                                                { yylhs.value.as < std::vector<pdm::ast::EnumStmt::Field*> > ().push_back(yystack_[0].value.as < pdm::ast::EnumStmt::Field* > ()); }
#line 2254 "parser.tab.cc"
    break;

  case 37: // unprefixed_enum_field_pl: unprefixed_enum_field_pl "|" enum_field
#line 380 "parser.yy"
                                                { yylhs.value.as < std::vector<pdm::ast::EnumStmt::Field*> > () = std::move(yystack_[2].value.as < std::vector<pdm::ast::EnumStmt::Field*> > ()); yylhs.value.as < std::vector<pdm::ast::EnumStmt::Field*> > ().push_back(yystack_[0].value.as < pdm::ast::EnumStmt::Field* > ()); }
#line 2260 "parser.tab.cc"
    break;

  case 38: // enum_field: tid
#line 383 "parser.yy"
                                     { yylhs.value.as < pdm::ast::EnumStmt::Field* > () = mgr->new_enum_stmt_field(yylhs.location, yystack_[0].value.as < TokenInfo > ().ID_intstr, std::move(std::vector<ast::Typespec*>{}), false); }
#line 2266 "parser.tab.cc"
    break;

  case 39: // enum_field: tid "(" ")"
#line 384 "parser.yy"
                                     { yylhs.value.as < pdm::ast::EnumStmt::Field* > () = mgr->new_enum_stmt_field(yylhs.location, yystack_[2].value.as < TokenInfo > ().ID_intstr, std::move(std::vector<ast::Typespec*>{}), true); }
#line 2272 "parser.tab.cc"
    break;

  case 40: // enum_field: tid "(" typespec_cl1 ")"
#line 385 "parser.yy"
                                     { yylhs.value.as < pdm::ast::EnumStmt::Field* > () = mgr->new_enum_stmt_field(yylhs.location, yystack_[3].value.as < TokenInfo > ().ID_intstr, std::move(yystack_[1].value.as < std::vector<pdm::ast::Typespec*> > ()), true); }
#line 2278 "parser.tab.cc"
    break;

  case 41: // typeclass_stmt: "typeclass" tid "<" tid typespec ">" "=" "{" expr_sl "}"
#line 388 "parser.yy"
                                                                                        { 
        yylhs.value.as < pdm::ast::Stmt* > () = mgr->new_typeclass_stmt(yylhs.location, yystack_[8].value.as < TokenInfo > ().ID_intstr, yystack_[6].value.as < TokenInfo > ().ID_intstr, yystack_[5].value.as < pdm::ast::Typespec* > (), std::move(std::vector<ast::TPattern*>{}), std::move(yystack_[1].value.as < std::vector<pdm::ast::Exp*> > ())); 
      }
#line 2286 "parser.tab.cc"
    break;

  case 42: // typeclass_stmt: "typeclass" tid "<" tid typespec ">" tpattern_seq "=" "{" expr_sl "}"
#line 391 "parser.yy"
                                                                                        { 
        yylhs.value.as < pdm::ast::Stmt* > () = mgr->new_typeclass_stmt(yylhs.location, yystack_[9].value.as < TokenInfo > ().ID_intstr, yystack_[7].value.as < TokenInfo > ().ID_intstr, yystack_[6].value.as < pdm::ast::Typespec* > (), std::move(yystack_[4].value.as < std::vector<pdm::ast::TPattern*> > ()), std::move(yystack_[1].value.as < std::vector<pdm::ast::Exp*> > ())); 
      }
#line 2294 "parser.tab.cc"
    break;

  case 43: // using_stmt: "using" bracketed_exp
#line 397 "parser.yy"
                             { yylhs.value.as < pdm::ast::Stmt* > () = mgr->new_using_stmt(yylhs.location, yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2300 "parser.tab.cc"
    break;

  case 44: // importStmt: "import" vid "from" stringl "type" stringl
#line 401 "parser.yy"
                                                       { yylhs.value.as < pdm::ast::Stmt* > () = mgr->new_import_stmt(yylhs.location, yystack_[4].value.as < TokenInfo > ().ID_intstr, *yystack_[2].value.as < TokenInfo > ().String_utf8string, *yystack_[0].value.as < TokenInfo > ().String_utf8string); }
#line 2306 "parser.tab.cc"
    break;

  case 45: // extern_stmt: "extern" vid "from" expr
#line 405 "parser.yy"
                                    { yylhs.value.as < pdm::ast::Stmt* > () = mgr->new_extern_stmt(yylhs.location, yystack_[2].value.as < TokenInfo > ().ID_intstr, yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2312 "parser.tab.cc"
    break;

  case 46: // tid: "<TypeId>"
#line 412 "parser.yy"
     { yylhs.value.as < TokenInfo > () = yystack_[0].value.as < TokenInfo > (); }
#line 2318 "parser.tab.cc"
    break;

  case 47: // vid: "<val_id>"
#line 413 "parser.yy"
     { yylhs.value.as < TokenInfo > () = yystack_[0].value.as < TokenInfo > (); }
#line 2324 "parser.tab.cc"
    break;

  case 48: // floatl: "4.2"
#line 415 "parser.yy"
      { yylhs.value.as < TokenInfo > () = yystack_[0].value.as < TokenInfo > (); }
#line 2330 "parser.tab.cc"
    break;

  case 49: // stringl: "'sq-string-literal'"
#line 418 "parser.yy"
      { yylhs.value.as < TokenInfo > () = yystack_[0].value.as < TokenInfo > (); }
#line 2336 "parser.tab.cc"
    break;

  case 50: // stringl: "\"dq-string-literal\""
#line 419 "parser.yy"
      { yylhs.value.as < TokenInfo > () = yystack_[0].value.as < TokenInfo > (); }
#line 2342 "parser.tab.cc"
    break;

  case 51: // expr: binary_exp
#line 426 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2348 "parser.tab.cc"
    break;

  case 52: // expr_cl2: expr "," expr
#line 433 "parser.yy"
                             { yylhs.value.as < std::vector<pdm::ast::Exp*> > ().reserve(2); yylhs.value.as < std::vector<pdm::ast::Exp*> > ().push_back(yystack_[2].value.as < pdm::ast::Exp* > ()); yylhs.value.as < std::vector<pdm::ast::Exp*> > ().push_back(yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2354 "parser.tab.cc"
    break;

  case 53: // expr_cl2: expr_cl2 "," expr
#line 434 "parser.yy"
                             { yylhs.value.as < std::vector<pdm::ast::Exp*> > () = std::move(yystack_[2].value.as < std::vector<pdm::ast::Exp*> > ()); yylhs.value.as < std::vector<pdm::ast::Exp*> > ().push_back(yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2360 "parser.tab.cc"
    break;

  case 54: // expr_sl: expr ";"
#line 437 "parser.yy"
                             { yylhs.value.as < std::vector<pdm::ast::Exp*> > ().push_back(yystack_[1].value.as < pdm::ast::Exp* > ()); }
#line 2366 "parser.tab.cc"
    break;

  case 55: // expr_sl: expr_sl expr ";"
#line 438 "parser.yy"
                             { yylhs.value.as < std::vector<pdm::ast::Exp*> > () = std::move(yystack_[2].value.as < std::vector<pdm::ast::Exp*> > ()); yylhs.value.as < std::vector<pdm::ast::Exp*> > ().push_back(yystack_[1].value.as < pdm::ast::Exp* > ()); }
#line 2372 "parser.tab.cc"
    break;

  case 56: // bracketed_exp: unit_exp
#line 442 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2378 "parser.tab.cc"
    break;

  case 57: // bracketed_exp: paren_exp
#line 443 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2384 "parser.tab.cc"
    break;

  case 58: // bracketed_exp: vtupleExpr
#line 444 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2390 "parser.tab.cc"
    break;

  case 59: // bracketed_exp: vstructExpr
#line 445 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2396 "parser.tab.cc"
    break;

  case 60: // bracketed_exp: chain_exp
#line 446 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2402 "parser.tab.cc"
    break;

  case 61: // unit_exp: "(" ")"
#line 449 "parser.yy"
                        { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_unit_exp(yylhs.location); }
#line 2408 "parser.tab.cc"
    break;

  case 62: // unit_exp: "{" "}"
#line 450 "parser.yy"
                        { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_unit_exp(yylhs.location); }
#line 2414 "parser.tab.cc"
    break;

  case 63: // paren_exp: "(" type_query_exp ")"
#line 453 "parser.yy"
                                    { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_paren_exp(yylhs.location, yystack_[1].value.as < pdm::ast::Exp* > ()); }
#line 2420 "parser.tab.cc"
    break;

  case 64: // vtupleExpr: "(" expr "," ")"
#line 456 "parser.yy"
                                   { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_tuple_exp(yylhs.location, std::move(std::vector(1,yystack_[2].value.as < pdm::ast::Exp* > ()))); }
#line 2426 "parser.tab.cc"
    break;

  case 65: // vtupleExpr: "(" expr_cl2 ")"
#line 457 "parser.yy"
                                   { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_tuple_exp(yylhs.location, std::move(yystack_[1].value.as < std::vector<pdm::ast::Exp*> > ())); }
#line 2432 "parser.tab.cc"
    break;

  case 66: // vstructExpr: "{" struct_exp_field_cl "}"
#line 460 "parser.yy"
                                            { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_struct_exp(yylhs.location, std::move(yystack_[1].value.as < std::vector<pdm::ast::StructExp::Field*> > ())); }
#line 2438 "parser.tab.cc"
    break;

  case 67: // primary_exp: bracketed_exp
#line 463 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2444 "parser.tab.cc"
    break;

  case 68: // primary_exp: vid
#line 464 "parser.yy"
                     { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_id_exp(yylhs.location, yystack_[0].value.as < TokenInfo > ().ID_intstr); }
#line 2450 "parser.tab.cc"
    break;

  case 69: // primary_exp: int_expr
#line 465 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2456 "parser.tab.cc"
    break;

  case 70: // primary_exp: floatl
#line 466 "parser.yy"
                     { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_float_exp(yylhs.location, yystack_[0].value.as < TokenInfo > ().Float); }
#line 2462 "parser.tab.cc"
    break;

  case 71: // primary_exp: stringls
#line 467 "parser.yy"
                     { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_string_exp(yylhs.location, std::move(yystack_[0].value.as < std::vector<pdm::ast::StringExp::Piece> > ())); }
#line 2468 "parser.tab.cc"
    break;

  case 72: // primary_exp: if_exp
#line 468 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2474 "parser.tab.cc"
    break;

  case 73: // primary_exp: lambda_exp
#line 469 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2480 "parser.tab.cc"
    break;

  case 74: // int_expr: "42"
#line 472 "parser.yy"
                { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_int_exp(yylhs.location, yystack_[0].value.as < TokenInfo > ().Int, ast::IntExp::Base::Dec); }
#line 2486 "parser.tab.cc"
    break;

  case 75: // int_expr: "0x2a"
#line 473 "parser.yy"
                { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_int_exp(yylhs.location, yystack_[0].value.as < TokenInfo > ().Int, ast::IntExp::Base::Hex); }
#line 2492 "parser.tab.cc"
    break;

  case 76: // stringls: "'sq-string-literal'"
#line 476 "parser.yy"
                             { yylhs.value.as < std::vector<pdm::ast::StringExp::Piece> > ().emplace_back(yylhs.location, *yystack_[0].value.as < TokenInfo > ().String_utf8string, ast::StringExp::QuoteKind::SingleQuote); }
#line 2498 "parser.tab.cc"
    break;

  case 77: // stringls: "\"dq-string-literal\""
#line 477 "parser.yy"
                             { yylhs.value.as < std::vector<pdm::ast::StringExp::Piece> > ().emplace_back(yylhs.location, *yystack_[0].value.as < TokenInfo > ().String_utf8string, ast::StringExp::QuoteKind::DoubleQuote); }
#line 2504 "parser.tab.cc"
    break;

  case 78: // stringls: stringls "'sq-string-literal'"
#line 478 "parser.yy"
                             { yylhs.value.as < std::vector<pdm::ast::StringExp::Piece> > () = std::move(yystack_[1].value.as < std::vector<pdm::ast::StringExp::Piece> > ()); yylhs.value.as < std::vector<pdm::ast::StringExp::Piece> > ().emplace_back(yystack_[0].location, *yystack_[0].value.as < TokenInfo > ().String_utf8string, ast::StringExp::QuoteKind::SingleQuote); }
#line 2510 "parser.tab.cc"
    break;

  case 79: // stringls: stringls "\"dq-string-literal\""
#line 479 "parser.yy"
                             { yylhs.value.as < std::vector<pdm::ast::StringExp::Piece> > () = std::move(yystack_[1].value.as < std::vector<pdm::ast::StringExp::Piece> > ()); yylhs.value.as < std::vector<pdm::ast::StringExp::Piece> > ().emplace_back(yystack_[0].location, *yystack_[0].value.as < TokenInfo > ().String_utf8string, ast::StringExp::QuoteKind::DoubleQuote); }
#line 2516 "parser.tab.cc"
    break;

  case 80: // if_exp: "if" bracketed_exp "then" bracketed_exp
#line 482 "parser.yy"
                                                                        { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_if_exp(yylhs.location, yystack_[2].value.as < pdm::ast::Exp* > (), yystack_[0].value.as < pdm::ast::Exp* > (), nullptr); }
#line 2522 "parser.tab.cc"
    break;

  case 81: // if_exp: "if" bracketed_exp "then" bracketed_exp "else" primary_exp
#line 483 "parser.yy"
                                                                        { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_if_exp(yylhs.location, yystack_[4].value.as < pdm::ast::Exp* > (), yystack_[2].value.as < pdm::ast::Exp* > (), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2528 "parser.tab.cc"
    break;

  case 82: // chain_exp: "{" expr "}"
#line 486 "parser.yy"
                                          { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_chain_exp(yylhs.location, std::move(std::vector<ast::Stmt*>{}), yystack_[1].value.as < pdm::ast::Exp* > ()); }
#line 2534 "parser.tab.cc"
    break;

  case 83: // chain_exp: "{" chain_prefix "}"
#line 487 "parser.yy"
                                           { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_chain_exp(yylhs.location, std::move(yystack_[1].value.as < std::vector<pdm::ast::Stmt*> > ()), nullptr); }
#line 2540 "parser.tab.cc"
    break;

  case 84: // chain_exp: "{" chain_prefix expr "}"
#line 488 "parser.yy"
                                           { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_chain_exp(yylhs.location, std::move(yystack_[2].value.as < std::vector<pdm::ast::Stmt*> > ()), yystack_[1].value.as < pdm::ast::Exp* > ()); }
#line 2546 "parser.tab.cc"
    break;

  case 85: // chain_prefix: chain_prefix_stmt ";"
#line 491 "parser.yy"
                                               { yylhs.value.as < std::vector<pdm::ast::Stmt*> > ().push_back(yystack_[1].value.as < pdm::ast::Stmt* > ()); }
#line 2552 "parser.tab.cc"
    break;

  case 86: // chain_prefix: chain_prefix chain_prefix_stmt ";"
#line 492 "parser.yy"
                                                { yylhs.value.as < std::vector<pdm::ast::Stmt*> > () = std::move(yystack_[2].value.as < std::vector<pdm::ast::Stmt*> > ()); yylhs.value.as < std::vector<pdm::ast::Stmt*> > ().push_back(yystack_[1].value.as < pdm::ast::Stmt* > ()); }
#line 2558 "parser.tab.cc"
    break;

  case 87: // lambda_exp: "fn" vpattern "=" bracketed_exp
#line 495 "parser.yy"
                                          { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_lambda_exp(yylhs.location, yystack_[2].value.as < pdm::ast::VPattern* > (), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2564 "parser.tab.cc"
    break;

  case 88: // postfix_exp: primary_exp
#line 499 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2570 "parser.tab.cc"
    break;

  case 89: // postfix_exp: tcall_exp
#line 500 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2576 "parser.tab.cc"
    break;

  case 90: // postfix_exp: vcall_exp
#line 501 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2582 "parser.tab.cc"
    break;

  case 91: // postfix_exp: dot_name_exp
#line 502 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2588 "parser.tab.cc"
    break;

  case 92: // postfix_exp: dot_index_exp
#line 503 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2594 "parser.tab.cc"
    break;

  case 93: // tcall_exp: postfix_exp "[" targ_cl "]"
#line 506 "parser.yy"
                                         { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_tcall_exp(yylhs.location, yystack_[3].value.as < pdm::ast::Exp* > (), std::move(yystack_[1].value.as < std::vector<pdm::ast::TArg*> > ())); }
#line 2600 "parser.tab.cc"
    break;

  case 94: // vcall_exp: postfix_exp "(" ")"
#line 509 "parser.yy"
                                            { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_vcall_exp(yylhs.location, yystack_[2].value.as < pdm::ast::Exp* > (), std::move(std::vector<ast::VArg*>{})); }
#line 2606 "parser.tab.cc"
    break;

  case 95: // vcall_exp: postfix_exp "(" varg_cl ")"
#line 510 "parser.yy"
                                            { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_vcall_exp(yylhs.location, yystack_[3].value.as < pdm::ast::Exp* > (), std::move(yystack_[1].value.as < std::vector<pdm::ast::VArg*> > ())); }
#line 2612 "parser.tab.cc"
    break;

  case 96: // dot_name_exp: postfix_exp "." "<val_id>"
#line 513 "parser.yy"
                            { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_dot_name_exp(yylhs.location, yystack_[2].value.as < pdm::ast::Exp* > (), yystack_[0].value.as < TokenInfo > ().ID_intstr, ast::DotNameExp::RhsHint::LhsStruct); }
#line 2618 "parser.tab.cc"
    break;

  case 97: // dot_name_exp: postfix_exp "." "<TypeId>"
#line 514 "parser.yy"
                            { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_dot_name_exp(yylhs.location, yystack_[2].value.as < pdm::ast::Exp* > (), yystack_[0].value.as < TokenInfo > ().ID_intstr, ast::DotNameExp::RhsHint::LhsEnum); }
#line 2624 "parser.tab.cc"
    break;

  case 98: // dot_index_exp: postfix_exp "." int_expr
#line 517 "parser.yy"
                                    { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_dot_index_exp(yylhs.location, yystack_[2].value.as < pdm::ast::Exp* > (), yystack_[0].value.as < pdm::ast::Exp* > (), ast::DotIndexExp::RhsHint::LhsNotPtr); }
#line 2630 "parser.tab.cc"
    break;

  case 99: // dot_index_exp: postfix_exp "." bracketed_exp
#line 518 "parser.yy"
                                    { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_dot_index_exp(yylhs.location, yystack_[2].value.as < pdm::ast::Exp* > (), yystack_[0].value.as < pdm::ast::Exp* > (), ast::DotIndexExp::RhsHint::LhsNotPtr); }
#line 2636 "parser.tab.cc"
    break;

  case 100: // unary_exp: postfix_exp
#line 522 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2642 "parser.tab.cc"
    break;

  case 101: // unary_exp: unary_op unary_exp
#line 523 "parser.yy"
                             { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_unary_exp(yylhs.location, yystack_[1].value.as < pdm::ast::UnaryOperator > (), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2648 "parser.tab.cc"
    break;

  case 102: // unary_op: "+"
#line 526 "parser.yy"
                 { yylhs.value.as < pdm::ast::UnaryOperator > () = ast::UnaryOperator::Plus; }
#line 2654 "parser.tab.cc"
    break;

  case 103: // unary_op: "-"
#line 527 "parser.yy"
                 { yylhs.value.as < pdm::ast::UnaryOperator > () = ast::UnaryOperator::Minus; }
#line 2660 "parser.tab.cc"
    break;

  case 104: // unary_op: "*"
#line 528 "parser.yy"
                 { yylhs.value.as < pdm::ast::UnaryOperator > () = ast::UnaryOperator::DeRef; }
#line 2666 "parser.tab.cc"
    break;

  case 105: // unary_op: "^"
#line 529 "parser.yy"
                 { yylhs.value.as < pdm::ast::UnaryOperator > () = ast::UnaryOperator::GetRef; }
#line 2672 "parser.tab.cc"
    break;

  case 106: // unary_op: "not"
#line 530 "parser.yy"
                 { yylhs.value.as < pdm::ast::UnaryOperator > () = ast::UnaryOperator::Not; }
#line 2678 "parser.tab.cc"
    break;

  case 107: // binary_exp: or_binary_exp
#line 534 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2684 "parser.tab.cc"
    break;

  case 108: // mul_binary_op: "*"
#line 537 "parser.yy"
                 { yylhs.value.as < pdm::ast::BinaryOperator > () = ast::BinaryOperator::Mul; }
#line 2690 "parser.tab.cc"
    break;

  case 109: // mul_binary_op: "/"
#line 538 "parser.yy"
                 { yylhs.value.as < pdm::ast::BinaryOperator > () = ast::BinaryOperator::Div; }
#line 2696 "parser.tab.cc"
    break;

  case 110: // mul_binary_op: "%"
#line 539 "parser.yy"
                 { yylhs.value.as < pdm::ast::BinaryOperator > () = ast::BinaryOperator::Rem; }
#line 2702 "parser.tab.cc"
    break;

  case 111: // mul_binary_exp: unary_exp
#line 542 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2708 "parser.tab.cc"
    break;

  case 112: // mul_binary_exp: mul_binary_exp mul_binary_op unary_exp
#line 543 "parser.yy"
                                               { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_binary_exp(yylhs.location, yystack_[1].value.as < pdm::ast::BinaryOperator > (), yystack_[2].value.as < pdm::ast::Exp* > (), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2714 "parser.tab.cc"
    break;

  case 113: // add_binary_op: "+"
#line 546 "parser.yy"
             { yylhs.value.as < pdm::ast::BinaryOperator > () = ast::BinaryOperator::Add; }
#line 2720 "parser.tab.cc"
    break;

  case 114: // add_binary_op: "-"
#line 547 "parser.yy"
             { yylhs.value.as < pdm::ast::BinaryOperator > () = ast::BinaryOperator::Subtract; }
#line 2726 "parser.tab.cc"
    break;

  case 115: // add_binary_exp: mul_binary_exp
#line 550 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2732 "parser.tab.cc"
    break;

  case 116: // add_binary_exp: add_binary_exp add_binary_op mul_binary_exp
#line 551 "parser.yy"
                                                    { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_binary_exp(yylhs.location, yystack_[1].value.as < pdm::ast::BinaryOperator > (), yystack_[2].value.as < pdm::ast::Exp* > (), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2738 "parser.tab.cc"
    break;

  case 117: // cmp_binary_op: "<"
#line 554 "parser.yy"
                { yylhs.value.as < pdm::ast::BinaryOperator > () = ast::BinaryOperator::Less; }
#line 2744 "parser.tab.cc"
    break;

  case 118: // cmp_binary_op: "<="
#line 555 "parser.yy"
                { yylhs.value.as < pdm::ast::BinaryOperator > () = ast::BinaryOperator::LessOrEq; }
#line 2750 "parser.tab.cc"
    break;

  case 119: // cmp_binary_op: ">"
#line 556 "parser.yy"
                { yylhs.value.as < pdm::ast::BinaryOperator > () = ast::BinaryOperator::Greater; }
#line 2756 "parser.tab.cc"
    break;

  case 120: // cmp_binary_op: ">="
#line 557 "parser.yy"
                { yylhs.value.as < pdm::ast::BinaryOperator > () = ast::BinaryOperator::GreaterOrEq; }
#line 2762 "parser.tab.cc"
    break;

  case 121: // cmp_binary_exp: add_binary_exp
#line 560 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2768 "parser.tab.cc"
    break;

  case 122: // cmp_binary_exp: cmp_binary_exp cmp_binary_op add_binary_exp
#line 561 "parser.yy"
                                                    { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_binary_exp(yylhs.location, yystack_[1].value.as < pdm::ast::BinaryOperator > (), yystack_[2].value.as < pdm::ast::Exp* > (), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2774 "parser.tab.cc"
    break;

  case 123: // eq_binary_op: "=="
#line 564 "parser.yy"
                 { yylhs.value.as < pdm::ast::BinaryOperator > () = ast::BinaryOperator::Equals; }
#line 2780 "parser.tab.cc"
    break;

  case 124: // eq_binary_op: "!="
#line 565 "parser.yy"
                 { yylhs.value.as < pdm::ast::BinaryOperator > () = ast::BinaryOperator::NotEquals; }
#line 2786 "parser.tab.cc"
    break;

  case 125: // eq_binary_exp: cmp_binary_exp
#line 568 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2792 "parser.tab.cc"
    break;

  case 126: // eq_binary_exp: eq_binary_exp eq_binary_op cmp_binary_exp
#line 569 "parser.yy"
                                                { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_binary_exp(yylhs.location, yystack_[1].value.as < pdm::ast::BinaryOperator > (), yystack_[2].value.as < pdm::ast::Exp* > (), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2798 "parser.tab.cc"
    break;

  case 127: // and_binary_exp: eq_binary_exp
#line 572 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2804 "parser.tab.cc"
    break;

  case 128: // and_binary_exp: and_binary_exp "and" eq_binary_exp
#line 573 "parser.yy"
                                           { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_binary_exp(yylhs.location, ast::BinaryOperator::And, yystack_[2].value.as < pdm::ast::Exp* > (), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2810 "parser.tab.cc"
    break;

  case 129: // xor_binary_exp: and_binary_exp
#line 576 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2816 "parser.tab.cc"
    break;

  case 130: // xor_binary_exp: xor_binary_exp "xor" and_binary_exp
#line 577 "parser.yy"
                                           { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_binary_exp(yylhs.location, ast::BinaryOperator::XOr, yystack_[2].value.as < pdm::ast::Exp* > (), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2822 "parser.tab.cc"
    break;

  case 131: // or_binary_exp: xor_binary_exp
#line 580 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2828 "parser.tab.cc"
    break;

  case 132: // or_binary_exp: or_binary_exp "or" xor_binary_exp
#line 581 "parser.yy"
                                           { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_binary_exp(yylhs.location, ast::BinaryOperator::Or, yystack_[2].value.as < pdm::ast::Exp* > (), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2834 "parser.tab.cc"
    break;

  case 133: // type_query_exp: binary_exp
#line 585 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2840 "parser.tab.cc"
    break;

  case 134: // type_query_exp: typespec type_query_op typespec
#line 586 "parser.yy"
                                        { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_type_query_exp(yylhs.location, yystack_[1].value.as < pdm::ast::TypeQueryKind > (), yystack_[2].value.as < pdm::ast::Typespec* > (), yystack_[0].value.as < pdm::ast::Typespec* > ()); }
#line 2846 "parser.tab.cc"
    break;

  case 135: // type_query_op: ":<"
#line 589 "parser.yy"
                    { yylhs.value.as < pdm::ast::TypeQueryKind > () = ast::TypeQueryKind::LhsSubtypesRhs; }
#line 2852 "parser.tab.cc"
    break;

  case 136: // type_query_op: ">:"
#line 590 "parser.yy"
                    { yylhs.value.as < pdm::ast::TypeQueryKind > () = ast::TypeQueryKind::LhsSupertypesRhs; }
#line 2858 "parser.tab.cc"
    break;

  case 137: // type_query_op: "::"
#line 591 "parser.yy"
                    { yylhs.value.as < pdm::ast::TypeQueryKind > () = ast::TypeQueryKind::LhsEqualsRhs; }
#line 2864 "parser.tab.cc"
    break;

  case 138: // typespec: unary_typespec
#line 599 "parser.yy"
      { yylhs.value.as < pdm::ast::Typespec* > () = yystack_[0].value.as < pdm::ast::Typespec* > (); }
#line 2870 "parser.tab.cc"
    break;

  case 139: // typespec_cl1: typespec
#line 602 "parser.yy"
                                  { yylhs.value.as < std::vector<pdm::ast::Typespec*> > ().push_back(yystack_[0].value.as < pdm::ast::Typespec* > ()); }
#line 2876 "parser.tab.cc"
    break;

  case 140: // typespec_cl1: typespec_cl1 "," typespec
#line 603 "parser.yy"
                                  { yylhs.value.as < std::vector<pdm::ast::Typespec*> > () = std::move(yystack_[2].value.as < std::vector<pdm::ast::Typespec*> > ()); yylhs.value.as < std::vector<pdm::ast::Typespec*> > ().push_back(yystack_[0].value.as < pdm::ast::Typespec* > ()); }
#line 2882 "parser.tab.cc"
    break;

  case 141: // typespec_cl2: typespec "," typespec
#line 606 "parser.yy"
                                  { yylhs.value.as < std::vector<pdm::ast::Typespec*> > ().reserve(2); yylhs.value.as < std::vector<pdm::ast::Typespec*> > ().push_back(yystack_[2].value.as < pdm::ast::Typespec* > ()); yylhs.value.as < std::vector<pdm::ast::Typespec*> > ().push_back(yystack_[0].value.as < pdm::ast::Typespec* > ()); }
#line 2888 "parser.tab.cc"
    break;

  case 142: // typespec_cl2: typespec_cl2 "," typespec
#line 607 "parser.yy"
                                  { yylhs.value.as < std::vector<pdm::ast::Typespec*> > () = std::move(yystack_[2].value.as < std::vector<pdm::ast::Typespec*> > ()); yylhs.value.as < std::vector<pdm::ast::Typespec*> > ().push_back(yystack_[0].value.as < pdm::ast::Typespec* > ()); }
#line 2894 "parser.tab.cc"
    break;

  case 143: // struct_typespec_field: vid typespec
#line 611 "parser.yy"
                                  { yylhs.value.as < pdm::ast::StructTypespec::Field* > () = mgr->new_struct_typespec_field(yylhs.location, yystack_[1].value.as < TokenInfo > ().ID_intstr, yystack_[0].value.as < pdm::ast::Typespec* > ()); }
#line 2900 "parser.tab.cc"
    break;

  case 144: // struct_typespec_field_cl: struct_typespec_field
#line 614 "parser.yy"
                                                          { yylhs.value.as < std::vector<pdm::ast::StructTypespec::Field*> > ().push_back(yystack_[0].value.as < pdm::ast::StructTypespec::Field* > ()); }
#line 2906 "parser.tab.cc"
    break;

  case 145: // struct_typespec_field_cl: struct_typespec_field_cl "," struct_typespec_field
#line 615 "parser.yy"
                                                            { yylhs.value.as < std::vector<pdm::ast::StructTypespec::Field*> > () = std::move(yystack_[2].value.as < std::vector<pdm::ast::StructTypespec::Field*> > ()); yylhs.value.as < std::vector<pdm::ast::StructTypespec::Field*> > ().push_back(yystack_[0].value.as < pdm::ast::StructTypespec::Field* > ()); }
#line 2912 "parser.tab.cc"
    break;

  case 146: // primary_typespec: tid
#line 619 "parser.yy"
                        { yylhs.value.as < pdm::ast::Typespec* > () = mgr->new_id_typespec(yylhs.location, yystack_[0].value.as < TokenInfo > ().ID_intstr); }
#line 2918 "parser.tab.cc"
    break;

  case 147: // primary_typespec: paren_typespec
#line 620 "parser.yy"
      { yylhs.value.as < pdm::ast::Typespec* > () = yystack_[0].value.as < pdm::ast::Typespec* > (); }
#line 2924 "parser.tab.cc"
    break;

  case 148: // primary_typespec: tuple_typespec
#line 621 "parser.yy"
      { yylhs.value.as < pdm::ast::Typespec* > () = yystack_[0].value.as < pdm::ast::Typespec* > (); }
#line 2930 "parser.tab.cc"
    break;

  case 149: // primary_typespec: mod_prefix_tid
#line 622 "parser.yy"
      { yylhs.value.as < pdm::ast::Typespec* > () = yystack_[0].value.as < pdm::ast::Typespec* > (); }
#line 2936 "parser.tab.cc"
    break;

  case 150: // primary_typespec: fn_typespec
#line 623 "parser.yy"
      { yylhs.value.as < pdm::ast::Typespec* > () = yystack_[0].value.as < pdm::ast::Typespec* > (); }
#line 2942 "parser.tab.cc"
    break;

  case 151: // paren_typespec: "(" typespec ")"
#line 626 "parser.yy"
                                { yylhs.value.as < pdm::ast::Typespec* > () = mgr->new_paren_typespec(yylhs.location, yystack_[1].value.as < pdm::ast::Typespec* > ()); }
#line 2948 "parser.tab.cc"
    break;

  case 152: // tuple_typespec: "(" typespec "," ")"
#line 629 "parser.yy"
                                    { yylhs.value.as < pdm::ast::Typespec* > () = mgr->new_tuple_typespec(yylhs.location, std::move(std::vector(1,yystack_[2].value.as < pdm::ast::Typespec* > ()))); }
#line 2954 "parser.tab.cc"
    break;

  case 153: // tuple_typespec: "(" typespec_cl2 ")"
#line 630 "parser.yy"
                                    { yylhs.value.as < pdm::ast::Typespec* > () = mgr->new_tuple_typespec(yylhs.location, std::move(yystack_[1].value.as < std::vector<pdm::ast::Typespec*> > ())); }
#line 2960 "parser.tab.cc"
    break;

  case 154: // mod_prefix_tid: mod_prefix tid
#line 633 "parser.yy"
                            { yylhs.value.as < pdm::ast::Typespec* > () = mgr->new_dot_name_typespec_with_mod_prefix(yylhs.location, std::move(yystack_[1].value.as < std::vector<pdm::intern::String> > ()), yystack_[0].value.as < TokenInfo > ().ID_intstr); }
#line 2966 "parser.tab.cc"
    break;

  case 155: // mod_prefix: vid "."
#line 636 "parser.yy"
                            { yylhs.value.as < std::vector<pdm::intern::String> > ().push_back(yystack_[1].value.as < TokenInfo > ().ID_intstr); }
#line 2972 "parser.tab.cc"
    break;

  case 156: // mod_prefix: mod_prefix vid "."
#line 637 "parser.yy"
                            { yylhs.value.as < std::vector<pdm::intern::String> > () = std::move(yystack_[2].value.as < std::vector<pdm::intern::String> > ()); }
#line 2978 "parser.tab.cc"
    break;

  case 157: // fn_typespec: "Fn" vpattern primary_typespec
#line 640 "parser.yy"
                                       { yylhs.value.as < pdm::ast::Typespec* > () = mgr->new_fn_typespec(yylhs.location, std::move(yystack_[1].value.as < pdm::ast::VPattern* > ()), yystack_[0].value.as < pdm::ast::Typespec* > ()); }
#line 2984 "parser.tab.cc"
    break;

  case 158: // postfix_typespec: primary_typespec
#line 644 "parser.yy"
      { yylhs.value.as < pdm::ast::Typespec* > () = yystack_[0].value.as < pdm::ast::Typespec* > (); }
#line 2990 "parser.tab.cc"
    break;

  case 159: // postfix_typespec: tcall_typespec
#line 645 "parser.yy"
      { yylhs.value.as < pdm::ast::Typespec* > () = yystack_[0].value.as < pdm::ast::Typespec* > (); }
#line 2996 "parser.tab.cc"
    break;

  case 160: // postfix_typespec: dot_typespec
#line 646 "parser.yy"
      { yylhs.value.as < pdm::ast::Typespec* > () = yystack_[0].value.as < pdm::ast::Typespec* > (); }
#line 3002 "parser.tab.cc"
    break;

  case 161: // tcall_typespec: postfix_typespec "[" targ_cl "]"
#line 649 "parser.yy"
                                              { yylhs.value.as < pdm::ast::Typespec* > () = mgr->new_tcall_typespec(yylhs.location, yystack_[3].value.as < pdm::ast::Typespec* > (), std::move(yystack_[1].value.as < std::vector<pdm::ast::TArg*> > ())); }
#line 3008 "parser.tab.cc"
    break;

  case 162: // dot_typespec: postfix_typespec "." "<val_id>"
#line 651 "parser.yy"
                                         { yylhs.value.as < pdm::ast::Typespec* > () = mgr->new_dot_name_typespec_with_type_prefix(yylhs.location, yystack_[2].value.as < pdm::ast::Typespec* > (), yystack_[0].value.as < TokenInfo > ().ID_intstr); }
#line 3014 "parser.tab.cc"
    break;

  case 163: // unary_typespec: postfix_typespec
#line 655 "parser.yy"
      { yylhs.value.as < pdm::ast::Typespec* > () = yystack_[0].value.as < pdm::ast::Typespec* > (); }
#line 3020 "parser.tab.cc"
    break;

  case 164: // long_typespec: unary_typespec
#line 659 "parser.yy"
      { yylhs.value.as < pdm::ast::Typespec* > () = yystack_[0].value.as < pdm::ast::Typespec* > (); }
#line 3026 "parser.tab.cc"
    break;

  case 165: // long_typespec: struct_typespec
#line 660 "parser.yy"
      { yylhs.value.as < pdm::ast::Typespec* > () = yystack_[0].value.as < pdm::ast::Typespec* > (); }
#line 3032 "parser.tab.cc"
    break;

  case 166: // struct_typespec: "{" struct_typespec_field_cl "}"
#line 663 "parser.yy"
                                              { yylhs.value.as < pdm::ast::Typespec* > () = mgr->new_struct_typespec(yylhs.location, std::move(yystack_[1].value.as < std::vector<pdm::ast::StructTypespec::Field*> > ())); }
#line 3038 "parser.tab.cc"
    break;

  case 167: // targ: typespec
#line 666 "parser.yy"
               { yylhs.value.as < pdm::ast::TArg* > () = mgr->new_targ_typespec(yylhs.location, yystack_[0].value.as < pdm::ast::Typespec* > ()); }
#line 3044 "parser.tab.cc"
    break;

  case 168: // targ: expr
#line 667 "parser.yy"
               { yylhs.value.as < pdm::ast::TArg* > () = mgr->new_targ_exp(yylhs.location, yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 3050 "parser.tab.cc"
    break;

  case 169: // targ_cl: targ
#line 670 "parser.yy"
                            { yylhs.value.as < std::vector<pdm::ast::TArg*> > ().push_back(yystack_[0].value.as < pdm::ast::TArg* > ()); }
#line 3056 "parser.tab.cc"
    break;

  case 170: // targ_cl: targ_cl "," targ
#line 671 "parser.yy"
                            { yylhs.value.as < std::vector<pdm::ast::TArg*> > () = std::move(yystack_[2].value.as < std::vector<pdm::ast::TArg*> > ()); yylhs.value.as < std::vector<pdm::ast::TArg*> > ().push_back(yystack_[0].value.as < pdm::ast::TArg* > ()); }
#line 3062 "parser.tab.cc"
    break;

  case 171: // varg: expr
#line 673 "parser.yy"
                            { yylhs.value.as < pdm::ast::VArg* > () = mgr->new_varg(yylhs.location, yystack_[0].value.as < pdm::ast::Exp* > (), ast::VArgKind::In); }
#line 3068 "parser.tab.cc"
    break;

  case 172: // varg: "out" expr
#line 674 "parser.yy"
                            { yylhs.value.as < pdm::ast::VArg* > () = mgr->new_varg(yylhs.location, yystack_[0].value.as < pdm::ast::Exp* > (), ast::VArgKind::Out); }
#line 3074 "parser.tab.cc"
    break;

  case 173: // varg: "inout" expr
#line 675 "parser.yy"
                            { yylhs.value.as < pdm::ast::VArg* > () = mgr->new_varg(yylhs.location, yystack_[0].value.as < pdm::ast::Exp* > (), ast::VArgKind::InOut); }
#line 3080 "parser.tab.cc"
    break;

  case 174: // varg_cl: varg
#line 678 "parser.yy"
                            { yylhs.value.as < std::vector<pdm::ast::VArg*> > ().push_back(yystack_[0].value.as < pdm::ast::VArg* > ()); }
#line 3086 "parser.tab.cc"
    break;

  case 175: // varg_cl: varg_cl "," varg
#line 679 "parser.yy"
                            { yylhs.value.as < std::vector<pdm::ast::VArg*> > () = std::move(yystack_[2].value.as < std::vector<pdm::ast::VArg*> > ()); yylhs.value.as < std::vector<pdm::ast::VArg*> > ().push_back(yystack_[0].value.as < pdm::ast::VArg* > ()); }
#line 3092 "parser.tab.cc"
    break;

  case 176: // struct_exp_field: vid "=" expr
#line 687 "parser.yy"
                    { yylhs.value.as < pdm::ast::StructExp::Field* > () = mgr->new_struct_exp_field(yylhs.location, yystack_[2].value.as < TokenInfo > ().ID_intstr, yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 3098 "parser.tab.cc"
    break;

  case 177: // vpattern_field: vid typespec
#line 690 "parser.yy"
                            { yylhs.value.as < pdm::ast::VPattern::Field* > () = mgr->new_vpattern_field(yylhs.location, yystack_[1].value.as < TokenInfo > ().ID_intstr, yystack_[0].value.as < pdm::ast::Typespec* > (), ast::VArgKind::In); }
#line 3104 "parser.tab.cc"
    break;

  case 178: // vpattern_field: "out" vid typespec
#line 691 "parser.yy"
                            { yylhs.value.as < pdm::ast::VPattern::Field* > () = mgr->new_vpattern_field(yylhs.location, yystack_[1].value.as < TokenInfo > ().ID_intstr, yystack_[0].value.as < pdm::ast::Typespec* > (), ast::VArgKind::Out); }
#line 3110 "parser.tab.cc"
    break;

  case 179: // vpattern_field: "inout" vid typespec
#line 692 "parser.yy"
                            { yylhs.value.as < pdm::ast::VPattern::Field* > () = mgr->new_vpattern_field(yylhs.location, yystack_[1].value.as < TokenInfo > ().ID_intstr, yystack_[0].value.as < pdm::ast::Typespec* > (), ast::VArgKind::InOut); }
#line 3116 "parser.tab.cc"
    break;

  case 180: // lpattern_field: vid typespec
#line 695 "parser.yy"
                    { yylhs.value.as < pdm::ast::LPattern::Field* > () = mgr->new_lpattern_field(yylhs.location, ast::LPattern::FieldKind::IdTypespecPair, yystack_[1].value.as < TokenInfo > ().ID_intstr, yystack_[0].value.as < pdm::ast::Typespec* > ()); }
#line 3122 "parser.tab.cc"
    break;

  case 181: // lpattern_field: vid
#line 696 "parser.yy"
                    { yylhs.value.as < pdm::ast::LPattern::Field* > () = mgr->new_lpattern_field(yylhs.location, ast::LPattern::FieldKind::IdSingleton, yystack_[0].value.as < TokenInfo > ().ID_intstr); }
#line 3128 "parser.tab.cc"
    break;

  case 182: // tpattern_field: vid typespec
#line 699 "parser.yy"
                    { yylhs.value.as < pdm::ast::TPattern::Field* > () = mgr->new_tpattern_field(yylhs.location, ast::TPattern::FieldKind::Value, yystack_[1].value.as < TokenInfo > ().ID_intstr, yystack_[0].value.as < pdm::ast::Typespec* > ()); }
#line 3134 "parser.tab.cc"
    break;

  case 183: // tpattern_field: tid typespec
#line 700 "parser.yy"
                    { yylhs.value.as < pdm::ast::TPattern::Field* > () = mgr->new_tpattern_field(yylhs.location, ast::TPattern::FieldKind::Type, yystack_[1].value.as < TokenInfo > ().ID_intstr, yystack_[0].value.as < pdm::ast::Typespec* > ()); }
#line 3140 "parser.tab.cc"
    break;

  case 184: // lpattern: "(" lpattern_field_cl ")"
#line 704 "parser.yy"
                                       { yylhs.value.as < pdm::ast::LPattern* > () = mgr->new_lpattern(yylhs.location, std::move(yystack_[1].value.as < std::vector<pdm::ast::LPattern::Field*> > ())); }
#line 3146 "parser.tab.cc"
    break;

  case 185: // lpattern: "(" ")"
#line 705 "parser.yy"
                                       { yylhs.value.as < pdm::ast::LPattern* > () = mgr->new_lpattern(yylhs.location, std::move(std::vector<ast::LPattern::Field*>{})); }
#line 3152 "parser.tab.cc"
    break;

  case 186: // lpattern_naked: lpattern_field
#line 708 "parser.yy"
                                       { yylhs.value.as < pdm::ast::LPattern* > () = mgr->new_lpattern(yylhs.location, std::move(std::vector<ast::LPattern::Field*>{1,yystack_[0].value.as < pdm::ast::LPattern::Field* > ()})); }
#line 3158 "parser.tab.cc"
    break;

  case 187: // lpattern_naked: lpattern
#line 709 "parser.yy"
      { yylhs.value.as < pdm::ast::LPattern* > () = yystack_[0].value.as < pdm::ast::LPattern* > (); }
#line 3164 "parser.tab.cc"
    break;

  case 188: // vpattern: "(" vpattern_field_cl ")"
#line 712 "parser.yy"
                                       { yylhs.value.as < pdm::ast::VPattern* > () = mgr->new_vpattern(yylhs.location, std::move(yystack_[1].value.as < std::vector<pdm::ast::VPattern::Field*> > ())); }
#line 3170 "parser.tab.cc"
    break;

  case 189: // vpattern: "(" ")"
#line 713 "parser.yy"
                                      { yylhs.value.as < pdm::ast::VPattern* > () = mgr->new_vpattern(yylhs.location, std::move(std::vector<ast::VPattern::Field*>{})); }
#line 3176 "parser.tab.cc"
    break;

  case 190: // tpattern: "[" tpattern_field_cl "]"
#line 716 "parser.yy"
                                               { yylhs.value.as < pdm::ast::TPattern* > () = mgr->new_tpattern(yylhs.location, std::move(yystack_[1].value.as < std::vector<pdm::ast::TPattern::Field*> > ()), false); }
#line 3182 "parser.tab.cc"
    break;

  case 191: // tpattern: "!" "[" tpattern_field_cl "]"
#line 717 "parser.yy"
                                               { yylhs.value.as < pdm::ast::TPattern* > () = mgr->new_tpattern(yylhs.location, std::move(yystack_[1].value.as < std::vector<pdm::ast::TPattern::Field*> > ()), true); }
#line 3188 "parser.tab.cc"
    break;

  case 192: // vpattern_field_cl: vpattern_field
#line 721 "parser.yy"
                                              { yylhs.value.as < std::vector<pdm::ast::VPattern::Field*> > ().push_back(yystack_[0].value.as < pdm::ast::VPattern::Field* > ()); }
#line 3194 "parser.tab.cc"
    break;

  case 193: // vpattern_field_cl: vpattern_field_cl "," vpattern_field
#line 722 "parser.yy"
                                               { yylhs.value.as < std::vector<pdm::ast::VPattern::Field*> > () = std::move(yystack_[2].value.as < std::vector<pdm::ast::VPattern::Field*> > ()); yylhs.value.as < std::vector<pdm::ast::VPattern::Field*> > ().push_back(yystack_[0].value.as < pdm::ast::VPattern::Field* > ()); }
#line 3200 "parser.tab.cc"
    break;

  case 194: // lpattern_field_cl: lpattern_field
#line 725 "parser.yy"
                                              { yylhs.value.as < std::vector<pdm::ast::LPattern::Field*> > ().push_back(yystack_[0].value.as < pdm::ast::LPattern::Field* > ()); }
#line 3206 "parser.tab.cc"
    break;

  case 195: // lpattern_field_cl: lpattern_field_cl "," lpattern_field
#line 726 "parser.yy"
                                               { yylhs.value.as < std::vector<pdm::ast::LPattern::Field*> > () = std::move(yystack_[2].value.as < std::vector<pdm::ast::LPattern::Field*> > ()); yylhs.value.as < std::vector<pdm::ast::LPattern::Field*> > ().push_back(yystack_[0].value.as < pdm::ast::LPattern::Field* > ()); }
#line 3212 "parser.tab.cc"
    break;

  case 196: // tpattern_field_cl: tpattern_field
#line 729 "parser.yy"
                                              { yylhs.value.as < std::vector<pdm::ast::TPattern::Field*> > ().push_back(yystack_[0].value.as < pdm::ast::TPattern::Field* > ()); }
#line 3218 "parser.tab.cc"
    break;

  case 197: // tpattern_field_cl: tpattern_field_cl "," tpattern_field
#line 730 "parser.yy"
                                               { yylhs.value.as < std::vector<pdm::ast::TPattern::Field*> > () = std::move(yystack_[2].value.as < std::vector<pdm::ast::TPattern::Field*> > ()); yylhs.value.as < std::vector<pdm::ast::TPattern::Field*> > ().push_back(yystack_[0].value.as < pdm::ast::TPattern::Field* > ()); }
#line 3224 "parser.tab.cc"
    break;

  case 198: // struct_exp_field_cl: struct_exp_field
#line 733 "parser.yy"
                                                    { yylhs.value.as < std::vector<pdm::ast::StructExp::Field*> > ().push_back(yystack_[0].value.as < pdm::ast::StructExp::Field* > ()); }
#line 3230 "parser.tab.cc"
    break;

  case 199: // struct_exp_field_cl: struct_exp_field_cl "," struct_exp_field
#line 734 "parser.yy"
                                                    { yylhs.value.as < std::vector<pdm::ast::StructExp::Field*> > () = std::move(yystack_[2].value.as < std::vector<pdm::ast::StructExp::Field*> > ()); yylhs.value.as < std::vector<pdm::ast::StructExp::Field*> > ().push_back(yystack_[0].value.as < pdm::ast::StructExp::Field* > ()); }
#line 3236 "parser.tab.cc"
    break;

  case 200: // tpattern_seq: tpattern
#line 738 "parser.yy"
                             { yylhs.value.as < std::vector<pdm::ast::TPattern*> > ().push_back(yystack_[0].value.as < pdm::ast::TPattern* > ()); }
#line 3242 "parser.tab.cc"
    break;

  case 201: // tpattern_seq: tpattern_seq tpattern
#line 739 "parser.yy"
                             { yylhs.value.as < std::vector<pdm::ast::TPattern*> > () = std::move(yystack_[1].value.as < std::vector<pdm::ast::TPattern*> > ()); yylhs.value.as < std::vector<pdm::ast::TPattern*> > ().push_back(yystack_[0].value.as < pdm::ast::TPattern* > ()); }
#line 3248 "parser.tab.cc"
    break;


#line 3252 "parser.tab.cc"

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





  const short parser::yypact_ninf_ = -172;

  const short parser::yytable_ninf_ = -134;

  const short
  parser::yypact_[] =
  {
      62,    51,    71,    62,    48,  -172,    80,  -172,   105,  -172,
     201,  -172,    83,   138,   138,   138,   151,   151,   151,  -172,
     126,   114,  -172,  -172,  -172,  -172,  -172,  -172,  -172,   366,
      14,  -172,  -172,  -172,  -172,  -172,  -172,  -172,   142,   171,
      59,  -172,    88,     7,   148,  -172,   167,  -172,    83,   181,
     181,  -172,  -172,  -172,  -172,  -172,  -172,   366,  -172,  -172,
    -172,  -172,  -172,  -172,   195,  -172,   203,   127,  -172,  -172,
    -172,   -14,  -172,  -172,   115,  -172,  -172,  -172,  -172,  -172,
     596,   191,    67,    45,   207,    68,   219,   229,   244,   230,
     -27,  -172,  -172,  -172,  -172,   261,  -172,    -1,  -172,  -172,
    -172,    20,    20,    20,   596,  -172,   240,  -172,  -172,  -172,
    -172,  -172,   228,   245,   144,  -172,  -172,    61,   232,   596,
      53,   261,   243,   -33,  -172,    59,    77,   140,   151,  -172,
     231,  -172,   254,   151,  -172,   287,   242,   102,   128,   146,
    -172,   505,   596,  -172,  -172,  -172,    12,   402,   437,  -172,
    -172,  -172,  -172,  -172,   596,  -172,  -172,   596,  -172,  -172,
    -172,  -172,   596,  -172,  -172,   596,   596,   596,   596,  -172,
    -172,  -172,  -172,   102,  -172,   264,   294,   437,    16,   102,
    -172,  -172,   246,   247,   248,   253,  -172,   596,  -172,  -172,
     272,   267,   138,  -172,  -172,  -172,   293,  -172,   138,   138,
    -172,   102,  -172,   149,   102,   102,  -172,    40,   261,   102,
      83,   -29,  -172,   102,   138,   195,  -172,  -172,  -172,    77,
     231,   151,    47,   102,    83,    83,  -172,    69,  -172,   102,
    -172,  -172,  -172,  -172,  -172,  -172,  -172,  -172,   596,   596,
    -172,  -172,  -172,   190,  -172,  -172,  -172,    91,  -172,    67,
      45,   207,    68,   219,   229,  -172,  -172,  -172,   129,  -172,
    -172,   204,  -172,   596,   596,   596,   596,  -172,  -172,  -172,
     228,  -172,   232,   102,   102,  -172,    34,  -172,  -172,  -172,
     261,  -172,   165,   259,  -172,   102,    83,   206,   102,  -172,
      74,  -172,  -172,  -172,  -172,   211,   266,   315,  -172,  -172,
    -172,  -172,  -172,  -172,   471,  -172,   437,  -172,  -172,   138,
    -172,  -172,  -172,  -172,  -172,  -172,  -172,  -172,  -172,  -172,
    -172,    83,   269,  -172,  -172,   138,  -172,   102,  -172,   177,
     304,  -172,  -172,  -172,  -172,    83,  -172,  -172,   282,   183,
    -172,  -172,   596,   283,   290,   540,   596,  -172,  -172,   291,
     574,  -172,  -172
  };

  const unsigned char
  parser::yydefact_[] =
  {
       0,     0,     0,     2,     0,     5,     0,     1,     0,     3,
       0,     4,     0,     0,     0,     0,     0,     0,     0,    24,
       0,     0,    19,    20,    21,    22,    25,    23,    26,     0,
       0,    43,    56,    57,    58,    59,    60,    47,     0,     0,
       0,    46,     0,     0,     0,     6,     0,     7,     0,     0,
       0,   106,    74,    75,    48,    77,    76,     0,    61,   104,
     102,   103,   105,   146,    68,    70,     0,     0,    67,    88,
      69,    71,    72,    73,   100,    89,    90,    91,    92,   111,
       0,    51,   115,   121,   125,   127,   129,   131,   107,     0,
       0,   158,   147,   148,   149,     0,   150,   163,   159,   160,
     138,     0,     0,     0,     0,    62,     0,     9,    10,    11,
      12,    13,    68,    18,     0,    51,   198,     0,     0,     0,
       0,     0,     0,     0,   200,     0,     0,     0,     0,    33,
      35,    36,    38,     0,     8,     0,     0,     0,     0,     0,
     155,     0,     0,    65,    79,    78,     0,     0,     0,    68,
     101,   108,   109,   110,     0,   113,   114,     0,   117,   118,
     119,   120,     0,   123,   124,     0,     0,     0,     0,    63,
     137,   135,   136,     0,   154,     0,     0,     0,     0,   181,
     186,   187,     0,     0,     0,     0,    85,     0,    82,    83,
       0,    18,     0,    66,    50,    49,     0,    45,     0,     0,
     189,     0,   192,     0,     0,     0,   196,     0,     0,     0,
       0,     0,   201,     0,     0,     0,   164,    31,   165,     0,
      34,     0,     0,     0,     0,     0,   157,     0,   151,     0,
     153,    64,    52,    53,    96,    97,    99,    98,     0,     0,
      94,   171,   174,     0,   168,   167,   169,     0,   112,   116,
     122,   126,   128,   130,   132,   134,   156,   162,     0,   185,
     194,     0,   180,     0,     0,     0,     0,   176,    86,    84,
       0,   199,     0,     0,     0,   177,     0,   188,   183,   182,
       0,   190,     0,     0,    29,     0,     0,     0,     0,   144,
       0,    32,    37,    39,   139,     0,     0,    80,    87,   152,
     141,   142,   172,   173,     0,    95,     0,    93,   161,     0,
     184,    14,    15,    16,    17,    44,   178,   179,   193,   197,
     191,     0,     0,    30,   143,     0,   166,     0,    40,     0,
       0,   175,   170,   195,    27,     0,   145,   140,     0,     0,
      81,    28,     0,     0,     0,     0,     0,    54,    41,     0,
       0,    55,    42
  };

  const short
  parser::yypgoto_[] =
  {
    -172,  -172,  -172,   329,    57,  -172,   226,  -172,  -172,  -172,
    -172,  -172,   313,  -172,  -172,  -172,  -172,   213,   121,  -172,
    -172,  -172,  -172,     9,    79,  -172,    72,   -28,  -172,    -3,
     -12,  -172,  -172,  -172,  -172,    17,   200,  -172,  -172,  -172,
    -172,  -172,  -172,  -172,  -172,  -172,  -172,   -75,  -172,   -17,
    -172,   193,  -172,   186,  -172,   189,  -172,   185,   194,   188,
    -172,  -172,  -172,    46,  -172,  -172,    32,  -172,   221,  -172,
    -172,  -172,  -172,  -172,  -172,  -172,  -172,  -118,   141,  -172,
      56,   198,    64,  -172,   173,    87,  -171,    86,  -172,   179,
     -40,  -121,  -172,  -172,   163,  -172,   -39
  };

  const short
  parser::yydefgoto_[] =
  {
      -1,     2,     3,     4,     5,    20,   106,   107,   108,   109,
     110,   111,    21,    22,    23,    24,   129,   130,   131,    25,
      26,    27,    28,    63,   149,    65,   196,   244,    67,   345,
      68,    32,    33,    34,    35,    69,    70,    71,    72,    36,
     114,    73,    74,    75,    76,    77,    78,    79,    80,   115,
     154,    82,   157,    83,   162,    84,   165,    85,    86,    87,
      88,    89,   173,   245,   295,   139,   289,   290,    91,    92,
      93,    94,    95,    96,    97,    98,    99,   100,   217,   218,
     246,   247,   242,   243,   116,   202,   180,   206,   181,   182,
     123,   124,   203,   261,   207,   117,   125
  };

  const short
  parser::yytable_[] =
  {
      31,    66,   113,   127,   212,   150,   212,   260,   216,   136,
     137,    41,    81,   170,   209,   234,   235,    37,   285,    37,
     144,   145,    48,    37,   210,    42,    43,    44,   286,    66,
     101,   102,   103,   104,    49,   176,   135,    37,   171,   172,
      81,    51,   177,    52,    53,    52,    53,    54,    55,    56,
      37,    41,   132,    29,     6,    29,    37,    30,   259,    30,
     105,   178,    59,   198,   199,    60,    61,    19,    50,     1,
     128,     7,    37,    41,    62,    90,   185,    19,   280,   248,
      37,    41,   198,   199,   281,   211,   191,     9,   213,   293,
      50,   197,    38,    39,    40,   200,   155,   156,    50,   192,
     120,   216,   121,   138,   174,    37,    41,   193,    64,   112,
     213,   299,   325,   232,   233,   151,   152,   153,   213,   241,
     326,   122,   214,    50,    29,    10,   163,   164,    30,   306,
     204,   121,    12,     1,   236,   307,    64,   132,   333,    13,
      14,    37,   223,   213,    11,   126,    15,    37,    16,    17,
     122,   146,    48,    47,    18,    41,   147,   118,   148,   267,
     101,   102,   103,   104,    49,   142,   227,   306,   170,   143,
     228,    51,    45,   308,   175,    52,    53,    54,    55,    56,
     179,   179,   179,   121,   229,    29,   119,   276,   230,    30,
     189,   277,    59,   171,   172,    60,    61,   219,   284,   201,
     205,   133,   122,   280,    62,   215,   134,    12,     1,   320,
     302,   303,   297,   298,    13,    14,   215,   204,   212,   255,
     121,    15,   120,    16,    17,   262,   121,    64,   304,    18,
     132,   140,   305,  -133,   338,   311,   312,   313,   314,   122,
     343,   141,   309,   166,   227,   122,   310,   275,   228,   327,
     278,   279,   215,   328,   167,   283,    64,   179,   215,   287,
     158,   159,   160,   161,    37,    41,   194,   195,   294,   296,
     168,   270,   169,   300,   323,   301,   241,   273,   274,   186,
     215,   183,   184,   215,   215,   187,   208,   205,   215,   204,
     339,   188,   215,   288,   221,   222,   224,   257,   215,   225,
     256,   215,   215,   263,   264,   265,   215,    37,   215,   334,
     266,   268,    48,   269,   344,   272,   321,   349,   344,   316,
     317,   329,   349,   341,    49,   330,   335,   342,   346,   347,
     351,   322,     8,    46,   324,    52,    53,    54,    55,    56,
     190,   220,   292,   350,   315,    29,   237,   340,   250,    30,
     249,   252,   215,   215,   251,   201,   254,   336,   226,   205,
     291,   253,   332,   318,   215,   271,   319,   215,   331,    37,
      41,   282,     0,   337,    48,   258,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    64,    49,    50,   179,     0,
       0,     0,     0,    51,     0,     0,     0,    52,    53,    54,
      55,    56,     0,     0,   288,    37,   215,    57,    58,     0,
      48,    30,     0,     0,    59,     0,     0,    60,    61,     0,
       0,     0,    49,     0,     0,     0,    62,     0,     0,    51,
       0,   238,   239,    52,    53,    54,    55,    56,     0,     0,
      37,    41,     0,    29,   240,    48,     0,    30,     0,     0,
      59,     0,     0,    60,    61,     0,     0,    49,    50,     0,
       0,     0,    62,     0,    51,     0,     0,     0,    52,    53,
      54,    55,    56,     0,    37,     0,     0,     0,    57,    48,
       0,     0,    30,     0,     0,    59,     0,     0,    60,    61,
       0,    49,     0,     0,     0,     0,     0,    62,    51,     0,
     238,   239,    52,    53,    54,    55,    56,     0,    37,     0,
       0,     0,    29,    48,     0,     0,    30,     0,     0,    59,
       0,     0,    60,    61,     0,    49,     0,     0,     0,     0,
       0,    62,    51,     0,     0,     0,    52,    53,    54,    55,
      56,     0,     0,    37,     0,     0,    29,   231,    48,     0,
      30,     0,     0,    59,     0,     0,    60,    61,     0,     0,
      49,     0,     0,     0,     0,    62,     0,    51,     0,     0,
       0,    52,    53,    54,    55,    56,     0,    37,     0,     0,
       0,    29,    48,     0,     0,    30,   348,     0,    59,     0,
       0,    60,    61,     0,    49,     0,     0,     0,     0,    37,
      62,    51,     0,     0,    48,    52,    53,    54,    55,    56,
       0,     0,     0,     0,     0,    29,    49,     0,     0,    30,
     352,     0,    59,    51,     0,    60,    61,    52,    53,    54,
      55,    56,     0,     0,    62,     0,     0,    29,     0,     0,
       0,    30,     0,     0,    59,     0,     0,    60,    61,     0,
       0,     0,     0,     0,     0,     0,    62
  };

  const short
  parser::yycheck_[] =
  {
      12,    29,    30,    42,   125,    80,   127,   178,   126,    49,
      50,     4,    29,    40,    47,     3,     4,     3,    47,     3,
      34,    35,     8,     3,    57,    16,    17,    18,    57,    57,
      16,    17,    18,    19,    20,    36,    48,     3,    65,    66,
      57,    27,    43,    31,    32,    31,    32,    33,    34,    35,
       3,     4,    43,    41,     3,    41,     3,    45,    42,    45,
      46,    41,    48,    29,    30,    51,    52,    10,    21,     7,
      63,     0,     3,     4,    60,    29,   104,    20,    38,   154,
       3,     4,    29,    30,    44,   125,   114,    39,    41,    42,
      21,   119,    13,    14,    15,    42,    51,    52,    21,    38,
      41,   219,    43,    57,    95,     3,     4,    46,    29,    30,
      41,    42,    38,   141,   142,    48,    49,    50,    41,   147,
      46,    62,    45,    21,    41,    45,    58,    59,    45,    38,
     121,    43,     6,     7,   146,    44,    57,   128,   309,    13,
      14,     3,   133,    41,    39,    57,    20,     3,    22,    23,
      62,    36,     8,    39,    28,     4,    41,    15,    43,   187,
      16,    17,    18,    19,    20,    38,    38,    38,    40,    42,
      42,    27,    46,    44,    95,    31,    32,    33,    34,    35,
     101,   102,   103,    43,    38,    41,    15,    38,    42,    45,
      46,    42,    48,    65,    66,    51,    52,    57,   210,   120,
     121,    53,    62,    38,    60,   126,    39,     6,     7,    44,
     238,   239,   224,   225,    13,    14,   137,   208,   339,   173,
      43,    20,    41,    22,    23,   179,    43,   148,    38,    28,
     221,    36,    42,    42,    57,   263,   264,   265,   266,    62,
      57,    38,    38,    24,    38,    62,    42,   201,    42,    38,
     204,   205,   173,    42,    25,   209,   177,   178,   179,   213,
      53,    54,    55,    56,     3,     4,    34,    35,   222,   223,
      26,   192,    42,   227,   286,   229,   304,   198,   199,    39,
     201,   102,   103,   204,   205,    57,    43,   208,   209,   280,
     329,    46,   213,   214,    63,    41,     9,     3,   219,    57,
      36,   222,   223,    57,    57,    57,   227,     3,   229,   321,
      57,    39,     8,    46,   342,    22,    57,   345,   346,   273,
     274,    55,   350,   335,    20,    10,    57,    45,    45,    39,
      39,   285,     3,    20,   288,    31,    32,    33,    34,    35,
     114,   128,   221,   346,   272,    41,   146,   330,   162,    45,
     157,   166,   273,   274,   165,   276,   168,   325,   137,   280,
     219,   167,   306,   276,   285,   192,   280,   288,   304,     3,
       4,   208,    -1,   327,     8,   177,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   306,    20,    21,   309,    -1,
      -1,    -1,    -1,    27,    -1,    -1,    -1,    31,    32,    33,
      34,    35,    -1,    -1,   325,     3,   327,    41,    42,    -1,
       8,    45,    -1,    -1,    48,    -1,    -1,    51,    52,    -1,
      -1,    -1,    20,    -1,    -1,    -1,    60,    -1,    -1,    27,
      -1,    29,    30,    31,    32,    33,    34,    35,    -1,    -1,
       3,     4,    -1,    41,    42,     8,    -1,    45,    -1,    -1,
      48,    -1,    -1,    51,    52,    -1,    -1,    20,    21,    -1,
      -1,    -1,    60,    -1,    27,    -1,    -1,    -1,    31,    32,
      33,    34,    35,    -1,     3,    -1,    -1,    -1,    41,     8,
      -1,    -1,    45,    -1,    -1,    48,    -1,    -1,    51,    52,
      -1,    20,    -1,    -1,    -1,    -1,    -1,    60,    27,    -1,
      29,    30,    31,    32,    33,    34,    35,    -1,     3,    -1,
      -1,    -1,    41,     8,    -1,    -1,    45,    -1,    -1,    48,
      -1,    -1,    51,    52,    -1,    20,    -1,    -1,    -1,    -1,
      -1,    60,    27,    -1,    -1,    -1,    31,    32,    33,    34,
      35,    -1,    -1,     3,    -1,    -1,    41,    42,     8,    -1,
      45,    -1,    -1,    48,    -1,    -1,    51,    52,    -1,    -1,
      20,    -1,    -1,    -1,    -1,    60,    -1,    27,    -1,    -1,
      -1,    31,    32,    33,    34,    35,    -1,     3,    -1,    -1,
      -1,    41,     8,    -1,    -1,    45,    46,    -1,    48,    -1,
      -1,    51,    52,    -1,    20,    -1,    -1,    -1,    -1,     3,
      60,    27,    -1,    -1,     8,    31,    32,    33,    34,    35,
      -1,    -1,    -1,    -1,    -1,    41,    20,    -1,    -1,    45,
      46,    -1,    48,    27,    -1,    51,    52,    31,    32,    33,
      34,    35,    -1,    -1,    60,    -1,    -1,    41,    -1,    -1,
      -1,    45,    -1,    -1,    48,    -1,    -1,    51,    52,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    60
  };

  const unsigned char
  parser::yystos_[] =
  {
       0,     7,    69,    70,    71,    72,     3,     0,    71,    39,
      45,    39,     6,    13,    14,    20,    22,    23,    28,    72,
      73,    80,    81,    82,    83,    87,    88,    89,    90,    41,
      45,    98,    99,   100,   101,   102,   107,     3,    92,    92,
      92,     4,    91,    91,    91,    46,    80,    39,     8,    20,
      21,    27,    31,    32,    33,    34,    35,    41,    42,    48,
      51,    52,    60,    91,    92,    93,    95,    96,    98,   103,
     104,   105,   106,   109,   110,   111,   112,   113,   114,   115,
     116,   117,   119,   121,   123,   125,   126,   127,   128,   129,
     131,   136,   137,   138,   139,   140,   141,   142,   143,   144,
     145,    16,    17,    18,    19,    46,    74,    75,    76,    77,
      78,    79,    92,    95,   108,   117,   152,   163,    15,    15,
      41,    43,    62,   158,   159,   164,    57,   164,    63,    84,
      85,    86,    91,    53,    39,    98,   158,   158,   131,   133,
      36,    38,    38,    42,    34,    35,    36,    41,    43,    92,
     115,    48,    49,    50,   118,    51,    52,   120,    53,    54,
      55,    56,   122,    58,    59,   124,    24,    25,    26,    42,
      40,    65,    66,   130,    91,    92,    36,    43,    41,    92,
     154,   156,   157,   157,   157,    95,    39,    57,    46,    46,
      74,    95,    38,    46,    34,    35,    94,    95,    29,    30,
      42,    92,   153,   160,    91,    92,   155,   162,    43,    47,
      57,   158,   159,    41,    45,    92,   145,   146,   147,    57,
      85,    63,    41,    91,     9,    57,   136,    38,    42,    38,
      42,    42,    95,    95,     3,     4,    98,   104,    29,    30,
      42,    95,   150,   151,    95,   131,   148,   149,   115,   119,
     121,   123,   125,   126,   127,   131,    36,     3,   149,    42,
     154,   161,   131,    57,    57,    57,    57,    95,    39,    46,
      92,   152,    22,    92,    92,   131,    38,    42,   131,   131,
      38,    44,   162,   131,    98,    47,    57,   131,    92,   134,
     135,   146,    86,    42,   131,   132,   131,    98,    98,    42,
     131,   131,    95,    95,    38,    42,    38,    44,    44,    38,
      42,    95,    95,    95,    95,    94,   131,   131,   153,   155,
      44,    57,   131,    98,   131,    38,    46,    38,    42,    55,
      10,   150,   148,   154,    98,    57,   134,   131,    57,   164,
     103,    98,    45,    57,    95,    97,    45,    39,    46,    95,
      97,    39,    46
  };

  const unsigned char
  parser::yyr1_[] =
  {
       0,    68,    69,    70,    70,    71,    72,    73,    73,    74,
      74,    74,    74,    74,    75,    76,    77,    78,    79,    80,
      80,    80,    80,    80,    80,    80,    80,    81,    81,    81,
      81,    82,    82,    83,    84,    84,    85,    85,    86,    86,
      86,    87,    87,    88,    89,    90,    91,    92,    93,    94,
      94,    95,    96,    96,    97,    97,    98,    98,    98,    98,
      98,    99,    99,   100,   101,   101,   102,   103,   103,   103,
     103,   103,   103,   103,   104,   104,   105,   105,   105,   105,
     106,   106,   107,   107,   107,   108,   108,   109,   110,   110,
     110,   110,   110,   111,   112,   112,   113,   113,   114,   114,
     115,   115,   116,   116,   116,   116,   116,   117,   118,   118,
     118,   119,   119,   120,   120,   121,   121,   122,   122,   122,
     122,   123,   123,   124,   124,   125,   125,   126,   126,   127,
     127,   128,   128,   129,   129,   130,   130,   130,   131,   132,
     132,   133,   133,   134,   135,   135,   136,   136,   136,   136,
     136,   137,   138,   138,   139,   140,   140,   141,   142,   142,
     142,   143,   144,   145,   146,   146,   147,   148,   148,   149,
     149,   150,   150,   150,   151,   151,   152,   153,   153,   153,
     154,   154,   155,   155,   156,   156,   157,   157,   158,   158,
     159,   159,   160,   160,   161,   161,   162,   162,   163,   163,
     164,   164
  };

  const signed char
  parser::yyr2_[] =
  {
       0,     2,     1,     2,     3,     1,     5,     2,     3,     1,
       1,     1,     1,     1,     4,     4,     4,     4,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     7,     8,     5,
       6,     4,     5,     3,     2,     1,     1,     3,     1,     3,
       4,    10,    11,     2,     6,     4,     1,     1,     1,     1,
       1,     1,     3,     3,     2,     3,     1,     1,     1,     1,
       1,     2,     2,     3,     4,     3,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     2,     2,
       4,     6,     3,     3,     4,     2,     3,     4,     1,     1,
       1,     1,     1,     4,     3,     4,     3,     3,     3,     3,
       1,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     3,     1,     1,     1,     3,     1,     1,     1,
       1,     1,     3,     1,     1,     1,     3,     1,     3,     1,
       3,     1,     3,     1,     3,     1,     1,     1,     1,     1,
       3,     3,     3,     2,     1,     3,     1,     1,     1,     1,
       1,     3,     4,     3,     2,     2,     3,     3,     1,     1,
       1,     4,     3,     1,     1,     1,     3,     1,     1,     1,
       3,     1,     2,     2,     1,     3,     3,     2,     3,     3,
       2,     1,     2,     2,     3,     2,     1,     1,     3,     2,
       3,     4,     1,     3,     1,     3,     1,     3,     1,     3,
       1,     2
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
  "\"fn\"", "\"Fn\"", "\"type\"", "\"enum\"", "\"and\"", "\"xor\"",
  "\"or\"", "\"not\"", "\"typeclass\"", "\"out\"", "\"inout\"", "\"42\"",
  "\"0x2a\"", "\"4.2\"", "\"\\\"dq-string-literal\\\"\"",
  "\"'sq-string-literal'\"", "\".\"", "\":\"", "\",\"", "\";\"", "\"::\"",
  "\"(\"", "\")\"", "\"[\"", "\"]\"", "\"{\"", "\"}\"", "\"->\"", "\"*\"",
  "\"/\"", "\"%\"", "\"+\"", "\"-\"", "\"<\"", "\"<=\"", "\">\"", "\">=\"",
  "\"=\"", "\"==\"", "\"!=\"", "\"^\"", "\"&\"", "\"!\"", "\"|\"",
  "\"EOS\"", "\":<\"", "\">:\"", "\"<null>\"", "$accept", "script",
  "scriptContent", "scriptContentStmt", "mod_stmt", "moduleContent",
  "chain_prefix_stmt", "const_stmt", "val_stmt", "var_stmt", "set_stmt",
  "discard_stmt", "moduleContentStmt", "fn_stmt", "type_stmt", "enum_stmt",
  "enum_field_pl", "unprefixed_enum_field_pl", "enum_field",
  "typeclass_stmt", "using_stmt", "importStmt", "extern_stmt", "tid",
  "vid", "floatl", "stringl", "expr", "expr_cl2", "expr_sl",
  "bracketed_exp", "unit_exp", "paren_exp", "vtupleExpr", "vstructExpr",
  "primary_exp", "int_expr", "stringls", "if_exp", "chain_exp",
  "chain_prefix", "lambda_exp", "postfix_exp", "tcall_exp", "vcall_exp",
  "dot_name_exp", "dot_index_exp", "unary_exp", "unary_op", "binary_exp",
  "mul_binary_op", "mul_binary_exp", "add_binary_op", "add_binary_exp",
  "cmp_binary_op", "cmp_binary_exp", "eq_binary_op", "eq_binary_exp",
  "and_binary_exp", "xor_binary_exp", "or_binary_exp", "type_query_exp",
  "type_query_op", "typespec", "typespec_cl1", "typespec_cl2",
  "struct_typespec_field", "struct_typespec_field_cl", "primary_typespec",
  "paren_typespec", "tuple_typespec", "mod_prefix_tid", "mod_prefix",
  "fn_typespec", "postfix_typespec", "tcall_typespec", "dot_typespec",
  "unary_typespec", "long_typespec", "struct_typespec", "targ", "targ_cl",
  "varg", "varg_cl", "struct_exp_field", "vpattern_field",
  "lpattern_field", "tpattern_field", "lpattern", "lpattern_naked",
  "vpattern", "tpattern", "vpattern_field_cl", "lpattern_field_cl",
  "tpattern_field_cl", "struct_exp_field_cl", "tpattern_seq", YY_NULLPTR
  };
#endif


#if YYDEBUG
  const short
  parser::yyrline_[] =
  {
       0,   302,   302,   305,   306,   309,   317,   320,   321,   329,
     330,   331,   332,   333,   336,   339,   342,   345,   348,   352,
     353,   354,   355,   356,   357,   358,   359,   362,   363,   364,
     365,   368,   369,   372,   375,   376,   379,   380,   383,   384,
     385,   388,   391,   397,   401,   405,   412,   413,   415,   418,
     419,   426,   433,   434,   437,   438,   442,   443,   444,   445,
     446,   449,   450,   453,   456,   457,   460,   463,   464,   465,
     466,   467,   468,   469,   472,   473,   476,   477,   478,   479,
     482,   483,   486,   487,   488,   491,   492,   495,   499,   500,
     501,   502,   503,   506,   509,   510,   513,   514,   517,   518,
     522,   523,   526,   527,   528,   529,   530,   534,   537,   538,
     539,   542,   543,   546,   547,   550,   551,   554,   555,   556,
     557,   560,   561,   564,   565,   568,   569,   572,   573,   576,
     577,   580,   581,   585,   586,   589,   590,   591,   599,   602,
     603,   606,   607,   611,   614,   615,   619,   620,   621,   622,
     623,   626,   629,   630,   633,   636,   637,   640,   644,   645,
     646,   649,   651,   655,   659,   660,   663,   666,   667,   670,
     671,   673,   674,   675,   678,   679,   687,   690,   691,   692,
     695,   696,   699,   700,   704,   705,   708,   709,   712,   713,
     716,   717,   721,   722,   725,   726,   729,   730,   733,   734,
     738,   739
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

#line 33 "parser.yy"
} } // pdm::parser
#line 3947 "parser.tab.cc"

#line 742 "parser.yy"


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

    void parser::error(source::Loc const& loc, std::string const& message) {
        // todo: post feedback here
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
    llocp->source(source);

    bool const print_token_info = false;
    if (pdm::DEBUG && print_token_info) {
        // DebugPrintToken("YYLEX:", tk, info, llocp);
        debug_print_token("YYLEX:", tk, &info, llocp);
    }
    if (tk == Tk::EOS) {
        return Tk::YYEOF;
    } else {
        return tk;
    }
}
