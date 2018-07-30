#include <sstream>
#include <regex>
#include <limits>
#include <iomanip>
#include <iostream>
#include <thread>
#include <cstring>

#include <math.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#include "interpreter.hpp"
#include "../../Common/Utils/utils.hpp"
#include "../../Common/termcolor.hpp"

#include "../../Common/info.hpp"
#include "../../Common/values.hpp"

Interpreter::Interpreter(std::string const path) {
    m_stream_size = utils::file_getsize(path);
}
Interpreter::~Interpreter() {}

void Interpreter::start(ByteLexer& b) {
    if (vars::DEBUG) {
        // start socket server here.
        // and wait for the client to connect.
        // while not client connected, wait.
        // until client connects (here, the debugger).
        int newsockfd, portno = 9999;
        sock = socket(AF_INET, SOCK_STREAM, 0);
        if (sock < 0) {
            std::cerr << termcolor::red << "An error occured while trying to open a new socket." << '\n'
                << "What happened: ";
            perror("");
            std::cerr << termcolor::reset << std::endl;
            return;
        }

        sockaddr_in serv_addr;
        bzero(reinterpret_cast<char*>(&serv_addr), sizeof(serv_addr));
        serv_addr.sin_family = AF_INET;
        serv_addr.sin_addr.s_addr = INADDR_ANY;
        serv_addr.sin_port = htons(portno);

        if (bind(sock, reinterpret_cast<sockaddr*>(&serv_addr), sizeof(serv_addr)) < 0) {
            std::cerr << termcolor::red << "An error occured while binding the address to the socket." << '\n'
                << "What happened: ";
            perror("");
            std::cerr << termcolor::reset << std::endl;
            return;
        }

        listen(sock, 1);

        std::clog << termcolor::red << "Waiting for the debugger to connect..." << termcolor::reset << std::endl;

        while ((newsockfd = accept(sock, 0, 0))) {
            socket_id = static_cast<int>(newsockfd);

            char buf[10];
            read(socket_id, buf, 10);
            char send[10] = {'h', 'e', 'a', 'r', 't', 'b', 'e', 'a', 't', '\0'};
            write(socket_id, send, 10);
            if (std::string{buf, 9} == "heartbeat") break;
        }

        std::clog << termcolor::green << "Debugger attached successfully !" << termcolor::reset << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }

    execution_time = std::chrono::system_clock::now();
    loadConsumersInMemory(b);
    configVM();
    if (labels.find("main") == labels.end()) {
        if (vars::DEBUG) {
            std::stringstream ss;
            ss << "error " << "Error 0x0000: No main entry point in the code given." << '\n'
                << "Please add a main entry point to your program and start again.";
            std::string val{ss.str()};
            write(socket_id, val.c_str(), 4096);
        }
        return;
    }
    temp.push({});
    for (line_number = labels["main"];line_number < m_consumers.size();++line_number) {
        if (vars::DEBUG) {
            if (exec_count == 0) {
                char buf[4096];
                int mem_size{0}, temp_size{0};
                for (auto const v : mem) {
                    if (!v.isNull) mem_size++;
                }
                for (auto const v : temp.top()) {
                    if (!v.isNull) temp_size++;
                }
                std::stringstream ss;
                ss << "stats mem=" << mem.max_size() << ";" << (mem_size==0?"empty":std::to_string(mem_size)) << "\n"
                    << "temp=" << temp.top().max_size() << ";" << (temp_size==0?"empty":std::to_string(temp_size)) << "\n"
                    << "param=" << (param.empty()?"empty":std::to_string(param.size())) << "\n"
                    << *m_consumers[line_number];
                std::string s = ss.str();
                buf[0] = static_cast<unsigned char>(s.size());
                for (size_t i{0};i < s.size();++i) {
                    if (i > 4096) break;
                    buf[i+1] = s[i];
                }
                char const null[1] = {'\0'};
                for (auto length{s.size()+1};length < 4096;++length)
                    strcat(buf, null);
                write(socket_id, buf, 4096);
                char buffer[256];
                read(socket_id, buffer, 256);
                uint8_t const size = static_cast<uint8_t>(buffer[0]);
                int i{1};
                std::string cmd;
                while (buffer[i] != '\0' && i <= size) {
                    cmd += buffer[i];
                    i++;
                }
                std::vector<std::string> splitted = utils::str_split(cmd, ' ');
                std::string& command = splitted[0];
                if (command == "exec") {
                    uint32_t count = static_cast<uint32_t>(std::stoull(splitted[1]));
                    exec_count = count-1;
                } else if (command == "exit") {
                    char buf[5] = {'\x04', 'e', 'x', 'i', 't'};
                    if (!ERROR)
                        write(socket_id, buf, 5);
                    std::this_thread::sleep_for(std::chrono::milliseconds(500));
                    close(sock);
                    close(socket_id);
                    std::cerr << termcolor::yellow << "Process exited with code 0" << termcolor::reset << std::endl;
                    getchar();
                    exit(0);
                } else {
                    line_number--;
                    continue;
                }
            } else
                exec_count--;
        }
        checkDomainOfConsumer(m_consumers[line_number]);
    }
    
    if (vars::DEBUG) {
        char buf[5] = {'\x04', 'e', 'x', 'i', 't'};
        if (!ERROR)
            write(socket_id, buf, 5);
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        close(sock);
        close(socket_id);
        std::cerr << termcolor::yellow << "Process exited with code 0" << termcolor::reset << std::endl;
        getchar();
        exit(0);
    }
}

void Interpreter::configVM() {
    std::cout.sync_with_stdio(false);
    std::random_device rd;
    generator = std::mt19937{rd()};
    for (size_t i{0};i < m_consumers.size();++i) {
        ByteConsumer* const c = m_consumers[i];
        ByteToken const t = c->getInstruction();
        if (t.getValueIfExisting() == info::SystemOpcodes::LBL) {
            labels[c->getArgs()[0].getStringValueIfExisting()] = i;
        }
    }
}

