cmake_minimum_required(VERSION 3.5)
cmake_policy(SET CMP0015 NEW)

project(SnowStar)

add_subdirectory(Compiler/)
add_subdirectory(Debugger/)
add_subdirectory(VM/)