/**
 * Written in 2013-2015 by Ruben Van Boxem <vanboxem.ruben@gmail.com>
 *
 * This file is dual licensed under the MIT and the University of Illinois Open
 * Source Licenses. See LICENSE.TXT for details.
 *
 ********************************************************************************************/

/*
 * test/types/references.c++
 **/

#include <type_traits.h++>

#include "../test.h++"

using namespace kiss;

int main()
{
  // is_lvalue_reference
  test_unary_trait_cv<is_lvalue_reference, int&>();
  test_unary_trait_cv<is_lvalue_reference, Class&>();
  test_unary_trait_cv<is_lvalue_reference, int(&)(int)>();
  test_unary_trait_cv<is_lvalue_reference, int&&, false>(),
  test_unary_trait_cv<is_lvalue_reference, Class, false>();

  // is_rvalue_reference
  test_unary_trait_cv<is_rvalue_reference, int&&>();
  test_unary_trait_cv<is_rvalue_reference, Class&&>();
  test_unary_trait_cv<is_rvalue_reference, int(&&)(int)>();
  test_unary_trait_cv<is_rvalue_reference, int&, false>();
  test_unary_trait_cv<is_rvalue_reference, Class, false>();

  // add_lvalue_reference
  test_nested_type_trait<add_lvalue_reference, void, void>();
  test_nested_type_trait<add_lvalue_reference, int, int&>();
  test_nested_type_trait<add_lvalue_reference, int[3], int(&)[3]>();
  test_nested_type_trait<add_lvalue_reference, int&, int&>();
  test_nested_type_trait<add_lvalue_reference, const int&, const int&>();
  test_nested_type_trait<add_lvalue_reference, int*, int*&>();
  test_nested_type_trait<add_lvalue_reference, const int*, const int*&>();

  // add_rvalue_reference
  test_nested_type_trait<add_rvalue_reference, void, void>();
  test_nested_type_trait<add_rvalue_reference, int, int&&>();
  test_nested_type_trait<add_rvalue_reference, int[3], int(&&)[3]>();
  test_nested_type_trait<add_rvalue_reference, int&, int&>();
  test_nested_type_trait<add_rvalue_reference, const int&, const int&>();
  test_nested_type_trait<add_rvalue_reference, int*, int*&&>();
  test_nested_type_trait<add_rvalue_reference, const int*, const int*&&>();

  // remove_reference
  test_nested_type_trait<remove_reference, void, void>();
  test_nested_type_trait<remove_reference, int, int>();
  test_nested_type_trait<remove_reference, int[3], int[3]>();
  test_nested_type_trait<remove_reference, int*, int*>();
  test_nested_type_trait<remove_reference, const int*, const int*>();

  test_nested_type_trait<remove_reference, int&, int>();
  test_nested_type_trait<remove_reference, const int&, const int>();
  test_nested_type_trait<remove_reference, int(&)[3], int[3]>();
  test_nested_type_trait<remove_reference, int*&, int*>();
  test_nested_type_trait<remove_reference, const int*&, const int*>();

  test_nested_type_trait<remove_reference, int&&, int>();
  test_nested_type_trait<remove_reference, const int&&, const int>();
  test_nested_type_trait<remove_reference, int(&&)[3], int[3]>();
  test_nested_type_trait<remove_reference, int*&&, int*>();
  test_nested_type_trait<remove_reference, const int*&&, const int*>();
}
