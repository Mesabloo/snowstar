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

#include <llvm_visitor.hpp>

#if defined(_WIN32) || defined (_WIN64)
#   undef VOID
#endif

#include <termcolor/termcolor.hpp>

#include <llvm/Support/raw_ostream.h>

LLVMVisitor::LLVMVisitor(llvm::Module& mod) : module{mod} {
    llvmTypes = {
        {"bool", llvm::Type::getInt1Ty(module.getContext())},
        {"chr", llvm::Type::getInt8Ty(module.getContext())},
        {"i8", llvm::Type::getInt8Ty(module.getContext())},
        {"ui8", llvm::Type::getInt8Ty(module.getContext())},
        {"i16", llvm::Type::getInt16Ty(module.getContext())},
        {"ui16", llvm::Type::getInt16Ty(module.getContext())},
        {"i32", llvm::Type::getInt32Ty(module.getContext())},
        {"ui32", llvm::Type::getInt32Ty(module.getContext())},
        {"i64", llvm::Type::getInt64Ty(module.getContext())},
        {"ui64", llvm::Type::getInt64Ty(module.getContext())},
        {"f32", llvm::Type::getFloatTy(module.getContext())},
        {"f64", llvm::Type::getDoubleTy(module.getContext())},
        {"str", llvm::ArrayType::get(llvm::Type::getInt8Ty(module.getContext()), 0)},
        {"void", llvm::Type::getVoidTy(module.getContext())}
    };
}

antlrcpp::Any LLVMVisitor::visitCompilationUnit(SnowStarParser::CompilationUnitContext* ctx) {
    // llvm::FunctionType* type = llvm::FunctionType::get(llvm::IntegerType::get(module.getContext(), 32), false);
    // llvm::Function* main = llvm::Function::Create(type, llvm::Function::ExternalLinkage, "main", &module);
    // cur_block = llvm::BasicBlock::Create(module.getContext(), "entry", main, 0);

    curBlock = llvm::BasicBlock::Create(module.getContext());

    llvm::FunctionType* type = llvm::FunctionType::get(llvmTypes["void"], false);
    llvm::Function* global_init = llvm::Function::Create(type, llvm::Function::InternalLinkage, "__ss_GLOBAL_var_init", &module);
    global_init->setSection(".text.startup");
    llvm::BasicBlock* global_block = llvm::BasicBlock::Create(module.getContext(), "entry", global_init);
    functions.emplace_back(global_init, global_block);

    visitChildren(ctx);

    llvm::ReturnInst::Create(module.getContext(), nullptr, std::get<1>(functions[0]));

    // llvm::ConstantInt* i32_0 = llvm::ConstantInt::get(module.getContext(), llvm::APInt(32, 0));
    // llvm::ReturnInst::Create(module.getContext(), i32_0, cur_block);
    return 0;
}

antlrcpp::Any LLVMVisitor::visitWithDeclaration(SnowStarParser::WithDeclarationContext* ctx) {
    auto& type = llvmTypes[ctx->theType()->getText()];

    llvmTypes[ctx->withName()->IDENTIFIER()->getText()] = type;

    if (ctx->theType()->IDENTIFIER()) {
        auto alias_it = std::find_if(aliases.begin(), aliases.end(), [&ctx] (Alias const& a) { return a.first == ctx->theType()->IDENTIFIER()->getText(); });
        while (alias_it != aliases.end() && alias_it->second->IDENTIFIER()) {
            alias_it = std::find_if(aliases.begin(), aliases.end(), [&alias_it] (Alias const& a) { return a.first == alias_it->second->getText(); });
        }
        
        aliases.emplace_back(ctx->withName()->IDENTIFIER()->getText(), alias_it->second);
    } else
        aliases.emplace_back(ctx->withName()->IDENTIFIER()->getText(), ctx->theType());

    return type;
}

