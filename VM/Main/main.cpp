#include <iostream>
#include <thread>

#include <values.hpp>
#include <Lexer/byte_lexer.hpp>
#include <Utils/utils.hpp>
#include <Interpreter/interpreter.hpp>
#include <termcolor.hpp>

int main(int argc, const char **argv) {
    if (argc < 2) {
        std::cerr << termcolor::red << "Program usage: " << argv[0] << " {file.ssbc} [options]" << '\n'
            << '\t' << "{file.ssbc}: the path to the file to compile" << '\n'
            << '\t' << "[options]:" << '\n'
            << '\t' << '\t' << "--debug: starts the debugger" << std::endl;
        getchar();
        return 0;
    }

    if (argv[1]) {
        std::string arg{argv[1]};
        arg.erase(arg.begin()+arg.find_last_of("/\\"), arg.end());
        vars::PATH = arg;
    }

    if (argc > 2) {
        for (int i(2);i < argc;++i) {
            std::string arg = argv[i];
            if (arg == "--debug")
                vars::DEBUG = true;
        //    if (arg == "--exit-on-end")
        //        vars::EXIT_ON_END = true;
        }
    }

    ByteLexer bl(argv[1]);
    Interpreter i(argv[1]);
    i.start(bl);

    getchar();
}