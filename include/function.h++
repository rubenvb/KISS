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
 * function.h++
 *  Equivalent to C++'s std::function.
 **/

#ifndef KISS_FUNCTION_H
#define KISS_FUNCTION_H

#include "config.h++"
#include "utility.h++"

/*
 *from Lounge<C++>
 **/

namespace kiss
{
  namespace implementation
  {
    template<class ret, class ...param_types)
    class function_interface
    {
    public:
      virtual ret operator()(param_types... ps) = 0;
      virtual ~function_interface() = 0;
    };

    template<class functor, class ret, class ...param_types>
    class function_impl : function_interface<ret, param_types...>
    {
      functor data;
    public:
      function_impl(functor d)
      : data(kiss::move(d))
      {}
      virtual ret operator()(param_types... ps) { return data(); }
    };
  }

  template<class ret, class ...param_types>
  class function
  {
    std::unique_ptr<function_interface<ret, param_types...>> ptr;
  public:
    template<class functor>
    function(functor d)
    : ptr(new function_impl<functor, ret, param_types...>(kiss::move(d))
    {}
    ret operator()(param_types... ps) {return (*ptr)();}
  };
}

#endif
