#include <string>
#include <iostream>

#include <lexer.hpp>
//#include <interpreter.hpp>

int main() {
    std::string input;

    
    //MathsInterpreter intr;

    while (input != "exit") {
        std::cin >> input;
        if (input == "exit") break;
        MathsLexer lex;
        auto tokens = lex.tokenize(input);
        for (auto t : tokens) {
            if (t == nullptr) continue;
            std::cout << '"' << t->toString() << "\" ";
        }
        std::cout << std::endl;
        auto node = lex.parse(tokens);
        /*for (auto t : tokens) {
            if (t == nullptr) continue;
            std::cout << '"' << t->toString() << "\" ";
        }*/
        while (!node.empty()) {
            auto n = node.top();
            std::cout << *n << std::endl;
            node.pop();
        }
        //intr.execute(e);
    }
    return 0;
}