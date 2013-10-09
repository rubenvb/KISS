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
set(CMAKE_CXX_FLAGS "-std=c++11 -pedantic-errors -Wextra -Wconversion -Wuninitialized -Winit-self -Wmissing-include-dirs -Wstrict-aliasing -Werror -Wno-constexpr-not-const ${CMAKE_CXX_FLAGS}")
endif()

# Library
file(GLOB library_source src/*.c++)
file(GLOB library_headers include/*.h++)
add_library(KISS ${library_headers} ${library_source})
set_target_properties(KISS PROPERTIES LINKER_LANGUAGE CXX)
include_directories(${KISS_SOURCE_DIR}/include)

# tests
enable_testing()
set(TEST_ROOT ${KISS_SOURCE_DIR}/test)
function(runtime_test test_dir test_name)
  add_executable(${test_name} EXCLUDE_FROM_ALL ${TEST_ROOT}/${test_dir}/${test_name}.c++ ${TEST_ROOT}/test.h++)
  set_target_properties(${test_name} PROPERTIES RUNTIME_OUTPUT_DIRECTORY test/${test_dir})
  add_test(remove/${test_dir}/${test_name} ${CMAKE_COMMAND} -E remove test/${test_dir}/${test_name}${CMAKE_EXECUTABLE_SUFFIX})
  add_test(build/${test_dir}/${test_name}' ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target ${test_name})
  add_test(test/${test_dir}/${test_name} test/${test_dir}/${test_name})
  set_property(TEST test/${test_dir}/${test_name} APPEND PROPERTY DEPENDS build/${test_dir}/${test_name})
endfunction()
function(compile_test test_dir test_name)
  add_library(${test_name} OBJECT EXCLUDE_FROM_ALL ${TEST_ROOT}/${test_dir}/${test_name}.c++ ${TEST_ROOT}/test.h++)
  set_target_properties(${test_name} PROPERTIES RUNTIME_OUTPUT_DIRECTORY test/${test_dir})
  add_test(${test_dir}/${test_name} ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target ${test_name})
endfunction()

compile_test(types basic)
compile_test(types references)
compile_test(types pointers)
compile_test(types utility)
compile_test(types const_volatile)
compile_test(types primary_categories)
compile_test(types composite_categories)
compile_test(types miscellaneous)
compile_test(types signedness)
compile_test(types memory)
compile_test(types construction_destruction_assignment_copy_move)
compile_test(types inheritance)
compile_test(types alignment)

runtime_test(utility compressed_pair)

runtime_test(utility tuple)

runtime_test(smart_pointers unique_ptr)
