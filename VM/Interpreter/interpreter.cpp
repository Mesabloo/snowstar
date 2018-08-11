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
    temp.push({});
    std::random_device rd;
    generator = std::mt19937{rd()};
    begin = std::chrono::system_clock::now();
    if (!this->make(path)) {
        std::cerr << termcolor::red << "Failed parsing file header. It may not be a Snow* bytecode file." << termcolor::reset << std::endl;
        return;
    }
    line_number = label_table[0]->getLine()+1;
    while (true) {
        //std::cout << utils::int_to_hex<uint16_t>(code_table[line_number]->getInstruction()) << " / " << utils::int_to_hex<uint16_t>(*code_table[line_number]->getArgument()) << std::endl;
        if (!domain(code_table[line_number])) break;
        ++line_number;
    }
    return;
}

bool Interpreter::domain(std::unique_ptr<AtomicToken> const& token) {
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
        //getchar();
        return false;
    }
    return true;
}

int8_t Interpreter::exec_system(std::unique_ptr<AtomicToken> const& token) {
    switch (token->getInstruction()) {
        case info::SystemOpcodes::SYS: {
            switch (std::get<int64_t>(loaded.top())) {
                case 1: {
                    loaded.pop();
                    std::stack<Value> copy{param};
                    while (!copy.empty()) {
                        std::cout << std::get<std::string>(copy.top());
                        copy.pop();
                    }
                    std::cout.flush();
                    return 1;
                }
                case 2: {
                    loaded.pop();
                    std::string value;
                    std::cin >> value;
                    switch (*(token->getArgument()) & 0xff) {
                        case info::MemsegOpcodes::MEM: {
                            mem[((*(token->getArgument()) & 0xff00) >> 8)] = value;
                            return 1;
                        }
                        case info::MemsegOpcodes::TEMP: {
                            temp.top()[((*(token->getArgument()) & 0xff00) >> 8)] = value;
                            return 1;
                        }
                        case info::MemsegOpcodes::PARAM: {
                            param.push(value);
                            return 1;
                        }    
                        case info::MemsegOpcodes::NOST: {
                            return 1;
                        }                
                    }
                    return -1;
                }
            }
            return -1;
        }
        case info::SystemOpcodes::LABEL: {
            return 1;
        }
        case info::SystemOpcodes::INT: {
            auto end = std::chrono::system_clock::now();
            auto time_taken = std::chrono::duration<double, std::milli>(end-begin).count();
            std::cout << termcolor::yellow << "Process exited with code " << std::get<int64_t>(loaded.top()) << " after " << time_taken << "ms." << '\n' << termcolor::reset;
            loaded.pop();
            return 0;
        }
        case info::SystemOpcodes::JMP: {
            line_number = label_table[*(token->getArgument())]->getLine();
            return 1;
        }
        case info::SystemOpcodes::CALL: {
            call_stack.top().second = line_number;
            line_number = label_table[*(token->getArgument())]->getLine();
            temp.push({});
            return 1;
        }
        case info::SystemOpcodes::BACK: {
            line_number = call_stack.top().second;
            temp.pop();
            call_stack.top().first = loaded.top();
            loaded.pop();
            call_stack.pop();
            return 1;
        }
        case info::SystemOpcodes::RET: {
            switch (*(token->getArgument()) & 0xff) {
                case info::MemsegOpcodes::MEM: {
                    call_stack.emplace(mem[((*(token->getArgument()) & 0xff00) >> 8)], 0);
                    return 1;
                }
                case info::MemsegOpcodes::TEMP: {
                    call_stack.emplace(temp.top()[((*(token->getArgument()) & 0xff00) >> 8)], 0);
                    return 1;
                }
            }
            return -1;
        }
    }
    return -1;
}

