/**
 * This file is dual licensed under the MIT and the University of Illinois Open
 * Source Licenses. See LICENSE.TXT for details.
 *
 ********************************************************************************************/

 /*
  * types/basic_types.c++
  *  Basic types tests.
  */

#include <types.h++>

int main()
{
  // verify 8-bit unsigned char
  static_assert( (unsigned char)(-1) == 255, "unsigned char isn't 8 bits wide");
  // Verify type size
  static_assert(sizeof(kiss::int8) == 1,   "sizeof(kiss::int8) != 1 byte");
  static_assert(sizeof(kiss::int16) == 2,  "sizeof(kiss::int16 != 2 bytes");
  static_assert(sizeof(kiss::int32) == 4,  "sizeof(kiss::int32 != 4 bytes");
  static_assert(sizeof(kiss::char8) == 1,  "sizeof(kiss::char8 != 1 byte");
  static_assert(sizeof(kiss::char16) == 2, "sizeof(kiss::char16 != 2 bytes");
  static_assert(sizeof(kiss::char32) == 4, "sizeof(kiss::char32 != 4 bytes");
}
