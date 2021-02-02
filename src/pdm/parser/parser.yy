/* parser.yy: specifies a grammar + code to produce a parser using `bison` parser generator.
 */

/* TODO:
 * - implement 'extern_stmt'
 *   - extern fn
 *   - extern type
 * - [x] implement 'type_query_exp'
 * - implement 'Fn' (type_specs...) type_spec
 */

%require "3.2"

%language "C++"

/* write a parser header file, please */
%defines

%define api.namespace {pdm::parser}

// selecting parser type:
// %glr-parser
// %define lr.type lalr
// %define lr.type ielr
// %define lr.type canonical-lr
// %define api.pure true

// including headers:
%code requires {
    #include "pdm/core/config.hh"

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
    #include "pdm/ast/setspec/class_spec.hh"
    #include "pdm/ast/setspec/type_spec.hh"
    #include "pdm/ast/setspec/struct.hh"
    #include "pdm/ast/setspec/tcall.hh"

    #include "pdm/parser/reader.hh"
    #include "pdm/parser/lexer.hh"

    #include "pdm/source/source.hh"
    #include "pdm/source/pos.hh"
    #include "pdm/source/loc.hh"

    #include "pdm/feedback/feedback.hh"
    #include "pdm/feedback/note.hh"
    #include "pdm/feedback/severity.hh"
    #include "pdm/feedback/letter.hh"
}

%code provides {
    using Tk = pdm::parser::parser::token_kind_type;
}

%{
    // #define YYSTYPE pdm::parser::TokenInfo
%}

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

//
// File Nonterminals:
//

%type <pdm::ast::Script*> script
%type <std::vector<pdm::ast::Stmt*>> script_head
%type <pdm::ast::Stmt*> script_head_stmt
%type <std::vector<pdm::ast::ModStmt*>> script_body
%type <pdm::ast::ModStmt*> script_body_stmt

%type <pdm::ast::ModStmt*> top_mod_stmt 
%type <pdm::ast::ModContentStmt*> sub_mod_stmt
%type <std::vector<pdm::ast::ModContentStmt*>> mod_content

//
// Stmt:
//

%type <pdm::ast::ModContentStmt*> mod_content_stmt
%type <pdm::ast::Stmt*> chain_prefix_stmt const_stmt val_stmt var_stmt set_stmt discard_stmt
%type <pdm::ast::Stmt*> import_stmt
%type <pdm::ast::ModContentStmt*> mod_val_stmt mod_type_stmt mod_enum_stmt mod_typeclass_stmt
%type <pdm::ast::ModEnumStmt::Field*> enum_field
%type <std::vector<pdm::ast::ModEnumStmt::Field*>> unprefixed_enum_field_pl enum_field_pl

%type <pdm::ast::Stmt*> extern_stmt;

/* %type <pdm::ast::Stmt*> linkStmt linkStmtItem */
/* %type <std::vector<pdm::ast::Stmt*>> linkStmtContent */

//
// Shared:
//

%type <TokenInfo> tid vid floatl stringl
%type <std::vector<pdm::intern::String>> mod_prefix

//
// Expression Nonterminals:
//

%type <pdm::ast::Exp*> expr long_exp
%type <std::vector<pdm::ast::Exp*>> expr_cl0 expr_cl2
%type <std::vector<pdm::ast::TypeQueryExp*>> type_query_exp_sl

%type <pdm::ast::Exp*> bracketed_exp unit_exp int_expr
%type <pdm::ast::Exp*> primary_exp 
%type <std::vector<pdm::ast::StringExp::Piece>> stringls
%type <pdm::ast::Exp*> paren_exp vtupleExpr vstructExpr
%type <pdm::ast::Exp*> if_exp chain_exp lambda_exp
%type <std::vector<pdm::ast::Stmt*>> chain_prefix
%type <pdm::ast::Exp*> unary_exp
%type <pdm::ast::UnaryOperator> unary_op

%type <pdm::ast::Exp*> postfix_exp 
%type <pdm::ast::Exp*> tcall_exp vcall_exp
%type <pdm::ast::Exp*> dot_name_exp dot_index_exp

