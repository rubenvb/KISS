/**
 * This file is dual licensed under the MIT and the University of Illinois Open
 * Source Licenses. See LICENSE.TXT for details.
 *
 ********************************************************************************************/

 /*
  * types/boolean_traits.c++
  *  Boolean traits tests.
  */

#include <types.h++>

class Class {};

int main()
{
  // is_reference
  static_assert(!kiss::is_reference<Class>(),   "Class recognized as reference");
  static_assert( kiss::is_reference<Class&>(),  "Class& recognized as reference");
  static_assert( kiss::is_reference<Class&&>(), "Class&& not recognized as reference");
  static_assert(!kiss::is_reference<Class*>(),  "Class* recognized as reference");
  static_assert( kiss::is_reference<Class*&>(), "Class*& recognized as reference");
  // is_arithmetic
  // is_fundamental
  // is_member_pointer
  // is_scalar
  // is_object
  // is_compound
}
