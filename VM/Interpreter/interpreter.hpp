#ifndef INTERPRETER_HPP
#define INTERPRETER_HPP

#include <string>
#include <vector>
#include <stack>
#include <stdlib.h>
#include <utility>
#include <map>

#include "../Lexer/byte_consumer.hpp"
#include "../Lexer/byte_lexer.hpp"

class Interpreter {
    public:
        Interpreter(std::string const);
        ~Interpreter();

        void start(ByteLexer&);

    private:
        void loadConsumersInMemory(ByteLexer&);
        void checkDomainOfConsumer(ByteConsumer* const&);
        int8_t executeSystemConsumer(ByteConsumer* const&);
        int8_t executeMathsConsumer(ByteConsumer* const&);
        int8_t executeMemoryConsumer(ByteConsumer* const&);
        int8_t executeComparativeConsumer(ByteConsumer* const&);

    protected:

        typedef struct ValueContainer {
            uint32_t integer_storage;
            double float_storage;
            std::string string_storage;

            bool isIntegerNumber, isFloatingNumber, isString;
        } ValueContainer;

        std::vector<ByteConsumer*> m_consumers;
        std::streampos m_stream_size;

        std::map<uint32_t, ValueContainer> mem, temp;
        std::stack<ValueContainer> param;
};

#endif