#ifndef ERROR_LISTENER_HPP
#define ERROR_LISTENER_HPP

#include <BaseErrorListener.h>

class ErrorListener : public antlr4::BaseErrorListener {
    std::stringstream m_os;

public:
    ErrorListener() {}
    
    void syntaxError(antlr4::Recognizer*, antlr4::Token*, size_t line, size_t charPositionInLine, std::string const& msg, std::exception_ptr) override {
        m_os << "Error at [" << line << ";" << charPositionInLine << "]: " << msg << std::endl;
    }
    
    void resetStuff() {
        m_os.clear();
    }
    
    friend std::ostream& operator<<(std::ostream& os, ErrorListener const& errListener) {
        os << errListener.m_os.str();
        return os;
    }
};

#endif