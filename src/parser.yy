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

// %glr-parser

%define lr.type lalr
// %define lr.type ielr
// %define lr.type canonical-lr
%define api.pure true
%locations
%define api.location.type {Span}

// adding a 'Source*' param to the lexer and parser:
%param {Source* source}

// adding an output ptr param to the parser:
%parse-param {AstNode** outp}

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
%union {
    TokenInfo token;
    AstNode* nt;
    AstNode** ntSb;
    AstUnaryOperator uop;
    AstBinaryOperator bop;
}

//
// File Nonterminals:
//

%type <nt> script
%type <ntSb> scriptContent
%type <nt> scriptContentStmt

%type <nt> moduleStmt
%type <ntSb> moduleContent

//
// Stmt:
//

%type <nt> moduleContentStmt
%type <nt> chainPrefixStmt letStmt setStmt discardStmt
%type <nt> attachStmt importStmt externStmt
%type <nt> typedefStmt_enum typedefStmt defStmt

//
// Shared:
//

%type <token> tid vid floatl stringl
%type <nt> unit

//
// Expression Nonterminals:
//

%type <nt> expr
%type <ntSb> expr_cl
%type <ntSb> expr_cl2

%type <nt> parenExpr
%type <nt> primaryExpr 
%type <nt> vparen vtuple vstruct 
%type <nt> ifThenElse 
%type <nt> chain
%type <ntSb> chainPrefix
%type <nt> unaryExpr
%type <uop> unaryOp

%type <nt> postfixExpr 
%type <nt> castExpr
%type <nt> vtcall vvcall
%type <nt> dotNmExpr dotIxExpr
%type <nt> colonNmExpr

%type <nt> binaryExpr 
%type <nt> mulBinaryExpr addBinaryExpr cmpBinaryExpr eqBinaryExpr andBinaryExpr xorBinaryExpr orBinaryExpr
%type <bop> mulBinaryOp addBinaryOp cmpBinaryOp eqBinaryOp

//
// Typespec Nonterminals:
//

%type <nt> typespec
%type <nt> primaryTypespec
%type <nt> postfixTypespec
%type <ntSb> typespec_cl

//
// Pattern Nonterminals:
//

%type <nt> lpattern vpattern tpattern
%type <nt> vpatternField lpatternField tpatternField vstructField
%type <ntSb> vpatternField_cl lpatternField_cl tpatternField_cl vstructField_cl
%type <nt>   ttarg vtarg
%type <ntSb> ttarg_cl vtarg_cl


// we want 'ast.h' and 'extra-tokens.h' in the header
// https://stackoverflow.com/questions/47726404/how-to-put-header-file-to-tab-h-in-bison
%code requires {
    #include "ast.h"
    #include "source.h"
    #include "lexer.h"
    #include "extra-tokens.h"

    #include "stb/stretchy_buffer.h"
}

%code provides {
    int yylex(YYSTYPE *lvalp, YYLTYPE *llocp, Source* source);
    void yyerror(YYLTYPE* llocp, Source* source, AstNode** outp, char const* message);
}

%token <token> TK_VID   "a VID (ID with first letter lowercase)"
%token <token> TK_TID   "a TID (ID with first letter uppercase)"
%token <token> TK_HOLE  "a HOLE (ID without any letters)"

%token TK_KW_NAMESPACE  "'namespace'"
%token TK_KW_MOD "'mod'"
%token TK_KW_DO "'do'"
%token TK_KW_IF "'if'" 
%token TK_KW_THEN "'then'"
%token TK_KW_ELSE "'else'"
%token TK_KW_OPERATOR "'operator'"  // deprecated?
%token TK_KW_MATCH "'match'"
%token TK_KW_WITH "'with'"
%token TK_KW_RETURN "'return'"      // deprecated?
%token TK_KW_DISCARD "'discard'"    // deprecated?
%token TK_KW_ATTACH "'attach'"
%token TK_KW_IMPORT "'import'"
%token TK_KW_EXPORT "'export'"      // deprecated? 
%token TK_KW_EXTERN "'extern'"
%token TK_KW_FROM "'from'" 
%token TK_KW_AS "'as'"
%token TK_KW_FUN "'fun'"
%token TK_KW_LET "'let'" 
%token TK_KW_SET "'set'" 
%token TK_KW_DEF "'def'" 
%token TK_KW_TYPE "'type'" 
%token TK_KW_ENUM "'enum'"
%token TK_KW_AND "'and'" 
%token TK_KW_XOR "'xor'" 
%token TK_KW_OR "'or'" 
%token TK_KW_NOT "'not'"
%token TK_KW_TTUPLE "'Tuple'"
%token TK_KW_TARRAY "'Array'"

%token <token> TK_DINT_LIT TK_XINT_LIT TK_FLOAT_LIT 
%token <token> TK_DQSTRING_LIT TK_SQSTRING_LIT

