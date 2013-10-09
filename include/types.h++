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

/*
 * references
 **/
  // is_lvalue_reference
  template<typename> struct is_lvalue_reference : false_type {};
  template<typename T> struct is_lvalue_reference<T&> : true_type {};
  // is_rvalue_reference
  template<typename> struct is_rvalue_reference : false_type {};
  template<typename T> struct is_rvalue_reference<T&&> : true_type {};

  // add_lvalue_reference
  template<typename T> struct add_lvalue_reference { using type = T&; };
  template<> struct add_lvalue_reference<void> { using type = void; };
  template<> struct add_lvalue_reference<const void> { using type = const void; };
  template<> struct add_lvalue_reference<volatile void> { using type = volatile void; };
  template<> struct add_lvalue_reference<const volatile void>  { using type = const volatile void; };
  // add_rvalue_reference
  template<typename T> struct add_rvalue_reference { using type = T&&; };
  template<> struct add_rvalue_reference<void> { using type = void; };
  template<> struct add_rvalue_reference<const void> { using type = const void; };
  template<> struct add_rvalue_reference<volatile void> { using type = volatile void; };
  template<> struct add_rvalue_reference<const volatile void> { using type = const volatile void; };

  // remove_reference
  template <typename T> struct remove_reference      { using type = T; };
  template <typename T> struct remove_reference<T&>  { using type = T; };
  template <typename T> struct remove_reference<T&&> { using type = T; };

/*
 * pointers
 **/
  // add_pointer
  template<typename T> struct add_pointer { using type = typename remove_reference<T>::type*; };

  // remove_pointer
  template<typename T> struct remove_pointer { using type = T; };
  template<typename T> struct remove_pointer<T*> { using type = T; };
  template<typename T> struct remove_pointer<T* const> { using type = T; };
  template<typename T> struct remove_pointer<T* volatile> { using type = T; };
  template<typename T> struct remove_pointer<T* const volatile> { using type = T; };

/*
 * Utility
 **/

  // conditional
  namespace implementation
  {
    template<bool, typename First, typename Second> struct conditional { using type = First; };
    template<typename First, typename Second> struct conditional<false, First, Second> { using type = Second; };
  }
  template<bool B, typename First, typename Second> using conditional = typename implementation::conditional<B, First, Second>::type;

  // declval
  template<typename T> typename add_rvalue_reference<T>::type declval() noexcept;

  // enable_if
  namespace implementation
  {
    template<bool, typename T = void> struct enable_if {};
    template<typename T> struct enable_if<true, T> { using type = T; };
  }
  template<bool Condition, typename T = void> using enable_if = typename implementation::enable_if<Condition, T>::type;

  // forward
  template<typename T>
  inline constexpr T&& forward(typename remove_reference<T>::type& t) noexcept
  { return static_cast<T&&>(t); }
  template<typename T>
  inline constexpr T&& forward(typename remove_reference<T>::type&& t) noexcept
  {
    static_assert(!is_lvalue_reference<T>::value, "An rvalue cannot be forwarded as an lvalue.");
    return static_cast<T&&>(t);
  }

  // identity
  template<typename T> using identity = T;

  // is_same
  template<typename, typename> struct is_same : false_type {};
  template<typename T> struct is_same<T,T> : true_type {};

  // move
  template<typename T>
  inline constexpr typename remove_reference<T>::type&& move(T&& t) noexcept
  { return static_cast<typename remove_reference<T>::type&&>(t); }

/*
 * const-volatile
 **/
  // is_const
  template<typename> struct is_const : false_type {};
  template<typename T> struct is_const<T const> : true_type {};
  // is_volatile
  template<typename T> struct is_volatile : false_type {};
  template<typename T> struct is_volatile<T volatile> : true_type {};

  // add_const
  template<typename T> struct add_const { using type = const T; };
  // add_volatile
  template<typename T> struct add_volatile { using type = volatile T; };
  // add_cv
  template<typename T> struct add_cv { using type = const volatile T; };

  // remove_const
  template<typename T> struct remove_const { using type = T; };
  template<typename T> struct remove_const<const T> { using type = T; };
  // remove_volatile
  template<typename T> struct remove_volatile { using type = T; };
  template<typename T> struct remove_volatile<volatile T> { using type = T; };
  // remove_cv
  template<typename T> struct remove_cv { using type = typename remove_volatile<typename remove_const<T>::type>::type; };

