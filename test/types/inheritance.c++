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
 * test/types/inheritance.c++
 **/

#include "types.h++"

#include "../test.h++"

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
//TODO underlying_type
//TODO has_virtual_destructor
//TODO is_base_of
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
//TODO is_empty
//TODO is_polymorphic
//TODO is_abstract
}
