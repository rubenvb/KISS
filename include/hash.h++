/**
 * Written in 2015-2015 by Ruben Van Boxem <vanboxem.ruben@gmail.com>
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
 * hash.h++
 *  Hashing specialized for kiss types.
 **/

#ifndef KISS_HASH_H
#define KISS_HASH_H

#include "config.h++"

#include "types.h++"

namespace kiss
{
  template<typename T>
  constexpr size_type hash() noexcept;
}

#endif