%type <pdm::ast::Exp*> binary_exp 
%type <pdm::ast::Exp*> mul_binary_exp add_binary_exp cmp_binary_exp eq_binary_exp and_binary_exp xor_binary_exp or_binary_exp
%type <pdm::ast::BinaryOperator> mul_binary_op add_binary_op cmp_binary_op eq_binary_op

%type <pdm::ast::TypeQueryExp*> type_query_exp
%type <pdm::ast::TypeQueryKind> type_query_op

%type <pdm::ast::StructExp::Field*> struct_exp_field
%type <std::vector<pdm::ast::StructExp::Field*>> struct_exp_field_cl

//
// TypeSpec Nonterminals:
//

%type <pdm::ast::TypeSpec*> type_spec long_type_spec
%type <pdm::ast::TypeSpec*> primary_type_spec paren_type_spec tuple_type_spec struct_type_spec mod_prefix_tid fn_type_spec
%type <pdm::ast::TypeSpec*> postfix_type_spec tcall_type_spec
%type <pdm::ast::TypeSpec*> unary_type_spec
%type <std::vector<pdm::ast::TypeSpec*>> type_spec_cl1 type_spec_cl2
%type <pdm::ast::StructTypeSpec::Field*> struct_type_spec_field
%type <std::vector<pdm::ast::StructTypeSpec::Field*>> struct_type_spec_field_cl

//
// ClassSpec Nonterminals:
//

%type <pdm::ast::ClassSpec*> class_spec
%type <pdm::ast::ClassSpec*> primary_class_spec
%type <pdm::ast::ClassSpec*> postfix_class_spec

//
// Pattern Nonterminals:
//

%type <pdm::ast::LPattern*> lpattern destructured_lpattern
%type <pdm::ast::VPattern*> vpattern 
%type <pdm::ast::TPattern*> tpattern
%type <pdm::ast::VPattern::Field*> vpattern_field 
%type <pdm::ast::LPattern::Field*> lpattern_field
%type <pdm::ast::TPattern::Field*> tpattern_field
%type <std::vector<pdm::ast::VPattern::Field*>> vpattern_field_cl 
%type <std::vector<pdm::ast::LPattern::Field*>> lpattern_field_cl 
%type <std::vector<pdm::ast::TPattern::Field*>> tpattern_field_cl
%type <pdm::ast::TArg*> targ
%type <pdm::ast::VArg*> varg
%type <std::vector<pdm::ast::TArg*>> targ_cl
%type <std::vector<pdm::ast::VArg*>> varg_cl
%type <std::vector<pdm::ast::TPattern*>> tpattern_seq

%code provides {
    // int yylex(pdm::parser::TokenInfo *lvalp, pdm::source::Loc *llocp, pdm::source::Source* source, pdm::parser::Lexer* lexer);
    int yylex(pdm::parser::parser::semantic_type* st, pdm::source::Loc* llocp, pdm::source::Source* source, pdm::parser::Lexer* lexer);
    void yyerror(pdm::source::Loc* llocp, char const* message, pdm::source::Source* source, pdm::parser::Lexer* lexer);
}

%token <TokenInfo> VID   "<val_id>"
%token <TokenInfo> TID   "<TypeId>"
%token <TokenInfo> HOLE  "<__42__>"

%token KW_USING "using"
%token KW_MOD "module"
%token KW_SUB "sub"
%token KW_IF "if" 
%token KW_THEN "then"
%token KW_ELSE "else"
%token KW_MATCH "match"
%token KW_WITH "with"
%token KW_IMPORT "import"
%token KW_EXTERN "extern"
%token KW_FROM "from"
%token KW_CONST "const"
%token KW_VAL "val" 
%token KW_VAR "var"
%token KW_SET "set" 
%token KW_FN "fn" 
%token KW_LAMBDA "lambda"
%token KW_TFN "Fn"
%token KW_TYPE "type" 
%token KW_AND "and" 
%token KW_XOR "xor" 
%token KW_OR "or" 
%token KW_NOT "not"
%token KW_TYPECLASS "typeclass"
%token KW_OUT "out"
%token KW_INOUT "inout"
%token KW_DISCARD "discard"

