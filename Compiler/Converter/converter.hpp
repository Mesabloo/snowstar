#ifndef CONVERTER_HPP
#define CONVERTER_HPP

#include <memory>

#include <Lexer/token.hpp>

class Converter {
    public:
        Converter();
        ~Converter();

        bool start(std::vector<Consumer>) const;
};

#endif