int8_t Interpreter::exec_maths(std::unique_ptr<AtomicToken> const& token) {
    Value const& v1{loaded.top()};
    loaded.pop();
    Value v0;
    if (!loaded.empty()) {
        v0 = loaded.top();
        loaded.pop();
    }
    //std::cout << (*(token->getArgument()) & 0xff) << std::endl;
    //std::cout << "Inserting value at index=" << ((*(token->getArgument()) & 0xff00) >> 8) << std::endl;
    switch (token->getInstruction()) {
        case info::MathsOpcodes::ADD: {
            switch (*(token->getArgument()) & 0xff) {
                case info::MemsegOpcodes::MEM: {
                    mem[((*(token->getArgument()) & 0xff00) >> 8)] = (std::get<int64_t>(v0) + std::get<int64_t>(v1));
                    return 1;
                }
                case info::MemsegOpcodes::TEMP: {
                    temp.top()[((*(token->getArgument()) & 0xff00) >> 8)] = (std::get<int64_t>(v0) + std::get<int64_t>(v1));
                    return 1;
                }
                case info::MemsegOpcodes::PARAM: {
                    param.push(std::get<int64_t>(v0) + std::get<int64_t>(v1));
                    return 1;
                }
            }
            return -1;
        }
        case info::MathsOpcodes::DIV: {
            switch (*(token->getArgument()) & 0xff) {
                case info::MemsegOpcodes::MEM: {
                    mem[((*(token->getArgument()) & 0xff00) >> 8)] = (std::get<int64_t>(v0) / std::get<int64_t>(v1));
                    return 1;
                }
                case info::MemsegOpcodes::TEMP: {
                    temp.top()[((*(token->getArgument()) & 0xff00) >> 8)] = (std::get<int64_t>(v0) / std::get<int64_t>(v1));
                    return 1;
                }
                case info::MemsegOpcodes::PARAM: {
                    param.push(std::get<int64_t>(v0) / std::get<int64_t>(v1));
                    return 1;
                }
            }
            return -1;
        }
        case info::MathsOpcodes::MOD: {
            switch (*(token->getArgument()) & 0xff) {
                case info::MemsegOpcodes::MEM: {
                    mem[((*(token->getArgument()) & 0xff00) >> 8)] = (std::get<int64_t>(v0) % std::get<int64_t>(v1));
                    return 1;
                }
                case info::MemsegOpcodes::TEMP: {
                    temp.top()[((*(token->getArgument()) & 0xff00) >> 8)] = (std::get<int64_t>(v0) % std::get<int64_t>(v1));
                    return 1;
                }
                case info::MemsegOpcodes::PARAM: {
                    param.push(std::get<int64_t>(v0) % std::get<int64_t>(v1));
                    return 1;
                }
            }
            return -1;
        }
        case info::MathsOpcodes::MUL: {
            switch (*(token->getArgument()) & 0xff) {
                case info::MemsegOpcodes::MEM: {
                    mem[((*(token->getArgument()) & 0xff00) >> 8)] = (std::get<int64_t>(v0) * std::get<int64_t>(v1));
                    return 1;
                }
                case info::MemsegOpcodes::TEMP: {
                    temp.top()[((*(token->getArgument()) & 0xff00) >> 8)] = (std::get<int64_t>(v0) * std::get<int64_t>(v1));
                    return 1;
                }
                case info::MemsegOpcodes::PARAM: {
                    param.push(std::get<int64_t>(v0) * std::get<int64_t>(v1));
                    return 1;
                }
            }
            return -1;
        }
        case info::MathsOpcodes::RAND: {
            switch (*(token->getArgument()) & 0xff) {
                case info::MemsegOpcodes::MEM: {
                    mem[((*(token->getArgument()) & 0xff00) >> 8)] = std::uniform_int_distribution<int64_t>(std::get<int64_t>(v0), std::get<int64_t>(v1))(generator);
                    return 1;
                }
                case info::MemsegOpcodes::TEMP: {
                    temp.top()[((*(token->getArgument()) & 0xff00) >> 8)] = std::uniform_int_distribution<int64_t>(std::get<int64_t>(v0), std::get<int64_t>(v1))(generator);
                    return 1;
                }
                case info::MemsegOpcodes::PARAM: {
                    param.push(std::uniform_int_distribution<int64_t>(std::get<int64_t>(v0), std::get<int64_t>(v1))(generator));
                    return 1;
                }
            }
            return -1;
        }
        case info::MathsOpcodes::SUB: {
            switch (*(token->getArgument()) & 0xff) {
                case info::MemsegOpcodes::MEM: {
                    mem[((*(token->getArgument()) & 0xff00) >> 8)] = (std::get<int64_t>(v0) - std::get<int64_t>(v1));
                    return 1;
                }
                case info::MemsegOpcodes::TEMP: {
                    temp.top()[((*(token->getArgument()) & 0xff00) >> 8)] = (std::get<int64_t>(v0) - std::get<int64_t>(v1));
                    return 1;
                }
                case info::MemsegOpcodes::PARAM: {
                    param.push(std::get<int64_t>(v0) - std::get<int64_t>(v1));
                    return 1;
                }
            }
            return -1;
        }
        case info::MathsOpcodes::AND: {
            switch (*(token->getArgument()) & 0xff) {
                case info::MemsegOpcodes::MEM: {
                    mem[((*(token->getArgument()) & 0xff00) >> 8)] = (std::get<int64_t>(v0) & std::get<int64_t>(v1));
                    return 1;
                }
                case info::MemsegOpcodes::TEMP: {
                    temp.top()[((*(token->getArgument()) & 0xff00) >> 8)] = (std::get<int64_t>(v0) & std::get<int64_t>(v1));
                    return 1;
                }
                case info::MemsegOpcodes::PARAM: {
                    param.push(std::get<int64_t>(v0) & std::get<int64_t>(v1));
                    return 1;
                }
            }
            return -1;
        }
        case info::MathsOpcodes::OR: {
            switch (*(token->getArgument()) & 0xff) {
                case info::MemsegOpcodes::MEM: {
                    mem[((*(token->getArgument()) & 0xff00) >> 8)] = (std::get<int64_t>(v0) | std::get<int64_t>(v1));
                    return 1;
                }
                case info::MemsegOpcodes::TEMP: {
                    temp.top()[((*(token->getArgument()) & 0xff00) >> 8)] = (std::get<int64_t>(v0) | std::get<int64_t>(v1));
                    return 1;
                }
                case info::MemsegOpcodes::PARAM: {
                    param.push(std::get<int64_t>(v0) | std::get<int64_t>(v1));
                    return 1;
                }
            }
            return -1;
        }
        case info::MathsOpcodes::XOR: {
            switch (*(token->getArgument()) & 0xff) {
                case info::MemsegOpcodes::MEM: {
                    mem[((*(token->getArgument()) & 0xff00) >> 8)] = (std::get<int64_t>(v0) ^ std::get<int64_t>(v1));
                    return 1;
                }
                case info::MemsegOpcodes::TEMP: {
                    temp.top()[((*(token->getArgument()) & 0xff00) >> 8)] = (std::get<int64_t>(v0) ^ std::get<int64_t>(v1));
                    return 1;
                }
                case info::MemsegOpcodes::PARAM: {
                    param.push(std::get<int64_t>(v0) ^ std::get<int64_t>(v1));
                    return 1;
                }
            }
            return -1;
        }
        case info::MathsOpcodes::NOT: {
            switch (*(token->getArgument()) & 0xff) {
                case info::MemsegOpcodes::MEM: {
                    mem[((*(token->getArgument()) & 0xff00) >> 8)] = (~std::get<int64_t>(v1));
                    return 1;
                }
                case info::MemsegOpcodes::TEMP: {
                    temp.top()[((*(token->getArgument()) & 0xff00) >> 8)] = (~std::get<int64_t>(v1));
                    return 1;
                }
                case info::MemsegOpcodes::PARAM: {
                    param.push(~std::get<int64_t>(v1));
                    return 1;
                }
            }
            return -1;
        }
        case info::MathsOpcodes::ADDF: {
            switch (*(token->getArgument()) & 0xff) {
                case info::MemsegOpcodes::MEM: {
                    mem[((*(token->getArgument()) & 0xff00) >> 8)] = (std::get<double>(v0) + std::get<double>(v1));
                    return 1;
                }
                case info::MemsegOpcodes::TEMP: {
                    temp.top()[((*(token->getArgument()) & 0xff00) >> 8)] = (std::get<double>(v0) + std::get<double>(v1));
                    return 1;
                }
                case info::MemsegOpcodes::PARAM: {
                    param.push(std::get<double>(v0) + std::get<double>(v1));
                    return 1;
                }
            }
            return -1;
        }
        case info::MathsOpcodes::DIVF: {
            switch (*(token->getArgument()) & 0xff) {
                case info::MemsegOpcodes::MEM: {
                    mem[((*(token->getArgument()) & 0xff00) >> 8)] = (std::get<double>(v0) / std::get<double>(v1));
                    return 1;
                }
                case info::MemsegOpcodes::TEMP: {
                    temp.top()[((*(token->getArgument()) & 0xff00) >> 8)] = (std::get<double>(v0) / std::get<double>(v1));
                    return 1;
                }
                case info::MemsegOpcodes::PARAM: {
                    param.push(std::get<double>(v0) / std::get<double>(v1));
                    return 1;
                }
            }
            return -1;
        }
        case info::MathsOpcodes::MULF: {
            switch (*(token->getArgument()) & 0xff) {
                case info::MemsegOpcodes::MEM: {
                    mem[((*(token->getArgument()) & 0xff00) >> 8)] = (std::get<double>(v0) * std::get<double>(v1));
                    return 1;
                }
                case info::MemsegOpcodes::TEMP: {
                    temp.top()[((*(token->getArgument()) & 0xff00) >> 8)] = (std::get<double>(v0) * std::get<double>(v1));
                    return 1;
                }
                case info::MemsegOpcodes::PARAM: {
                    param.push(std::get<double>(v0) * std::get<double>(v1));
                    return 1;
                }
            }
            return -1;
        }
        case info::MathsOpcodes::RANDF: {
            switch (*(token->getArgument()) & 0xff) {
                case info::MemsegOpcodes::MEM: {
                    mem[((*(token->getArgument()) & 0xff00) >> 8)] = std::uniform_real_distribution<double>(std::get<double>(v0), std::get<double>(v1))(generator);
                    return 1;
                }
                case info::MemsegOpcodes::TEMP: {
                    temp.top()[((*(token->getArgument()) & 0xff00) >> 8)] = std::uniform_real_distribution<double>(std::get<double>(v0), std::get<double>(v1))(generator);
                    return 1;
                }
                case info::MemsegOpcodes::PARAM: {
                    param.push(std::uniform_real_distribution<double>(std::get<double>(v0), std::get<double>(v1))(generator));
                    return 1;
                }
            }
            return -1;
        }
        case info::MathsOpcodes::SUBF: {
            switch (*(token->getArgument()) & 0xff) {
                case info::MemsegOpcodes::MEM: {
                    mem[((*(token->getArgument()) & 0xff00) >> 8)] = (std::get<double>(v0) - std::get<double>(v1));
                    return 1;
                }
                case info::MemsegOpcodes::TEMP: {
                    temp.top()[((*(token->getArgument()) & 0xff00) >> 8)] = (std::get<double>(v0) - std::get<double>(v1));
                    return 1;
                }
                case info::MemsegOpcodes::PARAM: {
                    param.push(std::get<double>(v0) - std::get<double>(v1));
                    return 1;
                }
            }
            return -1;
        }
    }
    return -1;
}

