
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

tree::TerminalNode* SnowStarParser::CompilationUnitContext::EOF() {
  return getToken(SnowStarParser::EOF, 0);
}

std::vector<SnowStarParser::DeclarationSeqContext *> SnowStarParser::CompilationUnitContext::declarationSeq() {
  return getRuleContexts<SnowStarParser::DeclarationSeqContext>();
}

SnowStarParser::DeclarationSeqContext* SnowStarParser::CompilationUnitContext::declarationSeq(size_t i) {
  return getRuleContext<SnowStarParser::DeclarationSeqContext>(i);
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
    setState(55);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << SnowStarParser::BOOL)
      | (1ULL << SnowStarParser::CHR)
      | (1ULL << SnowStarParser::I8)
      | (1ULL << SnowStarParser::UI8)
      | (1ULL << SnowStarParser::I16)
      | (1ULL << SnowStarParser::UI16)
      | (1ULL << SnowStarParser::I32)
      | (1ULL << SnowStarParser::UI32)
      | (1ULL << SnowStarParser::I64)
      | (1ULL << SnowStarParser::UI64)
      | (1ULL << SnowStarParser::F32)
      | (1ULL << SnowStarParser::F64)
      | (1ULL << SnowStarParser::STR)
      | (1ULL << SnowStarParser::VOID)
      | (1ULL << SnowStarParser::WITH)
      | (1ULL << SnowStarParser::UNIT)
      | (1ULL << SnowStarParser::DTYPE)
      | (1ULL << SnowStarParser::IMPORT)
      | (1ULL << SnowStarParser::SEMI))) != 0) || _la == SnowStarParser::IDENTIFIER) {
      setState(52);
      declarationSeq();
      setState(57);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(58);
    match(SnowStarParser::EOF);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- DeclarationSeqContext ------------------------------------------------------------------

SnowStarParser::DeclarationSeqContext::DeclarationSeqContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

SnowStarParser::FunctionDeclarationContext* SnowStarParser::DeclarationSeqContext::functionDeclaration() {
  return getRuleContext<SnowStarParser::FunctionDeclarationContext>(0);
}

SnowStarParser::VariableDeclarationContext* SnowStarParser::DeclarationSeqContext::variableDeclaration() {
  return getRuleContext<SnowStarParser::VariableDeclarationContext>(0);
}

SnowStarParser::UnitDeclarationContext* SnowStarParser::DeclarationSeqContext::unitDeclaration() {
  return getRuleContext<SnowStarParser::UnitDeclarationContext>(0);
}

SnowStarParser::DtypeDeclarationContext* SnowStarParser::DeclarationSeqContext::dtypeDeclaration() {
  return getRuleContext<SnowStarParser::DtypeDeclarationContext>(0);
}

SnowStarParser::WithDeclarationContext* SnowStarParser::DeclarationSeqContext::withDeclaration() {
  return getRuleContext<SnowStarParser::WithDeclarationContext>(0);
}

SnowStarParser::ImportDeclarationContext* SnowStarParser::DeclarationSeqContext::importDeclaration() {
  return getRuleContext<SnowStarParser::ImportDeclarationContext>(0);
}

SnowStarParser::EmptyDeclarationContext* SnowStarParser::DeclarationSeqContext::emptyDeclaration() {
  return getRuleContext<SnowStarParser::EmptyDeclarationContext>(0);
}


size_t SnowStarParser::DeclarationSeqContext::getRuleIndex() const {
  return SnowStarParser::RuleDeclarationSeq;
}

antlrcpp::Any SnowStarParser::DeclarationSeqContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SnowStarParserVisitor*>(visitor))
    return parserVisitor->visitDeclarationSeq(this);
  else
    return visitor->visitChildren(this);
}

SnowStarParser::DeclarationSeqContext* SnowStarParser::declarationSeq() {
  DeclarationSeqContext *_localctx = _tracker.createInstance<DeclarationSeqContext>(_ctx, getState());
  enterRule(_localctx, 2, SnowStarParser::RuleDeclarationSeq);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(67);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 1, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(60);
      functionDeclaration();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(61);
      variableDeclaration();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(62);
      unitDeclaration();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(63);
      dtypeDeclaration();
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(64);
      withDeclaration();
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(65);
      importDeclaration();
      break;
    }

    case 7: {
      enterOuterAlt(_localctx, 7);
      setState(66);
      emptyDeclaration();
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

//----------------- VariableDeclarationContext ------------------------------------------------------------------

SnowStarParser::VariableDeclarationContext::VariableDeclarationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

SnowStarParser::TheTypeContext* SnowStarParser::VariableDeclarationContext::theType() {
  return getRuleContext<SnowStarParser::TheTypeContext>(0);
}

SnowStarParser::VariableNameContext* SnowStarParser::VariableDeclarationContext::variableName() {
  return getRuleContext<SnowStarParser::VariableNameContext>(0);
}

tree::TerminalNode* SnowStarParser::VariableDeclarationContext::SEMI() {
  return getToken(SnowStarParser::SEMI, 0);
}

SnowStarParser::VariableInitializerContext* SnowStarParser::VariableDeclarationContext::variableInitializer() {
  return getRuleContext<SnowStarParser::VariableInitializerContext>(0);
}


size_t SnowStarParser::VariableDeclarationContext::getRuleIndex() const {
  return SnowStarParser::RuleVariableDeclaration;
}

antlrcpp::Any SnowStarParser::VariableDeclarationContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SnowStarParserVisitor*>(visitor))
    return parserVisitor->visitVariableDeclaration(this);
  else
    return visitor->visitChildren(this);
}

SnowStarParser::VariableDeclarationContext* SnowStarParser::variableDeclaration() {
  VariableDeclarationContext *_localctx = _tracker.createInstance<VariableDeclarationContext>(_ctx, getState());
  enterRule(_localctx, 4, SnowStarParser::RuleVariableDeclaration);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(69);
    theType();
    setState(70);
    variableName();
    setState(72);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == SnowStarParser::ASSIGN) {
      setState(71);
      variableInitializer();
    }
    setState(74);
    match(SnowStarParser::SEMI);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- VariableNameContext ------------------------------------------------------------------

SnowStarParser::VariableNameContext::VariableNameContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* SnowStarParser::VariableNameContext::IDENTIFIER() {
  return getToken(SnowStarParser::IDENTIFIER, 0);
}


size_t SnowStarParser::VariableNameContext::getRuleIndex() const {
  return SnowStarParser::RuleVariableName;
}

antlrcpp::Any SnowStarParser::VariableNameContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SnowStarParserVisitor*>(visitor))
    return parserVisitor->visitVariableName(this);
  else
    return visitor->visitChildren(this);
}

SnowStarParser::VariableNameContext* SnowStarParser::variableName() {
  VariableNameContext *_localctx = _tracker.createInstance<VariableNameContext>(_ctx, getState());
  enterRule(_localctx, 6, SnowStarParser::RuleVariableName);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(76);
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

tree::TerminalNode* SnowStarParser::VariableInitializerContext::ASSIGN() {
  return getToken(SnowStarParser::ASSIGN, 0);
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
  enterRule(_localctx, 8, SnowStarParser::RuleVariableInitializer);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(78);
    match(SnowStarParser::ASSIGN);
    setState(79);
    expression(0);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- UnitDeclarationContext ------------------------------------------------------------------

SnowStarParser::UnitDeclarationContext::UnitDeclarationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* SnowStarParser::UnitDeclarationContext::UNIT() {
  return getToken(SnowStarParser::UNIT, 0);
}

SnowStarParser::UnitNameContext* SnowStarParser::UnitDeclarationContext::unitName() {
  return getRuleContext<SnowStarParser::UnitNameContext>(0);
}

SnowStarParser::BasicBlockDeclarationContext* SnowStarParser::UnitDeclarationContext::basicBlockDeclaration() {
  return getRuleContext<SnowStarParser::BasicBlockDeclarationContext>(0);
}


size_t SnowStarParser::UnitDeclarationContext::getRuleIndex() const {
  return SnowStarParser::RuleUnitDeclaration;
}

antlrcpp::Any SnowStarParser::UnitDeclarationContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SnowStarParserVisitor*>(visitor))
    return parserVisitor->visitUnitDeclaration(this);
  else
    return visitor->visitChildren(this);
}

SnowStarParser::UnitDeclarationContext* SnowStarParser::unitDeclaration() {
  UnitDeclarationContext *_localctx = _tracker.createInstance<UnitDeclarationContext>(_ctx, getState());
  enterRule(_localctx, 10, SnowStarParser::RuleUnitDeclaration);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(81);
    match(SnowStarParser::UNIT);
    setState(82);
    unitName();
    setState(83);
    basicBlockDeclaration();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- UnitNameContext ------------------------------------------------------------------

SnowStarParser::UnitNameContext::UnitNameContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* SnowStarParser::UnitNameContext::IDENTIFIER() {
  return getToken(SnowStarParser::IDENTIFIER, 0);
}


size_t SnowStarParser::UnitNameContext::getRuleIndex() const {
  return SnowStarParser::RuleUnitName;
}

antlrcpp::Any SnowStarParser::UnitNameContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SnowStarParserVisitor*>(visitor))
    return parserVisitor->visitUnitName(this);
  else
    return visitor->visitChildren(this);
}

