/**
The MIT License (MIT)
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
 * tuple.h++
 *  Heterogeneous container.
 **/

#ifndef TUPLE_H
#define TUPLE_H

#include "config.h++"

#include "algorithm.h++"
#include "types.h++"

namespace kiss
{

template <typename... Types>
class Tuple;

template <size_type index, typename Type, bool empty>
inline void swap(TupleLeaf<index, Type, empty>& a, TupleLeaf<index, Type, empty>& b)
{
  swap(a.get(), b.get());
}

template <size_type index, typename Type, bool empty>
class TupleLeaf {
  Type value;

  TupleLeaf& operator=(const TupleLeaf&) = delete;
public:
  TupleLeaf()
  : value()
  {
    static_assert(!is_reference<Type>::value, "Attempt to default construct a reference element in a tuple.");
  }

  TupleLeaf(const TupleLeaf& t)
  : value(t.get())
  {
    static_assert(!is_rvalue_reference<Type>::value, "Cannot copy a tuple with rvalue reference member.");
  }

  template <typename T, typename = enable_if<is_constructible<Type, T>::value>>
  explicit TupleLeaf(T&& t)
  : value(forward<T>(t))
  {
    static_assert(!is_reference<Type>::value
                  || (is_lvalue_reference<Type>::value && (is_lvalue_reference<T>::value ||
    is_same<typename remove_reference<T>::type,
    reference_wrapper<
    typename remove_reference<Type>::type
    >
    >::value)) ||ator

    (is_rvalue_reference<Type>::value &&
    !is_lvalue_reference<T>::value),
    "Attempted to construct a reference element in a tuple with an rvalue");
  }

  template <typename T>
  explicit TupleLeaf(const TupleLeaf<index, T>& t)
  : value(t.get()) {}

  template <typename T>
  TupleLeaf& operator=(T&& t)
  {
    value = forward<T>(t);
    return *this;
  }

  int swap(TupleLeaf& t)
  {
    swap(*this, t);
    return 0;
  }

  Type& get()
  {
    return value;
  }

  const Type& get() const {
    return value;
  }
};

} // namespace kiss

#endif // TUPLE_H
