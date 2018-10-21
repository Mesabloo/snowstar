
// Generated from SnowStarParser.g4 by ANTLR 4.7.1

#pragma once


#include "antlr4-runtime.h"




class  SnowStarParser : public antlr4::Parser {
public:
  enum {
    BOOLEAN = 1, CHAR = 2, INTEGER8 = 3, INTEGER16 = 4, INTEGER32 = 5, INTEGER64 = 6, 
    REAL16 = 7, REAL32 = 8, REAL64 = 9, VOID = 10, DECIMAL_LITERAL = 11, 
    HEX_LITERAL = 12, BIN_LITERAL = 13, FLOAT_LITERAL = 14, BOOL_LITERAL = 15, 
    CHAR_LITERAL = 16, STRING_LITERAL = 17, NIL_LITERAL = 18, LPAREN = 19, 
    RPAREN = 20, LBRACE = 21, RBRACE = 22, LBRACK = 23, RBRACK = 24, SEMI = 25, 
    COMMA = 26, DOT = 27, ASSIGN = 28, WS = 29, COMMENT = 30, LINE_COMMENT = 31, 
    IDENTIFIER = 32
  };

  enum {
    RuleCompilationUnit = 0, RuleStatement = 1, RuleExpression = 2, RuleDefine = 3, 
    RuleDeclare = 4, RuleDeclareNoID = 5, RuleLiteral = 6, RuleType = 7, 
    RuleError = 8
  };

  SnowStarParser(antlr4::TokenStream *input);
  ~SnowStarParser();

  virtual std::string getGrammarFileName() const override;
  virtual const antlr4::atn::ATN& getATN() const override { return _atn; };
  virtual const std::vector<std::string>& getTokenNames() const override { return _tokenNames; }; // deprecated: use vocabulary instead.
  virtual const std::vector<std::string>& getRuleNames() const override;
  virtual antlr4::dfa::Vocabulary& getVocabulary() const override;


  class CompilationUnitContext;
  class StatementContext;
  class ExpressionContext;
  class DefineContext;
  class DeclareContext;
  class DeclareNoIDContext;
  class LiteralContext;
  class TypeContext;
  class ErrorContext; 

  class  CompilationUnitContext : public antlr4::ParserRuleContext {
  public:
    CompilationUnitContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<StatementContext *> statement();
    StatementContext* statement(size_t i);

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  CompilationUnitContext* compilationUnit();

  class  StatementContext : public antlr4::ParserRuleContext {
  public:
    antlr4::Token *eol = nullptr;;
    StatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    DeclareContext *declare();
    DefineContext *define();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  StatementContext* statement();

  class  ExpressionContext : public antlr4::ParserRuleContext {
  public:
    ExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IDENTIFIER();
    LiteralContext *literal();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ExpressionContext* expression();

  class  DefineContext : public antlr4::ParserRuleContext {
  public:
    antlr4::Token *eop = nullptr;;
    DefineContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    DeclareContext *declare();
    DeclareNoIDContext *declareNoID();
    ExpressionContext *expression();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  DefineContext* define();

  class  DeclareContext : public antlr4::ParserRuleContext {
  public:
    DeclareContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    TypeContext *type();
    antlr4::tree::TerminalNode *IDENTIFIER();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  DeclareContext* declare();

  class  DeclareNoIDContext : public antlr4::ParserRuleContext {
  public:
    DeclareNoIDContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    TypeContext *type();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  DeclareNoIDContext* declareNoID();

  class  LiteralContext : public antlr4::ParserRuleContext {
  public:
    LiteralContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *DECIMAL_LITERAL();
    antlr4::tree::TerminalNode *HEX_LITERAL();
    antlr4::tree::TerminalNode *BIN_LITERAL();
    antlr4::tree::TerminalNode *FLOAT_LITERAL();
    antlr4::tree::TerminalNode *BOOL_LITERAL();
    antlr4::tree::TerminalNode *CHAR_LITERAL();
    antlr4::tree::TerminalNode *NIL_LITERAL();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  LiteralContext* literal();

  class  TypeContext : public antlr4::ParserRuleContext {
  public:
    TypeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *BOOLEAN();
    antlr4::tree::TerminalNode *CHAR();
    antlr4::tree::TerminalNode *INTEGER8();
    antlr4::tree::TerminalNode *INTEGER16();
    antlr4::tree::TerminalNode *INTEGER32();
    antlr4::tree::TerminalNode *INTEGER64();
    antlr4::tree::TerminalNode *REAL16();
    antlr4::tree::TerminalNode *REAL32();
    antlr4::tree::TerminalNode *REAL64();
    antlr4::tree::TerminalNode *VOID();
    antlr4::tree::TerminalNode *IDENTIFIER();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  TypeContext* type();

  class  ErrorContext : public antlr4::ParserRuleContext {
  public:
    ErrorContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ErrorContext* error();


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

