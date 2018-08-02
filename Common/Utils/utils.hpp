#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>
#include <vector>
#include <iostream>
#include <iomanip>
#include <cstring>
#include <type_traits>

namespace utils {
    auto to_upper = [] (char ch) {
        return std::use_facet<std::ctype<char>>(std::locale()).toupper(ch);
    };

    std::vector<std::string> str_split(std::string const&, char const);
    bool str_endswith(std::string const&, std::string const&);
    bool str_endswith(std::string const&, std::string const&, unsigned);
    bool str_startswith(std::string const&, std::string const&);
    bool str_startswith(std::string const&, std::string const&, unsigned);
    std::streamsize file_getsize(std::string const&);
    bool str_is_number(std::string const&);
    std::string str_join(std::string const&, std::string const&, char const);

    template <typename T = int, typename = std::enable_if<std::is_integral<T>::value>>
    std::string int_to_hex(T val) {
        std::stringstream ss;
        ss << std::setw(sizeof(T)) << std::setfill('0') << std::hex << val;
        return std::string{ss.str()};
    }

    template <typename T>
    T number_fromString(std::string const& value) {
        std::istringstream ss(value);
        T return_value;
        ss >> return_value;
        return return_value;
    }
    
    template <typename Word>
    std::ostream& stream_write(std::ostream& outs, Word value) {
        for (unsigned size = sizeof(Word); size; --size, value >>= 8) {
            outs.put(static_cast<unsigned char>(value & 0xFF));
            std::cout << std::hex << std::setfill('0') << std::setw(2) << (value & 0xFF) << " ";
        }
        return outs;
    }

    inline std::ostream& stream_write_float(std::ostream& outs, double value) {
        unsigned char c[sizeof(double)];
        memcpy(c, &value, sizeof(value));
        for (size_t i{0};i < sizeof(double);++i)
            stream_write<unsigned char>(outs, c[i]);
        std::cout << std::endl;
        return outs;
    }

    template <typename Word>
    std::istream& stream_read(std::istream& ins, Word& value) {
        value = 0;
        for (unsigned size = 0; size < sizeof(Word); ++size) {
            value |= ins.get() << (8 * size);
            //std::cout << std::hex << std::setfill('0') << std::setw(2) << (value & 0xFF) << " ";
            //std::cout.flush();
        }
        return ins;
    }

    inline std::istream& stream_read_float(std::istream& ins, double& value) {
        value = 0;
        unsigned char c[sizeof(double)] = {0,0,0,0,0,0,0,0};
        for (size_t i{0};i < sizeof(double);++i)
            stream_read<unsigned char>(ins, c[i]);
        memcpy(&value, c, sizeof(value));
        return ins;
    }
}

#endif