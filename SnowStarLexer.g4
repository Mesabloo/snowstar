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

lexer grammar SnowStarLexer;

// Reserved words

BOOL
    :                         'bool'
    ;
CHR
   :                          'chr'
   ;
I8
  :                           'i8'
  ;
UI8
   :                          'ui8'
   ;
I16
   :                          'i16'
   ;
UI16
    :                         'ui16'
    ;
I32
   :                          'i32'
   ;
UI32
    :                         'ui32'
    ;
I64
   :                          'i64'
   ;
UI64
    :                         'ui64'
    ;
F32
   :                          'f32'
   ;
F64
   :                          'f64'
   ;
STR
   :                          'str'
   ;
VOID
    :                         'void'
    ;

WITH
    :                         'with'
    ;
RET
   :                          'return'
   ;
EXTERNAL
        :                     'external'
        ;
UNIT
    :                         'unit'
    ;
ALIGN_AS
        :                     'align'
        ;
DTYPE
     :                        'dtype'
     ;
IMPORT
      :                       'import'
      ;

// Literals

DEC_LITERAL
               :              Digits+
               ;

HEX_LITERAL
           :                  '0' [xX] HexDigits+
           ;

BIN_LITERAL
           :                  '0' [bB] BinDigits+
           ;

OCT_LITERAL
           :                  '0' [cC] OctDigits+
           ;

FLOAT_LITERAL
             :                (Digits+ '.' Digits* | '.' Digits* | Digits+ '.')
             ;

BOOL_LITERAL
            :                 'true'
            |                 'false'
            ;

CHAR_LITERAL
            :                 CharDelimiter (~['\\\r\n] | EscapeSequence) CharDelimiter
            ;

STRING_LITERAL
              :               StringDelimiter (~["\\\r\n] | EscapeSequence)* StringDelimiter
              ;

// Separators

BEGIN_COM
         :                    '(*'
         ;
END_COM
       :                      '*)'
       ;
INLINE_COM
          :                   '//'
          ;
LPAREN
      :                       '('
      ;
RPAREN
      :                       ')'
      ;
LBRACE
      :                       '{'
      ;
RBRACE
      :                       '}'
      ;
LBRACK
      :                       '['
      ;
RBRACK
      :                       ']'
      ;
SEMI
    :                         ';'
    ;
COMMA
     :                        ','
     ;
DOT
   :                          '.'
   ;
COLON
     :                        ':'
     ;
COLONCOLON
          :                   '::'
          ;

// Operators

TO_ARROW
        :                     '=>'
        ;
ASSIGN
      :                       '='
      ;
EQUALS
      :                       '=='
      ;
NEQUALS
       :                      '!='
       ;
GREATER
       :                      '>'
       ;
LOWER
     :                        '<'
     ;
GREATER_EQ
          :                   '>='
          ;
LOWER_EQ
        :                     '<='
        ;
LOGIC_OR
        :                     '||'
        ;
LOGIC_AND
         :                    '&&'
         ;
LOGIC_NOT
         :                    '!'
         ;
PLUS
    :                         '+'
    ;
MINUS
     :                        '-'
     ;
STAR
    :                         '*'
    ;
SLASH
     :                        '/'
     ;
BIN_NOT
       :                      '~'
       ;
BIN_AND
       :                      '&'
       ;
BIN_OR
      :                       '|'
      ;
BIN_XOR
       :                      '^'
       ;

// Whitespaces and comments

WS
  :                           [ \t\r\n\u000C]+ -> channel(HIDDEN)
  ;
COMMENT
       :                      BEGIN_COM .*? END_COM    -> channel(HIDDEN)
       ;
LINE_COMMENT
            :                 INLINE_COM ~[\r\n]*     -> channel(HIDDEN)
            ;

// Identifiers

IDENTIFIER
          :                   Letter LetterOrDigit*
          ;

// Fragments

fragment EscapeSequence
                       :      '\\' [btnfr"'\\]
                       ;
fragment HexDigits
                  :           HexDigit HexDigit*?
                  ;
fragment HexDigit
                 :            [0-9a-fA-F]
                 ;
fragment BinDigits
                  :           [01] [01]*?
                  ;
fragment OctDigits
                  :           [0-7] [0-7]*?
                  ;
fragment Digits
               :              [0-9] [0-9]*?
               ;
fragment LetterOrDigit
                      :       Letter
                      |       [0-9]
                      ;
fragment Letter
               :              [a-zA-Z_]
 //              | ~[\u0000-\u007F\uD800-\uDBFF] // covers all characters above 0x7F which are not a surrogate
 //              | [\uD800-\uDBFF] [\uDC00-\uDFFF] // covers UTF-16 surrogate pairs encodings for U+10000 to U+10FFFF
               ;
fragment CharDelimiter
                      :       '\''
                      ;
fragment StringDelimiter
                        :     '"'
                        ;