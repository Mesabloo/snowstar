#include <visitor.hpp>

namespace utils {
    bool str_startswith(std::string const& src, std::string const& prefix) {
        return src.size() >= prefix.size() && src.substr(0, prefix.size()) == prefix;
    }
}

antlrcpp::Any Visitor::visitProgram(SnowStarParser::ProgramContext* context) {
    antlrcpp::Any result = visitChildren(context);
    //if (result.is<std::vector<Error>>()) errors = result.as<std::vector<Error>>();
    return errors;
}

antlrcpp::Any Visitor::visitStatement(SnowStarParser::StatementContext* context) {
    antlrcpp::Any result = visitChildren(context);
    if (result.is<std::vector<Error>>())
        for (auto e : result.as<std::vector<Error>>())
            errors.first.push_back(e);
    return antlrcpp::Any();
}

antlrcpp::Any Visitor::visitDeclare(SnowStarParser::DeclareContext* context) {
    auto ids = context->Identifier();
    auto type = context->Type();
    std::vector<std::pair<std::string, antlr4::Token*>> tmp;
    for (auto id : ids) {
        auto it = std::find_if(declared.begin(), declared.end(), [&] (std::pair<std::string, antlr4::Token*> const& p) { return p.first == id->getText(); });
        //std::clog << "Declaration of " << id->getText() << ": " << (it != declared.end()?"Already declared, should return an error":"not declared") << std::endl;
        if (it != declared.end()) return std::vector<Error>{Error::fromMessage("Redeclaration of field '" + id->getText() + "' at ["+std::to_string(id->getSymbol()->getLine())+";"+std::to_string(id->getSymbol()->getCharPositionInLine()+1)+"].")};
        std::pair<std::string, antlr4::Token*> pair = std::make_pair(id->getText(), type->getSymbol());
        declared.push_back(pair);
        tmp.push_back(pair);
    }
    return tmp;
}

