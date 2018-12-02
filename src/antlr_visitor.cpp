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

#include <filesystem>
#include <unordered_set>

#include <termcolor/termcolor.hpp>
#include <errors.hpp>

#if defined(_WIN32) || defined(_WIN64)
#	undef VOID
#endif

namespace utils {
    inline bool str_startswith(std::string const& src, std::string const& prefix) {
        return src.size() >= prefix.size() && src.substr(0, prefix.size()) == prefix;
    }
}


ANTLRVisitor::ANTLRVisitor(std::string const& file) : fileName{file} {
    std::filesystem::path path = std::filesystem::path{fileName};
    fileName = std::filesystem::canonical(path).string();

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
                UnknownIDError().print(fileName, ctx, lineContext, {id}, {}, functionContext);
                errored = true;
            } else
                scopedAliases[scopedAliases.size()-1].emplace_back(ctx->withName()->getText(), alias_it->second);
        } else
            scopedAliases[scopedAliases.size()-1].emplace_back(ctx->withName()->getText(), ctx->theType());
    } else {
        // Well the alias already exists, so we need to throw an error.
        AlreadyExistingIDError().print(fileName, ctx, lineContext, {ctx->withName()->IDENTIFIER()->getText()}, {}, functionContext);
        errored = true;
    }
    
    return antlrcpp::Any();
}

antlrcpp::Any ANTLRVisitor::visitVariableDeclaration(SnowStarParser::VariableDeclarationContext* ctx) {
    #ifndef NDEBUG
        std::clog << termcolor::green << "   [i]   | Visiting a variable declaration: " << ctx->getText() << termcolor::reset << std::endl;
    #endif

    lineContext = ctx;

    if (ctx->theType()->builtinTypes() && ctx->theType()->builtinTypes()->VOID()) {
        InvalidDeclaringTypeError().print(fileName, lineContext, ctx->theType()->builtinTypes()->VOID()->getSymbol(), {"void"}, {}, functionContext);
        return ctx->theType();
    }

    std::vector<Declaration> declaredVariables;
    for (auto const& scope : scopedDeclarations) {
        for (auto const& decl : scope) {
            declaredVariables.push_back(decl);
        }
    }
    
    auto it = std::find_if(declaredVariables.begin(), declaredVariables.end(), [&ctx] (Declaration const& var) { return std::get<0>(var) == ctx->variableName()->IDENTIFIER()->getText(); });
    #ifndef NDEBUG
        std::clog << termcolor::green << std::boolalpha << "   [i]   | >> " << ctx->variableName()->IDENTIFIER()->getText() << " is already declared: " << (it != declaredVariables.end()) << std::noboolalpha << termcolor::reset << std::endl;
    #endif
    if (it != declaredVariables.end()) {
        #ifndef NDEBUG
            std::clog << termcolor::magenta << "   ...   | Variable " << ctx->variableName()->IDENTIFIER()->getText() << " redeclared." << termcolor::reset << std::endl;
        #endif
        RedeclaredVariableError().print(fileName, lineContext, ctx->variableName()->IDENTIFIER()->getSymbol(), {ctx->variableName()->IDENTIFIER()->getText(), std::to_string(std::get<3>(*it).first), std::to_string(std::get<3>(*it).second+1)}, {"changing the name"}, functionContext);
        errored = true;
    } else {
        auto type = ctx->theType();
        Declaration* d = nullptr;

        if (type->IDENTIFIER()) {
            std::vector<Alias> definedAliases{};
            for (auto const& scope : scopedAliases) {
                for (auto const& alias : scope) {
                    definedAliases.push_back(alias);
                }
            }

            auto it1 = std::find_if(definedAliases.begin(), definedAliases.end(), [&type] (Alias const& alias) { return std::get<0>(alias) == type->IDENTIFIER()->getText(); });
            if (it1 == definedAliases.end()) {
                InvalidDeclaringTypeError().print(fileName, lineContext, type->IDENTIFIER()->getSymbol(), {type->getText()}, {}, functionContext);
                errored = true;
                return antlrcpp::Any();
            } else {
                d = &scopedDeclarations.rbegin()->emplace_back(ctx->variableName()->IDENTIFIER()->getText(), it1->second, false, std::make_pair(ctx->variableName()->IDENTIFIER()->getSymbol()->getLine(), ctx->variableName()->IDENTIFIER()->getSymbol()->getCharPositionInLine()));
                type = it1->second;
            }
        } else
            d = &scopedDeclarations.rbegin()->emplace_back(ctx->variableName()->IDENTIFIER()->getText(), ctx->theType(), false, std::make_pair(ctx->variableName()->IDENTIFIER()->getSymbol()->getLine(), ctx->variableName()->IDENTIFIER()->getSymbol()->getCharPositionInLine()));

        if (auto v = ctx->variableInitializer()) {
            auto expr = visitVariableInitializer(v).as<ExprType>();

            // additional type checking for value/expression
            if (expr == ExprType::VOID) {
                // error: invalid type (shouldn't be possible, unless casted)
            } else {
                if (expr != toType(type->builtinTypes())) {
                    WrongTypedValueError().print(fileName, lineContext, ctx->variableInitializer()->expression(), {getType(toType(ctx->theType()->builtinTypes())), getType(expr), "in variable initialization"}, {}, functionContext);
                    errored = true;
                }
            }

            std::get<2>(*d) = true;
        } else if (functionContext.size() == 0) {
            UndefinedGlobalError().print(fileName, lineContext, ctx->variableName(), {ctx->variableName()->IDENTIFIER()->getText()}, {}, functionContext);
            errored = true;
            scopedDeclarations.rbegin()->pop_back();
        }
    }

    return antlrcpp::Any();
}

