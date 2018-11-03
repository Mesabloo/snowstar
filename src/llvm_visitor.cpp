#include <llvm_visitor.hpp>

#if defined(_WIN32) || defined (_WIN64)
#   undef VOID
#endif

#include <termcolor/termcolor.hpp>

#include <llvm/Support/raw_ostream.h>

LLVMVisitor::LLVMVisitor(llvm::Module& mod) : module{mod} {
    llvm_types = {
        {"bool", llvm::IntegerType::get(module.getContext(), 1)},
        {"char", llvm::Type::getInt8Ty(module.getContext())},
        {"int8", llvm::Type::getInt8Ty(module.getContext())},
        {"int16", llvm::Type::getInt16Ty(module.getContext())},
        {"int32", llvm::Type::getInt32Ty(module.getContext())},
        {"int64", llvm::Type::getInt64Ty(module.getContext())},
        {"real16", llvm::Type::getHalfTy(module.getContext())},
        {"real32", llvm::Type::getFloatTy(module.getContext())},
        {"real64", llvm::Type::getDoubleTy(module.getContext())}
    };
}

antlrcpp::Any LLVMVisitor::visitCompilationUnit(SnowStarParser::CompilationUnitContext* ctx) {
    llvm::FunctionType* type = llvm::FunctionType::get(llvm::IntegerType::get(module.getContext(), 32), false);
    llvm::Function* main = llvm::Function::Create(type, llvm::Function::ExternalLinkage, "main", &module);
    cur_block = llvm::BasicBlock::Create(module.getContext(), "entry", main, 0);

    visitChildren(ctx);

    llvm::ConstantInt* i32_0 = llvm::ConstantInt::get(module.getContext(), llvm::APInt(32, 0));
    llvm::ReturnInst::Create(module.getContext(), i32_0, cur_block);
    return 0;
}

antlrcpp::Any LLVMVisitor::visitDeclare(SnowStarParser::DeclareContext* ctx) {
    llvm::AllocaInst* val = new llvm::AllocaInst(
        llvm_types[ctx->type()->getText()], 
        0,
        ctx->IDENTIFIER()->getText(), 
        cur_block
    );

    #ifndef NDEBUG
        std::clog << termcolor::blue << "   :::   | Generated LLVM code for declaration." << termcolor::reset << std::endl;
    #endif

    if (ctx->type()->IDENTIFIER()) {
        return Decl(std::find_if(aliases.begin(), aliases.end(), [&ctx](Alias const& a) { return a.first == ctx->type()->IDENTIFIER()->getText(); })->second, val);

    } else
        return Decl(ctx->type(), val);
}

antlrcpp::Any LLVMVisitor::visitDefine(SnowStarParser::DefineContext* ctx) {
    auto type = visitDeclare(ctx->declare()).as<Decl>();
    declared.push_back(type);
    llvm::Value* value = visitExpression(ctx->expression());
    expr_number_tmp = 0;

    llvm::StoreInst* store = new llvm::StoreInst{value, type.second, cur_block};

    #ifndef NDEBUG
        std::clog << termcolor::blue << "   :::   | Generated LLVM code for definition." << termcolor::reset << std::endl;
    #endif

    return store;
}

antlrcpp::Any LLVMVisitor::visitAlias(SnowStarParser::AliasContext* ctx) {
    auto& type = llvm_types[ctx->type()->getText()];

    llvm_types[ctx->IDENTIFIER()->getText()] = type;

    if (ctx->type()->IDENTIFIER()) {
        auto alias_it = std::find_if(aliases.begin(), aliases.end(), [&ctx] (Alias const& a) { return a.first == ctx->type()->IDENTIFIER()->getText(); });
        while (alias_it != aliases.end() && alias_it->second->IDENTIFIER()) {
            alias_it = std::find_if(aliases.begin(), aliases.end(), [&alias_it] (Alias const& a) { return a.first == alias_it->second->getText(); });
        }
        
        aliases.push_back(Alias(ctx->IDENTIFIER()->getText(), alias_it->second));
    } else
        aliases.push_back(Alias(ctx->IDENTIFIER()->getText(), ctx->type()));

    return type;
}