/*
 * Primary categories
 **/
  // is_void
  namespace implementation
  {
    template<typename> struct is_void : false_type {};
    template<> struct is_void<void> : true_type {};
  }
  template<typename T> struct is_void : implementation::is_void<typename remove_cv<T>::type> {};
  // is_integral
  namespace implementation
  {
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
  }
  template<typename T> struct is_integral : implementation::is_integral<typename remove_cv<T>::type> {};
  // is_floating_point
  namespace implementation
  {
    template<typename> struct is_floating_point : false_type {};
    template<> struct is_floating_point<float> : true_type {};
    template<> struct is_floating_point<double> : true_type {};
    template<> struct is_floating_point<long double> : true_type {};
  }
  template<typename T> struct is_floating_point : implementation::is_floating_point<typename remove_cv<T>::type> {};
  // is_c_array
  namespace implementation
  {
    template<typename> struct is_c_array : public false_type {};
    template<typename T> struct is_c_array<T[]> : public true_type {};
    template<typename T, size_type N> struct is_c_array<T[N]> : public true_type {};
  }
  template<typename T> struct is_c_array : implementation::is_c_array<typename remove_cv<T>::type> {};
  // is_pointer
  namespace implementation
  {
    template<typename> struct is_pointer : false_type {};
    template<typename T> struct is_pointer<T*> : true_type {};
  }
  template<typename T> struct is_pointer : implementation::is_pointer<typename remove_cv<T>::type> {};
//TODO INTRINSIC is_enum
  template<typename T> struct is_enum : integral_constant<bool, __is_enum(typename remove_cv<T>::type)> {};
 //TODO INTRINSIC is_union
  template<typename T> struct is_union : integral_constant<bool, __is_union(typename remove_cv<T>::type)> {};
//TODO INTRINSIC is_class
  template<typename T> struct is_class : integral_constant<bool, __is_class(typename remove_cv<T>::type)> {};
  // is_function
  template<typename> struct is_function : public false_type { };
  template<typename Result, typename... ArgTypes> struct is_function<Result(ArgTypes...)> : public true_type { };
  template<typename Result, typename... ArgTypes> struct is_function<Result(ArgTypes..., ...)> : public true_type { };
  // is_member_function_pointer
  namespace implementation
  {
    template<typename> struct is_member_function_pointer : false_type {};
    template <typename T, typename Class> struct is_member_function_pointer<T Class::*> : is_function<typename remove_cv<T>::type> {};
  }
  template<typename T> struct is_member_function_pointer : implementation::is_member_function_pointer<typename remove_reference<T>::type> {};
  // is_member_object_pointer
  namespace implementation
  {
    template<typename> struct is_member_object_pointer : false_type {};
    template<typename T, typename Class> struct is_member_object_pointer<T Class::*> : integral_constant<bool, !is_function<T>::value> {};
  }
  template<typename T> struct is_member_object_pointer : implementation::is_member_object_pointer<typename remove_cv<T>::type> {};
  // is_nullptr
  namespace implementation
  {
    template<typename> struct is_nullptr : false_type {};
    template<> struct is_nullptr<nullptr_type> : true_type {};
  }
  template<typename T> struct is_nullptr : implementation::is_nullptr<typename remove_cv<T>::type> {};

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
  namespace implementation
  {
    template<typename> struct is_member_pointer : false_type {};
    template<typename T, typename Class> struct is_member_pointer<T Class::*> : true_type {};
  }
  template<typename T> struct is_member_pointer : implementation::is_member_pointer<typename remove_cv<T>::type> {};
  // is_scalar
  template<typename T> struct is_scalar : integral_constant<bool, is_pointer<T>() || is_nullptr<T>() || is_arithmetic<T>() || is_enum<T>() || is_member_pointer<T>()> {};
  // is_object
  template<typename T> struct is_object : integral_constant<bool, is_scalar<T>() || is_c_array<T>() || is_union<T>() || is_class<T>()> {};
  // is_compund
  template<typename T> struct is_compound : integral_constant<bool, !is_fundamental<T>()> {};

