
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


//----------------- CompilationUnitContext ------------------------------------------------------------------

SnowStarParser::CompilationUnitContext::CompilationUnitContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<SnowStarParser::StatementContext *> SnowStarParser::CompilationUnitContext::statement() {
  return getRuleContexts<SnowStarParser::StatementContext>();
}

SnowStarParser::StatementContext* SnowStarParser::CompilationUnitContext::statement(size_t i) {
  return getRuleContext<SnowStarParser::StatementContext>(i);
}


size_t SnowStarParser::CompilationUnitContext::getRuleIndex() const {
  return SnowStarParser::RuleCompilationUnit;
}

antlrcpp::Any SnowStarParser::CompilationUnitContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SnowStarParserVisitor*>(visitor))
    return parserVisitor->visitCompilationUnit(this);
  else
    return visitor->visitChildren(this);
}

SnowStarParser::CompilationUnitContext* SnowStarParser::compilationUnit() {
  CompilationUnitContext *_localctx = _tracker.createInstance<CompilationUnitContext>(_ctx, getState());
  enterRule(_localctx, 0, SnowStarParser::RuleCompilationUnit);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(25); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(24);
      statement();
      setState(27); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << SnowStarParser::BOOLEAN)
      | (1ULL << SnowStarParser::CHAR)
      | (1ULL << SnowStarParser::INTEGER8)
      | (1ULL << SnowStarParser::INTEGER16)
      | (1ULL << SnowStarParser::INTEGER32)
      | (1ULL << SnowStarParser::INTEGER64)
      | (1ULL << SnowStarParser::REAL16)
      | (1ULL << SnowStarParser::REAL32)
      | (1ULL << SnowStarParser::REAL64)
      | (1ULL << SnowStarParser::VOID)
      | (1ULL << SnowStarParser::WITH)
      | (1ULL << SnowStarParser::IDENTIFIER))) != 0));
   
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

SnowStarParser::DeclareContext* SnowStarParser::StatementContext::declare() {
  return getRuleContext<SnowStarParser::DeclareContext>(0);
}

SnowStarParser::DefineContext* SnowStarParser::StatementContext::define() {
  return getRuleContext<SnowStarParser::DefineContext>(0);
}

SnowStarParser::AliasContext* SnowStarParser::StatementContext::alias() {
  return getRuleContext<SnowStarParser::AliasContext>(0);
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
  enterRule(_localctx, 2, SnowStarParser::RuleStatement);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(41);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 4, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(29);
      declare();
      setState(31);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == SnowStarParser::SEMI) {
        setState(30);
        dynamic_cast<StatementContext *>(_localctx)->eol = match(SnowStarParser::SEMI);
      }
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(33);
      define();
      setState(35);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == SnowStarParser::SEMI) {
        setState(34);
        dynamic_cast<StatementContext *>(_localctx)->eol = match(SnowStarParser::SEMI);
      }
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(37);
      alias();
      setState(39);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == SnowStarParser::SEMI) {
        setState(38);
        dynamic_cast<StatementContext *>(_localctx)->eol = match(SnowStarParser::SEMI);
      }
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

//----------------- ExpressionContext ------------------------------------------------------------------

SnowStarParser::ExpressionContext::ExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* SnowStarParser::ExpressionContext::IDENTIFIER() {
  return getToken(SnowStarParser::IDENTIFIER, 0);
}

