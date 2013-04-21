/**
 * This file is dual licensed under the MIT and the University of Illinois Open
 * Source Licenses. See LICENSE.TXT for details.
 *
 ********************************************************************************************/

 /*
  * test/types/signedness.c++
  *  Signedness traits tests.
  */

#include <types.h++>

using namespace kiss;

template<typename Unsigned, typename Signed>
void test_make_signed()
{
  static_assert(is_same<typename make_signed<Unsigned>::type, Signed>(), "");
}
template<typename Unsigned, typename Signed>
void test_make_unsigned()
{
  static_assert(is_same<typename make_unsigned<Signed>::type, Unsigned>(), "");
}
template<typename T>
void test_is_signed()
{
  static_assert(is_signed<T>(), "");
  static_assert(is_signed<const T>(), "");
  static_assert(is_signed<volatile T>(), "");
  static_assert(is_signed<const volatile T>(), "");
}
template<typename T>
void test_is_not_signed()
{
  static_assert(!is_signed<T>(), "");
  static_assert(!is_signed<const T>(), "");
  static_assert(!is_signed<volatile T>(), "");
  static_assert(!is_signed<const volatile T>(), "");
}

class Class {};

int main()
{
  // make_signed
  test_make_signed<void, void>();
  test_make_signed<int&, int&>();
  test_make_signed<int&&, int&&>();
  test_make_signed<int*, int*>();
  test_make_signed<signed char, signed char>();
  test_make_signed<unsigned char, signed char>();
  test_make_signed<char, signed char>();
  test_make_signed<short, signed short>();
  test_make_signed<unsigned short, signed short>();
  test_make_signed<int, signed int>();
  test_make_signed<unsigned int, signed int>();
  test_make_signed<long, signed long>();
  test_make_signed<unsigned long, signed long>();
  test_make_signed<long long, signed long long>();
  test_make_signed<unsigned long long, signed long long>();
  // is_signed
  test_is_not_signed<void>();
  test_is_not_signed<int&>();
  test_is_not_signed<int&&>();
  test_is_not_signed<Class>();
  test_is_not_signed<int*>();
  test_is_not_signed<const int*>();
  test_is_not_signed<char[3]>();
  test_is_not_signed<char[]>();
  test_is_not_signed<bool>();
  test_is_not_signed<unsigned>();

  test_is_signed<int>();
  test_is_signed<double>();
}
