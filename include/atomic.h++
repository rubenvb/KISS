/**
 * Written in 2013-2015 by Ruben Van Boxem <vanboxem.ruben@gmail.com>
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
 * atomic.h++
 *  KISS atomics.
 *  https://gcc.gnu.org/onlinedocs/gcc/_005f_005fatomic-Builtins.html
 **/

#ifndef KISS_ATOMIC_H
#define KISS_ATOMIC_H

#include "config.h++"

namespace kiss
{
  namespace atomic
  {
  /*
   * Operation ordering
   **/
    enum order
    {
      relaxed,
      consume,
      acquire,
      release,
      acquire_release,
      sequentially_consistent
    };
  /*
   * arithmetic
   **/
    template<typename T> inline T increment(T& t, order o = sequentially_consistent) noexcept
    {
      return __atomic_add_fetch(&t, 1, o);
    }
    template<typename T> inline T decrement(T& t, order o = sequentially_consistent) noexcept
    {
      return __atomic_sub_fetch(&t, -1, o);
    }
  }
}

#endif