SnowStarParser::LiteralContext* SnowStarParser::ExpressionContext::literal() {
  return getRuleContext<SnowStarParser::LiteralContext>(0);
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
  ExpressionContext *_localctx = _tracker.createInstance<ExpressionContext>(_ctx, getState());
  enterRule(_localctx, 4, SnowStarParser::RuleExpression);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(45);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case SnowStarParser::IDENTIFIER: {
        enterOuterAlt(_localctx, 1);
        setState(43);
        match(SnowStarParser::IDENTIFIER);
        break;
      }

      case SnowStarParser::DECIMAL_LITERAL:
      case SnowStarParser::HEX_LITERAL:
      case SnowStarParser::BIN_LITERAL:
      case SnowStarParser::FLOAT_LITERAL:
      case SnowStarParser::BOOL_LITERAL:
      case SnowStarParser::CHAR_LITERAL:
      case SnowStarParser::NIL_LITERAL: {
        enterOuterAlt(_localctx, 2);
        setState(44);
        literal();
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

//----------------- AssignContext ------------------------------------------------------------------

SnowStarParser::AssignContext::AssignContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* SnowStarParser::AssignContext::IDENTIFIER() {
  return getToken(SnowStarParser::IDENTIFIER, 0);
}

SnowStarParser::ExpressionContext* SnowStarParser::AssignContext::expression() {
  return getRuleContext<SnowStarParser::ExpressionContext>(0);
}


size_t SnowStarParser::AssignContext::getRuleIndex() const {
  return SnowStarParser::RuleAssign;
}

antlrcpp::Any SnowStarParser::AssignContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SnowStarParserVisitor*>(visitor))
    return parserVisitor->visitAssign(this);
  else
    return visitor->visitChildren(this);
}

SnowStarParser::AssignContext* SnowStarParser::assign() {
  AssignContext *_localctx = _tracker.createInstance<AssignContext>(_ctx, getState());
  enterRule(_localctx, 6, SnowStarParser::RuleAssign);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(47);
    match(SnowStarParser::IDENTIFIER);
    setState(49);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == SnowStarParser::ASSIGN) {
      setState(48);
      dynamic_cast<AssignContext *>(_localctx)->eop = match(SnowStarParser::ASSIGN);
    }
    setState(52);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << SnowStarParser::DECIMAL_LITERAL)
      | (1ULL << SnowStarParser::HEX_LITERAL)
      | (1ULL << SnowStarParser::BIN_LITERAL)
      | (1ULL << SnowStarParser::FLOAT_LITERAL)
      | (1ULL << SnowStarParser::BOOL_LITERAL)
      | (1ULL << SnowStarParser::CHAR_LITERAL)
      | (1ULL << SnowStarParser::NIL_LITERAL)
      | (1ULL << SnowStarParser::IDENTIFIER))) != 0)) {
      setState(51);
      expression();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- DefineContext ------------------------------------------------------------------

SnowStarParser::DefineContext::DefineContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

SnowStarParser::DeclareContext* SnowStarParser::DefineContext::declare() {
  return getRuleContext<SnowStarParser::DeclareContext>(0);
}

SnowStarParser::DeclareNoIDContext* SnowStarParser::DefineContext::declareNoID() {
  return getRuleContext<SnowStarParser::DeclareNoIDContext>(0);
}

SnowStarParser::ExpressionContext* SnowStarParser::DefineContext::expression() {
  return getRuleContext<SnowStarParser::ExpressionContext>(0);
}


size_t SnowStarParser::DefineContext::getRuleIndex() const {
  return SnowStarParser::RuleDefine;
}

antlrcpp::Any SnowStarParser::DefineContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SnowStarParserVisitor*>(visitor))
    return parserVisitor->visitDefine(this);
  else
    return visitor->visitChildren(this);
}

