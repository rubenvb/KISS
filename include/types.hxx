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

#include "config.hxx"
#include "tmp.hxx"

namespace kiss
{
/* Basic types */
  // implementation of template meta-programming type selector
  namespace implementation
  {
    template<typename T>
    struct Next;

    template<> struct Next<char > { typedef short     Type; };
    template<> struct Next<short> { typedef int       Type; };
    template<> struct Next<int  > { typedef long      Type; };
    template<> struct Next<long > { typedef long long Type; };

    template<> struct Next<unsigned char > { typedef unsigned short     Type; };
    template<> struct Next<unsigned short> { typedef unsigned int       Type; };
    template<> struct Next<unsigned int  > { typedef unsigned long      Type; };
    template<> struct Next<unsigned long > { typedef unsigned long long Type; };

    template<unsigned n, typename T, unsigned size = sizeof(T)>
    struct FindTypeHelper
    {
      typedef typename Next<T>::Type NextType;
      typedef typename FindTypeHelper<n, NextType>::Type Type;
    };

    // Specialization for n == sizeof(T)
    template<unsigned n, typename T>
    struct FindTypeHelper<n, T, n>
    {
      typedef T Type;
    };

    template<unsigned n>
    struct FindSignedType
    {
      typedef typename FindTypeHelper<n, char>::Type Type;
    };

    template<unsigned n>
    struct FindUnsignedType
    {
      typedef typename FindTypeHelper<n, unsigned char>::Type Type;
    };

    template<unsigned n>
    struct Unsigned
    {
      typedef typename FindUnsignedType<n>::Type Type;
    };

    template<unsigned n>
    struct Signed
    {
      typedef typename FindSignedType<n>::Type Type;
    };
  }

  // pointer and size types
  typedef decltype(nullptr)           nullptr_type;
  typedef decltype(sizeof(0))         size_type;
  typedef decltype((char*)0-(char*)0) ptrdiff_type;

  // fixed-width signed integers
  typedef implementation::Signed<1>::Type int8;
  typedef implementation::Signed<2>::Type int16;
  typedef implementation::Signed<4>::Type int32;
  typedef implementation::Signed<8>::Type int64;

  // fixed width unsigned integers
  typedef implementation::Unsigned<1>::Type uint8;
  typedef implementation::Unsigned<2>::Type uint16;
  typedef implementation::Unsigned<4>::Type uint32;
  typedef implementation::Unsigned<8>::Type uint64;

  // UTF character types
  typedef char     char8;
#if defined(_MSC_VER) && !defined(__clang__) && !defined(__ICL)
  // C++11 requires distinct types, but alas
  typedef wchar_t char16;
  typedef uint32  char32;
#else
  typedef char16_t char16;
  typedef char32_t char32;
#endif

