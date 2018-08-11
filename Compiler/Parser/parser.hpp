#ifndef PARSER_HPP
#define PARSER_HPP

#include <string>
#include <vector>
#include <memory>

#include <Lexer/token.hpp>
#include "except.hpp"

class Parser {
    public:
        Parser(std::vector<std::vector<Token>> const&);
        ~Parser();

        std::vector<Exception> assertSyntax() const;
        std::vector<Exception> assertSemantics();

        std::vector<std::vector<Token>> getLines() const;
        std::vector<Consumer> getConsumers() const;

    protected:
        std::vector<std::vector<Token>> m_lines;
        std::vector<Consumer> m_cons;
};

#endif