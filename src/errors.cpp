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

std::unique_ptr<Error> RedeclaredVariableError::from(antlr4::ParserRuleContext* ctx, antlr4::Token* in_fault, std::string const args...) {
    int line = in_fault->getLine(),
        character = in_fault->getCharPositionInLine(),
        first_character = ctx->getStart()->getCharPositionInLine();
    std::string code = ctx->getStart()->getInputStream()->getText(antlr4::misc::Interval{ctx->getStart()->getStartIndex(), ctx->getStop()->getStopIndex()}),
                token = in_fault->getText();

    auto token_beg = code.find(token);
    if (token_beg != code.npos) {
        std::stringstream ss;
        ss << code.substr(0, token_beg) << termcolor::colorize << termcolor::red << code.substr(token_beg, token.size()) << termcolor::reset << code.substr(token_beg + token.size());
        code = std::string{ss.str()};
    }

    std::stringstream ss;
    ss << "Redeclared variable `" << args << "` at line " << std::to_string(line) << ":" << std::to_string(character+1) << "\n"
        << termcolor::colorize << code << "\n"
        << spacer(" ", character-first_character) << termcolor::red << "^" << spacer("~", token.size()-1) << termcolor::reset;
    
    return std::make_unique<RedeclaredVariableError>(std::string{ss.str()});
}
std::unique_ptr<Error> RedeclaredVariableError::from(antlr4::ParserRuleContext* ctx, antlr4::ParserRuleContext* in_fault, std::string const args...) {
    return this->from(ctx, in_fault->getStart(), args);
}

std::unique_ptr<Error> WrongTypedValueError::from(antlr4::ParserRuleContext* ctx, antlr4::Token* in_fault, std::string const args...) {
    int line = in_fault->getLine(),
        character = in_fault->getCharPositionInLine(),
        first_character = ctx->getStart()->getCharPositionInLine();
    std::string code = ctx->getStart()->getInputStream()->getText(antlr4::misc::Interval{ctx->getStart()->getStartIndex(), ctx->getStop()->getStopIndex()}),
                token = in_fault->getText();

    auto token_beg = code.find(token);
    if (token_beg != code.npos) {
        std::stringstream ss;
        ss << code.substr(0, token_beg) << termcolor::colorize << termcolor::red << code.substr(token_beg, token.size()) << termcolor::reset << code.substr(token_beg + token.size());
        code = std::string{ss.str()};
    }

    std::stringstream ss;
    ss << "Inconsistent types, expected `" << utils::str_split(args, ';')[0] << "` found `" << utils::str_split(args, ';')[1] << "` on variable declaration at line " << std::to_string(line) << ":" << std::to_string(character+1) << "\n"
        << termcolor::colorize << code << "\n"
        << spacer(" ", character-first_character) << termcolor::red << "^" << spacer("~", token.size()-1) << termcolor::reset;
    
    return std::make_unique<WrongTypedValueError>(std::string{ss.str()});
}
std::unique_ptr<Error> WrongTypedValueError::from(antlr4::ParserRuleContext* ctx, antlr4::ParserRuleContext* in_fault, std::string const args...) {
    return this->from(ctx, in_fault->getStart(), args);
}

std::unique_ptr<Error> InvalidDeclaringTypeError::from(antlr4::ParserRuleContext* ctx, antlr4::Token* in_fault, std::string const args...) {
    int line = in_fault->getLine(),
        character = in_fault->getCharPositionInLine(),
        first_character = ctx->getStart()->getCharPositionInLine();
    std::string code = ctx->getStart()->getInputStream()->getText(antlr4::misc::Interval{ctx->getStart()->getStartIndex(), ctx->getStop()->getStopIndex()}),
                token = in_fault->getText();

    auto token_beg = code.find(token);
    if (token_beg != code.npos) {
        std::stringstream ss;
        ss << code.substr(0, token_beg) << termcolor::colorize << termcolor::red << code.substr(token_beg, token.size()) << termcolor::reset << code.substr(token_beg + token.size());
        code = std::string{ss.str()};
    }

    std::stringstream ss;
    ss << "Cannot declare a variable of type void at line " << std::to_string(line) << ":" << std::to_string(character+1) << "\n"
        << termcolor::colorize << code << "\n"
        << spacer(" ", character-first_character) << termcolor::red << "^" << spacer("~", token.size()-1) << termcolor::reset;
    
    return std::make_unique<InvalidDeclaringTypeError>(std::string{ss.str()});
}
std::unique_ptr<Error> InvalidDeclaringTypeError::from(antlr4::ParserRuleContext* ctx, antlr4::ParserRuleContext* in_fault, std::string const args...) {
    return this->from(ctx, in_fault->getStart(), args);
}

std::unique_ptr<Warning> ImplicitCastWarning::from(antlr4::ParserRuleContext* ctx, antlr4::Token* in_fault, std::string const args...) {
    int line = in_fault->getLine(),
        character = in_fault->getCharPositionInLine(),
        first_character = ctx->getStart()->getCharPositionInLine();
    std::string code = ctx->getStart()->getInputStream()->getText(antlr4::misc::Interval{ctx->getStart()->getStartIndex(), ctx->getStop()->getStopIndex()}),
                token = in_fault->getText();

    auto token_beg = code.find(token);
    if (token_beg != code.npos) {
        std::stringstream ss;
        ss << code.substr(0, token_beg) << termcolor::colorize << termcolor::yellow << code.substr(token_beg, token.size()) << termcolor::reset << code.substr(token_beg + token.size());
        code = std::string{ss.str()};
    }

    std::stringstream ss;
    ss << "Implicit cast performed from type `" << utils::str_split(args, ';')[0] << "` to type `" << utils::str_split(args, ';')[1] << "` at line " << std::to_string(line) << ":" << std::to_string(character+1) << "\n"
        << termcolor::colorize << code << "\n"
        << spacer(" ", character-first_character) << termcolor::yellow << "^" << spacer("~", token.size()-1) << termcolor::reset;
    
    return std::make_unique<ImplicitCastWarning>(std::string{ss.str()});
}
std::unique_ptr<Warning> ImplicitCastWarning::from(antlr4::ParserRuleContext* ctx, antlr4::ParserRuleContext* in_fault, std::string const args...) {
    return this->from(ctx, in_fault->getStart(), args);
}