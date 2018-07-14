#include <sstream>
#include <iostream>

#include "byte_consumer.hpp"

#include "../../Common/info.hpp"

ByteConsumer::Store::Store() : m_memory(ByteToken::Type::LITERAL_MEMORY, info::m_bytes["nost"], -1) {}
ByteConsumer::Store::Store(ByteToken const& memory) : m_memory(memory){}
ByteConsumer::Store::~Store() {}

ByteToken ByteConsumer::Store::getMemory() const { return m_memory; }

std::ostream& operator<<(std::ostream& os, ByteConsumer::Store const& a) {
    return os << "[ " << std::hex << a.getMemory().getValueIfExisting() << ", " << std::dec << a.getMemory().getIntegerValueIfExisting() << " ]";
}

bool operator==(ByteConsumer::Store const& a, ByteConsumer::Store const& b) {
    return a.getMemory() == b.getMemory();
}

ByteConsumer::ByteConsumer(ByteToken const& instruction, ByteConsumer::Store const& storage, std::vector<ByteToken> const& args) : m_instruction(instruction), m_storage(storage), m_args(args) {}
ByteConsumer::~ByteConsumer() {}

ByteToken ByteConsumer::getInstruction() const { return m_instruction; }
ByteConsumer::Store ByteConsumer::getStorage() const { return m_storage; }
std::vector<ByteToken> ByteConsumer::getArgs() const { return m_args; }

std::ostream& operator<<(std::ostream& os, ByteConsumer const& a) {
    std::stringstream ss;
    for (auto const& bt : a.getArgs())
        ss << bt << " ";
    return os << a.getInstruction() << a.getStorage() << " " << ss.str();
}
bool operator==(ByteConsumer const& a, ByteConsumer const& b) {
    bool all_args_types_valid{true};
    if (a.getArgs().size() != b.getArgs().size())
        all_args_types_valid = false;
    else
        for (size_t i{0};i < a.getArgs().size();++i)
            if (a.getArgs()[i].getType() != b.getArgs()[i].getType()) {
                all_args_types_valid = false;
                break;
            }
    return a.getInstruction() == b.getInstruction()
        && a.getStorage() == b.getStorage()
        && all_args_types_valid;
}