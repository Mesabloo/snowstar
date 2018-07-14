#ifndef EXCEPT_HPP
#define EXCEPT_HPP

#include <string>

class Exception {
    public:
        Exception(std::string const, uint32_t const, std::string const);
        ~Exception();

        std::string getMessage() const;

    protected:
        std::string m_msg;
};

#endif