
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
    setState(21); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(20);
      statement();
      setState(23); 
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
    setState(33);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 3, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(25);
      declare();
      setState(27);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == SnowStarParser::SEMI) {
        setState(26);
        dynamic_cast<StatementContext *>(_localctx)->eol = match(SnowStarParser::SEMI);
      }
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(29);
      define();
      setState(31);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == SnowStarParser::SEMI) {
        setState(30);
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
    setState(37);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case SnowStarParser::IDENTIFIER: {
        enterOuterAlt(_localctx, 1);
        setState(35);
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
        setState(36);
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
    setState(39);
    match(SnowStarParser::IDENTIFIER);
    setState(41);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == SnowStarParser::ASSIGN) {
      setState(40);
      dynamic_cast<AssignContext *>(_localctx)->eop = match(SnowStarParser::ASSIGN);
    }
    setState(44);
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
      setState(43);
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
    setState(48);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 7, _ctx)) {
    case 1: {
      setState(46);
      declare();
      break;
    }

    case 2: {
      setState(47);
      declareNoID();
      break;
    }

    }
    setState(51);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == SnowStarParser::ASSIGN) {
      setState(50);
      dynamic_cast<DefineContext *>(_localctx)->eop = match(SnowStarParser::ASSIGN);
    }
    setState(54);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 9, _ctx)) {
    case 1: {
      setState(53);
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
    setState(56);
    type();
    setState(57);
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
    setState(59);
    type();
   
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
  enterRule(_localctx, 14, SnowStarParser::RuleLiteral);
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
  enterRule(_localctx, 16, SnowStarParser::RuleType);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(63);
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
  enterRule(_localctx, 18, SnowStarParser::RuleError);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(65);
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
  "declareNoID", "literal", "type", "error"
};

std::vector<std::string> SnowStarParser::_literalNames = {
  "", "'bool'", "'char'", "'int8'", "'int16'", "'int32'", "'int64'", "'real16'", 
  "'real32'", "'real64'", "'void'", "", "", "", "", "", "", "", "'nil'", 
  "'('", "')'", "'{'", "'}'", "'['", "']'", "';'", "','", "'.'", "'='"
};

std::vector<std::string> SnowStarParser::_symbolicNames = {
  "", "BOOLEAN", "CHAR", "INTEGER8", "INTEGER16", "INTEGER32", "INTEGER64", 
  "REAL16", "REAL32", "REAL64", "VOID", "DECIMAL_LITERAL", "HEX_LITERAL", 
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
    0x3, 0x22, 0x46, 0x4, 0x2, 0x9, 0x2, 0x4, 0x3, 0x9, 0x3, 0x4, 0x4, 0x9, 
    0x4, 0x4, 0x5, 0x9, 0x5, 0x4, 0x6, 0x9, 0x6, 0x4, 0x7, 0x9, 0x7, 0x4, 
    0x8, 0x9, 0x8, 0x4, 0x9, 0x9, 0x9, 0x4, 0xa, 0x9, 0xa, 0x4, 0xb, 0x9, 
    0xb, 0x3, 0x2, 0x6, 0x2, 0x18, 0xa, 0x2, 0xd, 0x2, 0xe, 0x2, 0x19, 0x3, 
    0x3, 0x3, 0x3, 0x5, 0x3, 0x1e, 0xa, 0x3, 0x3, 0x3, 0x3, 0x3, 0x5, 0x3, 
    0x22, 0xa, 0x3, 0x5, 0x3, 0x24, 0xa, 0x3, 0x3, 0x4, 0x3, 0x4, 0x5, 0x4, 
    0x28, 0xa, 0x4, 0x3, 0x5, 0x3, 0x5, 0x5, 0x5, 0x2c, 0xa, 0x5, 0x3, 0x5, 
    0x5, 0x5, 0x2f, 0xa, 0x5, 0x3, 0x6, 0x3, 0x6, 0x5, 0x6, 0x33, 0xa, 0x6, 
    0x3, 0x6, 0x5, 0x6, 0x36, 0xa, 0x6, 0x3, 0x6, 0x5, 0x6, 0x39, 0xa, 0x6, 
    0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x8, 0x3, 0x8, 0x3, 0x9, 0x3, 0x9, 
    0x3, 0xa, 0x3, 0xa, 0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 0x2, 0x2, 0xc, 0x2, 
    0x4, 0x6, 0x8, 0xa, 0xc, 0xe, 0x10, 0x12, 0x14, 0x2, 0x4, 0x4, 0x2, 
    0xd, 0x12, 0x14, 0x14, 0x4, 0x2, 0x3, 0xc, 0x22, 0x22, 0x2, 0x45, 0x2, 
    0x17, 0x3, 0x2, 0x2, 0x2, 0x4, 0x23, 0x3, 0x2, 0x2, 0x2, 0x6, 0x27, 
    0x3, 0x2, 0x2, 0x2, 0x8, 0x29, 0x3, 0x2, 0x2, 0x2, 0xa, 0x32, 0x3, 0x2, 
    0x2, 0x2, 0xc, 0x3a, 0x3, 0x2, 0x2, 0x2, 0xe, 0x3d, 0x3, 0x2, 0x2, 0x2, 
    0x10, 0x3f, 0x3, 0x2, 0x2, 0x2, 0x12, 0x41, 0x3, 0x2, 0x2, 0x2, 0x14, 
    0x43, 0x3, 0x2, 0x2, 0x2, 0x16, 0x18, 0x5, 0x4, 0x3, 0x2, 0x17, 0x16, 
    0x3, 0x2, 0x2, 0x2, 0x18, 0x19, 0x3, 0x2, 0x2, 0x2, 0x19, 0x17, 0x3, 
    0x2, 0x2, 0x2, 0x19, 0x1a, 0x3, 0x2, 0x2, 0x2, 0x1a, 0x3, 0x3, 0x2, 
    0x2, 0x2, 0x1b, 0x1d, 0x5, 0xc, 0x7, 0x2, 0x1c, 0x1e, 0x7, 0x1b, 0x2, 
    0x2, 0x1d, 0x1c, 0x3, 0x2, 0x2, 0x2, 0x1d, 0x1e, 0x3, 0x2, 0x2, 0x2, 
    0x1e, 0x24, 0x3, 0x2, 0x2, 0x2, 0x1f, 0x21, 0x5, 0xa, 0x6, 0x2, 0x20, 
    0x22, 0x7, 0x1b, 0x2, 0x2, 0x21, 0x20, 0x3, 0x2, 0x2, 0x2, 0x21, 0x22, 
    0x3, 0x2, 0x2, 0x2, 0x22, 0x24, 0x3, 0x2, 0x2, 0x2, 0x23, 0x1b, 0x3, 
    0x2, 0x2, 0x2, 0x23, 0x1f, 0x3, 0x2, 0x2, 0x2, 0x24, 0x5, 0x3, 0x2, 
    0x2, 0x2, 0x25, 0x28, 0x7, 0x22, 0x2, 0x2, 0x26, 0x28, 0x5, 0x10, 0x9, 
    0x2, 0x27, 0x25, 0x3, 0x2, 0x2, 0x2, 0x27, 0x26, 0x3, 0x2, 0x2, 0x2, 
    0x28, 0x7, 0x3, 0x2, 0x2, 0x2, 0x29, 0x2b, 0x7, 0x22, 0x2, 0x2, 0x2a, 
    0x2c, 0x7, 0x1e, 0x2, 0x2, 0x2b, 0x2a, 0x3, 0x2, 0x2, 0x2, 0x2b, 0x2c, 
    0x3, 0x2, 0x2, 0x2, 0x2c, 0x2e, 0x3, 0x2, 0x2, 0x2, 0x2d, 0x2f, 0x5, 
    0x6, 0x4, 0x2, 0x2e, 0x2d, 0x3, 0x2, 0x2, 0x2, 0x2e, 0x2f, 0x3, 0x2, 
    0x2, 0x2, 0x2f, 0x9, 0x3, 0x2, 0x2, 0x2, 0x30, 0x33, 0x5, 0xc, 0x7, 
    0x2, 0x31, 0x33, 0x5, 0xe, 0x8, 0x2, 0x32, 0x30, 0x3, 0x2, 0x2, 0x2, 
    0x32, 0x31, 0x3, 0x2, 0x2, 0x2, 0x33, 0x35, 0x3, 0x2, 0x2, 0x2, 0x34, 
    0x36, 0x7, 0x1e, 0x2, 0x2, 0x35, 0x34, 0x3, 0x2, 0x2, 0x2, 0x35, 0x36, 
    0x3, 0x2, 0x2, 0x2, 0x36, 0x38, 0x3, 0x2, 0x2, 0x2, 0x37, 0x39, 0x5, 
    0x6, 0x4, 0x2, 0x38, 0x37, 0x3, 0x2, 0x2, 0x2, 0x38, 0x39, 0x3, 0x2, 
    0x2, 0x2, 0x39, 0xb, 0x3, 0x2, 0x2, 0x2, 0x3a, 0x3b, 0x5, 0x12, 0xa, 
    0x2, 0x3b, 0x3c, 0x7, 0x22, 0x2, 0x2, 0x3c, 0xd, 0x3, 0x2, 0x2, 0x2, 
    0x3d, 0x3e, 0x5, 0x12, 0xa, 0x2, 0x3e, 0xf, 0x3, 0x2, 0x2, 0x2, 0x3f, 
    0x40, 0x9, 0x2, 0x2, 0x2, 0x40, 0x11, 0x3, 0x2, 0x2, 0x2, 0x41, 0x42, 
    0x9, 0x3, 0x2, 0x2, 0x42, 0x13, 0x3, 0x2, 0x2, 0x2, 0x43, 0x44, 0xb, 
    0x2, 0x2, 0x2, 0x44, 0x15, 0x3, 0x2, 0x2, 0x2, 0xc, 0x19, 0x1d, 0x21, 
    0x23, 0x27, 0x2b, 0x2e, 0x32, 0x35, 0x38, 
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