SnowStarParser::DefineContext* SnowStarParser::define() {
  DefineContext *_localctx = _tracker.createInstance<DefineContext>(_ctx, getState());
  enterRule(_localctx, 8, SnowStarParser::RuleDefine);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(56);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 8, _ctx)) {
    case 1: {
      setState(54);
      declare();
      break;
    }

    case 2: {
      setState(55);
      declareNoID();
      break;
    }

    }
    setState(59);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == SnowStarParser::ASSIGN) {
      setState(58);
      dynamic_cast<DefineContext *>(_localctx)->eop = match(SnowStarParser::ASSIGN);
    }
    setState(62);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 10, _ctx)) {
    case 1: {
      setState(61);
      expression();
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

//----------------- DeclareContext ------------------------------------------------------------------

SnowStarParser::DeclareContext::DeclareContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

SnowStarParser::TypeContext* SnowStarParser::DeclareContext::type() {
  return getRuleContext<SnowStarParser::TypeContext>(0);
}

tree::TerminalNode* SnowStarParser::DeclareContext::IDENTIFIER() {
  return getToken(SnowStarParser::IDENTIFIER, 0);
}


size_t SnowStarParser::DeclareContext::getRuleIndex() const {
  return SnowStarParser::RuleDeclare;
}

antlrcpp::Any SnowStarParser::DeclareContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SnowStarParserVisitor*>(visitor))
    return parserVisitor->visitDeclare(this);
  else
    return visitor->visitChildren(this);
}

SnowStarParser::DeclareContext* SnowStarParser::declare() {
  DeclareContext *_localctx = _tracker.createInstance<DeclareContext>(_ctx, getState());
  enterRule(_localctx, 10, SnowStarParser::RuleDeclare);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(64);
    type();
    setState(65);
    match(SnowStarParser::IDENTIFIER);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- DeclareNoIDContext ------------------------------------------------------------------

SnowStarParser::DeclareNoIDContext::DeclareNoIDContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

SnowStarParser::TypeContext* SnowStarParser::DeclareNoIDContext::type() {
  return getRuleContext<SnowStarParser::TypeContext>(0);
}


size_t SnowStarParser::DeclareNoIDContext::getRuleIndex() const {
  return SnowStarParser::RuleDeclareNoID;
}

antlrcpp::Any SnowStarParser::DeclareNoIDContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SnowStarParserVisitor*>(visitor))
    return parserVisitor->visitDeclareNoID(this);
  else
    return visitor->visitChildren(this);
}

SnowStarParser::DeclareNoIDContext* SnowStarParser::declareNoID() {
  DeclareNoIDContext *_localctx = _tracker.createInstance<DeclareNoIDContext>(_ctx, getState());
  enterRule(_localctx, 12, SnowStarParser::RuleDeclareNoID);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(67);
    type();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AliasContext ------------------------------------------------------------------

SnowStarParser::AliasContext::AliasContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* SnowStarParser::AliasContext::IDENTIFIER() {
  return getToken(SnowStarParser::IDENTIFIER, 0);
}

SnowStarParser::TypeContext* SnowStarParser::AliasContext::type() {
  return getRuleContext<SnowStarParser::TypeContext>(0);
}


size_t SnowStarParser::AliasContext::getRuleIndex() const {
  return SnowStarParser::RuleAlias;
}

antlrcpp::Any SnowStarParser::AliasContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SnowStarParserVisitor*>(visitor))
    return parserVisitor->visitAlias(this);
  else
    return visitor->visitChildren(this);
}

SnowStarParser::AliasContext* SnowStarParser::alias() {
  AliasContext *_localctx = _tracker.createInstance<AliasContext>(_ctx, getState());
  enterRule(_localctx, 14, SnowStarParser::RuleAlias);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(69);
    dynamic_cast<AliasContext *>(_localctx)->with = match(SnowStarParser::WITH);
    setState(71);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 11, _ctx)) {
    case 1: {
      setState(70);
      match(SnowStarParser::IDENTIFIER);
      break;
    }

    }
    setState(74);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == SnowStarParser::ASSIGN) {
      setState(73);
      dynamic_cast<AliasContext *>(_localctx)->eop = match(SnowStarParser::ASSIGN);
    }
    setState(77);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 13, _ctx)) {
    case 1: {
      setState(76);
      type();
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

//----------------- TestContext ------------------------------------------------------------------

SnowStarParser::TestContext::TestContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* SnowStarParser::TestContext::IDENTIFIER() {
  return getToken(SnowStarParser::IDENTIFIER, 0);
}


size_t SnowStarParser::TestContext::getRuleIndex() const {
  return SnowStarParser::RuleTest;
}

antlrcpp::Any SnowStarParser::TestContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SnowStarParserVisitor*>(visitor))
    return parserVisitor->visitTest(this);
  else
    return visitor->visitChildren(this);
}

