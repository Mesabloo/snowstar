
// Generated from SnowStarParser.g4 by ANTLR 4.7.1


#include "SnowStarParserVisitor.h"

#include "SnowStarParser.h"


using namespace antlrcpp;
using namespace antlr4;

SnowStarParser::SnowStarParser(TokenStream *input) : Parser(input) {
  _interpreter = new atn::ParserATNSimulator(this, _atn, _decisionToDFA, _sharedContextCache);
}

SnowStarParser::~SnowStarParser() {
  delete _interpreter;
}

std::string SnowStarParser::getGrammarFileName() const {
  return "SnowStarParser.g4";
}

const std::vector<std::string>& SnowStarParser::getRuleNames() const {
  return _ruleNames;
}

dfa::Vocabulary& SnowStarParser::getVocabulary() const {
  return _vocabulary;
}


//----------------- VariableDeclaratorsContext ------------------------------------------------------------------

SnowStarParser::VariableDeclaratorsContext::VariableDeclaratorsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<SnowStarParser::VariableDeclaratorContext *> SnowStarParser::VariableDeclaratorsContext::variableDeclarator() {
  return getRuleContexts<SnowStarParser::VariableDeclaratorContext>();
}

SnowStarParser::VariableDeclaratorContext* SnowStarParser::VariableDeclaratorsContext::variableDeclarator(size_t i) {
  return getRuleContext<SnowStarParser::VariableDeclaratorContext>(i);
}


size_t SnowStarParser::VariableDeclaratorsContext::getRuleIndex() const {
  return SnowStarParser::RuleVariableDeclarators;
}

antlrcpp::Any SnowStarParser::VariableDeclaratorsContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SnowStarParserVisitor*>(visitor))
    return parserVisitor->visitVariableDeclarators(this);
  else
    return visitor->visitChildren(this);
}

SnowStarParser::VariableDeclaratorsContext* SnowStarParser::variableDeclarators() {
  VariableDeclaratorsContext *_localctx = _tracker.createInstance<VariableDeclaratorsContext>(_ctx, getState());
  enterRule(_localctx, 0, SnowStarParser::RuleVariableDeclarators);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(36);
    variableDeclarator();
    setState(41);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == SnowStarParser::COMMA) {
      setState(37);
      match(SnowStarParser::COMMA);
      setState(38);
      variableDeclarator();
      setState(43);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- VariableDeclaratorContext ------------------------------------------------------------------

SnowStarParser::VariableDeclaratorContext::VariableDeclaratorContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

SnowStarParser::VariableDeclaratorIdContext* SnowStarParser::VariableDeclaratorContext::variableDeclaratorId() {
  return getRuleContext<SnowStarParser::VariableDeclaratorIdContext>(0);
}

SnowStarParser::VariableInitializerContext* SnowStarParser::VariableDeclaratorContext::variableInitializer() {
  return getRuleContext<SnowStarParser::VariableInitializerContext>(0);
}


size_t SnowStarParser::VariableDeclaratorContext::getRuleIndex() const {
  return SnowStarParser::RuleVariableDeclarator;
}

antlrcpp::Any SnowStarParser::VariableDeclaratorContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SnowStarParserVisitor*>(visitor))
    return parserVisitor->visitVariableDeclarator(this);
  else
    return visitor->visitChildren(this);
}

SnowStarParser::VariableDeclaratorContext* SnowStarParser::variableDeclarator() {
  VariableDeclaratorContext *_localctx = _tracker.createInstance<VariableDeclaratorContext>(_ctx, getState());
  enterRule(_localctx, 2, SnowStarParser::RuleVariableDeclarator);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(44);
    variableDeclaratorId();
    setState(47);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == SnowStarParser::ASSIGN) {
      setState(45);
      match(SnowStarParser::ASSIGN);
      setState(46);
      variableInitializer();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- VariableDeclaratorIdContext ------------------------------------------------------------------

SnowStarParser::VariableDeclaratorIdContext::VariableDeclaratorIdContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* SnowStarParser::VariableDeclaratorIdContext::IDENTIFIER() {
  return getToken(SnowStarParser::IDENTIFIER, 0);
}


size_t SnowStarParser::VariableDeclaratorIdContext::getRuleIndex() const {
  return SnowStarParser::RuleVariableDeclaratorId;
}

antlrcpp::Any SnowStarParser::VariableDeclaratorIdContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SnowStarParserVisitor*>(visitor))
    return parserVisitor->visitVariableDeclaratorId(this);
  else
    return visitor->visitChildren(this);
}

SnowStarParser::VariableDeclaratorIdContext* SnowStarParser::variableDeclaratorId() {
  VariableDeclaratorIdContext *_localctx = _tracker.createInstance<VariableDeclaratorIdContext>(_ctx, getState());
  enterRule(_localctx, 4, SnowStarParser::RuleVariableDeclaratorId);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(49);
    match(SnowStarParser::IDENTIFIER);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- VariableInitializerContext ------------------------------------------------------------------

SnowStarParser::VariableInitializerContext::VariableInitializerContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

SnowStarParser::ExpressionContext* SnowStarParser::VariableInitializerContext::expression() {
  return getRuleContext<SnowStarParser::ExpressionContext>(0);
}


size_t SnowStarParser::VariableInitializerContext::getRuleIndex() const {
  return SnowStarParser::RuleVariableInitializer;
}

antlrcpp::Any SnowStarParser::VariableInitializerContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SnowStarParserVisitor*>(visitor))
    return parserVisitor->visitVariableInitializer(this);
  else
    return visitor->visitChildren(this);
}

SnowStarParser::VariableInitializerContext* SnowStarParser::variableInitializer() {
  VariableInitializerContext *_localctx = _tracker.createInstance<VariableInitializerContext>(_ctx, getState());
  enterRule(_localctx, 6, SnowStarParser::RuleVariableInitializer);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(51);
    expression(0);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- LiteralContext ------------------------------------------------------------------

SnowStarParser::LiteralContext::LiteralContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

SnowStarParser::IntegerLiteralContext* SnowStarParser::LiteralContext::integerLiteral() {
  return getRuleContext<SnowStarParser::IntegerLiteralContext>(0);
}

tree::TerminalNode* SnowStarParser::LiteralContext::FLOAT_LITERAL() {
  return getToken(SnowStarParser::FLOAT_LITERAL, 0);
}

tree::TerminalNode* SnowStarParser::LiteralContext::CHAR_LITERAL() {
  return getToken(SnowStarParser::CHAR_LITERAL, 0);
}

tree::TerminalNode* SnowStarParser::LiteralContext::STRING_LITERAL() {
  return getToken(SnowStarParser::STRING_LITERAL, 0);
}

tree::TerminalNode* SnowStarParser::LiteralContext::BOOL_LITERAL() {
  return getToken(SnowStarParser::BOOL_LITERAL, 0);
}

tree::TerminalNode* SnowStarParser::LiteralContext::NIL_LITERAL() {
  return getToken(SnowStarParser::NIL_LITERAL, 0);
}


size_t SnowStarParser::LiteralContext::getRuleIndex() const {
  return SnowStarParser::RuleLiteral;
}

antlrcpp::Any SnowStarParser::LiteralContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SnowStarParserVisitor*>(visitor))
    return parserVisitor->visitLiteral(this);
  else
    return visitor->visitChildren(this);
}

