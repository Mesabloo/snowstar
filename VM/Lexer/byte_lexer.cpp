#include <algorithm>
#include <iostream>

#include "byte_lexer.hpp"
#include "../../Common/Utils/utils.hpp"

#include "../../Common/info.hpp"

#include "../../Common/termcolor.hpp"

std::ifstream ByteLexer::is = std::ifstream();
long long ByteLexer::m_read_size = 0;

ByteLexer::ByteLexer(std::string const& file) {
    is = std::ifstream(file, std::ifstream::ios_base::binary);
    m_read_size = 0;
}
ByteLexer::~ByteLexer() {}

long long ByteLexer::getSize() const { return m_read_size; }

std::vector<ByteToken*> ByteLexer::readLine() {
    double value{0};
    std::vector<ByteToken*> vect;
    if (!is) {
        std::cerr << "\033[38;5;194m" << "The file you tried to read cannot be open." << std::endl;
        return {};
    }
    do {
        utils::stream_read_float(is, value);
        m_read_size += sizeof(value);
        ByteToken* t = checkValue(value);
        if (t != nullptr)
            vect.push_back(t);
    } while (value != static_cast<double>(info::Dividers::EOL));
    return vect;
}

std::string string_buffer, integer_buffer;
std::vector<ByteToken*> memory_type_buffer;
bool isString{false}, isNumber{false}, isMemory{false};
ByteToken* ByteLexer::checkValue(double const val) {
    // std::clog << termcolor::magenta << "Value=" << std::hex << static_cast<int64_t>(val) << "\tIsNumber=" << isNumber
    //    << "\tIsString=" << isString << "\tIsMemory=" << isMemory << termcolor::reset << std::endl;
    if (val == static_cast<double>(info::Dividers::EOL))
        return nullptr;
    if (val == static_cast<double>(info::Dividers::STRING) && !isString && !isNumber && !isMemory) {
        isString = true;
        return nullptr;
    }
    if ((val == static_cast<double>(info::Dividers::NUMBER_FLOAT) || val == static_cast<double>(info::Dividers::NUMBER_INTEGER)) && !isString && !isNumber) {
        isNumber = true;
        return nullptr;
    }
    if (val == static_cast<double>(info::Dividers::MEMORY) && !isString && !isNumber && !isMemory) {
        isMemory = true;
        return nullptr;
    }
    if (val == static_cast<double>(info::Dividers::INSTR_PARAMS) && !isString && !isNumber && !isMemory)
        return new ByteToken(ByteToken::Type::SEPARATOR, static_cast<double>(val));
    if (isString) {
        if (val == static_cast<double>(info::Dividers::STRING)) {
            ByteToken* t = new ByteToken(ByteToken::Type::LITERAL_STRING, string_buffer);
            string_buffer = "";
            isString = false;
            return t;
        } else
            string_buffer += static_cast<char>(val - 0x21);
        return nullptr;
    }
    if (isNumber) {
        if (val == static_cast<double>(info::Dividers::NUMBER_INTEGER)) {
            char* end;
            ByteToken* t = new ByteToken(ByteToken::Type::LITERAL_NUMBER, static_cast<int64_t>(std::strtod(integer_buffer.c_str(), &end)));
            integer_buffer = "";
            isNumber = false;
            if (!isMemory)
                return t;
            memory_type_buffer.push_back(t);
        } else if (val == static_cast<double>(info::Dividers::NUMBER_FLOAT)) {
            ByteToken* t = new ByteToken(ByteToken::Type::LITERAL_NUMBER, std::stod(integer_buffer), true);
            integer_buffer = "";
            isNumber = false;
            return t;
        } else
            integer_buffer += std::to_string(val);
        return nullptr;
    }
    if (isMemory) {
        if (val == static_cast<double>(info::Dividers::MEMORY)) {
            ByteToken* t = new ByteToken(ByteToken::Type::LITERAL_MEMORY, memory_type_buffer[0]->getValueIfExisting(), memory_type_buffer[1]->getIntegerValueIfExisting());
            memory_type_buffer.erase(memory_type_buffer.begin(), memory_type_buffer.end());
            isMemory = false;
            return t;
        } else
            memory_type_buffer.push_back(new ByteToken(ByteToken::Type::KEYWORD, static_cast<double>(val), false));
        return nullptr;
    }
    return new ByteToken(ByteToken::Type::KEYWORD, static_cast<double>(val), false);
}

ByteConsumer* ByteLexer::createConsumerFromLine(std::vector<ByteToken*> line) const {
    if (line.size() == 0)
        return nullptr;
    int argc = line.size();
    ByteToken* instr = line[0];
    ByteToken* mem_or_div = line[1];
    if (mem_or_div->getType() == ByteToken::Type::SEPARATOR)
        argc -= 2;
    else
        argc -= 3;
    if (argc < 0) {
        std::cerr << termcolor::red << "Actual argument number cannot be smaller than 0 ! (i.e. argc=" << argc << " is not valid)" << std::endl;
        return nullptr;
    }
    if (argc == 0) {
        if (mem_or_div->getType() == ByteToken::Type::SEPARATOR)
            return new ByteConsumer(*instr, ByteConsumer::Store(), {});
        else
            return new ByteConsumer(*instr, ByteConsumer::Store(*mem_or_div), {});
    }
    std::vector<ByteToken> args;
    for (size_t i = line.size()-argc;i < line.size();++i)
        args.push_back(*line[i]);
    if (mem_or_div->getType() == ByteToken::Type::SEPARATOR)
        return new ByteConsumer(*instr, ByteConsumer::Store(), args);
    else
        return new ByteConsumer(*instr, ByteConsumer::Store(*mem_or_div), args);
}