SnowStarParser::TestContext* SnowStarParser::test() {
  TestContext *_localctx = _tracker.createInstance<TestContext>(_ctx, getState());
  enterRule(_localctx, 16, SnowStarParser::RuleTest);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(80);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == SnowStarParser::ASSIGN) {
      setState(79);
      dynamic_cast<TestContext *>(_localctx)->e = match(SnowStarParser::ASSIGN);
    }
    setState(83);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == SnowStarParser::IDENTIFIER) {
      setState(82);
      match(SnowStarParser::IDENTIFIER);
    }
    setState(86);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == SnowStarParser::SEMI) {
      setState(85);
      dynamic_cast<TestContext *>(_localctx)->ex = match(SnowStarParser::SEMI);
    }
   
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

tree::TerminalNode* SnowStarParser::LiteralContext::DECIMAL_LITERAL() {
  return getToken(SnowStarParser::DECIMAL_LITERAL, 0);
}

tree::TerminalNode* SnowStarParser::LiteralContext::HEX_LITERAL() {
  return getToken(SnowStarParser::HEX_LITERAL, 0);
}

tree::TerminalNode* SnowStarParser::LiteralContext::BIN_LITERAL() {
  return getToken(SnowStarParser::BIN_LITERAL, 0);
}

tree::TerminalNode* SnowStarParser::LiteralContext::FLOAT_LITERAL() {
  return getToken(SnowStarParser::FLOAT_LITERAL, 0);
}

tree::TerminalNode* SnowStarParser::LiteralContext::BOOL_LITERAL() {
  return getToken(SnowStarParser::BOOL_LITERAL, 0);
}

tree::TerminalNode* SnowStarParser::LiteralContext::CHAR_LITERAL() {
  return getToken(SnowStarParser::CHAR_LITERAL, 0);
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
  enterRule(_localctx, 18, SnowStarParser::RuleLiteral);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(88);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << SnowStarParser::DECIMAL_LITERAL)
      | (1ULL << SnowStarParser::HEX_LITERAL)
      | (1ULL << SnowStarParser::BIN_LITERAL)
      | (1ULL << SnowStarParser::FLOAT_LITERAL)
      | (1ULL << SnowStarParser::BOOL_LITERAL)
      | (1ULL << SnowStarParser::CHAR_LITERAL)
      | (1ULL << SnowStarParser::NIL_LITERAL))) != 0))) {
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

//----------------- TypeContext ------------------------------------------------------------------

SnowStarParser::TypeContext::TypeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* SnowStarParser::TypeContext::BOOLEAN() {
  return getToken(SnowStarParser::BOOLEAN, 0);
}

tree::TerminalNode* SnowStarParser::TypeContext::CHAR() {
  return getToken(SnowStarParser::CHAR, 0);
}

tree::TerminalNode* SnowStarParser::TypeContext::INTEGER8() {
  return getToken(SnowStarParser::INTEGER8, 0);
}

tree::TerminalNode* SnowStarParser::TypeContext::INTEGER16() {
  return getToken(SnowStarParser::INTEGER16, 0);
}

tree::TerminalNode* SnowStarParser::TypeContext::INTEGER32() {
  return getToken(SnowStarParser::INTEGER32, 0);
}

tree::TerminalNode* SnowStarParser::TypeContext::INTEGER64() {
  return getToken(SnowStarParser::INTEGER64, 0);
}

tree::TerminalNode* SnowStarParser::TypeContext::REAL16() {
  return getToken(SnowStarParser::REAL16, 0);
}

tree::TerminalNode* SnowStarParser::TypeContext::REAL32() {
  return getToken(SnowStarParser::REAL32, 0);
}

tree::TerminalNode* SnowStarParser::TypeContext::REAL64() {
  return getToken(SnowStarParser::REAL64, 0);
}

tree::TerminalNode* SnowStarParser::TypeContext::VOID() {
  return getToken(SnowStarParser::VOID, 0);
}

tree::TerminalNode* SnowStarParser::TypeContext::IDENTIFIER() {
  return getToken(SnowStarParser::IDENTIFIER, 0);
}


size_t SnowStarParser::TypeContext::getRuleIndex() const {
  return SnowStarParser::RuleType;
}

antlrcpp::Any SnowStarParser::TypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SnowStarParserVisitor*>(visitor))
    return parserVisitor->visitType(this);
  else
    return visitor->visitChildren(this);
}

