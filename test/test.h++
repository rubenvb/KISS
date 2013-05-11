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
 * test/test.h++
 *  Common testing functionality.
 **/

#include <types.h++>

// testing types
class AbstractClass { virtual void foo() = 0; };
using Array = char[1];
class Class
{
  Class(const Class&);
  Class& operator=(const Class&);
  int operator&() const { return 42; }
};
enum Enum {};
using Function = void();
using FunctionPtr = void(*)();
using Function1 = void(int);
using Function2 = void(int, double);
class IncompleteClass;
union Union {};

template<template<typename T> class trait, typename U, bool B = true>
void test_unary_trait()
{
  static_assert(trait<U>::value == B, "");
}
template<template<typename T> class trait, typename U, bool B = true>
void test_unary_trait_cv()
{
  static_assert(trait<U>::value == B, "");
  static_assert(trait<const U>::value == B, "");
  static_assert(trait<volatile U>::value == B, "");
  static_assert(trait<const volatile U>::value == B, "");
}

template<template<typename T1, typename T2> class trait, typename U, typename V, bool B = true>
void test_binary_trait()
{
  static_assert(trait<U, V>::value == B, "");
}

template<template<typename T> class trait, typename U, typename V, bool B = true>
void test_nested_type_trait()
{
  static_assert(kiss::is_same<typename trait<U>::type, V>::value == B, "");
}
template<template<typename T> class trait, typename U, typename V, bool B = true>
void test_nested_type_trait_cv()
{
  static_assert(kiss::is_same<typename trait<U>::type, V>::value == B, "");
  static_assert(kiss::is_same<typename trait<const U>::type, V>::value == B, "");
  static_assert(kiss::is_same<typename trait<volatile U>::type, V>::value == B, "");
  static_assert(kiss::is_same<typename trait<const volatile U>::type, V>::value == B, "");
}
