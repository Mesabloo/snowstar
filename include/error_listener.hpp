#ifndef ERROR_LISTENER_HPP
#define ERROR_LISTENER_HPP

#include <BaseErrorListener.h>
#include <filesystem>

class ErrorListener : public antlr4::BaseErrorListener {
    #if !defined(_WIN32) && !defined(_WIN64)
    std::stringstream m_os;
    #else
    std::wstringstream m_os;
    #endif

    int lastError = -1;

public:
    ErrorListener() {}
    
    void syntaxError(antlr4::Recognizer* recog, antlr4::Token*, size_t line, size_t charPositionInLine, std::string const& msg, std::exception_ptr) override {
        #if !defined(_WIN32) && !defined(_WIN64)
        std::function<std::string(std::string const, unsigned int)> spacer = [=] (std::string const s1, unsigned int n) -> std::string { std::string s; for (unsigned int tmp{0};tmp < n;++tmp) s+=s1; return s; };
        #else
        std::function<std::wstring(std::wstring const, unsigned int)> spacer = [=] (std::wstring const s1, unsigned int n) -> std::wstring { std::wstring s; for (unsigned int tmp{0};tmp < n;++tmp) s+=s1; return s; };
        #endif

        std::string code = msg;
        #ifndef NDEBUG
            std::cerr << "   !!!   | Error in grammar file: " << recog->getGrammarFileName() << std::endl;
        #endif
        
        auto lexer = static_cast<SnowStarLexer*>(recog);
        std::string file = std::filesystem::canonical(std::filesystem::path(lexer->getSourceName()));
        
        m_os
        #if !defined(_WIN32) && !defined(_WIN64)
            << termcolor::colorize
            << termcolor::bold
        #endif
            << termcolor::on_red << termcolor::white
            << "Error"
            << termcolor::reset << termcolor::white
            << ": " << msg << "\n"
            << termcolor::grey
        #if !defined(_WIN32) && !defined(_WIN64)
            << termcolor::bold
        #else
            << termcolor::reset << termcolor::white
        #endif
        #if !defined(_WIN32) && !defined(_WIN64)
            << " ├─╼"
        #else
            << L" ├─╼"
        #endif
            << termcolor::reset << termcolor::red
            << " code"
            << termcolor::reset << termcolor::white
            << ": " << std::to_string(line+charPositionInLine) << "\n"
            << termcolor::grey
        #if !defined(_WIN32) && !defined(_WIN64)
            << termcolor::bold
        #else
            << termcolor::reset << termcolor::white
        #endif
        #if !defined(_WIN32) && !defined(_WIN64)
            << " ╰─╼ "
        #else
            << L" ╰─╼ "
        #endif
            << termcolor::reset << termcolor::green
            << file << " @ line " << std::to_string(line) << ":" << std::to_string(charPositionInLine+1) << "\n"
            << termcolor::reset
            << "\n";
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