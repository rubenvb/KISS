cmake_minimum_required (VERSION 2.8)

project(KISS)

if(MSVC)
set(CMAKE_CXX_FLAGS "/Oi ${CMAKE_CXX_FLAGS}")
elseif(CMAKE_COMPILER_IS_GNUCXX)
set(CMAKE_CXX_FLAGS "-std=c++11 -Wall -Wextra -pedantic ${CMAKE_CXX_FLAGS}")
elseif("${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang")
set(CMAKE_CXX_FLAGS "-std=c++11 -Wall -Wextra -pedantic ${CMAKE_CXX_FLAGS}")
endif()

# Library
file(GLOB library_source src/*.cxx)
file(GLOB library_headers include/*.hxx)
add_library(KISS ${library_headers} ${library_source})
include_directories(${KISS_SOURCE_DIR}/include)

# test executable
add_executable(test_KISS Test/main.cxx)

# tests
enable_testing()
set(TEST_DIR "${KISS_SOURCE_DIR}/Test")
add_test("types/cv_traits" ${CMAKE_CXX_COMPILER} "${TEST_DIR}/types/cv_traits.cxx" -I${KISS_SOURCE_DIR}/include -std=c++11 -ocv_traits)
add_test("types/misc_traits" ${CMAKE_CXX_COMPILER} "${TEST_DIR}/types/misc_traits.cxx" -I${KISS_SOURCE_DIR}/include -std=c++11 -omisc_traits)
add_test("types/numerical_traits" ${CMAKE_CXX_COMPILER} "${TEST_DIR}/types/numerical_traits.cxx" -I${KISS_SOURCE_DIR}/include -std=c++11 -onumerical_traits)
