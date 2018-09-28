parser grammar SnowStarParser;

options { tokenVocab=SnowStarLexer; }

// global
compilationUnit: statement+;

statement:       declare ';'
         |       define ';';

expression:      IDENTIFIER
          |      literal;

// variables
declare:   primitiveType IDENTIFIER;
define:    declare '=' (expression);


// primitives

literal:         DECIMAL_LITERAL
       |         HEX_LITERAL
       |         BIN_LITERAL
       |         FLOAT_LITERAL
       |         BOOL_LITERAL
       |         CHAR_LITERAL
       |         NIL_LITERAL;

primitiveType:   BOOLEAN
             |   CHAR
             |   INTEGER8
             |   INTEGER16
             |   INTEGER32
             |   INTEGER64
             |   REAL32
             |   REAL64
             |   VOID;