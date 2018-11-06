#ifndef ERRORS_HPP
#define ERRORS_HPP

#include <string>
#include <sstream>
#include <memory>
#include <vector>
#include <initializer_list>
#include <variant>

#include <antlr4-runtime.h>

#include <termcolor/termcolor.hpp>

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

class Error {
public:
    Error() = default;
#if !defined(_WIN32) && !defined(_WIN64)
    Error(std::string const& msg) : m_msg{msg} {}
#else
    Error(std::wstring const& msg) : m_msg{msg} {}
#endif

    virtual std::unique_ptr<Error> from(std::string const&, antlr4::ParserRuleContext*, antlr4::ParserRuleContext*, std::initializer_list<std::string> const) = 0;
    virtual std::unique_ptr<Error> from(std::string const&, antlr4::ParserRuleContext*, antlr4::Token*, std::initializer_list<std::string> const) = 0;

#if !defined(_WIN32) && !defined(_WIN64)
    std::string getError() const { return m_msg; }
protected:
    std::string m_msg;

    std::function<std::string(std::string const, unsigned int)> spacer = [=] (std::string const s1, unsigned int n) -> std::string { std::string s; for (unsigned int tmp{0};tmp < n;++tmp) s+=s1; return s; };
    std::string prettify(std::string const&, int, int, int, std::string const&, std::string const&, std::variant<antlr4::Token*, antlr4::ParserRuleContext*>);
#else
    std::wstring getError() const { return m_msg; }
protected:
    std::wstring m_msg;

    std::function<std::wstring(std::wstring const, unsigned int)> spacer = [=] (std::wstring const s1, unsigned int n) -> std::wstring { std::wstring s; for (unsigned int tmp{0};tmp < n;++tmp) s+=s1; return s; };
    std::wstring prettify(std::string const&, int, int, int, std::string const&, std::string const&, std::variant<antlr4::Token*, antlr4::ParserRuleContext*>);
#endif
};

struct RedeclaredVariableError : Error {
    RedeclaredVariableError() = default;
#if !defined(_WIN32) && !defined(_WIN64)
    RedeclaredVariableError(std::string const& msg) : Error{msg} {}
#else
    RedeclaredVariableError(std::wstring const& msg) : Error{msg} {}
#endif

    virtual std::unique_ptr<Error> from(std::string const&, antlr4::ParserRuleContext*, antlr4::Token*, std::initializer_list<std::string> const);
    virtual std::unique_ptr<Error> from(std::string const&, antlr4::ParserRuleContext*, antlr4::ParserRuleContext*, std::initializer_list<std::string> const);
};

struct WrongTypedValueError : Error {
    WrongTypedValueError() = default;
#if !defined(_WIN32) && !defined(_WIN64)
    WrongTypedValueError(std::string const& msg) : Error{msg} {}
#else
    WringTypedValueError(std::wstring const& msg) : Error{msg} {}
#endif

    virtual std::unique_ptr<Error> from(std::string const&, antlr4::ParserRuleContext*, antlr4::Token*, std::initializer_list<std::string> const);
    virtual std::unique_ptr<Error> from(std::string const&, antlr4::ParserRuleContext*, antlr4::ParserRuleContext*, std::initializer_list<std::string> const);
};

struct InvalidDeclaringTypeError : Error {
    InvalidDeclaringTypeError() = default;
#if !defined(_WIN32) && !defined(_WIN64)
    InvalidDeclaringTypeError(std::string const& msg) : Error{msg} {}
#else
    InvalidDeclaringTypeError(std::wstring const& msg) : Error{msg} {}
#endif

    virtual std::unique_ptr<Error> from(std::string const&, antlr4::ParserRuleContext*, antlr4::Token*, std::initializer_list<std::string> const);
    virtual std::unique_ptr<Error> from(std::string const&, antlr4::ParserRuleContext*, antlr4::ParserRuleContext*, std::initializer_list<std::string> const);
};

struct InvalidComparisonTypeError : Error {
    InvalidComparisonTypeError() = default;
#if !defined(_WIN32) && !defined(_WIN64)
    InvalidComparisonTypeError(std::string const& msg) : Error{msg} {}
#else
    InvalidComparisonTypeError(std::wstring const& msg) : Error{msg} {}
#endif

    virtual std::unique_ptr<Error> from(std::string const&, antlr4::ParserRuleContext*, antlr4::Token*, std::initializer_list<std::string> const);
    virtual std::unique_ptr<Error> from(std::string const&, antlr4::ParserRuleContext*, antlr4::ParserRuleContext*, std::initializer_list<std::string> const);
};

struct UndeclaredVariableError : Error {
    UndeclaredVariableError() = default;
#if !defined(_WIN32) && !defined(_WIN64)
    UndeclaredVariableError(std::string const& msg) : Error{msg} {}
#else
    UndeclaredVariableError(std::wstring const& msg) : Error{msg} {}
#endif

    virtual std::unique_ptr<Error> from(std::string const&, antlr4::ParserRuleContext*, antlr4::Token*, std::initializer_list<std::string> const);
    virtual std::unique_ptr<Error> from(std::string const&, antlr4::ParserRuleContext*, antlr4::ParserRuleContext*, std::initializer_list<std::string> const);
};