SnowStarParser::TypeContext* SnowStarParser::type() {
  TypeContext *_localctx = _tracker.createInstance<TypeContext>(_ctx, getState());
  enterRule(_localctx, 20, SnowStarParser::RuleType);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(90);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << SnowStarParser::BOOLEAN)
      | (1ULL << SnowStarParser::CHAR)
      | (1ULL << SnowStarParser::INTEGER8)
      | (1ULL << SnowStarParser::INTEGER16)
      | (1ULL << SnowStarParser::INTEGER32)
      | (1ULL << SnowStarParser::INTEGER64)
      | (1ULL << SnowStarParser::REAL16)
      | (1ULL << SnowStarParser::REAL32)
      | (1ULL << SnowStarParser::REAL64)
      | (1ULL << SnowStarParser::VOID)
      | (1ULL << SnowStarParser::IDENTIFIER))) != 0))) {
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

//----------------- ErrorContext ------------------------------------------------------------------

SnowStarParser::ErrorContext::ErrorContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t SnowStarParser::ErrorContext::getRuleIndex() const {
  return SnowStarParser::RuleError;
}

antlrcpp::Any SnowStarParser::ErrorContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SnowStarParserVisitor*>(visitor))
    return parserVisitor->visitError(this);
  else
    return visitor->visitChildren(this);
}

