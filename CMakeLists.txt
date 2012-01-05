cmake_minimum_required (VERSION 2.6)

project(Nectar)

if(MSVC)
elseif(CMAKE_COMPILER_IS_GNUCXX)
set(CMAKE_CXX_FLAGS "-nostdinc++")
endif()

# Library
file(GLOB library_source src/*.cxx)
file(GLOB library_headers include/*.hxx)
add_library(Nectar ${library_headers} ${library_source})

# test executable
add_executable(test_nectar Test/main.cxx)