%token <TokenInfo> DINT_LIT "42"
%token <TokenInfo> XINT_LIT "0x2a"
%token <TokenInfo> UNSIGNED_DINT_LIT "42u"
%token <TokenInfo> UNSIGNED_XINT_LIT "0x2Au"
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
%token COLON_DASH  ":-"
%token EOS       "EOS"

%token COLON_LTHAN ":<"
%token GTHAN_COLON ">:"

%token NONE      "<null>"


%start script;

%%

/*
 * Scripts:
 */

script: script_head script_body { 
    $$ = mgr->new_script(source, @$, std::move($1), std::move($2)); 

    // setting the returnp here => this is the node parser returns.  
    *returnp = $$; 
};

script_head
    : %empty                                    { $$.reserve(16); }
    | script_head script_head_stmt SEMICOLON    { $$ = std::move($1); $$.push_back($2); }
    ;
script_head_stmt
    : import_stmt
    | extern_stmt
    ;

script_body
    : %empty                                  { $$.reserve(16); }
    | script_body script_body_stmt SEMICOLON  { $$ = std::move($1); $$.push_back($2); }
    ;
script_body_stmt
    : top_mod_stmt
    ;

/*
 * Modules:
 */

top_mod_stmt
    : KW_MOD TID LCYBRK mod_content RCYBRK    { $$ = mgr->new_mod_stmt(@$, $2.ID_intstr, std::move(std::vector<ast::TPattern*>{}), std::move($4)); }
    ;
sub_mod_stmt
    : KW_SUB TID              LCYBRK mod_content RCYBRK    { $$ = mgr->new_mod_stmt(@$, $2.ID_intstr, std::move(std::vector<ast::TPattern*>{}), std::move($4)); }
    | KW_SUB TID tpattern_seq LCYBRK mod_content RCYBRK    { $$ = mgr->new_mod_stmt(@$, $2.ID_intstr, std::move($3), std::move($5)); }
    ;
mod_content
    : mod_content_stmt SEMICOLON                { $$.push_back($1); }
    | mod_content mod_content_stmt SEMICOLON    { $$ = std::move($1); $$.push_back($2); }
    ;

/*
 * Statements:
 */

mod_content_stmt
    : mod_val_stmt
    | mod_type_stmt
    | mod_enum_stmt
    | mod_typeclass_stmt
    | sub_mod_stmt
    ;
mod_val_stmt
    : vid              BIND expr    { $$ = mgr->new_internal_mod_val_stmt(@$, $1.ID_intstr, std::move(std::vector<ast::TPattern*>{}), $3); }
    | vid tpattern_seq BIND expr    { $$ = mgr->new_internal_mod_val_stmt(@$, $1.ID_intstr, std::move($2), $4); }
    | vid type_spec              KW_FROM tid stringl  { $$ = mgr->new_external_mod_val_stmt(@$, $1.ID_intstr, std::move(std::vector<ast::TPattern*>{}), $2, $4.ID_intstr, *$5.String_utf8string); }
    | vid tpattern_seq type_spec KW_FROM tid stringl  { $$ = mgr->new_external_mod_val_stmt(@$, $1.ID_intstr, std::move($2), $3, $5.ID_intstr, *$6.String_utf8string); }
    ;
mod_type_stmt
    : tid              BIND long_type_spec   { $$ = mgr->new_mod_type_stmt(@$, $1.ID_intstr, std::move(std::vector<ast::TPattern*>{}), $3); }
    | tid tpattern_seq BIND long_type_spec   { $$ = mgr->new_mod_type_stmt(@$, $1.ID_intstr, std::move($2), $4); }
    ;
mod_enum_stmt
    : tid              enum_field_pl    { $$ = mgr->new_mod_enum_stmt(@$, $1.ID_intstr, std::move(std::vector<ast::TPattern*>{}), std::move($2)); }
    | tid tpattern_seq enum_field_pl    { $$ = mgr->new_mod_enum_stmt(@$, $1.ID_intstr, std::move($2), std::move($3)); }
    ;
