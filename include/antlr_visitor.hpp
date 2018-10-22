#ifndef ANTLR_VISITOR_HPP
#define ANTLR_VISITOR_HPP

#include <sstream>
#include <iostream>
#include <map>

#include <SnowStarParserBaseVisitor.h>

#include <antlr4-runtime.h>

#include <errors.hpp>

class ANTLRVisitor : public SnowStarParserBaseVisitor {
    using Var = std::tuple<std::string, SnowStarParser::TypeContext*, std::pair<int, int>>;
    using Decl = SnowStarParser::TypeContext*;
    std::vector<Var> declared{};

    struct E {
        std::vector<std::unique_ptr<Error>> errs;
        std::vector<std::unique_ptr<Warning>> warns;
    } errors;

    antlr4::ParserRuleContext* current_stmt_context;

    std::string file_name;

public:
    ANTLRVisitor(std::string const&);

    E& getErrorsAndWarnings() { return errors; }

    virtual antlrcpp::Any visitCompilationUnit(SnowStarParser::CompilationUnitContext*) override;
    virtual antlrcpp::Any visitStatement(SnowStarParser::StatementContext*) override;
    virtual antlrcpp::Any visitExpression(SnowStarParser::ExpressionContext*) override;
    virtual antlrcpp::Any visitDefine(SnowStarParser::DefineContext*) override;
    virtual antlrcpp::Any visitDeclare(SnowStarParser::DeclareContext*) override;
    virtual antlrcpp::Any visitDeclareNoID(SnowStarParser::DeclareNoIDContext*) override;
};

#endif