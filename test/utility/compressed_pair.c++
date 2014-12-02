/**
 * Written in 2013-2015 by Ruben Van Boxem <vanboxem.ruben@gmail.com>
 *
 * This file is dual licensed under the MIT and the University of Illinois Open
 * Source Licenses. See LICENSE.TXT for details.
 *
 ********************************************************************************************/

/*
 * test/utility/compressed_pair.c++
 **/

#include "compressed_pair.h++"

using namespace kiss;

struct empty {};

int main()
{
  // check compressedness in case of empty types
  static_assert(sizeof(pair<empty, char>) == 1, "");
  static_assert(sizeof(pair<empty, empty>) == 1, "");
  static_assert(sizeof(pair<char, empty>) == 1, "");

  using pair1 = pair<int, short>;
  using pair2 = pair<double, long>;
  constexpr pair1 p1(3, 4);
  static_assert(p1.first == 3, "");
  static_assert(p1.second == 4, "");
  constexpr pair2 p2(3, 4);
  static_assert(p2.first == 3, "");
  static_assert(p2.second == 4, "");

  //static_assert(false, "more tests needed");
}
