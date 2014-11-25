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
 * error.h++
 *  Fundamental error types.
 *  KISS error exceptions.
 **/

#ifndef KISS_ERROR_H
#define KISS_ERROR_H

#include "config.h++"

namespace kiss {
  class error;

  class unimplemented
  {
  public:
    unimplemented() {}
    void print_message() { throw -1; }
  };

  class error
  {
  public:
      virtual void print_message() { throw unimplemented(); }
  };
}

#endif
