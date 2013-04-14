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
  * config.hxx
  *  Configuration defines.
  */

#ifndef __KISS_CONFIG
#define __KISS_CONFIG

// has_feature workaround
#if !defined(__clang__)
#define __has_feature(X) 0
#endif

#if defined(__GNUC__)
#define __is_literal __is_literal_type
#endif

// constexpr workaround
#if defined(_MSC_VER) // || (defined(__clang__) && !__has_feature(cxx_constexpr))
#define constexpr
#endif

#endif
