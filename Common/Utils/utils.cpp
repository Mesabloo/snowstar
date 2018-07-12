#include <sstream>
#include <limits>
#include <fstream>
#include <algorithm>

#include "utils.hpp"

namespace utils {
    std::vector<std::string> str_split(std::string const& str, char const& separator) {
        std::vector<std::string> vect;
        std::istringstream f{str};
        std::string s;
        while (getline(f, s, separator)) {
            vect.push_back(s);
        }
        return vect;
    }

    bool str_endswith(std::string const& str, std::string const& suffix, unsigned suffixLen) {
        return str.size() >= suffixLen && 0 == str.compare(str.size()-suffixLen, suffixLen, suffix.c_str(), suffixLen);
    }

    bool str_endswith(std::string const& str, std::string const& suffix) {
        return str_endswith(str, suffix, std::string::traits_type::length(suffix.c_str()));
    }

    bool str_startswith(std::string const& str, std::string const& prefix, unsigned prefixLen) {
        return str.size() >= prefixLen && 0 == str.compare(0, prefixLen, prefix.c_str(), prefixLen);
    }

    bool str_startswith(std::string const& str, std::string const& prefix) {
        return str_startswith(str, prefix, std::string::traits_type::length(prefix.c_str()));
    }

    std::streamsize file_getsize(std::string const& path) {
        std::ifstream file;
        file.open(path, std::ios::in|std::ios::binary);
        file.ignore(std::numeric_limits<std::streamsize>::max());
        std::streamsize length = file.gcount();
        file.clear();   //  Since ignore will have set eof.
        file.seekg(0, std::ios_base::beg);
        file.close();
        return length;
    }

    bool str_is_number(const std::string& s) {
        return !s.empty() && std::find_if(s.begin(), 
            s.end(), [=](char c) { return !std::isdigit(c) && c != '.'; }) == s.end();
    }
}