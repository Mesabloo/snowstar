#ifndef SNOWSTARVISITOR_HPP
#define SNOWSTARVISITOR_HPP

#include <sstream>
#include <iostream>
#include <variant>
#include <map>

#include <SnowStarParserBaseVisitor.h>
#include <SnowStarLexer.h>

#include <antlr4-runtime.h>

#include <errors.hpp>
#include <termcolor/termcolor.hpp>

#include <llvm/IR/Module.h>
#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/IRBuilder.h>

class Visitor : public SnowStarParserBaseVisitor {
    using Var = std::tuple<std::string, SnowStarParser::TypeContext*, std::pair<int, int>>;
    using Decl = std::pair<SnowStarParser::TypeContext*, llvm::AllocaInst*>;
    std::vector<Var> declared{};

    struct E {
        std::vector<std::unique_ptr<Error>> errs;
        std::vector<std::unique_ptr<Warning>> warns;
    } errors;

    llvm::Module& module;
    // llvm::IRBuilder<> current_builder;
    llvm::BasicBlock* cur_block;

    std::map<std::string, llvm::Type*> llvm_types;

    antlr4::ParserRuleContext* current_stmt_context;

    std::string file_name;

public:
    Visitor(std::string const&, llvm::Module&);

    E& getErrorsAndWarnings() { return errors; }

    virtual antlrcpp::Any visitCompilationUnit(SnowStarParser::CompilationUnitContext*) override;
    virtual antlrcpp::Any visitStatement(SnowStarParser::StatementContext*) override;
    virtual antlrcpp::Any visitExpression(SnowStarParser::ExpressionContext*) override;
    virtual antlrcpp::Any visitDefine(SnowStarParser::DefineContext*) override;
    virtual antlrcpp::Any visitDeclare(SnowStarParser::DeclareContext*) override;
    virtual antlrcpp::Any visitDeclareNoID(SnowStarParser::DeclareNoIDContext*) override;
};

#endif