void Interpreter::loadConsumersInMemory(ByteLexer& b) {
    // int i{0};
    while (b.getSize() < m_stream_size) {
        // std::clog << termcolor::blue << "Line #" << (i+1) << "\tRead=" << b.getSize() << "B\tTotal=" << m_stream_size << "B" <<  termcolor::reset << std::endl;
        ByteConsumer* c = b.createConsumerFromLine(b.readLine());
        // std::clog << *c << std::endl;
        if (c == nullptr) {
            getchar();
            return;
        }
        m_consumers.push_back(c);
        // ++i;
    }
}

void Interpreter::checkDomainOfConsumer(ByteConsumer* const& c) {
    uint64_t value = static_cast<uint64_t>(c->getInstruction().getValueIfExisting());
    // std::clog << termcolor::green << *c << termcolor::reset << std::endl << std::endl;
    int8_t returned{1};
    switch (value & 0xF0) {
        case 0x40: // memsegs
            break;
        case 0x30: // comparative
            returned = executeComparativeConsumer(c);
            break;
        case 0x20: // memory
            returned = executeMemoryConsumer(c);
            break;
        case 0x10: // maths
            returned = executeMathsConsumer(c);
            break;
        case 0x00: // system
            returned = executeSystemConsumer(c);
            break;
        default: {
            if (vars::DEBUG) {
                std::stringstream ss;
                ss << "error " << "Error 0x5698: The opcode '0x" << std::hex << value << "' does not belong to any category provided by the language." << '\n'
                    << "Please contact the creator giving him the opcode as well as the error encountered if you didn't modify the file with the extension `.ssbc` by hand. If you did, then you might have done something wrong.";
                std::string val{ss.str()};
                write(socket_id, val.c_str(), 4096);
                ERROR = true;
            }
            returned = -1;
        }
    }
    if (returned <= 0) {
        std::cout << termcolor::reset;
        if (vars::DEBUG) {
            char buf[5] = {'\x04', 'e', 'x', 'i', 't'};
            if (!ERROR)
                write(socket_id, buf, 5);
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            close(sock);
            close(socket_id);
            if (ERROR)
                std::clog << termcolor::yellow << "Process exited on error with code " << std::to_string(returned) << "." << termcolor::reset << std::endl;
        }
        getchar();
        exit(returned);
    }
}

