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
 * unique_ptr.h++
 *  Smart pointer that holds exclusive ownership of its data.
 **/

#ifndef KISS_UNIQUE_PTR_H
#define KISS_UNIQUE_PTR_H

#include "config.h++"
#include "compressed_pair.h++"
#include "types.h++"

namespace kiss
{
/*
 * Default deleters
 **/
  template<typename T> struct default_delete
  {
    constexpr default_delete() noexcept = default;
    template<typename U> default_delete(const enable_if<is_convertible<T, U>::value, default_delete<U>>&) noexcept {}
    void operator()(T* pointer) const { delete pointer; }
  };
  template<typename T> struct default_delete<T[]>
    {
    constexpr default_delete() noexcept = default;
    void operator()(T* array) const { delete[] array; }
    template<typename U> void operator()(U*) const = delete;
    };
/*
 * unique_ptr - unique_ptr clone
 **/
  template<typename T, typename D = default_delete<T>>
  class unique_ptr
  {
  public:
    using element_type = T;
    using deleter_type = D;
    using pointer_type = typename add_pointer<element_type>::type;
  private:
    pair<pointer_type, deleter_type> data;

  public:
    // constructors
    constexpr unique_ptr() noexcept : data()
    {
      static_assert(is_nothrow_default_constructible<D>(), "Deleter must be default constructible.");
      static_assert(is_pointer<D>() || is_reference<D>(), "Deleter cannot be a pointer or reference type here.");
    }
    explicit unique_ptr(pointer_type pointer) noexcept : data(pointer, deleter_type())
    {
      static_assert(is_nothrow_default_constructible<D>(), "Deleter must be default constructible.");
      static_assert(is_pointer<D>() || is_reference<D>(), "Deleter cannot be a pointer or reference type here.");
    }
    unique_ptr(pointer_type p, conditional<is_reference<deleter_type>::value,
                                           deleter_type,
                                           typename add_lvalue_reference<const deleter_type>::type> d) noexcept
    : data(p, d) {}
    unique_ptr(pointer_type p, typename remove_reference<deleter_type>::type&& d) noexcept
    : data(p, move(d))
    { static_assert(!is_reference<deleter_type>::value, "R-value deleter cannot bind to reference here."); }

    // destructor
    ~unique_ptr() { reset(); }

    // reset
    void reset(pointer_type p = pointer_type()) noexcept
    {
      pointer_type temp = data.first;
      data.first = p;
      if(temp != pointer_type())
        data.second.operator()(temp);
    }

    // no copying from lvalues
    unique_ptr(const unique_ptr&) = delete;
    unique_ptr& operator=(const unique_ptr&) = delete;
  };
  // class template specialization for array types
  template<typename T, typename D>
  class unique_ptr<T[], D>
  {
  };

/*
 * make_unique - perfect forwarding and exception safety
 **/
  template<typename T, typename... Args>
  unique_ptr<T> make_unique(Args&&... args)
  {
    return unique_ptr<T>(new T(forward<Args>(args)...));
  }

/*
 * Operator overloads
 **/
  template<typename T1, typename D1, typename T2, typename D2>
  bool operator==(const unique_ptr<T1, D1>& x, const unique_ptr<T2, D2>& y);
  template<typename T1, typename D1, typename T2, typename D2>
  bool operator!=(const unique_ptr<T1, D1>& x, const unique_ptr<T2, D2>& y);
  template<typename T1, typename D1, typename T2, typename D2>
  bool operator<(const unique_ptr<T1, D1>& x, const unique_ptr<T2, D2>& y);
  template<typename T1, typename D1, typename T2, typename D2>
  bool operator<=(const unique_ptr<T1, D1>& x, const unique_ptr<T2, D2>& y);
  template<typename T1, typename D1, typename T2, typename D2>
  bool operator>(const unique_ptr<T1, D1>& x, const unique_ptr<T2, D2>& y);
  template<typename T1, typename D1, typename T2, typename D2>
  bool operator>=(const unique_ptr<T1, D1>& x, const unique_ptr<T2, D2>& y);
  template <typename T, typename D>
  bool operator==(const unique_ptr<T, D>& x, nullptr_type) noexcept;
  template <typename T, typename D>
  bool operator==(nullptr_type, const unique_ptr<T, D>& y) noexcept;
  template <typename T, typename D>
  bool operator!=(const unique_ptr<T, D>& x, nullptr_type) noexcept;
  template <typename T, typename D>
  bool operator!=(nullptr_type, const unique_ptr<T, D>& y) noexcept;
  template <typename T, typename D>
  bool operator<(const unique_ptr<T, D>& x, nullptr_type);
  template <typename T, typename D>
  bool operator<(nullptr_type, const unique_ptr<T, D>& y);
  template <typename T, typename D>
  bool operator<=(const unique_ptr<T, D>& x, nullptr_type);
  template <typename T, typename D>
  bool operator<=(nullptr_type, const unique_ptr<T, D>& y);
  template <typename T, typename D>
  bool operator>(const unique_ptr<T, D>& x, nullptr_type);
  template <typename T, typename D>
  bool operator>(nullptr_type, const unique_ptr<T, D>& y);
  template <typename T, typename D>
  bool operator>=(const unique_ptr<T, D>& x, nullptr_type);
  template <typename T, typename D>
  bool operator>=(nullptr_type, const unique_ptr<T, D>& y);
}

#endif
