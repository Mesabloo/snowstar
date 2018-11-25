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

#ifndef ERRORS_HPP
#define ERRORS_HPP

#include <string>
#include <sstream>
#include <memory>
#include <vector>
#include <initializer_list>
#include <variant>

#include <antlr4-runtime.h>

#include <SnowStarParser.h>
#include <termcolor/termcolor.hpp>

namespace utils {
    inline std::vector<std::string> str_split(std::string const& str, char const separator) {
        std::vector<std::string> vect;
        std::istringstream f{str};
        std::string s;
        while (getline(f, s, separator)) {
            vect.push_back(s);
        }
        return vect;
    }
}

class Throwable {
protected:
#   if !defined(_WIN32) && !defined(_WIN64)
    std::function<std::string(std::string const, unsigned int)> spacer = [=] (std::string const s1, unsigned int n) -> std::string { std::string s; for (unsigned int tmp{0};tmp < n;++tmp) s+=s1; return s; };
#   else
    std::function<std::wstring(std::wstring const, unsigned int)> spacer = [=] (std::wstring const s1, unsigned int n) -> std::wstring { std::wstring s; for (unsigned int tmp{0};tmp < n;++tmp) s+=s1; return s; };
#   endif

    using Function = std::tuple<std::string, SnowStarParser::TheTypeContext*, std::vector<SnowStarParser::TheTypeContext*>>;
                   /*           ^^^^^^^^^^^ function name
                                             ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ function return type
                                                                              ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ function argument types
                   */
    using FunctionContext = std::pair<Function, std::pair<int, int>>;
                          /*          ^^^^^^^^ the function
                                                ^^^^^^^^^^^^^^^^^^^ function line and char position
                          */

    void printPrettify(std::string const&, int, int, int, std::string const&, std::string const&, std::variant<antlr4::Token*, antlr4::ParserRuleContext*>, bool, std::initializer_list<std::string>, std::vector<FunctionContext> const&);
    void colorCode(std::string const&, std::string const&, antlr4::ParserRuleContext*, std::variant<antlr4::Token*, antlr4::ParserRuleContext*>, bool);
    void suggest(std::initializer_list<std::string>);
    void initWithTextError(std::string const&, std::string const&, antlr4::ParserRuleContext*, std::variant<antlr4::Token*, antlr4::ParserRuleContext*>, bool, std::initializer_list<std::string>, std::vector<FunctionContext> const&);
    void contextualize(std::vector<FunctionContext> const&);

public:
    Throwable() = default;
    virtual ~Throwable() = default;

    virtual void print(std::string const&, antlr4::ParserRuleContext*, std::variant<antlr4::Token*, antlr4::ParserRuleContext*>, std::initializer_list<std::string> const, std::initializer_list<std::string> const, std::vector<FunctionContext> const&) = 0;
};

/**
 * Errors
 */

struct RedeclaredVariableError : public Throwable {
    RedeclaredVariableError() : Throwable() {}
    virtual ~RedeclaredVariableError() override = default;

    virtual void print(std::string const&, antlr4::ParserRuleContext*, std::variant<antlr4::Token*, antlr4::ParserRuleContext*>, std::initializer_list<std::string> const, std::initializer_list<std::string> const, std::vector<FunctionContext> const&) override;
};

struct WrongTypedValueError : public Throwable {
    WrongTypedValueError() : Throwable() {}
    virtual ~WrongTypedValueError() override = default;

    virtual void print(std::string const&, antlr4::ParserRuleContext*, std::variant<antlr4::Token*, antlr4::ParserRuleContext*>, std::initializer_list<std::string> const, std::initializer_list<std::string> const, std::vector<FunctionContext> const&) override;
};

struct InvalidDeclaringTypeError : public Throwable {
    InvalidDeclaringTypeError() : Throwable() {}
    virtual ~InvalidDeclaringTypeError() override = default;

    virtual void print(std::string const&, antlr4::ParserRuleContext*, std::variant<antlr4::Token*, antlr4::ParserRuleContext*>, std::initializer_list<std::string> const, std::initializer_list<std::string> const, std::vector<FunctionContext> const&) override;
};

struct InvalidComparisonTypeError : public Throwable {
    InvalidComparisonTypeError() : Throwable() {}
    virtual ~InvalidComparisonTypeError() override = default;

    virtual void print(std::string const&, antlr4::ParserRuleContext*, std::variant<antlr4::Token*, antlr4::ParserRuleContext*>, std::initializer_list<std::string> const, std::initializer_list<std::string> const, std::vector<FunctionContext> const&) override;
};

struct UndeclaredVariableError : public Throwable {
    UndeclaredVariableError() : Throwable() {}
    virtual ~UndeclaredVariableError() override = default;

    virtual void print(std::string const&, antlr4::ParserRuleContext*, std::variant<antlr4::Token*, antlr4::ParserRuleContext*>, std::initializer_list<std::string> const, std::initializer_list<std::string> const, std::vector<FunctionContext> const&) override;
};