int8_t Interpreter::exec_memory(std::unique_ptr<AtomicToken> const& token) {
    switch (token->getInstruction()) {
        case info::MemoryOpcodes::FREE: {
            switch (*(token->getArgument()) & 0xff) {
                case info::MemsegOpcodes::MEM: {
                    mem[((*(token->getArgument()) & 0xff00) >> 8)] = std::variant<std::string, int64_t, double>{};
                    return 1;
                }
                case info::MemsegOpcodes::TEMP: {
                    temp.top()[((*(token->getArgument()) & 0xff00) >> 8)] = std::variant<std::string, int64_t, double>{};
                    return 1;
                }
            }
            return -1;
        }
        case info::MemoryOpcodes::POP: {
            Value const& v{param.top()};
            switch (*(token->getArgument()) & 0xff) {
                case info::MemsegOpcodes::PARAM: {
                    param.pop();
                    return 1;
                }
            }
            return -1;
        }
        case info::MemoryOpcodes::PUSH: {
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
            switch (*(token->getArgument()) & 0xff) {
                case info::MemsegOpcodes::MEM: {
                    //std::cout << "Storing value at mem_index=" << ((*(token->getArgument()) & 0xff00) >> 8) << std::endl;
                    mem[((*(token->getArgument()) & 0xff00) >> 8)] = loaded.top();
                    loaded.pop();
                    return 1;
                }
                case info::MemsegOpcodes::TEMP: {
                    temp.top()[((*(token->getArgument()) & 0xff00) >> 8)] = loaded.top();
                    loaded.pop();
                    return 1;
                }
            }
            return -1;
        }
        case info::MemoryOpcodes::ITOS: {
            //std::cout << "ITOS=" << std::to_string(std::get<int64_t>(loaded.top())) << std::endl;
            switch (*(token->getArgument()) & 0xff) {
                case info::MemsegOpcodes::MEM: {
                    //std::cout << "Storing value at mem_index=" << ((*(token->getArgument()) & 0xff00) >> 8) << std::endl;
                    mem[((*(token->getArgument()) & 0xff00) >> 8)] = std::to_string(std::get<int64_t>(loaded.top()));
                    loaded.pop();
                    return 1;
                }
                case info::MemsegOpcodes::TEMP: {
                    temp.top()[((*(token->getArgument()) & 0xff00) >> 8)] = std::to_string(std::get<int64_t>(loaded.top()));
                    loaded.pop();
                    return 1;
                }
                case info::MemsegOpcodes::PARAM: {
                    param.push(std::to_string(std::get<int64_t>(loaded.top())));
                    loaded.pop();
                    return 1;
                }
            }
            return -1;
        }
        case info::MemoryOpcodes::FTOS: {
            switch (*(token->getArgument()) & 0xff) {
                case info::MemsegOpcodes::MEM: {
                    //std::cout << "Storing value at mem_index=" << ((*(token->getArgument()) & 0xff00) >> 8) << std::endl;
                    mem[((*(token->getArgument()) & 0xff00) >> 8)] = std::to_string(std::get<double>(loaded.top()));
                    loaded.pop();
                    return 1;
                }
                case info::MemsegOpcodes::TEMP: {
                    temp.top()[((*(token->getArgument()) & 0xff00) >> 8)] = std::to_string(std::get<double>(loaded.top()));
                    loaded.pop();
                    return 1;
                }
                case info::MemsegOpcodes::PARAM: {
                    param.push(std::to_string(std::get<double>(loaded.top())));
                    loaded.pop();
                    return 1;
                }
            }
            return -1;
        }
        case info::MemoryOpcodes::ITOF: {
            switch (*(token->getArgument()) & 0xff) {
                case info::MemsegOpcodes::MEM: {
                    //std::cout << "Storing value at mem_index=" << ((*(token->getArgument()) & 0xff00) >> 8) << std::endl;
                    mem[((*(token->getArgument()) & 0xff00) >> 8)] = static_cast<double>(std::get<int64_t>(loaded.top()));
                    loaded.pop();
                    return 1;
                }
                case info::MemsegOpcodes::TEMP: {
                    temp.top()[((*(token->getArgument()) & 0xff00) >> 8)] = static_cast<double>(std::get<int64_t>(loaded.top()));
                    loaded.pop();
                    return 1;
                }
                case info::MemsegOpcodes::PARAM: {
                    param.push(static_cast<double>(std::get<int64_t>(loaded.top())));
                    loaded.pop();
                    return 1;
                }
            }
            return -1;
        }
        case info::MemoryOpcodes::FTOI: {
            switch (*(token->getArgument()) & 0xff) {
                case info::MemsegOpcodes::MEM: {
                    //std::cout << "Storing value at mem_index=" << ((*(token->getArgument()) & 0xff00) >> 8) << std::endl;
                    mem[((*(token->getArgument()) & 0xff00) >> 8)] = static_cast<int64_t>(std::get<double>(loaded.top()));
                    loaded.pop();
                    return 1;
                }
                case info::MemsegOpcodes::TEMP: {
                    temp.top()[((*(token->getArgument()) & 0xff00) >> 8)] = static_cast<int64_t>(std::get<double>(loaded.top()));
                    loaded.pop();
                    return 1;
                }
                case info::MemsegOpcodes::PARAM: {
                    param.push(static_cast<int64_t>(std::get<double>(loaded.top())));
                    loaded.pop();
                    return 1;
                }
            }
            return -1;
        }
        case info::MemoryOpcodes::STOI: {
            switch (*(token->getArgument()) & 0xff) {
                case info::MemsegOpcodes::MEM: {
                    //std::cout << "Storing value at mem_index=" << ((*(token->getArgument()) & 0xff00) >> 8) << std::endl;
                    mem[((*(token->getArgument()) & 0xff00) >> 8)] = static_cast<int64_t>(std::strtoll(std::get<std::string>(loaded.top()).c_str(), nullptr, 10));
                    loaded.pop();
                    return 1;
                }
                case info::MemsegOpcodes::TEMP: {
                    temp.top()[((*(token->getArgument()) & 0xff00) >> 8)] = static_cast<int64_t>(std::strtoll(std::get<std::string>(loaded.top()).c_str(), nullptr, 10));
                    loaded.pop();
                    return 1;
                }
                case info::MemsegOpcodes::PARAM: {
                    param.push(static_cast<int64_t>(std::strtoll(std::get<std::string>(loaded.top()).c_str(), nullptr, 10)));
                    loaded.pop();
                    return 1;
                }
            }
            return -1;
        }
        case info::MemoryOpcodes::STOF: {
            switch (*(token->getArgument()) & 0xff) {
                case info::MemsegOpcodes::MEM: {
                    //std::cout << "Storing value at mem_index=" << ((*(token->getArgument()) & 0xff00) >> 8) << std::endl;
                    mem[((*(token->getArgument()) & 0xff00) >> 8)] = std::strtod(std::get<std::string>(loaded.top()).c_str(), nullptr);
                    loaded.pop();
                    return 1;
                }
                case info::MemsegOpcodes::TEMP: {
                    temp.top()[((*(token->getArgument()) & 0xff00) >> 8)] = std::strtod(std::get<std::string>(loaded.top()).c_str(), nullptr);
                    loaded.pop();
                    return 1;
                }
                case info::MemsegOpcodes::PARAM: {
                    param.push(std::strtod(std::get<std::string>(loaded.top()).c_str(), nullptr));
                    loaded.pop();
                    return 1;
                }
            }
            return -1;
        }
    }
    return -1;
}

