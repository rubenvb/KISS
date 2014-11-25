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
 * tuple.h++
 *  Heterogeneous set of values.
 *  Code adapted from https://bitbucket.org/mitchnull/samples/src/tip/cpp/Tuple/Tuple.hpp.
 **/

#ifndef KISS_TUPLE_H
#define KISS_TUPLE_H

#include "config.h++"

#include "algorithm.h++"
#include "reference_wrapper.h++"
#include "types.h++"
#include "type_traits.h++"

namespace kiss
{

template<typename... Types>
class Tuple;

template<size_type index, typename T, bool empty = is_empty<T>::value && !__is_final(T)>
class TupleLeaf;

template<size_type index, typename T, bool empty>
inline void swap(TupleLeaf<index, T, empty>& a,
                 TupleLeaf<index, T, empty>& b) {
    swap(a.get(), b.get());
}

template <size_type index, typename T, bool empty>
class TupleLeaf
{
  T value;

  TupleLeaf& operator=(const TupleLeaf&) = delete;

public:
  TupleLeaf()
  : value()
  {
    static_assert(!is_reference<T>::value, "Attempt to default construct a reference element in a tuple");
  }

  TupleLeaf(const TupleLeaf& t)
  : value(t.get())
  {
    static_assert(!is_rvalue_reference<T>::value, "Can not copy a tuple with rvalue reference member");
  }

  template <typename U, typename = typename enable_if<
  is_constructible<T, U>::value>::type>
  explicit TupleLeaf(U&& t)
  : value(forward<U>(t))
  {
    static_assert(!is_reference<T>::value
                  || (is_lvalue_reference<T>::value
                      && (is_lvalue_reference<U>::value
                          || is_same<typename remove_reference<U>::type, reference_wrapper<typename remove_reference<T>::type>>::value))
                  || (is_rvalue_reference<T>::value
                      && !is_lvalue_reference<U>::value),
    "Attempted to construct a reference element in a tuple with an rvalue");
  }

  template <typename U>
  explicit TupleLeaf(const TupleLeaf<index, U>& t)
  : value(t.get()) {
  }

  template <typename U>
  TupleLeaf& operator=(U&& t) {
    value = forward<U>(t);
    return *this;
  }

  int swap(TupleLeaf& t) {
    swap(*this, t); //TODO check if this is the right swap
    return 0;
  }

  T& get() {
    return value;
  }

  const T& get() const {
    return value;
  }
};

} // namespace kiss

#endif // TUPLE_H
