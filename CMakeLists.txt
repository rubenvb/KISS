#
# KISS - A simple and complete C++ library
#
# Written in 2013 by Ruben Van Boxem <vanboxem.ruben@gmail.com>
#
# To the extent possible under law, the author(s) have dedicated all copyright and related
# and neighboring rights to this software to the public domain worldwide. This software is
# distributed without any warranty.
#
# You should have received a copy of the CC0 Public Domain Dedication along with this software.
# If not, see <http://creativecommons.org/publicdomain/zero/1.0/>.
#

cmake_minimum_required (VERSION 2.8)

project(KISS)

if(CMAKE_COMPILER_IS_GNUCXX)
set(CMAKE_CXX_FLAGS "-std=c++11 -pedantic-errors -Wextra -Wconversion -Wuninitialized -Winit-self -Wmissing-include-dirs -Wstrict-aliasing -Werror ${CMAKE_CXX_FLAGS}")
elseif("${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang")
set(CMAKE_CXX_FLAGS "-std=c++11 -pedantic-errors -Wextra -Wconversion -Wuninitialized -Winit-self -Wmissing-include-dirs -Wstrict-aliasing -Werror ${CMAKE_CXX_FLAGS}")
endif()

# Library
file(GLOB library_source src/*.c++)
file(GLOB library_headers include/*.h++)
add_library(KISS ${library_headers} ${library_source})
set_target_properties(KISS PROPERTIES LINKER_LANGUAGE CXX)
include_directories(${KISS_SOURCE_DIR}/include)

# test executable
add_executable(test_KISS Test/main.cxx)

# tests
enable_testing()
set(TEST_ROOT "${KISS_SOURCE_DIR}/test")
function(test test_dir test_name)
  add_executable(${test_name} ${TEST_ROOT}/${test_dir}/${test_name}.c++)
  add_test(${test_dir}/${test_name} ${test_name})
endfunction()

test(types basic_types)
test(types transforming_traits)
test(types boolean_traits)
test(types value_traits)

#add_test("types/compiler_traits" ${CMAKE_CXX_COMPILER} "${TEST_DIR}/types/compiler_traits.cxx" -I${KISS_SOURCE_DIR}/include -std=c++11 -ocompiler_traits)
#add_test("types/cv_traits" ${CMAKE_CXX_COMPILER} "${TEST_DIR}/types/cv_traits.cxx" -I${KISS_SOURCE_DIR}/include -std=c++11 -ocv_traits)
#add_test("types/misc_traits" ${CMAKE_CXX_COMPILER} "${TEST_DIR}/types/misc_traits.cxx" -I${KISS_SOURCE_DIR}/include -std=c++11 -omisc_traits)
#add_test("types/numerical_traits" ${CMAKE_CXX_COMPILER} "${TEST_DIR}/types/numerical_traits.cxx" -I${KISS_SOURCE_DIR}/include -std=c++11 -onumerical_traits)
