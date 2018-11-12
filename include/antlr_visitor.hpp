#ifndef ANTLR_VISITOR_HPP
#define ANTLR_VISITOR_HPP

#include <sstream>
#include <iostream>
#include <map>
#include <variant>

#include <SnowStarParserBaseVisitor.h>

#include <antlr4-runtime.h>

class ANTLRVisitor : public SnowStarParserBaseVisitor {
/*     using Decl = SnowStarParser::TypeContext*;
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

    antlr4::ParserRuleContext* current_stmt_context; */

    using Alias = std::pair<std::string, SnowStarParser::TheTypeContext*>;
    template<typename T>
    using Scope = std::vector<T>;

    std::vector<Scope<Alias>> scopedAliases{{}};

    antlr4::ParserRuleContext* lineContext;

    std::string fileName;

    bool errored{false};

public:
    ANTLRVisitor(std::string const&);

    constexpr bool hasErrored() { return errored; }

    virtual antlrcpp::Any visitCompilationUnit(SnowStarParser::CompilationUnitContext*) override;
    virtual antlrcpp::Any visitWithDeclaration(SnowStarParser::WithDeclarationContext*) override;
};

#endif