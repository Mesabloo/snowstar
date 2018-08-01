#include <iostream>

#include <Lexer/lexer.hpp>
#include <Parser/parser.hpp>
#include <Converter/converter.hpp>
#include <values.hpp>
#include <termcolor.hpp>

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << termcolor::red << "Program usage: " << argv[0] << " {file.sssc}" << '\n' << '\t' << "{file.sssc}: the path to the file to compile" << std::endl;
        getchar();
        return 0;
    }

    if (argv[1]) {
        std::string arg{argv[1]};
        arg.erase(arg.begin()+arg.find_last_of("/\\"), arg.end());
        vars::PATH = arg;
    }

    if (argc > 2) {
        for (int i{2};i < argc;++i) {
            // args checking goes there
        }
    }

    Lexer l(argv[1]);
    auto tokens = l.tokenize();
    tokens = l.preprocess(tokens);
    std::cout << termcolor::grey << "Before optimizing: " << std::endl;
    for (auto const& t : tokens) {
        std::cout << "Token<"<< Token::getTypeSignification(t->getType()) << ">(" << t->getValue() << ")" << std::endl;
    }
    std::cout << std::endl << std::endl << termcolor::reset << "After optimizing: " << std::endl;
    auto const new_tokens = l.optimize(tokens);
    if (new_tokens.empty()) {
        getchar();
        return -23;
    }
    for (auto const& line : new_tokens) {
        for (auto const& t : line) {
            std::cout << "Token<"<< Token::getTypeSignification(t->getType()) << ">(" << t->getValue() << ")" << '\t';
        }
        std::cout << std::endl;
    }

    std::cout << std::endl;
    Parser p(new_tokens);

    std::cout << std::endl << std::endl << termcolor::grey << "After uncommenting: " << std::endl;
    auto opt_tokens = p.getLines();
    if (opt_tokens.empty()) {
        getchar();
        return -23;
    }
    for (auto const& line : opt_tokens) {
        for (auto const& t : line) {
            std::cout << "Token<"<< Token::getTypeSignification(t->getType()) << ">(" << t->getValue() << ")" << '\t';
        }
        std::cout << std::endl;
    }

    std::cout << std::endl;

    auto const& e = p.assertSyntax();
    for (auto const& ex : e) {
        std::cout << ex->getMessage();
    }
    if (!e.empty()) {
        getchar();
        return -3;
    } else {
        std::cout << termcolor::yellow << "No syntactical errors !" << "\033[0m" << std::endl;
    }
    auto const& e1 = p.assertSemantics();
    for (auto const& ex : e1) {
        std::cout << ex->getMessage();
    }
    if (!e1.empty()) {
        getchar();
        return -9;
    } else {
        std::cout << termcolor::yellow << "No semantical errors !" << "\033[0m" << std::endl;
    }

    std::cout << std::endl;

    Converter co;
    if (!co.start(p.getConsumers())) {
        getchar();
        return -67;
    }

    std::cout << std::endl << termcolor::green << "File written. You may now use the VM !" << "\033[0m" << std::endl;

    getchar();
    return 0;
}