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
  * types.hxx
  *  Basic type definitions.
  *  Metatemplate programming helpers for type transformation.
  */

#ifndef KISS_TYPES
#define KISS_TYPES

#include "config.h++"

namespace kiss
{
/*
 * Basic types
 **/
  // pointer and size types
  typedef decltype(nullptr)           nullptr_type;
  typedef decltype(sizeof(0))         size_type;
  typedef decltype((char*)0-(char*)0) ptrdiff_type;

  // fixed-width signed integers
  typedef signed char      int8;
  typedef signed short     int16;
  typedef signed int       int32;
  typedef signed long long int64;

  // fixed width unsigned integers
  typedef unsigned char      uint8;
  typedef unsigned short     uint16;
  typedef unsigned int       uint32;
  typedef unsigned long long uint64;

  // UTF character types
  typedef char    char8;
  typedef char16_t char16;
  typedef char32_t char32;

/*
 * integral_constant
 **/
  template<typename T, T valueT>
  struct integral_constant
  {
    static constexpr T value = valueT;
    typedef integral_constant<T,value> type;
    constexpr operator T() { return value; }
  };
  // true_type
  typedef integral_constant<bool, true> true_type;
  // false_type
  typedef integral_constant<bool, false> false_type;

/*
 * Transforming traits
 **/
  // remove_const
  template<typename T> struct remove_const { typedef T type; };
  template<typename T> struct remove_const<const T> { typedef T type; };
  // remove_volatile
  template<typename T> struct remove_volatile { typedef T type; };
  template<typename T> struct remove_volatile<volatile T> { typedef T type; };
  // remove_cv
  template<typename T> struct remove_cv
  { typedef typename remove_volatile<typename remove_const<T>::type>::type type; };
  // add_const
  template<typename T> struct add_const { typedef const T type; };
  template<typename T> struct add_const<const T> { typedef T type; };
  // add_volatile
  template<typename T> struct add_volatile { typedef volatile T type; };
  template<typename T> struct add_volatile<volatile T> { typedef T type; };
  // add_cv
  template<typename T> struct add_cv { typedef const volatile T type; };
  template<typename T> struct add_cv<const T> { typedef volatile T type; };
  template<typename T> struct add_cv<volatile T> { typedef const T type; };
  template<typename T> struct add_cv<const volatile T> { typedef T type; };
  // remove_reference
  template <typename T> struct remove_reference      { typedef T type; };
  template <typename T> struct remove_reference<T&>  { typedef T type; };
  template <typename T> struct remove_reference<T&&> { typedef T type; };
  // add_lvalue_reference
  template<typename T> struct add_lvalue_reference { typedef T& type; };
  template<> struct add_lvalue_reference<void> { typedef void type; };
  template<> struct add_lvalue_reference<const void> { typedef const void type; };
  template<> struct add_lvalue_reference<volatile void> { typedef volatile void type; };
  template<> struct add_lvalue_reference<const volatile void>  {typedef const volatile void type; };
  // add_rvalue_reference
  template<typename T> struct add_rvalue_reference { typedef T&& type; };
  template<> struct add_rvalue_reference<void> { typedef void type; };
  template<> struct add_rvalue_reference<const void> { typedef const void type; };
  template<> struct add_rvalue_reference<volatile void> { typedef volatile void type; };
  template<> struct add_rvalue_reference<const volatile void> { typedef const volatile void type; };
  // remove_pointer
  template<typename T> struct remove_pointer { typedef T type; };
  template<typename T> struct remove_pointer<T*> { typedef T type; };
  // add_pointer
  template<typename T> struct add_pointer { typedef typename remove_reference<T>::type* type; };
  // remove_extent
  template<typename T> struct remove_extent { typedef T type; };
  template<typename T> struct remove_extent<T[]> { typedef T type; };
  template<typename T, size_type N> struct remove_extent<T[N]> { typedef T type; };
  // remove_all_extents
  template<typename T> struct remove_all_extents { typedef T type; };
  template<typename T> struct remove_all_extents<T[]> { typedef typename remove_all_extents<T>::type type; };
  template<typename T, size_type N> struct remove_all_extents<T[N]> { typedef typename remove_all_extents<T>::type type; };
  // underlying_type: compiler intrinsic supported by GCC/Clang/MSVC
  template<typename T> struct underlying_type { typedef __underlying_type(T) type; };

/*
 * declval
 **/
  template <typename T> typename add_rvalue_reference<T>::type declval() noexcept;

/*
 * Boolean traits
 **/
  // Intrinsic implementations - need to be converted to pure, but simple SFINAE
  // is_base_of
  template<typename Base, typename Class> struct is_base_of : integral_constant<bool, __is_base_of(Base, Class)> {};
  // is_class
  template<typename T> struct is_class : integral_constant<bool, __is_class(typename remove_cv<T>::type)> {};
  // is_convertible
  //template<typename T, typename U> struct is_convertible : integral_constant<bool, __is_convertible(T,U)> {};
  // is_enum
  template<typename T> struct is_enum : integral_constant<bool, __is_enum(typename remove_cv<T>::type)> {};
  // is_union
  template<typename T> struct is_union : integral_constant<bool, __is_union(typename remove_cv<T>::type)> {};

