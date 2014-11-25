/**
 * Written in 2013-2015 by Ruben Van Boxem <vanboxem.ruben@gmail.com>
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
 * test/types/memory.c++
 **/

#include "types.h++"
//#include "pair.h++"

#include "../test.h++"

using namespace kiss;

int main()
{
  // is_literal_type
  test_unary_trait_cv<is_literal_type, int>();
  test_unary_trait_cv<is_literal_type, int&>();
  test_unary_trait_cv<is_literal_type, EmptyClass>();
  test_unary_trait_cv<is_literal_type, Class, false>();

  // is_pod
  test_unary_trait_cv<is_pod, void, false>();
  test_unary_trait_cv<is_pod, int&, false>();
  test_unary_trait_cv<is_pod, Class, false>();

  test_unary_trait_cv<is_pod, int>();
  test_unary_trait_cv<is_pod, double>();
  test_unary_trait_cv<is_pod, int*>();
  test_unary_trait_cv<is_pod, const int*>();
  test_unary_trait_cv<is_pod, char[3]>();
  test_unary_trait_cv<is_pod, char[3]>();

  // is_trivial
  test_unary_trait<is_trivial, int>();
  test_unary_trait<is_trivial, int&, false>();
  test_unary_trait<is_trivial, volatile int&, false>();
  test_unary_trait<is_trivial, EmptyClass>();
  test_unary_trait<is_trivial, Class, false>();

  // is_trivially_copyable
  /*
  test_unary_trait_cv<is_trivially_copyable, int>();
  test_unary_trait_cv<is_trivially_copyable, const int>();
  test_unary_trait_cv<is_trivially_copyable, int&, false>();
  test_unary_trait_cv<is_trivially_copyable, NotEmptyClass>();
  test_unary_trait_cv<is_trivially_copyable, const NotEmptyClass>();
  test_unary_trait_cv<is_trivially_copyable, const NotEmptyClass&, false>();
  test_unary_trait_cv<is_trivially_copyable, VirtuallyDestructibleClass, false>();
  test_unary_trait_cv<is_trivially_copyable, TriviallyCopyableClass>();
  */
  // is_standard_layout
  test_unary_trait_cv<is_standard_layout, int>();
  test_unary_trait_cv<is_standard_layout, int[3]>();
  test_unary_trait_cv<is_standard_layout, int&, false>();
  test_unary_trait_cv<is_standard_layout, volatile int&, false>();
  //test_unary_trait_cv<is_standard_layout, pair<int, double>>();
}
