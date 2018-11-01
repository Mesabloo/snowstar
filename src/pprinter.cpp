#include <pprinter.hpp>

#include <termcolor/termcolor.hpp>

PrettyPrinter::PrettyPrinter(antlr4::tree::ParseTree* tree, std::ostream& out) : m_os{out} {
    #if !defined(_WIN32) && !defined(_WIN64)
    m_os << termcolor::colorize;
    #endif
    this->visit(tree);
}

antlrcpp::Any PrettyPrinter::visitCompilationUnit(SnowStarParser::CompilationUnitContext* ctx) {
    m_os << "╮" << '\n';
    visitChildren(ctx);
    m_os << "╯" << std::endl;
    return 0;
}

antlrcpp::Any PrettyPrinter::visitStatement(SnowStarParser::StatementContext* ctx) {
    m_os << "├─┬╼ Statement" << '\n';
    visitChildren(ctx);
    m_os << "├─╯" << '\n';
    return 0;
}
// TODO: print definition
antlrcpp::Any PrettyPrinter::visitDefine(SnowStarParser::DefineContext* ctx) {
    m_os << "│ ├─┬╼ Definition @ line " << ctx->getStart()->getLine() << '\n'
         << "│ │ ├╼ Type=" << ctx->declare()->type()->getText() << '\n'
         << "│ │ ├╼ Id=" << ctx->declare()->IDENTIFIER()->getText() << '\n'
         << "│ │ ├╼ Value=" << ctx->expression()->getText() << '\n'
         << "│ ├─╯\n";
    return 1;
}
// TODO: print alias
antlrcpp::Any PrettyPrinter::visitAlias(SnowStarParser::AliasContext* ctx) {
    m_os << "│ ├─┬╼ Type Alias @ line " << ctx->getStart()->getLine() << '\n'
         << "│ │ ├╼ Type=" << ctx->type()->getText() << '\n'
         << "│ │ ├╼ Id=" << ctx->IDENTIFIER()->getText() << '\n'
         << "│ ├─╯\n";
    return 1;
}
// TODO: print expression
antlrcpp::Any PrettyPrinter::visitExpression(SnowStarParser::ExpressionContext* ctx) {
    return 1;
}