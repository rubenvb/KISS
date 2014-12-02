/**
 * Written in 2013-2015 by Ruben Van Boxem <vanboxem.ruben@gmail.com>
 *
 * This file is dual licensed under the MIT and the University of Illinois Open
 * Source Licenses. See LICENSE.TXT for details.
 *
 ********************************************************************************************/

/*
 * test/types/pointers.c++
 **/

#include <type_traits.h++>

#include "../test.h++"

using namespace kiss;

int main()
{
  // add_pointer
  test_nested_type_trait<add_pointer, void, void*>();
  test_nested_type_trait<add_pointer, int, int*>();
  test_nested_type_trait<add_pointer, int[3], int(*)[3]>();
  test_nested_type_trait<add_pointer, int&, int*>();
  test_nested_type_trait<add_pointer, const int&, const int*>();
  test_nested_type_trait<add_pointer, int*, int**>();
  test_nested_type_trait<add_pointer, const int*, const int**>();

  // remove_pointer
  test_nested_type_trait<remove_pointer, void, void>();
  test_nested_type_trait<remove_pointer, int, int>();
  test_nested_type_trait<remove_pointer, int[3], int[3]>();
  test_nested_type_trait<remove_pointer, int*, int>();
  test_nested_type_trait<remove_pointer, const int*, const int>();
  test_nested_type_trait<remove_pointer, int**, int*>();
  test_nested_type_trait<remove_pointer, int** const, int*>();
  test_nested_type_trait<remove_pointer, int*const * , int* const>();
  test_nested_type_trait<remove_pointer, const int** , const int*>();

  test_nested_type_trait<remove_pointer, int&, int&>();
  test_nested_type_trait<remove_pointer, const int&, const int&>();
  test_nested_type_trait<remove_pointer, int(&)[3], int(&)[3]>();
  test_nested_type_trait<remove_pointer, int(*)[3], int[3]>();
  test_nested_type_trait<remove_pointer, int*&, int*&>();
  test_nested_type_trait<remove_pointer, const int*&, const int*&>();
}
