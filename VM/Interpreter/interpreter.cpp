#include <sstream>
#include <regex>
#include <limits>
#include <iomanip>
#include <iostream>

#include <math.h>
#include <time.h>

#include "interpreter.hpp"
#include "../../Common/Utils/utils.hpp"
#include "../../Common/termcolor.hpp"

#include "../../Common/info.hpp"

Interpreter::Interpreter(std::string const path) {
    m_stream_size = utils::file_getsize(path);
}
Interpreter::~Interpreter() {}

void Interpreter::start(ByteLexer& b) {
    loadConsumersInMemory(b);
    configVM();
    for (ByteConsumer* const& c : m_consumers)
        checkDomainOfConsumer(c);
}

void Interpreter::configVM() {
    std::cout.sync_with_stdio(false);
    srand(time(NULL));
}

void Interpreter::loadConsumersInMemory(ByteLexer& b) {
    while (b.getSize() < m_stream_size) {
        ByteConsumer* c = b.createConsumerFromLine(b.readLine());
        if (c == nullptr) {
            getchar();
            return;
        }
        m_consumers.push_back(c);
    }
}

void Interpreter::checkDomainOfConsumer(ByteConsumer* const& c) {
    uint64_t value = static_cast<uint64_t>(c->getInstruction().getValueIfExisting());
    int8_t returned;
    switch (value & 0xFF000000) {
        case 0x50000000: // memsegs
            break;
        case 0x40000000: // comparative
            returned = executeComparativeConsumer(c);
            break;
        case 0x30000000: // memory
            returned = executeMemoryConsumer(c);
            break;
        case 0x20000000: // maths
            returned = executeMathsConsumer(c);
            break;
        case 0x10000000: // system
            returned = executeSystemConsumer(c);
            break;
        default:
            std::cerr << termcolor::red << "Error 0x5698: The opcode '0x" << std::hex << value << "' does not belong to any category provided by the language." << '\n'
                << "Please contact the creator giving him the opcode as well as the error encountered if you didn't modify the file with the extension `.ssbc` by hand. If you did, then you might have done something wrong.";
            returned = -1;
    }
    if (returned <= 0) {
        getchar();
        exit(returned);
    }
}

