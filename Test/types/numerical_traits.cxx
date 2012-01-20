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
  * types/numerical_traits.cxx
  *  Numerical traits
  */

#include <types.hxx>

class dummy_class{};

int main()
{
    // integer type test
    static_assert( kiss::is_integral<kiss::int8>(),    "int8 is not recognized as integral type" );
    static_assert( kiss::is_integral<kiss::uint8>(),   "uint8 is not recognized as integral type" );
    static_assert( kiss::is_integral<kiss::int16>(),   "int16 is not recognized as integral type" );
    static_assert( kiss::is_integral<kiss::uint16>(),  "uint16 is not recognized as integral type" );
    static_assert( kiss::is_integral<kiss::int32>(),   "int32 is not recognized as integral type" );
    static_assert( kiss::is_integral<kiss::uint32>(),  "uint32 is not recognized as integral type" );
    static_assert( kiss::is_integral<kiss::int64>(),   "int64 is not recognized as integral type" );
    static_assert( kiss::is_integral<kiss::uint64>(),  "uint64 is not recognized as integral type" );
    static_assert( !kiss::is_integral<float>(),        "float is recognized as integral type" );
    static_assert( !kiss::is_integral<double>(),       "double is recognized as integral type" );
    static_assert( !kiss::is_integral<long double>(),  "long double is recognized as integral type" );
    static_assert( !kiss::is_integral<dummy_class>(),  "dummy class is recognized as integral type" );
    static_assert( !kiss::is_integral<kiss::int8&>(),  "l-reference type is recognized as integral type" );
    static_assert( !kiss::is_integral<kiss::int8&&>(), "r-value reference type is recognized as integral type" );
    static_assert( !kiss::is_integral<kiss::int8*>(),  "pointer type is recognized as integral type" );
    // floating point type test
    static_assert( !kiss::is_floating_point<kiss::int8>(),   "int8 is recognized as a floating point type" );
    static_assert( !kiss::is_floating_point<kiss::uint8>(),  "uint8 is recognized as a floating point type" );
    static_assert( !kiss::is_floating_point<kiss::int16>(),  "int16 is recognized as a floating point type" );
    static_assert( !kiss::is_floating_point<kiss::uint16>(), "uint16 is recognized as a floating point type" );
    static_assert( !kiss::is_floating_point<kiss::int32>(),  "int32 is recognized as a floating point type" );
    static_assert( !kiss::is_floating_point<kiss::uint32>(), "uint32 is recognized as a floating point type" );
    static_assert( !kiss::is_floating_point<kiss::int64>(),  "int64 is recognized as a floating point type" );
    static_assert( !kiss::is_floating_point<kiss::uint64>(), "uint64 is recognized as a floating point type" );
    static_assert( kiss::is_floating_point<float>(),         "float is not recognized as a floating point type" );
    static_assert( kiss::is_floating_point<double>(),        "double is not recognized as a floating point type" );
    static_assert( kiss::is_floating_point<long double>(),   "long double is not recognized as a floating point type" );
    static_assert( !kiss::is_floating_point<dummy_class>(),  "dummy class is recognized as a floating point type" );
    static_assert( !kiss::is_floating_point<kiss::int8&>(),  "l-reference type is recognized as a floating point type" );
    static_assert( !kiss::is_floating_point<kiss::int8&&>(), "r-value reference type is recognized as a floating point type" );
    static_assert( !kiss::is_floating_point<kiss::int8*>(),  "pointer type is recognized as a floating point type" );
    // arithmetic type test
    static_assert( kiss::is_arithmetic<kiss::int8>(),    "int8 is not recognized as an arithmetic type" );
    static_assert( kiss::is_arithmetic<kiss::uint8>(),   "uint8 is not recognized as an arithmetic type" );
    static_assert( kiss::is_arithmetic<kiss::int16>(),   "int16 is not recognized as an arithmetic type" );
    static_assert( kiss::is_arithmetic<kiss::uint16>(),  "uint16 is not recognized as an arithmetic type" );
    static_assert( kiss::is_arithmetic<kiss::int32>(),   "int32 is not recognized as an arithmetic type" );
    static_assert( kiss::is_arithmetic<kiss::uint32>(),  "uint32 is not recognized as an arithmetic type" );
    static_assert( kiss::is_arithmetic<kiss::int64>(),   "int64 is not recognized as an arithmetic type" );
    static_assert( kiss::is_arithmetic<kiss::uint64>(),  "uint64 is not recognized as an arithmetic type" );
    static_assert( kiss::is_arithmetic<float>(),         "float is not recognized as an arithmetic type" );
    static_assert( kiss::is_arithmetic<double>(),        "double is not recognized as an arithmetic type" );
    static_assert( kiss::is_arithmetic<long double>(),   "long double is not recognized as an arithmetic type" );
    static_assert( !kiss::is_arithmetic<dummy_class>(),  "dummy class is recognized as an arithmetic type" );
    static_assert( !kiss::is_arithmetic<kiss::int8&>(),  "dummy class is recognized as an arithmetic type" );
    static_assert( !kiss::is_arithmetic<kiss::int8&&>(), "dummy class is recognized as an arithmetic type" );
    static_assert( !kiss::is_arithmetic<kiss::int8*>(),  "dummy class is recognized as an arithmetic type" );
    // signedness
    static_assert( kiss::is_signed<kiss::int8>(),    "int8 is not recognized as integral type" );
    static_assert( !kiss::is_signed<kiss::uint8>(),  "uint8 is not recognized as integral type" );
    static_assert( kiss::is_signed<kiss::int16>(),   "int16 is not recognized as integral type" );
    static_assert( !kiss::is_signed<kiss::uint16>(), "uint16 is not recognized as integral type" );
    static_assert( kiss::is_signed<kiss::int32>(),   "int32 is not recognized as integral type" );
    static_assert( !kiss::is_signed<kiss::uint32>(), "uint32 is not recognized as integral type" );
    static_assert( kiss::is_signed<kiss::int64>(),   "int64 is not recognized as integral type" );
    static_assert( !kiss::is_signed<kiss::uint64>(), "uint64 is not recognized as integral type" );
    static_assert( kiss::is_signed<float>(),         "float is recognized as integral type" );
    static_assert( kiss::is_signed<double>(),        "double is recognized as integral type" );
    static_assert( kiss::is_signed<long double>(),   "long double is recognized as integral type" );
    // unsignedness
    static_assert( !kiss::is_unsigned<kiss::int8>(),  "int8 is not recognized as integral type" );
    static_assert( kiss::is_unsigned<kiss::uint8>(),  "uint8 is not recognized as integral type" );
    static_assert( !kiss::is_unsigned<kiss::int16>(), "int16 is not recognized as integral type" );
    static_assert( kiss::is_unsigned<kiss::uint16>(), "uint16 is not recognized as integral type" );
    static_assert( !kiss::is_unsigned<kiss::int32>(), "int32 is not recognized as integral type" );
    static_assert( kiss::is_unsigned<kiss::uint32>(), "uint32 is not recognized as integral type" );
    static_assert( !kiss::is_unsigned<kiss::int64>(), "int64 is not recognized as integral type" );
    static_assert( kiss::is_unsigned<kiss::uint64>(), "uint64 is not recognized as integral type" );
    static_assert( !kiss::is_unsigned<float>(),       "float is recognized as integral type" );
    static_assert( !kiss::is_unsigned<double>(),      "double is recognized as integral type" );
    static_assert( !kiss::is_unsigned<long double>(), "long double is recognized as integral type" );    
}