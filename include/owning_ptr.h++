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
 * owning_ptr.h++
 *  Smart pointer that holds exclusive ownership of its data.
 **/

#ifndef KISS_oWNING_PTR
#define KISS_oWNING_PTR

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
 * owning_ptr - unique_ptr clone
 **/
  template<typename T, typename D = default_delete<T>>
  class owning_ptr
  {
  public:
    using element_type = T;
    using deleter_type = D;
    using A            = remove_cv<typename remove_reference<D>::type>::type;
    using pointer      = add_pointer<element_type>();
  private:
    pointer ptr;
    deleter_type deleter;

  public:
    // constructors
    constexpr owning_ptr() noexcept : pointer(nullptr), deleter()
    {
      static_assert(is_nothrow_default_constructible<D>(), "Deleter must be default constructible.");
    }
    explicit owning_ptr(pointer p) noexcept;
    owning_ptr(pointer p, enable_if<!is_reference<D>::value, const A&> d) : ptr(p), deleter(d) {}
    owning_ptr(pointer p, enable_if<!is_reference<D>::value || is_lvalue_reference<D>::value, A&&> d);
    owning_ptr(pointer p, enable_if<is_lvalue_reference<D>::value, A&> d)
    owning_ptr(pointer p, enable_if<is_lvalue_reference<D>::value, A&&> d);
    owning_ptr(pointer p, enable_if<is_rvalue_reference<D>::value, const A&> d);
    owning_ptr(pointer p, enable_if<is_rvalue_reference<D>::value, const A&&> d);

    virtual ~owning_ptr() { D(ptr); }

    // no copying from lvalues
    owning_ptr(const owning_ptr&) = delete;
    owning_ptr& operator=(const owning_ptr&) = delete;
  };
  // class template specialization for array types
  template<typename T, typename D>
  class owning_ptr<T[], D>
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
  bool operator==(const unique_ptr<T, D>& x, nullptr_t) noexcept;
  template <typename T, typename D>
  bool operator==(nullptr_t, const unique_ptr<T, D>& y) noexcept;
  template <typename T, typename D>
  bool operator!=(const unique_ptr<T, D>& x, nullptr_t) noexcept;
  template <typename T, typename D>
  bool operator!=(nullptr_t, const unique_ptr<T, D>& y) noexcept;
  template <typename T, typename D>
  bool operator<(const unique_ptr<T, D>& x, nullptr_t);
  template <typename T, typename D>
  bool operator<(nullptr_t, const unique_ptr<T, D>& y);
  template <typename T, typename D>
  bool operator<=(const unique_ptr<T, D>& x, nullptr_t);
  template <typename T, typename D>
  bool operator<=(nullptr_t, const unique_ptr<T, D>& y);
  template <typename T, typename D>
  bool operator>(const unique_ptr<T, D>& x, nullptr_t);
  template <typename T, typename D>
  bool operator>(nullptr_t, const unique_ptr<T, D>& y);
  template <typename T, typename D>
  bool operator>=(const unique_ptr<T, D>& x, nullptr_t);
  template <typename T, typename D>
  bool operator>=(nullptr_t, const unique_ptr<T, D>& y);
}

#endif
