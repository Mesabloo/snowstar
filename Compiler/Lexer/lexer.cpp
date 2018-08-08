#include <fstream>
#include <algorithm>
#include <regex>

#include "lexer.hpp"
#include <Utils/utils.hpp>
#include <info.hpp>
#include <termcolor.hpp>

Lexer::Lexer(std::string const path): isString{false}, isLComment{false}, isMLComment{false}, buffer{""}, m_path{path} {}
Lexer::~Lexer() {}

auto Lexer::tokenize() -> std::vector<Token*> {
    std::ifstream is;
    is.open(m_path, std::ifstream::ios_base::in);
    char c;
    while (is.get(c)) {
        auto const token = checkSyntax(c);
        if (token != nullptr)
            m_gen_tokens.push_back(token);
    }
    if (buffer != "") {
        auto const token = checkToken(buffer);
        if (token != nullptr)
            m_gen_tokens.push_back(token);
    }
    m_gen_tokens.push_back(new Token(Token::Type::EOL, ""));
    return m_gen_tokens;
}

auto Lexer::checkSyntax(char const c) -> Token* {
    switch (c) {
        case ' ': [[fallthrough]];
        case '\t': {
            if (!isString && !isLComment && !isMLComment) {
                if (buffer != "") {
                    auto const token = checkToken(buffer);
                    m_gen_tokens.push_back(token);
                }
                buffer = "";
            } else
                buffer += c;
            break;
        }
        case '\n': {
            if (!isMLComment) {
                if (buffer != "") {
                    auto const token = checkToken(buffer);
                    m_gen_tokens.push_back(token);
                }
                buffer = "";
                isString = false;
                isLComment = false;
                return new Token(Token::Type::EOL, "");
            } else {
                buffer += c;
            }
            break;
        }
        case ':': {
            if (!isString && !isMLComment && !isLComment) {
                if (buffer != "") {
                    Token* t = new Token(Token::Type::KEYWORD, "lbl");
                    m_gen_tokens.push_back(t);
                    auto const t1 = checkToken(buffer);
                    buffer = "";
                    return t1;
                }
                buffer = "";
                return nullptr;
            } else
                buffer += c;
            break;
        }
        case '[': [[fallthrough]];
        case ']': [[fallthrough]];
        case ',': {
            if (!isString && !isMLComment && !isLComment) {
                if (buffer != "") {
                    auto const token = checkToken(buffer);
                    m_gen_tokens.push_back(token);
                }
                buffer = "";
                return new Token(Token::Type::SEPARATOR, std::string({c}));
            } else
                buffer += c;
            break;
        }
        case '%': {
            if (!isString && !isMLComment) {
                if (buffer != "") {
                    auto const token = checkToken(buffer);
                    m_gen_tokens.push_back(token);
                }
                buffer = c;
                isLComment = true;
                return nullptr;
            } else 
                buffer += c;
            break;
        }
        default: {
            if (isString && utils::str_endswith(buffer, "\\")) {
                buffer = buffer.substr(0, buffer.size()-1);
                switch (c) {
                    case 'n': buffer += '\n'; break;
                    case 't': buffer += '\t'; break;
                    case 'r': buffer += '\r'; break;
                    case '\'': buffer += '\''; break;
                }
                return nullptr;
            }
            if (c == '\'' && !isLComment && !isMLComment) {
                if (isString) {
                    buffer += c;
                    auto const token = checkToken(buffer);
                    buffer = "";
                    isString = false;
                    return token;
                } else {
                    if (buffer != "") {
                        auto const token = checkToken(buffer);
                        m_gen_tokens.push_back(token);
                    }
                    buffer = c;
                    isString = true;
                }
                return nullptr;
            }
            buffer += c;
            if (buffer == "#*" && !isString && !isLComment && !isMLComment) {
                isMLComment = true;
            }
            if (utils::str_endswith(buffer, "*#") && isMLComment) {
                auto const token = checkToken(buffer);
                buffer = "";
                isMLComment = false;
                return token;
            }
            break;
        }
    }
    return nullptr;
}

