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

#ifndef KISS_META_UTILITY_H
#define KISS_META_UTILITY_H

#include "config.h++"
#include "types.h++"

namespace kiss
{
  template<size_type size, size_type... other_sizes>
  struct static_max;

  template<size_type size>
  struct static_max<size> : integral_constant<size_type, size> {};

  template<size_type size1, size_type size2, size_type... other_sizes>
  struct static_max<size1, size2, other_sizes...> : integral_constant<size_type, static_max<size1 >= size2 ? size1 : size2, other_sizes...>::value> {};
}

#endif