SnowStarParser::LiteralContext* SnowStarParser::literal() {
  LiteralContext *_localctx = _tracker.createInstance<LiteralContext>(_ctx, getState());
  enterRule(_localctx, 8, SnowStarParser::RuleLiteral);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(59);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case SnowStarParser::DECIMAL_LITERAL:
      case SnowStarParser::HEX_LITERAL:
      case SnowStarParser::BIN_LITERAL: {
        enterOuterAlt(_localctx, 1);
        setState(53);
        integerLiteral();
        break;
      }

      case SnowStarParser::FLOAT_LITERAL: {
        enterOuterAlt(_localctx, 2);
        setState(54);
        match(SnowStarParser::FLOAT_LITERAL);
        break;
      }

      case SnowStarParser::CHAR_LITERAL: {
        enterOuterAlt(_localctx, 3);
        setState(55);
        match(SnowStarParser::CHAR_LITERAL);
        break;
      }

      case SnowStarParser::STRING_LITERAL: {
        enterOuterAlt(_localctx, 4);
        setState(56);
        match(SnowStarParser::STRING_LITERAL);
        break;
      }

      case SnowStarParser::BOOL_LITERAL: {
        enterOuterAlt(_localctx, 5);
        setState(57);
        match(SnowStarParser::BOOL_LITERAL);
        break;
      }

      case SnowStarParser::NIL_LITERAL: {
        enterOuterAlt(_localctx, 6);
        setState(58);
        match(SnowStarParser::NIL_LITERAL);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- IntegerLiteralContext ------------------------------------------------------------------

SnowStarParser::IntegerLiteralContext::IntegerLiteralContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* SnowStarParser::IntegerLiteralContext::DECIMAL_LITERAL() {
  return getToken(SnowStarParser::DECIMAL_LITERAL, 0);
}

tree::TerminalNode* SnowStarParser::IntegerLiteralContext::HEX_LITERAL() {
  return getToken(SnowStarParser::HEX_LITERAL, 0);
}

tree::TerminalNode* SnowStarParser::IntegerLiteralContext::BIN_LITERAL() {
  return getToken(SnowStarParser::BIN_LITERAL, 0);
}


size_t SnowStarParser::IntegerLiteralContext::getRuleIndex() const {
  return SnowStarParser::RuleIntegerLiteral;
}

antlrcpp::Any SnowStarParser::IntegerLiteralContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SnowStarParserVisitor*>(visitor))
    return parserVisitor->visitIntegerLiteral(this);
  else
    return visitor->visitChildren(this);
}

SnowStarParser::IntegerLiteralContext* SnowStarParser::integerLiteral() {
  IntegerLiteralContext *_localctx = _tracker.createInstance<IntegerLiteralContext>(_ctx, getState());
  enterRule(_localctx, 10, SnowStarParser::RuleIntegerLiteral);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(61);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << SnowStarParser::DECIMAL_LITERAL)
      | (1ULL << SnowStarParser::HEX_LITERAL)
      | (1ULL << SnowStarParser::BIN_LITERAL))) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- BlockContext ------------------------------------------------------------------

SnowStarParser::BlockContext::BlockContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<SnowStarParser::BlockStatementContext *> SnowStarParser::BlockContext::blockStatement() {
  return getRuleContexts<SnowStarParser::BlockStatementContext>();
}

SnowStarParser::BlockStatementContext* SnowStarParser::BlockContext::blockStatement(size_t i) {
  return getRuleContext<SnowStarParser::BlockStatementContext>(i);
}


size_t SnowStarParser::BlockContext::getRuleIndex() const {
  return SnowStarParser::RuleBlock;
}

antlrcpp::Any SnowStarParser::BlockContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SnowStarParserVisitor*>(visitor))
    return parserVisitor->visitBlock(this);
  else
    return visitor->visitChildren(this);
}

SnowStarParser::BlockContext* SnowStarParser::block() {
  BlockContext *_localctx = _tracker.createInstance<BlockContext>(_ctx, getState());
  enterRule(_localctx, 12, SnowStarParser::RuleBlock);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(63);
    match(SnowStarParser::LBRACE);
    setState(67);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << SnowStarParser::BOOLEAN)
      | (1ULL << SnowStarParser::CHAR)
      | (1ULL << SnowStarParser::DEF)
      | (1ULL << SnowStarParser::INTEGER8)
      | (1ULL << SnowStarParser::INTEGER16)
      | (1ULL << SnowStarParser::INTEGER32)
      | (1ULL << SnowStarParser::INTEGER64)
      | (1ULL << SnowStarParser::REAL32)
      | (1ULL << SnowStarParser::REAL64)
      | (1ULL << SnowStarParser::STRING)
      | (1ULL << SnowStarParser::VOID)
      | (1ULL << SnowStarParser::DECIMAL_LITERAL)
      | (1ULL << SnowStarParser::HEX_LITERAL)
      | (1ULL << SnowStarParser::BIN_LITERAL)
      | (1ULL << SnowStarParser::FLOAT_LITERAL)
      | (1ULL << SnowStarParser::BOOL_LITERAL)
      | (1ULL << SnowStarParser::CHAR_LITERAL)
      | (1ULL << SnowStarParser::STRING_LITERAL)
      | (1ULL << SnowStarParser::NIL_LITERAL)
      | (1ULL << SnowStarParser::LPAREN)
      | (1ULL << SnowStarParser::LBRACE)
      | (1ULL << SnowStarParser::IDENTIFIER))) != 0)) {
      setState(64);
      blockStatement();
      setState(69);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(70);
    match(SnowStarParser::RBRACE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- BlockStatementContext ------------------------------------------------------------------

SnowStarParser::BlockStatementContext::BlockStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

SnowStarParser::LocalVariableDeclarationContext* SnowStarParser::BlockStatementContext::localVariableDeclaration() {
  return getRuleContext<SnowStarParser::LocalVariableDeclarationContext>(0);
}

SnowStarParser::StatementContext* SnowStarParser::BlockStatementContext::statement() {
  return getRuleContext<SnowStarParser::StatementContext>(0);
}


size_t SnowStarParser::BlockStatementContext::getRuleIndex() const {
  return SnowStarParser::RuleBlockStatement;
}

antlrcpp::Any SnowStarParser::BlockStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SnowStarParserVisitor*>(visitor))
    return parserVisitor->visitBlockStatement(this);
  else
    return visitor->visitChildren(this);
}

