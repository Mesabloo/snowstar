#include <visitor.hpp>

namespace utils {
    bool str_startswith(std::string const& src, std::string const& prefix) {
        return src.size() >= prefix.size() && src.substr(0, prefix.size()) == prefix;
    }
}

Visitor::Visitor(llvm::Module& m) : module{m}, current_builder{m.getContext()} {

    llvm::FunctionType* type = llvm::FunctionType::get(current_builder.getInt32Ty(), false);
    llvm::Function* main = llvm::Function::Create(type, llvm::Function::ExternalLinkage, "main", &module);
}

antlrcpp::Any Visitor::visitStatement(SnowStarParser::StatementContext* ctx) {
    #ifndef NDEBUG
        std::clog << termcolor::green << "Visiting a statement..." << termcolor::reset << std::endl;
    #endif

    current_stmt_context = ctx;

    #ifndef NDEBUG
        std::clog << termcolor::magenta << "Current line: " <<
            ctx->getStart()->getInputStream()->getText(antlr4::misc::Interval{ctx->getStart()->getStartIndex(), ctx->getStop()->getStopIndex()})
            << termcolor::reset << std::endl;
    #endif
    visitChildren(ctx);
    return antlrcpp::Any();
}

antlrcpp::Any Visitor::visitExpression(SnowStarParser::ExpressionContext* ctx) {
    #ifndef NDEBUG
        std::clog << termcolor::green << "Visiting an expression..." << termcolor::reset << std::endl;
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
        std::clog << termcolor::green << "Visiting a declaration..." << termcolor::reset << std::endl;
    #endif
    if (ctx->primitiveType()->VOID()) {
        errors.errs.push_back(InvalidDeclaringTypeError().from(current_stmt_context, ctx->primitiveType()->VOID()->getSymbol(), ""));
        return ctx->primitiveType();
    }
    auto it = std::find_if(declared.begin(), declared.end(), [&] (Var const& var) { return var.first == ctx->IDENTIFIER()->getText(); });
    #ifndef NDEBUG
        std::clog << termcolor::green << std::boolalpha << ">> " << ctx->IDENTIFIER()->getText() << " is already declared: " << (it != declared.end()) << termcolor::reset << std::endl;
    #endif
    if (it != declared.end()) {
        // throw an error here : redeclared variable
        #ifndef NDEBUG
            std::clog << termcolor::magenta << "Variable " << ctx->IDENTIFIER()->getText() << " redeclared." << termcolor::reset << std::endl;
        #endif
        errors.errs.push_back(RedeclaredVariableError().from(current_stmt_context, ctx->IDENTIFIER()->getSymbol(), ctx->IDENTIFIER()->getText()));
    }
    declared.push_back(std::make_pair(ctx->IDENTIFIER()->getText(), ctx->primitiveType()));

    // LLVM generation

    return ctx->primitiveType();
}

