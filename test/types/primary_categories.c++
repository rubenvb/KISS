/**
 * Written in 2013-2015 by Ruben Van Boxem <vanboxem.ruben@gmail.com>
 *
 * This file is dual licensed under the MIT and the University of Illinois Open
 * Source Licenses. See LICENSE.TXT for details.
 *
 ********************************************************************************************/

/*
 * test/types/primary_categories.c++
 **/

#include <type_traits.h++>

#include "../test.h++"

using namespace kiss;

int main()
{
  // is_void
  test_unary_trait_cv<is_void, void>();
  test_unary_trait_cv<is_void, int, false>();
  test_unary_trait_cv<is_void, int*, false>();
  test_unary_trait_cv<is_void, int[], false>();
  test_unary_trait_cv<is_void, Array, false>();
  test_unary_trait_cv<is_void, Class, false>();
  test_unary_trait_cv<is_void, Function, false>();
  test_unary_trait_cv<is_void, nullptr_type, false>();

  // is_integral
  test_unary_trait_cv<is_integral, void, false>();
  test_unary_trait_cv<is_integral, int>();
  test_unary_trait_cv<is_integral, int*, false>();
  test_unary_trait_cv<is_integral, int[], false>();
  test_unary_trait_cv<is_integral, Array, false>();
  test_unary_trait_cv<is_integral, Class, false>();
  test_unary_trait_cv<is_integral, Function, false>();
  test_unary_trait_cv<is_integral, nullptr_type, false>();

  // is_floating_point
  test_unary_trait_cv<is_floating_point, void, false>();
  test_unary_trait_cv<is_floating_point, int, false>();
  test_unary_trait_cv<is_floating_point, int*, false>();
  test_unary_trait_cv<is_floating_point, int[], false>();
  test_unary_trait_cv<is_floating_point, float>();
  test_unary_trait_cv<is_floating_point, double>();
  test_unary_trait_cv<is_floating_point, long double>();
  test_unary_trait_cv<is_floating_point, Array, false>();
  test_unary_trait_cv<is_floating_point, Class, false>();
  test_unary_trait_cv<is_floating_point, Function, false>();
  test_unary_trait_cv<is_floating_point, nullptr_type, false>();

  // is_c_array
  test_unary_trait_cv<is_c_array, void, false>();
  test_unary_trait_cv<is_c_array, int, false>();
  test_unary_trait_cv<is_c_array, int*, false>();
  test_unary_trait_cv<is_c_array, int[]>();
  test_unary_trait_cv<is_c_array, Array>();
  test_unary_trait_cv<is_c_array, Class, false>();
  test_unary_trait_cv<is_c_array, Function, false>();
  test_unary_trait_cv<is_c_array, nullptr_type, false>();

  // is_pointer
  test_unary_trait_cv<is_pointer, void, false>();
  test_unary_trait_cv<is_pointer, int, false>();
  test_unary_trait_cv<is_pointer, int*>();
  test_unary_trait_cv<is_pointer, int[], false>();
  test_unary_trait_cv<is_pointer, Array, false>();
  test_unary_trait_cv<is_pointer, Class, false>();
  test_unary_trait_cv<is_pointer, Function, false>();
  test_unary_trait_cv<is_pointer, FunctionPtr>();
  test_unary_trait_cv<is_pointer, nullptr_type, false>();

  // is_lvalue_reference
  test_unary_trait_cv<is_lvalue_reference, int&>();
  test_unary_trait_cv<is_lvalue_reference, Class&>();
  test_unary_trait_cv<is_lvalue_reference, int(&)(int)>();
  test_unary_trait_cv<is_lvalue_reference, int&&, false>();
  test_unary_trait_cv<is_lvalue_reference, Class, false>();

  // is_rvalue_reference
  test_unary_trait_cv<is_rvalue_reference, int&&>();
  test_unary_trait_cv<is_rvalue_reference, Class&&>();
  test_unary_trait_cv<is_rvalue_reference, int(&&)(int)>();
  test_unary_trait_cv<is_rvalue_reference, int&, false>();
  test_unary_trait_cv<is_rvalue_reference, Class, false>();

  // is_enum
  test_unary_trait_cv<is_enum, void, false>();
  test_unary_trait_cv<is_enum, int, false>();
  test_unary_trait_cv<is_enum, Class, false>();
  test_unary_trait_cv<is_enum, Enum>();
  test_unary_trait_cv<is_enum, Class, false>();
  test_unary_trait_cv<is_enum, Function, false>();
  test_unary_trait_cv<is_enum, IncompleteClass, false>();
  test_unary_trait_cv<is_enum, Union, false>();

  // is_union
  test_unary_trait_cv<is_union, void, false>();
  test_unary_trait_cv<is_union, int, false>();
  test_unary_trait_cv<is_union, Class, false>();
  test_unary_trait_cv<is_union, Enum, false>();
  test_unary_trait_cv<is_union, Class, false>();
  test_unary_trait_cv<is_union, Function, false>();
  test_unary_trait_cv<is_union, IncompleteClass, false>();
  test_unary_trait_cv<is_union, Union>();

  // is_class
  test_unary_trait_cv<is_class, void, false>();
  test_unary_trait_cv<is_class, int, false>();
  test_unary_trait_cv<is_class, Class>();
  test_unary_trait_cv<is_class, Enum, false>();
  test_unary_trait_cv<is_class, Function, false>();
  test_unary_trait_cv<is_class, IncompleteClass>();
  test_unary_trait_cv<is_class, Union, false>();

  // is_function
  test_unary_trait_cv<is_function, int (int)>();
  test_unary_trait_cv<is_function, Class(Class)>();
  test_unary_trait_cv<is_function, float (int, float, int[], int&)>();
  test_unary_trait_cv<is_function, int (int, ...)>();
  test_unary_trait_cv<is_function, int&, false>();
  test_unary_trait_cv<is_function, void, false>();
  test_unary_trait_cv<is_function, const void, false>();
  test_unary_trait_cv<is_function, AbstractClass, false>();
  test_unary_trait_cv<is_function, int(&)(int), false>();
  test_unary_trait_cv<is_function, Class, false>();
  test_unary_trait_cv<is_function, FunctionPtr, false>();

  // is_member_function_pointer
  test_unary_trait_cv<is_member_pointer, void (Class::*)()>();
  test_unary_trait_cv<is_member_pointer, int (Class::*)(int)>();
  test_unary_trait_cv<is_member_pointer, int (Class::*)(int) const>();
  test_unary_trait_cv<is_member_pointer, int (Class::*)(float, ...)>();
  test_unary_trait_cv<is_member_pointer, Class (Class::*)(Class)>();
  test_unary_trait_cv<is_member_pointer, float (Class::*)(int, float, int[], int&)>();
  test_unary_trait_cv<is_member_pointer, int (Class::*)>();
  test_unary_trait_cv<is_member_pointer, const int (Class::*)>();
  test_unary_trait_cv<is_member_pointer, Class (Class::*)>();

  test_unary_trait_cv<is_member_pointer, Class, false>();
  test_unary_trait_cv<is_member_pointer, int*, false>();

  // is_member_function_pointer
  test_unary_trait<is_member_function_pointer, void (Class::*)()>();
  test_unary_trait<is_member_function_pointer, int (Class::*)(int)>();
  test_unary_trait<is_member_function_pointer, int (Class::*)(int) const>();
  test_unary_trait<is_member_function_pointer, int (Class::*)(int) volatile>();
  test_unary_trait<is_member_function_pointer, int (Class::*)(float, ...)>();
  test_unary_trait<is_member_function_pointer, Class (Class::*)(Class)>();
  test_unary_trait<is_member_function_pointer, float (Class::*)(int, float, int[], int&)>();

  test_unary_trait<is_member_function_pointer, int (Class::*), false>();
  test_unary_trait<is_member_function_pointer, const int (Class::*), false>();
  test_unary_trait<is_member_function_pointer, Class (Class::*), false>();
  test_unary_trait<is_member_function_pointer, Class, false>();

  // is_member_object_pointer
  test_unary_trait<is_member_object_pointer, int (Class::*)>();
  test_unary_trait<is_member_object_pointer, const int (Class::*)>();
  test_unary_trait<is_member_object_pointer, Class(Class::*)>();

  test_unary_trait<is_member_object_pointer, int (Class::*)(int), false>();
  test_unary_trait<is_member_object_pointer, int (Class::*)(int) const, false>();
  test_unary_trait<is_member_object_pointer, int (Class::*)(float, ...), false>();
  test_unary_trait<is_member_object_pointer, Class (Class::*)(Class), false>();
  test_unary_trait<is_member_object_pointer, float (Class::*)(int, float, int[], int&), false>();
  test_unary_trait<is_member_object_pointer, Class, false>();
}
