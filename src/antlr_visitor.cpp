#include <antlr_visitor.hpp>

#if defined(_WIN32) || defined(_WIN64)
    #undef VOID
#endif

#include <filesystem>

#include <termcolor/termcolor.hpp>
#include <parser_errors.hpp>

#define ERRORED (!errors.errs.empty() || !errors.warns.empty())

namespace utils {
    bool str_startswith(std::string const& src, std::string const& prefix) {
        return src.size() >= prefix.size() && src.substr(0, prefix.size()) == prefix;
    }
}

ANTLRVisitor::ANTLRVisitor(std::string const& file) : file_name{file} {
    std::filesystem::path path = std::filesystem::path{file_name};
    file_name = std::filesystem::canonical(path);

    #ifndef NDEBUG
        std::clog << termcolor::green << "   [i]   | Current file path: " << file_name << termcolor::reset << std::endl;
    #endif
}

antlrcpp::Any ANTLRVisitor::visitCompilationUnit(SnowStarParser::CompilationUnitContext* ctx) {
    visitChildren(ctx);

    return antlrcpp::Any();
}

antlrcpp::Any ANTLRVisitor::visitStatement(SnowStarParser::StatementContext* ctx) {
    #ifndef NDEBUG
        std::clog << termcolor::green << "   [i]   | Visiting a statement..." << termcolor::reset << std::endl;
    #endif

    current_stmt_context = ctx;

    #ifndef NDEBUG
        std::clog << termcolor::magenta << "   ...   | Current line: " <<
            ctx->getStart()->getInputStream()->getText(antlr4::misc::Interval{ctx->getStart()->getStartIndex(), ctx->getStop()->getStopIndex()})
            << termcolor::reset << std::endl;
    #endif

    if (!ctx->eol) {
        errors.errs.push_back(MissingTokenError().from(file_name, current_stmt_context, ctx->getStop(), "`;` at the end of statement,~"+ctx->getStop()->getText()));
        return antlrcpp::Any();
    }

    visitChildren(ctx);
    return antlrcpp::Any();
}

antlrcpp::Any ANTLRVisitor::visitExpression(SnowStarParser::ExpressionContext* ctx) {
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
    return 0;
}

antlrcpp::Any ANTLRVisitor::visitDeclare(SnowStarParser::DeclareContext* ctx) {
    #ifndef NDEBUG
        std::clog << termcolor::green << "   [i]   | Visiting a declaration..." << termcolor::reset << std::endl;
    #endif

    if (!ctx->IDENTIFIER()) return antlrcpp::Any();

    if (ctx->type()->VOID()) {
        errors.errs.push_back(InvalidDeclaringTypeError().from(file_name, current_stmt_context, ctx->type()->VOID()->getSymbol(), "void"));
        return ctx->type();
    }
    
    auto it = std::find_if(declared.begin(), declared.end(), [&ctx] (Var const& var) { return std::get<0>(var) == ctx->IDENTIFIER()->getText(); });
    #ifndef NDEBUG
        std::clog << termcolor::green << std::boolalpha << "   [i]   | >> " << ctx->IDENTIFIER()->getText() << " is already declared: " << (it != declared.end()) << std::noboolalpha << termcolor::reset << std::endl;
    #endif
    if (it != declared.end()) {
        // throw an error here : redeclared variable
        #ifndef NDEBUG
            std::clog << termcolor::magenta << "   ...   | Variable " << ctx->IDENTIFIER()->getText() << " redeclared." << termcolor::reset << std::endl;
        #endif
        errors.errs.push_back(RedeclaredVariableError().from(file_name, current_stmt_context, ctx->IDENTIFIER()->getSymbol(), ctx->IDENTIFIER()->getText()+"~"+std::to_string(std::get<2>(*it).first)+"~"+std::to_string(std::get<2>(*it).second+1)));
        return nullptr;
    }

    if (ctx->type()->IDENTIFIER()) {
        auto it1 = std::find_if(aliases.begin(), aliases.end(), [&ctx] (Alias const& alias) { return std::get<0>(alias) == ctx->type()->IDENTIFIER()->getText(); });
        if (it1 == aliases.end()) {
            errors.errs.push_back(InvalidDeclaringTypeError().from(file_name, current_stmt_context, ctx->type()->IDENTIFIER()->getSymbol(), ctx->type()->getText()));
            return nullptr;
        }

        declared.push_back(std::make_tuple(ctx->IDENTIFIER()->getText(), it1->second, std::make_pair(ctx->IDENTIFIER()->getSymbol()->getLine(), ctx->IDENTIFIER()->getSymbol()->getCharPositionInLine())));
        return it1->second;
    } else
        declared.push_back(std::make_tuple(ctx->IDENTIFIER()->getText(), ctx->type(), std::make_pair(ctx->IDENTIFIER()->getSymbol()->getLine(), ctx->IDENTIFIER()->getSymbol()->getCharPositionInLine())));

    return ctx->type();
}

