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
#line 2057 "parser.tab.cc"
    break;

  case 3: // scriptContent: scriptContentStmt ";"
#line 305 "parser.yy"
                                                    { yylhs.value.as < std::vector<pdm::ast::Stmt*> > ().push_back(yystack_[1].value.as < pdm::ast::Stmt* > ()); }
#line 2063 "parser.tab.cc"
    break;

  case 4: // scriptContent: scriptContent scriptContentStmt ";"
#line 306 "parser.yy"
                                                    { yylhs.value.as < std::vector<pdm::ast::Stmt*> > () = std::move(yystack_[2].value.as < std::vector<pdm::ast::Stmt*> > ()); yylhs.value.as < std::vector<pdm::ast::Stmt*> > ().push_back(yystack_[1].value.as < pdm::ast::Stmt* > ()); }
#line 2069 "parser.tab.cc"
    break;

  case 5: // scriptContentStmt: mod_stmt
#line 309 "parser.yy"
      { yylhs.value.as < pdm::ast::Stmt* > () = yystack_[0].value.as < pdm::ast::Stmt* > (); }
#line 2075 "parser.tab.cc"
    break;

  case 6: // scriptContentStmt: import_stmt
#line 310 "parser.yy"
      { yylhs.value.as < pdm::ast::Stmt* > () = yystack_[0].value.as < pdm::ast::Stmt* > (); }
#line 2081 "parser.tab.cc"
    break;

  case 7: // scriptContentStmt: extern_stmt
#line 311 "parser.yy"
      { yylhs.value.as < pdm::ast::Stmt* > () = yystack_[0].value.as < pdm::ast::Stmt* > (); }
#line 2087 "parser.tab.cc"
    break;

  case 8: // mod_stmt: "mod" "<val_id>" "{" moduleContent "}"
#line 319 "parser.yy"
                                                { yylhs.value.as < pdm::ast::Stmt* > () = mgr->new_mod_stmt(yylhs.location, yystack_[3].value.as < TokenInfo > ().ID_intstr, std::move(yystack_[1].value.as < std::vector<pdm::ast::Stmt*> > ())); }
#line 2093 "parser.tab.cc"
    break;

  case 9: // moduleContent: moduleContentStmt ";"
#line 322 "parser.yy"
                                                    { yylhs.value.as < std::vector<pdm::ast::Stmt*> > ().push_back(yystack_[1].value.as < pdm::ast::Stmt* > ()); }
#line 2099 "parser.tab.cc"
    break;

  case 10: // moduleContent: moduleContent moduleContentStmt ";"
#line 323 "parser.yy"
                                                    { yylhs.value.as < std::vector<pdm::ast::Stmt*> > () = std::move(yystack_[2].value.as < std::vector<pdm::ast::Stmt*> > ()); yylhs.value.as < std::vector<pdm::ast::Stmt*> > ().push_back(yystack_[1].value.as < pdm::ast::Stmt* > ()); }
#line 2105 "parser.tab.cc"
    break;

  case 11: // chain_prefix_stmt: const_stmt
#line 331 "parser.yy"
      { yylhs.value.as < pdm::ast::Stmt* > () = yystack_[0].value.as < pdm::ast::Stmt* > (); }
#line 2111 "parser.tab.cc"
    break;

  case 12: // chain_prefix_stmt: val_stmt
#line 332 "parser.yy"
      { yylhs.value.as < pdm::ast::Stmt* > () = yystack_[0].value.as < pdm::ast::Stmt* > (); }
#line 2117 "parser.tab.cc"
    break;

  case 13: // chain_prefix_stmt: var_stmt
#line 333 "parser.yy"
      { yylhs.value.as < pdm::ast::Stmt* > () = yystack_[0].value.as < pdm::ast::Stmt* > (); }
#line 2123 "parser.tab.cc"
    break;

  case 14: // chain_prefix_stmt: set_stmt
#line 334 "parser.yy"
      { yylhs.value.as < pdm::ast::Stmt* > () = yystack_[0].value.as < pdm::ast::Stmt* > (); }
#line 2129 "parser.tab.cc"
    break;

  case 15: // chain_prefix_stmt: discard_stmt
#line 335 "parser.yy"
      { yylhs.value.as < pdm::ast::Stmt* > () = yystack_[0].value.as < pdm::ast::Stmt* > (); }
#line 2135 "parser.tab.cc"
    break;

  case 16: // const_stmt: "const" lpattern_naked "=" expr
