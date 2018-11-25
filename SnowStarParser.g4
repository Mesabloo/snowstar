/*
 *  Snow* Compiler, a compiler made with ANTLR and LLVM for compiling Snow* source code
 *  Copyright (C) 2018  Mesabloo
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.

 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

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
              |              variableDeclaration       // type name (= value)?;
              |              unitDeclaration           // unit name {statements*}
              |              dtypeDeclaration          // dtype name {vars*}
              |              withDeclaration           // with name = type;
              |              importDeclaration         // import file;
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
                   :         functionHeader TO_ARROW basicBlockDeclaration SEMI
                   ;

functionHeader
              :              theType functionParamsTypes functionName ASSIGN functionParams
              ;

functionParamsTypes
                   :         LPAREN (theType (COMMA theType)*)? RPAREN
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

returnDeclaration
                 :           RET expression? SEMI
                 ;

emptyDeclaration
                :            SEMI
                ;


/** Statement */
statementSeq
            :                variableDeclaration         // type name (= value);
            |                withDeclaration             // with name = type;
            |                importDeclaration           // import file;
            |                returnDeclaration           // return value;
            |                emptyDeclaration            // ;
            ;

/** Expressions */
expression
          :                  primaryExpression
          |                  unary=(PLUS | LOGIC_NOT | BIN_NOT | MINUS) expression
          |                  LPAREN theType RPAREN expression
          |                  expression binary=(STAR | SLASH) expression
          |                  expression binary=(PLUS | MINUS) expression
          |                  expression binary=(GREATER | LOWER | GREATER_EQ | LOWER_EQ) expression
          |                  expression binary=(EQUALS | NEQUALS) expression
          |                  expression binary=(BIN_XOR | BIN_AND | BIN_OR) expression
          |                  expression binary=(LOGIC_AND | LOGIC_OR) expression
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
            |                CHR
            |                I8
            |                UI8
            |                I16
            |                UI16
            |                I32
            |                UI32
            |                I64
            |                UI64
            |                F32
            |                F64
            |                STR
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
     |                       STRING_LITERAL
     ;