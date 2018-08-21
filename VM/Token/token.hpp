#ifndef ATOMIC_TOKEN_HPP
#define ATOMIC_TOKEN_HPP

#include <stdint.h>
#include <optional>
#include <variant>

#include "value.hpp" 

class AtomicToken {
    public:
        AtomicToken();
        AtomicToken(uint8_t const, std::optional<int16_t> const&);
        ~AtomicToken() = default;

        uint8_t getInstruction() const;
        std::optional<int16_t> getArgument() const;

    protected:
        uint8_t m_instr;
        std::optional<int16_t> m_arg;
};

class LabelToken {
    public:
        LabelToken();
        LabelToken(uint16_t const, uint16_t const);
        ~LabelToken() = default;

        uint16_t getID() const;
        uint16_t getLine() const;

    protected:
        uint16_t m_id, m_line;
};

class ConstToken {
    public:
        ConstToken();
        ConstToken(uint16_t const, Value const&);
        ~ConstToken() = default;

        uint16_t getID() const;
        Value& getValue();

    protected:
        uint16_t m_id;
        Value m_value;
};

#endif