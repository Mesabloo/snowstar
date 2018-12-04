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

#if defined(_WIN32) || defined(_WIN64)
#   include <io.h>
#   include <fcntl.h>
#endif

void Throwable::printPrettify(std::string const& file, int line, int charac, int firstCharac, std::string const& msg, std::string const& code, std::variant<antlr4::Token*, antlr4::ParserRuleContext*> tk, bool isWarning, std::initializer_list<std::string> alts, std::vector<FunctionContext> const& fContext) {
    #if !defined(_WIN32) && !defined(_WIN64)
    std::ostream& ss{std::cerr};
	ss  << "\n"
		<< termcolor::colorize
		<< termcolor::bold;
	if (!isWarning) {
		ss  << termcolor::on_red << termcolor::white
			<< "Error:";
	}
	else {
		ss  << termcolor::on_yellow << termcolor::white
			<< "Warning:";
	}
	ss  << termcolor::reset << termcolor::white
		<< " " << msg << "\n"
		<< termcolor::grey
		<< termcolor::bold
		<< " ├┬╼ in: "
		<< termcolor::reset << termcolor::green
		<< file << " @ line " << std::to_string(line) << ":" << std::to_string(charac + 1) << std::flush
		<< termcolor::reset;
	this->contextualize(fContext);
	if (alts.size() > 0)
		this->suggest(alts);
	ss  << termcolor::grey
		<< termcolor::bold
		<< " │"
		<< spacer(" ", charac - firstCharac + 4)
		<< termcolor::reset;
	if (!isWarning)
		ss  << termcolor::red;
	else
		ss  << termcolor::yellow;
	if (std::holds_alternative<antlr4::Token*>(tk))
		ss << spacer("⌄", std::get<0>(tk)->getText().size());
	else {
		std::string tokens = std::get<1>(tk)->getStart()->getInputStream()->getText(antlr4::misc::Interval{ std::get<1>(tk)->getStart()->getStartIndex(), std::get<1>(tk)->getStop()->getStopIndex() });
		ss << spacer("⌄", tokens.size());
	}
	ss
		<< termcolor::grey
		<< termcolor::bold
		<< "\n"
		<< " ╰──╼" << " "
		<< termcolor::reset
		<< std::flush;
    #else
    std::wostream& ss{std::wcout};
	ss  << L"\n";
    if (!isWarning) {
		std::cout << termcolor::on_red << termcolor::white << std::flush;
        ss    << L"Error";
    } else {
		std::cout << termcolor::on_yellow << termcolor::white << std::flush;
        ss    << L"Warning";
    }
	ss
		<< L":";
	std::cout << termcolor::reset << termcolor::white<< std::flush;
	ss	<< L" " << std::wstring(msg.begin(), msg.end()) << "\n";
	std::cout << termcolor::reset << termcolor::white << std::flush;
	ss
		<< L" \u251C\u252C\u2022 ";
	std::cout << termcolor::reset << termcolor::green << std::flush;
	ss	<< L"in: " << std::wstring(file.begin(), file.end()) << L" @ line " << std::to_wstring(line) << L":" << std::to_wstring(charac+1);
    this->contextualize(fContext);
    if (alts.size() > 0)
        this->suggest(alts);
	std::cout << termcolor::reset << termcolor::white << std::flush;
    ss  
        << L" \u2502"
        << spacer(L" ", charac-firstCharac+4);
	std::cout << termcolor::reset << termcolor::red << std::flush;
    if (std::holds_alternative<antlr4::Token*>(tk))
        ss << spacer(L"v", std::get<0>(tk)->getText().size());
    else {
        std::string tokens = std::get<1>(tk)->getStart()->getInputStream()->getText(antlr4::misc::Interval{std::get<1>(tk)->getStart()->getStartIndex(), std::get<1>(tk)->getStop()->getStopIndex()});
        ss << spacer(L"v", tokens.size());
    }
	std::cout << termcolor::reset << termcolor::white << std::flush;
    ss
        << L"\n"
        << L" \u2514\u2500\u2500\u2022 ";
	#endif
}

