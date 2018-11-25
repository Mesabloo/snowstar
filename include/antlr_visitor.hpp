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

#ifndef ANTLR_VISITOR_HPP
#define ANTLR_VISITOR_HPP

#include <sstream>
#include <iostream>
#include <map>
#include <variant>

#include <SnowStarParserBaseVisitor.h>

#include <antlr4-runtime.h>

class ANTLRVisitor : public SnowStarParserBaseVisitor {
    enum class ExprType {
        VOID,
        I8,
        UI8,
        I16,
        UI16,
        I32,
        UI32,
        I64,
        UI64,
        F32,
        F64,
        CHR,
        BOOL,
        STR
    };

    using Alias = std::pair<std::string, SnowStarParser::TheTypeContext*>;
                /*          ^^^^^^^^^^^ alias name
                                         ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ alias base type
                */
    using Declaration = std::tuple<std::string, SnowStarParser::TheTypeContext*, bool, std::pair<int, int>>;
                      /*           ^^^^^^^^^^^ variable name
                                                ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ variable type
                                                                                 ^^^^ is variable initliazed or not
                                                                                       ^^^^^^^^^^^^^^^^^^^ line and char position
                      */
    using VarInit = Alias;
    template<typename T>
    using Scope = std::vector<T>;
    using Function = std::tuple<std::string, SnowStarParser::TheTypeContext*, std::vector<SnowStarParser::TheTypeContext*>>;
                   /*           ^^^^^^^^^^^ function name
                                             ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ function return type
                                                                              ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ function argument types
                   */
    using FunctionContext = std::pair<Function, std::pair<int, int>>;
                          /*          ^^^^^^^^ the function
                                                ^^^^^^^^^^^^^^^^^^^ function line and char position
                          */

    std::vector<Scope<Alias>> scopedAliases{{}};
    std::vector<Scope<Declaration>> scopedDeclarations{{}};
    std::vector<Function> functions{};

    antlr4::ParserRuleContext* lineContext;
    std::vector<FunctionContext> functionContext{};

    std::string fileName;

    bool errored{false};

public:
    ANTLRVisitor(std::string const&);

    constexpr bool hasErrored() { return errored; }

    virtual antlrcpp::Any visitCompilationUnit(SnowStarParser::CompilationUnitContext*) override;
        // returns antlrcpp::Any
    virtual antlrcpp::Any visitWithDeclaration(SnowStarParser::WithDeclarationContext*) override;
        // returns antlrcpp::Any
    virtual antlrcpp::Any visitVariableDeclaration(SnowStarParser::VariableDeclarationContext*) override;
        // returns antlrcpp::Any
    virtual antlrcpp::Any visitVariableInitializer(SnowStarParser::VariableInitializerContext*) override;
        // returns ExprType
    virtual antlrcpp::Any visitExpression(SnowStarParser::ExpressionContext*) override;
        // returns ExprType
    virtual antlrcpp::Any visitFunctionDeclaration(SnowStarParser::FunctionDeclarationContext*) override;
        // returns antlrcpp::Any
    virtual antlrcpp::Any visitFunctionHeader(SnowStarParser::FunctionHeaderContext*) override;
        // returns Function
    virtual antlrcpp::Any visitFunctionParams(SnowStarParser::FunctionParamsContext*) override;
        // returns std::vector<Declaration>
    virtual antlrcpp::Any visitBasicBlockDeclaration(SnowStarParser::BasicBlockDeclarationContext*) override;
        // returns antlrcpp::Any
    virtual antlrcpp::Any visitReturnDeclaration(SnowStarParser::ReturnDeclarationContext*) override;
        // returns antlrcpp::Any

protected:
    std::function<std::string(ExprType const)> getType = [] (ExprType const e) -> std::string {
        switch (e) {
            case ExprType::BOOL: return "bool";
            case ExprType::CHR: return "chr";
            case ExprType::I8: return "i8";
            case ExprType::UI8: return "ui8";
            case ExprType::I16: return "i16";
            case ExprType::UI16: return "ui16";
            case ExprType::I32: return "i32";
            case ExprType::UI32: return "ui32";
            case ExprType::I64: return "i64";
            case ExprType::UI64: return "ui64";
            case ExprType::F32: return "f32";
            case ExprType::F64: return "f64";
            case ExprType::STR: return "str";
            case ExprType::VOID: return "void";
            default: return "error-type";
        }
    };

    std::function<ExprType(SnowStarParser::BuiltinTypesContext* const)> toType = [] (SnowStarParser::BuiltinTypesContext* const type) -> ExprType {
        if (type->BOOL()) return ExprType::BOOL;
        if (type->CHR()) return ExprType::CHR;
        if (type->I8()) return ExprType::I8;
        if (type->UI8()) return ExprType::UI8;
        if (type->I16()) return ExprType::I16;
        if (type->UI16()) return ExprType::UI16;
        if (type->I32()) return ExprType::I32;
        if (type->UI32()) return ExprType::UI32;
        if (type->I64()) return ExprType::I64;
        if (type->UI64()) return ExprType::UI64;
        if (type->F32()) return ExprType::F32;
        if (type->F64()) return ExprType::F64;
        if (type->STR()) return ExprType::STR;
        return ExprType::VOID;
    };
};

#endif