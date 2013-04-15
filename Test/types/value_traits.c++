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
  * types/misc.cxx
  *  Miscellaneous traits
  */

#include <types.h++>

auto l = [](){};
class Class {};
// all sorts of function pointers
typedef void (function)();
//typedef const volatile int (cvfunction)();
typedef void (*fp)();
//typedef const volatile void (*cvfp)();
typedef void (Class::*mfp)();
/*
 * Enable when  r-value for *this is widely available
typedef void (Class::*mfpr)()&;
typedef void (Class::*mfprr)()&&;
 */
typedef void (Class::*cvmfp)() const volatile;
typedef int Class::*ptm;
typedef const int Class::* const volatile cvptm;
typedef decltype(l) lambda;

int main()
{
}
