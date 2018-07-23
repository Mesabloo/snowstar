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
    Consumer(Token(Token::Type::KEYWORD, "free"), Consumer::Store(), {Token(Token::Type::LITERAL_MEMORY, "mem_value")}),
    Consumer(Token(Token::Type::KEYWORD, "push"), Consumer::Store(Token(Token::Type::KEYWORD, "memseg"), Token(Token::Type::LITERAL_NUMBER_INT, "index")), {Token(Token::Type::LITERAL_NUMBER_INT, "value")}), // Literal
    Consumer(Token(Token::Type::KEYWORD, "push"), Consumer::Store(Token(Token::Type::KEYWORD, "memseg"), Token(Token::Type::LITERAL_NUMBER_INT, "index")), {Token(Token::Type::LITERAL_NUMBER_FLOAT, "value")}), // Literal
    Consumer(Token(Token::Type::KEYWORD, "push"), Consumer::Store(Token(Token::Type::KEYWORD, "memseg"), Token(Token::Type::LITERAL_NUMBER_INT, "index")), {Token(Token::Type::LITERAL_STRING, "value")}), // Literal
    Consumer(Token(Token::Type::KEYWORD, "push"), Consumer::Store(Token(Token::Type::KEYWORD, "memseg"), Token(Token::Type::LITERAL_NUMBER_INT, "index")), {Token(Token::Type::LITERAL_MEMORY, "value")}), // Literal.Memory
    Consumer(Token(Token::Type::KEYWORD, "pop"), Consumer::Store(Token(Token::Type::KEYWORD, "memseg"), Token(Token::Type::LITERAL_NUMBER_INT, "index")), {Token(Token::Type::LITERAL_MEMORY, "mem_value")}),
    Consumer(Token(Token::Type::KEYWORD, "rand"), Consumer::Store(Token(Token::Type::KEYWORD, "memseg"), Token(Token::Type::LITERAL_NUMBER_INT, "index")), {Token(Token::Type::LITERAL_NUMBER_INT, "low_bound"), Token(Token::Type::LITERAL_NUMBER_INT, "high_bound")}), // Literal
    Consumer(Token(Token::Type::KEYWORD, "rand"), Consumer::Store(Token(Token::Type::KEYWORD, "memseg"), Token(Token::Type::LITERAL_NUMBER_INT, "index")), {Token(Token::Type::LITERAL_NUMBER_INT, "low_bound"), Token(Token::Type::LITERAL_MEMORY, "high_bound")}), // Literal.Memory
    Consumer(Token(Token::Type::KEYWORD, "rand"), Consumer::Store(Token(Token::Type::KEYWORD, "memseg"), Token(Token::Type::LITERAL_NUMBER_INT, "index")), {Token(Token::Type::LITERAL_MEMORY, "low_bound"), Token(Token::Type::LITERAL_NUMBER_INT, "high_bound")}), // Literal.Memory
    Consumer(Token(Token::Type::KEYWORD, "rand"), Consumer::Store(Token(Token::Type::KEYWORD, "memseg"), Token(Token::Type::LITERAL_NUMBER_INT, "index")), {Token(Token::Type::LITERAL_MEMORY, "low_bound"), Token(Token::Type::LITERAL_MEMORY, "high_bound")}), // Literal.Memory
    Consumer(Token(Token::Type::KEYWORD, "lbl"), Consumer::Store(), {Token(Token::Type::LITERAL_STRING, "label_name")}),
    Consumer(Token(Token::Type::KEYWORD, "jmp"), Consumer::Store(), {Token(Token::Type::LITERAL_STRING, "label_name")}),
    Consumer(Token(Token::Type::KEYWORD, "call"), Consumer::Store(), {Token(Token::Type::LITERAL_STRING, "label_name")}),
    Consumer(Token(Token::Type::KEYWORD, "back"), Consumer::Store(), {}),
    Consumer(Token(Token::Type::KEYWORD, "jwe"), Consumer::Store(), {Token(Token::Type::LITERAL_STRING, "label_name")}),
    Consumer(Token(Token::Type::KEYWORD, "jwd"), Consumer::Store(), {Token(Token::Type::LITERAL_STRING, "label_name")}),
    Consumer(Token(Token::Type::KEYWORD, "jwg"), Consumer::Store(), {Token(Token::Type::LITERAL_STRING, "label_name")}),
    Consumer(Token(Token::Type::KEYWORD, "jwl"), Consumer::Store(), {Token(Token::Type::LITERAL_STRING, "label_name")}),
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

std::map<std::string, double const> info::m_bytes = {
    // system category: 0x10000000 + index
    {"int", 0x10'000'000 + 0x1},
    {"sys", 0x10'000'000 + 0x2},
    {"back", 0x10'000'000 + 0x3},
    {"lbl", 0x10'000'000 + 0x4},
    {"jmp", 0x10'000'000 + 0x5},
    {"call", 0x10'000'000 + 0x6},

    // math category: 0x20000000 + index
    {"add", 0x20'000'000 + 0x1},
    {"sub", 0x20'000'000 + 0x2},
    {"mul", 0x20'000'000 + 0x3},
    {"div", 0x20'000'000 + 0x4},
    {"mod", 0x20'000'000 + 0x5},
    {"rand", 0x20'000'000 + 0x6},

    // memory category: 0x30000000 + index
    {"push", 0x30'000'000 + 0x1},
    {"pop", 0x30'000'000 + 0x2},
    {"store", 0x30'000'000 + 0x3},
    {"free", 0x30'000'000 + 0x4},

    // comparative category: 0x40000000 + index
    {"cmp", 0x40'000'000 + 0x1},
    {"jwe", 0x40'000'000 + 0x2},
    {"jwd", 0x40'000'000 + 0x3},
    {"jwg", 0x40'000'000 + 0x4},
    {"jwl", 0x40'000'000 + 0x5},

    // memsegs category: 0x50000000 + index
    {"mem", 0x50'000'000 + 0x1},
    {"temp", 0x50'000'000 + 0x2},
    {"param", 0x50'000'000 + 0x3},
    {"nost", 0x50'000'000 + 0x4}

    // strings category: 0x21 + index
};