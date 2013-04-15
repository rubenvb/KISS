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
 * math.h++
 *  Math functions.
 **/

#ifndef KISS_MATH
#define KISS_MATH

#include "config.h++"
#include "error.hxx"
#include "tmp.hxx"
#include "types.hxx"

// define template for all overloads; better than templates usability-wise


#define OVERLOAD_FLOAT_MATH_FUNCTION(function) \
  inline float function(float x) { return C::function##f(x); } \
  inline double function(double x) { return C::function(x); } \
  inline long double function(long double x) { return C::function##l(x); }
#define OVERLOAD_INT_MATH_FUNCTION(function) \
  inline int function(int x) { return C::function(x); } \
  inline long int function(long int x) { return C::##ll##function(x); } \
  inline long long int function(long long int x) { return C::##ll##function(x); }

namespace kiss
{
/*
 * These are taken directly from the C Standard and prevents necessary inclusion of a C header
 **/
  namespace C
  {
    extern "C"
    {
    // Trigonometric
    double acos(double x);
    float acosf(float x);
    long double acosl(long double x);

    double asin(double x);
    float asinf(float x);
    long double asinl(long double x);

    double asin(double x);
    float asinf(float x);
    long double asinl(long double x);

    double atan(double x);
    float atanf(float x);
    long double atanl(long double x);

    double atan2(double y, double x);
    float atan2f(float y, float x);
    long double atan2l(long double y, long double x);

    double cos(double x);
    float cosf(float x);
    long double cosl(long double x);

    double sin(double x);
    float sinf(float x);
    long double sinl(long double x);

    double tan(double x);
    float tanf(float x);
    long double tanl(long double x);

    // Hyperbolic functions
    double acosh(double x);
    float acoshf(float x);
    long double acoshl(long double x);

    double asinh(double x);
    float asinhf(float x);
    long double asinhl(long double x);

    double atanh(double x);
    float atanhf(float x);
    long double atanhl(long double x);

    double cosh(double x);
    float coshf(float x);
    long double coshl(long double x);

    double sinh(double x);
    float sinhf(float x);
    long double sinhl(long double x);

    double tanh(double x);
    float tanhf(float x);
    long double tanhl(long double x);

    // Exponential and logarithmic functions
    double exp(double x);
    float expf(float x);
    long double expl(long double x);

    double exp2(double x);
    float exp2f(float x);
    long double exp2l(long double x);

    double expm1(double x);
    float expm1f(float x);
    long double expm1l(long double x);

    double frexp(double value, int* exp);
    float frexpf(float value, int* exp);
    long double frexpl(long double value, int* exp);

    int ilogb(double x);
    int ilogbf(float x);
    int ilogbl(long double x);

    double ldexp(double x, int exp);
    float ldexpf(float x, int exp);
    long double ldexpl(long double x, int exp);

    double log(double x);
    float logf(float x);
    long double logl(long double x);

    double log10(double x);
    float log10f(float x);
    long double log10l(long double x);

    double log1p(double x);
    float log1pf(float x);
    long double log1pl(long double x);

    double log2(double x);
    float log2f(float x);
    long double log2l(long double x);

    double logb(double x);
    float logbf(float x);
    long double logbl(long double x);

    double modf(double value, double* iptr);
    float modff(float value, float* iptr);
    long double modfl(long double value, long double* iptr);

    double scalbn(double x, int n);
    float scalbnf(float x, int n);
    long double scalbnl(long double x, int n);

    // Power and absolute-value functions
    double cbrt(double x);
    float cbrtf(float x);
    long double cbrtl(long double x);

    double fabs(double x);
    float fabsf(float x);
    long double fabsl(long double x);

    double pow(double x, double y);
    float powf(float x, float y);
    long double powl(long double x, long double y);

    double sqrt(double x);
    float sqrtf(float x);
    long double sqrtl(long double x);

    // Error and gamma functions
    double erf(double x);
    float erff(float x);
    long double erfl(long double x);

    double erfc(double x);
    float erfcf(float x);
    long double erfcl(long double x);

    double lgamma(double x);
    float lgammaf(float x);
    long double lgammal(long double x);

    double tgamma(double x);
    float tgammaf(float x);
    long double tgammal(long double x);

    // Nearest integer functions
    double ceil(double x);
    float ceilf(float x);
    long double ceill(long double x);

    double floor(double x);
    float floorf(float x);
    long double floorl(long double x);

    double nearbyint(double x);
    float nearbyintf(float x);
    long double nearbyintl(long double x);

    double rint(double x);
    float rintf(float x);
    long double rintl(long double x);

    long int lrint(double x);
    long int lrintf(float x);
    long int lrintl(long double x);
    long long int llrint(double x);
    long long int llrintf(float x);
    long long int llrintl(long double x);

    double round(double x);
    float roundf(float x);
    long double roundl(long double x);

    long int lround(double x);
    long int lroundf(float x);
    long int lroundl(long double x);
    long long int llround(double x);
    long long int llroundf(float x);
    long long int llroundl(long double x);

    double trunc(double x);
    float truncf(float x);
    long double truncl(long double x);

    double fmod(double x, double y);
    float fmodf(float x, float y);
    long double fmodl(long double x, long double y);

    double remainder(double x, double y);
    float remainderf(float x, float y);
    long double remainderl(long double x, long double y);

    // The remquo functions
    double remquo(double x, double y, int* quo);
    float remquof(float x, float y, int* quo);
    long double remquol(long double x, long double y, int* quo);

    // Manipulation functions
    double copysign(double x, double y);
    float copysignf(float x, float y);
    long double copysignl(long double x, long double y);

    double nan(const char* tagp);
    float nanf(const char* tagp);
    long double nanl(const char* tagp);

    double nextafter(double x, double y);
    float nextafterf(float x, float y);
    long double nextafterl(long double x, long double y);

    double nexttoward(double x, long double y);
    float nexttowardf(float x, long double y);
    long double nexttowardl(long double x, long double y);

    // Maximum, minimum, and positive difference functions
    double fdim(double x, double y);
    float fdimf(float x, float y);
    long double fdiml(long double x, long double y);

    double fmax(double x, double y);
    float fmaxf(float x, float y);
    long double fmaxl(long double x, long double y);

    double fmin(double x, double y);
    float fminf(float x, float y);
    long double fminl(long double x, long double y);

    // Floating multiply-add
    double fma(double x, double y, double z);
    float fmaf(float x, float y, float z);
    long double fmal(long double x, long double y, long double z);
    }
  }
/*
 * Trigonometric functions
 */
  inline float acos(float x) { return C::acosf(x); } \
  inline double acos(double x) { return C::acos(x); } \
  inline long double acos(long double x) { return C::acosl(x); }

  inline float asin(float x) { return C::asinf(x); } \
  inline double asin(double x) { return C::asin(x); } \
  inline long double asin(long double x) { return C::asinl(x); }

  inline float atan(float x) { return C::atanf(x); } \
  inline double atan(double x) { return C::atan(x); } \
  inline long double atan(long double x) { return C::atanl(x); }

  inline float atan2(float x, float y) { return C::atan2f(x, y); } \
  inline double atan2(double x, double y) { return C::atan2(x, y); } \
  inline long double atan2(long double x, long double y) { return C::atan2l(x, y); }

  inline float cos(float x) { return C::cosf(x); } \
  inline double cos(double x) { return C::cos(x); } \
  inline long double cos(long double x) { return C::cosl(x); }

  inline float sin(float x) { return C::sinf(x); } \
  inline double sin(double x) { return C::sin(x); } \
  inline long double sin(long double x) { return C::sinl(x); }

  inline float tan(float x) { return C::tanf(x); } \
  inline double tan(double x) { return C::tan(x); } \
  inline long double tan(long double x) { return C::tanl(x); }

  inline float acosh(float x) { return C::acoshf(x); } \
  inline double acosh(double x) { return C::acosh(x); } \
  inline long double acosh(long double x) { return C::acoshl(x); }

  inline float asinh(float x) { return C::asinhf(x); } \
  inline double asinh(double x) { return C::asinh(x); } \
  inline long double asinh(long double x) { return C::asinhl(x); }

  inline float atanh(float x) { return C::atanhf(x); } \
  inline double atanh(double x) { return C::atanh(x); } \
  inline long double atanh(long double x) { return C::atanhl(x); }

  inline float sinh(float x) { return C::sinhf(x); } \
  inline double sinh(double x) { return C::sinh(x); } \
  inline long double sinh(long double x) { return C::sinhl(x); }

  inline float tanh(float x) { return C::tanhf(x); } \
  inline double tanh(double x) { return C::tanh(x); } \
  inline long double tanh(long double x) { return C::tanhl(x); }

  inline float exp(float x) { return C::expf(x); }
  inline double exp(double x) { return C::exp(x); }
  inline long double exp(long double x) { return C::expl(x); }

  inline float exp2(float x) { return C::exp2f(x); }
  inline double exp2(double x) { return C::exp2(x); }
  inline long double exp2(long double x) { return C::exp2l(x); }

  inline float expm1(float x) { return C::expm1f(x); }
  inline double exp1m(double x) { return C::expm1(x); }
  inline long double exp1m(long double x) { return C::expm1l(x); }

  inline float frexp(float x, int* exp) { return C::frexpf(x, exp); }
  inline double frexp(double x, int* exp) { return C::frexp(x, exp); }
  inline long double frexp(long double x, int* exp) { return C::frexpl(x, exp); }

  inline int ilogb(float x) { return C::ilogbf(x); }
  inline int ilogb(double x) { return C::ilogb(x); }
  inline int ilogb(long double x) { return C::ilogbl(x); }

  inline float ldexp(float x, int exp) { return C::ldexpf(x, exp); }
  inline double ldexp(double x, int exp) { return C::ldexp(x, exp); }
  inline long double ldexp(long double x, int exp) { return C::ldexpl(x, exp); }

  inline float log(float x) { return C::logf(x); }
  inline double log(double x) { return C::log(x); }
  inline long double log(long double x) { return C::logl(x); }

  inline float log10(float x) { return C::log10f(x); }
  inline double log10(double x) { return C::log10(x); }
  inline long double log10(long double x) { return C::log10l(x); }

  inline float log1p(float x) { return C::log1pf(x); }
  inline double log1p(double x) { return C::log1p(x); }
  inline long double log1p(long double x) { return C::log1pl(x); }

  inline float log2(float x) { return C::log2f(x); }
  inline double log2(double x) { return C::log2(x); }
  inline long double log2(long double x) { return C::log2l(x); }

  inline float logb(float x) { return C::logbf(x); }
  inline double logb(double x) { return C::logb(x); }
  inline long double logb(long double x) { return C::logbl(x); }

  inline float modf(float x, float* iptr) { return C::modff(x, iptr); }
  inline double modf(double x, double* iptr) { return C::modf(x, iptr); }
  inline long double modf(long double x, long double* iptr) { return C::modfl(x, iptr); }

  inline float scalbn(float x, int n) { return C::scalbnf(x, n); }
  inline double scalbn(double x, int n) { return C::scalbn(x, n); }
  inline long double scalbn(long double x, int n) { return C::scalbnl(x, n); }

  inline float cbrt(float x) { return C::cbrtf(x); }
  inline double cbrt(double x) { return C::cbrt(x); }
  inline long double cbrt(long double x) { return C::cbrtl(x); }

  // fabs-> abs
  inline float abs(float x) { return C::fabsf(x); }
  inline double abs(double x) { return C::fabs(x); }
  inline long double abs(long double x) { return C::fabsl(x); }

  inline float pow(float x, float y) { return C::powf(x, y); }
  inline double pow(double x, double y) { return C::pow(x, y); }
  inline long double pow(long double x, long double y) { return C::powl(x, y); }

  inline float sqrt(float x) { return C::sqrtf(x); }
  inline double sqrt(double x) { return C::sqrt(x); }
  inline long double sqrt(long double x) { return C::sqrtl(x); }

  inline float erf(float x) { return C::erff(x); }
  inline double erf(double x) { return C::erf(x); }
  inline long double erf(long double x) { return C::erfl(x); }

  inline float erfc(float x) { return C::erfcf(x); }
  inline double erfc(double x) { return C::erfc(x); }
  inline long double erfc(long double x) { return C::erfcl(x); }

  inline float lgamma(float x) { return C::lgammaf(x); }
  inline double lgamma(double x) { return C::lgamma(x); }
  inline long double lgamma(long double x) { return C::lgammal(x); }

  inline float tgamma(float x) { return C::tgammaf(x); }
  inline double tgamma(double x) { return C::tgamma(x); }
  inline long double tgamma(long double x) { return C::tgammal(x); }

  inline float ceil(float x) { return C::ceilf(x); }
  inline double ceil(double x) { return C::ceil(x); }
  inline long double ceil(long double x) { return C::ceill(x); }

  inline float floor(float x) { return C::floorf(x); }
  inline double floor(double x) { return C::floor(x); }
  inline long double floor(long double x) { return C::floorl(x); }

  inline float nearbyint(float x) { return C::nearbyintf(x); }
  inline double nearbyint(double x) { return C::nearbyint(x); }
  inline long double nearbyint(long double x) { return C::nearbyintl(x); }

  inline float rint(float x) { return C::rintf(x); }
  inline double rint(double x) { return C::rint(x); }
  inline long double rint(long double x) { return C::rintl(x); }

  inline long int lrint(float x) { return C::lrintf(x); }
  inline long int lrint(double x) { return C::lrint(x); }
  inline long int lrint(long double x) { return C::lrintl(x); }
  inline long long int llrint(float x) { return C::llrintf(x); }
  inline long long int llrint(double x) { return C::llrint(x); }
  inline long long int llrint(long double x) { return C::llrintl(x); }

  inline float round(float x) { return C::roundf(x); }
  inline double round(double x) { return C::round(x); }
  inline long double round(long double x) { return C::roundl(x); }

  inline long int lround(float x) { return C::lroundf(x); }
  inline long int lround(double x) { return C::lround(x); }
  inline long int lround(long double x) { return C::lroundl(x); }
  inline long long int llround(float x) { return C::llroundf(x); }
  inline long long int llround(double x) { return C::llround(x); }
  inline long long int llround(long double x) { return C::llroundl(x); }

  inline float trunc(float x) { return C::truncf(x); }
  inline double trunc(double x) { return C::trunc(x); }
  inline long double trunc(long double x) { return C::truncl(x); }

  // fmod->mod
  inline float mod(float x, float y) { return C::fmodf(x, y); }
  inline double mod(double x, double y) { return C::fmod(x, y); }
  inline long double mod(long double x, long double y) { return C::fmodl(x, y); }

  inline float remainder(float x, float y) { return C::remainderf(x, y); }
  inline double remainder(double x, double y) { return C::remainder(x, y); }
  inline long double remainder(long double x, long double y) { return C::remainderl(x, y); }

  inline float remquo(float x, float y, int* quo) { return C::remquof(x, y, quo); }
  inline double remquo(double x, double y, int* quo) { return C::remquo(x, y, quo); }
  inline long double remquo(long double x, long double y, int* quo) { return C::remquol(x, y, quo); }

  inline float copysign(float x, float y) { return C::copysignf(x, y); }
  inline double copysign(double x, double y) { return C::copysign(x, y); }
  inline long double copysign(long double x, long double y) { return C::copysignl(x, y); }

//TODO
  //inline float nan( x) { return C::nanf(x); }
  //inline double nan (double x) { return C::nan(x); }
  //inline long double nan(long double x) { return C::nanl(x); }

  inline float nextafter(float x, float y) { return C::nextafterf(x, y); }
  inline double nextafter(double x, double y) { return C::nextafter(x, y); }
  inline long double nextafter(long double x, long double y) { return C::nextafterl(x, y); }

  inline float nexttoward(float x, float y) { return C::nexttowardf(x, y); }
  inline double nexttoward(double x, double y) { return C::nexttoward(x, y); }
  inline long double nexttoward(long double x, long double y) { return C::nexttowardl(x, y); }

  inline float fdim(float x, float y) { return C::fdimf(x, y); }
  inline double fdim(double x, double y) { return C::fdim(x, y); }
  inline long double fdim(long double x, long double y) { return C::fdiml(x, y); }

  // fmax->max
  inline float max(float x, float y) { return C::fmaxf(x, y); }
  inline double max(double x, double y) { return C::fmax(x, y); }
  inline long double max(long double x, long double y) { return C::fmaxl(x, y); }

  // fmin->min
  inline float min(float x, float y) { return C::fminf(x, y); }
  inline double min(double x, double y) { return C::fmin(x, y); }
  inline long double min(long double x, long double y) { return C::fminl(x, y); }

  inline float fma(float x, float y, float z) { return C::fmaf(x, y, z); }
  inline double fma(double x, double y, double z) { return C::fma(x, y, z); }
  inline long double fma(long double x, long double y, long double z) { return C::fmal(x, y, z); }
}

#endif
