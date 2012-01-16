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
#include "tmp.hxx"
#include "types.hxx"

// force MSVC intrinsics for math functions
#ifdef _MSC_VER
// MSVC needs declarations for #pragma intrinsic
/*namespace kiss{namespace __implementation{*/extern "C"{
int abs(int);
double fabs(double);
long labs(long);
__int64 _abs64(__int64);
double acos(double);
float acosf(float);
double asin(double);
float asinf(float);
double atan(double);
float atanf(float);
double atan2(double,double);
float atan2f(float,float);
double ceil(double);
float ceilf(float);
double cos(double);
float cosf(float);
double cosh(double);
float coshf(float);
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
// these have no intrinsics
inline double logl(const long double x) { return log(static_cast<double>(x)); }
inline double sqrtl(const long double x) { return sqrt(static_cast<double>(x)); }
inline double acosh(const double x) { return log(x+sqrt(x*x-1)); }
inline float acoshf(const float x) { return logf(x+sqrtf(x*x-1)); }
inline long double acoshl(const long double x) { return logl(x+sqrtl(x*x-1)); }
inline double asinh(const double x) { return log(x+sqrt(x*x+1)); }
inline float asinhf(const float x) { return logf(x+sqrtf(x*x+1)); }
inline long double asinhl(const long double x) { return logl(1+sqrtl(x*x+1)); }
} // force MSVC to generate intrinsics
#pragma intrinsic(abs,   fabs,   labs, _abs64, \
                  acos,  acosf,  /*acosl,*/ \
                  /*acosh, acoshf, acoshl,*/ \
                  asin,  asinf,  /*asinl,*/ \
                  /*asinh, asinhf, asinhl,*/ \
                  atan,  atanf,  /*atanl,*/ \
                  atan2, atan2f, /*atan2l,*/ \
                  /*atanh, atanhf, atanhl, */ \
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
} } // define __builtin_* for MSVC
#define __builtin_abs         abs
#define __builtin_fabs        __implementation::fabs
#define __builtin_fabsf(X)    static_cast<float>(__implementation::fabs(X))
#define __builtin_fabsl(X)    __implementation::fabs(static_cast<double>(X))
#define __builtin_labs        __implementation::labs
#define __builtin_llabs       __implementation::_abs64
#define __builtin_acos        acos
#define __builtin_acosf       __implementation::acosf
#define __builtin_acosl(X)    acos(static_cast<double>(X))
#define __builtin_acosh       acosh
#define __builtin_acoshf      __implementation::acoshf
#define __builtin_acoshl      __implementation::acoshl
#define __builtin_asin        asin
#define __builtin_asinf       __implementation::asinf
#define __builtin_asinl(X)    asin(static_cast<double>(X))
#define __builtin_asinh       asinh
#define __builtin_asinhf      __implementation::asinhf
#define __builtin_asinhl      __implementation::asinhl
#define __builtin_atan        atan
#define __builtin_atanf       atanf
#define __builtin_atanl(X)    atan(static_cast<double>(X))
#define __builtin_atan2       atan2
#define __builtin_atan2f      atan2f
#define __builtin_atan2l(X,Y) atan2(static_cast<double(X), static_cast<double>(Y))
#define __builtin_ceil        ceil
#define __builtin_ceilf       ceilf
#define __builtin_ceill(X)    ceil(static_cast<double>(X))
#define __builtin_cosh        cosh
#define __builtin_coshf       coshf
#define __builtin_coshl(X)    cosh(static_cast<double>(X))
#define __builtin_cos         cos
#define __builtin_cosf        cosf
#define __builtin_cosl(X)     cos(static_cast<double>(X))
#define __builtin_exp         exp
#define __builtin_expf        expf
#define __builtin_expl(X)     exp(static_cast<double>(X))
#define __builtin_floor       floor
#define __builtin_floorf      floorf
#define __builtin_floorl(X)   floor(static_cast<double>(X))
#define __builtin_fmod        fmod
#define __builtin_fmodf       fmodf
#define __builtin_fmodl(X)    fmodl(static_cast<double>(X))
#define __builtin_log         log
#define __builtin_logf        logf
#define __builtin_logl(X)     log(static_cast<double>(X))
#define __builtin_log10       log10
#define __builtin_log10f      log10f
#define __builtin_log10l(X)   log10(static_cast<double>(X))
#define __builtin_pow         pow
#define __builtin_powf        powf
#define __builtin_powl(X)     pow(static_cast<double>(X))
#define __builtin_sin         sin
#define __builtin_sinf        sinf
#define __builtin_sinl(X)     sin(static_cast<double>(X))
#define __builtin_sinh        sinh
#define __builtin_sinhf       sinhf
#define __builtin_sinhl(X)    sinh(static_cast<double>(X))
#define __builtin_sqrt        sqrt
#define __builtin_sqrtf       sqrtf
#define __builtin_sqrtl(X)    sqrt(static_cast<double>(X))
#define __builtin_tan         tan
#define __builtin_tanf        tanf
#define __builtin_tanl(X)     tan(static_cast<double>(X))
#define __builtin_tanh        tanh
#define __builtin_tanhf       tanhf
#define __builtin_tanhl(X)    tanh(static_cast<double>(X))
#endif

