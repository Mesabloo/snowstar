#include <iostream>

#include "../Lexer/lexer.hpp"

int main() {
    Lexer l("/home/mesabloo/Documents/snowstar/test.sssc");
    auto const tokens = l.tokenize();
    std::cout << "Before optimizing: " << std::endl;
    for (auto const& t : tokens) {
        std::cout << "Token<"<< Token::getTypeSignification(t->getType()) << ">(" << t->getValue() << ")" << std::endl;
    }
    std::cout << std::endl << std::endl << "After optimizing: " << std::endl;
    auto const new_tokens = l.optimize(tokens);
    for (auto const& line : new_tokens) {
        for (auto const& t : line) {
            std::cout << "Token<"<< Token::getTypeSignification(t->getType()) << ">(" << t->getValue() << ")" << '\t';
        }
        std::cout << std::endl;
    }

//    Parser p(l);

    getchar();
}