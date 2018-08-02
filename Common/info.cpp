#include "info.hpp"

std::vector<Token> info::m_keywords = {
    Token(Token::Type::KEYWORD, "mem"), // MEMory segmentation
    Token(Token::Type::KEYWORD, "param"), // PARAMeter segment
    Token(Token::Type::KEYWORD, "temp"), // TEMPorary data segment
    Token(Token::Type::KEYWORD, "nost"), // NO STorage

    Token(Token::Type::KEYWORD, "int"), // INTerrupt instruction
    Token(Token::Type::KEYWORD, "sys"), // SYStem instruction
    Token(Token::Type::KEYWORD, "store"), // STORE instruction
    Token(Token::Type::KEYWORD, "free"), // DELete instruction
    Token(Token::Type::KEYWORD, "push"), // PUSH instruction
    Token(Token::Type::KEYWORD, "pop"), // POP instruction
    Token(Token::Type::KEYWORD, "lbl"), // LaBeL declaration instruction
    Token(Token::Type::KEYWORD, "jmp"), // JuMP to label instruction
    Token(Token::Type::KEYWORD, "call"), // CALL function instruction
    Token(Token::Type::KEYWORD, "cmp"), // CoMPare instruction
    Token(Token::Type::KEYWORD, "jwe"), // JumpWhenEqual instruction
    Token(Token::Type::KEYWORD, "jwd"), // JumpWhenDifferent instruction
    Token(Token::Type::KEYWORD, "jwg"), // JumpWhenGreater instruction
    Token(Token::Type::KEYWORD, "jwl"), // JumpWhenLower instruction
    Token(Token::Type::KEYWORD, "back"), // BACK instruction
    Token(Token::Type::KEYWORD, "len"), // LENgth instruction
    Token(Token::Type::KEYWORD, "add"), // ADDition instruction
    Token(Token::Type::KEYWORD, "sub"), // SUBstraction instruction
    Token(Token::Type::KEYWORD, "mul"), // MULtiplication instruction
    Token(Token::Type::KEYWORD, "div"), // DIVision instruction
    Token(Token::Type::KEYWORD, "mod"), // MODulo instruction
    Token(Token::Type::KEYWORD, "rand") // RaNDom instruction
};

