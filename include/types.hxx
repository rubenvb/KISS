/**
 * Copyright 2012 Ruben Van Boxem. All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without modification, are
 * permitted provided that the following conditions are met:
 * 
 *    1. Redistributions of source code must retain the above copyright notice, this list of
 *       conditions and the following disclaimer.
 * 
 *    2. Redistributions in binary form must reproduce the above copyright notice, this list
 *       of conditions and the following disclaimer in the documentation and/or other materials
 *       provided with the distribution.
 * 
 * THIS SOFTWARE IS PROVIDED BY RUBEN VAN BOXEM ''AS IS'' AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND
 * FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL <COPYRIGHT HOLDER> OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * 
 * The views and conclusions contained in the software and documentation are those of the
 * authors and should not be interpreted as representing official policies, either expressed
 * or implied, of Ruben Van Boxem.
 ********************************************************************************************/
 
 /*
  * types.hxx
  *  Basic type definitions.
  *  Metatemplate programming helpers for type transformation.
  */

#ifndef __KISS_TYPES
#define __KISS_TYPES
  
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

/*
 * Limits
 */
/*
 * Type traits - using alias templates
 */
    namespace __implementation
    {
        // integral_constant
        template<typename T, T v>
        struct integral_constant
        {
            static 
#ifdef constexpr
            const
#else
            constexpr
#endif
                 T result = v;
            typedef integral_constant<T,v> type;
            constexpr operator T() { return result; }
        };
        // true_type
        typedef integral_constant<bool, true> true_type;
        // false_type
        typedef integral_constant<bool, false> false_type;
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
        // is_void
        template<typename T> struct is_void : public false_type {};
        template<> struct is_void<void> : public true_type {};
        // is_nullptr
        template<typename T> struct is_nullptr : public false_type {};
        template<> struct is_nullptr<nullptr_type> : public true_type {};
        // is_const
        template<typename T> struct is_const : public false_type {};
        template<typename T> struct is_const<T const> : public true_type {};
        // is_volatile
        template<typename T> struct is_volatile : public false_type {};
        template<typename T> struct is_volatile<T volatile> : public true_type {};
        // is_integral
        template<typename T> struct is_integral : public false_type{};
        template<> struct is_integral<bool>               : public true_type {};
        template<> struct is_integral<char>               : public true_type {};
        template<> struct is_integral<signed char>        : public true_type {};
        template<> struct is_integral<unsigned char>      : public true_type {};
        template<> struct is_integral<wchar_t>            : public true_type {};
        template<> struct is_integral<char16_t>           : public true_type {};
        template<> struct is_integral<char32_t>           : public true_type {};
        template<> struct is_integral<short>              : public true_type {};
        template<> struct is_integral<unsigned short>     : public true_type {};
        template<> struct is_integral<int>                : public true_type {};
        template<> struct is_integral<unsigned int>       : public true_type {};
        template<> struct is_integral<long>               : public true_type {};
        template<> struct is_integral<unsigned long>      : public true_type {};
        template<> struct is_integral<long long>          : public true_type {};
        template<> struct is_integral<unsigned long long> : public true_type {};
        // is_floating_point
        template<typename T> struct is_floating_point : public false_type {};
        template<> struct is_floating_point<float> : public true_type {};
        template<> struct is_floating_point<double> : public true_type {};
        template<> struct is_floating_point<long double> : public true_type {};
        // is_unbound_c_array for default_constructible traits
        template<typename T> struct is_unbound_c_array : public false_type {};
        template<typename T> struct is_unbound_c_array<T[]> : public true_type {};
        // is_c_array
        template<typename T> struct is_c_array : public false_type {};
        template<typename T> struct is_c_array<T[]> : public true_type {};
        template<typename T, size_type N> struct is_c_array<T[N]> : public true_type {};
        // is_pointer
        template<typename T> struct is_pointer : public false_type {};
        template<typename T> struct is_pointer<T*> : public true_type {};
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
        // is_lvalue_reference
        template<typename T> struct is_lvalue_reference : public false_type {};
        template<typename T> struct is_lvalue_reference<T&> : public true_type {};
        // is_rvalue_reference
        template<typename T> struct is_rvalue_reference : public false_type {};
        template<typename T> struct is_rvalue_reference<T&&> : public true_type {};
        // is_function
        template<typename T, typename... Args> struct is_function : public false_type {};
        template<typename T, typename... Args> struct is_function<T(Args...)> : public true_type {}; // normal function
        template<typename T, typename... Args> struct is_function<T(Args...,...)> : public true_type {}; // variadic function
        // is_member_object_pointer
        template<typename T> struct is_member_object_pointer : public false_type {};
        //template<typename T, typename Class> struct is_member_object_pointer<
        // is_member_function_pointer
        template<typename T> struct is_member_function_pointer : public false_type {};
        template<typename T, typename Class, typename... Args> struct is_member_function_pointer<T (Class::*)(Args...)> : public true_type {};
        template<typename T, typename Class, typename... Args> struct is_member_function_pointer<T (Class::*)(Args...) const> : public true_type {};
        template<typename T, typename Class, typename... Args> struct is_member_function_pointer<T (Class::*)(Args...) volatile> : public true_type {};
        template<typename T, typename Class, typename... Args> struct is_member_function_pointer<T (Class::*)(Args...) const volatile> : public true_type {};
    /*
     * need ref-qualifiers aka rvalue for *this
        template<typename T, typename Class, typename... Args> struct is_member_function_pointer<T (Class::*)(Args...) &> : public true_type {};
        template<typename T, typename Class, typename... Args> struct is_member_function_pointer<T (Class::*)(Args...) const &> : public true_type {};
        template<typename T, typename Class, typename... Args> struct is_member_function_pointer<T (Class::*)(Args...) volatile &> : public true_type {};
        template<typename T, typename Class, typename... Args> struct is_member_function_pointer<T (Class::*)(Args...) const volatile &> : public true_type {};
        template<typename T, typename Class, typename... Args> struct is_member_function_pointer<T (Class::*)(Args...) &&> : public true_type {};
        template<typename T, typename Class, typename... Args> struct is_member_function_pointer<T (Class::*)(Args...) const &&> : public true_type {};
        template<typename T, typename Class, typename... Args> struct is_member_function_pointer<T (Class::*)(Args...) volatile &&> : public true_type {};
        template<typename T, typename Class, typename... Args> struct is_member_function_pointer<T (Class::*)(Args...) const volatile &&> : public true_type {};
        template<typename T, typename Class, typename... Args> struct is_member_function_pointer<T (Class::*)(Args...,...)> : public true_type {};
        template<typename T, typename Class, typename... Args> struct is_member_function_pointer<T (Class::*)(Args...,...) const> : public true_type {};
        template<typename T, typename Class, typename... Args> struct is_member_function_pointer<T (Class::*)(Args...,...) volatile> : public true_type {};
        template<typename T, typename Class, typename... Args> struct is_member_function_pointer<T (Class::*)(Args...,...) const volatile> : public true_type {};
        template<typename T, typename Class, typename... Args> struct is_member_function_pointer<T (Class::*)(Args...,...) &> : public true_type {};
        template<typename T, typename Class, typename... Args> struct is_member_function_pointer<T (Class::*)(Args...,...) const &> : public true_type {};
        template<typename T, typename Class, typename... Args> struct is_member_function_pointer<T (Class::*)(Args...,...) volatile &> : public true_type {};
        template<typename T, typename Class, typename... Args> struct is_member_function_pointer<T (Class::*)(Args...,...) const volatile &> : public true_type {};
        template<typename T, typename Class, typename... Args> struct is_member_function_pointer<T (Class::*)(Args...,...) &&> : public true_type {};
        template<typename T, typename Class, typename... Args> struct is_member_function_pointer<T (Class::*)(Args...,...) const &&> : public true_type {};
        template<typename T, typename Class, typename... Args> struct is_member_function_pointer<T (Class::*)(Args...,...) volatile &&> : public true_type {};
        template<typename T, typename Class, typename... Args> struct is_member_function_pointer<T (Class::*)(Args...,...) const volatile &&> : public true_type {};
     */
        // is_signed
        template<typename T> struct is_signed : public integral_constant<bool, T(-1) < T(0)> {};
        
        // rank
        template<typename T> struct rank : public integral_constant<size_type, 0> {};
        template<typename T> struct rank<T[]> : public integral_constant<size_type, 0> {};
        template<typename T, size_type N> struct rank<T[N]> : public integral_constant<size_type, N> {};
        // extent
        template<typename T, size_type N> struct extent : public integral_constant<size_type, 0> {};
        template<typename T, size_type N> struct extent<T[], N> : public integral_constant<size_type, N==0 ? 0 : extent<T,N-1>::result> {};
        template<typename T, size_type N, size_type S> struct extent<T[S], N> : public integral_constant<size_type, N==0 ? 0 : extent<T,N-1>::result> {};
        // remove_extent
        template<typename T> struct remove_extent { typedef T type; };
        template<typename T> struct remove_extent<T[]> { typedef T type; };
        template<typename T, size_type N> struct remove_extent<T[N]> { typedef T type; };
        // remove_all_extents
        template<typename T> struct remove_all_extents { typedef T type; };
        template<typename T> struct remove_all_extents<T[]> { typedef typename remove_all_extents<T>::type type; };
        template<typename T, size_type N> struct remove_all_extents<T[N]> { typedef typename remove_all_extents<T>::type type; };
        
        // is_same
        template<typename T1, typename T2> struct is_same : public false_type {};
        template<typename T> struct is_same<T,T> : public true_type {};
        
        // underlying_type
        template<typename T> struct underlying_type { typedef __underlying_type(T) type; };
        
    /*
     * Missing compiler intrinsic/builtins workarounds - Cleanup/expand
     * Unused...
     */
        template<typename T>
        struct is_complete_type{
            static int tester[1];
            typedef char (&two)[2];
 
            template<typename U> static char test(int (&)[int(sizeof(U)>0)]);
            template<typename> static two test(...);
        public:
            static bool constexpr value = sizeof(test<T>(tester)) == 1;
        };
    }
