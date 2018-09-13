
// Generated from SnowStar.g4 by ANTLR 4.7.1


#include "SnowStarVisitor.h"

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
  return "SnowStar.g4";
}

const std::vector<std::string>& SnowStarParser::getRuleNames() const {
  return _ruleNames;
}

dfa::Vocabulary& SnowStarParser::getVocabulary() const {
  return _vocabulary;
}


//----------------- ProgramContext ------------------------------------------------------------------

SnowStarParser::ProgramContext::ProgramContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<SnowStarParser::StatementContext *> SnowStarParser::ProgramContext::statement() {
  return getRuleContexts<SnowStarParser::StatementContext>();
}

SnowStarParser::StatementContext* SnowStarParser::ProgramContext::statement(size_t i) {
  return getRuleContext<SnowStarParser::StatementContext>(i);
}


size_t SnowStarParser::ProgramContext::getRuleIndex() const {
  return SnowStarParser::RuleProgram;
}

antlrcpp::Any SnowStarParser::ProgramContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SnowStarVisitor*>(visitor))
    return parserVisitor->visitProgram(this);
  else
    return visitor->visitChildren(this);
}

SnowStarParser::ProgramContext* SnowStarParser::program() {
  ProgramContext *_localctx = _tracker.createInstance<ProgramContext>(_ctx, getState());
  enterRule(_localctx, 0, SnowStarParser::RuleProgram);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(13); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(12);
      statement();
      setState(15); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while (_la == SnowStarParser::T__0);
   
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

tree::TerminalNode* SnowStarParser::StatementContext::NewLine() {
  return getToken(SnowStarParser::NewLine, 0);
}

SnowStarParser::DefineContext* SnowStarParser::StatementContext::define() {
  return getRuleContext<SnowStarParser::DefineContext>(0);
}


size_t SnowStarParser::StatementContext::getRuleIndex() const {
  return SnowStarParser::RuleStatement;
}

antlrcpp::Any SnowStarParser::StatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SnowStarVisitor*>(visitor))
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
    setState(25);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 3, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(17);
      declare();
      setState(19);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == SnowStarParser::NewLine) {
        setState(18);
        match(SnowStarParser::NewLine);
      }
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(21);
      define();
      setState(23);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == SnowStarParser::NewLine) {
        setState(22);
        match(SnowStarParser::NewLine);
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

//----------------- ValueContext ------------------------------------------------------------------

SnowStarParser::ValueContext::ValueContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* SnowStarParser::ValueContext::Integer() {
  return getToken(SnowStarParser::Integer, 0);
}

tree::TerminalNode* SnowStarParser::ValueContext::Real() {
  return getToken(SnowStarParser::Real, 0);
}

tree::TerminalNode* SnowStarParser::ValueContext::Boolean() {
  return getToken(SnowStarParser::Boolean, 0);
}

tree::TerminalNode* SnowStarParser::ValueContext::Character() {
  return getToken(SnowStarParser::Character, 0);
}

tree::TerminalNode* SnowStarParser::ValueContext::String() {
  return getToken(SnowStarParser::String, 0);
}

tree::TerminalNode* SnowStarParser::ValueContext::Null() {
  return getToken(SnowStarParser::Null, 0);
}

tree::TerminalNode* SnowStarParser::ValueContext::Identifier() {
  return getToken(SnowStarParser::Identifier, 0);
}

SnowStarParser::CastContext* SnowStarParser::ValueContext::cast() {
  return getRuleContext<SnowStarParser::CastContext>(0);
}


size_t SnowStarParser::ValueContext::getRuleIndex() const {
  return SnowStarParser::RuleValue;
}

antlrcpp::Any SnowStarParser::ValueContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SnowStarVisitor*>(visitor))
    return parserVisitor->visitValue(this);
  else
    return visitor->visitChildren(this);
}

