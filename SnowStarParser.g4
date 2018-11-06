parser grammar SnowStarParser;

options {
    tokenVocab = SnowStarLexer;
}

// global
compilationUnit: statement+
               //| function
               ;

statement
         :       declare eol=';'?
         |       define eol=';'?
         |       alias eol=';'?;

// variables

expression
          :      (IDENTIFIER | literal | lparen='(' expression ')')
          |      uop=('+' | '-' | '!' | '~') expression?
          |      expression bop=('*' | '/') expression?
          |      expression bop=('+' | '-') expression?
          |      expression bop=('<=' | '>=' | '<' | '>' | '==' | '!=') expression?
          |      expression bop=( '&' | '^' | '|' | '&&' |'||') expression?;

assign
      :          IDENTIFIER eop='='? expression?;

define
      :          (declare | declareNoID) eop='='? expression?;
declare
       :         type IDENTIFIER;
declareNoID
           :     type;

alias
     :           with='with' IDENTIFIER? eop='='? type?;

// primitives

literal
       :         DECIMAL_LITERAL
       |         HEX_LITERAL
       |         BIN_LITERAL
       |         FLOAT_LITERAL
       |         BOOL_LITERAL
       |         CHAR_LITERAL;

type
    :   BOOLEAN
    |   CHAR
    |   INTEGER8
    |   INTEGER16
    |   INTEGER32
    |   INTEGER64
    |   REAL16
    |   REAL32
    |   REAL64
    |   VOID
    |   IDENTIFIER;