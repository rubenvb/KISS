/**
 * This file is dual licensed under the MIT and the University of Illinois Open
 * Source Licenses. See LICENSE.TXT for details.
 *
 ********************************************************************************************/

 /*
  * test/types/arrays.c++
  */

#include <types.h++>

#include "../test.h++"

using namespace kiss;

int main()
{
//TODO rank

//TODO extent

//TODO remove_extent
  static_assert(is_same<remove_extent<int>::type, int>(), "");
  static_assert(is_same<remove_extent<int[]>::type, int>(), "");
  static_assert(is_same<remove_extent<const int[]>::type, const int>(), "");
  static_assert(is_same<remove_extent<int[3]>::type, int>(), "");
  static_assert(is_same<remove_extent<const int[3]>::type, const int>(), "");
  static_assert(is_same<remove_extent<int[][3]>::type, int[3]>(), "");
  static_assert(is_same<remove_extent<const int[][3]>::type, const int[3]>(), "");
  static_assert(is_same<remove_extent<int[2][3]>::type, int[3]>(), "");
  static_assert(is_same<remove_extent<const int[2][3]>::type, const int[3]>(), "");
  static_assert(is_same<remove_extent<int[1][2][3]>::type, int[2][3]>(), "");
  static_assert(is_same<remove_extent<const int[1][2][3]>::type, const int[2][3]>(), "");

//TODO remove_all_extents
  static_assert(is_same<remove_all_extents<int>::type, int>(), "");
  static_assert(is_same<remove_all_extents<int[]>::type, int>(), "");
  static_assert(is_same<remove_all_extents<const int[]>::type, const int>(), "");
  static_assert(is_same<remove_all_extents<int[3]>::type, int>(), "");
  static_assert(is_same<remove_all_extents<const int[3]>::type, const int>(), "");
  static_assert(is_same<remove_all_extents<int[][3]>::type, int>(), "");
  static_assert(is_same<remove_all_extents<const int[][3]>::type, const int>(), "");
  static_assert(is_same<remove_all_extents<int[2][3]>::type, int>(), "");
  static_assert(is_same<remove_all_extents<const int[2][3]>::type, const int>(), "");
  static_assert(is_same<remove_all_extents<int[1][2][3]>::type, int>(), "");
  static_assert(is_same<remove_all_extents<const int[1][2][3]>::type, const int>(), "");

  // decay
  test_nested_type_trait<decay, void, void>();
  test_nested_type_trait<decay, int, int>();
  test_nested_type_trait<decay, const volatile int, int>();
  test_nested_type_trait<decay, int*, int*>();
  test_nested_type_trait<decay, int[3], int*>();
  test_nested_type_trait<decay, const int[3], const int*>();
  test_nested_type_trait<decay, void(), void (*)()>();
}