auto Lexer::checkToken(std::string const& buf) const -> Token* {
    if (isString && std::regex_match(buf, std::regex("^(['])((?:[^\\\']|\\.)*)\\1$")))
        return new Token(Token::Type::LITERAL_STRING, buf);
    if (isLComment)
        return new Token(Token::Type::INLINE_COMMENT, buf);
    if (isMLComment)
        return new Token(Token::Type::MULTILINE_COMMENT, buf);
    if (std::find_if(info::m_keywords.begin(), info::m_keywords.end(), [=] (Token const& t) {return t == Token(Token::Type::KEYWORD, buf);}) != info::m_keywords.end())
        return new Token(Token::Type::KEYWORD, buf);
    if (std::regex_match(buf, std::regex("^((-)?[0-9])+(\\.{1}[0-9]*){1}$")))
        return new Token(Token::Type::LITERAL_NUMBER_FLOAT, buf);
    if (std::regex_match(buf, std::regex("^((-)?[0-9]+)$")))
        return new Token(Token::Type::LITERAL_NUMBER_INT, buf);
    Token* tmp = m_gen_tokens[m_gen_tokens.size()-1];
    if (tmp->getValue() == "lbl" || tmp->getValue() == "call" || tmp->getValue() == "jmp" || tmp->getValue() == "jwe" || tmp->getValue() == "jwd" || tmp->getValue() == "jwg" || tmp->getValue() == "jwl")
        return new Token(Token::Type::LABEL, buf);
    if (std::regex_match(buf, std::regex("^@@.+$")))
        return new Token(Token::Type::PREPROCESSOR, buf);
    return new Token(Token::Type::INVALID, buf);
}

auto Lexer::preprocess(std::vector<Token*> const& tokens) const -> std::vector<Token*> {
    std::vector<Token*> copy{tokens};
    std::vector<Token*> directives;
    for (auto const t : copy) {
        if (t->getType() != Token::Type::PREPROCESSOR) continue;
    }
    return tokens;
}

auto Lexer::optimize(std::vector<Token*> const& tokens) const -> std::vector<std::vector<Token*>> {
    std::vector<std::vector<Token*>> file;
    std::vector<Token*> line;
    unsigned long long line_number{1};
    for (long unsigned int j{0};j < tokens.size();++j) {
        Token* current{tokens[j]};
        if (current->getType() == Token::Type::EOL) {
            line.push_back(current);
            file.push_back(line);
            line = {};
            line_number++;
            continue;
        }
        if (current->getType() == Token::Type::MULTILINE_COMMENT) {
            line_number += utils::str_split(current->getValue(), '\n').size();
        }
        if (current->getType() == Token::Type::SEPARATOR) {
            if (current->getValue() == "[") {
                if (tokens[j+2]->getValue() == "]") {
                    std::string seg{tokens[j+1]->getValue()};
                    if (seg == "mem" || seg == "temp") {
                        std::cout << termcolor::red << "Compilation has been aborted. Error code: 0x56332e31" << '\n'
                            << "InvalidSegmentException: Invalid memory segment '" << tokens[j+1]->getValue() << "' provided without index for memory access." << termcolor::reset << std::endl;
                        return {};
                    }
                    Token* t = new Token(Token::Type::LITERAL_MEMORY, tokens[j+1]->getValue()+".0");
                    line.push_back(t);
                    j += 2;
                } else {
                    if (tokens[j+3]->getType() != Token::Type::LITERAL_NUMBER_INT) {
                        std::cout << termcolor::red << "Compilation has been aborted. Error code: 0x10594972" << '\n'
                            << "NotAnIntegerException: Unknown integer '" << tokens[j+3]->getValue() << "' provided for memory access." << termcolor::reset << std::endl;
                        return {};
                    }
                    int index{std::stoi(tokens[j+3]->getValue())};
                    std::string seg{tokens[j+1]->getValue()};
                    if ((seg == "mem" && (index > 255 || index < 0)) || (seg == "temp" && (index > 31 || index < 0))) {
                        if (index > 255) {
                            std::cout << termcolor::red << "Compilation has been aborted. Error code: 0xa265bd23" << '\n'
                                << "InvalidIndexException: Invalid integer '" << tokens[j+3]->getValue() << "' provided for memory access as memory index." << termcolor::reset << std::endl;
                            return {};
                        }
                    }
                    Token* t = new Token(Token::Type::LITERAL_MEMORY, tokens[j+1]->getValue()+"."+tokens[j+3]->getValue());
                    line.push_back(t);
                    j += 4;
                }
                continue;
            }
        }
        line.push_back(current);
    }

    return file;
}