SnowStarParser::UnitNameContext* SnowStarParser::unitName() {
  UnitNameContext *_localctx = _tracker.createInstance<UnitNameContext>(_ctx, getState());
  enterRule(_localctx, 12, SnowStarParser::RuleUnitName);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(85);
    match(SnowStarParser::IDENTIFIER);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- BasicBlockDeclarationContext ------------------------------------------------------------------

SnowStarParser::BasicBlockDeclarationContext::BasicBlockDeclarationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* SnowStarParser::BasicBlockDeclarationContext::LBRACE() {
  return getToken(SnowStarParser::LBRACE, 0);
}

tree::TerminalNode* SnowStarParser::BasicBlockDeclarationContext::RBRACE() {
  return getToken(SnowStarParser::RBRACE, 0);
}

std::vector<SnowStarParser::StatementSeqContext *> SnowStarParser::BasicBlockDeclarationContext::statementSeq() {
  return getRuleContexts<SnowStarParser::StatementSeqContext>();
}

SnowStarParser::StatementSeqContext* SnowStarParser::BasicBlockDeclarationContext::statementSeq(size_t i) {
  return getRuleContext<SnowStarParser::StatementSeqContext>(i);
}


size_t SnowStarParser::BasicBlockDeclarationContext::getRuleIndex() const {
  return SnowStarParser::RuleBasicBlockDeclaration;
}

antlrcpp::Any SnowStarParser::BasicBlockDeclarationContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SnowStarParserVisitor*>(visitor))
    return parserVisitor->visitBasicBlockDeclaration(this);
  else
    return visitor->visitChildren(this);
}

SnowStarParser::BasicBlockDeclarationContext* SnowStarParser::basicBlockDeclaration() {
  BasicBlockDeclarationContext *_localctx = _tracker.createInstance<BasicBlockDeclarationContext>(_ctx, getState());
  enterRule(_localctx, 14, SnowStarParser::RuleBasicBlockDeclaration);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(87);
    match(SnowStarParser::LBRACE);
    setState(91);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << SnowStarParser::BOOL)
      | (1ULL << SnowStarParser::CHR)
      | (1ULL << SnowStarParser::I8)
      | (1ULL << SnowStarParser::UI8)
      | (1ULL << SnowStarParser::I16)
      | (1ULL << SnowStarParser::UI16)
      | (1ULL << SnowStarParser::I32)
      | (1ULL << SnowStarParser::UI32)
      | (1ULL << SnowStarParser::I64)
      | (1ULL << SnowStarParser::UI64)
      | (1ULL << SnowStarParser::F32)
      | (1ULL << SnowStarParser::F64)
      | (1ULL << SnowStarParser::STR)
      | (1ULL << SnowStarParser::VOID)
      | (1ULL << SnowStarParser::WITH)
      | (1ULL << SnowStarParser::IMPORT)
      | (1ULL << SnowStarParser::SEMI))) != 0) || _la == SnowStarParser::IDENTIFIER) {
      setState(88);
      statementSeq();
      setState(93);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(94);
    match(SnowStarParser::RBRACE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- DtypeDeclarationContext ------------------------------------------------------------------

SnowStarParser::DtypeDeclarationContext::DtypeDeclarationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* SnowStarParser::DtypeDeclarationContext::DTYPE() {
  return getToken(SnowStarParser::DTYPE, 0);
}

SnowStarParser::DtypeNameContext* SnowStarParser::DtypeDeclarationContext::dtypeName() {
  return getRuleContext<SnowStarParser::DtypeNameContext>(0);
}

SnowStarParser::DtypeBlockDeclarationContext* SnowStarParser::DtypeDeclarationContext::dtypeBlockDeclaration() {
  return getRuleContext<SnowStarParser::DtypeBlockDeclarationContext>(0);
}


size_t SnowStarParser::DtypeDeclarationContext::getRuleIndex() const {
  return SnowStarParser::RuleDtypeDeclaration;
}

antlrcpp::Any SnowStarParser::DtypeDeclarationContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SnowStarParserVisitor*>(visitor))
    return parserVisitor->visitDtypeDeclaration(this);
  else
    return visitor->visitChildren(this);
}

SnowStarParser::DtypeDeclarationContext* SnowStarParser::dtypeDeclaration() {
  DtypeDeclarationContext *_localctx = _tracker.createInstance<DtypeDeclarationContext>(_ctx, getState());
  enterRule(_localctx, 16, SnowStarParser::RuleDtypeDeclaration);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(96);
    match(SnowStarParser::DTYPE);
    setState(97);
    dtypeName();
    setState(98);
    dtypeBlockDeclaration();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- DtypeNameContext ------------------------------------------------------------------

SnowStarParser::DtypeNameContext::DtypeNameContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* SnowStarParser::DtypeNameContext::IDENTIFIER() {
  return getToken(SnowStarParser::IDENTIFIER, 0);
}


size_t SnowStarParser::DtypeNameContext::getRuleIndex() const {
  return SnowStarParser::RuleDtypeName;
}

antlrcpp::Any SnowStarParser::DtypeNameContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SnowStarParserVisitor*>(visitor))
    return parserVisitor->visitDtypeName(this);
  else
    return visitor->visitChildren(this);
}

SnowStarParser::DtypeNameContext* SnowStarParser::dtypeName() {
  DtypeNameContext *_localctx = _tracker.createInstance<DtypeNameContext>(_ctx, getState());
  enterRule(_localctx, 18, SnowStarParser::RuleDtypeName);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(100);
    match(SnowStarParser::IDENTIFIER);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- DtypeBlockDeclarationContext ------------------------------------------------------------------

SnowStarParser::DtypeBlockDeclarationContext::DtypeBlockDeclarationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* SnowStarParser::DtypeBlockDeclarationContext::LBRACE() {
  return getToken(SnowStarParser::LBRACE, 0);
}

tree::TerminalNode* SnowStarParser::DtypeBlockDeclarationContext::RBRACE() {
  return getToken(SnowStarParser::RBRACE, 0);
}

std::vector<SnowStarParser::VariableDeclarationContext *> SnowStarParser::DtypeBlockDeclarationContext::variableDeclaration() {
  return getRuleContexts<SnowStarParser::VariableDeclarationContext>();
}

SnowStarParser::VariableDeclarationContext* SnowStarParser::DtypeBlockDeclarationContext::variableDeclaration(size_t i) {
  return getRuleContext<SnowStarParser::VariableDeclarationContext>(i);
}


size_t SnowStarParser::DtypeBlockDeclarationContext::getRuleIndex() const {
  return SnowStarParser::RuleDtypeBlockDeclaration;
}

antlrcpp::Any SnowStarParser::DtypeBlockDeclarationContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SnowStarParserVisitor*>(visitor))
    return parserVisitor->visitDtypeBlockDeclaration(this);
  else
    return visitor->visitChildren(this);
}

SnowStarParser::DtypeBlockDeclarationContext* SnowStarParser::dtypeBlockDeclaration() {
  DtypeBlockDeclarationContext *_localctx = _tracker.createInstance<DtypeBlockDeclarationContext>(_ctx, getState());
  enterRule(_localctx, 20, SnowStarParser::RuleDtypeBlockDeclaration);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(102);
    match(SnowStarParser::LBRACE);
    setState(106);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << SnowStarParser::BOOL)
      | (1ULL << SnowStarParser::CHR)
      | (1ULL << SnowStarParser::I8)
      | (1ULL << SnowStarParser::UI8)
      | (1ULL << SnowStarParser::I16)
      | (1ULL << SnowStarParser::UI16)
      | (1ULL << SnowStarParser::I32)
      | (1ULL << SnowStarParser::UI32)
      | (1ULL << SnowStarParser::I64)
      | (1ULL << SnowStarParser::UI64)
      | (1ULL << SnowStarParser::F32)
      | (1ULL << SnowStarParser::F64)
      | (1ULL << SnowStarParser::STR)
      | (1ULL << SnowStarParser::VOID))) != 0) || _la == SnowStarParser::IDENTIFIER) {
      setState(103);
      variableDeclaration();
      setState(108);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(109);
    match(SnowStarParser::RBRACE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FunctionDeclarationContext ------------------------------------------------------------------

SnowStarParser::FunctionDeclarationContext::FunctionDeclarationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

SnowStarParser::TheTypeContext* SnowStarParser::FunctionDeclarationContext::theType() {
  return getRuleContext<SnowStarParser::TheTypeContext>(0);
}

SnowStarParser::FunctionNameContext* SnowStarParser::FunctionDeclarationContext::functionName() {
  return getRuleContext<SnowStarParser::FunctionNameContext>(0);
}

SnowStarParser::FunctionParamsContext* SnowStarParser::FunctionDeclarationContext::functionParams() {
  return getRuleContext<SnowStarParser::FunctionParamsContext>(0);
}

SnowStarParser::BasicBlockDeclarationContext* SnowStarParser::FunctionDeclarationContext::basicBlockDeclaration() {
  return getRuleContext<SnowStarParser::BasicBlockDeclarationContext>(0);
}


size_t SnowStarParser::FunctionDeclarationContext::getRuleIndex() const {
  return SnowStarParser::RuleFunctionDeclaration;
}

antlrcpp::Any SnowStarParser::FunctionDeclarationContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SnowStarParserVisitor*>(visitor))
    return parserVisitor->visitFunctionDeclaration(this);
  else
    return visitor->visitChildren(this);
}

SnowStarParser::FunctionDeclarationContext* SnowStarParser::functionDeclaration() {
  FunctionDeclarationContext *_localctx = _tracker.createInstance<FunctionDeclarationContext>(_ctx, getState());
  enterRule(_localctx, 22, SnowStarParser::RuleFunctionDeclaration);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(111);
    theType();
    setState(112);
    functionName();
    setState(113);
    functionParams();
    setState(114);
    basicBlockDeclaration();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FunctionNameContext ------------------------------------------------------------------

SnowStarParser::FunctionNameContext::FunctionNameContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* SnowStarParser::FunctionNameContext::IDENTIFIER() {
  return getToken(SnowStarParser::IDENTIFIER, 0);
}


size_t SnowStarParser::FunctionNameContext::getRuleIndex() const {
  return SnowStarParser::RuleFunctionName;
}

antlrcpp::Any SnowStarParser::FunctionNameContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SnowStarParserVisitor*>(visitor))
    return parserVisitor->visitFunctionName(this);
  else
    return visitor->visitChildren(this);
}