enum_field_pl
    : PIPE unprefixed_enum_field_pl { $$ = std::move($2); }
    ;
unprefixed_enum_field_pl
    : enum_field                                { $$.push_back($1); }
    | unprefixed_enum_field_pl PIPE enum_field  { $$ = std::move($1); $$.push_back($3); }
    ;
enum_field
    : tid                            { $$ = mgr->new_enum_stmt_field(@$, $1.ID_intstr, std::move(std::vector<ast::TypeSpec*>{}), false); }
    | tid LPAREN RPAREN              { $$ = mgr->new_enum_stmt_field(@$, $1.ID_intstr, std::move(std::vector<ast::TypeSpec*>{}), true); }
    | tid LPAREN type_spec_cl1 RPAREN { $$ = mgr->new_enum_stmt_field(@$, $1.ID_intstr, std::move($3), true); }
    ;
mod_typeclass_stmt
    : tid              COLON_DASH LTHAN tid class_spec GTHAN LCYBRK type_query_exp_sl RCYBRK { 
        $$ = mgr->new_mod_typeclass_stmt(@$, $1.ID_intstr, $4.ID_intstr, $5, std::move(std::vector<ast::TPattern*>{}), std::move($8)); 
      }
    | tid tpattern_seq COLON_DASH LTHAN tid class_spec GTHAN LCYBRK type_query_exp_sl RCYBRK { 
        $$ = mgr->new_mod_typeclass_stmt(@$, $1.ID_intstr, $5.ID_intstr, $6, std::move($2), std::move($9)); 
      }
    ;

import_stmt
    : KW_IMPORT tid KW_FROM stringl KW_TYPE stringl    { $$ = mgr->new_import_stmt(@$, $2.ID_intstr, *$4.String_utf8string, *$6.String_utf8string); }
    ;
extern_stmt
    : KW_EXTERN tid KW_FROM expr    { $$ = mgr->new_extern_stmt(@$, $2.ID_intstr, $4); }
    ;

chain_prefix_stmt
    : const_stmt
    | val_stmt
    | var_stmt
    | set_stmt
    | discard_stmt
    ;
const_stmt
    : KW_CONST lpattern BIND expr { $$ = mgr->new_const_stmt(@$, $2, $4); }
    ;
val_stmt
    : KW_VAL lpattern BIND expr   { $$ = mgr->new_val_stmt(@$, $2, $4); }
    ;
var_stmt
    : KW_VAR lpattern BIND expr   { $$ = mgr->new_var_stmt(@$, $2, $4); }
    ;
set_stmt
    : KW_SET expr BIND expr   { $$ = mgr->new_set_stmt(@$, $2, $4); }
    ; 
discard_stmt
    : KW_DISCARD expr   { $$ = mgr->new_discard_stmt(@$, $2); }
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
mod_prefix
    : tid COLON               { $$.push_back($1.ID_intstr); }
    | mod_prefix vid COLON    { $$ = std::move($1); }
    ;

/*
 * Expressions:
 */

expr: binary_exp
    ;
long_exp
    : expr
    ;

expr_cl0
    : %empty                 {}
    | expr_cl0 COMMA expr    { $$ = std::move($1); $$.push_back($3); }
    ;
expr_cl2
    : expr COMMA expr        { $$.reserve(2); $$.push_back($1); $$.push_back($3); }
    | expr_cl2 COMMA expr    { $$ = std::move($1); $$.push_back($3); }
    ;
type_query_exp_sl
    : type_query_exp SEMICOLON         { $$.push_back($1); }
    | type_query_exp_sl type_query_exp SEMICOLON { $$ = std::move($1); $$.push_back($2); }
    ;

bracketed_exp
    : unit_exp
    | paren_exp
    | vtupleExpr
    | vstructExpr
    | chain_exp
    ;
unit_exp
    : LPAREN RPAREN     { $$ = mgr->new_unit_exp(@$); }
    | LCYBRK RCYBRK     { $$ = mgr->new_unit_exp(@$); }
    ;
