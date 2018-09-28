cmake_minimum_required(VERSION 3.8)
project(Compiler)

find_package(LLVM REQUIRED CONFIG)

message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")

include_directories(
    ${SnowStar_SOURCE_DIR}/antlr/cpp_runtime/runtime/src
    ${SnowStar_SOURCE_DIR}/lib/antlr
    ${SnowStar_SOURCE_DIR}/ext
    ${SnowStar_SOURCE_DIR}/include
    ${LLVM_INCLUDE_DIRS}
)

add_definitions(${LLVM_DEFINITIONS})

file(
    GLOB_RECURSE SOURCE_FILES
    ${SnowStar_SOURCE_DIR}/lib/antlr/*.cpp
    ${Compiler_SOURCE_DIR}/*.cpp
)

add_executable(
    Compiler ${SOURCE_FILES}
)

llvm_map_components_to_libnames(llvm_libs support core irreader)

target_link_libraries(Compiler antlr4_shared)
target_link_libraries(Compiler ${llvm_libs})
if(CMAKE_DL_LIBS)
    target_link_libraries(Compiler ${CMAKE_DL_LIBS})
endif(CMAKE_DL_LIBS)

target_compile_features(Compiler PUBLIC cxx_std_17)
set(CMAKE_BUILD_TYPE "Debug")

if (MSVC)
#    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++17")
endif (MSVC)

if (CMAKE_COMPILER_IS_GNUCC)
#    set(CMAKE_CXX_FLAGS "-std=c++17 -O2 -march=native -DNDEBUG")
    set(CMAKE_CXX_FLAGS "-ggdb -Wall -Wextra -W")
endif()

add_custom_command(
    TARGET Compiler POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory "${SnowStar_SOURCE_DIR}/dist/" $<TARGET_FILE_DIR:Compiler>
)