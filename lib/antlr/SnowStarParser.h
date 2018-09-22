
// Generated from SnowStarParser.g4 by ANTLR 4.7.1

#pragma once


#include "antlr4-runtime.h"




class  SnowStarParser : public antlr4::Parser {
public:
  enum {
    BOOLEAN = 1, CHAR = 2, DEF = 3, INTEGER8 = 4, INTEGER16 = 5, INTEGER32 = 6, 
    INTEGER64 = 7, REAL32 = 8, REAL64 = 9, STRING = 10, VOID = 11, DECIMAL_LITERAL = 12, 
    HEX_LITERAL = 13, BIN_LITERAL = 14, FLOAT_LITERAL = 15, BOOL_LITERAL = 16, 
    CHAR_LITERAL = 17, STRING_LITERAL = 18, NIL_LITERAL = 19, LPAREN = 20, 
    RPAREN = 21, LBRACE = 22, RBRACE = 23, LBRACK = 24, RBRACK = 25, SEMI = 26, 
    COMMA = 27, DOT = 28, ASSIGN = 29, TYPEOF = 30, LOWER = 31, GREATER = 32, 
    WS = 33, COMMENT = 34, LINE_COMMENT = 35, IDENTIFIER = 36
  };

  enum {
    RuleVariableDeclarators = 0, RuleVariableDeclarator = 1, RuleVariableDeclaratorId = 2, 
    RuleVariableInitializer = 3, RuleLiteral = 4, RuleIntegerLiteral = 5, 
    RuleBlock = 6, RuleBlockStatement = 7, RuleLocalVariableDeclaration = 8, 
    RuleStatement = 9, RuleExpression = 10, RulePrimary = 11, RuleCreator = 12, 
    RuleCreatedName = 13, RuleTypeGeneric = 14, RuleTypeList = 15, RuleTypeType = 16, 
    RulePrimitiveType = 17
  };

  SnowStarParser(antlr4::TokenStream *input);
  ~SnowStarParser();

  virtual std::string getGrammarFileName() const override;
  virtual const antlr4::atn::ATN& getATN() const override { return _atn; };
  virtual const std::vector<std::string>& getTokenNames() const override { return _tokenNames; }; // deprecated: use vocabulary instead.
  virtual const std::vector<std::string>& getRuleNames() const override;
  virtual antlr4::dfa::Vocabulary& getVocabulary() const override;


  class VariableDeclaratorsContext;
  class VariableDeclaratorContext;
  class VariableDeclaratorIdContext;
  class VariableInitializerContext;
  class LiteralContext;
  class IntegerLiteralContext;
  class BlockContext;
  class BlockStatementContext;
  class LocalVariableDeclarationContext;
  class StatementContext;
  class ExpressionContext;
  class PrimaryContext;
  class CreatorContext;
  class CreatedNameContext;
  class TypeGenericContext;
  class TypeListContext;
  class TypeTypeContext;
  class PrimitiveTypeContext; 

  class  VariableDeclaratorsContext : public antlr4::ParserRuleContext {
  public:
    VariableDeclaratorsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<VariableDeclaratorContext *> variableDeclarator();
    VariableDeclaratorContext* variableDeclarator(size_t i);

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  VariableDeclaratorsContext* variableDeclarators();

  class  VariableDeclaratorContext : public antlr4::ParserRuleContext {
  public:
    VariableDeclaratorContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    VariableDeclaratorIdContext *variableDeclaratorId();
    VariableInitializerContext *variableInitializer();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  VariableDeclaratorContext* variableDeclarator();

  class  VariableDeclaratorIdContext : public antlr4::ParserRuleContext {
  public:
    VariableDeclaratorIdContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IDENTIFIER();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  VariableDeclaratorIdContext* variableDeclaratorId();

  class  VariableInitializerContext : public antlr4::ParserRuleContext {
  public:
    VariableInitializerContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ExpressionContext *expression();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  VariableInitializerContext* variableInitializer();

  class  LiteralContext : public antlr4::ParserRuleContext {
  public:
    LiteralContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    IntegerLiteralContext *integerLiteral();
    antlr4::tree::TerminalNode *FLOAT_LITERAL();
    antlr4::tree::TerminalNode *CHAR_LITERAL();
    antlr4::tree::TerminalNode *STRING_LITERAL();
    antlr4::tree::TerminalNode *BOOL_LITERAL();
    antlr4::tree::TerminalNode *NIL_LITERAL();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  LiteralContext* literal();

