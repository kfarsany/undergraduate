cmake_minimum_required(VERSION 3.12.3.0)
project(CMAKE_TRY_COMPILE C)
set(CMAKE_VERBOSE_MAKEFILE 1)
set(CMAKE_C_FLAGS "")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${COMPILE_DEFINITIONS}")
set(CMAKE_EXE_LINKER_FLAGS "-Wl,--enable-auto-import")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${EXE_LINKER_FLAGS}")
include_directories(${INCLUDE_DIRECTORIES})
set(CMAKE_SUPPRESS_REGENERATION 1)
link_directories(${LINK_DIRECTORIES})
add_definitions(-std=c11)
cmake_policy(SET CMP0065 OLD)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "/cygdrive/c/Users/Kian/CLionProjects/program2/cmake-build-debug/CMakeFiles/CMakeTmp")
add_executable(cmTC_03ee2 "/cygdrive/c/Users/Kian/CLionProjects/program2/cmake-build-debug/CMakeFiles/feature_tests.c")
target_link_libraries(cmTC_03ee2  "" )
