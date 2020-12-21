/* parser.yy: specifies a grammar + code to produce a parser using `bison` parser generator.
 */

/* see docs on define "api.pure" "full"...
 * - %define Summary
 *     https://www.gnu.org/software/bison/manual/html_node/_0025define-Summary.html 
 * - A Pure (Reentrant) Parser
 *     https://www.gnu.org/software/bison/manual/html_node/Pure-Decl.html
 * - Calling Conventions for Pure Parsers 
 *     https://www.gnu.org/software/bison/manual/html_node/Pure-Calling.html
 */

%require "3.2"

%language "C++"
%defines

%define api.namespace {pdm::parser}

// %glr-parser
// %define lr.type lalr
%define lr.type ielr
// %define lr.type canonical-lr
// %define api.pure true

// we want 'ast.h' and 'extra-tokens.h' in the header
// https://stackoverflow.com/questions/47726404/how-to-put-header-file-to-tab-h-in-bison
%code requires {
    #include <stb/stretchy_buffer.h>

    #include "pdm/core/config.hh"

    // todo: include more AST files here:
    #include "pdm/ast/node.hh"
    #include "pdm/ast/script/script.hh"
    #include "pdm/ast/exp/exp.hh"
    #include "pdm/ast/exp/struct.hh"
    #include "pdm/ast/exp/unary.hh"
    #include "pdm/ast/exp/binary.hh"
    #include "pdm/ast/exp/tcall.hh"
    #include "pdm/ast/stmt/stmt.hh"
    #include "pdm/ast/pattern/vpattern.hh"
    #include "pdm/ast/pattern/lpattern.hh"
    #include "pdm/ast/pattern/tpattern.hh"
    #include "pdm/ast/typespec/typespec.hh"
    #include "pdm/ast/typespec/struct.hh"
    #include "pdm/ast/typespec/tcall.hh"

    #include "pdm/parser/reader.hh"
    #include "pdm/parser/lexer.hh"

    #include "pdm/source/source.hh"
    #include "pdm/source/pos.hh"
    #include "pdm/source/loc.hh"
}

// %define api.position.type {source::Pos}
%locations
// %define api.location.file {"../source/loc.hh"}
%define api.location.type {pdm::source::Loc}

// adding 'Source*' 'Lexer*' params to the lexer and parser:
%param {pdm::source::Source* source}
%param {pdm::parser::Lexer* lexer}

// adding an output ptr param to the parser:
%parse-param {pdm::ast::Script** outp}

// see: https://www.gnu.org/software/bison/manual/html_node/Value-Type.html
// #define YYSTYPE TokenInfo
// %define api.value.type {TokenInfo}
// todo: fix this type with a union of...
// 1. TokenInfo
// 2. AstNode*
// 3. AstNode** (sb)
// or use
// %code requires { 
//     #define YYSTYPE TokenInfo
// }

//
// Union:
//

%union {
    pdm::parser::TokenInfo token;
    
    pdm::ast::Script* script;
    pdm::ast::Script** script_sb;
    
    pdm::ast::Stmt* stmt;
    pdm::ast::Stmt** stmt_sb;

    pdm::ast::Exp* exp;
    pdm::ast::Exp** exp_sb;

    pdm::ast::UnaryOperator uop;
    pdm::ast::BinaryOperator bop;

    pdm::ast::StructExp::Field* structexp_field;
    pdm::ast::StructExp::Field** structexp_field_sb;

    pdm::ast::Typespec* typespec;
    pdm::ast::Typespec** typespec_sb;

    pdm::ast::LPattern* lpattern;
    pdm::ast::VPattern* vpattern;
    pdm::ast::TPattern* tpattern;
    pdm::ast::LPattern::Field* lpattern_field;
    pdm::ast::VPattern::Field* vpattern_field;
    pdm::ast::TPattern::Field* tpattern_field;

    pdm::ast::TCallExp::Arg* tcallexp_arg;
    pdm::ast::TCallExp::Arg** tcallexp_arg_sb;

    pdm::ast::TCallTypespec::Arg* tcallts_arg;
    pdm::ast::TCallTypespec::Arg** tcallts_arg_sb;

    pdm::ast::StructTypespec::Field* structts_field;
    pdm::ast::StructTypespec::Field** structts_field_sb;
}

//
// File Nonterminals:
//

%type <script> script
%type <script_sb> scriptContent
%type <stmt> scriptContentStmt

