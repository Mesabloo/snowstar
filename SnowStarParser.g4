parser grammar SnowStarParser;

options {
    tokenVocab = SnowStarLexer;
}

/** Entry point/Basic concepts */
compilationUnit
               :             declarationSeq* EOF
               ;


/** Declarations */
declarationSeq
              :              functionDeclaration       // type name (params*) {statements*} 
              |              variableDeclaration       // type name (= value)?
              |              unitDeclaration           // unit name {statements*}
              |              dtypeDeclaration          // dtype name {vars*}
              |              withDeclaration           // with name = type
              |              importDeclaration         // import file
              |              emptyDeclaration          // ;
              ;

variableDeclaration
                   :         theType variableName variableInitializer? SEMI
                   ;

variableName
            :                IDENTIFIER
            ;

variableInitializer
                   :         ASSIGN expression
                   ;

unitDeclaration 
               :             UNIT unitName basicBlockDeclaration
               ;

unitName
        :                    IDENTIFIER
        ;

basicBlockDeclaration
                     :       LBRACE statementSeq* RBRACE
                     ;

dtypeDeclaration
                :            DTYPE dtypeName dtypeBlockDeclaration
                ;

dtypeName
         :                   IDENTIFIER
         ;

dtypeBlockDeclaration
                     :       LBRACE variableDeclaration* RBRACE
                     ;

functionDeclaration
                   :         theType functionName functionParams basicBlockDeclaration
                   ;

functionName
            :                IDENTIFIER
            ;

functionParams
              :              LPAREN (parameterDeclaration (COMMA parameterDeclaration)*)? RPAREN
              ;          

parameterDeclaration
                    :        theType IDENTIFIER (ASSIGN value)?
                    ;

withDeclaration
               :             WITH withName ASSIGN theType SEMI
               ;
            
withName
        :                    IDENTIFIER
        ;

importDeclaration
                 :           IMPORT importName SEMI
                 ;

importName
          :                  IDENTIFIER
          ;

emptyDeclaration
                :            SEMI
                ;


/** Statement */
statementSeq
            :                variableDeclaration         // type name (= value),
            |                withDeclaration             // with name = type
            |                importDeclaration           // import file
            |                emptyDeclaration            // ;
            ;

/** Expressions */
expression
          :                  primaryExpression
          |                  (PLUS | LOGIC_NOT | BIN_NOT | MINUS) expression
          |                  LPAREN theType RPAREN expression
          |                  expression (STAR | SLASH) expression
          |                  expression (PLUS | MINUS) expression
          |                  expression (GREATER | LOWER | GREATER_EQ | LOWER_EQ) expression
          |                  expression (EQUALS | NEQUALS) expression
          |                  expression (BIN_XOR | BIN_AND | BIN_OR) expression
          |                  expression (LOGIC_AND | LOGIC_OR) expression
          ;

primaryExpression
                 :           LPAREN expression RPAREN
                 |           IDENTIFIER
                 |           value
                 ;


/** Types and classes */
theType
       :                     builtinTypes
       |                     IDENTIFIER
       ;

builtinTypes
            :                BOOL
            |                CHAR
            |                INT8
            |                INT16
            |                INT32
            |                INT64
            |                REAL16
            |                REAL32
            |                REAL64
            |                VOID
            ;

value
     :                       BOOL_LITERAL
     |                       CHAR_LITERAL
     |                       DEC_LITERAL
     |                       BIN_LITERAL
     |                       HEX_LITERAL
     |                       OCT_LITERAL
     |                       FLOAT_LITERAL
     ;