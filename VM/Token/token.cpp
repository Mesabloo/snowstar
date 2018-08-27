#include "token.hpp"

AtomicToken::AtomicToken(): m_instr{0}, m_arg{std::nullopt} {}
AtomicToken::AtomicToken(uint8_t const instr, std::optional<int16_t> const& arg) : m_instr{instr}, m_arg{arg}, m_arg2{std::nullopt} {}
AtomicToken::AtomicToken(uint8_t const instr, std::optional<int16_t> const& arg, std::optional<int16_t> const& arg2) : m_instr{instr}, m_arg{arg}, m_arg2{arg2} {}

uint8_t AtomicToken::getInstruction() const { return m_instr; }
std::optional<int16_t> AtomicToken::getArgument() const { return m_arg; }
std::optional<int16_t> AtomicToken::getArgument2() const { return m_arg2; }


LabelToken::LabelToken(): m_id{0}, m_line{0} {}
LabelToken::LabelToken(uint16_t const id, uint16_t const line) : m_id{id}, m_line{line} {}

uint16_t LabelToken::getID() const { return m_id; }
uint16_t LabelToken::getLine() const { return m_line; }


ConstToken::ConstToken(): m_id{0}, m_value{Value{}} {}
ConstToken::ConstToken(uint16_t const id, Value const& value) : m_id{id}, m_value{value} {}

uint16_t ConstToken::getID() const { return m_id; }
Value& ConstToken::getValue() { return m_value; }