SnowStarParser::BlockStatementContext* SnowStarParser::blockStatement() {
  BlockStatementContext *_localctx = _tracker.createInstance<BlockStatementContext>(_ctx, getState());
  enterRule(_localctx, 14, SnowStarParser::RuleBlockStatement);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(76);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case SnowStarParser::BOOLEAN:
      case SnowStarParser::CHAR:
      case SnowStarParser::INTEGER8:
      case SnowStarParser::INTEGER16:
      case SnowStarParser::INTEGER32:
      case SnowStarParser::INTEGER64:
      case SnowStarParser::REAL32:
      case SnowStarParser::REAL64:
      case SnowStarParser::STRING:
      case SnowStarParser::VOID: {
        enterOuterAlt(_localctx, 1);
        setState(72);
        localVariableDeclaration();
        setState(73);
        match(SnowStarParser::SEMI);
        break;
      }

      case SnowStarParser::DEF:
      case SnowStarParser::DECIMAL_LITERAL:
      case SnowStarParser::HEX_LITERAL:
      case SnowStarParser::BIN_LITERAL:
      case SnowStarParser::FLOAT_LITERAL:
      case SnowStarParser::BOOL_LITERAL:
      case SnowStarParser::CHAR_LITERAL:
      case SnowStarParser::STRING_LITERAL:
      case SnowStarParser::NIL_LITERAL:
      case SnowStarParser::LPAREN:
      case SnowStarParser::LBRACE:
      case SnowStarParser::IDENTIFIER: {
        enterOuterAlt(_localctx, 2);
        setState(75);
        statement();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- LocalVariableDeclarationContext ------------------------------------------------------------------

SnowStarParser::LocalVariableDeclarationContext::LocalVariableDeclarationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

SnowStarParser::TypeGenericContext* SnowStarParser::LocalVariableDeclarationContext::typeGeneric() {
  return getRuleContext<SnowStarParser::TypeGenericContext>(0);
}

SnowStarParser::VariableDeclaratorsContext* SnowStarParser::LocalVariableDeclarationContext::variableDeclarators() {
  return getRuleContext<SnowStarParser::VariableDeclaratorsContext>(0);
}


size_t SnowStarParser::LocalVariableDeclarationContext::getRuleIndex() const {
  return SnowStarParser::RuleLocalVariableDeclaration;
}

antlrcpp::Any SnowStarParser::LocalVariableDeclarationContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SnowStarParserVisitor*>(visitor))
    return parserVisitor->visitLocalVariableDeclaration(this);
  else
    return visitor->visitChildren(this);
}

SnowStarParser::LocalVariableDeclarationContext* SnowStarParser::localVariableDeclaration() {
  LocalVariableDeclarationContext *_localctx = _tracker.createInstance<LocalVariableDeclarationContext>(_ctx, getState());
  enterRule(_localctx, 16, SnowStarParser::RuleLocalVariableDeclaration);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(78);
    typeGeneric();
    setState(79);
    variableDeclarators();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StatementContext ------------------------------------------------------------------

SnowStarParser::StatementContext::StatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

SnowStarParser::BlockContext* SnowStarParser::StatementContext::block() {
  return getRuleContext<SnowStarParser::BlockContext>(0);
}

SnowStarParser::ExpressionContext* SnowStarParser::StatementContext::expression() {
  return getRuleContext<SnowStarParser::ExpressionContext>(0);
}


size_t SnowStarParser::StatementContext::getRuleIndex() const {
  return SnowStarParser::RuleStatement;
}

antlrcpp::Any SnowStarParser::StatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SnowStarParserVisitor*>(visitor))
    return parserVisitor->visitStatement(this);
  else
    return visitor->visitChildren(this);
}

SnowStarParser::StatementContext* SnowStarParser::statement() {
  StatementContext *_localctx = _tracker.createInstance<StatementContext>(_ctx, getState());
  enterRule(_localctx, 18, SnowStarParser::RuleStatement);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(85);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case SnowStarParser::LBRACE: {
        enterOuterAlt(_localctx, 1);
        setState(81);
        dynamic_cast<StatementContext *>(_localctx)->blockLabel = block();
        break;
      }

      case SnowStarParser::DEF:
      case SnowStarParser::DECIMAL_LITERAL:
      case SnowStarParser::HEX_LITERAL:
      case SnowStarParser::BIN_LITERAL:
      case SnowStarParser::FLOAT_LITERAL:
      case SnowStarParser::BOOL_LITERAL:
      case SnowStarParser::CHAR_LITERAL:
      case SnowStarParser::STRING_LITERAL:
      case SnowStarParser::NIL_LITERAL:
      case SnowStarParser::LPAREN:
      case SnowStarParser::IDENTIFIER: {
        enterOuterAlt(_localctx, 2);
        setState(82);
        dynamic_cast<StatementContext *>(_localctx)->statementExpression = expression(0);
        setState(83);
        match(SnowStarParser::SEMI);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ExpressionContext ------------------------------------------------------------------

SnowStarParser::ExpressionContext::ExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

SnowStarParser::PrimaryContext* SnowStarParser::ExpressionContext::primary() {
  return getRuleContext<SnowStarParser::PrimaryContext>(0);
}

SnowStarParser::TypeTypeContext* SnowStarParser::ExpressionContext::typeType() {
  return getRuleContext<SnowStarParser::TypeTypeContext>(0);
}

std::vector<SnowStarParser::ExpressionContext *> SnowStarParser::ExpressionContext::expression() {
  return getRuleContexts<SnowStarParser::ExpressionContext>();
}

SnowStarParser::ExpressionContext* SnowStarParser::ExpressionContext::expression(size_t i) {
  return getRuleContext<SnowStarParser::ExpressionContext>(i);
}

tree::TerminalNode* SnowStarParser::ExpressionContext::DEF() {
  return getToken(SnowStarParser::DEF, 0);
}

SnowStarParser::CreatorContext* SnowStarParser::ExpressionContext::creator() {
  return getRuleContext<SnowStarParser::CreatorContext>(0);
}


size_t SnowStarParser::ExpressionContext::getRuleIndex() const {
  return SnowStarParser::RuleExpression;
}

antlrcpp::Any SnowStarParser::ExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SnowStarParserVisitor*>(visitor))
    return parserVisitor->visitExpression(this);
  else
    return visitor->visitChildren(this);
}


SnowStarParser::ExpressionContext* SnowStarParser::expression() {
   return expression(0);
}

