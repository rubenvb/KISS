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
  // declval
  // decay
  // common_type
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
