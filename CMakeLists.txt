cmake_minimum_required(VERSION 3.8)
cmake_policy(SET CMP0015 NEW)

project(SnowStar)

add_subdirectory(antlr/cpp_runtime/)
# add_subdirectory(llvm/)
add_subdirectory(src/)