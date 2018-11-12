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
    // using Decl = std::pair<SnowStarParser::TypeContext*, llvm::AllocaInst*>;
    using Alias = std::pair<std::string, SnowStarParser::TheTypeContext*>;

    llvm::Module& module;
    llvm::BasicBlock* curBlock;

    std::map<std::string, llvm::Type*> llvmTypes;

    std::vector<Alias> aliases{};
    // std::vector<Decl> declared{};

    // int expr_number_tmp{0};

public:
    LLVMVisitor(llvm::Module&);

    virtual antlrcpp::Any visitCompilationUnit(SnowStarParser::CompilationUnitContext*) override;
    virtual antlrcpp::Any visitWithDeclaration(SnowStarParser::WithDeclarationContext*) override;
};

#endif