#include <fstream>
#include <iostream>
#include <algorithm>
#include <sstream>
#include <iomanip>

#include <termcolor.hpp>
#include <Utils/utils.hpp>
#include <info.hpp>
#include "interpreter.hpp"

Interpreter::Interpreter() {}
Interpreter::~Interpreter() {}

void Interpreter::start(std::string const& path) {
    std::cout.sync_with_stdio(false);
    begin = std::chrono::system_clock::now();
    if (!this->make(path)) {
        std::cerr << termcolor::red << "Failed parsing file header. It may not be a Snow* bytecode file." << termcolor::reset << std::endl;
        return;
    }
    line_number = label_table[0]->getLine();
    while (true) {
        //std::cout << std::hex << code_table[i]->getInstruction() << " / " << (*code_table[i]->getArgument()) << std::endl;
        domain(code_table[line_number]);
        ++line_number;
    }
    return;
}

void Interpreter::domain(AtomicToken* const& token) {
    int8_t returned{-1};
    //std::cout << std::hex << token->getInstruction() << std::endl;
    switch (token->getInstruction() & 0xf0) {
        case 0x00: { // System
            returned = exec_system(token);
            break;
        }
        case 0x10: { // Maths
            returned = exec_maths(token);
            break;
        }
        case 0x20: { // Memory
            returned = exec_memory(token);
            break;
        }
        case 0x30: { // Comparative
            returned = exec_comparative(token);
            break;
        }
        case 0x50: {
            returned = exec_special(token);
            break;
        }
    }
    if (returned <= 0) {
        std::cout.flush();
        getchar();
        exit(returned);
    }
}

int8_t Interpreter::exec_system(AtomicToken* const& token) {
    switch (token->getInstruction()) {
        case info::SystemOpcodes::SYS: {
            switch (std::get<int32_t>(loaded.top())) {
                case 1: {
                    std::stack<Value> copy{param};
                    std::stringstream ss;
                    while (!copy.empty()) {
                        ss << std::get<std::string>(copy.top());
                        copy.pop();
                    }
                    std::cout << ss.str();
                    std::cout.flush();
                    return 1;
                }
                case 2: {
                    return 1;
                }
            }
            loaded.pop();
            return -1;
        }
        case info::SystemOpcodes::LABEL: {
            return 1;
        }
        case info::SystemOpcodes::INT: {
            auto end = std::chrono::system_clock::now();
            auto time_taken = std::chrono::duration<double, std::milli>(end-begin).count();
            std::cout << termcolor::yellow << "Process exited with code " << std::get<int32_t>(loaded.top()) << " after " << time_taken << "ms." << '\n' << termcolor::reset;
            loaded.pop();
            return 0;
        }
        case info::SystemOpcodes::JMP: {
            return 1;
        }
        case info::SystemOpcodes::CALL: {
            return 1;
        }
        case info::SystemOpcodes::BACK: {
            return 1;
        }
    }
    return -1;
}

int8_t Interpreter::exec_maths(AtomicToken* const& token) {
    switch (token->getInstruction()) {
        case info::MathsOpcodes::ADD: {
            return 1;
        }
        case info::MathsOpcodes::DIV: {
            return 1;
        }
        case info::MathsOpcodes::MOD: {
            return 1;
        }
        case info::MathsOpcodes::MUL: {
            return 1;
        }
        case info::MathsOpcodes::RAND: {
            return 1;
        }
        case info::MathsOpcodes::SUB: {
            return 1;
        }
    }
    return -1;
}

int8_t Interpreter::exec_memory(AtomicToken* const& token) {
    switch (token->getInstruction()) {
        case info::MemoryOpcodes::FREE: {
            return 1;
        }
        case info::MemoryOpcodes::POP: {
            Value const& v{param.top()};
            switch (*(token->getArgument()) & 0xff) {
                case info::MemsegOpcodes::PARAM: {
                    loaded.pop();
                    param.pop();
                    return 1;
                }
            }
            return -1;
        }
        case info::MemoryOpcodes::PUSH: {
            //std::clog << std::hex << (*(token->getArgument())) << " -> " << info::MemsegOpcodes::PARAM << std::endl;
            switch (*(token->getArgument()) & 0xff) {
                case info::MemsegOpcodes::PARAM: {
                    param.push(loaded.top());
                    loaded.pop();
                    return 1;
                }
            }
            return -1;
        }
        case info::MemoryOpcodes::STORE: {
            return 1;
        }
    }
    return -1;
}