std::vector<Consumer> info::m_syntax = {
    Consumer(Token(), Consumer::Store(), {}),
    Consumer(Token(Token::Type::KEYWORD, "int"), Consumer::Store(), {Token(Token::Type::LITERAL_NUMBER_INT, "code")}),
    Consumer(Token(Token::Type::KEYWORD, "sys"), Consumer::Store(), {Token(Token::Type::LITERAL_NUMBER_INT, "code")}),
    Consumer(Token(Token::Type::KEYWORD, "sys"), Consumer::Store(Token(Token::Type::KEYWORD, "memseg"), Token(Token::Type::LITERAL_NUMBER_INT, "index")), {Token(Token::Type::LITERAL_NUMBER_INT, "code")}),
    Consumer(Token(Token::Type::KEYWORD, "store"), Consumer::Store(Token(Token::Type::KEYWORD, "memseg"), Token(Token::Type::LITERAL_NUMBER_INT, "index")), {Token(Token::Type::LITERAL_NUMBER_INT, "value")}), // Literal
    Consumer(Token(Token::Type::KEYWORD, "store"), Consumer::Store(Token(Token::Type::KEYWORD, "memseg"), Token(Token::Type::LITERAL_NUMBER_INT, "index")), {Token(Token::Type::LITERAL_NUMBER_FLOAT, "value")}), // Literal
    Consumer(Token(Token::Type::KEYWORD, "store"), Consumer::Store(Token(Token::Type::KEYWORD, "memseg"), Token(Token::Type::LITERAL_NUMBER_INT, "index")), {Token(Token::Type::LITERAL_STRING, "value")}), // Literal
    Consumer(Token(Token::Type::KEYWORD, "store"), Consumer::Store(Token(Token::Type::KEYWORD, "memseg"), Token(Token::Type::LITERAL_NUMBER_INT, "index")), {Token(Token::Type::LITERAL_MEMORY, "mem_value")}), // Literal.Memory
    Consumer(Token(Token::Type::KEYWORD, "free"), Consumer::Store(Token(Token::Type::KEYWORD, "memseg"), Token(Token::Type::LITERAL_NUMBER_INT, "index")), {}),
    Consumer(Token(Token::Type::KEYWORD, "push"), Consumer::Store(Token(Token::Type::KEYWORD, "memseg"), Token(Token::Type::LITERAL_NUMBER_INT, "index")), {Token(Token::Type::LITERAL_NUMBER_INT, "value")}), // Literal
    Consumer(Token(Token::Type::KEYWORD, "push"), Consumer::Store(Token(Token::Type::KEYWORD, "memseg"), Token(Token::Type::LITERAL_NUMBER_INT, "index")), {Token(Token::Type::LITERAL_NUMBER_FLOAT, "value")}), // Literal
    Consumer(Token(Token::Type::KEYWORD, "push"), Consumer::Store(Token(Token::Type::KEYWORD, "memseg"), Token(Token::Type::LITERAL_NUMBER_INT, "index")), {Token(Token::Type::LITERAL_STRING, "value")}), // Literal
    Consumer(Token(Token::Type::KEYWORD, "push"), Consumer::Store(Token(Token::Type::KEYWORD, "memseg"), Token(Token::Type::LITERAL_NUMBER_INT, "index")), {Token(Token::Type::LITERAL_MEMORY, "value")}), // Literal.Memory
    Consumer(Token(Token::Type::KEYWORD, "pop"), Consumer::Store(Token(Token::Type::KEYWORD, "memseg"), Token(Token::Type::LITERAL_NUMBER_INT, "index")), {}),
    Consumer(Token(Token::Type::KEYWORD, "rand"), Consumer::Store(Token(Token::Type::KEYWORD, "memseg"), Token(Token::Type::LITERAL_NUMBER_INT, "index")), {Token(Token::Type::LITERAL_NUMBER_INT, "low_bound"), Token(Token::Type::LITERAL_NUMBER_INT, "high_bound")}), // Literal
    Consumer(Token(Token::Type::KEYWORD, "rand"), Consumer::Store(Token(Token::Type::KEYWORD, "memseg"), Token(Token::Type::LITERAL_NUMBER_INT, "index")), {Token(Token::Type::LITERAL_NUMBER_INT, "low_bound"), Token(Token::Type::LITERAL_MEMORY, "high_bound")}), // Literal.Memory
    Consumer(Token(Token::Type::KEYWORD, "rand"), Consumer::Store(Token(Token::Type::KEYWORD, "memseg"), Token(Token::Type::LITERAL_NUMBER_INT, "index")), {Token(Token::Type::LITERAL_MEMORY, "low_bound"), Token(Token::Type::LITERAL_NUMBER_INT, "high_bound")}), // Literal.Memory
    Consumer(Token(Token::Type::KEYWORD, "rand"), Consumer::Store(Token(Token::Type::KEYWORD, "memseg"), Token(Token::Type::LITERAL_NUMBER_INT, "index")), {Token(Token::Type::LITERAL_MEMORY, "low_bound"), Token(Token::Type::LITERAL_MEMORY, "high_bound")}), // Literal.Memory
    Consumer(Token(Token::Type::KEYWORD, "lbl"), Consumer::Store(), {Token(Token::Type::LABEL, "label_name")}),
    Consumer(Token(Token::Type::KEYWORD, "jmp"), Consumer::Store(), {Token(Token::Type::LABEL, "label_name")}),
    Consumer(Token(Token::Type::KEYWORD, "call"), Consumer::Store(), {Token(Token::Type::LABEL, "label_name")}),
    Consumer(Token(Token::Type::KEYWORD, "back"), Consumer::Store(), {}),
    Consumer(Token(Token::Type::KEYWORD, "jwe"), Consumer::Store(), {Token(Token::Type::LABEL, "label_name")}),
    Consumer(Token(Token::Type::KEYWORD, "jwd"), Consumer::Store(), {Token(Token::Type::LABEL, "label_name")}),
    Consumer(Token(Token::Type::KEYWORD, "jwg"), Consumer::Store(), {Token(Token::Type::LABEL, "label_name")}),
    Consumer(Token(Token::Type::KEYWORD, "jwl"), Consumer::Store(), {Token(Token::Type::LABEL, "label_name")}),
    Consumer(Token(Token::Type::KEYWORD, "cmp"), Consumer::Store(), {Token(Token::Type::LITERAL_NUMBER_INT, "first_value"), Token(Token::Type::LITERAL_NUMBER_INT, "second_value")}),
    Consumer(Token(Token::Type::KEYWORD, "cmp"), Consumer::Store(), {Token(Token::Type::LITERAL_NUMBER_FLOAT, "first_value"), Token(Token::Type::LITERAL_NUMBER_FLOAT, "second_value")}),
    Consumer(Token(Token::Type::KEYWORD, "cmp"), Consumer::Store(), {Token(Token::Type::LITERAL_STRING, "first_value"), Token(Token::Type::LITERAL_STRING, "second_value")}),
    Consumer(Token(Token::Type::KEYWORD, "cmp"), Consumer::Store(), {Token(Token::Type::LITERAL_MEMORY, "first_value"), Token(Token::Type::LITERAL_MEMORY, "second_value")}),
    Consumer(Token(Token::Type::KEYWORD, "cmp"), Consumer::Store(), {Token(Token::Type::LITERAL_MEMORY, "first_value"), Token(Token::Type::LITERAL_STRING, "second_value")}),
    Consumer(Token(Token::Type::KEYWORD, "cmp"), Consumer::Store(), {Token(Token::Type::LITERAL_MEMORY, "first_value"), Token(Token::Type::LITERAL_NUMBER_INT, "second_value")}),
    Consumer(Token(Token::Type::KEYWORD, "cmp"), Consumer::Store(), {Token(Token::Type::LITERAL_MEMORY, "first_value"), Token(Token::Type::LITERAL_NUMBER_FLOAT, "second_value")}),
    Consumer(Token(Token::Type::KEYWORD, "cmp"), Consumer::Store(), {Token(Token::Type::LITERAL_STRING, "first_value"), Token(Token::Type::LITERAL_MEMORY, "second_value")}),
    Consumer(Token(Token::Type::KEYWORD, "cmp"), Consumer::Store(), {Token(Token::Type::LITERAL_NUMBER_INT, "first_value"), Token(Token::Type::LITERAL_MEMORY, "second_value")}),
    Consumer(Token(Token::Type::KEYWORD, "cmp"), Consumer::Store(), {Token(Token::Type::LITERAL_NUMBER_FLOAT, "first_value"), Token(Token::Type::LITERAL_MEMORY, "second_value")}),
    Consumer(Token(Token::Type::KEYWORD, "add"), Consumer::Store(Token(Token::Type::KEYWORD, "memseg"), Token(Token::Type::LITERAL_NUMBER_INT, "index")), {Token(Token::Type::LITERAL_NUMBER_INT, "low_bound"), Token(Token::Type::LITERAL_NUMBER_INT, "high_bound")}), // Literal
    Consumer(Token(Token::Type::KEYWORD, "add"), Consumer::Store(Token(Token::Type::KEYWORD, "memseg"), Token(Token::Type::LITERAL_NUMBER_INT, "index")), {Token(Token::Type::LITERAL_NUMBER_INT, "low_bound"), Token(Token::Type::LITERAL_MEMORY, "high_bound")}), // Literal.Memory
    Consumer(Token(Token::Type::KEYWORD, "add"), Consumer::Store(Token(Token::Type::KEYWORD, "memseg"), Token(Token::Type::LITERAL_NUMBER_INT, "index")), {Token(Token::Type::LITERAL_MEMORY, "low_bound"), Token(Token::Type::LITERAL_NUMBER_INT, "high_bound")}), // Literal.Memory
    Consumer(Token(Token::Type::KEYWORD, "add"), Consumer::Store(Token(Token::Type::KEYWORD, "memseg"), Token(Token::Type::LITERAL_NUMBER_INT, "index")), {Token(Token::Type::LITERAL_MEMORY, "low_bound"), Token(Token::Type::LITERAL_MEMORY, "high_bound")}), // Literal.Memory
    Consumer(Token(Token::Type::KEYWORD, "sub"), Consumer::Store(Token(Token::Type::KEYWORD, "memseg"), Token(Token::Type::LITERAL_NUMBER_INT, "index")), {Token(Token::Type::LITERAL_NUMBER_INT, "low_bound"), Token(Token::Type::LITERAL_NUMBER_INT, "high_bound")}), // Literal
    Consumer(Token(Token::Type::KEYWORD, "sub"), Consumer::Store(Token(Token::Type::KEYWORD, "memseg"), Token(Token::Type::LITERAL_NUMBER_INT, "index")), {Token(Token::Type::LITERAL_NUMBER_INT, "low_bound"), Token(Token::Type::LITERAL_MEMORY, "high_bound")}), // Literal.Memory
    Consumer(Token(Token::Type::KEYWORD, "sub"), Consumer::Store(Token(Token::Type::KEYWORD, "memseg"), Token(Token::Type::LITERAL_NUMBER_INT, "index")), {Token(Token::Type::LITERAL_MEMORY, "low_bound"), Token(Token::Type::LITERAL_NUMBER_INT, "high_bound")}), // Literal.Memory
    Consumer(Token(Token::Type::KEYWORD, "sub"), Consumer::Store(Token(Token::Type::KEYWORD, "memseg"), Token(Token::Type::LITERAL_NUMBER_INT, "index")), {Token(Token::Type::LITERAL_MEMORY, "low_bound"), Token(Token::Type::LITERAL_MEMORY, "high_bound")}), // Literal.Memory
    Consumer(Token(Token::Type::KEYWORD, "mul"), Consumer::Store(Token(Token::Type::KEYWORD, "memseg"), Token(Token::Type::LITERAL_NUMBER_INT, "index")), {Token(Token::Type::LITERAL_NUMBER_INT, "low_bound"), Token(Token::Type::LITERAL_NUMBER_INT, "high_bound")}), // Literal
    Consumer(Token(Token::Type::KEYWORD, "mul"), Consumer::Store(Token(Token::Type::KEYWORD, "memseg"), Token(Token::Type::LITERAL_NUMBER_INT, "index")), {Token(Token::Type::LITERAL_NUMBER_INT, "low_bound"), Token(Token::Type::LITERAL_MEMORY, "high_bound")}), // Literal.Memory
    Consumer(Token(Token::Type::KEYWORD, "mul"), Consumer::Store(Token(Token::Type::KEYWORD, "memseg"), Token(Token::Type::LITERAL_NUMBER_INT, "index")), {Token(Token::Type::LITERAL_MEMORY, "low_bound"), Token(Token::Type::LITERAL_NUMBER_INT, "high_bound")}), // Literal.Memory
    Consumer(Token(Token::Type::KEYWORD, "mul"), Consumer::Store(Token(Token::Type::KEYWORD, "memseg"), Token(Token::Type::LITERAL_NUMBER_INT, "index")), {Token(Token::Type::LITERAL_MEMORY, "low_bound"), Token(Token::Type::LITERAL_MEMORY, "high_bound")}), // Literal.Memory
    Consumer(Token(Token::Type::KEYWORD, "div"), Consumer::Store(Token(Token::Type::KEYWORD, "memseg"), Token(Token::Type::LITERAL_NUMBER_INT, "index")), {Token(Token::Type::LITERAL_NUMBER_INT, "low_bound"), Token(Token::Type::LITERAL_NUMBER_INT, "high_bound")}), // Literal
    Consumer(Token(Token::Type::KEYWORD, "div"), Consumer::Store(Token(Token::Type::KEYWORD, "memseg"), Token(Token::Type::LITERAL_NUMBER_INT, "index")), {Token(Token::Type::LITERAL_NUMBER_INT, "low_bound"), Token(Token::Type::LITERAL_MEMORY, "high_bound")}), // Literal.Memory
    Consumer(Token(Token::Type::KEYWORD, "div"), Consumer::Store(Token(Token::Type::KEYWORD, "memseg"), Token(Token::Type::LITERAL_NUMBER_INT, "index")), {Token(Token::Type::LITERAL_MEMORY, "low_bound"), Token(Token::Type::LITERAL_NUMBER_INT, "high_bound")}), // Literal.Memory
    Consumer(Token(Token::Type::KEYWORD, "div"), Consumer::Store(Token(Token::Type::KEYWORD, "memseg"), Token(Token::Type::LITERAL_NUMBER_INT, "index")), {Token(Token::Type::LITERAL_MEMORY, "low_bound"), Token(Token::Type::LITERAL_MEMORY, "high_bound")}), // Literal.Memory
    Consumer(Token(Token::Type::KEYWORD, "mod"), Consumer::Store(Token(Token::Type::KEYWORD, "memseg"), Token(Token::Type::LITERAL_NUMBER_INT, "index")), {Token(Token::Type::LITERAL_NUMBER_INT, "low_bound"), Token(Token::Type::LITERAL_NUMBER_INT, "high_bound")}), // Literal
    Consumer(Token(Token::Type::KEYWORD, "mod"), Consumer::Store(Token(Token::Type::KEYWORD, "memseg"), Token(Token::Type::LITERAL_NUMBER_INT, "index")), {Token(Token::Type::LITERAL_NUMBER_INT, "low_bound"), Token(Token::Type::LITERAL_MEMORY, "high_bound")}), // Literal.Memory
    Consumer(Token(Token::Type::KEYWORD, "mod"), Consumer::Store(Token(Token::Type::KEYWORD, "memseg"), Token(Token::Type::LITERAL_NUMBER_INT, "index")), {Token(Token::Type::LITERAL_MEMORY, "low_bound"), Token(Token::Type::LITERAL_NUMBER_INT, "high_bound")}), // Literal.Memory
    Consumer(Token(Token::Type::KEYWORD, "mod"), Consumer::Store(Token(Token::Type::KEYWORD, "memseg"), Token(Token::Type::LITERAL_NUMBER_INT, "index")), {Token(Token::Type::LITERAL_MEMORY, "low_bound"), Token(Token::Type::LITERAL_MEMORY, "high_bound")}) // Literal.Memory
};

