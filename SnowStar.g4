grammar SnowStar;

program : statement+ ;

statement : declare NewLine?
    | define NewLine? ;
//    | print NewLine? ;

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
Null : 'nil' ;

Identifier : [a-zA-Z_0-9]+ ;

value : Integer
    | Real
    | Boolean
    | Character
    | String 
    | Null
    | Identifier ;

declare : 'decl' Identifier (',' Identifier)* ':' Type ;
// declare : 'decl' Identifier ':' Type ;
// define : declare '=' val = (defineObject | defineLiteral)+ ;
define : declare '=' value (',' value)* ;
// fragment defineObject : LPAR value (',' value)* RPAR ;
// define : declare '=' LPAR? value RPAR? ;
// print : 'print' LPAR value RPAR ;
cast : LPAR Type RPAR value ;
//Function : '{' NewLine* statement* NewLine* '}' ;
//    | Function ;

WhiteSpace : [ \t]+ -> skip ;
Comment : '%' ~[\r\n]* NewLine? -> skip ;
MultiLine_Comment : '#*' .*? '*#' -> skip ;
NewLine : '\r'? '\n' -> skip ;

LPAR : '(' ;
RPAR : ')' ;
LBCK : '{' ;
RBCK : '}' ;