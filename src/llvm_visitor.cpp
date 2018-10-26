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

//    if (llvm_types.find(ctx->type()->getText()))


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
    llvm::Value* value = nullptr;

    if (ctx->expression()->literal()) {
        if (type.first->BOOLEAN() && ctx->expression()->literal()->BOOL_LITERAL()) {
            value = llvm::Constant::getIntegerValue(llvm_types["bool"], llvm::APInt(1, ctx->expression()->literal()->BOOL_LITERAL()->getText()=="true"?1:0, false));
        }
        if (type.first->CHAR() && ctx->expression()->literal()->CHAR_LITERAL()) {
            value = llvm::Constant::getIntegerValue(llvm_types["char"], llvm::APInt(8, ctx->expression()->literal()->CHAR_LITERAL()->getText()[1], true));
        }
        if ((type.first->INTEGER8() || type.first->INTEGER16() || type.first->INTEGER32() || type.first->INTEGER64()) && (ctx->expression()->literal()->DECIMAL_LITERAL() || ctx->expression()->literal()->FLOAT_LITERAL())) {
            value = llvm::Constant::getIntegerValue(llvm_types[type.first->getText()], llvm::APInt(type.first->INTEGER8()?8:type.first->INTEGER16()?16:type.first->INTEGER32()?32:type.first->INTEGER64()?64:0, std::stoll(ctx->expression()->literal()->getText()), true));
        }
        if ((type.first->REAL32() || type.first->REAL64() || type.first->REAL16()) && ctx->expression()->literal()->FLOAT_LITERAL() && ctx->expression()->literal()->DECIMAL_LITERAL()) {
            value = llvm::ConstantFP::get(llvm_types[type.first->getText()], std::stod(ctx->expression()->literal()->getText()));
        }
    }

    llvm::StoreInst* store = new llvm::StoreInst{value, type.second, cur_block};

    #ifndef NDEBUG
        std::clog << termcolor::blue << "   :::   | Generated LLVM code for definition." << termcolor::reset << std::endl;
    #endif

    return store;
}

antlrcpp::Any LLVMVisitor::visitAlias(SnowStarParser::AliasContext* ctx) {
    auto& type = llvm_types[ctx->type()->getText()];

    llvm_types[ctx->IDENTIFIER()->getText()] = type;
    // llvm_types[ctx->IDENTIFIER()->getText()] = type;

    aliases.push_back(Alias(ctx->IDENTIFIER()->getText(), ctx->type()));

    return type;
}


antlrcpp::Any LLVMVisitor::visitStatement(SnowStarParser::StatementContext* ctx) {
    visitChildren(ctx);
    return 0;
}
antlrcpp::Any LLVMVisitor::visitExpression(SnowStarParser::ExpressionContext* ctx) {
    visitChildren(ctx);
    return 0;
}