  // integral_constant
  template<typename T, T value>
  struct integral_constant
  {
    //static constexpr T result = value;
    typedef integral_constant<T,value> type;
    constexpr operator T() { return value; }
  };
  // true_type
  typedef integral_constant<bool, true> true_type;
  // false_type
  typedef integral_constant<bool, false> false_type;

/*
 * Transforming type traits - using alias templates
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
  template<> struct add_lvalue_reference<void> {typedef void type;};
  template<> struct add_lvalue_reference<const void> {typedef const void type;};
  template<> struct add_lvalue_reference<volatile void> {typedef volatile void type;};
  template<> struct add_lvalue_reference<const volatile void> {typedef const volatile void type;};
  // add_rvalue_reference
  template<typename T> struct add_rvalue_reference { typedef T&& type; };
  template<> struct add_rvalue_reference<void> {typedef void type;};
  template<> struct add_rvalue_reference<const void> {typedef const void type;};
  template<> struct add_rvalue_reference<volatile void> {typedef volatile void type;};
  template<> struct add_rvalue_reference<const volatile void> {typedef const volatile void type;};
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

  // underlying_type
  template<typename T> struct underlying_type { typedef __underlying_type(T) type; };
/*
 * declval
 **/
  template <class T>
  add_rvalue_reference<T> declval() noexcept;
/*
 * Value type_traits
 **/
  namespace implementation
  {
    // is_void
    template<typename T> struct is_void : false_type {};
    template<> struct is_void<void> : true_type {};
    // is_integral
    template<typename T> struct is_integral : false_type{};
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
    template<typename T> struct is_floating_point : false_type {};
    template<> struct is_floating_point<float> : true_type {};
    template<> struct is_floating_point<double> : true_type {};
    template<> struct is_floating_point<long double> : true_type {};
    // is_pointer
    template<typename T> struct is_pointer : false_type {};
    template<typename T> struct is_pointer<T*> : true_type {};
  }
  // is_void
  template<typename T> struct is_void : implementation::is_void<typename remove_cv<T>::type> {};
  // is_nullptr
  template<typename T> struct is_nullptr : false_type {};
  template<> struct is_nullptr<nullptr_type> : true_type {};
  // is_const
  template<typename T> struct is_const : false_type {};
  template<typename T> struct is_const<T const> : true_type {};
  // is_volatile
  template<typename T> struct is_volatile : false_type {};
  template<typename T> struct is_volatile<T volatile> : true_type {};
  // is_integral
  template<typename T> struct is_integral : implementation::is_integral<typename remove_cv<T>::type> {};
  // is_floating_point
  template<typename T> struct is_floating_point : implementation::is_floating_point<typename remove_cv<T>::type> {};
  // is_c_array
  template<typename T> struct is_c_array : false_type {};
  template<typename T> struct is_c_array<T[]> : true_type {};
  template<typename T, size_type N> struct is_c_array<T[N]> : true_type {};
  // is_pointer
  template<typename T> struct is_pointer : implementation::is_pointer<typename remove_cv<T>::type> {};
  // is_lvalue_reference
  template<typename T> struct is_lvalue_reference : false_type {};
  template<typename T> struct is_lvalue_reference<T&> : true_type {};
  // is_rvalue_reference
  template<typename T> struct is_rvalue_reference : false_type {};
  template<typename T> struct is_rvalue_reference<T&&> : true_type {};
  // is_reference
  template<typename T> struct is_reference : integral_constant<bool, is_lvalue_reference<T>() || is_rvalue_reference<T>()> {};
  // is_function
  template<typename T, typename... Args> struct is_function : false_type {};
  template<typename T, typename... Args> struct is_function<T(Args...)> : true_type {}; // normal function
  template<typename T, typename... Args> struct is_function<T(Args...,...)> : true_type {}; // variadic function
  // is_member_object_pointer
  template<typename T> struct is_member_object_pointer : false_type {};
  // is_member_function_pointer
  template<typename T> struct is_member_function_pointer : false_type {};
  template<typename T, typename Class, typename... Args> struct is_member_function_pointer<T (Class::*)(Args...)> : true_type {};
  template<typename T, typename Class, typename... Args> struct is_member_function_pointer<T (Class::*)(Args...) const> : true_type {};
  template<typename T, typename Class, typename... Args> struct is_member_function_pointer<T (Class::*)(Args...) volatile> : true_type {};
  template<typename T, typename Class, typename... Args> struct is_member_function_pointer<T (Class::*)(Args...) const volatile> : true_type {};
  // is_signed
  template<typename T> struct is_signed : integral_constant<bool, T(-1) < T(0)> {};
  // is_same
  template<typename T1, typename T2> struct is_same : false_type {};
  template<typename T> struct is_same<T,T> : true_type {};
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
  // union
  template<typename T> struct is_enum : integral_constant<bool, __is_enum(typename remove_cv<T>::type)> {};
  template<typename T> struct is_union : integral_constant<bool, __is_union(typename remove_cv<T>::type)> {};
  template<typename T> struct is_class : integral_constant<bool, __is_class(typename remove_cv<T>::type)> {};
/*
 * Primary classification
 **/
  /*template<typename T> constexpr bool
  is_void() { return implementation::is_void<typename implementation::remove_cv<T>::type>::result; }
  template<typename T> constexpr bool
  is_integral() { return implementation::is_integral<typename implementation::remove_cv<T>::type>::result; }
  template<typename T> constexpr bool
  is_floating_point() { return implementation::is_floating_point<typename implementation::remove_cv<T>::type>::result; }
  template<typename T> constexpr bool
  is_unbound_c_array() { return implementation::is_unbound_c_array<T>::result; }
  template<typename T> constexpr bool
  is_c_array() { return implementation::is_c_array<T>::result; }
  template<typename T> constexpr bool
  is_pointer() { return implementation::is_pointer<typename implementation::remove_cv<T>::type>::result; }
  template<typename T> constexpr bool
  is_nullptr() { return implementation::is_nullptr<T>::result; }
  template<typename T> constexpr bool
  is_lvalue_reference() { return implementation::is_lvalue_reference<T>::result; }
  template<typename T> constexpr bool
  is_rvalue_reference() { return implementation::is_rvalue_reference<T>::result; }
  template<typename T> constexpr bool
  is_member_object_pointer() { return implementation::is_member_object_pointer<T>::result; }
  template<typename T> constexpr bool
  is_member_function_pointer() { return implementation::is_member_function_pointer<typename implementation::remove_cv<T>::type>::result; }
  template<typename T> constexpr bool
  template<typename T> constexpr bool
  is_function() { return implementation::is_function<typename implementation::remove_cv<T>::type>::result; }*/
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
 * Const-volatile
 */
  /*template<typename T>
  constexpr bool is_const() { return implementation::is_const<T>::result; }
  template<typename T>
  constexpr bool is_volatile() { return implementation::is_volatile<T>::result; }*/

/*
 * Reference transformations
 */


/*
 * Pointer transformations
 */

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
  template<typename T>
  constexpr bool is_pod() { return __is_pod(T); }
  template<typename T>
  constexpr bool is_trivial() { return __is_trivial(T); }
  template<typename T>
  constexpr bool is_trivially_copyable() { return __has_trivial_copy(T); }
  template<typename T>
  constexpr bool is_standard_layout() { return __is_standard_layout(T); }
  /* ^ remove_all_extent scalar */
  template<typename T>
  constexpr bool is_literal_type() { return __is_literal(T); }
  /* ^ remove_all_extent scalar, remove_all_extent reference */
  template<typename T>
  constexpr bool is_empty() { return __is_empty(T); }
  template<typename T>
  constexpr bool is_polymorphic() { return __is_polymorphic(T); }
  template<typename T>
  constexpr bool is_abstract() { return __is_abstract(T); }

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
