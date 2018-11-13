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
        INT8,
        INT16,
        INT32,
        INT64,
        REAL16,
        REAL32,
        REAL64,
        CHAR,
        BOOL
    };

    using Alias = std::pair<std::string, SnowStarParser::TheTypeContext*>;
    using Declaration = std::tuple<std::string, SnowStarParser::TheTypeContext*, bool, std::pair<int, int>>;
    using VarInit = Alias;
    template<typename T>
    using Scope = std::vector<T>;

    std::vector<Scope<Alias>> scopedAliases{{}};
    std::vector<Scope<Declaration>> scopedDeclarations{{}};

    antlr4::ParserRuleContext* lineContext;

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
        // returns VarInit
};

#endif