  // Traits needed below
  // is_const
  template<typename> struct is_const : false_type {};
  template<typename T> struct is_const<T const> : true_type {};
  // is_convertible
  template<class From, class To>
  struct is_convertible{
    static void foo(To);
    template<class F>
    static auto test(int) -> decltype(foo(declval<F>()), true_type{});
    template<class>
    static auto test(...) -> false_type;

    static constexpr bool value = decltype(test<From>(0))::value;
    constexpr operator bool() { return value; }
  };
  // is_lvalue_reference
  template<typename> struct is_lvalue_reference : false_type {};
  template<typename T> struct is_lvalue_reference<T&> : true_type {};
  // is_nullptr
  template<typename> struct is_nullptr : false_type {};
  template<> struct is_nullptr<nullptr_type> : true_type {};
  // is_rvalue_reference
  template<typename> struct is_rvalue_reference : false_type {};
  template<typename T> struct is_rvalue_reference<T&&> : true_type {};
  // is_same
  template<typename, typename> struct is_same : false_type {};
  template<typename T> struct is_same<T,T> : true_type {};
  // is_volatile
  template<typename T> struct is_volatile : false_type {};
  template<typename T> struct is_volatile<T volatile> : true_type {};

  namespace implementation
  {
    // is_void
    template<typename> struct is_void : false_type {};
    template<> struct is_void<void> : true_type {};
    // is_integral
    template<typename> struct is_integral : false_type{};
    template<> struct is_integral<bool>               : true_type {};
    template<> struct is_integral<char>               : true_type {};
    template<> struct is_integral<signed char>        : true_type {};
    template<> struct is_integral<unsigned char>      : true_type {};
    template<> struct is_integral<wchar_t>            : true_type {};
    template<> struct is_integral<char16_t>           : true_type {};
    template<> struct is_integral<char32_t>           : true_type {};
    template<> struct is_integral<short>              : true_type {};
    template<> struct is_integral<unsigned short>     : true_type {};
    template<> struct is_integral<int>                : true_type {};
    template<> struct is_integral<unsigned int>       : true_type {};
    template<> struct is_integral<long>               : true_type {};
    template<> struct is_integral<unsigned long>      : true_type {};
    template<> struct is_integral<long long>          : true_type {};
    template<> struct is_integral<unsigned long long> : true_type {};
    // is_floating_point
    template<typename> struct is_floating_point : false_type {};
    template<> struct is_floating_point<float> : true_type {};
    template<> struct is_floating_point<double> : true_type {};
    template<> struct is_floating_point<long double> : true_type {};
    // is_pointer
    template<typename> struct is_pointer : false_type {};
    template<typename T> struct is_pointer<T*> : true_type {};
    // is_unbound_c_array for default_constructible traits
    template<typename> struct is_unbound_c_array : public false_type {};
    template<typename T> struct is_unbound_c_array<T[]> : public true_type {};
    // is_c_array
    template<typename> struct is_c_array : public false_type {};
    template<typename T> struct is_c_array<T[]> : public true_type {};
    template<typename T, size_type N> struct is_c_array<T[N]> : public true_type {};
    // is_function
    template<typename T> struct is_function : integral_constant<bool, !is_convertible<T*, const volatile void*>()> {};
    template<typename T> struct is_function<T&> : false_type {};
    template<typename T> struct is_function<T&&> : false_type {};
    // own implementation
    //template<typename> struct is_function : false_type {};
    // template<typename T, typename... Args> struct is_function<T(Args...)> : true_type {}; // normal function
    // template<typename T, typename... Args> struct is_function<T(Args...,...)> : true_type {}; // variadic function

    // is_member_function_pointer
    template<typename> struct is_member_function_pointer : false_type {};
    template <typename T, typename Class> struct is_member_function_pointer<T Class::*> : is_function<T> {};

