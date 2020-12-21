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

#line 18 "parser.yy"
namespace pdm { namespace parser {
#line 137 "parser.tab.cc"

  /// Build a parser object.
  parser::parser (pdm::source::Source* source_yyarg, pdm::parser::Lexer* lexer_yyarg, pdm::ast::Script** outp_yyarg)
#if YYDEBUG
    : yydebug_ (false),
      yycdebug_ (&std::cerr),
#else
    :
#endif
      source (source_yyarg),
      lexer (lexer_yyarg),
      outp (outp_yyarg)
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
    , value (that.value)
    , location (that.location)
  {}


  /// Constructor for valueless symbols.
  template <typename Base>
  parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, YY_MOVE_REF (location_type) l)
    : Base (t)
    , value ()
    , location (l)
  {}

  template <typename Base>
  parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, YY_RVREF (semantic_type) v, YY_RVREF (location_type) l)
    : Base (t)
    , value (YY_MOVE (v))
    , location (YY_MOVE (l))
  {}

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
    value = YY_MOVE (s.value);
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
    : super_type (YY_MOVE (that.state), YY_MOVE (that.value), YY_MOVE (that.location))
  {
#if 201103L <= YY_CPLUSPLUS
    // that is emptied.
    that.state = empty_state;
#endif
  }

  parser::stack_symbol_type::stack_symbol_type (state_type s, YY_MOVE_REF (symbol_type) that)
    : super_type (s, YY_MOVE (that.value), YY_MOVE (that.location))
  {
    // that is emptied.
    that.kind_ = symbol_kind::S_YYEMPTY;
  }

