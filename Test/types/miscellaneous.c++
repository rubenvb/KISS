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

using namespace kiss;

template<typename T, typename U>
void test_decay()
{
  static_assert(is_same<typename decay<T>::type, U>(), "");
}

template <class T, class U>
void test_is_same()
{
    static_assert(is_same<T, U>(), "");
    static_assert(!is_same<const T, U>(), "");
    static_assert(!is_same<T, const U>(), "");
    static_assert(is_same<const T, const U>(), "");
}
template <class T, class U>
void test_is_same_reference()
{
    static_assert(is_same<T, U>(), "");
    static_assert(is_same<const T, U>(), "");
    static_assert(is_same<T, const U>(), "");
    static_assert(is_same<const T, const U>(), "");
}
template <class T, class U>
void test_is_not_same()
{
    static_assert(!is_same<T, U>(), "");
}

class Class {};

int main()
{
  // conditional
  static_assert(is_same<conditional<true, char, int>, char>(), "");
  static_assert(is_same<conditional<false, char, int>, int>(), "");

  // declval
  // decay
  test_decay<void, void>();
  test_decay<int, int>();
  test_decay<const volatile int, int>();
  test_decay<int*, int*>();
  test_decay<int[3], int*>();
  test_decay<const int[3], const int*>();
  test_decay<void(), void (*)()>();
  // common_type
  static_assert(is_same<common_type<int>::type, int>(), "");
  static_assert(is_same<common_type<char>::type, char>(), "");

  static_assert(is_same<common_type<double, char>::type, double>(), "");
  static_assert(is_same<common_type<short, char>::type, int>(), "");

  static_assert(is_same<common_type<double, char, long long>::type, double>(), "");
  static_assert(is_same<common_type<unsigned, char, long long>::type, long long>(), "");

  // result_of

  // is_same
  test_is_same<int, int>();
  test_is_same<void, void>();
  test_is_same<Class, Class>();
  test_is_same<int*, int*>();
  test_is_same_reference<int&, int&>();

  test_is_not_same<int, void>();
  test_is_not_same<void, Class>();
  test_is_not_same<Class, int*>();
  test_is_not_same<int*, int&>();
  test_is_not_same<int&, int>();

}