    // own implementation - missing r-value ref for this variants?
    //template<typename T> struct is_member_function_pointer : false_type {};
    //template<typename T, typename Class, typename... Args> struct is_member_function_pointer<T (Class::*)(Args...)> : true_type {};
    //template<typename T, typename Class, typename... Args> struct is_member_function_pointer<T (Class::*)(Args...) const> : true_type {};
    //template<typename T, typename Class, typename... Args> struct is_member_function_pointer<T (Class::*)(Args...) volatile> : true_type {};
    //template<typename T, typename Class, typename... Args> struct is_member_function_pointer<T (Class::*)(Args...) const volatile> : true_type {};

  }
  // is_c_array
  template<typename T> struct is_c_array : implementation::is_c_array<typename remove_cv<T>::type> {};
  // is_floating_point
  template<typename T> struct is_floating_point : implementation::is_floating_point<typename remove_cv<T>::type> {};
  // is_function
  template<typename T> struct is_function : implementation::is_function<typename remove_cv<T>::type> {};
  // is_integral
  template<typename T> struct is_integral : implementation::is_integral<typename remove_cv<T>::type> {};

  // is_member_function_pointer
  //template<typename T> struct is_member_function_pointer : implementation::is_member_function_pointer<T const volatile> {};
  template<typename T> struct is_member_function_pointer : implementation::is_member_function_pointer<typename remove_reference<T>::type> {};
  // is_member_pointer

  // is_member_object_pointer
  //template<typename T> struct is_member_object_pointer : integral_constant<bool, is_member_pointer<T>() && !is_member_function_pointer<T>()> {};

  // is_pointer
  template<typename T> struct is_pointer : implementation::is_pointer<typename remove_cv<T>::type> {};

  // is_reference
  template<typename T> struct is_reference : integral_constant<bool, is_lvalue_reference<T>() || is_rvalue_reference<T>()> {};
  // is_signed
  template<typename T> struct is_signed : integral_constant<bool, T(-1) < T(0)> {};
  // is_unbound_c_array
  template<typename T> struct is_unbound_c_array : implementation::is_unbound_c_array<typename remove_cv<T>::type> {};
  // is_void
  template<typename T> struct is_void : implementation::is_void<typename remove_cv<T>::type> {};


/*
 * Value traits
 **/
  // rank
  template<typename T> struct rank : integral_constant<size_type, 0> {};
  template<typename T> struct rank<T[]> : integral_constant<size_type, 0> {};
  template<typename T, size_type N> struct rank<T[N]> : integral_constant<size_type, N> {};
  // extent
  template<typename T, size_type N> struct extent : integral_constant<size_type, 0> {};
  template<typename T, size_type N> struct extent<T[], N> : integral_constant<size_type, N==0 ? 0 : extent<T,N-1>::result> {};
  template<typename T, size_type N, size_type S> struct extent<T[S], N> : integral_constant<size_type, N==0 ? 0 : extent<T,N-1>::result> {};
  // nothrow
  template<typename T, typename... Args> struct is_nothrow_constructible : integral_constant<bool, noexcept(T(declval<Args>()...))> {};
  template<typename T> struct is_nothrow_default_constructible : integral_constant<bool, noexcept(declval<T>())> {};
  template<typename T> struct is_nothrow_copy_constructible : integral_constant<bool, noexcept(T(declval<T>()))> {};
  template<typename T> struct is_nothrow_move_constructible : integral_constant<bool, noexcept(T(declval<add_rvalue_reference<T>>()))> {};
  template<typename T, typename X> struct is_nothrow_assignable : integral_constant<bool, noexcept(declval<T>() = declval<X>())> {};
  template<typename T, typename X> struct is_nothrow_copy_assignable : is_nothrow_assignable<add_lvalue_reference<T>, const add_lvalue_reference<X>> {};
  template<typename T, typename X> struct is_nothrow_move_assignable : is_nothrow_assignable<add_lvalue_reference<T>, add_rvalue_reference<X>> {};
  template<typename T> struct is_nothrow_destructible : integral_constant<bool, noexcept(declval<T>().~T())> {};