int8_t Interpreter::exec_comparative(std::unique_ptr<AtomicToken> const& token) {
    switch (token->getInstruction()) {
        case info::ComparativeOpcodes::CMP: {
            Value const& v1{loaded.top()};
            loaded.pop();
            Value const& v0{loaded.top()};
            loaded.pop();
            if (v0 == v1) {
                conditioner = 0;
            } else if (v0 > v1) {
                conditioner = 1;
            } else if (v0 < v1) {
                conditioner = -1;
            }
            //std::cout << "CMP=" << std::to_string(conditioner) << std::endl;
            return 1;
        }
        case info::ComparativeOpcodes::JWD: {
            if (conditioner != 0) {
                line_number = label_table[*(token->getArgument())]->getLine();
            }
            return 1;
        }
        case info::ComparativeOpcodes::JWE: {
            if (conditioner == 0) {
                line_number = label_table[*(token->getArgument())]->getLine();
            }
            return 1;
        }
        case info::ComparativeOpcodes::JWG: {
            if (conditioner == 1) {
                line_number = label_table[*(token->getArgument())]->getLine();
            }
            return 1;
        }
        case info::ComparativeOpcodes::JWL: {
            //std::cout << "JWL=" << std::to_string(conditioner) << std::endl;
            if (conditioner == -1) {
                line_number = label_table[*(token->getArgument())]->getLine();
            }
            return 1;
        }
    }
    return -1;
}