SnowStarParser::ExpressionContext* SnowStarParser::expression(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  SnowStarParser::ExpressionContext *_localctx = _tracker.createInstance<ExpressionContext>(_ctx, parentState);
  SnowStarParser::ExpressionContext *previousContext = _localctx;
  size_t startState = 20;
  enterRecursionRule(_localctx, 20, SnowStarParser::RuleExpression, precedence);

    

  auto onExit = finally([=] {
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(96);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 6, _ctx)) {
    case 1: {
      setState(88);
      primary();
      break;
    }

    case 2: {
      setState(89);
      match(SnowStarParser::LPAREN);
      setState(90);
      typeType();
      setState(91);
      match(SnowStarParser::RPAREN);
      setState(92);
      expression(3);
      break;
    }

    case 3: {
      setState(94);
      match(SnowStarParser::DEF);
      setState(95);
      creator();
      break;
    }

    }
    _ctx->stop = _input->LT(-1);
    setState(103);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 7, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        _localctx = _tracker.createInstance<ExpressionContext>(parentContext, parentState);
        pushNewRecursionContext(_localctx, startState, RuleExpression);
        setState(98);

        if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
        setState(99);
        dynamic_cast<ExpressionContext *>(_localctx)->bop = match(SnowStarParser::ASSIGN);
        setState(100);
        expression(1); 
      }
      setState(105);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 7, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- PrimaryContext ------------------------------------------------------------------

SnowStarParser::PrimaryContext::PrimaryContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

SnowStarParser::ExpressionContext* SnowStarParser::PrimaryContext::expression() {
  return getRuleContext<SnowStarParser::ExpressionContext>(0);
}

SnowStarParser::LiteralContext* SnowStarParser::PrimaryContext::literal() {
  return getRuleContext<SnowStarParser::LiteralContext>(0);
}

tree::TerminalNode* SnowStarParser::PrimaryContext::IDENTIFIER() {
  return getToken(SnowStarParser::IDENTIFIER, 0);
}


size_t SnowStarParser::PrimaryContext::getRuleIndex() const {
  return SnowStarParser::RulePrimary;
}

antlrcpp::Any SnowStarParser::PrimaryContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SnowStarParserVisitor*>(visitor))
    return parserVisitor->visitPrimary(this);
  else
    return visitor->visitChildren(this);
}

SnowStarParser::PrimaryContext* SnowStarParser::primary() {
  PrimaryContext *_localctx = _tracker.createInstance<PrimaryContext>(_ctx, getState());
  enterRule(_localctx, 22, SnowStarParser::RulePrimary);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(112);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case SnowStarParser::LPAREN: {
        enterOuterAlt(_localctx, 1);
        setState(106);
        match(SnowStarParser::LPAREN);
        setState(107);
        expression(0);
        setState(108);
        match(SnowStarParser::RPAREN);
        break;
      }

      case SnowStarParser::DECIMAL_LITERAL:
      case SnowStarParser::HEX_LITERAL:
      case SnowStarParser::BIN_LITERAL:
      case SnowStarParser::FLOAT_LITERAL:
      case SnowStarParser::BOOL_LITERAL:
      case SnowStarParser::CHAR_LITERAL:
      case SnowStarParser::STRING_LITERAL:
      case SnowStarParser::NIL_LITERAL: {
        enterOuterAlt(_localctx, 2);
        setState(110);
        literal();
        break;
      }

      case SnowStarParser::IDENTIFIER: {
        enterOuterAlt(_localctx, 3);
        setState(111);
        match(SnowStarParser::IDENTIFIER);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- CreatorContext ------------------------------------------------------------------

SnowStarParser::CreatorContext::CreatorContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

SnowStarParser::CreatedNameContext* SnowStarParser::CreatorContext::createdName() {
  return getRuleContext<SnowStarParser::CreatedNameContext>(0);
}


size_t SnowStarParser::CreatorContext::getRuleIndex() const {
  return SnowStarParser::RuleCreator;
}

antlrcpp::Any SnowStarParser::CreatorContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SnowStarParserVisitor*>(visitor))
    return parserVisitor->visitCreator(this);
  else
    return visitor->visitChildren(this);
}

SnowStarParser::CreatorContext* SnowStarParser::creator() {
  CreatorContext *_localctx = _tracker.createInstance<CreatorContext>(_ctx, getState());
  enterRule(_localctx, 24, SnowStarParser::RuleCreator);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(114);
    createdName();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- CreatedNameContext ------------------------------------------------------------------

SnowStarParser::CreatedNameContext::CreatedNameContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* SnowStarParser::CreatedNameContext::IDENTIFIER() {
  return getToken(SnowStarParser::IDENTIFIER, 0);
}

SnowStarParser::TypeGenericContext* SnowStarParser::CreatedNameContext::typeGeneric() {
  return getRuleContext<SnowStarParser::TypeGenericContext>(0);
}

SnowStarParser::PrimitiveTypeContext* SnowStarParser::CreatedNameContext::primitiveType() {
  return getRuleContext<SnowStarParser::PrimitiveTypeContext>(0);
}


size_t SnowStarParser::CreatedNameContext::getRuleIndex() const {
  return SnowStarParser::RuleCreatedName;
}

antlrcpp::Any SnowStarParser::CreatedNameContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SnowStarParserVisitor*>(visitor))
    return parserVisitor->visitCreatedName(this);
  else
    return visitor->visitChildren(this);
}

SnowStarParser::CreatedNameContext* SnowStarParser::createdName() {
  CreatedNameContext *_localctx = _tracker.createInstance<CreatedNameContext>(_ctx, getState());
  enterRule(_localctx, 26, SnowStarParser::RuleCreatedName);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(122);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case SnowStarParser::IDENTIFIER: {
        enterOuterAlt(_localctx, 1);
        setState(116);
        match(SnowStarParser::IDENTIFIER);
        setState(117);
        match(SnowStarParser::TYPEOF);
        setState(119);
        _errHandler->sync(this);

        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 9, _ctx)) {
        case 1: {
          setState(118);
          typeGeneric();
          break;
        }

        }
        break;
      }

      case SnowStarParser::BOOLEAN:
      case SnowStarParser::CHAR:
      case SnowStarParser::INTEGER8:
      case SnowStarParser::INTEGER16:
      case SnowStarParser::INTEGER32:
      case SnowStarParser::INTEGER64:
      case SnowStarParser::REAL32:
      case SnowStarParser::REAL64:
      case SnowStarParser::STRING:
      case SnowStarParser::VOID: {
        enterOuterAlt(_localctx, 2);
        setState(121);
        primitiveType();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- TypeGenericContext ------------------------------------------------------------------

SnowStarParser::TypeGenericContext::TypeGenericContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

SnowStarParser::TypeTypeContext* SnowStarParser::TypeGenericContext::typeType() {
  return getRuleContext<SnowStarParser::TypeTypeContext>(0);
}

std::vector<SnowStarParser::TypeGenericContext *> SnowStarParser::TypeGenericContext::typeGeneric() {
  return getRuleContexts<SnowStarParser::TypeGenericContext>();
}

SnowStarParser::TypeGenericContext* SnowStarParser::TypeGenericContext::typeGeneric(size_t i) {
  return getRuleContext<SnowStarParser::TypeGenericContext>(i);
}


size_t SnowStarParser::TypeGenericContext::getRuleIndex() const {
  return SnowStarParser::RuleTypeGeneric;
}

antlrcpp::Any SnowStarParser::TypeGenericContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SnowStarParserVisitor*>(visitor))
    return parserVisitor->visitTypeGeneric(this);
  else
    return visitor->visitChildren(this);
}

