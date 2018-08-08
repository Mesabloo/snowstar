#ifndef PARSER_HPP
#define PARSER_HPP

#include <string>
#include <vector>
#include <memory>

#include <Lexer/token.hpp>
#include "except.hpp"

class Parser {
    public:
        Parser(std::vector<std::vector<std::shared_ptr<Token>>> const&);
        ~Parser();

        std::vector<std::unique_ptr<Exception>> assertSyntax() const;
        std::vector<std::unique_ptr<Exception>> assertSemantics();

        std::vector<std::vector<std::shared_ptr<Token>>> getLines() const;
        std::vector<std::shared_ptr<Consumer>> getConsumers() const;

    protected:
        std::vector<std::vector<std::shared_ptr<Token>>> m_lines;
        std::vector<std::shared_ptr<Consumer>> m_cons;
};

#endif