SnowStarParser::FunctionNameContext* SnowStarParser::functionName() {
  FunctionNameContext *_localctx = _tracker.createInstance<FunctionNameContext>(_ctx, getState());
  enterRule(_localctx, 24, SnowStarParser::RuleFunctionName);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(116);
    match(SnowStarParser::IDENTIFIER);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FunctionParamsContext ------------------------------------------------------------------

SnowStarParser::FunctionParamsContext::FunctionParamsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* SnowStarParser::FunctionParamsContext::LPAREN() {
  return getToken(SnowStarParser::LPAREN, 0);
}

tree::TerminalNode* SnowStarParser::FunctionParamsContext::RPAREN() {
  return getToken(SnowStarParser::RPAREN, 0);
}

std::vector<SnowStarParser::ParameterDeclarationContext *> SnowStarParser::FunctionParamsContext::parameterDeclaration() {
  return getRuleContexts<SnowStarParser::ParameterDeclarationContext>();
}

SnowStarParser::ParameterDeclarationContext* SnowStarParser::FunctionParamsContext::parameterDeclaration(size_t i) {
  return getRuleContext<SnowStarParser::ParameterDeclarationContext>(i);
}

std::vector<tree::TerminalNode *> SnowStarParser::FunctionParamsContext::COMMA() {
  return getTokens(SnowStarParser::COMMA);
}

tree::TerminalNode* SnowStarParser::FunctionParamsContext::COMMA(size_t i) {
  return getToken(SnowStarParser::COMMA, i);
}


size_t SnowStarParser::FunctionParamsContext::getRuleIndex() const {
  return SnowStarParser::RuleFunctionParams;
}

antlrcpp::Any SnowStarParser::FunctionParamsContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SnowStarParserVisitor*>(visitor))
    return parserVisitor->visitFunctionParams(this);
  else
    return visitor->visitChildren(this);
}

SnowStarParser::FunctionParamsContext* SnowStarParser::functionParams() {
  FunctionParamsContext *_localctx = _tracker.createInstance<FunctionParamsContext>(_ctx, getState());
  enterRule(_localctx, 26, SnowStarParser::RuleFunctionParams);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(118);
    match(SnowStarParser::LPAREN);
    setState(127);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << SnowStarParser::BOOL)
      | (1ULL << SnowStarParser::CHR)
      | (1ULL << SnowStarParser::I8)
      | (1ULL << SnowStarParser::UI8)
      | (1ULL << SnowStarParser::I16)
      | (1ULL << SnowStarParser::UI16)
      | (1ULL << SnowStarParser::I32)
      | (1ULL << SnowStarParser::UI32)
      | (1ULL << SnowStarParser::I64)
      | (1ULL << SnowStarParser::UI64)
      | (1ULL << SnowStarParser::F32)
      | (1ULL << SnowStarParser::F64)
      | (1ULL << SnowStarParser::STR)
      | (1ULL << SnowStarParser::VOID))) != 0) || _la == SnowStarParser::IDENTIFIER) {
      setState(119);
      parameterDeclaration();
      setState(124);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == SnowStarParser::COMMA) {
        setState(120);
        match(SnowStarParser::COMMA);
        setState(121);
        parameterDeclaration();
        setState(126);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
    }
    setState(129);
    match(SnowStarParser::RPAREN);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ParameterDeclarationContext ------------------------------------------------------------------

SnowStarParser::ParameterDeclarationContext::ParameterDeclarationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

SnowStarParser::TheTypeContext* SnowStarParser::ParameterDeclarationContext::theType() {
  return getRuleContext<SnowStarParser::TheTypeContext>(0);
}

tree::TerminalNode* SnowStarParser::ParameterDeclarationContext::IDENTIFIER() {
  return getToken(SnowStarParser::IDENTIFIER, 0);
}

tree::TerminalNode* SnowStarParser::ParameterDeclarationContext::ASSIGN() {
  return getToken(SnowStarParser::ASSIGN, 0);
}

SnowStarParser::ValueContext* SnowStarParser::ParameterDeclarationContext::value() {
  return getRuleContext<SnowStarParser::ValueContext>(0);
}


size_t SnowStarParser::ParameterDeclarationContext::getRuleIndex() const {
  return SnowStarParser::RuleParameterDeclaration;
}

antlrcpp::Any SnowStarParser::ParameterDeclarationContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SnowStarParserVisitor*>(visitor))
    return parserVisitor->visitParameterDeclaration(this);
  else
    return visitor->visitChildren(this);
}

SnowStarParser::ParameterDeclarationContext* SnowStarParser::parameterDeclaration() {
  ParameterDeclarationContext *_localctx = _tracker.createInstance<ParameterDeclarationContext>(_ctx, getState());
  enterRule(_localctx, 28, SnowStarParser::RuleParameterDeclaration);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(131);
    theType();
    setState(132);
    match(SnowStarParser::IDENTIFIER);
    setState(135);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == SnowStarParser::ASSIGN) {
      setState(133);
      match(SnowStarParser::ASSIGN);
      setState(134);
      value();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- WithDeclarationContext ------------------------------------------------------------------

SnowStarParser::WithDeclarationContext::WithDeclarationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* SnowStarParser::WithDeclarationContext::WITH() {
  return getToken(SnowStarParser::WITH, 0);
}

SnowStarParser::WithNameContext* SnowStarParser::WithDeclarationContext::withName() {
  return getRuleContext<SnowStarParser::WithNameContext>(0);
}

tree::TerminalNode* SnowStarParser::WithDeclarationContext::ASSIGN() {
  return getToken(SnowStarParser::ASSIGN, 0);
}

SnowStarParser::TheTypeContext* SnowStarParser::WithDeclarationContext::theType() {
  return getRuleContext<SnowStarParser::TheTypeContext>(0);
}

tree::TerminalNode* SnowStarParser::WithDeclarationContext::SEMI() {
  return getToken(SnowStarParser::SEMI, 0);
}


size_t SnowStarParser::WithDeclarationContext::getRuleIndex() const {
  return SnowStarParser::RuleWithDeclaration;
}

antlrcpp::Any SnowStarParser::WithDeclarationContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SnowStarParserVisitor*>(visitor))
    return parserVisitor->visitWithDeclaration(this);
  else
    return visitor->visitChildren(this);
}

SnowStarParser::WithDeclarationContext* SnowStarParser::withDeclaration() {
  WithDeclarationContext *_localctx = _tracker.createInstance<WithDeclarationContext>(_ctx, getState());
  enterRule(_localctx, 30, SnowStarParser::RuleWithDeclaration);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(137);
    match(SnowStarParser::WITH);
    setState(138);
    withName();
    setState(139);
    match(SnowStarParser::ASSIGN);
    setState(140);
    theType();
    setState(141);
    match(SnowStarParser::SEMI);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- WithNameContext ------------------------------------------------------------------

SnowStarParser::WithNameContext::WithNameContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* SnowStarParser::WithNameContext::IDENTIFIER() {
  return getToken(SnowStarParser::IDENTIFIER, 0);
}


size_t SnowStarParser::WithNameContext::getRuleIndex() const {
  return SnowStarParser::RuleWithName;
}

antlrcpp::Any SnowStarParser::WithNameContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SnowStarParserVisitor*>(visitor))
    return parserVisitor->visitWithName(this);
  else
    return visitor->visitChildren(this);
}

SnowStarParser::WithNameContext* SnowStarParser::withName() {
  WithNameContext *_localctx = _tracker.createInstance<WithNameContext>(_ctx, getState());
  enterRule(_localctx, 32, SnowStarParser::RuleWithName);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(143);
    match(SnowStarParser::IDENTIFIER);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ImportDeclarationContext ------------------------------------------------------------------

SnowStarParser::ImportDeclarationContext::ImportDeclarationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* SnowStarParser::ImportDeclarationContext::IMPORT() {
  return getToken(SnowStarParser::IMPORT, 0);
}

SnowStarParser::ImportNameContext* SnowStarParser::ImportDeclarationContext::importName() {
  return getRuleContext<SnowStarParser::ImportNameContext>(0);
}

tree::TerminalNode* SnowStarParser::ImportDeclarationContext::SEMI() {
  return getToken(SnowStarParser::SEMI, 0);
}


size_t SnowStarParser::ImportDeclarationContext::getRuleIndex() const {
  return SnowStarParser::RuleImportDeclaration;
}

antlrcpp::Any SnowStarParser::ImportDeclarationContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SnowStarParserVisitor*>(visitor))
    return parserVisitor->visitImportDeclaration(this);
  else
    return visitor->visitChildren(this);
}

SnowStarParser::ImportDeclarationContext* SnowStarParser::importDeclaration() {
  ImportDeclarationContext *_localctx = _tracker.createInstance<ImportDeclarationContext>(_ctx, getState());
  enterRule(_localctx, 34, SnowStarParser::RuleImportDeclaration);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(145);
    match(SnowStarParser::IMPORT);
    setState(146);
    importName();
    setState(147);
    match(SnowStarParser::SEMI);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ImportNameContext ------------------------------------------------------------------

SnowStarParser::ImportNameContext::ImportNameContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* SnowStarParser::ImportNameContext::IDENTIFIER() {
  return getToken(SnowStarParser::IDENTIFIER, 0);
}


size_t SnowStarParser::ImportNameContext::getRuleIndex() const {
  return SnowStarParser::RuleImportName;
}

antlrcpp::Any SnowStarParser::ImportNameContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SnowStarParserVisitor*>(visitor))
    return parserVisitor->visitImportName(this);
  else
    return visitor->visitChildren(this);
}