int8_t Interpreter::executeSystemConsumer(ByteConsumer* const& c) {
    uint64_t value = static_cast<uint64_t>(c->getInstruction().getValueIfExisting());
    switch (value) {
        case info::SystemOpcodes::INT: {
            int arg0_returncode = c->getArgs()[0].getIntegerValueIfExisting();
            std::chrono::system_clock::time_point end = std::chrono::system_clock::now();
            auto time_exec = std::chrono::duration<double, std::milli>(end-execution_time).count();
            std::cout << termcolor::yellow << "Process exited with code " << arg0_returncode << " after " << (time_exec > 1000 ? std::to_string(time_exec/1000) + "s" : std::to_string(time_exec) + "ms") << termcolor::reset << std::endl;
            return 0;
        }
        case info::SystemOpcodes::SYS: {
            ByteToken const arg0 = c->getArgs()[0];
            if (!arg0.isIntegerNumber()) {
                if (vars::DEBUG) {
                    std::stringstream ss;
                    ss << "error " << "Error 0x9834: Invalid integer number ('" << arg0.getStringValueIfExisting() << "', " << arg0.getIntegerValueIfExisting() << ", " << arg0.getDoubleValueIfExisting() << ") used as a memory segment index." << '\n'
                        << "If you did not modify the bytecode file by hand, please contact the creator giving him the error code as well as the bytecode.";
                    std::string val{ss.str()};
                    write(socket_id, val.c_str(), 4096);
                    ERROR = true;
                }
                return -32;
            }
            int code = arg0.getIntegerValueIfExisting();
            if (code < 0) {
                if (vars::DEBUG) {
                    std::stringstream ss;
                    ss << "error " << "Error 0x0563: Invalid argument ('" << arg0.getStringValueIfExisting() << "', " << arg0.getIntegerValueIfExisting() << ", " << arg0.getDoubleValueIfExisting() << ") specified for $sys." << '\n'
                        << "If you tried to modify the bytecode file, please regenerate one with the compiler given for this job.";
                    std::string val{ss.str()};
                    write(socket_id, val.c_str(), 4096);
                    ERROR = true;
                }
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
                            if (vars::DEBUG) {
                                std::stringstream ss;
                                ss << "error " << "Error 0x4563: Invalid value " << val << " contained in @param." << '\n'
                                    << "If you don't know why it happens, or didn't modify the bytecode by hand, then contact the creator specifying your code and the error code.";
                                std::string val{ss.str()};
                                write(socket_id, val.c_str(), 4096);
                                ERROR = true;
                            }
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
                    val.isNull = false;
                    if (utils::str_is_number(input)) {
                        val.string_storage = "";
                        if (std::regex_match(input, std::regex(".*(\\.[0-9]*){1}"))) {
                            val.float_storage = std::stod(input);
                            val.isFloatingNumber = true;
                        } else {
                            val.integer_storage = std::stoi(input);
                            val.isIntegerNumber = true;
                        }
                    } else {
                        val.isString = true;
                        val.string_storage = input;
                    }
                    int const memory_index = memseg.getIntegerValueIfExisting();
                    if (memory_index < 0) {
                        return 1;
                    }
                    if (memory_value == _nost) {
                        return 1;
                    } else if (memory_value == _mem) {
                        mem[memory_index] = val;
                    } else if (memory_value == _temp) {
                        temp.top()[memory_index] = val;
                    } else if (memory_value == _param) {
                        param.push(val);
                    } else {
                        if (vars::DEBUG) {
                            std::stringstream ss;
                            ss << "error " << "Error 0x2369: Invalid memseg '0x" << std::hex << memory_value << "'." << '\n'
                                << "Unless you tried to modify the bytecode file by hand, check your code. This may not be your fault. If it isn't, please contact the creator with the error code and the value given.";
                            std::string val{ss.str()};
                            write(socket_id, val.c_str(), 4096);
                            ERROR = true;
                        }
                        return -85;
                    }
                    return 1;
                }
                default: {
                    if (vars::DEBUG) {
                        std::stringstream ss;
                        ss << "error " << "Error 0x0563: Invalid argument ('" << arg0.getStringValueIfExisting() << "', " << arg0.getIntegerValueIfExisting() << ", " << arg0.getDoubleValueIfExisting() << ") specified for $sys." << '\n'
                            << "If you tried to modify the bytecode file, please regenerate one with the compiler given for this job.";
                        std::string val{ss.str()};
                        write(socket_id, val.c_str(), 4096);
                        ERROR = true;
                    }
                    return -7;
                }
            }
            return 1;
        }
        case info::SystemOpcodes::BACK: {
            if (call_stack.empty()) {
                if (vars::DEBUG) {
                    std::stringstream ss;
                    ss << "error " << "Error 0x3678: Empty call stack while using $back" << '\n'
                        << "This is entirely your fault. You put one $back too much, or made one $call too much. Please review your code.";
                    std::string val{ss.str()};
                    write(socket_id, val.c_str(), 4096);
                    ERROR = true;
                }
                return -45;
            }
            line_number = call_stack.top();
            call_stack.pop();
            temp.pop();
            return 1;
        }
        case info::SystemOpcodes::LBL: {
            return 1;
        }
        case info::SystemOpcodes::JMP: {
            ByteToken const arg0 = c->getArgs()[0];
            if (!arg0.isString()) {
                if (vars::DEBUG) {
                    std::stringstream ss;
                    ss << "error " << "Error 0x0563: Invalid argument ('" << arg0.getStringValueIfExisting() << "', " << arg0.getIntegerValueIfExisting() << ", " << arg0.getDoubleValueIfExisting() << ") specified for $jmp." << '\n'
                        << "If you tried to modify the bytecode file, please regenerate one with the compiler given for this job.";
                    std::string val{ss.str()};
                    write(socket_id, val.c_str(), 4096);
                    ERROR = true;
                }
                return -7;
            }
            std::string const lbl = arg0.getStringValueIfExisting();
            if (labels.find(lbl) == labels.end()) {
                if (vars::DEBUG) {
                    std::stringstream ss;
                    ss << "error " << "Error 0x6532: Unknown label '" << lbl << "'." << '\n'
                        << "If you tried to modify the bytecode file, please modify it the good way, or use the compiler to generate a correct bytecode file. If you did not try to modify it, please contact the creator with the error code.";
                    std::string val{ss.str()};
                    write(socket_id, val.c_str(), 4096);
                    ERROR = true;
                }
                return -65;
            }
            line_number = labels[lbl];
            return 1;
        }
        case info::SystemOpcodes::CALL: {
            ByteToken const arg0 = c->getArgs()[0];
            if (!arg0.isString()) {
                if (vars::DEBUG) {
                    std::stringstream ss;
                    ss << "error " << "Error 0x0563: Invalid argument ('" << arg0.getStringValueIfExisting() << "', " << arg0.getIntegerValueIfExisting() << ", " << arg0.getDoubleValueIfExisting() << ") specified for $jmp." << '\n'
                        << "If you tried to modify the bytecode file, please regenerate one with the compiler given for this job.";
                    std::string val{ss.str()};
                    write(socket_id, val.c_str(), 4096);
                    ERROR = true;
                }
                return -7;
            }
            std::string const lbl = arg0.getStringValueIfExisting();
            if (labels.find(lbl) == labels.end()) {
                if (vars::DEBUG) {
                    std::stringstream ss;
                    ss << "error " << "Error 0x6532: Unknown label '" << lbl << "'." << '\n'
                        << "If you tried to modify the bytecode file, please modify it the good way, or use the compiler to generate a correct bytecode file. If you did not try to modify it, please contact the creator with the error code.";
                    std::string val{ss.str()};
                    write(socket_id, val.c_str(), 4096);
                    ERROR = true;
                }
                return -65;
            }
            call_stack.push(line_number);
            line_number = labels[lbl];
            temp.push({});
            return 1;
        }
        default: {
            if (vars::DEBUG) {
                std::stringstream ss;
                ss << "error " << "Error 0x6312: The opcode '0x" << std::hex << value << "' does not belong to the `system` category provided by the language." << '\n'
                    << "Please contact the creator giving him the opcode as well as the error encountered if you didn't modify the file with the extension `.ssbc` by hand. If you did, then you might have done something wrong.";
                std::string val{ss.str()};
                write(socket_id, val.c_str(), 4096);
                ERROR = true;
            }
            return -1;
        }
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
            val.isNull = false;
            ByteToken const arg0 = c->getArgs()[0];
            if (arg0.isIntegerNumber()) {
                val.isIntegerNumber = true;
                val.integer_storage = arg0.getIntegerValueIfExisting();
            } else if (arg0.isDoubleNumber()) {
                val.isFloatingNumber = true;
                val.float_storage = arg0.getDoubleValueIfExisting();
            } else if (arg0.isString()) {
                val.isString = true;
                val.string_storage = arg0.getStringValueIfExisting();
            } else if (arg0.isMemory()) {
                uint64_t const memory_segment = arg0.getValueIfExisting();
                int const index = arg0.getIntegerValueIfExisting();
                if (index > 0) {
                    if (memory_segment == _mem) {
                        val = mem[index];
                    } else if (memory_segment == _temp) {
                        val = temp.top()[index];
                    } else if (memory_segment == _param) {
                        if (vars::DEBUG) {
                            std::stringstream ss;
                            ss << "error " << "Error 0x3258: Invalid segment '0x" << std::hex << memory_segment << "' used with instruction $store." << '\n'
                                << "It is recommended that you check your code and recompile it. If the issue is not solved, please contact the creator giving him the error code as well as the memory segment causing the error.";
                            std::string val{ss.str()};
                            write(socket_id, val.c_str(), 4096);
                            ERROR = true;
                        }
                        return -87;
                    } else if (memory_value != _nost) {
                        if (vars::DEBUG) {
                            std::stringstream ss;
                            ss << "error " << "Error 0x2369: Invalid memseg '0x" << std::hex << memory_value << "'." << '\n'
                                << "Unless you tried to modify the bytecode file by hand, check your code. This may not be your fault. If it isn't, please contact the creator with the error code and the value given.";
                            std::string val{ss.str()};
                            write(socket_id, val.c_str(), 4096);
                            ERROR = true;
                        }
                        return -85;
                    }
                }
            } else {
                if (vars::DEBUG) {
                    std::stringstream ss;
                    ss << "error " << "Error 0x5968: Invalid token ('" << arg0.getStringValueIfExisting() << "', " << arg0.getValueIfExisting() << ", " << arg0.getIntegerValueIfExisting() << "." << '\n'
                        << "If you did not try to modify the bytecode file by hand, it is recommended to contact the creator giving him the error code as well as the token in fault.";
                    std::string val{ss.str()};
                    write(socket_id, val.c_str(), 4096);
                    ERROR = true;
                }
                return -63;
            }
            if (!memseg.isMemory()) {
                if (vars::DEBUG) {
                    std::stringstream ss;
                    ss << "error " << "Error 0x9834: Invalid integer number ('" << memseg.getStringValueIfExisting() << "', " << memseg.getIntegerValueIfExisting() << ", " << memseg.getDoubleValueIfExisting() << ") used as a memory segment index." << '\n'
                        << "If you did not modify the bytecode file by hand, please contact the creator giving him the error code as well as the bytecode.";
                    std::string val{ss.str()};
                    write(socket_id, val.c_str(), 4096);
                    ERROR = true;
                }
                return -32;
            }
            if (memseg.getIntegerValueIfExisting() < 0) {
                return 1;
            }
            if (memory_value == _nost) {
                return 1;
            } else if (memory_value == _temp) {
                temp.top()[memseg.getIntegerValueIfExisting()] = val;
            } else if (memory_value == _param) {
                if (vars::DEBUG) {
                    std::stringstream ss;
                    ss << "error " << "Error 0x3258: Invalid segment '0x" << std::hex << memory_value << "' used with instruction $store." << '\n'
                        << "It is recommended that you check your code and recompile it. If the issue is not solved, please contact the creator giving him the error code as well as the memory segment causing the error.";
                    std::string val{ss.str()};
                    write(socket_id, val.c_str(), 4096);
                    ERROR = true;
                }
                return -87;
            } else if (memory_value == _mem) {
                mem[memseg.getIntegerValueIfExisting()] = val;
            } else {
                if (vars::DEBUG) {
                    std::stringstream ss;
                    ss << "error " << "Error 0x2369: Invalid memseg '0x" << std::hex << memory_value << "'." << '\n'
                        << "Unless you tried to modify the bytecode file by hand, check your code. This may not be your fault. If it isn't, please contact the creator with the error code and the value given.";
                    std::string val{ss.str()};
                    write(socket_id, val.c_str(), 4096);
                    ERROR = true;
                }
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
                if (vars::DEBUG) {
                    std::stringstream ss;
                    ss << "error " << "Error 0x3258: Invalid segment '0x" << std::hex << memory_value << "' used with instruction $push." << '\n'
                        << "It is recommended that you check your code and recompile it. If the issue is not solved, please contact the creator giving him the error code as well as the memory segment causing the error.";
                    std::string val{ss.str()};
                    write(socket_id, val.c_str(), 4096);
                    ERROR = true;
                }
                return -87;
            }
            if (memory_value == _nost) {
                return 1;
            }
            ValueContainer val;
            val.isNull = false;
            ByteToken const arg0 = c->getArgs()[0];
            if (arg0.isIntegerNumber()) {
                val.isIntegerNumber = true;
                val.integer_storage = arg0.getIntegerValueIfExisting();
            } else if (arg0.isDoubleNumber()) {
                val.isFloatingNumber = true;
                val.float_storage = arg0.getDoubleValueIfExisting();
            } else if (arg0.isString()) {
                val.isString = true;
                val.string_storage = arg0.getStringValueIfExisting();
            } else if (arg0.isMemory()) {
                uint64_t const memory_segment = arg0.getValueIfExisting();
                int const index = arg0.getIntegerValueIfExisting();
                if (index > 0) {
                    if (memory_segment == _mem) {
                        val = mem[index];
                    } else if (memory_segment == _temp) {
                        val = temp.top()[index];
                    } else if (memory_segment == _param) {
                        if (vars::DEBUG) {
                            std::stringstream ss;
                            ss << "error " << "Error 0x3258: Invalid segment '0x" << std::hex << memory_segment << "' used with instruction $store." << '\n'
                                << "It is recommended that you check your code and recompile it. If the issue is not solved, please contact the creator giving him the error code as well as the memory segment causing the error.";
                            std::string val{ss.str()};
                            write(socket_id, val.c_str(), 4096);
                            ERROR = true;
                        }
                        return -87;
                    } else if (memory_value != _nost) {
                        if (vars::DEBUG) {
                            std::stringstream ss;
                            ss << "error " << "Error 0x2369: Invalid memseg '0x" << std::hex << memory_value << "'." << '\n'
                                << "Unless you tried to modify the bytecode file by hand, check your code. This may not be your fault. If it isn't, please contact the creator with the error code and the value given.";
                            std::string val{ss.str()};
                            write(socket_id, val.c_str(), 4096);
                            ERROR = true;
                        }
                        return -85;
                    }
                }
            } else {
                if (vars::DEBUG) {
                    std::stringstream ss;
                    ss << "error " << "Error 0x5968: Invalid token ('" << arg0.getStringValueIfExisting() << "', " << arg0.getValueIfExisting() << ", " << arg0.getIntegerValueIfExisting() << "." << '\n'
                        << "If you did not try to modify the bytecode file by hand, it is recommended to contact the creator giving him the error code as well as the token in fault.";
                    std::string val{ss.str()};
                    write(socket_id, val.c_str(), 4096);
                    ERROR = true;
                }
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
                if (vars::DEBUG) {
                    std::stringstream ss;
                    ss << "error " << "Error 0x5968: Invalid token ('" << arg0.getStringValueIfExisting() << "', " << arg0.getValueIfExisting() << ", " << arg0.getIntegerValueIfExisting() << "." << '\n'
                        << "If you did not try to modify the bytecode file by hand, it is recommended to contact the creator giving him the error code as well as the token in fault.";
                    std::string val{ss.str()};
                    write(socket_id, val.c_str(), 4096);
                    ERROR = true;
                }
                return -63;
            }
            double const pop_seg = arg0.getValueIfExisting();
            if (pop_seg == _mem || pop_seg == _temp) {
                if (vars::DEBUG) {
                    std::stringstream ss;
                    ss << "error " << "Error 0x3258: Invalid segment '0x" << std::hex << memory_value << "' used with instruction $pop." << '\n'
                        << "It is recommended that you check your code and recompile it. If the issue is not solved, please contact the creator giving him the error code as well as the memory segment causing the error.";
                    std::string val{ss.str()};
                    write(socket_id, val.c_str(), 4096);
                    ERROR = true;
                }
                return -87;
            }
            if (pop_seg == _nost) {
                return 1;
            }
            if (static_cast<uint8_t>(memseg.getValueIfExisting()) == _nost) {
                if (pop_seg == _param) {
                    param.pop();
                    return 1;
                }
            } else {
                ValueContainer val;
                if (!memseg.isIntegerNumber()) {
                    if (vars::DEBUG) {
                        std::stringstream ss;
                        ss << "error " << "Error 0x9834: Invalid integer number ('" << memseg.getStringValueIfExisting() << "', " << memseg.getIntegerValueIfExisting() << ", " << memseg.getDoubleValueIfExisting() << ") used as a memory segment index." << '\n'
                            << "If you did not modify the bytecode file by hand, please contact the creator giving him the error code as well as the bytecode.";
                        std::string val{ss.str()};
                        write(socket_id, val.c_str(), 4096);
                        ERROR = true;
                    }
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
                    temp.top()[index] = val;
                } else if (seg == _param) {
                    param.push(val);
                }
            }
            return 1;;
        }
        case info::MemoryOpcodes::FREE: {
            ByteToken const arg0 = c->getArgs()[0];
            if (!arg0.isMemory()) {
                if (vars::DEBUG) {
                    std::stringstream ss;
                    ss << "error " << "Error 0x5968: Invalid token ('" << arg0.getStringValueIfExisting() << "', " << arg0.getValueIfExisting() << ", " << arg0.getIntegerValueIfExisting() << "." << '\n'
                        << "If you did not try to modify the bytecode file by hand, it is recommended to contact the creator giving him the error code as well as the token in fault.";
                    std::string val{ss.str()};
                    write(socket_id, val.c_str(), 4096);
                    ERROR = true;
                }
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
                if (vars::DEBUG) {
                    std::stringstream ss;
                    ss << "error " << "Error 0x3258: Invalid segment '0x" << std::hex << memory_value << "' used with instruction $free." << '\n'
                        << "It is recommended that you check your code and recompile it. If the issue is not solved, please contact the creator giving him the error code as well as the memory segment causing the error.";
                    std::string val{ss.str()};
                    write(socket_id, val.c_str(), 4096);
                    ERROR = true;
                }
                return -87;
            }
            int const index = arg0.getIntegerValueIfExisting();
            if (index < 0) {
                if (vars::DEBUG) {
                    std::stringstream ss;
                    ss << "error " << "Error 0x9834: Invalid integer number ('" << arg0.getStringValueIfExisting() << "', " << arg0.getIntegerValueIfExisting() << ", " << arg0.getDoubleValueIfExisting() << ") used as a memory segment index." << '\n'
                        << "If you did not modify the bytecode file by hand, please contact the creator giving him the error code as well as the bytecode.";
                    std::string val{ss.str()};
                    write(socket_id, val.c_str(), 4096);
                    ERROR = true;
                }
                return -32;
            }
            if (memory_value == _mem) {
                std::remove(mem.begin(), mem.end(), mem[index]);
                return 1;
            } else if (memory_value == _temp) {
                std::remove(temp.top().begin(), temp.top().end(), temp.top()[index]);
                return 1;
            } else {
                if (vars::DEBUG) {
                    std::stringstream ss;
                    ss << "error " << "Error 0x2369: Invalid memseg '0x" << std::hex << memory_value << "'." << '\n'
                        << "Unless you tried to modify the bytecode file by hand, check your code. This may not be your fault. If it isn't, please contact the creator with the error code and the value given.";
                    std::string val{ss.str()};
                    write(socket_id, val.c_str(), 4096);
                    ERROR = true;
                }
                return -85;
            }
            return 1;
        }
        default: {
            if (vars::DEBUG) {
                std::stringstream ss;
                ss << "error " << "Error 0x6313: The opcode '0x" << std::hex << value << "' does not belong to the `memory` category provided by the language." << '\n'
                    << "Please contact the creator giving him the opcode as well as the error encountered if you didn't modify the file with the extension `.ssbc` by hand. If you did, then you might have done something wrong.";
                std::string val{ss.str()};
                write(socket_id, val.c_str(), 4096);
                ERROR = true;
            }
            return -1;
        }
    }
}

