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
 * aligned_storage.h++
 *  Provides aligned memory.
 **/

#ifndef KISS_ALIGNED_STORAGE_H
#define KISS_ALIGNED_STORAGE_H

#include "config.h++"
#include "meta_utility.h++"
#include "types.h++"

namespace kiss
{
  //TODO aligned_storage - needs default argument
  namespace implementation
  {
    template<size_type size>
    struct arraystruct { char array[size]; };
  }
  template<size_type size, size_type alignment = alignof(implementation::arraystruct<size>)>
  struct aligned_storage
  { using type = struct { alignas(alignment) unsigned char data[size]; }; };
}

#endif