%type <stmt> moduleStmt
%type <stmt_sb> moduleContent

//
// Stmt:
//

%type <stmt> moduleContentStmt
%type <stmt> chainPrefixStmt letStmt setStmt discardStmt
%type <stmt> importStmt

%type <stmt> typedefStmt_enum typedefStmt defStmt

%type <stmt> linkStmt linkStmtItem
%type <stmt_sb> linkStmtContent

//
// Shared:
//

%type <token> tid vid floatl stringl

//
// Expression Nonterminals:
//

%type <exp> expr
%type <exp_sb> expr_cl1
%type <exp_sb> expr_cl2

%type <exp> parenExpr unitExpr
%type <exp> primaryExpr 
%type <exp> vparenExpr vtupleExpr vstructExpr
%type <exp> ifThenElseExpr chainExpr vlambdaExpr
%type <stmt_sb> chainPrefix
%type <exp> unaryExpr
%type <uop> unaryOp

%type <exp> postfixExpr 
%type <exp> vtcallExpr vvcallExpr
%type <exp> dotNmExpr dotIxExpr

%type <exp> binaryExpr 
%type <exp> mulBinaryExpr addBinaryExpr cmpBinaryExpr eqBinaryExpr andBinaryExpr xorBinaryExpr orBinaryExpr
%type <bop> mulBinaryOp addBinaryOp cmpBinaryOp eqBinaryOp

%type <structexp_field> vstructExprField
%type <structexp_field_sb> vstructExprField_cl

//
// Typespec Nonterminals:
//

%type <typespec> typespec
%type <typespec> primaryTypespec parenTypespec tupleTypespec structTypespec
%type <typespec> postfixTypespec ttcall tdot
%type <typespec> unaryTypespec
%type <typespec_sb> typespec_cl
%type <structts_field> structTypespecField
%type <structts_field_sb> structTypespecField_cl

//
// Pattern Nonterminals:
//

%type <lpattern> lpattern 
%type <vpattern> vpattern 
%type <tpattern> tpattern
%type <vpattern_field> vpatternField 
%type <lpattern_field> lpatternField
%type <tpattern_field> tpatternField
%type <vpattern_field_sb> vpatternField_cl 
%type <lpattern_field_sb> lpatternField_cl 
%type <tpattern_field_sb> tpatternField_cl
%type <tcall_arg> ttarg vtarg
%type <tcall_arg_sb> ttarg_cl vtarg_cl

%code provides {
    int yylex(pdm::parser::TokenInfo *lvalp, pdm::source::Loc *llocp, pdm::source::Source* source, pdm::parser::Lexer* lexer);
    void yyerror(pdm::source::Loc* llocp, char const* message, pdm::source::Source* source, pdm::parser::Lexer* lexer);
}

%token <pdm::parser::TokenInfo> TK_VID   "<val_id>"
%token <pdm::parser::TokenInfo> TK_TID   "<TypeId>"
%token <pdm::parser::TokenInfo> TK_HOLE  "<__42__>"

%token TK_KW_USING "using"
%token TK_KW_MOD "mod"
%token TK_KW_IF "if" 
%token TK_KW_THEN "then"
%token TK_KW_ELSE "else"
%token TK_KW_MATCH "match"
%token TK_KW_WITH "with"
%token TK_KW_IMPORT "import"
%token TK_KW_LINK "link"
%token TK_KW_FROM "from"
%token TK_KW_AS "as"
%token TK_KW_LET "let" 
%token TK_KW_SET "set" 
%token TK_KW_FN "fn" 
%token TK_KW_TYPE "type" 
%token TK_KW_ENUM "enum"
%token TK_KW_AND "and" 
%token TK_KW_XOR "xor" 
%token TK_KW_OR "or" 
%token TK_KW_NOT "not"

%token <token> TK_DINT_LIT "42"
%token <token> TK_XINT_LIT "0x2a"
%token <token> TK_FLOAT_LIT "4.2"
%token <token> TK_DQSTRING_LIT "\"dq-string-literal\""
%token <token> TK_SQSTRING_LIT "'sq-string-literal'"

