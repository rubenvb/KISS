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
 * limits.h++
 *  Numerical limits.
 **/

#ifndef KISS_LIMITS_H
#define KISS_LIMITS_H

#include "config.h++"
#include "types.h++"

namespace kiss
{
    template<typename T> struct limits
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

//TODO

#endif
