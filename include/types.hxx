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
        // is_c_array
        template<typename T> struct is_c_array : public false_type {};
        template<typename T> struct is_c_array<T[]> : public true_type {};
        template<typename T, size_type N> struct is_c_array<T[N]> : public true_type {};
        // is_pointer
        template<typename T> struct is_pointer : public false_type {};
        template<typename T> struct is_pointer<T*> : public true_type {};
        // is_signed - only works with numeric types, other types produce ugly errors
        template<typename T> struct is_signed : public integral_constant<bool, T(-1) < T(0)> {};
        // remove_reference
        template <typename T> struct remove_reference      {typedef T type;};
        template <typename T> struct remove_reference<T&>  {typedef T type;};
        template <typename T> struct remove_reference<T&&> {typedef T type;};
    }
/*
 * Short forms: either alias templates or constexpr functions
 */
    // remove_const
    template<typename T>
    using remove_const = typename __implementation::remove_const<T>::type;
    // remove_volatile
    template<typename T>
    using remove_volatile = typename __implementation::remove_volatile<T>::type;
    // remove_cv
    template<typename T>
    using remove_cv = typename __implementation::remove_cv<T>::type;
    // is_void
    template<typename T>
    constexpr bool is_void() { return __implementation::is_void<remove_cv<T>>::result; }
    // is_const
    template<typename T>
    constexpr bool is_const() { return __implementation::is_const<T>::result; }
    // is_nullptr
    template<typename T>
    constexpr bool is_nullptr() { return __implementation::is_nullptr<T>::result; }
    // is_volatile
    template<typename T>
    constexpr bool is_volatile() { return __implementation::is_volatile<T>::result; }
    // is_integral
    template<typename T>
    constexpr bool is_integral() { return __implementation::is_integral<typename __implementation::remove_cv<T>::type>::result; }
    // is_floating_point
    template<typename T> 
    constexpr bool is_floating_point() { return __implementation::is_floating_point<typename __implementation::remove_cv<T>::type>::result; }
    // is_c_array
    template<typename T>
    constexpr bool is_c_array() { return __implementation::is_c_array<T>::result; }
    // is_pointer
    template<typename T>
    constexpr bool is_pointer() { return __implementation::is_pointer<typename __implementation::remove_cv<T>::type>::result; }
    // is_arithmetic
    template<typename T>
    constexpr bool is_arithmetic() { return is_integral<T>() || is_floating_point<T>(); }
    // is_signed
    template<typename T>
    constexpr bool is_signed() { static_assert( is_arithmetic<T>(), "is_signed can only be used on arithmetic types");
                                 return __implementation::is_signed<T>::result; }
    // is_unsigned
    template<typename T>
    constexpr bool is_unsigned() { static_assert( is_arithmetic<T>(), "is_unsigned can only be used on arithmetic types");
                                   return !__implementation::is_signed<T>::result; }
    // remove_reference
    template<typename T>
    using remove_reference = typename __implementation::remove_reference<T>::type;
}

/* This little bit of code above makes any code including <initializer_list>
    fail to compile so here are the preprocessor defines to prevent double 
    declaration */
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
        // number of elements
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