int8_t Interpreter::exec_comparative(AtomicToken* const& token) {
    switch (token->getInstruction()) {
        case info::ComparativeOpcodes::CMP: {
            return 1;
        }
        case info::ComparativeOpcodes::JWD: {
            return 1;
        }
        case info::ComparativeOpcodes::JWE: {
            return 1;
        }
        case info::ComparativeOpcodes::JWG: {
            return 1;
        }
        case info::ComparativeOpcodes::JWL: {
            return 1;
        }
    }
    return -1;
}

int8_t Interpreter::exec_special(AtomicToken* const& token) {
    switch (token->getInstruction()) {
        case info::SpecialOpcodes::LOAD_CONST: {
            loaded.push(const_table[*(token->getArgument())]->getValue());
            //std::clog << std::get<std::string>(const_table[*(token->getArgument())]->getValue()) << std::endl;
            return 1;
        }
        case info::SpecialOpcodes::LOAD_MEM: {
            switch (*(token->getArgument()) & 0xff) {
                case info::MemsegOpcodes::MEM: {
                    loaded.push(mem[*(token->getArgument()) & 0xff00]);
                    return 1;
                }
                case info::MemsegOpcodes::TEMP: {
                    loaded.push(temp.top()[*(token->getArgument()) & 0xff00]);
                    return 1;
                }
                case info::MemsegOpcodes::PARAM: {
                    loaded.push(param.top());
                    return 1;
                }
            }
            return -1;
        }
    }
    return -1;
}

bool Interpreter::make(std::string const& path) {
    std::ifstream is{path, std::ios_base::binary};
    std::string header{""};
    for (uint8_t i{0};i < 8;++i) {
        unsigned char x;
        utils::stream_read<unsigned char>(is, x);
        header += x;
    }
    if (header != "snowstar") return false;
    //std::clog << "Read snowstar" << std::endl;
    //std::cout << std::endl;

    unsigned char x;
    uint16_t table_size;
    // Parsing labels table:
    utils::stream_read<unsigned char>(is, x); // LABEL_TABLE
    utils::stream_read<uint16_t>(is, table_size);
    //std::clog << "Reading label_table, size=" << table_size << std::endl;
    for (uint16_t i{0};i < table_size;++i) {
        uint16_t label_id, label_no;
        utils::stream_read<uint16_t>(is, label_id);
        utils::stream_read<uint16_t>(is, label_no);
        label_table[label_id] = new LabelToken(label_id, label_no);
    }
    //std::cout << std::endl;

    // Parsing consts table:
    utils::stream_read<unsigned char>(is, x); // CONST_TABLE
    utils::stream_read<uint16_t>(is, table_size);
    // std::clog << "Reading const_table, size=" << table_size << std::endl;
    for (uint16_t i{0};i < table_size;++i) {
        uint8_t type;
        uint16_t id, size;
        Value value;
        utils::stream_read<uint16_t>(is, id);
        utils::stream_read<uint8_t>(is, type);
        utils::stream_read<uint16_t>(is, size);
        std::string val{""};
        for (int j{0};j < size;++j) {
            unsigned char y;
            utils::stream_read<unsigned char>(is, y);
            val += y;
        }
        if (type == '\x03') { // is string
            for (auto& c : val)
                c -= 0x20;
            value.emplace<std::string>(val); 
        }
        if (type == '\x04') { // is int
            for (auto& c : val)
                c -= 0x10;
            value.emplace<int32_t>(std::strtoll(val.c_str(), nullptr, 16));
        }
        if (type == '\x05') { // is float
            value.emplace<float>(std::strtof(val.c_str(), nullptr));
        }
        const_table[id] = new ConstToken(id, value);
    }
    //std::cout << std::endl;

    // Parsing code table:
    utils::stream_read<unsigned char>(is, x); // CODE_TABLE
    utils::stream_read<uint16_t>(is, table_size);
    for (uint16_t i{0};i < table_size;++i) {
        uint8_t hasArg, opcode;
        std::optional<int16_t> arg;
        utils::stream_read<uint8_t>(is, hasArg);
        utils::stream_read<uint8_t>(is, opcode);
        if (hasArg == '\x01')
            utils::stream_read<int16_t>(is, *arg);
        code_table[i] = new AtomicToken(opcode, arg);
        //std::clog << std::hex << opcode << " " << *arg << std::endl;
    }

    return true;
}