antlrcpp::Any LLVMVisitor::visitStatement(SnowStarParser::StatementContext* ctx) {
    visitChildren(ctx);
    return 0;
}
antlrcpp::Any LLVMVisitor::visitExpression(SnowStarParser::ExpressionContext* ctx) {

    llvm::IRBuilder<> builder(cur_block);
    llvm::Value* val;
    
    if (ctx->bop) {
        llvm::Value *lhs = visitExpression(ctx->expression()[0]).as<llvm::Value*>(),
                    *rhs = visitExpression(ctx->expression()[1]).as<llvm::Value*>();

        #ifndef NDEBUG
            std::clog << termcolor::magenta << "   ...   | Operator='" << ctx->bop->getText() << "'" << termcolor::reset << std::endl;
        #endif

        if (ctx->bop->getText() == "+")
            val = builder.CreateAdd(lhs, rhs, std::to_string(expr_number_tmp));
        else if (ctx->bop->getText() == "-")
            val = builder.CreateSub(lhs, rhs, std::to_string(expr_number_tmp));
        else if (ctx->bop->getText() == "*")
            val = builder.CreateMul(lhs, rhs, std::to_string(expr_number_tmp));
        else if (ctx->bop->getText() == "/") {
            if ((lhs->getType()->isDoubleTy() || lhs->getType()->isFloatTy() || lhs->getType()->isHalfTy()) || (rhs->getType()->isDoubleTy() || rhs->getType()->isFloatTy() || rhs->getType()->isHalfTy()))
                val = builder.CreateFDiv(lhs, rhs, std::to_string(expr_number_tmp));
            else
                val = builder.CreateSDiv(lhs, rhs, std::to_string(expr_number_tmp), false);
        } else if (ctx->bop->getText() == "^")
            val = builder.CreateXor(lhs, rhs, std::to_string(expr_number_tmp));
        else if (ctx->bop->getText() == "&&" || ctx->bop->getText() == "&")
            val = builder.CreateAnd(lhs, rhs, std::to_string(expr_number_tmp));
        else if (ctx->bop->getText() == "||" || ctx->bop->getText() == "|")
            val = builder.CreateOr(lhs, rhs, std::to_string(expr_number_tmp));
        else if (ctx->bop->getText() == "==") {
            if ((lhs->getType()->isDoubleTy() || lhs->getType()->isFloatTy() || lhs->getType()->isHalfTy()) || (rhs->getType()->isDoubleTy() || rhs->getType()->isFloatTy() || rhs->getType()->isHalfTy()))
                val = builder.CreateFCmpOEQ(lhs, rhs, std::to_string(expr_number_tmp));
            else
                val = builder.CreateICmpEQ(lhs, rhs, std::to_string(expr_number_tmp));
        } else if (ctx->bop->getText() == "!=") {
            if ((lhs->getType()->isDoubleTy() || lhs->getType()->isFloatTy() || lhs->getType()->isHalfTy()) || (rhs->getType()->isDoubleTy() || rhs->getType()->isFloatTy() || rhs->getType()->isHalfTy()))
                val = builder.CreateFCmpONE(lhs, rhs, std::to_string(expr_number_tmp));
            else
                val = builder.CreateICmpNE(lhs, rhs, std::to_string(expr_number_tmp));
        } else if (ctx->bop->getText() == ">=") {
            if ((lhs->getType()->isDoubleTy() || lhs->getType()->isFloatTy() || lhs->getType()->isHalfTy()) || (rhs->getType()->isDoubleTy() || rhs->getType()->isFloatTy() || rhs->getType()->isHalfTy()))
                val = builder.CreateFCmpOGE(lhs, rhs, std::to_string(expr_number_tmp));
            else
                val = builder.CreateICmpSGE(lhs, rhs, std::to_string(expr_number_tmp));
        } else if (ctx->bop->getText() == "<=") {
            if ((lhs->getType()->isDoubleTy() || lhs->getType()->isFloatTy() || lhs->getType()->isHalfTy()) || (rhs->getType()->isDoubleTy() || rhs->getType()->isFloatTy() || rhs->getType()->isHalfTy()))
                val = builder.CreateFCmpOLE(lhs, rhs, std::to_string(expr_number_tmp));
            else
                val = builder.CreateICmpSLE(lhs, rhs, std::to_string(expr_number_tmp));
        } else if (ctx->bop->getText() == ">") {
            if ((lhs->getType()->isDoubleTy() || lhs->getType()->isFloatTy() || lhs->getType()->isHalfTy()) || (rhs->getType()->isDoubleTy() || rhs->getType()->isFloatTy() || rhs->getType()->isHalfTy()))
                val = builder.CreateFCmpOGT(lhs, rhs, std::to_string(expr_number_tmp));
            else
                val = builder.CreateICmpSGT(lhs, rhs, std::to_string(expr_number_tmp));
        } else if (ctx->bop->getText() == "<") {
            if ((lhs->getType()->isDoubleTy() || lhs->getType()->isFloatTy() || lhs->getType()->isHalfTy()) || (rhs->getType()->isDoubleTy() || rhs->getType()->isFloatTy() || rhs->getType()->isHalfTy()))
                val = builder.CreateFCmpOLT(lhs, rhs, std::to_string(expr_number_tmp));
            else
                val = builder.CreateICmpSLT(lhs, rhs, std::to_string(expr_number_tmp));
        }
    } else if (ctx->uop) {
        llvm::Value* expr = visitExpression(ctx->expression()[0]).as<llvm::Value*>();
        if (ctx->uop->getText() == "-")
            val = builder.CreateSub(llvm::Constant::getIntegerValue(expr->getType(), llvm::APInt(8, 0, true)), expr, std::to_string(expr_number_tmp));
        else if (ctx->uop->getText() == "+")
            val = expr;
        else if (ctx->uop->getText() == "~")
            val = builder.CreateNeg(expr, std::to_string(expr_number_tmp));
        else if (ctx->uop->getText() == "!")
            val = builder.CreateNot(expr, std::to_string(expr_number_tmp));
    } else {
        if (ctx->IDENTIFIER()) {
            auto it = std::find_if(declared.begin(), declared.end(), [&ctx] (Decl const& d) { return static_cast<std::string>(d.second->getName()) == ctx->IDENTIFIER()->getText(); });
            val = it->second;
        } else if (ctx->literal()) {
            auto findType = [] (SnowStarParser::LiteralContext* ct) -> std::string {
                std::string val{ct->getText()};
                if (ct->BOOL_LITERAL()) return "bool";
                if (ct->CHAR_LITERAL()) return "char";
                if (ct->FLOAT_LITERAL()) {
                    double d = std::stod(val);
                    if (d > std::numeric_limits<float>::max() || d < std::numeric_limits<float>::min()) return "real64";
                    else if (d < std::numeric_limits<float>::max()/2) return "real16";
                    else return "real32";
                }
                if (ct->DECIMAL_LITERAL()) {
                    int64_t i = std::stoll(val);
                    if (i < std::numeric_limits<int8_t>::max() && i > std::numeric_limits<int8_t>::min()) return "int8";
                    else if (i < std::numeric_limits<int16_t>::max() && i > std::numeric_limits<int16_t>::min()) return "int16";
                    else if (i < std::numeric_limits<int32_t>::max() && i > std::numeric_limits<int32_t>::min()) return "int64";
                    else return "int32";
                }
                return "void";
            };

            if (ctx->literal()->BOOL_LITERAL()) {
                val = llvm::Constant::getIntegerValue(llvm_types["bool"], llvm::APInt(1, ctx->literal()->BOOL_LITERAL()->getText()=="true"?1:0, false));
            } else if (ctx->literal()->CHAR_LITERAL()) {
                val = llvm::Constant::getIntegerValue(llvm_types["char"], llvm::APInt(8, ctx->literal()->CHAR_LITERAL()->getText()[1], true));
            } else if (ctx->literal()->FLOAT_LITERAL()) {
                val = llvm::ConstantFP::get(llvm_types[findType(ctx->literal())], std::stod(ctx->literal()->getText()));
            } else {
                std::string type = findType(ctx->literal());
                val = llvm::Constant::getIntegerValue(llvm_types[type], llvm::APInt(type == "int8"?8:type == "int16"?16:type == "int32"?32:type == "int64"?64:0, std::stoll(ctx->literal()->getText()), true));
            }
        } else {
            val = visitExpression(ctx->expression()[0]).as<llvm::Value*>();
        }
    }

    expr_number_tmp++;

    return val;
}