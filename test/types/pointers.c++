/**
 * Written in 2013 by Ruben Van Boxem <vanboxem.ruben@gmail.com>
 *
 * To the extent possible under law, the author(s) have dedicated all copyright and related
 * and neighboring rights to this software to the public domain worldwide. This software is
 * distributed without any warranty.
 *
 * You should have received a copy of the CC0 Public Domain Dedication along with this software.
 * If not, see <http://creativecommons.org/publicdomain/zero/1.0/>.
 *
 ********************************************************************************************/

/*
 * test/types/pointers.c++
 **/

#include <types.h++>

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
