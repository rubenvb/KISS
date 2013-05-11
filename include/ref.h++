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
 * ref.h++
 * A copy constructible and copy assignable wrapper around a reference to an object or function and assorted utilities.
 *
 **/

#ifndef KISS_REF_H
#define KISS_REF_H

#include "config.h++"
#include "tmp.h++"
#include "types.h++"

namespace kiss
{
  // reference_wrapper
  template<class T> struct reference_wrapper
  {
    using type = T;

    // construction
    explicit reference_wrapper(T& t) noexcept : t(addressof<T>(t)) {}
    reference_wrapper(T&&) = delete;
    reference_wrapper(const reference_wrapper<T>& x) noexcept : t(x.t) {}

    // Access
    operator T& () const { return *t; }
    T& get() const { return *t; }

    template<typename... ArgTypes>
    typename result_of<T&(ArgTypes&&...)>::type operator() (ArgTypes&&...) const;

  private:
    T* t;
  };

  // ref
  template<class T> inline reference_wrapper<T> const ref(T & t)
  { return reference_wrapper<T>(t); }
  // cref
  template<class T> inline reference_wrapper<T const> const cref(T const & t)
  { return reference_wrapper<T const>(t); }

  // is_reference_wrapper
  template<typename T> struct is_reference_wrapper : public false_type {};
  template<typename T> struct is_reference_wrapper<reference_wrapper<T> const> : true_type {};
  template<typename T> struct is_reference_wrapper<reference_wrapper<T> volatile> : true_type {};
  template<typename T> struct is_reference_wrapper<reference_wrapper<T> const volatile> : true_type {};

  // unwrap_reference
  template<typename T> struct unwrap_reference { using type = T; };
  template<typename T> struct unwrap_reference<reference_wrapper<T> const> { using type = T; };
  template<typename T> struct unwrap_reference<reference_wrapper<T> volatile> { using type = T; };
  template<typename T> struct unwrap_reference<reference_wrapper<T> const volatile> { using type = T; };

  // unwrap reference
  template<typename T> inline typename unwrap_reference<T>::type&
  unwrap_ref(T& t) { return t; }
}

#endif
