#include <iomanip>

#include "byte_token.hpp"

std::ostream& operator<<(std::ostream& os, ByteToken::Type const& t) {
    switch (t) {
        case ByteToken::Type::KEYWORD: os << "Keyword"; break;
        case ByteToken::Type::SEPARATOR: os << "Separator"; break;
        case ByteToken::Type::LITERAL_STRING: os << "Literal.String"; break;
        case ByteToken::Type::LITERAL_NUMBER: os << "Literal.Number"; break;
        case ByteToken::Type::LITERAL_MEMORY: os << "Literal.Memory"; break;
        default: os << "Invalid";
    }
    return os;
}

ByteToken::ByteToken(ByteToken::Type const type, int8_t const value) : m_type(type), m_value(value), isStr(false), isIntNumb(false), isDoubleNumb(false), isMem(false) {}
ByteToken::ByteToken(ByteToken::Type const type, std::string const str_value) : m_type(type), m_string_value(str_value), isStr(true), isIntNumb(false), isDoubleNumb(false), isMem(false) {}
ByteToken::ByteToken(ByteToken::Type const type, int64_t int_value) : m_type(type), m_integer_value(int_value), isStr(false), isIntNumb(true), isDoubleNumb(false), isMem(false) {}
ByteToken::ByteToken(ByteToken::Type const type, int8_t const memseg, int64_t const index) : m_type(type), m_value(memseg), m_integer_value(index), isStr(false), isIntNumb(false), isDoubleNumb(false), isMem(true) {}
ByteToken::ByteToken(ByteToken::Type const type, double value) : m_type(type), m_double_value(value), isStr(false), isIntNumb(false), isDoubleNumb(true), isMem(false) {}
ByteToken::~ByteToken() {}

bool ByteToken::isString() const { return isStr; }
bool ByteToken::isIntegerNumber() const { return isIntNumb; }
bool ByteToken::isDoubleNumber() const { return isDoubleNumb; }
bool ByteToken::isMemory() const { return isMem; }

ByteToken::Type ByteToken::getType() const { return m_type; }
double ByteToken::getValueIfExisting() const {
    if (isString() || isIntegerNumber() || isDoubleNumber()) return -1;
    return m_value;
}
std::string ByteToken::getStringValueIfExisting() const {
    if (!isString()) return "";
    return m_string_value;
}
int64_t ByteToken::getIntegerValueIfExisting() const {
    if (!isIntegerNumber() && !isMemory()) return -1;
    return m_integer_value;
}
double ByteToken::getDoubleValueIfExisting() const {
    if (!isDoubleNumber()) return -1;
    return m_double_value;
}

bool operator==(ByteToken const& a, ByteToken const& b) {
    return (a.isString() && b.isString()) && (a.isIntegerNumber() && b.isIntegerNumber()) && (a.isDoubleNumber() && b.isDoubleNumber()) && (a.isMemory() && b.isMemory())
        && a.getIntegerValueIfExisting() == b.getIntegerValueIfExisting()
        && a.getStringValueIfExisting() == b.getStringValueIfExisting()
        && a.getValueIfExisting() == b.getValueIfExisting()
        && a.getType() == b.getType();
}
std::ostream& operator<<(std::ostream& os, ByteToken const& a) {
    return os << "ByteToken<" << a.getType() << ">{" << std::hex << a.getValueIfExisting() << ", " << std::dec << a.getIntegerValueIfExisting() << ", '" << a.getStringValueIfExisting() << "'}";
}