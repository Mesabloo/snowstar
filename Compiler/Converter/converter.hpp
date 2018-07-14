#ifndef CONVERTER_HPP
#define CONVERTER_HPP

#include <vector>
#include <map>

#include <stdint.h>

#include "../Lexer/token.hpp"

class Converter {
    public:
        Converter();
        ~Converter();

        bool start(std::vector<Consumer*> const&) const;
};

#endif