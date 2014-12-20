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
 * allocator.h++
 *  KISS allocators:
 *   - default
 *   - stack
 *   - thread_private
 **/

#ifndef KISS_ALLOCATOR_H
#define KISS_ALLOCATOR_H

#include "config.h++"

#include "exceptions.h++"
#include "types.h++"

namespace kiss
{
  namespace C
  {
    extern "C"
    {
#ifdef _WIN32
    void* __stdcall GetProcessHeap();
      void* __stdcall HeapAlloc(void*, uint32, size_type);
      bool __stdcall HeapFree(void*, uint32, void*);
#else
      void* malloc(size_type);
#endif
    }
  }
#endif

  template <typename T>
  class allocator
  {
    T* allocate(size_type number_of_objects)
    {
#ifdef _WIN32
      T* result = C::HeapAlloc(C::GetProcessHeap(), 0, number_of_objects*sizeof(T));
#else
      T* result = C::malloc(number_of_bytes);
#endif
      if(result == nullptr)
        throw bad_alloc();
      else
        return result;
    }
    void deallocate(T* allocated_memory, size_type number_of_objects)
    {
#ifdef _WIN32
      C::HeapFree(C::GetProcessHeap(), 0, allocated_memory);
#else
      C::free(allocated_memory);
#endif
    }

    size_type max_size() { return static_cast<T>(-1) / sizeof(T); }
  };
}

#endif
