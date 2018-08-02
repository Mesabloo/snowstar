#include "token.hpp"

AtomicToken::AtomicToken(uint8_t const instr, std::optional<int16_t> const& arg) : m_instr{instr}, m_arg{arg} {}
AtomicToken::~AtomicToken() {}

uint8_t AtomicToken::getInstruction() const { return m_instr; }
std::optional<int16_t> AtomicToken::getArgument() const { return m_arg; }


LabelToken::LabelToken(uint16_t const id, uint16_t const line) : m_id{id}, m_line{line} {}
LabelToken::~LabelToken() {}

uint16_t LabelToken::getID() const { return m_id; }
uint16_t LabelToken::getLine() const { return m_line; }


ConstToken::ConstToken(uint16_t const id, Value const& value) : m_id{id}, m_value{value} {}
ConstToken::~ConstToken() {}

uint16_t ConstToken::getID() const { return m_id; }
Value ConstToken::getValue() const { return m_value; }