antlrcpp::Any Visitor::visitDefine(SnowStarParser::DefineContext* ctx) {
    #ifndef NDEBUG
        std::clog << termcolor::green << "Visiting a definition..." << termcolor::reset << std::endl;
    #endif
    auto type = visitDeclare(ctx->declare()).as<decltype(ctx->declare()->primitiveType())>();
    if (type->VOID()) return antlrcpp::Any();

    auto findStringType = [] (SnowStarParser::LiteralContext* ct) -> std::string {
        std::string val{ct->getText()};
        if (ct->BOOL_LITERAL()) return "bool";
        if (ct->CHAR_LITERAL()) return "char";
        if (ct->FLOAT_LITERAL()) {
            double d = std::stod(val);
            if (d > std::numeric_limits<float>::max() || d < std::numeric_limits<float>::min()) return "real64";
            else return "real32";
        }
        if (ct->DECIMAL_LITERAL()) {
            int64_t i = std::stoll(val);
            if (i < std::numeric_limits<int8_t>::max() && i > std::numeric_limits<int8_t>::min()) return "int8";
            else if (i < std::numeric_limits<int16_t>::max() && i > std::numeric_limits<int16_t>::min()) return "int16";
            else if (i < std::numeric_limits<int32_t>::max() && i > std::numeric_limits<int32_t>::min()) return "int32";
            else return "int64";
        }
        return "void";
    };
    if (auto id = ctx->expression()->IDENTIFIER()) {
        auto it = std::find_if(declared.begin(), declared.end(), [&] (Var const& v) { return id->getText() == v.first; });
        if (it == declared.end()) {
            // throw error
            errors.errs.push_back(UndeclaredVariableError().from(current_stmt_context, id->getSymbol(), id->getSymbol()->getText()));
            return antlrcpp::Any();
        }
        if (type->BOOLEAN() && it->second->getText() != "bool") {
            // inconsistent types bool and not bool
            errors.errs.push_back(WrongTypedValueError().from(current_stmt_context, ctx->expression()->getStart(), "bool;"+it->second->getText()));
        }
        if (type->CHAR() && it->second->getText() != "char") {
            // inconsistent types char and not char
            errors.errs.push_back(WrongTypedValueError().from(current_stmt_context, ctx->expression(), "char;"+it->second->getText()));
        }
        if ((type->INTEGER8() || type->INTEGER16() || type->INTEGER32() || type->INTEGER64()) && !utils::str_startswith(it->second->getText(), "int")) {
            // inconsistent types
            errors.errs.push_back(WrongTypedValueError().from(current_stmt_context, ctx->expression(), [&type]() -> std::string { return type->INTEGER8()?"int8":type->INTEGER16()?"int16":type->INTEGER32()?"int32":"int64"; }()+";"+it->second->getText()));
        }
        if ((type->REAL32() || type->REAL64())) {
            if (utils::str_startswith(it->second->getText(), "int")) {
                // implicit 
                errors.warns.push_back(ImplicitCastWarning().from(current_stmt_context, ctx->expression(), it->second->getText()+";"+[&type]() -> std::string { return type->REAL32()?"real32":"real64"; }()));
            } else if (!utils::str_startswith(it->second->getText(), "real")) {
                // inconsistent types
                errors.errs.push_back(WrongTypedValueError().from(current_stmt_context, ctx->expression(), [&type]() -> std::string { return type->REAL32()?"real32":"real64"; }()+";"+it->second->getText()));
            }
        }
    } else if (ctx->expression()->literal()) {
        if (type->BOOLEAN() && !ctx->expression()->literal()->BOOL_LITERAL()) {
            // error: value is of wrong type
            errors.errs.push_back(WrongTypedValueError().from(current_stmt_context, ctx->expression()->getStart(), "bool;"+findStringType(ctx->expression()->literal())));
        }
        if (type->CHAR() && !ctx->expression()->literal()->CHAR_LITERAL()) {
            // error: value is of wrong type
            errors.errs.push_back(WrongTypedValueError().from(current_stmt_context, ctx->expression(), "char;"+findStringType(ctx->expression()->literal())));
        }
        if ((type->INTEGER8() || type->INTEGER16() || type->INTEGER32() || type->INTEGER64()) && (!ctx->expression()->literal()->DECIMAL_LITERAL()/* && !ctx->expression()->literal()->HEX_LITERAL() && !ctx->expression()->literal()->BIN_LITERAL() */)) {
            // error: value is of wrong type
            errors.errs.push_back(WrongTypedValueError().from(current_stmt_context, ctx->expression(), [&type]() -> std::string { return type->INTEGER8()?"int8":type->INTEGER16()?"int16":type->INTEGER32()?"int32":"int64"; }()+";"+findStringType(ctx->expression()->literal())));
        }
        if ((type->REAL32() || type->REAL64())) {
            if (ctx->expression()->literal()->DECIMAL_LITERAL()/* || ctx->expression()->literal()->HEX_LITERAL() || ctx->expression()->literal()->BIN_LITERAL() */) {
                // implicit conversion
                // throw warning
                errors.warns.push_back(ImplicitCastWarning().from(current_stmt_context, ctx->expression(), findStringType(ctx->expression()->literal())+";"+[&type]() -> std::string { return type->REAL32()?"real32":"real64"; }()));
            } else if (!ctx->expression()->literal()->FLOAT_LITERAL()) {
                // error: value is of wrong type
                errors.errs.push_back(WrongTypedValueError().from(current_stmt_context, ctx->expression(), [&type]() -> std::string { return type->REAL32()?"real32":"real64"; }()+";"+findStringType(ctx->expression()->literal())));
            }
        }
    } else {
        // error: invalid expression. Should be detected by the Lexer.
    }
    return antlrcpp::Any();
}