%token TK_DOT "'.'"
%token TK_COLON "':'"
%token TK_COMMA "','"
%token TK_SEMICOLON "';'"
%token TK_DBL_COLON "'::'"      // deprecated?
%token TK_TPL_COLON "':::'"     // deprecated?
%token TK_LPAREN    "'('"
%token TK_RPAREN    "')'"
%token TK_LSQBRK    "'['"
%token TK_RSQBRK    "']'"
%token TK_LCYBRK    "'{'"
%token TK_RCYBRK    "'}'"
%token TK_ARROW     "'->'"
%token TK_ASTERISK  "'*'"
%token TK_FSLASH    "'/'"
%token TK_PERCENT   "'%'"
%token TK_PLUS      "'+'"
%token TK_MINUS     "'-'"
%token TK_LTHAN     "'<'"
%token TK_LETHAN    "'<='"
%token TK_GTHAN     "'>'"
%token TK_GETHAN    "'>='"
%token TK_BIND      "'='"
%token TK_EQUALS    "'=='"
%token TK_NEQUALS   "'!='"
%token TK_DOLLAR    "'$'"       // deprecated?
%token TK_CARET     "'^'"
%token TK_EXCLAIM   "'!'"
%token TK_EOS       "EOS"

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
    | externStmt    { $$ = $1; }
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
    : TK_KW_DO expr    { $$ = NewAstDiscardStmt(@$, $2); }
    ;

moduleContentStmt
    : defStmt               { $$ = $1; }
    | typedefStmt           { $$ = $1; }
    | typedefStmt_enum      { $$ = $1; }
    | attachStmt            { $$ = $1; }
    | importStmt            { $$ = $1; }
    | externStmt            { $$ = $1; }
    | moduleStmt            { $$ = $1; }
    ;
defStmt
    : TK_KW_DEF vid          vpattern TK_ARROW castExpr   { $$ = NewAstDefStmt(@$, $2.ID_symbolID, NULL, $3, $5); }
    | TK_KW_DEF vid tpattern vpattern TK_ARROW castExpr   { $$ = NewAstDefStmt(@$, $2.ID_symbolID, $3,   $4, $6); }
    ;
typedefStmt
    : TK_KW_TYPE tid tpattern TK_BIND typespec   { $$ = NewAstTypedefStmt(@$, $2.ID_symbolID, $3, $5); }
    ;
typedefStmt_enum
    : TK_KW_ENUM tid tpattern TK_BIND vstruct  { $$ = NewAstTypedefEnumStmt(@$, $2.ID_symbolID, $3, $5); }
    ;

attachStmt
    : TK_KW_ATTACH vid TK_KW_FROM stringl TK_KW_AS stringl   { $$ = NewAstAttachStmt(@$, $2.ID_symbolID, $4.String_utf8string, $6.String_utf8string); }
    ;
importStmt
    : TK_KW_IMPORT vid TK_DOT vid               { $$ = NewAstImportStmt(@$, $2.ID_symbolID, $4.ID_symbolID, 0); }
    | TK_KW_IMPORT vid TK_DOT vid TK_ASTERISK   { $$ = NewAstImportStmt(@$, $2.ID_symbolID, $4.ID_symbolID, 1); }
    ;

externStmt
    : TK_KW_EXTERN TK_KW_DEF vid vpattern TK_ARROW typespec   { $$ = NewAstExternStmt(@$, $3.ID_symbolID, $4, NewAstType2Val(@6,$6)); }
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

unit: TK_LPAREN TK_RPAREN   { $$ = NewAstUnit(@$); }
    ; 

/*
 * Expressions:
 */

expr: binaryExpr    { $$ = $1; }
    ;
expr_cl
    : expr                      { $$ = NULL; sb_push(($$),$1); }
    | expr_cl TK_COMMA expr     { $$ = $1; sb_push(($$),$3); }
    ;
expr_cl2
    : expr TK_COMMA expr        { $$ = NULL; sb_push($$,$1); sb_push($$,$3); }
    | expr_cl2 TK_COMMA expr     { $$ = $1; sb_push($$,$3); }
    ;

parenExpr
    : unit          { $$ = $1; }
    | vparen        { $$ = $1; }
    | vtuple        { $$ = $1; }
    | vstruct       { $$ = $1; }
    | chain         { $$ = $1; }
    ;
primaryExpr
    : parenExpr     { $$ = $1; }
    | vid           { $$ = NewAstVID(@$, $1.ID_symbolID); }
    | TK_DINT_LIT   { $$ = NewAstIntLiteral(@$, $1.Int, 10); }
    | TK_XINT_LIT   { $$ = NewAstIntLiteral(@$, $1.Int, 16); }
    | floatl        { $$ = NewAstFloatLiteral(@$, $1.Float); }
    | stringl       { $$ = NewAstStringLiteral(@$, $1.String_utf8string); }
    | ifThenElse    { $$ = $1; }
    ;
vparen
    : TK_LPAREN expr TK_RPAREN  { $$ = NewAstVParen(@$, $2); }
    ;
vtuple
    : TK_LPAREN expr_cl2  TK_RPAREN     { $$ = NewAstVTupleWithFieldsSb(@$, $2); }
    ;
