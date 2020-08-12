grammar Lang;

options {
    language='Python3';
}

fragment L: [a-zA-Z_];
fragment D: [0-9];
fragment X: [0-9a-fA-F];
fragment SP: 'f' ;
fragment DC: ~('"' |'\\'|'\r'|'\n') | '\'';
fragment SC: ~('\''|'\\'|'\r'|'\n') | '"';

ID: L (L|D)* ;
DINT: D (D|'_')* ;
XINT: ('0x'|'0X') (X|'_')+ ;
FLOAT: DINT ('.' (D|'_')*)? ([eE] (D|'_')+)? ;
DQSTRING: SP? '"'  DC*  '"';
SQSTRING: SP? '\'' SC* '\'';

IGNORED: (WHITESPACE | LINE_COMMENT) -> skip;
fragment WHITESPACE: (' '|'\t'|'\n'|'\r');
fragment LINE_COMMENT: '#' ~[\r\n\f]*;

sourceFile: importHeader? exportHeader? sourceBody EOF;
importHeader: 'import' '{' its+=vField (',' its+=vField)* '}' ';' ;
exportHeader: 'export' '{' its+=vField (',' its+=vField)* '}' ';' ;
sourceBody: (defn_its+=fileStmt ';')*;

fileStmt
    : lhs=ID args=fnArgs ('=' rhs=expr)?        #bindFunStmt
    | lhs=ID             ('=' rhs=expr)         #bindValStmt
    | lhs=ID args=tsArgs ('=' rhs=typespec)     #bindTypespecStmt
    ;
stmt: through=fileStmt      #throughStmt
    | 'do' rhs=expr         #dropStmt
    ;

expr: through=matchExpr;
primaryExpr
    : ID                                                            #idExpr
    | 'operator' '(' op=anyOp ',' arity=DINT ')'                    #opExpr
    | DINT                                                          #decIntExpr
    | XINT                                                          #hexIntExpr
    | FLOAT                                                         #floatExpr
    | SQSTRING                                                      #sqStringExpr
    | DQSTRING                                                      #dqStringExpr
    | '(' paren_its=exprList? ')'                                   #parenExpr
    | '{' tuple_its=vFieldList '}'                                  #tupleExpr
    | '[' list_its=exprList? ']'                                    #listExpr
    | '{' (prefix_its+=stmt ';')* (result=expr) '}'                 #chainExpr
    | 'if' cond=expr 'then' if_true=expr ('else' if_false=expr)?    #iteExpr
    ;
postfixExpr
    : through=primaryExpr                                           #throughPostfixExpr
    | prefix=postfixExpr '.' suffix=ID                              #dotNameExpr
    | prefix=postfixExpr '.' suffix=DINT                            #dotIndexExpr
    | lhs=postfixExpr '<' args=typespecList '>'                     #tCallExpr
    | lhs=postfixExpr '(' args=exprList? ')'                        #vCallExpr
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

lambdaExpr: through=binaryExpr | lambdaArm ;
matchExpr: through=lambdaExpr | 'match' args=lambdaExpr '{' body=matchBody '}' ;
matchBody: (arms+=lambdaArm ';')* ;
lambdaArm: args=fnArgs '->' rhs=binaryExpr ;


binaryMulOp: '*' | '/' | '%';
binaryAddOp: '+' | '-';
binaryRelOp: '<' | '>' | '<=' | '>=';
binaryEqOp: '==' | '!=';
binaryAndOp: '&&';
binaryOrOp: '||';
binaryOp: binaryMulOp | binaryAddOp | binaryRelOp | binaryEqOp | binaryAndOp | binaryOrOp;
anyOp: unaryOp | binaryOp;
exprList: args+=expr (',' args+=expr)* ;

typespec: through=binaryTypespec;
primaryTypespec
    : ID                    #idTypespec
    | '(' it=typespec ')'   #parenTypespec
    | '[' tFieldList? ']'   #enumTypespec
    | '{' tFieldList? '}'   #structTypespec
    ;
postfixTypespec
    : through=primaryTypespec
    | lhs=postfixTypespec '<' tArgs=typespecList '>'
    | lhs=postfixTypespec '(' vArgs=exprList ')'
    ;
unaryTypespec
    : through=postfixTypespec
    | op='^' arg=unaryTypespec
    ;
funBinaryTypespec
    : through=unaryTypespec
    | lt=funBinaryTypespec op='->' rt=unaryTypespec
    ;
binaryTypespec: it=funBinaryTypespec;

vField: lhs=ID ':' val=expr ;
tField: lhs=ID (':' ts=typespec)? ;
vFieldList: its+=vField (',' its+=vField)* ;
tFieldList: its+=tField (',' its+=tField)* ;
typespecList: its+=typespec (',' its+=typespec)* ;

tsArgs: ('<' tArgs=tFieldList '>') ;
fnArgs: tsArgs? ('(' vArgs=tFieldList? ')' | singleVArg=tField) ;
