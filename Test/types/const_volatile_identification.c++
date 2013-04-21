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

int main()
{
  // is_const
  static_assert(!kiss::is_const<int>(),                "int recognized as const");
  static_assert( kiss::is_const<const int>(),          "const int not recognized as const");
  static_assert(!kiss::is_const<volatile int>(),       "volatile int recognized as const");
  static_assert( kiss::is_const<const volatile int>(), "const volatile int not recognized as const");
  static_assert(!kiss::is_const<const int*>(),         "const int* not recognized as const");
  static_assert( kiss::is_const<int* const>(),         "int* const not recognized as const");
  static_assert( kiss::is_const<const int* const>(),   "const int* const not recognized as const");
  static_assert(!kiss::is_const<const int&>(),         "const int& recognized as const");
  static_assert(!kiss::is_const<const int&&>(),        "const int&& recognized as const");
  //is_volatile
  static_assert(!kiss::is_volatile<int>(),                    "int recognized as volatile");
  static_assert(!kiss::is_volatile<const int>(),              "const int recognized as volatile");
  static_assert( kiss::is_volatile<volatile int>(),           "volatile int not recognized as volatile");
  static_assert( kiss::is_volatile<const volatile int>(),     "const volatile int not recognized as volatile");
  static_assert(!kiss::is_volatile<volatile int*>(),          "volatile int* not recognized as volatile");
  static_assert( kiss::is_volatile<int* volatile>(),          "int* const not recognized as volatile");
  static_assert( kiss::is_volatile<volatile int* volatile>(), "volatile int* const not recognized as volatile");
  static_assert(!kiss::is_volatile<volatile int&>(),          "volatile int& recognized as volatile");
  static_assert(!kiss::is_volatile<volatile int&&>(),         "volatile int&& recognized as volatile");
}
