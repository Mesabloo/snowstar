#ifndef ERROR_LISTENER_HPP
#define ERROR_LISTENER_HPP

#include <BaseErrorListener.h>

class ErrorListener : public antlr4::BaseErrorListener {
    std::stringstream m_os;

public:
    ErrorListener() {}
    
    void syntaxError(antlr4::Recognizer* recog, antlr4::Token*, size_t line, size_t charPositionInLine, std::string const& msg, std::exception_ptr) override {
        auto lambda = [](int const n, char const c) -> std::string { std::string s; for (int i=0;i < n;++i) { s += c; } return s; };
        std::string code = msg;
        #ifndef NDEBUG
            std::cerr << "Error in grammar file: " << recog->getGrammarFileName() << std::endl;
        #endif
        m_os << termcolor::colorize << termcolor::red << "error at " << line << ":" << (charPositionInLine+1) << termcolor::reset << ": " << code << "\n";
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