antlrcpp::Any ANTLRVisitor::visitVariableInitializer(SnowStarParser::VariableInitializerContext* ctx) {
    #ifndef NDEBUG
        std::clog << termcolor::green << "   [i]   | Visiting a variable initialization: " << ctx->getText() << termcolor::reset << std::endl;
    #endif

    ExprType type = visitExpression(ctx->expression());

    return type;
}

antlrcpp::Any ANTLRVisitor::visitExpression(SnowStarParser::ExpressionContext* ctx) {
    ExprType type = ExprType::VOID;

    if (auto expr = ctx->primaryExpression()) {
        if (auto id = expr->IDENTIFIER()) {
            // a variable
            std::vector<Declaration> declaredVariables{};
            for (auto const& scope : scopedDeclarations) {
                for (auto const& decl : scope) {
                    declaredVariables.push_back(decl);
                }
            }

            auto it = std::find_if(declaredVariables.begin(), declaredVariables.end(), [&id] (Declaration const& d) { return std::get<0>(d) == id->getText(); });
            if (it == declaredVariables.end()) {
                errored = true;
                UndeclaredVariableError().print(fileName, lineContext, id->getSymbol(), {id->getText()}, {}, functionContext);
            } else {
                if (!std::get<2>(*it)) {
                    UndefinedVariableError().print(fileName, lineContext, id->getSymbol(), {id->getText()}, {}, functionContext);
                    errored = true;
                    type = toType(std::get<1>(*it)->builtinTypes());
                } else {
                    type = toType(std::get<1>(*it)->builtinTypes());
                }
            }
        } else if (auto val = expr->value()) {
            // a value
            auto findType = [this, &ctx] (SnowStarParser::ValueContext* ct) -> ExprType {
                std::string val{ct->getText()};
                if (ct->BOOL_LITERAL()) return ExprType::BOOL;
                if (ct->CHAR_LITERAL()) return ExprType::CHR;
                if (ct->FLOAT_LITERAL()) {
                    try {
                        double d = std::stod(val);
                        if (d > std::numeric_limits<float>::max() || d < std::numeric_limits<float>::min()) return ExprType::F64;
                        else return ExprType::F32;
                    } catch (std::out_of_range& oor) {
                        LiteralOverflowError().print(fileName, lineContext, ctx, {val, "f64"}, {}, functionContext);
                        errored = true;
                        return ExprType::VOID;
                    }
                }
                if (ct->DEC_LITERAL()) {
                    try {
                        uint64_t i = std::stoull(val);
                        if (i <= std::numeric_limits<uint8_t>::max() && i >= std::numeric_limits<uint8_t>::min()) return ExprType::UI8;
                        else if (i <= std::numeric_limits<uint16_t>::max() && i >= std::numeric_limits<uint16_t>::min()) return ExprType::UI16;
                        else if (i <= std::numeric_limits<uint32_t>::max() && i >= std::numeric_limits<uint32_t>::min()) return ExprType::UI32;
                        else return ExprType::UI64;
                    } catch (std::out_of_range& oor) {
                        LiteralOverflowError().print(fileName, lineContext, ctx, {val, "ui64"}, {}, functionContext);
                        errored = true;
                        return ExprType::VOID;
                    }
                }
                if (ct->STRING_LITERAL()) {
                    return ExprType::STR;
                }
                return ExprType::VOID;
            };
            type = findType(expr->value());
        } else {
            type = visitExpression(expr->expression());
            // an expression between ()
        }
    } else {
        // operations
        if (auto type2 = ctx->theType()) {
            // cast
        } else if (auto unexpr = ctx->unary) {
            // unary expressions
            auto expr = visitExpression(ctx->expression()[0]).as<ExprType>();

            if (unexpr->getText() == "~") {
                if (expr == ExprType::BOOL || expr == ExprType::CHR || expr == ExprType::STR) {
                    ExpressionTypeError().print(fileName, lineContext, ctx->expression()[0], {"an integral type", "`"+getType(expr)+"`"}, {}, functionContext);
                    errored = true;
                } else if (expr == ExprType::F32 || expr == ExprType::F64) {
                    ExpressionTypeError().print(fileName, lineContext, ctx->expression()[0], {"an integral type", "`"+getType(expr)+"`"}, {"casting to an integral type"}, functionContext);
                    errored = true;
                } else {
                    type = expr;
                }
            } else if (unexpr->getText() == "!") {
                if (expr != ExprType::BOOL) {
                    ExpressionTypeError().print(fileName, lineContext, ctx->expression()[0], {"`bool` type", "`"+getType(expr)+"`"}, {"`true`", "`false`"}, functionContext);
                    errored = true;
                } else
                    type = ExprType::BOOL;
            } else if (unexpr->getText() == "-") {
                if (expr == ExprType::F32 || expr == ExprType::F64) {
                    type = expr;
                } else if (expr == ExprType::STR || expr == ExprType::CHR || expr == ExprType::BOOL) {
                    ExpressionTypeError().print(fileName, lineContext, ctx->expression()[0], {"an arithmetic type", "`"+getType(expr)+"`"}, {}, functionContext);
                    errored = true;
                } else if (expr == ExprType::UI8) {
                    type = ExprType::I8;
                } else if (expr == ExprType::UI16) {
                    type = ExprType::I16;
                } else if (expr == ExprType::UI32) {
                    type = ExprType::I32;
                } else if (expr == ExprType::UI64) {
                    type = ExprType::I64;
                } else {
                    type = expr;
                }
            } else if (unexpr->getText() == "+") {
                if (expr == ExprType::F32 || expr == ExprType::F64) {
                    type = expr;
                } else if (expr == ExprType::BOOL || expr == ExprType::CHR || expr == ExprType::STR) {
                    ExpressionTypeError().print(fileName, lineContext, ctx->expression()[0], {"an arithmetic type", "`"+getType(expr)+"`"}, {}, functionContext);
                    errored = true;
                } else if (expr == ExprType::UI8) {
                    type = ExprType::I8;
                } else if (expr == ExprType::UI16) {
                    type = ExprType::I16;
                } else if (expr == ExprType::UI32) {
                    type = ExprType::I32;
                } else if (expr == ExprType::UI64) {
                    type = ExprType::I64;
                } else {
                    type = expr;
                }
            } else {

            }
        } else if (auto binexpr = ctx->binary) {
            // binary expressions

            auto expr0 = visitExpression(ctx->expression()[0]).as<ExprType>(),
                 expr1 = visitExpression(ctx->expression()[1]).as<ExprType>();

            if (binexpr->getText() == "*" || binexpr->getText() == "/" || binexpr->getText() == "+" || binexpr->getText() == "-") {
                if (expr0 == ExprType::CHR || expr0 == ExprType::BOOL) {
                    if (binexpr->getText() == "+")
                        ExpressionTypeError().print(fileName, lineContext, ctx->expression()[0], {"an arithmetic or `str` type", "`"+getType(expr0)+"`"}, {}, functionContext);
                    else
                        ExpressionTypeError().print(fileName, lineContext, ctx->expression()[0], {"an arithmetic type", "`"+getType(expr0)+"`"}, {}, functionContext);
                    errored = true;
                } else if (expr1 == ExprType::CHR || expr1 == ExprType::BOOL) {
                    if (binexpr->getText() == "+")
                        ExpressionTypeError().print(fileName, lineContext, ctx->expression()[1], {"an arithmetic or `str` type", "`"+getType(expr1)+"`"}, {}, functionContext);
                    else
                        ExpressionTypeError().print(fileName, lineContext, ctx->expression()[1], {"an arithmetic type", "`"+getType(expr1)+"`"}, {}, functionContext);
                    errored = true;
                } else if (expr0 == ExprType::STR && binexpr->getText() != "+") {
                    ExpressionTypeError().print(fileName, lineContext, ctx->expression()[0], {"an arithmetic type", "`str`"}, {"casting"}, functionContext);
                    errored = true;
                } else if (expr1 == ExprType::STR && binexpr->getText() != "+") {
                    ExpressionTypeError().print(fileName, lineContext, ctx->expression()[1], {"an arithmetic type", "`str`"}, {"casting"}, functionContext);
                    errored = true;
                } else {
                    if (expr0 != expr1) {
                        ExpressionTypeError().print(fileName, lineContext, ctx->expression()[1], {"`"+getType(expr0)+"` type", "`"+getType(expr1)+"`"}, {"casting"}, functionContext);
                        errored = true;
                    } else {
                        type = expr0;
                    }
                }
            } else if (binexpr->getText() == ">" || binexpr->getText() == ">=" || binexpr->getText() == "<" || binexpr->getText() == "<=") {
                if (expr0 == ExprType::BOOL || expr0 == ExprType::STR) {
                    ExpressionTypeError().print(fileName, lineContext, ctx->expression()[0], {"an ordered type", "`"+getType(expr0)+"`"}, {}, functionContext);
                    errored = true;
                } else if (expr1 == ExprType::BOOL || expr1 == ExprType::STR) {
                    ExpressionTypeError().print(fileName, lineContext, ctx->expression()[1], {"an ordered type", "`"+getType(expr1)+"`"}, {}, functionContext);
                    errored = true;
                } else if (expr0 != expr1) {
                    ExpressionTypeError().print(fileName, lineContext, ctx->expression()[1], {"`"+getType(expr0)+"` type", "`"+getType(expr1)+"`"}, {"casting"}, functionContext);
                    errored = true;
                } else {
                    type = ExprType::BOOL;
                }
            } else if (binexpr->getText() == "==" || binexpr->getText() == "!=") {
                if (expr0 != expr1) {
                    ExpressionTypeError().print(fileName, lineContext, ctx->expression()[1], {"`"+getType(expr0)+"`", "`"+getType(expr1)+"`"}, {}, functionContext);
                    errored = true;
                } else if ((expr0 == ExprType::F32 && expr1 == ExprType::F32) || (expr0 == ExprType::F64 && expr1 == ExprType::F64)) {
                    FloatingPointWarning().print(fileName, lineContext, ctx, {}, {}, functionContext);
                    type = ExprType::BOOL;
                } else {
                    type = ExprType::BOOL;
                }
            } else if (binexpr->getText() == "|" || binexpr->getText() == "&" || binexpr->getText() == "^") {
                if (expr0 == ExprType::CHR || expr0 == ExprType::BOOL || expr0 == ExprType::STR) {
                    ExpressionTypeError().print(fileName, lineContext, ctx->expression()[0], {"an integral type", "`"+getType(expr0)+"`"}, {}, functionContext);
                    errored = true;
                } else if (expr1 == ExprType::CHR || expr1 == ExprType::BOOL || expr1 == ExprType::STR) {
                    ExpressionTypeError().print(fileName, lineContext, ctx->expression()[1], {"an integral type", "`"+getType(expr1)+"`"}, {}, functionContext);
                    errored = true;
                } else if (expr0 != expr1) {
                    ExpressionTypeError().print(fileName, lineContext, ctx->expression()[1], {"`"+getType(expr0)+"` type", "`"+getType(expr1)+"`"}, {}, functionContext);
                    errored = true;
                } else {
                    type = expr0;
                }
            } else if (binexpr->getText() == "&&" || binexpr->getText() == "||") {
                if (expr0 != ExprType::BOOL) {
                    ExpressionTypeError().print(fileName, lineContext, ctx->expression()[0], {"`bool` type", "`"+getType(expr0)+"`"}, {}, functionContext);
                    errored = true;
                } else if (expr1 != ExprType::BOOL) {
                    ExpressionTypeError().print(fileName, lineContext, ctx->expression()[1], {"`bool` type", "`"+getType(expr1)+"`"}, {}, functionContext);
                    errored = true;
                } else {
                    type = ExprType::BOOL;
                }
            }
        }
    }

    return type;
}

