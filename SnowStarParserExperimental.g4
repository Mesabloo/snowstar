parser grammar SnowStarParser;

options {
    tokenVocab = SnowStarLexer;
}


/** Entry point/Basic concepts */
compilationUnit
               :             declarationSeq? EOF
               ;


/** Expressions */
primaryExpression
                 :           literal
                 |           LPAREN expression RPAREN
                 |           idExpression
                 ;
idExpression
            :                IDENTIFIER
            ;
expressionList
              :              initializerList
              ;
unaryExpression
               :             unaryOperator expression
               ;
unaryOperator
             :               '|'
             |               '+'
             |               '!'
             |               '~'
             |               '-'
             ;
castExpression
              :              unaryExpression
              |              LPAREN thetypeid RPAREN castExpression
              ;
multiplicativeExpression
                        :    castExpression
                        |    multiplicativeExpression STAR castExpression
                        |    multiplicativeExpression SLASH castExpression
                        ;
additiveExpression
                  :          multiplicativeExpression
                  |          additiveExpression PLUS multiplicativeExpression
                  |          additiveExpression MINUS multiplicativeExpression
                  ;
relationalExpression
                    :        additiveExpression
                    |        relationalExpression LOWER additiveExpression
                    |        relationalExpression GREATER additiveExpression
                    |        relationalExpression LOWER_EQ additiveExpression
                    |        relationalExpression GREATER_EQ additiveExpression
                    ;
equalityExpression
                  :          relationalExpression
                  |          equalityExpression EQUALS relationalExpression
                  |          equalityExpression NEQUALS relationalExpression
                  ;
andExpression
             :               equalityExpression
             |               andExpression BIN_AND equalityExpression
             ;
exclusiveOrExpression
                     :       andExpression
                     |       exclusiveOrExpression BIN_XOR andExpression
                     ;
inclusiveOrExpression
                     :       exclusiveOrExpression
                     |       inclusiveOrExpression BIN_OR exclusiveOrExpression
                     ;
logicalAndExpression
                    :        inclusiveOrExpression
                    |        logicalAndExpression LOGIC_AND exclusiveOrExpression
                    ;
logicalOrExpression
                   :         logicalAndExpression
                   |         logicalOrExpression LOGIC_OR logicalAndExpression
                   ;
assignementExpression
                     :       logicalOrExpression
                     |       logicalOrExpression assignementOperator initializerClause
                     ;
assignementOperator
                   :         ASSIGN
                   ;

expression
          :                  assignementExpression
          |                  expression COMMA assignementExpression
          ;


/** Statements */
statement 
         :                   attributeSpecifierSeq? expressionStatement
         |                   attributeSpecifierSeq? compoundStatement
         |                   declarationStatement
         ;
expressionStatement
                   :         expression? SEMI
                   ;
compoundStatement
                 :           LBRACE statementSeq? RBRACE
                 ;
statementSeq
            :                statement
            |                statementSeq statement
            ;   
declarationStatement
                    :        blockDeclaration
                    ;


/** Declarations */
declarationSeq
              :              declaration
              |              declarationSeq declaration
              ;
declaration
           :                 blockDeclaration
           |                 functionDefinition
           |                 namespaceDefinition
           |                 emptyDeclaration
           |                 attributeDeclaration
           ;
blockDeclaration
                :            simpleDeclaration
                |            aliasDeclaration
                ;
aliasDeclaration
                :            WITH IDENTIFIER attributeSpecifierSeq? ASSIGN thetypeid SEMI
                ;
simpleDeclaration
                 :           declSpecifierSeq? initDeclaratorList? SEMI
                 |           attributeSpecifierSeq declSpecifierSeq? initDeclaratorList SEMI
                 ;
emptyDeclaration
                :            SEMI
                ;
attributeDeclaration
                    :        attributeSpecifierSeq SEMI
                    ;
declSpecifier
             :               typeSpecifier
             |               functionSpecifier
             ;
