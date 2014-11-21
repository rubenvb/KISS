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
 * pointer_traits.h++
 * A uniform interface to pointer-like types.
 *
 **/

#ifndef KISS_POINTER_TRAITS_H
#define KISS_POINTER_TRAITS_H

#include "config.h++"

namespace kiss
{
  template<typename Ptr>
  struct pointer_traits
  {
    using pointer_type = Ptr;
    using element_type = typename remove_pointer<Ptr>::type;
    using difference_type = decltype(declval<Ptr>()-declval<Ptr>());
    template<typename U> using rebind = see below;
    static pointer_type pointer_to(see below r);
  };
  template<typename T>
  struct pointer_traits<T*>
  {
    using pointer_type = T*;
    using element_type = T;
    using difference_type = ptrdiff_type;
    template<typename U> using rebind = U*;
    static pointer_type pointer_to(see below r) noexcept;
  };
}

#endif