antlrcpp::Any LLVMVisitor::visitVariableDeclaration(SnowStarParser::VariableDeclarationContext* ctx) {
    llvm::Type* type = llvmTypes[ctx->theType()->getText()];
    ExprType val;
    llvm::Value* value = nullptr;
    if (auto init = ctx->variableInitializer()) {
        val = visitVariableInitializer(init).as<ExprType>();
        value = std::get<0>(val);
    }
    if (!curBlock->getParent()) {
        // global variable

        #ifndef NDEBUG
            value->dump();
        #endif

        llvm::GlobalVariable* gb = new llvm::GlobalVariable(module, std::get<1>(val), false, llvm::GlobalValue::LinkageTypes::InternalLinkage, llvm::Constant::getNullValue(std::get<1>(val)), ctx->variableName()->IDENTIFIER()->getText());
        new llvm::StoreInst(value, gb, std::get<1>(functions[0]));
        value = gb;
    } else {
        // local variable
        llvm::AllocaInst* inst = new llvm::AllocaInst(std::get<1>(val), 0, ctx->variableName()->IDENTIFIER()->getText(), curBlock);
        if (ctx->variableInitializer()) 
            new llvm::StoreInst(value, inst, curBlock);
        value = inst;
    }
    if (ctx->theType()->IDENTIFIER()) {
        declared.emplace_back(std::find_if(aliases.begin(), aliases.end(), [&ctx](Alias const& a) { return a.first == ctx->theType()->IDENTIFIER()->getText(); })->second, value, ctx->variableName()->IDENTIFIER()->getText());
    } else
        declared.emplace_back(ctx->theType(), value, ctx->variableName()->IDENTIFIER()->getText());
    
    return antlrcpp::Any();
}

antlrcpp::Any LLVMVisitor::visitVariableInitializer(SnowStarParser::VariableInitializerContext* ctx) {
    ExprType inst = visitExpression(ctx->expression());
    return inst;
}

