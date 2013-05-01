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
 * assert.h++
 * Assertion macro which can be enabled by defining KISS_ASSERT
 *
 **/

#ifndef KISS_ASSERT_H
#define KISS_ASSERT_H

namespace kiss
{
  namespace C
  {
    extern "C" { void exit(int); }
  }
  namespace implementation
  {
    inline void assert(bool condition, const char*)
    {
      if(!condition)
      {
        //TODO: output
        C::exit(1);
      }
    }
  }
}
#ifdef KISS_ASSERT
#define assert
#else

#endif

#endif
