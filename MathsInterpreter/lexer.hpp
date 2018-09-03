#pragma once
#ifndef LEXER_HPP
#define LEXER_HPP

#include <string>
#include <vector>
#include <array>
#include <memory>
#include <stack>
#include <cstdint>

struct Token {
    enum class Type {
        None,
        Operator,
        Number
    };

    virtual std::string toString() = 0;
    virtual ~Token() {}

    Type type = Type::None;
};

struct Operator final : Token {
    std::uint8_t priority;

    enum class Symbol {
        ADD, MUL, DIV, SUB, LPAR, RPAR, MOD, LOG_NOT, UNI_SUB, UNI_ADD
    };

    enum class Associative {
        LEFT, RIGHT, NONE
    };

    Operator(char const oper, Symbol const s) : op{oper}, symb{s} {
        type = Type::Operator;
        switch (symb) {
            case Symbol::LPAR: [[fallthrough]];
            case Symbol::RPAR: {
                priority = 6;
                assoc = Associative::NONE;
                unary = false;
                break;
            }
            case Symbol::MOD: [[fallthrough]];
            case Symbol::DIV: [[fallthrough]];
            case Symbol::MUL: {
                priority = 3;
                assoc = Associative::LEFT;
                unary = false;
                break;
            }
            case Symbol::ADD: [[fallthrough]];
            case Symbol::SUB: {
                priority = 2;
                assoc = Associative::LEFT;
                unary = false;
                break;
            }
            case Symbol::UNI_SUB: [[fallthrough]];
            case Symbol::UNI_ADD: [[fallthrough]];
            case Symbol::LOG_NOT: {
                priority = 5;
                assoc = Associative::RIGHT;
                unary = true;
                break;
            }
            default: {
                priority = 0;
                assoc = Associative::NONE;
                unary = false;
            }
        }
    }

    virtual std::string toString() {
        //std::string to_return{op};
        //to_return += " → ";
        //to_return += (symb == Symbol::ADD?"ADD":symb == Symbol::SUB?"SUB":symb == Symbol::MUL?"MUL":symb == Symbol::DIV?"DIV":symb == Symbol::LPAR?"LPAR":symb == Symbol::RPAR?"RPAR":"None");
        return std::string{op};
    }

    Associative getAssoc() const { return assoc; }
    Symbol getSymbol() const { return symb;}
    bool isNumberOperator() const { return symb == Symbol::ADD || symb == Symbol::DIV || symb == Symbol::SUB || symb == Symbol::MUL; }
    bool isUnary() const { return unary; }

    virtual ~Operator() {}

protected:
    char op;
    Symbol symb;
    Associative assoc;
    bool unary;
};

struct Number final : Token {
    Number(std::string const& value) : val{value} { type = Type::Number; }

    virtual std::string toString() { return val; }

    virtual ~Number() {}

protected:
    std::string val;
};

class Node {
    Node* lhs;
    Node* rhs;
    Token* value;

public:
    Node(Token* val, Node* left, Node* right) : lhs{left}, rhs{right}, value{val} {}

    Token* getValue() const { return value; }
    Node* getLNode() const { return lhs; }
    Node* getRNode() const { return rhs; }

    friend std::ostream& operator<<(std::ostream& os, Node const& n) {
        if (n.getValue() == nullptr) return os;
        os << n.getValue()->toString();
        if (n.getLNode() != nullptr && n.getRNode() != nullptr)
            os << " { ";
        if (n.getLNode() != nullptr)
            os << *n.getLNode();
        if (n.getRNode() != nullptr)
            os << " | " << *n.getRNode();
        if (n.getLNode() != nullptr && n.getRNode() != nullptr)
            os << " }";
        return os;
    }
};

class MathsLexer {
public:
    MathsLexer() {}

    std::vector<Token*> tokenize(std::string const& input) {
        m_list = {};
        for (char const c : input) {
            auto ptr = getToken(c);
            if (ptr != nullptr) m_list.push_back(ptr);
        }
        if (buffer != "") {
            auto t = detectToken(buffer);
            if (t != nullptr) m_list.push_back(t);
        }

        return m_list;
    }