SnowStarParser::ImportNameContext* SnowStarParser::importName() {
  ImportNameContext *_localctx = _tracker.createInstance<ImportNameContext>(_ctx, getState());
  enterRule(_localctx, 36, SnowStarParser::RuleImportName);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(149);
    match(SnowStarParser::IDENTIFIER);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- EmptyDeclarationContext ------------------------------------------------------------------

SnowStarParser::EmptyDeclarationContext::EmptyDeclarationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* SnowStarParser::EmptyDeclarationContext::SEMI() {
  return getToken(SnowStarParser::SEMI, 0);
}


size_t SnowStarParser::EmptyDeclarationContext::getRuleIndex() const {
  return SnowStarParser::RuleEmptyDeclaration;
}

antlrcpp::Any SnowStarParser::EmptyDeclarationContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SnowStarParserVisitor*>(visitor))
    return parserVisitor->visitEmptyDeclaration(this);
  else
    return visitor->visitChildren(this);
}

SnowStarParser::EmptyDeclarationContext* SnowStarParser::emptyDeclaration() {
  EmptyDeclarationContext *_localctx = _tracker.createInstance<EmptyDeclarationContext>(_ctx, getState());
  enterRule(_localctx, 38, SnowStarParser::RuleEmptyDeclaration);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(151);
    match(SnowStarParser::SEMI);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StatementSeqContext ------------------------------------------------------------------

SnowStarParser::StatementSeqContext::StatementSeqContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

SnowStarParser::VariableDeclarationContext* SnowStarParser::StatementSeqContext::variableDeclaration() {
  return getRuleContext<SnowStarParser::VariableDeclarationContext>(0);
}

SnowStarParser::WithDeclarationContext* SnowStarParser::StatementSeqContext::withDeclaration() {
  return getRuleContext<SnowStarParser::WithDeclarationContext>(0);
}

SnowStarParser::ImportDeclarationContext* SnowStarParser::StatementSeqContext::importDeclaration() {
  return getRuleContext<SnowStarParser::ImportDeclarationContext>(0);
}

SnowStarParser::EmptyDeclarationContext* SnowStarParser::StatementSeqContext::emptyDeclaration() {
  return getRuleContext<SnowStarParser::EmptyDeclarationContext>(0);
}


size_t SnowStarParser::StatementSeqContext::getRuleIndex() const {
  return SnowStarParser::RuleStatementSeq;
}

antlrcpp::Any SnowStarParser::StatementSeqContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SnowStarParserVisitor*>(visitor))
    return parserVisitor->visitStatementSeq(this);
  else
    return visitor->visitChildren(this);
}

SnowStarParser::StatementSeqContext* SnowStarParser::statementSeq() {
  StatementSeqContext *_localctx = _tracker.createInstance<StatementSeqContext>(_ctx, getState());
  enterRule(_localctx, 40, SnowStarParser::RuleStatementSeq);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(157);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case SnowStarParser::BOOL:
      case SnowStarParser::CHR:
      case SnowStarParser::I8:
      case SnowStarParser::UI8:
      case SnowStarParser::I16:
      case SnowStarParser::UI16:
      case SnowStarParser::I32:
      case SnowStarParser::UI32:
      case SnowStarParser::I64:
      case SnowStarParser::UI64:
      case SnowStarParser::F32:
      case SnowStarParser::F64:
      case SnowStarParser::STR:
      case SnowStarParser::VOID:
      case SnowStarParser::IDENTIFIER: {
        enterOuterAlt(_localctx, 1);
        setState(153);
        variableDeclaration();
        break;
      }

      case SnowStarParser::WITH: {
        enterOuterAlt(_localctx, 2);
        setState(154);
        withDeclaration();
        break;
      }

      case SnowStarParser::IMPORT: {
        enterOuterAlt(_localctx, 3);
        setState(155);
        importDeclaration();
        break;
      }

      case SnowStarParser::SEMI: {
        enterOuterAlt(_localctx, 4);
        setState(156);
        emptyDeclaration();
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

SnowStarParser::PrimaryExpressionContext* SnowStarParser::ExpressionContext::primaryExpression() {
  return getRuleContext<SnowStarParser::PrimaryExpressionContext>(0);
}

std::vector<SnowStarParser::ExpressionContext *> SnowStarParser::ExpressionContext::expression() {
  return getRuleContexts<SnowStarParser::ExpressionContext>();
}

SnowStarParser::ExpressionContext* SnowStarParser::ExpressionContext::expression(size_t i) {
  return getRuleContext<SnowStarParser::ExpressionContext>(i);
}

tree::TerminalNode* SnowStarParser::ExpressionContext::PLUS() {
  return getToken(SnowStarParser::PLUS, 0);
}

tree::TerminalNode* SnowStarParser::ExpressionContext::LOGIC_NOT() {
  return getToken(SnowStarParser::LOGIC_NOT, 0);
}

tree::TerminalNode* SnowStarParser::ExpressionContext::BIN_NOT() {
  return getToken(SnowStarParser::BIN_NOT, 0);
}

tree::TerminalNode* SnowStarParser::ExpressionContext::MINUS() {
  return getToken(SnowStarParser::MINUS, 0);
}

tree::TerminalNode* SnowStarParser::ExpressionContext::LPAREN() {
  return getToken(SnowStarParser::LPAREN, 0);
}

SnowStarParser::TheTypeContext* SnowStarParser::ExpressionContext::theType() {
  return getRuleContext<SnowStarParser::TheTypeContext>(0);
}

tree::TerminalNode* SnowStarParser::ExpressionContext::RPAREN() {
  return getToken(SnowStarParser::RPAREN, 0);
}

tree::TerminalNode* SnowStarParser::ExpressionContext::STAR() {
  return getToken(SnowStarParser::STAR, 0);
}

tree::TerminalNode* SnowStarParser::ExpressionContext::SLASH() {
  return getToken(SnowStarParser::SLASH, 0);
}

tree::TerminalNode* SnowStarParser::ExpressionContext::GREATER() {
  return getToken(SnowStarParser::GREATER, 0);
}

tree::TerminalNode* SnowStarParser::ExpressionContext::LOWER() {
  return getToken(SnowStarParser::LOWER, 0);
}

tree::TerminalNode* SnowStarParser::ExpressionContext::GREATER_EQ() {
  return getToken(SnowStarParser::GREATER_EQ, 0);
}

tree::TerminalNode* SnowStarParser::ExpressionContext::LOWER_EQ() {
  return getToken(SnowStarParser::LOWER_EQ, 0);
}

tree::TerminalNode* SnowStarParser::ExpressionContext::EQUALS() {
  return getToken(SnowStarParser::EQUALS, 0);
}

tree::TerminalNode* SnowStarParser::ExpressionContext::NEQUALS() {
  return getToken(SnowStarParser::NEQUALS, 0);
}

tree::TerminalNode* SnowStarParser::ExpressionContext::BIN_XOR() {
  return getToken(SnowStarParser::BIN_XOR, 0);
}

tree::TerminalNode* SnowStarParser::ExpressionContext::BIN_AND() {
  return getToken(SnowStarParser::BIN_AND, 0);
}

tree::TerminalNode* SnowStarParser::ExpressionContext::BIN_OR() {
  return getToken(SnowStarParser::BIN_OR, 0);
}

tree::TerminalNode* SnowStarParser::ExpressionContext::LOGIC_AND() {
  return getToken(SnowStarParser::LOGIC_AND, 0);
}

tree::TerminalNode* SnowStarParser::ExpressionContext::LOGIC_OR() {
  return getToken(SnowStarParser::LOGIC_OR, 0);
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
  size_t startState = 42;
  enterRecursionRule(_localctx, 42, SnowStarParser::RuleExpression, precedence);

    size_t _la = 0;

  auto onExit = finally([=] {
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(168);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 9, _ctx)) {
    case 1: {
      setState(160);
      primaryExpression();
      break;
    }

    case 2: {
      setState(161);
      dynamic_cast<ExpressionContext *>(_localctx)->unary = _input->LT(1);
      _la = _input->LA(1);
      if (!((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & ((1ULL << SnowStarParser::LOGIC_NOT)
        | (1ULL << SnowStarParser::PLUS)
        | (1ULL << SnowStarParser::MINUS)
        | (1ULL << SnowStarParser::BIN_NOT))) != 0))) {
        dynamic_cast<ExpressionContext *>(_localctx)->unary = _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(162);
      expression(8);
      break;
    }

    case 3: {
      setState(163);
      match(SnowStarParser::LPAREN);
      setState(164);
      theType();
      setState(165);
      match(SnowStarParser::RPAREN);
      setState(166);
      expression(7);
      break;
    }

    }
    _ctx->stop = _input->LT(-1);
    setState(190);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 11, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(188);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 10, _ctx)) {
        case 1: {
          _localctx = _tracker.createInstance<ExpressionContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleExpression);
          setState(170);

          if (!(precpred(_ctx, 6))) throw FailedPredicateException(this, "precpred(_ctx, 6)");
          setState(171);
          dynamic_cast<ExpressionContext *>(_localctx)->binary = _input->LT(1);
          _la = _input->LA(1);
          if (!(_la == SnowStarParser::STAR

          || _la == SnowStarParser::SLASH)) {
            dynamic_cast<ExpressionContext *>(_localctx)->binary = _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(172);
          expression(7);
          break;
        }

        case 2: {
          _localctx = _tracker.createInstance<ExpressionContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleExpression);
          setState(173);

          if (!(precpred(_ctx, 5))) throw FailedPredicateException(this, "precpred(_ctx, 5)");
          setState(174);
          dynamic_cast<ExpressionContext *>(_localctx)->binary = _input->LT(1);
          _la = _input->LA(1);
          if (!(_la == SnowStarParser::PLUS

          || _la == SnowStarParser::MINUS)) {
            dynamic_cast<ExpressionContext *>(_localctx)->binary = _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(175);
          expression(6);
          break;
        }

        case 3: {
          _localctx = _tracker.createInstance<ExpressionContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleExpression);
          setState(176);

          if (!(precpred(_ctx, 4))) throw FailedPredicateException(this, "precpred(_ctx, 4)");
          setState(177);
          dynamic_cast<ExpressionContext *>(_localctx)->binary = _input->LT(1);
          _la = _input->LA(1);
          if (!((((_la & ~ 0x3fULL) == 0) &&
            ((1ULL << _la) & ((1ULL << SnowStarParser::GREATER)
            | (1ULL << SnowStarParser::LOWER)
            | (1ULL << SnowStarParser::GREATER_EQ)
            | (1ULL << SnowStarParser::LOWER_EQ))) != 0))) {
            dynamic_cast<ExpressionContext *>(_localctx)->binary = _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(178);
          expression(5);
          break;
        }

        case 4: {
          _localctx = _tracker.createInstance<ExpressionContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleExpression);
          setState(179);

          if (!(precpred(_ctx, 3))) throw FailedPredicateException(this, "precpred(_ctx, 3)");
          setState(180);
          dynamic_cast<ExpressionContext *>(_localctx)->binary = _input->LT(1);
          _la = _input->LA(1);
          if (!(_la == SnowStarParser::EQUALS

          || _la == SnowStarParser::NEQUALS)) {
            dynamic_cast<ExpressionContext *>(_localctx)->binary = _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(181);
          expression(4);
          break;
        }

        case 5: {
          _localctx = _tracker.createInstance<ExpressionContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleExpression);
          setState(182);

          if (!(precpred(_ctx, 2))) throw FailedPredicateException(this, "precpred(_ctx, 2)");
          setState(183);
          dynamic_cast<ExpressionContext *>(_localctx)->binary = _input->LT(1);
          _la = _input->LA(1);
          if (!((((_la & ~ 0x3fULL) == 0) &&
            ((1ULL << _la) & ((1ULL << SnowStarParser::BIN_AND)
            | (1ULL << SnowStarParser::BIN_OR)
            | (1ULL << SnowStarParser::BIN_XOR))) != 0))) {
            dynamic_cast<ExpressionContext *>(_localctx)->binary = _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(184);
          expression(3);
          break;
        }

        case 6: {
          _localctx = _tracker.createInstance<ExpressionContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleExpression);
          setState(185);

          if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
          setState(186);
          dynamic_cast<ExpressionContext *>(_localctx)->binary = _input->LT(1);
          _la = _input->LA(1);
          if (!(_la == SnowStarParser::LOGIC_OR

          || _la == SnowStarParser::LOGIC_AND)) {
            dynamic_cast<ExpressionContext *>(_localctx)->binary = _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(187);
          expression(2);
          break;
        }

        } 
      }
      setState(192);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 11, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- PrimaryExpressionContext ------------------------------------------------------------------