int8_t Interpreter::executeSystemConsumer(ByteConsumer* const& c) {
    uint64_t value = static_cast<uint64_t>(c->getInstruction().getValueIfExisting());
    switch (value) {
        case info::SystemOpcodes::INT: {
            int arg0_returncode = c->getArgs()[0].getIntegerValueIfExisting();
            std::cout << termcolor::yellow << "Process exited with code " << arg0_returncode << termcolor::reset << std::endl;
            return 0;
        }
        case info::SystemOpcodes::SYS: {
            ByteToken const arg0 = c->getArgs()[0];
            if (!arg0.isIntegerNumber()) {
                std::cerr << termcolor::red << "Error 0x9834: Invalid integer number ('" << arg0.getStringValueIfExisting() << "', " << arg0.getIntegerValueIfExisting() << ", " << arg0.getDoubleValueIfExisting() << ") used as a memory segment index." << '\n'
                    << "If you did not modify the bytecode file by hand, please contact the creator giving him the error code as well as the bytecode.";
                return -32;
            }
            int code = arg0.getIntegerValueIfExisting();
            if (code < 0) {
                std::cerr << termcolor::red << "Error 0x0563: Invalid argument ('" << arg0.getStringValueIfExisting() << "', " << arg0.getIntegerValueIfExisting() << ", " << arg0.getDoubleValueIfExisting() << ") specified for $sys." << '\n'
                    << "If you tried to modify the bytecode file, please regenerate one with the compiler given for this job.";
                return -7;
            }
            switch (code) {
                case 1: {
                    std::stack<ValueContainer> temp_stack = param;
                    std::stringstream ss;
                    while (!temp_stack.empty()) {
                        auto val = temp_stack.top();
                        temp_stack.pop();
                        if (val.isString) {
                            ss << val.string_storage;
                        } else if (val.isIntegerNumber) {
                            ss << val.integer_storage;
                        } else if (val.isFloatingNumber) {
                            ss << std::setprecision(std::numeric_limits<double>::max_digits10 -1) << val.float_storage;
                        } else {
                            std::cerr << termcolor::red << "Error 0x2369: Invalid value ('" << val.string_storage << "', " << val.integer_storage << ", " << val.float_storage << ") contained in @param." << '\n'
                                << "If you don't know why it happens, or didn't modify the bytecode by hand, then contact the creator specifying your code and the error code.";
                            return -96;
                        }
                    }
                    std::cout << termcolor::reset;
                    if (ss.str() == "")
                        std::cout << '\n';
                    else
                        std::cout << ss.str();
                    std::cout << termcolor::reset;
                    std::cout.flush();
                    return 1;
                }
                case 2: {
                    ByteToken const memseg = c->getStorage().getMemory();
                    uint64_t const memory_value = memseg.getValueIfExisting(),
                             _mem = info::m_bytes["mem"],
                             _temp = info::m_bytes["temp"],
                             _param = info::m_bytes["param"],
                             _nost = info::m_bytes["nost"];
                    std::string input;
                    std::getline(std::cin, input);
                    ValueContainer val;
                    if (utils::str_is_number(input)) {
                        val.string_storage = "";
                        val.isString = false;
                        if (std::regex_match(input, std::regex(".*(\\.[0-9]*){1}"))) {
                            val.float_storage = std::stod(input);
                            val.isFloatingNumber = true;
                            val.isIntegerNumber = false;
                        } else {
                            val.integer_storage = std::stoi(input);
                            val.isIntegerNumber = true;
                            val.isFloatingNumber = false;
                        }
                    } else {
                        val.isString = true;
                        val.isFloatingNumber = false;
                        val.isIntegerNumber = false;
                        val.string_storage = input;
                    }
                    if (!memseg.isIntegerNumber()) {
                        std::cerr << termcolor::red << "Error 0x9834: Invalid integer number ('" << memseg.getStringValueIfExisting() << "', " << memseg.getIntegerValueIfExisting() << ", " << memseg.getDoubleValueIfExisting() << ") used as a memory segment index." << '\n'
                            << "If you did not modify the bytecode file by hand, please contact the creator giving him the error code as well as the bytecode.";
                        return -32;
                    }
                    int32_t const memory_index = memseg.getIntegerValueIfExisting();
                    if (memory_index < 0) {
                        return 1;
                    }
                    if (memory_value == _nost) {
                        return 1;
                    } else if (memory_value == _mem) {
                        mem[memory_index] = val;
                    } else if (memory_value == _temp) {
                        temp[memory_index] = val;
                    } else if (memory_value == _param) {
                        param.push(val);
                    } else {
                        std::cerr << termcolor::red << "Error 0x2369: Invalid memseg '0x" << std::hex << memory_value << "'." << '\n'
                            << "Unless you tried to modify the bytecode file by hand, check your code. This may not be your fault. If it isn't, please contact the creator witht the error code and the value given.";
                        return -85;
                    }
                    return 1;
                }
                default:
                    std::cerr << termcolor::red << "Error 0x0563: Invalid argument ('" << arg0.getStringValueIfExisting() << "', " << arg0.getIntegerValueIfExisting() << ", " << arg0.getDoubleValueIfExisting() << ") specified for $sys." << '\n'
                        << "If you tried to modify the bytecode file, please regenerate one with the compiler given for this job.";
                    return -7;
            }
            return 1;
        }
        case info::SystemOpcodes::BACK: {
            return 1;
        }
        case info::SystemOpcodes::LBL: {
            return 1;
        }
        case info::SystemOpcodes::JMP: {
            return 1;
        }
        default:
            std::cerr << termcolor::red << "Error 0x6312: The opcode '0x" << std::hex << value << "' does not belong to the `system` category provided by the language." << '\n'
                << "Please contact the creator giving him the opcode as well as the error encountered if you didn't modify the file with the extension `.ssbc` by hand. If you did, then you might have done something wrong.";
            return -1;
    }
}

