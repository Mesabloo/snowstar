#include <algorithm>
#include <stack>
#include <array>

#include "parser.hpp"
#include <info.hpp>
#include <Utils/utils.hpp>
#include <termcolor.hpp>

Parser::Parser(std::vector<std::vector<Token>> const& lines) {
    std::vector<std::vector<Token>> no_comment;
    std::vector<Token> line;
    for (auto const& l : lines) {
        for (auto const& t : l) {
            if (t.getType() != Token::Type::INLINE_COMMENT && t.getType() != Token::Type::MULTILINE_COMMENT)
                line.push_back(t);
            else {
                if (t.getType() == Token::Type::MULTILINE_COMMENT) {
                    for (size_t i{0};i < utils::str_split(t.getValue(), '\n').size()-1;++i) {
                        no_comment.push_back(line);
                        line = {Token(Token::Type::EOL, "")};
                    }
                }
            }
            if (t.getType() == Token::Type::EOL) {
                no_comment.push_back(line);
                line = {};
            }
        }
    }
    no_comment.push_back(line);
    for (auto& l : no_comment) {
        if (l.size() > 1) {
            if (l[0].getType() == Token::Type::EOL)
                l.erase(l.begin());
        }
    }
    m_lines = no_comment;
}
Parser::~Parser() {}

auto Parser::assertSyntax() const -> std::vector<Exception> {
    std::vector<Exception> excepts;
    for (unsigned long i{0};i < m_lines.size();++i) {
        if (m_lines[i].empty()) continue;
        for (auto const& t : m_lines[i]) {
            if (t.getType() == Token::Type::INVALID) {
                excepts.push_back(Exception("UnknownTokenException", 0x5A639C54, "The token '" + t.getValue() + "' at line " + std::to_string(i+1) + " doesn't exist."));
                continue;
            }
        }
        auto const& line = m_lines[i];
        auto const& instr = line[0];
        if (instr.getType() == Token::Type::EOL) continue;
        if (instr.getType() != Token::Type::KEYWORD && instr.getValue() != "mem" && instr.getValue() != "temp" && instr.getValue() != "param" && instr.getValue() != "nost") {
            excepts.push_back(Exception("InvalidTokenException", 0x36DE95C4, "The line " + std::to_string(i+1) + " is not starting with an instruction."));
        }
    }
    return excepts;
}

