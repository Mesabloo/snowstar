#include <iostream>

#include "../Lexer/lexer.hpp"

int main() {
    Lexer l("/home/mesabloo/Documents/snowstar/test.sssc");
    auto tokens = l.tokenize();
    for (auto const& t : tokens) {
        std::cout << "Token<"<< Token::getTypeSignification(t->getType()) << ">(" << t->getValue() << ")" << std::endl;
    }

    getchar();
}