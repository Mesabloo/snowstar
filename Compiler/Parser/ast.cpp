#include "ast.hpp"

#include <algorithm>
#include <functional>
#include <sstream>
#include <unordered_map>
#include <stack>

#include <info.hpp>
#include <Utils/utils.hpp>
#include <termcolor.hpp>

AST::Expression::Expression(): m_expr{}, m_storage{} {}
AST::Expression::Expression(Token const& t): m_expr{t}, m_storage{} {}
AST::Expression::Expression(Consumer::Store const& s): m_expr{}, m_storage{s} {}
bool operator==(AST::Expression a, AST::Expression b) {
    return a.m_expr == b.m_expr && a.m_storage == b.m_storage;
}

AST::Node::Info::Info(AST::Expression const& instr, AST::Expression const& store, std::vector<AST::Expression> const& args): instruction{instr}, target{store}, arguments{args} {}
AST::Node::Node(): m_info{AST::Node::Info{AST::Expression(), AST::Expression(), {}}}, m_children{} {}
bool AST::Node::hasChildren() const { return m_children.size() > 0; }
AST::Node::Node(AST::Node::Info const& info, std::vector<AST::Node> const& children): m_info{info}, m_children{children} {}
std::ostream& operator<<(std::ostream& os, AST::Node& node) {
    return os << node.toString(0) << std::endl;
}
bool operator==(AST::Node a, AST::Node b) {
    return a.m_children == b.m_children
        && a.m_info.instruction == b.m_info.instruction
        && a.m_info.target == b.m_info.target
        && a.m_info.arguments == b.m_info.arguments;
}
std::string AST::Node::toString(unsigned int level, bool const isLast) {
    std::stringstream ss;
    for (unsigned int l=level;l > 0;--l) {
        ss << "│  ";
    }
    if (isLast)
        ss << "└─";
    else
        ss << "├─";
    ss << " " << m_info.instruction.m_expr.getValue() 
        << "(target='" << m_info.target.m_storage.getMemseg().getValue() << "." << m_info.target.m_storage.getIndex().getValue() << "', "
        << "args=[";
    for (unsigned i{0}; i < m_info.arguments.size();++i) {
        auto const& e = m_info.arguments[i];
        ss << Token::getTypeSignification(e.m_expr.getType()) << "<" << e.m_expr.getValue() << ">";
        if (i < m_info.arguments.size()-1)
            ss << ", ";
    }
    ss << "])" << std::endl;
    for (auto& n : m_children) {
        ss << n.toString(level+1, n == *(m_children.end()-1));
    }
    std::string stringified{ss.str()};
    return stringified;
}

