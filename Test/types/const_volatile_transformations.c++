/**
 * This file is dual licensed under the MIT and the University of Illinois Open
 * Source Licenses. See LICENSE.TXT for details.
 *
 ********************************************************************************************/

 /*
  * types/transforming_traits.c++
  *  Transforming traits tests.
  */

#include <types.h++>

using namespace kiss;

template <class T>
void test_add_const()
{
  static_assert(is_same<typename add_const<T>::type, const U>(), "");
  static_assert(is_same<typename add_const<const T>::type, const U>(), "");
  static_assert(is_same<typename add_const<volatile T>::type, const volatile U>(), "");
  static_assert(is_same<typename add_const<const volatile T>::type, const volatile U>(), "");
}
template <class T>
void test_add_volatile()
{
  static_assert(is_same<typename add_volatile<T>::type, volatile U>(), "");
  static_assert(is_same<typename add_volatile<const T>::type, const volatile U>(), "");
  static_assert(is_same<typename add_volatile<volatile T>::type, volatile U>(), "");
  static_assert(is_same<typename add_volatile<const volatile T>::type, const volatile U>(), "");
}
template <class T>
void test_add_cv()
{
  static_assert(is_same<typename add_cv<T>::type, const volatile U>(), "");
  static_assert(is_same<typename add_cv<const T>::type, const volatile U>(), "");
  static_assert(is_same<typename add_cv<volatile T>::type, const volatile U>(), "");
  static_assert(is_same<typename add_cv<const volatile T>::type, const volatile U>(), "");
}

int main()
{
  // remove_const
  // remove_volatile
  // remove_cv

  // add_const
  test_add_const<void>();
  test_add_const<int>();
  test_add_const<int[3]>();
  test_add_const<int&>();
  test_add_const<const int&>();
  test_add_const<int*>();
  test_add_const<const int*>();
  // add_volatile
  test_add_volatile<void>();
  test_add_volatile<int>();
  test_add_volatile<int[3]>();
  test_add_volatile<int&>();
  test_add_volatile<const int&>();
  test_add_volatile<int*>();
  test_add_volatile<const int*>();
  // add_cv
  test_add_cv<void>();
  test_add_cv<int>();
  test_add_cv<int[3]>();
  test_add_cv<int&>();
  test_add_cv<const int&>();
  test_add_cv<int*>();
  test_add_cv<const int*>();
}