antlrcpp::Any ANTLRVisitor::visitFunctionDeclaration(SnowStarParser::FunctionDeclarationContext* ctx) {
    #ifndef NDEBUG
        std::clog << termcolor::green << "   [i]   | Visiting a function declaration: " << ctx->functionHeader()->getText() << termcolor::reset << std::endl;
    #endif

    scopedAliases.push_back({});
    scopedDeclarations.push_back({});

    auto functionDef = visitFunctionHeader(ctx->functionHeader()).as<Function>();
    functions.push_back(functionDef);

    functionContext.emplace_back(functionDef, std::make_pair(ctx->getStart()->getLine(), ctx->getStart()->getCharPositionInLine()));

    visitBasicBlockDeclaration(ctx->basicBlockDeclaration());

    scopedAliases.pop_back();
    scopedDeclarations.pop_back();

    functionContext.pop_back();

    return antlrcpp::Any();
}

antlrcpp::Any ANTLRVisitor::visitFunctionHeader(SnowStarParser::FunctionHeaderContext* ctx) {
    lineContext = ctx;

    std::vector<Alias> definedAliases{};
    for (auto const& scope : scopedAliases) {
        for (auto const& alias : scope) {
            definedAliases.push_back(alias);
        }
    }

    SnowStarParser::TheTypeContext* returnType{ctx->theType()};
    if (ctx->theType()->IDENTIFIER()) {
        auto it1 = std::find_if(definedAliases.begin(), definedAliases.end(), [&returnType] (Alias const& alias) { return std::get<0>(alias) == returnType->IDENTIFIER()->getText(); });
        if (it1 == definedAliases.end()) {
            InvalidDeclaringTypeError().print(fileName, lineContext, returnType->IDENTIFIER()->getSymbol(), {returnType->getText()}, {}, functionContext);
            errored = true;
        } else
            returnType = it1->second;
    }

    std::vector<SnowStarParser::TheTypeContext*> functionParametersTypes{ctx->functionParamsTypes()->theType()};
    
    auto functionParams = visitFunctionParams(ctx->functionParams()).as<std::vector<Declaration>>();

    if (functionParametersTypes.size() > functionParams.size()) {
        int i{0};
        for (;i < functionParams.size();++i) {
            auto type{functionParametersTypes[i]};

            if (type->IDENTIFIER()) {
                auto it1 = std::find_if(definedAliases.begin(), definedAliases.end(), [&type] (Alias const& alias) { return std::get<0>(alias) == type->IDENTIFIER()->getText(); });
                if (it1 == definedAliases.end()) {
                    InvalidDeclaringTypeError().print(fileName, lineContext, type->IDENTIFIER()->getSymbol(), {type->getText()}, {}, functionContext);
                    errored = true;
                    continue;
                } else
                    type = it1->second;
            }
            auto decl_type{std::get<1>(functionParams[i])};

            ExprType e1 = toType(type->builtinTypes());
            ExprType e2 = ExprType::VOID;
            if (decl_type) {
                if (decl_type->IDENTIFIER()) {
                    auto it1 = std::find_if(definedAliases.begin(), definedAliases.end(), [&decl_type] (Alias const& alias) { return std::get<0>(alias) == decl_type->IDENTIFIER()->getText(); });
                    if (it1 == definedAliases.end()) {
                        InvalidDeclaringTypeError().print(fileName, lineContext, decl_type->IDENTIFIER()->getSymbol(), {decl_type->getText()}, {}, functionContext);
                        errored = true;
                        continue;
                    } else
                        e2 = toType(it1->second->builtinTypes());
                } else
                    e2 = toType(decl_type->builtinTypes());

                if (e1 != e2) {
                    ParameterTypeMismatchError().print(fileName, lineContext, decl_type, {getType(e1), getType(e2)}, {}, functionContext);
                    errored = true;
                }
            } else
                continue;
        }
        for (;i < functionParametersTypes.size();++i) {
            if (functionParametersTypes[i]->IDENTIFIER()) {
                auto it1 = std::find_if(definedAliases.begin(), definedAliases.end(), [&functionParametersTypes, i] (Alias const& alias) { return std::get<0>(alias) == functionParametersTypes[i]->IDENTIFIER()->getText(); });
                if (it1 == definedAliases.end()) {
                    InvalidDeclaringTypeError().print(fileName, lineContext, functionParametersTypes[i]->IDENTIFIER()->getSymbol(), {functionParametersTypes[i]->getText()}, {}, functionContext);
                } else
                    MissingParameterError().print(fileName, lineContext, ctx->functionParams()->RPAREN()->getSymbol(), {getType(toType(it1->second->builtinTypes()))}, {}, functionContext);
            } else
                MissingParameterError().print(fileName, lineContext, ctx->functionParams()->RPAREN()->getSymbol(), {getType(toType(functionParametersTypes[i]->builtinTypes()))}, {}, functionContext);
            errored = true;
        }
    } else if (functionParametersTypes.size() < functionParams.size()) {
        int i{0};
        for (;i < functionParametersTypes.size();++i) {
            auto type{functionParametersTypes[i]};

            if (type->IDENTIFIER()) {
                auto it1 = std::find_if(definedAliases.begin(), definedAliases.end(), [&type] (Alias const& alias) { return std::get<0>(alias) == type->IDENTIFIER()->getText(); });
                if (it1 == definedAliases.end()) {
                    InvalidDeclaringTypeError().print(fileName, lineContext, type->IDENTIFIER()->getSymbol(), {type->getText()}, {}, functionContext);
                    errored = true;
                    continue;
                } else
                    type = it1->second;
            }
            auto decl_type{std::get<1>(functionParams[i])};

            ExprType e1 = toType(type->builtinTypes());
            ExprType e2 = ExprType::VOID;
            if (decl_type) {
                if (decl_type->IDENTIFIER()) {
                    auto it1 = std::find_if(definedAliases.begin(), definedAliases.end(), [&decl_type] (Alias const& alias) { return std::get<0>(alias) == decl_type->IDENTIFIER()->getText(); });
                    if (it1 == definedAliases.end()) {
                        InvalidDeclaringTypeError().print(fileName, lineContext, decl_type->IDENTIFIER()->getSymbol(), {decl_type->getText()}, {}, functionContext);
                        errored = true;
                        continue;
                    } else
                        e2 = toType(it1->second->builtinTypes());
                } else
                    e2 = toType(decl_type->builtinTypes());

                if (e1 != e2) {
                    ParameterTypeMismatchError().print(fileName, lineContext, decl_type, {getType(e1), getType(e2)}, {}, functionContext);
                    errored = true;
                }
            } else
                continue;
        }
        for (;i < functionParams.size();++i) {
            if (std::get<1>(functionParams[i])->IDENTIFIER()) {
                auto it1 = std::find_if(definedAliases.begin(), definedAliases.end(), [&functionParams, i] (Alias const& alias) { return std::get<0>(alias) == std::get<1>(functionParams[i])->IDENTIFIER()->getText(); });
                if (it1 == definedAliases.end()) {
                    InvalidDeclaringTypeError().print(fileName, lineContext, std::get<1>(functionParams[i])->IDENTIFIER()->getSymbol(), {std::get<1>(functionParams[i])->getText()}, {}, functionContext);
                } else
                    MissingParameterTypeError().print(fileName, lineContext, ctx->functionParams()->RPAREN()->getSymbol(), {getType(toType(it1->second->builtinTypes()))}, {}, functionContext);
            } else
                MissingParameterTypeError().print(fileName, lineContext, ctx->functionParams()->RPAREN()->getSymbol(), {getType(toType(std::get<1>(functionParams[i])->builtinTypes()))}, {}, functionContext);
            errored = true;
        }
    } else {
        for (int i{0};i < functionParametersTypes.size();++i) {
            auto type{functionParametersTypes[i]};

            if (type->IDENTIFIER()) {
                auto it1 = std::find_if(definedAliases.begin(), definedAliases.end(), [&type] (Alias const& alias) { return std::get<0>(alias) == type->IDENTIFIER()->getText(); });
                if (it1 == definedAliases.end()) {
                    InvalidDeclaringTypeError().print(fileName, lineContext, type->IDENTIFIER()->getSymbol(), {type->getText()}, {}, functionContext);
                    errored = true;
                    continue;
                } else
                    type = it1->second;
            }
            auto decl_type{std::get<1>(functionParams[i])};

            ExprType e1 = toType(type->builtinTypes());
            ExprType e2 = ExprType::VOID;
            if (decl_type) {
                if (decl_type->IDENTIFIER()) {
                    auto it1 = std::find_if(definedAliases.begin(), definedAliases.end(), [&decl_type] (Alias const& alias) { return std::get<0>(alias) == decl_type->IDENTIFIER()->getText(); });
                    if (it1 == definedAliases.end()) {
                        InvalidDeclaringTypeError().print(fileName, lineContext, decl_type->IDENTIFIER()->getSymbol(), {decl_type->getText()}, {}, functionContext);
                        errored = true;
                        continue;
                    } else
                        e2 = toType(it1->second->builtinTypes());
                } else
                    e2 = toType(decl_type->builtinTypes());

                if (e1 != e2) {
                    ParameterTypeMismatchError().print(fileName, lineContext, decl_type, {getType(e1), getType(e2)}, {}, functionContext);
                    errored = true;
                }
            } else
                continue;
        }
    }

    return std::make_tuple(ctx->functionName()->getText(), returnType, functionParametersTypes);
}

