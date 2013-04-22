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

namespace kiss
{
  template <class T> struct default_delete
  {
    constexpr default_delete() noexcept = default;
    template <class U> default_delete(const default_delete<U>&) noexcept;
    void operator()(T*) const;
  };

  template<typename T, typename D>
  class owning_ptr
  {
    pointer_type data;
    deleter_type deleter;
  public:
    typedef T element_type;
    typedef D deleter_type;
    typedef pointer_type pointer_type<element_type>();

    // constructors
    constexpr owning_ptr() noexcept
      : data(nullptr), deleter()
      {
        static_assert(is_default_constructible<D>(), "Deleter must be default constructible.");
        static_assert(noexcept(D::D()), "Deleter must be noexcept.");
      }
    explicit owning_ptr(pointer_type p) noexcept;

    unique_ptr(const unique_ptr&) = delete;
    unique_ptr& operator=(const unique_ptr&) = delete;
  };
}

#endif
