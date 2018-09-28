
// Generated from SnowStarLexer.g4 by ANTLR 4.7.1

#pragma once


#include "antlr4-runtime.h"




class  SnowStarLexer : public antlr4::Lexer {
public:
  enum {
    BOOLEAN = 1, CHAR = 2, INTEGER8 = 3, INTEGER16 = 4, INTEGER32 = 5, INTEGER64 = 6, 
    REAL32 = 7, REAL64 = 8, VOID = 9, DECIMAL_LITERAL = 10, HEX_LITERAL = 11, 
    BIN_LITERAL = 12, FLOAT_LITERAL = 13, BOOL_LITERAL = 14, CHAR_LITERAL = 15, 
    STRING_LITERAL = 16, NIL_LITERAL = 17, LPAREN = 18, RPAREN = 19, LBRACE = 20, 
    RBRACE = 21, LBRACK = 22, RBRACK = 23, SEMI = 24, COMMA = 25, DOT = 26, 
    ASSIGN = 27, WS = 28, COMMENT = 29, LINE_COMMENT = 30, IDENTIFIER = 31
  };

  SnowStarLexer(antlr4::CharStream *input);
  ~SnowStarLexer();

  virtual std::string getGrammarFileName() const override;
  virtual const std::vector<std::string>& getRuleNames() const override;

  virtual const std::vector<std::string>& getChannelNames() const override;
  virtual const std::vector<std::string>& getModeNames() const override;
  virtual const std::vector<std::string>& getTokenNames() const override; // deprecated, use vocabulary instead
  virtual antlr4::dfa::Vocabulary& getVocabulary() const override;

  virtual const std::vector<uint16_t> getSerializedATN() const override;
  virtual const antlr4::atn::ATN& getATN() const override;

private:
  static std::vector<antlr4::dfa::DFA> _decisionToDFA;
  static antlr4::atn::PredictionContextCache _sharedContextCache;
  static std::vector<std::string> _ruleNames;
  static std::vector<std::string> _tokenNames;
  static std::vector<std::string> _channelNames;
  static std::vector<std::string> _modeNames;

  static std::vector<std::string> _literalNames;
  static std::vector<std::string> _symbolicNames;
  static antlr4::dfa::Vocabulary _vocabulary;
  static antlr4::atn::ATN _atn;
  static std::vector<uint16_t> _serializedATN;


  // Individual action functions triggered by action() above.

  // Individual semantic predicate functions triggered by sempred() above.

  struct Initializer {
    Initializer();
  };
  static Initializer _init;
};

