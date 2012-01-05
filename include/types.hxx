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
  *  Resorts to template tricks if compiler is unknown.
  */

#include "config.hxx"

namespace __nectar_namespace
{
#if defined(__clang__) || defined(__GNUC__)
    // fixed width signed integer types
    typedef signed char int8;
    typedef short       int16;
    typedef int         int32;
    typedef long long   int64;
    
    // fixed with unsigned integer types
    typedef unsigned char      uint8;
    typedef unsigned short     uint16;
    typedef unsigned int       uint32;
    typedef unsigned long long uint64;
#elif defined(MSVC)
    // fixed width signed integer types
    typedef __int8  int8;
    typedef __int16 int16;
    typedef __int32 int32;
    typedef __int64 int64;
    
    // fixed width unsigned integer types
    typedef uint8  unsigned __int8;
    typedef uint16 unsigned __int16;
    typedef uint32 unsigned __int32;
    typedef uint64 unsigned __int64;
    
    // fixed width character types, map to UTF-8/16/32
    typedef char8  char;
    enum char16  : uint16 {};
    enum char32  : uint32 {};
#else
    // template metaprogramming to find the types of correct widths. Assumes sizes multiple of 8
    namespace __implementation
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
    typedef __implementation::Signed<1>::Type int8;
    typedef __implementation::Signed<2>::Type int16;
    typedef __implementation::Signed<4>::Type int32;
    typedef __implementation::Signed<8>::Type int64;
    
    typedef __implementation::Unsigned<1>::Type uint8;
    typedef __implementation::Unsigned<2>::Type uint16;
    typedef __implementation::Unsigned<4>::Type uint32;
    typedef __implementation::Unsigned<8>::Type uint64;
#endif
}