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

#include <stdio.h>
#include <math.h++>
#include <tmp.h++>
#include <types.h++>
#include <utility.h++>
  using namespace kiss;

#include <typeinfo>

class A
{
public:
  A(int) {}
  A(char) noexcept {}
  A() noexcept {}
};

int main()
{
  static_assert(kiss::is_same<int, kiss::remove_cv<const volatile int>::type>(), "uhoh");
}
