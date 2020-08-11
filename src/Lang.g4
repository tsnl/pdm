grammar Lang;

options {
    language='Python3';
}

fragment L: [a-zA-Z_];
fragment D: [0-9];
fragment X: [0-9a-fA-F];
fragment DC: ~('"' |'\\'|'\r'|'\n') | '\'';
fragment SC: ~('\''|'\\'|'\r'|'\n') | '"';

ID: L (L|D)* ;
DINT: D (D|'_')* ;
XINT: ('0x'|'0X') (X|'_')+ ;
FLOAT: DINT ('.' (D|'_')*)? ([eE] (D|'_')+)? ;
DQSTRING: '"'  DC*  '"';
SQSTRING: '\'' SC* '\'';

IGNORED: (WHITESPACE | LINE_COMMENT) -> skip;
fragment WHITESPACE: (' '|'\t'|'\n'|'\r');
fragment LINE_COMMENT: '#' ~[\r\n\f]*;

sourceFile: importHeader? exportHeader? sourceBody EOF;
importHeader: 'import' '{' its+=field (',' its+=field)* '}' ;
exportHeader: 'export' '{' its+=field (',' its+=field)* '}' ';' ;
sourceBody: (defn_its+=stmt ';')*;

stmt: ts=typespec? lhs=ID                                     '=' rhs=expr  #bindValStmt
    | ts=typespec? lhs=ID '(' (args+=ID ',')* (args+=ID)? ')' '=' rhs=expr  #bindFunStmt
    ;

expr: through=binaryExpr;
primaryExpr
    : ID                                                            #idExpr
    | 'operator' '(' op=anyOp ',' arity=DINT ')'                    #opExpr
    | DINT                                                          #decIntExpr
    | XINT                                                          #hexIntExpr
    | FLOAT                                                         #floatExpr
    | '(' paren_it=expr ')'                                         #parenExpr
    | '{' tuple_its+=field (',' tuple_its+=field)* '}'              #tupleExpr
    | '[' (list_its+=expr (',' list_its+=expr)*)? ']'               #listExpr
    | '{' (prefix_its+=stmt ';')* (result=expr) '}'                 #chainExpr
    | 'if' cond=expr 'then' if_true=expr ('else' if_false=expr)?    #iteExpr
    ;
field: lhs=ID ':' val=expr ;
postfixExpr
    : through=primaryExpr                                       #throughPostfixExpr
    | prefix=postfixExpr '.' suffix=ID                          #dotNameExpr
    | prefix=postfixExpr '.' suffix=DINT                        #dotIndexExpr
    | lhs=postfixExpr '(' (args+=expr (',' args+=expr)*)? ')'   #callExpr
    ;
unaryExpr: through=postfixExpr | op=unaryOp arg=unaryExpr ;
unaryOp: '!' | '+' | '-' | '*' | '^';
mulBinaryExpr: through=unaryExpr | lt=mulBinaryExpr op=binaryMulOp rt=unaryExpr;
addBinaryExpr: through=mulBinaryExpr | lt=addBinaryExpr op=binaryAddOp rt=mulBinaryExpr;
relBinaryExpr: through=addBinaryExpr | lt=relBinaryExpr op=binaryRelOp rt=addBinaryExpr;
eqBinaryExpr:  through=relBinaryExpr | lt=eqBinaryExpr op=binaryEqOp rt=relBinaryExpr;
andBinaryExpr: through=eqBinaryExpr | lt=andBinaryExpr op=binaryAndOp rt=eqBinaryExpr;
orBinaryExpr:  through=andBinaryExpr | lt=orBinaryExpr op=binaryOrOp rt=andBinaryExpr;
binaryExpr: through=orBinaryExpr;
binaryMulOp: '*' | '/' | '%';
binaryAddOp: '+' | '-';
binaryRelOp: '<' | '>' | '<=' | '>=';
binaryEqOp: '==' | '!=';
binaryAndOp: '&&';
binaryOrOp: '||';
binaryOp: binaryMulOp | binaryAddOp | binaryRelOp | binaryEqOp | binaryAndOp | binaryOrOp;
anyOp: unaryOp | binaryOp;

typespec: through=binaryTypespec;
primaryTypespec
    : ID                                            #idTypespec
    | '(' it=typespec ')'                           #parenTypespec
    | '[' its+=typespec (',' its+=typespec)* ']'    #enumTypespec
    | '{' its+=typespec (',' its+=typespec)* '}'    #structTypespec
    ;
unaryTypespec
    : through=primaryTypespec
    | op='^' arg=unaryTypespec
    ;
funBinaryTypespec
    : through=unaryTypespec
    | lt=funBinaryTypespec op='->' rt=unaryTypespec
    ;
binaryTypespec: it=funBinaryTypespec;