antlrcpp::Any LLVMVisitor::visitExpression(SnowStarParser::ExpressionContext* ctx) {
    llvm::Value* inst = nullptr;
    llvm::Type* type = nullptr;
    bool isSigned = true;
    llvm::IRBuilder<llvm::ConstantFolder> builder(!curBlock->getParent()?std::get<1>(functions[0]):curBlock);

    if (auto pexpr = ctx->primaryExpression()) {
        if (auto id = pexpr->IDENTIFIER()) {
            #ifndef NDEBUG
                std::clog << termcolor::cyan << "   ___   | Variable:" << id->getText() << termcolor::reset << std::endl;
            #endif
            auto it = std::find_if(declared.rbegin(), declared.rend(), [&id] (Decl const& d) { return std::get<2>(d) == id->getText(); });
            inst = builder.CreateLoad(std::get<1>(*it), std::to_string(expr_number_tmp));
            type = inst->getType();
            auto theType = std::get<0>(*it)->builtinTypes();
            if (theType && theType->UI8() || theType->UI16() || theType->UI32() || theType->UI64())
                isSigned = false;
            expr_number_tmp++;
        } else if (auto lit = pexpr->value()) {
            #ifndef NDEBUG
                std::clog << termcolor::cyan << "   ___   | Literal:" << lit->getText() << termcolor::reset << std::endl;
            #endif

            if (lit->BOOL_LITERAL()) {
                inst = llvm::Constant::getIntegerValue(llvmTypes["bool"], llvm::APInt{1, (uint64_t)(lit->getText()=="true"?1:0), false});
                type = llvmTypes["bool"];
            } else if (lit->CHAR_LITERAL()) {
                inst = llvm::Constant::getIntegerValue(llvmTypes["chr"], llvm::APInt{8, (uint64_t)lit->getText()[1], false});
                type = llvmTypes["chr"];
            } else if (lit->DEC_LITERAL() || lit->BIN_LITERAL() || lit->HEX_LITERAL() || lit->OCT_LITERAL()) {
                std::uint64_t val = std::strtoull(lit->getText().c_str(), nullptr, lit->DEC_LITERAL()?10:lit->BIN_LITERAL()?2:lit->OCT_LITERAL()?8:16);
                if (val <= std::numeric_limits<std::uint8_t>::max()) {
                    inst = llvm::Constant::getIntegerValue(llvmTypes["ui8"], llvm::APInt{8, val, false});
                    type = llvmTypes["ui8"];
                    isSigned = false;
                } else if (val <= std::numeric_limits<std::uint16_t>::max()) {
                    inst = llvm::Constant::getIntegerValue(llvmTypes["ui16"], llvm::APInt{16, val, false});
                    type = llvmTypes["ui16"];
                    isSigned = false;
                } else if (val <= std::numeric_limits<std::uint32_t>::max()) {
                    inst = llvm::Constant::getIntegerValue(llvmTypes["ui32"], llvm::APInt{32, val, false});
                    type = llvmTypes["ui32"];
                    isSigned = false;
                } else {
                    inst = llvm::Constant::getIntegerValue(llvmTypes["ui64"], llvm::APInt{64, val, false});
                    type = llvmTypes["ui64"];
                    isSigned = false;
                }
            } else if (lit->FLOAT_LITERAL()) {
                double val = std::stod(lit->FLOAT_LITERAL()->getText());
                if (val >= std::numeric_limits<std::float_t>::min() && val <= std::numeric_limits<std::float_t>::max()) {
                    inst = llvm::ConstantFP::get(llvmTypes["f32"], val);
                    type = llvmTypes["f32"];
                } else {
                    inst = llvm::ConstantFP::get(llvmTypes["f64"], val);
                    type = llvmTypes["f64"];
                }
            } else if (lit->STRING_LITERAL()) {
                inst = llvm::ConstantDataArray::getString(module.getContext(), lit->STRING_LITERAL()->getText().substr(1, lit->STRING_LITERAL()->getText().size()-2));
                type = inst->getType();
            }
        } else {
            ExprType expr = visitExpression(pexpr->expression());
            inst = std::get<0>(expr);
            type = std::get<1>(expr);
            isSigned = std::get<2>(expr);
        }
    } else {
        if (auto type2 = ctx->theType()) {

        } else if (auto unexpr = ctx->unary) {
            ExprType expr = visitExpression(ctx->expression()[0]);
            if (unexpr->getText() == "+") {
                inst = std::get<0>(expr);
                type = std::get<1>(expr);
            } else if (unexpr->getText() == "-") {
                if (std::get<1>(expr)->isFloatingPointTy()) {
                    inst = builder.CreateFSub(llvm::ConstantFP::get(module.getContext(), llvm::APFloat{0.0}), std::get<0>(expr), std::to_string(expr_number_tmp));
                    type = std::get<1>(expr);
                } else {
                    inst = builder.CreateSub(llvm::Constant::getIntegerValue(llvmTypes["i8"], llvm::APInt{8, 0, false}), std::get<0>(expr), std::to_string(expr_number_tmp));
                    type = std::get<1>(expr);
                }
            } else if (unexpr->getText() == "~") {
                inst = builder.CreateNot(std::get<0>(expr), std::to_string(expr_number_tmp));
                type = std::get<1>(expr);
            } else if (unexpr->getText() == "!") {
                inst = builder.CreateNot(std::get<0>(expr), std::to_string(expr_number_tmp));
                type = llvmTypes["bool"];
            }
            expr_number_tmp++;
        } else if (auto binexpr = ctx->binary) {
            ExprType expr0 = visitExpression(ctx->expression()[0]),
                     expr1 = visitExpression(ctx->expression()[1]);

            if (binexpr->getText() == "+") {
                if (std::get<1>(expr0)->isArrayTy()) {
                    // string
                    //inst = builder.CreateCall(/* concat, {std::get<0>(expr0), std::get<0>(expr1)}, std::to_string(expr_number_tmp)*/);
                    type = std::get<1>(expr0);
                } else if (std::get<1>(expr0)->isFloatingPointTy()) {
                    // float
                    inst = builder.CreateFAdd(std::get<0>(expr0), std::get<0>(expr1), std::to_string(expr_number_tmp));
                    type = std::get<1>(expr0);
                } else {
                    // number
                    if (!std::get<2>(expr0))
                        inst = builder.CreateNSWAdd(std::get<0>(expr0), std::get<0>(expr1), std::to_string(expr_number_tmp));
                    else
                        inst = builder.CreateNUWAdd(std::get<0>(expr0), std::get<0>(expr1), std::to_string(expr_number_tmp));
                    type = std::get<1>(expr0);
                }
            } else if (binexpr->getText() == "*") {
                if (std::get<1>(expr0)->isFloatingPointTy()) {
                    inst = builder.CreateFMul(std::get<0>(expr0), std::get<0>(expr1), std::to_string(expr_number_tmp));
                    type = std::get<1>(expr0);
                } else {
                    if (!std::get<2>(expr0))
                        inst = builder.CreateNSWMul(std::get<0>(expr0), std::get<0>(expr1), std::to_string(expr_number_tmp));
                    else
                        inst = builder.CreateNUWMul(std::get<0>(expr0), std::get<0>(expr1), std::to_string(expr_number_tmp));
                    type = std::get<1>(expr0);
                }
            } else if (binexpr->getText() == "/") {
                if (std::get<1>(expr0)->isFloatingPointTy()) {
                    inst = builder.CreateFDiv(std::get<0>(expr0), std::get<0>(expr1), std::to_string(expr_number_tmp));
                    type = std::get<1>(expr0);
                } else {
                    if (std::get<2>(expr0))
                        inst = builder.CreateSDiv(std::get<0>(expr0), std::get<0>(expr1), std::to_string(expr_number_tmp));
                    else
                        inst = builder.CreateUDiv(std::get<0>(expr0), std::get<0>(expr1), std::to_string(expr_number_tmp));
                    type = std::get<1>(expr0);
                }
            } else if (binexpr->getText() == "-") {
                if (std::get<1>(expr0)->isFloatingPointTy()) {
                    inst = builder.CreateFSub(std::get<0>(expr0), std::get<0>(expr1), std::to_string(expr_number_tmp));
                    type = std::get<1>(expr0);
                } else {
                    if (!std::get<2>(expr0))
                        inst = builder.CreateNSWSub(std::get<0>(expr0), std::get<0>(expr1), std::to_string(expr_number_tmp));
                    else
                        inst = builder.CreateNUWSub(std::get<0>(expr0), std::get<0>(expr1), std::to_string(expr_number_tmp));
                    type = std::get<1>(expr0);
                }
            } else if (binexpr->getText() == ">") {
                if (std::get<1>(expr0)->isFloatingPointTy()) {
                    inst = builder.CreateFCmpOGT(std::get<0>(expr0), std::get<0>(expr1), std::to_string(expr_number_tmp));
                    type = llvmTypes["bool"];
                } else {
                    if (std::get<2>(expr0)) {
                        // we perform operation as unsigned
                        inst = builder.CreateICmpSGT(std::get<0>(expr0), std::get<0>(expr1), std::to_string(expr_number_tmp));
                    } else {
                        inst = builder.CreateICmpUGT(std::get<0>(expr0), std::get<0>(expr1), std::to_string(expr_number_tmp));
                    }
                    type = llvmTypes["bool"];
                }
            } else if (binexpr->getText() == "<") {
                if (std::get<1>(expr0)->isFloatingPointTy()) {
                    inst = builder.CreateFCmpOLT(std::get<0>(expr0), std::get<0>(expr1), std::to_string(expr_number_tmp));
                    type = llvmTypes["bool"];
                } else {
                    if (std::get<2>(expr0)) {
                        // we perform operation as unsigned
                        inst = builder.CreateICmpSLT(std::get<0>(expr0), std::get<0>(expr1), std::to_string(expr_number_tmp));
                    } else {
                        inst = builder.CreateICmpULT(std::get<0>(expr0), std::get<0>(expr1), std::to_string(expr_number_tmp));
                    }
                    type = llvmTypes["bool"];
                }
            } else if (binexpr->getText() == "<=") {
                if (std::get<1>(expr0)->isFloatingPointTy()) {
                    inst = builder.CreateFCmpOLE(std::get<0>(expr0), std::get<0>(expr1), std::to_string(expr_number_tmp));
                    type = llvmTypes["bool"];
                } else {
                    if (std::get<2>(expr0)) {
                        // we perform operation as signed
                        inst = builder.CreateICmpSLE(std::get<0>(expr0), std::get<0>(expr1), std::to_string(expr_number_tmp));
                    } else {
                        inst = builder.CreateICmpULE(std::get<0>(expr0), std::get<0>(expr1), std::to_string(expr_number_tmp));
                    }
                    type = llvmTypes["bool"];
                }
            } else if (binexpr->getText() == ">=") {
                if (std::get<1>(expr0)->isFloatingPointTy()) {
                    inst = builder.CreateFCmpOGE(std::get<0>(expr0), std::get<0>(expr1), std::to_string(expr_number_tmp));
                    type = llvmTypes["bool"];
                } else {
                    if (std::get<2>(expr0)) {
                        // we perform operation as unsigned
                        inst = builder.CreateICmpSGE(std::get<0>(expr0), std::get<0>(expr1), std::to_string(expr_number_tmp));
                    } else {
                        inst = builder.CreateICmpUGE(std::get<0>(expr0), std::get<0>(expr1), std::to_string(expr_number_tmp));
                    }
                    type = llvmTypes["bool"];
                }
            } else if (binexpr->getText() == "==") {
                if (std::get<1>(expr0)->isFloatingPointTy()) {
                    inst = builder.CreateFCmpOEQ(std::get<0>(expr0), std::get<0>(expr1), std::to_string(expr_number_tmp));
                    type = llvmTypes["bool"];
                } else {
                    inst = builder.CreateICmpEQ(std::get<0>(expr0), std::get<0>(expr1), std::to_string(expr_number_tmp));
                    type = llvmTypes["bool"];
                }
            } else if (binexpr->getText() == "!=") {
                if (std::get<1>(expr0)->isFloatingPointTy()) {
                    inst = builder.CreateFCmpONE(std::get<0>(expr0), std::get<0>(expr1), std::to_string(expr_number_tmp));
                    type = llvmTypes["bool"];
                } else {
                    inst = builder.CreateICmpNE(std::get<0>(expr0), std::get<0>(expr1), std::to_string(expr_number_tmp));
                    type = llvmTypes["bool"];
                }
            } else if (binexpr->getText() == "^") {
                inst = builder.CreateXor(std::get<0>(expr0), std::get<0>(expr1), std::to_string(expr_number_tmp));
                type = std::get<1>(expr0);
                isSigned = std::get<2>(expr0);
            } else if (binexpr->getText() == "|") {
                inst = builder.CreateAnd(std::get<0>(expr0), std::get<0>(expr1), std::to_string(expr_number_tmp));
                type = std::get<1>(expr0);
                isSigned = std::get<2>(expr0);
            } else if (binexpr->getText() == "&") {
                inst = builder.CreateOr(std::get<0>(expr0), std::get<0>(expr1), std::to_string(expr_number_tmp));
                type = std::get<1>(expr0);
                isSigned = std::get<2>(expr0);
            } else if (binexpr->getText() == "||") {
                inst = builder.CreateOr(std::get<0>(expr0), std::get<0>(expr1), std::to_string(expr_number_tmp));
                type = llvmTypes["bool"];
            } else if (binexpr->getText() == "&&") {
                inst = builder.CreateAnd(std::get<0>(expr0), std::get<0>(expr1), std::to_string(expr_number_tmp));
                type = llvmTypes["bool"];
            }
            expr_number_tmp++;
        }
    }
    return std::make_tuple(inst, type, isSigned);
}