antlrcpp::Any ANTLRVisitor::visitFunctionParams(SnowStarParser::FunctionParamsContext* ctx) {
    std::vector<Declaration> params{};

    std::vector<Declaration> declaredVariables{};
    for (auto const& scope : scopedDeclarations) {
        for (auto const& decl : scope) {
            declaredVariables.push_back(decl);
        }
    }

    for (auto var : ctx->parameterDeclaration()) {
        auto it = std::find_if(declaredVariables.begin(), declaredVariables.end(), [&var] (Declaration const& d) { return std::get<0>(d) == var->IDENTIFIER()->getText(); });
        if (it != declaredVariables.end()) {
            // redeclared variable
            RedeclaredVariableError().print(fileName, lineContext, var->IDENTIFIER()->getSymbol(), {var->IDENTIFIER()->getText(), std::to_string(std::get<3>(*it).first), std::to_string(std::get<3>(*it).second+1)}, {"changing the name"}, functionContext);
            errored = true;
            params.emplace_back("", nullptr, false, std::make_pair(0, 0));
        } else {
            auto type = var->theType();

            if (type->IDENTIFIER()) {
                std::vector<Alias> definedAliases{};
                for (auto const& scope : scopedAliases) {
                    for (auto const& alias : scope) {
                        definedAliases.push_back(alias);
                    }
                }

                auto it1 = std::find_if(definedAliases.begin(), definedAliases.end(), [&type] (Alias const& alias) { return std::get<0>(alias) == type->IDENTIFIER()->getText(); });
                if (it1 == definedAliases.end()) {
                    InvalidDeclaringTypeError().print(fileName, lineContext, type->IDENTIFIER()->getSymbol(), {type->getText()}, {}, functionContext);
                    errored = true;
                    params.emplace_back("", nullptr, false, std::make_pair(0, 0));
                } else {
                    params.emplace_back(scopedDeclarations.rbegin()->emplace_back(var->IDENTIFIER()->getText(), it1->second, false, std::make_pair(var->IDENTIFIER()->getSymbol()->getLine(), var->IDENTIFIER()->getSymbol()->getCharPositionInLine())));
                    type = it1->second;
                }
            } else
                params.emplace_back(scopedDeclarations.rbegin()->emplace_back(var->IDENTIFIER()->getText(), var->theType(), true, std::make_pair(var->IDENTIFIER()->getSymbol()->getLine(), var->IDENTIFIER()->getSymbol()->getCharPositionInLine())));
        }
    }

    return params;
}

