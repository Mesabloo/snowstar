#ifndef LEXER_HPP
#define LEXER_HPP

#include <vector>
#include <string>
#include <memory>

#include "token.hpp"

class Lexer {
    public:
        Lexer(std::string const);
        ~Lexer();

        auto tokenize() -> std::vector<std::shared_ptr<Token>>;
        auto preprocess(std::vector<std::shared_ptr<Token>> const&) const -> std::vector<std::shared_ptr<Token>>;
        auto optimize(std::vector<std::shared_ptr<Token>> const&) const -> std::vector<std::vector<std::shared_ptr<Token>>>;

    private:
        bool isString, isLComment, isMLComment;
        std::string buffer;
        std::shared_ptr<Token> checkToken(std::string const&) const;
        std::shared_ptr<Token> checkSyntax(char const);

    protected:
        std::string m_path;
        std::vector<std::shared_ptr<Token>> m_gen_tokens;
};

#endif