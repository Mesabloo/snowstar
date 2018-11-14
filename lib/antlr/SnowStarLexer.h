
// Generated from SnowStarLexer.g4 by ANTLR 4.7.1

#pragma once


#include "antlr4-runtime.h"




class  SnowStarLexer : public antlr4::Lexer {
public:
  enum {
    BOOL = 1, CHR = 2, I8 = 3, I16 = 4, I32 = 5, I64 = 6, F32 = 7, F64 = 8, 
    STR = 9, VOID = 10, WITH = 11, RET = 12, EXTERNAL = 13, UNIT = 14, ALIGN_AS = 15, 
    DTYPE = 16, IMPORT = 17, DEC_LITERAL = 18, HEX_LITERAL = 19, BIN_LITERAL = 20, 
    OCT_LITERAL = 21, FLOAT_LITERAL = 22, BOOL_LITERAL = 23, CHAR_LITERAL = 24, 
    STRING_LITERAL = 25, BEGIN_COM = 26, END_COM = 27, INLINE_COM = 28, 
    LPAREN = 29, RPAREN = 30, LBRACE = 31, RBRACE = 32, LBRACK = 33, RBRACK = 34, 
    SEMI = 35, COMMA = 36, DOT = 37, COLON = 38, COLONCOLON = 39, ASSIGN = 40, 
    EQUALS = 41, NEQUALS = 42, GREATER = 43, LOWER = 44, GREATER_EQ = 45, 
    LOWER_EQ = 46, LOGIC_OR = 47, LOGIC_AND = 48, LOGIC_NOT = 49, PLUS = 50, 
    MINUS = 51, STAR = 52, SLASH = 53, BIN_NOT = 54, BIN_AND = 55, BIN_OR = 56, 
    BIN_XOR = 57, WS = 58, COMMENT = 59, LINE_COMMENT = 60, IDENTIFIER = 61
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

