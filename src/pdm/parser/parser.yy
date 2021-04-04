/* parser.yy: specifies a grammar + code to produce a parser using `bison` parser generator.
 */

%require "3.2"

%language "C++"

/* write a parser header file, please */
%defines

%define api.namespace {pdm::parser}

// selecting parser type:
// %glr-parser
// %define lr.type lalr
%define lr.type ielr
// %define lr.type canonical-lr
// %define api.pure true

// including headers:
%code requires {
    #include "pdm/core/config.hh"

    #include "pdm/feedback/feedback.hh"
    #include "pdm/feedback/severity.hh"
    #include "pdm/feedback/letter.hh"
    #include "pdm/feedback/note.hh"

    #include "pdm/ast/node.hh"
    #include "pdm/ast/manager.hh"
    #include "pdm/ast/visitor.hh"

    #include "pdm/parser/lexer.hh"

    #include "pdm/source/local-script-source.hh"
    #include "pdm/source/local-package-source.hh"
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
%param {pdm::source::ISource* source}
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

//
// Scripts:
//

%type <pdm::ast::Script*> script
%type <std::vector<pdm::ast::HeaderStmt*>> script_header
%type <pdm::ast::HeaderStmt*> script_header_stmt
%type <pdm::ast::Script::Field*> script_field
%type <std::vector<pdm::ast::Script::Field*>> script_field_sl

//
// Modules:
//

%type <pdm::ast::BaseModExp*> native_mod_exp
%type <std::vector<pdm::ast::BaseModExp::Field*>> mod_field_sl
%type <pdm::ast::BaseModExp::Field*> mod_field

//
// Stmt:
//

%type <pdm::ast::Stmt*> chain_prefix_stmt const_stmt val_stmt var_stmt set_stmt discard_stmt
%type <pdm::ast::HeaderStmt*> import_stmt
%type <std::vector<ast::ImportStmt::FieldGroup*>> import_field_group_sl0;
%type <ast::ImportStmt::FieldGroup*> import_field_group;
%type <std::vector<ast::ImportStmt::Field*>> import_field_cl1;


/* %type <pdm::ast::Stmt*> linkStmt linkStmtItem */
/* %type <std::vector<pdm::ast::Stmt*>> linkStmtContent */

//
// Shared:
//

%type <TokenInfo> tid vid cid floatl stringl
%type <pdm::ast::ModAddress*> mod_prefix

//
// Expression Nonterminals:
//

%type <pdm::ast::Exp*> expr long_exp
%type <std::vector<pdm::ast::Exp*>> /* expr_cl0 */ expr_cl2

%type <pdm::ast::Exp*> bracketed_exp int_expr
%type <pdm::ast::Exp*> primary_exp /* unit_exp */
%type <std::vector<pdm::ast::StringExp::Piece>> stringls
%type <pdm::ast::Exp*> paren_exp vtupleExpr vstructExpr
%type <pdm::ast::Exp*> if_exp chain_exp lambda_exp
%type <std::vector<pdm::ast::Stmt*>> chain_prefix
%type <pdm::ast::Exp*> unary_exp
%type <pdm::ast::UnaryOperator> unary_op

%type <pdm::ast::Exp*> postfix_exp 
%type <pdm::ast::Exp*> vcall_exp
%type <pdm::ast::Exp*> dot_name_exp dot_index_exp

%type <pdm::ast::Exp*> binary_exp 
%type <pdm::ast::Exp*> mul_binary_exp add_binary_exp cmp_binary_exp eq_binary_exp and_binary_exp xor_binary_exp or_binary_exp
%type <pdm::ast::BinaryOperator> mul_binary_op add_binary_op cmp_binary_op eq_binary_op

%type <pdm::ast::TypeQueryExp*> type_query_exp
%type <std::vector<pdm::ast::TypeQueryExp*>> type_query_exp_sl0
%type <pdm::ast::TypeQueryKind> type_query_op

%type <pdm::ast::StructExp::Field*> struct_exp_field
%type <std::vector<pdm::ast::StructExp::Field*>> struct_exp_field_cl

//
// TypeSpec Nonterminals:
//

%type <pdm::ast::TypeSpec*> type_spec
%type <pdm::ast::TypeSpec*> tuple_type_spec struct_type_spec enum_type_spec
%type <pdm::ast::TypeSpec*> mod_prefix_tid
%type <pdm::ast::FnTypeSpec*> fn_type_spec
%type <pdm::ast::TypeSpec*> array_type_spec
%type <std::vector<pdm::ast::TypeSpec*>> /* type_spec_cl1 */ type_spec_cl2
%type <pdm::ast::StructTypeSpec::Field*> struct_type_spec_field
%type <pdm::ast::EnumTypeSpec::Field*> enum_type_spec_field
%type <std::vector<pdm::ast::StructTypeSpec::Field*>> struct_type_spec_field_cl
%type <std::vector<pdm::ast::EnumTypeSpec::Field*>> enum_type_spec_field_cl

//
// ClassSpec Nonterminals:
//

%type <pdm::ast::ClassSpec*> class_spec
%type <pdm::ast::ClassSpec*> primary_class_spec class_exp_class_spec
%type <pdm::ast::ClassSpec*> mod_prefix_cid_class_spec

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
%type <std::vector<pdm::ast::TPattern::Field*>> tpattern_field_cl1
%type <pdm::ast::TArg*> targ
%type <pdm::ast::VArg*> varg
%type <std::vector<pdm::ast::TArg*>> targ_cl
%type <std::vector<pdm::ast::VArg*>> varg_cl

%code provides {
    // int yylex(pdm::parser::TokenInfo *lvalp, pdm::source::Loc *llocp, pdm::source::ISource* source, pdm::parser::Lexer* lexer);
    int yylex(pdm::parser::parser::semantic_type* st, pdm::source::Loc* llocp, pdm::source::ISource* source, pdm::parser::Lexer* lexer);
    void yyerror(pdm::source::Loc* llocp, char const* message, pdm::source::ISource* source, pdm::parser::Lexer* lexer);
}

%token <TokenInfo> VID   "val_id"
%token <TokenInfo> TID   "TypeId"
%token <TokenInfo> CID   "CLS_ID"
%token <TokenInfo> HOLE  "__42__"

%token KW_USING "using"
%token KW_MOD "mod"
%token KW_STRUCT "struct"
%token KW_ENUM "enum"
%token KW_TYPECLASS "typeclass"
%token KW_IF "if"
%token KW_THEN "then"
%token KW_ELSE "else"
%token KW_MATCH "match"     /* reserved */
%token KW_WITH "with"       /* reserved */
%token KW_IMPORTS "imports"
%token KW_EXTERN "extern"
%token KW_FROM "from"
%token KW_CONST "const"
%token KW_VAL "val"
%token KW_VAR "var"
%token KW_LET "let"
%token KW_SET "set"
%token KW_FN "anonymous_fn"
%token KW_AND "and"
%token KW_XOR "xor" 
%token KW_OR "or" 
%token KW_NOT "not"
%token KW_OUT "out"
%token KW_INOUT "inout"
%token KW_DISCARD "discard"
%token KW_AS "as"
%token KW_FOR "for"
%token KW_CORE_PROFILE "CORE_PROFILE"           /* todo: add to lexer */
%token KW_BROWSER_PROFILE "BROWSER_PROFILE"     /* todo: add to lexer */
%token KW_NATIVE_PROFILE "NATIVE_PROFILE"       /* todo: add to lexer */

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
%token EOS       "EOS"

%token COLON_LTHAN ":<"
%token GTHAN_COLON ">:"

%token NONE      "<null>"


%start script;

%%

/*
 * Scripts:
 */

script: script_header script_field_sl {
    $$ = mgr->new_script(source, @$, std::move($1), std::move($2));

    // setting the returnp here => this is the node parser returns.  
    *returnp = $$; 
};

script_header
    : %empty                                        { $$.reserve(16); }
    | script_header script_header_stmt SEMICOLON    { $$ = std::move($1); $$.push_back($2); }
    ;
script_header_stmt
    : import_stmt
    ;

script_field
    : KW_MOD vid native_mod_exp  { $$ = mgr->new_script_field(@$, $2.ID_intstr, $3); }
    ;
script_field_sl
    : script_field SEMICOLON                    { $$.push_back($1); }
    | script_field_sl script_field SEMICOLON    { $$ = std::move($1); $$.push_back($2); }
    ;

/*
 * Modules:
 */

native_mod_exp
    :          LCYBRK mod_field_sl RCYBRK     { $$ = mgr->new_native_mod_exp(@$, nullptr, std::move($2)); }
    | tpattern LCYBRK mod_field_sl RCYBRK     { $$ = mgr->new_native_mod_exp(@$, $1, std::move($3)); }
    |          LCYBRK              RCYBRK     { $$ = mgr->new_native_mod_exp(@$, nullptr, std::move(std::vector<ast::BaseModExp::Field*>{})); }
    | tpattern LCYBRK              RCYBRK     { $$ = mgr->new_native_mod_exp(@$, $1, std::move(std::vector<ast::BaseModExp::Field*>{})); }
    ;
mod_field_sl
    :              mod_field SEMICOLON  { $$.push_back($1); }
    | mod_field_sl mod_field SEMICOLON  { $$ = std::move($1); $$.push_back($2); }
    ;
mod_field
    : KW_LET vid BIND long_exp    { $$ = mgr->new_value_field_for_mod_exp(@$, $2.ID_intstr, $4); }
    | KW_LET tid BIND type_spec   { $$ = mgr->new_type_field_for_mod_exp(@$, $2.ID_intstr, $4); }
    | KW_LET cid BIND class_spec  { $$ = mgr->new_class_field_for_mod_exp(@$, $2.ID_intstr, $4); }
    | KW_MOD vid native_mod_exp   { $$ = mgr->new_mod_field_for_mod_exp(@$, $2.ID_intstr, $3); }
    | KW_LET vid vpattern type_spec BIND bracketed_exp {
        auto desugared_type_spec = mgr->new_fn_type_spec(@$, $3, $4);
        auto desugared_exp = mgr->new_lambda_exp(@$, desugared_type_spec, $6);
        $$ = mgr->new_value_field_for_mod_exp(@$, $2.ID_intstr, desugared_exp);
      }
    | KW_LET cid LPAREN tid class_spec RPAREN BIND LCYBRK type_query_exp_sl0 RCYBRK {
         auto class_spec = mgr->new_class_exp_class_spec(@$, $4.ID_intstr, $5, std::move($9));
         $$ = mgr->new_class_field_for_mod_exp(@$, $2.ID_intstr, class_spec);
      }
    ;

/*
 * Statements:
 */

import_stmt
    : KW_IMPORTS LCYBRK import_field_group_sl0 RCYBRK {
        $$ = mgr->new_import_stmt(@$, std::move($3));
      }
    ;
import_field_group_sl0
    : %empty {}
    | import_field_group_sl0 import_field_group SEMICOLON  { $$ = std::move($1); $$.push_back($2); }
    ;
import_field_group
    : import_field_cl1 KW_FROM stringl   { $$ = mgr->new_import_field_group(@$, std::move($1), *$3.String_utf8string); };
    ;
import_field_cl1
    : vid                           { $$.push_back(mgr->new_import_field(@1, $1.ID_intstr)); }
    | import_field_cl1 COMMA vid    { $$ = std::move($1); $$.push_back(mgr->new_import_field(@3, $3.ID_intstr)); }
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

tid: TID;   /* type-id */
vid: VID;   /* value-id */
cid: CID;   /* class-id */

floatl
    : FLOAT_LIT
    ;
stringl
    : SQSTRING_LIT
    | DQSTRING_LIT
    ;
mod_prefix
    :            vid                       DBL_COLON  { $$ = mgr->new_mod_address(@$, nullptr, $1.ID_intstr, std::move(std::vector<ast::TArg*>{})); }
    |            vid LSQBRK targ_cl RSQBRK DBL_COLON  { $$ = mgr->new_mod_address(@$, nullptr, $1.ID_intstr, std::move($3)); }
    | mod_prefix vid                       DBL_COLON  { $$ = mgr->new_mod_address(@$, $1, $2.ID_intstr, std::move(std::vector<ast::TArg*>{})); }
    | mod_prefix vid LSQBRK targ_cl RSQBRK DBL_COLON  { $$ = mgr->new_mod_address(@$, $1, $2.ID_intstr, std::move($4)); }
    ;

/*
 * Expressions:
 */

expr: binary_exp
    ;
long_exp
    : expr
    | lambda_exp
    ;

/*
 * expr_cl0
 *     : %empty                 {}
 *     | expr_cl0 COMMA expr    { $$ = std::move($1); $$.push_back($3); }
 *     ;
 *
 */

expr_cl2
    : expr COMMA expr        { $$.reserve(2); $$.push_back($1); $$.push_back($3); }
    | expr_cl2 COMMA expr    { $$ = std::move($1); $$.push_back($3); }
    ;
type_query_exp_sl0
    : %empty                                      {}
    | type_query_exp_sl0 type_query_exp SEMICOLON { $$ = std::move($1); $$.push_back($2); }
    ;

bracketed_exp
    : paren_exp
    | vtupleExpr
    | vstructExpr
    | chain_exp
    ;

/*
 * unit_exp
 *     : LCYBRK RCYBRK     { $$ = mgr->new_unit_exp(@$); }
 *     ;
 *
 */

paren_exp
    : LPAREN long_exp RPAREN  { $$ = mgr->new_paren_exp(@$, $2); }
    ;
vtupleExpr
    : LPAREN RPAREN                { $$ = mgr->new_tuple_exp(@$, std::move(std::vector<ast::Exp*>())); }
    | LPAREN expr COMMA RPAREN     { $$ = mgr->new_tuple_exp(@$, std::move(std::vector(1,$2))); }
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
    | mod_prefix vid    { $$ = mgr->new_module_dot_name_exp(@$, $1, $2.ID_intstr); }
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
    : KW_IF bracketed_exp bracketed_exp                         { $$ = mgr->new_if_exp(@$, $2, $3, nullptr); }
    | KW_IF bracketed_exp bracketed_exp KW_ELSE primary_exp     { $$ = mgr->new_if_exp(@$, $2, $3, $5); }
    ;
chain_exp
    : LCYBRK                       RCYBRK      { $$ = mgr->new_chain_exp(@$, std::move(std::vector<ast::Stmt*>{}), nullptr); }
    | LCYBRK long_exp              RCYBRK      { $$ = mgr->new_chain_exp(@$, std::move(std::vector<ast::Stmt*>{}), $2); }
    | LCYBRK chain_prefix          RCYBRK      { $$ = mgr->new_chain_exp(@$, std::move($2), nullptr); }
    | LCYBRK chain_prefix long_exp RCYBRK      { $$ = mgr->new_chain_exp(@$, std::move($2), $3); }
    ;
chain_prefix
    : chain_prefix_stmt             SEMICOLON   { $$.push_back($1); }
    | chain_prefix chain_prefix_stmt SEMICOLON  { $$ = std::move($1); $$.push_back($2); }
    ;
lambda_exp
    : fn_type_spec bracketed_exp   { $$ = mgr->new_lambda_exp(@$, $1, $2); }
    ;

postfix_exp
    : primary_exp
    | vcall_exp
    | dot_name_exp
    | dot_index_exp
    ;
vcall_exp
    : postfix_exp LPAREN RPAREN             { $$ = mgr->new_vcall_exp(@$, $1, std::move(std::vector<ast::VArg*>{})); }
    | postfix_exp LPAREN varg_cl RPAREN     { $$ = mgr->new_vcall_exp(@$, $1, std::move($3)); }
    ;
dot_name_exp
    : postfix_exp DOT VID                       { $$ = mgr->new_struct_dot_name_exp(@$, $1, $3.ID_intstr); }
    | type_spec DBL_COLON TID                       { $$ = mgr->new_enum_dot_name_exp(@$, $1, $3.ID_intstr, nullptr); }
    | type_spec DBL_COLON TID KW_USING paren_exp    { $$ = mgr->new_enum_dot_name_exp(@$, $1, $3.ID_intstr, $5); }
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
    : type_spec type_query_op type_spec   { $$ = mgr->new_type_query_exp(@$, $2, $1, $3); }
    ;
type_query_op
    : COLON_LTHAN   { $$ = ast::TypeQueryKind::LhsSubtypesRhs; }
    | GTHAN_COLON   { $$ = ast::TypeQueryKind::LhsSupertypesRhs; }
    | EQUALS        { $$ = ast::TypeQueryKind::LhsEqualsRhs; }
    ;

/*
 * TypeSpecs:
 */

/*
 *  type_spec_cl1
 *      : type_spec                    { $$.push_back($1); }
 *      | type_spec_cl1 COMMA type_spec { $$ = std::move($1); $$.push_back($3); }
 *      ;
 */

type_spec_cl2
    : type_spec COMMA type_spec     { $$.reserve(2); $$.push_back($1); $$.push_back($3); }
    | type_spec_cl2 COMMA type_spec { $$ = std::move($1); $$.push_back($3); }
    ;

type_spec
    : tid               { $$ = mgr->new_id_type_spec(@$, $1.ID_intstr); }
    | mod_prefix_tid
    | tuple_type_spec
    | array_type_spec
    | struct_type_spec
    | enum_type_spec
    | fn_type_spec  { $$ = dynamic_cast<ast::TypeSpec*>($1); }
    ;

mod_prefix_tid
    : mod_prefix tid        { $$ = mgr->new_ma_type_spec(@$, $1, $2.ID_intstr); }
    ;

tuple_type_spec
    : LCYBRK type_spec     RCYBRK  { $$ = mgr->new_tuple_type_spec(@$, std::move(std::vector(1,$2))); }
    | LCYBRK type_spec_cl2 RCYBRK  { $$ = mgr->new_tuple_type_spec(@$, std::move($2)); }
    ;
array_type_spec
    : LSQBRK type_spec ASTERISK expr RSQBRK     { $$ = nullptr; }
    ;

struct_type_spec
    : LCYBRK struct_type_spec_field_cl RCYBRK  { $$ = mgr->new_struct_type_spec(@$, std::move($2)); }
    ;
struct_type_spec_field_cl
    : struct_type_spec_field                                  { $$.push_back($1); }
    | struct_type_spec_field_cl COMMA struct_type_spec_field  { $$ = std::move($1); $$.push_back($3); }
    ;
struct_type_spec_field
    : vid type_spec                 { $$ = mgr->new_struct_type_spec_field(@$, $1.ID_intstr, $2); }
    ;

enum_type_spec_field
    : tid               { $$ = mgr->new_enum_type_spec_field(@$, $1.ID_intstr, nullptr); }
    | tid type_spec     { $$ = mgr->new_enum_type_spec_field(@$, $1.ID_intstr, $2); }
    ;
enum_type_spec_field_cl
    : enum_type_spec_field                                  { $$.push_back($1); }
    | enum_type_spec_field_cl COMMA enum_type_spec_field    { $$ = std::move($1); $$.push_back($3); }
    ;
enum_type_spec
    : KW_ENUM LCYBRK enum_type_spec_field_cl RCYBRK     { $$ = mgr->new_enum_type_spec(@$, std::move($3)); }
    ;
fn_type_spec
    : KW_FN vpattern type_spec { $$ = mgr->new_fn_type_spec(@$, $2, $3); }
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
    : primary_class_spec
    ;
primary_class_spec
    : cid               { $$ = mgr->new_id_class_spec(@$, $1.ID_intstr); }
    | mod_prefix_cid_class_spec
    | class_exp_class_spec
    ;
mod_prefix_cid_class_spec
    : mod_prefix cid    { $$ = mgr->new_ma_class_spec(@$, std::move($1), $2.ID_intstr); }
    ;

/* todo: implement class_exp_class_spec in parser.yy */
class_exp_class_spec
    : KW_TYPECLASS LPAREN tid class_spec RPAREN LCYBRK type_query_exp_sl0 RCYBRK {
            $$ = mgr->new_class_exp_class_spec(@$, $3.ID_intstr, $4, std::move($7));
        }
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
    : vid type_spec   { $$ = mgr->new_value_tpattern_field(@$, $1.ID_intstr, $2); }
    | tid class_spec  { $$ = mgr->new_type_tpattern_field(@$, $1.ID_intstr, $2); }
    ;

destructured_lpattern
    : LCYBRK lpattern_field_cl RCYBRK  { $$ = mgr->new_lpattern(@$, std::move($2), true); }
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
    : LSQBRK tpattern_field_cl1 RSQBRK  { $$ = mgr->new_tpattern(@$, std::move($2), false); }
    ;

vpattern_field_cl
    : vpattern_field                          { $$.push_back($1); }
    | vpattern_field_cl COMMA vpattern_field   { $$ = std::move($1); $$.push_back($3); }
    ;
lpattern_field_cl
    : lpattern_field                           { $$.push_back($1); }
    | lpattern_field_cl COMMA lpattern_field   { $$ = std::move($1); $$.push_back($3); }
    ;
tpattern_field_cl1
    : tpattern_field                          { $$.push_back($1); }
    | tpattern_field_cl1 COMMA tpattern_field   { $$ = std::move($1); $$.push_back($3); }
    ;
struct_exp_field_cl
    : struct_exp_field                              { $$.push_back($1); }
    | struct_exp_field_cl COMMA struct_exp_field    { $$ = std::move($1); $$.push_back($3); }
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

    ast::Script* parse_script(ast::Manager* manager, source::LocalScriptSource* source) {
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
        // std::cout << "YACC error: " << message << " at " << loc << std::endl;
    }

}

int yylex (
    pdm::parser::parser::semantic_type* semval,
    pdm::source::Loc* llocp,
    pdm::source::ISource* source,
    pdm::parser::Lexer* lexer
) {
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
