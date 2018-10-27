#include <errors.hpp>

std::string Error::prettify(std::string const& file, int errCode, int line, int charac, int firstCharac, std::string const& msg, std::string const& code, antlr4::Token* tk) {
    #if !defined(_WIN32) && !defined(_WIN64)
    std::stringstream ss;
    #else
    std::wstringstream ss;
    #endif
    
    ss
    #if !defined(_WIN32) && !defined(_WIN64)
        << termcolor::colorize
        << termcolor::bold
    #endif
        << termcolor::on_red << termcolor::white
        << "Error"
        << termcolor::reset << termcolor::white
        << ": " << msg << "\n"
        << termcolor::grey
    #if !defined(_WIN32) && !defined(_WIN64)
        << termcolor::bold
    #else
        << termcolor::reset << termcolor::white
    #endif
    #if !defined(_WIN32) && !defined(_WIN64)
        << " ├─╼"
    #else
        << L" ├─╼"
    #endif
        << termcolor::reset << termcolor::red
        << " code"
        << termcolor::reset << termcolor::white
        << ": " << std::to_string(errCode) << "\n"
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
        << termcolor::reset << termcolor::red;
    #if !defined(_WIN32) && !defined(_WIN64)
    if (!tk)
        ss << spacer("↓", code.size());
    else
        ss << spacer("↓", tk->getText().size());
    #else
    if (!tk)
        ss << spacer(L"↓", code.size());
    else
        ss << spacer(L"↓", tk->getText().size());
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
        << "\n";
    #if !defined(_WIN32) && !defined(_WIN64)
    return std::string{ss.str()};
    #else
    return std::wstring{ss.str()};
    #endif
}
std::string Warning::prettify(std::string const& file, int errCode, int line, int charac, int firstCharac, std::string const& msg, std::string const& code, antlr4::Token* tk) {
    #if !defined(_WIN32) && !defined(_WIN64)
    std::stringstream ss;
    #else
    std::wstringstream ss;
    #endif
    
    ss
    #if !defined(_WIN32) && !defined(_WIN64)
        << termcolor::colorize
        << termcolor::bold
    #endif
        << termcolor::on_yellow << termcolor::white
        << "Warning"
        << termcolor::reset << termcolor::white
        << ": " << msg << "\n"
        << termcolor::grey
    #if !defined(_WIN32) && !defined(_WIN64)
        << termcolor::bold
    #else
        << termcolor::reset << termcolor::white
    #endif
    #if !defined(_WIN32) && !defined(_WIN64)
        << " ├─╼"
    #else
        << L" ├─╼"
    #endif
        << termcolor::reset << termcolor::yellow
        << " code"
        << termcolor::reset << termcolor::white
        << ": " << std::to_string(errCode) << "\n"
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
        << termcolor::reset << termcolor::yellow
    #if !defined(_WIN32) && !defined(_WIN64)
        << spacer("↓", tk->getText().size())
    #else
        << spacer(L"↓", tk->getText().size())
    #endif
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
        << "\n";
    #if !defined(_WIN32) && !defined(_WIN64)
    return std::string{ss.str()};
    #else
    return std::wstring{ss.str()};
    #endif
}

std::unique_ptr<Error> RedeclaredVariableError::from(std::string const& path, antlr4::ParserRuleContext* ctx, antlr4::Token* in_fault, std::string const args...) {
    int line = in_fault->getLine(),
        character = in_fault->getCharPositionInLine(),
        first_character = ctx->getStart()->getCharPositionInLine();
    std::string code = ctx->getStart()->getInputStream()->getText(antlr4::misc::Interval{ctx->getStart()->getStartIndex(), ctx->getStop()->getStopIndex()}),
                token = in_fault->getText();

    auto token_beg = code.find(token, character-first_character);
    if (token_beg != code.npos) {
        std::stringstream ss;
        ss << code.substr(0, token_beg)
        #if !defined(_WIN32) && !defined(_WIN64)
            << termcolor::colorize
        #endif 
            << termcolor::red << code.substr(token_beg, token.size()) << termcolor::reset << code.substr(token_beg + token.size());
        code = std::string{ss.str()};
    }
    
    return std::make_unique<RedeclaredVariableError>(prettify(path, -3, line, character, first_character, "Redeclared variable `" + utils::str_split(args, '~')[0] + "`, previously declared at line " + utils::str_split(args, '~')[1] + ":" + utils::str_split(args, '~')[2] + ".", code, in_fault));
}
std::unique_ptr<Error> RedeclaredVariableError::from(std::string const& path, antlr4::ParserRuleContext* ctx, antlr4::ParserRuleContext* in_fault, std::string const args...) {
    return this->from(path, ctx, in_fault->getStart(), args);
}

