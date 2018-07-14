#ifndef BYTE_TOKEN_HPP
#define BYTE_TOKEN_HPP

#include <string>
#include <iostream>

#include <stdlib.h>

class ByteToken {
    public:

        typedef enum class Type {
            LITERAL_STRING,
            LITERAL_NUMBER,
            LITERAL_MEMORY,
            KEYWORD,
            SEPARATOR
        } Type;

        friend std::ostream& operator<<(std::ostream&, ByteToken::Type const&);

        ByteToken(ByteToken::Type const&, double const); // keyword or separator
        ByteToken(ByteToken::Type const&, std::string const); // string literal
        ByteToken(ByteToken::Type const&, uint32_t const); // integer number literal
        ByteToken(ByteToken::Type const&, double const); // float number literal
        ByteToken(ByteToken::Type const&, double const, uint32_t const); // memory literal
        ~ByteToken();

        bool isString() const;
        bool isIntegerNumber() const;
        bool isDoubleNumber() const;
        bool isMemory() const;

        ByteToken::Type getType() const;
        double getValueIfExisting() const;
        std::string getStringValueIfExisting() const;
        uint32_t getIntegerValueIfExisting() const;
        double getDoubleValueIfExisting() const;

        friend std::ostream& operator<<(std::ostream&, ByteToken const&);
        friend bool operator==(ByteToken const&, ByteToken const&);

    protected:
        ByteToken::Type m_type;

        double m_value;
        std::string m_string_value;
        uint32_t m_integer_value;
        double m_double_value;

        bool isStr, isIntNumb, isDoubleNumb, isMem;
};

#endif