int8_t Interpreter::exec_special(std::unique_ptr<AtomicToken> const& token) {
    switch (token->getInstruction()) {
        case info::SpecialOpcodes::LOAD_CONST: {
            //std::cout << "Loading constant at index=" << *(token->getArgument()) << std::endl;
            loaded.push(const_table[*(token->getArgument())]->getValue());
            //std::clog << std::get<std::string>(const_table[*(token->getArgument())]->getValue()) << std::endl;
            return 1;
        }
        case info::SpecialOpcodes::LOAD_MEM: {
            //std::cout << std::hex << *(token->getArgument()) << std::endl;
            switch (*(token->getArgument()) & 0xff) {
                case info::MemsegOpcodes::MEM: {
                    //std::cout << "Loading memory at index=" << ((*(token->getArgument()) & 0xff00) >> 8) << std::endl;
                    loaded.push(mem[((*(token->getArgument()) & 0xff00) >> 8)]);
                    return 1;
                }
                case info::MemsegOpcodes::TEMP: {
                    loaded.push(temp.top()[((*(token->getArgument()) & 0xff00) >> 8)]);
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
        label_table[label_id] = std::make_unique<LabelToken>(label_id, label_no);
    }
    //std::cout << std::endl;

    // Parsing consts table:
    utils::stream_read<unsigned char>(is, x); // CONST_TABLE
    utils::stream_read<uint16_t>(is, table_size);
    //std::clog << "Reading const_table, size=" << table_size << std::endl;
    for (uint16_t i{0};i < table_size;++i) {
        uint8_t type;
        uint16_t id, size;
        Value value;
        utils::stream_read<uint16_t>(is, id);
        utils::stream_read<uint8_t>(is, type);
        utils::stream_read<uint16_t>(is, size);
        //std::clog << "Const_size=" << size << std::endl;
        std::string val{""};
        for (int j{0};j < size;++j) {
            uint8_t y;
            utils::stream_read<uint8_t>(is, y);
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
            value.emplace<int64_t>(std::strtoll(val.c_str(), nullptr, 16));
        }
        if (type == '\x05') { // is float
            for (auto& c : val)
                c -= 0x20;
            value.emplace<double>(std::stod(val.c_str()));
        }
        const_table[id] = std::make_unique<ConstToken>(id, value);
    }
    //std::cout << std::endl;

    // Parsing code table:
    utils::stream_read<unsigned char>(is, x); // CODE_TABLE
    utils::stream_read<uint16_t>(is, table_size);
    //std::clog << "Reading code_table, size=" << table_size << std::endl;
    for (uint16_t i{0};i < table_size;++i) {
        uint8_t hasArg, opcode;
        std::optional<int16_t> arg;
        utils::stream_read<uint8_t>(is, hasArg);
        utils::stream_read<uint8_t>(is, opcode);
        if (hasArg == '\x01')
            utils::stream_read<int16_t>(is, *arg);
        code_table[i] = std::make_unique<AtomicToken>(opcode, arg);
        //std::clog << std::hex << opcode << " " << *arg << std::endl;
    }

    return true;
}