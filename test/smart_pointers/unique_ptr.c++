/**
 * Written in 2013-2015 by Ruben Van Boxem <vanboxem.ruben@gmail.com>
 *
 * This file is dual licensed under the MIT and the University of Illinois Open
 * Source Licenses. See LICENSE.TXT for details.
 *
 ********************************************************************************************/

/*
 * test/types/unique_ptr.c++
 **/

#include "unique_ptr.h++"

using namespace kiss;

int main()
{
  static_assert(sizeof(pair<int*, default_delete<int*>>) == sizeof(int*), "");
  static_assert(sizeof(unique_ptr<int>) == sizeof(int*), "");
  // static_assert(false, "unimplemented");
}
