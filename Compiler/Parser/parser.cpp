#include <algorithm>
#include <stack>
#include <array>

#include "parser.hpp"
#include "ast.hpp"
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
    std::vector<Exception> excepts;
    auto tree = AST::build(getLines());
    if (tree.first == nullptr) {
        excepts = tree.second;
        m_cons = {};
    } else {
        excepts = tree.first->checkForErrors();
        m_cons = tree.first->getConsumers();
        std::cout << termcolor::blue << '\n' << "AST:" << '\n'
            << *tree.first << termcolor::reset << std::flush;
    }
    return excepts;
}

auto Parser::getConsumers() const -> std::vector<Consumer> { return m_cons; }

auto Parser::getLines() const -> std::vector<std::vector<Token>> { return m_lines; }