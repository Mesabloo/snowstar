
// Generated from SnowStarParser.g4 by ANTLR 4.7.1

#pragma once


#include "antlr4-runtime.h"




class  SnowStarParser : public antlr4::Parser {
public:
  enum {
    BOOL = 1, CHR = 2, I8 = 3, I16 = 4, I32 = 5, I64 = 6, F32 = 7, F64 = 8, 
    STR = 9, VOID = 10, WITH = 11, RET = 12, EXTERNAL = 13, UNIT = 14, ALIGN_AS = 15, 
    DTYPE = 16, IMPORT = 17, DEC_LITERAL = 18, HEX_LITERAL = 19, BIN_LITERAL = 20, 
    OCT_LITERAL = 21, FLOAT_LITERAL = 22, BOOL_LITERAL = 23, CHAR_LITERAL = 24, 
    STRING_LITERAL = 25, BEGIN_COM = 26, END_COM = 27, INLINE_COM = 28, 
    LPAREN = 29, RPAREN = 30, LBRACE = 31, RBRACE = 32, LBRACK = 33, RBRACK = 34, 
    SEMI = 35, COMMA = 36, DOT = 37, COLON = 38, COLONCOLON = 39, ASSIGN = 40, 
    EQUALS = 41, NEQUALS = 42, GREATER = 43, LOWER = 44, GREATER_EQ = 45, 
    LOWER_EQ = 46, LOGIC_OR = 47, LOGIC_AND = 48, LOGIC_NOT = 49, PLUS = 50, 
    MINUS = 51, STAR = 52, SLASH = 53, BIN_NOT = 54, BIN_AND = 55, BIN_OR = 56, 
    BIN_XOR = 57, WS = 58, COMMENT = 59, LINE_COMMENT = 60, IDENTIFIER = 61
  };

  enum {
    RuleCompilationUnit = 0, RuleDeclarationSeq = 1, RuleVariableDeclaration = 2, 
    RuleVariableName = 3, RuleVariableInitializer = 4, RuleUnitDeclaration = 5, 
    RuleUnitName = 6, RuleBasicBlockDeclaration = 7, RuleDtypeDeclaration = 8, 
    RuleDtypeName = 9, RuleDtypeBlockDeclaration = 10, RuleFunctionDeclaration = 11, 
    RuleFunctionName = 12, RuleFunctionParams = 13, RuleParameterDeclaration = 14, 
    RuleWithDeclaration = 15, RuleWithName = 16, RuleImportDeclaration = 17, 
    RuleImportName = 18, RuleEmptyDeclaration = 19, RuleStatementSeq = 20, 
    RuleExpression = 21, RulePrimaryExpression = 22, RuleTheType = 23, RuleBuiltinTypes = 24, 
    RuleValue = 25
  };

  SnowStarParser(antlr4::TokenStream *input);
  ~SnowStarParser();

  virtual std::string getGrammarFileName() const override;
  virtual const antlr4::atn::ATN& getATN() const override { return _atn; };
  virtual const std::vector<std::string>& getTokenNames() const override { return _tokenNames; }; // deprecated: use vocabulary instead.
  virtual const std::vector<std::string>& getRuleNames() const override;
  virtual antlr4::dfa::Vocabulary& getVocabulary() const override;


  class CompilationUnitContext;
  class DeclarationSeqContext;
  class VariableDeclarationContext;
  class VariableNameContext;
  class VariableInitializerContext;
  class UnitDeclarationContext;
  class UnitNameContext;
  class BasicBlockDeclarationContext;
  class DtypeDeclarationContext;
  class DtypeNameContext;
  class DtypeBlockDeclarationContext;
  class FunctionDeclarationContext;
  class FunctionNameContext;
  class FunctionParamsContext;
  class ParameterDeclarationContext;
  class WithDeclarationContext;
  class WithNameContext;
  class ImportDeclarationContext;
  class ImportNameContext;
  class EmptyDeclarationContext;
  class StatementSeqContext;
  class ExpressionContext;
  class PrimaryExpressionContext;
  class TheTypeContext;
  class BuiltinTypesContext;
  class ValueContext; 

  class  CompilationUnitContext : public antlr4::ParserRuleContext {
  public:
    CompilationUnitContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *EOF();
    std::vector<DeclarationSeqContext *> declarationSeq();
    DeclarationSeqContext* declarationSeq(size_t i);

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  CompilationUnitContext* compilationUnit();

  class  DeclarationSeqContext : public antlr4::ParserRuleContext {
  public:
    DeclarationSeqContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    FunctionDeclarationContext *functionDeclaration();
    VariableDeclarationContext *variableDeclaration();
    UnitDeclarationContext *unitDeclaration();
    DtypeDeclarationContext *dtypeDeclaration();
    WithDeclarationContext *withDeclaration();
    ImportDeclarationContext *importDeclaration();
    EmptyDeclarationContext *emptyDeclaration();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  DeclarationSeqContext* declarationSeq();

