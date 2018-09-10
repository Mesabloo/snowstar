#include <visitor.hpp>

namespace utils {
    bool str_startswith(std::string const& src, std::string const& prefix) {
        return src.size() >= prefix.size() && src.substr(0, prefix.size()) == prefix;
    }
}

antlrcpp::Any Visitor::visitProgram(SnowStarParser::ProgramContext* context) {
    antlrcpp::Any result = visitChildren(context);
    if (result.is<std::vector<Error>>()) errors = result.as<std::vector<Error>>();
    return errors;
}

antlrcpp::Any Visitor::visitStatement(SnowStarParser::StatementContext* context) {
    antlrcpp::Any result = visitChildren(context);
    if (result.is<std::vector<Error>>())
        return result;
    return antlrcpp::Any();
}

antlrcpp::Any Visitor::visitDeclare(SnowStarParser::DeclareContext* context) {
    auto ids = context->Identifier();
    auto type = context->Type();
    std::vector<std::pair<std::string, antlr4::Token*>> tmp;
    for (auto id : ids) {
        auto it = std::find_if(declared.begin(), declared.end(), [&] (std::pair<std::string, antlr4::Token*> const& p) { return p.first == id->getText(); });
        if (it != declared.end()) return std::vector<Error>{Error::fromMessage("Redeclaration of field " + id->getText())};
        std::pair<std::string, antlr4::Token*> pair = std::make_pair(id->getText(), type->getSymbol());
        declared.push_back(pair);
        tmp.push_back(pair);
    }
    return tmp;
}

antlrcpp::Any Visitor::visitDefine(SnowStarParser::DefineContext* context) {
    antlrcpp::Any result = visitDeclare(context->declare());
    if (result.is<std::vector<Error>>()) return result;
    auto resources = result.as<std::vector<std::pair<std::string, antlr4::Token*>>>();
    auto values = context->value();
    if (resources.size() > values.size()) {
        std::cerr << Warning::fromMessage("Number of identifiers doesn't match number of values. Default intializing to `nil`.").print() << std::endl;
        // while (values.size() < resources.size())
        //    values.push_back(nullptr);
    }
    if (values.size() > resources.size())
        std::cerr << Warning::fromMessage("Too many values for a smaller number of identifiers. Ignoring some values.").print() << std::endl;
    for (unsigned int i{0}, j{0};i < values.size() && j < resources.size();++i, ++j) {
        auto value = values[i];
        auto res = resources[j];

        if (value == nullptr) {

        }

        if (value->Identifier() != nullptr) {
            auto it = std::find_if(declared.begin(), declared.end(), [&] (std::pair<std::string, antlr4::Token*> const& p) { return p.first == value->getText(); });
            if (it == declared.end()) return std::vector<Error>{Error::fromMessage("Undeclared variable " + value->getText())}; // make error here
            if (!(utils::str_startswith(res.second->getText(), "integer") && utils::str_startswith(it->second->getText(), "integer"))
                ^ !(utils::str_startswith(res.second->getText(), "real") && (utils::str_startswith(it->second->getText(), "integer") ^ utils::str_startswith(it->second->getText(), "real")))
                ^ (res.second->getText() != it->second->getText()))
                return std::vector<Error>{Error::fromMessage("Inconsistent types -> " + res.second->getText() + " cannot hold a value of type " + it->second->getText())};
            else if (utils::str_startswith(res.second->getText(), "real") && utils::str_startswith(it->second->getText(), "integer"))
                std::cerr << Warning::fromMessage("Implicit cast from integer to real at ["+(std::to_string(it->second->getLine()))+";"+(std::to_string(it->second->getCharPositionInLine()))+"].").print() << std::endl;
        }
        if (value->Integer() != nullptr) {
            if (!utils::str_startswith(res.second->getText(), "integer") && !utils::str_startswith(res.second->getText(), "real")) return std::vector<Error>{Error::fromMessage("Inconsistent types -> " + res.second->getText() + " cannot hold a value of type " + value->getText() + " at ["+(std::to_string(value->Integer()->getSymbol()->getLine()))+";"+(std::to_string(value->Integer()->getSymbol()->getCharPositionInLine()))+"].")};
        }
        if (value->Real() != nullptr) {
            if (!utils::str_startswith(res.second->getText(), "real")) return std::vector<Error>{Error::fromMessage("Inconsistent types -> " + res.second->getText() + " cannot hold a value of type " + value->getText() + " at ["+(std::to_string(value->Real()->getSymbol()->getLine()))+";"+(std::to_string(value->Real()->getSymbol()->getCharPositionInLine()))+"].")}; 
        }
        if (value->Boolean() != nullptr) {
            if (!utils::str_startswith(res.second->getText(), "boolean")) return std::vector<Error>{Error::fromMessage("Inconsistent types -> " + res.second->getText() + " cannot hold a value of type " + value->getText() + " at ["+(std::to_string(value->Boolean()->getSymbol()->getLine()))+";"+(std::to_string(value->Boolean()->getSymbol()->getCharPositionInLine()))+"].")}; 
        }
        if (value->Character() != nullptr) {
            if (!utils::str_startswith(res.second->getText(), "character")) return std::vector<Error>{Error::fromMessage("Inconsistent types -> " + res.second->getText() + " cannot hold a value of type " + value->getText() + " at ["+(std::to_string(value->Character()->getSymbol()->getLine()))+";"+(std::to_string(value->Character()->getSymbol()->getCharPositionInLine()))+"].")}; 
        }
        if (value->String() != nullptr) {
            if (!utils::str_startswith(res.second->getText(), "string")) return std::vector<Error>{Error::fromMessage("Inconsistent types -> " + res.second->getText() + " cannot hold a value of type " + value->getText() + " at ["+(std::to_string(value->String()->getSymbol()->getLine()))+";"+(std::to_string(value->String()->getSymbol()->getCharPositionInLine()))+"].")}; 
        }
    }
    return antlrcpp::Any();
}