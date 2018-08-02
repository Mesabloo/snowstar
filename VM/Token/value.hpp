#ifndef VALUE_HPP
#define VALUE_HPP

#include <variant>
#include <string>
#include <stdint.h>

using Value = std::variant<std::string, int32_t, float>;

#endif