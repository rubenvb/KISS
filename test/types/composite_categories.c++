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
 * test/types/composite_categories.c++
 **/

#include <types.h++>

#include "../test.h++"

using namespace kiss;

int main()
{
  // is_reference
  test_unary_trait_cv<is_reference, int&>();
  test_unary_trait_cv<is_reference, Class&>();
  test_unary_trait_cv<is_reference, int(&)(int)>();
  test_unary_trait_cv<is_reference, int&&>();
  test_unary_trait_cv<is_reference, Class&&>();
  test_unary_trait_cv<is_reference, int(&&)(int)>();
  test_unary_trait_cv<is_reference, Class, false>();

  // is_arithmetic
  test_unary_trait_cv<is_arithmetic, void, false>();
  test_unary_trait_cv<is_arithmetic, int>();
  test_unary_trait_cv<is_arithmetic, int*, false>();
  test_unary_trait_cv<is_arithmetic, Class, false>();
  test_unary_trait_cv<is_arithmetic, Enum, false>();
  test_unary_trait_cv<is_arithmetic, Class, false>();
  test_unary_trait_cv<is_arithmetic, Function, false>();
  test_unary_trait_cv<is_arithmetic, IncompleteClass, false>();
  test_unary_trait_cv<is_arithmetic, Union, false>();

  // is_fundamental
  test_unary_trait_cv<is_fundamental, void>();
  test_unary_trait_cv<is_fundamental, char>();
  test_unary_trait_cv<is_fundamental, signed char>();
  test_unary_trait_cv<is_fundamental, unsigned char>();
  test_unary_trait_cv<is_fundamental, wchar_t>();
  test_unary_trait_cv<is_fundamental, short>();
  test_unary_trait_cv<is_fundamental, unsigned short>();
  test_unary_trait_cv<is_fundamental, int>();
  test_unary_trait_cv<is_fundamental, unsigned int>();
  test_unary_trait_cv<is_fundamental, long>();
  test_unary_trait_cv<is_fundamental, unsigned long>();
  test_unary_trait_cv<is_fundamental, long long>();
  test_unary_trait_cv<is_fundamental, unsigned long long>();
  test_unary_trait_cv<is_fundamental, float>();
  test_unary_trait_cv<is_fundamental, double>();
  test_unary_trait_cv<is_fundamental, long double>();
  test_unary_trait_cv<is_fundamental, nullptr_type>();
  test_unary_trait_cv<is_fundamental, Class, false>();

  // is_member_pointer
  test_unary_trait_cv<is_member_pointer, int (Class::*)>();
  test_unary_trait_cv<is_member_pointer, const int (Class::*)>();
  test_unary_trait_cv<is_member_pointer, Class (Class::*)>();
  test_unary_trait_cv<is_member_pointer, int (Class::*)(int)>();
  test_unary_trait_cv<is_member_pointer, int (Class::*)(int) const>();
  test_unary_trait_cv<is_member_pointer, int (Class::*) (float, ...)>();
  test_unary_trait_cv<is_member_pointer, Class (Class::*)(Class)>();
  test_unary_trait_cv<is_member_pointer, float (Class::*)(int, float, int[], int&)>();
  test_unary_trait_cv<is_member_pointer, Class, false>();

  // is_scalar
  test_unary_trait<is_scalar, int>();
  test_unary_trait<is_scalar, float>();
  test_unary_trait<is_scalar, Enum>();
  test_unary_trait<is_scalar, int*>();
  test_unary_trait<is_scalar, int(*)(int)>();
  test_unary_trait<is_scalar, int (Class::*)>();
  test_unary_trait<is_scalar, int (Class::*) (int)>();
  test_unary_trait<is_scalar, nullptr_type>();
  test_unary_trait<is_scalar, Class, false>();

  // is_object
  test_unary_trait<is_object, int (int), false>();
  test_unary_trait<is_object, Class (Class), false>();
  test_unary_trait<is_object, float (int, float, int[], int&), false>();
  test_unary_trait<is_object, int&, false>();
  test_unary_trait<is_object, Class&, false>();
  test_unary_trait<is_object, int(&)(int), false>();
  test_unary_trait<is_object, void, false>();
  test_unary_trait<is_object, const void, false>();
  test_unary_trait<is_object, IncompleteClass>();
  test_unary_trait<is_object, Class>();

  // is_compound
  test_unary_trait<is_compound, void, false>();
  test_unary_trait<is_compound, char, false>();
  test_unary_trait<is_compound, signed char, false>();
  test_unary_trait<is_compound, unsigned char, false>();
  test_unary_trait<is_compound, wchar_t, false>();
  test_unary_trait<is_compound, short, false>();
  test_unary_trait<is_compound, unsigned short, false>();
  test_unary_trait<is_compound, int, false>();
  test_unary_trait<is_compound, unsigned int, false>();
  test_unary_trait<is_compound, long, false>();
  test_unary_trait<is_compound, unsigned long, false>();
  test_unary_trait<is_compound, long long, false>();
  test_unary_trait<is_compound, unsigned long long, false>();
  test_unary_trait<is_compound, float, false>();
  test_unary_trait<is_compound, double, false>();
  test_unary_trait<is_compound, long double, false>();
  test_unary_trait<is_compound, nullptr_type, false>();
  test_unary_trait<is_compound, Class>();
}
