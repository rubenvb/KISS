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
 * array.h++
 *  Fixed and variable sized managed memory with contiguous storage
 **/

#ifndef KISS_ARRAY_H
#define KISS_ARRAY_H

#include "config.h++"

namespace kiss
{
  //T& get(array<T, size>&) noexcept;
  //template<size_t index, typename T, size_type size>
  //const T& get(const array<T, size>&) noexcept;
  //template <size_t index, typename T, size_type size>
  //T&& get(array<T, size>&&) noexcept;
  // Fixed-size
  template<typename T, kiss::size_type N>
  class array
  {
    T[N] storage;
  public:
    constexpr kiss::size_type size() { return N };

  };

  // Variable-size
  template<typename T>
  class array
  {

  };

}

#endif