namespace kiss
{
    // absolute value
    inline constexpr int abs(const int x)
    { return __builtin_abs(x); }
    //#ifndef __clang__
    inline constexpr long abs(const long x)
    { return __builtin_labs(x); }
    inline constexpr long long abs(const long long x)
    { return __builtin_llabs(x); }
    //#endif
    inline constexpr double abs(const double& x)
    { return __builtin_fabs(x); }
    inline constexpr float abs(const float& x)
    { return __builtin_fabsf(x); }
    inline constexpr long double abs(const long double& x)
    { return __builtin_fabsl(x); }
    // acos = cos^(-1)
    inline constexpr int acos(const int x)
    { return static_cast<int>(__builtin_acos(x)); }
    inline constexpr long acos(const long x)
    { return static_cast<long>(__builtin_acos(x)); }
    inline constexpr long long acos(const long long x)
    { return static_cast<long long>(__builtin_acos(x)); }
    inline constexpr double acos(const double x)
    { return __builtin_acos(x); }
    inline constexpr float acos(const float x)
    { return __builtin_acosf(x); }
    inline constexpr long double acos(const long double x)
    { return __builtin_acosl(x); }
    // acosh = cosh^(-1)
    inline constexpr int acosh(const int x)
    { return static_cast<int>(__builtin_acosh(x)); }
    inline constexpr long acosh(const long x)
    { return static_cast<long>(__builtin_acosh(x)); }
    inline constexpr long long acosh(const long long x)
    { return static_cast<long long>(__builtin_acosh(x)); }
    inline constexpr double acosh(const double x)
    { return __builtin_acosh(x); }
    inline constexpr float acoshf(const float x)
    { return __builtin_acosf(x); }
    inline constexpr long double acosh(const long double x)
    { return __builtin_acoshl(x); }
    // asin = sin^(-1)
    inline constexpr int asin(const int x)
    { return static_cast<int>(__builtin_asin(x)); }
    inline constexpr long asin(const long x)
    { return static_cast<long>(__builtin_asin(x)); }
    inline constexpr long long asin(const long long x)
    { return static_cast<long long>(__builtin_asin(x)); }
    inline constexpr double asin(const double x)
    { return __builtin_asin(x); }
    inline constexpr float asin(const float x)
    { return __builtin_asinf(x); }
    inline constexpr long double asin(const long double x)
    { return __builtin_asinl(x); }
    // asinh = sinh^(-1)
    inline constexpr int asinh(const int x)
    { return static_cast<int>(__builtin_asinh(x)); }
    inline constexpr long asinh(const long x)
    { return static_cast<long>(__builtin_asinh(x)); }
    inline constexpr long long asinh(const long long x)
    { return static_cast<long long>(__builtin_asinh(x)); }
    inline constexpr double asinh(const double x)
    { return __builtin_asinh(x); }
    inline constexpr float asinh(const float x)
    { return __builtin_asinhf(x); }
    inline constexpr long double asinh(const long double x)
    { return __builtin_asinhl(x); }
    // atan = tan^(-1)
    inline constexpr int atan(const int x)
    { return static_cast<int>(__builtin_atan(x)); }
    inline constexpr long atan(const long x)
    { return static_cast<long>(__builtin_atan(x)); }
    inline constexpr long long atan(const long long x)
    { return static_cast<long long>(__builtin_atan(x)); }
    inline constexpr double atan(const double x)
    { return __builtin_atan(x); }
    inline constexpr float atan(const float x)
    { return __builtin_atanf(x); }
    inline constexpr long double atan(const long double x)
    { return __builtin_atanl(x); }
    // atan2 = tan2^(-1)
    inline constexpr int atan2(const int x, const int y)
    { return static_cast<int>(__builtin_atan2(x, y)); }
    inline constexpr long atan2(const long x, const long y)
    { return static_cast<long>(__builtin_atan2(x, y)); }
    inline constexpr long long atan2(const long long x, const long long y)
    { return static_cast<long long>(__builtin_atan2(x, y)); }
    inline constexpr double atan2(const double x, const double y)
    { return __builtin_atan2(x, y); }
    inline constexpr float atan2(const float x, const float y)
    { return __builtin_atan2f(x, y); }
    inline constexpr long double asinh(const long double x, const long double y)
    { return __builtin_atan2l(x, y); }
    // ceil: round to +infinity
    inline constexpr int ceil(const int x)
    { return x; }
    inline constexpr long ceil(const long x)
    { return x; }
    inline constexpr long long ceil(const long long x)
    { return x; }
    inline constexpr double ceil(const double x)
    { return __builtin_ceil(x); }
    inline constexpr float ceil(const float x)
    { return __builtin_ceilf(x); }
    inline constexpr long double ceil(const long double x)
    { return __builtin_ceill(x); }
    // cosh
    inline constexpr int cosh(const int x)
    { return static_cast<int>(__builtin_cosh(x)); }
    inline constexpr long cosh(const long x)
    { return static_cast<long>(__builtin_cosh(x)); }
    inline constexpr long long cosh(const long long x)
    { return static_cast<long long>(__builtin_cosh(x)); }
    inline constexpr double cosh(const double x)
    { return __builtin_cosh(x); }
    inline constexpr float cosh(const float x)
    { return __builtin_coshf(x); }
    inline constexpr long double cosh(const long double x)
    { return __builtin_coshl(x); }
    // cos
    inline constexpr int cos(const int x)
    { return static_cast<int>(__builtin_cos(x)); }
    inline constexpr long cos(const long x)
    { return static_cast<long>(__builtin_cos(x)); }
    inline constexpr long long cos(const long long x)
    { return static_cast<long long>(__builtin_cos(x)); }
    inline constexpr double cos(const double x)
    { return __builtin_cos(x); }
    inline constexpr float cos(const float x)
    { return __builtin_cosf(x); }
    inline constexpr long double cos(const long double x)
    { return __builtin_cosl(x); }
    // exp
    inline constexpr int exp(const int x)
    { return static_cast<int>(__builtin_exp(x)); }
    inline constexpr long exp(const long x)
    { return static_cast<long>(__builtin_exp(x)); }
    inline constexpr long long exp(const long long x)
    { return static_cast<long long>(__builtin_exp(x)); }
    inline constexpr double exp(const double x)
    { return __builtin_exp(x); }
    inline constexpr float exp(const float x)
    { return __builtin_expf(x); }
    inline constexpr long double exp(const long double x)
    { return __builtin_expl(x); }
    // floor: round to -infinity
    template<typename T> typename kiss::enable_if<kiss::is_integral<T>::result, T>::type
    inline constexpr floor(const int x)
    { return x; }
    inline constexpr double floor(const double x)
    { return __builtin_floor(x); }
    inline constexpr float floor(const float x)
    { return __builtin_floorf(x); }
    inline constexpr long double floor(const long double x)
    { return __builtin_floorl(x); }
    // mod = (floating point) remainder of x%y
    template<typename T> typename kiss::enable_if<kiss::is_integral<T>::result, T>::type
    inline constexpr mod(const T x, const T y)
    { return x%y; }
    inline constexpr double mod(const double x, const double y)
    { return __builtin_fmod(x, y); }
    inline constexpr float mod(const float x, const float y)
    { return __builtin_fmodf(x, y); }
    inline constexpr long double mod(const long double x, const long double y)
    { return __builtin_fmodl(x, y); }
}

