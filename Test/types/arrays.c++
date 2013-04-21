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

int main()
{
  // rank
  // extent
  // remove_extent
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

  // remove_all_extents
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
}