auto Parser::assertSemantics() -> std::vector<Exception> {
    std::array<Token::Type, 256> mem_emul;
    std::stack<std::array<Token::Type, 32>> temp_emul;
    temp_emul.push({});
    std::stack<Token::Type> param_emul;

    std::vector<Exception> excepts;
    for (unsigned long i{0};i < m_lines.size();++i) {
        if (m_lines[i].empty()) continue;
        auto const& line = m_lines[i];
        auto const& instr = line[0];
        if (instr.getType() == Token::Type::EOL) continue;
        std::vector<Consumer>::iterator c{info::m_syntax.begin()};
        std::unique_ptr<Consumer> cons{nullptr};
        std::vector<std::vector<Consumer>::iterator> holder;
        bool found{false};
        while (c != info::m_syntax.end()) {
            c = std::find_if(
                c+1,
                info::m_syntax.end(),
                [=] (Consumer const& c1) {
                    return c1.getInstruction() == instr;
                }
            );
            if (c == info::m_syntax.end() && !found)
                excepts.push_back(Exception("InstructionNotFoundException", 0x23D9645B, "Unknown instruction '" + instr.getValue() + "' at line " + std::to_string(i+1)));
            else {
                if (c == info::m_syntax.end()) continue;
                uint8_t argc{0}, to_deduce{0};
                Token tmp{instr};
                while (tmp.getType() != Token::Type::EOL) {
                    argc++;
                    tmp = line[argc];
                    if (tmp.getType() == Token::Type::SEPARATOR) {
                        to_deduce++;
                        continue;
                    }
                }
                std::vector<Token> args;
                uint8_t offset{0};
                if (c->getStorage().getMemseg().getValue() == "nost" && c->getStorage().getIndex().getValue() == "-1")
                    // no storage specifier. offset = 1 (args at offset+x) (instr [args, ...])
                    offset = 1;
                else
                    // storage specifier. offset = 2 (args at offset+x) (instr [storage] [args, ...])
                    offset = 2;
                argc -= offset;
                argc -= to_deduce;
                for (uint8_t i{0};i < argc*2;i += 2) {
                    args.push_back(line[offset+i]);
                }

                Consumer::Store st;
                if (offset == 2) {
                    auto t = line[1];
                    if (t.getType() != Token::Type::LITERAL_MEMORY) {
                        excepts.push_back(Exception("InvalidTokenException", 0xA67123D1, "Unexpected token '" + t.getValue() + "' at line " + std::to_string(i+1)));
                        continue;
                    }
                    std::string const memseg = utils::str_split(t.getValue(), '.')[0],
                                      index = utils::str_split(t.getValue(), '.')[1];
                    if (std::find(info::m_keywords.begin(), info::m_keywords.end(), Token(Token::Type::KEYWORD, memseg)) == info::m_keywords.end()) {
                        excepts.push_back(Exception("InvalidTokenException", 0x36BE6A5D, "Unknown memory segment '" + memseg + "' at line " + std::to_string(i+1)));
                        continue;
                    }
                    st = Consumer::Store(Token(Token::Type::KEYWORD, memseg), Token(Token::Type::LITERAL_NUMBER_INT, index));
                }

                cons = std::make_unique<Consumer>(instr, st, args);

                if (*cons == *c) {
                    found = true;
                    m_cons.push_back(*cons);
                    Consumer::Store const& cons_store{cons->getStorage()},
                               c_store{c->getStorage()};
                    std::string cons_seg{cons_store.getMemseg().getValue()},
                                c_seg{c_store.getMemseg().getValue()};
                    if (c_seg == "memory") {
                        if (cons_seg != "mem" && cons_seg != "temp") {
                            excepts.push_back(Exception("InvalidMemorySegmentException", 0x25AD6F3E, "Illegal use of memory segment '" + cons_seg + "' for instruction " + c->getInstruction().getValue() + " at line " + std::to_string(i+1)));
                            continue;
                        }
                    } else if (c_seg == "stack") {
                        if (cons_seg != "param") {
                            excepts.push_back(Exception("InvalidMemorySegmentException", 0x25AD6F3E, "Illegal use of memory segment '" + cons_seg + "' for instruction " + c->getInstruction().getValue() + " at line " + std::to_string(i+1)));
                            continue;
                        }
                    }
                    break;
                } else {
                    holder.push_back(c);
                }
            }
        }
        if (!found) {
            for (auto const& h : holder) {
                excepts.push_back(Exception("InvalidUsageException", 0x369BF1F2, "Invalid usage of instruction '" + instr.getValue() + "': " + h->toString() + " at line " + std::to_string(i+1)));
            }
            continue;
        }

    /*    Consumer checker{*cons};
        for (auto& arg : checker.getArgs()) {
            if (arg.getType() != Token::Type::LITERAL_MEMORY) continue;
            std::string const seg{utils::str_split(arg.getValue(), '.')[0]};
            int const index{std::stoi(utils::str_split(arg.getValue(), '.')[1])};
            try {
                if (seg == "mem") {
                    arg = Token(mem_emul[index], arg.getValue());
                    std::cout << termcolor::green << "mem." << std::to_string(index) << " <=> " << Token::getTypeSignification(arg.getType()) << termcolor::reset << std::endl;
                } else if (seg == "temp") {
                    arg = Token(temp_emul.top()[index], arg.getValue());
                    std::cout << termcolor::green << "temp." << std::to_string(index) << " <=> " << Token::getTypeSignification(arg.getType()) << termcolor::reset << std::endl;
                } else if (seg == "param") {
                    arg = Token(param_emul.top(), arg.getValue());
                    std::cout << termcolor::green << "param." << std::to_string(index) << " <=> " << Token::getTypeSignification(arg.getType()) << termcolor::reset << std::endl;
                }
            } catch (std::bad_alloc const& ba) {
                excepts.push_back(std::make_unique<Exception>("UndefinedMemoryIndexException", 0x56AB24D3, "Index " + std::to_string(index) + " provided for memory access inside " + seg + " is empty and so cannot be used at line " + std::to_string(i+1) + "."));
                continue;
            }
        }
        std::cout << termcolor::magenta << checker.getInstruction().getValue() << "[" << checker.getStorage().getMemseg().getValue() << "." << checker.getStorage().getIndex().getValue() << "] ";
        for (auto const arg : checker.getArgs()) {
            std::cout << Token::getTypeSignification(arg.getType()) << ", ";
        }
        std::cout << termcolor::reset << std::endl;
        if (checker.getStorage().getIndex().getValue() != "-1") {
            // not a `nost.-1`
            Token const& instr{checker.getInstruction()};
            std::string const& instr_name{instr.getValue()},
                               seg{checker.getStorage().getMemseg().getValue()};
            int const index{std::stoi(checker.getStorage().getIndex().getValue())};
            if (instr_name == "store") {
                if (seg == "mem") {
                    mem_emul[index] = checker.getArgs()[0].getType();
                } else if (seg == "temp") {
                    temp_emul.top()[index] = checker.getArgs()[0].getType();
                }
            } else if (instr_name == "push") {
                if (seg == "param") {
                    param_emul.push(checker.getArgs()[0].getType());
                }
            } else if (instr_name == "ftos" ||
                       instr_name == "itos" ||
                      (instr_name == "sys" && checker.getArgs()[0].getValue() == "2")) {
                if (seg == "mem") {
                    mem_emul[index] = Token::Type::LITERAL_STRING;
                } else if (seg == "temp") {
                    temp_emul.top()[index] = Token::Type::LITERAL_STRING;
                } else if (seg == "param") {
                    param_emul.push(Token::Type::LITERAL_STRING);
                }
            } else if (instr_name == "add" ||
                       instr_name == "mul" ||
                       instr_name == "div" ||
                       instr_name == "sub" ||
                       instr_name == "rand" ||
                       instr_name == "ftoi" ||
                       instr_name == "stoi" ||
                       instr_name == "and" ||
                       instr_name == "or" ||
                       instr_name == "xor" ||
                       instr_name == "not") {
                if (seg == "mem") {
                    mem_emul[index] = Token::Type::LITERAL_NUMBER_INT;
                } else if (seg == "temp") {
                    temp_emul.top()[index] = Token::Type::LITERAL_NUMBER_INT;
                } else if (seg == "param") {
                    param_emul.push(Token::Type::LITERAL_NUMBER_INT);
                }
            } else if (instr_name == "addf" ||
                       instr_name == "mulf" ||
                       instr_name == "divf" ||
                       instr_name == "subf" ||
                       instr_name == "randf" ||
                       instr_name == "itof" ||
                       instr_name == "stof") {
                if (seg == "mem") {
                    mem_emul[index] = Token::Type::LITERAL_NUMBER_FLOAT;
                } else if (seg == "temp") {
                    temp_emul.top()[index] = Token::Type::LITERAL_NUMBER_FLOAT;
                } else if (seg == "param") {
                    param_emul.push(Token::Type::LITERAL_NUMBER_FLOAT);
                }
            } else if (instr_name == "ret") {
                if (seg == "mem") {
                    mem_emul[index] = Token::Type::LITERAL_MEMORY;
                } else if (seg == "temp") {
                    temp_emul.top()[index] = Token::Type::LITERAL_MEMORY;
                } else if (seg == "param") {
                    param_emul.push(Token::Type::LITERAL_MEMORY);
                }
            }
        }
        auto tmp = info::m_syntax.begin();
        found = false;
        while (tmp != info::m_syntax.end()) {
            tmp = std::find_if(
                tmp+1,
                info::m_syntax.end(),
                [=] (Consumer cx) {return cx.getInstruction() == checker.getInstruction();});
            if (tmp == info::m_syntax.end() && !found) {
                excepts.push_back(std::make_unique<Exception>("InvalidUsageException", 0x369BF1F2, "Invalid usage of instruction '" + instr->getValue() + "' at line " + std::to_string(i+1)));
                continue;
            } else {
                if (*tmp == checker) {
                    found = true;
                    break;
                }
            }
        }
        if (!found) {
            excepts.push_back(std::make_unique<Exception>("InvalidUsageException", 0x369BF1F2, "Invalid usage of instruction '" + instr->getValue() + "' at line " + std::to_string(i+1)));
            continue;
        } */
    }
    return excepts;
}

auto Parser::getConsumers() const -> std::vector<Consumer> { return m_cons; }

auto Parser::getLines() const -> std::vector<std::vector<Token>> { return m_lines; }