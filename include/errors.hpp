#ifndef ERRORS_HPP
#define ERRORS_HPP

#include <string>
#include <sstream>
#include <memory>
#include <vector>

#include <antlr4-runtime.h>

#include <termcolor/termcolor.hpp>

class Error {
public:
    Error() = default;
    Error(std::string const& msg) : m_msg{msg} {}

    virtual std::unique_ptr<Error> from(std::string const&, antlr4::ParserRuleContext*, antlr4::ParserRuleContext*, std::string const...) = 0;
    virtual std::unique_ptr<Error> from(std::string const&, antlr4::ParserRuleContext*, antlr4::Token*, std::string const...) = 0;

    std::string getError() const { return m_msg; }
protected:
    std::string m_msg;

    std::function<std::string(std::string const, unsigned int)> spacer = [=] (std::string const s1, unsigned int n) -> std::string { std::string s; for (unsigned int tmp{0};tmp < n;++tmp) s+=s1; return s; };

    std::string prettify(std::string const&, int, int, int, int, std::string const&, std::string const&, antlr4::Token*);
};

struct RedeclaredVariableError : Error {
    RedeclaredVariableError() = default;
    RedeclaredVariableError(std::string const& msg) : Error(msg) {}

    virtual std::unique_ptr<Error> from(std::string const&, antlr4::ParserRuleContext*, antlr4::Token*, std::string const...);
    virtual std::unique_ptr<Error> from(std::string const&, antlr4::ParserRuleContext*, antlr4::ParserRuleContext*, std::string const...);
};

struct WrongTypedValueError : Error {
    WrongTypedValueError() = default;
    WrongTypedValueError(std::string const& msg) : Error(msg) {}

    virtual std::unique_ptr<Error> from(std::string const&, antlr4::ParserRuleContext*, antlr4::Token*, std::string const...);
    virtual std::unique_ptr<Error> from(std::string const&, antlr4::ParserRuleContext*, antlr4::ParserRuleContext*, std::string const...);
};

struct InvalidDeclaringTypeError : Error {
    InvalidDeclaringTypeError() = default;
    InvalidDeclaringTypeError(std::string const& msg) : Error(msg) {}

    virtual std::unique_ptr<Error> from(std::string const&, antlr4::ParserRuleContext*, antlr4::Token*, std::string const...);
    virtual std::unique_ptr<Error> from(std::string const&, antlr4::ParserRuleContext*, antlr4::ParserRuleContext*, std::string const...);
};

struct UndeclaredVariableError : Error {
    UndeclaredVariableError() = default;
    UndeclaredVariableError(std::string const& msg) : Error(msg) {}

    virtual std::unique_ptr<Error> from(std::string const&, antlr4::ParserRuleContext*, antlr4::Token*, std::string const...);
    virtual std::unique_ptr<Error> from(std::string const&, antlr4::ParserRuleContext*, antlr4::ParserRuleContext*, std::string const...);
};

class Warning {
public:
    Warning() = default;
    Warning(std::string const& msg) : m_msg{msg} {}

    virtual std::unique_ptr<Warning> from(std::string const&, antlr4::ParserRuleContext*, antlr4::ParserRuleContext*, std::string const...) = 0;
    virtual std::unique_ptr<Warning> from(std::string const&, antlr4::ParserRuleContext*, antlr4::Token*, std::string const...) = 0;

    std::string getError() const { return m_msg; }
protected:
    std::string m_msg;
    std::function<std::string(std::string const, unsigned int)> spacer = [=] (std::string const s1, unsigned int n) -> std::string { std::string s; for (unsigned int tmp{0};tmp < n;++tmp) s+=s1; return s; };

    std::string prettify(std::string const&, int, int, int, int, std::string const&, std::string const&, antlr4::Token*);
};

struct ImplicitCastWarning : Warning {
    ImplicitCastWarning() = default;
    ImplicitCastWarning(std::string const& msg) : Warning(msg) {}

    virtual std::unique_ptr<Warning> from(std::string const&, antlr4::ParserRuleContext*, antlr4::ParserRuleContext*, std::string const...);
    virtual std::unique_ptr<Warning> from(std::string const&, antlr4::ParserRuleContext*, antlr4::Token*, std::string const...);
};

#endif