SnowStarParser::ValueContext* SnowStarParser::value() {
  ValueContext *_localctx = _tracker.createInstance<ValueContext>(_ctx, getState());
  enterRule(_localctx, 4, SnowStarParser::RuleValue);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(35);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case SnowStarParser::Integer: {
        enterOuterAlt(_localctx, 1);
        setState(27);
        match(SnowStarParser::Integer);
        break;
      }

      case SnowStarParser::Real: {
        enterOuterAlt(_localctx, 2);
        setState(28);
        match(SnowStarParser::Real);
        break;
      }

      case SnowStarParser::Boolean: {
        enterOuterAlt(_localctx, 3);
        setState(29);
        match(SnowStarParser::Boolean);
        break;
      }

      case SnowStarParser::Character: {
        enterOuterAlt(_localctx, 4);
        setState(30);
        match(SnowStarParser::Character);
        break;
      }

      case SnowStarParser::String: {
        enterOuterAlt(_localctx, 5);
        setState(31);
        match(SnowStarParser::String);
        break;
      }

      case SnowStarParser::Null: {
        enterOuterAlt(_localctx, 6);
        setState(32);
        match(SnowStarParser::Null);
        break;
      }

      case SnowStarParser::Identifier: {
        enterOuterAlt(_localctx, 7);
        setState(33);
        match(SnowStarParser::Identifier);
        break;
      }

      case SnowStarParser::LPAR: {
        enterOuterAlt(_localctx, 8);
        setState(34);
        cast();
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

//----------------- DeclareContext ------------------------------------------------------------------

SnowStarParser::DeclareContext::DeclareContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> SnowStarParser::DeclareContext::Identifier() {
  return getTokens(SnowStarParser::Identifier);
}

tree::TerminalNode* SnowStarParser::DeclareContext::Identifier(size_t i) {
  return getToken(SnowStarParser::Identifier, i);
}

tree::TerminalNode* SnowStarParser::DeclareContext::Type() {
  return getToken(SnowStarParser::Type, 0);
}


size_t SnowStarParser::DeclareContext::getRuleIndex() const {
  return SnowStarParser::RuleDeclare;
}

antlrcpp::Any SnowStarParser::DeclareContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SnowStarVisitor*>(visitor))
    return parserVisitor->visitDeclare(this);
  else
    return visitor->visitChildren(this);
}

SnowStarParser::DeclareContext* SnowStarParser::declare() {
  DeclareContext *_localctx = _tracker.createInstance<DeclareContext>(_ctx, getState());
  enterRule(_localctx, 6, SnowStarParser::RuleDeclare);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(37);
    match(SnowStarParser::T__0);
    setState(38);
    match(SnowStarParser::Identifier);
    setState(43);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == SnowStarParser::T__1) {
      setState(39);
      match(SnowStarParser::T__1);
      setState(40);
      match(SnowStarParser::Identifier);
      setState(45);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(46);
    match(SnowStarParser::T__2);
    setState(47);
    match(SnowStarParser::Type);
   
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

std::vector<SnowStarParser::ValueContext *> SnowStarParser::DefineContext::value() {
  return getRuleContexts<SnowStarParser::ValueContext>();
}

SnowStarParser::ValueContext* SnowStarParser::DefineContext::value(size_t i) {
  return getRuleContext<SnowStarParser::ValueContext>(i);
}


size_t SnowStarParser::DefineContext::getRuleIndex() const {
  return SnowStarParser::RuleDefine;
}

antlrcpp::Any SnowStarParser::DefineContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SnowStarVisitor*>(visitor))
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
    setState(49);
    declare();
    setState(50);
    match(SnowStarParser::T__3);
    setState(51);
    value();
    setState(56);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == SnowStarParser::T__1) {
      setState(52);
      match(SnowStarParser::T__1);
      setState(53);
      value();
      setState(58);
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

//----------------- CastContext ------------------------------------------------------------------

SnowStarParser::CastContext::CastContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* SnowStarParser::CastContext::LPAR() {
  return getToken(SnowStarParser::LPAR, 0);
}

tree::TerminalNode* SnowStarParser::CastContext::Type() {
  return getToken(SnowStarParser::Type, 0);
}

tree::TerminalNode* SnowStarParser::CastContext::RPAR() {
  return getToken(SnowStarParser::RPAR, 0);
}

SnowStarParser::ValueContext* SnowStarParser::CastContext::value() {
  return getRuleContext<SnowStarParser::ValueContext>(0);
}


size_t SnowStarParser::CastContext::getRuleIndex() const {
  return SnowStarParser::RuleCast;
}

antlrcpp::Any SnowStarParser::CastContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SnowStarVisitor*>(visitor))
    return parserVisitor->visitCast(this);
  else
    return visitor->visitChildren(this);
}