antlrcpp::Any ANTLRVisitor::visitBasicBlockDeclaration(SnowStarParser::BasicBlockDeclarationContext* ctx) {
    #ifndef NDEBUG
        std::clog << termcolor::green << "   [i]   | Visiting a function block: {}" << termcolor::reset << std::endl;
    #endif

    visitChildren(ctx);

    return antlrcpp::Any();
}

antlrcpp::Any ANTLRVisitor::visitReturnDeclaration(SnowStarParser::ReturnDeclarationContext* ctx) {
    #ifndef NDEBUG
        std::clog << termcolor::green << "   [i]   | Visiting a return statement: " << ctx->getText() << termcolor::reset << std::endl;
    #endif

    lineContext = ctx;

    auto it = functionContext.rbegin();
    if (it == functionContext.rend()) {
        MisplacedStatementError().print(fileName, lineContext, ctx, {"return", "a function scope"}, {}, functionContext);
        errored = true;
    } else {
        ExprType expr = ExprType::VOID;
        if (ctx->expression())
            expr = visitExpression(ctx->expression()).as<ExprType>();
        ExprType functionReturn = ExprType::VOID;
        Function f = it->first;
        if (!std::get<1>(f)->IDENTIFIER()) {
            functionReturn = toType(std::get<1>(f)->builtinTypes());
            if (functionReturn != expr) {
                if (ctx->expression())
                    WrongTypedValueError().print(fileName, lineContext, ctx->expression(), {getType(functionReturn), getType(expr), "in return statement"}, {}, functionContext);
                else
                    WrongTypedValueError().print(fileName, lineContext, ctx, {getType(functionReturn), getType(expr), "in return statement"}, {}, functionContext);
                errored = true;
            }
        }
    }

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
}*/