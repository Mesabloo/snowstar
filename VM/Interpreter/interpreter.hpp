#ifndef INTERPRETER_HPP
#define INTERPRETER_HPP

#include <string>
#include <variant>
#include <stack>
#include <array>
#include <vector>
#include <limits>
#include <chrono>
#include <random>
#include <memory>
#include <unordered_map>

#include <Token/token.hpp>
#include <Token/value.hpp>

class Interpreter {
    public:
        Interpreter();
        ~Interpreter();

        void start(std::string const&);

    private:
        bool make(std::string const&);
        bool domain(AtomicToken const&);
        int8_t exec_system(AtomicToken const&);
        int8_t exec_maths(AtomicToken const&);
        int8_t exec_memory(AtomicToken const&);
        int8_t exec_comparative(AtomicToken const&);
        int8_t exec_special(AtomicToken const&);

        std::chrono::system_clock::time_point begin;
        uint16_t line_number;

    protected:
        std::array<ConstToken, std::numeric_limits<uint16_t>::max()> const_table;
        std::array<LabelToken, std::numeric_limits<uint16_t>::max()> label_table;
        std::array<AtomicToken, std::numeric_limits<uint16_t>::max()> code_table;

        std::stack<Value> param;
        std::unordered_map<uint32_t, Value> mem;
        std::stack<std::unordered_map<uint32_t, Value>> temp;
        
        std::stack<Value*> loaded;

        std::stack<std::pair<Value&, uint16_t>> call_stack;
        int8_t conditioner;
        std::mt19937 generator;
};

#endif