/*
 * Primary classification
 */
        template<typename T> constexpr bool 
    is_void() { return __implementation::is_void<typename __implementation::remove_cv<T>::type>::result; }
        template<typename T> constexpr bool 
    is_integral() { return __implementation::is_integral<typename __implementation::remove_cv<T>::type>::result; }
        template<typename T> constexpr bool
    is_floating_point() { return __implementation::is_floating_point<typename __implementation::remove_cv<T>::type>::result; }
        template<typename T> constexpr bool
    is_unbound_c_array() { return __implementation::is_unbound_c_array<T>::result; }
        template<typename T> constexpr bool
    is_c_array() { return __implementation::is_c_array<T>::result; }
        template<typename T> constexpr bool
    is_pointer() { return __implementation::is_pointer<typename __implementation::remove_cv<T>::type>::result; }
        template<typename T> constexpr bool
    is_nullptr() { return __implementation::is_nullptr<T>::result; }
        template<typename T> constexpr bool
    is_lvalue_reference() { return __implementation::is_lvalue_reference<T>::result; }
        template<typename T> constexpr bool
    is_rvalue_reference() { return __implementation::is_rvalue_reference<T>::result; }
        template<typename T> constexpr bool
    is_member_object_pointer() { return __implementation::is_member_object_pointer<T>::result; }
        template<typename T> constexpr bool
    is_member_function_pointer() { return __implementation::is_member_function_pointer<typename __implementation::remove_cv<T>::type>::result; }
        template<typename T> constexpr bool
    is_enum() { return __is_enum(typename __implementation::remove_cv<T>::type); }
        template<typename T> constexpr bool
    is_union() { return __is_union(typename __implementation::remove_cv<T>::type); }
        template<typename T> constexpr bool
    is_class() { return __is_class(typename __implementation::remove_cv<T>::type); }
        template<typename T> constexpr bool
    is_function() { return __implementation::is_function<typename __implementation::remove_cv<T>::type>::result; }
