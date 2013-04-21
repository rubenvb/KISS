/**
 * Written in 2013 by Ruben Van Boxem <vanboxem.ruben@gmail.com>
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
 * integral_constant, true_type, false_type
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
 * reference-pointer transformations
 **/
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

  // remove_reference
  template <typename T> struct remove_reference      { typedef T type; };
  template <typename T> struct remove_reference<T&>  { typedef T type; };
  template <typename T> struct remove_reference<T&&> { typedef T type; };

  // add_pointer
  template<typename T> struct add_pointer { typedef typename remove_reference<T>::type* type; };

  // remove_pointer
  template<typename T> struct remove_pointer { typedef T type; };
  template<typename T> struct remove_pointer<T*> { typedef T type; };

/*
 * Miscellaneous
 **/
  namespace implementation
  {
    // conditional
    template<bool, typename First, typename Second> struct conditional { typedef First type; };
    template<typename First, typename Second> struct conditional<false, First, Second> { typedef Second type; };
  }
  // conditional
  template<bool B, typename First, typename Second> using conditional = typename implementation::conditional<B, First, Second>::type;
  // declval
  template<typename T> typename add_rvalue_reference<T>::type declval() noexcept;
//TODO decay
  // common_type
  template<typename ...T> struct common_type;
  template<typename T> struct common_type<T> { typedef T type; };
  template <typename T, typename U> struct common_type<T, U> { typedef decltype(true ? declval<T>() : declval<U>()) type; };
  template <typename T, typename U, typename... V> struct common_type<T, U, V...> { typedef typename common_type<typename common_type<T, U>::type, V...>::type type; };
//TODO result_of
  //template <typename Function, typename... Args> struct result_of<Function(Args...)>{ typedef decltype(declval<Fn>()(declval<ArgTypes>()...)) type; };

  // is_same
  template<typename, typename> struct is_same : false_type {};
  template<typename T> struct is_same<T,T> : true_type {};

/*
 * KISS traits - useful but not present in C++11
 **/
  // is_convertible
  template<typename From, typename To>
  struct is_convertible{
    static void foo(To);
    template<typename F>
    static auto test(int) -> decltype(foo(declval<F>()), void(), true_type{});
    template<typename>
    static auto test(...) -> false_type;

    constexpr operator bool() { return decltype(test<From>(0))(); }
  };
  // is_complete
  template<typename T, typename... Ts>
  struct is_complete{
    template<unsigned...> void foo();
    template<typename... Us>
    static auto test(int) -> decltype(foo<sizeof(Us)...>(), void(), true_type{});
    template<typename...>
    static auto test(...) -> false_type;

    constexpr operator bool() { return decltype(test<T, Ts...>(0))(); }
  };

  // is_nullptr
  template<typename> struct is_nullptr : false_type {};
  template<> struct is_nullptr<nullptr_type> : true_type {};

/*
 * const-volatile identification
 **/
  // is_const
  template<typename> struct is_const : false_type {};
  template<typename T> struct is_const<T const> : true_type {};
  // is_volatile
  template<typename T> struct is_volatile : false_type {};
  template<typename T> struct is_volatile<T volatile> : true_type {};

/*
 * const-volatile transformations
 **/
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

  // remove_const
  template<typename T> struct remove_const { typedef T type; };
  template<typename T> struct remove_const<const T> { typedef T type; };
  // remove_volatile
  template<typename T> struct remove_volatile { typedef T type; };
  template<typename T> struct remove_volatile<volatile T> { typedef T type; };
  // remove_cv
  template<typename T> struct remove_cv
  { typedef typename remove_volatile<typename remove_const<T>::type>::type type; };

/*
 * Primary type categories
 **/
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
    // is_c_array
    template<typename> struct is_c_array : public false_type {};
    template<typename T> struct is_c_array<T[]> : public true_type {};
    template<typename T, size_type N> struct is_c_array<T[N]> : public true_type {};
    // is_pointer
    template<typename> struct is_pointer : false_type {};
    template<typename T> struct is_pointer<T*> : true_type {};
    // is_function
    template<typename T> struct is_function : integral_constant<bool, !is_convertible<T*, const volatile void*>()> {};
    template<typename T> struct is_function<T&> : false_type {};
    template<typename T> struct is_function<T&&> : false_type {};
  }
  // is_void
  template<typename T> struct is_void : implementation::is_void<typename remove_cv<T>::type> {};
  // is_integral
  template<typename T> struct is_integral : implementation::is_integral<typename remove_cv<T>::type> {};
  // is_floating_point
  template<typename T> struct is_floating_point : implementation::is_floating_point<typename remove_cv<T>::type> {};
  // is_c_array
  template<typename T> struct is_c_array : implementation::is_c_array<typename remove_cv<T>::type> {};
  // is_pointer
  template<typename T> struct is_pointer : implementation::is_pointer<typename remove_cv<T>::type> {};
  // is_lvalue_reference
  template<typename> struct is_lvalue_reference : false_type {};
  template<typename T> struct is_lvalue_reference<T&> : true_type {};
  // is_rvalue_reference
  template<typename> struct is_rvalue_reference : false_type {};
  template<typename T> struct is_rvalue_reference<T&&> : true_type {};
