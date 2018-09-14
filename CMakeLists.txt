cmake_minimum_required(VERSION 3.5)
cmake_policy(SET CMP0015 NEW)

project(RootProject)

add_subdirectory(antlr/cpp_runtime/)
add_subdirectory(llvm/)
add_subdirectory(src/)