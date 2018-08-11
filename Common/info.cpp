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
    Token(Token::Type::KEYWORD, "add"), // ADDition instruction
    Token(Token::Type::KEYWORD, "sub"), // SUBstraction instruction
    Token(Token::Type::KEYWORD, "mul"), // MULtiplication instruction
    Token(Token::Type::KEYWORD, "div"), // DIVision instruction
    Token(Token::Type::KEYWORD, "mod"), // MODulo instruction
    Token(Token::Type::KEYWORD, "rand"), // RaNDom instruction
    Token(Token::Type::KEYWORD, "itos"), // IntegerTOString instruction
    Token(Token::Type::KEYWORD, "ftos"), // FloatTOString instruction
    Token(Token::Type::KEYWORD, "and"), // bitwise AND instruction
    Token(Token::Type::KEYWORD, "or"), // bitwise OR instruction
    Token(Token::Type::KEYWORD, "xor"), // bitwise XOR instruction
    Token(Token::Type::KEYWORD, "not"), // bitwise NOT instruction
    Token(Token::Type::KEYWORD, "addf"), // ADD Float instruction
    Token(Token::Type::KEYWORD, "subf"), // SUB Float instruction
    Token(Token::Type::KEYWORD, "mulf"), // MUL Float instruction
    Token(Token::Type::KEYWORD, "divf"), // DIV Float instruction
    Token(Token::Type::KEYWORD, "randf"), // RAND Float instruction
    Token(Token::Type::KEYWORD, "itof"), // IntegerTOFloat instruction
    Token(Token::Type::KEYWORD, "ftoi"), // FloatTOInteger instruction
    Token(Token::Type::KEYWORD, "stoi"), // StringTOInteger instruction
    Token(Token::Type::KEYWORD, "stof"), // StringTOFloat instruction
    Token(Token::Type::KEYWORD, "ret") // RETurn instruction
};

