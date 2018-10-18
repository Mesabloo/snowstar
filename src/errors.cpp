#include <errors.hpp>

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

std::string Error::prettify(std::string const& file, int errCode, int line, int charac, int firstCharac, std::string const& msg, std::string const& code, antlr4::Token* tk) {
    std::stringstream ss;
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
        << " ├─╼"
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
        << " ╰┬╼ "
        << termcolor::reset << termcolor::green
        << file << " @ line " << std::to_string(line) << ":" << std::to_string(charac+1) << "\n"
        << termcolor::reset << termcolor::grey
    #if !defined(_WIN32) && !defined(_WIN64)
        << termcolor::bold
    #else
        << termcolor::reset << termcolor::white
    #endif
        << "  │" << spacer(" ", charac-firstCharac+4)
        << termcolor::reset << termcolor::red
        << spacer("↓", tk->getText().size())
        << termcolor::grey
    #if !defined(_WIN32) && !defined(_WIN64)
        << termcolor::bold
    #else
        << termcolor::reset << termcolor::white
    #endif
        << "\n"
        << "  ╰──╼" << " "
        << termcolor::reset
        << code
        << "\n";
    return std::string{ss.str()};
}
std::string Warning::prettify(std::string const& file, int errCode, int line, int charac, int firstCharac, std::string const& msg, std::string const& code, antlr4::Token* tk) {
    std::stringstream ss;
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
        << " ├─╼"
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
        << " ╰┬╼ "
        << termcolor::reset << termcolor::green
        << file << " @ line " << std::to_string(line) << ":" << std::to_string(charac+1) << "\n"
        << termcolor::reset << termcolor::grey
    #if !defined(_WIN32) && !defined(_WIN64)
        << termcolor::bold
    #else
        << termcolor::reset << termcolor::white
    #endif
        << "  │" << spacer(" ", charac-firstCharac+4)
        << termcolor::reset << termcolor::yellow
        << spacer("↓", tk->getText().size())
        << termcolor::grey
    #if !defined(_WIN32) && !defined(_WIN64)
        << termcolor::bold
    #else
        << termcolor::reset << termcolor::white
    #endif
        << "\n"
        << "  ╰──╼" << " "
        << termcolor::reset
        << code
        << "\n";
    return std::string{ss.str()};
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
    
    return std::make_unique<RedeclaredVariableError>(prettify(path, -3, line, character, first_character, "Redeclared variable `" + utils::str_split(args, ';')[0] + "`, previously declared at line " + utils::str_split(args, ';')[1] + ":" + utils::str_split(args, ';')[2] + ".", code, in_fault));
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
    
    return std::make_unique<WrongTypedValueError>(prettify(path, line, -2, character, first_character, "Inconsistent types. Expected `" + utils::str_split(args, ';')[0] + "`, found `" + utils::str_split(args, ';')[1] + "` on variable declaration.", code, in_fault));
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
    
    return std::make_unique<InvalidDeclaringTypeError>(prettify(path, 2, line, character, first_character, "Cannot declare a variable of type " + args + ".", code, in_fault));
}
std::unique_ptr<Error> InvalidDeclaringTypeError::from(std::string const& path, antlr4::ParserRuleContext* ctx, antlr4::ParserRuleContext* in_fault, std::string const args...) {
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
    
    return std::make_unique<ImplicitCastWarning>(prettify(path, -4, line, character, first_character, "Implicit cast performed from type `" + utils::str_split(args, ';')[0] + "` to type `" + utils::str_split(args, ';')[1] + "`.", code, in_fault));
}
std::unique_ptr<Warning> ImplicitCastWarning::from(std::string const& path, antlr4::ParserRuleContext* ctx, antlr4::ParserRuleContext* in_fault, std::string const args...) {
    return this->from(path, ctx, in_fault->getStart(), args);
}