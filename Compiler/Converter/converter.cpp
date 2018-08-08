#include <fstream>
#include <string>
#include <iostream>
#include <algorithm>

#include <Utils/utils.hpp>
#include <info.hpp>
#include "converter.hpp"
#include <termcolor.hpp>
#include <values.hpp>

Converter::Converter() {}
Converter::~Converter() {}

bool Converter::start(std::vector<std::shared_ptr<Consumer>> consumers) const {
    std::string const header{"snowstar"};
    std::vector<std::string> labels_table,
                             consts_table,
                             code_table;
    std::map<std::string, uint16_t> label_corres;
    uint16_t labels_id{1},
             consts_id{0},
             instrs_no{0};
    int line{0};
    for (size_t i{0};i < consumers.size();++i) {
        std::shared_ptr<Consumer>& c{consumers[i]};
        if (c->getInstruction().getType() == Token::Type::EOL) continue;
        for (auto const& arg : c->getArgs()) {
            if (utils::str_startswith(Token::getTypeSignification(arg.getType()), "Literal."))
                line++;
        }
        if (c->getInstruction().getValue() == "lbl") {
            std::string id_no{""};
            std::string instruction{"LABEL "};
            if (c->getArgs()[0].getValue() == "main") {
                id_no += static_cast<unsigned char>(0 & 0x00ff);
                id_no += static_cast<unsigned char>(0 & 0xff00);
                instruction += static_cast<unsigned char>(0 & 0x00ff);
                instruction += static_cast<unsigned char>(0 & 0xff00);
                label_corres[c->getArgs()[0].getValue()] = 0;
            } else {
                id_no += static_cast<unsigned char>(labels_id & 0x00ff);
                id_no += static_cast<unsigned char>(labels_id & 0xff00);
                instruction += static_cast<unsigned char>(labels_id & 0x00ff);
                instruction += static_cast<unsigned char>(labels_id & 0xff00);
                label_corres[c->getArgs()[0].getValue()] = labels_id;
            }
            id_no += static_cast<unsigned char>((i+line) & 0x00ff);
            id_no += static_cast<unsigned char>((i+line) & 0xff00);
            labels_table.push_back(id_no);
            code_table.resize(i+line+1);
            code_table[i+line] = instruction;
            std::cout << "Label at line " << (i+line) << std::endl;
            if (c->getArgs()[0].getValue() != "main")
                labels_id++;
            continue;
        }
        //line++;
    }
    for (auto& c : consumers) {
        if (c->getInstruction().getType() == Token::Type::EOL) continue;
        for (auto& t : c->getArgs()) {
            if (utils::str_startswith(Token::getTypeSignification(t.getType()), "Literal.")) {
                uint16_t size{8};
                std::string value{""};
                switch (t.getType()) {
                    case Token::Type::LITERAL_MEMORY: {
                        std::string name{utils::str_split(t.getValue(), '.')[0]};
                        std::string index{utils::str_split(t.getValue(), '.')[1]};
                        uint8_t mem{info::m_bytes[name]};
                        value += static_cast<unsigned char>(mem & 0xff);
                        value += static_cast<unsigned char>(static_cast<uint8_t>(std::stoi(index)));
                        t = Token(Token::Type::MEM_TABLE, value);
                        if (instrs_no+1 > code_table.size())
                            code_table.resize(code_table.size()+1);
                        code_table[instrs_no] = "LOAD_MEM " + value;
                        break;
                    }
                    case Token::Type::LITERAL_NUMBER_FLOAT: {
                        std::string hexa{t.getValue()};
                        size = hexa.size();
                        value += '\x05';
                        value += static_cast<unsigned char>(size & 0x00ff);
                        value += static_cast<unsigned char>(size & 0xff00);
                        for (int i{0};i < size;++i)
                            value += hexa[i] + 0x20;
                        t = Token(Token::Type::CONST_TABLE, std::to_string(consts_id));
                        std::string id_no{""};
                        id_no += static_cast<unsigned char>(consts_id & 0x00ff);
                        id_no += static_cast<unsigned char>(consts_id & 0xff00);
                        id_no += value;
                        consts_table.push_back(id_no);
                        std::string instruction{"LOAD_CONST "};
                        instruction += static_cast<unsigned char>(consts_id & 0x00ff);
                        instruction += static_cast<unsigned char>(consts_id & 0xff00);
                        if (instrs_no+1 > code_table.size())
                            code_table.resize(code_table.size()+1);
                        code_table[instrs_no] = instruction;
                        consts_id++;
                        break;
                    }
                    case Token::Type::LITERAL_NUMBER_INT: {
                        value += '\x04';
                        value += static_cast<unsigned char>(size & 0x00ff);
                        value += static_cast<unsigned char>(size & 0xff00);
                        std::string hex = utils::int_to_hex<int64_t>(std::stoll(t.getValue()));
                        for (auto const c : hex)
                            value += c + 0x10;
                        t = Token(Token::Type::CONST_TABLE, std::to_string(consts_id));
                        std::string id_no{""};
                        id_no += static_cast<unsigned char>(consts_id & 0x00ff);
                        id_no += static_cast<unsigned char>(consts_id & 0xff00);
                        id_no += value;
                        consts_table.push_back(id_no);
                        std::string instruction{"LOAD_CONST "};
                        instruction += static_cast<unsigned char>(consts_id & 0x00ff);
                        instruction += static_cast<unsigned char>(consts_id & 0xff00);
                        if (instrs_no+1 > code_table.size())
                            code_table.resize(code_table.size()+1);
                        code_table[instrs_no] = instruction;
                        consts_id++;
                        break;
                    }
                    case Token::Type::LITERAL_STRING: {
                        value += '\x03';
                        size = t.getValue().size()-2;
                        std::string val{t.getValue().substr(1, size)};
                        value += static_cast<unsigned char>(size & 0x00ff);
                        value += static_cast<unsigned char>(size & 0xff00);
                        for (auto const charac : val)
                            value += static_cast<unsigned char>(charac + 0x20);
                        t = Token(Token::Type::CONST_TABLE, std::to_string(consts_id));
                        std::string id_no{""};
                        id_no += static_cast<unsigned char>(consts_id & 0x00ff);
                        id_no += static_cast<unsigned char>(consts_id & 0xff00);
                        id_no += value;
                        consts_table.push_back(id_no);
                        std::string instruction{"LOAD_CONST "};
                        instruction += static_cast<unsigned char>(consts_id & 0x00ff);
                        instruction += static_cast<unsigned char>(consts_id & 0xff00);
                        if (instrs_no+1 > code_table.size())
                            code_table.resize(code_table.size()+1);
                        code_table[instrs_no] = instruction;
                        consts_id++;
                        break;
                    }
                }
                instrs_no++;
            }
        }
        std::string instr{c->getInstruction().getValue()},
                    memseg{c->getStorage().getMemseg().getValue()},
                    index{c->getStorage().getIndex().getValue()};;
        std::transform(instr.begin(), instr.end(), instr.begin(), utils::to_upper);
        if (instr != "LBL") {
            instr += ' ';
            //std::cout << instrs_no << " // " << instr << std::endl;
            if (instr == "JMP " || instr == "CALL " || instr == "JWE " || instr == "JWD " || instr == "JWL " || instr == "JWG ") {
                uint16_t instr_number = label_corres[c->getArgs()[0].getValue()];
                std::string instruction{""};
                instruction += static_cast<unsigned char>(instr_number & 0x00ff);
                instruction += static_cast<unsigned char>(instr_number & 0xff00);
                instr += instruction;
            }
            if (index != "-1") {
                uint8_t mem{info::m_bytes[memseg]};
                instr += static_cast<unsigned char>(mem);
                instr += static_cast<unsigned char>(static_cast<uint8_t>(std::stoi(index)));
            }
            try {
                std::string lbl = code_table.at(instrs_no);
                if (!utils::str_startswith(lbl, "LABEL")) throw std::out_of_range{""};
                std::cout << "There's a label at line " << instrs_no << std::endl;
            } catch (const std::out_of_range& oor) {
                if (instrs_no+1 > code_table.size())
                    code_table.resize(code_table.size()+1);
                code_table[instrs_no] = instr;
                std::cout << "We inserted " << instr << " at line " << instrs_no << std::endl;
            }
            //instrs_no++;
        }
        instrs_no++;
    }

    std::cout << termcolor::magenta << "Pseudo bytecode:" << std::endl;

    std::clog << header << std::endl;
    uint16_t label_no0{labels_id};
    std::cout << "LABEL_TABLE " << label_no0 << std::endl;
    for (auto const& l : labels_table)
        std::cout << l << std::endl;
    uint16_t const_no0{consts_id};
    std::cout << "CONST_TABLE " << const_no0 << std::endl;
    for (auto const& c : consts_table)
        std::cout << c << std::endl;
    uint16_t instr_no0{instrs_no};
    std::cout << "CODE_TABLE " << instr_no0 << std::endl;
    for (auto const& s : code_table)
        std::cout << s << std::endl;


    std::ofstream out{vars::PATH + "/out.cwsc", std::ios_base::binary};
    std::cout << std::endl << termcolor::reset << termcolor::red << "Bytecode:" << std::endl;

    for (auto hchar : header) {
        //std::cout << hchar;
        utils::stream_write<unsigned char>(out, hchar);
    }
    uint16_t label_no{labels_id};
    //std::cout << info::m_bytes["LABEL_TABLE"] << static_cast<unsigned char>(label_no & 0x00ff) << static_cast<unsigned char>(label_no & 0xff00);
    utils::stream_write<unsigned char>(out, info::m_bytes["LABEL_TABLE"]);
    utils::stream_write<uint16_t>(out, label_no);
    for (auto const& l : labels_table) {
        //std::cout << l;
        for (auto hchar : l)
            utils::stream_write<unsigned char>(out, hchar);
    }
    uint16_t const_no{consts_id};
    //std::cout << info::m_bytes["CONST_TABLE"] << static_cast<unsigned char>(const_no & 0x00ff) << static_cast<unsigned char>(const_no & 0xff00);
    utils::stream_write<unsigned char>(out, info::m_bytes["CONST_TABLE"]);
    utils::stream_write<uint16_t>(out, const_no);
    for (auto const& c : consts_table) {
        //std::cout << c;
        for (auto hchar : c)
            utils::stream_write<unsigned char>(out, hchar);
    }
    uint16_t instr_no{instrs_no};
    //std::cout << info::m_bytes["CODE_TABLE"] << static_cast<unsigned char>(instr_no & 0x00ff) << static_cast<unsigned char>(instr_no & 0xff00);
    utils::stream_write<unsigned char>(out, info::m_bytes["CODE_TABLE"]);
    utils::stream_write<uint16_t>(out, instr_no);
    for (auto const& s : code_table) {
        std::vector<std::string> splitted = utils::str_split(s, ' ');
        if (splitted.size() == 1) {
            //std::cout << '\x01' << info::m_bytes[splitted[0]];
            utils::stream_write<unsigned char>(out, '\x00');
            utils::stream_write<unsigned char>(out, info::m_bytes[splitted[0]]);
        } else {
            //std::cout << '\x02' << info::m_bytes[splitted[0]] << splitted[1];
            utils::stream_write<unsigned char>(out, '\x01');
            utils::stream_write<unsigned char>(out, info::m_bytes[splitted[0]]);
            for (auto hchar : splitted[1])
                utils::stream_write<unsigned char>(out, hchar);
        }
    }

    std::cout << termcolor::reset << std::endl;
    out.flush();
    out.close();

    return true;
}