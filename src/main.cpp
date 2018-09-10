#include <fstream>

#include <antlr4-runtime.h>
#include <SnowStarLexer.h>
#include <SnowStarParser.h>

#include <visitor.hpp>
#include <error_listener.hpp>

int main(int, char** argv) {
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
    antlr4::tree::ParseTree* tree = parser.program();

    if (parser.getNumberOfSyntaxErrors() > 0) {
        std::cerr << "Unexpected errors occured:\n" << parser_listener << std::endl;
        return 1;
    }

    Visitor v;
    std::vector<Error> result = v.visit(tree);
    for (auto const& e : result) {
        std::cout << e.print() << std::endl;
    }
    if (!result.empty()) return 1;

    return 0;
}