/*
 * Miscellaneous
 **/
  // addressof
  template<typename T> T* addressof(T& arg)
  { return reinterpret_cast<T*>(&const_cast<char&>(reinterpret_cast<const volatile char&>(arg))); }

  // common_type
  template<typename ...T> struct common_type;
  template<typename T> struct common_type<T> { using type = T; };
  template<typename T, typename U> struct common_type<T, U> { using type = decltype(true ? declval<T>() : declval<U>()); };
  template<typename T, typename U, typename... V> struct common_type<T, U, V...> { using type = typename common_type<typename common_type<T, U>::type, V...>::type; };

  // is_convertible
  namespace implementation
  {
    template<typename From, typename To> struct is_convertible;
    template<> struct is_convertible<void, void> : true_type {};
    template<typename To> struct is_convertible<void, To> : false_type {};
    template<typename From> struct is_convertible<From, void> : false_type {};
    template<typename From, typename To>
    struct is_convertible
    {
    private:
      static void foo(To);
      template<typename F>
      static auto test(int) -> decltype(foo(declval<F>()), void(), true_type{});
      template<typename>
      static auto test(...) -> false_type;
    public:
      static constexpr bool value = decltype(test<From>(0))::value;
      constexpr operator bool() { return value; }
    };
  }
  template<typename From, typename To> struct is_convertible : implementation::is_convertible<From, To> {};
  /*template<typename From, typename To> struct is_convertible : conditional<is_void<From>::value || is_void<To>::value,
                                                                           conditional<is_void<To>::value && is_void<From>::value,
                                                                                       true_type,
                                                                                       false_type>,
                                                                           implementation::is_convertible<From, To>> {};*/
  /*template<> struct is_convertible<void, void> : true_type {};
  template<> struct is_convertible<void, const void> : true_type {};
  template<> struct is_convertible<void, volatile void> : true_type {};
  template<> struct is_convertible<void, const volatile void> : true_type {};
  template<> struct is_convertible<const void, void> : true_type {};
  template<> struct is_convertible<const void, const void> : true_type {};
  template<> struct is_convertible<const void, volatile void> : true_type {};
  template<> struct is_convertible<const void, const volatile void> : true_type {};
  template<> struct is_convertible<const volatile void, void> : true_type {};
  template<> struct is_convertible<const volatile void, const void> : true_type {};
  template<> struct is_convertible<const volatile void, volatile void> : true_type {};
  template<> struct is_convertible<const volatile void, const volatile void> : true_type {};
  template<typename T> struct is_convertible<void, T> : false_type {};
  template<typename T> struct is_convertible<const void, T> : false_type {};
  template<typename T> struct is_convertible<volatile void, T> : false_type {};
  template<typename T> struct is_convertible<const volatile void, T> : false_type {};*/
  /*template<typename T> struct is_convertible<T, void> : false_type {};
  template<typename T> struct is_convertible<T, const void> : false_type {};
  template<typename T> struct is_convertible<T, volatile void> : false_type {};
  template<typename T> struct is_convertible<T, const volatile void> : false_type {};*/

  //template<typename T> struct is_convertible<Array[], Array[]> : false_type{};
  template<typename T, size_type N> struct is_convertible<T[N], T[N]> : false_type{}; // !is_convertible<Array, Array>

  // is_complete
  template<typename T, typename... Ts>
  struct is_complete
  {
  private:
    template<unsigned...> static constexpr void foo();
    template<typename... Us>
    static auto test(int) -> decltype(foo<sizeof(Us)...>(), void(), true_type{});
    template<typename...>
    static auto test(...) -> false_type;
  public:
    static constexpr bool value = decltype(test<T, Ts...>(0))::value;
    constexpr operator bool() { return value; }
  };

//TODO is_polymorphic_functor
  //    template<typename T>
  //    struct is_polymorphic_functor
  //    {
  //    private:
  //      template<typename U, typename V>
  //      static auto test(U *u, V* v) -> decltype((*u)(*v), void(), false_type); // error here
  //      template<typename>
  //      static auto test(...) -> true_type;
  //      struct foo {};
  //    public:
  //      static const bool value = decltype(test((T*)nullptr))::value;
  //    };