std::vector<Consumer> info::m_syntax = {
    Consumer(Token(), Consumer::Store(), {}),
    Consumer(Token(Token::Type::KEYWORD, "int"), Consumer::Store(), {Token(Token::Type::LITERAL_NUMBER_INT, "code")}),
    Consumer(Token(Token::Type::KEYWORD, "sys"), Consumer::Store(), {Token(Token::Type::LITERAL_NUMBER_INT, "code")}),
    Consumer(Token(Token::Type::KEYWORD, "sys"), Consumer::Store(Token(Token::Type::KEYWORD, "memseg"), Token(Token::Type::LITERAL_NUMBER_INT, "index")), {Token(Token::Type::LITERAL_NUMBER_INT, "code")}),
    Consumer(Token(Token::Type::KEYWORD, "store"), Consumer::Store(Token(Token::Type::KEYWORD, "memory"), Token(Token::Type::LITERAL_NUMBER_INT, "index")), {Token(Token::Type::LITERAL_NUMBER_INT, "value")}), // Literal
    Consumer(Token(Token::Type::KEYWORD, "store"), Consumer::Store(Token(Token::Type::KEYWORD, "memory"), Token(Token::Type::LITERAL_NUMBER_INT, "index")), {Token(Token::Type::LITERAL_NUMBER_FLOAT, "value")}), // Literal
    Consumer(Token(Token::Type::KEYWORD, "store"), Consumer::Store(Token(Token::Type::KEYWORD, "memory"), Token(Token::Type::LITERAL_NUMBER_INT, "index")), {Token(Token::Type::LITERAL_STRING, "value")}), // Literal
    Consumer(Token(Token::Type::KEYWORD, "store"), Consumer::Store(Token(Token::Type::KEYWORD, "memory"), Token(Token::Type::LITERAL_NUMBER_INT, "index")), {Token(Token::Type::LITERAL_MEMORY, "mem_value")}), // Literal.Memory
    Consumer(Token(Token::Type::KEYWORD, "free"), Consumer::Store(Token(Token::Type::KEYWORD, "memory"), Token(Token::Type::LITERAL_NUMBER_INT, "index")), {}),
    Consumer(Token(Token::Type::KEYWORD, "push"), Consumer::Store(Token(Token::Type::KEYWORD, "stack"), Token(Token::Type::LITERAL_NUMBER_INT, "0")), {Token(Token::Type::LITERAL_NUMBER_INT, "value")}), // Literal
    Consumer(Token(Token::Type::KEYWORD, "push"), Consumer::Store(Token(Token::Type::KEYWORD, "stack"), Token(Token::Type::LITERAL_NUMBER_INT, "0")), {Token(Token::Type::LITERAL_NUMBER_FLOAT, "value")}), // Literal
    Consumer(Token(Token::Type::KEYWORD, "push"), Consumer::Store(Token(Token::Type::KEYWORD, "stack"), Token(Token::Type::LITERAL_NUMBER_INT, "0")), {Token(Token::Type::LITERAL_STRING, "value")}), // Literal
    Consumer(Token(Token::Type::KEYWORD, "push"), Consumer::Store(Token(Token::Type::KEYWORD, "stack"), Token(Token::Type::LITERAL_NUMBER_INT, "0")), {Token(Token::Type::LITERAL_MEMORY, "value")}), // Literal.Memory
    Consumer(Token(Token::Type::KEYWORD, "pop"), Consumer::Store(Token(Token::Type::KEYWORD, "stack"), Token(Token::Type::LITERAL_NUMBER_INT, "0")), {}),
    Consumer(Token(Token::Type::KEYWORD, "rand"), Consumer::Store(Token(Token::Type::KEYWORD, "memseg"), Token(Token::Type::LITERAL_NUMBER_INT, "index")), {Token(Token::Type::LITERAL_NUMBER_INT, "low_bound"), Token(Token::Type::LITERAL_NUMBER_INT, "high_bound")}), // Literal
    Consumer(Token(Token::Type::KEYWORD, "rand"), Consumer::Store(Token(Token::Type::KEYWORD, "memseg"), Token(Token::Type::LITERAL_NUMBER_INT, "index")), {Token(Token::Type::LITERAL_NUMBER_INT, "low_bound"), Token(Token::Type::LITERAL_MEMORY, "high_bound")}), // Literal.Memory
    Consumer(Token(Token::Type::KEYWORD, "rand"), Consumer::Store(Token(Token::Type::KEYWORD, "memseg"), Token(Token::Type::LITERAL_NUMBER_INT, "index")), {Token(Token::Type::LITERAL_MEMORY, "low_bound"), Token(Token::Type::LITERAL_NUMBER_INT, "high_bound")}), // Literal.Memory
    Consumer(Token(Token::Type::KEYWORD, "rand"), Consumer::Store(Token(Token::Type::KEYWORD, "memseg"), Token(Token::Type::LITERAL_NUMBER_INT, "index")), {Token(Token::Type::LITERAL_MEMORY, "low_bound"), Token(Token::Type::LITERAL_MEMORY, "high_bound")}), // Literal.Memory
    Consumer(Token(Token::Type::KEYWORD, "lbl"), Consumer::Store(), {Token(Token::Type::LABEL, "label_name")}),
    Consumer(Token(Token::Type::KEYWORD, "jmp"), Consumer::Store(), {Token(Token::Type::LABEL, "label_name")}),
    Consumer(Token(Token::Type::KEYWORD, "call"), Consumer::Store(), {Token(Token::Type::LABEL, "label_name")}),
    Consumer(Token(Token::Type::KEYWORD, "back"), Consumer::Store(), {Token(Token::Type::LITERAL_MEMORY, "return_value")}), // Literal.Memory
    Consumer(Token(Token::Type::KEYWORD, "back"), Consumer::Store(), {Token(Token::Type::LITERAL_STRING, "return_value")}), // Literal
    Consumer(Token(Token::Type::KEYWORD, "back"), Consumer::Store(), {Token(Token::Type::LITERAL_NUMBER_FLOAT, "return_value")}), // Literal
    Consumer(Token(Token::Type::KEYWORD, "back"), Consumer::Store(), {Token(Token::Type::LITERAL_NUMBER_INT, "return_value")}), // Literal
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
    Consumer(Token(Token::Type::KEYWORD, "mod"), Consumer::Store(Token(Token::Type::KEYWORD, "memseg"), Token(Token::Type::LITERAL_NUMBER_INT, "index")), {Token(Token::Type::LITERAL_MEMORY, "low_bound"), Token(Token::Type::LITERAL_MEMORY, "high_bound")}), // Literal.Memory
    Consumer(Token(Token::Type::KEYWORD, "itos"), Consumer::Store(Token(Token::Type::KEYWORD, "memseg"), Token(Token::Type::LITERAL_NUMBER_INT, "index")), {Token(Token::Type::LITERAL_NUMBER_INT, "to_cast")}), // Literal
    Consumer(Token(Token::Type::KEYWORD, "itos"), Consumer::Store(Token(Token::Type::KEYWORD, "memseg"), Token(Token::Type::LITERAL_NUMBER_INT, "index")), {Token(Token::Type::LITERAL_MEMORY, "to_cast")}), // Literal.Memory
    Consumer(Token(Token::Type::KEYWORD, "ftos"), Consumer::Store(Token(Token::Type::KEYWORD, "memseg"), Token(Token::Type::LITERAL_NUMBER_INT, "index")), {Token(Token::Type::LITERAL_NUMBER_FLOAT, "to_cast")}), // Literal
    Consumer(Token(Token::Type::KEYWORD, "ftos"), Consumer::Store(Token(Token::Type::KEYWORD, "memseg"), Token(Token::Type::LITERAL_NUMBER_INT, "index")), {Token(Token::Type::LITERAL_MEMORY, "to_cast")}), // Literal.Memory
    Consumer(Token(Token::Type::KEYWORD, "not"), Consumer::Store(Token(Token::Type::KEYWORD, "memseg"), Token(Token::Type::LITERAL_NUMBER_INT, "index")), {Token(Token::Type::LITERAL_NUMBER_INT, "to_negate")}), // Literal
    Consumer(Token(Token::Type::KEYWORD, "not"), Consumer::Store(Token(Token::Type::KEYWORD, "memseg"), Token(Token::Type::LITERAL_NUMBER_INT, "index")), {Token(Token::Type::LITERAL_MEMORY, "to_negate")}), // Literal.Memory
    Consumer(Token(Token::Type::KEYWORD, "and"), Consumer::Store(Token(Token::Type::KEYWORD, "memseg"), Token(Token::Type::LITERAL_NUMBER_INT, "index")), {Token(Token::Type::LITERAL_NUMBER_INT, "first"), Token(Token::Type::LITERAL_NUMBER_INT, "second")}), // Literal + Literal
    Consumer(Token(Token::Type::KEYWORD, "and"), Consumer::Store(Token(Token::Type::KEYWORD, "memseg"), Token(Token::Type::LITERAL_NUMBER_INT, "index")), {Token(Token::Type::LITERAL_MEMORY, "first"), Token(Token::Type::LITERAL_NUMBER_INT, "second")}), // Literal.Memory + Literal
    Consumer(Token(Token::Type::KEYWORD, "and"), Consumer::Store(Token(Token::Type::KEYWORD, "memseg"), Token(Token::Type::LITERAL_NUMBER_INT, "index")), {Token(Token::Type::LITERAL_NUMBER_INT, "first"), Token(Token::Type::LITERAL_MEMORY, "second")}), // Literal + Literal.Memory
    Consumer(Token(Token::Type::KEYWORD, "and"), Consumer::Store(Token(Token::Type::KEYWORD, "memseg"), Token(Token::Type::LITERAL_NUMBER_INT, "index")), {Token(Token::Type::LITERAL_MEMORY, "first"), Token(Token::Type::LITERAL_MEMORY, "second")}), // Literal.Memory + Literal.Memory
    Consumer(Token(Token::Type::KEYWORD, "or"), Consumer::Store(Token(Token::Type::KEYWORD, "memseg"), Token(Token::Type::LITERAL_NUMBER_INT, "index")), {Token(Token::Type::LITERAL_NUMBER_INT, "first"), Token(Token::Type::LITERAL_NUMBER_INT, "second")}), // Literal + Literal
    Consumer(Token(Token::Type::KEYWORD, "or"), Consumer::Store(Token(Token::Type::KEYWORD, "memseg"), Token(Token::Type::LITERAL_NUMBER_INT, "index")), {Token(Token::Type::LITERAL_MEMORY, "first"), Token(Token::Type::LITERAL_NUMBER_INT, "second")}), // Literal.Memory + Literal
    Consumer(Token(Token::Type::KEYWORD, "or"), Consumer::Store(Token(Token::Type::KEYWORD, "memseg"), Token(Token::Type::LITERAL_NUMBER_INT, "index")), {Token(Token::Type::LITERAL_NUMBER_INT, "first"), Token(Token::Type::LITERAL_MEMORY, "second")}), // Literal + Literal.Memory
    Consumer(Token(Token::Type::KEYWORD, "or"), Consumer::Store(Token(Token::Type::KEYWORD, "memseg"), Token(Token::Type::LITERAL_NUMBER_INT, "index")), {Token(Token::Type::LITERAL_MEMORY, "first"), Token(Token::Type::LITERAL_MEMORY, "second")}), // Literal.Memory + Literal.Memory
    Consumer(Token(Token::Type::KEYWORD, "xor"), Consumer::Store(Token(Token::Type::KEYWORD, "memseg"), Token(Token::Type::LITERAL_NUMBER_INT, "index")), {Token(Token::Type::LITERAL_NUMBER_INT, "first"), Token(Token::Type::LITERAL_NUMBER_INT, "second")}), // Literal + Literal
    Consumer(Token(Token::Type::KEYWORD, "xor"), Consumer::Store(Token(Token::Type::KEYWORD, "memseg"), Token(Token::Type::LITERAL_NUMBER_INT, "index")), {Token(Token::Type::LITERAL_MEMORY, "first"), Token(Token::Type::LITERAL_NUMBER_INT, "second")}), // Literal.Memory + Literal
    Consumer(Token(Token::Type::KEYWORD, "xor"), Consumer::Store(Token(Token::Type::KEYWORD, "memseg"), Token(Token::Type::LITERAL_NUMBER_INT, "index")), {Token(Token::Type::LITERAL_NUMBER_INT, "first"), Token(Token::Type::LITERAL_MEMORY, "second")}), // Literal + Literal.Memory
    Consumer(Token(Token::Type::KEYWORD, "xor"), Consumer::Store(Token(Token::Type::KEYWORD, "memseg"), Token(Token::Type::LITERAL_NUMBER_INT, "index")), {Token(Token::Type::LITERAL_MEMORY, "first"), Token(Token::Type::LITERAL_MEMORY, "second")}), // Literal.Memory + Literal.Memory
    Consumer(Token(Token::Type::KEYWORD, "addf"), Consumer::Store(Token(Token::Type::KEYWORD, "memseg"), Token(Token::Type::LITERAL_NUMBER_INT, "index")), {Token(Token::Type::LITERAL_NUMBER_FLOAT, "low_bound"), Token(Token::Type::LITERAL_NUMBER_FLOAT, "high_bound")}), // Literal
    Consumer(Token(Token::Type::KEYWORD, "addf"), Consumer::Store(Token(Token::Type::KEYWORD, "memseg"), Token(Token::Type::LITERAL_NUMBER_INT, "index")), {Token(Token::Type::LITERAL_NUMBER_FLOAT, "low_bound"), Token(Token::Type::LITERAL_MEMORY, "high_bound")}), // Literal.Memory
    Consumer(Token(Token::Type::KEYWORD, "addf"), Consumer::Store(Token(Token::Type::KEYWORD, "memseg"), Token(Token::Type::LITERAL_NUMBER_INT, "index")), {Token(Token::Type::LITERAL_MEMORY, "low_bound"), Token(Token::Type::LITERAL_NUMBER_FLOAT, "high_bound")}), // Literal.Memory
    Consumer(Token(Token::Type::KEYWORD, "addf"), Consumer::Store(Token(Token::Type::KEYWORD, "memseg"), Token(Token::Type::LITERAL_NUMBER_INT, "index")), {Token(Token::Type::LITERAL_MEMORY, "low_bound"), Token(Token::Type::LITERAL_MEMORY, "high_bound")}), // Literal.Memory
    Consumer(Token(Token::Type::KEYWORD, "subf"), Consumer::Store(Token(Token::Type::KEYWORD, "memseg"), Token(Token::Type::LITERAL_NUMBER_INT, "index")), {Token(Token::Type::LITERAL_NUMBER_FLOAT, "low_bound"), Token(Token::Type::LITERAL_NUMBER_FLOAT, "high_bound")}), // Literal
    Consumer(Token(Token::Type::KEYWORD, "subf"), Consumer::Store(Token(Token::Type::KEYWORD, "memseg"), Token(Token::Type::LITERAL_NUMBER_INT, "index")), {Token(Token::Type::LITERAL_NUMBER_FLOAT, "low_bound"), Token(Token::Type::LITERAL_MEMORY, "high_bound")}), // Literal.Memory
    Consumer(Token(Token::Type::KEYWORD, "subf"), Consumer::Store(Token(Token::Type::KEYWORD, "memseg"), Token(Token::Type::LITERAL_NUMBER_INT, "index")), {Token(Token::Type::LITERAL_MEMORY, "low_bound"), Token(Token::Type::LITERAL_NUMBER_FLOAT, "high_bound")}), // Literal.Memory
    Consumer(Token(Token::Type::KEYWORD, "subf"), Consumer::Store(Token(Token::Type::KEYWORD, "memseg"), Token(Token::Type::LITERAL_NUMBER_INT, "index")), {Token(Token::Type::LITERAL_MEMORY, "low_bound"), Token(Token::Type::LITERAL_MEMORY, "high_bound")}), // Literal.Memory
    Consumer(Token(Token::Type::KEYWORD, "mulf"), Consumer::Store(Token(Token::Type::KEYWORD, "memseg"), Token(Token::Type::LITERAL_NUMBER_INT, "index")), {Token(Token::Type::LITERAL_NUMBER_FLOAT, "low_bound"), Token(Token::Type::LITERAL_NUMBER_FLOAT, "high_bound")}), // Literal
    Consumer(Token(Token::Type::KEYWORD, "mulf"), Consumer::Store(Token(Token::Type::KEYWORD, "memseg"), Token(Token::Type::LITERAL_NUMBER_INT, "index")), {Token(Token::Type::LITERAL_NUMBER_FLOAT, "low_bound"), Token(Token::Type::LITERAL_MEMORY, "high_bound")}), // Literal.Memory
    Consumer(Token(Token::Type::KEYWORD, "mulf"), Consumer::Store(Token(Token::Type::KEYWORD, "memseg"), Token(Token::Type::LITERAL_NUMBER_INT, "index")), {Token(Token::Type::LITERAL_MEMORY, "low_bound"), Token(Token::Type::LITERAL_NUMBER_FLOAT, "high_bound")}), // Literal.Memory
    Consumer(Token(Token::Type::KEYWORD, "mulf"), Consumer::Store(Token(Token::Type::KEYWORD, "memseg"), Token(Token::Type::LITERAL_NUMBER_INT, "index")), {Token(Token::Type::LITERAL_MEMORY, "low_bound"), Token(Token::Type::LITERAL_MEMORY, "high_bound")}), // Literal.Memory
    Consumer(Token(Token::Type::KEYWORD, "divf"), Consumer::Store(Token(Token::Type::KEYWORD, "memseg"), Token(Token::Type::LITERAL_NUMBER_INT, "index")), {Token(Token::Type::LITERAL_NUMBER_FLOAT, "low_bound"), Token(Token::Type::LITERAL_NUMBER_FLOAT, "high_bound")}), // Literal
    Consumer(Token(Token::Type::KEYWORD, "divf"), Consumer::Store(Token(Token::Type::KEYWORD, "memseg"), Token(Token::Type::LITERAL_NUMBER_INT, "index")), {Token(Token::Type::LITERAL_NUMBER_FLOAT, "low_bound"), Token(Token::Type::LITERAL_MEMORY, "high_bound")}), // Literal.Memory
    Consumer(Token(Token::Type::KEYWORD, "divf"), Consumer::Store(Token(Token::Type::KEYWORD, "memseg"), Token(Token::Type::LITERAL_NUMBER_INT, "index")), {Token(Token::Type::LITERAL_MEMORY, "low_bound"), Token(Token::Type::LITERAL_NUMBER_FLOAT, "high_bound")}), // Literal.Memory
    Consumer(Token(Token::Type::KEYWORD, "divf"), Consumer::Store(Token(Token::Type::KEYWORD, "memseg"), Token(Token::Type::LITERAL_NUMBER_INT, "index")), {Token(Token::Type::LITERAL_MEMORY, "low_bound"), Token(Token::Type::LITERAL_MEMORY, "high_bound")}), // Literal.Memory
    Consumer(Token(Token::Type::KEYWORD, "randf"), Consumer::Store(Token(Token::Type::KEYWORD, "memseg"), Token(Token::Type::LITERAL_NUMBER_INT, "index")), {Token(Token::Type::LITERAL_NUMBER_FLOAT, "low_bound"), Token(Token::Type::LITERAL_NUMBER_FLOAT, "high_bound")}), // Literal
    Consumer(Token(Token::Type::KEYWORD, "randf"), Consumer::Store(Token(Token::Type::KEYWORD, "memseg"), Token(Token::Type::LITERAL_NUMBER_INT, "index")), {Token(Token::Type::LITERAL_NUMBER_FLOAT, "low_bound"), Token(Token::Type::LITERAL_MEMORY, "high_bound")}), // Literal.Memory
    Consumer(Token(Token::Type::KEYWORD, "randf"), Consumer::Store(Token(Token::Type::KEYWORD, "memseg"), Token(Token::Type::LITERAL_NUMBER_INT, "index")), {Token(Token::Type::LITERAL_MEMORY, "low_bound"), Token(Token::Type::LITERAL_NUMBER_FLOAT, "high_bound")}), // Literal.Memory
    Consumer(Token(Token::Type::KEYWORD, "randf"), Consumer::Store(Token(Token::Type::KEYWORD, "memseg"), Token(Token::Type::LITERAL_NUMBER_INT, "index")), {Token(Token::Type::LITERAL_MEMORY, "low_bound"), Token(Token::Type::LITERAL_MEMORY, "high_bound")}), // Literal.Memory
    Consumer(Token(Token::Type::KEYWORD, "itof"), Consumer::Store(Token(Token::Type::KEYWORD, "memseg"), Token(Token::Type::LITERAL_NUMBER_INT, "index")), {Token(Token::Type::LITERAL_NUMBER_INT, "to_cast")}), // Literal
    Consumer(Token(Token::Type::KEYWORD, "itof"), Consumer::Store(Token(Token::Type::KEYWORD, "memseg"), Token(Token::Type::LITERAL_NUMBER_INT, "index")), {Token(Token::Type::LITERAL_MEMORY, "to_cast")}), // Literal.Memory
    Consumer(Token(Token::Type::KEYWORD, "ftoi"), Consumer::Store(Token(Token::Type::KEYWORD, "memseg"), Token(Token::Type::LITERAL_NUMBER_INT, "index")), {Token(Token::Type::LITERAL_NUMBER_FLOAT, "to_cast")}), // Literal
    Consumer(Token(Token::Type::KEYWORD, "ftoi"), Consumer::Store(Token(Token::Type::KEYWORD, "memseg"), Token(Token::Type::LITERAL_NUMBER_INT, "index")), {Token(Token::Type::LITERAL_MEMORY, "to_cast")}), // Literal.Memory
    Consumer(Token(Token::Type::KEYWORD, "stoi"), Consumer::Store(Token(Token::Type::KEYWORD, "memseg"), Token(Token::Type::LITERAL_NUMBER_INT, "index")), {Token(Token::Type::LITERAL_STRING, "to_cast")}), // Literal
    Consumer(Token(Token::Type::KEYWORD, "stoi"), Consumer::Store(Token(Token::Type::KEYWORD, "memseg"), Token(Token::Type::LITERAL_NUMBER_INT, "index")), {Token(Token::Type::LITERAL_MEMORY, "to_cast")}), // Literal.Memory
    Consumer(Token(Token::Type::KEYWORD, "stof"), Consumer::Store(Token(Token::Type::KEYWORD, "memseg"), Token(Token::Type::LITERAL_NUMBER_INT, "index")), {Token(Token::Type::LITERAL_STRING, "to_cast")}), // Literal
    Consumer(Token(Token::Type::KEYWORD, "stof"), Consumer::Store(Token(Token::Type::KEYWORD, "memseg"), Token(Token::Type::LITERAL_NUMBER_INT, "index")), {Token(Token::Type::LITERAL_MEMORY, "to_cast")}), // Literal.Memory
    Consumer(Token(Token::Type::KEYWORD, "ret"), Consumer::Store(Token(Token::Type::KEYWORD, "memory"), Token(Token::Type::LITERAL_NUMBER_INT, "index")), {})
};