%token TK_DOT       "."
%token TK_COLON     ":"
%token TK_COMMA     ","
%token TK_SEMICOLON ";"
%token TK_DBL_COLON "::"
%token TK_LPAREN    "("
%token TK_RPAREN    ")"
%token TK_LSQBRK    "["
%token TK_RSQBRK    "]"
%token TK_LCYBRK    "{"
%token TK_RCYBRK    "}"
%token TK_ARROW     "->"
%token TK_ASTERISK  "*"
%token TK_FSLASH    "/"
%token TK_PERCENT   "%"
%token TK_PLUS      "+"
%token TK_MINUS     "-"
%token TK_LTHAN     "<"
%token TK_LETHAN    "<="
%token TK_GTHAN     ">"
%token TK_GETHAN    ">="
%token TK_BIND      "="
%token TK_EQUALS    "=="
%token TK_NEQUALS   "!="
%token TK_CARET     "^"
%token TK_AMPERSAND "&"
%token TK_EXCLAIM   "!"
%token TK_EOS       "EOS"

%token TK_NULL      "<null>"

/* Added tokens:
 * TK_KW_YIELD -> TK_KW_DISCARD 
 * TK_NOT -> TK_KW_NOT
 * -> TK_EXCLAIM
 * -> TK_KW_SET
 * -> TK_KW_MODULE
 * -> TK_KW_FROM
 * -> TK_KW_AS
 * -> TK_KW_TYPE
 * -> TK_KW_ENUM
 */

%start script;
// %start module;
// %start letStmt

%%

/*
 * Scripts:
 */

script
    : scriptContent { $$ = NewAstScriptWithModulesSb(@$, source, $1); *outp = $$; }
    ;
scriptContent
    : scriptContentStmt               TK_SEMICOLON     { $$ = NULL; sb_push($$,$1); }
    | scriptContent scriptContentStmt TK_SEMICOLON     { $$ = $1; sb_push($$,$2); }
    ;
scriptContentStmt
    : moduleStmt    { $$ = $1; }
    ;

/*
 * Modules:
 */

moduleStmt
    : TK_KW_MOD TK_VID TK_LCYBRK moduleContent TK_RCYBRK    { $$ = NewAstModuleStmtWithStmtSb(@$, $2.ID_symbolID, $4); }
    ;
moduleContent
    : moduleContentStmt TK_SEMICOLON                   { $$ = NULL; sb_push($$, $1); }
    | moduleContent moduleContentStmt TK_SEMICOLON     { $$ = $1; sb_push($$, $2); }
    ;

/*
 * Statements:
 */

chainPrefixStmt
    : letStmt       { $$ = $1; }
    | setStmt       { $$ = $1; }
    | discardStmt   { $$ = $1; }
    ;
letStmt
    : TK_KW_LET lpattern TK_BIND expr   { $$ = NewAstLetStmt(@$, $2, $4); }
    ;
setStmt
    : TK_KW_SET expr TK_BIND expr   { $$ = NewAstSetStmt(@$, $2, $4); }
    ; 
discardStmt
    : expr    { $$ = NewAstDiscardStmt(@$, $1); }
    ;

moduleContentStmt
    : defStmt               { $$ = $1; }
    | typedefStmt           { $$ = $1; }
    | typedefStmt_enum      { $$ = $1; }
    | importStmt            { $$ = $1; }
    | linkStmt              { $$ = $1; }
    | moduleStmt            { $$ = $1; }
    ;
defStmt
    : TK_KW_FN vid          vpattern TK_ARROW expr   { $$ = NewAstDefStmt(@$, $2.ID_symbolID, NULL, $3, $5); }
    | TK_KW_FN vid tpattern vpattern TK_ARROW expr   { $$ = NewAstDefStmt(@$, $2.ID_symbolID, $3,   $4, $6); }
    ;
typedefStmt
    : TK_KW_TYPE tid tpattern TK_BIND typespec   { $$ = NewAstTypedefStmt(@$, $2.ID_symbolID, $3, $5); }
    ;
typedefStmt_enum
    : TK_KW_ENUM tid tpattern TK_BIND structTypespec  { $$ = NewAstTypedefEnumStmt(@$, $2.ID_symbolID, $3, $5); }
    ;

importStmt
    : TK_KW_IMPORT vid TK_KW_FROM stringl TK_KW_AS stringl  { $$ = NewAstImportStmt(@$, $2.ID_symbolID, $4.String_utf8string, $6.String_utf8string); }
    ;

linkStmt
    : TK_KW_LINK stringl TK_LCYBRK linkStmtContent TK_RCYBRK   { $$ = NewAstLinkStmt(@$, $2.String_utf8string, $4); }
    ;
