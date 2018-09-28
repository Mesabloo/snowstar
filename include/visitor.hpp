#ifndef SNOWSTARVISITOR_HPP
#define SNOWSTARVISITOR_HPP

#include <sstream>
#include <iostream>
#include <variant>

#include <SnowStarParserBaseVisitor.h>
#include <SnowStarLexer.h>

#include <antlr4-runtime.h>

#include <errors.hpp>
#include <termcolor/termcolor.hpp>

#include <llvm/IR/Module.h>
#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/IRBuilder.h>

class Visitor : public SnowStarParserBaseVisitor {
    using Var = std::pair<std::string, SnowStarParser::PrimitiveTypeContext*>;
    std::vector<Var> declared{};

    struct E {
        std::vector<std::unique_ptr<Error>> errs;
        std::vector<std::unique_ptr<Warning>> warns;
    } errors;

    antlr4::ParserRuleContext* current_stmt_context;

    llvm::Module& module;
    llvm::IRBuilder<> current_builder;

public:
    Visitor(llvm::Module&);

    E& getErrorsAndWarnings() { return errors; }

    virtual antlrcpp::Any visitStatement(SnowStarParser::StatementContext*) override;
    virtual antlrcpp::Any visitExpression(SnowStarParser::ExpressionContext*) override;
    virtual antlrcpp::Any visitDefine(SnowStarParser::DefineContext*) override;
    virtual antlrcpp::Any visitDeclare(SnowStarParser::DeclareContext*) override;
};

#endif