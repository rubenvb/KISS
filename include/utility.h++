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
 * utility.h++
 *  Utility functions.
 **/

#ifndef KISS_UTILITY_H
#define KISS_UTILITY_H

#include "types.h++"

namespace kiss
{
  template<class T> remove_reference<T>&& move(T&&) noexcept;

  template<typename T> constexpr T&&
  forward(remove_reference<T> t)
  {
    static_assert(!kiss::is_lvalue_reference<T>(), "lvalue cannot be converted to rvalue.");
    return static_cast<T&&>(t);
  }
}

#endif