paren_exp
    : LPAREN long_exp RPAREN  { $$ = mgr->new_paren_exp(@$, $2); }
    ;
vtupleExpr
    : LPAREN expr COMMA RPAREN     { $$ = mgr->new_tuple_exp(@$, std::move(std::vector(1,$2))); }
    | LPAREN expr_cl2   RPAREN     { $$ = mgr->new_tuple_exp(@$, std::move($2)); }
    ;
vstructExpr
    : LCYBRK struct_exp_field_cl RCYBRK     { $$ = mgr->new_struct_exp(@$, std::move($2)); }
    ;
primary_exp
    : bracketed_exp
    | vid            { $$ = mgr->new_id_exp(@$, $1.ID_intstr); }
    | int_expr
    | floatl         { $$ = mgr->new_float_exp(@$, $1.Float); }
    | stringls       { $$ = mgr->new_string_exp(@$, std::move($1)); }
    | if_exp
    | lambda_exp
    ;
int_expr
    : DINT_LIT  { $$ = mgr->new_int_exp(@$, $1.Int, ast::IntExp::Base::Dec, false); }
    | XINT_LIT  { $$ = mgr->new_int_exp(@$, $1.Int, ast::IntExp::Base::Hex, false); }
    | UNSIGNED_DINT_LIT  { $$ = mgr->new_int_exp(@$, $1.Int, ast::IntExp::Base::Dec, true); }
    | UNSIGNED_XINT_LIT  { $$ = mgr->new_int_exp(@$, $1.Int, ast::IntExp::Base::Hex, true); }
    ;
stringls
    : SQSTRING_LIT           { $$.emplace_back(@$, *$1.String_utf8string, ast::StringExp::QuoteKind::SingleQuote); }
    | DQSTRING_LIT           { $$.emplace_back(@$, *$1.String_utf8string, ast::StringExp::QuoteKind::DoubleQuote); }
    | stringls SQSTRING_LIT  { $$ = std::move($1); $$.emplace_back(@2, *$2.String_utf8string, ast::StringExp::QuoteKind::SingleQuote); }
    | stringls DQSTRING_LIT  { $$ = std::move($1); $$.emplace_back(@2, *$2.String_utf8string, ast::StringExp::QuoteKind::DoubleQuote); }
    ;
if_exp
    : KW_IF bracketed_exp KW_THEN bracketed_exp                         { $$ = mgr->new_if_exp(@$, $2, $4, nullptr); }
    | KW_IF bracketed_exp KW_THEN bracketed_exp KW_ELSE primary_exp     { $$ = mgr->new_if_exp(@$, $2, $4, $6); }
    ;
chain_exp
    : LCYBRK expr             RCYBRK      { $$ = mgr->new_chain_exp(@$, std::move(std::vector<ast::Stmt*>{}), $2); }
    | LCYBRK chain_prefix      RCYBRK      { $$ = mgr->new_chain_exp(@$, std::move($2), nullptr); }
    | LCYBRK chain_prefix expr RCYBRK      { $$ = mgr->new_chain_exp(@$, std::move($2), $3); }
    ;
chain_prefix
    : chain_prefix_stmt             SEMICOLON  { $$.push_back($1); }
    | chain_prefix chain_prefix_stmt SEMICOLON  { $$ = std::move($1); $$.push_back($2); }
    ;
lambda_exp
    : KW_FN vpattern                bracketed_exp   { $$ = mgr->new_lambda_exp(@$, $2, nullptr, $3); }
    | KW_FN vpattern ARROW type_spec bracketed_exp   { $$ = mgr->new_lambda_exp(@$, $2, $4, $5); }
    ;

postfix_exp
    : primary_exp
    | tcall_exp
    | vcall_exp
    | dot_name_exp
    | dot_index_exp
    ;
tcall_exp
    : postfix_exp LSQBRK targ_cl RSQBRK  { $$ = mgr->new_tcall_exp(@$, $1, std::move($3)); }
    ;