int8_t Interpreter::executeMemoryConsumer(ByteConsumer* const& c) {
    uint64_t value = static_cast<uint64_t>(c->getInstruction().getValueIfExisting());
    switch (value) {
        case info::MemoryOpcodes::STORE: {
            ByteToken const memseg = c->getStorage().getMemory();
            uint64_t const memory_value = memseg.getValueIfExisting(),
                           _mem = info::m_bytes["mem"],
                           _temp = info::m_bytes["temp"],
                           _param = info::m_bytes["param"],
                           _nost = info::m_bytes["nost"];
            ValueContainer val;
            ByteToken const arg0 = c->getArgs()[0];
            if (arg0.isIntegerNumber()) {
                val.isString = false;
                val.isIntegerNumber = true;
                val.isFloatingNumber = false;
                val.integer_storage = arg0.getIntegerValueIfExisting();
            } else if (arg0.isDoubleNumber()) {
                val.isString = false;
                val.isIntegerNumber = false;
                val.isFloatingNumber = true;
                val.float_storage = arg0.getDoubleValueIfExisting();
            } else if (arg0.isString()) {
                val.isString = true;
                val.isIntegerNumber = false;
                val.isFloatingNumber = false;
                val.string_storage = arg0.getStringValueIfExisting();
            } else if (arg0.isMemory()) {
                uint64_t const memory_segment = arg0.getValueIfExisting();
                if (!arg0.isIntegerNumber()) {
                    std::cerr << termcolor::red << "Error 0x9834: Invalid integer number ('" << arg0.getStringValueIfExisting() << "', " << arg0.getIntegerValueIfExisting() << ", " << arg0.getDoubleValueIfExisting() << ") used as a memory segment index." << '\n'
                        << "If you did not modify the bytecode file by hand, please contact the creator giving him the error code as well as the bytecode.";
                    return -32;
                }
                int const index = arg0.getIntegerValueIfExisting();
                if (index < 0) {
                    val.isString = false;
                    val.isFloatingNumber = false;
                    val.isIntegerNumber = false;
                } else {
                    if (memory_segment == _nost) {
                        val.isString = false;
                        val.isFloatingNumber = false;
                        val.isIntegerNumber = false;
                    } else if (memory_segment == _mem) {
                        val = mem[index];
                    } else if (memory_segment == _temp) {
                        val = temp[index];
                    } else if (memory_segment == _param) {
                        std::cerr << termcolor::red << "Error 0x3258: Invalid segment '0x" << std::hex << memory_segment << "' used with instruction $store." << '\n'
                            << "It is recommended that you check your code and recompile it. If the issue is not solved, please contact the creator giving him the error code as well as the memory segment causing the error.";
                        return -87;
                    }
                }
            } else {
                std::cerr << termcolor::red << "Error 0x5968: Invalid token ('" << arg0.getStringValueIfExisting() << "', " << arg0.getValueIfExisting() << ", " << arg0.getIntegerValueIfExisting() << "." << '\n'
                    << "If you did not try to modify the bytecode file by hand, it is recommended to contact the creator giving him the error code as well as the token in fault.";
                return -63;
            }
            if (!memseg.isMemory()) {
                std::cerr << termcolor::red << "Error 0x9834: Invalid integer number ('" << memseg.getStringValueIfExisting() << "', " << memseg.getIntegerValueIfExisting() << ", " << memseg.getDoubleValueIfExisting() << ") used as a memory segment index." << '\n'
                    << "If you did not modify the bytecode file by hand, please contact the creator giving him the error code as well as the bytecode.";
                return -32;
            }
            if (memseg.getIntegerValueIfExisting() < 0) {
                return 1;
            }
            if (memory_value == _nost) {
                return 1;
            } else if (memory_value == _temp) {
                temp[memseg.getIntegerValueIfExisting()] = val;
            } else if (memory_value == _param) {
                std::cerr << termcolor::red << "Error 0x3258: Invalid segment '0x" << std::hex << memory_value << "' used with instruction $store." << '\n'
                    << "It is recommended that you check your code and recompile it. If the issue is not solved, please contact the creator giving him the error code as well as the memory segment causing the error.";
                return -87;
            } else if (memory_value == _mem) {
                mem[memseg.getIntegerValueIfExisting()] = val;
            } else {
                std::cerr << termcolor::red << "Error 0x2369: Invalid memseg '0x" << std::hex << memory_value << "'." << '\n'
                    << "Unless you tried to modify the bytecode file by hand, check your code. This may not be your fault. If it isn't, please contact the creator with the error code and the value given.";
                return -85;
            }
            return 1;
        }
        case info::MemoryOpcodes::PUSH: {
            ByteToken const memseg = c->getStorage().getMemory();
            uint64_t const memory_value = memseg.getValueIfExisting(),
                           _mem = info::m_bytes["mem"],
                           _temp = info::m_bytes["temp"],
                           _param = info::m_bytes["param"],
                           _nost = info::m_bytes["nost"];
            if (memory_value == _mem || memory_value == _temp) {
                std::cerr << termcolor::red << "Error 0x3258: Invalid segment '0x" << std::hex << memory_value << "' used with instruction $push." << '\n'
                    << "It is recommended that you check your code and recompile it. If the issue is not solved, please contact the creator giving him the error code as well as the memory segment causing the error.";
                return -87;
            }
            if (memory_value == _nost) {
                return 1;
            }
            ValueContainer val;
            ByteToken const arg0 = c->getArgs()[0];
            if (arg0.isIntegerNumber()) {
                val.isString = false;
                val.isFloatingNumber = false;
                val.isIntegerNumber = true;
                val.integer_storage = arg0.getIntegerValueIfExisting();
            } else if (arg0.isDoubleNumber()) {
                val.isString = false;
                val.isFloatingNumber = true;
                val.isIntegerNumber = false;
                val.float_storage = arg0.getDoubleValueIfExisting();
            } else if (arg0.isString()) {
                val.isString = true;
                val.isFloatingNumber = false;
                val.isIntegerNumber = false;
                val.string_storage = arg0.getStringValueIfExisting();
            } else if (arg0.isMemory()) {
                uint64_t const memory_segment = arg0.getValueIfExisting();
                int const index = arg0.getIntegerValueIfExisting();
                if (index < 0) {
                    val.isString = false;
                    val.isFloatingNumber = false;
                    val.isIntegerNumber = false;
                } else {
                    if (memory_segment == _nost) {
                        val.isString = false;
                        val.isFloatingNumber = false;
                        val.isIntegerNumber = false;
                    } else if (memory_segment == _mem) {
                        val = mem[index];
                    } else if (memory_segment == _temp) {
                        val = temp[index];
                    } else if (memory_segment == _param) {
                        std::cerr << termcolor::red << "Error 0x3258: Invalid segment '0x" << std::hex << memory_segment << "' used with instruction $store." << '\n'
                            << "It is recommended that you check your code and recompile it. If the issue is not solved, please contact the creator giving him the error code as well as the memory segment causing the error.";
                        return -87;
                    } else {
                        std::cerr << termcolor::red << "Error 0x2369: Invalid memseg '0x" << std::hex << memory_value << "'." << '\n'
                            << "Unless you tried to modify the bytecode file by hand, check your code. This may not be your fault. If it isn't, please contact the creator with the error code and the value given.";
                        return -85;
                    }
                }
            } else {
                std::cerr << termcolor::red << "Error 0x5968: Invalid token ('" << arg0.getStringValueIfExisting() << "', " << arg0.getValueIfExisting() << ", " << arg0.getIntegerValueIfExisting() << "." << '\n'
                    << "If you did not try to modify the bytecode file by hand, it is recommended to contact the creator giving him the error code as well as the token in fault.";
                return -63;
            }
            if (memory_value == _param) {
                param.push(val);
            }
            return 1;
        }
        case info::MemoryOpcodes::POP: {
            ByteToken const memseg = c->getStorage().getMemory();
            uint64_t const memory_value = memseg.getValueIfExisting(),
                           _mem = info::m_bytes["mem"],
                           _temp = info::m_bytes["temp"],
                           _param = info::m_bytes["param"],
                           _nost = info::m_bytes["nost"];
            ByteToken const arg0 = c->getArgs()[0];
            if (!arg0.isMemory()) {
                std::cerr << termcolor::red << "Error 0x5968: Invalid token ('" << arg0.getStringValueIfExisting() << "', " << arg0.getValueIfExisting() << ", " << arg0.getIntegerValueIfExisting() << "." << '\n'
                    << "If you did not try to modify the bytecode file by hand, it is recommended to contact the creator giving him the error code as well as the token in fault.";
                return -63;
            }
            double const pop_seg = arg0.getValueIfExisting();
            if (pop_seg == _mem || pop_seg == _temp) {
                std::cerr << termcolor::red << "Error 0x3258: Invalid segment '0x" << std::hex << memory_value << "' used with instruction $pop." << '\n'
                    << "It is recommended that you check your code and recompile it. If the issue is not solved, please contact the creator giving him the error code as well as the memory segment causing the error.";
                return -87;
            }
            if (pop_seg == _nost) {
                return 1;
            }
            if ((memseg.getValueIfExisting() == _nost)) {
                if (pop_seg == _param) {
                    param.pop();
                    return 1;
                }
            } else {
                ValueContainer val;
                if (!memseg.isIntegerNumber()) {
                    std::cerr << termcolor::red << "Error 0x9834: Invalid integer number ('" << memseg.getStringValueIfExisting() << "', " << memseg.getIntegerValueIfExisting() << ", " << memseg.getDoubleValueIfExisting() << ") used as a memory segment index." << '\n'
                        << "If you did not modify the bytecode file by hand, please contact the creator giving him the error code as well as the bytecode.";
                    return -32;
                }
                int const index = memseg.getIntegerValueIfExisting();
                if (index < 0) {
                    return 1;
                }
                double seg = memseg.getValueIfExisting();
                if (pop_seg == _param) {
                    val = param.top();
                    param.pop();
                }
                if (seg == _mem) {
                    mem[index] = val;
                } else if (seg == _temp) {
                    temp[index] = val;
                } else if (seg == _param) {
                    param.push(val);
                }
            }
            return 1;;
        }
        case info::MemoryOpcodes::FREE: {
            ByteToken const arg0 = c->getArgs()[0];
            if (!arg0.isMemory()) {
                std::cerr << termcolor::red << "Error 0x5968: Invalid token ('" << arg0.getStringValueIfExisting() << "', " << arg0.getValueIfExisting() << ", " << arg0.getIntegerValueIfExisting() << "." << '\n'
                    << "If you did not try to modify the bytecode file by hand, it is recommended to contact the creator giving him the error code as well as the token in fault.";
                return -63;
            }
            uint64_t const memory_value = arg0.getValueIfExisting(),
                         _mem = info::m_bytes["mem"],
                         _temp = info::m_bytes["temp"],
                         _param = info::m_bytes["param"],
                         _nost = info::m_bytes["nost"];
            if (memory_value == _nost) {
                return 1;
            } else if (memory_value == _param) {
                std::cerr << termcolor::red << "Error 0x3258: Invalid segment '0x" << std::hex << memory_value << "' used with instruction $free." << '\n'
                    << "It is recommended that you check your code and recompile it. If the issue is not solved, please contact the creator giving him the error code as well as the memory segment causing the error.";
                return -87;
            }
            int const index = arg0.getIntegerValueIfExisting();
            if (index < 0) {
                std::cerr << termcolor::red << "Error 0x9834: Invalid integer number ('" << arg0.getStringValueIfExisting() << "', " << arg0.getIntegerValueIfExisting() << ", " << arg0.getDoubleValueIfExisting() << ") used as a memory segment index." << '\n'
                    << "If you did not modify the bytecode file by hand, please contact the creator giving him the error code as well as the bytecode.";
                return -32;
            }
            if (memory_value == _mem) {
                mem.erase(index);
                return 1;
            } else if (memory_value == _temp) {
                temp.erase(index);
                return 1;
            } else {
                std::cerr << termcolor::red << "Error 0x2369: Invalid memseg '0x" << std::hex << memory_value << "'." << '\n'
                    << "Unless you tried to modify the bytecode file by hand, check your code. This may not be your fault. If it isn't, please contact the creator with the error code and the value given.";
                return -85;
            }
            return 1;
        }
        default:
            std::cerr << termcolor::red << "Error 0x6313: The opcode '0x" << std::hex << value << "' does not belong to the `memory` category provided by the language." << '\n'
                << "Please contact the creator giving him the opcode as well as the error encountered if you didn't modify the file with the extension `.ssbc` by hand. If you did, then you might have done something wrong.";
            return -1;
    }
}