std::pair<std::unique_ptr<AST>, std::vector<Exception>> AST::build(std::vector<std::vector<Token>> const& lines) {
    AST::Node n;
    AST::Node* parentOf{&n};
    AST::Node* childOf{&n};
    std::unique_ptr<AST> ast{std::make_unique<AST>(n)};
    for (unsigned int i{0};i < lines.size();++i) {
        auto const& line{lines[i]};
        if (line.empty()) continue;
        if (line[0].getType() == Token::Type::EOL) continue;
        if (line[0].getValue() == "lbl") {
            parentOf->m_children.push_back(AST::Node(AST::Node::Info(AST::Expression{line[0]}, AST::Expression{}, {AST::Expression{line[1]}}), {}));
            ast->m_cons.push_back(Consumer{line[0], Consumer::Store(), {line[1]}});
            childOf = parentOf;
            parentOf = &*parentOf->m_children.rbegin();
        } else {
            auto c{info::m_syntax.begin()};
            bool exists{false};
            while (c != info::m_syntax.end()) {
                c = std::find_if(c+1, info::m_syntax.end(), [line] (Consumer const& c1) { return c1.getInstruction() == line[0]; });
                if (c == info::m_syntax.end() && !exists) {
                    return std::make_pair<std::unique_ptr<AST>, std::vector<Exception>>(nullptr, {Exception("MissingInstructionException", 0x2574458A, "The instruction '" + line[0].getValue() + "' at line " + std::to_string(i+1) + " either doesn't exist or the compiler you use is not updated to the latest version.")});
                } else {
                    if (exists) break;
                    uint8_t offset{0}, argc{0}, to_deduce{0};
                    for (Token const& t : line) {
                        if (t.getType() == Token::Type::EOL) break;
                        argc++;
                        if (t.getType() == Token::Type::SEPARATOR)
                            to_deduce++;
                    }
                    argc -= to_deduce;
                    if (c->getStorage().getMemseg().getValue() == "nost")
                        offset = 1;
                    else
                        offset = 2;
                    argc -= offset;
                    std::vector<Token> args;
                    for (auto i{0};i < argc*2; i += 2)
                        args.push_back(line[offset+i]);

                    Consumer::Store storage;
                    if (offset == 2) {
                        Token const& store{line[1]};
                        if (store.getType() != Token::Type::LITERAL_MEMORY)
                            return std::make_pair<std::unique_ptr<AST>, std::vector<Exception>>(nullptr, {Exception("InvalidTokenException", 0xA67123D1, "Unexpected token '" + store.getValue() + "' at line " + std::to_string(i+1))});
                        std::string const seg{utils::str_split(store.getValue(), '.')[0]},
                                          index{utils::str_split(store.getValue(), '.')[1]};
                        if (std::find(info::m_keywords.begin(), info::m_keywords.end(), Token(Token::Type::KEYWORD, seg)) == info::m_keywords.end()) {
                            return std::make_pair<std::unique_ptr<AST>, std::vector<Exception>>(nullptr, {Exception("InvalidTokenException", 0x36BE6A5D, "Unknown memory segment '" + seg + "' at line " + std::to_string(i+1))});
                        }
                        storage = Consumer::Store(Token(Token::Type::KEYWORD, seg), Token(Token::Type::LITERAL_NUMBER_INT, index));
                    }
                    Consumer const instr{line[0], storage, args};

                    if (instr == *c) {
                        exists = true;
                        ast->m_cons.push_back(instr);
                        Consumer::Store const& cons_store{instr.getStorage()},
                                c_store{c->getStorage()};
                        std::string cons_seg{cons_store.getMemseg().getValue()},
                                    c_seg{c_store.getMemseg().getValue()};
                        if (c_seg == "memory") {
                            if (cons_seg != "mem" && cons_seg != "temp") {
                                return std::make_pair<std::unique_ptr<AST>, std::vector<Exception>>(nullptr, {Exception("InvalidMemorySegmentException", 0x25AD6F3E, "Illegal use of memory segment '" + cons_seg + "' for instruction " + c->getInstruction().getValue() + " at line " + std::to_string(i+1))});
                            }
                        } else if (c_seg == "stack") {
                            if (cons_seg != "param") {
                                return std::make_pair<std::unique_ptr<AST>, std::vector<Exception>>(nullptr, {Exception("InvalidMemorySegmentException", 0x25AD6F3E, "Illegal use of memory segment '" + cons_seg + "' for instruction " + c->getInstruction().getValue() + " at line " + std::to_string(i+1))});
                            }
                        }
                        break;
                    }
                }
            }
            if (!exists) {
                return std::make_pair<std::unique_ptr<AST>, std::vector<Exception>>(nullptr, {Exception("InvalidUsageException", 0x369BF1F2, "Invalid usage of instruction '" + line[0].getValue() + "' at line " + std::to_string(i+1))});
            }
            auto& c1 = ast->m_cons[ast->m_cons.size()-1];
            std::vector<AST::Expression> exprs;
            for (auto const& arg : c1.getArgs())
                exprs.push_back(AST::Expression{arg});
            parentOf->m_children.push_back(Node{AST::Node::Info{AST::Expression{c1.getInstruction()}, AST::Expression{c1.getStorage()}, exprs}, {}});
            if (line[0].getValue() == "int" || line[0].getValue() == "back" || line[0].getValue() == "jmp") {
                parentOf = childOf;
            }
        }
    }
    ast->setNode(n);
    return std::make_pair<std::unique_ptr<AST>, std::vector<Exception>>(std::make_unique<AST>(*ast), {});
}

