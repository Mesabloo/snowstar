
// Generated from SnowStarLexer.g4 by ANTLR 4.7.1

#pragma once


#include "antlr4-runtime.h"




class  SnowStarLexer : public antlr4::Lexer {
public:
  enum {
    BOOL = 1, CHR = 2, I8 = 3, UI8 = 4, I16 = 5, UI16 = 6, I32 = 7, UI32 = 8, 
    I64 = 9, UI64 = 10, F32 = 11, F64 = 12, STR = 13, VOID = 14, WITH = 15, 
    RET = 16, EXTERNAL = 17, UNIT = 18, ALIGN_AS = 19, DTYPE = 20, IMPORT = 21, 
    DEC_LITERAL = 22, HEX_LITERAL = 23, BIN_LITERAL = 24, OCT_LITERAL = 25, 
    FLOAT_LITERAL = 26, BOOL_LITERAL = 27, CHAR_LITERAL = 28, STRING_LITERAL = 29, 
    BEGIN_COM = 30, END_COM = 31, INLINE_COM = 32, LPAREN = 33, RPAREN = 34, 
    LBRACE = 35, RBRACE = 36, LBRACK = 37, RBRACK = 38, SEMI = 39, COMMA = 40, 
    DOT = 41, COLON = 42, COLONCOLON = 43, TO_ARROW = 44, ASSIGN = 45, EQUALS = 46, 
    NEQUALS = 47, GREATER = 48, LOWER = 49, GREATER_EQ = 50, LOWER_EQ = 51, 
    LOGIC_OR = 52, LOGIC_AND = 53, LOGIC_NOT = 54, PLUS = 55, MINUS = 56, 
    STAR = 57, SLASH = 58, BIN_NOT = 59, BIN_AND = 60, BIN_OR = 61, BIN_XOR = 62, 
    WS = 63, COMMENT = 64, LINE_COMMENT = 65, IDENTIFIER = 66
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

