#ifndef SNOWSTARVISITOR_HPP
#define SNOWSTARVISITOR_HPP

#include <sstream>

#include "SnowStarBaseVisitor.h"
#include "SnowStarLexer.h"

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
        return Error(msg, 0);
    }

    static Error fromCode(int8_t const code) {
        return Error("", code);
    }

    std::string print() const {
        std::stringstream ss;
        ss << "An unexpected error occured.\n";
        if (m_code != 0)
            ss << "Code: " << m_code << '\n';
        if (m_msg != "")
            ss << "Message: " << m_msg;
        ss << std::flush;
        return std::string{ss.str()};
    }

protected:
    std::string m_msg;
    int8_t m_code;

    Error(std::string const& msg, int8_t const code) : m_msg{msg}, m_code{code} {}
};

namespace utils {
    bool str_startswith(std::string const& src, std::string const& prefix) {
        return src.size() >= prefix.size() && src.substr(0, prefix.size()) == prefix;
    }
}

class Visitor : public SnowStarBaseVisitor {
    std::vector<Error> errors;
    std::vector<std::pair<std::string, antlr4::Token*>> declared;

    virtual antlrcpp::Any visitProgram(SnowStarParser::ProgramContext* context) {
        antlrcpp::Any result = visitChildren(context);
        if (result.is<std::vector<Error>>()) errors = result.as<std::vector<Error>>();
        return errors;
    }

    virtual antlrcpp::Any visitStatement(SnowStarParser::StatementContext* context) {
        antlrcpp::Any result = visitChildren(context);
        if (result.is<std::vector<Error>>())
            return result;
        return antlrcpp::Any();
    }

    virtual antlrcpp::Any visitDeclare(SnowStarParser::DeclareContext* context) {
        auto id = context->Identifier(),
             type = context->Type();
        auto it = std::find_if(declared.begin(), declared.end(), [&] (std::pair<std::string, antlr4::Token*> const& p) { return p.first == id->getText(); });
        if (it != declared.end()) return std::vector<Error>{Error::fromMessage("Redeclaration of field " + id->getText())};
        std::pair<std::string, antlr4::Token*> pair = std::make_pair(id->getText(), type->getSymbol());
        declared.push_back(pair);
        return pair;
    }

    virtual antlrcpp::Any visitDefine(SnowStarParser::DefineContext* context) {
        antlrcpp::Any result = visitDeclare(context->declare());
        if (result.is<std::vector<Error>>()) return result;
        auto res = result.as<std::pair<std::string, antlr4::Token*>>();
        auto value = context->value();
        if (value->Identifier() != nullptr) {
            auto it = std::find_if(declared.begin(), declared.end(), [&] (std::pair<std::string, antlr4::Token*> const& p) { return p.first == value->getText(); });
            if (it == declared.end()) return std::vector<Error>{Error::fromMessage("Undeclared variable " + value->getText())}; // make error here
            if (!(utils::str_startswith(res.second->getText(), "integer") && utils::str_startswith(it->second->getText(), "integer"))
                ^ !(utils::str_startswith(res.second->getText(), "real") && (utils::str_startswith(it->second->getText(), "integer") ^ utils::str_startswith(it->second->getText(), "real")))
                ^ (res.second->getText() != it->second->getText()))
                return std::vector<Error>{Error::fromMessage("Inconsistent types -> " + res.second->getText() + " cannot hold a value of type " + it->second->getText())};
        }
        if (value->Integer() != nullptr) {
            if (!utils::str_startswith(res.second->getText(), "integer") && !utils::str_startswith(res.second->getText(), "real")) return std::vector<Error>{Error::fromMessage("Inconsistent types -> " + res.second->getText() + " cannot hold a value of type " + value->getText())};
        }
        if (value->Real() != nullptr) {
            if (!utils::str_startswith(res.second->getText(), "real")) return std::vector<Error>{Error::fromMessage("Inconsistent types -> " + res.second->getText() + " cannot hold a value of type " + value->getText())}; 
        }
        if (value->Boolean() != nullptr) {
            if (!utils::str_startswith(res.second->getText(), "boolean")) return std::vector<Error>{Error::fromMessage("Inconsistent types -> " + res.second->getText() + " cannot hold a value of type " + value->getText())}; 
        }
        if (value->Character() != nullptr) {
            if (!utils::str_startswith(res.second->getText(), "character")) return std::vector<Error>{Error::fromMessage("Inconsistent types -> " + res.second->getText() + " cannot hold a value of type " + value->getText())}; 
        }
        if (value->String() != nullptr) {
            if (!utils::str_startswith(res.second->getText(), "string")) return std::vector<Error>{Error::fromMessage("Inconsistent types -> " + res.second->getText() + " cannot hold a value of type " + value->getText())}; 
        }
        return antlrcpp::Any();
    }
};

#endif