/**
 * Written in 2013-2015 by Ruben Van Boxem <vanboxem.ruben@gmail.com>
 * Improved by contributions by Xeo and Luc Danton from stackoverflow.com
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
  * types.hxx
  *  Basic type definitions.
  *  Metatemplate programming helpers for type transformation.
  */

#ifndef KISS_TYPES_H
#define KISS_TYPES_H

#include "config.h++"

namespace kiss
{
/*
 * Basic types
 **/
  // pointer and size types
  using nullptr_type = decltype(nullptr);
  using size_type    = decltype(sizeof(0));
  using ptrdiff_type = decltype((char*)0-(char*)0);

  // fixed-width signed integers
  using int8  = signed char;
  using int16 = signed short;
  using int32 = signed int;
  using int64 = signed long long;

  // fixed width unsigned integers
  using uint8  = unsigned char;
  using uint16 = unsigned short;
  using uint32 = unsigned int;
  using uint64 = unsigned long long;

  // UTF character types
  using char8  = char;
  using char16 = char16_t;
  using char32 = char32_t;

  // integral_constant
  template<typename T, T valueT>
  struct integral_constant
  {
    static constexpr T value = valueT;
    using type = integral_constant<T,value>;
    constexpr operator T() { return value; }
  };
  // true_type
  using true_type = integral_constant<bool, true>;
  // false_type
  using false_type = integral_constant<bool, false>;

}

/*
 * This little bit of code below makes any code including <initializer_list>
 * fail to compile so here are the preprocessor defines to prevent double
 * declaration for GCC's libstdc++ and LLVM's libc++
 **/
#if !defined(_LIBCPP_INITIALIZER_LIST) && !defined(_INITIALIZER_LIST)
#define _LIBCPP_INITIALIZER_LIST
#define _INITIALIZER_LIST
/*
 * initializer_list type for brace-intializer-lists C++11 requires this in namespace std, unfortunately
 */
namespace std
{
  template<typename E> class initializer_list
  {
  public:
    using value_type      = E;
    using reference       = const E&;
    using const_reference = const E&;
    using size_type       = kiss::size_type;
    using iterator        = const E*;
    using const_iterator  = const E*;
    initializer_list();
    kiss::size_type size() const;
    const E* begin() const;
    const E* end() const;
  };
  template<typename E> const E* begin(initializer_list<E> il)
  { return il.begin(); }
  template<typename E> const E* end(initializer_list<E> il)
  { return il.end(); }
}
namespace kiss
{
  template<typename T> using initializer_list = std::initializer_list<T>;
}
#endif

/*
 * This defines the type_info struct, also bound to the implementation, required for the typeid keyword
 **/
namespace std
{
  class type_info
  {
  public:
    virtual ~type_info();

    bool operator==(const type_info& rhs) const noexcept;
    bool operator!=(const type_info& rhs) const noexcept;

    bool before(const type_info& rhs) const noexcept;
    kiss::size_type hash_code() const noexcept;
    const char* name() const noexcept;

    type_info(const type_info& rhs) = delete;
    type_info& operator=(const type_info& rhs) = delete;
  };
}
namespace kiss
{
  using std::type_info;

  // A compile-time rtti-less way of getting a numeric id for a type
  // by iavr, retrieved from: http://codereview.stackexchange.com/questions/48594
  // uses a pointer to a specialization of a function template as id
  // TODO: may not work accross shared library boundaries...
  class type_id_t
  {
    using signature = type_id_t();

    signature* id;
    constexpr type_id_t(signature* id) : id{id} {}

  public:
    template<typename T>
    friend constexpr type_id_t type_id() noexcept;

    constexpr bool operator==(type_id_t o) const noexcept { return id == o.id; }
    constexpr bool operator!=(type_id_t o) const noexcept { return id != o.id; }
    constexpr bool operator<(type_id_t o) const noexcept { return id < o.id; }
  };

  template<typename T>
  constexpr type_id_t type_id() noexcept { return &type_id<T>; }
}

#endif