/*
 * Secondary classification
 */
        template<typename T> constexpr bool 
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
    is_compound() { return !is_fundamental<T>(); }
/*
 * Const-volatile
 */
        template<typename T> constexpr bool 
    is_const() { return __implementation::is_const<T>::result; }
        template<typename T> constexpr bool
    is_volatile() { return __implementation::is_volatile<T>::result; }
        template<typename T> using
    remove_const = typename __implementation::remove_const<T>::type;
        template<typename T> using
    remove_volatile = typename __implementation::remove_volatile<T>::type;
        template<typename T> using
    remove_cv = typename __implementation::remove_cv<T>::type;
        template<typename T> using
    add_const = typename __implementation::add_const<T>::type;
        template<typename T> using
    add_volatile = typename __implementation::add_volatile<T>::type;
        template<typename T> using
    add_cv = typename __implementation::add_cv<T>::type;
/*
 * Reference transformations
 */
        template<typename T> using
    remove_reference = typename __implementation::remove_reference<T>::type; 
        template<typename T> using
    add_lvalue_reference = typename __implementation::add_lvalue_reference<T>::type;
        template<typename T> using
    add_rvalue_reference = typename __implementation::add_rvalue_reference<T>::type;
/*
 * Pointer transformations
 */
        template<typename T> using
    remove_pointer = typename __implementation::remove_pointer<T>::type;
        template<typename T> using
    add_pointer = typename __implementation::add_pointer<T>::type;
