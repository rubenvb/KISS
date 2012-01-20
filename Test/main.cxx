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

#include <types.hxx>
    using namespace kiss;
 
int main()
{
    
    static_assert( is_integral<signed char>(),        "int8 is not recognized as integral type" );
    static_assert( is_integral<unsigned char>(),       "uint8 is not recognized as integral type" );
    static_assert( is_integral<short>(),       "int16 is not recognized as integral type" );
    static_assert( is_integral<unsigned short>(),      "uint16 is not recognized as integral type" );
    static_assert( is_integral<int>(),       "int32 is not recognized as integral type" );
    static_assert( is_integral<unsigned int>(),      "uint32 is not recognized as integral type" );
    static_assert( !is_integral<float>(),       "float is recognized as integral type" );
    static_assert( !is_integral<double>(),      "double is recognized as integral type" );
    static_assert( !is_integral<long double>(), "long double is recognized as integral type" );
}