#include <algorithm>

#include "parser.hpp"
#include <info.hpp>
#include <Utils/utils.hpp>

Parser::Parser(std::vector<std::vector<Token*>> const& lines) {
    std::vector<std::vector<Token*>> no_comment;
    std::vector<Token*> line;
    for (auto const& l : lines) {
        for (auto const& t : l) {
            if (t->getType() != Token::Type::INLINE_COMMENT && t->getType() != Token::Type::MULTILINE_COMMENT)
                line.push_back(t);
            else {
                if (t->getType() == Token::Type::MULTILINE_COMMENT) {
                    for (size_t i{0};i < utils::str_split(t->getValue(), '\n').size()-1;++i) {
                        no_comment.push_back(line);
                        line = {new Token(Token::Type::EOL, "")};
                    }
                }
            }
            if (t->getType() == Token::Type::EOL) {
                no_comment.push_back(line);
                line = {};
            }
        }
    }
    no_comment.push_back(line);
    for (auto& l : no_comment) {
        if (l.size() > 1) {
            if (l[0]->getType() == Token::Type::EOL)
                l.erase(l.begin());
        }
    }
    m_lines = no_comment;
}
Parser::~Parser() {}

auto Parser::assertSyntax() const -> std::vector<Exception*> {
    std::vector<Exception*> excepts;
    for (unsigned long i{0};i < m_lines.size();++i) {
        if (m_lines[i].empty()) continue;
        for (auto const& t : m_lines[i]) {
            if (t->getType() == Token::Type::INVALID) {
                excepts.push_back(new Exception("UnknownTokenException", 0x5A639C54, "The token '" + t->getValue() + "' at line " + std::to_string(i+1) + " doesn't exist."));
                continue;
            }
        }
        auto const& line = m_lines[i];
        Token* instr = line[0];
        if (instr->getType() == Token::Type::EOL) continue;
        if (instr->getType() != Token::Type::KEYWORD && instr->getValue() != "mem" && instr->getValue() != "temp" && instr->getValue() != "param" && instr->getValue() != "nost") {
            excepts.push_back(new Exception("InvalidTokenException", 0x36DE95C4, "The line " + std::to_string(i+1) + " is not starting with an instruction."));
        }
    }
    return excepts;
}

auto Parser::assertSemantics() -> std::vector<Exception*> {
    std::vector<Exception*> excepts;
    for (unsigned long i{0};i < m_lines.size();++i) {
        if (m_lines[i].empty()) continue;
        auto const& line = m_lines[i];
        Token* instr = line[0];
        if (instr->getType() == Token::Type::EOL) continue;
        std::vector<Consumer>::iterator c{info::m_syntax.begin()};
        std::vector<std::vector<Consumer>::iterator> holder;
        bool found{false};
        while (c != info::m_syntax.end()) {
            c = std::find_if(
                c+1,
                info::m_syntax.end(),
                [=] (Consumer const& c1) {
                    return c1.getInstruction() == *instr;
                }
            );
            if (c == info::m_syntax.end() && !found)
                excepts.push_back(new Exception("InstructionNotFoundException", 0x23D9645B, "Unknown instruction '" + instr->getValue() + "' at line " + std::to_string(i+1)));
            else {
                uint8_t const argc = c->getArgs().size();
                std::vector<Token> args;
                uint8_t offset{0};
                if (c->getStorage().getMemseg().getValue() == "nost" && c->getStorage().getIndex().getValue() == "-1")
                    // no storage specifier. offset = 1 (args at offset+x) (instr args)
                    offset = 1;
                else
                    // storage specifier. offset = 2 (args at offset+x) (instr [ memseg , index ] args)
                    offset = 2;
                for (uint8_t i{0};i < argc*2;i += 2)
                    args.push_back(*line[offset+i]);

                Consumer::Store st;
                if (offset == 2) {
                    Token* t = line[1];
                    if (t->getType() != Token::Type::LITERAL_MEMORY) {
                        std::stringstream ss;
                        ss << "Unexpected token '" << t << "' at line " << i+1;
                        excepts.push_back(new Exception("InvalidTokenException", 0xA67123D1, "Unexpected token '" + t->getValue() + "' at line " + std::to_string(i+1)));
                        continue;
                    }
                    std::string const memseg = utils::str_split(t->getValue(), '.')[0],
                                      index = utils::str_split(t->getValue(), '.')[1];
                    if (std::find(info::m_keywords.begin(), info::m_keywords.end(), Token(Token::Type::KEYWORD, memseg)) == info::m_keywords.end()) {
                        excepts.push_back(new Exception("InvalidTokenException", 0x36BE6A5D, "Unknown memory segment '" + memseg + "' at line " + std::to_string(i+1)));
                        continue;
                    }
                    st = Consumer::Store(Token(Token::Type::KEYWORD, memseg), Token(Token::Type::LITERAL_NUMBER_INT, index));
                }

                Consumer* cons = new Consumer(*instr, st, args);

                if (*cons == *c) {
                    found = true;
                    m_cons.push_back(cons);
                    break;
                } else {
                    holder.push_back(c);
                }
            }
        }
        if (!found) {
            for (auto const& h : holder) {
                excepts.push_back(new Exception("InvalidUsageException", 0x369BF1F2, "Invalid usage of instruction '" + instr->getValue() + "': " + h->toString() + " at line " + std::to_string(i+1)));
            }
            continue;
        }
    }
    return excepts;
}

auto Parser::getConsumers() const -> std::vector<Consumer*> { return m_cons; }

auto Parser::getLines() const -> std::vector<std::vector<Token*>> { return m_lines; }