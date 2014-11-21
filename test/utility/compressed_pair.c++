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