std::map<std::string, uint8_t const> info::m_bytes = {
    // system category: 0x10000000 + index
    {"INT", 0x00 + 0x0},
    {"SYS", 0x00 + 0x1},
    {"BACK", 0x00 + 0x2},
    {"LABEL", 0x00 + 0x3},
    {"JMP", 0x00 + 0x4},
    {"CALL", 0x00 + 0x5},

    // math category: 0x20000000 + index
    {"ADD", 0x10 + 0x1},
    {"SUB", 0x10 + 0x2},
    {"MUL", 0x10 + 0x3},
    {"DIV", 0x10 + 0x4},
    {"MOD", 0x10 + 0xA},
    {"RAND", 0x10 + 0xB},

    // memory category: 0x30000000 + index
    {"PUSH", 0x20 + 0x0},
    {"POP", 0x20 + 0x1},
    {"STORE", 0x20 + 0x2},
    {"FREE", 0x20 + 0x3},

    // comparative category: 0x40000000 + index
    {"CMP", 0x30 + 0x0},
    {"JWE", 0x30 + 0x1},
    {"JWD", 0x30 + 0x2},
    {"JWG", 0x30 + 0x3},
    {"JWL", 0x30 + 0x4},

    // memsegs category: 0x50000000 + index
    {"mem", 0x40 + 0x0},
    {"temp", 0x40 + 0x1},
    {"param", 0x40 + 0x2},
    {"nost", 0x40 + 0x3},

    // strings category: 0x21 + index

    // special instructions category: 0x60 + index
    {"LOAD_CONST", 0x50 + 0x0},
    {"LOAD_MEM", 0x50 + 0x1},
    {"LABEL_TABLE", 0x50 + 0x2},
    {"CONST_TABLE", 0x50 + 0x3},
    {"CODE_TABLE", 0x50 + 0x4}
};