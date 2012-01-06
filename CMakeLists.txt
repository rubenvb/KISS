cmake_minimum_required (VERSION 2.6)

project(KISS)

if(MSVC)
elseif(CMAKE_COMPILER_IS_GNUCXX)
set(CMAKE_CXX_FLAGS "-std=c++0x ${CMAKE_CXX_FLAGS}")
endif()

# Library
file(GLOB library_source src/*.cxx)
file(GLOB library_headers include/*.hxx)
add_library(KISS ${library_headers} ${library_source})
include_directories(${Nectar_SOURCE_DIR}/include)

# test executable
add_executable(test_KISS Test/main.cxx)