vcall_exp
    : postfix_exp LPAREN RPAREN             { $$ = mgr->new_vcall_exp(@$, $1, std::move(std::vector<ast::VArg*>{})); }
    | postfix_exp LPAREN varg_cl RPAREN     { $$ = mgr->new_vcall_exp(@$, $1, std::move($3)); }
    ;
dot_name_exp
    : postfix_exp DOT VID                           { $$ = mgr->new_struct_dot_name_exp(@$, $1, $3.ID_intstr); }
    | postfix_exp DOT TID LPAREN expr_cl0 RPAREN    { $$ = mgr->new_enum_dot_name_exp(@$, $1, $3.ID_intstr, std::move($5)); }
    | mod_prefix VID   { $$ = mgr->new_module_dot_exp(@$, std::move($1), $2.ID_intstr); }
    ;
dot_index_exp
    : postfix_exp DOT int_expr      { $$ = mgr->new_dot_index_exp(@$, $1, $3, ast::DotIndexExp::RhsHint::LhsNotPtr); }
    | postfix_exp DOT bracketed_exp { $$ = mgr->new_dot_index_exp(@$, $1, $3, ast::DotIndexExp::RhsHint::LhsNotPtr); }
    ;

unary_exp
    : postfix_exp
    | unary_op unary_exp     { $$ = mgr->new_unary_exp(@$, $1, $2); }
    ;
unary_op
    : PLUS       { $$ = ast::UnaryOperator::Plus; }
    | MINUS      { $$ = ast::UnaryOperator::Minus; }
    | ASTERISK   { $$ = ast::UnaryOperator::DeRef; }
    | CARET      { $$ = ast::UnaryOperator::GetRef; }
    | KW_NOT     { $$ = ast::UnaryOperator::Not; }
    ;

binary_exp
    : or_binary_exp
    ;
mul_binary_op
    : ASTERISK   { $$ = ast::BinaryOperator::Mul; }
    | FSLASH     { $$ = ast::BinaryOperator::Div; }
    | PERCENT    { $$ = ast::BinaryOperator::Rem; }
    ;
mul_binary_exp
    : unary_exp
    | mul_binary_exp mul_binary_op unary_exp   { $$ = mgr->new_binary_exp(@$, $2, $1, $3); }
    ;
add_binary_op
    : PLUS   { $$ = ast::BinaryOperator::Add; }
    | MINUS  { $$ = ast::BinaryOperator::Subtract; }
    ;
add_binary_exp
    : mul_binary_exp
    | add_binary_exp add_binary_op mul_binary_exp   { $$ = mgr->new_binary_exp(@$, $2, $1, $3); }
    ;
cmp_binary_op
    : LTHAN     { $$ = ast::BinaryOperator::Less; }
    | LETHAN    { $$ = ast::BinaryOperator::LessOrEq; }
    | GTHAN     { $$ = ast::BinaryOperator::Greater; }
    | GETHAN    { $$ = ast::BinaryOperator::GreaterOrEq; }
    ;
cmp_binary_exp
    : add_binary_exp
    | cmp_binary_exp cmp_binary_op add_binary_exp   { $$ = mgr->new_binary_exp(@$, $2, $1, $3); }
    ;
eq_binary_op
    : EQUALS     { $$ = ast::BinaryOperator::Equals; }
    | NEQUALS    { $$ = ast::BinaryOperator::NotEquals; }
    ;
eq_binary_exp
    : cmp_binary_exp
    | eq_binary_exp eq_binary_op cmp_binary_exp { $$ = mgr->new_binary_exp(@$, $2, $1, $3); }
    ;
and_binary_exp
    : eq_binary_exp
    | and_binary_exp KW_AND eq_binary_exp  { $$ = mgr->new_binary_exp(@$, ast::BinaryOperator::And, $1, $3); }
    ;
xor_binary_exp
    : and_binary_exp
    | xor_binary_exp KW_XOR and_binary_exp { $$ = mgr->new_binary_exp(@$, ast::BinaryOperator::XOr, $1, $3); }
    ;