  class  IntegerLiteralContext : public antlr4::ParserRuleContext {
  public:
    IntegerLiteralContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *DECIMAL_LITERAL();
    antlr4::tree::TerminalNode *HEX_LITERAL();
    antlr4::tree::TerminalNode *BIN_LITERAL();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  IntegerLiteralContext* integerLiteral();

  class  BlockContext : public antlr4::ParserRuleContext {
  public:
    BlockContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<BlockStatementContext *> blockStatement();
    BlockStatementContext* blockStatement(size_t i);

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  BlockContext* block();

  class  BlockStatementContext : public antlr4::ParserRuleContext {
  public:
    BlockStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    LocalVariableDeclarationContext *localVariableDeclaration();
    StatementContext *statement();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  BlockStatementContext* blockStatement();

  class  LocalVariableDeclarationContext : public antlr4::ParserRuleContext {
  public:
    LocalVariableDeclarationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    TypeGenericContext *typeGeneric();
    VariableDeclaratorsContext *variableDeclarators();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  LocalVariableDeclarationContext* localVariableDeclaration();

  class  StatementContext : public antlr4::ParserRuleContext {
  public:
    SnowStarParser::BlockContext *blockLabel = nullptr;;
    SnowStarParser::ExpressionContext *statementExpression = nullptr;;
    StatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    BlockContext *block();
    ExpressionContext *expression();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  StatementContext* statement();

  class  ExpressionContext : public antlr4::ParserRuleContext {
  public:
    antlr4::Token *bop = nullptr;;
    ExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    PrimaryContext *primary();
    TypeTypeContext *typeType();
    std::vector<ExpressionContext *> expression();
    ExpressionContext* expression(size_t i);
    antlr4::tree::TerminalNode *DEF();
    CreatorContext *creator();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ExpressionContext* expression();
  ExpressionContext* expression(int precedence);
  class  PrimaryContext : public antlr4::ParserRuleContext {
  public:
    PrimaryContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ExpressionContext *expression();
    LiteralContext *literal();
    antlr4::tree::TerminalNode *IDENTIFIER();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  PrimaryContext* primary();

  class  CreatorContext : public antlr4::ParserRuleContext {
  public:
    CreatorContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    CreatedNameContext *createdName();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  CreatorContext* creator();

  class  CreatedNameContext : public antlr4::ParserRuleContext {
  public:
    CreatedNameContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IDENTIFIER();
    TypeGenericContext *typeGeneric();
    PrimitiveTypeContext *primitiveType();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  CreatedNameContext* createdName();

  class  TypeGenericContext : public antlr4::ParserRuleContext {
  public:
    TypeGenericContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    TypeTypeContext *typeType();
    std::vector<TypeGenericContext *> typeGeneric();
    TypeGenericContext* typeGeneric(size_t i);

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  TypeGenericContext* typeGeneric();

  class  TypeListContext : public antlr4::ParserRuleContext {
  public:
    TypeListContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<TypeTypeContext *> typeType();
    TypeTypeContext* typeType(size_t i);

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  TypeListContext* typeList();

  class  TypeTypeContext : public antlr4::ParserRuleContext {
  public:
    TypeTypeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    PrimitiveTypeContext *primitiveType();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  TypeTypeContext* typeType();

  class  PrimitiveTypeContext : public antlr4::ParserRuleContext {
  public:
    PrimitiveTypeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *BOOLEAN();
    antlr4::tree::TerminalNode *CHAR();
    antlr4::tree::TerminalNode *INTEGER8();
    antlr4::tree::TerminalNode *INTEGER16();
    antlr4::tree::TerminalNode *INTEGER32();
    antlr4::tree::TerminalNode *INTEGER64();
    antlr4::tree::TerminalNode *REAL32();
    antlr4::tree::TerminalNode *REAL64();
    antlr4::tree::TerminalNode *STRING();
    antlr4::tree::TerminalNode *VOID();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  PrimitiveTypeContext* primitiveType();


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

