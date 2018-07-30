#include <fstream>
#include <sstream>
#include <iomanip>
#include <regex>

#include "converter.hpp"
#include <values.hpp>
#include <Utils/utils.hpp>
#include <termcolor.hpp>
#include <info.hpp>

Converter::Converter() {}
Converter::~Converter() {}

bool Converter::start(std::vector<Consumer*> const& cons) const {
    std::ofstream os;
    os.open(vars::PATH + "/out.ssbc", std::ofstream::ios_base::binary | std::ofstream::ios_base::out);
    os << std::hex;
    for (auto const& c : cons) {
        std::clog << termcolor::green << c->toString() << termcolor::reset << std::endl;
        Token const instr = c->getInstruction();
        Consumer::Store const storage = c->getStorage();
        std::vector<Token> const args = c->getArgs();

        utils::stream_write<int8_t>(os, info::m_bytes[instr.getValue()]);
        if (storage.getIndex().getValue() != "-1") {
            utils::stream_write<int8_t>(os, info::Dividers::MEMORY);
            utils::stream_write<int8_t>(os, info::m_bytes[storage.getMemseg().getValue()]);
            std::string val = storage.getIndex().getValue();
            std::string value;
            try {
                value = std::to_string(std::stoll(val));
            } catch (std::invalid_argument& e) {
                std::cerr << termcolor::red << "Compilation aborted. Error code: 0x" << std::hex << 0x10594972 << '\n'
                    << "IllegalTypeException" << ": " << "Invalid integer '" << val << "'." << "\033[0m" << std::endl;
                return false;
            }
            int8_t div = info::Dividers::NUMBER_INTEGER;
            utils::stream_write<int8_t>(os, div);
            for (char const& c : value)
                utils::stream_write<char>(os, c);
            utils::stream_write<int8_t>(os, div);
            utils::stream_write<int8_t>(os, info::Dividers::MEMORY);
        }

        utils::stream_write<int8_t>(os, info::Dividers::INSTR_PARAMS);

        for (Token const& t : args) {
            switch (t.getType()) {
                case Token::Type::KEYWORD: {
                    utils::stream_write<int8_t>(os, info::m_bytes[t.getValue()]);
                    break;
                }
                case Token::Type::LITERAL_STRING: {
                    std::string val = t.getValue();
                    val.erase(val.begin(), val.begin()+1);
                    val.erase(val.end()-1, val.end());
                    utils::stream_write<int8_t>(os, info::Dividers::STRING);
                    for (char const& c : val) {
                        utils::stream_write<int8_t>(os, c + 0x21);
                    }
                    utils::stream_write<int8_t>(os, info::Dividers::STRING);
                    break;
                }
                case Token::Type::LITERAL_NUMBER_INT: {
                    std::string val = t.getValue();
                    std::string value;
                    try {
                        value = std::to_string(std::stoll(val));
                    } catch (std::invalid_argument& e) {
                        std::cerr << termcolor::red << "Compilation aborted. Error code: 0x" << std::hex << 0x10594972 << '\n'
                            << "IllegalTypeException" << ": " << "Invalid integer '" << val << "'." << "\033[0m" << std::endl;
                        return false;
                    }
                    int8_t div = info::Dividers::NUMBER_INTEGER;
                    utils::stream_write<int8_t>(os, div);
                    for (char const& c : value)
                        utils::stream_write<char>(os, c);
                    utils::stream_write<int8_t>(os, div);
                    break;
                }
                case Token::Type::LITERAL_NUMBER_FLOAT: {
                    std::string val = t.getValue();
                    double value;
                    try {
                        value = std::stod(val);
                    } catch (std::invalid_argument& e) {
                        std::cerr << termcolor::red << "Compilation aborted. Error code: 0x" << std::hex << 0x10594972 << '\n'
                            << "IllegalTypeException" << ": " << "Invalid float number '" << val << "'." << "\033[0m" << std::endl;
                        return false;
                    }
                    int8_t div = info::Dividers::NUMBER_FLOAT;
                    utils::stream_write<int8_t>(os, div);
                    utils::stream_write_float(os, value);
                    utils::stream_write<int8_t>(os, div);
                    break;
                }
                case Token::Type::LITERAL_MEMORY: {
                    utils::stream_write<int8_t>(os, info::Dividers::MEMORY);
                    std::string const seg = utils::str_split(t.getValue(), '.')[0],
                                      val = utils::str_split(t.getValue(), '.')[1];
                    utils::stream_write<int8_t>(os, info::m_bytes[seg]);
                    std::string value;
                    try {
                        value = std::to_string(std::stoll(val));
                    } catch (std::invalid_argument& e) {
                        std::cerr << termcolor::red << "Compilation aborted. Error code: 0x" << std::hex << 0x10594972 << '\n'
                            << "IllegalTypeException" << ": " << "Invalid integer '" << val << "'." << "\033[0m" << std::endl;
                        return false;
                    }
                    int8_t div = info::Dividers::NUMBER_INTEGER;
                    utils::stream_write<int8_t>(os, div);
                    for (char const& c : value)
                        utils::stream_write<char>(os, c);
                    utils::stream_write<int8_t>(os, div);
                    utils::stream_write<int8_t>(os, info::Dividers::MEMORY);
                    break;
                }
                default:
                    break;
            }
        }
        utils::stream_write<int8_t>(os, info::Dividers::EOL);
        std::cout << std::endl;
    }

    os.flush();
    os.close();
    return true;
}