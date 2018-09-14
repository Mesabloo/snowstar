grammar SnowStar;

program : statement+ ;

statement : declare NewLine?
    | define NewLine? ;
//    | print NewLine? ;

Type : 'int8'
    | 'int16' 
    | 'int32'
    | 'int64' 
    | 'real32'
    | 'real64'
    | 'bool'
    | 'char'
    | 'str'
    | 'void' ;

Integer : [0-9]+ | '0x' [0-9A-Fa-f]* | '0b' [01]* ;
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
    | Identifier
    | cast ;

declare : 'decl' Identifier (',' Identifier)* ':' Type ;
define : declare '=' value (',' value)* ;
// fragment defineObject : LPAR value (',' value)* RPAR ;
// define : declare '=' LPAR? value RPAR? ;
// print : 'print' LPAR value RPAR ;
cast : LPAR Type RPAR LPAR? value RPAR? ;
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