SnowStarParser::PrimaryExpressionContext::PrimaryExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* SnowStarParser::PrimaryExpressionContext::LPAREN() {
  return getToken(SnowStarParser::LPAREN, 0);
}

SnowStarParser::ExpressionContext* SnowStarParser::PrimaryExpressionContext::expression() {
  return getRuleContext<SnowStarParser::ExpressionContext>(0);
}

tree::TerminalNode* SnowStarParser::PrimaryExpressionContext::RPAREN() {
  return getToken(SnowStarParser::RPAREN, 0);
}

tree::TerminalNode* SnowStarParser::PrimaryExpressionContext::IDENTIFIER() {
  return getToken(SnowStarParser::IDENTIFIER, 0);
}

SnowStarParser::ValueContext* SnowStarParser::PrimaryExpressionContext::value() {
  return getRuleContext<SnowStarParser::ValueContext>(0);
}


size_t SnowStarParser::PrimaryExpressionContext::getRuleIndex() const {
  return SnowStarParser::RulePrimaryExpression;
}

antlrcpp::Any SnowStarParser::PrimaryExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SnowStarParserVisitor*>(visitor))
    return parserVisitor->visitPrimaryExpression(this);
  else
    return visitor->visitChildren(this);
}

SnowStarParser::PrimaryExpressionContext* SnowStarParser::primaryExpression() {
  PrimaryExpressionContext *_localctx = _tracker.createInstance<PrimaryExpressionContext>(_ctx, getState());
  enterRule(_localctx, 44, SnowStarParser::RulePrimaryExpression);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(199);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case SnowStarParser::LPAREN: {
        enterOuterAlt(_localctx, 1);
        setState(193);
        match(SnowStarParser::LPAREN);
        setState(194);
        expression(0);
        setState(195);
        match(SnowStarParser::RPAREN);
        break;
      }

      case SnowStarParser::IDENTIFIER: {
        enterOuterAlt(_localctx, 2);
        setState(197);
        match(SnowStarParser::IDENTIFIER);
        break;
      }

      case SnowStarParser::DEC_LITERAL:
      case SnowStarParser::HEX_LITERAL:
      case SnowStarParser::BIN_LITERAL:
      case SnowStarParser::OCT_LITERAL:
      case SnowStarParser::FLOAT_LITERAL:
      case SnowStarParser::BOOL_LITERAL:
      case SnowStarParser::CHAR_LITERAL:
      case SnowStarParser::STRING_LITERAL: {
        enterOuterAlt(_localctx, 3);
        setState(198);
        value();
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

//----------------- TheTypeContext ------------------------------------------------------------------

SnowStarParser::TheTypeContext::TheTypeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

SnowStarParser::BuiltinTypesContext* SnowStarParser::TheTypeContext::builtinTypes() {
  return getRuleContext<SnowStarParser::BuiltinTypesContext>(0);
}

tree::TerminalNode* SnowStarParser::TheTypeContext::IDENTIFIER() {
  return getToken(SnowStarParser::IDENTIFIER, 0);
}


size_t SnowStarParser::TheTypeContext::getRuleIndex() const {
  return SnowStarParser::RuleTheType;
}

antlrcpp::Any SnowStarParser::TheTypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SnowStarParserVisitor*>(visitor))
    return parserVisitor->visitTheType(this);
  else
    return visitor->visitChildren(this);
}

SnowStarParser::TheTypeContext* SnowStarParser::theType() {
  TheTypeContext *_localctx = _tracker.createInstance<TheTypeContext>(_ctx, getState());
  enterRule(_localctx, 46, SnowStarParser::RuleTheType);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(203);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case SnowStarParser::BOOL:
      case SnowStarParser::CHR:
      case SnowStarParser::I8:
      case SnowStarParser::UI8:
      case SnowStarParser::I16:
      case SnowStarParser::UI16:
      case SnowStarParser::I32:
      case SnowStarParser::UI32:
      case SnowStarParser::I64:
      case SnowStarParser::UI64:
      case SnowStarParser::F32:
      case SnowStarParser::F64:
      case SnowStarParser::STR:
      case SnowStarParser::VOID: {
        enterOuterAlt(_localctx, 1);
        setState(201);
        builtinTypes();
        break;
      }

      case SnowStarParser::IDENTIFIER: {
        enterOuterAlt(_localctx, 2);
        setState(202);
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

//----------------- BuiltinTypesContext ------------------------------------------------------------------

SnowStarParser::BuiltinTypesContext::BuiltinTypesContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* SnowStarParser::BuiltinTypesContext::BOOL() {
  return getToken(SnowStarParser::BOOL, 0);
}

tree::TerminalNode* SnowStarParser::BuiltinTypesContext::CHR() {
  return getToken(SnowStarParser::CHR, 0);
}

tree::TerminalNode* SnowStarParser::BuiltinTypesContext::I8() {
  return getToken(SnowStarParser::I8, 0);
}

tree::TerminalNode* SnowStarParser::BuiltinTypesContext::UI8() {
  return getToken(SnowStarParser::UI8, 0);
}

tree::TerminalNode* SnowStarParser::BuiltinTypesContext::I16() {
  return getToken(SnowStarParser::I16, 0);
}

tree::TerminalNode* SnowStarParser::BuiltinTypesContext::UI16() {
  return getToken(SnowStarParser::UI16, 0);
}

tree::TerminalNode* SnowStarParser::BuiltinTypesContext::I32() {
  return getToken(SnowStarParser::I32, 0);
}

tree::TerminalNode* SnowStarParser::BuiltinTypesContext::UI32() {
  return getToken(SnowStarParser::UI32, 0);
}

tree::TerminalNode* SnowStarParser::BuiltinTypesContext::I64() {
  return getToken(SnowStarParser::I64, 0);
}

tree::TerminalNode* SnowStarParser::BuiltinTypesContext::UI64() {
  return getToken(SnowStarParser::UI64, 0);
}

tree::TerminalNode* SnowStarParser::BuiltinTypesContext::F32() {
  return getToken(SnowStarParser::F32, 0);
}

tree::TerminalNode* SnowStarParser::BuiltinTypesContext::F64() {
  return getToken(SnowStarParser::F64, 0);
}

tree::TerminalNode* SnowStarParser::BuiltinTypesContext::STR() {
  return getToken(SnowStarParser::STR, 0);
}

tree::TerminalNode* SnowStarParser::BuiltinTypesContext::VOID() {
  return getToken(SnowStarParser::VOID, 0);
}


size_t SnowStarParser::BuiltinTypesContext::getRuleIndex() const {
  return SnowStarParser::RuleBuiltinTypes;
}

antlrcpp::Any SnowStarParser::BuiltinTypesContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SnowStarParserVisitor*>(visitor))
    return parserVisitor->visitBuiltinTypes(this);
  else
    return visitor->visitChildren(this);
}