struct UndefinedVariableError : public Throwable {
    UndefinedVariableError() : Throwable() {}
    virtual ~UndefinedVariableError() override = default;

    virtual void print(std::string const&, antlr4::ParserRuleContext*, std::variant<antlr4::Token*, antlr4::ParserRuleContext*>, std::initializer_list<std::string> const, std::initializer_list<std::string> const, std::vector<FunctionContext> const&) override;
};

struct AlreadyExistingIDError : public Throwable {
    AlreadyExistingIDError() : Throwable() {}
    virtual ~AlreadyExistingIDError() override = default;

    virtual void print(std::string const&, antlr4::ParserRuleContext*, std::variant<antlr4::Token*, antlr4::ParserRuleContext*>, std::initializer_list<std::string> const, std::initializer_list<std::string> const, std::vector<FunctionContext> const&) override;
};

struct UnknownIDError : public Throwable {
    UnknownIDError() : Throwable() {}
    virtual ~UnknownIDError() override = default;

    virtual void print(std::string const&, antlr4::ParserRuleContext*, std::variant<antlr4::Token*, antlr4::ParserRuleContext*>, std::initializer_list<std::string> const, std::initializer_list<std::string> const, std::vector<FunctionContext> const&) override;
};

struct LiteralOverflowError : public Throwable {
    LiteralOverflowError() : Throwable() {}
    virtual ~LiteralOverflowError() override = default;

    virtual void print(std::string const&, antlr4::ParserRuleContext*, std::variant<antlr4::Token*, antlr4::ParserRuleContext*>, std::initializer_list<std::string> const, std::initializer_list<std::string> const, std::vector<FunctionContext> const&) override;
};

struct ExpressionTypeError : public Throwable {
    ExpressionTypeError() : Throwable() {}
    virtual ~ExpressionTypeError() override = default;

    virtual void print(std::string const&, antlr4::ParserRuleContext*, std::variant<antlr4::Token*, antlr4::ParserRuleContext*>, std::initializer_list<std::string> const, std::initializer_list<std::string> const, std::vector<FunctionContext> const&) override;
};

struct ParameterTypeMismatchError : public Throwable {
    ParameterTypeMismatchError() : Throwable() {}
    virtual ~ParameterTypeMismatchError() override = default;

    virtual void print(std::string const&, antlr4::ParserRuleContext*, std::variant<antlr4::Token*, antlr4::ParserRuleContext*>, std::initializer_list<std::string> const, std::initializer_list<std::string> const, std::vector<FunctionContext> const&) override;
};

struct MissingParameterTypeError : public Throwable {
    MissingParameterTypeError() : Throwable() {}
    virtual ~MissingParameterTypeError() override = default;

    virtual void print(std::string const&, antlr4::ParserRuleContext*, std::variant<antlr4::Token*, antlr4::ParserRuleContext*>, std::initializer_list<std::string> const, std::initializer_list<std::string> const, std::vector<FunctionContext> const&) override;
};

struct MissingParameterError : public Throwable {
    MissingParameterError() : Throwable() {}
    virtual ~MissingParameterError() override = default;

    virtual void print(std::string const&, antlr4::ParserRuleContext*, std::variant<antlr4::Token*, antlr4::ParserRuleContext*>, std::initializer_list<std::string> const, std::initializer_list<std::string> const, std::vector<FunctionContext> const&) override;
};

struct UndefinedGlobalError : public Throwable {
    UndefinedGlobalError() : Throwable() {}
    virtual ~UndefinedGlobalError() override = default;

    virtual void print(std::string const&, antlr4::ParserRuleContext*, std::variant<antlr4::Token*, antlr4::ParserRuleContext*>, std::initializer_list<std::string> const, std::initializer_list<std::string> const, std::vector<FunctionContext> const&) override;
};

struct MisplacedStatementError : public Throwable {
    MisplacedStatementError() : Throwable() {}
    virtual ~MisplacedStatementError() override = default;

    virtual void print(std::string const&, antlr4::ParserRuleContext*, std::variant<antlr4::Token*, antlr4::ParserRuleContext*>, std::initializer_list<std::string> const, std::initializer_list<std::string> const, std::vector<FunctionContext> const&) override;
};

/**
 * Warnings
 */

struct ImplicitCastWarning : public Throwable {
    ImplicitCastWarning() : Throwable() {}
    virtual ~ImplicitCastWarning() override = default;

    virtual void print(std::string const&, antlr4::ParserRuleContext*, std::variant<antlr4::Token*, antlr4::ParserRuleContext*>, std::initializer_list<std::string> const, std::initializer_list<std::string> const, std::vector<FunctionContext> const&) override;
};

struct FloatingPointWarning : public Throwable {
    FloatingPointWarning() : Throwable() {}
    virtual ~FloatingPointWarning() override = default;
    
    virtual void print(std::string const&, antlr4::ParserRuleContext*, std::variant<antlr4::Token*, antlr4::ParserRuleContext*>, std::initializer_list<std::string> const, std::initializer_list<std::string> const, std::vector<FunctionContext> const&) override;
};

#endif