std::unique_ptr<Error> UndeclaredVariableError::from(std::string const& path, antlr4::ParserRuleContext* ctx, antlr4::Token* in_fault, std::string const args...) {
    int line = in_fault->getLine(),
        character = in_fault->getCharPositionInLine(),
        first_character = ctx->getStart()->getCharPositionInLine();
    std::string code = ctx->getStart()->getInputStream()->getText(antlr4::misc::Interval{ctx->getStart()->getStartIndex(), ctx->getStop()->getStopIndex()}),
                token = in_fault->getText();

    auto token_beg = code.find(token, character-first_character);
    if (token_beg != code.npos) {
        std::stringstream ss;
        ss << code.substr(0, token_beg)
        #if !defined(_WIN32) && !defined(_WIN64)
            << termcolor::colorize
        #endif 
            << termcolor::red << code.substr(token_beg, token.size()) << termcolor::reset << code.substr(token_beg + token.size());
        code = std::string{ss.str()};
    }
    
    return std::make_unique<RedeclaredVariableError>(prettify(path, 7, line, character, first_character, "Undeclared variable `" + args + "`.", code, in_fault));
}
std::unique_ptr<Error> UndeclaredVariableError::from(std::string const& path, antlr4::ParserRuleContext* ctx, antlr4::ParserRuleContext* in_fault, std::string const args...) {
    return this->from(path, ctx, in_fault->getStart(), args);
}

std::unique_ptr<Error> WrongTypedValueError::from(std::string const& path, antlr4::ParserRuleContext* ctx, antlr4::Token* in_fault, std::string const args...) {
    int line = in_fault->getLine(),
        character = in_fault->getCharPositionInLine(),
        first_character = ctx->getStart()->getCharPositionInLine();
    std::string code = ctx->getStart()->getInputStream()->getText(antlr4::misc::Interval{ctx->getStart()->getStartIndex(), ctx->getStop()->getStopIndex()}),
                token = in_fault->getText();

    auto token_beg = code.find(token, character-first_character);
    if (token_beg != code.npos) {
        std::stringstream ss;
        ss << code.substr(0, token_beg)
        #if !defined(_WIN32) && !defined(_WIN64)
            << termcolor::colorize
        #endif 
            << termcolor::red << code.substr(token_beg, token.size()) << termcolor::reset << code.substr(token_beg + token.size());
        code = std::string{ss.str()};
    };
    
    return std::make_unique<WrongTypedValueError>(prettify(path, line, -2, character, first_character, "Inconsistent types. Expected `" + utils::str_split(args, '~')[0] + "`, found `" + utils::str_split(args, '~')[1] + "` on variable declaration.", code, in_fault));
}
std::unique_ptr<Error> WrongTypedValueError::from(std::string const& path, antlr4::ParserRuleContext* ctx, antlr4::ParserRuleContext* in_fault, std::string const args...) {
    return this->from(path, ctx, in_fault->getStart(), args);
}

std::unique_ptr<Error> InvalidDeclaringTypeError::from(std::string const& path, antlr4::ParserRuleContext* ctx, antlr4::Token* in_fault, std::string const args...) {
    int line = in_fault->getLine(),
        character = in_fault->getCharPositionInLine(),
        first_character = ctx->getStart()->getCharPositionInLine();
    std::string code = ctx->getStart()->getInputStream()->getText(antlr4::misc::Interval{ctx->getStart()->getStartIndex(), ctx->getStop()->getStopIndex()}),
                token = in_fault->getText();

    auto token_beg = code.find(token, character-first_character);
    if (token_beg != code.npos) {
        std::stringstream ss;
        ss << code.substr(0, token_beg)
        #if !defined(_WIN32) && !defined(_WIN64)
            << termcolor::colorize
        #endif 
            << termcolor::red << code.substr(token_beg, token.size()) << termcolor::reset << code.substr(token_beg + token.size());
        code = std::string{ss.str()};
    }
    
    return std::make_unique<InvalidDeclaringTypeError>(prettify(path, 2, line, character, first_character, "Invalid variable declaration type `" + args + "`.", code, in_fault));
}
std::unique_ptr<Error> InvalidDeclaringTypeError::from(std::string const& path, antlr4::ParserRuleContext* ctx, antlr4::ParserRuleContext* in_fault, std::string const args...) {
    return this->from(path, ctx, in_fault->getStart(), args);
}

