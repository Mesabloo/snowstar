project(MyProject)
include_directories(
    ${RootProject_SOURCE_DIR}/antlr/cpp_runtime/runtime/src
    ${RootProject_SOURCE_DIR}/lib/antlr
    ${RootProject_SOURCE_DIR}/ext
    ${RootProject_SOURCE_DIR}/include
)

file(
    GLOB_RECURSE SOURCE_FILES
    ${RootProject_SOURCE_DIR}/lib/antlr/*.cpp
    ${MyProject_SOURCE_DIR}/*.cpp
)

add_executable(
    MyProject ${SOURCE_FILES}
)

target_link_libraries(MyProject antlr4_shared)
if(CMAKE_DL_LIBS)
    target_link_libraries(MyProject ${CMAKE_DL_LIBS})
endif(CMAKE_DL_LIBS)

if (MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++17")
endif (MSVC)

if (CMAKE_COMPILER_IS_GNUCC)
#    set(CMAKE_CXX_FLAGS "-std=c++17 -O2 -march=native -DNDEBUG")
    set(CMAKE_CXX_FLAGS "-std=c++17 -ggdb -Wall -Wextra -W")
endif()

add_custom_command(
    TARGET MyProject POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory "${RootProject_SOURCE_DIR}/dist/" $<TARGET_FILE_DIR:MyProject>
)