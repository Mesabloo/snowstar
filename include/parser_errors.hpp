#ifndef PARSER_ERRORS_HPP
#define PARSER_ERRORS_HPP

#include <errors.hpp>

struct MissingTokenError : Error {
    MissingTokenError() = default;
#if !defined(_WIN32) && !defined(_WIN64)
    MissingTokenError(std::string const& msg) : Error{msg} {}
#else
    MissingTokenError(std::wstring const& msg) : Error{msg} {}
#endif

    virtual std::unique_ptr<Error> from(std::string const&, antlr4::ParserRuleContext*, antlr4::Token*, std::string const...);
    virtual std::unique_ptr<Error> from(std::string const&, antlr4::ParserRuleContext*, antlr4::ParserRuleContext*, std::string const...);
};

struct InvalidStatementError : Error {
    InvalidStatementError() = default;
#if !defined(_WIN32) && !defined(_WIN64)
    InvalidStatementError(std::string const& msg) : Error{msg} {}
#else
    InvalidStatementError(std::wstring const& msg) : Error{msg} {}
#endif

    virtual std::unique_ptr<Error> from(std::string const&, antlr4::ParserRuleContext*, antlr4::Token*, std::string const...);
    virtual std::unique_ptr<Error> from(std::string const&, antlr4::ParserRuleContext*, antlr4::ParserRuleContext*, std::string const...);
};

#endif