  /*
 * Secondary classification
 */
 /* template<typename T> constexpr bool
  is_reference() { return is_rvalue_reference<T>() || is_lvalue_reference<T>(); }
  template<typename T> constexpr bool
  is_arithmetic() { return is_integral<T>() || is_floating_point<T>(); }
  template<typename T> constexpr bool
  is_fundamental() { return is_void<T>() || is_arithmetic<T>(); }
  template<typename T> constexpr bool
  is_member_pointer() { return is_member_object_pointer<T>() || is_member_function_pointer<T>(); }
  template<typename T> constexpr bool
  is_scalar() { return is_pointer<T>() || is_arithmetic<T>() || is_enum<T>() || is_member_pointer<T>(); }
  template<typename T> constexpr bool
  is_object() { return is_scalar<T> || is_c_array<T>() || is_union<T>() || is_class<T>(); }
  template<typename T> constexpr bool
  is_compound() { return !is_fundamental<T>(); }*/


  /*
 * Integral properties
 */
  // is_signed
  /*template<typename T>
  constexpr bool is_signed()
  { static_assert( is_arithmetic<T>(), "is_signed can only be used on arithmetic types");
    return implementation::is_signed<T>::result;
  }
  // is_unsigned
  template<typename T>
  constexpr bool is_unsigned()
  {
    static_assert( is_arithmetic<T>(), "is_unsigned can only be used on arithmetic types");
    return !implementation::is_signed<T>::result;
  }*/
  // make_signed
  // make_unsigned
  /*
 * Array properties and transformations
 */
  // rank
  /*template<typename T>
  constexpr size_type rank() { return implementation::rank<T>::result; }
  template<typename T>
  constexpr size_type extent() { return implementation::rank<T>::result; }
  template<typename T>
  constexpr size_type remove_extent() { return implementation::remove_extent<T>::result; }
  template<typename T>
  constexpr size_type remove_all_extents() { return implementation::remove_all_extents<T>::result; }*/
  /*
 * Member introspection (mostly compiler magic)
 */
  /*template<typename T>
  constexpr bool is_pod() { return __is_pod(T); }
  template<typename T>
  constexpr bool is_trivial() { return __is_trivial(T); }
  template<typename T>
  constexpr bool is_trivially_copyable() { return __has_trivial_copy(T); }
  template<typename T>
  constexpr bool is_standard_layout() { return __is_standard_layout(T); }
  // remove_all_extent scalar
  template<typename T>
  constexpr bool is_literal_type() { return __is_literal(T); }
  // remove_all_extent scalar, remove_all_extent reference
  template<typename T>
  constexpr bool is_empty() { return __is_empty(T); }
  template<typename T>
  constexpr bool is_polymorphic() { return __is_polymorphic(T); }
  template<typename T>
  constexpr bool is_abstract() { return __is_abstract(T); }
  */
  //is_constructible
  // is_default_constructible
  // is_copy_constructible
  // is_move_constructible
  // is_assignable
  // is_copy_assignable
  // is_move_assignable
  // is_destructible

  template<typename T>
  constexpr bool is_trivially_constructible() { return __has_trivial_copy(T); }
  // ^ this needs overloads for rvalue refs?
  // is_trivially_default_constructible
  // is_trivially_copy_constructible
  // is_trivially_move_constructible
  // is_trivially_assignable
  // is_trivially_copy_assignable
  // is_trivially_move_assignable
  // is_trivially_destructible



  template<typename T>
  constexpr bool has_virtual_destructor() { return __has_virtual_destructor(T); }

/*
 * Intertype relations
 */
  //template<typename T1, typename T2>
  //constexpr bool is_same() { return implementation::is_same<T1,T2>::result; }
  //template<typename Base, typename Class>
  //constexpr bool is_base_of() { return __is_base_of(Base,Class); }
  // GCC 4.8: unimplemented
  //template<typename From, typename To>
  //constexpr bool is_convertible_to() { return __is_convertible_to(From, To); }
/*
 * Alignment properties and transformations
 */
  template<typename T>
  constexpr size_type alignment_of(const T t) { return __alignof__(t); }
  // aligned_storage

  // decay
  // common_type
  // result_of

/*
 * Things not in the C++ standard
 **/
  // allocator_traits
  template<typename T>
  using pointer_type = remove_reference<T>();
}

/*
 * This little bit of code above makes any code including <initializer_list>
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
  template<class E> class initializer_list
  {
  public:
    typedef E        value_type;
    typedef const E& reference;
    typedef const E& const_reference;
    typedef kiss::size_type size_type;
    typedef const E* iterator;
    typedef const E* const_iterator;
    initializer_list();
    kiss::size_type size() const;
    const E* begin() const;
    const E* end() const;
  };
  template<class E> const E* begin(initializer_list<E> il)
  { return il.begin(); }
  template<class E> const E* end(initializer_list<E> il)
  { return il.end(); }
}
#endif

#endif