//TODO INTRINSIC is_enum
  template<typename T> struct is_enum : integral_constant<bool, __is_enum(typename remove_cv<T>::type)> {};
//TODO INTRINSIC is_union
  template<typename T> struct is_union : integral_constant<bool, __is_union(typename remove_cv<T>::type)> {};
//TODO INTRINSIC is_class
  template<typename T> struct is_class : integral_constant<bool, __is_class(typename remove_cv<T>::type)> {};
  // is_function
  template<typename T> struct is_function : implementation::is_function<typename remove_cv<T>::type> {};
  namespace implementation
  {
    // is_member_object_pointer
    template<typename> struct is_member_object_pointer : false_type {};
    template<typename T, typename Class> struct is_member_object_pointer<T Class::*> : integral_constant<bool, !is_function<T>()> {};
    // is_member_function_pointer
    template<typename> struct is_member_function_pointer : false_type {};
    template <typename T, typename Class> struct is_member_function_pointer<T Class::*> : is_function<T> {};
  }
  // is_member_object_pointer
  template<typename T> struct is_member_object_pointer : implementation::is_member_object_pointer<typename remove_reference<T>::type> {};
  // is_member_function_pointer
  template<typename T> struct is_member_function_pointer : implementation::is_member_function_pointer<typename remove_reference<T>::type> {};

/*
 * Composite type categories
 **/
  // is_reference
  template<typename T> struct is_reference : integral_constant<bool, is_lvalue_reference<T>() || is_rvalue_reference<T>()> {};
  //is_arithmetic
  template<typename T> struct is_arithmetic : integral_constant<bool, is_floating_point<T>() || is_integral<T>()> {};
  // is_fundamental
  template<typename T> struct is_fundamental : integral_constant<bool, is_void<T>() || is_nullptr<T>() || is_arithmetic<T>()> {};
  // is_member_pointer
  template<typename T> struct is_member_pointer : integral_constant<bool, is_member_function_pointer<T>() || is_member_object_pointer<T>()> {};
  // is_scalar
  template<typename T> struct is_scalar : integral_constant<bool, is_pointer<T>() || is_arithmetic<T>() || is_enum<T>() || is_member_pointer<T>()> {};
  // is_object
  template<typename T> struct is_object : integral_constant<bool, is_scalar<T>() || is_c_array<T>() || is_union<T>() || is_class<T>()> {};
  // is_compund
  template<typename T> struct is_compound : integral_constant<bool, !is_fundamental<T>()> {};

/*
 * Signedness
 **/
  namespace implementation
  {
    // make_signed
    template<typename T> struct make_signed { typedef T type; };
    template<> struct make_signed<char> { typedef signed char type; };
    template<> struct make_signed<unsigned char> { typedef signed char type; };
    template<> struct make_signed<unsigned short> { typedef signed short type; };
    template<> struct make_signed<unsigned int> { typedef signed int type; };
    template<> struct make_signed<unsigned long> { typedef signed long type; };
    template<> struct make_signed<unsigned long long> { typedef signed long long type; };
    // make_unsigned
    template<typename T> struct make_unsigned { typedef T type; };
    template<> struct make_unsigned<char> { typedef unsigned char type; };
    template<> struct make_unsigned<signed char> { typedef unsigned char type; };
    template<> struct make_unsigned<signed short> { typedef unsigned short type; };
    template<> struct make_unsigned<signed int> { typedef unsigned int type; };
    template<> struct make_unsigned<signed long> { typedef unsigned long type; };
    template<> struct make_unsigned<signed long long> { typedef unsigned long long type; };
    // is_signed
    template<typename T> struct is_signed : integral_constant<bool, T(-1) < T(0)> {};
  }
  // make_signed
  template<typename T> struct make_signed { typedef typename implementation::make_signed<typename remove_cv<T>::type>::type type; };
  template<typename T> struct make_signed<const T> { typedef const typename implementation::make_signed<typename remove_cv<T>::type>::type type; };
  template<typename T> struct make_signed<volatile T> { typedef volatile typename implementation::make_signed<typename remove_cv<T>::type>::type type; };
  template<typename T> struct make_signed<const volatile T> { typedef const volatile typename implementation::make_signed<typename remove_cv<T>::type>::type type; };
  // make_unsigned
  template<typename T> struct make_unsigned { typedef typename implementation::make_unsigned<typename remove_cv<T>::type>::type type; };
  template<typename T> struct make_unsigned<const T> { typedef typename implementation::make_unsigned<typename remove_cv<T>::type>::type type; };
  template<typename T> struct make_unsigned<volatile T> { typedef typename implementation::make_unsigned<typename remove_cv<T>::type>::type type; };
  template<typename T> struct make_unsigned<const volatile T> { typedef typename implementation::make_unsigned<typename remove_cv<T>::type>::type type; };
  // is_signed
  template<typename T> struct is_signed : conditional<is_arithmetic<T>::value, implementation::is_signed<T>, false_type> {};

