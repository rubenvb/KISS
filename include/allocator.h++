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

/*
 * Mallocator - http://blogs.msdn.com/b/vcblog/archive/2008/08/28/the-mallocator.aspx
 **/
// The following headers are required for all allocators.
#include <stddef.h>  // Required for size_t and ptrdiff_t and NULL
#include <new>       // Required for placement new and std::bad_alloc
#include <stdexcept> // Required for std::length_error

// The following headers contain stuff that Mallocator uses.
#include <stdlib.h>  // For malloc() and free()
#include <iostream>  // For std::cout
#include <ostream>   // For std::endl

template<typename T> class Mallocator
{
public:
  // The following will be the same for virtually all allocators.
  typedef T * pointer;
  typedef const T * const_pointer;
  typedef T& reference;
  typedef const T& const_reference;
  typedef T value_type;
  typedef size_t size_type;
  typedef ptrdiff_t difference_type;

  T* address(T& r) const
  {
    return &r;
  }

  const T* address(const T& s) const
  {
    return &s;
  }

  size_t max_size() const
  {
    return static_cast<size_type>(-1) / sizeof(T);
  }

  // The following must be the same for all allocators.
  template <typename U> struct rebind
  {
    typedef Mallocator<U> other;
  };

  bool operator!=(const Mallocator& other) const
  {
    return !(*this == other);
  }

  void construct(T * const p, const T& t) const
  {
    void* const pv = static_cast<void*>(p);

    new (pv) T(t);
  }

  void destroy(T * const p) const; // Defined below.

  // Returns true if and only if storage allocated from *this
  // can be deallocated from other, and vice versa.
  // Always returns true for stateless allocators.
  bool operator==(const Mallocator& other) const
  {
    return true;
  }

  // Default constructor, copy constructor, rebinding constructor, and destructor.
  // Empty for stateless allocators.
  Mallocator() { }

  Mallocator(const Mallocator&) { }

  template<typename U> Mallocator(const Mallocator<U>&) { }

  ~Mallocator() { }

  // The following will be different for each allocator.
  T* allocate(const size_t n) const
  {
    // Mallocator prints a diagnostic message to demonstrate
    // what it's doing. Real allocators won't do this.
    std::cout << "Allocating " << n << (n == 1 ? " object" : "objects")
              << " of size " << sizeof(T) << "." << std::endl;

    // The return value of allocate(0) is unspecified.
    // Mallocator returns NULL in order to avoid depending
    // on malloc(0)'s implementation-defined behavior
    // (the implementation can define malloc(0) to return NULL,
    // in which case the bad_alloc check below would fire).
    // All allocators can return NULL in this case.
    if(n == 0)
    {
      return NULL;
    }

    // All allocators should contain an integer overflow check.
    // The Standardization Committee recommends that std::length_error
    // be thrown in the case of integer overflow.
    if(n > max_size())
    {
      throw std::length_error("Mallocator<T>::allocate() - Integer overflow.");
    }

    // Mallocator wraps malloc().
    void* const pv = malloc(n * sizeof(T));
    // Allocators should throw std::bad_alloc in the case of memory allocation failure.
    if (pv == NULL)
    {
      throw std::bad_alloc();
    }
    return static_cast<T*>(pv);
  }

  void deallocate(T* const p, const size_t n) const
  {
    // Mallocator prints a diagnostic message to demonstrate
    // what it's doing. Real allocators won't do this.
    std::cout << "Deallocating " << n << (n == 1 ? " object" : "objects")
              << " of size " << sizeof(T) << "." << std::endl;

    // Mallocator wraps free().
    free(p);
  }

  // The following will be the same for all allocators that ignore hints.
  template<typename U> T* allocate(const size_t n, const U* /* const hint */) const
  {
    return allocate(n);
  }

  // Allocators are not required to be assignable, so
  // all allocators should have a private unimplemented
  // assignment operator. Note that this will trigger the
  // off-by-default (enabled under /Wall) warning C4626
  // "assignment operator could not be generated because a
  // base class assignment operator is inaccessible" within
  // the STL headers, but that warning is useless.
private:
  Mallocator& operator=(const Mallocator&);
};

#endif
