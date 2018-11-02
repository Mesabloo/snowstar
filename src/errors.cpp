#include <errors.hpp>


#if !defined(_WIN32) && !defined(_WIN64)
std::string 
#else
std::wstring
#endif
Error::prettify(std::string const& file, int line, int charac, int firstCharac, std::string const& msg, std::string const& code, std::variant<antlr4::Token*, antlr4::ParserRuleContext*> tk) {
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
        << "\n";
    #if !defined(_WIN32) && !defined(_WIN64)
    return std::string{ss.str()};
    #else
    return std::wstring{ss.str()};
    #endif
}

#if !defined(_WIN32) && !defined(_WIN64)
std::string 
#else
std::wstring
#endif
Warning::prettify(std::string const& file, int line, int charac, int firstCharac, std::string const& msg, std::string const& code, std::variant<antlr4::Token*, antlr4::ParserRuleContext*> tk) {
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
        << termcolor::reset << termcolor::yellow;
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
    ss << termcolor::grey
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

std::unique_ptr<Error> RedeclaredVariableError::from(std::string const& path, antlr4::ParserRuleContext* ctx, antlr4::Token* in_fault, std::initializer_list<std::string> const args) {
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
    
    return std::make_unique<RedeclaredVariableError>(prettify(path, line, character, first_character, "Redeclared variable `" + *(args.begin()+0) + "`, previously declared at line " + *(args.begin()+1) + ":" + *(args.begin()+2) + ".", code, in_fault));
}
std::unique_ptr<Error> RedeclaredVariableError::from(std::string const& path, antlr4::ParserRuleContext* ctx, antlr4::ParserRuleContext* in_fault, std::initializer_list<std::string> const args) {
    int line = in_fault->getStart()->getLine(),
        character = in_fault->getStart()->getCharPositionInLine(),
        first_character = ctx->getStart()->getCharPositionInLine();
    std::string code = ctx->getStart()->getInputStream()->getText(antlr4::misc::Interval{in_fault->getStart()->getStartIndex(), in_fault->getStop()->getStopIndex()}),
                token = ctx->getStart()->getInputStream()->getText(antlr4::misc::Interval{in_fault->getStart()->getStartIndex(), in_fault->getStop()->getStopIndex()});

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
    
    return std::make_unique<RedeclaredVariableError>(prettify(path, line, character, first_character, "Redeclared variable `" + *(args.begin()+0) + "`, previously declared at line " + *(args.begin()+1) + ":" + *(args.begin()+2) + ".", code, in_fault));
}

std::unique_ptr<Error> UndeclaredVariableError::from(std::string const& path, antlr4::ParserRuleContext* ctx, antlr4::Token* in_fault, std::initializer_list<std::string> const args) {
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
    
    return std::make_unique<RedeclaredVariableError>(prettify(path, line, character, first_character, "Undeclared variable `" + *(args.begin()+0) + "`.", code, in_fault));
}
std::unique_ptr<Error> UndeclaredVariableError::from(std::string const& path, antlr4::ParserRuleContext* ctx, antlr4::ParserRuleContext* in_fault, std::initializer_list<std::string> const args) {
    int line = in_fault->getStart()->getLine(),
        character = in_fault->getStart()->getCharPositionInLine(),
        first_character = ctx->getStart()->getCharPositionInLine();
    std::string code = ctx->getStart()->getInputStream()->getText(antlr4::misc::Interval{ctx->getStart()->getStartIndex(), ctx->getStop()->getStopIndex()}),
                token = ctx->getStart()->getInputStream()->getText(antlr4::misc::Interval{in_fault->getStart()->getStartIndex(), in_fault->getStop()->getStopIndex()});

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

    return std::make_unique<RedeclaredVariableError>(prettify(path, line, character, first_character, "Undeclared variable `" + *(args.begin()+0) + "`.", code, in_fault));
}

std::unique_ptr<Error> WrongTypedValueError::from(std::string const& path, antlr4::ParserRuleContext* ctx, antlr4::Token* in_fault, std::initializer_list<std::string> const args) {
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
    
    return std::make_unique<WrongTypedValueError>(prettify(path, line, character, first_character, "Inconsistent types. Expected `" + *(args.begin()+0) + "`, found `" + *(args.begin()+1) + "` " + *(args.begin()+2) + ".", code, in_fault));
}
std::unique_ptr<Error> WrongTypedValueError::from(std::string const& path, antlr4::ParserRuleContext* ctx, antlr4::ParserRuleContext* in_fault, std::initializer_list<std::string> const args) {
    int line = in_fault->getStart()->getLine(),
        character = in_fault->getStart()->getCharPositionInLine(),
        first_character = ctx->getStart()->getCharPositionInLine();
    std::string code = ctx->getStart()->getInputStream()->getText(antlr4::misc::Interval{ctx->getStart()->getStartIndex(), ctx->getStop()->getStopIndex()}),
                token = ctx->getStart()->getInputStream()->getText(antlr4::misc::Interval{in_fault->getStart()->getStartIndex(), in_fault->getStop()->getStopIndex()});

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

    return std::make_unique<WrongTypedValueError>(prettify(path, line, character, first_character, "Inconsistent types. Expected `" + *(args.begin()+0) + "`, found `" + *(args.begin()+1) + "` " + *(args.begin()+2) + ".", code, in_fault));
}

std::unique_ptr<Error> InvalidDeclaringTypeError::from(std::string const& path, antlr4::ParserRuleContext* ctx, antlr4::Token* in_fault, std::initializer_list<std::string> const args) {
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
    
    return std::make_unique<InvalidDeclaringTypeError>(prettify(path, line, character, first_character, "Invalid variable declaration type `" + *(args.begin()+0) + "`.", code, in_fault));
}
std::unique_ptr<Error> InvalidDeclaringTypeError::from(std::string const& path, antlr4::ParserRuleContext* ctx, antlr4::ParserRuleContext* in_fault, std::initializer_list<std::string> const args) {
    int line = in_fault->getStart()->getLine(),
        character = in_fault->getStart()->getCharPositionInLine(),
        first_character = ctx->getStart()->getCharPositionInLine();
    std::string code = ctx->getStart()->getInputStream()->getText(antlr4::misc::Interval{ctx->getStart()->getStartIndex(), ctx->getStop()->getStopIndex()}),
                token = ctx->getStart()->getInputStream()->getText(antlr4::misc::Interval{in_fault->getStart()->getStartIndex(), in_fault->getStop()->getStopIndex()});

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
    
    return std::make_unique<InvalidDeclaringTypeError>(prettify(path, line, character, first_character, "Invalid variable declaration type `" + *(args.begin()+0) + "`.", code, in_fault));
}

std::unique_ptr<Error> AlreadyExistingIDError::from(std::string const& path, antlr4::ParserRuleContext* ctx, antlr4::Token* in_fault, std::initializer_list<std::string> const args) {
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
    
    return std::make_unique<AlreadyExistingIDError>(prettify(path, line, character, first_character, "Name `" + *(args.begin()+0) + "` already taken.", code, in_fault));
}
std::unique_ptr<Error> AlreadyExistingIDError::from(std::string const& path, antlr4::ParserRuleContext* ctx, antlr4::ParserRuleContext* in_fault, std::initializer_list<std::string> const args) {
    int line = in_fault->getStart()->getLine(),
        character = in_fault->getStart()->getCharPositionInLine(),
        first_character = ctx->getStart()->getCharPositionInLine();
    std::string code = ctx->getStart()->getInputStream()->getText(antlr4::misc::Interval{ctx->getStart()->getStartIndex(), ctx->getStop()->getStopIndex()}),
                token = ctx->getStart()->getInputStream()->getText(antlr4::misc::Interval{in_fault->getStart()->getStartIndex(), in_fault->getStop()->getStopIndex()});

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

    return std::make_unique<AlreadyExistingIDError>(prettify(path, line, character, first_character, "Name `" + *(args.begin()+0) + "` already taken.", code, in_fault));
}

std::unique_ptr<Error> UnknownIDError::from(std::string const& path, antlr4::ParserRuleContext* ctx, antlr4::Token* in_fault, std::initializer_list<std::string> const args) {
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
    
    return std::make_unique<UnknownIDError>(prettify(path, line, character, first_character, "Unknown name `" + *(args.begin()+0) + "`.", code, in_fault));
}
std::unique_ptr<Error> UnknownIDError::from(std::string const& path, antlr4::ParserRuleContext* ctx, antlr4::ParserRuleContext* in_fault, std::initializer_list<std::string> const args) {
    int line = in_fault->getStart()->getLine(),
        character = in_fault->getStart()->getCharPositionInLine(),
        first_character = ctx->getStart()->getCharPositionInLine();
    std::string code = ctx->getStart()->getInputStream()->getText(antlr4::misc::Interval{ctx->getStart()->getStartIndex(), ctx->getStop()->getStopIndex()}),
                token = ctx->getStart()->getInputStream()->getText(antlr4::misc::Interval{in_fault->getStart()->getStartIndex(), in_fault->getStop()->getStopIndex()});

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

    return std::make_unique<UnknownIDError>(prettify(path, line, character, first_character, "Unknown name `" + *(args.begin()+0) + "`.", code, in_fault));
}

std::unique_ptr<Warning> ImplicitCastWarning::from(std::string const& path, antlr4::ParserRuleContext* ctx, antlr4::Token* in_fault, std::initializer_list<std::string> const args) {
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
    
    return std::make_unique<ImplicitCastWarning>(prettify(path, line, character, first_character, "Implicit cast performed from type `" + *(args.begin()+0) + "` to type `" + *(args.begin()+1) + "`.", code, in_fault));
}
std::unique_ptr<Warning> ImplicitCastWarning::from(std::string const& path, antlr4::ParserRuleContext* ctx, antlr4::ParserRuleContext* in_fault, std::initializer_list<std::string> const args) {
    int line = in_fault->getStart()->getLine(),
        character = in_fault->getStart()->getCharPositionInLine(),
        first_character = ctx->getStart()->getCharPositionInLine();
    std::string code = ctx->getStart()->getInputStream()->getText(antlr4::misc::Interval{ctx->getStart()->getStartIndex(), ctx->getStop()->getStopIndex()}),
                token = ctx->getStart()->getInputStream()->getText(antlr4::misc::Interval{in_fault->getStart()->getStartIndex(), in_fault->getStop()->getStopIndex()});

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

    return std::make_unique<ImplicitCastWarning>(prettify(path, line, character, first_character, "Implicit cast performed from type `" + *(args.begin()+0) + "` to type `" + *(args.begin()+1) + "`.", code, in_fault));
}