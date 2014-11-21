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
 * test/types/alignment.c++
 **/

#include "types.h++"

#include "../test.h++"

using namespace kiss;

int main()
{
  // alignment_of
  test_unary_trait_cv<alignment_of, int&, 4>();
  test_unary_trait_cv<alignment_of, Class, 1>();
  test_unary_trait_cv<alignment_of, int*, sizeof(long) == 4 ? 4 : 8>();
  test_unary_trait_cv<alignment_of, const int*, sizeof(long) == 4 ? 4 : 8>();
  test_unary_trait_cv<alignment_of, char[3], 1>();
  test_unary_trait_cv<alignment_of, int, 4>();
  test_unary_trait_cv<alignment_of, double, 8>();
  test_unary_trait_cv<alignment_of, bool, 1>();
  test_unary_trait_cv<alignment_of, unsigned, 4>();

  // aligned_storage
  using T1 = aligned_storage<10, 1>::type;
 test_unary_trait_cv<alignment_of, T1, 1>();
 static_assert(sizeof(T1) == 10, "");

  using T2 = aligned_storage<10, 2>::type;
  test_unary_trait_cv<alignment_of, T2, 2>();
  static_assert(sizeof(T2) == 10, "");

  using T3 = aligned_storage<10, 4>::type;
  test_unary_trait_cv<alignment_of, T3, 4>();
  static_assert(sizeof(T3) == 12, "");

  using T4 = aligned_storage<10, 8>::type;
  test_unary_trait_cv<alignment_of, T4, 8>();
  static_assert(sizeof(T4) == 16, "");

  using T5 = aligned_storage<10, 16>::type;
  test_unary_trait_cv<alignment_of, T5, 16>();
  static_assert(sizeof(T5) == 16, "");

  using T6 = aligned_storage<10, 32>::type;
  test_unary_trait_cv<alignment_of, T6, 32>();
  static_assert(sizeof(T6) == 32, "");

  using T7 = aligned_storage<20, 32>::type;
  test_unary_trait_cv<alignment_of, T7, 32>();
  static_assert(sizeof(T7) == 32, "");

  using T8 = aligned_storage<40, 32>::type;
  test_unary_trait_cv<alignment_of, T8, 32>();
  static_assert(sizeof(T8) == 64, "");

  using T9 = aligned_storage<12, 16>::type;
  test_unary_trait_cv<alignment_of, T9, 16>();
  static_assert(sizeof(T9) == 16, "");

//TODO default argument and tests need checking
  /*using T10 = aligned_storage<1>::type;
  test_unary_trait_cv<alignment_of, T10, 1>();
  static_assert(sizeof(T10) == 1, "");

  using T11 = aligned_storage<2>::type;
  test_unary_trait_cv<alignment_of, T11, 2>();
  static_assert(sizeof(T11) == 2, "");

  using T12 = aligned_storage<3>::type;
  test_unary_trait_cv<alignment_of, T12, 2>();
  static_assert(sizeof(T12) == 4, "");

  using T13 = aligned_storage<4>::type;
  test_unary_trait_cv<alignment_of, T13, 4>();
  static_assert(sizeof(T13) == 4, "");

  using T14 = aligned_storage<5>::type;
  test_unary_trait_cv<alignment_of, T14, 4>();
  static_assert(sizeof(T14) == 8, "");

  using T15 = aligned_storage<7>::type;
  test_unary_trait_cv<alignment_of, T15, 4>();
  static_assert(sizeof(T15) == 8, "");

  using T16 = aligned_storage<8>::type;
  test_unary_trait_cv<alignment_of, T16, 8>();
  static_assert(sizeof(T16) == 8, "");

  using T17 = aligned_storage<9>::type;
  test_unary_trait_cv<alignment_of, T17, 8>();
  static_assert(sizeof(T17) == 16, "");

  using T18 = aligned_storage<15>::type;
  test_unary_trait_cv<alignment_of, T18, 8>();
  static_assert(sizeof(T18) == 16, "");

  using T19 = aligned_storage<16>::type;
  test_unary_trait_cv<alignment_of, T19, 16>();
  static_assert(sizeof(T19) == 16, "");

  using T20 = aligned_storage<17>::type;
  test_unary_trait_cv<alignment_of, T20, 16>();
  static_assert(sizeof(T20) == 32, "");

  using T21 = aligned_storage<10>::type;
  test_unary_trait_cv<alignment_of, T21, 8>();
  static_assert(sizeof(T21) == 16, "");*/
}
