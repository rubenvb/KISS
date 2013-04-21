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

template <class T, class U>
void test_is_base_of()
{
    static_assert(is_base_of<T, U>(), "");
    static_assert(is_base_of<const T, U>(), "");
    static_assert(is_base_of<T, const U>(), "");
    static_assert(is_base_of<const T, const U>(), "");
}
template <class T, class U>
void test_is_not_base_of()
{
    static_assert(!is_base_of<T, U>(), "");
}

struct Struct {};
struct Child : Struct {};
struct OtherChild : Struct {};
struct PrivateChild : private Child, private OtherChild {};

int main()
{
  // underlying_type
  // has_virtual_destructor
  // is_base_of
  test_is_base_of<Struct, PrivateChild>();
  test_is_base_of<Child, PrivateChild>();
  test_is_base_of<OtherChild, PrivateChild>();
  test_is_base_of<Struct, Child>();
  test_is_base_of<Struct, OtherChild>();
  test_is_base_of<Struct, Struct>();

  test_is_not_base_of<PrivateChild, Child>();
  test_is_not_base_of<Struct&, PrivateChild&>();
  test_is_not_base_of<Struct[3], PrivateChild[3]>();
  test_is_not_base_of<int, int>();
  // is_empty
  // is_polymorphic
  // is_abstract
}
