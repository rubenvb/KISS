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
 * test/utility/aligned_union.c++
 **/

#include "aligned_union.h++"

#include "../test.h++"

using namespace kiss;

using char_union = aligned_union<10, char>::type;
using short_union = aligned_union<10, short>::type;
using int_union = aligned_union<10, int>::type;
using double_union = aligned_union<10, double >::type;
using short_char_union = aligned_union<10, short, char>::type;
using char_short_union = aligned_union<10, char, short>::type;
using int_char_short_union = aligned_union<2, int, char, short>::type;
using char_int_short_union = aligned_union<2, char, int, short >::type;
using char_short_int_union = aligned_union<2, char, short, int >::type;

int main()
{
  test_unary_trait<alignment_of, char_union, alignment_of<char>::value>();
  static_assert(sizeof(char_union) == 10, "");

  test_unary_trait<alignment_of, short_union, alignment_of<short>::value>();
  static_assert(sizeof(short_union) == 10, "");

  test_unary_trait<alignment_of, int_union, alignment_of<int>::value>();
  static_assert(sizeof(int_union) == 12, ""); // alignment = 4, first multiple greater than 10 is 12

  test_unary_trait<alignment_of, double_union, alignment_of<double>::value>();
  static_assert(sizeof(double_union) == 16, "");

  test_unary_trait<alignment_of, short_char_union, alignment_of<short>::value>();
  static_assert(sizeof(short_char_union) == 10, "");

  test_unary_trait<alignment_of, char_short_union, alignment_of<short>::value>();
  static_assert(sizeof(char_short_union) == 10, "");

  test_unary_trait<alignment_of, int_char_short_union, alignment_of<int>::value>();
  static_assert(sizeof(int_char_short_union) == 4, "");

  test_unary_trait<alignment_of, char_int_short_union, alignment_of<int>::value>();
  static_assert(sizeof(char_int_short_union) == 4, "");

  test_unary_trait<alignment_of, char_short_int_union, alignment_of<int>::value>();
  static_assert(sizeof(char_short_int_union) == 4, "");
}