SnowStarParser::ErrorContext* SnowStarParser::error() {
  ErrorContext *_localctx = _tracker.createInstance<ErrorContext>(_ctx, getState());
  enterRule(_localctx, 22, SnowStarParser::RuleError);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(92);
    matchWildcard();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

// Static vars and initialization.
std::vector<dfa::DFA> SnowStarParser::_decisionToDFA;
atn::PredictionContextCache SnowStarParser::_sharedContextCache;

// We own the ATN which in turn owns the ATN states.
atn::ATN SnowStarParser::_atn;
std::vector<uint16_t> SnowStarParser::_serializedATN;

std::vector<std::string> SnowStarParser::_ruleNames = {
  "compilationUnit", "statement", "expression", "assign", "define", "declare", 
  "declareNoID", "alias", "test", "literal", "type", "error"
};

std::vector<std::string> SnowStarParser::_literalNames = {
  "", "'bool'", "'char'", "'int8'", "'int16'", "'int32'", "'int64'", "'real16'", 
  "'real32'", "'real64'", "'void'", "'with'", "", "", "", "", "", "", "", 
  "'nil'", "'('", "')'", "'{'", "'}'", "'['", "']'", "';'", "','", "'.'", 
  "'='"
};

std::vector<std::string> SnowStarParser::_symbolicNames = {
  "", "BOOLEAN", "CHAR", "INTEGER8", "INTEGER16", "INTEGER32", "INTEGER64", 
  "REAL16", "REAL32", "REAL64", "VOID", "WITH", "DECIMAL_LITERAL", "HEX_LITERAL", 
  "BIN_LITERAL", "FLOAT_LITERAL", "BOOL_LITERAL", "CHAR_LITERAL", "STRING_LITERAL", 
  "NIL_LITERAL", "LPAREN", "RPAREN", "LBRACE", "RBRACE", "LBRACK", "RBRACK", 
  "SEMI", "COMMA", "DOT", "ASSIGN", "WS", "COMMENT", "LINE_COMMENT", "IDENTIFIER"
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
    0x3, 0x23, 0x61, 0x4, 0x2, 0x9, 0x2, 0x4, 0x3, 0x9, 0x3, 0x4, 0x4, 0x9, 
    0x4, 0x4, 0x5, 0x9, 0x5, 0x4, 0x6, 0x9, 0x6, 0x4, 0x7, 0x9, 0x7, 0x4, 
    0x8, 0x9, 0x8, 0x4, 0x9, 0x9, 0x9, 0x4, 0xa, 0x9, 0xa, 0x4, 0xb, 0x9, 
    0xb, 0x4, 0xc, 0x9, 0xc, 0x4, 0xd, 0x9, 0xd, 0x3, 0x2, 0x6, 0x2, 0x1c, 
    0xa, 0x2, 0xd, 0x2, 0xe, 0x2, 0x1d, 0x3, 0x3, 0x3, 0x3, 0x5, 0x3, 0x22, 
    0xa, 0x3, 0x3, 0x3, 0x3, 0x3, 0x5, 0x3, 0x26, 0xa, 0x3, 0x3, 0x3, 0x3, 
    0x3, 0x5, 0x3, 0x2a, 0xa, 0x3, 0x5, 0x3, 0x2c, 0xa, 0x3, 0x3, 0x4, 0x3, 
    0x4, 0x5, 0x4, 0x30, 0xa, 0x4, 0x3, 0x5, 0x3, 0x5, 0x5, 0x5, 0x34, 0xa, 
    0x5, 0x3, 0x5, 0x5, 0x5, 0x37, 0xa, 0x5, 0x3, 0x6, 0x3, 0x6, 0x5, 0x6, 
    0x3b, 0xa, 0x6, 0x3, 0x6, 0x5, 0x6, 0x3e, 0xa, 0x6, 0x3, 0x6, 0x5, 0x6, 
    0x41, 0xa, 0x6, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x8, 0x3, 0x8, 0x3, 
    0x9, 0x3, 0x9, 0x5, 0x9, 0x4a, 0xa, 0x9, 0x3, 0x9, 0x5, 0x9, 0x4d, 0xa, 
    0x9, 0x3, 0x9, 0x5, 0x9, 0x50, 0xa, 0x9, 0x3, 0xa, 0x5, 0xa, 0x53, 0xa, 
    0xa, 0x3, 0xa, 0x5, 0xa, 0x56, 0xa, 0xa, 0x3, 0xa, 0x5, 0xa, 0x59, 0xa, 
    0xa, 0x3, 0xb, 0x3, 0xb, 0x3, 0xc, 0x3, 0xc, 0x3, 0xd, 0x3, 0xd, 0x3, 
    0xd, 0x2, 0x2, 0xe, 0x2, 0x4, 0x6, 0x8, 0xa, 0xc, 0xe, 0x10, 0x12, 0x14, 
    0x16, 0x18, 0x2, 0x4, 0x4, 0x2, 0xe, 0x13, 0x15, 0x15, 0x4, 0x2, 0x3, 
    0xc, 0x23, 0x23, 0x2, 0x66, 0x2, 0x1b, 0x3, 0x2, 0x2, 0x2, 0x4, 0x2b, 
    0x3, 0x2, 0x2, 0x2, 0x6, 0x2f, 0x3, 0x2, 0x2, 0x2, 0x8, 0x31, 0x3, 0x2, 
    0x2, 0x2, 0xa, 0x3a, 0x3, 0x2, 0x2, 0x2, 0xc, 0x42, 0x3, 0x2, 0x2, 0x2, 
    0xe, 0x45, 0x3, 0x2, 0x2, 0x2, 0x10, 0x47, 0x3, 0x2, 0x2, 0x2, 0x12, 
    0x52, 0x3, 0x2, 0x2, 0x2, 0x14, 0x5a, 0x3, 0x2, 0x2, 0x2, 0x16, 0x5c, 
    0x3, 0x2, 0x2, 0x2, 0x18, 0x5e, 0x3, 0x2, 0x2, 0x2, 0x1a, 0x1c, 0x5, 
    0x4, 0x3, 0x2, 0x1b, 0x1a, 0x3, 0x2, 0x2, 0x2, 0x1c, 0x1d, 0x3, 0x2, 
    0x2, 0x2, 0x1d, 0x1b, 0x3, 0x2, 0x2, 0x2, 0x1d, 0x1e, 0x3, 0x2, 0x2, 
    0x2, 0x1e, 0x3, 0x3, 0x2, 0x2, 0x2, 0x1f, 0x21, 0x5, 0xc, 0x7, 0x2, 
    0x20, 0x22, 0x7, 0x1c, 0x2, 0x2, 0x21, 0x20, 0x3, 0x2, 0x2, 0x2, 0x21, 
    0x22, 0x3, 0x2, 0x2, 0x2, 0x22, 0x2c, 0x3, 0x2, 0x2, 0x2, 0x23, 0x25, 
    0x5, 0xa, 0x6, 0x2, 0x24, 0x26, 0x7, 0x1c, 0x2, 0x2, 0x25, 0x24, 0x3, 
    0x2, 0x2, 0x2, 0x25, 0x26, 0x3, 0x2, 0x2, 0x2, 0x26, 0x2c, 0x3, 0x2, 
    0x2, 0x2, 0x27, 0x29, 0x5, 0x10, 0x9, 0x2, 0x28, 0x2a, 0x7, 0x1c, 0x2, 
    0x2, 0x29, 0x28, 0x3, 0x2, 0x2, 0x2, 0x29, 0x2a, 0x3, 0x2, 0x2, 0x2, 
    0x2a, 0x2c, 0x3, 0x2, 0x2, 0x2, 0x2b, 0x1f, 0x3, 0x2, 0x2, 0x2, 0x2b, 
    0x23, 0x3, 0x2, 0x2, 0x2, 0x2b, 0x27, 0x3, 0x2, 0x2, 0x2, 0x2c, 0x5, 
    0x3, 0x2, 0x2, 0x2, 0x2d, 0x30, 0x7, 0x23, 0x2, 0x2, 0x2e, 0x30, 0x5, 
    0x14, 0xb, 0x2, 0x2f, 0x2d, 0x3, 0x2, 0x2, 0x2, 0x2f, 0x2e, 0x3, 0x2, 
    0x2, 0x2, 0x30, 0x7, 0x3, 0x2, 0x2, 0x2, 0x31, 0x33, 0x7, 0x23, 0x2, 
    0x2, 0x32, 0x34, 0x7, 0x1f, 0x2, 0x2, 0x33, 0x32, 0x3, 0x2, 0x2, 0x2, 
    0x33, 0x34, 0x3, 0x2, 0x2, 0x2, 0x34, 0x36, 0x3, 0x2, 0x2, 0x2, 0x35, 
    0x37, 0x5, 0x6, 0x4, 0x2, 0x36, 0x35, 0x3, 0x2, 0x2, 0x2, 0x36, 0x37, 
    0x3, 0x2, 0x2, 0x2, 0x37, 0x9, 0x3, 0x2, 0x2, 0x2, 0x38, 0x3b, 0x5, 
    0xc, 0x7, 0x2, 0x39, 0x3b, 0x5, 0xe, 0x8, 0x2, 0x3a, 0x38, 0x3, 0x2, 
    0x2, 0x2, 0x3a, 0x39, 0x3, 0x2, 0x2, 0x2, 0x3b, 0x3d, 0x3, 0x2, 0x2, 
    0x2, 0x3c, 0x3e, 0x7, 0x1f, 0x2, 0x2, 0x3d, 0x3c, 0x3, 0x2, 0x2, 0x2, 
    0x3d, 0x3e, 0x3, 0x2, 0x2, 0x2, 0x3e, 0x40, 0x3, 0x2, 0x2, 0x2, 0x3f, 
    0x41, 0x5, 0x6, 0x4, 0x2, 0x40, 0x3f, 0x3, 0x2, 0x2, 0x2, 0x40, 0x41, 
    0x3, 0x2, 0x2, 0x2, 0x41, 0xb, 0x3, 0x2, 0x2, 0x2, 0x42, 0x43, 0x5, 
    0x16, 0xc, 0x2, 0x43, 0x44, 0x7, 0x23, 0x2, 0x2, 0x44, 0xd, 0x3, 0x2, 
    0x2, 0x2, 0x45, 0x46, 0x5, 0x16, 0xc, 0x2, 0x46, 0xf, 0x3, 0x2, 0x2, 
    0x2, 0x47, 0x49, 0x7, 0xd, 0x2, 0x2, 0x48, 0x4a, 0x7, 0x23, 0x2, 0x2, 
    0x49, 0x48, 0x3, 0x2, 0x2, 0x2, 0x49, 0x4a, 0x3, 0x2, 0x2, 0x2, 0x4a, 
    0x4c, 0x3, 0x2, 0x2, 0x2, 0x4b, 0x4d, 0x7, 0x1f, 0x2, 0x2, 0x4c, 0x4b, 
    0x3, 0x2, 0x2, 0x2, 0x4c, 0x4d, 0x3, 0x2, 0x2, 0x2, 0x4d, 0x4f, 0x3, 
    0x2, 0x2, 0x2, 0x4e, 0x50, 0x5, 0x16, 0xc, 0x2, 0x4f, 0x4e, 0x3, 0x2, 
    0x2, 0x2, 0x4f, 0x50, 0x3, 0x2, 0x2, 0x2, 0x50, 0x11, 0x3, 0x2, 0x2, 
    0x2, 0x51, 0x53, 0x7, 0x1f, 0x2, 0x2, 0x52, 0x51, 0x3, 0x2, 0x2, 0x2, 
    0x52, 0x53, 0x3, 0x2, 0x2, 0x2, 0x53, 0x55, 0x3, 0x2, 0x2, 0x2, 0x54, 
    0x56, 0x7, 0x23, 0x2, 0x2, 0x55, 0x54, 0x3, 0x2, 0x2, 0x2, 0x55, 0x56, 
    0x3, 0x2, 0x2, 0x2, 0x56, 0x58, 0x3, 0x2, 0x2, 0x2, 0x57, 0x59, 0x7, 
    0x1c, 0x2, 0x2, 0x58, 0x57, 0x3, 0x2, 0x2, 0x2, 0x58, 0x59, 0x3, 0x2, 
    0x2, 0x2, 0x59, 0x13, 0x3, 0x2, 0x2, 0x2, 0x5a, 0x5b, 0x9, 0x2, 0x2, 
    0x2, 0x5b, 0x15, 0x3, 0x2, 0x2, 0x2, 0x5c, 0x5d, 0x9, 0x3, 0x2, 0x2, 
    0x5d, 0x17, 0x3, 0x2, 0x2, 0x2, 0x5e, 0x5f, 0xb, 0x2, 0x2, 0x2, 0x5f, 
    0x19, 0x3, 0x2, 0x2, 0x2, 0x13, 0x1d, 0x21, 0x25, 0x29, 0x2b, 0x2f, 
    0x33, 0x36, 0x3a, 0x3d, 0x40, 0x49, 0x4c, 0x4f, 0x52, 0x55, 0x58, 
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