SnowStarParser::CastContext* SnowStarParser::cast() {
  CastContext *_localctx = _tracker.createInstance<CastContext>(_ctx, getState());
  enterRule(_localctx, 10, SnowStarParser::RuleCast);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(59);
    match(SnowStarParser::LPAR);
    setState(60);
    match(SnowStarParser::Type);
    setState(61);
    match(SnowStarParser::RPAR);
    setState(62);
    value();
   
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
  "program", "statement", "value", "declare", "define", "cast"
};

std::vector<std::string> SnowStarParser::_literalNames = {
  "", "'decl'", "','", "':'", "'='", "", "", "", "", "", "", "'nil'", "", 
  "", "", "", "", "'('", "')'", "'{'", "'}'"
};

std::vector<std::string> SnowStarParser::_symbolicNames = {
  "", "", "", "", "", "Type", "Integer", "Real", "Boolean", "Character", 
  "String", "Null", "Identifier", "WhiteSpace", "Comment", "MultiLine_Comment", 
  "NewLine", "LPAR", "RPAR", "LBCK", "RBCK"
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
    0x3, 0x16, 0x43, 0x4, 0x2, 0x9, 0x2, 0x4, 0x3, 0x9, 0x3, 0x4, 0x4, 0x9, 
    0x4, 0x4, 0x5, 0x9, 0x5, 0x4, 0x6, 0x9, 0x6, 0x4, 0x7, 0x9, 0x7, 0x3, 
    0x2, 0x6, 0x2, 0x10, 0xa, 0x2, 0xd, 0x2, 0xe, 0x2, 0x11, 0x3, 0x3, 0x3, 
    0x3, 0x5, 0x3, 0x16, 0xa, 0x3, 0x3, 0x3, 0x3, 0x3, 0x5, 0x3, 0x1a, 0xa, 
    0x3, 0x5, 0x3, 0x1c, 0xa, 0x3, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 
    0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x5, 0x4, 0x26, 0xa, 0x4, 0x3, 
    0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x7, 0x5, 0x2c, 0xa, 0x5, 0xc, 0x5, 
    0xe, 0x5, 0x2f, 0xb, 0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x6, 0x3, 
    0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x7, 0x6, 0x39, 0xa, 0x6, 0xc, 0x6, 
    0xe, 0x6, 0x3c, 0xb, 0x6, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 
    0x7, 0x3, 0x7, 0x2, 0x2, 0x8, 0x2, 0x4, 0x6, 0x8, 0xa, 0xc, 0x2, 0x2, 
    0x2, 0x49, 0x2, 0xf, 0x3, 0x2, 0x2, 0x2, 0x4, 0x1b, 0x3, 0x2, 0x2, 0x2, 
    0x6, 0x25, 0x3, 0x2, 0x2, 0x2, 0x8, 0x27, 0x3, 0x2, 0x2, 0x2, 0xa, 0x33, 
    0x3, 0x2, 0x2, 0x2, 0xc, 0x3d, 0x3, 0x2, 0x2, 0x2, 0xe, 0x10, 0x5, 0x4, 
    0x3, 0x2, 0xf, 0xe, 0x3, 0x2, 0x2, 0x2, 0x10, 0x11, 0x3, 0x2, 0x2, 0x2, 
    0x11, 0xf, 0x3, 0x2, 0x2, 0x2, 0x11, 0x12, 0x3, 0x2, 0x2, 0x2, 0x12, 
    0x3, 0x3, 0x2, 0x2, 0x2, 0x13, 0x15, 0x5, 0x8, 0x5, 0x2, 0x14, 0x16, 
    0x7, 0x12, 0x2, 0x2, 0x15, 0x14, 0x3, 0x2, 0x2, 0x2, 0x15, 0x16, 0x3, 
    0x2, 0x2, 0x2, 0x16, 0x1c, 0x3, 0x2, 0x2, 0x2, 0x17, 0x19, 0x5, 0xa, 
    0x6, 0x2, 0x18, 0x1a, 0x7, 0x12, 0x2, 0x2, 0x19, 0x18, 0x3, 0x2, 0x2, 
    0x2, 0x19, 0x1a, 0x3, 0x2, 0x2, 0x2, 0x1a, 0x1c, 0x3, 0x2, 0x2, 0x2, 
    0x1b, 0x13, 0x3, 0x2, 0x2, 0x2, 0x1b, 0x17, 0x3, 0x2, 0x2, 0x2, 0x1c, 
    0x5, 0x3, 0x2, 0x2, 0x2, 0x1d, 0x26, 0x7, 0x8, 0x2, 0x2, 0x1e, 0x26, 
    0x7, 0x9, 0x2, 0x2, 0x1f, 0x26, 0x7, 0xa, 0x2, 0x2, 0x20, 0x26, 0x7, 
    0xb, 0x2, 0x2, 0x21, 0x26, 0x7, 0xc, 0x2, 0x2, 0x22, 0x26, 0x7, 0xd, 
    0x2, 0x2, 0x23, 0x26, 0x7, 0xe, 0x2, 0x2, 0x24, 0x26, 0x5, 0xc, 0x7, 
    0x2, 0x25, 0x1d, 0x3, 0x2, 0x2, 0x2, 0x25, 0x1e, 0x3, 0x2, 0x2, 0x2, 
    0x25, 0x1f, 0x3, 0x2, 0x2, 0x2, 0x25, 0x20, 0x3, 0x2, 0x2, 0x2, 0x25, 
    0x21, 0x3, 0x2, 0x2, 0x2, 0x25, 0x22, 0x3, 0x2, 0x2, 0x2, 0x25, 0x23, 
    0x3, 0x2, 0x2, 0x2, 0x25, 0x24, 0x3, 0x2, 0x2, 0x2, 0x26, 0x7, 0x3, 
    0x2, 0x2, 0x2, 0x27, 0x28, 0x7, 0x3, 0x2, 0x2, 0x28, 0x2d, 0x7, 0xe, 
    0x2, 0x2, 0x29, 0x2a, 0x7, 0x4, 0x2, 0x2, 0x2a, 0x2c, 0x7, 0xe, 0x2, 
    0x2, 0x2b, 0x29, 0x3, 0x2, 0x2, 0x2, 0x2c, 0x2f, 0x3, 0x2, 0x2, 0x2, 
    0x2d, 0x2b, 0x3, 0x2, 0x2, 0x2, 0x2d, 0x2e, 0x3, 0x2, 0x2, 0x2, 0x2e, 
    0x30, 0x3, 0x2, 0x2, 0x2, 0x2f, 0x2d, 0x3, 0x2, 0x2, 0x2, 0x30, 0x31, 
    0x7, 0x5, 0x2, 0x2, 0x31, 0x32, 0x7, 0x7, 0x2, 0x2, 0x32, 0x9, 0x3, 
    0x2, 0x2, 0x2, 0x33, 0x34, 0x5, 0x8, 0x5, 0x2, 0x34, 0x35, 0x7, 0x6, 
    0x2, 0x2, 0x35, 0x3a, 0x5, 0x6, 0x4, 0x2, 0x36, 0x37, 0x7, 0x4, 0x2, 
    0x2, 0x37, 0x39, 0x5, 0x6, 0x4, 0x2, 0x38, 0x36, 0x3, 0x2, 0x2, 0x2, 
    0x39, 0x3c, 0x3, 0x2, 0x2, 0x2, 0x3a, 0x38, 0x3, 0x2, 0x2, 0x2, 0x3a, 
    0x3b, 0x3, 0x2, 0x2, 0x2, 0x3b, 0xb, 0x3, 0x2, 0x2, 0x2, 0x3c, 0x3a, 
    0x3, 0x2, 0x2, 0x2, 0x3d, 0x3e, 0x7, 0x13, 0x2, 0x2, 0x3e, 0x3f, 0x7, 
    0x7, 0x2, 0x2, 0x3f, 0x40, 0x7, 0x14, 0x2, 0x2, 0x40, 0x41, 0x5, 0x6, 
    0x4, 0x2, 0x41, 0xd, 0x3, 0x2, 0x2, 0x2, 0x9, 0x11, 0x15, 0x19, 0x1b, 
    0x25, 0x2d, 0x3a, 
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