antlrcpp::Any LLVMVisitor::visitFunctionDeclaration(SnowStarParser::FunctionDeclarationContext* ctx) {
    auto function = visitFunctionHeader(ctx->functionHeader()).as<llvm::Function*>();

    llvm::BasicBlock* prevBlock = curBlock;
    // visitBlock
    functions.emplace_back(function, nullptr);

    auto funBlock = visitBasicBlockDeclaration(ctx->basicBlockDeclaration()).as<llvm::BasicBlock*>();

    if (!funBlock->getTerminator())
        llvm::ReturnInst::Create(module.getContext(), nullptr, funBlock);

    curBlock = prevBlock;

    return antlrcpp::Any();
}

antlrcpp::Any LLVMVisitor::visitFunctionHeader(SnowStarParser::FunctionHeaderContext* ctx) {
    auto params = visitFunctionParams(ctx->functionParams()).as<std::vector<std::pair<llvm::Type*, std::string>>>();
    std::vector<llvm::Type*> parameters = visitFunctionParamsTypes(ctx->functionParamsTypes());

    llvm::FunctionType* returnType = llvm::FunctionType::get(llvmTypes[ctx->theType()->getText()], parameters, false);
    llvm::Function* func = llvm::Function::Create(returnType, llvm::GlobalValue::LinkageTypes::ExternalLinkage, ctx->functionName()->getText(), &module);

    llvm::Function::arg_iterator args = func->arg_begin();
    for (auto p : params) {
        llvm::Value* param = args++;
        param->setName(p.second);
    }

    return func;
}

