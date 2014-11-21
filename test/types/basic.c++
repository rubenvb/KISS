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
  * test/types/basic.c++
  **/

#include "types.h++"

using namespace kiss;

int main()
{
  // verify 8-bit unsigned char
  static_assert( (unsigned char)(-1) == 255, "unsigned char isn't 8 bits wide");

  // Verify type size
  static_assert(sizeof(int8) == 1,   "sizeof(int8) != 1 byte");
  static_assert(sizeof(int16) == 2,  "sizeof(int16 != 2 bytes");
  static_assert(sizeof(int32) == 4,  "sizeof(int32 != 4 bytes");
  static_assert(sizeof(char8) == 1,  "sizeof(char8 != 1 byte");
  static_assert(sizeof(char16) == 2, "sizeof(char16 != 2 bytes");
  static_assert(sizeof(char32) == 4, "sizeof(char32 != 4 bytes");
}
