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

class Throwable {
protected:
#   if !defined(_WIN32) && !defined(_WIN64)
    std::function<std::string(std::string const, unsigned int)> spacer = [=] (std::string const s1, unsigned int n) -> std::string { std::string s; for (unsigned int tmp{0};tmp < n;++tmp) s+=s1; return s; };
#   else
    std::function<std::wstring(std::wstring const, unsigned int)> spacer = [=] (std::wstring const s1, unsigned int n) -> std::wstring { std::wstring s; for (unsigned int tmp{0};tmp < n;++tmp) s+=s1; return s; };
#   endif

    void printPrettify(std::string const&, int, int, int, std::string const&, std::string const&, std::variant<antlr4::Token*, antlr4::ParserRuleContext*>, bool);
    void colorCode(std::string&, std::string const&, antlr4::ParserRuleContext*, std::variant<antlr4::Token*, antlr4::ParserRuleContext*>, bool);
    void initWithTextError(std::string const&, std::string const&, antlr4::ParserRuleContext*, std::variant<antlr4::Token*, antlr4::ParserRuleContext*>, bool);

public:
    Throwable() = default;
    virtual ~Throwable() = default;

    virtual void print(std::string const&, antlr4::ParserRuleContext*, std::variant<antlr4::Token*, antlr4::ParserRuleContext*>, std::initializer_list<std::string> const) = 0;
};

/**
 * Errors
 */

struct RedeclaredVariableError : public Throwable {
    RedeclaredVariableError() : Throwable() {}
    virtual ~RedeclaredVariableError() override = default;

    virtual void print(std::string const&, antlr4::ParserRuleContext*, std::variant<antlr4::Token*, antlr4::ParserRuleContext*>, std::initializer_list<std::string> const) override;
};

struct WrongTypedValueError : public Throwable {
    WrongTypedValueError() : Throwable() {}
    virtual ~WrongTypedValueError() override = default;

    virtual void print(std::string const&, antlr4::ParserRuleContext*, std::variant<antlr4::Token*, antlr4::ParserRuleContext*>, std::initializer_list<std::string> const) override;
};

struct InvalidDeclaringTypeError : public Throwable {
    InvalidDeclaringTypeError() : Throwable() {}
    virtual ~InvalidDeclaringTypeError() override = default;

    virtual void print(std::string const&, antlr4::ParserRuleContext*, std::variant<antlr4::Token*, antlr4::ParserRuleContext*>, std::initializer_list<std::string> const) override;
};

struct InvalidComparisonTypeError : public Throwable {
    InvalidComparisonTypeError() : Throwable() {}
    virtual ~InvalidComparisonTypeError() override = default;

    virtual void print(std::string const&, antlr4::ParserRuleContext*, std::variant<antlr4::Token*, antlr4::ParserRuleContext*>, std::initializer_list<std::string> const) override;
};

struct UndeclaredVariableError : public Throwable {
    UndeclaredVariableError() : Throwable() {}
    virtual ~UndeclaredVariableError() override = default;

    virtual void print(std::string const&, antlr4::ParserRuleContext*, std::variant<antlr4::Token*, antlr4::ParserRuleContext*>, std::initializer_list<std::string> const) override;
};

struct UndefinedVariableError : public Throwable {
    UndefinedVariableError() : Throwable() {}
    virtual ~UndefinedVariableError() override = default;

    virtual void print(std::string const&, antlr4::ParserRuleContext*, std::variant<antlr4::Token*, antlr4::ParserRuleContext*>, std::initializer_list<std::string> const) override;
};

struct AlreadyExistingIDError : public Throwable {
    AlreadyExistingIDError() : Throwable() {}
    virtual ~AlreadyExistingIDError() override = default;

    virtual void print(std::string const&, antlr4::ParserRuleContext*, std::variant<antlr4::Token*, antlr4::ParserRuleContext*>, std::initializer_list<std::string> const) override;
};

struct UnknownIDError : public Throwable {
    UnknownIDError() : Throwable() {}
    virtual ~UnknownIDError() override = default;

    virtual void print(std::string const&, antlr4::ParserRuleContext*, std::variant<antlr4::Token*, antlr4::ParserRuleContext*>, std::initializer_list<std::string> const) override;
};

/**
 * Warnings
 */

struct ImplicitCastWarning : public Throwable {
    ImplicitCastWarning() : Throwable() {}
    virtual ~ImplicitCastWarning() override = default;

    virtual void print(std::string const&, antlr4::ParserRuleContext*, std::variant<antlr4::Token*, antlr4::ParserRuleContext*>, std::initializer_list<std::string> const) override;
};

struct FloatingPointWarning : public Throwable {
    FloatingPointWarning() : Throwable() {}
    virtual ~FloatingPointWarning() override = default;
    
    virtual void print(std::string const&, antlr4::ParserRuleContext*, std::variant<antlr4::Token*, antlr4::ParserRuleContext*>, std::initializer_list<std::string> const) override;
};

#endif