  class  VariableDeclarationContext : public antlr4::ParserRuleContext {
  public:
    VariableDeclarationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    TheTypeContext *theType();
    VariableNameContext *variableName();
    antlr4::tree::TerminalNode *SEMI();
    VariableInitializerContext *variableInitializer();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  VariableDeclarationContext* variableDeclaration();

  class  VariableNameContext : public antlr4::ParserRuleContext {
  public:
    VariableNameContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IDENTIFIER();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  VariableNameContext* variableName();

  class  VariableInitializerContext : public antlr4::ParserRuleContext {
  public:
    VariableInitializerContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *ASSIGN();
    ExpressionContext *expression();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  VariableInitializerContext* variableInitializer();

  class  UnitDeclarationContext : public antlr4::ParserRuleContext {
  public:
    UnitDeclarationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *UNIT();
    UnitNameContext *unitName();
    BasicBlockDeclarationContext *basicBlockDeclaration();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  UnitDeclarationContext* unitDeclaration();

  class  UnitNameContext : public antlr4::ParserRuleContext {
  public:
    UnitNameContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IDENTIFIER();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  UnitNameContext* unitName();

  class  BasicBlockDeclarationContext : public antlr4::ParserRuleContext {
  public:
    BasicBlockDeclarationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LBRACE();
    antlr4::tree::TerminalNode *RBRACE();
    std::vector<StatementSeqContext *> statementSeq();
    StatementSeqContext* statementSeq(size_t i);

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  BasicBlockDeclarationContext* basicBlockDeclaration();

  class  DtypeDeclarationContext : public antlr4::ParserRuleContext {
  public:
    DtypeDeclarationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *DTYPE();
    DtypeNameContext *dtypeName();
    DtypeBlockDeclarationContext *dtypeBlockDeclaration();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  DtypeDeclarationContext* dtypeDeclaration();

  class  DtypeNameContext : public antlr4::ParserRuleContext {
  public:
    DtypeNameContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IDENTIFIER();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  DtypeNameContext* dtypeName();

  class  DtypeBlockDeclarationContext : public antlr4::ParserRuleContext {
  public:
    DtypeBlockDeclarationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LBRACE();
    antlr4::tree::TerminalNode *RBRACE();
    std::vector<VariableDeclarationContext *> variableDeclaration();
    VariableDeclarationContext* variableDeclaration(size_t i);

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  DtypeBlockDeclarationContext* dtypeBlockDeclaration();

  class  FunctionDeclarationContext : public antlr4::ParserRuleContext {
  public:
    FunctionDeclarationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    TheTypeContext *theType();
    FunctionNameContext *functionName();
    FunctionParamsContext *functionParams();
    BasicBlockDeclarationContext *basicBlockDeclaration();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  FunctionDeclarationContext* functionDeclaration();

  class  FunctionNameContext : public antlr4::ParserRuleContext {
  public:
    FunctionNameContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IDENTIFIER();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  FunctionNameContext* functionName();

  class  FunctionParamsContext : public antlr4::ParserRuleContext {
  public:
    FunctionParamsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LPAREN();
    antlr4::tree::TerminalNode *RPAREN();
    std::vector<ParameterDeclarationContext *> parameterDeclaration();
    ParameterDeclarationContext* parameterDeclaration(size_t i);
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  FunctionParamsContext* functionParams();

  class  ParameterDeclarationContext : public antlr4::ParserRuleContext {
  public:
    ParameterDeclarationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    TheTypeContext *theType();
    antlr4::tree::TerminalNode *IDENTIFIER();
    antlr4::tree::TerminalNode *ASSIGN();
    ValueContext *value();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ParameterDeclarationContext* parameterDeclaration();

  class  WithDeclarationContext : public antlr4::ParserRuleContext {
  public:
    WithDeclarationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *WITH();
    WithNameContext *withName();
    antlr4::tree::TerminalNode *ASSIGN();
    TheTypeContext *theType();
    antlr4::tree::TerminalNode *SEMI();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  WithDeclarationContext* withDeclaration();

  class  WithNameContext : public antlr4::ParserRuleContext {
  public:
    WithNameContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IDENTIFIER();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  WithNameContext* withName();

  class  ImportDeclarationContext : public antlr4::ParserRuleContext {
  public:
    ImportDeclarationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IMPORT();
    ImportNameContext *importName();
    antlr4::tree::TerminalNode *SEMI();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ImportDeclarationContext* importDeclaration();

  class  ImportNameContext : public antlr4::ParserRuleContext {
  public:
    ImportNameContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IDENTIFIER();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ImportNameContext* importName();

