#ifndef VALUE_HPP
#define VALUE_HPP

#include <variant>
#include <string>
#include <cstdint>

using Value = std::variant<std::string, int64_t, double>;

#endif