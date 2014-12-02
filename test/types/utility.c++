/**
 * Written in 2013-2015 by Ruben Van Boxem <vanboxem.ruben@gmail.com>
 *
 * This file is dual licensed under the MIT and the University of Illinois Open
 * Source Licenses. See LICENSE.TXT for details.
 *
 ********************************************************************************************/

/*
 * test/types/utility.c++
 **/

#include <type_traits.h++>

#include "../test.h++"

using namespace kiss;

int main()
{
  // conditional
  static_assert(is_same<conditional<true, char, int>, char>(), "");
  static_assert(is_same<conditional<false, char, int>, int>(), "");

  // declval
  static_assert(is_same<decltype(declval<Class>()), Class&&>::value, "");
  static_assert(!is_same<decltype(declval<Class>()), Class>::value, "");

//TODO enable_if

//TODO forward

  // is_same
  test_binary_trait<is_same, int, int>();
  test_binary_trait<is_same, void, void>();
  test_binary_trait<is_same, Class, Class>();
  test_binary_trait<is_same, int*, int*>();
  test_binary_trait<is_same, int&, int&>();

  test_binary_trait<is_same, int, void, false>();
  test_binary_trait<is_same, void, Class, false>();
  test_binary_trait<is_same, Class, int*, false>();
  test_binary_trait<is_same, int*, int&, false>();
  test_binary_trait<is_same, int&, int, false>();
}
