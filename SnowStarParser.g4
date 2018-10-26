parser grammar SnowStarParser;

options {
    tokenVocab = SnowStarLexer;
}

// global
compilationUnit: statement+;

statement
// options { paraphrase = 'a statement'; }
         :       declare eol=';'?
         |       define eol=';'?
         |       alias eol=';'?;

expression
// options { paraphrase = 'an expression'; }
          :      IDENTIFIER
          |      literal;

// variables
assign
// options { paraphrase = 'an assignation'; }
      :          IDENTIFIER eop='='? expression?;

define
// options { paraphrase = 'a definition'; }
      :          (declare|declareNoID) eop='='? expression?;
declare
// options { paraphrase = 'a declaration'; }
       :         type IDENTIFIER;
declareNoID:     type;

alias:           with='with' IDENTIFIER? eop='='? type?;

// primitives

literal
// options { paraphrase = 'a literal'; }
       :         DECIMAL_LITERAL
       |         HEX_LITERAL
       |         BIN_LITERAL
       |         FLOAT_LITERAL
       |         BOOL_LITERAL
       |         CHAR_LITERAL
       |         NIL_LITERAL;

type
// options { paraphrase = 'a type'; }
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

error: .;