// undefine __builtin_* MSVC workarounds
#ifdef _MSC_VER
#undef __builtin_abs
#undef __builtin_fabs
#undef __builtin_fabsf
#undef __builtin_fabsl
#undef __builtin_labs
#undef __builtin_llabs
#undef __builtin_acos
#undef __builtin_acosf
#undef __builtin_acosl
#undef __builtin_asin
#undef __builtin_asinf
#undef __builtin_asinl
#undef __builtin_atan
#undef __builtin_atanf
#undef __builtin_atanl
#undef __builtin_atan2
#undef __builtin_atan2f
#undef __builtin_atan2l
#undef __builtin_ceil
#undef __builtin_ceilf
#undef __builtin_ceill
#undef __builtin_cosh
#undef __builtin_coshf
#undef __builtin_coshl
#undef __builtin_cos
#undef __builtin_cosf
#undef __builtin_cosl
#undef __builtin_exp
#undef __builtin_expf
#undef __builtin_expl
#undef __builtin_floor
#undef __builtin_floorf
#undef __builtin_floorl
#undef __builtin_fmod
#undef __builtin_fmodf
#undef __builtin_fmodl
#undef __builtin_log
#undef __builtin_logf
#undef __builtin_logl
#undef __builtin_log10
#undef __builtin_log10f
#undef __builtin_log10l
#undef __builtin_pow
#undef __builtin_powf
#undef __builtin_powl
#undef __builtin_sin
#undef __builtin_sinf
#undef __builtin_sinl
#undef __builtin_sinh
#undef __builtin_sinhf
#undef __builtin_sinhl
#undef __builtin_sqrt
#undef __builtin_sqrtf
#undef __builtin_sqrtl
#undef __builtin_tan
#undef __builtin_tanf
#undef __builtin_tanl
#undef __builtin_tanh
#undef __builtin_tanhf
#undef __builtin_tanhl
#endif

#endif
 