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
        INT = 0x00 + 0x0,
        SYS = 0x00 + 0x1,
        BACK = 0x00 + 0x2,
        LBL = 0x00 + 0x3,
        JMP = 0x00 + 0x4,
        CALL = 0x00 + 0x5
    };

    enum MathsOpcodes {
        // math category: 0x20000000 + index
        ADD = 0x10 + 0x1,
        SUB = 0x10 + 0x2,
        MUL = 0x10 + 0x3,
        DIV = 0x10 + 0x4,
        MOD = 0x10 + 0xA,
        RAND = 0x10 + 0xB
    };

    enum MemoryOpcodes {
        // memory category: 0x30000000 + index
        PUSH = 0x20 + 0x0,
        POP = 0x20 + 0x1,
        STORE = 0x20 + 0x2,
        FREE = 0x20 + 0x3
    };

    enum ComparativeOpcodes {
        // comparative category: 0x40000000 + index
        CMP = 0x30 + 0x0,
        JWE = 0x30 + 0x1,
        JWD = 0x30 + 0x2,
        JWG = 0x30 + 0x3,
        JWL = 0x30 + 0x4
    };

    enum MemsegOpcodes {
        // memsegs category: 0x50000000 + index
        MEM = 0x40 + 0x0,
        TEMP = 0x40 + 0x1,
        PARAM = 0x40 + 0x2,
        NOST = 0x40 + 0x3
    };
};

#endif