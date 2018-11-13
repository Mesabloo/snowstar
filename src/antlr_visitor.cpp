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

#include <antlr_visitor.hpp>

#if defined(_WIN32) || defined(_WIN64)
    #undef VOID
#endif

#include <filesystem>
#include <unordered_set>

#include <termcolor/termcolor.hpp>
#include <errors.hpp>

namespace utils {
    bool str_startswith(std::string const& src, std::string const& prefix) {
        return src.size() >= prefix.size() && src.substr(0, prefix.size()) == prefix;
    }
}


ANTLRVisitor::ANTLRVisitor(std::string const& file) : fileName{file} {
    std::filesystem::path path = std::filesystem::path{fileName};
    fileName = std::filesystem::canonical(path);

    #ifndef NDEBUG
        std::clog << termcolor::green << "   [i]   | Current file path: " << fileName << termcolor::reset << std::endl;
    #endif
}

antlrcpp::Any ANTLRVisitor::visitCompilationUnit(SnowStarParser::CompilationUnitContext* ctx) {
    #ifndef NDEBUG
        std::clog << termcolor::yellow << "   /!\\   | Starting semantically analysing..." << termcolor::reset << std::endl;
    #endif

    visitChildren(ctx);

    return antlrcpp::Any();
}

antlrcpp::Any ANTLRVisitor::visitWithDeclaration(SnowStarParser::WithDeclarationContext* ctx) {
    #ifndef NDEBUG
        std::clog << termcolor::green << "   [i]   | Visiting an alias declaration: " << ctx->getText() << termcolor::reset << std::endl;
    #endif

    lineContext = ctx;

    std::vector<Alias> definedAliases{};
    for (auto const& scope : scopedAliases) {
        for (auto const& alias : scope) {
            definedAliases.push_back(alias);
        }
    }
    auto it = std::find_if(definedAliases.begin(), definedAliases.end(), [&ctx] (Alias const& a) { return a.first == ctx->withName()->IDENTIFIER()->getText(); });

    if (it == definedAliases.end()) {
        if (ctx->theType()->IDENTIFIER()) {
            auto alias_it = std::find_if(definedAliases.begin(), definedAliases.end(), [&ctx] (Alias const& a) { return a.first == ctx->theType()->IDENTIFIER()->getText(); });
            std::string id{ctx->theType()->IDENTIFIER()->getText()};
            while (alias_it != definedAliases.end() && alias_it->second->IDENTIFIER()) {
                id = alias_it->second->IDENTIFIER()->getText();
                alias_it = std::find_if(definedAliases.begin(), definedAliases.end(), [&alias_it] (Alias const& a) { return a.first == alias_it->second->IDENTIFIER()->getText(); });
                #ifndef NDEBUG
                if (alias_it != definedAliases.end()) {
                    std::clog << termcolor::blue << "   :::   | Found alias with name `" << alias_it->second->getText() << "`." << termcolor::reset << std::endl;
                } else {
                    std::clog << termcolor::yellow << "   /!\\   | Could not find an alias with name `" << id << "`." << termcolor::reset << std::endl;
                }
                #endif
            }
            if (alias_it == definedAliases.end()) {
                // The alias referenced does not exist.
                UnknownIDError().print(fileName, ctx, lineContext, {id});
                errored = true;
            } else
                scopedAliases[scopedAliases.size()-1].emplace_back(ctx->withName()->getText(), alias_it->second);
        } else
            scopedAliases[scopedAliases.size()-1].emplace_back(ctx->withName()->getText(), ctx->theType());
    } else {
        // Well the alias already exists, so we need to throw an error.
        AlreadyExistingIDError().print(fileName, ctx, lineContext, {ctx->withName()->IDENTIFIER()->getText()});
        errored = true;
    }
    
    return antlrcpp::Any();
}

