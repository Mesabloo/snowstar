#include <parser_errors.hpp>

std::unique_ptr<Error> MissingTokenError::from(std::string const& path, antlr4::ParserRuleContext* ctx, antlr4::Token* in_fault, std::string const args...) {
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

    return std::make_unique<MissingTokenError>(prettify(path, 15, line, character, first_character, "Missing " + utils::str_split(args, '~')[0] + " after `" + utils::str_split(args, '~')[1] + "` token.", code, in_fault));
}

std::unique_ptr<Error> MissingTokenError::from(std::string const& path, antlr4::ParserRuleContext* ctx, antlr4::ParserRuleContext* in_fault, std::string const args...) {
    return from(path, ctx, in_fault->getStart(), args);
}

std::unique_ptr<Error> InvalidStatementError::from(std::string const& path, antlr4::ParserRuleContext* ctx, antlr4::Token*, std::string const args...) {
    int line = ctx->getStart()->getLine(),
        character = 1,
        first_character = ctx->getStart()->getCharPositionInLine();
    std::string code = ctx->getText(),
                token = ctx->getText();

    auto token_beg = code.find(token, character-1-first_character);
    if (token_beg != code.npos) {
        std::stringstream ss;
        ss << code.substr(0, token_beg)
        #if !defined(_WIN32) && !defined(_WIN64)
            << termcolor::colorize
        #endif 
            << termcolor::red << code.substr(token_beg, token.size()) << termcolor::reset << code.substr(token_beg + token.size());
        code = std::string{ss.str()};
    }

    return std::make_unique<InvalidStatementError>(prettify(path, -9, line, character-1, first_character, "Invalid statement.", code, ctx->getStart()));
}

std::unique_ptr<Error> InvalidStatementError::from(std::string const& path, antlr4::ParserRuleContext* ctx, antlr4::ParserRuleContext* in_fault, std::string const args...) {
    return from(path, ctx, in_fault->getStart(), args);
}