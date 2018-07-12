

#include "token.hpp"

std::string Token::getTypeSignification(Token::Type type) {
    switch (type) {
        case Token::Type::KEYWORD: return "Keyword";
        case Token::Type::LITERAL_STRING: return "Literal.String";
        case Token::Type::LITERAL_NUMBER: return "Literal.Number";
        case Token::Type::LITERAL_MEMORY: return "Literal.Memory";
        case Token::Type::SEPARATOR: return "Separator";
        case Token::Type::EOL: return "EOL";
        case Token::Type::INLINE_COMMENT: return "Comment.Inline";
        case Token::Type::MULTILINE_COMMENT: return "Comment.Multiline";
        case Token::Type::INVALID: [[fallthrough]];
        default: return "Invalid";
    }
}

Token::Token(): m_type{Token::Type::INVALID}, m_value{""} {}
Token::Token(Token::Type type, std::string value): m_type{type}, m_value{value} {}
Token::~Token() {}

Token::Type Token::getType() const { return m_type; }
std::string Token::getValue() const { return m_value; }


Consumer::Store::Store() {}
Consumer::Store::Store(Token const&, Token const&) {}
Consumer::Store::~Store() {}

Consumer::Consumer(Token const& instr, Consumer::Store const& store, std::vector<Token> const& args): m_instruction{instr}, m_storage{store}, m_args{args} {}

Token Consumer::getInstruction() const { return m_instruction; }
Consumer::Store Consumer::getStorage() const { return m_storage; }
std::vector<Token> Consumer::getArgs() const { return m_args; }


bool operator==(Token const& a, Token const& b) {
    return a.getType() == b.getType() && a.getValue() == b.getValue();
}