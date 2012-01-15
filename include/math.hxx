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
  * math.hxx
  *  main mathematics function header
  */

#ifndef __KISS_MATH_H
#define __KISS_MATH_H

#include "config.hxx"

// force MSVC intrinsics for math functions
#ifdef _MSC_VER
// MSVC needs declarations for #pragma intrinsic
namespace kiss{namespace __implementation{extern "C"{
int abs(int);
double fabs(double);
long labs(long);
__int64 _abs64(__int64);
double acos(double);
float acosf(float);
double acosh(double);
float acoshf(float);
double asin(double);
float asinf(float);
double atan(double);
float atanf(float);
double atan2(double,double);
float atan2f(float,float);
double ceil(double);
float ceilf(float);
double cosh(double);
float coshf(float);
double cos(double);
float cosf(float);
double exp(double);
float expf(float);
double floor(double);
float floorf(float);
double fmod(double,double);
float fmodf(float,float);
double log(double);
float logf(float);
double log10(double);
float log10f(float);
double pow(double,double);
float powf(float,float);
double sin(double);
float sinf(float);
double sinh(double);
float sinhf(float);
double sqrt(double);
float sqrtf(float);
double tan(double);
float tanf(float);
double tanh(double);
float tanhf(float);
} // force MSVC to generate intrinsics
#pragma intrinsic(abs,   fabs,   labs, _abs64, \
                  acos,  acosf,  /*acosl,*/ \
                  acosh, acoshf, /*acoshl,*/ \
                  asin,  asinf,  /*asinl,*/ \
                  atan,  atanf,  /*atanl,*/ \
                  atan2, atan2f, /*atan2l,*/ \
                  ceil,  ceilf,  /*ceill,*/ \
                  cosh,  coshf,  /*coshl,*/ \
                  cos,   cosf,   /*cosl,*/ \
                  exp,   expf,   /*expl,*/ \
                  floor, floorf, /*floorl,*/ \
                  fmod,  fmodf,  /*fmodl,*/ \
                  log,   logf,   /*logl,*/ \
                  log10, log10f, /*log10l,*/ \
                  pow,   powf,   /*powl,*/ \
                  sin,   sinf,   /*sinl,*/ \
                  sinh,  sinhf,  /*sinhl,*/ \
                  sqrt,  sqrtf,  /*sqrtl,*/ \
                  tan,   tanf,   /*tanl,*/ \
                  tanh,  tanhf,  /*tanhl*/ )
} // define __builtin_* for MSVC
#define __builtin_abs         abs
#define __builtin_fabs        __implementation::fabs
#define __builtin_fabsf(X)    static_cast<float>(__implementation::fabs(X))
#define __builtin_fabsl(X)    __implementation::fabs(static_cast<double>(X))
#define __builtin_labs        __implementation::labs
#define __builtin_llabs       __implementation::_abs64
#define __builtin_acos        acos
#define __builtin_acosf       __implementation::acosf
#define __builtin_acosl(X)    acos(static_cast<double>(X))
#define __builtin_asin        asin
#define __builtin_asinf       asinf
#define __builtin_asinl(X)    asinl(static_cast<double>(X))
#define __builtin_atan        atan
#define __builtin_atanf       atanf
#define __builtin_atanl(X)    atanl(static_cast<double>(X))
#define __builtin_atan2       atan2
#define __builtin_atan2f      atan2f
#define __builtin_atan2l(X,Y) atan2l(static_cast<double(X), static_cast<double>(Y))
#define __builtin_ceil        ceil
#define __builtin_ceilf       ceilf
#define __builtin_ceill(X)    ceill(static_cast<double>(X))
#define __builtin_cosh        cosh
#define __builtin_coshf       coshf
#define __builtin_coshl(X)    coshl(static_cast<double>(X))
#define __builtin_
#define __builtin_
#define __builtin_
#define __builtin_
#define __builtin_
#define __builtin_
#define __builtin_
#define __builtin_
#endif