/*
 * Array properties and transformations
 **/
  // rank
  template<typename T> struct rank : integral_constant<size_type, 0> {};
  template<typename T> struct rank<T[]> : integral_constant<size_type, 0> {};
  template<typename T, size_type N> struct rank<T[N]> : integral_constant<size_type, N> {};
  // extent
  template<typename T, size_type N> struct extent : integral_constant<size_type, 0> {};
  template<typename T, size_type N> struct extent<T[], N> : integral_constant<size_type, N==0 ? 0 : extent<T,N-1>::result> {};
  template<typename T, size_type N, size_type S> struct extent<T[S], N> : integral_constant<size_type, N==0 ? 0 : extent<T,N-1>::result> {};

  // remove_extent
  template<typename T> struct remove_extent { typedef T type; };
  template<typename T> struct remove_extent<T[]> { typedef T type; };
  template<typename T, size_type N> struct remove_extent<T[N]> { typedef T type; };
  // remove_all_extents
  template<typename T> struct remove_all_extents { typedef T type; };
  template<typename T> struct remove_all_extents<T[]> { typedef typename remove_all_extents<T>::type type; };
  template<typename T, size_type N> struct remove_all_extents<T[N]> { typedef typename remove_all_extents<T>::type type; };

/*
 * Memory properties
 **/
//TODO is_literal
  template<typename T> struct is_literal_type : false_type {};
  // is_pod
  template<typename T> struct is_pod : integral_constant<bool, __is_pod(T)> {};
  // is_trivial
  template<typename T> struct is_trivial : integral_constant<bool, __is_trivial(T)> {};
  // is_trivially_copyable
  template<typename T> struct is_trivially_copyable : integral_constant<bool, __has_trivial_copy(T)> {};
  // is_standard_layout
  template<typename T> struct is_standard_layout : integral_constant<bool, __is_standard_layout(T)> {};

/*
 * Construction, destruction, assignment, copy, and move properties
 **/
//TODO is_constructible
  template<typename T, typename... Args> struct is_constructible
  {
    static_assert(is_complete<T>() && is_complete<Args...>(), "is_constructible can only be used with complete types");
    template<typename F>
    static auto test(int) -> decltype(T(declval<Args>()...), void(), true_type{});
    template<typename>
    static auto test(...) -> false_type;

    constexpr operator bool() { return decltype(test<T>(0))(); }
  };
  // is_default_constructible
  template<typename T> struct is_default_constructible
  {
    static void foo(T = T());
    template<typename F>
    static auto test(int) -> decltype(foo(), void(), true_type{});
    template<typename>
    static auto test(...) -> false_type;

    constexpr operator bool() { return decltype(test<T>(0))(); }
  };
// is_copy_constructible
  template<typename T> struct is_copy_constructible : is_convertible<T,T> {};
//TODO is_move_constructible
  template<typename T> struct is_move_constructible
  {
    static void foo(T);
    template<typename F>
    static auto test(int) -> decltype(T(declval<typename add_rvalue_reference<F>::type>()), void(), true_type{});
    template<typename>
    static auto test(...) -> false_type;

    constexpr operator bool() { return decltype(test<T>(0))(); }
  };

//TODO is_destructible
  template<typename T> struct is_destructible : false_type {};

