#include <string>

#include <Interpreter/interpreter.hpp>
#include <termcolor.hpp>
#include <values.hpp>
#include <benchmark.hpp>
#include <Utils/utils.hpp>

int main(int argc, char const** argv) {
    if (argc < 2) {
        std::cerr << termcolor::red << "Program usage: " << argv[0] << " {file.iwsc} [options]" << '\n'
            << '\t' << "{file.iwsc}: the path to the file to execute" << '\n'
            << '\t' << "[options]: One of the following" << '\n'
            << '\t' << '\t' << "--benchmark=<number>: make a benchmark on the specified number of executions." << '\n'
            << '\t' << '\t' << '\t' << "Alias: --b=<number>" << '\n'
            << '\t' << '\t' << "--link-lib=<path>: link a .dll/.so to Snow* when running the program to add extra features." << '\n'
            << '\t' << '\t' << '\t' << "Alias: --lib=<path> --l=<path>" << termcolor::reset << std::endl;
        getchar();
        return 0;
    }

    if (argv[1]) {
        std::string arg{argv[1]};
        arg.erase(arg.begin()+arg.find_last_of("/\\"), arg.end());
        vars::PATH = arg;
    }

    bool bench{false};
    long bench_number{100};
    if (argc > 2) {
        for (int i{2};i < argc;++i) {
            // args checking goes there
            std::string arg{argv[i]};
            std::vector<std::string> args{utils::str_split(arg, '=')};
            if (args[0] == "--benchmark" || args[0] == "--b") {
                bench = true;
                bench_number = std::strtol(args[1].c_str(), nullptr, 10);
            }
            if (args[0] == "--link-lib" || args[0] == "--lib" || args[0] == "--l") {
                // load dynamic library here.
            }
        }
    }

    Interpreter i;
    if (bench) {
        BENCHMARK_MRSTATS("VM test", i.start(argv[1]), bench_number, ms);
    } else
        i.start(argv[1]);

    getchar();
}