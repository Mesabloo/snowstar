#ifndef LEXER_HPP
#define LEXER_HPP

#include <vector>
#include <string>

#include "token.hpp"

class Lexer {
    public:
        Lexer(std::string const);
        ~Lexer();

        auto tokenize() -> std::vector<Token*>;

    private:
        bool isString, isLComment, isMLComment;
        std::string buffer;
        Token* checkToken(std::string const&) const;
        Token* checkSyntax(char const);

    protected:
        std::string m_path;
        std::vector<Token*> m_gen_tokens;
};

#endif