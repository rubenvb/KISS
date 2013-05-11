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
 * atomic.h++
 *  KISS atomics.
 **/

#ifndef KISS_ATOMIC_H
#define KISS_ATOMIC_H

#include "config.h++"

namespace kiss
{
  namespace atomic
  {
  /*
   * arithmetic
   **/
    template<typename T> inline T increment(T& t) noexcept
    {
      return __sync_add_and_fetch(&t, 1);
    }
    template<typename T> inline T decrement(T& t) noexcept
    {
      return __sync_add_and_fetch(&t, -1);
    }
  }
}

#endif
