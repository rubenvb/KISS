/**
 * Written in 2013-2015 by Ruben Van Boxem <vanboxem.ruben@gmail.com>
 *
 * This file is dual licensed under the MIT and the University of Illinois Open
 * Source Licenses. See LICENSE.TXT for details.
 *
 ********************************************************************************************/

/*
 * test/test.h++
 *  Common testing functionality.
 **/

#include <type_traits.h++>

// testing types
class AbstractClass { virtual ~AbstractClass() = 0; };
using Array = char[1];
class Class
{
  Class(const Class&);
  Class& operator=(const Class&);
  int operator&() const { return 42; }
};
class Child : public Class {};
class OtherChild : public Child {};
class PrivateChild : Child {};
class EmptyClass {};
enum Enum {};
class Final final {};
using Function = void();
using FunctionPtr = void(*)();
using Function1 = void(int);
using Function2 = void(int, double);
class IncompleteClass;
class NonCopyableClass { NonCopyableClass(const NonCopyableClass&) = delete; };
class NotEmptyClass { int i; };
class TriviallyCopyableClass { TriviallyCopyableClass(); };
class VirtuallyDestructibleClass { int i; virtual ~VirtuallyDestructibleClass() { i=42; } };
union Union {};
struct ZeroBit { int : 0; };

template<template<typename T> class trait, typename U, int B = true>
void test_unary_trait()
{
  static_assert(trait<U>::value == B, "");
}
template<template<typename T> class trait, typename U, int B = true>
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
template<template<typename T1, typename T2> class trait, typename U, typename V, bool B = true>
void test_binary_trait_cv()
{
  static_assert(trait<U, V>::value == B, "");
  static_assert(trait<U, const V>::value == B, "");
  static_assert(trait<U, volatile V>::value == B, "");
  static_assert(trait<U, const volatile V>::value == B, "");
  static_assert(trait<const U, V>::value == B, "");
  static_assert(trait<const U, const V>::value == B, "");
  static_assert(trait<const U, volatile V>::value == B, "");
  static_assert(trait<const U, const volatile V>::value == B, "");
  static_assert(trait<volatile U, V>::value == B, "");
  static_assert(trait<volatile U, const V>::value == B, "");
  static_assert(trait<volatile U, volatile V>::value == B, "");
  static_assert(trait<volatile U, const volatile V>::value == B, "");
  static_assert(trait<const volatile U, const V>::value == B, "");
  static_assert(trait<const volatile U, volatile V>::value == B, "");
  static_assert(trait<const volatile U, const volatile V>::value == B, "");
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