struct UndefinedVariableError : Error {
    UndefinedVariableError() = default;
#if !defined(_WIN32) && !defined(_WIN64)
    UndefinedVariableError(std::string const& msg) : Error{msg} {}
#else
    UndefinedVariableError(std::wstring const& msg) : Error{msg} {}
#endif

    virtual std::unique_ptr<Error> from(std::string const&, antlr4::ParserRuleContext*, antlr4::Token*, std::initializer_list<std::string> const);
    virtual std::unique_ptr<Error> from(std::string const&, antlr4::ParserRuleContext*, antlr4::ParserRuleContext*, std::initializer_list<std::string> const);
};

struct AlreadyExistingIDError: Error {
    AlreadyExistingIDError() = default;
#if !defined(_WIN32) && !defined(_WIN64)
    AlreadyExistingIDError(std::string const& msg) : Error{msg} {}
#else
    AlreadyExistingIDError(std::wstring const& msg) : Error{msg} {}
#endif

    virtual std::unique_ptr<Error> from(std::string const&, antlr4::ParserRuleContext*, antlr4::Token*, std::initializer_list<std::string> const);
    virtual std::unique_ptr<Error> from(std::string const&, antlr4::ParserRuleContext*, antlr4::ParserRuleContext*, std::initializer_list<std::string> const);
};

struct UnknownIDError: Error {
    UnknownIDError() = default;
#if !defined(_WIN32) && !defined(_WIN64)
    UnknownIDError(std::string const& msg) : Error{msg} {}
#else
    UnknownIDError(std::wstring const& msg) : Error{msg} {}
#endif

    virtual std::unique_ptr<Error> from(std::string const&, antlr4::ParserRuleContext*, antlr4::Token*, std::initializer_list<std::string> const);
    virtual std::unique_ptr<Error> from(std::string const&, antlr4::ParserRuleContext*, antlr4::ParserRuleContext*, std::initializer_list<std::string> const);
};

class Warning {
public:
    Warning() = default;
#if !defined(_WIN32) && !defined(_WIN64)
    Warning(std::string const& msg) : m_msg{msg} {}
#else
    Warning(std::wstring const& msg) : m_msg{msg} {}
#endif

    virtual std::unique_ptr<Warning> from(std::string const&, antlr4::ParserRuleContext*, antlr4::ParserRuleContext*, std::initializer_list<std::string> const) = 0;
    virtual std::unique_ptr<Warning> from(std::string const&, antlr4::ParserRuleContext*, antlr4::Token*, std::initializer_list<std::string> const) = 0;

#if !defined(_WIN32) && !defined(_WIN64)
    std::string getError() const { return m_msg; }
protected:
    std::string m_msg;

    std::function<std::string(std::string const, unsigned int)> spacer = [=] (std::string const s1, unsigned int n) -> std::string { std::string s; for (unsigned int tmp{0};tmp < n;++tmp) s+=s1; return s; };
    std::string prettify(std::string const&, int, int, int, std::string const&, std::string const&, std::variant<antlr4::Token*, antlr4::ParserRuleContext*>);
#else
    std::wstring getError() const { return m_msg; }
protected:
    std::wstring m_msg;

    std::function<std::wstring(std::wstring const, unsigned int)> spacer = [=] (std::wstring const s1, unsigned int n) -> std::wstring { std::wstring s; for (unsigned int tmp{0};tmp < n;++tmp) s+=s1; return s; };
    std::wstring prettify(std::string const&, int, int, int, std::string const&, std::string const&, std::variant<antlr4::Token*, antlr4::ParserRuleContext*>);
    
#endif
};

struct ImplicitCastWarning : Warning {
    ImplicitCastWarning() = default;
#if !defined(_WIN32) && !defined(_WIN64)
    ImplicitCastWarning(std::string const& msg) : Warning{msg} {}
#else
    ImplicitCastWarning(std::wstring const& msg) : Warning{msg} {}
#endif

    virtual std::unique_ptr<Warning> from(std::string const&, antlr4::ParserRuleContext*, antlr4::ParserRuleContext*, std::initializer_list<std::string> const);
    virtual std::unique_ptr<Warning> from(std::string const&, antlr4::ParserRuleContext*, antlr4::Token*, std::initializer_list<std::string> const);
};

struct FloatingPointWarning : Warning {
    FloatingPointWarning() = default;
#if !defined(_WIN32) && !defined(_WIN64)
    FloatingPointWarning(std::string const& msg) : Warning{msg} {}
#else
    FloatingPointWarning(std::wstring const& msg) : Warning{msg} {}
#endif

    virtual std::unique_ptr<Warning> from(std::string const&, antlr4::ParserRuleContext*, antlr4::ParserRuleContext*, std::initializer_list<std::string> const);
    virtual std::unique_ptr<Warning> from(std::string const&, antlr4::ParserRuleContext*, antlr4::Token*, std::initializer_list<std::string> const);
};

#endif