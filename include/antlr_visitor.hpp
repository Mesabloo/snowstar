#ifndef ANTLR_VISITOR_HPP
#define ANTLR_VISITOR_HPP

#include <sstream>
#include <iostream>
#include <map>
#include <variant>

#include <SnowStarParserBaseVisitor.h>

#include <antlr4-runtime.h>

#include <errors.hpp>

class ANTLRVisitor : public SnowStarParserBaseVisitor {
    using Decl = SnowStarParser::TypeContext*;
    using Var = std::tuple<std::string, Decl, bool, std::pair<int, int>>;
    using Alias = std::pair<std::string, Decl>;
    enum class ExprType {
        VOID,
        INT8,
        INT16,
        INT32,
        INT64,
        REAL16,
        REAL32,
        REAL64,
        CHAR,
        BOOL
    };
    std::vector<Var> declared{};
    std::vector<Alias> aliases{};

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
    virtual antlrcpp::Any visitAlias(SnowStarParser::AliasContext*) override;
};

#endif