#if YY_CPLUSPLUS < 201103L
  parser::stack_symbol_type&
  parser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
    value = that.value;
    location = that.location;
    return *this;
  }

  parser::stack_symbol_type&
  parser::stack_symbol_type::operator= (stack_symbol_type& that)
  {
    state = that.state;
    value = that.value;
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

    // User destructor.
    YYUSE (yysym.kind ());
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
      /* If YYLEN is nonzero, implement the default value of the
         action: '$$ = $1'.  Otherwise, use the top of the stack.

         Otherwise, the following line sets YYLHS.VALUE to garbage.
         This behavior is undocumented and Bison users should not rely
         upon it.  */
      if (yylen)
        yylhs.value = yystack_[yylen - 1].value;
      else
        yylhs.value = yystack_[0].value;

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
#line 298 "parser.yy"
                    { (yylhs.value.script) = NewAstScriptWithModulesSb(yylhs.location, source, (yystack_[0].value.script_sb)); *outp = (yylhs.value.script); }
#line 606 "parser.tab.cc"
    break;

  case 3: // scriptContent: scriptContentStmt ";"
#line 301 "parser.yy"
                                                       { (yylhs.value.script_sb) = NULL; sb_push((yylhs.value.script_sb),(yystack_[1].value.stmt)); }
#line 612 "parser.tab.cc"
    break;

  case 4: // scriptContent: scriptContent scriptContentStmt ";"
#line 302 "parser.yy"
                                                       { (yylhs.value.script_sb) = (yystack_[2].value.script_sb); sb_push((yylhs.value.script_sb),(yystack_[1].value.stmt)); }
#line 618 "parser.tab.cc"
    break;

  case 5: // scriptContentStmt: moduleStmt
#line 305 "parser.yy"
                    { (yylhs.value.stmt) = (yystack_[0].value.stmt); }
#line 624 "parser.tab.cc"
    break;

  case 6: // moduleStmt: "mod" "<val_id>" "{" moduleContent "}"
#line 313 "parser.yy"
                                                            { (yylhs.value.stmt) = NewAstModuleStmtWithStmtSb(yylhs.location, (yystack_[3].value.pdm::parser::TokenInfo).ID_symbolID, (yystack_[1].value.stmt_sb)); }
#line 630 "parser.tab.cc"
    break;

  case 7: // moduleContent: moduleContentStmt ";"
#line 316 "parser.yy"
                                                       { (yylhs.value.stmt_sb) = NULL; sb_push((yylhs.value.stmt_sb), (yystack_[1].value.stmt)); }
#line 636 "parser.tab.cc"
    break;

  case 8: // moduleContent: moduleContent moduleContentStmt ";"
#line 317 "parser.yy"
                                                       { (yylhs.value.stmt_sb) = (yystack_[2].value.stmt_sb); sb_push((yylhs.value.stmt_sb), (yystack_[1].value.stmt)); }
#line 642 "parser.tab.cc"
    break;

  case 9: // chainPrefixStmt: letStmt
#line 325 "parser.yy"
                    { (yylhs.value.stmt) = (yystack_[0].value.stmt); }
#line 648 "parser.tab.cc"
    break;

  case 10: // chainPrefixStmt: setStmt
#line 326 "parser.yy"
                    { (yylhs.value.stmt) = (yystack_[0].value.stmt); }
#line 654 "parser.tab.cc"
    break;

  case 11: // chainPrefixStmt: discardStmt
#line 327 "parser.yy"
                    { (yylhs.value.stmt) = (yystack_[0].value.stmt); }
#line 660 "parser.tab.cc"
    break;

  case 12: // letStmt: "let" lpattern "=" expr
#line 330 "parser.yy"
                                        { (yylhs.value.stmt) = NewAstLetStmt(yylhs.location, (yystack_[2].value.lpattern), (yystack_[0].value.exp)); }
#line 666 "parser.tab.cc"
    break;

  case 13: // setStmt: "set" expr "=" expr
#line 333 "parser.yy"
                                    { (yylhs.value.stmt) = NewAstSetStmt(yylhs.location, (yystack_[2].value.exp), (yystack_[0].value.exp)); }
#line 672 "parser.tab.cc"
    break;

  case 14: // discardStmt: expr
#line 336 "parser.yy"
              { (yylhs.value.stmt) = NewAstDiscardStmt(yylhs.location, (yystack_[0].value.exp)); }
#line 678 "parser.tab.cc"
    break;

  case 15: // moduleContentStmt: defStmt
#line 340 "parser.yy"
                            { (yylhs.value.stmt) = (yystack_[0].value.stmt); }
#line 684 "parser.tab.cc"
    break;

  case 16: // moduleContentStmt: typedefStmt
#line 341 "parser.yy"
                            { (yylhs.value.stmt) = (yystack_[0].value.stmt); }
#line 690 "parser.tab.cc"
    break;

  case 17: // moduleContentStmt: typedefStmt_enum
#line 342 "parser.yy"
                            { (yylhs.value.stmt) = (yystack_[0].value.stmt); }
#line 696 "parser.tab.cc"
    break;

  case 18: // moduleContentStmt: importStmt
#line 343 "parser.yy"
                            { (yylhs.value.stmt) = (yystack_[0].value.stmt); }
#line 702 "parser.tab.cc"
    break;

  case 19: // moduleContentStmt: linkStmt
#line 344 "parser.yy"
                            { (yylhs.value.stmt) = (yystack_[0].value.stmt); }
#line 708 "parser.tab.cc"
    break;

  case 20: // moduleContentStmt: moduleStmt
#line 345 "parser.yy"
                            { (yylhs.value.stmt) = (yystack_[0].value.stmt); }
#line 714 "parser.tab.cc"
    break;

  case 21: // defStmt: "fn" vid vpattern "->" expr
#line 348 "parser.yy"
                                                     { (yylhs.value.stmt) = NewAstDefStmt(yylhs.location, (yystack_[3].value.token).ID_symbolID, NULL, (yystack_[2].value.vpattern), (yystack_[0].value.exp)); }
#line 720 "parser.tab.cc"
    break;

  case 22: // defStmt: "fn" vid tpattern vpattern "->" expr
#line 349 "parser.yy"
                                                     { (yylhs.value.stmt) = NewAstDefStmt(yylhs.location, (yystack_[4].value.token).ID_symbolID, (yystack_[3].value.tpattern),   (yystack_[2].value.vpattern), (yystack_[0].value.exp)); }
#line 726 "parser.tab.cc"
    break;

  case 23: // typedefStmt: "type" tid tpattern "=" typespec
#line 352 "parser.yy"
                                                 { (yylhs.value.stmt) = NewAstTypedefStmt(yylhs.location, (yystack_[3].value.token).ID_symbolID, (yystack_[2].value.tpattern), (yystack_[0].value.typespec)); }
#line 732 "parser.tab.cc"
    break;

  case 24: // typedefStmt_enum: "enum" tid tpattern "=" structTypespec
#line 355 "parser.yy"
                                                      { (yylhs.value.stmt) = NewAstTypedefEnumStmt(yylhs.location, (yystack_[3].value.token).ID_symbolID, (yystack_[2].value.tpattern), (yystack_[0].value.typespec)); }
#line 738 "parser.tab.cc"
    break;

  case 25: // importStmt: "import" vid "from" stringl "as" stringl
#line 359 "parser.yy"
                                                            { (yylhs.value.stmt) = NewAstImportStmt(yylhs.location, (yystack_[4].value.token).ID_symbolID, (yystack_[2].value.token).String_utf8string, (yystack_[0].value.token).String_utf8string); }
#line 744 "parser.tab.cc"
    break;

  case 26: // linkStmt: "link" stringl "{" linkStmtContent "}"
#line 363 "parser.yy"
                                                               { (yylhs.value.stmt) = NewAstLinkStmt(yylhs.location, (yystack_[3].value.token).String_utf8string, (yystack_[1].value.stmt_sb)); }
#line 750 "parser.tab.cc"
    break;

  case 27: // linkStmtItem: vid vpattern "->" typespec "from" stringl
#line 366 "parser.yy"
                                                            { (yylhs.value.stmt) = NewAstLinkStmtItem(yylhs.location, (yystack_[5].value.token).ID_symbolID, (yystack_[4].value.vpattern), NewAstType2Val(yystack_[2].location,(yystack_[2].value.typespec)), (yystack_[0].value.token).String_utf8string); }
#line 756 "parser.tab.cc"
    break;

  case 28: // linkStmtContent: linkStmtItem ";"
#line 369 "parser.yy"
                                                    { (yylhs.value.stmt_sb).push_back((yystack_[1].value.stmt)); }
#line 762 "parser.tab.cc"
    break;

  case 29: // linkStmtContent: linkStmtContent linkStmtItem ";"
#line 370 "parser.yy"
                                                    { (yylhs.value.stmt_sb) = (yystack_[2].value.stmt_sb); (yylhs.value.stmt_sb).push_back((yystack_[1].value.stmt)); }
#line 768 "parser.tab.cc"
    break;

  case 30: // tid: "<TypeId>"
#line 377 "parser.yy"
                { (yylhs.value.token) = (yystack_[0].value.pdm::parser::TokenInfo); }
#line 774 "parser.tab.cc"
    break;

  case 31: // vid: "<val_id>"
#line 378 "parser.yy"
                { (yylhs.value.token) = (yystack_[0].value.pdm::parser::TokenInfo); }
#line 780 "parser.tab.cc"
    break;

  case 32: // floatl: "4.2"
#line 380 "parser.yy"
                    { (yylhs.value.token) = (yystack_[0].value.token); }
#line 786 "parser.tab.cc"
    break;

  case 33: // stringl: "'sq-string-literal'"
#line 383 "parser.yy"
                        { (yylhs.value.token) = (yystack_[0].value.token); }
#line 792 "parser.tab.cc"
    break;

  case 34: // stringl: "\"dq-string-literal\""
#line 384 "parser.yy"
                        { (yylhs.value.token) = (yystack_[0].value.token); }
#line 798 "parser.tab.cc"
    break;

  case 35: // expr: binaryExpr
#line 391 "parser.yy"
                    { (yylhs.value.exp) = (yystack_[0].value.exp); }
#line 804 "parser.tab.cc"
    break;

  case 36: // expr_cl1: expr
#line 394 "parser.yy"
                                { (yylhs.value.exp_sb) = NULL; sb_push(((yylhs.value.exp_sb)),(yystack_[0].value.exp)); }
#line 810 "parser.tab.cc"
    break;

  case 37: // expr_cl1: expr_cl1 "," expr
#line 395 "parser.yy"
                                { (yylhs.value.exp_sb) = (yystack_[2].value.exp_sb); sb_push(((yylhs.value.exp_sb)),(yystack_[0].value.exp)); }
#line 816 "parser.tab.cc"
    break;

  case 38: // expr_cl2: expr "," expr
#line 398 "parser.yy"
                                { (yylhs.value.exp_sb) = NULL; sb_push((yylhs.value.exp_sb),(yystack_[2].value.exp)); sb_push((yylhs.value.exp_sb),(yystack_[0].value.exp)); }
#line 822 "parser.tab.cc"
    break;

  case 39: // expr_cl2: expr_cl2 "," expr
#line 399 "parser.yy"
                                { (yylhs.value.exp_sb) = (yystack_[2].value.exp_sb); sb_push((yylhs.value.exp_sb),(yystack_[0].value.exp)); }
#line 828 "parser.tab.cc"
    break;

  case 40: // parenExpr: unitExpr
#line 403 "parser.yy"
                    { (yylhs.value.exp) = (yystack_[0].value.exp); }
#line 834 "parser.tab.cc"
    break;

  case 41: // parenExpr: vparenExpr
#line 404 "parser.yy"
                    { (yylhs.value.exp) = (yystack_[0].value.exp); }
#line 840 "parser.tab.cc"
    break;

  case 42: // parenExpr: vtupleExpr
#line 405 "parser.yy"
                    { (yylhs.value.exp) = (yystack_[0].value.exp); }
#line 846 "parser.tab.cc"
    break;

  case 43: // parenExpr: vstructExpr
#line 406 "parser.yy"
                    { (yylhs.value.exp) = (yystack_[0].value.exp); }
#line 852 "parser.tab.cc"
    break;

  case 44: // parenExpr: chainExpr
#line 407 "parser.yy"
                    { (yylhs.value.exp) = (yystack_[0].value.exp); }
#line 858 "parser.tab.cc"
    break;

  case 45: // parenExpr: vlambdaExpr
#line 408 "parser.yy"
                    { (yylhs.value.exp) = (yystack_[0].value.exp); }
#line 864 "parser.tab.cc"
    break;

  case 47: // primaryExpr: parenExpr
#line 414 "parser.yy"
                     { (yylhs.value.exp) = (yystack_[0].value.exp); }
#line 870 "parser.tab.cc"
    break;

  case 48: // primaryExpr: vid
#line 415 "parser.yy"
                     { (yylhs.value.exp) = NewAstVID(yylhs.location, (yystack_[0].value.token).ID_symbolID); }
#line 876 "parser.tab.cc"
    break;

  case 49: // primaryExpr: "42"
#line 416 "parser.yy"
                     { (yylhs.value.exp) = NewAstIntLiteral(yylhs.location, (yystack_[0].value.token).Int, 10); }
#line 882 "parser.tab.cc"
    break;

  case 50: // primaryExpr: "0x2a"
#line 417 "parser.yy"
                     { (yylhs.value.exp) = NewAstIntLiteral(yylhs.location, (yystack_[0].value.token).Int, 16); }
#line 888 "parser.tab.cc"
    break;

  case 51: // primaryExpr: floatl
#line 418 "parser.yy"
                     { (yylhs.value.exp) = NewAstFloatLiteral(yylhs.location, (yystack_[0].value.token).Float); }
#line 894 "parser.tab.cc"
    break;

  case 52: // primaryExpr: stringl
#line 419 "parser.yy"
                     { (yylhs.value.exp) = NewAstStringLiteral(yylhs.location, (yystack_[0].value.token).String_utf8string); }
#line 900 "parser.tab.cc"
    break;

  case 53: // primaryExpr: ifThenElseExpr
#line 420 "parser.yy"
                     { (yylhs.value.exp) = (yystack_[0].value.exp); }
#line 906 "parser.tab.cc"
    break;

  case 54: // vparenExpr: "(" expr ")"
#line 423 "parser.yy"
                                { (yylhs.value.exp) = NewAstVParen(yylhs.location, (yystack_[1].value.exp)); }
#line 912 "parser.tab.cc"
    break;

  case 55: // vtupleExpr: "(" expr_cl2 ")"
#line 426 "parser.yy"
                                        { (yylhs.value.exp) = NewAstVTupleWithFieldsSb(yylhs.location, (yystack_[1].value.exp_sb)); }
#line 918 "parser.tab.cc"
    break;

  case 56: // vstructExpr: "{" vstructExprField_cl "}"
#line 429 "parser.yy"
                                                  { (yylhs.value.exp) = NewAstVStructWithFieldsSb(yylhs.location, (yystack_[1].value.structexp_field_sb)); }
#line 924 "parser.tab.cc"
    break;

  case 57: // ifThenElseExpr: "if" parenExpr "then" parenExpr
#line 432 "parser.yy"
                                                                     { (yylhs.value.exp) = NewAstIte(yylhs.location, (yystack_[2].value.exp), (yystack_[0].value.exp), NULL); }
#line 930 "parser.tab.cc"
    break;

  case 58: // ifThenElseExpr: "if" parenExpr "then" parenExpr "else" primaryExpr
#line 433 "parser.yy"
                                                                     { (yylhs.value.exp) = NewAstIte(yylhs.location, (yystack_[4].value.exp), (yystack_[2].value.exp), (yystack_[0].value.exp)); }
#line 936 "parser.tab.cc"
    break;

  case 59: // chainExpr: "{" expr "}"
#line 436 "parser.yy"
                                                { (yylhs.value.exp) = NewAstChainWith(yylhs.location, NULL, (yystack_[1].value.exp)); }
#line 942 "parser.tab.cc"
    break;

  case 60: // chainExpr: "{" chainPrefix "}"
#line 437 "parser.yy"
                                                { (yylhs.value.exp) = NewAstChainWith(yylhs.location, (yystack_[1].value.stmt_sb), NULL); }
#line 948 "parser.tab.cc"
    break;

  case 61: // chainExpr: "{" chainPrefix expr "}"
#line 438 "parser.yy"
                                                { (yylhs.value.exp) = NewAstChainWith(yylhs.location, (yystack_[2].value.stmt_sb), (yystack_[1].value.exp)); }
#line 954 "parser.tab.cc"
    break;

  case 62: // chainPrefix: chainPrefixStmt ";"
#line 441 "parser.yy"
                                                { (yylhs.value.stmt_sb) = NULL; sb_push(((yylhs.value.stmt_sb)),(yystack_[1].value.stmt)); }
#line 960 "parser.tab.cc"
    break;

  case 63: // chainPrefix: chainPrefix chainPrefixStmt ";"
#line 442 "parser.yy"
                                                { (yylhs.value.stmt_sb) = (yystack_[2].value.stmt_sb); sb_push(((yylhs.value.stmt_sb)),(yystack_[1].value.stmt)); }
#line 966 "parser.tab.cc"
    break;

  case 64: // vlambdaExpr: "fn" lpattern parenExpr
#line 445 "parser.yy"
                                    { (yylhs.value.exp) = NULL; }
#line 972 "parser.tab.cc"
    break;

  case 65: // postfixExpr: primaryExpr
#line 449 "parser.yy"
                    { (yylhs.value.exp) = (yystack_[0].value.exp); }
#line 978 "parser.tab.cc"
    break;

  case 66: // postfixExpr: vtcallExpr
#line 450 "parser.yy"
                    { (yylhs.value.exp) = (yystack_[0].value.exp); }
#line 984 "parser.tab.cc"
    break;

  case 67: // postfixExpr: vvcallExpr
#line 451 "parser.yy"
                    { (yylhs.value.exp) = (yystack_[0].value.exp); }
#line 990 "parser.tab.cc"
    break;

  case 68: // postfixExpr: dotNmExpr
#line 452 "parser.yy"
                    { (yylhs.value.exp) = (yystack_[0].value.exp); }
#line 996 "parser.tab.cc"
    break;

  case 69: // postfixExpr: dotIxExpr
#line 453 "parser.yy"
                    { (yylhs.value.exp) = (yystack_[0].value.exp); }
#line 1002 "parser.tab.cc"
    break;

  case 70: // vtcallExpr: postfixExpr "[" vtarg_cl "]"
#line 456 "parser.yy"
                                                { (yylhs.value.exp) = NewAstTCallWithArgsSb(yylhs.location, (yystack_[3].value.exp), (yystack_[1].value.tcall_arg_sb)); }
#line 1008 "parser.tab.cc"
    break;

  case 71: // vvcallExpr: postfixExpr "(" ")"
#line 459 "parser.yy"
                                                { (yylhs.value.exp) = NewAstVCallWithArgsSb(yylhs.location, (yystack_[2].value.exp), NULL); }
#line 1014 "parser.tab.cc"
    break;

  case 72: // vvcallExpr: postfixExpr "(" expr_cl1 ")"
#line 460 "parser.yy"
                                                 { (yylhs.value.exp) = NewAstVCallWithArgsSb(yylhs.location, (yystack_[3].value.exp), (yystack_[1].value.exp_sb)); }
#line 1020 "parser.tab.cc"
    break;

  case 73: // dotNmExpr: postfixExpr "." "<val_id>"
#line 463 "parser.yy"
                                        { (yylhs.value.exp) = NewAstDotName(yylhs.location, (yystack_[2].value.exp), (yystack_[0].value.pdm::parser::TokenInfo).ID_symbolID); }
#line 1026 "parser.tab.cc"
    break;

  case 74: // dotIxExpr: postfixExpr "." "42"
#line 466 "parser.yy"
                                        { (yylhs.value.exp) = NewAstDotIndex(yylhs.location, (yystack_[2].value.exp), (yystack_[0].value.token).Int); }
#line 1032 "parser.tab.cc"
    break;

  case 75: // unaryExpr: postfixExpr
#line 470 "parser.yy"
                            { (yylhs.value.exp) = (yystack_[0].value.exp); }
#line 1038 "parser.tab.cc"
    break;

  case 76: // unaryExpr: unaryOp unaryExpr
#line 471 "parser.yy"
                            { (yylhs.value.exp) = NewAstUnary(yylhs.location, (yystack_[1].value.uop), (yystack_[0].value.exp)); }
#line 1044 "parser.tab.cc"
    break;

  case 77: // unaryOp: "+"
#line 474 "parser.yy"
                    { (yylhs.value.uop) = UOP_PLUS; }
#line 1050 "parser.tab.cc"
    break;

  case 78: // unaryOp: "-"
#line 475 "parser.yy"
                    { (yylhs.value.uop) = UOP_MINUS; }
#line 1056 "parser.tab.cc"
    break;

  case 79: // unaryOp: "*"
#line 476 "parser.yy"
                    { (yylhs.value.uop) = UOP_DEREF; }
#line 1062 "parser.tab.cc"
    break;

  case 80: // unaryOp: "^"
#line 477 "parser.yy"
                    { (yylhs.value.uop) = UOP_GETREF; }
#line 1068 "parser.tab.cc"
    break;

  case 81: // unaryOp: "not"
#line 478 "parser.yy"
                    { (yylhs.value.uop) = UOP_NOT; }
#line 1074 "parser.tab.cc"
    break;

  case 82: // binaryExpr: orBinaryExpr
#line 482 "parser.yy"
                    { (yylhs.value.exp) = (yystack_[0].value.exp); }
#line 1080 "parser.tab.cc"
    break;

  case 83: // mulBinaryOp: "*"
#line 485 "parser.yy"
                    { (yylhs.value.bop) = BOP_MUL; }
#line 1086 "parser.tab.cc"
    break;

  case 84: // mulBinaryOp: "/"
#line 486 "parser.yy"
                    { (yylhs.value.bop) = BOP_DIV; }
#line 1092 "parser.tab.cc"
    break;

  case 85: // mulBinaryOp: "%"
#line 487 "parser.yy"
                    { (yylhs.value.bop) = BOP_REM; }
#line 1098 "parser.tab.cc"
    break;

  case 86: // mulBinaryExpr: unaryExpr
#line 490 "parser.yy"
                                            { (yylhs.value.exp) = (yystack_[0].value.exp); }
#line 1104 "parser.tab.cc"
    break;

  case 87: // mulBinaryExpr: mulBinaryExpr mulBinaryOp unaryExpr
#line 491 "parser.yy"
                                            { (yylhs.value.exp) = NewAstBinary(yylhs.location, (yystack_[1].value.bop), (yystack_[2].value.exp), (yystack_[0].value.exp)); }
#line 1110 "parser.tab.cc"
    break;

  case 88: // addBinaryOp: "+"
#line 494 "parser.yy"
                { (yylhs.value.bop) = BOP_ADD; }
#line 1116 "parser.tab.cc"
    break;

  case 89: // addBinaryOp: "-"
#line 495 "parser.yy"
                { (yylhs.value.bop) = BOP_SUBTRACT; }
#line 1122 "parser.tab.cc"
    break;

  case 90: // addBinaryExpr: mulBinaryExpr
#line 498 "parser.yy"
                                                { (yylhs.value.exp) = (yystack_[0].value.exp); }
#line 1128 "parser.tab.cc"
    break;

  case 91: // addBinaryExpr: addBinaryExpr addBinaryOp mulBinaryExpr
#line 499 "parser.yy"
                                                { (yylhs.value.exp) = NewAstBinary(yylhs.location, (yystack_[1].value.bop), (yystack_[2].value.exp), (yystack_[0].value.exp)); }
#line 1134 "parser.tab.cc"
    break;

  case 92: // cmpBinaryOp: "<"
#line 502 "parser.yy"
                    { (yylhs.value.bop) = BOP_LTHAN; }
#line 1140 "parser.tab.cc"
    break;

  case 93: // cmpBinaryOp: "<="
#line 503 "parser.yy"
                    { (yylhs.value.bop) = BOP_LETHAN; }
#line 1146 "parser.tab.cc"
    break;

  case 94: // cmpBinaryOp: ">"
#line 504 "parser.yy"
                    { (yylhs.value.bop) = BOP_GTHAN; }
#line 1152 "parser.tab.cc"
    break;

  case 95: // cmpBinaryOp: ">="
#line 505 "parser.yy"
                    { (yylhs.value.bop) = BOP_GETHAN; }
#line 1158 "parser.tab.cc"
    break;

  case 96: // cmpBinaryExpr: addBinaryExpr
#line 508 "parser.yy"
                                                { (yylhs.value.exp) = (yystack_[0].value.exp); }
#line 1164 "parser.tab.cc"
    break;

  case 97: // cmpBinaryExpr: cmpBinaryExpr cmpBinaryOp addBinaryExpr
#line 509 "parser.yy"
                                                { (yylhs.value.exp) = NewAstBinary(yylhs.location, (yystack_[1].value.bop), (yystack_[2].value.exp), (yystack_[0].value.exp)); }
#line 1170 "parser.tab.cc"
    break;

  case 98: // eqBinaryOp: "=="
#line 512 "parser.yy"
                    { (yylhs.value.bop) = BOP_EQUALS; }
#line 1176 "parser.tab.cc"
    break;

  case 99: // eqBinaryOp: "!="
#line 513 "parser.yy"
                    { (yylhs.value.bop) = BOP_NEQUALS; }
#line 1182 "parser.tab.cc"
    break;

  case 100: // eqBinaryExpr: cmpBinaryExpr
#line 516 "parser.yy"
                                            { (yylhs.value.exp) = (yystack_[0].value.exp); }
#line 1188 "parser.tab.cc"
    break;

  case 101: // eqBinaryExpr: eqBinaryExpr eqBinaryOp cmpBinaryExpr
#line 517 "parser.yy"
                                            { (yylhs.value.exp) = NewAstBinary(yylhs.location, (yystack_[1].value.bop), (yystack_[2].value.exp), (yystack_[0].value.exp)); }
#line 1194 "parser.tab.cc"
    break;

  case 102: // andBinaryExpr: eqBinaryExpr
#line 520 "parser.yy"
                                            { (yylhs.value.exp) = (yystack_[0].value.exp); }
#line 1200 "parser.tab.cc"
    break;

  case 103: // andBinaryExpr: andBinaryExpr "and" eqBinaryExpr
#line 521 "parser.yy"
                                            { (yylhs.value.exp) = NewAstBinary(yylhs.location, BOP_AND, (yystack_[2].value.exp), (yystack_[0].value.exp)); }
#line 1206 "parser.tab.cc"
    break;

  case 104: // xorBinaryExpr: andBinaryExpr
#line 524 "parser.yy"
                                            { (yylhs.value.exp) = (yystack_[0].value.exp); }
#line 1212 "parser.tab.cc"
    break;

  case 105: // xorBinaryExpr: xorBinaryExpr "xor" andBinaryExpr
#line 525 "parser.yy"
                                            { (yylhs.value.exp) = NewAstBinary(yylhs.location, BOP_XOR, (yystack_[2].value.exp), (yystack_[0].value.exp)); }
#line 1218 "parser.tab.cc"
    break;

  case 106: // orBinaryExpr: xorBinaryExpr
#line 528 "parser.yy"
                                            { (yylhs.value.exp) = (yystack_[0].value.exp); }
#line 1224 "parser.tab.cc"
    break;

  case 107: // orBinaryExpr: orBinaryExpr "or" xorBinaryExpr
#line 529 "parser.yy"
                                            { (yylhs.value.exp) = NewAstBinary(yylhs.location, BOP_OR, (yystack_[2].value.exp), (yystack_[0].value.exp)); }
#line 1230 "parser.tab.cc"
    break;

  case 108: // typespec: unaryTypespec
#line 537 "parser.yy"
                     { (yylhs.value.typespec) = (yystack_[0].value.typespec); }
#line 1236 "parser.tab.cc"
    break;

  case 109: // typespec_cl: typespec
#line 540 "parser.yy"
                                    { (yylhs.value.typespec_sb) = NULL; sb_push((yylhs.value.typespec_sb),(yystack_[0].value.typespec)); }
#line 1242 "parser.tab.cc"
    break;

  case 110: // typespec_cl: typespec_cl "," typespec
#line 541 "parser.yy"
                                    { (yylhs.value.typespec_sb) = (yystack_[2].value.typespec_sb); sb_push((yylhs.value.typespec_sb),(yystack_[0].value.typespec)); }
#line 1248 "parser.tab.cc"
    break;

  case 113: // structTypespecField_cl: structTypespecField_cl "," structTypespecField
#line 549 "parser.yy"
      { (yylhs.value.structts_field_sb) = (yystack_[2].value.structts_field_sb); }
#line 1254 "parser.tab.cc"
    break;

  case 114: // primaryTypespec: tid
#line 553 "parser.yy"
                        { (yylhs.value.typespec) = NewAstTID(yylhs.location, (yystack_[0].value.token).ID_symbolID); }
#line 1260 "parser.tab.cc"
    break;

  case 115: // primaryTypespec: parenTypespec
#line 554 "parser.yy"
                        { (yylhs.value.typespec) = (yystack_[0].value.typespec); }
#line 1266 "parser.tab.cc"
    break;

  case 116: // primaryTypespec: structTypespec
#line 555 "parser.yy"
                        { (yylhs.value.typespec) = (yystack_[0].value.typespec); }
#line 1272 "parser.tab.cc"
    break;

  case 117: // primaryTypespec: tupleTypespec
#line 556 "parser.yy"
                        { (yylhs.value.typespec) = (yystack_[0].value.typespec); }
#line 1278 "parser.tab.cc"
    break;

  case 121: // postfixTypespec: primaryTypespec
#line 569 "parser.yy"
                       { (yylhs.value.typespec) = (yystack_[0].value.typespec); }
#line 1284 "parser.tab.cc"
    break;

  case 122: // postfixTypespec: ttcall
#line 570 "parser.yy"
      { (yylhs.value.typespec) = (yystack_[0].value.typespec); }
#line 1290 "parser.tab.cc"
    break;

  case 123: // postfixTypespec: tdot
#line 571 "parser.yy"
      { (yylhs.value.typespec) = (yystack_[0].value.typespec); }
#line 1296 "parser.tab.cc"
    break;

  case 124: // ttcall: postfixTypespec "[" ttarg_cl "]"
#line 574 "parser.yy"
                                                    { (yylhs.value.typespec) = NewAstTCallWithArgsSb(yylhs.location, (yystack_[3].value.typespec), (yystack_[1].value.tcall_arg_sb)); }
#line 1302 "parser.tab.cc"
    break;

  case 125: // tdot: postfixTypespec "." "<val_id>"
#line 576 "parser.yy"
      { (yylhs.value.typespec) = (yystack_[2].value.typespec); }
#line 1308 "parser.tab.cc"
    break;

  case 126: // unaryTypespec: postfixTypespec
#line 580 "parser.yy"
                                    { (yylhs.value.typespec) = (yystack_[0].value.typespec); }
#line 1314 "parser.tab.cc"
    break;

  case 127: // unaryTypespec: "&" unaryTypespec
#line 581 "parser.yy"
                                    { (yylhs.value.typespec) = NewAstTMut(yylhs.location,(yystack_[0].value.typespec)); }
#line 1320 "parser.tab.cc"
    break;

  case 128: // unaryTypespec: "^" unaryTypespec
#line 582 "parser.yy"
                                    { (yylhs.value.typespec) = NewAstTPtr(yylhs.location,(yystack_[0].value.typespec)); }
#line 1326 "parser.tab.cc"
    break;

  case 129: // ttarg: typespec
#line 587 "parser.yy"
                { (yylhs.value.tcall_arg) = (yystack_[0].value.typespec); }
#line 1332 "parser.tab.cc"
    break;

  case 130: // ttarg: expr
#line 588 "parser.yy"
                { (yylhs.value.tcall_arg) = NewAstVal2Type(yylhs.location,(yystack_[0].value.exp)); }
#line 1338 "parser.tab.cc"
    break;

  case 131: // ttarg_cl: ttarg
#line 591 "parser.yy"
                                { (yylhs.value.tcall_arg_sb) = NULL; sb_push((yylhs.value.tcall_arg_sb),(yystack_[0].value.tcall_arg)); }
#line 1344 "parser.tab.cc"
    break;

  case 132: // ttarg_cl: ttarg_cl "," ttarg
#line 592 "parser.yy"
                                { (yylhs.value.tcall_arg_sb) = (yystack_[2].value.tcall_arg_sb); sb_push((yylhs.value.tcall_arg_sb),(yystack_[0].value.tcall_arg)); }
#line 1350 "parser.tab.cc"
    break;

  case 133: // vtarg: typespec
#line 597 "parser.yy"
               { (yylhs.value.tcall_arg) = NewAstType2Val(yylhs.location,(yystack_[0].value.typespec)); }
#line 1356 "parser.tab.cc"
    break;

  case 134: // vtarg: expr
#line 598 "parser.yy"
               { (yylhs.value.tcall_arg) = (yystack_[0].value.exp); }
#line 1362 "parser.tab.cc"
    break;

  case 135: // vtarg_cl: vtarg
#line 601 "parser.yy"
                                { (yylhs.value.tcall_arg_sb) = NULL; sb_push((yylhs.value.tcall_arg_sb),(yystack_[0].value.tcall_arg)); }
#line 1368 "parser.tab.cc"
    break;

  case 136: // vtarg_cl: vtarg_cl "," vtarg
#line 602 "parser.yy"
                                { (yylhs.value.tcall_arg_sb) = (yystack_[2].value.tcall_arg_sb); sb_push((yylhs.value.tcall_arg_sb),(yystack_[0].value.tcall_arg)); }
#line 1374 "parser.tab.cc"
    break;

  case 137: // vstructExprField: vid "=" expr
#line 610 "parser.yy"
                       { (yylhs.value.structexp_field) = NewAstField(yylhs.location, (yystack_[2].value.token).ID_symbolID, (yystack_[0].value.exp)); }
#line 1380 "parser.tab.cc"
    break;

  case 138: // vpatternField: vid typespec
#line 613 "parser.yy"
                   { (yylhs.value.vpattern_field) = NewAstField(yylhs.location, (yystack_[1].value.token).ID_symbolID, NewAstType2Val(yystack_[0].location,(yystack_[0].value.typespec))); }
#line 1386 "parser.tab.cc"
    break;

  case 139: // lpatternField: vpatternField
#line 616 "parser.yy"
                    { (yylhs.value.lpattern_field) = (yystack_[0].value.vpattern_field); }
#line 1392 "parser.tab.cc"
    break;

  case 140: // lpatternField: vid
#line 617 "parser.yy"
                    { (yylhs.value.lpattern_field) = NewAstField(yylhs.location, (yystack_[0].value.token).ID_symbolID, NULL); }
#line 1398 "parser.tab.cc"
    break;

  case 141: // tpatternField: tid
#line 620 "parser.yy"
                    { (yylhs.value.tpattern_field) = NewAstField(yylhs.location, (yystack_[0].value.token).ID_symbolID, NULL); }
#line 1404 "parser.tab.cc"
    break;

  case 142: // tpatternField: vpatternField
#line 621 "parser.yy"
                    { (yylhs.value.tpattern_field) = (yystack_[0].value.vpattern_field); }
#line 1410 "parser.tab.cc"
    break;

  case 143: // lpattern: lpatternField
#line 624 "parser.yy"
                                            { (yylhs.value.lpattern) = NewAstVPatternSingleton(yylhs.location,(yystack_[0].value.lpattern_field)); }
#line 1416 "parser.tab.cc"
    break;

  case 144: // lpattern: "(" lpatternField_cl ")"
#line 625 "parser.yy"
                                            { (yylhs.value.lpattern) = NewAstVPatternWithFieldsSb(yylhs.location,(yystack_[1].value.lpattern_field_sb)); }
#line 1422 "parser.tab.cc"
    break;

  case 145: // lpattern: "(" ")"
#line 626 "parser.yy"
                                            { (yylhs.value.lpattern) = NewAstVPatternWithFieldsSb(yylhs.location,NULL); }
#line 1428 "parser.tab.cc"
    break;

  case 146: // vpattern: "(" vpatternField_cl ")"
#line 629 "parser.yy"
                                            { (yylhs.value.vpattern) = NewAstVPatternWithFieldsSb(yylhs.location,(yystack_[1].value.vpattern_field_sb)); }
#line 1434 "parser.tab.cc"
    break;

  case 147: // vpattern: "(" ")"
#line 630 "parser.yy"
                                            { (yylhs.value.vpattern) = NewAstVPatternWithFieldsSb(yylhs.location,NULL); }
#line 1440 "parser.tab.cc"
    break;

  case 148: // tpattern: "[" tpatternField_cl "]"
#line 633 "parser.yy"
                                            { (yylhs.value.tpattern) = NewAstVPatternWithFieldsSb(yylhs.location,(yystack_[1].value.tpattern_field_sb)); }
#line 1446 "parser.tab.cc"
    break;

  case 149: // tpattern: "<" tpatternField_cl ">"
#line 634 "parser.yy"
                                            { (yylhs.value.tpattern) = NewAstVPatternWithFieldsSb(yylhs.location,(yystack_[1].value.tpattern_field_sb)); }
#line 1452 "parser.tab.cc"
    break;

  case 150: // vpatternField_cl: vpatternField
#line 638 "parser.yy"
                                                { (yylhs.value.vpattern_field_sb) = NULL; sb_push((yylhs.value.vpattern_field_sb),(yystack_[0].value.vpattern_field)); }
#line 1458 "parser.tab.cc"
    break;

  case 151: // vpatternField_cl: vpatternField_cl "," vpatternField
#line 639 "parser.yy"
                                                { (yylhs.value.vpattern_field_sb) = (yystack_[2].value.vpattern_field_sb); sb_push((yylhs.value.vpattern_field_sb),(yystack_[0].value.vpattern_field)); }
#line 1464 "parser.tab.cc"
    break;

  case 152: // lpatternField_cl: lpatternField
#line 642 "parser.yy"
                                                { (yylhs.value.lpattern_field_sb) = NULL; sb_push((yylhs.value.lpattern_field_sb),(yystack_[0].value.lpattern_field)); }
#line 1470 "parser.tab.cc"
    break;

  case 153: // lpatternField_cl: lpatternField_cl "," lpatternField
#line 643 "parser.yy"
                                                { (yylhs.value.lpattern_field_sb) = (yystack_[2].value.lpattern_field_sb); sb_push((yylhs.value.lpattern_field_sb),(yystack_[0].value.lpattern_field)); }
#line 1476 "parser.tab.cc"
    break;

  case 154: // tpatternField_cl: tpatternField
#line 646 "parser.yy"
                                                { (yylhs.value.tpattern_field_sb) = NULL; sb_push((yylhs.value.tpattern_field_sb),(yystack_[0].value.tpattern_field)); }
#line 1482 "parser.tab.cc"
    break;

  case 155: // tpatternField_cl: tpatternField_cl "," tpatternField
#line 647 "parser.yy"
                                                { (yylhs.value.tpattern_field_sb) = (yystack_[2].value.tpattern_field_sb); sb_push((yylhs.value.tpattern_field_sb),(yystack_[0].value.tpattern_field)); }
#line 1488 "parser.tab.cc"
    break;

  case 156: // vstructExprField_cl: vstructExprField
#line 650 "parser.yy"
                                                    { (yylhs.value.structexp_field_sb) = NULL; sb_push((yylhs.value.structexp_field_sb),(yystack_[0].value.structexp_field)); }
#line 1494 "parser.tab.cc"
    break;

  case 157: // vstructExprField_cl: vstructExprField_cl "," vstructExprField
#line 651 "parser.yy"
                                                    { (yylhs.value.structexp_field_sb) = (yystack_[2].value.structexp_field_sb); sb_push((yylhs.value.structexp_field_sb),(yystack_[0].value.structexp_field)); }
#line 1500 "parser.tab.cc"
    break;


#line 1504 "parser.tab.cc"

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





  const short parser::yypact_ninf_ = -144;

  const signed char parser::yytable_ninf_ = -1;

  const short
  parser::yypact_[] =
  {
       6,    33,    56,     6,     4,  -144,    21,  -144,    46,  -144,
     160,  -144,    91,   134,    91,    93,    93,  -144,   179,    71,
    -144,  -144,  -144,  -144,  -144,  -144,    99,  -144,  -144,    67,
      -5,  -144,    38,    38,  -144,    82,  -144,   134,    91,    12,
     172,   172,    95,    88,   103,   114,  -144,   124,   111,    17,
      88,  -144,    15,  -144,    69,  -144,  -144,  -144,    59,    27,
     369,   140,    15,   151,   134,  -144,  -144,   163,   152,    15,
      15,    91,    15,    15,  -144,  -144,  -144,  -144,  -144,  -144,
      -6,  -144,  -144,  -144,    91,  -144,   172,  -144,  -144,    -1,
       9,  -144,  -144,  -144,  -144,   307,   276,  -144,  -144,  -144,
    -144,  -144,  -144,  -144,  -144,  -144,  -144,  -144,  -144,  -144,
    -144,  -144,  -144,  -144,    16,  -144,  -144,  -144,  -144,  -144,
     369,  -144,   127,   143,   157,   158,   181,   186,   189,   369,
    -144,  -144,  -144,  -144,    15,   185,  -144,    60,    15,  -144,
      48,  -144,  -144,   215,   211,  -144,  -144,   212,    31,    15,
    -144,  -144,    -1,  -144,    94,   101,     9,   369,   190,  -144,
    -144,  -144,   171,   187,   245,  -144,    49,    18,   338,   211,
    -144,  -144,  -144,  -144,   369,  -144,  -144,   369,  -144,  -144,
    -144,  -144,   369,  -144,  -144,   369,   369,   369,   369,  -144,
     210,  -144,    15,  -144,  -144,    91,  -144,  -144,   122,   276,
      15,  -144,  -144,  -144,    76,    -1,  -144,  -144,   109,  -144,
     369,  -144,   369,  -144,   174,   175,  -144,   369,  -144,  -144,
     195,   191,    91,  -144,  -144,  -144,  -144,  -144,   120,  -144,
    -144,  -144,    90,  -144,   127,   143,   157,   158,   181,   186,
     134,  -144,  -144,    10,   211,  -144,   221,    91,  -144,  -144,
    -144,   369,   369,  -144,  -144,  -144,   171,  -144,   369,  -144,
     211,  -144,  -144,  -144,    92,  -144,  -144,  -144,  -144,  -144,
    -144
  };

  const unsigned char
  parser::yydefact_[] =
  {
       0,     0,     0,     2,     0,     5,     0,     1,     0,     3,
       0,     4,     0,     0,     0,     0,     0,    20,     0,     0,
      15,    16,    17,    18,    19,    31,     0,    34,    33,     0,
       0,    30,     0,     0,     6,     0,     7,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     8,     0,     0,     0,
       0,   147,     0,   150,     0,   141,   142,   154,     0,     0,
       0,     0,     0,     0,     0,    28,    26,     0,     0,     0,
       0,     0,     0,     0,   114,   138,   121,   115,   116,   117,
     126,   122,   123,   108,     0,   146,     0,   148,   149,     0,
       0,    81,    49,    50,    32,     0,     0,    79,    77,    78,
      80,    48,    51,    52,    21,    47,    40,    65,    41,    42,
      43,    53,    44,    45,    75,    66,    67,    68,    69,    86,
       0,    35,    90,    96,   100,   102,   104,   106,    82,     0,
      23,    24,    25,    29,     0,     0,   109,     0,     0,   112,
       0,   128,   127,     0,     0,   151,   155,     0,     0,   140,
     139,   143,     0,    46,     0,     0,     0,     0,     0,     9,
      10,    11,    48,    14,     0,   156,     0,     0,     0,     0,
      76,    83,    84,    85,     0,    88,    89,     0,    92,    93,
      94,    95,     0,    98,    99,     0,     0,     0,     0,    22,
       0,   118,     0,   120,   111,     0,   119,   125,     0,     0,
      80,   130,   129,   131,     0,     0,   145,   152,     0,    64,
       0,    54,     0,    55,     0,     0,    62,     0,    59,    60,
       0,    14,     0,    56,    73,    74,    71,    36,     0,   134,
     133,   135,     0,    87,    91,    97,   101,   103,   105,   107,
       0,   110,   113,    48,     0,   124,    57,     0,   144,    38,
      39,     0,     0,   137,    63,    61,     0,   157,     0,    72,
       0,    70,    27,   132,     0,   153,    12,    13,    37,   136,
      58
  };

  const short
  parser::yypgoto_[] =
  {
    -144,  -144,  -144,   231,    73,  -144,    78,  -144,  -144,  -144,
     225,  -144,  -144,  -144,  -144,  -144,   196,  -144,     1,   -12,
    -144,    -7,   -56,  -144,  -144,   -88,  -144,   -20,  -144,  -144,
    -144,  -144,  -144,  -144,  -144,  -144,  -144,  -144,  -144,  -144,
    -111,  -144,  -144,  -144,    75,  -144,    64,  -144,    65,  -144,
      70,    68,    72,  -144,   -59,  -144,    66,  -144,  -144,  -144,
     202,  -144,  -144,  -144,  -144,   -65,    24,  -144,    20,  -144,
      37,   -17,  -143,   183,   121,    53,   184,  -144,  -144,   235,
    -144
  };

  const short
  parser::yydefgoto_[] =
  {
      -1,     2,     3,     4,     5,    18,   158,   159,   160,   161,
      19,    20,    21,    22,    23,    24,    48,    49,    74,   101,
     102,   103,   154,   228,   155,   105,   106,   107,   108,   109,
     110,   111,   112,   164,   113,   114,   115,   116,   117,   118,
     119,   120,   121,   174,   122,   177,   123,   182,   124,   185,
     125,   126,   127,   128,    75,   137,   139,   140,    76,    77,
      78,    79,    80,    81,    82,    83,   203,   204,   231,   232,
     165,   150,   151,    57,   152,    42,    43,    54,   208,    58,
     166
  };

  const short
  parser::yytable_[] =
  {
      26,   147,    30,   130,   104,   207,    29,   141,   142,   170,
     135,   136,    25,     1,    31,    25,    32,    33,    90,    31,
      25,   224,    53,    56,    56,   143,    50,    52,    52,    52,
      47,    39,   144,    40,    25,    95,     6,    50,     9,    96,
     163,    55,    55,    41,   225,   148,    69,   167,    70,    51,
      71,    69,   168,    70,   169,    71,     7,   132,    66,   138,
      86,    10,   217,   233,   209,    72,    73,   145,   206,    56,
      72,    73,    52,   189,    52,   190,    40,    88,   149,   194,
      11,   195,   222,    17,   162,   202,    41,    55,   201,   196,
     223,    17,    86,   192,    25,    25,    61,    31,    87,   193,
      89,   215,    84,    68,   265,    36,    85,    38,   221,   244,
     230,    90,   227,   229,    37,   245,    46,   246,    92,    93,
      94,    27,    28,   260,    39,    25,    31,   210,    95,   261,
      89,   211,    96,   241,   212,   141,   149,    60,   213,   135,
      64,    90,   247,   163,   149,    65,   248,    91,    92,    93,
      94,    27,    28,   258,   249,    62,   250,   259,   198,   153,
      70,   253,   199,    27,    28,    97,    63,     1,    98,    99,
     171,   172,   173,    12,    13,    25,    31,   200,    73,    14,
      15,    16,   129,   138,   194,   202,     1,   243,   201,   175,
     176,    71,    12,    13,   134,   266,   267,   133,    14,    15,
      16,   230,   268,   186,   229,   178,   179,   180,   181,   187,
     256,   183,   184,   188,    25,    31,    44,    45,   197,    89,
      34,   205,   191,   217,   216,   240,   251,   252,   218,   254,
      90,   264,   255,   262,     8,   149,    91,    92,    93,    94,
      27,    28,   220,    35,   270,    67,   235,   198,    25,    70,
     236,   199,   234,    89,    97,   238,   237,    98,    99,   257,
     239,   242,   156,   157,    90,   131,   200,    73,   263,   146,
      91,    92,    93,    94,    27,    28,    59,   214,     0,    25,
     269,    95,     0,     0,    89,    96,   219,     0,    97,     0,
       0,    98,    99,   156,   157,    90,     0,     0,     0,     0,
     100,    91,    92,    93,    94,    27,    28,     0,     0,     0,
      25,     0,    95,     0,     0,    89,    96,     0,     0,    97,
       0,     0,    98,    99,     0,     0,    90,     0,     0,     0,
       0,   100,    91,    92,    93,    94,    27,    28,     0,     0,
       0,    25,     0,    95,   153,     0,    89,    96,     0,     0,
      97,     0,     0,    98,    99,     0,     0,    90,     0,     0,
       0,     0,   100,    91,    92,    93,    94,    27,    28,     0,
       0,     0,    25,     0,    95,   226,     0,    89,    96,     0,
       0,    97,     0,     0,    98,    99,     0,     0,    90,     0,
       0,     0,     0,   100,    91,    92,    93,    94,    27,    28,
       0,     0,     0,     0,     0,    95,     0,     0,     0,    96,
       0,     0,    97,     0,     0,    98,    99,     0,     0,     0,
       0,     0,     0,     0,   100
  };

  const short
  parser::yycheck_[] =
  {
      12,    89,    14,    62,    60,   148,    13,    72,    73,   120,
      69,    70,     3,     7,     4,     3,    15,    16,    19,     4,
       3,     3,    39,    40,    41,    31,    38,    39,    40,    41,
      37,    36,    38,    38,     3,    36,     3,    49,    34,    40,
      96,    40,    41,    48,    26,    36,    36,    31,    38,    37,
      40,    36,    36,    38,    38,    40,     0,    64,    41,    71,
      33,    40,    52,   174,   152,    55,    56,    84,    37,    86,
      55,    56,    84,   129,    86,   134,    38,    50,    90,   138,
      34,    33,    33,    10,    96,   144,    48,    86,   144,    41,
      41,    18,    33,    33,     3,     3,    43,     4,    39,    39,
       8,   157,    33,    50,   247,    34,    37,    40,   164,    33,
     169,    19,   168,   169,    15,    39,    34,   205,    26,    27,
      28,    29,    30,    33,    36,     3,     4,    33,    36,    39,
       8,    37,    40,   192,    33,   200,   148,    42,    37,   198,
      16,    19,    33,   199,   156,    34,    37,    25,    26,    27,
      28,    29,    30,    33,   210,    52,   212,    37,    36,    37,
      38,   217,    40,    29,    30,    43,    52,     7,    46,    47,
      43,    44,    45,    13,    14,     3,     4,    55,    56,    19,
      20,    21,    42,   195,   243,   244,     7,   199,   244,    46,
      47,    40,    13,    14,    42,   251,   252,    34,    19,    20,
      21,   260,   258,    22,   260,    48,    49,    50,    51,    23,
     222,    53,    54,    24,     3,     4,    32,    33,     3,     8,
      41,     9,    37,    52,    34,    15,    52,    52,    41,    34,
      19,    10,    41,   240,     3,   247,    25,    26,    27,    28,
      29,    30,   164,    18,   264,    49,   182,    36,     3,    38,
     185,    40,   177,     8,    43,   187,   186,    46,    47,   222,
     188,   195,    17,    18,    19,    63,    55,    56,   244,    86,
      25,    26,    27,    28,    29,    30,    41,   156,    -1,     3,
     260,    36,    -1,    -1,     8,    40,    41,    -1,    43,    -1,
      -1,    46,    47,    17,    18,    19,    -1,    -1,    -1,    -1,
      55,    25,    26,    27,    28,    29,    30,    -1,    -1,    -1,
       3,    -1,    36,    -1,    -1,     8,    40,    -1,    -1,    43,
      -1,    -1,    46,    47,    -1,    -1,    19,    -1,    -1,    -1,
      -1,    55,    25,    26,    27,    28,    29,    30,    -1,    -1,
      -1,     3,    -1,    36,    37,    -1,     8,    40,    -1,    -1,
      43,    -1,    -1,    46,    47,    -1,    -1,    19,    -1,    -1,
      -1,    -1,    55,    25,    26,    27,    28,    29,    30,    -1,
      -1,    -1,     3,    -1,    36,    37,    -1,     8,    40,    -1,
      -1,    43,    -1,    -1,    46,    47,    -1,    -1,    19,    -1,
      -1,    -1,    -1,    55,    25,    26,    27,    28,    29,    30,
      -1,    -1,    -1,    -1,    -1,    36,    -1,    -1,    -1,    40,
      -1,    -1,    43,    -1,    -1,    46,    47,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    55
  };

  const unsigned char
  parser::yystos_[] =
  {
       0,     7,    61,    62,    63,    64,     3,     0,    63,    34,
      40,    34,    13,    14,    19,    20,    21,    64,    65,    70,
      71,    72,    73,    74,    75,     3,    79,    29,    30,    81,
      79,     4,    78,    78,    41,    70,    34,    15,    40,    36,
      38,    48,   135,   136,   136,   136,    34,    81,    76,    77,
      79,    37,    79,   131,   137,    78,   131,   133,   139,   139,
      42,   135,    52,    52,    16,    34,    41,    76,   135,    36,
      38,    40,    55,    56,    78,   114,   118,   119,   120,   121,
     122,   123,   124,   125,    33,    37,    33,    39,    50,     8,
      19,    25,    26,    27,    28,    36,    40,    43,    46,    47,
      55,    79,    80,    81,    82,    85,    86,    87,    88,    89,
      90,    91,    92,    94,    95,    96,    97,    98,    99,   100,
     101,   102,   104,   106,   108,   110,   111,   112,   113,    42,
     114,   120,    81,    34,    42,   114,   114,   115,    79,   116,
     117,   125,   125,    31,    38,   131,   133,    85,    36,    79,
     131,   132,   134,    37,    82,    84,    17,    18,    66,    67,
      68,    69,    79,    82,    93,   130,   140,    31,    36,    38,
     100,    43,    44,    45,   103,    46,    47,   105,    48,    49,
      50,    51,   107,    53,    54,   109,    22,    23,    24,    82,
     114,    37,    33,    39,   114,    33,    41,     3,    36,    40,
      55,    82,   114,   126,   127,     9,    37,   132,   138,    85,
      33,    37,    33,    37,   134,    82,    34,    52,    41,    41,
      66,    82,    33,    41,     3,    26,    37,    82,    83,    82,
     114,   128,   129,   100,   104,   106,   108,   110,   111,   112,
      15,   114,   116,    79,    33,    39,    85,    33,    37,    82,
      82,    52,    52,    82,    34,    41,    79,   130,    33,    37,
      33,    39,    81,   126,    10,   132,    82,    82,    82,   128,
      87
  };

  const unsigned char
  parser::yyr1_[] =
  {
       0,    60,    61,    62,    62,    63,    64,    65,    65,    66,
      66,    66,    67,    68,    69,    70,    70,    70,    70,    70,
      70,    71,    71,    72,    73,    74,    75,    76,    77,    77,
      78,    79,    80,    81,    81,    82,    83,    83,    84,    84,
      85,    85,    85,    85,    85,    85,    86,    87,    87,    87,
      87,    87,    87,    87,    88,    89,    90,    91,    91,    92,
      92,    92,    93,    93,    94,    95,    95,    95,    95,    95,
      96,    97,    97,    98,    99,   100,   100,   101,   101,   101,
     101,   101,   102,   103,   103,   103,   104,   104,   105,   105,
     106,   106,   107,   107,   107,   107,   108,   108,   109,   109,
     110,   110,   111,   111,   112,   112,   113,   113,   114,   115,
     115,   116,   117,   117,   118,   118,   118,   118,   119,   120,
     121,   122,   122,   122,   123,   124,   125,   125,   125,   126,
     126,   127,   127,   128,   128,   129,   129,   130,   131,   132,
     132,   133,   133,   134,   134,   134,   135,   135,   136,   136,
     137,   137,   138,   138,   139,   139,   140,   140
  };

  const signed char
  parser::yyr2_[] =
  {
       0,     2,     1,     2,     3,     1,     5,     2,     3,     1,
       1,     1,     4,     4,     1,     1,     1,     1,     1,     1,
       1,     5,     6,     5,     5,     6,     5,     6,     2,     3,
       1,     1,     1,     1,     1,     1,     1,     3,     3,     3,
       1,     1,     1,     1,     1,     1,     2,     1,     1,     1,
       1,     1,     1,     1,     3,     3,     3,     4,     6,     3,
       3,     4,     2,     3,     3,     1,     1,     1,     1,     1,
       4,     3,     4,     3,     3,     1,     2,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     3,     1,     1,
       1,     3,     1,     1,     1,     1,     1,     3,     1,     1,
       1,     3,     1,     3,     1,     3,     1,     3,     1,     1,
       3,     2,     1,     3,     1,     1,     1,     1,     3,     3,
       3,     1,     1,     1,     4,     3,     1,     2,     2,     1,
       1,     1,     3,     1,     1,     1,     3,     3,     2,     1,
       1,     1,     1,     1,     3,     2,     3,     2,     3,     3,
       1,     3,     1,     3,     1,     3,     1,     3
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
  "\"link\"", "\"from\"", "\"as\"", "\"let\"", "\"set\"", "\"fn\"",
  "\"type\"", "\"enum\"", "\"and\"", "\"xor\"", "\"or\"", "\"not\"",
  "\"42\"", "\"0x2a\"", "\"4.2\"", "\"\\\"dq-string-literal\\\"\"",
  "\"'sq-string-literal'\"", "\".\"", "\":\"", "\",\"", "\";\"", "\"::\"",
  "\"(\"", "\")\"", "\"[\"", "\"]\"", "\"{\"", "\"}\"", "\"->\"", "\"*\"",
  "\"/\"", "\"%\"", "\"+\"", "\"-\"", "\"<\"", "\"<=\"", "\">\"", "\">=\"",
  "\"=\"", "\"==\"", "\"!=\"", "\"^\"", "\"&\"", "\"!\"", "\"EOS\"",
  "\"<null>\"", "$accept", "script", "scriptContent", "scriptContentStmt",
  "moduleStmt", "moduleContent", "chainPrefixStmt", "letStmt", "setStmt",
  "discardStmt", "moduleContentStmt", "defStmt", "typedefStmt",
  "typedefStmt_enum", "importStmt", "linkStmt", "linkStmtItem",
  "linkStmtContent", "tid", "vid", "floatl", "stringl", "expr", "expr_cl1",
  "expr_cl2", "parenExpr", "unitExpr", "primaryExpr", "vparenExpr",
  "vtupleExpr", "vstructExpr", "ifThenElseExpr", "chainExpr",
  "chainPrefix", "vlambdaExpr", "postfixExpr", "vtcallExpr", "vvcallExpr",
  "dotNmExpr", "dotIxExpr", "unaryExpr", "unaryOp", "binaryExpr",
  "mulBinaryOp", "mulBinaryExpr", "addBinaryOp", "addBinaryExpr",
  "cmpBinaryOp", "cmpBinaryExpr", "eqBinaryOp", "eqBinaryExpr",
  "andBinaryExpr", "xorBinaryExpr", "orBinaryExpr", "typespec",
  "typespec_cl", "structTypespecField", "structTypespecField_cl",
  "primaryTypespec", "parenTypespec", "structTypespec", "tupleTypespec",
  "postfixTypespec", "ttcall", "tdot", "unaryTypespec", "ttarg",
  "ttarg_cl", "vtarg", "vtarg_cl", "vstructExprField", "vpatternField",
  "lpatternField", "tpatternField", "lpattern", "vpattern", "tpattern",
  "vpatternField_cl", "lpatternField_cl", "tpatternField_cl",
  "vstructExprField_cl", YY_NULLPTR
  };
#endif


#if YYDEBUG
  const short
  parser::yyrline_[] =
  {
       0,   298,   298,   301,   302,   305,   313,   316,   317,   325,
     326,   327,   330,   333,   336,   340,   341,   342,   343,   344,
     345,   348,   349,   352,   355,   359,   363,   366,   369,   370,
     377,   378,   380,   383,   384,   391,   394,   395,   398,   399,
     403,   404,   405,   406,   407,   408,   411,   414,   415,   416,
     417,   418,   419,   420,   423,   426,   429,   432,   433,   436,
     437,   438,   441,   442,   445,   449,   450,   451,   452,   453,
     456,   459,   460,   463,   466,   470,   471,   474,   475,   476,
     477,   478,   482,   485,   486,   487,   490,   491,   494,   495,
     498,   499,   502,   503,   504,   505,   508,   509,   512,   513,
     516,   517,   520,   521,   524,   525,   528,   529,   537,   540,
     541,   545,   548,   549,   553,   554,   555,   556,   559,   562,
     565,   569,   570,   571,   574,   576,   580,   581,   582,   587,
     588,   591,   592,   597,   598,   601,   602,   610,   613,   616,
     617,   620,   621,   624,   625,   626,   629,   630,   633,   634,
     638,   639,   642,   643,   646,   647,   650,   651
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
      55,    56,    57,    58,    59
    };
    // Last valid token kind.
    const int code_max = 314;

    if (t <= 0)
      return symbol_kind::S_YYEOF;
    else if (t <= code_max)
      return YY_CAST (symbol_kind_type, translate_table[t]);
    else
      return symbol_kind::S_YYUNDEF;
  }

