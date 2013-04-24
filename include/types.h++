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

/*
 * integral_constant, true_type, false_type
 **/
  template<typename T, T valueT>
  struct integral_constant
  {
    static constexpr T value = valueT;
    using type = integral_constant<T,value>;
    constexpr operator T() { return value; }
  };
  // true_type/false_type
  using true_type = integral_constant<bool, true>;
  using false_type = integral_constant<bool, false>;

/*
 * reference-pointer transformations
 **/
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

  // add_pointer
  template<typename T> struct add_pointer { using type = typename remove_reference<T>::type*; };

  // remove_pointer
  template<typename T> struct remove_pointer { using type = T; };
  template<typename T> struct remove_pointer<T*> { using type = T; };

/*
 * Miscellaneous
 **/
  namespace implementation
  {
    // conditional
    template<bool, typename First, typename Second> struct conditional { using type = First; };
    template<typename First, typename Second> struct conditional<false, First, Second> { using type = Second; };
  }
  // conditional
  template<bool B, typename First, typename Second> using conditional = typename implementation::conditional<B, First, Second>::type;
  // declval
  template<typename T> typename add_rvalue_reference<T>::type declval() noexcept;
  // common_type
  template<typename ...T> struct common_type;
  template<typename T> struct common_type<T> { using type = T; };
  template <typename T, typename U> struct common_type<T, U> { using type = decltype(true ? declval<T>() : declval<U>()); };
  template <typename T, typename U, typename... V> struct common_type<T, U, V...> { using type = typename common_type<typename common_type<T, U>::type, V...>::type; };
//TODO result_of
  template <typename Function, typename... Args> struct result_of{ using type = decltype(declval<Function>()(declval<Args>()...)); };

  // is_same
  template<typename, typename> struct is_same : false_type {};
  template<typename T> struct is_same<T,T> : true_type {};

/*
 * KISS traits - useful but not present in C++11
 **/
  // is_convertible
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
    constexpr operator bool() { return decltype(test<From>(0))(); }
  };
  // is_complete
  template<typename T, typename... Ts>
  struct is_complete
  {
  private:
    template<unsigned...> void foo();
    template<typename... Us>
    static auto test(int) -> decltype(foo<sizeof(Us)...>(), void(), true_type{});
    template<typename...>
    static auto test(...) -> false_type;
  public:
    constexpr operator bool() { return decltype(test<T, Ts...>(0))(); }
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
  //      static const bool value = decltype(test((T*)nullptr))();
  //    };

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
    template<typename T> struct make_signed { using type = T; };
    template<> struct make_signed<char> { using type = signed char; };
    template<> struct make_signed<unsigned char> { using type = signed char; };
    template<> struct make_signed<unsigned short> { using type = signed short; };
    template<> struct make_signed<unsigned int> { using type = signed int; };
    template<> struct make_signed<unsigned long> { using type = signed long; };
    template<> struct make_signed<unsigned long long> { using type = signed long long; };
    // make_unsigned
    template<typename T> struct make_unsigned { using type = T; };
    template<> struct make_unsigned<char> { using type = unsigned char; };
    template<> struct make_unsigned<signed char> { using type = unsigned char; };
    template<> struct make_unsigned<signed short> { using type = unsigned short; };
    template<> struct make_unsigned<signed int> { using type = unsigned int; };
    template<> struct make_unsigned<signed long> { using type = unsigned long; };
    template<> struct make_unsigned<signed long long> { using type = unsigned long long; };
    // is_signed
    template<typename T> struct is_signed : integral_constant<bool, T(-1) < T(0)> {};
  }
  // make_signed
  template<typename T> struct make_signed { using type = typename implementation::make_signed<typename remove_cv<T>::type>::type; };
  template<typename T> struct make_signed<const T> { using type = const typename implementation::make_signed<typename remove_cv<T>::type>::type; };
  template<typename T> struct make_signed<volatile T> { using type = volatile typename implementation::make_signed<typename remove_cv<T>::type>::type; };
  template<typename T> struct make_signed<const volatile T> { using type = const volatile typename implementation::make_signed<typename remove_cv<T>::type>::type; };
  // make_unsigned
  template<typename T> struct make_unsigned { using type = typename implementation::make_unsigned<typename remove_cv<T>::type>::type; };
  template<typename T> struct make_unsigned<const T> { using type = typename implementation::make_unsigned<typename remove_cv<T>::type>::type; };
  template<typename T> struct make_unsigned<volatile T> { using type = typename implementation::make_unsigned<typename remove_cv<T>::type>::type; };
  template<typename T> struct make_unsigned<const volatile T> { using type = typename implementation::make_unsigned<typename remove_cv<T>::type>::type; };
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
  template<typename T>
  constexpr size_type alignment_of(const T t) { return __alignof__(t); }
//TODO aligned_storage - needs default argument
  template<size_type size, size_type alignment>
  struct aligned_storage
  {
    using type = struct { alignas(alignment) unsigned char data[size]; };
  };
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
#endif

#endif