SnowStarParser::TypeGenericContext* SnowStarParser::typeGeneric() {
  TypeGenericContext *_localctx = _tracker.createInstance<TypeGenericContext>(_ctx, getState());
  enterRule(_localctx, 28, SnowStarParser::RuleTypeGeneric);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(124);
    typeType();
    setState(140);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 13, _ctx)) {
    case 1: {
      setState(125);
      match(SnowStarParser::LOWER);
      setState(136);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & ((1ULL << SnowStarParser::BOOLEAN)
        | (1ULL << SnowStarParser::CHAR)
        | (1ULL << SnowStarParser::INTEGER8)
        | (1ULL << SnowStarParser::INTEGER16)
        | (1ULL << SnowStarParser::INTEGER32)
        | (1ULL << SnowStarParser::INTEGER64)
        | (1ULL << SnowStarParser::REAL32)
        | (1ULL << SnowStarParser::REAL64)
        | (1ULL << SnowStarParser::STRING)
        | (1ULL << SnowStarParser::VOID))) != 0)) {
        setState(126);
        typeGeneric();
        setState(131);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while (_la == SnowStarParser::COMMA) {
          setState(127);
          match(SnowStarParser::COMMA);
          setState(128);
          typeGeneric();
          setState(133);
          _errHandler->sync(this);
          _la = _input->LA(1);
        }
        setState(138);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
      setState(139);
      match(SnowStarParser::GREATER);
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- TypeListContext ------------------------------------------------------------------

SnowStarParser::TypeListContext::TypeListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<SnowStarParser::TypeTypeContext *> SnowStarParser::TypeListContext::typeType() {
  return getRuleContexts<SnowStarParser::TypeTypeContext>();
}

SnowStarParser::TypeTypeContext* SnowStarParser::TypeListContext::typeType(size_t i) {
  return getRuleContext<SnowStarParser::TypeTypeContext>(i);
}


size_t SnowStarParser::TypeListContext::getRuleIndex() const {
  return SnowStarParser::RuleTypeList;
}

antlrcpp::Any SnowStarParser::TypeListContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SnowStarParserVisitor*>(visitor))
    return parserVisitor->visitTypeList(this);
  else
    return visitor->visitChildren(this);
}

SnowStarParser::TypeListContext* SnowStarParser::typeList() {
  TypeListContext *_localctx = _tracker.createInstance<TypeListContext>(_ctx, getState());
  enterRule(_localctx, 30, SnowStarParser::RuleTypeList);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(142);
    typeType();
    setState(147);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == SnowStarParser::COMMA) {
      setState(143);
      match(SnowStarParser::COMMA);
      setState(144);
      typeType();
      setState(149);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- TypeTypeContext ------------------------------------------------------------------

SnowStarParser::TypeTypeContext::TypeTypeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

SnowStarParser::PrimitiveTypeContext* SnowStarParser::TypeTypeContext::primitiveType() {
  return getRuleContext<SnowStarParser::PrimitiveTypeContext>(0);
}


size_t SnowStarParser::TypeTypeContext::getRuleIndex() const {
  return SnowStarParser::RuleTypeType;
}

antlrcpp::Any SnowStarParser::TypeTypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SnowStarParserVisitor*>(visitor))
    return parserVisitor->visitTypeType(this);
  else
    return visitor->visitChildren(this);
}

SnowStarParser::TypeTypeContext* SnowStarParser::typeType() {
  TypeTypeContext *_localctx = _tracker.createInstance<TypeTypeContext>(_ctx, getState());
  enterRule(_localctx, 32, SnowStarParser::RuleTypeType);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(150);
    primitiveType();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- PrimitiveTypeContext ------------------------------------------------------------------

SnowStarParser::PrimitiveTypeContext::PrimitiveTypeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* SnowStarParser::PrimitiveTypeContext::BOOLEAN() {
  return getToken(SnowStarParser::BOOLEAN, 0);
}

tree::TerminalNode* SnowStarParser::PrimitiveTypeContext::CHAR() {
  return getToken(SnowStarParser::CHAR, 0);
}

tree::TerminalNode* SnowStarParser::PrimitiveTypeContext::INTEGER8() {
  return getToken(SnowStarParser::INTEGER8, 0);
}

tree::TerminalNode* SnowStarParser::PrimitiveTypeContext::INTEGER16() {
  return getToken(SnowStarParser::INTEGER16, 0);
}

tree::TerminalNode* SnowStarParser::PrimitiveTypeContext::INTEGER32() {
  return getToken(SnowStarParser::INTEGER32, 0);
}

tree::TerminalNode* SnowStarParser::PrimitiveTypeContext::INTEGER64() {
  return getToken(SnowStarParser::INTEGER64, 0);
}

tree::TerminalNode* SnowStarParser::PrimitiveTypeContext::REAL32() {
  return getToken(SnowStarParser::REAL32, 0);
}

tree::TerminalNode* SnowStarParser::PrimitiveTypeContext::REAL64() {
  return getToken(SnowStarParser::REAL64, 0);
}

tree::TerminalNode* SnowStarParser::PrimitiveTypeContext::STRING() {
  return getToken(SnowStarParser::STRING, 0);
}

tree::TerminalNode* SnowStarParser::PrimitiveTypeContext::VOID() {
  return getToken(SnowStarParser::VOID, 0);
}


size_t SnowStarParser::PrimitiveTypeContext::getRuleIndex() const {
  return SnowStarParser::RulePrimitiveType;
}

antlrcpp::Any SnowStarParser::PrimitiveTypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SnowStarParserVisitor*>(visitor))
    return parserVisitor->visitPrimitiveType(this);
  else
    return visitor->visitChildren(this);
}

SnowStarParser::PrimitiveTypeContext* SnowStarParser::primitiveType() {
  PrimitiveTypeContext *_localctx = _tracker.createInstance<PrimitiveTypeContext>(_ctx, getState());
  enterRule(_localctx, 34, SnowStarParser::RulePrimitiveType);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(152);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << SnowStarParser::BOOLEAN)
      | (1ULL << SnowStarParser::CHAR)
      | (1ULL << SnowStarParser::INTEGER8)
      | (1ULL << SnowStarParser::INTEGER16)
      | (1ULL << SnowStarParser::INTEGER32)
      | (1ULL << SnowStarParser::INTEGER64)
      | (1ULL << SnowStarParser::REAL32)
      | (1ULL << SnowStarParser::REAL64)
      | (1ULL << SnowStarParser::STRING)
      | (1ULL << SnowStarParser::VOID))) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

