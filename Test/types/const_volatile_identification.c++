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
