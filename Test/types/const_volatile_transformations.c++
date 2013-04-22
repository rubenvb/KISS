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

template<typename T>
void test_remove_const()
{
  static_assert(is_same<typename remove_const<T>::type, T>(), "");
  static_assert(is_same<typename remove_const<const T>::type, T>(), "");
  static_assert(is_same<typename remove_const<volatile T>::type, volatile T>(), "");
  static_assert(is_same<typename remove_const<const volatile T>::type, volatile T>(), "");
}
template<typename T>
void test_remove_volatile()
{

  static_assert(is_same<typename remove_volatile<T>::type, T>(), "");
  static_assert(is_same<typename remove_volatile<const T>::type, const T>(), "");
  static_assert(is_same<typename remove_volatile<volatile T>::type, T>(), "");
  static_assert(is_same<typename remove_volatile<const volatile T>::type, const T>(), "");
}
template<typename T>
void test_remove_cv()
{

  static_assert(is_same<typename remove_cv<T>::type, T>(), "");
  static_assert(is_same<typename remove_cv<const T>::type, T>(), "");
  static_assert(is_same<typename remove_cv<volatile T>::type, T>(), "");
  static_assert(is_same<typename remove_cv<const volatile T>::type, T>(), "");
}

template<typename T>
void test_add_const()
{
  static_assert(is_same<typename add_const<T>::type, const T>(), "");
  static_assert(is_same<typename add_const<const T>::type, const T>(), "");
  static_assert(is_same<typename add_const<volatile T>::type, const volatile T>(), "");
  static_assert(is_same<typename add_const<const volatile T>::type, const volatile T>(), "");
}
template<typename T>
void test_add_volatile()
{
  static_assert(is_same<typename add_volatile<T>::type, volatile T>(), "");
  static_assert(is_same<typename add_volatile<const T>::type, const volatile T>(), "");
  static_assert(is_same<typename add_volatile<volatile T>::type, volatile T>(), "");
  static_assert(is_same<typename add_volatile<const volatile T>::type, const volatile T>(), "");
}
template<typename T>
void test_add_cv()
{
  static_assert(is_same<typename add_cv<T>::type, const volatile T>(), "");
  static_assert(is_same<typename add_cv<const T>::type, const volatile T>(), "");
  static_assert(is_same<typename add_cv<volatile T>::type, const volatile T>(), "");
  static_assert(is_same<typename add_cv<const volatile T>::type, const volatile T>(), "");
}

int main()
{
  // remove_const
  test_remove_const<void>();
  test_remove_const<int>();
  test_remove_const<int[3]>();
  test_remove_const<int&>();
  test_remove_const<const int&>();
  test_remove_const<int*>();
  test_remove_const<const int*>();
  // remove_volatile
  // remove_cv
  test_remove_cv<void>();
  test_remove_cv<int>();
  test_remove_cv<int[3]>();
  test_remove_cv<int&>();
  test_remove_cv<const int&>();
  test_remove_cv<int*>();
  test_remove_cv<const int*>();

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
