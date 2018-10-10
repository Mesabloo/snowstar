#include <visitor.hpp>

#include <llvm/Support/raw_ostream.h>

#define ERRORED (!errors.errs.empty() && !errors.warns.empty())

namespace utils {
    bool str_startswith(std::string const& src, std::string const& prefix) {
        return src.size() >= prefix.size() && src.substr(0, prefix.size()) == prefix;
    }
}

Visitor::Visitor(std::string const& file, llvm::Module& m) : module{m}, file_name{file} {
    llvm_types = {
        {"bool", llvm::IntegerType::get(module.getContext(), 1)},
        {"char", llvm::Type::getInt8Ty(module.getContext())},
        {"int8", llvm::Type::getInt8Ty(module.getContext())},
        {"int16", llvm::Type::getInt16Ty(module.getContext())},
        {"int32", llvm::Type::getInt32Ty(module.getContext())},
        {"int64", llvm::Type::getInt64Ty(module.getContext())},
        {"int128", llvm::Type::getInt128Ty(module.getContext())},
        {"real16", llvm::Type::getHalfTy(module.getContext())},
        {"real32", llvm::Type::getFloatTy(module.getContext())},
        {"real64", llvm::Type::getDoubleTy(module.getContext())}
    };
}

antlrcpp::Any Visitor::visitCompilationUnit(SnowStarParser::CompilationUnitContext* ctx) {
    llvm::FunctionType* type = llvm::FunctionType::get(llvm::IntegerType::get(module.getContext(), 32), false);
    llvm::Function* main = llvm::Function::Create(type, llvm::Function::ExternalLinkage, "main", &module);
    cur_block = llvm::BasicBlock::Create(module.getContext(), "entry", main, 0);

    visitChildren(ctx);

    if (!ERRORED) {
        llvm::ConstantInt* i32_0 = llvm::ConstantInt::get(module.getContext(), llvm::APInt(32, 0));
        llvm::ReturnInst::Create(module.getContext(), i32_0, cur_block);
    }
    return antlrcpp::Any();
}

antlrcpp::Any Visitor::visitStatement(SnowStarParser::StatementContext* ctx) {
    #ifndef NDEBUG
        std::clog << termcolor::green << "   [i]   | Visiting a statement..." << termcolor::reset << std::endl;
    #endif

    current_stmt_context = ctx;

    #ifndef NDEBUG
        std::clog << termcolor::magenta << "   ...   | Current line: " <<
            ctx->getStart()->getInputStream()->getText(antlr4::misc::Interval{ctx->getStart()->getStartIndex(), ctx->getStop()->getStopIndex()})
            << termcolor::reset << std::endl;
    #endif
    visitChildren(ctx);
    return antlrcpp::Any();
}

antlrcpp::Any Visitor::visitExpression(SnowStarParser::ExpressionContext* ctx) {
    #ifndef NDEBUG
        std::clog << termcolor::green << "   [i]   | Visiting an expression..." << termcolor::reset << std::endl;
    #endif
    auto res = visitChildren(ctx);
    /*if (ctx->bop && ctx->bop->getText() == "=") {
        // we used `visitCreator`->`visitExpression`
    }*/
    /*if (ctx->DEF()) {
        // we used `visitCreator`
    }*/
    return antlrcpp::Any();
}

antlrcpp::Any Visitor::visitDeclare(SnowStarParser::DeclareContext* ctx) {
    #ifndef NDEBUG
        std::clog << termcolor::green << "   [i]   | Visiting a declaration..." << termcolor::reset << std::endl;
    #endif
    if (ctx->primitiveType()->VOID()) {
        errors.errs.push_back(InvalidDeclaringTypeError().from(current_stmt_context, ctx->primitiveType()->VOID()->getSymbol(), "void"));
        return ctx->primitiveType();
    }
    auto it = std::find_if(declared.begin(), declared.end(), [&] (Var const& var) { return std::get<0>(var) == ctx->IDENTIFIER()->getText(); });
    #ifndef NDEBUG
        std::clog << termcolor::green << std::boolalpha << "   [i]   | >> " << ctx->IDENTIFIER()->getText() << " is already declared: " << (it != declared.end()) << termcolor::reset << std::endl;
    #endif
    if (it != declared.end()) {
        // throw an error here : redeclared variable
        #ifndef NDEBUG
            std::clog << termcolor::magenta << "   ...   | Variable " << ctx->IDENTIFIER()->getText() << " redeclared." << termcolor::reset << std::endl;
        #endif
        errors.errs.push_back(RedeclaredVariableError().from(current_stmt_context, ctx->IDENTIFIER()->getSymbol(), ctx->IDENTIFIER()->getText()+";"+std::to_string(std::get<2>(*it).first)+";"+std::to_string(std::get<2>(*it).second)));
        return nullptr;
    }
    declared.push_back(std::make_tuple(ctx->IDENTIFIER()->getText(), ctx->primitiveType(), std::make_pair(ctx->IDENTIFIER()->getSymbol()->getLine(), ctx->IDENTIFIER()->getSymbol()->getCharPositionInLine())));

    // LLVM generation

    if (!ERRORED) {
        // std::clog << std::boolalpha << "t:is_nullptr=" << (t == nullptr) << "cur_block:is_nullptr=" << (cur_block == nullptr) << std::endl;
        
        llvm::AllocaInst* val = new llvm::AllocaInst(
            llvm_types[ctx->primitiveType()->getText()], 
            0,
            ctx->IDENTIFIER()->getText(), 
            cur_block
        );

        #ifndef NDEBUG
            std::clog << termcolor::blue << "   :::   | Generated LLVM code for declaration." << termcolor::reset << std::endl;
        #endif
        //new llvm::AllocaInst(type(ctx->primitiveType()), 1, "test", cur_block);

        return Decl(ctx->primitiveType(), val);
    } else 
        return std::make_pair(ctx->primitiveType(), nullptr);
}