antlrcpp::Any ANTLRVisitor::visitDeclareNoID(SnowStarParser::DeclareNoIDContext*) {
    return -1;
}

antlrcpp::Any ANTLRVisitor::visitDefine(SnowStarParser::DefineContext* ctx) {
    #ifndef NDEBUG
        std::clog << termcolor::green << "   [i]   | Visiting a definition..." << termcolor::reset << std::endl;
    #endif

    antlrcpp::Any t;
    if (ctx->declareNoID())
        t = visitDeclareNoID(ctx->declareNoID());
    else
        t = visitDeclare(ctx->declare());

    if (t.is<int>() || !ctx->declare()->IDENTIFIER()) {
        errors.errs.push_back(MissingTokenError().from(file_name, current_stmt_context, (ctx->declare()?ctx->declare()->type()->getStart():ctx->declareNoID()->type()->getStart()), "identifier in variable declaration~"+(ctx->declare()?ctx->declare()->type()->getStart()->getText():ctx->declareNoID()->type()->getStart()->getText())));
        return antlrcpp::Any();
    }

    if (!ctx->eop) {
        errors.errs.push_back(MissingTokenError().from(file_name, current_stmt_context, ctx->declare()->IDENTIFIER()->getSymbol(), "'=' token in variable declaration~"+ctx->declare()->IDENTIFIER()->getText()));
        return antlrcpp::Any();
    }

    if (!ctx->expression()) {
        errors.errs.push_back(MissingTokenError().from(file_name, current_stmt_context, ctx->eop, "value in variable declaration~"+ctx->eop->getText()));
        return antlrcpp::Any();
    }

    if (!t.is<Decl>()) return antlrcpp::Any();
    Decl type = t.as<Decl>();
    if (type->VOID()) return antlrcpp::Any();

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
            else return "int64";
        }
        return "void";
    };

    if (auto id = ctx->expression()->IDENTIFIER()) {
        auto it = std::find_if(declared.begin(), declared.end(), [&] (Var const& v) { return id->getText() == std::get<0>(v); });
        if (it == declared.end()) {
            // throw error
            errors.errs.push_back(UndeclaredVariableError().from(file_name, current_stmt_context, id->getSymbol(), id->getSymbol()->getText()));
            return antlrcpp::Any();
        }
        if (type->BOOLEAN() && std::get<1>(*it)->getText() != "bool") {
            // inconsistent types bool and not bool
            errors.errs.push_back(WrongTypedValueError().from(file_name, current_stmt_context, ctx->expression()->getStart(), "bool~"+std::get<1>(*it)->getText()));
            return antlrcpp::Any();
        }
        if (type->CHAR() && std::get<1>(*it)->getText() != "char") {
            // inconsistent types char and not char
            errors.errs.push_back(WrongTypedValueError().from(file_name, current_stmt_context, ctx->expression(), "char~"+std::get<1>(*it)->getText()));
            return antlrcpp::Any();
        }
        if ((type->INTEGER8() || type->INTEGER16() || type->INTEGER32() || type->INTEGER64())) {
            if (utils::str_startswith(std::get<1>(*it)->getText(), "real")) {
                // implicit cast
                errors.warns.push_back(ImplicitCastWarning().from(file_name, current_stmt_context, ctx->expression(), std::get<1>(*it)->getText()+"~"+[&type]() -> std::string { return type->INTEGER8()?"int8":type->INTEGER16()?"int16":type->INTEGER32()?"int32":"int64"; }()));
            } else if (!utils::str_startswith(std::get<1>(*it)->getText(), "int")) {
                // inconsistent types
                errors.errs.push_back(WrongTypedValueError().from(file_name, current_stmt_context, ctx->expression(), [&type]() -> std::string { return type->INTEGER8()?"int8":type->INTEGER16()?"int16":type->INTEGER32()?"int32":"int64"; }()+"~"+std::get<1>(*it)->getText()));
                return antlrcpp::Any();
            }
        }
        if ((type->REAL32() || type->REAL64() || type->REAL16()) && !utils::str_startswith(std::get<1>(*it)->getText(), "int") && !utils::str_startswith(std::get<1>(*it)->getText(), "real")) {
            errors.errs.push_back(WrongTypedValueError().from(file_name, current_stmt_context, ctx->expression(), [&type]() -> std::string { return type->REAL32()?"real32":"real64"; }()+"~"+std::get<1>(*it)->getText()));
            return antlrcpp::Any();
        }
    } else if (ctx->expression()->literal()) {
        if (type->BOOLEAN() && !ctx->expression()->literal()->BOOL_LITERAL()) {
            // error: value is of wrong type
            errors.errs.push_back(WrongTypedValueError().from(file_name, current_stmt_context, ctx->expression()->getStart(), "bool~"+findStringType(ctx->expression()->literal())));
            return antlrcpp::Any();
        }
        if (type->CHAR() && !ctx->expression()->literal()->CHAR_LITERAL()) {
            // error: value is of wrong type
            errors.errs.push_back(WrongTypedValueError().from(file_name, current_stmt_context, ctx->expression(), "char~"+findStringType(ctx->expression()->literal())));
            return antlrcpp::Any();
        }
        if ((type->INTEGER8() || type->INTEGER16() || type->INTEGER32() || type->INTEGER64())) {
            if (ctx->expression()->literal()->FLOAT_LITERAL()) {
                // implicit cast
                errors.warns.push_back(ImplicitCastWarning().from(file_name, current_stmt_context, ctx->expression(), findStringType(ctx->expression()->literal())+"~"+[&type]() -> std::string { return type->INTEGER8()?"int8":type->INTEGER16()?"int16":type->INTEGER32()?"int32":"int64"; }()));
            } else if (!ctx->expression()->literal()->DECIMAL_LITERAL()/* && !ctx->expression()->literal()->HEX_LITERAL() && !ctx->expression()->literal()->BIN_LITERAL() */) {
                // error: value is of wrong type
                errors.errs.push_back(WrongTypedValueError().from(file_name, current_stmt_context, ctx->expression(), [&type]() -> std::string { return type->INTEGER8()?"int8":type->INTEGER16()?"int16":type->INTEGER32()?"int32":"int64"; }()+"~"+findStringType(ctx->expression()->literal())));
                return antlrcpp::Any();
            }
            
        }
        if ((type->REAL32() || type->REAL64() || type->REAL16()) && !ctx->expression()->literal()->DECIMAL_LITERAL() && !ctx->expression()->literal()->FLOAT_LITERAL()/* && !ctx->expression()->literal()->HEX_LITERAL() && !ctx->expression()->literal()->BIN_LITERAL() */) {
            errors.errs.push_back(WrongTypedValueError().from(file_name, current_stmt_context, ctx->expression(), [&type]() -> std::string { return type->REAL32()?"real32":"real64"; }()+"~"+findStringType(ctx->expression()->literal())));
            return antlrcpp::Any();
        }
    } else {
        // error: invalid expression. Should be detected by the Lexer.
    }

    return antlrcpp::Any();
}

