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
  * limits.hxx
  *  numerical limits for kiss datatypes
  */

#include "config.hxx"
#include "types.hxx"

namespace kiss
{
    template<typename T> struct numeric_limits
    {
    public:
        static constexpr T min = 0;
        static constexpr T max = 0;
        static constexpr T lowest = 0;
        
        static constexpr digits = 0;
        static constexpr digits10 = 0;
        static constexpr max_digits10 = 0;
        static constexpr bool is_signed = is_signed<T>();
        static constexpr bool is_integer = is_integal<T>();
        static constexpr int32 radix = 0;
        static constexpr T epsilon = 0;
        static constexpr T round_error = 0;
        
        static constexpr int32 min_exponent = 0;
        static constexpr int32 min_exponent10 = 0;
        static constexpr int32 max_exponent = 0;
        static constexpr int32 max_exponent10 = 0;
        
        static constexpr has_infinity = false;
        static constexpr has_quiet_NaN = false;
        static constexpr has_signaling_NaN = false;
        // has_denorm
        // has_denorm_loss
        static constexpr T infinity = 0;
        static constexpr T quiet_NaN = 0;
        static constexpr T signaling_NaN = 0;
        //static constexpr T denorm_min = 0;
        
        // is_iec559
        // is_bounded
        // is_modulo
        
        // traps
        // tinyness_before
        // round_style
}
