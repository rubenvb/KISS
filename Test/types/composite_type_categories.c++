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
