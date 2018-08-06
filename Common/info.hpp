#ifndef INFO_HPP
#define INFO_HPP

#include <vector>
#include <map>

#include <stdlib.h>

#include <Lexer/token.hpp>

struct info {
    static std::vector<Token> m_keywords;
    static std::vector<Consumer> m_syntax;
    static std::map<std::string, uint8_t const> m_bytes;

    enum SystemOpcodes {
        // system category: 0x00 + index
        INT = 0x00 + 0x0,
        SYS = 0x00 + 0x1,
        BACK = 0x00 + 0x2,
        LABEL = 0x00 + 0x3,
        JMP = 0x00 + 0x4,
        CALL = 0x00 + 0x5
    };

    enum MathsOpcodes {
        // math category: 0x10 + index
        ADD = 0x10 + 0x0,
        SUB = 0x10 + 0x1,
        MUL = 0x10 + 0x2,
        DIV = 0x10 + 0x3,
        MOD = 0x10 + 0x4,
        RAND = 0x10 + 0x5,
        AND = 0x10 + 0x6,
        OR = 0x10 + 0x7,
        XOR = 0x10 + 0x8,
        NOT = 0x10 + 0x9,
        ADDF = 0x10 + 0xA,
        SUBF = 0x10 + 0xB,
        MULF = 0x10 + 0xC,
        DIVF = 0x10 + 0xD,
        RANDF = 0x10 + 0xE
    };

    enum MemoryOpcodes {
        // memory category: 0x20 + index
        PUSH = 0x20 + 0x0,
        POP = 0x20 + 0x1,
        STORE = 0x20 + 0x2,
        FREE = 0x20 + 0x3,
        ITOS = 0x20 + 0x4,
        FTOS = 0x20 + 0x5
    };

    enum ComparativeOpcodes {
        // comparative category: 0x30 + index
        CMP = 0x30 + 0x0,
        JWE = 0x30 + 0x1,
        JWD = 0x30 + 0x2,
        JWG = 0x30 + 0x3,
        JWL = 0x30 + 0x4
    };

    enum MemsegOpcodes {
        // memsegs category: 0x40 + index
        MEM = 0x40 + 0x0,
        TEMP = 0x40 + 0x1,
        PARAM = 0x40 + 0x2,
        NOST = 0x40 + 0x3
    };

    enum SpecialOpcodes {
        // special opcodes category: 0x50 + index
        LOAD_CONST = 0x50 + 0x0,
        LOAD_MEM = 0x50 + 0x1,
        LABEL_TABLE = 0x50 + 0x2,
        CONST_TABLE = 0x50 + 0x3,
        CODE_TABLE = 0x50 + 0x4
    };
};

#endif