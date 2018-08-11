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

#include <Token/token.hpp>
#include <Token/value.hpp>

class Interpreter {
    public:
        Interpreter();
        ~Interpreter();

        void start(std::string const&);

    private:
        bool make(std::string const&);
        bool domain(std::unique_ptr<AtomicToken> const&);
        int8_t exec_system(std::unique_ptr<AtomicToken> const&);
        int8_t exec_maths(std::unique_ptr<AtomicToken> const&);
        int8_t exec_memory(std::unique_ptr<AtomicToken> const&);
        int8_t exec_comparative(std::unique_ptr<AtomicToken> const&);
        int8_t exec_special(std::unique_ptr<AtomicToken> const&);

        std::chrono::system_clock::time_point begin;
        uint16_t line_number;

    protected:
        std::array<std::unique_ptr<ConstToken>, std::numeric_limits<uint16_t>::max()> const_table;
        std::array<std::unique_ptr<LabelToken>, std::numeric_limits<uint16_t>::max()> label_table;
        std::array<std::unique_ptr<AtomicToken>, std::numeric_limits<uint16_t>::max()> code_table;

        std::stack<Value> param;
        std::array<Value, 256> mem;
        std::stack<std::array<Value, 32>> temp;
        
        std::stack<Value> loaded;

        std::stack<std::pair<Value&, uint16_t>> call_stack;
        int8_t conditioner;
        std::mt19937 generator;
};

#endif