void Throwable::colorCode(std::string const& code, std::string const& tokens, antlr4::ParserRuleContext* ctx, std::variant<antlr4::Token*, antlr4::ParserRuleContext*> inFault, bool isWarning) {
    int character;

    if (std::holds_alternative<antlr4::Token*>(inFault))
        character = std::get<antlr4::Token*>(inFault)->getCharPositionInLine();
    else
        character = std::get<antlr4::ParserRuleContext*>(inFault)->getStart()->getCharPositionInLine();
    int firstCharacter = ctx->getStart()->getCharPositionInLine();

    auto tokenBeg = code.find(tokens, character-firstCharacter);
    if (tokenBeg != code.npos) {
		std::string begCode = code.substr(0, tokenBeg);
		std::string middleCode = code.substr(tokenBeg, tokens.size());
		std::string endCode = code.substr(tokenBeg + tokens.size());
		#if !defined(_WIN32) && !defined(_WIN64)
		std::ostream& ss{std::cerr};
		ss  << termcolor::reset << termcolor::white
			<< begCode
		if (isWarning)
			ss << termcolor::yellow;
		else
			ss << termcolor::red;
		ss  << middleCode 
			<< termcolor::reset << termcolor::white
			<< endCode
			<< termcolor::reset
			<< std::flush;
		#else
		std::wostream& ss{std::wcout};
		std::cout << termcolor::reset << termcolor::white << std::flush;
		ss << std::wstring(begCode.begin(), begCode.end());
		std::cout << termcolor::reset << (isWarning ? termcolor::yellow : termcolor::red) << std::flush;
		ss << std::wstring(middleCode.begin(), middleCode.end());
		std::cout << termcolor::reset << termcolor::white << std::flush;
		ss << std::wstring(endCode.begin(), endCode.end());
		std::cout << termcolor::reset << std::flush;
		#endif
	} else {
		#if !defined(_WIN32) && !defined(_WIN64)
		std::ostream& ss{std::cerr};
		ss  << termcolor::reset << termcolor::white
			<< code
			<< termcolor::reset
			<< std::flush;
		#else
		std::wostream& ss{std::wcout};
		std::cout << termcolor::reset << termcolor::white << std::flush;
		ss << std::wstring(code.begin(), code.end());
		std::cout << termcolor::reset << std::flush;
		#endif
	}
}

void Throwable::suggest(std::initializer_list<std::string> alts) {
    if (alts.size() == 0) return;

	#if !defined(_WIN32) && !defined(_WIN64)
	std::ostream& ss{std::cerr};
	ss  << termcolor::grey << termcolor::bold
		<< " ├───╼╸ "
		<< termcolor::reset << termcolor::blue
		<< "Try: ";
	if (alts.size() == 1) {
		ss << *(alts.begin() + 0) << ".";
	} else {
		for (int i{ 0 }; i < alts.size() - 2; ++i) {
			ss << *(alts.begin() + i) << ", ";
		}
		ss << *(alts.begin() + alts.size() - 2) << " or " << *(alts.begin() + alts.size() - 1) << ".";
	}
	ss << termcolor::reset << "\n" << std::flush;
	#else
	std::wostream& ss{std::wcout};
	std::cout << termcolor::reset << termcolor::white << std::flush;
	ss
		<< L" \u251C\u2500\u2500\u2500\u2022 ";
	std::cout << termcolor::reset << termcolor::blue << std::flush;
	ss  << "Try: ";
	if (alts.size() == 1) {
		std::string val = *(alts.begin() + 0);
		ss << std::wstring(val.begin(), val.end()) << L".";
	} else {
        for (int i{0};i < alts.size()-2;++i) {
			std::string val = *(alts.begin() + i);
			ss << std::wstring(val.begin(), val.end()) << L", ";
        }
		std::string val1 = *(alts.begin() + alts.size() - 2),
					val2 = *(alts.begin() + alts.size() - 1);
		ss << std::wstring(val1.begin(), val1.end()) << L" or " << std::wstring(val2.begin(), val2.end()) << L".";
    }
	std::cout << termcolor::reset;
    ss  << L"\n";
	#endif
}

