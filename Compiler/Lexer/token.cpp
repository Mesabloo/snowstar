

#include "token.hpp"

std::string Token::getTypeSignification(Token::Type type) {
    switch (type) {
        case Token::Type::KEYWORD: return "Keyword";
        case Token::Type::LITERAL_STRING: return "Literal.String";
        case Token::Type::LITERAL_NUMBER_FLOAT: return "Literal.Number.Float";
        case Token::Type::LITERAL_NUMBER_INT: return "Literal.Number.Integer";
        case Token::Type::LITERAL_MEMORY: return "Literal.Memory";
        case Token::Type::SEPARATOR: return "Separator";
        case Token::Type::EOL: return "EOL";
        case Token::Type::INLINE_COMMENT: return "Comment.Inline";
        case Token::Type::MULTILINE_COMMENT: return "Comment.Multiline";
        case Token::Type::LABEL: return "Label";

        case Token::Type::LABEL_TABLE: return "Table.Labels";
        case Token::Type::CONST_TABLE: return "Table.Constants";
        case Token::Type::MEM_TABLE: return "Table.Memory";

        case Token::Type::INVALID: [[fallthrough]];
        default: return "Invalid";
    }
}

Token::Token(): m_type{Token::Type::INVALID}, m_value{""} {}
Token::Token(Token::Type type, std::string value): m_type{type}, m_value{value} {}
Token::~Token() {}

Token::Type Token::getType() const { return m_type; }
std::string Token::getValue() const { return m_value; }


Consumer::Store::Store(): m_memseg{Token(Token::Type::KEYWORD, "nost")}, m_index{Token(Token::Type::LITERAL_NUMBER_INT, "-1")} {}
Consumer::Store::Store(Token const& memseg, Token const& index): m_memseg{memseg}, m_index{index} {}
Consumer::Store::~Store() {}

Token Consumer::Store::getMemseg() const { return m_memseg; }
Token Consumer::Store::getIndex() const { return m_index; }

Consumer::Consumer(Token const& instr, Consumer::Store const& store, std::vector<Token> const& args): m_instruction{instr}, m_storage{store}, m_args{args} {}

Token Consumer::getInstruction() const { return m_instruction; }
Consumer::Store Consumer::getStorage() const { return m_storage; }
std::vector<Token> Consumer::getArgs() const { return m_args; }

std::string Consumer::toString() const {
    std::string args;
    for (auto const& t : getArgs())
        args += t.getValue() + ", ";
    args = args.substr(0, args.size()-2);
    return getInstruction().getValue() + "[" + getStorage().getMemseg().getValue() + "." + getStorage().getIndex().getValue() + "] " + args;
}


bool operator==(Token const& a, Token const& b) {
    return a.getType() == b.getType() && a.getValue() == b.getValue();
}

bool operator==(Consumer const& a, Consumer const& b) {
    bool are_args_valid = true;
    if (a.getArgs().size() == b.getArgs().size()) {
        for (size_t i{0};i < a.getArgs().size();++i) {
            if (a.getArgs()[i].getType() != b.getArgs()[i].getType()) {
                are_args_valid = false;
                break;
            }
        }
    } else
        are_args_valid = false;
    return a.getInstruction().getType() == b.getInstruction().getType()
        && a.getStorage().getMemseg().getType() == b.getStorage().getMemseg().getType()
        && a.getStorage().getIndex().getType() == b.getStorage().getIndex().getType()
        && are_args_valid;
}