linkStmtItem
    : vid vpattern TK_ARROW typespec TK_KW_FROM stringl     { $$ = NewAstLinkStmtItem(@$, $1.ID_symbolID, $2, NewAstType2Val(@4,$4), $6.String_utf8string); }
    ;
linkStmtContent
    : linkStmtItem TK_SEMICOLON                     { $$.push_back($1); }
    | linkStmtContent linkStmtItem TK_SEMICOLON     { $$ = $1; $$.push_back($2); }
    ;

/*
 * Shared:
 */

tid: TK_TID     { $$ = $1; };
vid: TK_VID     { $$ = $1; };
floatl
    : TK_FLOAT_LIT  { $$ = $1; }
    ;
stringl
    : TK_SQSTRING_LIT   { $$ = $1; }
    | TK_DQSTRING_LIT   { $$ = $1; }
    ;

/*
 * Expressions:
 */

expr: binaryExpr    { $$ = $1; }
    ;
expr_cl1
    : expr                      { $$ = NULL; sb_push(($$),$1); }
    | expr_cl1 TK_COMMA expr    { $$ = $1; sb_push(($$),$3); }
    ;
expr_cl2
    : expr TK_COMMA expr        { $$ = NULL; sb_push($$,$1); sb_push($$,$3); }
    | expr_cl2 TK_COMMA expr    { $$ = $1; sb_push($$,$3); }
    ;

parenExpr
    : unitExpr      { $$ = $1; }
    | vparenExpr    { $$ = $1; }
    | vtupleExpr    { $$ = $1; }
    | vstructExpr   { $$ = $1; }
    | chainExpr     { $$ = $1; }
    | vlambdaExpr   { $$ = $1; }
    ;
unitExpr
    : TK_LPAREN TK_RPAREN
    ;
primaryExpr
    : parenExpr      { $$ = $1; }
    | vid            { $$ = NewAstVID(@$, $1.ID_symbolID); }
    | TK_DINT_LIT    { $$ = NewAstIntLiteral(@$, $1.Int, 10); }
    | TK_XINT_LIT    { $$ = NewAstIntLiteral(@$, $1.Int, 16); }
    | floatl         { $$ = NewAstFloatLiteral(@$, $1.Float); }
    | stringl        { $$ = NewAstStringLiteral(@$, $1.String_utf8string); }
    | ifThenElseExpr { $$ = $1; }
    ;
vparenExpr
    : TK_LPAREN expr TK_RPAREN  { $$ = NewAstVParen(@$, $2); }
    ;
vtupleExpr
    : TK_LPAREN expr_cl2  TK_RPAREN     { $$ = NewAstVTupleWithFieldsSb(@$, $2); }
    ;
vstructExpr
    : TK_LCYBRK vstructExprField_cl TK_RCYBRK     { $$ = NewAstVStructWithFieldsSb(@$, $2); }
    ;
ifThenElseExpr
    : TK_KW_IF parenExpr TK_KW_THEN parenExpr                        { $$ = NewAstIte(@$, $2, $4, NULL); }
    | TK_KW_IF parenExpr TK_KW_THEN parenExpr TK_KW_ELSE primaryExpr { $$ = NewAstIte(@$, $2, $4, $6); }
    ;
chainExpr
    : TK_LCYBRK expr             TK_RCYBRK      { $$ = NewAstChainWith(@$, NULL, $2); }
    | TK_LCYBRK chainPrefix      TK_RCYBRK      { $$ = NewAstChainWith(@$, $2, NULL); }
    | TK_LCYBRK chainPrefix expr TK_RCYBRK      { $$ = NewAstChainWith(@$, $2, $3); }
    ;
chainPrefix
    : chainPrefixStmt             TK_SEMICOLON  { $$ = NULL; sb_push(($$),$1); }
    | chainPrefix chainPrefixStmt TK_SEMICOLON  { $$ = $1; sb_push(($$),$2); }
    ;
vlambdaExpr
    : TK_KW_FN lpattern parenExpr   { $$ = NULL; }
    ;

postfixExpr
    : primaryExpr   { $$ = $1; }
    | vtcallExpr    { $$ = $1; }
    | vvcallExpr    { $$ = $1; }
    | dotNmExpr     { $$ = $1; }
    | dotIxExpr     { $$ = $1; }
    ;
vtcallExpr
    : postfixExpr TK_LSQBRK vtarg_cl TK_RSQBRK  { $$ = NewAstTCallWithArgsSb(@$, $1, $3); }
    ;
