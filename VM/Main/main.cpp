#include <iostream>

#include "../../Common/values.hpp"
#include "../Lexer/byte_lexer.hpp"
#include "../../Common/Utils/utils.hpp"
#include "../Interpreter/interpreter.hpp"

int main(int argc, const char **argv) {
    if (argc < 2) {
        std::cerr << "\033[38;5;196m " << "Program usage: " << argv[0] << " {file.ssbc}" << '\n' << '\t' << "{file.ssbc}: the path to the file to compile" << std::endl;
        getchar();
        return 0;
    }

    if (argv[1]) {
        std::string arg{argv[1]};
        arg.erase(arg.begin()+arg.find_last_of("/\\"), arg.end());
        vars::PATH = arg;
    }

    ByteLexer bl(argv[1]);

    Interpreter i(argv[1]);
    i.start(bl);

    getchar();
}