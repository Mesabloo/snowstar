#include <fstream>
#include <vector>
#include <string>

#include <antlr4-runtime.h>
#include <SnowStarLexer.h>
#include <SnowStarParser.h>

#include <visitor.hpp>
#include <error_listener.hpp>
#include <termcolor/termcolor.hpp>

#include <llvm/IR/Module.h>

namespace utils {
    std::vector<std::string> str_split(std::string const& str, char const separator) {
        std::vector<std::string> vect;
        std::istringstream f{str};
        std::string s;
        while (getline(f, s, separator)) {
            vect.push_back(s);
        }
        return vect;
    }
};

int main(int argc, char** argv) {

    if (argc > 2) {
        for (int i{2};i < argc;++i) {
            std::string arg{argv[i]};
            std::vector<std::string> args{utils::str_split(arg, '=')};
            // args checking here
        }
    }

    antlr4::ANTLRFileStream input(argv[1]);
    SnowStarLexer lexer(&input);
    ErrorListener lexer_listener;
    lexer.removeErrorListeners();
    lexer.addErrorListener(&lexer_listener);
    antlr4::CommonTokenStream tokens(&lexer);
    
    tokens.fill();

    if (lexer.getNumberOfSyntaxErrors() > 0) {
        std::cerr << "Unexpected errors occured:\n" << lexer_listener << std::endl;
        return 1;
    }

    SnowStarParser parser(&tokens);
    ErrorListener parser_listener;
    parser.removeErrorListeners();
    parser.addErrorListener(&parser_listener);
    antlr4::tree::ParseTree* tree = parser.statement();

    if (parser.getNumberOfSyntaxErrors() > 0) {
        std::cerr << "Unexpected errors occured:\n" << parser_listener << std::endl;
        return 1;
    }

    std::clog << tree->toStringTree(&parser) << std::endl;

    std::string arg{argv[1]};
    arg.erase(arg.begin()+arg.find_last_of("/\\"), arg.end());
    arg.erase(arg.begin()+arg.find_last_of("."), arg.end());
    static llvm::LLVMContext ctx{};
    llvm::Module mod = llvm::Module("test.ll", ctx);

    Visitor v{mod};
    std::pair<std::vector<Error>, std::vector<Warning>> const& result = v.visit(tree);
    for (auto const& e : result.first) {
        std::cerr << e.print() << std::endl;
    }
    if (!result.first.empty()) return 1;
    for (auto const& w : result.second) {
        std::cerr << w.print() << std::endl;
    }

    //mod.dump();

    return 0;
}