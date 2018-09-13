#ifndef SNOWSTARVISITOR_HPP
#define SNOWSTARVISITOR_HPP

#include <sstream>
#include <iostream>

#include <SnowStarBaseVisitor.h>
#include <SnowStarLexer.h>

#include <termcolor/termcolor.hpp>

struct EvalValue {
    enum ValueType {
        Real32,
        Real64,
        Int8,
        Int16,
        Int32,
        Int64,
        Boolean,
        Character,
        String,
        Null
    } type; // NULL and NOT NULL are possible literals, so we need an enum for them.
    double number;

    EvalValue(ValueType aType, double aNumber) : type(aType), number(aNumber) {}

    bool isNullType() {
        return type == Null;
    }

    static EvalValue fromBool(bool value) {
        return EvalValue(Boolean, value);
    }
    static EvalValue fromNumber(float number) {
        return EvalValue(Real32, number);
    }
    static EvalValue fromNumber(double number) {
        return EvalValue(Real64, number);
    }
    static EvalValue fromNumber(int8_t number) {
        return EvalValue(Int8, static_cast<double>(number));
    }
    static EvalValue fromNumber(int16_t number) {
        return EvalValue(Int16, static_cast<double>(number));
    }
    static EvalValue fromNumber(int32_t number) {
        return EvalValue(Int32, static_cast<double>(number));
    }
    static EvalValue fromNumber(int64_t number) {
        return EvalValue(Int64, static_cast<double>(number));
    }
    static EvalValue fromNull() {
        return EvalValue(Null, 0);
    }
};

struct Error {
    static Error fromMessage(std::string const& msg) {
        return Error(msg);
    }

    std::string print() const {
        std::stringstream ss;
        if (m_msg != "")
            ss << termcolor::colorize << termcolor::red << "Error: " << m_msg;
        ss << termcolor::reset << std::flush;
        return std::string{ss.str()};
    }

protected:
    std::string m_msg;

    Error(std::string const& msg) : m_msg{msg} {}
};

struct Warning {
    static Warning fromMessage(std::string const& msg) {
        return Warning(msg);
    }

    std::string print() const {
        std::stringstream ss;
        if (m_msg != "")
            ss << termcolor::colorize << termcolor::yellow << "Warning: " << m_msg;
        ss << termcolor::reset << std::flush;
        return std::string{ss.str()};
    }

protected:
    Warning(std::string const& msg) : m_msg{msg} {}

    std::string m_msg;
};

class Visitor : public SnowStarBaseVisitor {
    std::pair<std::vector<Error>, std::vector<Warning>> errors;
    std::vector<std::pair<std::string, antlr4::Token*>> declared;

public:
    virtual antlrcpp::Any visitProgram(SnowStarParser::ProgramContext*);
    virtual antlrcpp::Any visitStatement(SnowStarParser::StatementContext*);
    virtual antlrcpp::Any visitDeclare(SnowStarParser::DeclareContext*);
    virtual antlrcpp::Any visitDefine(SnowStarParser::DefineContext*);
    virtual antlrcpp::Any visitValue(SnowStarParser::ValueContext*);
};

#endif