vvcallExpr
    : postfixExpr TK_LPAREN TK_RPAREN           { $$ = NewAstVCallWithArgsSb(@$, $1, NULL); }
    | postfixExpr TK_LPAREN expr_cl1 TK_RPAREN   { $$ = NewAstVCallWithArgsSb(@$, $1, $3); }
    ;
dotNmExpr
    : postfixExpr TK_DOT TK_VID         { $$ = NewAstDotName(@$, $1, $3.ID_symbolID); }
    ;
dotIxExpr
    : postfixExpr TK_DOT TK_DINT_LIT    { $$ = NewAstDotIndex(@$, $1, $3.Int); }
    ;

unaryExpr
    : postfixExpr           { $$ = $1; }
    | unaryOp unaryExpr     { $$ = NewAstUnary(@$, $1, $2); }
    ;
unaryOp
    : TK_PLUS       { $$ = UOP_PLUS; }
    | TK_MINUS      { $$ = UOP_MINUS; }
    | TK_ASTERISK   { $$ = UOP_DEREF; }
    | TK_CARET      { $$ = UOP_GETREF; }
    | TK_KW_NOT     { $$ = UOP_NOT; }
    ;

binaryExpr
    : orBinaryExpr  { $$ = $1; }
    ;
mulBinaryOp
    : TK_ASTERISK   { $$ = BOP_MUL; }
    | TK_FSLASH     { $$ = BOP_DIV; }
    | TK_PERCENT    { $$ = BOP_REM; }
    ;
mulBinaryExpr
    : unaryExpr                             { $$ = $1; }
    | mulBinaryExpr mulBinaryOp unaryExpr   { $$ = NewAstBinary(@$, $2, $1, $3); }
    ;
addBinaryOp
    : TK_PLUS   { $$ = BOP_ADD; }
    | TK_MINUS  { $$ = BOP_SUBTRACT; }
    ;
addBinaryExpr
    : mulBinaryExpr                             { $$ = $1; }
    | addBinaryExpr addBinaryOp mulBinaryExpr   { $$ = NewAstBinary(@$, $2, $1, $3); }
    ;
cmpBinaryOp
    : TK_LTHAN      { $$ = BOP_LTHAN; }
    | TK_LETHAN     { $$ = BOP_LETHAN; }
    | TK_GTHAN      { $$ = BOP_GTHAN; }
    | TK_GETHAN     { $$ = BOP_GETHAN; }
    ;
cmpBinaryExpr
    : addBinaryExpr                             { $$ = $1; }
    | cmpBinaryExpr cmpBinaryOp addBinaryExpr   { $$ = NewAstBinary(@$, $2, $1, $3); }
    ;
eqBinaryOp
    : TK_EQUALS     { $$ = BOP_EQUALS; }
    | TK_NEQUALS    { $$ = BOP_NEQUALS; }
    ;
eqBinaryExpr
    : cmpBinaryExpr                         { $$ = $1; }
    | eqBinaryExpr eqBinaryOp cmpBinaryExpr { $$ = NewAstBinary(@$, $2, $1, $3); }
    ;
andBinaryExpr
    : eqBinaryExpr                          { $$ = $1; }
    | andBinaryExpr TK_KW_AND eqBinaryExpr  { $$ = NewAstBinary(@$, BOP_AND, $1, $3); }
    ;
xorBinaryExpr
    : andBinaryExpr                         { $$ = $1; }
    | xorBinaryExpr TK_KW_XOR andBinaryExpr { $$ = NewAstBinary(@$, BOP_XOR, $1, $3); }
    ;
orBinaryExpr
    : xorBinaryExpr                         { $$ = $1; }
    | orBinaryExpr TK_KW_OR xorBinaryExpr   { $$ = NewAstBinary(@$, BOP_OR, $1, $3); }
    ;

/*
 * Typespecs:
 */

typespec
    : unaryTypespec  { $$ = $1; }
    ;
typespec_cl
    : typespec                      { $$ = NULL; sb_push($$,$1); }
    | typespec_cl TK_COMMA typespec { $$ = $1; sb_push($$,$3); }
    ;

structTypespecField
    : vid typespec
    ;
structTypespecField_cl
    : structTypespecField
    | structTypespecField_cl TK_COMMA structTypespecField
    ;