std::unique_ptr<Error> AlreadyExistingIDError::from(std::string const& path, antlr4::ParserRuleContext* ctx, antlr4::Token* in_fault, std::string const args...) {
    int line = in_fault->getLine(),
        character = in_fault->getCharPositionInLine(),
        first_character = ctx->getStart()->getCharPositionInLine();
    std::string code = ctx->getStart()->getInputStream()->getText(antlr4::misc::Interval{ctx->getStart()->getStartIndex(), ctx->getStop()->getStopIndex()}),
                token = in_fault->getText();

    auto token_beg = code.find(token, character-first_character);
    if (token_beg != code.npos) {
        std::stringstream ss;
        ss << code.substr(0, token_beg)
        #if !defined(_WIN32) && !defined(_WIN64)
            << termcolor::colorize
        #endif 
            << termcolor::red << code.substr(token_beg, token.size()) << termcolor::reset << code.substr(token_beg + token.size());
        code = std::string{ss.str()};
    }
    
    return std::make_unique<AlreadyExistingIDError>(prettify(path, 2, line, character, first_character, "Name `" + args + "` already taken.", code, in_fault));
}
std::unique_ptr<Error> AlreadyExistingIDError::from(std::string const& path, antlr4::ParserRuleContext* ctx, antlr4::ParserRuleContext* in_fault, std::string const args...) {
    return this->from(path, ctx, in_fault->getStart(), args);
}

std::unique_ptr<Error> UnknownIDError::from(std::string const& path, antlr4::ParserRuleContext* ctx, antlr4::Token* in_fault, std::string const args...) {
    int line = in_fault->getLine(),
        character = in_fault->getCharPositionInLine(),
        first_character = ctx->getStart()->getCharPositionInLine();
    std::string code = ctx->getStart()->getInputStream()->getText(antlr4::misc::Interval{ctx->getStart()->getStartIndex(), ctx->getStop()->getStopIndex()}),
                token = in_fault->getText();

    auto token_beg = code.find(token, character-first_character);
    if (token_beg != code.npos) {
        std::stringstream ss;
        ss << code.substr(0, token_beg)
        #if !defined(_WIN32) && !defined(_WIN64)
            << termcolor::colorize
        #endif 
            << termcolor::red << code.substr(token_beg, token.size()) << termcolor::reset << code.substr(token_beg + token.size());
        code = std::string{ss.str()};
    }
    
    return std::make_unique<UnknownIDError>(prettify(path, 2, line, character, first_character, "Unknown name `" + args + "`.", code, in_fault));
}
std::unique_ptr<Error> UnknownIDError::from(std::string const& path, antlr4::ParserRuleContext* ctx, antlr4::ParserRuleContext* in_fault, std::string const args...) {
    return this->from(path, ctx, in_fault->getStart(), args);
}

std::unique_ptr<Warning> ImplicitCastWarning::from(std::string const& path, antlr4::ParserRuleContext* ctx, antlr4::Token* in_fault, std::string const args...) {
    int line = in_fault->getLine(),
        character = in_fault->getCharPositionInLine(),
        first_character = ctx->getStart()->getCharPositionInLine();
    std::string code = ctx->getStart()->getInputStream()->getText(antlr4::misc::Interval{ctx->getStart()->getStartIndex(), ctx->getStop()->getStopIndex()}),
                token = in_fault->getText();

    auto token_beg = code.find(token, character-first_character);
    if (token_beg != code.npos) {
        std::stringstream ss;
        ss << code.substr(0, token_beg)
        #if !defined(_WIN32) && !defined(_WIN64)
            << termcolor::colorize
        #endif 
            << termcolor::yellow << code.substr(token_beg, token.size()) << termcolor::reset << code.substr(token_beg + token.size());
        code = std::string{ss.str()};
    }
    
    return std::make_unique<ImplicitCastWarning>(prettify(path, -4, line, character, first_character, "Implicit cast performed from type `" + utils::str_split(args, '~')[0] + "` to type `" + utils::str_split(args, '~')[1] + "`.", code, in_fault));
}
std::unique_ptr<Warning> ImplicitCastWarning::from(std::string const& path, antlr4::ParserRuleContext* ctx, antlr4::ParserRuleContext* in_fault, std::string const args...) {
    return this->from(path, ctx, in_fault->getStart(), args);
}