SnowStarParser::BuiltinTypesContext* SnowStarParser::builtinTypes() {
  BuiltinTypesContext *_localctx = _tracker.createInstance<BuiltinTypesContext>(_ctx, getState());
  enterRule(_localctx, 48, SnowStarParser::RuleBuiltinTypes);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(205);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << SnowStarParser::BOOL)
      | (1ULL << SnowStarParser::CHR)
      | (1ULL << SnowStarParser::I8)
      | (1ULL << SnowStarParser::UI8)
      | (1ULL << SnowStarParser::I16)
      | (1ULL << SnowStarParser::UI16)
      | (1ULL << SnowStarParser::I32)
      | (1ULL << SnowStarParser::UI32)
      | (1ULL << SnowStarParser::I64)
      | (1ULL << SnowStarParser::UI64)
      | (1ULL << SnowStarParser::F32)
      | (1ULL << SnowStarParser::F64)
      | (1ULL << SnowStarParser::STR)
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

//----------------- ValueContext ------------------------------------------------------------------

SnowStarParser::ValueContext::ValueContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* SnowStarParser::ValueContext::BOOL_LITERAL() {
  return getToken(SnowStarParser::BOOL_LITERAL, 0);
}

tree::TerminalNode* SnowStarParser::ValueContext::CHAR_LITERAL() {
  return getToken(SnowStarParser::CHAR_LITERAL, 0);
}

tree::TerminalNode* SnowStarParser::ValueContext::DEC_LITERAL() {
  return getToken(SnowStarParser::DEC_LITERAL, 0);
}

tree::TerminalNode* SnowStarParser::ValueContext::BIN_LITERAL() {
  return getToken(SnowStarParser::BIN_LITERAL, 0);
}

tree::TerminalNode* SnowStarParser::ValueContext::HEX_LITERAL() {
  return getToken(SnowStarParser::HEX_LITERAL, 0);
}

tree::TerminalNode* SnowStarParser::ValueContext::OCT_LITERAL() {
  return getToken(SnowStarParser::OCT_LITERAL, 0);
}

tree::TerminalNode* SnowStarParser::ValueContext::FLOAT_LITERAL() {
  return getToken(SnowStarParser::FLOAT_LITERAL, 0);
}

tree::TerminalNode* SnowStarParser::ValueContext::STRING_LITERAL() {
  return getToken(SnowStarParser::STRING_LITERAL, 0);
}


size_t SnowStarParser::ValueContext::getRuleIndex() const {
  return SnowStarParser::RuleValue;
}

antlrcpp::Any SnowStarParser::ValueContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SnowStarParserVisitor*>(visitor))
    return parserVisitor->visitValue(this);
  else
    return visitor->visitChildren(this);
}

SnowStarParser::ValueContext* SnowStarParser::value() {
  ValueContext *_localctx = _tracker.createInstance<ValueContext>(_ctx, getState());
  enterRule(_localctx, 50, SnowStarParser::RuleValue);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(207);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << SnowStarParser::DEC_LITERAL)
      | (1ULL << SnowStarParser::HEX_LITERAL)
      | (1ULL << SnowStarParser::BIN_LITERAL)
      | (1ULL << SnowStarParser::OCT_LITERAL)
      | (1ULL << SnowStarParser::FLOAT_LITERAL)
      | (1ULL << SnowStarParser::BOOL_LITERAL)
      | (1ULL << SnowStarParser::CHAR_LITERAL)
      | (1ULL << SnowStarParser::STRING_LITERAL))) != 0))) {
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
    case 21: return expressionSempred(dynamic_cast<ExpressionContext *>(context), predicateIndex);

  default:
    break;
  }
  return true;
}

bool SnowStarParser::expressionSempred(ExpressionContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 0: return precpred(_ctx, 6);
    case 1: return precpred(_ctx, 5);
    case 2: return precpred(_ctx, 4);
    case 3: return precpred(_ctx, 3);
    case 4: return precpred(_ctx, 2);
    case 5: return precpred(_ctx, 1);

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
  "compilationUnit", "declarationSeq", "variableDeclaration", "variableName", 
  "variableInitializer", "unitDeclaration", "unitName", "basicBlockDeclaration", 
  "dtypeDeclaration", "dtypeName", "dtypeBlockDeclaration", "functionDeclaration", 
  "functionName", "functionParams", "parameterDeclaration", "withDeclaration", 
  "withName", "importDeclaration", "importName", "emptyDeclaration", "statementSeq", 
  "expression", "primaryExpression", "theType", "builtinTypes", "value"
};

std::vector<std::string> SnowStarParser::_literalNames = {
  "", "'bool'", "'chr'", "'i8'", "'ui8'", "'i16'", "'ui16'", "'i32'", "'ui32'", 
  "'i64'", "'ui64'", "'f32'", "'f64'", "'str'", "'void'", "'with'", "'return'", 
  "'external'", "'unit'", "'align'", "'dtype'", "'import'", "", "", "", 
  "", "", "", "", "", "'(*'", "'*)'", "'%'", "'('", "')'", "'{'", "'}'", 
  "'['", "']'", "';'", "','", "'.'", "':'", "'::'", "'='", "'=='", "'!='", 
  "'>'", "'<'", "'>='", "'<='", "'||'", "'&&'", "'!'", "'+'", "'-'", "'*'", 
  "'/'", "'~'", "'&'", "'|'", "'^'"
};

