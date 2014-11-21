/**
 * Written in 2014 by Ruben Van Boxem <vanboxem.ruben@gmail.com>
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
 * aligned_union.h++
 *  Provides aligned polymorphic memory.
 **/

#ifndef KISS_ALIGNED_UNION_H
#define KISS_ALIGNED_UNION_H

#include "config.h++"
#include "meta_utility.h++"
#include "types.h++"

namespace kiss
{

template<size_type minimum_size, typename... Types>
struct aligned_union
{
  static constexpr const size_type alignment = static_max<alignof(Types)...>::value;
  static constexpr const size_type size = static_max<minimum_size, sizeof(Types)...>::value;
  using type = typename aligned_storage<size, alignment>::type;
};

}

#endif