antlrcpp::Any LLVMVisitor::visitFunctionParamsTypes(SnowStarParser::FunctionParamsTypesContext* ctx) {
    std::vector<llvm::Type*> types;
    for (auto type : ctx->theType())
        types.push_back(llvmTypes[type->getText()]);
    return types;
}

antlrcpp::Any LLVMVisitor::visitFunctionParams(SnowStarParser::FunctionParamsContext* ctx) {
    std::vector<std::pair<llvm::Type*, std::string>> params{};

    for (auto var : ctx->parameterDeclaration()) 
        params.emplace_back(llvmTypes[var->IDENTIFIER()->getText()], var->IDENTIFIER()->getText());

    return params;
}

antlrcpp::Any LLVMVisitor::visitBasicBlockDeclaration(SnowStarParser::BasicBlockDeclarationContext* ctx) {
    llvm::BasicBlock* bl = llvm::BasicBlock::Create(module.getContext(), "entry", std::get<0>(*functions.rbegin()));
    std::get<1>(*functions.rbegin()) = bl;
    curBlock = bl;

    visitChildren(ctx);

    return bl;
}

antlrcpp::Any LLVMVisitor::visitReturnDeclaration(SnowStarParser::ReturnDeclarationContext* ctx) {
    llvm::ReturnInst::Create(module.getContext(), ctx->expression()?std::get<0>(visitExpression(ctx->expression()).as<ExprType>()):nullptr, curBlock);

    return antlrcpp::Any();
}