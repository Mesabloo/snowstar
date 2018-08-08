#ifndef CONVERTER_HPP
#define CONVERTER_HPP

#include <Lexer/token.hpp>

class Converter {
    public:
        Converter();
        ~Converter();

        bool start(std::vector<Consumer*>) const;
};

#endif