int8_t Interpreter::executeMathsConsumer(ByteConsumer* const& c) {
    uint64_t value = static_cast<uint64_t>(c->getInstruction().getValueIfExisting());
    switch (value) {
        case info::MathsOpcodes::ADD: {
            return 1;
        }
        case info::MathsOpcodes::SUB: {
            return 1;
        }
        case info::MathsOpcodes::MUL: {
            return 1;
        }
        case info::MathsOpcodes::DIV: {
            return 1;
        }
        case info::MathsOpcodes::RAND: {
            return 1;
        }
        case info::MathsOpcodes::MOD: {
            return 1;
        }
        default:
            std::cerr << termcolor::red << "Error 0x6314: The opcode '0x" << std::hex << value << "' does not belong to the `maths` category provided by the language." << '\n'
                << "Please contact the creator giving him the opcode as well as the error encountered if you didn't modify the file with the extension `.ssbc` by hand. If you did, then you might have done something wrong.";
            return -1;
    }
}

int8_t Interpreter::executeComparativeConsumer(ByteConsumer* const& c) {
    uint64_t value = static_cast<uint64_t>(c->getInstruction().getValueIfExisting());
    switch (value) {
        case info::ComparativeOpcodes::CMP: {
            return 1;
        }
        case info::ComparativeOpcodes::IEQ: {
            return 1;
        }
        case info::ComparativeOpcodes::INE: {
            return 1;
        }
        case info::ComparativeOpcodes::IGR: {
            return 1;
        }
        case info::ComparativeOpcodes::ILO: {
            return 1;
        }
        default:
            std::cerr << termcolor::red << "Error 0x6315: The opcode '0x" << std::hex << value << "' does not belong to the `comparative` category provided by the language." << '\n'
                << "Please contact the creator giving him the opcode as well as the error encountered if you didn't modify the file with the extension `.ssbc` by hand. If you did, then you might have done something wrong.";
            return -1;
    }
}