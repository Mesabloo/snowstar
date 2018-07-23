#ifndef INTERPRETER_HPP
#define INTERPRETER_HPP

#include <string>
#include <vector>
#include <stack>
#include <stdlib.h>
#include <utility>
#include <map>
#include <random>
#include <time.h>

#include "../Lexer/byte_consumer.hpp"
#include "../Lexer/byte_lexer.hpp"

class Interpreter {
    public:
        Interpreter(std::string const);
        ~Interpreter();

        void start(ByteLexer&);

        struct ValueContainer {
            int64_t integer_storage{0};
            double float_storage{0};
            std::string string_storage{""};

            bool isIntegerNumber{false}, isFloatingNumber{false}, isString{false};
        };

    private:
        void loadConsumersInMemory(ByteLexer&);
        void configVM();
        void checkDomainOfConsumer(ByteConsumer* const&);
        int8_t executeSystemConsumer(ByteConsumer* const&);
        int8_t executeMathsConsumer(ByteConsumer* const&);
        int8_t executeMemoryConsumer(ByteConsumer* const&);
        int8_t executeComparativeConsumer(ByteConsumer* const&);

    protected:
        std::vector<ByteConsumer*> m_consumers;
        std::streampos m_stream_size;

        std::map<uint32_t, ValueContainer> mem, temp;
        std::stack<ValueContainer> param;

        std::map<std::string, uint32_t> labels;
        std::stack<uint32_t> call_stack;
        uint32_t line_number{0};

        short int condition;

        std::mt19937 generator;
        clock_t execution_time;
};

inline bool operator==(Interpreter::ValueContainer const a, Interpreter::ValueContainer const b) {
    return a.integer_storage == b.integer_storage &&
        a.float_storage == b.float_storage &&
        a.string_storage == b.string_storage &&
        a.isIntegerNumber == b.isIntegerNumber &&
        a.isFloatingNumber == b.isFloatingNumber &&
        a.isString == b.isString;
}

inline bool operator!=(Interpreter::ValueContainer const a, Interpreter::ValueContainer const b) {
    return !(a == b);
}

inline bool operator<(Interpreter::ValueContainer const a, Interpreter::ValueContainer const b) {
    if (a.isIntegerNumber ^ b.isIntegerNumber) return false;
    if (a.isFloatingNumber ^ b.isFloatingNumber) return false;
    if (a.isString ^ b.isString) return false;
    if (a.isIntegerNumber && b.isIntegerNumber) return a.integer_storage < b.integer_storage;
    if (a.isFloatingNumber && b.isFloatingNumber) return a.float_storage < b.float_storage;
    if (a.isString && b.isString) return a.string_storage < b.string_storage;
    return false;
}

inline bool operator>=(Interpreter::ValueContainer const a, Interpreter::ValueContainer const b) {
    return !(a < b);
}

inline bool operator>(Interpreter::ValueContainer const a, Interpreter::ValueContainer const b) {
    if (a.isIntegerNumber ^ b.isIntegerNumber) return false;
    if (a.isFloatingNumber ^ b.isFloatingNumber) return false;
    if (a.isString ^ b.isString) return false;
    if (a.isIntegerNumber && b.isIntegerNumber) return a.integer_storage > b.integer_storage;
    if (a.isFloatingNumber && b.isFloatingNumber) return a.float_storage > b.float_storage;
    if (a.isString && b.isString) return a.string_storage > b.string_storage;
    return false;
}

inline bool operator<=(Interpreter::ValueContainer const a, Interpreter::ValueContainer const b) {
    return !(a > b);
}

#endif