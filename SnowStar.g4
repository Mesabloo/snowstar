grammar SnowStar;

program : statement+ ;

statement : declare NewLine?
    | define NewLine?
    | print NewLine? ;

Type : 'integer8'
    | 'integer16' 
    | 'integer32'
    | 'integer64' 
    | 'real32'
    | 'real64'
    | 'boolean'
    | 'character'
    | 'string'
    | 'void' ;

Integer : [0-9]+ ;
Real : [0-9]+ '.' [0-9]* ;
Boolean : 'true'
    | 'false' ;
Character : '`' ~[`\\\r\n] '`' ;
String : '"' ~["\\\r\n]* '"' ;

Identifier : [a-zA-Z_]+ ;

value : Integer
    | Real
    | Boolean
    | Character
    | String 
    | Identifier ;

declare : 'decl' Identifier ':' Type ;
define : declare '=' LPAR? value RPAR? ;
print: 'print' LPAR value RPAR;
//Function : '{' NewLine* statement* NewLine* '}' ;
//    | Function ;

WhiteSpace : [ \t]+ -> skip ;
Comment : '%' ~[\r\n]* '\r'? '\n' -> skip ;
MultiLine_Comment : '#*' .*? '*#' -> skip ;
NewLine : '\r'? '\n' -> skip ;

LPAR : '(' ;
RPAR : ')' ;
LBCK : '{' ;
RBCK : '}' ;