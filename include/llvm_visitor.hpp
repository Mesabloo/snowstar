/*
 *  Snow* Compiler, a compiler made with ANTLR and LLVM for compiling Snow* source code
 *  Copyright (C) 2018  Mesabloo
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.

 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef LLVM_VISITOR_HPP
#define LLVM_VISITOR_HPP

#include <iostream>
#include <utility>

#include <SnowStarParserBaseVisitor.h>

#include <antlr4-runtime.h>

#include <llvm/IR/Module.h>
#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/IRBuilder.h>

#include <termcolor/termcolor.hpp>

class LLVMVisitor : public SnowStarParserBaseVisitor {
    using Decl = std::tuple<SnowStarParser::TheTypeContext*, llvm::Value*, std::string>;
    using Alias = std::pair<std::string, SnowStarParser::TheTypeContext*>;
    using ExprType = std::tuple<llvm::Value*, llvm::Type*, bool>;
                                                        // ^^^^ is the type signed or not
    using Func = std::tuple<llvm::Function*, llvm::BasicBlock*>;

    llvm::Module& module;
    llvm::BasicBlock* curBlock{nullptr};

    std::map<std::string, llvm::Type*> llvmTypes;

    std::vector<Alias> aliases{};
    std::vector<Decl> declared{};
    std::vector<Func> functions{};

    int expr_number_tmp{0};

public:
    LLVMVisitor(llvm::Module&);

    virtual antlrcpp::Any visitCompilationUnit(SnowStarParser::CompilationUnitContext*) override;
        // returns antlrcpp::Any
    virtual antlrcpp::Any visitWithDeclaration(SnowStarParser::WithDeclarationContext*) override;
        // returns antlrcpp::Any
    virtual antlrcpp::Any visitVariableDeclaration(SnowStarParser::VariableDeclarationContext*) override;
        // returns antlrcpp::Any
    virtual antlrcpp::Any visitVariableInitializer(SnowStarParser::VariableInitializerContext*) override;
        // returns antlrcpp::Any
    virtual antlrcpp::Any visitExpression(SnowStarParser::ExpressionContext*) override;
        // returns ExprType
    virtual antlrcpp::Any visitFunctionDeclaration(SnowStarParser::FunctionDeclarationContext*) override;
        // returns antlrcpp::Any
    virtual antlrcpp::Any visitFunctionHeader(SnowStarParser::FunctionHeaderContext*) override;
        // returns llvm::Function*
    virtual antlrcpp::Any visitFunctionParamsTypes(SnowStarParser::FunctionParamsTypesContext*) override;
        // returns std::vector<llvm::Type*>
    virtual antlrcpp::Any visitFunctionParams(SnowStarParser::FunctionParamsContext*) override;
        // returns std::vector<std::pair<llvm::Type*, std::string>>
    virtual antlrcpp::Any visitBasicBlockDeclaration(SnowStarParser::BasicBlockDeclarationContext*) override;
        // returns llvm::Basicblock*
    virtual antlrcpp::Any visitReturnDeclaration(SnowStarParser::ReturnDeclarationContext*) override;
        // returns antlrcpp::Any
};

#endif