antlrcpp::Any Visitor::visitDefine(SnowStarParser::DefineContext* context) {
    antlrcpp::Any result = visitDeclare(context->declare());
    //std::clog << "After declarations: " << (result.is<std::vector<Error>>()?"errors":"no errors") << std::endl;
    if (result.is<std::vector<Error>>()) return result.as<std::vector<Error>>();
    auto resources = result.as<std::vector<std::pair<std::string, antlr4::Token*>>>();
    auto values = context->value();
    if (resources.size() > values.size()) {
        errors.second.push_back(Warning::fromMessage("Number of identifiers doesn't match number of values. Default intializing to `nil`."));
        while (values.size() < resources.size())
            values.push_back(nullptr);
    }
    if (values.size() > resources.size())
        errors.second.push_back(Warning::fromMessage("Too many values for a smaller number of identifiers. Ignoring some values."));
    for (unsigned int i{0}, j{0};i < values.size() && j < resources.size();++i, ++j) {
        auto value = values[i];
        auto res = resources[j];

        if (value == nullptr) {
            continue;
        }

        if (value->Identifier() != nullptr) {
            auto it = std::find_if(declared.begin(), declared.end(), [&] (std::pair<std::string, antlr4::Token*> const& p) { return p.first == value->getText(); });
            if (it == declared.end()) return std::vector<Error>{Error::fromMessage("Undeclared variable " + value->getText() + " at ["+std::to_string(value->Identifier()->getSymbol()->getLine())+";"+std::to_string(value->Identifier()->getSymbol()->getCharPositionInLine()+1)+"].")};
            if (!(utils::str_startswith(res.second->getText(), "int") && utils::str_startswith(it->second->getText(), "int"))
                ^ !(utils::str_startswith(res.second->getText(), "real") && (utils::str_startswith(it->second->getText(), "int") ^ utils::str_startswith(it->second->getText(), "real")))
                ^ (res.second->getText() != it->second->getText())
                && res.second->getText() != "void" && res.second->getText() != "str")
                return std::vector<Error>{Error::fromMessage("Inconsistent types -> " + res.second->getText() + " cannot hold a value of type " + it->second->getText())};
            else if (utils::str_startswith(res.second->getText(), "real") && utils::str_startswith(it->second->getText(), "int"))
                errors.second.push_back(Warning::fromMessage("Implicit cast from "+(it->second->getText())+" to "+(res.second->getText())+" at ["+(std::to_string(visitValue(value).as<antlr4::tree::TerminalNode*>()->getSymbol()->getLine()))+";"+(std::to_string(visitValue(value).as<antlr4::tree::TerminalNode*>()->getSymbol()->getCharPositionInLine()+1))+"]."));
            else if (res.second->getText() == "str")
                errors.second.push_back(Warning::fromMessage("Implicit cast from "+(it->second->getText())+" to str at ["+(std::to_string(visitValue(value).as<antlr4::tree::TerminalNode*>()->getSymbol()->getLine()))+";"+(std::to_string(visitValue(value).as<antlr4::tree::TerminalNode*>()->getSymbol()->getCharPositionInLine()+1))+"]."));
        }
        if (value->Integer() != nullptr) {
            if (!utils::str_startswith(res.second->getText(), "int") && !utils::str_startswith(res.second->getText(), "real") && res.second->getText() != "void" && res.second->getText() != "str") return std::vector<Error>{Error::fromMessage("Inconsistent types -> " + res.second->getText() + " cannot hold a value of type " + value->getText() + " at ["+(std::to_string(value->Integer()->getSymbol()->getLine()))+";"+(std::to_string(value->Integer()->getSymbol()->getCharPositionInLine()+1))+"].")};
            else if (utils::str_startswith(res.second->getText(), "real"))
                errors.second.push_back(Warning::fromMessage("Implicit cast from integer to "+(res.second->getText())+" at ["+(std::to_string(value->Integer()->getSymbol()->getLine()))+";"+(std::to_string(value->Integer()->getSymbol()->getCharPositionInLine()+1))+"]."));
            else if (res.second->getText() == "str")
                errors.second.push_back(Warning::fromMessage("Implicit cast from integer to str at ["+(std::to_string(value->Integer()->getSymbol()->getLine()))+";"+(std::to_string(value->Integer()->getSymbol()->getCharPositionInLine()+1))+"]."));
        }
        if (value->Real() != nullptr) {
            if (!utils::str_startswith(res.second->getText(), "real") && res.second->getText() != "void" && res.second->getText() != "str") return std::vector<Error>{Error::fromMessage("Inconsistent types -> " + res.second->getText() + " cannot hold a value of type " + value->getText() + " at ["+(std::to_string(value->Real()->getSymbol()->getLine()))+";"+(std::to_string(value->Real()->getSymbol()->getCharPositionInLine()+1))+"].")};
            else if (res.second->getText() == "str")
                errors.second.push_back(Warning::fromMessage("Implicit cast from real to str at ["+(std::to_string(value->Real()->getSymbol()->getLine()))+";"+(std::to_string(value->Real()->getSymbol()->getCharPositionInLine()+1))+"]."));
        }
        if (value->Boolean() != nullptr) {
            if (res.second->getText() != "bool" && res.second->getText() != "void" && res.second->getText() != "str") return std::vector<Error>{Error::fromMessage("Inconsistent types -> " + res.second->getText() + " cannot hold a value of type " + value->getText() + " at ["+(std::to_string(value->Boolean()->getSymbol()->getLine()))+";"+(std::to_string(value->Boolean()->getSymbol()->getCharPositionInLine()+1))+"].")};
            else if (res.second->getText() == "str")
                errors.second.push_back(Warning::fromMessage("Implicit cast from bool to str at ["+(std::to_string(value->Boolean()->getSymbol()->getLine()))+";"+(std::to_string(value->Boolean()->getSymbol()->getCharPositionInLine()+1))+"]."));
        }
        if (value->Character() != nullptr) {
            if (res.second->getText() != "char" && res.second->getText() != "void" && res.second->getText() != "str") return std::vector<Error>{Error::fromMessage("Inconsistent types -> " + res.second->getText() + " cannot hold a value of type " + value->getText() + " at ["+(std::to_string(value->Character()->getSymbol()->getLine()))+";"+(std::to_string(value->Character()->getSymbol()->getCharPositionInLine()+1))+"].")};
            else if (res.second->getText() == "str")
                errors.second.push_back(Warning::fromMessage("Implicit cast from char to str at ["+(std::to_string(value->Character()->getSymbol()->getLine()))+";"+(std::to_string(value->Character()->getSymbol()->getCharPositionInLine()+1))+"]."));
        }
        if (value->String() != nullptr) {
            if (res.second->getText() != "str" && res.second->getText() != "void") return std::vector<Error>{Error::fromMessage("Inconsistent types -> " + res.second->getText() + " cannot hold a value of type " + value->getText() + " at ["+(std::to_string(value->String()->getSymbol()->getLine()))+";"+(std::to_string(value->String()->getSymbol()->getCharPositionInLine()+1))+"].")};
        }
        if (value->Null() != nullptr) {
            continue;
        }
        if (value->cast() != nullptr) {
            visitCast(value->cast());
        }
    }
    return antlrcpp::Any();
}

