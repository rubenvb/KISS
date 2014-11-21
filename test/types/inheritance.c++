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

int main()
{
  // underlying_type
  enum E : int {};
  enum F : unsigned {};
  enum G : char {};

  test_nested_type_trait_cv<underlying_type, E, int>();
  test_nested_type_trait_cv<underlying_type, F, unsigned>();
  test_nested_type_trait_cv<underlying_type, G, char>();

  // has_virtual_destructor
  test_unary_trait<has_virtual_destructor, void, false>();
  test_unary_trait<has_virtual_destructor, Class, false>();
  test_unary_trait<has_virtual_destructor, int&, false>();
  test_unary_trait<has_virtual_destructor, Union, false>();
  test_unary_trait<has_virtual_destructor, EmptyClass, false>();
  test_unary_trait<has_virtual_destructor, int, false>();
  test_unary_trait<has_virtual_destructor, double, false>();
  test_unary_trait<has_virtual_destructor, int*, false>();
  test_unary_trait<has_virtual_destructor, const int*, false>();
  test_unary_trait<has_virtual_destructor, char[3], false>();
  test_unary_trait<has_virtual_destructor, char[3], false>();
  test_unary_trait<has_virtual_destructor, ZeroBit, false>();

  test_unary_trait<has_virtual_destructor, AbstractClass>();
  test_unary_trait<has_virtual_destructor, NotEmptyClass>();

  // is_base_of
  test_binary_trait_cv<is_base_of, Class, PrivateChild>();
  test_binary_trait_cv<is_base_of, Child, PrivateChild>();
  test_binary_trait_cv<is_base_of, Class, Child>();
  test_binary_trait_cv<is_base_of, Class, OtherChild>();
  test_binary_trait_cv<is_base_of, Class, Class>();

  test_binary_trait_cv<is_base_of, OtherChild, PrivateChild, false>();
  test_binary_trait_cv<is_base_of, PrivateChild, Child, false>();
  test_binary_trait_cv<is_base_of, Class&, PrivateChild&, false>();
  test_binary_trait_cv<is_base_of, Class[3], PrivateChild[3], false>();
  test_binary_trait_cv<is_base_of, int, int, false>();

  // is_empty
  test_unary_trait_cv<is_empty, void, false>();
  test_unary_trait_cv<is_empty, int&, false>();
  test_unary_trait_cv<is_empty, int, false>();
  test_unary_trait_cv<is_empty, double, false>();
  test_unary_trait_cv<is_empty, int*, false>();
  test_unary_trait_cv<is_empty, const int*, false>();
  test_unary_trait_cv<is_empty, char[3], false>();
  test_unary_trait_cv<is_empty, char[3], false>();
  test_unary_trait_cv<is_empty, Union, false>();
  test_unary_trait_cv<is_empty, NotEmptyClass, false>();

  test_unary_trait_cv<is_empty, EmptyClass>();
  test_unary_trait_cv<is_empty, ZeroBit>();

  // is_polymorphic
  test_unary_trait_cv<is_polymorphic, void, false>();
  test_unary_trait_cv<is_polymorphic, int&, false>();
  test_unary_trait_cv<is_polymorphic, int, false>();
  test_unary_trait_cv<is_polymorphic, double, false>();
  test_unary_trait_cv<is_polymorphic, int*, false>();
  test_unary_trait_cv<is_polymorphic, const int*, false>();
  test_unary_trait_cv<is_polymorphic, char[3], false>();
  test_unary_trait_cv<is_polymorphic, char[3], false>();
  test_unary_trait_cv<is_polymorphic, Union, false>();
  test_unary_trait_cv<is_polymorphic, EmptyClass, false>();
  test_unary_trait_cv<is_polymorphic, ZeroBit, false>();
  test_unary_trait_cv<is_polymorphic, Final, false>();
  test_unary_trait_cv<is_polymorphic, NotEmptyClass&, false>();
  test_unary_trait_cv<is_polymorphic, AbstractClass&, false>();
  test_unary_trait_cv<is_polymorphic, NotEmptyClass>();
  test_unary_trait_cv<is_polymorphic, AbstractClass>();

  // is_abstract
  test_unary_trait_cv<is_abstract, void, false>();
  test_unary_trait_cv<is_abstract, int&, false>();
  test_unary_trait_cv<is_abstract, int, false>();
  test_unary_trait_cv<is_abstract, double, false>();
  test_unary_trait_cv<is_abstract, int*, false>();
  test_unary_trait_cv<is_abstract, const int*, false>();
  test_unary_trait_cv<is_abstract, char[3], false>();
  test_unary_trait_cv<is_abstract, char[3], false>();
  test_unary_trait_cv<is_abstract, Union, false>();
  test_unary_trait_cv<is_abstract, EmptyClass, false>();
  test_unary_trait_cv<is_abstract, ZeroBit, false>();
  test_unary_trait_cv<is_abstract, NotEmptyClass, false>();
  test_unary_trait_cv<is_abstract, AbstractClass>();
}
