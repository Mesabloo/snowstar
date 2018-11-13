/*
 *  Snow* Compiler, a compiler made with ANTLR and LLVM for compiling Snow* source code
 *  Copyright (C) 2018  Mesabloo
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.

 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef ERROR_LISTENER_HPP
#define ERROR_LISTENER_HPP

#include <BaseErrorListener.h>
#include <filesystem>

class ErrorListener : public antlr4::BaseErrorListener {
    #if !defined(_WIN32) && !defined(_WIN64)
    std::ostream& m_os{std::cerr};
    #else
    std::wostream& m_os{std::wcerr};
    #endif

    inline std::vector<std::string> str_split(std::string const& str, char const separator) {
        std::vector<std::string> vect;
        std::istringstream f{str};
        std::string s;
        while (getline(f, s, separator)) {
            vect.push_back(s);
        }
        return vect;
    }

public:
    ErrorListener() {}
    
    void syntaxError(antlr4::Recognizer* recog, antlr4::Token*, size_t line, size_t charPositionInLine, std::string const& msg, std::exception_ptr) override {
        #if !defined(_WIN32) && !defined(_WIN64)
        std::function<std::string(std::string const, unsigned int)> spacer = [=] (std::string const s1, unsigned int n) -> std::string { std::string s; for (unsigned int tmp{0};tmp < n;++tmp) s+=s1; return s; };
        #else
        std::function<std::wstring(std::wstring const, unsigned int)> spacer = [=] (std::wstring const s1, unsigned int n) -> std::wstring { std::wstring s; for (unsigned int tmp{0};tmp < n;++tmp) s+=s1; return s; };
        #endif

        #ifndef NDEBUG
            std::cerr << "   !!!   | Error in grammar file: " << recog->getGrammarFileName() << std::endl;
        #endif
        
        auto lexer = static_cast<SnowStarLexer*>(recog);
        std::string file = std::filesystem::canonical(std::filesystem::path(lexer->getSourceName()));

        auto split = str_split(msg, '\n');
        std::string code = split[1];
        if (code == "")
            code = split[2];

        int first_charac = std::stoi(split[4]);
        
        std::size_t pos = code.find(split[2], std::stoi(split[3])-1-first_charac);
        if (pos != std::string::npos) {
            std::stringstream ss;
            ss
            #if !defined(_WIN32) && !defined(_WIN64)
                << termcolor::colorize
            #endif
                << termcolor::white
                << code.substr(0, pos)
                << termcolor::reset << termcolor::red
                << code.substr(pos, split[2].size())
                << termcolor::reset;
            if (pos+split[2].size()+1 < code.size()) {
                ss  << termcolor::white
                    << code.substr(pos+split[2].size())
                    << termcolor::reset;
            }
            code = ss.str();
        }
        
        m_os
        #if !defined(_WIN32) && !defined(_WIN64)
            << termcolor::colorize
            << termcolor::bold
        #endif
            << termcolor::on_red << termcolor::white
            << "Error"
            << termcolor::reset << termcolor::white
            << ": " << split[0] << "\n"
            << termcolor::grey
        
        #if !defined(_WIN32) && !defined(_WIN64)
            << termcolor::bold
        #else
            << termcolor::reset << termcolor::white
        #endif
        #if !defined(_WIN32) && !defined(_WIN64)
            << " ╰┬╼ "
        #else
            << L" ╰┬╼ "
        #endif
            << termcolor::reset << termcolor::green
            << file << " @ line " << std::to_string(line) << ":" << std::to_string(charPositionInLine+1) << "\n"
            << termcolor::reset << termcolor::grey
        #if !defined(_WIN32) && !defined(_WIN64)
            << termcolor::bold
        #else
            << termcolor::reset << termcolor::white
        #endif
        #if !defined(_WIN32) && !defined(_WIN64)
            << "  │"
        #else
            << L"  │"
        #endif
            << spacer(" ", std::stoi(split[3])+3-first_charac)
            << termcolor::reset << termcolor::red
        #if !defined(_WIN32) && !defined(_WIN64)
            << spacer("⌄", split[2].size())
        #else
            << spacer(L"⌄", split[2].size())
        #endif
            << termcolor::grey
        #if !defined(_WIN32) && !defined(_WIN64)
            << termcolor::bold
        #else
            << termcolor::reset << termcolor::white
        #endif
            << "\n"
        #if !defined(_WIN32) && !defined(_WIN64)
            << "  ╰──╼" << " "
        #else
            << L"  ╰──╼" << " "
        #endif
            << termcolor::reset
            << code
            << "\n";
    }
    
    friend std::ostream& operator<<(std::ostream& os, ErrorListener const& errListener) {
        //os << errListener.m_os.str();
        return os;
    }
};

#endif