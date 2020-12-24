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

/* see this on using C++ variants for Bison:
 *   https://www.gnu.org/software/bison/manual/html_node/A-Simple-C_002b_002b-Example.html
 */

%require "3.2"

%language "C++"
%defines

%define api.namespace {pdm::parser}

// %glr-parser
// %define lr.type lalr
// %define lr.type ielr
// %define lr.type canonical-lr
// %define api.pure true

// we want 'ast.h' and 'extra-tokens.h' in the header
// https://stackoverflow.com/questions/47726404/how-to-put-header-file-to-tab-h-in-bison
%code requires {
    #include "pdm/core/config.hh"

    // todo: include more AST files here:
    #include "pdm/ast/node.hh"
    #include "pdm/ast/manager.hh"
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

// adding an AST manager ptr param to the parser:
%parse-param {pdm::ast::Manager* mgr}

// adding an output ptr param to the parser:
%parse-param {pdm::ast::Script** returnp}

//
// Union:
//

%define api.value.type variant

// %union {
//     pdm::parser::TokenInfo token;
    
//     pdm::ast::Script* script;
//     pdm::ast::Script** script_sb;
    
//     pdm::ast::Stmt* stmt;
//     pdm::ast::Stmt** stmt_sb;

//     pdm::ast::Exp* exp;
//     pdm::ast::Exp** exp_sb;

//     pdm::ast::UnaryOperator uop;
//     pdm::ast::BinaryOperator bop;

//     pdm::ast::StructExp::Field* structexp_field;
//     pdm::ast::StructExp::Field** structexp_field_sb;

//     pdm::ast::Typespec* typespec;
//     pdm::ast::Typespec** typespec_sb;

//     pdm::ast::LPattern* lpattern;
//     pdm::ast::VPattern* vpattern;
//     pdm::ast::TPattern* tpattern;
//     pdm::ast::LPattern::Field* lpattern_field;
//     pdm::ast::VPattern::Field* vpattern_field;
//     pdm::ast::TPattern::Field* tpattern_field;

//     pdm::ast::TArg* tcallexp_arg;
//     pdm::ast::TArg** tcallexp_arg_sb;

//     pdm::ast::TArg* tcallts_arg;
//     pdm::ast::TArg** tcallts_arg_sb;

//     pdm::ast::StructTypespec::Field* structts_field;
//     pdm::ast::StructTypespec::Field** structts_field_sb;
// }

//
// File Nonterminals:
//

%type <pdm::ast::Script*> script
%type <std::vector<pdm::ast::Script*>> scriptContent
%type <pdm::ast::Stmt*> scriptContentStmt

%type <pdm::ast::Stmt*> mod_stmt
%type <std::vector<pdm::ast::Stmt*>> moduleContent

//
// Stmt:
//

%type <pdm::ast::Stmt*> moduleContentStmt
%type <pdm::ast::Stmt*> chainPrefixStmt constStmt letStmt varStmt setStmt discardStmt
%type <pdm::ast::Stmt*> importStmt
%type <pdm::ast::Stmt*> using_stmt
%type <pdm::ast::Stmt*> fn_stmt
%type <pdm::ast::Stmt*> type_stmt enum_stmt typeclass_stmt
%type <pdm::ast::EnumStmt::Field*> enum_field
%type <std::vector<pdm::ast::EnumStmt::Field*>> unprefixed_enum_field_pl enum_field_pl

/* %type <pdm::ast::Stmt*> linkStmt linkStmtItem */
/* %type <std::vector<pdm::ast::Stmt*>> linkStmtContent */

//
// Shared:
//

%type <pdm::parser::TokenInfo> tid vid floatl stringl

//
// Expression Nonterminals:
//

%type <pdm::ast::Exp*> expr
%type <std::vector<pdm::ast::Exp*>> expr_cl1 expr_cl2 expr_sl

%type <pdm::ast::Exp*> parenExpr unitExpr int_expr
%type <pdm::ast::Exp*> primaryExpr 
%type <std::vector<pdm::ast::StringExp::Piece*>> stringls
%type <pdm::ast::Exp*> vparenExpr vtupleExpr vstructExpr
%type <pdm::ast::Exp*> ifThenElseExpr chainExpr vlambdaExpr
%type <std::vector<pdm::ast::Stmt*>> chainPrefix
%type <pdm::ast::Exp*> unaryExpr
%type <pdm::ast::UnaryOperator> unaryOp

%type <pdm::ast::Exp*> postfixExpr 
%type <pdm::ast::Exp*> vtcallExpr vvcallExpr
%type <pdm::ast::Exp*> dotNmExpr dotIxExpr

%type <pdm::ast::Exp*> binaryExpr 
%type <pdm::ast::Exp*> mulBinaryExpr addBinaryExpr cmpBinaryExpr eqBinaryExpr andBinaryExpr xorBinaryExpr orBinaryExpr
%type <pdm::ast::BinaryOperator> mulBinaryOp addBinaryOp cmpBinaryOp eqBinaryOp

%type <pdm::ast::StructExp::Field*> vstructExprField
%type <std::vector<pdm::ast::StructExp::Field*>> vstructExprField_cl

//
// Typespec Nonterminals:
//

%type <pdm::ast::Typespec*> typespec long_typespec
%type <pdm::ast::Typespec*> primaryTypespec tupleTypespec structTypespec mod_prefix_tid
%type <std::vector<pdm::intern::String>> mod_prefix
%type <pdm::ast::Typespec*> postfixTypespec ttcall tdot
%type <pdm::ast::Typespec*> unaryTypespec
%type <std::vector<pdm::ast::Typespec*>> typespec_cl1 typespec_cl2
%type <pdm::ast::StructTypespec::Field*> structTypespecField
%type <std::vector<pdm::ast::StructTypespec::Field*>> structTypespecField_cl

//
// Pattern Nonterminals:
//

%type <pdm::ast::LPattern*> lpattern lpattern_naked
%type <pdm::ast::VPattern*> vpattern 
%type <pdm::ast::TPattern*> tpattern
%type <pdm::ast::VPattern::Field*> vpatternField 
%type <pdm::ast::LPattern::Field*> lpatternField
%type <pdm::ast::TPattern::Field*> tpatternField
%type <std::vector<pdm::ast::VPattern::Field*>> vpatternField_cl 
%type <std::vector<pdm::ast::LPattern::Field*>> lpatternField_cl 
%type <std::vector<pdm::ast::TPattern::Field*>> tpatternField_cl
%type <pdm::ast::TArg*> ttarg vtarg
%type <std::vector<pdm::ast::TArg*>> ttarg_cl vtarg_cl
%type <std::vector<pdm::ast::TPattern*>> tpattern_seq

%code provides {
    int yylex(pdm::parser::TokenInfo *lvalp, pdm::source::Loc *llocp, pdm::source::Source* source, pdm::parser::Lexer* lexer);
    void yyerror(pdm::source::Loc* llocp, char const* message, pdm::source::Source* source, pdm::parser::Lexer* lexer);
}

%token <pdm::parser::TokenInfo> VID   "<val_id>"
%token <pdm::parser::TokenInfo> TID   "<TypeId>"
%token <pdm::parser::TokenInfo> HOLE  "<__42__>"

%token KW_USING "using"
%token KW_MOD "mod"
%token KW_IF "if" 
%token KW_THEN "then"
%token KW_ELSE "else"
%token KW_MATCH "match"
%token KW_WITH "with"
%token KW_IMPORT "import"
%token KW_FROM "from"
%token KW_CONST "const"
%token KW_LET "let" 
%token KW_VAR "var"
%token KW_SET "set" 
%token KW_FN "fn" 
%token KW_TYPE "type" 
%token KW_ENUM "enum"
%token KW_AND "and" 
%token KW_XOR "xor" 
%token KW_OR "or" 
%token KW_NOT "not"
%token KW_TYPECLASS "typeclass"

%token <TokenInfo> DINT_LIT "42"
%token <TokenInfo> XINT_LIT "0x2a"
%token <TokenInfo> FLOAT_LIT "4.2"
%token <TokenInfo> DQSTRING_LIT "\"dq-string-literal\""
%token <TokenInfo> SQSTRING_LIT "'sq-string-literal'"

%token DOT       "."
%token COLON     ":"
%token COMMA     ","
%token SEMICOLON ";"
%token DBL_COLON "::"
%token LPAREN    "("
%token RPAREN    ")"
%token LSQBRK    "["
%token RSQBRK    "]"
%token LCYBRK    "{"
%token RCYBRK    "}"
%token ARROW     "->"
%token ASTERISK  "*"
%token FSLASH    "/"
%token PERCENT   "%"
%token PLUS      "+"
%token MINUS     "-"
%token LTHAN     "<"
%token LETHAN    "<="
%token GTHAN     ">"
%token GETHAN    ">="
%token BIND      "="
%token EQUALS    "=="
%token NEQUALS   "!="
%token CARET     "^"
%token AMPERSAND "&"
%token EXCLAIM   "!"
%token PIPE      "|"
%token EOS       "EOS"

%token NONE      "<null>"

/* Added tokens:
 * KW_YIELD -> KW_DISCARD 
 * NOT -> KW_NOT
 * -> EXCLAIM
 * -> KW_SET
 * -> KW_MODULE
 * -> KW_FROM
 * -> KW_AS
 * -> KW_TYPE
 * -> KW_ENUM
 */

%start script;
// %start module;
// %start letStmt

%%

/*
 * Scripts:
 */

script
    : scriptContent { $$ = mgr->new_script(source, @$, std::move($1)); *returnp = $$; }
    ;
scriptContent
    : scriptContentStmt               SEMICOLON     { $$.push_back($1); }
    | scriptContent scriptContentStmt SEMICOLON     { $$ = std::move($1); $$.push_back($2); }
    ;
scriptContentStmt
    : mod_stmt
    ;

/*
 * Modules:
 */

mod_stmt
    : KW_MOD VID LCYBRK moduleContent RCYBRK    { $$ = mgr->new_mod_stmt(@$, $2.ID_intstr, std::move($4)); }
    ;
moduleContent
    : moduleContentStmt SEMICOLON                   { $$.push_back($1); }
    | moduleContent moduleContentStmt SEMICOLON     { $$ = std::move($1); $$.push_back($2); }
    ;

/*
 * Statements:
 */

chainPrefixStmt
    : constStmt
    | letStmt
    | varStmt
    | setStmt
    | discardStmt
    ;
constStmt
    : KW_CONST lpattern_naked BIND expr { $$ = mgr->new_const_stmt(@$, $2, $4); }
    ;
letStmt
    : KW_LET lpattern_naked BIND expr   { $$ = mgr->new_let_stmt(@$, $2, $4); }
    ;
varStmt
    : KW_VAR lpattern_naked BIND expr   { $$ = mgr->new_var_stmt(@$, $2, $4); }
    ;
setStmt
    : KW_SET expr BIND expr   { $$ = mgr->new_set_stmt(@$, $2, $4); }
    ; 
discardStmt
    : expr    { $$ = mgr->new_discard_stmt(@$, $1); }
    ;

moduleContentStmt
    : fn_stmt
    | type_stmt
    | enum_stmt
    | typeclass_stmt
    | importStmt
    | mod_stmt
    | using_stmt
    ;
fn_stmt
    : KW_FN vid              vpattern ARROW typespec BIND parenExpr   { $$ = mgr->new_fn_stmt(@$, $2.ID_intstr, std::move({}), $3, $5, $7); }
    | KW_FN vid tpattern_seq vpattern ARROW typespec BIND parenExpr   { $$ = mgr->new_fn_stmt(@$, $2.ID_intstr, std::move($3), $4, $6, $8); }
    | KW_FN vid              vpattern                BIND parenExpr   { $$ = mgr->new_fn_stmt(@$, $2.ID_intstr, std::move({}), $3, nullptr, $5); }
    | KW_FN vid tpattern_seq vpattern                BIND parenExpr   { $$ = mgr->new_fn_stmt(@$, $2.ID_intstr, std::move($3), $4, nullptr, $6); }
    ;
type_stmt
    : KW_TYPE tid              BIND long_typespec   { $$ = mgr->new_type_stmt(@$, $2.ID_intstr, std::move({}), $4); }
    | KW_TYPE tid tpattern_seq BIND long_typespec   { $$ = mgr->new_type_stmt(@$, $2.ID_intstr, std::move($3), $5); }
    ;
enum_stmt
    : KW_ENUM tid enum_field_pl     { $$ = mgr->new_enum_stmt(@$, $2.ID_intstr, std::move($3)); }
    ;
enum_field_pl
    : PIPE unprefixed_enum_field_pl { $$ = std::move($2); }
    | unprefixed_enum_field_pl      { $$ = std::move($1); }
    ;
unprefixed_enum_field_pl
    : enum_field                                { $$.push_back($1); }
    | unprefixed_enum_field_pl PIPE enum_field  { $$ = std::move($1); $$.push_back($3); }
    ;
enum_field
    : tid                            { $$ = mgr->new_enum_stmt_field($1.ID_intstr, std::move({}), false); }
    | tid LPAREN RPAREN              { $$ = mgr->new_enum_stmt_field($1.ID_intstr, std::move({}), true); }
    | tid LPAREN typespec_cl1 RPAREN { $$ = mgr->new_enum_stmt_field($1.ID_intstr, std::move($3), true); }
    ;
typeclass_stmt
    : KW_TYPECLASS tid LTHAN tid typespec GTHAN              BIND LCYBRK expr_sl RCYBRK { 
        $$ = mgr->new_typeclass_stmt(@$, $2.ID_intstr, $4.ID_intstr, $5, std::move({}), std::move($9)); 
      }
    | KW_TYPECLASS tid LTHAN tid typespec GTHAN tpattern_seq BIND LCYBRK expr_sl RCYBRK { 
        $$ = mgr->new_typeclass_stmt(@$, $2.ID_intstr, $4.ID_intstr, $5, std::move($7), std::move($10)); 
      }
    ;

using_stmt
    : KW_USING parenExpr { $$ = mgr->new_using_stmt(@$, $2); }
    ;

importStmt
    : KW_IMPORT vid KW_FROM expr KW_TYPE expr    { $$ = mgr->new_import_stmt(@$, $2.ID_intstr, $4, $6); }
    ;

/*
 * Shared tokens:
 */

tid: TID;
vid: VID;
floatl
    : FLOAT_LIT
    ;
stringl
    : SQSTRING_LIT
    | DQSTRING_LIT
    ;

/*
 * Expressions:
 */

expr: binaryExpr
    ;
expr_cl1
    : expr                   { $$.push_back($1); }
    | expr_cl1 COMMA expr    { $$ = std::move($1); $$.push_back($3); }
    ;
expr_cl2
    : expr COMMA expr        { $$.reserve(2); $$.push_back($1); $$.push_back($3); }
    | expr_cl2 COMMA expr    { $$ = std::move($1); $$.push_back($3); }
    ;
expr_sl
    : expr SEMICOLON         { $$.push_back($1); }
    | expr_sl expr SEMICOLON { $$ = std::move($1); $$.push_back($2); }
    ;

parenExpr
    : unitExpr
    | vparenExpr
    | vtupleExpr
    | vstructExpr
    | chainExpr
    ;
unitExpr
    : LPAREN RPAREN
    | LCYBRK RCYBRK
    ;
primaryExpr
    : parenExpr
    | vid            { $$ = mgr->new_id_exp(@$, $1.ID_intstr); }
    | int_expr
    | floatl         { $$ = mgr->new_float_exp(@$, $1.Float); }
    | stringls       { $$ = mgr->new_string_exp(@$, std::move($1)); }
    | ifThenElseExpr
    | vlambdaExpr
    ;
int_expr
    : DINT_LIT  { $$ = mgr->new_int_exp(@$, $1.Int, IntExp::Base::Dec); }
    | XINT_LIT  { $$ = mgr->new_int_exp(@$, $1.Int, IntExp::Base::Hex); }
    ;
stringls
    : stringl           { $$.emplace_back(@1, *$1.String_utf8string); }
    | stringls stringl  { $$ = std::move($1); $$.emplace_back(@2, $2.String_utf8string); }
    ;
vparenExpr
    : LPAREN expr RPAREN  { $$ = mgr->new_paren_exp(@$, $2); }
    ;
vtupleExpr
    : LPAREN expr COMMA RPAREN     { $$ = mgr->new_tuple_exp(@$, std::move(std::vector(1,$2))); }
    | LPAREN expr_cl2   RPAREN     { $$ = mgr->new_tuple_exp(@$, std::move($2)); }
    ;
vstructExpr
    : LCYBRK vstructExprField_cl RCYBRK     { $$ = mgr->new_struct_exp(@$, std::move($2)); }
    ;
ifThenElseExpr
    : KW_IF parenExpr KW_THEN parenExpr                      { $$ = mgr->new_if_exp(@$, $2, $4, nullptr); }
    | KW_IF parenExpr KW_THEN parenExpr KW_ELSE primaryExpr  { $$ = mgr->new_if_exp(@$, $2, $4, $6); }
    ;
chainExpr
    : LCYBRK expr             RCYBRK      { $$ = mgr->new_chain_exp(@$, std::move({}), $2); }
    | LCYBRK chainPrefix      RCYBRK      { $$ = mgr->new_chain_exp(@$, std::move($2), nullptr); }
    | LCYBRK chainPrefix expr RCYBRK      { $$ = mgr->new_chain_exp(@$, std::move($2), $3); }
    ;
chainPrefix
    : chainPrefixStmt             SEMICOLON  { $$.push_back($1); }
    | chainPrefix chainPrefixStmt SEMICOLON  { $$ = std::move($1); $$.push_back($2); }
    ;
vlambdaExpr
    : KW_FN lpattern BIND parenExpr   { $$ = mgr->new_lambda_exp(@$, $2, $4); }
    ;

postfixExpr
    : primaryExpr
    | vtcallExpr
    | vvcallExpr
    | dotNmExpr
    | dotIxExpr
    ;
vtcallExpr
    : postfixExpr LSQBRK vtarg_cl RSQBRK  { $$ = mgr->new_tcall_exp(@$, $1, std::move($3)); }
    ;
vvcallExpr
    : postfixExpr LPAREN RPAREN            { $$ = mgr->new_vcall_exp(@$, $1, std::move(std::vector<ast::Exp*>{})); }
    | postfixExpr LPAREN expr_cl1 RPAREN   { $$ = mgr->new_vcall_exp(@$, $1, std::move($3)); }
    ;
dotNmExpr
    : postfixExpr DOT VID   { $$ = mgr->new_dot_name_exp(@$, $1, $3.ID_intstr, ast::DotNameExp::RhsHint::LhsStruct); }
    | postfixExpr DOT TID   { $$ = mgr->new_dot_name_exp(@$, $1, $3.ID_intstr, ast::DotNameExp::RhsHint::LhsEnum); }
    ;
dotIxExpr
    : postfixExpr DOT        int_expr       { $$ = mgr->new_dot_index_exp(@$, $1, $3); }
    | postfixExpr DOT LPAREN expr RPAREN    { $$ = mgr->new_dot_index_exp(@$, $1, $4); }
    ;

unaryExpr
    : postfixExpr
    | unaryOp unaryExpr     { $$ = mgr->new_unary_exp(@$, $1, $2); }
    ;
unaryOp
    : PLUS       { $$ = ast::UnaryOperator::Plus; }
    | MINUS      { $$ = ast::UnaryOperator::Minus; }
    | ASTERISK   { $$ = ast::UnaryOperator::DeRef; }
    | CARET      { $$ = ast::UnaryOperator::GetRef; }
    | KW_NOT     { $$ = ast::UnaryOperator::Not; }
    ;

binaryExpr
    : orBinaryExpr
    ;
mulBinaryOp
    : ASTERISK   { $$ = ast::BinaryOperator::Mul; }
    | FSLASH     { $$ = ast::BinaryOperator::Div; }
    | PERCENT    { $$ = ast::BinaryOperator::Rem; }
    ;
mulBinaryExpr
    : unaryExpr
    | mulBinaryExpr mulBinaryOp unaryExpr   { $$ = mgr->new_binary_exp(@$, $2, $1, $3); }
    ;
addBinaryOp
    : PLUS   { $$ = ast::BinaryOperator::Add; }
    | MINUS  { $$ = ast::BinaryOperator::Subtract; }
    ;
addBinaryExpr
    : mulBinaryExpr
    | addBinaryExpr addBinaryOp mulBinaryExpr   { $$ = mgr->new_binary_exp(@$, $2, $1, $3); }
    ;
cmpBinaryOp
    : LTHAN     { $$ = BOP_LTHAN; }
    | LETHAN    { $$ = BOP_LETHAN; }
    | GTHAN     { $$ = BOP_GTHAN; }
    | GETHAN    { $$ = BOP_GETHAN; }
    ;
cmpBinaryExpr
    : addBinaryExpr
    | cmpBinaryExpr cmpBinaryOp addBinaryExpr   { $$ = mgr->new_binary_exp(@$, $2, $1, $3); }
    ;
eqBinaryOp
    : EQUALS     { $$ = BOP_EQUALS; }
    | NEQUALS    { $$ = BOP_NEQUALS; }
    ;
eqBinaryExpr
    : cmpBinaryExpr
    | eqBinaryExpr eqBinaryOp cmpBinaryExpr { $$ = mgr->new_binary_exp(@$, $2, $1, $3); }
    ;
andBinaryExpr
    : eqBinaryExpr
    | andBinaryExpr KW_AND eqBinaryExpr  { $$ = mgr->new_binary_exp(@$, BOP_AND, $1, $3); }
    ;
xorBinaryExpr
    : andBinaryExpr
    | xorBinaryExpr KW_XOR andBinaryExpr { $$ = mgr->new_binary_exp(@$, BOP_XOR, $1, $3); }
    ;
orBinaryExpr
    : xorBinaryExpr
    | orBinaryExpr KW_OR xorBinaryExpr   { $$ = mgr->new_binary_exp(@$, BOP_OR, $1, $3); }
    ;

/*
 * Typespecs:
 */

typespec
    : unaryTypespec
    ;
typespec_cl1
    : typespec                    { $$.push_back($1); }
    | typespec_cl1 COMMA typespec { $$ = std::move($1); $$.push_back($3); }
    ;
typespec_cl2
    : typespec COMMA typespec     { $$.reserve(2); $$.push_back($1); $$.push_back($3); }
    | typespec_cl2 COMMA typespec { $$ = std::move($1); $$.push_back($3); }
    ;

structTypespecField
    : vid typespec                { $$ = mgr->new_struct_typespec_field(@$, $1.ID_intstr, $2); }
    ;
structTypespecField_cl
    : structTypespecField                               { $$.push_back($1); }
    | structTypespecField_cl COMMA structTypespecField  { $$ = std::move($1); $$.push_back($3); }
    ;

primaryTypespec
    : tid               { $$ = mgr->new_id_typespec(@$, $1.ID_intstr); }
    | tupleTypespec
    | mod_prefix_tid
    ;
tupleTypespec
    : LPAREN typespec COMMA RPAREN  { $$ = mgr->new_tuple_typespec(@$, std::move(std::vector(1,$2))); }
    | LPAREN typespec_cl2   RPAREN  { $$ = mgr->new_tuple_typespec(@$, std::move($2)); }
    ;
mod_prefix_tid
    : mod_prefix tid        { $$ = mgr->new_dot_name_typespec_with_mod_prefix(@$, std::move($1), $2.ID_intstr); }
    ;
mod_prefix
    : vid DOT               { $$.push_back($1.ID_intstr); }
    | mod_prefix vid DOT    { $$ = std::move($1); }
    ;

postfixTypespec
    : primaryTypespec
    | ttcall
    | tdot
    ;
ttcall
    : postfixTypespec LSQBRK ttarg_cl RSQBRK  { $$ = mgr->new_tcall_typespec(@$, $1, std::move($3)); }
    ;
tdot: postfixTypespec DOT VID   { $$ = mgr->new_dot_name_typespec_with_type_prefix(@$, $1, $3.ID_intstr); }
    ;

unaryTypespec
    : postfixTypespec
    | AMPERSAND unaryTypespec    { $$ = mgr->new_ptr_typespec(@$,$2); }
    ;

long_typespec
    : unaryTypespec
    | structTypespec
    ;
structTypespec
    : LCYBRK structTypespecField_cl RCYBRK  { $$ = mgr->new_struct_typespec(@$, std::move($2)); }
    ;

ttarg
    : typespec  { $$ = mgr->new_targ(@$, ) }
    | expr      { $$ = NewAstVal2Type(@$,$1); }
    ;
ttarg_cl
    : ttarg                     { $$ = NULL; sb_push($$,$1); }
    | ttarg_cl COMMA ttarg   { $$ = $1; sb_push($$,$3); }
    ;

/* value contexts' targs (template args): typespecs have Type2Val wrappers */
vtarg
    : typespec { $$ = NewAstType2Val(@$,$1); }
    | expr
    ;
vtarg_cl
    : vtarg                     { $$ = NULL; sb_push($$,$1); }
    | vtarg_cl COMMA vtarg   { $$ = $1; sb_push($$,$3); }
    ;

/*
 * Patterns & fields:
 */

vstructExprField
    : vid BIND expr { $$ = mgr->new_struct_exp_field(@$, $1.ID_intstr, $3); }
    ;
vpatternField
    : vid typespec { $$ = mgr->new_vpattern_field(@$, $1.ID_intstr, $2); }
    ;
lpatternField
    : vid typespec  { $$ = mgr->new_lpattern_field(@$, ast::LPattern::FieldKind::IdTypespecPair, $1.ID_intstr, $2); }
    | vid           { $$ = mgr->new_lpattern_field(@$, ast::LPattern::FieldKind::IdSingleton, $1.ID_intstr); }
    ;
tpatternField
    : vid typespec  { $$ = mgr->new_tpattern_field(@$, ast::TPattern::FieldKind::Val, $1.ID_intstr, $2); }
    | tid typespec  { $$ = mgr->new_tpattern_field(@$, ast::TPattern::FieldKind::Type, $1.ID_intstr, $2); }
    ;

lpattern
    : LPAREN lpatternField_cl RPAREN  { $$ = mgr->new_lpattern(@$, std::move($2)); }
    | LPAREN RPAREN                   { $$ = mgr->new_lpattern(@$, std::move(std::vector<ast::LPattern::Field*>{})); }
    ;
lpattern_naked
    : lpatternField                   { $$ = mgr->new_lpattern(@$, std::move(std::vector<ast::LPattern::Field*>{1,$1})); }
    | lpattern
    ;
vpattern
    : LPAREN vpatternField_cl RPAREN  { $$ = mgr->new_vpattern(@$, std::move($2)); }
    | LPAREN RPAREN                   { $$ = mgr->new_vpattern(@$, std::move(std::vector<ast::VPattern::Field*>{})); }
    ;
tpattern
    :         LSQBRK tpatternField_cl RSQBRK  { $$ = mgr->new_tpattern(@$, std::move($2), false); }
    | EXCLAIM LSQBRK tpatternField_cl RSQBRK  { $$ = mgr->new_tpattern(@$, std::move(std::vector<ast::TPattern::Field*>{}), true); }
    ;

vpatternField_cl
    : vpatternField                          { $$.push_back($1); }
    | vpatternField_cl COMMA vpatternField   { $$ = std::move($1); $$.push_back($3); }
    ;
lpatternField_cl
    : lpatternField                          { $$.push_back($1); }
    | lpatternField_cl COMMA lpatternField   { $$ = std::move($1); $$.push_back($3); }
    ;
tpatternField_cl
    : tpatternField                          { $$.push_back($1); }
    | tpatternField_cl COMMA tpatternField   { $$ = std::move($1); $$.push_back($3); }
    ;
vstructExprField_cl
    : vstructExprField                              { $$.push_back($1); }
    | vstructExprField_cl COMMA vstructExprField    { $$ = std::move($1); $$.push_back($3); }
    ;

tpattern_seq
    : tpattern               { $$.push_back($1); }
    | tpattern_seq tpattern  { $$ = std::move($1); $$.push_back($2); }
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


ast::Script* parse_script(ast::Manager* manager, source::Source* source) {
    Lexer lexer;
    if (!lexer.setup(source)) {
        return nullptr;
    }

    ast::Script* out = nullptr;
    int result = yyparse(source, &lexer, manager, &out);
    if (result == 0) {
        return out;
    } else {
        return nullptr;
    }
}

// int yylex (YYSTYPE *lvalp) {
//     /* TODO: Put value onto Bison stack. */
//     return NULL;
// }

int yylex(TokenInfo* info, source::Loc* llocp, source::Source* source, parser::Lexer* lexer) {
    // see:
    // https://www.gnu.org/software/bison/manual/html_node/Calling-Convention.html
    
    llocp->source(source);
    int tk = lexer->lex_one_token(info, llocp);
    llocp->source(source);

    if (pdm::DEBUG) {
        // DebugPrintToken("YYLEX:", tk, info, llocp);
    }
    if (tk == EOS) {
        return YYEOF;
    } else {
        return tk;
    }
}

// void yyerror(YYLTYPE* llocp, Source* source, ast::* returnp, char const* message) {
//     Loc loc = FirstLocOfSpan(*llocp);
//     FeedbackNote* note = CreateFeedbackNote("here...", loc, NULL);
//     PostFeedback(
//         FBK_ERROR, note,
//         "Parser error: %s", message
//     );
// }