declSpecifierSeq
                :            declSpecifier attributeSpecifierSeq?
                |            declSpecifier declSpecifierSeq
                ;
functionSpecifier
                 :           EXTERNAL
                 ;
typeSpecifier
             :               trailingTypeSpecifier
             ;
trailingTypeSpecifier
                     :       simpleTypeSpecifier
                     ;
typeSpecifierSeq:            typeSpecifier attributeSpecifierSeq?
	            |            typeSpecifier typeSpecifierSeq
                ;

trailingTypeSpecifierSeq:    trailingTypeSpecifier attributeSpecifierSeq?
	                    |    trailingTypeSpecifier trailingTypeSpecifierSeq
                        ;
simpleTypeSpecifier
                   :         CHAR
                   |         BOOL
                   |         INT8
                   |         INT16
                   |         INT32
                   |         INT64
                   |         REAL16
                   |         REAL32
                   |         REAL64
                   |         VOID
                   ;
namespaceName
             :               originalNamespaceName
             |               namespaceAlias
             ;
originalNamespaceName
                     :       IDENTIFIER
                     ;
namespaceDefinition
                   :         namedNamespaceDefinition
                   |         unnamedNamespaceDefinition
                   ;
namedNamespaceDefinition
                        :    originalNamespaceDefinition
                        |    extensionNamespaceDefinition
                        ;
originalNamespaceDefinition
                           : UNIT IDENTIFIER LBRACE namespaceBody RBRACE
                           ;
extensionNamespaceDefinition
                            :UNIT originalNamespaceName LBRACE namespaceBody RBRACE
                            ;
unnamedNamespaceDefinition
                          :  UNIT LBRACE namespaceBody RBRACE
                          ;
namespaceBody
             :               declarationSeq?
             ;
namespaceAlias
              :              IDENTIFIER
              ;
namespaceAliasDefinition
                        :    UNIT IDENTIFIER ASSIGN qualifiedNamespaceSpecifier SEMI
                        ;
qualifiedNamespaceSpecifier
                           : namespaceName
                           ;
attributeSpecifierSeq
                     :       attributeSpecifier
                     |       attributeSpecifierSeq attributeSpecifier
                     ;
attributeSpecifier
                  :          LBRACK LBRACK attributeList RBRACK RBRACK
                  |          alignmentSpecifier
                  ;
alignmentSpecifier
                  :          ALIGN_AS LPAREN thetypeid RPAREN
                  ;
attributeList
             :               attribute?
             |               attributeList COMMA attribute?
             ;
attribute
         :                   attributeToken attributeArgumentClause?
         ;
attributeToken
              :              IDENTIFIER
              ;
attributeArgumentClause
                       :     LPAREN balancedTokenSeq RPAREN
                       ;
balancedTokenSeq
                :            balancedToken?
                |            balancedTokenSeq balancedToken
                ;
balancedToken
             :               LPAREN balancedTokenSeq RPAREN
             |               LBRACK balancedTokenSeq RBRACK
             |               LBRACE balancedTokenSeq RBRACE
             ;

/** Declarators */
initDeclaratorList
                  :          initDeclarator
                  |          initDeclaratorList COMMA initDeclarator
                  ;
initDeclarator
              :              declarator initializer?
              ;
declarator
          :                  norefDeclarator parametersAndQualifiers trailingReturnType
          ;
norefDeclarator
               :             declaratorId attributeSpecifierSeq?
               |             norefDeclarator parametersAndQualifiers
               |             norefDeclarator LBRACK RBRACK attributeSpecifierSeq?
               ;
parametersAndQualifiers
                       :     LPAREN parameterDeclarationClause RPAREN refQualifier? attributeSpecifierSeq?
                       ;
trailingReturnType
                  :          COLONCOLON trailingTypeSpecifierSeq
                  ;
refQualifier
            :                BIN_AND
            ;
declaratorId
            :                idExpression
            ;
