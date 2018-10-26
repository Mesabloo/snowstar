#ifndef LLVM_VISITOR_HPP
#define LLVM_VISITOR_HPP

#include <iostream>

#include <SnowStarParserBaseVisitor.h>

#include <antlr4-runtime.h>

#include <llvm/IR/Module.h>
#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/IRBuilder.h>

#include <termcolor/termcolor.hpp>

class LLVMVisitor : public SnowStarParserBaseVisitor {
    using Decl = std::pair<SnowStarParser::TypeContext*, llvm::AllocaInst*>;
    using Alias = std::pair<std::string, SnowStarParser::TypeContext*>;

    llvm::Module& module;
    // llvm::IRBuilder<> current_builder;
    llvm::BasicBlock* cur_block;

    std::map<std::string, llvm::Type*> llvm_types;

    std::vector<Alias> aliases{};

public:
    LLVMVisitor(llvm::Module&);

    virtual antlrcpp::Any visitCompilationUnit(SnowStarParser::CompilationUnitContext*) override;
    virtual antlrcpp::Any visitStatement(SnowStarParser::StatementContext*) override;
    virtual antlrcpp::Any visitExpression(SnowStarParser::ExpressionContext*) override;
    virtual antlrcpp::Any visitDefine(SnowStarParser::DefineContext*) override;
    virtual antlrcpp::Any visitDeclare(SnowStarParser::DeclareContext*) override;
    virtual antlrcpp::Any visitAlias(SnowStarParser::AliasContext*) override;
};

#endif