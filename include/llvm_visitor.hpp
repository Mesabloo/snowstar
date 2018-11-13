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