thetypeid
         :                   typeSpecifierSeq
         ;
parameterDeclarationClause
                          :  parameterDeclaration
                          |  parameterDeclarationList
                          ;
parameterDeclarationList
                        :    parameterDeclaration
                        |    parameterDeclarationList COMMA parameterDeclaration
                        ;
parameterDeclaration
                    :        attributeSpecifierSeq? declSpecifierSeq declarator
                    |        attributeSpecifierSeq? declSpecifierSeq declarator ASSIGN initializerClause
                    ;
functionDefinition
                  :          attributeSpecifierSeq? declSpecifierSeq? declarator functionBody
                  ;
functionBody
            :                ctorInitializer? compoundStatement
            ;
initializer
           :                 braceOrEqualInitializer
           |                 LPAREN expressionList RPAREN
           ;
braceOrEqualInitializer
                       :     ASSIGN initializerClause
                       |     bracedInitList
                       ;
initializerClause
                 :           assignementExpression
                 |           bracedInitList
                 ;
initializerList
               :             initializerClause
               |             initializerList COMMA initializerClause
               ;
bracedInitList
              :              LBRACE initializerList COMMA? RBRACE
              |              LBRACE RBRACE
              ;


/** Types */
className
        :                    IDENTIFIER
        ;
classSpecifier
              :              classHead LBRACE memberSpecification? RBRACE
              ;
classHead
         :                   classKey attributeSpecifierSeq? classHeadName
         |                   classKey attributeSpecifierSeq?
         ;
classHeadName
             :               className
             ;
classKey
        :                    DTYPE
        ;
memberSpecification
                   :         memberDeclaration memberSpecification?
                   ;
memberDeclaration
                 :           attributeSpecifierSeq? declSpecifierSeq? memberDeclaratorList? SEMI
                 |           aliasDeclaration
                 |           emptyDeclaration
                 ;
memberDeclaratorList
                    :        memberDeclarator
                    |        memberDeclaratorList COMMA memberDeclarator
                    ;
memberDeclarator
                :            declarator braceOrEqualInitializer?
                ;


/** Special member functions */
ctorInitializer
               :             COLON memInitializerList
               ;
memInitializerList
                  :          memInitializer
                  |          memInitializer COMMA memInitializerList
                  ;
memInitializer
              :              memInitializerId LPAREN expressionList? RPAREN
              |              memInitializerId bracedInitList
              ;
memInitializerId
                :            IDENTIFIER
                ;


/** Special parser rules */
literal
       :                     BOOL_LITERAL
       |                     CHAR_LITERAL
       |                     DECIMAL_LITERAL
       |                     BIN_LITERAL
       |                     HEX_LITERAL
       |                     FLOAT_LITERAL;










































/*

// types:


type
    :      simpleType
    |      aliasType
    ;

simpleType
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
          ;

































function
        :          type IDENTIFIER '(' ')' block
        |          error
        ;

block
     :             '{' statement* '}'
     ;

topLevelStatement
                 : alias eol=';'?
                 ;

statement
         :         (define eol=';'? | declare eol=';'?)
         |         alias eol=';'?
         |         ret eol=';'?
         |         eol=';'
         |         error
         ;

// variables

expression
          :        (IDENTIFIER | literal | lparen='(' expression ')')
          |        uop=('+' | '-' | '!' | '~') expression
          |        expression bop=('*' | '/') expression
          |        expression bop=('+' | '-') expression
          |        expression bop=('<=' | '>=' | '<' | '>' | '==' | '!=') expression
          |        expression bop=( '&' | '^' | '|' | '&&' |'||') expression
          ;

assign
      :            IDENTIFIER eop='=' expression
      ;

define
      :            declare eop='=' expression
      ;
declare
       :           type IDENTIFIER
       ;

alias
     :             WITH IDENTIFIER eop='=' type
     ;

ret
   :               RET expression;


// primitives




error
     :        err=~WS; */