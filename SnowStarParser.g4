parser grammar SnowStarParser;

options { tokenVocab=SnowStarLexer; }











// Literals

variableDeclarators:   variableDeclarator (',' variableDeclarator)*;
variableDeclarator:    variableDeclaratorId ('=' variableInitializer)?;
variableDeclaratorId:  IDENTIFIER;
variableInitializer:   expression;

literal:         integerLiteral
       |         FLOAT_LITERAL
       |         CHAR_LITERAL
       |         STRING_LITERAL
       |         BOOL_LITERAL
       |         NIL_LITERAL;

integerLiteral:  DECIMAL_LITERAL
              |  HEX_LITERAL
              |  BIN_LITERAL;

// Blocks / Statements

block:                      '{' blockStatement* '}';
blockStatement:             localVariableDeclaration ';'
              |             statement;
localVariableDeclaration:   typeGeneric variableDeclarators;

statement:                  blockLabel=block
         |                  statementExpression=expression ';';

expression:                 primary
          |                 '(' typeType ')' expression      // cast
          |                 DEF creator
          |                 <assoc=right> expression bop='=' expression;

primary:                    '(' expression ')'
       |                    literal
       |                    IDENTIFIER;

// Miscellaneous

creator:         createdName;
createdName:     IDENTIFIER '->' typeGeneric?
           |     primitiveType;

typeGeneric:     typeType ('<' (typeGeneric (',' typeGeneric)*)* '>')?;
typeList:        typeType (',' typeType)*;
typeType:        primitiveType;

primitiveType:   BOOLEAN
             |   CHAR
             |   INTEGER8
             |   INTEGER16
             |   INTEGER32
             |   INTEGER64
             |   REAL32
             |   REAL64
             |   STRING
             |   VOID;