#line 18 "parser.yy"
} } // pdm::parser
#line 2106 "parser.tab.cc"

#line 654 "parser.yy"


#include <stdio.h>

#include "lexer.h"

#include "useful.h"
#include "source.h"
#include "ast.h"

RawAstNode* ParseScript(Source* source) {
    // TODO: implement me from `parser.c`
    AstNode* out = NULL;
    int result = yyparse(source, &out);
    if (result == 0) {
        return out;
    } else {
        COMPILER_ERROR("yyparse == 0 <=> error");
        return NULL;
    }
}

// int yylex (YYSTYPE *lvalp) {
//     /* TODO: Put value onto Bison stack. */
//     return TK_NULL;
// }

int yylex(YYSTYPE* lvalp, YYLTYPE* llocp, source::Source* source, parser::Lexer* lexer) {
    // see:
    // https://www.gnu.org/software/bison/manual/html_node/Calling-Convention.html

    TokenInfo* info = &lvalp->token;
    
    llocp->source(source);
    int tk = lexer->lex_one_token(info, llocp);
    
    if (pdm::DEBUG) {
        DebugPrintToken("YYLEX:", tk, info, llocp);
    }
    if (tk == TK_EOS) {
        return YYEOF;
    } else {
        return tk;
    }
}

void yyerror(YYLTYPE* llocp, Source* source, AstNode** outp, char const* message) {
    Loc loc = FirstLocOfSpan(*llocp);
    FeedbackNote* note = CreateFeedbackNote("here...", loc, NULL);
    PostFeedback(
        FBK_ERROR, note,
        "Parser error: %s", message
    );
}
