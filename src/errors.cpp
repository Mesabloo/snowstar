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

#include <errors.hpp>

void Throwable::printPrettify(std::string const& file, int line, int charac, int firstCharac, std::string const& msg, std::string const& code, std::variant<antlr4::Token*, antlr4::ParserRuleContext*> tk, bool isWarning) {
    #if !defined(_WIN32) && !defined(_WIN64)
    std::ostream& ss{std::cerr};
    #else
    std::wostream& ss{std::wcerr};
    #endif
    
    ss
    #if !defined(_WIN32) && !defined(_WIN64)
        << termcolor::colorize
        << termcolor::bold
    #endif
    ;
    if (!isWarning) {
        ss  << termcolor::on_red << termcolor::white
            << "Error";
    } else {
        ss  << termcolor::on_yellow << termcolor::white
            << "Warning";
    }
    ss  << termcolor::reset << termcolor::white
        << ": " << msg << "\n"
        << termcolor::grey
    #if !defined(_WIN32) && !defined(_WIN64)
        << termcolor::bold
    #else
        << termcolor::reset << termcolor::white
    #endif
    #if !defined(_WIN32) && !defined(_WIN64)
        << " ╰┬╼ "
    #else
        << L" ╰┬╼ "
    #endif
        << termcolor::reset << termcolor::green
        << file << " @ line " << std::to_string(line) << ":" << std::to_string(charac+1) << "\n"
        << termcolor::reset << termcolor::grey
    #if !defined(_WIN32) && !defined(_WIN64)
        << termcolor::bold
    #else
        << termcolor::reset << termcolor::white
    #endif
    #if !defined(_WIN32) && !defined(_WIN64)
        << "  │"
    #else
        << L"  │"
    #endif
        << spacer(" ", charac-firstCharac+4)
        << termcolor::reset;
    if (!isWarning)
        ss  << termcolor::red;
    else
        ss  << termcolor::yellow;
    #if !defined(_WIN32) && !defined(_WIN64)
    if (std::holds_alternative<antlr4::Token*>(tk))
        ss << spacer("⌄", std::get<0>(tk)->getText().size());
    else {
        std::string tokens = std::get<1>(tk)->getStart()->getInputStream()->getText(antlr4::misc::Interval{std::get<1>(tk)->getStart()->getStartIndex(), std::get<1>(tk)->getStop()->getStopIndex()});
        ss << spacer("⌄", tokens.size());
    } 
    #else
    if (std::holds_alternative<antlr4::Token*>)
        ss << spacer(L"⌄", std::get<0>(tk)->getText().size());
    else {
        std::string tokens = std::get<1>(tk)->getStart()->getInputStream()->getText(antlr4::misc::Interval{std::get<1>(tk)->getStart()->getStartIndex(), std::get<1>(tk)->getStop()->getStopIndex()});
        ss << spacer(L"⌄", tokens.size());
    } 
    #endif
    ss
        << termcolor::grey
    #if !defined(_WIN32) && !defined(_WIN64)
        << termcolor::bold
    #else
        << termcolor::reset << termcolor::white
    #endif
        << "\n"
    #if !defined(_WIN32) && !defined(_WIN64)
        << "  ╰──╼" << " "
    #else
        << L"  ╰──╼" << " "
    #endif
        << termcolor::reset
        << code
        << std::endl;
}

void Throwable::colorCode(std::string& code, std::string const& tokens, antlr4::ParserRuleContext* ctx, std::variant<antlr4::Token*, antlr4::ParserRuleContext*> inFault, bool isWarning) {
    int character;

    if (std::holds_alternative<antlr4::Token*>(inFault))
        character = std::get<antlr4::Token*>(inFault)->getCharPositionInLine();
    else
        character = std::get<antlr4::ParserRuleContext*>(inFault)->getStart()->getCharPositionInLine();
    int firstCharacter = ctx->getStart()->getCharPositionInLine();

    auto tokenBeg = code.find(tokens, character-firstCharacter);
    if (tokenBeg != code.npos) {
        std::stringstream ss;
        ss << code.substr(0, tokenBeg)
        #if !defined(_WIN32) && !defined(_WIN64)
            << termcolor::colorize
        #endif
        ;
        if (!isWarning)
            ss  << termcolor::red;
        else
            ss  << termcolor::yellow;
        ss  << code.substr(tokenBeg, tokens.size()) << termcolor::reset << code.substr(tokenBeg + tokens.size());
        code = std::string{ss.str()};
    }
}