antlrcpp::Any ANTLRVisitor::visitVariableDeclaration(SnowStarParser::VariableDeclarationContext* ctx) {
    #ifndef NDEBUG
        std::clog << termcolor::green << "   [i]   | Visiting a variable declaration: " << ctx->getText() << termcolor::reset << std::endl;
    #endif

    if (auto v = ctx->variableInitializer()) {
        auto expr = visitVariableInitializer(v);

        // additional type checking for value/expression
    }

    return antlrcpp::Any();
}

antlrcpp::Any ANTLRVisitor::visitVariableInitializer(SnowStarParser::VariableInitializerContext* ctx) {
    #ifndef NDEBUG
        std::clog << termcolor::green << "   [i]   | Visiting a variable initialization: " << ctx->getText() << termcolor::reset << std::endl;
    #endif
    return antlrcpp::Any();
}

/*

antlrcpp::Any ANTLRVisitor::visitFunction(SnowStarParser::FunctionContext* ctx) {
    #ifndef NDEBUG
        std::clog << termcolor::green << "   [i]   | Visiting a function declaration..." << termcolor::reset << std::endl;
    #endif

    visitBlock(ctx->block());

    return antlrcpp::Any();
}

antlrcpp::Any ANTLRVisitor::visitBlock(SnowStarParser::BlockContext* ctx) {
    #ifndef NDEBUG
        std::clog << termcolor::green << "   [i]   | Visiting a block..." << termcolor::reset << std::endl;
    #endif

    visitChildren(ctx);
    return antlrcpp::Any();
}

antlrcpp::Any ANTLRVisitor::visitTopLevelStatement(SnowStarParser::TopLevelStatementContext* ctx) {
    #ifndef NDEBUG
        std::clog << termcolor::green << "   [i]   | Visiting a top-level statement..." << termcolor::reset << std::endl;
    #endif

    current_stmt_context = ctx;

    if (!ctx->eol) {
        errors.errs.push_back(MissingTokenError().from(file_name, current_stmt_context, ctx->getStop(), {"`;` at the end of statement,", ctx->getStop()->getText()}));
        return antlrcpp::Any();
    }

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

    if (ctx->error()) {
        visitError(ctx->error());
        return antlrcpp::Any();
    }

    if (!ctx->eol) {
        errors.errs.push_back(MissingTokenError().from(file_name, current_stmt_context, ctx->getStop(), {"`;` at the end of statement,", ctx->getStop()->getText()}));
        return antlrcpp::Any();
    }

    visitChildren(ctx);
    return antlrcpp::Any();
}

antlrcpp::Any ANTLRVisitor::visitExpression(SnowStarParser::ExpressionContext* ctx) {
    #ifndef NDEBUG
        std::clog << termcolor::green << "   [i]   | Visiting an expression..." << termcolor::reset << std::endl;
        std::clog << termcolor::magenta << "   ...   | " << ctx->getText() << termcolor::reset << std::endl;
    #endif

    ExprType ret{ExprType::VOID};

    auto getType = [] (ExprType const e) -> std::string {
        switch (e) {
            case ExprType::BOOL: return "bool";
            case ExprType::CHAR: return "char";
            case ExprType::INT8: return "int8";
            case ExprType::INT16: return "int16";
            case ExprType::INT32: return "int32";
            case ExprType::INT64: return "int64";
            case ExprType::REAL16: return "real16";
            case ExprType::REAL32: return "real32";
            case ExprType::REAL64: return "real64";
            case ExprType::VOID: return "void";
            default: return "";
        }
    };

    if (ctx->bop) {
        ExprType lhs = visitExpression(ctx->expression()[0]).as<ExprType>(),
                 rhs = visitExpression(ctx->expression()[1]).as<ExprType>();

        if (lhs != ExprType::VOID && rhs != ExprType::VOID) {
            std::unordered_set<std::string> bool_op{"||", "&&", "==", "!=", "<=", ">=", "<", ">"},
                                            integer_op{"|", "&", "^"},
                                            int_real_op{"+", "-", "*", "/"};
            if (bool_op.find(ctx->bop->getText()) != bool_op.end()) {
                if (ctx->bop->getText() == "||" || ctx->bop->getText() == "&&") {
                    if (lhs != ExprType::BOOL || rhs != ExprType::BOOL) {
                        bool lhs_typed = lhs == ExprType::BOOL;
                        errors.errs.push_back(WrongTypedValueError().from(file_name, current_stmt_context, ctx->expression()[lhs_typed?1:0], {"bool", getType(lhs_typed?rhs:lhs), "in expression"}));
                    }
                } else {
                    if (ctx->bop->getText() == "==" || ctx->bop->getText() == "!=") {
                        if ((lhs == ExprType::REAL16 || lhs == ExprType::REAL32 || lhs == ExprType::REAL64) && (rhs == ExprType::REAL16 || rhs == ExprType::REAL32 || rhs == ExprType::REAL64)) {
                            errors.warns.push_back(FloatingPointWarning().from(file_name, current_stmt_context, ctx->bop, {}));
                        } else if ((lhs == ExprType::CHAR) ^ (rhs == ExprType::CHAR)) {
                            bool lhs_typed = lhs == ExprType::CHAR;
                            errors.errs.push_back(WrongTypedValueError().from(file_name, current_stmt_context, ctx->expression()[lhs_typed?0:1], {getType(lhs_typed?rhs:lhs), getType(lhs_typed?lhs:rhs), "in expression"}));
                        } else if ((lhs == ExprType::BOOL) ^ (rhs == ExprType::BOOL)) {
                            bool lhs_typed = lhs == ExprType::BOOL;
                            errors.errs.push_back(WrongTypedValueError().from(file_name, current_stmt_context, ctx->expression()[lhs_typed?0:1], {getType(lhs_typed?rhs:lhs), getType(lhs_typed?lhs:rhs), "in expression"}));
                        } else if ((lhs == ExprType::INT8 || lhs == ExprType::INT16 || lhs == ExprType::INT32 || lhs == ExprType::INT64) ^ (rhs == ExprType::INT8 || rhs == ExprType::INT16 || rhs == ExprType::INT32 || rhs == ExprType::INT64)) {
                            bool lhs_typed = (lhs == ExprType::INT8 || lhs == ExprType::INT16 || lhs == ExprType::INT32 || lhs == ExprType::INT64);
                            errors.errs.push_back(WrongTypedValueError().from(file_name, current_stmt_context, ctx->expression()[lhs_typed?0:1], {getType(lhs_typed?rhs:lhs), getType(lhs_typed?lhs:rhs), "in expression"}));
                        } else if ((lhs == ExprType::REAL16 || lhs == ExprType::REAL32 || lhs == ExprType::REAL64) ^ (rhs == ExprType::REAL16 || rhs == ExprType::REAL32 || rhs == ExprType::REAL64)) {
                            bool lhs_typed = (lhs == ExprType::REAL16 || lhs == ExprType::REAL32 || lhs == ExprType::REAL64);
                            errors.errs.push_back(WrongTypedValueError().from(file_name, current_stmt_context, ctx->expression()[lhs_typed?0:1], {getType(lhs_typed?rhs:lhs), getType(lhs_typed?lhs:rhs), "in expression"}));
                        }
                    } else {
                        if (lhs == ExprType::BOOL || rhs == ExprType::BOOL) {
                            bool lhs_typed = lhs == ExprType::BOOL;
                            errors.errs.push_back(InvalidComparisonTypeError().from(file_name, current_stmt_context, ctx->expression()[lhs_typed?0:1], {getType(lhs_typed?lhs:rhs)}));
                        } else if ((lhs == ExprType::CHAR) ^ (rhs == ExprType::CHAR)) {
                            bool lhs_typed = lhs == ExprType::CHAR;
                            errors.errs.push_back(WrongTypedValueError().from(file_name, current_stmt_context, ctx->expression()[lhs_typed?0:1], {getType(lhs_typed?rhs:lhs), getType(lhs_typed?lhs:rhs), "in expression"}));
                        } else if ((lhs == ExprType::INT8 || lhs == ExprType::INT16 || lhs == ExprType::INT32 || lhs == ExprType::INT64) ^ (rhs == ExprType::INT8 || rhs == ExprType::INT16 || rhs == ExprType::INT32 || rhs == ExprType::INT64)) {
                            bool lhs_typed = (lhs == ExprType::INT8 || lhs == ExprType::INT16 || lhs == ExprType::INT32 || lhs == ExprType::INT64);
                            errors.errs.push_back(WrongTypedValueError().from(file_name, current_stmt_context, ctx->expression()[lhs_typed?0:1], {getType(lhs_typed?rhs:lhs), getType(lhs_typed?lhs:rhs), "in expression"}));
                        } else if ((lhs == ExprType::REAL16 || lhs == ExprType::REAL32 || lhs == ExprType::REAL64) ^ (rhs == ExprType::REAL16 || rhs == ExprType::REAL32 || rhs == ExprType::REAL64)) {
                            bool lhs_typed = (lhs == ExprType::REAL16 || lhs == ExprType::REAL32 || lhs == ExprType::REAL64);
                            errors.errs.push_back(WrongTypedValueError().from(file_name, current_stmt_context, ctx->expression()[lhs_typed?0:1], {getType(lhs_typed?rhs:lhs), getType(lhs_typed?lhs:rhs), "in expression"}));
                        }
                    }
                }
                ret = ExprType::BOOL;
            }
            if (integer_op.find(ctx->bop->getText()) != integer_op.end()) {
                if ((lhs == ExprType::INT8 || lhs == ExprType::INT16 || lhs == ExprType::INT32 || lhs == ExprType::INT64) && (rhs == ExprType::INT8 || rhs == ExprType::INT16 || rhs == ExprType::INT32 || rhs == ExprType::INT64)) {
                    if (lhs == ExprType::INT64 || rhs == ExprType::INT64) {
                        ret = ExprType::INT64;
                    } else if (lhs == ExprType::INT32 || rhs == ExprType::INT32) {
                        ret = ExprType::INT32;
                    } else if (lhs == ExprType::INT16 || rhs == ExprType::INT16) {
                        ret = ExprType::INT16;
                    } else {
                        ret = ExprType::INT8;
                    }
                } else {
                    bool lhs_typed = (lhs != ExprType::INT8 && lhs != ExprType::INT16 && lhs != ExprType::INT32 && lhs != ExprType::INT64);
                    errors.errs.push_back(WrongTypedValueError().from(file_name, current_stmt_context, lhs_typed?ctx->expression()[0]:ctx->expression()[1], {getType(lhs_typed?rhs:lhs), getType(lhs_typed?lhs:rhs), "in expression"}));
                }
            }
            if (int_real_op.find(ctx->bop->getText()) != int_real_op.end()) {
                if ((lhs == ExprType::REAL64 || lhs == ExprType::REAL32 || lhs == ExprType::REAL16) && (rhs == ExprType::REAL64 || rhs == ExprType::REAL32 || rhs == ExprType::REAL16)) {
                    if (lhs == ExprType::REAL64 || rhs == ExprType::REAL64)
                        ret = ExprType::REAL64;
                    else if (lhs == ExprType::REAL32 || rhs == ExprType::REAL32)
                        ret = ExprType::REAL32;
                    else
                        ret = ExprType::REAL16;
                } else if ((lhs == ExprType::INT64 || lhs == ExprType::INT32 || lhs == ExprType::INT16 || lhs == ExprType::INT8) && (rhs == ExprType::INT64 || rhs == ExprType::INT32 || rhs == ExprType::INT16 || rhs == ExprType::INT8)) {
                    if (lhs == ExprType::INT64 || rhs == ExprType::INT64) {
                        ret = ExprType::INT64;
                    } else if (lhs == ExprType::INT32 || rhs == ExprType::INT32) {
                        ret = ExprType::INT32;
                    } else if (lhs == ExprType::INT16 || rhs == ExprType::INT16) {
                        ret = ExprType::INT16;
                    } else {
                        ret = ExprType::INT8;
                    }
                } else {
                    bool lhs_typed = (lhs != ExprType::REAL64 && lhs != ExprType::REAL32 && lhs != ExprType::REAL16 && lhs != ExprType::INT64 && lhs != ExprType::INT32 && lhs != ExprType::INT16 && lhs != ExprType::INT8);
                    errors.errs.push_back(WrongTypedValueError().from(file_name, current_stmt_context, lhs_typed?ctx->expression()[0]:ctx->expression()[1], {getType(lhs_typed?rhs:lhs), getType(lhs_typed?lhs:rhs), "in expression"}));
                }
            }
        }
    } else if (ctx->uop) {
        ExprType expr = visitExpression(ctx->expression()[0]).as<ExprType>();

        if (expr != ExprType::VOID) {
            if (ctx->uop->getText() == "~") {
                if (expr != ExprType::INT64 && expr != ExprType::INT32 && expr != ExprType::INT16 && expr != ExprType::INT8) {
                    errors.errs.push_back(WrongTypedValueError().from(file_name, current_stmt_context, ctx->expression()[0], {"int32", getType(expr), "in expression"}));
                } else {
                    ret = expr;
                }
            } else if (ctx->uop->getText() == "+" || ctx->uop->getText() == "-") {
                if (expr != ExprType::INT64 && expr != ExprType::INT32 && expr != ExprType::INT16 && expr != ExprType::INT8 && expr != ExprType::REAL16 && expr != ExprType::REAL32 && expr != ExprType::REAL64) {
                    errors.errs.push_back(WrongTypedValueError().from(file_name, current_stmt_context, ctx->expression()[0], {"int32", getType(expr), "in expression"}));
                } else {
                    ret = expr;
                }
            } else {
                if (expr != ExprType::BOOL) {
                    errors.errs.push_back(WrongTypedValueError().from(file_name, current_stmt_context, ctx->expression()[0], {"bool", getType(expr), "in expression"}));
                }
                ret = ExprType::BOOL;
            }
        }
    } else {
        if (ctx->literal()) {
            auto findType = [] (SnowStarParser::LiteralContext* ct) -> ExprType {
                std::string val{ct->getText()};
                if (ct->BOOL_LITERAL()) return ExprType::BOOL;
                if (ct->CHAR_LITERAL()) return ExprType::CHAR;
                if (ct->FLOAT_LITERAL()) {
                    double d = std::stod(val);
                    if (d > std::numeric_limits<float>::max() || d < std::numeric_limits<float>::min()) return ExprType::REAL64;
                    else if (d < std::numeric_limits<float>::max()/2) return ExprType::REAL16;
                    else return ExprType::REAL32;
                }
                if (ct->DECIMAL_LITERAL()) {
                    int64_t i = std::stoll(val);
                    if (i < std::numeric_limits<int8_t>::max() && i > std::numeric_limits<int8_t>::min()) return ExprType::INT8;
                    else if (i < std::numeric_limits<int16_t>::max() && i > std::numeric_limits<int16_t>::min()) return ExprType::INT16;
                    else if (i < std::numeric_limits<int32_t>::max() && i > std::numeric_limits<int32_t>::min()) return ExprType::INT32;
                    else return ExprType::INT32;
                }
                return ExprType::VOID;
            };
            ret = findType(ctx->literal());
        } else if (ctx->IDENTIFIER()) {
            auto it = std::find_if(declared.begin(), declared.end(), [&ctx] (Var const& v) { return ctx->IDENTIFIER()->getText() == std::get<0>(v); });
            if (it == declared.end()) {
                errors.errs.push_back(UndeclaredVariableError().from(file_name, current_stmt_context, ctx->IDENTIFIER()->getSymbol(), {ctx->IDENTIFIER()->getSymbol()->getText()}));
            } else {
                if (!std::get<2>(*it)) {
                    errors.errs.push_back(UndefinedVariableError().from(file_name, current_stmt_context, ctx->IDENTIFIER()->getSymbol(), {ctx->IDENTIFIER()->getText()}));
                } else {
                    auto type = std::get<1>(*it);
                    if (type->INTEGER16() || type->INTEGER32() || type->INTEGER64() || type->INTEGER8()) {
                        if (type->INTEGER8())
                            ret = ExprType::INT8;
                        else if (type->INTEGER16())
                            ret = ExprType::INT16;
                        else if (type->INTEGER32())
                            ret = ExprType::INT32;
                        else
                            ret = ExprType::INT64;
                    } else if (type->REAL16() || type->REAL32() || type->REAL64()) {
                        if (type->REAL16()) {
                            ret = ExprType::REAL16;
                        } else if (type->REAL32()) {
                            ret = ExprType::REAL32;
                        } else
                            ret = ExprType::REAL64;
                    } else if (type->CHAR()) {
                        ret = ExprType::CHAR;
                    } else if (type->BOOLEAN()) {
                        ret = ExprType::BOOL;
                    }
                }
            }
        } else {
            ret = visitExpression(ctx->expression()[0]).as<ExprType>();
            if (ret == ExprType::VOID)
                errors.errs.push_back(MissingTokenError().from(file_name, current_stmt_context, ctx->lparen, {"expression", ctx->lparen->getText()}));
        }
    }
    
    return ret;
}

antlrcpp::Any ANTLRVisitor::visitDeclare(SnowStarParser::DeclareContext* ctx) {
    #ifndef NDEBUG
        std::clog << termcolor::green << "   [i]   | Visiting a declaration..." << termcolor::reset << std::endl;
    #endif

    if (!ctx->IDENTIFIER()) return antlrcpp::Any();

    if (ctx->type()->VOID()) {
        errors.errs.push_back(InvalidDeclaringTypeError().from(file_name, current_stmt_context, ctx->type()->VOID()->getSymbol(), {"void"}));
        return ctx->type();
    }
    
    auto it = std::find_if(declared.begin(), declared.end(), [&ctx] (Var const& var) { return std::get<0>(var) == ctx->IDENTIFIER()->getText(); });
    #ifndef NDEBUG
        std::clog << termcolor::green << std::boolalpha << "   [i]   | >> " << ctx->IDENTIFIER()->getText() << " is already declared: " << (it != declared.end()) << std::noboolalpha << termcolor::reset << std::endl;
    #endif
    if (it != declared.end()) {
        #ifndef NDEBUG
            std::clog << termcolor::magenta << "   ...   | Variable " << ctx->IDENTIFIER()->getText() << " redeclared." << termcolor::reset << std::endl;
        #endif
        errors.errs.push_back(RedeclaredVariableError().from(file_name, current_stmt_context, ctx->IDENTIFIER()->getSymbol(), {ctx->IDENTIFIER()->getText(), std::to_string(std::get<3>(*it).first), std::to_string(std::get<3>(*it).second+1)}));
        return nullptr;
    }

    if (ctx->type()->IDENTIFIER()) {
        auto it1 = std::find_if(aliases.begin(), aliases.end(), [&ctx] (Alias const& alias) { return std::get<0>(alias) == ctx->type()->IDENTIFIER()->getText(); });
        if (it1 == aliases.end()) {
            errors.errs.push_back(InvalidDeclaringTypeError().from(file_name, current_stmt_context, ctx->type()->IDENTIFIER()->getSymbol(), {ctx->type()->getText()}));
            return nullptr;
        }

        declared.push_back(std::make_tuple(ctx->IDENTIFIER()->getText(), it1->second, false, std::make_pair(ctx->IDENTIFIER()->getSymbol()->getLine(), ctx->IDENTIFIER()->getSymbol()->getCharPositionInLine())));
        return it1->second;
    } else
        declared.push_back(std::make_tuple(ctx->IDENTIFIER()->getText(), ctx->type(), false, std::make_pair(ctx->IDENTIFIER()->getSymbol()->getLine(), ctx->IDENTIFIER()->getSymbol()->getCharPositionInLine())));

    return ctx->type();
}

antlrcpp::Any ANTLRVisitor::visitDefine(SnowStarParser::DefineContext* ctx) {
    #ifndef NDEBUG
        std::clog << termcolor::green << "   [i]   | Visiting a definition..." << termcolor::reset << std::endl;
    #endif

    antlrcpp::Any t = visitDeclare(ctx->declare());

    if (!t.is<Decl>()) return antlrcpp::Any();
    Decl type = t.as<Decl>();
    if (type->VOID()) return antlrcpp::Any();

    auto getType = [] (ExprType const e) -> std::string {
        switch (e) {
            case ExprType::BOOL: return "bool";
            case ExprType::CHAR: return "char";
            case ExprType::INT8: return "int8";
            case ExprType::INT16: return "int16";
            case ExprType::INT32: return "int32";
            case ExprType::INT64: return "int64";
            case ExprType::REAL16: return "real16";
            case ExprType::REAL32: return "real32";
            case ExprType::REAL64: return "real64";
            case ExprType::VOID: return "void";
            default: return "";
        }
    };

    ExprType res = visitExpression(ctx->expression()).as<ExprType>();
    if (res == ExprType::VOID) return antlrcpp::Any();

    if (type->BOOLEAN()) {
        if (res != ExprType::BOOL) {
            // type mismatch
            errors.errs.push_back(WrongTypedValueError().from(file_name, current_stmt_context, ctx->expression(), {"bool", getType(res), "in variable declaration"}));
        }
    } else if (type->CHAR()) {
        if (res != ExprType::CHAR) {
            // type mismatch
            errors.errs.push_back(WrongTypedValueError().from(file_name, current_stmt_context, ctx->expression(), {"char", getType(res), "in variable declaration"}));
        }
    } else if (type->INTEGER8() || type->INTEGER16() || type->INTEGER32() || type->INTEGER64()) {
        if (res != ExprType::INT8 && res != ExprType::INT16 && res != ExprType::INT32 && res != ExprType::INT64 && res != ExprType::REAL16 && res != ExprType::REAL32 && res != ExprType::REAL64) {
            // type mismatch
            errors.errs.push_back(WrongTypedValueError().from(file_name, current_stmt_context, ctx->expression(), {[&type]() -> std::string { return type->INTEGER8()?"int8":type->INTEGER16()?"int16":type->INTEGER32()?"int32":"int64"; }(), getType(res), "in variable declaration"}));
        } else if (res == ExprType::REAL16 || res == ExprType::REAL32 || res == ExprType::REAL64) {
            // warning narrowing conversion
            errors.warns.push_back(ImplicitCastWarning().from(file_name, current_stmt_context, ctx->expression(), {getType(res), [&type]() -> std::string { return type->INTEGER8()?"int8":type->INTEGER16()?"int16":type->INTEGER32()?"int32":"int64"; }()}));
        }
    } else if (type->REAL16() || type->REAL32() || type->REAL64()) {
        if (res != ExprType::INT8 && res != ExprType::INT16 && res != ExprType::INT32 && res != ExprType::INT64 && res != ExprType::REAL16 && res != ExprType::REAL32 && res != ExprType::REAL64) {
            errors.errs.push_back(WrongTypedValueError().from(file_name, current_stmt_context, ctx->expression(), {[&type]() -> std::string { return type->REAL32()?"real32":"real64"; }(), getType(res), "in variable declaration"}));
        }
    }

    auto const& it = std::find_if(declared.begin(), declared.end(), [&ctx] (Var const& v) { return std::get<0>(v) == ctx->declare()->IDENTIFIER()->getText(); });
    auto& b = std::get<2>(*it);
    b = true;

    return antlrcpp::Any();
}*/