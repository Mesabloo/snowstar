#include <fstream>

#include "antlr4-runtime.h"
#include "SnowStarLexer.h"
#include "SnowStarParser.h"

#include "visitor.hpp"

int main(int, char** argv) {
    antlr4::ANTLRFileStream input(argv[1]);
    SnowStarLexer lexer(&input);
    antlr4::CommonTokenStream tokens(&lexer);
    
    tokens.fill();
    for (auto token : tokens.getTokens()) {
        std::cout << token->toString() << std::endl;
    }

    SnowStarParser parser(&tokens);
    antlr4::tree::ParseTree* tree = parser.program();

    std::cout << tree->toStringTree(&parser) << std::endl << std::endl;

    Visitor v;
    std::vector<Error> result = v.visit(tree);
    for (auto const& e : result) {
        std::cout << e.print() << std::endl;
    }
    if (!result.empty()) return 1;

    return 0;
}