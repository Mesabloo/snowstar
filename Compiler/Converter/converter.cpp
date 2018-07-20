#include <fstream>
#include <sstream>
#include <iomanip>
#include <regex>

#include "converter.hpp"
#include "../../Common/values.hpp"
#include "../../Common/Utils/utils.hpp"
#include "../../Common/termcolor.hpp"

#include "../../Common/info.hpp"

Converter::Converter() {}
Converter::~Converter() {}

bool Converter::start(std::vector<Consumer*> const& cons) const {
    std::ofstream os;
    os.open(vars::PATH + "/out.ssbc", std::ofstream::ios_base::binary | std::ofstream::ios_base::out);
    os << std::hex;
    for (auto const& c : cons) {
        Token const instr = c->getInstruction();
        Consumer::Store const storage = c->getStorage();
        std::vector<Token> const args = c->getArgs();

        utils::stream_write_float(os, info::m_bytes[instr.getValue()]);
        if (storage.getIndex().getValue() != "-1") {
            utils::stream_write_float(os, static_cast<double>(info::Dividers::MEMORY));
            utils::stream_write_float(os, info::m_bytes[storage.getMemseg().getValue()]);
            std::string val = storage.getIndex().getValue();
            double value;
            try {
                value = static_cast<double>(std::stoi(val));
            } catch (std::invalid_argument& e) {
                std::cerr << termcolor::red << "Compilation aborted. Error code: 0x" << std::hex << 0x10594972 << '\n'
                    << "IllegalTypeException" << ": " << "Invalid integer '" << val << "' given as memory index." << "\033[0m" << std::endl;
                return false;
            }
            double div = static_cast<double>(info::Dividers::NUMBER_INTEGER);
            utils::stream_write_float(os, div);
            utils::stream_write_float(os, value);
            utils::stream_write_float(os, div);
            utils::stream_write_float(os, static_cast<double>(info::Dividers::MEMORY));
        }

        utils::stream_write_float(os, static_cast<double>(info::Dividers::INSTR_PARAMS));

        for (Token const& t : args) {
            switch (t.getType()) {
                case Token::Type::KEYWORD: {
                    utils::stream_write_float(os, info::m_bytes[t.getValue()]);
                    break;
                }
                case Token::Type::LITERAL_STRING: {
                    std::string val = t.getValue();
                    val.erase(val.begin(), val.begin()+1);
                    val.erase(val.end()-1, val.end());
                    utils::stream_write_float(os, static_cast<double>(info::Dividers::STRING));
                    for (char const& c : val) {
                        utils::stream_write_float(os, static_cast<double>(c) + 0x21);
                    }
                    utils::stream_write_float(os, static_cast<double>(info::Dividers::STRING));
                    break;
                }
                case Token::Type::LITERAL_NUMBER_INT: {
                    std::string val = t.getValue();
                    double value;
                    try {
                        value = std::stod(val);
                    } catch (std::invalid_argument& e) {
                        std::cerr << termcolor::red << "Compilation aborted. Error code: 0x" << std::hex << 0x10594972 << '\n'
                            << "IllegalTypeException" << ": " << "Invalid integer '" << val << "'." << "\033[0m" << std::endl;
                        return false;
                    }
                    double div;
                    div = static_cast<double>(info::Dividers::NUMBER_INTEGER);
                    utils::stream_write_float(os, div);
                    utils::stream_write_float(os, value);
                    utils::stream_write_float(os, div);
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
                    double div;
                    div = static_cast<double>(info::Dividers::NUMBER_FLOAT);
                    utils::stream_write_float(os, div);
                    utils::stream_write_float(os, value);
                    utils::stream_write_float(os, div);
                    break;
                }
                case Token::Type::LITERAL_MEMORY: {
                    utils::stream_write_float(os, static_cast<double>(info::Dividers::MEMORY));
                    std::string const seg = utils::str_split(t.getValue(), '.')[0],
                                      val = utils::str_split(t.getValue(), '.')[1];
                    utils::stream_write_float(os, info::m_bytes[seg]);
                    double value;
                    try {
                        value = static_cast<double>(std::stoi(val));
                    } catch (std::invalid_argument& e) {
                        std::cerr << termcolor::red << "Compilation aborted. Error code: 0x" << std::hex << 0x10594972 << '\n'
                            << "IllegalTypeException: " << "Invalid integer '" << val << "' given as memory index." << "\033[0m" << std::endl;
                        return false;
                    }
                    double div = static_cast<double>(info::Dividers::NUMBER_INTEGER);
                    utils::stream_write_float(os, div);
                    utils::stream_write_float(os, value);
                    utils::stream_write_float(os, div);
                    utils::stream_write_float(os, static_cast<double>(info::Dividers::MEMORY));
                    break;
                }
                default:
                    break;
            }
        }
        utils::stream_write_float(os, static_cast<double>(info::Dividers::EOL));
    }

    os.flush();
    os.close();
    return true;
}