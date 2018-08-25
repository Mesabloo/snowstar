#ifndef AST_HPP
#define AST_HPP

#include <vector>
#include <utility>
#include <Lexer/token.hpp>
#include "except.hpp"
#include <iostream>
#include <string>
#include <memory>

class AST {
    public:
        struct Expression {
            Expression();
            Expression(Token const&);
            Expression(Consumer::Store const&);
            ~Expression() = default;

            Token m_expr;
            Consumer::Store m_storage;

            friend bool operator==(Expression, Expression);
        };

        struct Node {
            struct Info {
                AST::Expression instruction;
                AST::Expression target;
                std::vector<AST::Expression> arguments;

                Info(AST::Expression const&, AST::Expression const&, std::vector<AST::Expression> const&);
            } m_info;

            std::vector<Node> m_children;

            bool hasChildren() const;

            Node();
            Node(Info const&, std::vector<Node> const&);

            std::string toString(unsigned int, bool const = false);
            friend std::ostream& operator<<(std::ostream&, AST::Node&);
            friend bool operator==(Node, Node);
        };

        AST(AST::Node const&);

        static std::pair<std::unique_ptr<AST>, std::vector<Exception>> build(std::vector<std::vector<Token>> const&);
        std::vector<Exception> checkForErrors() const;
        std::vector<Consumer>& getConsumers();
        void setNode(AST::Node const& n);

        ~AST() = default;

        friend std::ostream& operator<<(std::ostream&, AST&);

    protected:
        AST::Node m_main_node;
        std::vector<Consumer> m_cons;
};

#endif