void Throwable::initWithTextError(std::string const& error, std::string const& path, antlr4::ParserRuleContext* ctx, std::variant<antlr4::Token*, antlr4::ParserRuleContext*> inFault, bool isWarning) {
    int line, character, firstCharacter = ctx->getStart()->getCharPositionInLine();
    std::string code = ctx->getStart()->getInputStream()->getText(antlr4::misc::Interval{ctx->getStart()->getStartIndex(), ctx->getStop()->getStopIndex()}), token;
    if (std::holds_alternative<antlr4::ParserRuleContext*>(inFault)) {
        auto rule = std::get<antlr4::ParserRuleContext*>(inFault);
        line = rule->getStart()->getLine();
        character = rule->getStart()->getCharPositionInLine();
        token = ctx->getStart()->getInputStream()->getText(antlr4::misc::Interval{rule->getStart()->getStartIndex(), rule->getStop()->getStopIndex()});
    } else {
        auto tk = std::get<antlr4::Token*>(inFault);
        line = tk->getLine();
        character = tk->getCharPositionInLine();
        token = tk->getText();
    }

    this->colorCode(code, token, ctx, inFault, isWarning);
    
    this->printPrettify(path, line, character, firstCharacter, error, code, inFault, isWarning);
}

void RedeclaredVariableError::print(std::string const& path, antlr4::ParserRuleContext* ctx, std::variant<antlr4::Token*, antlr4::ParserRuleContext*> inFault, std::initializer_list<std::string> const args) {
    this->initWithTextError("Redeclared variable `" + *(args.begin()+0) + "`, previously declared at line " + *(args.begin()+1) + ":" + *(args.begin()+2) + ".", path, ctx, inFault, false);
}

void UndeclaredVariableError::print(std::string const& path, antlr4::ParserRuleContext* ctx, std::variant<antlr4::Token*, antlr4::ParserRuleContext*> inFault, std::initializer_list<std::string> const args) {
    this->initWithTextError("Undeclared variable `" + *(args.begin()+0) + "`.", path, ctx, inFault, false);
}

void UndefinedVariableError::print(std::string const& path, antlr4::ParserRuleContext* ctx, std::variant<antlr4::Token*, antlr4::ParserRuleContext*> inFault, std::initializer_list<std::string> const args) {
    this->initWithTextError("Variable `" + *(args.begin()+0) + "` referenced but not bound to a value.", path, ctx, inFault, false);
}

void WrongTypedValueError::print(std::string const& path, antlr4::ParserRuleContext* ctx, std::variant<antlr4::Token*, antlr4::ParserRuleContext*> inFault, std::initializer_list<std::string> const args) {
    this->initWithTextError("Inconsistent types. Expected `" + *(args.begin()+0) + "`, found `" + *(args.begin()+1) + "` " + *(args.begin()+2) + ".", path, ctx, inFault, false);
}

void InvalidDeclaringTypeError::print(std::string const& path, antlr4::ParserRuleContext* ctx, std::variant<antlr4::Token*, antlr4::ParserRuleContext*> inFault, std::initializer_list<std::string> const args) {
    this->initWithTextError("Invalid variable declaration type `" + *(args.begin()+0) + "`.", path, ctx, inFault, false);
}

void InvalidComparisonTypeError::print(std::string const& path, antlr4::ParserRuleContext* ctx, std::variant<antlr4::Token*, antlr4::ParserRuleContext*> inFault, std::initializer_list<std::string> const args) {
    this->initWithTextError("Invalid comparison type `" + *(args.begin()+0) + "`.", path, ctx, inFault, false);
}

void AlreadyExistingIDError::print(std::string const& path, antlr4::ParserRuleContext* ctx, std::variant<antlr4::Token*, antlr4::ParserRuleContext*> inFault, std::initializer_list<std::string> const args) {
    this->initWithTextError("Name `" + *(args.begin()+0) + "` already taken.", path, ctx, inFault, false);
}

void UnknownIDError::print(std::string const& path, antlr4::ParserRuleContext* ctx, std::variant<antlr4::Token*, antlr4::ParserRuleContext*> inFault, std::initializer_list<std::string> const args) {
    this->initWithTextError("Unknown name `" + *(args.begin()+0) + "`.", path, ctx, inFault, false);
}

void ImplicitCastWarning::print(std::string const& path, antlr4::ParserRuleContext* ctx, std::variant<antlr4::Token*, antlr4::ParserRuleContext*> inFault, std::initializer_list<std::string> const args) {
    this->initWithTextError("Implicit cast performed from type `" + *(args.begin()+0) + "` to type `" + *(args.begin()+1) + "`.", path, ctx, inFault, true);
}

void FloatingPointWarning::print(std::string const& path, antlr4::ParserRuleContext* ctx, std::variant<antlr4::Token*, antlr4::ParserRuleContext*> inFault, std::initializer_list<std::string> const args) {
    this->initWithTextError("Performing floating point comparison.", path, ctx, inFault, true);
}