void Throwable::initWithTextError(std::string const& error, std::string const& path, antlr4::ParserRuleContext* ctx, std::variant<antlr4::Token*, antlr4::ParserRuleContext*> inFault, bool isWarning, std::initializer_list<std::string> alternatives, std::vector<FunctionContext> const& fContext) {
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
    
    this->printPrettify(path, line, character, firstCharacter, error, code, inFault, isWarning, alternatives, fContext);

    this->colorCode(code, token, ctx, inFault, isWarning);

    #if !defined (_WIN32) && !defined(_WIN64)
    std::cerr << termcolor::reset << std::endl;
    #endif
}

void Throwable::contextualize(std::vector<FunctionContext> const& fContext) {
	#if !defined(_WIN32) && !defined(_WIN64)
	std::ostream& ss{ std::cerr };
	if (fContext.size() == 0) {
		ss << termcolor::grey << termcolor::bold
			<< "\n"
			<< " │╰╼"
			<< termcolor::reset << termcolor::green
			<< " in: global scope declared @ line 0:0"
			<< termcolor::reset << "\n" << std::flush;
	} else {
		for (int i{0}; i < fContext.size()-1; ++i) {
			ss
				<< termcolor::grey << termcolor::bold
				<< "\n" << " │├╼"
				<< termcolor::reset << termcolor::green
				<< " in: `" + (std::get<0>(fContext[i].first)) + "` declared @ line " + std::to_string(fContext[i].second.first) + ":" + std::to_string(fContext[i].second.second + 1) + ""
				<< termcolor::reset;
		}
		ss
			<< termcolor::grey << termcolor::bold
			<< "\n" << " │╰╼"
			<< termcolor::reset << termcolor::green
			<< " in: `" + (std::get<0>(fContext[fContext.size() - 1].first)) + "` declared @ line " + std::to_string(fContext[fContext.size() - 1].second.first) + ":" + std::to_string(fContext[fContext.size() - 1].second.second + 1) + ""
			<< termcolor::reset << "\n" << std::flush;
	}
    #else
    std::wostream& ss{std::wcout};
	if (fContext.size() == 0) {
		std::cout << termcolor::reset << termcolor::white << std::flush;
		ss  << L"\n" << L" \u2502\u2514\u2022";
		std::cout << termcolor::reset << termcolor::green << std::flush;
		ss  << L" in: global scope declared @ line 0:0"
			<< L"\n";
	} else {
		for (int i{ 0 }; i < fContext.size() - 1; ++i) {
			std::cout << termcolor::reset << termcolor::white << std::flush;
			ss	<< L"\n" << L" \u2502\u251C\u2022";
			std::cout << termcolor::reset << termcolor::green << std::flush;
			ss	<< L" in: `" + std::wstring(std::get<0>(fContext[i].first).begin(), std::get<0>(fContext[i].first).end()) + L"` declared @ line " + std::to_wstring(fContext[i].second.first) + L":" + std::to_wstring(fContext[i].second.second + 1) + L""
				<< L"\n";
		}
		std::cout << termcolor::reset << termcolor::white << std::flush;
		ss	<< L"\n" << L" \u2502\u2514\u2022";
		std::cout << termcolor::reset << termcolor::green << std::flush;
		ss	<< L" in: `" + std::wstring(std::get<0>(fContext[fContext.size() - 1].first).begin(), std::get<0>(fContext[fContext.size() - 1].first).end()) + L"` declared @ line " + std::to_wstring(fContext[fContext.size() - 1].second.first) + L":" + std::to_wstring(fContext[fContext.size() - 1].second.second + 1) + L""
			<< L"\n";
	}
    #endif
}

