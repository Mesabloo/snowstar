lexer grammar SnowStarLexer;

// Reserved words

BOOLEAN:    'bool';
CHAR:       'char';
DEF:        'def';
INTEGER8:   'int8';
INTEGER16:  'int16';
INTEGER32:  'int32';
INTEGER64:  'int64';
REAL32:     'real32';
REAL64:     'real64';
STRING:     'string';
VOID:       'void';

// Literals

DECIMAL_LITERAL:   Digits+;
HEX_LITERAL:       '0' [xX] HexDigits+;
BIN_LITERAL:       '0' [bB] BinDigits+;

FLOAT_LITERAL:     (Digits+ '.' Digits* | '.' Digits*);

BOOL_LITERAL:      'true'
            |      'false';

CHAR_LITERAL:      '`' (~[`\\\r\n] | EscapeSequence) '`';

STRING_LITERAL:    '"' (~["\\\r\n] | EscapeSequence)* '"';

NIL_LITERAL:       'nil';

// Separators

LPAREN: '(';
RPAREN: ')';
LBRACE: '{';
RBRACE: '}';
LBRACK: '[';
RBRACK: ']';
SEMI:   ';';
COMMA:  ',';
DOT:    '.';

// Operators

ASSIGN:    '=';
TYPEOF:    '->';
LOWER:     '<';
GREATER:   '>';

// Whitespaces and comments

WS:             [ \t\r\n\u000C]+ -> channel(HIDDEN);
COMMENT:        '#*' .*? '*#'    -> channel(HIDDEN);
LINE_COMMENT:   '#' ~[\r\n]*     -> channel(HIDDEN);

// Identifiers

IDENTIFIER: Letter LetterOrDigit*;

// Fragments

fragment EscapeSequence: '\\' [btnfr"`\\];
fragment HexDigits:      HexDigit HexDigit*?;
fragment HexDigit:       [0-9a-fA-F];
fragment BinDigits:      [01] [01]*?;
fragment Digits:         [0-9] [0-9]*?;
fragment LetterOrDigit:  Letter
                      |  [0-9];
fragment Letter:         [a-zA-Z_];
//               | ~[\u0000-\u007F\uD800-\uDBFF] // covers all characters above 0x7F which are not a surrogate
//               | [\uD800-\uDBFF] [\uDC00-\uDFFF] // covers UTF-16 surrogate pairs encodings for U+10000 to U+10FFFF