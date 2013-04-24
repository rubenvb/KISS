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

#ifndef KISS_UNIQUE_PTR
#define KISS_UNIQUE_PTR

#include "tmp.h++"
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
    using A            = typename remove_cv<typename remove_reference<D>::type>::type;
    using pointer      = typename add_pointer<element_type>::type;
  private:
    pointer ptr;
    deleter_type deleter;

  public:
    // constructors
    constexpr unique_ptr() noexcept : ptr(), deleter()
    {
      static_assert(is_nothrow_default_constructible<D>(), "Deleter must be default constructible.");
      static_assert(is_pointer<D>() || is_reference<D>(), "Deleter cannot be a pointer or reference type here.");
    }
    explicit unique_ptr(pointer p) noexcept : ptr(p), deleter()
    {
      static_assert(is_nothrow_default_constructible<D>(), "Deleter must be default constructible.");
      static_assert(is_pointer<D>() || is_reference<D>(), "Deleter cannot be a pointer or reference type here.");
    }
    unique_ptr(pointer p, conditional<is_reference<D>::value, D, typename add_lvalue_reference<const D>::type> d) : ptr(p), deleter(d) {}
    unique_ptr(pointer p, enable_if<!is_reference<D>::value || is_lvalue_reference<D>::value, A&&> d);
    unique_ptr(pointer p, enable_if<is_lvalue_reference<D>::value, A&> d);
    unique_ptr(pointer p, enable_if<is_lvalue_reference<D>::value, A&&> d);
    unique_ptr(pointer p, enable_if<is_rvalue_reference<D>::value, const A&> d);
    unique_ptr(pointer p, enable_if<is_rvalue_reference<D>::value, const A&&> d);

    virtual ~unique_ptr() { D(ptr); }

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
