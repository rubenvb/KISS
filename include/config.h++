/**
 * Written in 2013-2015 by Ruben Van Boxem <vanboxem.ruben@gmail.com>
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
 * config.h++
 *  Miscellaneous configuration.
 **/

#ifndef KISS_CONFIG_H
#define KISS_CONFIG_H

#if defined(_MSC_VER) && !defined(__clang__) && !defined(__ICL)
//#error "this shit is broken anyway"
#define constexpr const
#define __alignof__(type) __alignof(type)
#define alignas(number) __declspec(align(number))
typedef wchar_t       char16_t;
typedef unsigned long char32_t;
#endif

namespace kiss
{
  constexpr int major_version = 0;
  constexpr int minor_version = 1;
  constexpr int version = major_version*100+minor_version;
}

#endif