int8_t Interpreter::executeMathsConsumer(ByteConsumer* const& c) {
    uint64_t value = static_cast<uint64_t>(c->getInstruction().getValueIfExisting());
    uint64_t const memory_value = c->getStorage().getMemory().getValueIfExisting(),
                           _mem = info::m_bytes["mem"],
                           _temp = info::m_bytes["temp"],
                           _param = info::m_bytes["param"],
                           _nost = info::m_bytes["nost"];
    ByteToken const arg0 = c->getArgs()[0],
                    arg1 = c->getArgs()[1];
    if (arg0.isDoubleNumber() || arg0.isString()) {
        if (vars::DEBUG) {
            std::stringstream ss;
            ss << "error " << "Error 0x9834: Invalid integer number ('" << arg0.getStringValueIfExisting() << "', " << arg0.getIntegerValueIfExisting() << ", " << arg0.getDoubleValueIfExisting() << ") used as a memory segment index." << '\n'
                << "If you did not modify the bytecode file by hand, please contact the creator giving him the error code as well as the bytecode.";
            std::string val{ss.str()};
            write(socket_id, val.c_str(), 4096);
            ERROR = true;
        }
        return -32;
    }
    if (arg1.isDoubleNumber() || arg1.isString()) {
        if (vars::DEBUG) {
            std::stringstream ss;
            ss << "error " << "Error 0x9834: Invalid integer number ('" << arg1.getStringValueIfExisting() << "', " << arg1.getIntegerValueIfExisting() << ", " << arg1.getDoubleValueIfExisting() << ") used as a memory segment index." << '\n'
                << "If you did not modify the bytecode file by hand, please contact the creator giving him the error code as well as the bytecode.";
            std::string val{ss.str()};
            write(socket_id, val.c_str(), 4096);
            ERROR = true;
        }
        return -32;
    }
    ValueContainer val0, val1;
    val0.isNull = false;
    val1.isNull = false;
    if (arg0.isIntegerNumber()) {
        val0.isIntegerNumber = true;
        val0.integer_storage = arg0.getIntegerValueIfExisting();
    } else if (arg0.isMemory()) {
        uint64_t const seg = arg0.getValueIfExisting();
        int const index = arg0.getIntegerValueIfExisting();
        ValueContainer tmp;
        if (seg == _mem) {
            tmp = mem[index];
        } else if (seg == _temp) {
            tmp = temp.top()[index];
        } else {
            if (vars::DEBUG) {
                std::stringstream ss;
                ss << "error " << "Error 0x2369: Invalid memseg '0x" << std::hex << memory_value << "'." << '\n'
                    << "Unless you tried to modify the bytecode file by hand, check your code. This may not be your fault. If it isn't, please contact the creator with the error code and the value given.";
                std::string val{ss.str()};
                write(socket_id, val.c_str(), 4096);
                ERROR = true;
            }
            return -85;
        }
        if (!tmp.isIntegerNumber) {
            if (vars::DEBUG) {
                std::stringstream ss;
                ss << "error " << "Error 0x9834: Invalid integer number " << tmp << " used as a memory segment index." << '\n'
                    << "If you did not modify the bytecode file by hand, please contact the creator giving him the error code as well as the bytecode.";
                std::string val{ss.str()};
                write(socket_id, val.c_str(), 4096);
                ERROR = true;
            }
            return -32;
        }
        val0 = tmp;
    } else {
        if (vars::DEBUG) {
            std::stringstream ss;
            ss << "error " << "Error 0x9834: Invalid integer number ('" << arg0.getStringValueIfExisting() << "', " << arg0.getIntegerValueIfExisting() << ", " << arg0.getDoubleValueIfExisting() << ") used as a memory segment index." << '\n'
                << "If you did not modify the bytecode file by hand, please contact the creator giving him the error code as well as the bytecode.";
            std::string val{ss.str()};
            write(socket_id, val.c_str(), 4096);
            ERROR = true;
        }
        return -32;
    }
    if (arg1.isIntegerNumber()) {
        val1.isIntegerNumber = true;
        val1.integer_storage = arg1.getIntegerValueIfExisting();
    } else if (arg1.isMemory()) {
        uint64_t const seg = arg1.getValueIfExisting();
        int const index = arg1.getIntegerValueIfExisting();
        ValueContainer tmp;
        if (seg == _mem) {
            tmp = mem[index];
        } else if (seg == _temp) {
            tmp = temp.top()[index];
        } else {
            if (vars::DEBUG) {
                std::stringstream ss;
                ss << "error " << "Error 0x2369: Invalid memseg '0x" << std::hex << memory_value << "'." << '\n'
                    << "Unless you tried to modify the bytecode file by hand, check your code. This may not be your fault. If it isn't, please contact the creator with the error code and the value given.";
                std::string val{ss.str()};
                write(socket_id, val.c_str(), 4096);
                ERROR = true;
            }
            return -85;
        }
        if (!tmp.isIntegerNumber) {
            if (vars::DEBUG) {
                std::stringstream ss;
                ss << "error " << "Error 0x9834: Invalid integer number " << tmp << " used as a memory segment index." << '\n'
                    << "If you did not modify the bytecode file by hand, please contact the creator giving him the error code as well as the bytecode.";
                std::string val{ss.str()};
                write(socket_id, val.c_str(), 4096);
                ERROR = true;
            }
            return -32;
        }
        val1 = tmp;
    } else {
        if (vars::DEBUG) {
            std::stringstream ss;
            ss << "error " << "Error 0x9834: Invalid integer number ('" << arg1.getStringValueIfExisting() << "', " << arg1.getIntegerValueIfExisting() << ", " << arg1.getDoubleValueIfExisting() << ") used as a memory segment index." << '\n'
                << "If you did not modify the bytecode file by hand, please contact the creator giving him the error code as well as the bytecode.";
            std::string val{ss.str()};
            write(socket_id, val.c_str(), 4096);
            ERROR = true;
        }
        return -32;
    }
    ValueContainer result;
    result.isNull = false;
    switch (value) {
        case info::MathsOpcodes::ADD: {
            result.isIntegerNumber = true;
            result.integer_storage = val0.integer_storage + val1.integer_storage;
            break;
        }
        case info::MathsOpcodes::SUB: {
            result.isIntegerNumber = true;
            result.integer_storage = val0.integer_storage - val1.integer_storage;
            break;
        }
        case info::MathsOpcodes::MUL: {
            result.isIntegerNumber = true;
            result.integer_storage = val0.integer_storage * val1.integer_storage;
            break;
        }
        case info::MathsOpcodes::DIV: {
            if (val1.integer_storage == 0) {
                if (vars::DEBUG) {
                    std::stringstream ss;
                    ss << "error " << "Error 0x4695: Dividing by 0." << '\n'
                        << "Please make sure to not divide by 0 anymore !";
                    std::string val{ss.str()};
                    write(socket_id, val.c_str(), 4096);
                    ERROR = true;
                }
                return -24;
            }
            result.isIntegerNumber = true;
            result.integer_storage = static_cast<int64_t>(val0.integer_storage / val1.integer_storage);
            break;
        }
        case info::MathsOpcodes::RAND: {
            std::uniform_int_distribution<> distrib(val0.integer_storage, val1.integer_storage);
            result.isIntegerNumber = true;
            result.integer_storage = static_cast<int64_t>(distrib(generator));
            break;
        }
        case info::MathsOpcodes::MOD: {
            result.isIntegerNumber = true;
            result.integer_storage = val0.integer_storage % val1.integer_storage;
            break;
        }
        default: {
            if (vars::DEBUG) {
                std::stringstream ss;
                ss << "error " << "Error 0x6314: The opcode '0x" << std::hex << value << "' does not belong to the `integer maths` category provided by the language." << '\n'
                    << "Please contact the creator giving him the opcode as well as the error encountered if you didn't modify the file with the extension `.ssbc` by hand. If you did, then you might have done something wrong.";
                std::string val{ss.str()};
                write(socket_id, val.c_str(), 4096);
                ERROR = true;
            }
            return -1;
        }
    }
    int const index = c->getStorage().getMemory().getIntegerValueIfExisting();
    if (index == -1) {
        return 1;
    }
    if (memory_value == _mem) {
        mem[index] = result;
    } else if (memory_value == _temp) {
        temp.top()[index] = result;
    } else if (memory_value == _param) {
        param.push(result);
    } else if (memory_value == _nost) {
        return 1;
    } else {
        if (vars::DEBUG) {
            std::stringstream ss;
            ss << "error " << "Error 0x2369: Invalid memseg '0x" << std::hex << memory_value << "'." << '\n'
                << "Unless you tried to modify the bytecode file by hand, check your code. This may not be your fault. If it isn't, please contact the creator with the error code and the value given.";
            std::string val{ss.str()};
            write(socket_id, val.c_str(), 4096);
            ERROR = true;
        }
        return -85;
    }
    return 1;
}

