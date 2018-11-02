#include <parser_errors.hpp>

std::unique_ptr<Error> MissingTokenError::from(std::string const& path, antlr4::ParserRuleContext* ctx, antlr4::Token* in_fault, std::initializer_list<std::string> const args) {
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

    return std::make_unique<MissingTokenError>(prettify(path, line, character, first_character, "Missing " + *(args.begin()+0) + " after `" + *(args.begin()+1) + "` token.", code, in_fault));
}

std::unique_ptr<Error> MissingTokenError::from(std::string const& path, antlr4::ParserRuleContext* ctx, antlr4::ParserRuleContext* in_fault, std::initializer_list<std::string> const args) {
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

    return std::make_unique<MissingTokenError>(prettify(path, line, character, first_character, "Missing " + *(args.begin()+0) + " after `" + *(args.begin()+1) + "` token.", code, in_fault));
}