vstruct
    : TK_LCYBRK vstructField_cl TK_RCYBRK     { $$ = NewAstVStructWithFieldsSb(@$, $2); }
    ;
ifThenElse
    : TK_KW_IF parenExpr TK_KW_THEN parenExpr                        { $$ = NewAstIte(@$, $2, $4, NULL); }
    | TK_KW_IF parenExpr TK_KW_THEN parenExpr TK_KW_ELSE parenExpr   { $$ = NewAstIte(@$, $2, $4, $6); }
    ;
chain
    : TK_LCYBRK expr             TK_RCYBRK      { $$ = NewAstChainWith(@$, NULL, $2); }
    | TK_LCYBRK chainPrefix      TK_RCYBRK      { $$ = NewAstChainWith(@$, $2, NULL); }
    | TK_LCYBRK chainPrefix expr TK_RCYBRK      { $$ = NewAstChainWith(@$, $2, $3); }
    ;
chainPrefix
    : chainPrefixStmt             TK_SEMICOLON  { $$ = NULL; sb_push(($$),$1); }
    | chainPrefix chainPrefixStmt TK_SEMICOLON  { $$ = $1; sb_push(($$),$2); }
    ;

postfixExpr
    : primaryExpr   { $$ = $1; }
    | vtcall        { $$ = $1; }
    | vvcall        { $$ = $1; }
    | dotNmExpr     { $$ = $1; }
    | dotIxExpr     { $$ = $1; }
    | colonNmExpr   { $$ = $1; }
    ;
vtcall
    : postfixExpr TK_LSQBRK vtarg_cl TK_RSQBRK  { $$ = NewAstTCallWithArgsSb(@$, $1, $3); }
    ;
vvcall
    : postfixExpr TK_LPAREN TK_RPAREN           { $$ = NewAstVCallWithArgsSb(@$, $1, NULL); }
    | postfixExpr TK_LPAREN expr_cl TK_RPAREN   { $$ = NewAstVCallWithArgsSb(@$, $1, $3); }
    ;
dotNmExpr
    : postfixExpr TK_DOT TK_VID         { $$ = NewAstDotName(@$, $1, $3.ID_symbolID); }
    ;
dotIxExpr
    : postfixExpr TK_DOT TK_DINT_LIT    { $$ = NewAstDotIndex(@$, $1, $3.Int); }
    ;
colonNmExpr
    : postfixExpr TK_COLON TK_VID       { $$ = NewAstColonName(@$, $1, $3.ID_symbolID); }
    ;

castExpr
    : postfixExpr        { $$ = $1; }
    | typespec parenExpr { $$ = NewAstVCast(@$, NewAstType2Val(@1,$1), $2); }
    ;

unaryExpr
    : castExpr              { $$ = $1; }
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
    : postfixTypespec  { $$ = $1; }
    ;
typespec_cl
    : typespec                      { $$ = NULL; sb_push($$,$1); }
    | typespec_cl TK_COMMA typespec { $$ = $1; sb_push($$,$3); }
    ;

primaryTypespec
    : tid                                                       { $$ = NewAstTID(@$, $1.ID_symbolID); }
    | TK_KW_TTUPLE TK_LSQBRK typespec_cl TK_RSQBRK              { $$ = NewAstTTupleWithFieldsSb(@$,$3); }
    | TK_KW_TARRAY TK_LSQBRK typespec TK_COMMA expr TK_RSQBRK   { $$ = NewAstTArray(@$,$3,NewAstVal2Type(@$,$5)); } 
    ;
postfixTypespec
    : primaryTypespec                               { $$ = $1; }
    | postfixTypespec TK_LSQBRK ttarg_cl TK_RSQBRK  { $$ = NewAstTCallWithArgsSb(@$, $1, $3); }
    | postfixTypespec TK_CARET                      { $$ = NewAstTPtr(@$, $1); }
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

vstructField
    : vid TK_BIND expr { $$ = NewAstField(@$, $1.ID_symbolID, $3); }
    ;
vstructField_cl
    : vstructField                          { $$ = NULL; sb_push($$,$1); }
    | vstructField_cl TK_COMMA vstructField { $$ = $1; sb_push($$,$3); }
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
    | unit                                  { $$ = NewAstVPatternWithFieldsSb(@$,NULL); }
    ;
vpattern
    : TK_LPAREN vpatternField_cl TK_RPAREN  { $$ = NewAstVPatternWithFieldsSb(@$,$2); }
    | unit                                  { $$ = NewAstVPatternWithFieldsSb(@$,NULL); }
    ;
tpattern
    : TK_LSQBRK tpatternField_cl TK_RSQBRK  { $$ = NewAstVPatternWithFieldsSb(@$,$2); }
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

int yylex(YYSTYPE* lvalp, YYLTYPE* llocp, Source* source) {
    // see:
    // https://www.gnu.org/software/bison/manual/html_node/Calling-Convention.html

    TokenInfo* info = &lvalp->token;
    llocp->source = source;
    int tk = LexOneToken(source,info,llocp);
    if (DEBUG) {
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
