
// Generated from SnowStarParser.g4 by ANTLR 4.7.1

#pragma once


#include "antlr4-runtime.h"




class  SnowStarParser : public antlr4::Parser {
public:
  enum {
    BOOLEAN = 1, CHAR = 2, INTEGER8 = 3, INTEGER16 = 4, INTEGER32 = 5, INTEGER64 = 6, 
    REAL16 = 7, REAL32 = 8, REAL64 = 9, VOID = 10, WITH = 11, DECIMAL_LITERAL = 12, 
    HEX_LITERAL = 13, BIN_LITERAL = 14, FLOAT_LITERAL = 15, BOOL_LITERAL = 16, 
    CHAR_LITERAL = 17, STRING_LITERAL = 18, LPAREN = 19, RPAREN = 20, LBRACE = 21, 
    RBRACE = 22, LBRACK = 23, RBRACK = 24, SEMI = 25, COMMA = 26, DOT = 27, 
    INLINE_COM = 28, BEGIN_COM = 29, END_COM = 30, ASSIGN = 31, EQUALS = 32, 
    NEQUALS = 33, GREATER = 34, LOWER = 35, GREATER_EQ = 36, LOWER_EQ = 37, 
    LOGIC_OR = 38, LOGIC_AND = 39, LOGIC_NOT = 40, PLUS = 41, MINUS = 42, 
    STAR = 43, SLASH = 44, PERCENT = 45, BIN_NOT = 46, BIN_AND = 47, BIN_OR = 48, 
    BIN_XOR = 49, WS = 50, COMMENT = 51, LINE_COMMENT = 52, IDENTIFIER = 53
  };

  enum {
    RuleCompilationUnit = 0, RuleStatement = 1, RuleExpression = 2, RuleAssign = 3, 
    RuleDefine = 4, RuleDeclare = 5, RuleDeclareNoID = 6, RuleAlias = 7, 
    RuleLiteral = 8, RuleType = 9
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
  class AssignContext;
  class DefineContext;
  class DeclareContext;
  class DeclareNoIDContext;
  class AliasContext;
  class LiteralContext;
  class TypeContext; 

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
    AliasContext *alias();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  StatementContext* statement();

  class  ExpressionContext : public antlr4::ParserRuleContext {
  public:
    antlr4::Token *lparen = nullptr;;
    antlr4::Token *uop = nullptr;;
    antlr4::Token *bop = nullptr;;
    ExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IDENTIFIER();
    LiteralContext *literal();
    std::vector<ExpressionContext *> expression();
    ExpressionContext* expression(size_t i);

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ExpressionContext* expression();
  ExpressionContext* expression(int precedence);
  class  AssignContext : public antlr4::ParserRuleContext {
  public:
    antlr4::Token *eop = nullptr;;
    AssignContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IDENTIFIER();
    ExpressionContext *expression();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  AssignContext* assign();

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

  class  AliasContext : public antlr4::ParserRuleContext {
  public:
    antlr4::Token *with = nullptr;;
    antlr4::Token *eop = nullptr;;
    AliasContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IDENTIFIER();
    TypeContext *type();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  AliasContext* alias();

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