  class  EmptyDeclarationContext : public antlr4::ParserRuleContext {
  public:
    EmptyDeclarationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *SEMI();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  EmptyDeclarationContext* emptyDeclaration();

  class  StatementSeqContext : public antlr4::ParserRuleContext {
  public:
    StatementSeqContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    VariableDeclarationContext *variableDeclaration();
    WithDeclarationContext *withDeclaration();
    ImportDeclarationContext *importDeclaration();
    EmptyDeclarationContext *emptyDeclaration();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  StatementSeqContext* statementSeq();

  class  ExpressionContext : public antlr4::ParserRuleContext {
  public:
    ExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    PrimaryExpressionContext *primaryExpression();
    std::vector<ExpressionContext *> expression();
    ExpressionContext* expression(size_t i);
    antlr4::tree::TerminalNode *PLUS();
    antlr4::tree::TerminalNode *LOGIC_NOT();
    antlr4::tree::TerminalNode *BIN_NOT();
    antlr4::tree::TerminalNode *MINUS();
    antlr4::tree::TerminalNode *LPAREN();
    TheTypeContext *theType();
    antlr4::tree::TerminalNode *RPAREN();
    antlr4::tree::TerminalNode *STAR();
    antlr4::tree::TerminalNode *SLASH();
    antlr4::tree::TerminalNode *GREATER();
    antlr4::tree::TerminalNode *LOWER();
    antlr4::tree::TerminalNode *GREATER_EQ();
    antlr4::tree::TerminalNode *LOWER_EQ();
    antlr4::tree::TerminalNode *EQUALS();
    antlr4::tree::TerminalNode *NEQUALS();
    antlr4::tree::TerminalNode *BIN_XOR();
    antlr4::tree::TerminalNode *BIN_AND();
    antlr4::tree::TerminalNode *BIN_OR();
    antlr4::tree::TerminalNode *LOGIC_AND();
    antlr4::tree::TerminalNode *LOGIC_OR();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ExpressionContext* expression();
  ExpressionContext* expression(int precedence);
  class  PrimaryExpressionContext : public antlr4::ParserRuleContext {
  public:
    PrimaryExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LPAREN();
    ExpressionContext *expression();
    antlr4::tree::TerminalNode *RPAREN();
    antlr4::tree::TerminalNode *IDENTIFIER();
    ValueContext *value();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  PrimaryExpressionContext* primaryExpression();

  class  TheTypeContext : public antlr4::ParserRuleContext {
  public:
    TheTypeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    BuiltinTypesContext *builtinTypes();
    antlr4::tree::TerminalNode *IDENTIFIER();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  TheTypeContext* theType();

  class  BuiltinTypesContext : public antlr4::ParserRuleContext {
  public:
    BuiltinTypesContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *BOOL();
    antlr4::tree::TerminalNode *CHR();
    antlr4::tree::TerminalNode *I8();
    antlr4::tree::TerminalNode *I16();
    antlr4::tree::TerminalNode *I32();
    antlr4::tree::TerminalNode *I64();
    antlr4::tree::TerminalNode *F32();
    antlr4::tree::TerminalNode *F64();
    antlr4::tree::TerminalNode *STR();
    antlr4::tree::TerminalNode *VOID();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  BuiltinTypesContext* builtinTypes();

  class  ValueContext : public antlr4::ParserRuleContext {
  public:
    ValueContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *BOOL_LITERAL();
    antlr4::tree::TerminalNode *CHAR_LITERAL();
    antlr4::tree::TerminalNode *DEC_LITERAL();
    antlr4::tree::TerminalNode *BIN_LITERAL();
    antlr4::tree::TerminalNode *HEX_LITERAL();
    antlr4::tree::TerminalNode *OCT_LITERAL();
    antlr4::tree::TerminalNode *FLOAT_LITERAL();
    antlr4::tree::TerminalNode *STRING_LITERAL();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ValueContext* value();


  virtual bool sempred(antlr4::RuleContext *_localctx, size_t ruleIndex, size_t predicateIndex) override;
  bool expressionSempred(ExpressionContext *_localctx, size_t predicateIndex);

private:
  static std::vector<antlr4::dfa::DFA> _decisionToDFA;
  static antlr4::atn::PredictionContextCache _sharedContextCache;
  static std::vector<std::string> _ruleNames;
  static std::vector<std::string> _tokenNames;

  static std::vector<std::string> _literalNames;
  static std::vector<std::string> _symbolicNames;
  static antlr4::dfa::Vocabulary _vocabulary;
  static antlr4::atn::ATN _atn;
  static std::vector<uint16_t> _serializedATN;


  struct Initializer {
    Initializer();
  };
  static Initializer _init;
};

