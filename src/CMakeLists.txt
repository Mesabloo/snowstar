cmake_minimum_required(VERSION 3.8)
project(Compiler C CXX)

find_package(LLVM REQUIRED CONFIG)

message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")

find_package(Threads REQUIRED)

include_directories(
    ${SnowStar_SOURCE_DIR}/ext/antlr/cpp_runtime/runtime/src
    ${SnowStar_SOURCE_DIR}/ext/argh
    ${SnowStar_SOURCE_DIR}/lib/antlr
    ${SnowStar_SOURCE_DIR}/ext/tiny_process_library
    ${SnowStar_SOURCE_DIR}/ext/termcolor/include
    ${SnowStar_SOURCE_DIR}/include
    ${LLVM_INCLUDE_DIRS}
)

add_definitions(${LLVM_DEFINITIONS})

if (MSVC)
	file(
		GLOB_RECURSE SOURCE_FILES
		${SnowStar_SOURCE_DIR}/lib/antlr/*.cpp
		${Compiler_SOURCE_DIR}/*.cpp
		${SnowStar_SOURCE_DIR}/ext/tiny_process_library/process.cpp
		${SnowStar_SOURCE_DIR}/ext/tiny_process_library/process_win.cpp
	)
else()
	file(
		GLOB_RECURSE SOURCE_FILES
		${SnowStar_SOURCE_DIR}/lib/antlr/*.cpp
		${Compiler_SOURCE_DIR}/*.cpp
		${SnowStar_SOURCE_DIR}/ext/tiny_process_library/process.cpp
		${SnowStar_SOURCE_DIR}/ext/tiny_process_library/process_unix.cpp
	)
endif()

add_executable(
    ${PROJECT_NAME} ${SOURCE_FILES}
)

target_link_libraries (${PROJECT_NAME} ${CMAKE_THREAD_LIBS_INIT})
if (NOT MSVC)
	target_link_libraries(${PROJECT_NAME} stdc++fs)
endif()
target_link_libraries(${PROJECT_NAME} antlr4_shared)
if (MSVC)
	llvm_map_components_to_libnames(LLVM_LIBRARIES
	    support core irreader option target mc
	    x86asmparser          x86codegen          x86info          x86desc
	    amdgpuasmparser       amdgpucodegen       amdgpuinfo       amdgpudesc
	    armasmparser          armcodegen          arminfo          armdesc
	                          msp430codegen       msp430info       msp430desc
	                          xcorecodegen        xcoreinfo        xcoredesc
	    aarch64asmparser      aarch64codegen      aarch64info      aarch64desc
	    mipsasmparser         mipscodegen         mipsinfo         mipsdesc
	    systemzasmparser      systemzcodegen      systemzinfo      systemzdesc
	    hexagonasmparser      hexagoncodegen      hexagoninfo      hexagondesc
	    powerpcasmparser      powerpccodegen      powerpcinfo      powerpcdesc
	                          nvptxcodegen        nvptxinfo        nvptxdesc
	    lanaiasmparser        lanaicodegen        lanaiinfo        lanaidesc
	    sparcasmparser        sparccodegen        sparcinfo        sparcdesc
	    bpfasmparser          bpfcodegen          bpfinfo          bpfdesc
	)
	target_link_libraries(${PROJECT_NAME} ${LLVM_LIBRARIES})
else()
	target_link_libraries(${PROJECT_NAME} LLVM-7.0.0)
endif()

if(CMAKE_DL_LIBS)
    target_link_libraries(${PROJECT_NAME} ${CMAKE_DL_LIBS})
endif(CMAKE_DL_LIBS)

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)
set(CMAKE_BUILD_TYPE "Debug")
set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "ssc")

if (MSVC)
	if ("${CMAKE_BUILD_TYPE}" STREQUAL "Release")
    	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /D NOMINMAX /D NDEBUG")
    else()
    	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W3 /WX- /D NOMINMAX")
    endif()
endif (MSVC)

if (CMAKE_COMPILER_IS_GNUCC)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -L/usr/local/lib -Wl,-R/usr/local/lib")
    if ("${CMAKE_BUILD_TYPE}" STREQUAL "Release")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -march=native -DNDEBUG")
    else()
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ggdb -Wall -Wextra -W")
    endif()
endif()

message("Compile flags: ${CMAKE_CXX_FLAGS}")

add_custom_command(
    TARGET Compiler POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory "${SnowStar_SOURCE_DIR}/dist/" $<TARGET_FILE_DIR:Compiler>
)
