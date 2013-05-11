/**
 * Written in 2013 by Ruben Van Boxem <vanboxem.ruben@gmail.com>
 *  Inspired by R. Martinho Fernandez' Flaming Danger Zone Size Matters blog series.
 *  http://flamingdangerzone.com/cxx11/2012/07/06/optimal-tuple-i.html
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
 *  Heteregoneous container of an arbitrary constexpr amount of types/objects
 * Implementation details:
 *  The real tuple stores its elements in an optimal_storage struct in the optimal order,
 *   indexed using a simple unoptimized tuple.
 **/

#ifndef KISS_TUPLE_H
#define KISS_TUPLE_H

#include "config.h++"
#include "types.h++"

namespace kiss
{
  // Forward decarations
  namespace implementation
  {
    // simple_tuple
    template<typename... Ts> struct simple_tuple;
    // tuple_size
    template<typename Tuple> struct tuple_size;
  }
  // tuple_element
  /*template<size_type index, typename Tuple> struct tuple_element;
  template<size_type index, typename Tuple> struct tuple_element<index, const Tuple>
  { using type = typename add_const<typename tuple_element<index, Tuple>::type>::type; };
  template<size_type index, class Tuple> struct tuple_element<index, volatile Tuple>
  { using type = typename add_volatile<typename tuple_element<index, Tuple>::type>::type; };
  template<size_type index, typename Tuple> struct tuple_element<index, const volatile Tuple>
  { using type = typename add_cv<typename tuple_element<index, Tuple>::type>::type; };
*/
  namespace implementation
  {
  /*
   * Simple tuple to index the real tuple's indices to the optimal_storage
   **
    // simple_tuple
    template<> struct simple_tuple<> {};
    template<typename First, typename... Rest> struct simple_tuple<First, Rest...>
    {
      explicit simple_tuple(First first, Rest... the_rest) : first_element(first), rest(the_rest...) {}
    private:
      First first_element;
      simple_tuple<Rest...> rest;
    };
    // get
    template<size_type index, typename... Ts> typename tuple_element<0, simple_tuple<Ts...>>::type get(const simple_tuple<Ts...>& t)
    {
      return t.first_element;
    }
    template<size_type index, typename... Ts> typename tuple_element<index, simple_tuple<Ts...>>::type get(const simple_tuple<Ts...>& t)
    {
      return get<index-1,simple_tuple<Ts...>::rest>(t);
    }
    // tuple_size
    template<typename Tuple> struct tuple_size<const Tuple> : tuple_size<Tuple> {};
    template<typename Tuple> struct tuple_size<volatile Tuple> : tuple_size<Tuple> {};
    template<typename Tuple> struct tuple_size<const volatile Tuple> : tuple_size<Tuple> {};

    template<typename... Ts>
    struct tuple_size<simple_tuple<Ts...>> : integral_constant<size_type, sizeof...(Ts)> {};
    */
    // compile time array to index real typle to optimal_storage
    //template<typename... Ts>
    //struct tuple_index { static constexpr size_type array[sizeof...(Ts)]; };

    template<typename T, size_type I>
    struct indexed {
        using type = T;
        static constexpr size_type index = I;
    };

    // optimal_storage to use as little padding bytes as possible
    template<typename... T>
    struct optimal_storage
    {

    };
  }

/*
  template<typename... T>
  struct tuple
  {

  };

  // get
  template<size_type index, typename... Ts>
  typename tuple_element<index, tuple<Ts...>>::type& get(tuple<Ts...>&) noexcept;
  template<size_type index, typename... Ts>
  const typename tuple_element<index, tuple<Ts...>>::type& get(const tuple<Ts...>&) noexcept;
  template<size_type index, typename... Ts>
  typename tuple_element<index, tuple<Ts...>>::type&& get(tuple<Ts...>&&) noexcept;
*/
}

#endif
