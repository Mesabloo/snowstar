#include <string>

#include <Interpreter/interpreter.hpp>
#include <termcolor.hpp>
#include <values.hpp>
#include <benchmark.hpp>

int main(int argc, char const** argv) {
    if (argc < 2) {
        std::cerr << termcolor::red << "Program usage: " << argv[0] << " {file.cwsc} [options]" << '\n'
            << '\t' << "{file.cwsc}: the path to the file to execute" << '\n'
            << '\t' << "[options]: One of the following" << '\n'
            << '\t' << '\t' << "--benchmark <executions>: make a benchmark on a certain number of executions" << termcolor::reset << std::endl;
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
            if (arg == "--benchmark") {
                bench = true;
                bench_number = std::strtol(argv[++i], nullptr, 10);
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