bool SnowStarParser::sempred(RuleContext *context, size_t ruleIndex, size_t predicateIndex) {
  switch (ruleIndex) {
    case 10: return expressionSempred(dynamic_cast<ExpressionContext *>(context), predicateIndex);

  default:
    break;
  }
  return true;
}

bool SnowStarParser::expressionSempred(ExpressionContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 0: return precpred(_ctx, 1);

  default:
    break;
  }
  return true;
}

// Static vars and initialization.
std::vector<dfa::DFA> SnowStarParser::_decisionToDFA;
atn::PredictionContextCache SnowStarParser::_sharedContextCache;

// We own the ATN which in turn owns the ATN states.
atn::ATN SnowStarParser::_atn;
std::vector<uint16_t> SnowStarParser::_serializedATN;

std::vector<std::string> SnowStarParser::_ruleNames = {
  "variableDeclarators", "variableDeclarator", "variableDeclaratorId", "variableInitializer", 
  "literal", "integerLiteral", "block", "blockStatement", "localVariableDeclaration", 
  "statement", "expression", "primary", "creator", "createdName", "typeGeneric", 
  "typeList", "typeType", "primitiveType"
};

std::vector<std::string> SnowStarParser::_literalNames = {
  "", "'bool'", "'char'", "'def'", "'int8'", "'int16'", "'int32'", "'int64'", 
  "'real32'", "'real64'", "'string'", "'void'", "", "", "", "", "", "", 
  "", "'nil'", "'('", "')'", "'{'", "'}'", "'['", "']'", "';'", "','", "'.'", 
  "'='", "'->'", "'<'", "'>'"
};

std::vector<std::string> SnowStarParser::_symbolicNames = {
  "", "BOOLEAN", "CHAR", "DEF", "INTEGER8", "INTEGER16", "INTEGER32", "INTEGER64", 
  "REAL32", "REAL64", "STRING", "VOID", "DECIMAL_LITERAL", "HEX_LITERAL", 
  "BIN_LITERAL", "FLOAT_LITERAL", "BOOL_LITERAL", "CHAR_LITERAL", "STRING_LITERAL", 
  "NIL_LITERAL", "LPAREN", "RPAREN", "LBRACE", "RBRACE", "LBRACK", "RBRACK", 
  "SEMI", "COMMA", "DOT", "ASSIGN", "TYPEOF", "LOWER", "GREATER", "WS", 
  "COMMENT", "LINE_COMMENT", "IDENTIFIER"
};

dfa::Vocabulary SnowStarParser::_vocabulary(_literalNames, _symbolicNames);

std::vector<std::string> SnowStarParser::_tokenNames;

