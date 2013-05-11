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
 * test/types/const_volatile.c++.
 **/

#include <types.h++>

#include "../test.h++"

using namespace kiss;

//TODO get rid of these test_* functions in exchange for something more general in ../test.h++
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
  // is_const
  test_unary_trait<is_const, int, false>();
  test_unary_trait<is_const, const int>();
  test_unary_trait<is_const, volatile int, false>();
  test_unary_trait<is_const, const volatile int>();
  test_unary_trait<is_const, const int*, false>();
  test_unary_trait<is_const, int* const>();
  test_unary_trait<is_const, const int* const>();
  test_unary_trait<is_const, const int&, false>();
  test_unary_trait<is_const, const int&&, false>();

  //is_volatile
  test_unary_trait<is_volatile, int, false>();
  test_unary_trait<is_volatile, const int, false>();
  test_unary_trait<is_volatile, volatile int>();
  test_unary_trait<is_volatile, const volatile int>();
  test_unary_trait<is_volatile, volatile int*, false>();
  test_unary_trait<is_volatile, int* volatile>();
  test_unary_trait<is_volatile, volatile int* volatile>();
  test_unary_trait<is_volatile, volatile int&, false>();
  test_unary_trait<is_volatile, volatile int&&, false>();

  // remove_const
  test_remove_const<void>();
  test_remove_const<int>();
  test_remove_const<int[3]>();
  test_remove_const<int&>();
  test_remove_const<const int&>();
  test_remove_const<int*>();
  test_remove_const<const int*>();

  // remove_volatile
  test_remove_volatile<void>();
  test_remove_volatile<int>();
  test_remove_volatile<int[3]>();
  test_remove_volatile<int&>();
  test_remove_volatile<const int&>();
  test_remove_volatile<int*>();
  test_remove_volatile<volatile int*>();

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
