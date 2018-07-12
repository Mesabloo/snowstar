#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>
#include <vector>
#include <iostream>
#include <iomanip>
#include <cstring>

namespace utils {
    std::vector<std::string> str_split(std::string const&, char const&);
    bool str_endswith(std::string const&, std::string const&);
    bool str_endswith(std::string const&, std::string const&, unsigned);
    bool str_startswith(std::string const&, std::string const&);
    bool str_startswith(std::string const&, std::string const&, unsigned);
    std::streamsize file_getsize(std::string const&);
    bool str_is_number(std::string const&);
    
    template <typename Word>
    std::ostream& stream_write(std::ostream& outs, Word value) {
        for (unsigned size = sizeof(Word); size; --size, value >>= 8)
            outs.put(static_cast<char>(value & 0xFF));
        return outs;
    }

    inline std::ostream& stream_write_float(std::ostream& outs, double value) {
        unsigned char c[sizeof(double)];
        memcpy(c, &value, sizeof(value));
        for (size_t i{0};i < sizeof(double);++i)
            stream_write<unsigned char>(outs, c[i]);
        return outs;
    }

    template <typename Word>
    std::istream& stream_read(std::istream& ins, Word& value) {
        value = 0;
        for (unsigned size = 0; size < sizeof(Word); ++size)
            value |= ins.get() << (8 * size);
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