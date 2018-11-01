#ifndef PPRINTER_HPP
#define PPRINTER_HPP

#include <SnowStarParserBaseVisitor.h>
#include <antlr4-runtime.h>
#include <iostream>

class PrettyPrinter : protected SnowStarParserBaseVisitor {

    std::ostream& m_os;


public:
    PrettyPrinter(antlr4::tree::ParseTree*, std::ostream&);

protected:
    virtual antlrcpp::Any visitCompilationUnit(SnowStarParser::CompilationUnitContext*) override;
    virtual antlrcpp::Any visitStatement(SnowStarParser::StatementContext*) override;
    virtual antlrcpp::Any visitExpression(SnowStarParser::ExpressionContext*) override;
    virtual antlrcpp::Any visitDefine(SnowStarParser::DefineContext*) override;
    virtual antlrcpp::Any visitAlias(SnowStarParser::AliasContext*) override;
};

#endif