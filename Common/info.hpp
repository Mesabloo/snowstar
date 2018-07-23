#ifndef INFO_HPP
#define INFO_HPP

#include <vector>
#include <map>

#include <stdlib.h>

#include "../Compiler/Lexer/token.hpp"

struct info {
    static std::vector<Token> m_keywords;
    static std::vector<Consumer> m_syntax;
    static std::map<std::string, double const> m_bytes;
    
    enum Dividers {
        EOL = '\x16',
        NUMBER_FLOAT = '\x18',
        NUMBER_INTEGER = '\x15',
        STRING = '\x19',
        MEMORY = '\x17',
        INSTR_PARAMS = '\x10'
    };

    enum SystemOpcodes {
        // system category: 0x10000000 + index
        INT = 0x10'000'000 + 0x1,
        SYS = 0x10'000'000 + 0x2,
        BACK = 0x10'000'000 + 0x3,
        LBL = 0x10'000'000 + 0x4,
        JMP = 0x10'000'000 + 0x5,
        CALL = 0x10'000'000 + 0x6
    };

    enum MathsOpcodes {
        // math category: 0x20000000 + index
        ADD = 0x20'000'000 + 0x1,
        SUB = 0x20'000'000 + 0x2,
        MUL = 0x20'000'000 + 0x3,
        DIV = 0x20'000'000 + 0x4,
        MOD = 0x20'000'000 + 0x5,
        RAND = 0x20'000'000 + 0x6
    };

    enum MemoryOpcodes {
        // memory category: 0x30000000 + index
        PUSH = 0x30'000'000 + 0x1,
        POP = 0x30'000'000 + 0x2,
        STORE = 0x30'000'000 + 0x3,
        FREE = 0x30'000'000 + 0x4
    };

    enum ComparativeOpcodes {
        // comparative category: 0x40000000 + index
        CMP = 0x40'000'000 + 0x1,
        JWE = 0x40'000'000 + 0x2,
        JWD = 0x40'000'000 + 0x3,
        JWG = 0x40'000'000 + 0x4,
        JWL = 0x40'000'000 + 0x5
    };

    enum MemsegOpcodes {
        // memsegs category: 0x50000000 + index
        MEM = 0x50'000'000 + 0x1,
        TEMP = 0x50'000'000 + 0x2,
        PARAM = 0x50'000'000 + 0x3,
        NOST = 0x50'000'000 + 0x4
    };
};

#endif