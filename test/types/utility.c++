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
 * test/types/utility.c++
 **/

#include <types.h++>

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