std::vector<Exception> AST::checkForErrors() const {
    std::vector<Exception> excepts;
    auto it = std::find_if(m_cons.begin(), m_cons.end(), [] (Consumer c) { return c.getInstruction().getValue() == "lbl" && (c.getArgs().size() > 0?c.getArgs()[0].getValue() == "main":false); });
    if (it == m_cons.end()) it = m_cons.begin();
    std::map<std::string, Token::Type> mem_emul;
    std::stack<std::map<std::string, Token::Type>> temp_emul;
    temp_emul.push({});
    std::stack<std::pair<decltype(it), Consumer::Store>> call_stack_emul;
    std::stack<Token::Type> param_emul;
    for (int line{0};it != m_cons.end();++it, ++line) {
        Consumer c = *it;
        std::string instr = c.getInstruction().getValue(),
                    memseg = c.getStorage().getMemseg().getValue(),
                    memindex = c.getStorage().getIndex().getValue();
        for (auto& arg : c.getArgs()) {
            if (arg.getType() != Token::Type::LITERAL_MEMORY) continue;
            std::string seg{utils::str_split(arg.getValue(), '.')[0]},
                        index{utils::str_split(arg.getValue(), '.')[1]};
            std::cout << termcolor::green << "→ Replacing " << Token::getTypeSignification(arg.getType()) << "@" << arg.getValue() << " with ";
            if (seg == "mem") {
                if (mem_emul.find(index) == mem_emul.end())
                    return {Exception("UninitializedIndexException", 0x365AD24F, "Tried to use an uninitialized index inside the memory segment at line " + std::to_string(line+1) + ".")};
                arg = Token(mem_emul[index], arg.getValue());
            } else if (seg == "temp") {
                if (temp_emul.top().find(index) == temp_emul.top().end())
                    return {Exception("UninitializedIndexException", 0x365AD24F, "Tried to use an uninitialized index inside the temporary segment at line " + std::to_string(line+1) + ".")};
                arg = Token(temp_emul.top()[index], arg.getValue());
            } else if (seg == "param") {
                if (param_emul.empty())
                    return {Exception("UninitializedIndexException", 0x365AD24F, "Tried to use an uninitialized index inside the temporary segment at line " + std::to_string(line+1) + ".")};
                arg = Token(param_emul.top(), arg.getValue());
            }
            std::cout << Token::getTypeSignification(arg.getType()) << "@" << arg.getValue() << " on instruction '" << c.getInstruction().getValue() << "'." << termcolor::reset << std::endl;
        }

        /*std::clog << c.getInstruction().getValue() << "[" << c.getStorage().getMemseg().getValue() << "." << c.getStorage().getIndex().getValue() << "] ";
        for (auto& arg : c.getArgs()) {
            std::clog << Token::getTypeSignification(arg.getType()) << ", ";
        }
        std::clog << std::endl;*/

        if (std::find_if(info::m_syntax.begin(), info::m_syntax.end(), [&c] (Consumer& c1) { return c == c1 && c.getInstruction().getValue() == c1.getInstruction().getValue(); }) == info::m_syntax.end()) {
            return {Exception("InvalidUsageException", 0x2586ABD6, "Invalid use of instruction '" + c.getInstruction().getValue() + "' at line " + std::to_string(line+1) + ".")};
        }

        if (instr == "call") {
            call_stack_emul.push({it, c.getStorage()});
            auto tmp = std::find_if(m_cons.begin(), m_cons.end(), [&c] (Consumer c1) { return c1.getInstruction().getValue() == "lbl" && (c1.getArgs().size() > 0?c1.getArgs()[0].getValue() == (c.getArgs().size() > 0?c.getArgs()[0].getValue():""):false); });
            if (tmp == m_cons.end()) {
                return {Exception{"UnknownLabelException", 0x2AC9F3D1, "Trying to jump to an inexistant label using $call at line " + std::to_string(line+1) + "."}};
            }
            temp_emul.push({});
            it = tmp;
        } else if (instr == "jmp"/* || instr == "jwe" || instr == "jwd" || instr == "jwl" || instr == "jwg"*/) {
            auto tmp = std::find_if(m_cons.begin(), m_cons.end(), [&c] (Consumer c1) { return c1.getInstruction().getValue() == "lbl" && (c1.getArgs().size() > 0?c1.getArgs()[0].getValue() == (c.getArgs().size() > 0?c.getArgs()[0].getValue():""):false); });
            if (tmp == m_cons.end()) {
                return {Exception{"UnknownLabelException", 0x2AC9F3D1, "Trying to jump to an inexistant label using $call at line " + std::to_string(line+1) + "."}};
            }
            it = tmp;
        } else if (instr == "back") {
            if (call_stack_emul.empty())
                return {Exception("InvalidBackCallException", 0x22DFEDD4, "Trying to return from an inexistant call at line " + std::to_string(line+1) + ".")};
            auto tmp = call_stack_emul.top();
            call_stack_emul.pop();
            std::string seg{tmp.second.getMemseg().getValue()},
                        index{tmp.second.getIndex().getValue()};
            temp_emul.pop();
            if (seg == "mem")
                mem_emul[index] = c.getArgs()[0].getType();
            else if (seg == "temp")
                temp_emul.top()[index] = c.getArgs()[0].getType();
            it = tmp.first;
        } else if (instr == "int") break;

        if (instr == "store" || instr == "push") {
            if (memseg == "mem") {
                mem_emul[memindex] = c.getArgs()[0].getType();
            } else if (memseg == "temp") {
                temp_emul.top()[memindex] = c.getArgs()[0].getType();
            } else if (memseg == "param") {
                param_emul.push(c.getArgs()[0].getType());
            }
        } else if (instr == "free" || instr == "pop") {
            if (memseg == "mem") {
                mem_emul.erase(memindex);
            } else if (memseg == "temp") {
                temp_emul.top().erase(memindex);
            } else if (memseg == "param") {
                param_emul.pop();
            }
        }
        
        if (instr == "add" || instr == "sub" || instr == "div" || instr == "mul" || instr == "mod" || instr == "rand"
            || instr == "stoi" || instr == "ftoi"
            || instr == "and" || instr == "or" || instr == "xor" || instr == "not") {
            if (memseg == "mem") {
                mem_emul[memindex] = Token::Type::LITERAL_NUMBER_INT;
            } else if (memseg == "temp") {
                temp_emul.top()[memindex] = Token::Type::LITERAL_NUMBER_INT;
            } else if (memseg == "param") {
                param_emul.push(Token::Type::LITERAL_NUMBER_INT);
            }
        } else if (instr == "addf" || instr == "subf" || instr == "mulf" || instr == "divf"
            || instr == "stof" || instr == "itof") {
            if (memseg == "mem") {
                mem_emul[memindex] = Token::Type::LITERAL_NUMBER_FLOAT;
            } else if (memseg == "temp") {
                temp_emul.top()[memindex] = Token::Type::LITERAL_NUMBER_FLOAT;
            } else if (memseg == "param") {
                param_emul.push(Token::Type::LITERAL_NUMBER_FLOAT);
            }
        } else if (instr == "itos" || instr == "ftos") {
            if (memseg == "mem") {
                mem_emul[memindex] = Token::Type::LITERAL_STRING;
            } else if (memseg == "temp") {
                temp_emul.top()[memindex] = Token::Type::LITERAL_STRING;
            } else if (memseg == "param") {
                param_emul.push(Token::Type::LITERAL_STRING);
            }
        }
    }
    return excepts;
}

void AST::setNode(AST::Node const& n) { m_main_node = n; }
std::vector<Consumer>& AST::getConsumers() { return std::ref(m_cons); }
std::ostream& operator<<(std::ostream& os, AST& tree) {
    for (auto& n : tree.m_main_node.m_children) {
        std::string node_tree{n.toString(0, n == *(tree.m_main_node.m_children.end()-1))};
        node_tree.substr(0, node_tree.size()-1);
        os << node_tree;
    }
    os << std::endl;
    return os; 
}

AST::AST(AST::Node const& n): m_main_node{n} {}