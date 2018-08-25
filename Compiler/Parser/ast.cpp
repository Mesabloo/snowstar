#include "ast.hpp"

#include <algorithm>
#include <functional>
#include <sstream>

#include <info.hpp>
#include <Utils/utils.hpp>

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
        << "(target='" << m_info.target.m_storage.getMemseg().getValue() << "." << m_info.target.m_storage.getIndex().getValue() << "',"
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
    return {};
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