antlrcpp::Any Visitor::visitValue(SnowStarParser::ValueContext* context) {
    if (context->Identifier() != nullptr) return context->Identifier();
    if (context->Integer() != nullptr) return context->Integer();
    if (context->Real() != nullptr) return context->Real();
    if (context->Boolean() != nullptr) return context->Boolean();
    if (context->Character() != nullptr) return context->Character();
    if (context->String() != nullptr) return context->String();
    if (context->Null() != nullptr) return context->Null();
    if (context->cast() != nullptr) return visitCast(context->cast());
    return nullptr;
}

antlrcpp::Any Visitor::visitCast(SnowStarParser::CastContext* context) {
    auto type = context->Type();
    auto value = context->value();

    if (value->Identifier() != nullptr) {
        auto it = std::find_if(declared.begin(), declared.end(), [&] (std::pair<std::string, antlr4::Token*> const& p) { return p.first == value->getText(); });
        if (it == declared.end()) {
            errors.first.push_back(Error::fromMessage("Undeclared variable " + value->getText() + " at ["+std::to_string(value->Identifier()->getSymbol()->getLine())+";"+std::to_string(value->Identifier()->getSymbol()->getCharPositionInLine()+1)+"]."));
            return antlrcpp::Any();
        }
    }
    if (value->Integer() != nullptr) {
        if (type->getText() == "void") {
            errors.first.push_back(Error::fromMessage("Invalid cast from integer to void at ["+std::to_string(value->Integer()->getSymbol()->getLine())+";"+std::to_string(value->Integer()->getSymbol()->getCharPositionInLine()+1)+"]."));
            return antlrcpp::Any();
        }
    }
    if (value->Real() != nullptr) {
        if (type->getText() == "void") {
            errors.first.push_back(Error::fromMessage("Invalid cast from real to void at ["+std::to_string(value->Integer()->getSymbol()->getLine())+";"+std::to_string(value->Integer()->getSymbol()->getCharPositionInLine()+1)+"]."));
            return antlrcpp::Any();
        }
    }
    if (value->Boolean() != nullptr) {
        if (type->getText() == "void" || type->getText() == "char") {
            errors.first.push_back(Error::fromMessage("Invalid cast from bool to "+type->getText()+" at ["+std::to_string(value->Integer()->getSymbol()->getLine())+";"+std::to_string(value->Integer()->getSymbol()->getCharPositionInLine()+1)+"]."));
            return antlrcpp::Any();
        }
    }
    if (value->Character() != nullptr) {
        if (type->getText() == "void" || type->getText() == "bool") {
            errors.first.push_back(Error::fromMessage("Invalid cast from char to "+type->getText()+" at ["+std::to_string(value->Integer()->getSymbol()->getLine())+";"+std::to_string(value->Integer()->getSymbol()->getCharPositionInLine()+1)+"]."));
            return antlrcpp::Any();
        }
    }
    if (value->String() != nullptr) {
        if (type->getText() == "void") {
            errors.first.push_back(Error::fromMessage("Invalid cast from str to void at ["+std::to_string(value->Integer()->getSymbol()->getLine())+";"+std::to_string(value->Integer()->getSymbol()->getCharPositionInLine()+1)+"]."));
            return antlrcpp::Any();
        }
    }
    if (value->Null() != nullptr) {
        errors.first.push_back(Error::fromMessage("Invalid cast from a null value (nil) at ["+std::to_string(value->Integer()->getSymbol()->getLine())+";"+std::to_string(value->Integer()->getSymbol()->getCharPositionInLine()+1)+"]."));
        return antlrcpp::Any();
    }
    if (value->cast() != nullptr) {
        auto val = visitCast(value->cast());
        if (val.is<antlrcpp::Any>()) return val;
    }
}