//TODO result_of
  template<typename> struct result_of;
  template<typename F, typename... ArgTypes>
  struct result_of<F(ArgTypes...)> { using type = decltype(declval<F>()(declval<ArgTypes>()...)); };
  //template<typename> struct result_of;
  //template<typename T> struct result_of<T> { using type = T; };
  //template<typename T, typename Class, typename Thing>
  //struct result_of<T Class::*(Thing)> { using type = conditional<is_const<typename remove_pointer<Thing>::type>::value,
  //                                                               typename add_lvalue_reference<typename add_const<T>::type>::type, typename add_rvalue_reference<T>::type>; };
  //template<typename T, typename Class, typename... ArgTypes>
  //struct result_of<T Class::*(ArgTypes...)> { using type = void; }; // WRONG
  //template<typename T, typename Class, typename... ArgTypes>
  //struct result_of<T const Class::*(ArgTypes...)> { using type = T; };
  //template<typename Function, typename... ArgTypes>
  //struct result_of<Function(ArgTypes...)> { using type = decltype(declval<typename remove_cv<typename remove_reference<Function>::type>::type>()(declval<ArgTypes>()...)); };

/*
 * Signedness
 **/
  // make_signed
  namespace implementation
  {
    template<typename T> struct make_signed { using type = T; };
    template<> struct make_signed<char> { using type = signed char; };
    template<> struct make_signed<unsigned char> { using type = signed char; };
    template<> struct make_signed<unsigned short> { using type = signed short; };
    template<> struct make_signed<unsigned int> { using type = signed int; };
    template<> struct make_signed<unsigned long> { using type = signed long; };
    template<> struct make_signed<unsigned long long> { using type = signed long long; };
  }
  template<typename T> struct make_signed { using type = typename implementation::make_signed<typename remove_cv<T>::type>::type; };
  template<typename T> struct make_signed<const T> { using type = const typename implementation::make_signed<typename remove_cv<T>::type>::type; };
  template<typename T> struct make_signed<volatile T> { using type = volatile typename implementation::make_signed<typename remove_cv<T>::type>::type; };
  template<typename T> struct make_signed<const volatile T> { using type = const volatile typename implementation::make_signed<typename remove_cv<T>::type>::type; };
  // make_unsigned
  namespace implementation
  {
    template<typename T> struct make_unsigned { using type = T; };
    template<> struct make_unsigned<char> { using type = unsigned char; };
    template<> struct make_unsigned<signed char> { using type = unsigned char; };
    template<> struct make_unsigned<signed short> { using type = unsigned short; };
    template<> struct make_unsigned<signed int> { using type = unsigned int; };
    template<> struct make_unsigned<signed long> { using type = unsigned long; };
    template<> struct make_unsigned<signed long long> { using type = unsigned long long; };
  }
  template<typename T> struct make_unsigned { using type = typename implementation::make_unsigned<typename remove_cv<T>::type>::type; };
  template<typename T> struct make_unsigned<const T> { using type = typename implementation::make_unsigned<typename remove_cv<T>::type>::type; };
  template<typename T> struct make_unsigned<volatile T> { using type = typename implementation::make_unsigned<typename remove_cv<T>::type>::type; };
  template<typename T> struct make_unsigned<const volatile T> { using type = typename implementation::make_unsigned<typename remove_cv<T>::type>::type; };
  // is_signed
  namespace implementation
  {
    template<typename T> struct is_signed : integral_constant<bool, T(-1) < T(0)> {};
  }
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
  template<typename T> struct remove_extent { using type = T; };
  template<typename T> struct remove_extent<T[]> { using type = T; };
  template<typename T, size_type N> struct remove_extent<T[N]> { using type = T; };
  // remove_all_extents
  template<typename T> struct remove_all_extents { using type = T; };
  template<typename T> struct remove_all_extents<T[]> { using type = typename remove_all_extents<T>::type; };
  template<typename T, size_type N> struct remove_all_extents<T[N]> { using type = typename remove_all_extents<T>::type; };

  // decay
  template <class T>
  struct decay
  {
  private:
    using U = typename remove_reference<T>::type;
  public:
    using type = conditional<is_c_array<U>::value,
                             typename remove_extent<U>::type*,
                             conditional<is_function<U>::value,
                                         typename add_pointer<U>::type,
                                         typename remove_cv<U>::type>>;
  };

/*
 * Memory properties
 **/