namespace kiss
{
/*
 * Builtin template redirection
 */
    namespace builtin
    {
        // absolute value
        inline constexpr int abs(const int number)
        { return __builtin_abs(number); }
        inline constexpr long abs(const long number)
        { return __builtin_labs(number); }
        inline constexpr long long abs(const long long number)
        { return __builtin_llabs(number); }
        inline constexpr double abs(const double& number)
        { return __builtin_fabs(number); }
        inline constexpr float abs(const float& number)
        { return __builtin_fabsf(number); }
        inline constexpr long double abs(const long double& number)
        { return __builtin_fabsl(number); }
        // acos = cos^(-1)
        inline constexpr int acos(const int number)
        { return static_cast<int>(__builtin_acos(number)); }
        inline constexpr long acos(const long number)
        { return static_cast<long>(__builtin_acos(number)); }
        inline constexpr long long acos(const long long number)
        { return static_cast<long long>(__builtin_acos(number)); }
        inline constexpr double acos(const double& number)
        { return __builtin_acos(number); }
        inline constexpr float acos(const float& number)
        { return __builtin_acosf(number); }
        inline constexpr long double acos(const long double& number)
        { return __builtin_acosl(number); }
        // acosh = cosh^(-1)
        inline constexpr int acosh(const int number)
        { return static_cast<int>(__builtin_acosh(number)); }
        inline constexpr long acosh(const long number)
        { return static_cast<long>(__builtin_acosh(number)); }
        inline constexpr long long acosh(const long long number)
        { return static_cast<long long>(__builtin_acosh(number)); }
        inline constexpr double acosh(const double& number)
        { return __builtin_acosh(number); }
        inline constexpr float acoshf(const float& number)
        { return __builtin_acosf(number); }
        inline constexpr long double acosh(const long double& number)
        { return __builtin_acoshl(number); }
        // asin = sin^(-1)
        inline constexpr int asin(const int number)
        { return static_cast<int>(__builtin_asin(number)); }
        inline constexpr long asin(const long number)
        { return static_cast<long>(__builtin_asin(number)); }
        inline constexpr long long asin(const long long number)
        { return static_cast<long long>(__builtin_asin(number)); }
        inline constexpr double asin(const double& number)
        { return __builtin_asin(number); }
        inline constexpr float asin(const float& number)
        { return __builtin_asinf(number); }
        inline constexpr long double asin(const long double& number)
        { return __builtin_asinl(number); }
        // asinh = sinh^(-1)
        inline constexpr int asinh(const int number)
        { return static_cast<int>(__builtin_asinh(number)); }
        inline constexpr long asinh(const long number)
        { return static_cast<long>(__builtin_asinh(number)); }
        inline constexpr long long asinh(const long long number)
        { return static_cast<long long>(__builtin_asinh(number)); }
        inline constexpr double asinh(const double& number)
        { return __builtin_asinh(number); }
        inline constexpr float asinh(const float& number)
        { return __builtin_asinhf(number); }
        inline constexpr long double asinh(const long double& number)
        { return __builtin_asinhl(number); }
    }
/*
 * Basic math functions
 */
    // absolute value
    template<typename T_number>
    constexpr T_number abs(const T_number& number)
    { /*return number<0 ? -number : number;*/
        return builtin::abs(number); }
    
    // acos = cos^(-1)
    template<typename T_number>
    constexpr T_number acos(const T_number& number)
    { return builtin::acos(number); }
    
    // acosh = cosh^(-1)
    template<typename T_number>
    constexpr T_number acosh(const T_number& number)
    { return builtin::acosh(number); }
    
    // asin = sin^(-1)
    template<typename T_number>
    constexpr T_number asin(const T_number& number)
    { return builtin::asin(number); }
    
    // asin = sin^(-1)
    template<typename T_number>
    constexpr T_number asinh(const T_number& number)
    { return builtin::asinh(number); }

}
 
// undefine __builtin_*
#ifdef _MSC_VER
#undef 
#endif

#endif
 