int8_t Interpreter::executeComparativeConsumer(ByteConsumer* const& c) {
    uint64_t value = static_cast<uint64_t>(c->getInstruction().getValueIfExisting());
    switch (value) {
        case info::ComparativeOpcodes::CMP: {
            uint64_t const _mem = info::m_bytes["mem"],
                           _temp = info::m_bytes["temp"];
            ByteToken const arg0 = c->getArgs()[0],
                            arg1 = c->getArgs()[1];
            ValueContainer val0, val1;
            val0.isNull = false;
            val1.isNull = false;
            if (arg0.isDoubleNumber()) {
                val0.isFloatingNumber = true;
                val0.float_storage = arg0.getDoubleValueIfExisting();
            } else if (arg0.isIntegerNumber()) {
                val0.isIntegerNumber = true;
                val0.integer_storage = arg0.getIntegerValueIfExisting();
            } else if (arg0.isString()) {
                val0.isString = true;
                val0.string_storage = arg0.getStringValueIfExisting();
            } else if (arg0.isMemory()) {
                uint64_t const seg = arg0.getValueIfExisting();
                int const index = arg0.getIntegerValueIfExisting();
                if (index > 0) {
                    if (seg == _mem) {
                        val0 = mem[index];
                    } else if (seg == _temp) {
                        val0 = temp.top()[index];
                    } else {
                        if (vars::DEBUG) {
                            std::stringstream ss;
                            ss << "error " << "Error 0x2369: Invalid memseg '0x" << std::hex << seg << "'." << '\n'
                                << "Unless you tried to modify the bytecode file by hand, check your code. This may not be your fault. If it isn't, please contact the creator with the error code and the value given.";
                            std::string val{ss.str()};
                            write(socket_id, val.c_str(), 4096);
                            ERROR = true;
                        }
                        return -85;
                    }
                }
            }
            if (arg1.isDoubleNumber()) {
                val1.isFloatingNumber = true;
                val1.float_storage = arg1.getDoubleValueIfExisting();
            } else if (arg1.isIntegerNumber()) {
                val1.isIntegerNumber = true;
                val1.integer_storage = arg1.getIntegerValueIfExisting();
            } else if (arg1.isString()) {
                val1.isString = true;
                val1.string_storage = arg1.getStringValueIfExisting();
            } else if (arg1.isMemory()) {
                uint64_t const seg = arg1.getValueIfExisting();
                int const index = arg1.getIntegerValueIfExisting();
                if (index > 0) {
                    if (seg == _mem) {
                        val1 = mem[index];
                    } else if (seg == _temp) {
                        val1 = temp.top()[index];
                    } else {
                        if (vars::DEBUG) {
                            std::stringstream ss;
                            ss << "error " << "Error 0x2369: Invalid memseg '0x" << std::hex << seg << "'." << '\n'
                                << "Unless you tried to modify the bytecode file by hand, check your code. This may not be your fault. If it isn't, please contact the creator with the error code and the value given.";
                            std::string val{ss.str()};
                            write(socket_id, val.c_str(), 4096);
                            ERROR = true;
                        }
                        return -85;
                    }
                }
            }

            if (val0 == val1) {
                condition = 1;
            } else if (val0 > val1) {
                condition = 2;
            } else if (val0 < val1) {
                condition = -2;
            } else {
                condition = -1;
            }
            return 1;
        }
        case info::ComparativeOpcodes::JWE: {
            ByteToken const arg0 = c->getArgs()[0];
            if (!arg0.isString()) {
                if (vars::DEBUG) {
                    std::stringstream ss;
                    ss << "error " << "Error 0x0563: Invalid argument ('" << arg0.getStringValueIfExisting() << "', " << arg0.getIntegerValueIfExisting() << ", " << arg0.getDoubleValueIfExisting() << ") specified for $jmp." << '\n'
                        << "If you tried to modify the bytecode file, please regenerate one with the compiler given for this job.";
                    std::string val{ss.str()};
                    write(socket_id, val.c_str(), 4096);
                    ERROR = true;
                }
                return -7;
            }
            std::string const lbl = arg0.getStringValueIfExisting();
            if (labels.find(lbl) == labels.end()) {
                if (vars::DEBUG) {
                    std::stringstream ss;
                    ss << "error " << "Error 0x6532: Unknown label '" << lbl << "'." << '\n'
                        << "If you tried to modify the bytecode file, please modify it the good way, or use the compiler to generate a correct bytecode file. If you did not try to modify it, please contact the creator with the error code.";
                    std::string val{ss.str()};
                    write(socket_id, val.c_str(), 4096);
                    ERROR = true;
                }
                return -65;
            }
            if (condition == 1) {
                line_number = labels[lbl];
            }
            return 1;
        }
        case info::ComparativeOpcodes::JWD: {
            ByteToken const arg0 = c->getArgs()[0];
            if (!arg0.isString()) {
                if (vars::DEBUG) {
                    std::stringstream ss;
                    ss << "error " << "Error 0x0563: Invalid argument ('" << arg0.getStringValueIfExisting() << "', " << arg0.getIntegerValueIfExisting() << ", " << arg0.getDoubleValueIfExisting() << ") specified for $jmp." << '\n'
                        << "If you tried to modify the bytecode file, please regenerate one with the compiler given for this job.";
                    std::string val{ss.str()};
                    write(socket_id, val.c_str(), 4096);
                    ERROR = true;
                }
                return -7;
            }
            std::string const lbl = arg0.getStringValueIfExisting();
            if (labels.find(lbl) == labels.end()) {
                if (vars::DEBUG) {
                    std::stringstream ss;
                    ss << "error " << "Error 0x6532: Unknown label '" << lbl << "'." << '\n'
                        << "If you tried to modify the bytecode file, please modify it the good way, or use the compiler to generate a correct bytecode file. If you did not try to modify it, please contact the creator with the error code.";
                    std::string val{ss.str()};
                    write(socket_id, val.c_str(), 4096);
                    ERROR = true;
                }
                return -65;
            }
            if (condition != 1 && condition != 0) {
                line_number = labels[lbl];
            }
            return 1;
        }
        case info::ComparativeOpcodes::JWG: {
            ByteToken const arg0 = c->getArgs()[0];
            if (!arg0.isString()) {
                if (vars::DEBUG) {
                    std::stringstream ss;
                    ss << "error " << "Error 0x0563: Invalid argument ('" << arg0.getStringValueIfExisting() << "', " << arg0.getIntegerValueIfExisting() << ", " << arg0.getDoubleValueIfExisting() << ") specified for $jmp." << '\n'
                        << "If you tried to modify the bytecode file, please regenerate one with the compiler given for this job.";
                    std::string val{ss.str()};
                    write(socket_id, val.c_str(), 4096);
                    ERROR = true;
                }
                return -7;
            }
            std::string const lbl = arg0.getStringValueIfExisting();
            if (labels.find(lbl) == labels.end()) {
                if (vars::DEBUG) {
                    std::stringstream ss;
                    ss << "error " << "Error 0x6532: Unknown label '" << lbl << "'." << '\n'
                        << "If you tried to modify the bytecode file, please modify it the good way, or use the compiler to generate a correct bytecode file. If you did not try to modify it, please contact the creator with the error code.";
                    std::string val{ss.str()};
                    write(socket_id, val.c_str(), 4096);
                    ERROR = true;
                }
                return -65;
            }
            if (condition == 2) {
                line_number = labels[lbl];
            }
            return 1;
        }
        case info::ComparativeOpcodes::JWL: {
            ByteToken const arg0 = c->getArgs()[0];
            if (!arg0.isString()) {
                if (vars::DEBUG) {
                    std::stringstream ss;
                    ss << "error " << "Error 0x0563: Invalid argument ('" << arg0.getStringValueIfExisting() << "', " << arg0.getIntegerValueIfExisting() << ", " << arg0.getDoubleValueIfExisting() << ") specified for $jmp." << '\n'
                        << "If you tried to modify the bytecode file, please regenerate one with the compiler given for this job.";
                    std::string val{ss.str()};
                    write(socket_id, val.c_str(), 4096);
                    ERROR = true;
                }
                return -7;
            }
            std::string const lbl = arg0.getStringValueIfExisting();
            if (labels.find(lbl) == labels.end()) {
                if (vars::DEBUG) {
                    std::stringstream ss;
                    ss << "error " << "Error 0x6532: Unknown label '" << lbl << "'." << '\n'
                        << "If you tried to modify the bytecode file, please modify it the good way, or use the compiler to generate a correct bytecode file. If you did not try to modify it, please contact the creator with the error code.";
                    std::string val{ss.str()};
                    write(socket_id, val.c_str(), 4096);
                    ERROR = true;
                }
                return -65;
            }
            if (condition == -2) {
                line_number = labels[lbl];
            }
            return 1;
        }
        default: {
            if (vars::DEBUG) {
                std::stringstream ss;
                ss << "error " << "Error 0x6315: The opcode '0x" << std::hex << value << "' does not belong to the `comparative` category provided by the language." << '\n'
                    << "Please contact the creator giving him the opcode as well as the error encountered if you didn't modify the file with the extension `.ssbc` by hand. If you did, then you might have done something wrong.";
                std::string val{ss.str()};
                write(socket_id, val.c_str(), 4096);
                ERROR = true;
            }
            return -1;
        }
    }
}