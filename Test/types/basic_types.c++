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
  * types/basic_types.c++
  *  Basic types tests.
  */

#include <types.h++>

int main()
{
  // Verify type size
  static_assert(sizeof(kiss::int8) == 1,  "sizeof(kiss::int8) != 1 byte");
  static_assert(sizeof(kiss::int16) == 2, "sizeof(kiss::int16 != 2 bytes");
  static_assert(sizeof(kiss::int32) == 4, "sizeof(kiss::int32 != 4 bytes");
  static_assert(sizeof(kiss::char8) == 1, "sizeof(kiss::char8 != 1 byte");
  static_assert(sizeof(kiss::char16) == 2, "sizeof(kiss::char16 != 2 bytes");
  static_assert(sizeof(kiss::char32) == 4, "sizeof(kiss::char32 != 4 bytes");
}
