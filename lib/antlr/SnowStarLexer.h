
// Generated from SnowStarLexer.g4 by ANTLR 4.7.1

#pragma once


#include "antlr4-runtime.h"




class  SnowStarLexer : public antlr4::Lexer {
public:
  enum {
    BOOLEAN = 1, CHAR = 2, INTEGER8 = 3, INTEGER16 = 4, INTEGER32 = 5, INTEGER64 = 6, 
    REAL16 = 7, REAL32 = 8, REAL64 = 9, VOID = 10, WITH = 11, DECIMAL_LITERAL = 12, 
    HEX_LITERAL = 13, BIN_LITERAL = 14, FLOAT_LITERAL = 15, BOOL_LITERAL = 16, 
    CHAR_LITERAL = 17, STRING_LITERAL = 18, NIL_LITERAL = 19, LPAREN = 20, 
    RPAREN = 21, LBRACE = 22, RBRACE = 23, LBRACK = 24, RBRACK = 25, SEMI = 26, 
    COMMA = 27, DOT = 28, ASSIGN = 29, WS = 30, COMMENT = 31, LINE_COMMENT = 32, 
    IDENTIFIER = 33
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