//TODO INTRINSIC is_literal_type
  template<typename T> struct is_literal_type : integral_constant<bool, __is_literal_type(T)> {};
//TODO INTRINSIC is_pod
  template<typename T> struct is_pod : integral_constant<bool, __is_pod(T)> {};
//TODO INTRINSIC is_trivial
  template<typename T> struct is_trivial : integral_constant<bool, __is_trivial(T)> {};
//TODO INTRINSIC is_trivially_copyable
  // not in GCC 4.8.1
  //template<typename T> struct is_trivially_copyable : integral_constant<bool, __is_trivially_copyable(T)> {};
//TODO INTRINSIC is_standard_layout
  template<typename T> struct is_standard_layout : integral_constant<bool, __is_standard_layout(T)> {};

/*
 * Construction, destruction, assignment, copy, and move properties
 **/
  // is_constructible
  template<typename T, typename... Args> struct is_constructible
  {
    static_assert(is_complete<T, Args...>(), "is_constructible can only be used with complete types");
    template<typename F>
    static auto test(int) -> decltype(T(declval<Args>()...), void(), true_type{});
    template<typename>
    static auto test(...) -> false_type;

    static constexpr bool value = decltype(test<T>(0))::value;
    constexpr operator bool() { return value; }
  };
  // is_default_constructible
  template<typename T> struct is_default_constructible : is_constructible<T> {};
  /*{
    static void foo(T = T());
    template<typename F>
    static auto test(int) -> decltype(foo(), void(), true_type{});
    template<typename>
    static auto test(...) -> false_type;

    constexpr operator bool() { return decltype(test<T>(0))::value; }
  };*/
  // is_copy_constructible
  template<typename T> struct is_copy_constructible : is_convertible<T,T> {};
//TODO is_move_constructible
  template<typename T> struct is_move_constructible
  {
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
  // not in GCC 4.8.1
  //template<typename T, typename... ArgTypes> struct is_trivially_constructible : integral_constant<bool, __is_trivially_constructible(T, ArgTypes...)> {};
//TODO is_trivially_default_constructible
  //template<typename T> struct is_trivially_default_constructible : is_trivially_constructible<T> {};
//TODO is_trivially_copy_constructible
  //template<typename T> struct is_trivially_copy_constructible :  is_trivially_constructible<T, const typename add_lvalue_reference<T>::type> {};
//TODO is_trivially_move_constructible
  //template<typename T> struct is_trivially_move_constructible : is_trivially_constructible<T, const typename add_rvalue_reference<T>::type> {};

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
  template<typename T> struct is_nothrow_move_constructible : integral_constant<bool, noexcept(T(declval<typename add_rvalue_reference<T>::type>()))> {};
  // is_nothrow_assignable
  template<typename T, typename X> struct is_nothrow_assignable : integral_constant<bool, noexcept(declval<T>() = declval<X>())> {};
  // is_nothrow_copy_assignable
  template<typename T> struct is_nothrow_copy_assignable : is_nothrow_assignable<typename add_lvalue_reference<T>::type, const typename add_lvalue_reference<T>::type> {};
  // is_nothrow_move_assignable
  template<typename T> struct is_nothrow_move_assignable : is_nothrow_assignable<typename add_lvalue_reference<T>::type, typename add_rvalue_reference<T>::type> {};
  // is_nothrow_destructible
//TODO needs fallback?
  template<typename T> struct is_nothrow_destructible : integral_constant<bool, noexcept(declval<T&>().~T())> {};

/*
 * Inheritance properties
 **/
//TODO INTRINSIC underlying_type
  template<typename T> struct underlying_type { using type = __underlying_type(T); };
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
  // alignment_of
  template<typename T>
  struct alignment_of : integral_constant<size_type, alignof(typename remove_all_extents<T>::type)> {};
  // get the alignment of a (reference) variable as a member
  namespace implementation
  {
    template<typename T> struct member { T t; };
  }
  template<typename T> struct member_alignment_of : integral_constant<size_type, alignof(implementation::member<T>)> {};
//TODO aligned_storage - needs default argument
  template<size_type size, size_type alignment = member_alignment_of<long double>::value>
  struct aligned_storage
  { using type = struct { alignas(alignment) unsigned char data[size]; }; };
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

#endif