primaryTypespec
    : tid               { $$ = NewAstTID(@$, $1.ID_symbolID); }
    | parenTypespec     { $$ = $1; }
    | structTypespec    { $$ = $1; }
    | tupleTypespec     { $$ = $1; }
    ;
parenTypespec
    : TK_LPAREN typespec TK_RPAREN
    ;
structTypespec
    : TK_LCYBRK structTypespecField_cl TK_RCYBRK
    ;
tupleTypespec
    : TK_LSQBRK typespec_cl TK_RSQBRK
    ;

postfixTypespec
    : primaryTypespec  { $$ = $1; }
    | ttcall
    | tdot
    ;
ttcall
    : postfixTypespec TK_LSQBRK ttarg_cl TK_RSQBRK  { $$ = NewAstTCallWithArgsSb(@$, $1, $3); }
    ;
tdot: postfixTypespec TK_DOT TK_VID
    ;

unaryTypespec
    : postfixTypespec               { $$ = $1; }
    | TK_AMPERSAND unaryTypespec    { $$ = NewAstTMut(@$,$2); }
    | TK_CARET     unaryTypespec    { $$ = NewAstTPtr(@$,$2); }
    ;

/* type contexts' targs (template args): values have Val2Type wrappers */
ttarg
    : typespec  { $$ = $1; }
    | expr      { $$ = NewAstVal2Type(@$,$1); }
    ;
ttarg_cl
    : ttarg                     { $$ = NULL; sb_push($$,$1); }
    | ttarg_cl TK_COMMA ttarg   { $$ = $1; sb_push($$,$3); }
    ;

/* value contexts' targs (template args): typespecs have Type2Val wrappers */
vtarg
    : typespec { $$ = NewAstType2Val(@$,$1); }
    | expr     { $$ = $1; }
    ;
vtarg_cl
    : vtarg                     { $$ = NULL; sb_push($$,$1); }
    | vtarg_cl TK_COMMA vtarg   { $$ = $1; sb_push($$,$3); }
    ;

/*
 * Patterns & fields:
 */

vstructExprField
    : vid TK_BIND expr { $$ = NewAstField(@$, $1.ID_symbolID, $3); }
    ;
vpatternField
    : vid typespec { $$ = NewAstField(@$, $1.ID_symbolID, NewAstType2Val(@2,$2)); }
    ;
lpatternField
    : vpatternField { $$ = $1; }
    | vid           { $$ = NewAstField(@$, $1.ID_symbolID, NULL); }
    ;
tpatternField
    : tid           { $$ = NewAstField(@$, $1.ID_symbolID, NULL); }
    | vpatternField { $$ = $1; }
    ;
lpattern
    : lpatternField                         { $$ = NewAstVPatternSingleton(@$,$1); }
    | TK_LPAREN lpatternField_cl TK_RPAREN  { $$ = NewAstVPatternWithFieldsSb(@$,$2); }
    | TK_LPAREN TK_RPAREN                   { $$ = NewAstVPatternWithFieldsSb(@$,NULL); }
    ;
vpattern
    : TK_LPAREN vpatternField_cl TK_RPAREN  { $$ = NewAstVPatternWithFieldsSb(@$,$2); }
    | TK_LPAREN TK_RPAREN                   { $$ = NewAstVPatternWithFieldsSb(@$,NULL); }
    ;
tpattern
    : TK_LSQBRK tpatternField_cl TK_RSQBRK  { $$ = NewAstVPatternWithFieldsSb(@$,$2); }
    | TK_LTHAN  tpatternField_cl TK_GTHAN   { $$ = NewAstVPatternWithFieldsSb(@$,$2); }
    ;

vpatternField_cl
    : vpatternField                             { $$ = NULL; sb_push($$,$1); }
    | vpatternField_cl TK_COMMA vpatternField   { $$ = $1; sb_push($$,$3); }
    ;
lpatternField_cl
    : lpatternField                             { $$ = NULL; sb_push($$,$1); }
    | lpatternField_cl TK_COMMA lpatternField   { $$ = $1; sb_push($$,$3); }
    ;
tpatternField_cl
    : tpatternField                             { $$ = NULL; sb_push($$,$1); }
    | tpatternField_cl TK_COMMA tpatternField   { $$ = $1; sb_push($$,$3); }
    ;
vstructExprField_cl
    : vstructExprField                              { $$ = NULL; sb_push($$,$1); }
    | vstructExprField_cl TK_COMMA vstructExprField { $$ = $1; sb_push($$,$3); }
    ;

%%

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
