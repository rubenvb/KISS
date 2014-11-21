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
