/**
 * Written in 2013-2015 by Ruben Van Boxem <vanboxem.ruben@gmail.com>
 *
 * This file is dual licensed under the MIT and the University of Illinois Open
 * Source Licenses. See LICENSE.TXT for details.
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