or_binary_exp
    : xor_binary_exp
    | or_binary_exp KW_OR xor_binary_exp   { $$ = mgr->new_binary_exp(@$, ast::BinaryOperator::Or, $1, $3); }
    ;

type_query_exp
    : type_spec type_query_op long_type_spec   { $$ = mgr->new_type_query_exp(@$, $2, $1, $3); }
    ;
type_query_op
    : COLON_LTHAN   { $$ = ast::TypeQueryKind::LhsSubtypesRhs; }
    | GTHAN_COLON   { $$ = ast::TypeQueryKind::LhsSupertypesRhs; }
    | DBL_COLON     { $$ = ast::TypeQueryKind::LhsEqualsRhs; }
    ;

/*
 * TypeSpecs:
 */

type_spec
    : unary_type_spec
    ;
type_spec_cl1
    : type_spec                    { $$.push_back($1); }
    | type_spec_cl1 COMMA type_spec { $$ = std::move($1); $$.push_back($3); }
    ;
type_spec_cl2
    : type_spec COMMA type_spec     { $$.reserve(2); $$.push_back($1); $$.push_back($3); }
    | type_spec_cl2 COMMA type_spec { $$ = std::move($1); $$.push_back($3); }
    ;

struct_type_spec_field
    : vid type_spec                { $$ = mgr->new_struct_type_spec_field(@$, $1.ID_intstr, $2); }
    ;
struct_type_spec_field_cl
    : struct_type_spec_field                               { $$.push_back($1); }
    | struct_type_spec_field_cl COMMA struct_type_spec_field  { $$ = std::move($1); $$.push_back($3); }
    ;

primary_type_spec
    : tid               { $$ = mgr->new_id_type_spec(@$, $1.ID_intstr); }
    | paren_type_spec
    | tuple_type_spec
    | mod_prefix_tid
    | fn_type_spec
    ;
paren_type_spec
    : LPAREN type_spec RPAREN    { $$ = mgr->new_paren_type_spec(@$, $2); }
    ;
tuple_type_spec
    : LPAREN type_spec COMMA RPAREN  { $$ = mgr->new_tuple_type_spec(@$, std::move(std::vector(1,$2))); }
    | LPAREN type_spec_cl2   RPAREN  { $$ = mgr->new_tuple_type_spec(@$, std::move($2)); }
    ;
mod_prefix_tid
    : mod_prefix tid        { $$ = mgr->new_dot_name_type_spec_with_mod_prefix(@$, std::move($1), $2.ID_intstr); }
    ;
fn_type_spec
    : KW_TFN vpattern primary_type_spec { $$ = mgr->new_fn_type_spec(@$, std::move($2), $3); }
    ;

postfix_type_spec
    : primary_type_spec
    | tcall_type_spec
    ;
tcall_type_spec
    : postfix_type_spec LSQBRK targ_cl RSQBRK  { $$ = mgr->new_tcall_type_spec(@$, $1, std::move($3)); }
    ;

unary_type_spec
    : postfix_type_spec
    ;

long_type_spec
    : unary_type_spec
    | struct_type_spec
    ;
struct_type_spec
    : LCYBRK struct_type_spec_field_cl RCYBRK  { $$ = mgr->new_struct_type_spec(@$, std::move($2)); }
    ;

targ: type_spec { $$ = mgr->new_targ_type_spec(@$, $1); }
    | expr     { $$ = mgr->new_targ_exp(@$, $1); }
    ;
targ_cl
    : targ                  { $$.push_back($1); }
    | targ_cl COMMA targ    { $$ = std::move($1); $$.push_back($3); }
    ;
varg: expr                  { $$ = mgr->new_varg(@$, $1, ast::VArgAccessSpec::In); }
    | KW_OUT expr           { $$ = mgr->new_varg(@$, $2, ast::VArgAccessSpec::Out); }
    | KW_INOUT expr         { $$ = mgr->new_varg(@$, $2, ast::VArgAccessSpec::InOut); }
    ;
varg_cl
    : varg                  { $$.push_back($1); }
    | varg_cl COMMA varg    { $$ = std::move($1); $$.push_back($3); }
    ;