antlrcpp::Any Visitor::visitDefine(SnowStarParser::DefineContext* ctx) {
    #ifndef NDEBUG
        std::clog << termcolor::green << "   [i]   | Visiting a definition..." << termcolor::reset << std::endl;
    #endif
    antlrcpp::Any t = visitDeclare(ctx->declare());
    if (!t.is<Decl>()) return antlrcpp::Any();
    Decl type = t.as<Decl>();
    if (type.first->VOID()) return antlrcpp::Any();

    auto findStringType = [] (SnowStarParser::LiteralContext* ct) -> std::string {
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
            else if (i < std::numeric_limits<int32_t>::max() && i > std::numeric_limits<int32_t>::min()) return "int32";
            else if (i > std::numeric_limits<int64_t>::max()) return "int128";
            else return "int64";
        }
        return "void";
    };

    llvm::Value* value = nullptr;

    if (auto id = ctx->expression()->IDENTIFIER()) {
        auto it = std::find_if(declared.begin(), declared.end(), [&] (Var const& v) { return id->getText() == std::get<0>(v); });
        if (it == declared.end()) {
            // throw error
            errors.errs.push_back(UndeclaredVariableError().from(current_stmt_context, id->getSymbol(), id->getSymbol()->getText()));
            return antlrcpp::Any();
        }
        if (type.first->BOOLEAN() && std::get<1>(*it)->getText() != "bool") {
            // inconsistent types bool and not bool
            errors.errs.push_back(WrongTypedValueError().from(current_stmt_context, ctx->expression()->getStart(), "bool;"+std::get<1>(*it)->getText()));
            return antlrcpp::Any();
        } else if (type.first->BOOLEAN() && !ERRORED) {
            
        }
        if (type.first->CHAR() && std::get<1>(*it)->getText() != "char") {
            // inconsistent types char and not char
            errors.errs.push_back(WrongTypedValueError().from(current_stmt_context, ctx->expression(), "char;"+std::get<1>(*it)->getText()));
            return antlrcpp::Any();
        } else if (type.first->CHAR() && !ERRORED) {

        }
        if ((type.first->INTEGER8() || type.first->INTEGER16() || type.first->INTEGER32() || type.first->INTEGER64() || type.first->INTEGER128())) {
            if (utils::str_startswith(std::get<1>(*it)->getText(), "real")) {
                // implicit cast
                errors.warns.push_back(ImplicitCastWarning().from(current_stmt_context, ctx->expression(), std::get<1>(*it)->getText()+";"+[&type]() -> std::string { return type.first->INTEGER8()?"int8":type.first->INTEGER16()?"int16":type.first->INTEGER32()?"int32":"int64"; }()));
            } else if (!utils::str_startswith(std::get<1>(*it)->getText(), "int")) {
                // inconsistent types
                errors.errs.push_back(WrongTypedValueError().from(current_stmt_context, ctx->expression(), [&type]() -> std::string { return type.first->INTEGER8()?"int8":type.first->INTEGER16()?"int16":type.first->INTEGER32()?"int32":"int64"; }()+";"+std::get<1>(*it)->getText()));
                return antlrcpp::Any();
            }
            if (!ERRORED) {

            }
        }
        if ((type.first->REAL32() || type.first->REAL64() || type.first->REAL16()) && !utils::str_startswith(std::get<1>(*it)->getText(), "int") && !utils::str_startswith(std::get<1>(*it)->getText(), "real")) {
            errors.errs.push_back(WrongTypedValueError().from(current_stmt_context, ctx->expression(), [&type]() -> std::string { return type.first->REAL32()?"real32":"real64"; }()+";"+std::get<1>(*it)->getText()));
            return antlrcpp::Any();
        } else if ((type.first->REAL32() || type.first->REAL64() || type.first->REAL16()) && !ERRORED) {

        }
    } else if (ctx->expression()->literal()) {
        if (type.first->BOOLEAN() && !ctx->expression()->literal()->BOOL_LITERAL()) {
            // error: value is of wrong type
            errors.errs.push_back(WrongTypedValueError().from(current_stmt_context, ctx->expression()->getStart(), "bool;"+findStringType(ctx->expression()->literal())));
            return antlrcpp::Any();
        } else if (type.first->BOOLEAN() && !ERRORED) {
            value = llvm::Constant::getIntegerValue(llvm_types["bool"], llvm::APInt(1, ctx->expression()->literal()->BOOL_LITERAL()->getText()=="true"?1:0, false));
        }
        if (type.first->CHAR() && !ctx->expression()->literal()->CHAR_LITERAL()) {
            // error: value is of wrong type
            errors.errs.push_back(WrongTypedValueError().from(current_stmt_context, ctx->expression(), "char;"+findStringType(ctx->expression()->literal())));
            return antlrcpp::Any();
        } else if (ctx->expression()->literal()->CHAR_LITERAL() && !ERRORED) {
            value = llvm::Constant::getIntegerValue(llvm_types["char"], llvm::APInt(8, ctx->expression()->literal()->CHAR_LITERAL()->getText()[1], true));
        }
        if ((type.first->INTEGER8() || type.first->INTEGER16() || type.first->INTEGER32() || type.first->INTEGER64() || type.first->INTEGER128())) {
            if (ctx->expression()->literal()->FLOAT_LITERAL()) {
                // implicit cast
                errors.warns.push_back(ImplicitCastWarning().from(current_stmt_context, ctx->expression(), findStringType(ctx->expression()->literal())+";"+[&type]() -> std::string { return type.first->INTEGER8()?"int8":type.first->INTEGER16()?"int16":type.first->INTEGER32()?"int32":"int64"; }()));
            } else if (!ctx->expression()->literal()->DECIMAL_LITERAL()/* && !ctx->expression()->literal()->HEX_LITERAL() && !ctx->expression()->literal()->BIN_LITERAL() */) {
                // error: value is of wrong type
                errors.errs.push_back(WrongTypedValueError().from(current_stmt_context, ctx->expression(), [&type]() -> std::string { return type.first->INTEGER8()?"int8":type.first->INTEGER16()?"int16":type.first->INTEGER32()?"int32":"int64"; }()+";"+findStringType(ctx->expression()->literal())));
                return antlrcpp::Any();
            }
            if (!ERRORED) {
                value = llvm::Constant::getIntegerValue(llvm_types[type.first->getText()], llvm::APInt(type.first->INTEGER8()?8:type.first->INTEGER16()?16:type.first->INTEGER32()?32:type.first->INTEGER64()?64:type.first->INTEGER128()?128:0, std::stoll(ctx->expression()->literal()->getText()), true));
            }
        }
        if ((type.first->REAL32() || type.first->REAL64() || type.first->REAL16()) && !ctx->expression()->literal()->DECIMAL_LITERAL()/* && !ctx->expression()->literal()->HEX_LITERAL() && !ctx->expression()->literal()->BIN_LITERAL() */) {
            errors.errs.push_back(WrongTypedValueError().from(current_stmt_context, ctx->expression(), [&type]() -> std::string { return type.first->REAL32()?"real32":"real64"; }()+";"+findStringType(ctx->expression()->literal())));
            return antlrcpp::Any();
        } else if ((type.first->REAL32() || type.first->REAL64() || type.first->REAL16()) && !ERRORED) {
            value = llvm::ConstantFP::get(llvm_types[type.first->getText()], std::stod(ctx->expression()->literal()->getText()));
        }
    } else {
        // error: invalid expression. Should be detected by the Lexer.
    }

    // generate LLVM
    if (!ERRORED) {
        //type.second->setAlignment(4);

        llvm::StoreInst* store = new llvm::StoreInst{value, &*type.second, cur_block};

        #ifndef NDEBUG
            std::clog << termcolor::blue << "   :::   | Generated LLVM code for definition." << termcolor::reset << std::endl;
        #endif
    }

    return antlrcpp::Any();
}