#line 338 "parser.yy"
                                        { yylhs.value.as < pdm::ast::Stmt* > () = mgr->new_const_stmt(yylhs.location, yystack_[2].value.as < pdm::ast::LPattern* > (), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2141 "parser.tab.cc"
    break;

  case 17: // val_stmt: "val" lpattern_naked "=" expr
#line 341 "parser.yy"
                                        { yylhs.value.as < pdm::ast::Stmt* > () = mgr->new_val_stmt(yylhs.location, yystack_[2].value.as < pdm::ast::LPattern* > (), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2147 "parser.tab.cc"
    break;

  case 18: // var_stmt: "var" lpattern_naked "=" expr
#line 344 "parser.yy"
                                        { yylhs.value.as < pdm::ast::Stmt* > () = mgr->new_var_stmt(yylhs.location, yystack_[2].value.as < pdm::ast::LPattern* > (), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2153 "parser.tab.cc"
    break;

  case 19: // set_stmt: "set" expr "=" expr
#line 347 "parser.yy"
                              { yylhs.value.as < pdm::ast::Stmt* > () = mgr->new_set_stmt(yylhs.location, yystack_[2].value.as < pdm::ast::Exp* > (), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2159 "parser.tab.cc"
    break;

  case 20: // discard_stmt: expr
#line 350 "parser.yy"
              { yylhs.value.as < pdm::ast::Stmt* > () = mgr->new_discard_stmt(yylhs.location, yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2165 "parser.tab.cc"
    break;

  case 21: // moduleContentStmt: fn_stmt
#line 354 "parser.yy"
      { yylhs.value.as < pdm::ast::Stmt* > () = yystack_[0].value.as < pdm::ast::Stmt* > (); }
#line 2171 "parser.tab.cc"
    break;

  case 22: // moduleContentStmt: type_stmt
#line 355 "parser.yy"
      { yylhs.value.as < pdm::ast::Stmt* > () = yystack_[0].value.as < pdm::ast::Stmt* > (); }
#line 2177 "parser.tab.cc"
    break;

  case 23: // moduleContentStmt: enum_stmt
#line 356 "parser.yy"
      { yylhs.value.as < pdm::ast::Stmt* > () = yystack_[0].value.as < pdm::ast::Stmt* > (); }
#line 2183 "parser.tab.cc"
    break;

  case 24: // moduleContentStmt: typeclass_stmt
#line 357 "parser.yy"
      { yylhs.value.as < pdm::ast::Stmt* > () = yystack_[0].value.as < pdm::ast::Stmt* > (); }
#line 2189 "parser.tab.cc"
    break;

  case 25: // moduleContentStmt: import_stmt
#line 358 "parser.yy"
      { yylhs.value.as < pdm::ast::Stmt* > () = yystack_[0].value.as < pdm::ast::Stmt* > (); }
#line 2195 "parser.tab.cc"
    break;

  case 26: // moduleContentStmt: mod_stmt
#line 359 "parser.yy"
      { yylhs.value.as < pdm::ast::Stmt* > () = yystack_[0].value.as < pdm::ast::Stmt* > (); }
#line 2201 "parser.tab.cc"
    break;

  case 27: // moduleContentStmt: using_stmt
#line 360 "parser.yy"
      { yylhs.value.as < pdm::ast::Stmt* > () = yystack_[0].value.as < pdm::ast::Stmt* > (); }
#line 2207 "parser.tab.cc"
    break;

  case 28: // moduleContentStmt: extern_stmt
#line 361 "parser.yy"
      { yylhs.value.as < pdm::ast::Stmt* > () = yystack_[0].value.as < pdm::ast::Stmt* > (); }
#line 2213 "parser.tab.cc"
    break;

  case 29: // fn_stmt: "fn" vid vpattern "->" typespec "=" bracketed_exp
#line 364 "parser.yy"
                                                                          { yylhs.value.as < pdm::ast::Stmt* > () = mgr->new_fn_stmt(yylhs.location, yystack_[5].value.as < TokenInfo > ().ID_intstr, std::move(std::vector<ast::TPattern*>{}), yystack_[4].value.as < pdm::ast::VPattern* > (), yystack_[2].value.as < pdm::ast::Typespec* > (), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2219 "parser.tab.cc"
    break;

  case 30: // fn_stmt: "fn" vid tpattern_seq vpattern "->" typespec "=" bracketed_exp
#line 365 "parser.yy"
                                                                          { yylhs.value.as < pdm::ast::Stmt* > () = mgr->new_fn_stmt(yylhs.location, yystack_[6].value.as < TokenInfo > ().ID_intstr, std::move(yystack_[5].value.as < std::vector<pdm::ast::TPattern*> > ()), yystack_[4].value.as < pdm::ast::VPattern* > (), yystack_[2].value.as < pdm::ast::Typespec* > (), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2225 "parser.tab.cc"
    break;

  case 31: // fn_stmt: "fn" vid vpattern "=" bracketed_exp
#line 366 "parser.yy"
                                                                          { yylhs.value.as < pdm::ast::Stmt* > () = mgr->new_fn_stmt(yylhs.location, yystack_[3].value.as < TokenInfo > ().ID_intstr, std::move(std::vector<ast::TPattern*>{}), yystack_[2].value.as < pdm::ast::VPattern* > (), nullptr, yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2231 "parser.tab.cc"
    break;

  case 32: // fn_stmt: "fn" vid tpattern_seq vpattern "=" bracketed_exp
#line 367 "parser.yy"
                                                                          { yylhs.value.as < pdm::ast::Stmt* > () = mgr->new_fn_stmt(yylhs.location, yystack_[4].value.as < TokenInfo > ().ID_intstr, std::move(yystack_[3].value.as < std::vector<pdm::ast::TPattern*> > ()), yystack_[2].value.as < pdm::ast::VPattern* > (), nullptr, yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2237 "parser.tab.cc"
    break;

  case 33: // type_stmt: "type" tid "=" long_typespec
#line 370 "parser.yy"
                                                    { yylhs.value.as < pdm::ast::Stmt* > () = mgr->new_type_stmt(yylhs.location, yystack_[2].value.as < TokenInfo > ().ID_intstr, std::move(std::vector<ast::TPattern*>{}), yystack_[0].value.as < pdm::ast::Typespec* > ()); }
#line 2243 "parser.tab.cc"
    break;

  case 34: // type_stmt: "type" tid tpattern_seq "=" long_typespec
#line 371 "parser.yy"
                                                    { yylhs.value.as < pdm::ast::Stmt* > () = mgr->new_type_stmt(yylhs.location, yystack_[3].value.as < TokenInfo > ().ID_intstr, std::move(yystack_[2].value.as < std::vector<pdm::ast::TPattern*> > ()), yystack_[0].value.as < pdm::ast::Typespec* > ()); }
#line 2249 "parser.tab.cc"
    break;

  case 35: // enum_stmt: "enum" tid enum_field_pl
#line 374 "parser.yy"
                                    { yylhs.value.as < pdm::ast::Stmt* > () = mgr->new_enum_stmt(yylhs.location, yystack_[1].value.as < TokenInfo > ().ID_intstr, std::move(yystack_[0].value.as < std::vector<pdm::ast::EnumStmt::Field*> > ())); }
#line 2255 "parser.tab.cc"
    break;

  case 36: // enum_field_pl: "|" unprefixed_enum_field_pl
#line 377 "parser.yy"
                                    { yylhs.value.as < std::vector<pdm::ast::EnumStmt::Field*> > () = std::move(yystack_[0].value.as < std::vector<pdm::ast::EnumStmt::Field*> > ()); }
#line 2261 "parser.tab.cc"
    break;

  case 37: // enum_field_pl: unprefixed_enum_field_pl
#line 378 "parser.yy"
                                    { yylhs.value.as < std::vector<pdm::ast::EnumStmt::Field*> > () = std::move(yystack_[0].value.as < std::vector<pdm::ast::EnumStmt::Field*> > ()); }
#line 2267 "parser.tab.cc"
    break;

  case 38: // unprefixed_enum_field_pl: enum_field
#line 381 "parser.yy"
                                                { yylhs.value.as < std::vector<pdm::ast::EnumStmt::Field*> > ().push_back(yystack_[0].value.as < pdm::ast::EnumStmt::Field* > ()); }
#line 2273 "parser.tab.cc"
    break;

  case 39: // unprefixed_enum_field_pl: unprefixed_enum_field_pl "|" enum_field
#line 382 "parser.yy"
                                                { yylhs.value.as < std::vector<pdm::ast::EnumStmt::Field*> > () = std::move(yystack_[2].value.as < std::vector<pdm::ast::EnumStmt::Field*> > ()); yylhs.value.as < std::vector<pdm::ast::EnumStmt::Field*> > ().push_back(yystack_[0].value.as < pdm::ast::EnumStmt::Field* > ()); }
#line 2279 "parser.tab.cc"
    break;

  case 40: // enum_field: tid
#line 385 "parser.yy"
                                     { yylhs.value.as < pdm::ast::EnumStmt::Field* > () = mgr->new_enum_stmt_field(yylhs.location, yystack_[0].value.as < TokenInfo > ().ID_intstr, std::move(std::vector<ast::Typespec*>{}), false); }
#line 2285 "parser.tab.cc"
    break;

  case 41: // enum_field: tid "(" ")"
#line 386 "parser.yy"
                                     { yylhs.value.as < pdm::ast::EnumStmt::Field* > () = mgr->new_enum_stmt_field(yylhs.location, yystack_[2].value.as < TokenInfo > ().ID_intstr, std::move(std::vector<ast::Typespec*>{}), true); }
#line 2291 "parser.tab.cc"
    break;

  case 42: // enum_field: tid "(" typespec_cl1 ")"
#line 387 "parser.yy"
                                     { yylhs.value.as < pdm::ast::EnumStmt::Field* > () = mgr->new_enum_stmt_field(yylhs.location, yystack_[3].value.as < TokenInfo > ().ID_intstr, std::move(yystack_[1].value.as < std::vector<pdm::ast::Typespec*> > ()), true); }
#line 2297 "parser.tab.cc"
    break;

  case 43: // typeclass_stmt: "typeclass" tid "<" tid typespec ">" "=" "{" expr_sl "}"
#line 390 "parser.yy"
                                                                                        { 
        yylhs.value.as < pdm::ast::Stmt* > () = mgr->new_typeclass_stmt(yylhs.location, yystack_[8].value.as < TokenInfo > ().ID_intstr, yystack_[6].value.as < TokenInfo > ().ID_intstr, yystack_[5].value.as < pdm::ast::Typespec* > (), std::move(std::vector<ast::TPattern*>{}), std::move(yystack_[1].value.as < std::vector<pdm::ast::Exp*> > ())); 
      }
#line 2305 "parser.tab.cc"
    break;

  case 44: // typeclass_stmt: "typeclass" tid "<" tid typespec ">" tpattern_seq "=" "{" expr_sl "}"
#line 393 "parser.yy"
                                                                                        { 
        yylhs.value.as < pdm::ast::Stmt* > () = mgr->new_typeclass_stmt(yylhs.location, yystack_[9].value.as < TokenInfo > ().ID_intstr, yystack_[7].value.as < TokenInfo > ().ID_intstr, yystack_[6].value.as < pdm::ast::Typespec* > (), std::move(yystack_[4].value.as < std::vector<pdm::ast::TPattern*> > ()), std::move(yystack_[1].value.as < std::vector<pdm::ast::Exp*> > ())); 
      }
#line 2313 "parser.tab.cc"
    break;

  case 45: // using_stmt: "using" bracketed_exp
#line 399 "parser.yy"
                             { yylhs.value.as < pdm::ast::Stmt* > () = mgr->new_using_stmt(yylhs.location, yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2319 "parser.tab.cc"
    break;

  case 46: // import_stmt: "import" vid "from" stringl "type" stringl
#line 403 "parser.yy"
                                                       { yylhs.value.as < pdm::ast::Stmt* > () = mgr->new_import_stmt(yylhs.location, yystack_[4].value.as < TokenInfo > ().ID_intstr, *yystack_[2].value.as < TokenInfo > ().String_utf8string, *yystack_[0].value.as < TokenInfo > ().String_utf8string); }
#line 2325 "parser.tab.cc"
    break;

  case 47: // extern_stmt: "extern" vid "from" expr
#line 407 "parser.yy"
                                    { yylhs.value.as < pdm::ast::Stmt* > () = mgr->new_extern_stmt(yylhs.location, yystack_[2].value.as < TokenInfo > ().ID_intstr, yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2331 "parser.tab.cc"
    break;

  case 48: // tid: "<TypeId>"
#line 414 "parser.yy"
     { yylhs.value.as < TokenInfo > () = yystack_[0].value.as < TokenInfo > (); }
#line 2337 "parser.tab.cc"
    break;

  case 49: // vid: "<val_id>"
#line 415 "parser.yy"
     { yylhs.value.as < TokenInfo > () = yystack_[0].value.as < TokenInfo > (); }
#line 2343 "parser.tab.cc"
    break;

  case 50: // floatl: "4.2"
#line 417 "parser.yy"
      { yylhs.value.as < TokenInfo > () = yystack_[0].value.as < TokenInfo > (); }
#line 2349 "parser.tab.cc"
    break;

  case 51: // stringl: "'sq-string-literal'"
#line 420 "parser.yy"
      { yylhs.value.as < TokenInfo > () = yystack_[0].value.as < TokenInfo > (); }
#line 2355 "parser.tab.cc"
    break;

  case 52: // stringl: "\"dq-string-literal\""
#line 421 "parser.yy"
      { yylhs.value.as < TokenInfo > () = yystack_[0].value.as < TokenInfo > (); }
#line 2361 "parser.tab.cc"
    break;

  case 53: // expr: binary_exp
#line 428 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2367 "parser.tab.cc"
    break;

  case 54: // long_exp: type_query_exp
#line 431 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2373 "parser.tab.cc"
    break;

  case 55: // expr_cl2: expr "," expr
#line 438 "parser.yy"
                             { yylhs.value.as < std::vector<pdm::ast::Exp*> > ().reserve(2); yylhs.value.as < std::vector<pdm::ast::Exp*> > ().push_back(yystack_[2].value.as < pdm::ast::Exp* > ()); yylhs.value.as < std::vector<pdm::ast::Exp*> > ().push_back(yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2379 "parser.tab.cc"
    break;

  case 56: // expr_cl2: expr_cl2 "," expr
#line 439 "parser.yy"
                             { yylhs.value.as < std::vector<pdm::ast::Exp*> > () = std::move(yystack_[2].value.as < std::vector<pdm::ast::Exp*> > ()); yylhs.value.as < std::vector<pdm::ast::Exp*> > ().push_back(yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2385 "parser.tab.cc"
    break;

  case 57: // expr_sl: expr ";"
#line 442 "parser.yy"
                             { yylhs.value.as < std::vector<pdm::ast::Exp*> > ().push_back(yystack_[1].value.as < pdm::ast::Exp* > ()); }
#line 2391 "parser.tab.cc"
    break;

  case 58: // expr_sl: expr_sl expr ";"
#line 443 "parser.yy"
                             { yylhs.value.as < std::vector<pdm::ast::Exp*> > () = std::move(yystack_[2].value.as < std::vector<pdm::ast::Exp*> > ()); yylhs.value.as < std::vector<pdm::ast::Exp*> > ().push_back(yystack_[1].value.as < pdm::ast::Exp* > ()); }
#line 2397 "parser.tab.cc"
    break;

  case 59: // bracketed_exp: unit_exp
#line 447 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2403 "parser.tab.cc"
    break;

  case 60: // bracketed_exp: paren_exp
#line 448 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2409 "parser.tab.cc"
    break;

  case 61: // bracketed_exp: vtupleExpr
#line 449 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2415 "parser.tab.cc"
    break;

  case 62: // bracketed_exp: vstructExpr
#line 450 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2421 "parser.tab.cc"
    break;

  case 63: // bracketed_exp: chain_exp
#line 451 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2427 "parser.tab.cc"
    break;

  case 64: // unit_exp: "(" ")"
#line 454 "parser.yy"
                        { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_unit_exp(yylhs.location); }
#line 2433 "parser.tab.cc"
    break;

  case 65: // unit_exp: "{" "}"
#line 455 "parser.yy"
                        { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_unit_exp(yylhs.location); }
#line 2439 "parser.tab.cc"
    break;

  case 66: // paren_exp: "(" long_exp ")"
#line 458 "parser.yy"
                              { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_paren_exp(yylhs.location, yystack_[1].value.as < pdm::ast::Exp* > ()); }
#line 2445 "parser.tab.cc"
    break;

  case 67: // vtupleExpr: "(" expr "," ")"
#line 461 "parser.yy"
                                   { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_tuple_exp(yylhs.location, std::move(std::vector(1,yystack_[2].value.as < pdm::ast::Exp* > ()))); }
#line 2451 "parser.tab.cc"
    break;

  case 68: // vtupleExpr: "(" expr_cl2 ")"
#line 462 "parser.yy"
                                   { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_tuple_exp(yylhs.location, std::move(yystack_[1].value.as < std::vector<pdm::ast::Exp*> > ())); }
#line 2457 "parser.tab.cc"
    break;

  case 69: // vstructExpr: "{" struct_exp_field_cl "}"
#line 465 "parser.yy"
                                            { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_struct_exp(yylhs.location, std::move(yystack_[1].value.as < std::vector<pdm::ast::StructExp::Field*> > ())); }
#line 2463 "parser.tab.cc"
    break;

  case 70: // primary_exp: bracketed_exp
#line 468 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2469 "parser.tab.cc"
    break;

  case 71: // primary_exp: vid
#line 469 "parser.yy"
                     { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_id_exp(yylhs.location, yystack_[0].value.as < TokenInfo > ().ID_intstr); }
#line 2475 "parser.tab.cc"
    break;

  case 72: // primary_exp: int_expr
#line 470 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2481 "parser.tab.cc"
    break;

  case 73: // primary_exp: floatl
#line 471 "parser.yy"
                     { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_float_exp(yylhs.location, yystack_[0].value.as < TokenInfo > ().Float); }
#line 2487 "parser.tab.cc"
    break;

  case 74: // primary_exp: stringls
#line 472 "parser.yy"
                     { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_string_exp(yylhs.location, std::move(yystack_[0].value.as < std::vector<pdm::ast::StringExp::Piece> > ())); }
#line 2493 "parser.tab.cc"
    break;

  case 75: // primary_exp: if_exp
#line 473 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2499 "parser.tab.cc"
    break;

  case 76: // primary_exp: lambda_exp
#line 474 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2505 "parser.tab.cc"
    break;

  case 77: // int_expr: "42"
#line 477 "parser.yy"
                { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_int_exp(yylhs.location, yystack_[0].value.as < TokenInfo > ().Int, ast::IntExp::Base::Dec); }
#line 2511 "parser.tab.cc"
    break;

  case 78: // int_expr: "0x2a"
#line 478 "parser.yy"
                { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_int_exp(yylhs.location, yystack_[0].value.as < TokenInfo > ().Int, ast::IntExp::Base::Hex); }
#line 2517 "parser.tab.cc"
    break;

  case 79: // stringls: "'sq-string-literal'"
#line 481 "parser.yy"
                             { yylhs.value.as < std::vector<pdm::ast::StringExp::Piece> > ().emplace_back(yylhs.location, *yystack_[0].value.as < TokenInfo > ().String_utf8string, ast::StringExp::QuoteKind::SingleQuote); }
#line 2523 "parser.tab.cc"
    break;

  case 80: // stringls: "\"dq-string-literal\""
#line 482 "parser.yy"
                             { yylhs.value.as < std::vector<pdm::ast::StringExp::Piece> > ().emplace_back(yylhs.location, *yystack_[0].value.as < TokenInfo > ().String_utf8string, ast::StringExp::QuoteKind::DoubleQuote); }
#line 2529 "parser.tab.cc"
    break;

  case 81: // stringls: stringls "'sq-string-literal'"
#line 483 "parser.yy"
                             { yylhs.value.as < std::vector<pdm::ast::StringExp::Piece> > () = std::move(yystack_[1].value.as < std::vector<pdm::ast::StringExp::Piece> > ()); yylhs.value.as < std::vector<pdm::ast::StringExp::Piece> > ().emplace_back(yystack_[0].location, *yystack_[0].value.as < TokenInfo > ().String_utf8string, ast::StringExp::QuoteKind::SingleQuote); }
#line 2535 "parser.tab.cc"
    break;

  case 82: // stringls: stringls "\"dq-string-literal\""
#line 484 "parser.yy"
                             { yylhs.value.as < std::vector<pdm::ast::StringExp::Piece> > () = std::move(yystack_[1].value.as < std::vector<pdm::ast::StringExp::Piece> > ()); yylhs.value.as < std::vector<pdm::ast::StringExp::Piece> > ().emplace_back(yystack_[0].location, *yystack_[0].value.as < TokenInfo > ().String_utf8string, ast::StringExp::QuoteKind::DoubleQuote); }
#line 2541 "parser.tab.cc"
    break;

  case 83: // if_exp: "if" bracketed_exp "then" bracketed_exp
#line 487 "parser.yy"
                                                                        { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_if_exp(yylhs.location, yystack_[2].value.as < pdm::ast::Exp* > (), yystack_[0].value.as < pdm::ast::Exp* > (), nullptr); }
#line 2547 "parser.tab.cc"
    break;

  case 84: // if_exp: "if" bracketed_exp "then" bracketed_exp "else" primary_exp
#line 488 "parser.yy"
                                                                        { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_if_exp(yylhs.location, yystack_[4].value.as < pdm::ast::Exp* > (), yystack_[2].value.as < pdm::ast::Exp* > (), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2553 "parser.tab.cc"
    break;

  case 85: // chain_exp: "{" expr "}"
#line 491 "parser.yy"
                                          { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_chain_exp(yylhs.location, std::move(std::vector<ast::Stmt*>{}), yystack_[1].value.as < pdm::ast::Exp* > ()); }
#line 2559 "parser.tab.cc"
    break;

  case 86: // chain_exp: "{" chain_prefix "}"
#line 492 "parser.yy"
                                           { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_chain_exp(yylhs.location, std::move(yystack_[1].value.as < std::vector<pdm::ast::Stmt*> > ()), nullptr); }
#line 2565 "parser.tab.cc"
    break;

  case 87: // chain_exp: "{" chain_prefix expr "}"
#line 493 "parser.yy"
                                           { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_chain_exp(yylhs.location, std::move(yystack_[2].value.as < std::vector<pdm::ast::Stmt*> > ()), yystack_[1].value.as < pdm::ast::Exp* > ()); }
#line 2571 "parser.tab.cc"
    break;

  case 88: // chain_prefix: chain_prefix_stmt ";"
#line 496 "parser.yy"
                                               { yylhs.value.as < std::vector<pdm::ast::Stmt*> > ().push_back(yystack_[1].value.as < pdm::ast::Stmt* > ()); }
#line 2577 "parser.tab.cc"
    break;

  case 89: // chain_prefix: chain_prefix chain_prefix_stmt ";"
#line 497 "parser.yy"
                                                { yylhs.value.as < std::vector<pdm::ast::Stmt*> > () = std::move(yystack_[2].value.as < std::vector<pdm::ast::Stmt*> > ()); yylhs.value.as < std::vector<pdm::ast::Stmt*> > ().push_back(yystack_[1].value.as < pdm::ast::Stmt* > ()); }
#line 2583 "parser.tab.cc"
    break;

  case 90: // lambda_exp: "fn" vpattern "=" bracketed_exp
#line 500 "parser.yy"
                                          { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_lambda_exp(yylhs.location, yystack_[2].value.as < pdm::ast::VPattern* > (), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2589 "parser.tab.cc"
    break;

  case 91: // postfix_exp: primary_exp
#line 504 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2595 "parser.tab.cc"
    break;

  case 92: // postfix_exp: tcall_exp
#line 505 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2601 "parser.tab.cc"
    break;

  case 93: // postfix_exp: vcall_exp
#line 506 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2607 "parser.tab.cc"
    break;

  case 94: // postfix_exp: dot_name_exp
#line 507 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2613 "parser.tab.cc"
    break;

  case 95: // postfix_exp: dot_index_exp
#line 508 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2619 "parser.tab.cc"
    break;

  case 96: // tcall_exp: postfix_exp "[" targ_cl "]"
#line 511 "parser.yy"
                                         { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_tcall_exp(yylhs.location, yystack_[3].value.as < pdm::ast::Exp* > (), std::move(yystack_[1].value.as < std::vector<pdm::ast::TArg*> > ())); }
#line 2625 "parser.tab.cc"
    break;

  case 97: // vcall_exp: postfix_exp "(" ")"
#line 514 "parser.yy"
                                            { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_vcall_exp(yylhs.location, yystack_[2].value.as < pdm::ast::Exp* > (), std::move(std::vector<ast::VArg*>{})); }
#line 2631 "parser.tab.cc"
    break;

  case 98: // vcall_exp: postfix_exp "(" varg_cl ")"
#line 515 "parser.yy"
                                            { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_vcall_exp(yylhs.location, yystack_[3].value.as < pdm::ast::Exp* > (), std::move(yystack_[1].value.as < std::vector<pdm::ast::VArg*> > ())); }
#line 2637 "parser.tab.cc"
    break;

  case 99: // dot_name_exp: postfix_exp "." "<val_id>"
#line 518 "parser.yy"
                            { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_dot_name_exp(yylhs.location, yystack_[2].value.as < pdm::ast::Exp* > (), yystack_[0].value.as < TokenInfo > ().ID_intstr, ast::DotNameExp::RhsHint::LhsStruct); }
#line 2643 "parser.tab.cc"
    break;

  case 100: // dot_name_exp: postfix_exp "." "<TypeId>"
#line 519 "parser.yy"
                            { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_dot_name_exp(yylhs.location, yystack_[2].value.as < pdm::ast::Exp* > (), yystack_[0].value.as < TokenInfo > ().ID_intstr, ast::DotNameExp::RhsHint::LhsEnum); }
#line 2649 "parser.tab.cc"
    break;

  case 101: // dot_index_exp: postfix_exp "." int_expr
#line 522 "parser.yy"
                                    { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_dot_index_exp(yylhs.location, yystack_[2].value.as < pdm::ast::Exp* > (), yystack_[0].value.as < pdm::ast::Exp* > (), ast::DotIndexExp::RhsHint::LhsNotPtr); }
#line 2655 "parser.tab.cc"
    break;

  case 102: // dot_index_exp: postfix_exp "." bracketed_exp
#line 523 "parser.yy"
                                    { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_dot_index_exp(yylhs.location, yystack_[2].value.as < pdm::ast::Exp* > (), yystack_[0].value.as < pdm::ast::Exp* > (), ast::DotIndexExp::RhsHint::LhsNotPtr); }
#line 2661 "parser.tab.cc"
    break;

  case 103: // unary_exp: postfix_exp
#line 527 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2667 "parser.tab.cc"
    break;

  case 104: // unary_exp: unary_op unary_exp
#line 528 "parser.yy"
                             { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_unary_exp(yylhs.location, yystack_[1].value.as < pdm::ast::UnaryOperator > (), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2673 "parser.tab.cc"
    break;

  case 105: // unary_op: "+"
#line 531 "parser.yy"
                 { yylhs.value.as < pdm::ast::UnaryOperator > () = ast::UnaryOperator::Plus; }
#line 2679 "parser.tab.cc"
    break;

  case 106: // unary_op: "-"
#line 532 "parser.yy"
                 { yylhs.value.as < pdm::ast::UnaryOperator > () = ast::UnaryOperator::Minus; }
#line 2685 "parser.tab.cc"
    break;

  case 107: // unary_op: "*"
#line 533 "parser.yy"
                 { yylhs.value.as < pdm::ast::UnaryOperator > () = ast::UnaryOperator::DeRef; }
#line 2691 "parser.tab.cc"
    break;

  case 108: // unary_op: "^"
#line 534 "parser.yy"
                 { yylhs.value.as < pdm::ast::UnaryOperator > () = ast::UnaryOperator::GetRef; }
#line 2697 "parser.tab.cc"
    break;

  case 109: // unary_op: "not"
#line 535 "parser.yy"
                 { yylhs.value.as < pdm::ast::UnaryOperator > () = ast::UnaryOperator::Not; }
#line 2703 "parser.tab.cc"
    break;

  case 110: // binary_exp: or_binary_exp
#line 539 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2709 "parser.tab.cc"
    break;

  case 111: // mul_binary_op: "*"
#line 542 "parser.yy"
                 { yylhs.value.as < pdm::ast::BinaryOperator > () = ast::BinaryOperator::Mul; }
#line 2715 "parser.tab.cc"
    break;

  case 112: // mul_binary_op: "/"
#line 543 "parser.yy"
                 { yylhs.value.as < pdm::ast::BinaryOperator > () = ast::BinaryOperator::Div; }
#line 2721 "parser.tab.cc"
    break;

  case 113: // mul_binary_op: "%"
#line 544 "parser.yy"
                 { yylhs.value.as < pdm::ast::BinaryOperator > () = ast::BinaryOperator::Rem; }
#line 2727 "parser.tab.cc"
    break;

  case 114: // mul_binary_exp: unary_exp
#line 547 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2733 "parser.tab.cc"
    break;

  case 115: // mul_binary_exp: mul_binary_exp mul_binary_op unary_exp
#line 548 "parser.yy"
                                               { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_binary_exp(yylhs.location, yystack_[1].value.as < pdm::ast::BinaryOperator > (), yystack_[2].value.as < pdm::ast::Exp* > (), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2739 "parser.tab.cc"
    break;

  case 116: // add_binary_op: "+"
#line 551 "parser.yy"
             { yylhs.value.as < pdm::ast::BinaryOperator > () = ast::BinaryOperator::Add; }
#line 2745 "parser.tab.cc"
    break;

  case 117: // add_binary_op: "-"
#line 552 "parser.yy"
             { yylhs.value.as < pdm::ast::BinaryOperator > () = ast::BinaryOperator::Subtract; }
#line 2751 "parser.tab.cc"
    break;

  case 118: // add_binary_exp: mul_binary_exp
#line 555 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2757 "parser.tab.cc"
    break;

  case 119: // add_binary_exp: add_binary_exp add_binary_op mul_binary_exp
#line 556 "parser.yy"
                                                    { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_binary_exp(yylhs.location, yystack_[1].value.as < pdm::ast::BinaryOperator > (), yystack_[2].value.as < pdm::ast::Exp* > (), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2763 "parser.tab.cc"
    break;

  case 120: // cmp_binary_op: "<"
#line 559 "parser.yy"
                { yylhs.value.as < pdm::ast::BinaryOperator > () = ast::BinaryOperator::Less; }
#line 2769 "parser.tab.cc"
    break;

  case 121: // cmp_binary_op: "<="
#line 560 "parser.yy"
                { yylhs.value.as < pdm::ast::BinaryOperator > () = ast::BinaryOperator::LessOrEq; }
#line 2775 "parser.tab.cc"
    break;

  case 122: // cmp_binary_op: ">"
#line 561 "parser.yy"
                { yylhs.value.as < pdm::ast::BinaryOperator > () = ast::BinaryOperator::Greater; }
#line 2781 "parser.tab.cc"
    break;

  case 123: // cmp_binary_op: ">="
#line 562 "parser.yy"
                { yylhs.value.as < pdm::ast::BinaryOperator > () = ast::BinaryOperator::GreaterOrEq; }
#line 2787 "parser.tab.cc"
    break;

  case 124: // cmp_binary_exp: add_binary_exp
#line 565 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2793 "parser.tab.cc"
    break;

  case 125: // cmp_binary_exp: cmp_binary_exp cmp_binary_op add_binary_exp
#line 566 "parser.yy"
                                                    { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_binary_exp(yylhs.location, yystack_[1].value.as < pdm::ast::BinaryOperator > (), yystack_[2].value.as < pdm::ast::Exp* > (), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2799 "parser.tab.cc"
    break;

  case 126: // eq_binary_op: "=="
#line 569 "parser.yy"
                 { yylhs.value.as < pdm::ast::BinaryOperator > () = ast::BinaryOperator::Equals; }
#line 2805 "parser.tab.cc"
    break;

  case 127: // eq_binary_op: "!="
#line 570 "parser.yy"
                 { yylhs.value.as < pdm::ast::BinaryOperator > () = ast::BinaryOperator::NotEquals; }
#line 2811 "parser.tab.cc"
    break;

  case 128: // eq_binary_exp: cmp_binary_exp
#line 573 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2817 "parser.tab.cc"
    break;

  case 129: // eq_binary_exp: eq_binary_exp eq_binary_op cmp_binary_exp
#line 574 "parser.yy"
                                                { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_binary_exp(yylhs.location, yystack_[1].value.as < pdm::ast::BinaryOperator > (), yystack_[2].value.as < pdm::ast::Exp* > (), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2823 "parser.tab.cc"
    break;

  case 130: // and_binary_exp: eq_binary_exp
#line 577 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2829 "parser.tab.cc"
    break;

  case 131: // and_binary_exp: and_binary_exp "and" eq_binary_exp
#line 578 "parser.yy"
                                           { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_binary_exp(yylhs.location, ast::BinaryOperator::And, yystack_[2].value.as < pdm::ast::Exp* > (), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2835 "parser.tab.cc"
    break;

  case 132: // xor_binary_exp: and_binary_exp
#line 581 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2841 "parser.tab.cc"
    break;

  case 133: // xor_binary_exp: xor_binary_exp "xor" and_binary_exp
#line 582 "parser.yy"
                                           { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_binary_exp(yylhs.location, ast::BinaryOperator::XOr, yystack_[2].value.as < pdm::ast::Exp* > (), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2847 "parser.tab.cc"
    break;

  case 134: // or_binary_exp: xor_binary_exp
#line 585 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2853 "parser.tab.cc"
    break;

  case 135: // or_binary_exp: or_binary_exp "or" xor_binary_exp
#line 586 "parser.yy"
                                           { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_binary_exp(yylhs.location, ast::BinaryOperator::Or, yystack_[2].value.as < pdm::ast::Exp* > (), yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 2859 "parser.tab.cc"
    break;

  case 136: // type_query_exp: binary_exp
#line 590 "parser.yy"
      { yylhs.value.as < pdm::ast::Exp* > () = yystack_[0].value.as < pdm::ast::Exp* > (); }
#line 2865 "parser.tab.cc"
    break;

  case 137: // type_query_exp: typespec type_query_op typespec
#line 591 "parser.yy"
                                        { yylhs.value.as < pdm::ast::Exp* > () = mgr->new_type_query_exp(yylhs.location, yystack_[1].value.as < pdm::ast::TypeQueryKind > (), yystack_[2].value.as < pdm::ast::Typespec* > (), yystack_[0].value.as < pdm::ast::Typespec* > ()); }
#line 2871 "parser.tab.cc"
    break;

  case 138: // type_query_op: ":<"
#line 594 "parser.yy"
                    { yylhs.value.as < pdm::ast::TypeQueryKind > () = ast::TypeQueryKind::LhsSubtypesRhs; }
#line 2877 "parser.tab.cc"
    break;

  case 139: // type_query_op: ">:"
#line 595 "parser.yy"
                    { yylhs.value.as < pdm::ast::TypeQueryKind > () = ast::TypeQueryKind::LhsSupertypesRhs; }
#line 2883 "parser.tab.cc"
    break;

  case 140: // type_query_op: "::"
#line 596 "parser.yy"
                    { yylhs.value.as < pdm::ast::TypeQueryKind > () = ast::TypeQueryKind::LhsEqualsRhs; }
#line 2889 "parser.tab.cc"
    break;

  case 141: // typespec: unary_typespec
#line 604 "parser.yy"
      { yylhs.value.as < pdm::ast::Typespec* > () = yystack_[0].value.as < pdm::ast::Typespec* > (); }
#line 2895 "parser.tab.cc"
    break;

  case 142: // typespec_cl1: typespec
#line 607 "parser.yy"
                                  { yylhs.value.as < std::vector<pdm::ast::Typespec*> > ().push_back(yystack_[0].value.as < pdm::ast::Typespec* > ()); }
#line 2901 "parser.tab.cc"
    break;

  case 143: // typespec_cl1: typespec_cl1 "," typespec
#line 608 "parser.yy"
                                  { yylhs.value.as < std::vector<pdm::ast::Typespec*> > () = std::move(yystack_[2].value.as < std::vector<pdm::ast::Typespec*> > ()); yylhs.value.as < std::vector<pdm::ast::Typespec*> > ().push_back(yystack_[0].value.as < pdm::ast::Typespec* > ()); }
#line 2907 "parser.tab.cc"
    break;

  case 144: // typespec_cl2: typespec "," typespec
#line 611 "parser.yy"
                                  { yylhs.value.as < std::vector<pdm::ast::Typespec*> > ().reserve(2); yylhs.value.as < std::vector<pdm::ast::Typespec*> > ().push_back(yystack_[2].value.as < pdm::ast::Typespec* > ()); yylhs.value.as < std::vector<pdm::ast::Typespec*> > ().push_back(yystack_[0].value.as < pdm::ast::Typespec* > ()); }
#line 2913 "parser.tab.cc"
    break;

  case 145: // typespec_cl2: typespec_cl2 "," typespec
#line 612 "parser.yy"
                                  { yylhs.value.as < std::vector<pdm::ast::Typespec*> > () = std::move(yystack_[2].value.as < std::vector<pdm::ast::Typespec*> > ()); yylhs.value.as < std::vector<pdm::ast::Typespec*> > ().push_back(yystack_[0].value.as < pdm::ast::Typespec* > ()); }
#line 2919 "parser.tab.cc"
    break;

  case 146: // struct_typespec_field: vid typespec
#line 616 "parser.yy"
                                  { yylhs.value.as < pdm::ast::StructTypespec::Field* > () = mgr->new_struct_typespec_field(yylhs.location, yystack_[1].value.as < TokenInfo > ().ID_intstr, yystack_[0].value.as < pdm::ast::Typespec* > ()); }
#line 2925 "parser.tab.cc"
    break;

  case 147: // struct_typespec_field_cl: struct_typespec_field
#line 619 "parser.yy"
                                                          { yylhs.value.as < std::vector<pdm::ast::StructTypespec::Field*> > ().push_back(yystack_[0].value.as < pdm::ast::StructTypespec::Field* > ()); }
#line 2931 "parser.tab.cc"
    break;

  case 148: // struct_typespec_field_cl: struct_typespec_field_cl "," struct_typespec_field
#line 620 "parser.yy"
                                                            { yylhs.value.as < std::vector<pdm::ast::StructTypespec::Field*> > () = std::move(yystack_[2].value.as < std::vector<pdm::ast::StructTypespec::Field*> > ()); yylhs.value.as < std::vector<pdm::ast::StructTypespec::Field*> > ().push_back(yystack_[0].value.as < pdm::ast::StructTypespec::Field* > ()); }
#line 2937 "parser.tab.cc"
    break;

  case 149: // primary_typespec: tid
#line 624 "parser.yy"
                        { yylhs.value.as < pdm::ast::Typespec* > () = mgr->new_id_typespec(yylhs.location, yystack_[0].value.as < TokenInfo > ().ID_intstr); }
#line 2943 "parser.tab.cc"
    break;

  case 150: // primary_typespec: paren_typespec
#line 625 "parser.yy"
      { yylhs.value.as < pdm::ast::Typespec* > () = yystack_[0].value.as < pdm::ast::Typespec* > (); }
#line 2949 "parser.tab.cc"
    break;

  case 151: // primary_typespec: tuple_typespec
#line 626 "parser.yy"
      { yylhs.value.as < pdm::ast::Typespec* > () = yystack_[0].value.as < pdm::ast::Typespec* > (); }
#line 2955 "parser.tab.cc"
    break;

  case 152: // primary_typespec: mod_prefix_tid
#line 627 "parser.yy"
      { yylhs.value.as < pdm::ast::Typespec* > () = yystack_[0].value.as < pdm::ast::Typespec* > (); }
#line 2961 "parser.tab.cc"
    break;

  case 153: // primary_typespec: fn_typespec
#line 628 "parser.yy"
      { yylhs.value.as < pdm::ast::Typespec* > () = yystack_[0].value.as < pdm::ast::Typespec* > (); }
#line 2967 "parser.tab.cc"
    break;

  case 154: // paren_typespec: "(" typespec ")"
#line 631 "parser.yy"
                                { yylhs.value.as < pdm::ast::Typespec* > () = mgr->new_paren_typespec(yylhs.location, yystack_[1].value.as < pdm::ast::Typespec* > ()); }
#line 2973 "parser.tab.cc"
    break;

  case 155: // tuple_typespec: "(" typespec "," ")"
#line 634 "parser.yy"
                                    { yylhs.value.as < pdm::ast::Typespec* > () = mgr->new_tuple_typespec(yylhs.location, std::move(std::vector(1,yystack_[2].value.as < pdm::ast::Typespec* > ()))); }
#line 2979 "parser.tab.cc"
    break;

  case 156: // tuple_typespec: "(" typespec_cl2 ")"
#line 635 "parser.yy"
                                    { yylhs.value.as < pdm::ast::Typespec* > () = mgr->new_tuple_typespec(yylhs.location, std::move(yystack_[1].value.as < std::vector<pdm::ast::Typespec*> > ())); }
#line 2985 "parser.tab.cc"
    break;

  case 157: // mod_prefix_tid: mod_prefix tid
#line 638 "parser.yy"
                            { yylhs.value.as < pdm::ast::Typespec* > () = mgr->new_dot_name_typespec_with_mod_prefix(yylhs.location, std::move(yystack_[1].value.as < std::vector<pdm::intern::String> > ()), yystack_[0].value.as < TokenInfo > ().ID_intstr); }
#line 2991 "parser.tab.cc"
    break;

  case 158: // mod_prefix: vid "."
#line 641 "parser.yy"
                            { yylhs.value.as < std::vector<pdm::intern::String> > ().push_back(yystack_[1].value.as < TokenInfo > ().ID_intstr); }
#line 2997 "parser.tab.cc"
    break;

  case 159: // mod_prefix: mod_prefix vid "."
#line 642 "parser.yy"
                            { yylhs.value.as < std::vector<pdm::intern::String> > () = std::move(yystack_[2].value.as < std::vector<pdm::intern::String> > ()); }
#line 3003 "parser.tab.cc"
    break;

  case 160: // fn_typespec: "Fn" vpattern primary_typespec
#line 645 "parser.yy"
                                       { yylhs.value.as < pdm::ast::Typespec* > () = mgr->new_fn_typespec(yylhs.location, std::move(yystack_[1].value.as < pdm::ast::VPattern* > ()), yystack_[0].value.as < pdm::ast::Typespec* > ()); }
#line 3009 "parser.tab.cc"
    break;

  case 161: // postfix_typespec: primary_typespec
#line 649 "parser.yy"
      { yylhs.value.as < pdm::ast::Typespec* > () = yystack_[0].value.as < pdm::ast::Typespec* > (); }
#line 3015 "parser.tab.cc"
    break;

  case 162: // postfix_typespec: tcall_typespec
#line 650 "parser.yy"
      { yylhs.value.as < pdm::ast::Typespec* > () = yystack_[0].value.as < pdm::ast::Typespec* > (); }
#line 3021 "parser.tab.cc"
    break;

  case 163: // postfix_typespec: dot_typespec
#line 651 "parser.yy"
      { yylhs.value.as < pdm::ast::Typespec* > () = yystack_[0].value.as < pdm::ast::Typespec* > (); }
#line 3027 "parser.tab.cc"
    break;

  case 164: // tcall_typespec: postfix_typespec "[" targ_cl "]"
#line 654 "parser.yy"
                                              { yylhs.value.as < pdm::ast::Typespec* > () = mgr->new_tcall_typespec(yylhs.location, yystack_[3].value.as < pdm::ast::Typespec* > (), std::move(yystack_[1].value.as < std::vector<pdm::ast::TArg*> > ())); }
#line 3033 "parser.tab.cc"
    break;

  case 165: // dot_typespec: postfix_typespec "." "<val_id>"
#line 656 "parser.yy"
                                         { yylhs.value.as < pdm::ast::Typespec* > () = mgr->new_dot_name_typespec_with_type_prefix(yylhs.location, yystack_[2].value.as < pdm::ast::Typespec* > (), yystack_[0].value.as < TokenInfo > ().ID_intstr); }
#line 3039 "parser.tab.cc"
    break;

  case 166: // unary_typespec: postfix_typespec
#line 660 "parser.yy"
      { yylhs.value.as < pdm::ast::Typespec* > () = yystack_[0].value.as < pdm::ast::Typespec* > (); }
#line 3045 "parser.tab.cc"
    break;

  case 167: // long_typespec: unary_typespec
#line 664 "parser.yy"
      { yylhs.value.as < pdm::ast::Typespec* > () = yystack_[0].value.as < pdm::ast::Typespec* > (); }
#line 3051 "parser.tab.cc"
    break;

  case 168: // long_typespec: struct_typespec
#line 665 "parser.yy"
      { yylhs.value.as < pdm::ast::Typespec* > () = yystack_[0].value.as < pdm::ast::Typespec* > (); }
#line 3057 "parser.tab.cc"
    break;

  case 169: // struct_typespec: "{" struct_typespec_field_cl "}"
#line 668 "parser.yy"
                                              { yylhs.value.as < pdm::ast::Typespec* > () = mgr->new_struct_typespec(yylhs.location, std::move(yystack_[1].value.as < std::vector<pdm::ast::StructTypespec::Field*> > ())); }
#line 3063 "parser.tab.cc"
    break;

  case 170: // targ: typespec
#line 671 "parser.yy"
               { yylhs.value.as < pdm::ast::TArg* > () = mgr->new_targ_typespec(yylhs.location, yystack_[0].value.as < pdm::ast::Typespec* > ()); }
#line 3069 "parser.tab.cc"
    break;

  case 171: // targ: expr
#line 672 "parser.yy"
               { yylhs.value.as < pdm::ast::TArg* > () = mgr->new_targ_exp(yylhs.location, yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 3075 "parser.tab.cc"
    break;

  case 172: // targ_cl: targ
#line 675 "parser.yy"
                            { yylhs.value.as < std::vector<pdm::ast::TArg*> > ().push_back(yystack_[0].value.as < pdm::ast::TArg* > ()); }
#line 3081 "parser.tab.cc"
    break;

  case 173: // targ_cl: targ_cl "," targ
#line 676 "parser.yy"
                            { yylhs.value.as < std::vector<pdm::ast::TArg*> > () = std::move(yystack_[2].value.as < std::vector<pdm::ast::TArg*> > ()); yylhs.value.as < std::vector<pdm::ast::TArg*> > ().push_back(yystack_[0].value.as < pdm::ast::TArg* > ()); }
#line 3087 "parser.tab.cc"
    break;

  case 174: // varg: expr
#line 678 "parser.yy"
                            { yylhs.value.as < pdm::ast::VArg* > () = mgr->new_varg(yylhs.location, yystack_[0].value.as < pdm::ast::Exp* > (), ast::VArgKind::In); }
#line 3093 "parser.tab.cc"
    break;

  case 175: // varg: "out" expr
#line 679 "parser.yy"
                            { yylhs.value.as < pdm::ast::VArg* > () = mgr->new_varg(yylhs.location, yystack_[0].value.as < pdm::ast::Exp* > (), ast::VArgKind::Out); }
#line 3099 "parser.tab.cc"
    break;

  case 176: // varg: "inout" expr
#line 680 "parser.yy"
                            { yylhs.value.as < pdm::ast::VArg* > () = mgr->new_varg(yylhs.location, yystack_[0].value.as < pdm::ast::Exp* > (), ast::VArgKind::InOut); }
#line 3105 "parser.tab.cc"
    break;

  case 177: // varg_cl: varg
#line 683 "parser.yy"
                            { yylhs.value.as < std::vector<pdm::ast::VArg*> > ().push_back(yystack_[0].value.as < pdm::ast::VArg* > ()); }
#line 3111 "parser.tab.cc"
    break;

  case 178: // varg_cl: varg_cl "," varg
#line 684 "parser.yy"
                            { yylhs.value.as < std::vector<pdm::ast::VArg*> > () = std::move(yystack_[2].value.as < std::vector<pdm::ast::VArg*> > ()); yylhs.value.as < std::vector<pdm::ast::VArg*> > ().push_back(yystack_[0].value.as < pdm::ast::VArg* > ()); }
#line 3117 "parser.tab.cc"
    break;

  case 179: // struct_exp_field: vid "=" expr
#line 692 "parser.yy"
                    { yylhs.value.as < pdm::ast::StructExp::Field* > () = mgr->new_struct_exp_field(yylhs.location, yystack_[2].value.as < TokenInfo > ().ID_intstr, yystack_[0].value.as < pdm::ast::Exp* > ()); }
#line 3123 "parser.tab.cc"
    break;

  case 180: // vpattern_field: vid typespec
#line 695 "parser.yy"
                            { yylhs.value.as < pdm::ast::VPattern::Field* > () = mgr->new_vpattern_field(yylhs.location, yystack_[1].value.as < TokenInfo > ().ID_intstr, yystack_[0].value.as < pdm::ast::Typespec* > (), ast::VArgKind::In); }
#line 3129 "parser.tab.cc"
    break;

  case 181: // vpattern_field: "out" vid typespec
#line 696 "parser.yy"
                            { yylhs.value.as < pdm::ast::VPattern::Field* > () = mgr->new_vpattern_field(yylhs.location, yystack_[1].value.as < TokenInfo > ().ID_intstr, yystack_[0].value.as < pdm::ast::Typespec* > (), ast::VArgKind::Out); }
#line 3135 "parser.tab.cc"
    break;

  case 182: // vpattern_field: "inout" vid typespec
#line 697 "parser.yy"
                            { yylhs.value.as < pdm::ast::VPattern::Field* > () = mgr->new_vpattern_field(yylhs.location, yystack_[1].value.as < TokenInfo > ().ID_intstr, yystack_[0].value.as < pdm::ast::Typespec* > (), ast::VArgKind::InOut); }
#line 3141 "parser.tab.cc"
    break;

  case 183: // lpattern_field: vid typespec
#line 700 "parser.yy"
                    { yylhs.value.as < pdm::ast::LPattern::Field* > () = mgr->new_lpattern_field(yylhs.location, ast::LPattern::FieldKind::IdTypespecPair, yystack_[1].value.as < TokenInfo > ().ID_intstr, yystack_[0].value.as < pdm::ast::Typespec* > ()); }
#line 3147 "parser.tab.cc"
    break;

  case 184: // lpattern_field: vid
#line 701 "parser.yy"
                    { yylhs.value.as < pdm::ast::LPattern::Field* > () = mgr->new_lpattern_field(yylhs.location, ast::LPattern::FieldKind::IdSingleton, yystack_[0].value.as < TokenInfo > ().ID_intstr); }
#line 3153 "parser.tab.cc"
    break;

  case 185: // tpattern_field: vid typespec
#line 704 "parser.yy"
                    { yylhs.value.as < pdm::ast::TPattern::Field* > () = mgr->new_tpattern_field(yylhs.location, ast::TPattern::FieldKind::Value, yystack_[1].value.as < TokenInfo > ().ID_intstr, yystack_[0].value.as < pdm::ast::Typespec* > ()); }
#line 3159 "parser.tab.cc"
    break;

  case 186: // tpattern_field: tid typespec
#line 705 "parser.yy"
                    { yylhs.value.as < pdm::ast::TPattern::Field* > () = mgr->new_tpattern_field(yylhs.location, ast::TPattern::FieldKind::Type, yystack_[1].value.as < TokenInfo > ().ID_intstr, yystack_[0].value.as < pdm::ast::Typespec* > ()); }
#line 3165 "parser.tab.cc"
    break;

  case 187: // lpattern: "(" lpattern_field_cl ")"
#line 709 "parser.yy"
                                       { yylhs.value.as < pdm::ast::LPattern* > () = mgr->new_lpattern(yylhs.location, std::move(yystack_[1].value.as < std::vector<pdm::ast::LPattern::Field*> > ())); }
#line 3171 "parser.tab.cc"
    break;

  case 188: // lpattern: "(" ")"
#line 710 "parser.yy"
                                       { yylhs.value.as < pdm::ast::LPattern* > () = mgr->new_lpattern(yylhs.location, std::move(std::vector<ast::LPattern::Field*>{})); }
#line 3177 "parser.tab.cc"
    break;

  case 189: // lpattern_naked: lpattern_field
#line 713 "parser.yy"
                                       { yylhs.value.as < pdm::ast::LPattern* > () = mgr->new_lpattern(yylhs.location, std::move(std::vector<ast::LPattern::Field*>{1,yystack_[0].value.as < pdm::ast::LPattern::Field* > ()})); }
#line 3183 "parser.tab.cc"
    break;

  case 190: // lpattern_naked: lpattern
#line 714 "parser.yy"
      { yylhs.value.as < pdm::ast::LPattern* > () = yystack_[0].value.as < pdm::ast::LPattern* > (); }
#line 3189 "parser.tab.cc"
    break;

  case 191: // vpattern: "(" vpattern_field_cl ")"
#line 717 "parser.yy"
                                       { yylhs.value.as < pdm::ast::VPattern* > () = mgr->new_vpattern(yylhs.location, std::move(yystack_[1].value.as < std::vector<pdm::ast::VPattern::Field*> > ())); }
#line 3195 "parser.tab.cc"
    break;

  case 192: // vpattern: "(" ")"
#line 718 "parser.yy"
                                      { yylhs.value.as < pdm::ast::VPattern* > () = mgr->new_vpattern(yylhs.location, std::move(std::vector<ast::VPattern::Field*>{})); }
#line 3201 "parser.tab.cc"
    break;

  case 193: // tpattern: "[" tpattern_field_cl "]"
#line 721 "parser.yy"
                                               { yylhs.value.as < pdm::ast::TPattern* > () = mgr->new_tpattern(yylhs.location, std::move(yystack_[1].value.as < std::vector<pdm::ast::TPattern::Field*> > ()), false); }
#line 3207 "parser.tab.cc"
    break;

  case 194: // tpattern: "!" "[" tpattern_field_cl "]"
#line 722 "parser.yy"
                                               { yylhs.value.as < pdm::ast::TPattern* > () = mgr->new_tpattern(yylhs.location, std::move(yystack_[1].value.as < std::vector<pdm::ast::TPattern::Field*> > ()), true); }
#line 3213 "parser.tab.cc"
    break;

  case 195: // vpattern_field_cl: vpattern_field
#line 726 "parser.yy"
                                              { yylhs.value.as < std::vector<pdm::ast::VPattern::Field*> > ().push_back(yystack_[0].value.as < pdm::ast::VPattern::Field* > ()); }
#line 3219 "parser.tab.cc"
    break;

  case 196: // vpattern_field_cl: vpattern_field_cl "," vpattern_field
#line 727 "parser.yy"
                                               { yylhs.value.as < std::vector<pdm::ast::VPattern::Field*> > () = std::move(yystack_[2].value.as < std::vector<pdm::ast::VPattern::Field*> > ()); yylhs.value.as < std::vector<pdm::ast::VPattern::Field*> > ().push_back(yystack_[0].value.as < pdm::ast::VPattern::Field* > ()); }
#line 3225 "parser.tab.cc"
    break;

  case 197: // lpattern_field_cl: lpattern_field
#line 730 "parser.yy"
                                              { yylhs.value.as < std::vector<pdm::ast::LPattern::Field*> > ().push_back(yystack_[0].value.as < pdm::ast::LPattern::Field* > ()); }
#line 3231 "parser.tab.cc"
    break;

  case 198: // lpattern_field_cl: lpattern_field_cl "," lpattern_field
#line 731 "parser.yy"
                                               { yylhs.value.as < std::vector<pdm::ast::LPattern::Field*> > () = std::move(yystack_[2].value.as < std::vector<pdm::ast::LPattern::Field*> > ()); yylhs.value.as < std::vector<pdm::ast::LPattern::Field*> > ().push_back(yystack_[0].value.as < pdm::ast::LPattern::Field* > ()); }
#line 3237 "parser.tab.cc"
    break;

  case 199: // tpattern_field_cl: tpattern_field
#line 734 "parser.yy"
                                              { yylhs.value.as < std::vector<pdm::ast::TPattern::Field*> > ().push_back(yystack_[0].value.as < pdm::ast::TPattern::Field* > ()); }
#line 3243 "parser.tab.cc"
    break;

  case 200: // tpattern_field_cl: tpattern_field_cl "," tpattern_field
#line 735 "parser.yy"
                                               { yylhs.value.as < std::vector<pdm::ast::TPattern::Field*> > () = std::move(yystack_[2].value.as < std::vector<pdm::ast::TPattern::Field*> > ()); yylhs.value.as < std::vector<pdm::ast::TPattern::Field*> > ().push_back(yystack_[0].value.as < pdm::ast::TPattern::Field* > ()); }
#line 3249 "parser.tab.cc"
    break;

  case 201: // struct_exp_field_cl: struct_exp_field
#line 738 "parser.yy"
                                                    { yylhs.value.as < std::vector<pdm::ast::StructExp::Field*> > ().push_back(yystack_[0].value.as < pdm::ast::StructExp::Field* > ()); }
#line 3255 "parser.tab.cc"
    break;

  case 202: // struct_exp_field_cl: struct_exp_field_cl "," struct_exp_field
#line 739 "parser.yy"
                                                    { yylhs.value.as < std::vector<pdm::ast::StructExp::Field*> > () = std::move(yystack_[2].value.as < std::vector<pdm::ast::StructExp::Field*> > ()); yylhs.value.as < std::vector<pdm::ast::StructExp::Field*> > ().push_back(yystack_[0].value.as < pdm::ast::StructExp::Field* > ()); }
#line 3261 "parser.tab.cc"
    break;

  case 203: // tpattern_seq: tpattern
#line 743 "parser.yy"
                             { yylhs.value.as < std::vector<pdm::ast::TPattern*> > ().push_back(yystack_[0].value.as < pdm::ast::TPattern* > ()); }
#line 3267 "parser.tab.cc"
    break;

  case 204: // tpattern_seq: tpattern_seq tpattern
#line 744 "parser.yy"
                             { yylhs.value.as < std::vector<pdm::ast::TPattern*> > () = std::move(yystack_[1].value.as < std::vector<pdm::ast::TPattern*> > ()); yylhs.value.as < std::vector<pdm::ast::TPattern*> > ().push_back(yystack_[0].value.as < pdm::ast::TPattern* > ()); }
#line 3273 "parser.tab.cc"
    break;


#line 3277 "parser.tab.cc"

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





  const short parser::yypact_ninf_ = -194;

  const short parser::yytable_ninf_ = -137;

  const short
  parser::yypact_[] =
  {
     180,    13,    31,    31,    45,   180,    24,  -194,  -194,  -194,
      35,  -194,    96,   108,  -194,    59,  -194,   341,   147,   572,
    -194,     2,    31,   129,   129,   129,  -194,   291,    97,  -194,
    -194,  -194,  -194,  -194,  -194,  -194,  -194,  -194,   122,     2,
     121,  -194,  -194,  -194,  -194,  -194,  -194,    86,    19,  -194,
    -194,  -194,  -194,  -194,  -194,  -194,  -194,  -194,  -194,  -194,
    -194,  -194,  -194,   204,  -194,  -194,  -194,   107,  -194,  -194,
    -194,  -194,  -194,   572,  -194,   104,   232,   199,   248,   192,
     146,   197,  -194,   -29,  -194,    83,     3,   187,  -194,   206,
    -194,   147,   257,    72,   211,   121,    86,  -194,  -194,   243,
     247,   246,   131,   249,  -194,    38,  -194,  -194,  -194,  -194,
     305,  -194,   -26,  -194,  -194,  -194,    21,    21,    21,   572,
    -194,   255,  -194,  -194,  -194,  -194,  -194,   239,   256,   378,
    -194,   -25,  -194,  -194,    52,   412,   157,  -194,  -194,  -194,
    -194,   572,  -194,  -194,   572,  -194,  -194,  -194,  -194,   572,
    -194,  -194,   572,   572,   572,   572,   305,   267,   -32,  -194,
     -29,    28,   163,   129,  -194,   253,  -194,   271,   129,  -194,
    -194,     2,    31,    31,  -194,    55,  -194,   132,     2,    55,
     161,   177,  -194,   481,  -194,   572,  -194,  -194,  -194,  -194,
      55,  -194,   284,   319,   157,     6,    55,  -194,  -194,   266,
     268,   276,   278,  -194,   572,  -194,  -194,   285,   282,    31,
    -194,  -194,  -194,  -194,  -194,   572,   572,  -194,  -194,  -194,
     208,  -194,  -194,  -194,    30,  -194,   104,   232,   199,   248,
     192,   146,    55,    55,  -194,   166,   305,    55,     2,   -17,
    -194,    55,    31,   243,  -194,  -194,  -194,    28,   253,   129,
     126,    55,   328,    55,    55,  -194,    79,  -194,  -194,  -194,
     138,  -194,    55,  -194,  -194,  -194,  -194,  -194,  -194,  -194,
     169,  -194,  -194,   227,  -194,   572,   572,   572,   572,  -194,
    -194,  -194,   239,  -194,  -194,  -194,   447,  -194,   157,  -194,
    -194,  -194,   305,  -194,   186,   283,  -194,    55,     2,   235,
      55,  -194,    53,  -194,  -194,  -194,  -194,   240,   286,   229,
    -194,  -194,  -194,  -194,  -194,  -194,  -194,    31,  -194,  -194,
    -194,  -194,  -194,  -194,  -194,  -194,  -194,     2,   288,  -194,
    -194,    31,  -194,    55,  -194,   179,  -194,  -194,  -194,     2,
    -194,  -194,   297,   185,  -194,   572,   298,   307,   516,   572,
    -194,  -194,   310,   550,  -194,  -194
  };

  const unsigned char
  parser::yydefact_[] =
  {
       0,     0,     0,     0,     0,     2,     0,     5,     6,     7,
       0,    49,     0,     0,     1,     0,     3,     0,     0,     0,
       4,     0,     0,     0,     0,     0,    26,     0,     0,    21,
      22,    23,    24,    27,    25,    28,    52,    51,     0,     0,
       0,   109,    77,    78,    50,    80,    79,     0,     0,   107,
     105,   106,   108,    71,    73,    47,    70,    59,    60,    61,
      62,    91,    72,    74,    75,    63,    76,   103,    92,    93,
      94,    95,   114,     0,    53,   118,   124,   128,   130,   132,
     134,   110,    45,     0,    48,     0,     0,     0,     8,     0,
       9,     0,     0,     0,     0,     0,     0,    64,   149,    71,
       0,     0,     0,    53,    54,     0,   161,   150,   151,   152,
       0,   153,   166,   162,   163,   141,     0,     0,     0,     0,
      65,     0,    11,    12,    13,    14,    15,    71,    20,     0,
     201,     0,    82,    81,     0,     0,     0,   104,   111,   112,
     113,     0,   116,   117,     0,   120,   121,   122,   123,     0,
     126,   127,     0,     0,     0,     0,     0,     0,     0,   203,
       0,     0,     0,     0,    35,    37,    38,    40,     0,    10,
      46,     0,     0,     0,   192,     0,   195,     0,     0,     0,
       0,     0,   158,     0,    66,     0,    68,   140,   138,   139,
       0,   157,     0,     0,     0,     0,   184,   189,   190,     0,
       0,     0,     0,    88,     0,    85,    86,     0,    20,     0,
      69,    99,   100,   102,   101,     0,     0,    97,   174,   177,
       0,   171,   170,   172,     0,   115,   119,   125,   129,   131,
     133,   135,     0,     0,   199,     0,     0,     0,     0,     0,
     204,     0,     0,     0,   167,    33,   168,     0,    36,     0,
       0,     0,    83,     0,     0,   180,     0,   191,    90,   160,
       0,   154,     0,   156,    67,    55,    56,   137,   159,   165,
       0,   188,   197,     0,   183,     0,     0,     0,     0,   179,
      89,    87,     0,   202,   175,   176,     0,    98,     0,    96,
     186,   185,     0,   193,     0,     0,    31,     0,     0,     0,
       0,   147,     0,    34,    39,    41,   142,     0,     0,     0,
     181,   182,   196,   155,   144,   145,   164,     0,   187,    16,
      17,    18,    19,   178,   173,   200,   194,     0,     0,    32,
     146,     0,   169,     0,    42,     0,    84,   198,    29,     0,
     148,   143,     0,     0,    30,     0,     0,     0,     0,     0,
      57,    43,     0,     0,    58,    44
  };

  const short
  parser::yypgoto_[] =
  {
    -194,  -194,  -194,   345,    68,  -194,   222,  -194,  -194,  -194,
    -194,  -194,   325,  -194,  -194,  -194,  -194,   190,   110,  -194,
    -194,    95,    98,    -5,    39,  -194,   269,   -19,  -194,  -194,
      16,     5,  -194,  -194,  -194,  -194,    58,   234,  -194,  -194,
    -194,  -194,  -194,  -194,  -194,  -194,  -194,  -194,   -69,  -194,
     -39,  -194,   230,  -194,   224,  -194,   219,  -194,   231,   223,
     225,  -194,  -194,  -194,   125,  -194,  -194,    51,  -194,   209,
    -194,  -194,  -194,  -194,  -194,  -194,  -194,  -194,  -155,   136,
    -194,   101,   196,   105,  -194,   183,   137,  -193,   109,  -194,
     200,   -72,  -157,  -194,  -194,   164,  -194,   -84
  };

  const short
  parser::yydefgoto_[] =
  {
      -1,     4,     5,     6,     7,    27,   121,   122,   123,   124,
     125,   126,    28,    29,    30,    31,   164,   165,   166,    32,
      33,     8,     9,    98,    53,    54,    38,   221,   101,   102,
     348,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,   129,    66,    67,    68,    69,    70,    71,    72,    73,
      74,   141,    75,   144,    76,   149,    77,   152,    78,    79,
      80,    81,   104,   190,   222,   307,   181,   301,   302,   106,
     107,   108,   109,   110,   111,   112,   113,   114,   115,   245,
     246,   223,   224,   219,   220,   130,   176,   197,   234,   198,
     199,    94,   159,   177,   273,   235,   131,   160
  };

  const short
  parser::yytable_[] =
  {
      55,   162,   272,   240,   137,   240,   244,    84,   103,    11,
     193,   158,    93,   209,   156,   237,    10,   194,    85,    86,
      87,   210,    11,   179,    11,   238,    82,    39,   100,   128,
     297,    11,    84,   157,    11,   116,   117,   118,   119,    40,
     298,    12,    13,    47,    92,    14,    41,    48,   271,    95,
      42,    43,    44,    45,    46,   211,   212,   103,    11,    84,
      47,    83,   195,    16,    48,   120,   163,    49,   288,   241,
      50,    51,   225,   242,   289,    11,    95,   100,   187,    52,
      17,   167,    11,    42,    43,    26,    99,   127,   239,    11,
      84,   331,   244,    47,    39,    26,   241,    48,    20,   332,
     202,   172,   173,   188,   189,   191,    40,    95,   172,   173,
     208,    18,    34,    41,   174,    35,   218,    42,    43,    44,
      45,    46,    34,    19,   337,    35,   156,    96,    97,    11,
      84,    48,   175,    84,    49,    99,    90,    50,    51,   213,
     161,    11,    84,   134,    91,   157,    52,    95,   135,   192,
     136,   232,   138,   139,   140,   196,   196,   196,   167,    95,
      11,    84,    93,   251,   265,    39,   266,   241,   305,   185,
     256,   154,   105,   186,   257,    99,   252,    40,    95,   241,
     313,    36,    37,   258,    41,   279,   240,     1,    42,    43,
      44,    45,    46,     2,     3,   233,   284,   285,    96,   260,
     243,   187,    48,   261,   292,    49,   156,   288,    50,    51,
     293,   253,   254,   316,   243,   262,   153,    52,   243,   263,
     247,   180,   156,   155,   292,   157,   188,   189,   156,   243,
     326,   232,    11,    99,   196,   243,   342,    39,   132,   133,
     168,   157,   346,   296,   167,   169,   286,   157,   282,    40,
     287,   343,   145,   146,   147,   148,   319,   320,   321,   322,
      42,    43,    44,    45,    46,   317,   171,   218,   178,   318,
      47,   243,   243,   260,    48,   233,   243,   261,   333,   182,
     243,   300,   334,   142,   143,   183,   243,   232,   184,   243,
     243,  -136,   243,   243,   203,   175,   204,    21,     1,   243,
     255,   243,   205,   329,     2,     3,   150,   151,    11,    84,
     236,    22,   250,    23,    24,   267,   249,   200,   201,    25,
     268,   274,   269,   275,   280,   276,   347,    99,   281,   352,
     347,   233,   338,   277,   352,   278,   243,    88,   309,   243,
     327,   335,   345,   349,   344,   339,   350,    21,     1,   354,
      15,   207,    89,   248,     2,     3,   196,   290,   291,   304,
     170,    22,   295,    23,    24,   353,   299,   336,   214,    25,
     300,   228,   243,   227,   226,   306,   308,   230,   310,   311,
     231,    11,   340,   303,   229,   314,    39,   315,   259,   324,
     270,   323,   283,   312,   116,   117,   118,   119,    40,     0,
     294,   325,     0,     0,     0,    41,     0,     0,     0,    42,
      43,    44,    45,    46,     0,    11,     0,     0,     0,    47,
      39,     0,   328,    48,   206,   330,    49,     0,     0,    50,
      51,     0,    40,     0,     0,     0,     0,     0,    52,    41,
       0,   215,   216,    42,    43,    44,    45,    46,     0,     0,
      11,     0,     0,    47,   217,    39,     0,    48,   341,     0,
      49,     0,     0,    50,    51,     0,     0,    40,     0,     0,
       0,     0,    52,     0,    41,     0,   215,   216,    42,    43,
      44,    45,    46,     0,    11,     0,     0,     0,    47,    39,
       0,     0,    48,     0,     0,    49,     0,     0,    50,    51,
       0,    40,     0,     0,     0,     0,     0,    52,    41,     0,
       0,     0,    42,    43,    44,    45,    46,     0,     0,    11,
       0,     0,    47,   264,    39,     0,    48,     0,     0,    49,
       0,     0,    50,    51,     0,     0,    40,     0,     0,     0,
       0,    52,     0,    41,     0,     0,     0,    42,    43,    44,
      45,    46,     0,    11,     0,     0,     0,    47,    39,     0,
       0,    48,   351,     0,    49,     0,     0,    50,    51,     0,
      40,     0,     0,     0,     0,    11,    52,    41,     0,     0,
      39,    42,    43,    44,    45,    46,     0,     0,     0,     0,
       0,    47,    40,     0,     0,    48,   355,     0,    49,    41,
       0,    50,    51,    42,    43,    44,    45,    46,     0,     0,
      52,     0,     0,    47,     0,     0,     0,    48,     0,     0,
      49,     0,     0,    50,    51,     0,     0,     0,     0,     0,
       0,     0,    52
  };

  const short
  parser::yycheck_[] =
  {
      19,    85,   195,   160,    73,   162,   161,     4,    47,     3,
      36,    83,    41,    38,    43,    47,     3,    43,    23,    24,
      25,    46,     3,    95,     3,    57,    21,     8,    47,    48,
      47,     3,     4,    62,     3,    16,    17,    18,    19,    20,
      57,     2,     3,    41,    39,     0,    27,    45,    42,    21,
      31,    32,    33,    34,    35,     3,     4,    96,     3,     4,
      41,    22,    41,    39,    45,    46,    63,    48,    38,    41,
      51,    52,   141,    45,    44,     3,    21,    96,    40,    60,
      45,    86,     3,    31,    32,    17,    47,    48,   160,     3,
       4,    38,   247,    41,     8,    27,    41,    45,    39,    46,
     119,    29,    30,    65,    66,   110,    20,    21,    29,    30,
     129,    15,    17,    27,    42,    17,   135,    31,    32,    33,
      34,    35,    27,    15,   317,    27,    43,    41,    42,     3,
       4,    45,    93,     4,    48,    96,    39,    51,    52,   134,
      57,     3,     4,    36,    22,    62,    60,    21,    41,   110,
      43,   156,    48,    49,    50,   116,   117,   118,   163,    21,
       3,     4,    41,   168,   183,     8,   185,    41,    42,    38,
      38,    25,    47,    42,    42,   136,   171,    20,    21,    41,
      42,    34,    35,   178,    27,   204,   343,     7,    31,    32,
      33,    34,    35,    13,    14,   156,   215,   216,    41,    38,
     161,    40,    45,    42,    38,    48,    43,    38,    51,    52,
      44,   172,   173,    44,   175,    38,    24,    60,   179,    42,
      57,    96,    43,    26,    38,    62,    65,    66,    43,   190,
      44,   236,     3,   194,   195,   196,    57,     8,    34,    35,
      53,    62,    57,   238,   249,    39,    38,    62,   209,    20,
      42,   335,    53,    54,    55,    56,   275,   276,   277,   278,
      31,    32,    33,    34,    35,    38,     9,   286,    57,    42,
      41,   232,   233,    38,    45,   236,   237,    42,    38,    36,
     241,   242,    42,    51,    52,    38,   247,   292,    42,   250,
     251,    42,   253,   254,    39,   256,    57,     6,     7,   260,
     175,   262,    46,   298,    13,    14,    58,    59,     3,     4,
      43,    20,    41,    22,    23,   190,    63,   117,   118,    28,
      36,   196,     3,    57,    39,    57,   345,   288,    46,   348,
     349,   292,   327,    57,   353,    57,   297,    46,    10,   300,
      57,    55,    45,    45,   339,    57,    39,     6,     7,    39,
       5,   129,    27,   163,    13,    14,   317,   232,   233,   249,
      91,    20,   237,    22,    23,   349,   241,   309,   134,    28,
     331,   152,   333,   149,   144,   250,   251,   154,   253,   254,
     155,     3,   331,   247,   153,   260,     8,   262,   179,   288,
     194,   286,   209,   256,    16,    17,    18,    19,    20,    -1,
     236,   292,    -1,    -1,    -1,    27,    -1,    -1,    -1,    31,
      32,    33,    34,    35,    -1,     3,    -1,    -1,    -1,    41,
       8,    -1,   297,    45,    46,   300,    48,    -1,    -1,    51,
      52,    -1,    20,    -1,    -1,    -1,    -1,    -1,    60,    27,
      -1,    29,    30,    31,    32,    33,    34,    35,    -1,    -1,
       3,    -1,    -1,    41,    42,     8,    -1,    45,   333,    -1,
      48,    -1,    -1,    51,    52,    -1,    -1,    20,    -1,    -1,
      -1,    -1,    60,    -1,    27,    -1,    29,    30,    31,    32,
      33,    34,    35,    -1,     3,    -1,    -1,    -1,    41,     8,
      -1,    -1,    45,    -1,    -1,    48,    -1,    -1,    51,    52,
      -1,    20,    -1,    -1,    -1,    -1,    -1,    60,    27,    -1,
      -1,    -1,    31,    32,    33,    34,    35,    -1,    -1,     3,
      -1,    -1,    41,    42,     8,    -1,    45,    -1,    -1,    48,
      -1,    -1,    51,    52,    -1,    -1,    20,    -1,    -1,    -1,
      -1,    60,    -1,    27,    -1,    -1,    -1,    31,    32,    33,
      34,    35,    -1,     3,    -1,    -1,    -1,    41,     8,    -1,
      -1,    45,    46,    -1,    48,    -1,    -1,    51,    52,    -1,
      20,    -1,    -1,    -1,    -1,     3,    60,    27,    -1,    -1,
       8,    31,    32,    33,    34,    35,    -1,    -1,    -1,    -1,
      -1,    41,    20,    -1,    -1,    45,    46,    -1,    48,    27,
      -1,    51,    52,    31,    32,    33,    34,    35,    -1,    -1,
      60,    -1,    -1,    41,    -1,    -1,    -1,    45,    -1,    -1,
      48,    -1,    -1,    51,    52,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    60
  };

  const unsigned char
  parser::yystos_[] =
  {
       0,     7,    13,    14,    69,    70,    71,    72,    89,    90,
       3,     3,    92,    92,     0,    71,    39,    45,    15,    15,
      39,     6,    20,    22,    23,    28,    72,    73,    80,    81,
      82,    83,    87,    88,    89,    90,    34,    35,    94,     8,
      20,    27,    31,    32,    33,    34,    35,    41,    45,    48,
      51,    52,    60,    92,    93,    95,    99,   100,   101,   102,
     103,   104,   105,   106,   107,   108,   110,   111,   112,   113,
     114,   115,   116,   117,   118,   120,   122,   124,   126,   127,
     128,   129,    99,    92,     4,    91,    91,    91,    46,    80,
      39,    22,    99,    41,   159,    21,    41,    42,    91,    92,
      95,    96,    97,   118,   130,   132,   137,   138,   139,   140,
     141,   142,   143,   144,   145,   146,    16,    17,    18,    19,
      46,    74,    75,    76,    77,    78,    79,    92,    95,   109,
     153,   164,    34,    35,    36,    41,    43,   116,    48,    49,
      50,   119,    51,    52,   121,    53,    54,    55,    56,   123,
      58,    59,   125,    24,    25,    26,    43,    62,   159,   160,
     165,    57,   165,    63,    84,    85,    86,    91,    53,    39,
      94,     9,    29,    30,    42,    92,   154,   161,    57,   159,
     132,   134,    36,    38,    42,    38,    42,    40,    65,    66,
     131,    91,    92,    36,    43,    41,    92,   155,   157,   158,
     158,   158,    95,    39,    57,    46,    46,    74,    95,    38,
      46,     3,     4,    99,   105,    29,    30,    42,    95,   151,
     152,    95,   132,   149,   150,   116,   120,   122,   124,   126,
     127,   128,    91,    92,   156,   163,    43,    47,    57,   159,
     160,    41,    45,    92,   146,   147,   148,    57,    85,    63,
      41,    91,    99,    92,    92,   132,    38,    42,    99,   137,
      38,    42,    38,    42,    42,    95,    95,   132,    36,     3,
     150,    42,   155,   162,   132,    57,    57,    57,    57,    95,
      39,    46,    92,   153,    95,    95,    38,    42,    38,    44,
     132,   132,    38,    44,   163,   132,    99,    47,    57,   132,
      92,   135,   136,   147,    86,    42,   132,   133,   132,    10,
     132,   132,   154,    42,   132,   132,    44,    38,    42,    95,
      95,    95,    95,   151,   149,   156,    44,    57,   132,    99,
     132,    38,    46,    38,    42,    55,   104,   155,    99,    57,
     135,   132,    57,   165,    99,    45,    57,    95,    98,    45,
      39,    46,    95,    98,    39,    46
  };

  const unsigned char
  parser::yyr1_[] =
  {
       0,    68,    69,    70,    70,    71,    71,    71,    72,    73,
      73,    74,    74,    74,    74,    74,    75,    76,    77,    78,
      79,    80,    80,    80,    80,    80,    80,    80,    80,    81,
      81,    81,    81,    82,    82,    83,    84,    84,    85,    85,
      86,    86,    86,    87,    87,    88,    89,    90,    91,    92,
      93,    94,    94,    95,    96,    97,    97,    98,    98,    99,
      99,    99,    99,    99,   100,   100,   101,   102,   102,   103,
     104,   104,   104,   104,   104,   104,   104,   105,   105,   106,
     106,   106,   106,   107,   107,   108,   108,   108,   109,   109,
     110,   111,   111,   111,   111,   111,   112,   113,   113,   114,
     114,   115,   115,   116,   116,   117,   117,   117,   117,   117,
     118,   119,   119,   119,   120,   120,   121,   121,   122,   122,
     123,   123,   123,   123,   124,   124,   125,   125,   126,   126,
     127,   127,   128,   128,   129,   129,   130,   130,   131,   131,
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
       1,     1,     1,     1,     1,     1,     1,     1,     1,     7,
       8,     5,     6,     4,     5,     3,     2,     1,     1,     3,
       1,     3,     4,    10,    11,     2,     6,     4,     1,     1,
       1,     1,     1,     1,     1,     3,     3,     2,     3,     1,
       1,     1,     1,     1,     2,     2,     3,     4,     3,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     2,     2,     4,     6,     3,     3,     4,     2,     3,
       4,     1,     1,     1,     1,     1,     4,     3,     4,     3,
       3,     3,     3,     1,     2,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     3,     1,     1,     1,     3,
       1,     1,     1,     1,     1,     3,     1,     1,     1,     3,
       1,     3,     1,     3,     1,     3,     1,     3,     1,     1,
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
  "typeclass_stmt", "using_stmt", "import_stmt", "extern_stmt", "tid",
  "vid", "floatl", "stringl", "expr", "long_exp", "expr_cl2", "expr_sl",
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
       0,   302,   302,   305,   306,   309,   310,   311,   319,   322,
     323,   331,   332,   333,   334,   335,   338,   341,   344,   347,
     350,   354,   355,   356,   357,   358,   359,   360,   361,   364,
     365,   366,   367,   370,   371,   374,   377,   378,   381,   382,
     385,   386,   387,   390,   393,   399,   403,   407,   414,   415,
     417,   420,   421,   428,   431,   438,   439,   442,   443,   447,
     448,   449,   450,   451,   454,   455,   458,   461,   462,   465,
     468,   469,   470,   471,   472,   473,   474,   477,   478,   481,
     482,   483,   484,   487,   488,   491,   492,   493,   496,   497,
     500,   504,   505,   506,   507,   508,   511,   514,   515,   518,
     519,   522,   523,   527,   528,   531,   532,   533,   534,   535,
     539,   542,   543,   544,   547,   548,   551,   552,   555,   556,
     559,   560,   561,   562,   565,   566,   569,   570,   573,   574,
     577,   578,   581,   582,   585,   586,   590,   591,   594,   595,
     596,   604,   607,   608,   611,   612,   616,   619,   620,   624,
     625,   626,   627,   628,   631,   634,   635,   638,   641,   642,
     645,   649,   650,   651,   654,   656,   660,   664,   665,   668,
     671,   672,   675,   676,   678,   679,   680,   683,   684,   692,
     695,   696,   697,   700,   701,   704,   705,   709,   710,   713,
     714,   717,   718,   721,   722,   726,   727,   730,   731,   734,
     735,   738,   739,   743,   744
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
#line 3968 "parser.tab.cc"

#line 747 "parser.yy"


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
