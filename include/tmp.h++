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
 * tmp.h++
 *  Template meta programming constructs.
 **/

#ifndef KISS_TMP
#define KISS_TMP

#include "config.h++"

namespace kiss
{
  namespace implementation
  {
    // enable_if
    template<bool, typename T = void> struct enable_if {};
    template<typename T> struct enable_if<true, T> { typedef T type; };
    // disable_if
    template<bool, typename T = void> struct disable_if {};
    template<typename T> struct disable_if<false, T> { typedef T type; };
  }
  // enable_if
  template<bool Condition, typename T = void> using enable_if = typename implementation::enable_if<Condition, T>::type;
  // disable_if
  template<bool Condition, typename T = void> using disable_if = typename implementation::disable_if<Condition, T>::type;
}

#endif
