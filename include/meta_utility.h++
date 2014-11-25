/**
 * Written in 2014-2015 by Ruben Van Boxem <vanboxem.ruben@gmail.com>
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

#ifndef KISS_META_UTILITY_H
#define KISS_META_UTILITY_H

#include "config.h++"
#include "types.h++"

namespace kiss
{
  // conditional
  namespace implementation
  {
    template<bool, typename First, typename Second> struct conditional { using type = First; };
    template<typename First, typename Second> struct conditional<false, First, Second> { using type = Second; };
  }
  //template<bool B, typename First, typename Second> using conditional = typename implementation::conditional<B, First, Second>;
  template<bool B, typename First, typename Second> using conditional = typename implementation::conditional<B, First, Second>::type;

  // enable_if
  namespace implementation
  {
    template<bool, typename T = void> struct enable_if {};
    template<typename T> struct enable_if<true, T> { using type = T; };
  }
  template<bool Condition, typename T = void> using enable_if = typename implementation::enable_if<Condition, T>::type;

  // maximum of sizes
  template<size_type size, size_type... other_sizes>
  struct static_max;

  template<size_type size>
  struct static_max<size> : integral_constant<size_type, size> {};

  template<size_type size1, size_type size2, size_type... other_sizes>
  struct static_max<size1, size2, other_sizes...>
    : integral_constant<size_type, static_max<size1 >= size2 ? size1 : size2, other_sizes...>::value> {};

  // minimum of sizes
  template<size_type size, size_type... other_sizes>
  struct static_min;

  template<size_type size>
  struct static_min<size> : integral_constant<size_type, size> {};

  template<size_type size1, size_type size2, size_type... other_sizes>
  struct static_min<size1, size2, other_sizes...>
    : integral_constant<size_type, static_min<size1 <= size2 ? size1 : size2, other_sizes...>::value> {};
}

#endif