std::map<std::string, uint8_t const> info::m_bytes = {
    // system category: 0x00 + index
    {"INT", 0x00 + 0x0},
    {"SYS", 0x00 + 0x1},
    {"BACK", 0x00 + 0x2},
    {"LABEL", 0x00 + 0x3},
    {"JMP", 0x00 + 0x4},
    {"CALL", 0x00 + 0x5},
    {"RET", 0x00 + 0x6},

    // math category: 0x10 + index
    {"ADD", 0x10 + 0x0},
    {"SUB", 0x10 + 0x1},
    {"MUL", 0x10 + 0x2},
    {"DIV", 0x10 + 0x3},
    {"MOD", 0x10 + 0x4},
    {"RAND", 0x10 + 0x5},
    {"AND", 0x10 + 0x6},
    {"OR", 0x10 + 0x7},
    {"XOR", 0x10 + 0x8},
    {"NOT", 0x10 + 0x9},
    {"ADDF", 0x10 + 0xA},
    {"SUBF", 0x10 + 0xB},
    {"MULF", 0x10 + 0xC},
    {"DIVF", 0x10 + 0xD},
    {"RANDF", 0x10 + 0xE},

    // memory category: 0x20 + index
    {"PUSH", 0x20 + 0x0},
    {"POP", 0x20 + 0x1},
    {"STORE", 0x20 + 0x2},
    {"FREE", 0x20 + 0x3},
    {"ITOS", 0x20 + 0x4},
    {"FTOS", 0x20 + 0x5},
    {"FTOI", 0x20 + 0x6},
    {"ITOF", 0x20 + 0x7},
    {"STOI", 0x20 + 0x8},
    {"STOF", 0x20 + 0x9},

    // comparative category: 0x30 + index
    {"CMP", 0x30 + 0x0},
    {"JWE", 0x30 + 0x1},
    {"JWD", 0x30 + 0x2},
    {"JWG", 0x30 + 0x3},
    {"JWL", 0x30 + 0x4},

    // memsegs category: 0x40 + index
    {"mem", 0x40 + 0x0},
    {"temp", 0x40 + 0x1},
    {"param", 0x40 + 0x2},
    {"nost", 0x40 + 0x3},

    // strings category: 0x21 + index

    // special instructions category: 0x50 + index
    {"LOAD_CONST", 0x50 + 0x0},
    {"LOAD_MEM", 0x50 + 0x1},
    {"LABEL_TABLE", 0x50 + 0x2},
    {"CONST_TABLE", 0x50 + 0x3},
    {"CODE_TABLE", 0x50 + 0x4}
};