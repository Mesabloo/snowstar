cmake_minimum_required(VERSION 3.5)
cmake_policy(SET CMP0015 NEW)

project(SnowStarCompiler)

message(STATUS "Building project ${PROJECT_NAME}")

include_directories(
    ${SnowStar_SOURCE_DIR}/Common
    ${SnowStar_SOURCE_DIR}/Compiler
)

file(
    GLOB_RECURSE SOURCE_FILES
    ${SnowStarCompiler_SOURCE_DIR}/*.cpp
    ${SnowStar_SOURCE_DIR}/Common/*.cpp
)

add_executable(
    SnowStarCompiler ${SOURCE_FILES}
)

set_target_properties(
    SnowStarCompiler
    PROPERTIES
        VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD_REQUIRED ON)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_EXTENSIONS OFF)

if (MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++17")
endif (MSVC)

if (CMAKE_COMPILER_IS_GNUCC)
#    set(CMAKE_CXX_FLAGS "-std=c++17 -O2 -march=native -DNDEBUG")
    set(CMAKE_CXX_FLAGS "-std=c++17 -ggdb -Wall -Wextra -W -Wl,--export-dynamic")
endif()