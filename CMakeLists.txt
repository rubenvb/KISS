cmake_minimum_required (VERSION 2.8)

project(KISS)

if(MSVC)
elseif(CMAKE_COMPILER_IS_GNUCXX)
set(CMAKE_CXX_FLAGS "-std=c++0x -Wall -Wextra -pedantic ${CMAKE_CXX_FLAGS}")
elseif("${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang")
set(CMAKE_CXX_FLAGS "-std=c++0x -Wall -Wextra -pedantic ${CMAKE_CXX_FLAGS}")
endif()

# Library
file(GLOB library_source src/*.cxx)
file(GLOB library_headers include/*.hxx)
add_library(KISS ${library_headers} ${library_source})
include_directories(${KISS_SOURCE_DIR}/include)

# test executable
add_executable(test_KISS Test/main.cxx)
