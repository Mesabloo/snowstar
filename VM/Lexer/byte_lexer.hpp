#ifndef BYTE_LEXER_HPP
#define BYTE_LEXER_HPP

#include <vector>
#include <fstream>

#include "byte_token.hpp"
#include "byte_consumer.hpp"

class ByteLexer {
    public:
        ByteLexer(std::string const&);
        ~ByteLexer();

        std::vector<ByteToken*> readLine();
        ByteConsumer* createConsumerFromLine(std::vector<ByteToken*>) const;

        long long getSize() const;
        static std::ifstream is;

    private:
        ByteToken* checkValue(int8_t const);

    protected:
        static long long m_read_size;
};

#endif