antlrcpp::Any ANTLRVisitor::visitAlias(SnowStarParser::AliasContext* ctx) {
    #ifndef NDEBUG
        std::clog << termcolor::green << "   [i]   | Visiting an alias..." << termcolor::reset << std::endl;
    #endif

    if (!ctx->IDENTIFIER()) {
        errors.errs.push_back(MissingTokenError().from(file_name, current_stmt_context, ctx->with, "identifier in type aliasing~"+ctx->with->getText()));
        return antlrcpp::Any();
    }
    if (!ctx->eop) {
        errors.errs.push_back(MissingTokenError().from(file_name, current_stmt_context, ctx->IDENTIFIER()->getSymbol(), "`=` token in type aliasing~"+ctx->IDENTIFIER()->getSymbol()->getText()));
        return antlrcpp::Any();
    }
    if (!ctx->type()) {
        // missing type;
        errors.errs.push_back(MissingTokenError().from(file_name, current_stmt_context, ctx->eop, "type in type aliasing~"+ctx->eop->getText()));
        return antlrcpp::Any();
    }

    auto decl_it = std::find_if(declared.begin(), declared.end(), [&ctx](Var const& v) { return std::get<0>(v) == ctx->IDENTIFIER()->getText(); });
    auto alias_it = std::find_if(aliases.begin(), aliases.end(), [&ctx](Alias const& a) { return a.first == ctx->IDENTIFIER()->getText(); });
    if (decl_it != declared.end() || alias_it != aliases.end()) {
        // name already exists, we can't take it.
        errors.errs.push_back(AlreadyExistingIDError().from(file_name, current_stmt_context, ctx->IDENTIFIER()->getSymbol(), ctx->IDENTIFIER()->getText()));
        return antlrcpp::Any();
    }

    #ifndef NDEBUG
        std::clog << termcolor::green << "   [i]   | Alias name is composed?=" << std::boolalpha << (ctx->type()->IDENTIFIER()) << std::noboolalpha << "." << termcolor::reset << std::endl;
    #endif
    if (ctx->type()->IDENTIFIER()) {
        alias_it = std::find_if(aliases.begin(), aliases.end(), [&ctx] (Alias const& a) { return a.first == ctx->type()->IDENTIFIER()->getText(); });
        while (alias_it != aliases.end() && alias_it->second->IDENTIFIER()) {
            #ifndef NDEBUG
                std::string id = alias_it->second->IDENTIFIER()->getText();
            #endif  
            alias_it = std::find_if(aliases.begin(), aliases.end(), [&alias_it] (Alias const& a) { return a.first == alias_it->second->IDENTIFIER()->getText(); });
            #ifndef NDEBUG
                if (alias_it != aliases.end()) {
                    std::clog << termcolor::blue << "   :::   | Found alias with name `" << alias_it->second->getText() << "`." << termcolor::reset << std::endl;
                } else {
                    std::clog << termcolor::yellow << "   /!\\   | Could not find an alias with name `" << id << "`." << termcolor::reset << std::endl;
                }
            #endif
        }
        if (alias_it == aliases.end()) {
            errors.errs.push_back(UnknownIDError().from(file_name, current_stmt_context, ctx->type()->IDENTIFIER()->getSymbol(), ctx->type()->IDENTIFIER()->getText()));
            return nullptr;
        }

        aliases.push_back(std::make_pair(ctx->IDENTIFIER()->getText(), alias_it->second));
    } else
        aliases.push_back(std::make_pair(ctx->IDENTIFIER()->getText(), ctx->type()));

    return 0;
}