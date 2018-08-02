#include <string>

#include <Interpreter/interpreter.hpp>
#include <termcolor.hpp>
#include <values.hpp>
#include <benchmark.hpp>

int main(int argc, char const** argv) {
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

    Interpreter i;
    //BENCHMARK_MRSTATS("VM test", i.start(argv[1]), 1000000, ms);
    i.start(argv[1]);

    getchar();
}