//TODO is_assignable
  template<typename T, typename U> struct is_assignable : false_type
  { static_assert(is_complete<T>() && is_complete<U>(), "is_assignable can only be used with complete types"); };
  // is_copy_assignable
  template<typename T> struct is_copy_assignable : is_assignable<T&, const T&>
  { static_assert(is_complete<T>(), "is_copy_assignable can only be used with a complete type"); };
  // is_move_assignable
  template<typename T> struct is_move_assignable : is_assignable<T&, T&&>
  { static_assert(is_complete<T>(), "is_move_assignable can only be used with a complete type"); };

//TODO is_trivially_constructible
  template<typename> struct is_trivially_constructible : false_type {};
//TODO is_trivially_default_constructible
  template<typename> struct is_trivially_default_constructible : false_type {};
//TODO is_trivially_copy_constructible
  template<typename> struct is_trivially_copy_constructible : false_type {};
//TODO is_trivially_move_constructible
  template<typename> struct is_trivially_move_constructible : false_type {};

//TODO is_trivially_assignable
  template<typename> struct is_trivially_assignable : false_type {};
//TODO is_trivially_copy_assignable
  template<typename> struct is_trivially_copy_assignable : false_type {};
//TODO is_trivially_move_assignable
  template<typename> struct is_trivially_move_assignable : false_type {};

//TODO is_trivially_destructible
  template<typename> struct is_trivially_default_destructible : false_type {};

  // is_nothrow_constructible
  template<typename T, typename... Args> struct is_nothrow_constructible : integral_constant<bool, noexcept(T(declval<Args>()...))> {};
  // is_nothrow_default_constructible
  template<typename T> struct is_nothrow_default_constructible : integral_constant<bool, noexcept(declval<T>())> {};
  // is_nothrow_copy_constructible
  template<typename T> struct is_nothrow_copy_constructible : integral_constant<bool, noexcept(T(declval<T>()))> {};
  // is_nothrow_move_constructible
  template<typename T> struct is_nothrow_move_constructible : integral_constant<bool, noexcept(T(declval<add_rvalue_reference<T>>()))> {};
  // is_nothrow_assignable
  template<typename T, typename X> struct is_nothrow_assignable : integral_constant<bool, noexcept(declval<T>() = declval<X>())> {};
  // is_nothrow_copy_assignable
  template<typename T, typename X> struct is_nothrow_copy_assignable : is_nothrow_assignable<add_lvalue_reference<T>, const add_lvalue_reference<X>> {};
  // is_nothrow_move_assignable
  template<typename T, typename X> struct is_nothrow_move_assignable : is_nothrow_assignable<add_lvalue_reference<T>, add_rvalue_reference<X>> {};
  // is_nothrow_destructible
//TODO needs fallback?
  template<typename T> struct is_nothrow_destructible : integral_constant<bool, noexcept(declval<T&>().~T())> {};

/*
 * Inheritance properties
 **/
//TODO INTRINSIC underlying_type
  template<typename T> struct underlying_type { typedef __underlying_type(T) type; };
//TODO INTRINSIC has_virtual_destructor
  template<typename T> struct has_virtual_destructor : integral_constant<bool, __has_virtual_destructor(T)> {};
//TODO INTRINSIC is_base_of
  template<typename Base, typename Class> struct is_base_of : integral_constant<bool, __is_base_of(Base, Class)> {};
  // this fails for private/virtual inheritance, intrinsic required
  //template<typename Base, typename Class> struct is_base_of
  //{
  //  static void foo(Base*);
  //  template<class F>
  //  static auto test(int) -> decltype(foo(declval<F*>()), true_type{});
  //  template<class>
  //  static auto test(...) -> false_type;
  //
  //  static constexpr bool value = decltype(test<Class>(0))();
  //  constexpr operator bool() { return value; }
  //};
  // is_empty
  template<typename T> struct is_empty : integral_constant<bool, __is_empty(T)> {};
  // is_polymorphic
  template<typename T> struct is_polymorphic : integral_constant<bool, __is_polymorphic(T)> {};
  // is_abstract
  template<typename T> struct is_abstract : integral_constant<bool, __is_abstract(T)> {};

/*
 * Alignment
 */
  template<typename T>
  constexpr size_type alignment_of(const T t) { return __alignof__(t); }
  // aligned_storage
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
  template<typename E> class initializer_list
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
  template<typename E> const E* begin(initializer_list<E> il)
  { return il.begin(); }
  template<typename E> const E* end(initializer_list<E> il)
  { return il.end(); }
}
#endif

#endif