void RedeclaredVariableError::print(std::string const& path, antlr4::ParserRuleContext* ctx, std::variant<antlr4::Token*, antlr4::ParserRuleContext*> inFault, std::initializer_list<std::string> const args, std::initializer_list<std::string> const alts, std::vector<FunctionContext> const& fContext) {
    this->initWithTextError("Redeclared variable `" + *(args.begin()+0) + "`, previously declared at line " + *(args.begin()+1) + ":" + *(args.begin()+2) + ".", path, ctx, inFault, false, alts, fContext);
}

void UndeclaredVariableError::print(std::string const& path, antlr4::ParserRuleContext* ctx, std::variant<antlr4::Token*, antlr4::ParserRuleContext*> inFault, std::initializer_list<std::string> const args, std::initializer_list<std::string> const alts, std::vector<FunctionContext> const& fContext) {
    this->initWithTextError("Variable `" + *(args.begin()+0) + "` referenced but not declared.", path, ctx, inFault, false, alts, fContext);
}

void UndefinedVariableError::print(std::string const& path, antlr4::ParserRuleContext* ctx, std::variant<antlr4::Token*, antlr4::ParserRuleContext*> inFault, std::initializer_list<std::string> const args, std::initializer_list<std::string> const alts, std::vector<FunctionContext> const& fContext) {
    this->initWithTextError("Variable `" + *(args.begin()+0) + "` referenced but not bound to a value.", path, ctx, inFault, false, alts, fContext);
}

void WrongTypedValueError::print(std::string const& path, antlr4::ParserRuleContext* ctx, std::variant<antlr4::Token*, antlr4::ParserRuleContext*> inFault, std::initializer_list<std::string> const args, std::initializer_list<std::string> const alts, std::vector<FunctionContext> const& fContext) {
    this->initWithTextError("Inconsistent types. Expected `" + *(args.begin()+0) + "`, found `" + *(args.begin()+1) + "` " + *(args.begin()+2) + ".", path, ctx, inFault, false, alts, fContext);
}

void InvalidDeclaringTypeError::print(std::string const& path, antlr4::ParserRuleContext* ctx, std::variant<antlr4::Token*, antlr4::ParserRuleContext*> inFault, std::initializer_list<std::string> const args, std::initializer_list<std::string> const alts, std::vector<FunctionContext> const& fContext) {
    this->initWithTextError("Unknown variable declaration type `" + *(args.begin()+0) + "`.", path, ctx, inFault, false, alts, fContext);
}

void InvalidComparisonTypeError::print(std::string const& path, antlr4::ParserRuleContext* ctx, std::variant<antlr4::Token*, antlr4::ParserRuleContext*> inFault, std::initializer_list<std::string> const args, std::initializer_list<std::string> const alts, std::vector<FunctionContext> const& fContext) {
    this->initWithTextError("Invalid comparison type `" + *(args.begin()+0) + "`.", path, ctx, inFault, false, alts, fContext);
}

void AlreadyExistingIDError::print(std::string const& path, antlr4::ParserRuleContext* ctx, std::variant<antlr4::Token*, antlr4::ParserRuleContext*> inFault, std::initializer_list<std::string> const args, std::initializer_list<std::string> const alts, std::vector<FunctionContext> const& fContext) {
    this->initWithTextError("Name `" + *(args.begin()+0) + "` already taken.", path, ctx, inFault, false, alts, fContext);
}

void UnknownIDError::print(std::string const& path, antlr4::ParserRuleContext* ctx, std::variant<antlr4::Token*, antlr4::ParserRuleContext*> inFault, std::initializer_list<std::string> const args, std::initializer_list<std::string> const alts, std::vector<FunctionContext> const& fContext) {
    this->initWithTextError("Unknown name `" + *(args.begin()+0) + "`.", path, ctx, inFault, false, alts, fContext);
}

void LiteralOverflowError::print(std::string const& path, antlr4::ParserRuleContext* ctx, std::variant<antlr4::Token*, antlr4::ParserRuleContext*> inFault, std::initializer_list<std::string> const args, std::initializer_list<std::string> const alts, std::vector<FunctionContext> const& fContext) {
    this->initWithTextError("Number `" + *(args.begin()+0) + "` overflows a `" + *(args.begin()+1) + "` variable.", path, ctx, inFault, false, alts, fContext);
}

