
// Generated from SnowStarLexer.g4 by ANTLR 4.7.1

#pragma once


#include "antlr4-runtime.h"




class  SnowStarLexer : public antlr4::Lexer {
public:
  enum {
    BOOLEAN = 1, CHAR = 2, INTEGER8 = 3, INTEGER16 = 4, INTEGER32 = 5, INTEGER64 = 6, 
    REAL16 = 7, REAL32 = 8, REAL64 = 9, VOID = 10, WITH = 11, DECIMAL_LITERAL = 12, 
    HEX_LITERAL = 13, BIN_LITERAL = 14, FLOAT_LITERAL = 15, BOOL_LITERAL = 16, 
    CHAR_LITERAL = 17, STRING_LITERAL = 18, LPAREN = 19, RPAREN = 20, LBRACE = 21, 
    RBRACE = 22, LBRACK = 23, RBRACK = 24, SEMI = 25, COMMA = 26, DOT = 27, 
    ASSIGN = 28, EQUALS = 29, NEQUALS = 30, GREATER = 31, LOWER = 32, GREATER_EQ = 33, 
    LOWER_EQ = 34, LOGIC_OR = 35, LOGIC_AND = 36, LOGIC_NOT = 37, PLUS = 38, 
    MINUS = 39, STAR = 40, SLASH = 41, PERCENT = 42, BIN_NOT = 43, BIN_AND = 44, 
    BIN_OR = 45, BIN_XOR = 46, WS = 47, COMMENT = 48, LINE_COMMENT = 49, 
    IDENTIFIER = 50
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