SnowStarParser::Initializer::Initializer() {
	for (size_t i = 0; i < _symbolicNames.size(); ++i) {
		std::string name = _vocabulary.getLiteralName(i);
		if (name.empty()) {
			name = _vocabulary.getSymbolicName(i);
		}

		if (name.empty()) {
			_tokenNames.push_back("<INVALID>");
		} else {
      _tokenNames.push_back(name);
    }
	}

  _serializedATN = {
    0x3, 0x608b, 0xa72a, 0x8133, 0xb9ed, 0x417c, 0x3be7, 0x7786, 0x5964, 
    0x3, 0x26, 0x9d, 0x4, 0x2, 0x9, 0x2, 0x4, 0x3, 0x9, 0x3, 0x4, 0x4, 0x9, 
    0x4, 0x4, 0x5, 0x9, 0x5, 0x4, 0x6, 0x9, 0x6, 0x4, 0x7, 0x9, 0x7, 0x4, 
    0x8, 0x9, 0x8, 0x4, 0x9, 0x9, 0x9, 0x4, 0xa, 0x9, 0xa, 0x4, 0xb, 0x9, 
    0xb, 0x4, 0xc, 0x9, 0xc, 0x4, 0xd, 0x9, 0xd, 0x4, 0xe, 0x9, 0xe, 0x4, 
    0xf, 0x9, 0xf, 0x4, 0x10, 0x9, 0x10, 0x4, 0x11, 0x9, 0x11, 0x4, 0x12, 
    0x9, 0x12, 0x4, 0x13, 0x9, 0x13, 0x3, 0x2, 0x3, 0x2, 0x3, 0x2, 0x7, 
    0x2, 0x2a, 0xa, 0x2, 0xc, 0x2, 0xe, 0x2, 0x2d, 0xb, 0x2, 0x3, 0x3, 0x3, 
    0x3, 0x3, 0x3, 0x5, 0x3, 0x32, 0xa, 0x3, 0x3, 0x4, 0x3, 0x4, 0x3, 0x5, 
    0x3, 0x5, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 
    0x5, 0x6, 0x3e, 0xa, 0x6, 0x3, 0x7, 0x3, 0x7, 0x3, 0x8, 0x3, 0x8, 0x7, 
    0x8, 0x44, 0xa, 0x8, 0xc, 0x8, 0xe, 0x8, 0x47, 0xb, 0x8, 0x3, 0x8, 0x3, 
    0x8, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 0x5, 0x9, 0x4f, 0xa, 0x9, 
    0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 
    0x5, 0xb, 0x58, 0xa, 0xb, 0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 
    0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 0x5, 0xc, 0x63, 0xa, 0xc, 
    0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 0x7, 0xc, 0x68, 0xa, 0xc, 0xc, 0xc, 0xe, 
    0xc, 0x6b, 0xb, 0xc, 0x3, 0xd, 0x3, 0xd, 0x3, 0xd, 0x3, 0xd, 0x3, 0xd, 
    0x3, 0xd, 0x5, 0xd, 0x73, 0xa, 0xd, 0x3, 0xe, 0x3, 0xe, 0x3, 0xf, 0x3, 
    0xf, 0x3, 0xf, 0x5, 0xf, 0x7a, 0xa, 0xf, 0x3, 0xf, 0x5, 0xf, 0x7d, 0xa, 
    0xf, 0x3, 0x10, 0x3, 0x10, 0x3, 0x10, 0x3, 0x10, 0x3, 0x10, 0x7, 0x10, 
    0x84, 0xa, 0x10, 0xc, 0x10, 0xe, 0x10, 0x87, 0xb, 0x10, 0x7, 0x10, 0x89, 
    0xa, 0x10, 0xc, 0x10, 0xe, 0x10, 0x8c, 0xb, 0x10, 0x3, 0x10, 0x5, 0x10, 
    0x8f, 0xa, 0x10, 0x3, 0x11, 0x3, 0x11, 0x3, 0x11, 0x7, 0x11, 0x94, 0xa, 
    0x11, 0xc, 0x11, 0xe, 0x11, 0x97, 0xb, 0x11, 0x3, 0x12, 0x3, 0x12, 0x3, 
    0x13, 0x3, 0x13, 0x3, 0x13, 0x2, 0x3, 0x16, 0x14, 0x2, 0x4, 0x6, 0x8, 
    0xa, 0xc, 0xe, 0x10, 0x12, 0x14, 0x16, 0x18, 0x1a, 0x1c, 0x1e, 0x20, 
    0x22, 0x24, 0x2, 0x4, 0x3, 0x2, 0xe, 0x10, 0x4, 0x2, 0x3, 0x4, 0x6, 
    0xd, 0x2, 0x9f, 0x2, 0x26, 0x3, 0x2, 0x2, 0x2, 0x4, 0x2e, 0x3, 0x2, 
    0x2, 0x2, 0x6, 0x33, 0x3, 0x2, 0x2, 0x2, 0x8, 0x35, 0x3, 0x2, 0x2, 0x2, 
    0xa, 0x3d, 0x3, 0x2, 0x2, 0x2, 0xc, 0x3f, 0x3, 0x2, 0x2, 0x2, 0xe, 0x41, 
    0x3, 0x2, 0x2, 0x2, 0x10, 0x4e, 0x3, 0x2, 0x2, 0x2, 0x12, 0x50, 0x3, 
    0x2, 0x2, 0x2, 0x14, 0x57, 0x3, 0x2, 0x2, 0x2, 0x16, 0x62, 0x3, 0x2, 
    0x2, 0x2, 0x18, 0x72, 0x3, 0x2, 0x2, 0x2, 0x1a, 0x74, 0x3, 0x2, 0x2, 
    0x2, 0x1c, 0x7c, 0x3, 0x2, 0x2, 0x2, 0x1e, 0x7e, 0x3, 0x2, 0x2, 0x2, 
    0x20, 0x90, 0x3, 0x2, 0x2, 0x2, 0x22, 0x98, 0x3, 0x2, 0x2, 0x2, 0x24, 
    0x9a, 0x3, 0x2, 0x2, 0x2, 0x26, 0x2b, 0x5, 0x4, 0x3, 0x2, 0x27, 0x28, 
    0x7, 0x1d, 0x2, 0x2, 0x28, 0x2a, 0x5, 0x4, 0x3, 0x2, 0x29, 0x27, 0x3, 
    0x2, 0x2, 0x2, 0x2a, 0x2d, 0x3, 0x2, 0x2, 0x2, 0x2b, 0x29, 0x3, 0x2, 
    0x2, 0x2, 0x2b, 0x2c, 0x3, 0x2, 0x2, 0x2, 0x2c, 0x3, 0x3, 0x2, 0x2, 
    0x2, 0x2d, 0x2b, 0x3, 0x2, 0x2, 0x2, 0x2e, 0x31, 0x5, 0x6, 0x4, 0x2, 
    0x2f, 0x30, 0x7, 0x1f, 0x2, 0x2, 0x30, 0x32, 0x5, 0x8, 0x5, 0x2, 0x31, 
    0x2f, 0x3, 0x2, 0x2, 0x2, 0x31, 0x32, 0x3, 0x2, 0x2, 0x2, 0x32, 0x5, 
    0x3, 0x2, 0x2, 0x2, 0x33, 0x34, 0x7, 0x26, 0x2, 0x2, 0x34, 0x7, 0x3, 
    0x2, 0x2, 0x2, 0x35, 0x36, 0x5, 0x16, 0xc, 0x2, 0x36, 0x9, 0x3, 0x2, 
    0x2, 0x2, 0x37, 0x3e, 0x5, 0xc, 0x7, 0x2, 0x38, 0x3e, 0x7, 0x11, 0x2, 
    0x2, 0x39, 0x3e, 0x7, 0x13, 0x2, 0x2, 0x3a, 0x3e, 0x7, 0x14, 0x2, 0x2, 
    0x3b, 0x3e, 0x7, 0x12, 0x2, 0x2, 0x3c, 0x3e, 0x7, 0x15, 0x2, 0x2, 0x3d, 
    0x37, 0x3, 0x2, 0x2, 0x2, 0x3d, 0x38, 0x3, 0x2, 0x2, 0x2, 0x3d, 0x39, 
    0x3, 0x2, 0x2, 0x2, 0x3d, 0x3a, 0x3, 0x2, 0x2, 0x2, 0x3d, 0x3b, 0x3, 
    0x2, 0x2, 0x2, 0x3d, 0x3c, 0x3, 0x2, 0x2, 0x2, 0x3e, 0xb, 0x3, 0x2, 
    0x2, 0x2, 0x3f, 0x40, 0x9, 0x2, 0x2, 0x2, 0x40, 0xd, 0x3, 0x2, 0x2, 
    0x2, 0x41, 0x45, 0x7, 0x18, 0x2, 0x2, 0x42, 0x44, 0x5, 0x10, 0x9, 0x2, 
    0x43, 0x42, 0x3, 0x2, 0x2, 0x2, 0x44, 0x47, 0x3, 0x2, 0x2, 0x2, 0x45, 
    0x43, 0x3, 0x2, 0x2, 0x2, 0x45, 0x46, 0x3, 0x2, 0x2, 0x2, 0x46, 0x48, 
    0x3, 0x2, 0x2, 0x2, 0x47, 0x45, 0x3, 0x2, 0x2, 0x2, 0x48, 0x49, 0x7, 
    0x19, 0x2, 0x2, 0x49, 0xf, 0x3, 0x2, 0x2, 0x2, 0x4a, 0x4b, 0x5, 0x12, 
    0xa, 0x2, 0x4b, 0x4c, 0x7, 0x1c, 0x2, 0x2, 0x4c, 0x4f, 0x3, 0x2, 0x2, 
    0x2, 0x4d, 0x4f, 0x5, 0x14, 0xb, 0x2, 0x4e, 0x4a, 0x3, 0x2, 0x2, 0x2, 
    0x4e, 0x4d, 0x3, 0x2, 0x2, 0x2, 0x4f, 0x11, 0x3, 0x2, 0x2, 0x2, 0x50, 
    0x51, 0x5, 0x1e, 0x10, 0x2, 0x51, 0x52, 0x5, 0x2, 0x2, 0x2, 0x52, 0x13, 
    0x3, 0x2, 0x2, 0x2, 0x53, 0x58, 0x5, 0xe, 0x8, 0x2, 0x54, 0x55, 0x5, 
    0x16, 0xc, 0x2, 0x55, 0x56, 0x7, 0x1c, 0x2, 0x2, 0x56, 0x58, 0x3, 0x2, 
    0x2, 0x2, 0x57, 0x53, 0x3, 0x2, 0x2, 0x2, 0x57, 0x54, 0x3, 0x2, 0x2, 
    0x2, 0x58, 0x15, 0x3, 0x2, 0x2, 0x2, 0x59, 0x5a, 0x8, 0xc, 0x1, 0x2, 
    0x5a, 0x63, 0x5, 0x18, 0xd, 0x2, 0x5b, 0x5c, 0x7, 0x16, 0x2, 0x2, 0x5c, 
    0x5d, 0x5, 0x22, 0x12, 0x2, 0x5d, 0x5e, 0x7, 0x17, 0x2, 0x2, 0x5e, 0x5f, 
    0x5, 0x16, 0xc, 0x5, 0x5f, 0x63, 0x3, 0x2, 0x2, 0x2, 0x60, 0x61, 0x7, 
    0x5, 0x2, 0x2, 0x61, 0x63, 0x5, 0x1a, 0xe, 0x2, 0x62, 0x59, 0x3, 0x2, 
    0x2, 0x2, 0x62, 0x5b, 0x3, 0x2, 0x2, 0x2, 0x62, 0x60, 0x3, 0x2, 0x2, 
    0x2, 0x63, 0x69, 0x3, 0x2, 0x2, 0x2, 0x64, 0x65, 0xc, 0x3, 0x2, 0x2, 
    0x65, 0x66, 0x7, 0x1f, 0x2, 0x2, 0x66, 0x68, 0x5, 0x16, 0xc, 0x3, 0x67, 
    0x64, 0x3, 0x2, 0x2, 0x2, 0x68, 0x6b, 0x3, 0x2, 0x2, 0x2, 0x69, 0x67, 
    0x3, 0x2, 0x2, 0x2, 0x69, 0x6a, 0x3, 0x2, 0x2, 0x2, 0x6a, 0x17, 0x3, 
    0x2, 0x2, 0x2, 0x6b, 0x69, 0x3, 0x2, 0x2, 0x2, 0x6c, 0x6d, 0x7, 0x16, 
    0x2, 0x2, 0x6d, 0x6e, 0x5, 0x16, 0xc, 0x2, 0x6e, 0x6f, 0x7, 0x17, 0x2, 
    0x2, 0x6f, 0x73, 0x3, 0x2, 0x2, 0x2, 0x70, 0x73, 0x5, 0xa, 0x6, 0x2, 
    0x71, 0x73, 0x7, 0x26, 0x2, 0x2, 0x72, 0x6c, 0x3, 0x2, 0x2, 0x2, 0x72, 
    0x70, 0x3, 0x2, 0x2, 0x2, 0x72, 0x71, 0x3, 0x2, 0x2, 0x2, 0x73, 0x19, 
    0x3, 0x2, 0x2, 0x2, 0x74, 0x75, 0x5, 0x1c, 0xf, 0x2, 0x75, 0x1b, 0x3, 
    0x2, 0x2, 0x2, 0x76, 0x77, 0x7, 0x26, 0x2, 0x2, 0x77, 0x79, 0x7, 0x20, 
    0x2, 0x2, 0x78, 0x7a, 0x5, 0x1e, 0x10, 0x2, 0x79, 0x78, 0x3, 0x2, 0x2, 
    0x2, 0x79, 0x7a, 0x3, 0x2, 0x2, 0x2, 0x7a, 0x7d, 0x3, 0x2, 0x2, 0x2, 
    0x7b, 0x7d, 0x5, 0x24, 0x13, 0x2, 0x7c, 0x76, 0x3, 0x2, 0x2, 0x2, 0x7c, 
    0x7b, 0x3, 0x2, 0x2, 0x2, 0x7d, 0x1d, 0x3, 0x2, 0x2, 0x2, 0x7e, 0x8e, 
    0x5, 0x22, 0x12, 0x2, 0x7f, 0x8a, 0x7, 0x21, 0x2, 0x2, 0x80, 0x85, 0x5, 
    0x1e, 0x10, 0x2, 0x81, 0x82, 0x7, 0x1d, 0x2, 0x2, 0x82, 0x84, 0x5, 0x1e, 
    0x10, 0x2, 0x83, 0x81, 0x3, 0x2, 0x2, 0x2, 0x84, 0x87, 0x3, 0x2, 0x2, 
    0x2, 0x85, 0x83, 0x3, 0x2, 0x2, 0x2, 0x85, 0x86, 0x3, 0x2, 0x2, 0x2, 
    0x86, 0x89, 0x3, 0x2, 0x2, 0x2, 0x87, 0x85, 0x3, 0x2, 0x2, 0x2, 0x88, 
    0x80, 0x3, 0x2, 0x2, 0x2, 0x89, 0x8c, 0x3, 0x2, 0x2, 0x2, 0x8a, 0x88, 
    0x3, 0x2, 0x2, 0x2, 0x8a, 0x8b, 0x3, 0x2, 0x2, 0x2, 0x8b, 0x8d, 0x3, 
    0x2, 0x2, 0x2, 0x8c, 0x8a, 0x3, 0x2, 0x2, 0x2, 0x8d, 0x8f, 0x7, 0x22, 
    0x2, 0x2, 0x8e, 0x7f, 0x3, 0x2, 0x2, 0x2, 0x8e, 0x8f, 0x3, 0x2, 0x2, 
    0x2, 0x8f, 0x1f, 0x3, 0x2, 0x2, 0x2, 0x90, 0x95, 0x5, 0x22, 0x12, 0x2, 
    0x91, 0x92, 0x7, 0x1d, 0x2, 0x2, 0x92, 0x94, 0x5, 0x22, 0x12, 0x2, 0x93, 
    0x91, 0x3, 0x2, 0x2, 0x2, 0x94, 0x97, 0x3, 0x2, 0x2, 0x2, 0x95, 0x93, 
    0x3, 0x2, 0x2, 0x2, 0x95, 0x96, 0x3, 0x2, 0x2, 0x2, 0x96, 0x21, 0x3, 
    0x2, 0x2, 0x2, 0x97, 0x95, 0x3, 0x2, 0x2, 0x2, 0x98, 0x99, 0x5, 0x24, 
    0x13, 0x2, 0x99, 0x23, 0x3, 0x2, 0x2, 0x2, 0x9a, 0x9b, 0x9, 0x3, 0x2, 
    0x2, 0x9b, 0x25, 0x3, 0x2, 0x2, 0x2, 0x11, 0x2b, 0x31, 0x3d, 0x45, 0x4e, 
    0x57, 0x62, 0x69, 0x72, 0x79, 0x7c, 0x85, 0x8a, 0x8e, 0x95, 
  };

  atn::ATNDeserializer deserializer;
  _atn = deserializer.deserialize(_serializedATN);

  size_t count = _atn.getNumberOfDecisions();
  _decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    _decisionToDFA.emplace_back(_atn.getDecisionState(i), i);
  }
}

SnowStarParser::Initializer SnowStarParser::_init;