/*
 * Integral properties
 */
    // is_signed
    template<typename T> constexpr bool
    is_signed() { static_assert( is_arithmetic<T>(), "is_signed can only be used on arithmetic types");
                  return __implementation::is_signed<T>::result; }
    // is_unsigned
    template<typename T> constexpr bool
    is_unsigned() { static_assert( is_arithmetic<T>(), "is_unsigned can only be used on arithmetic types");
                    return !__implementation::is_signed<T>::result; }
    // make_signed
    // make_unsigned
/*
 * Array properties and transformations
 */
    // rank
        template<typename T> constexpr size_type
    rank() { return __implementation::rank<T>::result; }
        template<typename T> constexpr size_type
    extent() { return __implementation::rank<T>::result; }
        template<typename T> constexpr size_type
    remove_extent() { return __implementation::remove_extent<T>::result; }
        template<typename T> constexpr size_type
    remove_all_extents() { return __implementation::remove_all_extents<T>::result; }
/*
 * Member introspection (mostly compiler magic)
 */
        template<typename T> constexpr bool
    is_pod() { return __is_pod(T); }
        template<typename T> constexpr bool
    is_trivial() { return __is_trivial(T); }
    //#if __has_feature(is_trivially_copyable)
        template<typename T> constexpr bool
    is_trivially_copyable() { return __has_trivial_copy(T); }
    //#endif
        template<typename T> constexpr bool
    is_standard_layout() { return __is_standard_layout(T); }
    /* ^ remove_all_extent scalar */
        template<typename T> constexpr bool
    is_literal_type() { return __is_literal(T); }
    /* ^ remove_all_extent scalar, remove_all_extent reference */
        template<typename T> constexpr bool
    is_empty() { return __is_empty(T); }
        template<typename T> constexpr bool
    is_polymorphic() { return __is_polymorphic(T); }
        template<typename T> constexpr bool
    is_abstract() { return __is_abstract(T); }

    //is_constructible
    // is_default_constructible
    // is_copy_constructible
    // is_move_constructible
    // is_assignable
    // is_copy_assignable
    // is_move_assignable
    // is_destructible
    
        template<typename T> constexpr bool
    is_trivially_constructible() { return __has_trivial_copy(T); }
    // ^ this needs overloads for rvalue refs?
    // is_trivially_default_constructible
    // is_trivially_copy_constructible
    // is_trivially_move_constructible
    // is_trivially_assignable
    // is_trivially_copy_assignable
    // is_trivially_move_assignable
    // is_trivially_destructible

        template<typename T> constexpr bool
    is_nothrow_constructible() { return __has_nothrow_constructor(T); }
    // is_nothrow_default_constructible
        template<typename T> constexpr bool
    is_nothrow_copy_constructible() { return __has_nothrow_copy(T); }
    // is_nothrow_move_constructible
    // is_nothrow_assignable
    // is_nothrow_copy_assignable
    // is_nothrow_move_assignable
    // is_nothrow_destructible
    
        template<typename T> constexpr bool
    has_virtual_destructor() { return __has_virtual_destructor(T); }
    
/*
 * Intertype relations
 */
        template<typename T1, typename T2> constexpr bool
    is_same() { return __implementation::is_same<T1,T2>::result; }
        template<typename Base, typename Class> constexpr bool
    is_base_of() { return __is_base_of(Base,Class); }
    #if __has_feature(is_convertible_to)
        template<typename From, typename To> constexpr bool
    is_convertible_to() { return __is_convertible_to(From, To); }
    #endif
/*
 * Alignment properties and transformations
 */
        template<typename T> constexpr size_type
    alignment_of(const T t) { return __alignof__(t); }
    // aligned_storage

    // decay
    // common_type
        template<typename T> using
    underlying_type = typename __implementation::underlying_type<T>::type;
    // result_of
}

/* This little bit of code above makes any code including <initializer_list>
    fail to compile so here are the preprocessor defines to prevent double 
    declaration for GCC's libstdc++ and LLVM's libc++*/
#if !defined(_LIBCPP_INITIALIZER_LIST) && !defined(_INITIALIZER_LIST)
#define _LIBCPP_INITIALIZER_LIST
#define _INITIALIZER_LIST
/* initialize_list type for brace-intializer-lists
    C++11 requires this in namespace std, unfortunately */
namespace std
{
    template<class E> class initializer_list {
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