void ExpressionTypeError::print(std::string const& path, antlr4::ParserRuleContext* ctx, std::variant<antlr4::Token*, antlr4::ParserRuleContext*> inFault, std::initializer_list<std::string> const args, std::initializer_list<std::string> const alts, std::vector<FunctionContext> const& fContext) {
    this->initWithTextError("Expression must have " + *(args.begin() + 0) + ", not " + *(args.begin() + 1) + ".", path, ctx, inFault, false, alts, fContext);
}

void ParameterTypeMismatchError::print(std::string const& path, antlr4::ParserRuleContext* ctx, std::variant<antlr4::Token*, antlr4::ParserRuleContext*> inFault, std::initializer_list<std::string> const args, std::initializer_list<std::string> const alts, std::vector<FunctionContext> const& fContext) {
    this->initWithTextError("Parameter types mismatch: expected `" + *(args.begin() + 0) + "`, not `" + *(args.begin() + 1) + "`.", path, ctx, inFault, false, alts, fContext);
}

void MissingParameterTypeError::print(std::string const& path, antlr4::ParserRuleContext* ctx, std::variant<antlr4::Token*, antlr4::ParserRuleContext*> inFault, std::initializer_list<std::string> const args, std::initializer_list<std::string> const alts, std::vector<FunctionContext> const& fContext) {
    this->initWithTextError("Missing parameter type `" + *(args.begin() + 0) + "`.", path, ctx, inFault, false, alts, fContext);
}

void MissingParameterError::print(std::string const& path, antlr4::ParserRuleContext* ctx, std::variant<antlr4::Token*, antlr4::ParserRuleContext*> inFault, std::initializer_list<std::string> const args, std::initializer_list<std::string> const alts, std::vector<FunctionContext> const& fContext) {
    this->initWithTextError("Missing parameter of type `" + *(args.begin() + 0) + "`.", path, ctx, inFault, false, alts, fContext);
}

void UndefinedGlobalError::print(std::string const& path, antlr4::ParserRuleContext* ctx, std::variant<antlr4::Token*, antlr4::ParserRuleContext*> inFault, std::initializer_list<std::string> const args, std::initializer_list<std::string> const alts, std::vector<FunctionContext> const& fContext) {
    this->initWithTextError("Global `" + *(args.begin() + 0) + "` not bound to a value.", path, ctx, inFault, false, alts, fContext);
}

void MisplacedStatementError::print(std::string const& path, antlr4::ParserRuleContext* ctx, std::variant<antlr4::Token*, antlr4::ParserRuleContext*> inFault, std::initializer_list<std::string> const args, std::initializer_list<std::string> const alts, std::vector<FunctionContext> const& fContext) {
    this->initWithTextError("Misplaced `" + *(args.begin() + 0) + "` statement, expected to be found in " + *(args.begin()+1) + ".", path, ctx, inFault, false, alts, fContext);
}

void ImplicitCastWarning::print(std::string const& path, antlr4::ParserRuleContext* ctx, std::variant<antlr4::Token*, antlr4::ParserRuleContext*> inFault, std::initializer_list<std::string> const args, std::initializer_list<std::string> const alts, std::vector<FunctionContext> const& fContext) {
    this->initWithTextError("Implicit cast performed from type `" + *(args.begin()+0) + "` to type `" + *(args.begin()+1) + "`.", path, ctx, inFault, true, alts, fContext);
}

void FloatingPointWarning::print(std::string const& path, antlr4::ParserRuleContext* ctx, std::variant<antlr4::Token*, antlr4::ParserRuleContext*> inFault, std::initializer_list<std::string> const args, std::initializer_list<std::string> const alts, std::vector<FunctionContext> const& fContext) {
    this->initWithTextError("Performing floating point comparison.", path, ctx, inFault, true, alts, fContext);
}