    std::stack<Node*> parse(std::vector<Token*>& to_parse) {
        std::stack<Node*> node{};
        std::stack<Token*> parsed{};
        std::stack<Operator*> op_stack{};
        for (auto& t : to_parse) {
            switch (t->type) {
                case Token::Type::Operator: {
                    Operator* o = static_cast<Operator*>(t);
                    if (o->isNumberOperator()) {
                        if (!op_stack.empty()) {
                            Operator* top = op_stack.top();
                            while (((top->priority > o->priority) || (top->priority == o->priority && (top->getAssoc() == Operator::Associative::LEFT))) && (top->getSymbol() != Operator::Symbol::LPAR)) {
                                addNode(node, top);
                                op_stack.pop();
                                if (op_stack.empty()) break;
                                top = op_stack.top();
                            }
                        }
                    }
                    if (o->getSymbol() != Operator::Symbol::RPAR)
                        op_stack.push(o);
                    else {
                        if (op_stack.empty()) return {};
                        Operator* top = op_stack.top();
                        while (top->getSymbol() != Operator::Symbol::LPAR) {
                            //parsed.push(top);
                            addNode(node, top);
                            op_stack.pop();
                            if (op_stack.empty()) return {};
                            top = op_stack.top();
                        }
                        op_stack.pop();
                    }
                    break;
                }
                case Token::Type::Number: {
                    node.push(new Node(t, nullptr, nullptr));
                    break;
                }
                default:
                    break;
            }

        }
        while (!op_stack.empty()) {
            addNode(node, op_stack.top());
            op_stack.pop();
        }
        return node;
    }

private:
    std::string buffer{""};
    std::vector<Token*> m_list{};

    void addNode(std::stack<Node*>& stack, Operator*& op) const {
        Node* rNode = nullptr;
        if (!op->isUnary() && (stack.size() > 1)) {
            rNode = stack.top();
            stack.pop();
        }
        Node* lNode = stack.top();
        stack.pop();
        stack.push(new Node(op, lNode, rNode));
    }

protected:
    Token* detectToken(char const buf) {
        if (buf == '~') return new Operator('~', Operator::Symbol::LOG_NOT);
        if (m_list.size() == 0 || m_list[m_list.size()-1]->type != Token::Type::Operator) {
            if (buf == '-') return new Operator('-', Operator::Symbol::SUB);
            if (buf == '+') return new Operator('+', Operator::Symbol::ADD);
        } else if (static_cast<Operator*>(m_list[m_list.size()-1])->getSymbol() != Operator::Symbol::RPAR) {
            if (buf == '-') return new Operator('-', Operator::Symbol::UNI_SUB);
            if (buf == '+') return new Operator('+', Operator::Symbol::UNI_ADD);
        } else {
            if (buf == '-') return new Operator('-', Operator::Symbol::SUB);
            if (buf == '+') return new Operator('+', Operator::Symbol::ADD);
        }
        if (buf == '/') return new Operator('/', Operator::Symbol::DIV);
        if (buf == '*') return new Operator('*', Operator::Symbol::MUL);
        if (buf == '(') return new Operator('(', Operator::Symbol::LPAR);
        if (buf == ')') return new Operator(')', Operator::Symbol::RPAR);
        if (buf == '%') return new Operator('%', Operator::Symbol::MOD);
        return nullptr;
    }

    Token* detectToken(std::string const& buf) {
        auto lambda = [] (char const c) -> bool { return std::isdigit(c) | (c == '.'); };
        for (auto const& c : buf) if (!lambda(c)) return nullptr;
        return new Number(buf);
    }

    Token* getToken(char const c) {
        switch (c) {
            case ' ': [[fallthrough]];
            case '\t': [[fallthrough]];
            case '\n': {
                if (buffer != "") {
                    auto t = detectToken(buffer);
                    buffer = "";
                    return t;
                }
                return nullptr;
            }
            case '~': [[fallthrough]];
            case '%': [[fallthrough]];
            case '(': [[fallthrough]];
            case ')': [[fallthrough]];
            case '+': [[fallthrough]];
            case '-': [[fallthrough]];
            case '*': [[fallthrough]];
            case '/': {
                if (buffer != "") {
                    auto t = detectToken(buffer);
                    buffer = "";
                    if (t != nullptr) m_list.push_back(t);
                }
                auto t1 = detectToken(c);
                return t1;
            }
            default:
                buffer += c;
                return nullptr;
        }
    }
};

#endif