/*
 * ClassSpec exclusively used for RHS of tpattern_field with a TID
 * and as candidate spec in typeclass stmt.
 */

class_spec
    : postfix_class_spec
    ;
primary_class_spec
    : tid   { $$ = mgr->new_id_class_spec(@$, $1.ID_intstr); }
    ;
postfix_class_spec
    : primary_class_spec
    | postfix_class_spec LSQBRK targ_cl RSQBRK  { $$ = mgr->new_tcall_class_spec(@$, $1, std::move($3)); }
    ;

/*
 * Patterns & fields
 */

struct_exp_field
    : vid BIND expr { $$ = mgr->new_struct_exp_field(@$, $1.ID_intstr, $3); }
    ;
vpattern_field
    :          vid type_spec { $$ = mgr->new_vpattern_field(@$, $1.ID_intstr, $2, ast::VArgAccessSpec::In); }
    | KW_OUT   vid type_spec { $$ = mgr->new_vpattern_field(@$, $2.ID_intstr, $3, ast::VArgAccessSpec::Out); }
    | KW_INOUT vid type_spec { $$ = mgr->new_vpattern_field(@$, $2.ID_intstr, $3, ast::VArgAccessSpec::InOut); }
    ;
lpattern_field
    : vid type_spec  { $$ = mgr->new_lpattern_field(@$, ast::LPattern::FieldKind::IdTypeSpecPair, $1.ID_intstr, $2); }
    | vid           { $$ = mgr->new_lpattern_field(@$, ast::LPattern::FieldKind::IdSingleton, $1.ID_intstr); }
    ;
tpattern_field
    : vid type_spec   { $$ = mgr->new_tpattern_field(@$, ast::TPattern::FieldKind::Value, $1.ID_intstr, $2); }
    | tid class_spec  { $$ = mgr->new_tpattern_field(@$, ast::TPattern::FieldKind::Type, $1.ID_intstr, $2); }
    ;

destructured_lpattern
    : LPAREN lpattern_field_cl    RPAREN  { $$ = mgr->new_lpattern(@$, std::move($2), true); }
 /* | LPAREN lpattern_field COMMA RPAREN  { $$ = mgr->new_lpattern(@$, std::move(std::vector<ast::LPattern::Field*>{1,$2}), true)}  */
    ;
lpattern
    : lpattern_field    { $$ = mgr->new_lpattern(@$, std::move(std::vector<ast::LPattern::Field*>{1,$1}), false); }
    | destructured_lpattern
    ;
vpattern
    : LPAREN vpattern_field_cl RPAREN  { $$ = mgr->new_vpattern(@$, std::move($2)); }
    | LPAREN RPAREN                    { $$ = mgr->new_vpattern(@$, std::move(std::vector<ast::VPattern::Field*>{})); }
    ;
tpattern
    :         LSQBRK tpattern_field_cl RSQBRK  { $$ = mgr->new_tpattern(@$, std::move($2), false); }
    | EXCLAIM LSQBRK tpattern_field_cl RSQBRK  { $$ = mgr->new_tpattern(@$, std::move($3), true); }
    ;

vpattern_field_cl
    : vpattern_field                          { $$.push_back($1); }
    | vpattern_field_cl COMMA vpattern_field   { $$ = std::move($1); $$.push_back($3); }
    ;
lpattern_field_cl
    : lpattern_field                          { $$.push_back($1); }
    | lpattern_field_cl COMMA lpattern_field   { $$ = std::move($1); $$.push_back($3); }
    ;
tpattern_field_cl
    : tpattern_field                          { $$.push_back($1); }
    | tpattern_field_cl COMMA tpattern_field   { $$ = std::move($1); $$.push_back($3); }
    ;
struct_exp_field_cl
    : struct_exp_field                              { $$.push_back($1); }
    | struct_exp_field_cl COMMA struct_exp_field    { $$ = std::move($1); $$.push_back($3); }
    ;

tpattern_seq
    : tpattern               { $$.push_back($1); }
    | tpattern_seq tpattern  { $$ = std::move($1); $$.push_back($2); }
    ;

%%

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