std::vector<std::string> SnowStarParser::_symbolicNames = {
  "", "BOOL", "CHR", "I8", "UI8", "I16", "UI16", "I32", "UI32", "I64", "UI64", 
  "F32", "F64", "STR", "VOID", "WITH", "RET", "EXTERNAL", "UNIT", "ALIGN_AS", 
  "DTYPE", "IMPORT", "DEC_LITERAL", "HEX_LITERAL", "BIN_LITERAL", "OCT_LITERAL", 
  "FLOAT_LITERAL", "BOOL_LITERAL", "CHAR_LITERAL", "STRING_LITERAL", "BEGIN_COM", 
  "END_COM", "INLINE_COM", "LPAREN", "RPAREN", "LBRACE", "RBRACE", "LBRACK", 
  "RBRACK", "SEMI", "COMMA", "DOT", "COLON", "COLONCOLON", "ASSIGN", "EQUALS", 
  "NEQUALS", "GREATER", "LOWER", "GREATER_EQ", "LOWER_EQ", "LOGIC_OR", "LOGIC_AND", 
  "LOGIC_NOT", "PLUS", "MINUS", "STAR", "SLASH", "BIN_NOT", "BIN_AND", "BIN_OR", 
  "BIN_XOR", "WS", "COMMENT", "LINE_COMMENT", "IDENTIFIER"
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
    0x3, 0x43, 0xd4, 0x4, 0x2, 0x9, 0x2, 0x4, 0x3, 0x9, 0x3, 0x4, 0x4, 0x9, 
    0x4, 0x4, 0x5, 0x9, 0x5, 0x4, 0x6, 0x9, 0x6, 0x4, 0x7, 0x9, 0x7, 0x4, 
    0x8, 0x9, 0x8, 0x4, 0x9, 0x9, 0x9, 0x4, 0xa, 0x9, 0xa, 0x4, 0xb, 0x9, 
    0xb, 0x4, 0xc, 0x9, 0xc, 0x4, 0xd, 0x9, 0xd, 0x4, 0xe, 0x9, 0xe, 0x4, 
    0xf, 0x9, 0xf, 0x4, 0x10, 0x9, 0x10, 0x4, 0x11, 0x9, 0x11, 0x4, 0x12, 
    0x9, 0x12, 0x4, 0x13, 0x9, 0x13, 0x4, 0x14, 0x9, 0x14, 0x4, 0x15, 0x9, 
    0x15, 0x4, 0x16, 0x9, 0x16, 0x4, 0x17, 0x9, 0x17, 0x4, 0x18, 0x9, 0x18, 
    0x4, 0x19, 0x9, 0x19, 0x4, 0x1a, 0x9, 0x1a, 0x4, 0x1b, 0x9, 0x1b, 0x3, 
    0x2, 0x7, 0x2, 0x38, 0xa, 0x2, 0xc, 0x2, 0xe, 0x2, 0x3b, 0xb, 0x2, 0x3, 
    0x2, 0x3, 0x2, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 
    0x3, 0x3, 0x3, 0x5, 0x3, 0x46, 0xa, 0x3, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 
    0x5, 0x4, 0x4b, 0xa, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x5, 0x3, 0x5, 0x3, 
    0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 
    0x8, 0x3, 0x8, 0x3, 0x9, 0x3, 0x9, 0x7, 0x9, 0x5c, 0xa, 0x9, 0xc, 0x9, 
    0xe, 0x9, 0x5f, 0xb, 0x9, 0x3, 0x9, 0x3, 0x9, 0x3, 0xa, 0x3, 0xa, 0x3, 
    0xa, 0x3, 0xa, 0x3, 0xb, 0x3, 0xb, 0x3, 0xc, 0x3, 0xc, 0x7, 0xc, 0x6b, 
    0xa, 0xc, 0xc, 0xc, 0xe, 0xc, 0x6e, 0xb, 0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 
    0xd, 0x3, 0xd, 0x3, 0xd, 0x3, 0xd, 0x3, 0xd, 0x3, 0xe, 0x3, 0xe, 0x3, 
    0xf, 0x3, 0xf, 0x3, 0xf, 0x3, 0xf, 0x7, 0xf, 0x7d, 0xa, 0xf, 0xc, 0xf, 
    0xe, 0xf, 0x80, 0xb, 0xf, 0x5, 0xf, 0x82, 0xa, 0xf, 0x3, 0xf, 0x3, 0xf, 
    0x3, 0x10, 0x3, 0x10, 0x3, 0x10, 0x3, 0x10, 0x5, 0x10, 0x8a, 0xa, 0x10, 
    0x3, 0x11, 0x3, 0x11, 0x3, 0x11, 0x3, 0x11, 0x3, 0x11, 0x3, 0x11, 0x3, 
    0x12, 0x3, 0x12, 0x3, 0x13, 0x3, 0x13, 0x3, 0x13, 0x3, 0x13, 0x3, 0x14, 
    0x3, 0x14, 0x3, 0x15, 0x3, 0x15, 0x3, 0x16, 0x3, 0x16, 0x3, 0x16, 0x3, 
    0x16, 0x5, 0x16, 0xa0, 0xa, 0x16, 0x3, 0x17, 0x3, 0x17, 0x3, 0x17, 0x3, 
    0x17, 0x3, 0x17, 0x3, 0x17, 0x3, 0x17, 0x3, 0x17, 0x3, 0x17, 0x5, 0x17, 
    0xab, 0xa, 0x17, 0x3, 0x17, 0x3, 0x17, 0x3, 0x17, 0x3, 0x17, 0x3, 0x17, 
    0x3, 0x17, 0x3, 0x17, 0x3, 0x17, 0x3, 0x17, 0x3, 0x17, 0x3, 0x17, 0x3, 
    0x17, 0x3, 0x17, 0x3, 0x17, 0x3, 0x17, 0x3, 0x17, 0x3, 0x17, 0x3, 0x17, 
    0x7, 0x17, 0xbf, 0xa, 0x17, 0xc, 0x17, 0xe, 0x17, 0xc2, 0xb, 0x17, 0x3, 
    0x18, 0x3, 0x18, 0x3, 0x18, 0x3, 0x18, 0x3, 0x18, 0x3, 0x18, 0x5, 0x18, 
    0xca, 0xa, 0x18, 0x3, 0x19, 0x3, 0x19, 0x5, 0x19, 0xce, 0xa, 0x19, 0x3, 
    0x1a, 0x3, 0x1a, 0x3, 0x1b, 0x3, 0x1b, 0x3, 0x1b, 0x2, 0x3, 0x2c, 0x1c, 
    0x2, 0x4, 0x6, 0x8, 0xa, 0xc, 0xe, 0x10, 0x12, 0x14, 0x16, 0x18, 0x1a, 
    0x1c, 0x1e, 0x20, 0x22, 0x24, 0x26, 0x28, 0x2a, 0x2c, 0x2e, 0x30, 0x32, 
    0x34, 0x2, 0xb, 0x4, 0x2, 0x37, 0x39, 0x3c, 0x3c, 0x3, 0x2, 0x3a, 0x3b, 
    0x3, 0x2, 0x38, 0x39, 0x3, 0x2, 0x31, 0x34, 0x3, 0x2, 0x2f, 0x30, 0x3, 
    0x2, 0x3d, 0x3f, 0x3, 0x2, 0x35, 0x36, 0x3, 0x2, 0x3, 0x10, 0x3, 0x2, 
    0x18, 0x1f, 0x2, 0xd4, 0x2, 0x39, 0x3, 0x2, 0x2, 0x2, 0x4, 0x45, 0x3, 
    0x2, 0x2, 0x2, 0x6, 0x47, 0x3, 0x2, 0x2, 0x2, 0x8, 0x4e, 0x3, 0x2, 0x2, 
    0x2, 0xa, 0x50, 0x3, 0x2, 0x2, 0x2, 0xc, 0x53, 0x3, 0x2, 0x2, 0x2, 0xe, 
    0x57, 0x3, 0x2, 0x2, 0x2, 0x10, 0x59, 0x3, 0x2, 0x2, 0x2, 0x12, 0x62, 
    0x3, 0x2, 0x2, 0x2, 0x14, 0x66, 0x3, 0x2, 0x2, 0x2, 0x16, 0x68, 0x3, 
    0x2, 0x2, 0x2, 0x18, 0x71, 0x3, 0x2, 0x2, 0x2, 0x1a, 0x76, 0x3, 0x2, 
    0x2, 0x2, 0x1c, 0x78, 0x3, 0x2, 0x2, 0x2, 0x1e, 0x85, 0x3, 0x2, 0x2, 
    0x2, 0x20, 0x8b, 0x3, 0x2, 0x2, 0x2, 0x22, 0x91, 0x3, 0x2, 0x2, 0x2, 
    0x24, 0x93, 0x3, 0x2, 0x2, 0x2, 0x26, 0x97, 0x3, 0x2, 0x2, 0x2, 0x28, 
    0x99, 0x3, 0x2, 0x2, 0x2, 0x2a, 0x9f, 0x3, 0x2, 0x2, 0x2, 0x2c, 0xaa, 
    0x3, 0x2, 0x2, 0x2, 0x2e, 0xc9, 0x3, 0x2, 0x2, 0x2, 0x30, 0xcd, 0x3, 
    0x2, 0x2, 0x2, 0x32, 0xcf, 0x3, 0x2, 0x2, 0x2, 0x34, 0xd1, 0x3, 0x2, 
    0x2, 0x2, 0x36, 0x38, 0x5, 0x4, 0x3, 0x2, 0x37, 0x36, 0x3, 0x2, 0x2, 
    0x2, 0x38, 0x3b, 0x3, 0x2, 0x2, 0x2, 0x39, 0x37, 0x3, 0x2, 0x2, 0x2, 
    0x39, 0x3a, 0x3, 0x2, 0x2, 0x2, 0x3a, 0x3c, 0x3, 0x2, 0x2, 0x2, 0x3b, 
    0x39, 0x3, 0x2, 0x2, 0x2, 0x3c, 0x3d, 0x7, 0x2, 0x2, 0x3, 0x3d, 0x3, 
    0x3, 0x2, 0x2, 0x2, 0x3e, 0x46, 0x5, 0x18, 0xd, 0x2, 0x3f, 0x46, 0x5, 
    0x6, 0x4, 0x2, 0x40, 0x46, 0x5, 0xc, 0x7, 0x2, 0x41, 0x46, 0x5, 0x12, 
    0xa, 0x2, 0x42, 0x46, 0x5, 0x20, 0x11, 0x2, 0x43, 0x46, 0x5, 0x24, 0x13, 
    0x2, 0x44, 0x46, 0x5, 0x28, 0x15, 0x2, 0x45, 0x3e, 0x3, 0x2, 0x2, 0x2, 
    0x45, 0x3f, 0x3, 0x2, 0x2, 0x2, 0x45, 0x40, 0x3, 0x2, 0x2, 0x2, 0x45, 
    0x41, 0x3, 0x2, 0x2, 0x2, 0x45, 0x42, 0x3, 0x2, 0x2, 0x2, 0x45, 0x43, 
    0x3, 0x2, 0x2, 0x2, 0x45, 0x44, 0x3, 0x2, 0x2, 0x2, 0x46, 0x5, 0x3, 
    0x2, 0x2, 0x2, 0x47, 0x48, 0x5, 0x30, 0x19, 0x2, 0x48, 0x4a, 0x5, 0x8, 
    0x5, 0x2, 0x49, 0x4b, 0x5, 0xa, 0x6, 0x2, 0x4a, 0x49, 0x3, 0x2, 0x2, 
    0x2, 0x4a, 0x4b, 0x3, 0x2, 0x2, 0x2, 0x4b, 0x4c, 0x3, 0x2, 0x2, 0x2, 
    0x4c, 0x4d, 0x7, 0x29, 0x2, 0x2, 0x4d, 0x7, 0x3, 0x2, 0x2, 0x2, 0x4e, 
    0x4f, 0x7, 0x43, 0x2, 0x2, 0x4f, 0x9, 0x3, 0x2, 0x2, 0x2, 0x50, 0x51, 
    0x7, 0x2e, 0x2, 0x2, 0x51, 0x52, 0x5, 0x2c, 0x17, 0x2, 0x52, 0xb, 0x3, 
    0x2, 0x2, 0x2, 0x53, 0x54, 0x7, 0x14, 0x2, 0x2, 0x54, 0x55, 0x5, 0xe, 
    0x8, 0x2, 0x55, 0x56, 0x5, 0x10, 0x9, 0x2, 0x56, 0xd, 0x3, 0x2, 0x2, 
    0x2, 0x57, 0x58, 0x7, 0x43, 0x2, 0x2, 0x58, 0xf, 0x3, 0x2, 0x2, 0x2, 
    0x59, 0x5d, 0x7, 0x25, 0x2, 0x2, 0x5a, 0x5c, 0x5, 0x2a, 0x16, 0x2, 0x5b, 
    0x5a, 0x3, 0x2, 0x2, 0x2, 0x5c, 0x5f, 0x3, 0x2, 0x2, 0x2, 0x5d, 0x5b, 
    0x3, 0x2, 0x2, 0x2, 0x5d, 0x5e, 0x3, 0x2, 0x2, 0x2, 0x5e, 0x60, 0x3, 
    0x2, 0x2, 0x2, 0x5f, 0x5d, 0x3, 0x2, 0x2, 0x2, 0x60, 0x61, 0x7, 0x26, 
    0x2, 0x2, 0x61, 0x11, 0x3, 0x2, 0x2, 0x2, 0x62, 0x63, 0x7, 0x16, 0x2, 
    0x2, 0x63, 0x64, 0x5, 0x14, 0xb, 0x2, 0x64, 0x65, 0x5, 0x16, 0xc, 0x2, 
    0x65, 0x13, 0x3, 0x2, 0x2, 0x2, 0x66, 0x67, 0x7, 0x43, 0x2, 0x2, 0x67, 
    0x15, 0x3, 0x2, 0x2, 0x2, 0x68, 0x6c, 0x7, 0x25, 0x2, 0x2, 0x69, 0x6b, 
    0x5, 0x6, 0x4, 0x2, 0x6a, 0x69, 0x3, 0x2, 0x2, 0x2, 0x6b, 0x6e, 0x3, 
    0x2, 0x2, 0x2, 0x6c, 0x6a, 0x3, 0x2, 0x2, 0x2, 0x6c, 0x6d, 0x3, 0x2, 
    0x2, 0x2, 0x6d, 0x6f, 0x3, 0x2, 0x2, 0x2, 0x6e, 0x6c, 0x3, 0x2, 0x2, 
    0x2, 0x6f, 0x70, 0x7, 0x26, 0x2, 0x2, 0x70, 0x17, 0x3, 0x2, 0x2, 0x2, 
    0x71, 0x72, 0x5, 0x30, 0x19, 0x2, 0x72, 0x73, 0x5, 0x1a, 0xe, 0x2, 0x73, 
    0x74, 0x5, 0x1c, 0xf, 0x2, 0x74, 0x75, 0x5, 0x10, 0x9, 0x2, 0x75, 0x19, 
    0x3, 0x2, 0x2, 0x2, 0x76, 0x77, 0x7, 0x43, 0x2, 0x2, 0x77, 0x1b, 0x3, 
    0x2, 0x2, 0x2, 0x78, 0x81, 0x7, 0x23, 0x2, 0x2, 0x79, 0x7e, 0x5, 0x1e, 
    0x10, 0x2, 0x7a, 0x7b, 0x7, 0x2a, 0x2, 0x2, 0x7b, 0x7d, 0x5, 0x1e, 0x10, 
    0x2, 0x7c, 0x7a, 0x3, 0x2, 0x2, 0x2, 0x7d, 0x80, 0x3, 0x2, 0x2, 0x2, 
    0x7e, 0x7c, 0x3, 0x2, 0x2, 0x2, 0x7e, 0x7f, 0x3, 0x2, 0x2, 0x2, 0x7f, 
    0x82, 0x3, 0x2, 0x2, 0x2, 0x80, 0x7e, 0x3, 0x2, 0x2, 0x2, 0x81, 0x79, 
    0x3, 0x2, 0x2, 0x2, 0x81, 0x82, 0x3, 0x2, 0x2, 0x2, 0x82, 0x83, 0x3, 
    0x2, 0x2, 0x2, 0x83, 0x84, 0x7, 0x24, 0x2, 0x2, 0x84, 0x1d, 0x3, 0x2, 
    0x2, 0x2, 0x85, 0x86, 0x5, 0x30, 0x19, 0x2, 0x86, 0x89, 0x7, 0x43, 0x2, 
    0x2, 0x87, 0x88, 0x7, 0x2e, 0x2, 0x2, 0x88, 0x8a, 0x5, 0x34, 0x1b, 0x2, 
    0x89, 0x87, 0x3, 0x2, 0x2, 0x2, 0x89, 0x8a, 0x3, 0x2, 0x2, 0x2, 0x8a, 
    0x1f, 0x3, 0x2, 0x2, 0x2, 0x8b, 0x8c, 0x7, 0x11, 0x2, 0x2, 0x8c, 0x8d, 
    0x5, 0x22, 0x12, 0x2, 0x8d, 0x8e, 0x7, 0x2e, 0x2, 0x2, 0x8e, 0x8f, 0x5, 
    0x30, 0x19, 0x2, 0x8f, 0x90, 0x7, 0x29, 0x2, 0x2, 0x90, 0x21, 0x3, 0x2, 
    0x2, 0x2, 0x91, 0x92, 0x7, 0x43, 0x2, 0x2, 0x92, 0x23, 0x3, 0x2, 0x2, 
    0x2, 0x93, 0x94, 0x7, 0x17, 0x2, 0x2, 0x94, 0x95, 0x5, 0x26, 0x14, 0x2, 
    0x95, 0x96, 0x7, 0x29, 0x2, 0x2, 0x96, 0x25, 0x3, 0x2, 0x2, 0x2, 0x97, 
    0x98, 0x7, 0x43, 0x2, 0x2, 0x98, 0x27, 0x3, 0x2, 0x2, 0x2, 0x99, 0x9a, 
    0x7, 0x29, 0x2, 0x2, 0x9a, 0x29, 0x3, 0x2, 0x2, 0x2, 0x9b, 0xa0, 0x5, 
    0x6, 0x4, 0x2, 0x9c, 0xa0, 0x5, 0x20, 0x11, 0x2, 0x9d, 0xa0, 0x5, 0x24, 
    0x13, 0x2, 0x9e, 0xa0, 0x5, 0x28, 0x15, 0x2, 0x9f, 0x9b, 0x3, 0x2, 0x2, 
    0x2, 0x9f, 0x9c, 0x3, 0x2, 0x2, 0x2, 0x9f, 0x9d, 0x3, 0x2, 0x2, 0x2, 
    0x9f, 0x9e, 0x3, 0x2, 0x2, 0x2, 0xa0, 0x2b, 0x3, 0x2, 0x2, 0x2, 0xa1, 
    0xa2, 0x8, 0x17, 0x1, 0x2, 0xa2, 0xab, 0x5, 0x2e, 0x18, 0x2, 0xa3, 0xa4, 
    0x9, 0x2, 0x2, 0x2, 0xa4, 0xab, 0x5, 0x2c, 0x17, 0xa, 0xa5, 0xa6, 0x7, 
    0x23, 0x2, 0x2, 0xa6, 0xa7, 0x5, 0x30, 0x19, 0x2, 0xa7, 0xa8, 0x7, 0x24, 
    0x2, 0x2, 0xa8, 0xa9, 0x5, 0x2c, 0x17, 0x9, 0xa9, 0xab, 0x3, 0x2, 0x2, 
    0x2, 0xaa, 0xa1, 0x3, 0x2, 0x2, 0x2, 0xaa, 0xa3, 0x3, 0x2, 0x2, 0x2, 
    0xaa, 0xa5, 0x3, 0x2, 0x2, 0x2, 0xab, 0xc0, 0x3, 0x2, 0x2, 0x2, 0xac, 
    0xad, 0xc, 0x8, 0x2, 0x2, 0xad, 0xae, 0x9, 0x3, 0x2, 0x2, 0xae, 0xbf, 
    0x5, 0x2c, 0x17, 0x9, 0xaf, 0xb0, 0xc, 0x7, 0x2, 0x2, 0xb0, 0xb1, 0x9, 
    0x4, 0x2, 0x2, 0xb1, 0xbf, 0x5, 0x2c, 0x17, 0x8, 0xb2, 0xb3, 0xc, 0x6, 
    0x2, 0x2, 0xb3, 0xb4, 0x9, 0x5, 0x2, 0x2, 0xb4, 0xbf, 0x5, 0x2c, 0x17, 
    0x7, 0xb5, 0xb6, 0xc, 0x5, 0x2, 0x2, 0xb6, 0xb7, 0x9, 0x6, 0x2, 0x2, 
    0xb7, 0xbf, 0x5, 0x2c, 0x17, 0x6, 0xb8, 0xb9, 0xc, 0x4, 0x2, 0x2, 0xb9, 
    0xba, 0x9, 0x7, 0x2, 0x2, 0xba, 0xbf, 0x5, 0x2c, 0x17, 0x5, 0xbb, 0xbc, 
    0xc, 0x3, 0x2, 0x2, 0xbc, 0xbd, 0x9, 0x8, 0x2, 0x2, 0xbd, 0xbf, 0x5, 
    0x2c, 0x17, 0x4, 0xbe, 0xac, 0x3, 0x2, 0x2, 0x2, 0xbe, 0xaf, 0x3, 0x2, 
    0x2, 0x2, 0xbe, 0xb2, 0x3, 0x2, 0x2, 0x2, 0xbe, 0xb5, 0x3, 0x2, 0x2, 
    0x2, 0xbe, 0xb8, 0x3, 0x2, 0x2, 0x2, 0xbe, 0xbb, 0x3, 0x2, 0x2, 0x2, 
    0xbf, 0xc2, 0x3, 0x2, 0x2, 0x2, 0xc0, 0xbe, 0x3, 0x2, 0x2, 0x2, 0xc0, 
    0xc1, 0x3, 0x2, 0x2, 0x2, 0xc1, 0x2d, 0x3, 0x2, 0x2, 0x2, 0xc2, 0xc0, 
    0x3, 0x2, 0x2, 0x2, 0xc3, 0xc4, 0x7, 0x23, 0x2, 0x2, 0xc4, 0xc5, 0x5, 
    0x2c, 0x17, 0x2, 0xc5, 0xc6, 0x7, 0x24, 0x2, 0x2, 0xc6, 0xca, 0x3, 0x2, 
    0x2, 0x2, 0xc7, 0xca, 0x7, 0x43, 0x2, 0x2, 0xc8, 0xca, 0x5, 0x34, 0x1b, 
    0x2, 0xc9, 0xc3, 0x3, 0x2, 0x2, 0x2, 0xc9, 0xc7, 0x3, 0x2, 0x2, 0x2, 
    0xc9, 0xc8, 0x3, 0x2, 0x2, 0x2, 0xca, 0x2f, 0x3, 0x2, 0x2, 0x2, 0xcb, 
    0xce, 0x5, 0x32, 0x1a, 0x2, 0xcc, 0xce, 0x7, 0x43, 0x2, 0x2, 0xcd, 0xcb, 
    0x3, 0x2, 0x2, 0x2, 0xcd, 0xcc, 0x3, 0x2, 0x2, 0x2, 0xce, 0x31, 0x3, 
    0x2, 0x2, 0x2, 0xcf, 0xd0, 0x9, 0x9, 0x2, 0x2, 0xd0, 0x33, 0x3, 0x2, 
    0x2, 0x2, 0xd1, 0xd2, 0x9, 0xa, 0x2, 0x2, 0xd2, 0x35, 0x3, 0x2, 0x2, 
    0x2, 0x10, 0x39, 0x45, 0x4a, 0x5d, 0x6c, 0x7e, 0x81, 0x89, 0x9f, 0xaa, 
    0xbe, 0xc0, 0xc9, 0xcd, 
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
