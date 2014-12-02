/**
 * Written in 2013-2015 by Ruben Van Boxem <vanboxem.ruben@gmail.com>
 *
 * This file is dual licensed under the MIT and the University of Illinois Open
 * Source Licenses. See LICENSE.TXT for details.
 *
 ********************************************************************************************/

/*
 * test/types/miscellaneous.c++
 **/

#include <type_traits.h++>

#include "../test.h++"

using namespace kiss;

int main()
{
//TODO addressof

// common_type
  static_assert(is_same<common_type<int>::type, int>(), "");
  static_assert(is_same<common_type<char>::type, char>(), "");

  static_assert(is_same<common_type<double, char>::type, double>(), "");
  static_assert(is_same<common_type<short, char>::type, int>(), "");

  static_assert(is_same<common_type<double, char, long long>::type, double>(), "");
  static_assert(is_same<common_type<unsigned, char, long long>::type, long long>(), "");

  // is_convertible
  test_binary_trait<is_convertible, void, void>();
  test_binary_trait<is_convertible, const void, void>();
  test_binary_trait<is_convertible, void, const void>();
  test_binary_trait<is_convertible, const void, const void>();

  test_binary_trait<is_convertible, void, Function, false>();
  test_binary_trait<is_convertible, const void, Function, false>();

  test_binary_trait<is_convertible, void, Function&, false>();
  test_binary_trait<is_convertible, const void, Function&, false>();

  test_binary_trait<is_convertible, void, Function*, false>();
  test_binary_trait<is_convertible, void, Function* const, false>();
  test_binary_trait<is_convertible, const void, Function*, false>();
  test_binary_trait<is_convertible, const void, Function* const, false>();

  test_binary_trait<is_convertible, void, Array, false>();
  test_binary_trait<is_convertible, void, const Array, false>();
  test_binary_trait<is_convertible, const void, Array, false>();
  test_binary_trait<is_convertible, const void, const Array, false>();

  test_binary_trait<is_convertible, void, Array&, false>();
  test_binary_trait<is_convertible, void, const Array&, false>();
  test_binary_trait<is_convertible, const void, Array&, false>();
  test_binary_trait<is_convertible, const void, const Array&, false>();

  test_binary_trait<is_convertible, void, char, false>();
  test_binary_trait<is_convertible, void, const char, false>();
  test_binary_trait<is_convertible, const void, char, false>();
  test_binary_trait<is_convertible, const void, const char, false>();

  test_binary_trait<is_convertible, void, char&, false>();
  test_binary_trait<is_convertible, void, const char&, false>();
  test_binary_trait<is_convertible, const void, char&, false>();
  test_binary_trait<is_convertible, const void, const char&, false>();

  test_binary_trait<is_convertible, void, char*, false>();
  test_binary_trait<is_convertible, void, const char*, false>();
  test_binary_trait<is_convertible, const void, char*, false>();
  test_binary_trait<is_convertible, const void, const char*, false>();

  test_binary_trait<is_convertible, Function, void, false>();
  test_binary_trait<is_convertible, Function, const void, false>();

  test_binary_trait<is_convertible, Function, Function, false>();

  test_binary_trait<is_convertible, Function, Function&>();

  test_binary_trait<is_convertible, Function, Function*>();
  test_binary_trait<is_convertible, Function, Function* const>();

  test_binary_trait<is_convertible, Function, Array, false>();
  test_binary_trait<is_convertible, Function, const Array, false>();

  test_binary_trait<is_convertible, Function, Array&, false>();
  test_binary_trait<is_convertible, Function, const Array&, false>();

  test_binary_trait<is_convertible, Function, char, false>();
  test_binary_trait<is_convertible, Function, const char, false>();

  test_binary_trait<is_convertible, Function, char&, false>();
  test_binary_trait<is_convertible, Function, const char&, false>();

  test_binary_trait<is_convertible, Function, char*, false>();
  test_binary_trait<is_convertible, Function, const char*, false>();

  test_binary_trait<is_convertible, Function&, void, false>();
  test_binary_trait<is_convertible, Function&, const void, false>();

  test_binary_trait<is_convertible, Function&, Function, false>();

  test_binary_trait<is_convertible, Function&, Function&>();

  test_binary_trait<is_convertible, Function&, Function*>();
  test_binary_trait<is_convertible, Function&, Function* const>();

  test_binary_trait<is_convertible, Function&, Array, false>();
  test_binary_trait<is_convertible, Function&, const Array, false>();

  test_binary_trait<is_convertible, Function&, Array&, false>();
  test_binary_trait<is_convertible, Function&, const Array&, false>();

  test_binary_trait<is_convertible, Function&, char, false>();
  test_binary_trait<is_convertible, Function&, const char, false>();

  test_binary_trait<is_convertible, Function&, char&, false>();
  test_binary_trait<is_convertible, Function&, const char&, false>();

  test_binary_trait<is_convertible, Function&, char*, false>();
  test_binary_trait<is_convertible, Function&, const char*, false>();

  test_binary_trait<is_convertible, Function*, void, false>();
  test_binary_trait<is_convertible, Function*const, void, false>();
  test_binary_trait<is_convertible, Function*, const void, false>();
  test_binary_trait<is_convertible, Function*const, const void, false>();

  test_binary_trait<is_convertible, Function*, Function, false>();
  test_binary_trait<is_convertible, Function*const, Function, false>();

  test_binary_trait<is_convertible, Function*, Function&, false>();
  test_binary_trait<is_convertible, Function*const, Function&, false>();

  test_binary_trait<is_convertible, Function*, Function*>();
  test_binary_trait<is_convertible, Function*, Function* const>();
  test_binary_trait<is_convertible, Function*const, Function*>();
  test_binary_trait<is_convertible, Function*const, Function*const >();

  test_binary_trait<is_convertible, Function*, Array, false>();
  test_binary_trait<is_convertible, Function*, const Array, false>();
  test_binary_trait<is_convertible, Function*const, Array, false>();
  test_binary_trait<is_convertible, Function*const, const Array, false>();

  test_binary_trait<is_convertible, Function*, Array&, false>();
  test_binary_trait<is_convertible, Function*, const Array&, false>();
  test_binary_trait<is_convertible, Function*const, Array&, false>();
  test_binary_trait<is_convertible, Function*const, const Array&, false>();

  test_binary_trait<is_convertible, Function*, char, false>();
  test_binary_trait<is_convertible, Function*, const char, false>();
  test_binary_trait<is_convertible, Function*const, char, false>();
  test_binary_trait<is_convertible, Function*const, const char, false>();

  test_binary_trait<is_convertible, Function*, char&, false>();
  test_binary_trait<is_convertible, Function*, const char&, false>();
  test_binary_trait<is_convertible, Function*const, char&, false>();
  test_binary_trait<is_convertible, Function*const, const char&, false>();

  test_binary_trait<is_convertible, Function*, char*, false>();
  test_binary_trait<is_convertible, Function*, const char*, false>();
  test_binary_trait<is_convertible, Function*const, char*, false>();
  test_binary_trait<is_convertible, Function*const, const char*, false>();

  test_binary_trait<is_convertible, Array, void, false>();
  test_binary_trait<is_convertible, const Array, void, false>();
  test_binary_trait<is_convertible, Array, const void, false>();
  test_binary_trait<is_convertible, const Array, const void, false>();

  test_binary_trait<is_convertible, Array, Function, false>();
  test_binary_trait<is_convertible, const Array, Function, false>();

  test_binary_trait<is_convertible, Array, Function&, false>();
  test_binary_trait<is_convertible, const Array, Function&, false>();

  test_binary_trait<is_convertible, Array, Function*, false>();
  test_binary_trait<is_convertible, Array, Function* const, false>();
  test_binary_trait<is_convertible, const Array, Function*, false>();
  test_binary_trait<is_convertible, const Array, Function* const, false>();

  test_binary_trait<is_convertible, Array, Array, false>();
  test_binary_trait<is_convertible, Array, const Array, false>();
  test_binary_trait<is_convertible, const Array, Array, false>();
  test_binary_trait<is_convertible, const Array, const Array, false>();

  test_binary_trait<is_convertible, Array, Array&, false>();
  test_binary_trait<is_convertible, Array, const Array&>();
  test_binary_trait<is_convertible, const Array, Array&, false>();
  test_binary_trait<is_convertible, const Array, const Array&>();

  test_binary_trait<is_convertible, Array, char, false>();
  test_binary_trait<is_convertible, Array, const char, false>();
  test_binary_trait<is_convertible, const Array, char, false>();
  test_binary_trait<is_convertible, const Array, const char, false>();

  test_binary_trait<is_convertible, Array, char&, false>();
  test_binary_trait<is_convertible, Array, const char&, false>();
  test_binary_trait<is_convertible, const Array, char&, false>();
  test_binary_trait<is_convertible, const Array, const char&, false>();

  test_binary_trait<is_convertible, Array, char*>();
  test_binary_trait<is_convertible, Array, const char*>();
  test_binary_trait<is_convertible, const Array, char*, false>();
  test_binary_trait<is_convertible, const Array, const char*>();

  test_binary_trait<is_convertible, Array&, void, false>();
  test_binary_trait<is_convertible, const Array&, void, false>();
  test_binary_trait<is_convertible, Array&, const void, false>();
  test_binary_trait<is_convertible, const Array&, const void, false>();

  test_binary_trait<is_convertible, Array&, Function, false>();
  test_binary_trait<is_convertible, const Array&, Function, false>();

  test_binary_trait<is_convertible, Array&, Function&, false>();
  test_binary_trait<is_convertible, const Array&, Function&, false>();

  test_binary_trait<is_convertible, Array&, Function*, false>();
  test_binary_trait<is_convertible, Array&, Function* const, false>();
  test_binary_trait<is_convertible, const Array&, Function*, false>();
  test_binary_trait<is_convertible, const Array&, Function* const, false>();

  test_binary_trait<is_convertible, Array&, Array, false>();
  test_binary_trait<is_convertible, Array&, const Array, false>();
  test_binary_trait<is_convertible, const Array&, Array, false>();
  test_binary_trait<is_convertible, const Array&, const Array, false>();

  test_binary_trait<is_convertible, Array&, Array&>();
  test_binary_trait<is_convertible, Array&, const Array&>();
  test_binary_trait<is_convertible, const Array&, Array&, false>();
  test_binary_trait<is_convertible, const Array&, const Array&>();

  test_binary_trait<is_convertible, Array&, char, false>();
  test_binary_trait<is_convertible, Array&, const char, false>();
  test_binary_trait<is_convertible, const Array&, char, false>();
  test_binary_trait<is_convertible, const Array&, const char, false>();

  test_binary_trait<is_convertible, Array&, char&, false>();
  test_binary_trait<is_convertible, Array&, const char&, false>();
  test_binary_trait<is_convertible, const Array&, char&, false>();
  test_binary_trait<is_convertible, const Array&, const char&, false>();

  test_binary_trait<is_convertible, Array&, char*>();
  test_binary_trait<is_convertible, Array&, const char*>();
  test_binary_trait<is_convertible, const Array&, char*, false>();
  test_binary_trait<is_convertible, const Array&, const char*>();

  test_binary_trait<is_convertible, char, void, false>();
  test_binary_trait<is_convertible, const char, void, false>();
  test_binary_trait<is_convertible, char, const void, false>();
  test_binary_trait<is_convertible, const char, const void, false>();

  test_binary_trait<is_convertible, char, Function, false>();
  test_binary_trait<is_convertible, const char, Function, false>();

  test_binary_trait<is_convertible, char, Function&, false>();
  test_binary_trait<is_convertible, const char, Function&, false>();

  test_binary_trait<is_convertible, char, Function*, false>();
  test_binary_trait<is_convertible, char, Function* const, false>();
  test_binary_trait<is_convertible, const char, Function*, false>();
  test_binary_trait<is_convertible, const char, Function* const, false>();

  test_binary_trait<is_convertible, char, Array, false>();
  test_binary_trait<is_convertible, char, const Array, false>();
  test_binary_trait<is_convertible, const char, Array, false>();
  test_binary_trait<is_convertible, const char, const Array, false>();

  test_binary_trait<is_convertible, char, Array&, false>();
  test_binary_trait<is_convertible, char, const Array&, false>();
  test_binary_trait<is_convertible, const char, Array&, false>();
  test_binary_trait<is_convertible, const char, const Array&, false>();

  test_binary_trait<is_convertible, char, char>();
  test_binary_trait<is_convertible, char, const char>();
  test_binary_trait<is_convertible, const char, char>();
  test_binary_trait<is_convertible, const char, const char>();

  test_binary_trait<is_convertible, char, char&, false>();
  test_binary_trait<is_convertible, char, const char&>();
  test_binary_trait<is_convertible, const char, char&, false>();
  test_binary_trait<is_convertible, const char, const char&>();

  test_binary_trait<is_convertible, char, char*, false>();
  test_binary_trait<is_convertible, char, const char*, false>();
  test_binary_trait<is_convertible, const char, char*, false>();
  test_binary_trait<is_convertible, const char, const char*, false>();

  test_binary_trait<is_convertible, char&, void, false>();
  test_binary_trait<is_convertible, const char&, void, false>();
  test_binary_trait<is_convertible, char&, const void, false>();
  test_binary_trait<is_convertible, const char&, const void, false>();

  test_binary_trait<is_convertible, char&, Function, false>();
  test_binary_trait<is_convertible, const char&, Function, false>();

  test_binary_trait<is_convertible, char&, Function&, false>();
  test_binary_trait<is_convertible, const char&, Function&, false>();

  test_binary_trait<is_convertible, char&, Function*, false>();
  test_binary_trait<is_convertible, char&, Function* const, false>();
  test_binary_trait<is_convertible, const char&, Function*, false>();
  test_binary_trait<is_convertible, const char&, Function* const, false>();

  test_binary_trait<is_convertible, char&, Array, false>();
  test_binary_trait<is_convertible, char&, const Array, false>();
  test_binary_trait<is_convertible, const char&, Array, false>();
  test_binary_trait<is_convertible, const char&, const Array, false>();

  test_binary_trait<is_convertible, char&, Array&, false>();
  test_binary_trait<is_convertible, char&, const Array&, false>();
  test_binary_trait<is_convertible, const char&, Array&, false>();
  test_binary_trait<is_convertible, const char&, const Array&, false>();

  test_binary_trait<is_convertible, char&, char>();
  test_binary_trait<is_convertible, char&, const char>();
  test_binary_trait<is_convertible, const char&, char>();
  test_binary_trait<is_convertible, const char&, const char>();

  test_binary_trait<is_convertible, char&, char&>();
  test_binary_trait<is_convertible, char&, const char&>();
  test_binary_trait<is_convertible, const char&, char&, false>();
  test_binary_trait<is_convertible, const char&, const char&>();

  test_binary_trait<is_convertible, char&, char*, false>();
  test_binary_trait<is_convertible, char&, const char*, false>();
  test_binary_trait<is_convertible, const char&, char*, false>();
  test_binary_trait<is_convertible, const char&, const char*, false>();

  test_binary_trait<is_convertible, char*, void, false>();
  test_binary_trait<is_convertible, const char*, void, false>();
  test_binary_trait<is_convertible, char*, const void, false>();
  test_binary_trait<is_convertible, const char*, const void, false>();

  test_binary_trait<is_convertible, char*, Function, false>();
  test_binary_trait<is_convertible, const char*, Function, false>();

  test_binary_trait<is_convertible, char*, Function&, false>();
  test_binary_trait<is_convertible, const char*, Function&, false>();

  test_binary_trait<is_convertible, char*, Function*, false>();
  test_binary_trait<is_convertible, char*, Function* const, false>();
  test_binary_trait<is_convertible, const char*, Function*, false>();
  test_binary_trait<is_convertible, const char*, Function* const, false>();

  test_binary_trait<is_convertible, char*, Array, false>();
  test_binary_trait<is_convertible, char*, const Array, false>();
  test_binary_trait<is_convertible, const char*, Array, false>();
  test_binary_trait<is_convertible, const char*, const Array, false>();

  test_binary_trait<is_convertible, char*, Array&, false>();
  test_binary_trait<is_convertible, char*, const Array&, false>();
  test_binary_trait<is_convertible, const char*, Array&, false>();
  test_binary_trait<is_convertible, const char*, const Array&, false>();

  test_binary_trait<is_convertible, char*, char, false>();
  test_binary_trait<is_convertible, char*, const char, false>();
  test_binary_trait<is_convertible, const char*, char, false>();
  test_binary_trait<is_convertible, const char*, const char, false>();

  test_binary_trait<is_convertible, char*, char&, false>();
  test_binary_trait<is_convertible, char*, const char&, false>();
  test_binary_trait<is_convertible, const char*, char&, false>();
  test_binary_trait<is_convertible, const char*, const char&, false>();

  test_binary_trait<is_convertible, char*, char*>();
  test_binary_trait<is_convertible, char*, const char*>();
  test_binary_trait<is_convertible, const char*, char*, false>();
  test_binary_trait<is_convertible, const char*, const char*>();

  test_binary_trait<is_convertible, NonCopyableClass&, NonCopyableClass&>();
  test_binary_trait<is_convertible, NonCopyableClass&, const NonCopyableClass&>();
  test_binary_trait<is_convertible, NonCopyableClass&, const volatile NonCopyableClass&>();
  test_binary_trait<is_convertible, NonCopyableClass&, volatile NonCopyableClass&>();
  test_binary_trait<is_convertible, const NonCopyableClass&, const NonCopyableClass&>();
  test_binary_trait<is_convertible, const NonCopyableClass&, const volatile NonCopyableClass&>();
  test_binary_trait<is_convertible, volatile NonCopyableClass&, const volatile NonCopyableClass&>();
  test_binary_trait<is_convertible, const volatile NonCopyableClass&, const volatile NonCopyableClass&>();
  test_binary_trait<is_convertible, const NonCopyableClass&, NonCopyableClass&, false>();

//TODO is_complete

//TODO is_polymorphic_functor

//TODO result_of
  typedef bool (&PF1)();
  typedef short (*PF2)(long);
  struct S {
  operator PF2() const;
  double operator()(char, int&);
  void fn(long) const;
  char data;
  };
  typedef void (S::*PMF)(long) const;
  typedef char S::*PMD;
  test_nested_type_trait_cv<result_of, S(int), short>();
  test_nested_type_trait_cv<result_of, S&(unsigned char, int&), double>();
  test_nested_type_trait_cv<result_of, PF1(), bool>();
  //test_nested_type_trait_cv<result_of, PMF(unique_ptr<S>, int), void>();
  test_nested_type_trait_cv<result_of, PMD(S), char&&>();
  test_nested_type_trait_cv<result_of, PMD(const S*), const char&>();

  test_nested_type_trait_cv<result_of, S(int), short>();
  test_nested_type_trait_cv<result_of, S&(unsigned char, int&), double>();
  test_nested_type_trait_cv<result_of, PF1(), bool>();
  //test_nested_type_trait_cv<result_of, PMS(unique_ptr<S>, int), void>();
  test_nested_type_trait_cv<result_of, PMF(S, int), void>();
  test_nested_type_trait_cv<result_of, PMF(const S&, int), void>();
  test_nested_type_trait_cv<result_of, PMD(S), char&&>();
  test_nested_type_trait_cv<result_of, PMD(const S*), const char&>();

  struct X {
    int i;
    void f1() { }
    void f2() volatile { }
  };

  using pm = int X::*;
  using pmf1 = void (X::*)();
  using pmf2 = void (X::*)() volatile;

  test_nested_type_trait_cv<result_of, pm const&(X&), int&>();
  test_nested_type_trait_cv<result_of, pmf1 const&(X&), void>();
  test_nested_type_trait_cv<result_of, pmf2 const&(X&), void>();
  test_nested_type_trait_cv<result_of, pm(volatile X&), volatile int&>();
  test_nested_type_trait_cv<result_of, pmf2(volatile X&), void>();
}
