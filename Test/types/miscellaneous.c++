/**
 * This file is dual licensed under the MIT and the University of Illinois Open
 * Source Licenses. See LICENSE.TXT for details.
 *
 ********************************************************************************************/

 /*
  * types/boolean_traits.c++
  *  Boolean traits tests.
  */

#include <types.h++>

using namespace kiss;

// decay
template<typename T, typename U>
void test_decay()
{
  static_assert(is_same<typename decay<T>::type, U>(), "");
}

// result_of
typedef bool (&PF1)();
typedef short (*PF2)(long);
struct S
{
  operator PF2() const;
  double operator()(char, int&);
  void fn(long) const;
  char data;
};
typedef void (S::*PMF)(long) const;
typedef char S::*PMD;

// is_same
template <class T, class U>
void test_is_same()
{
  static_assert(is_same<T, U>(), "");
  static_assert(!is_same<const T, U>(), "");
  static_assert(!is_same<T, const U>(), "");
  static_assert(is_same<const T, const U>(), "");
}
template <class T, class U>
void test_is_same_reference()
{
  static_assert(is_same<T, U>(), "");
  static_assert(is_same<const T, U>(), "");
  static_assert(is_same<T, const U>(), "");
  static_assert(is_same<const T, const U>(), "");
}
template <class T, class U>
void test_is_not_same()
{
  static_assert(!is_same<T, U>(), "");
}

class Class {};

int main()
{
  // conditional
  static_assert(is_same<conditional<true, char, int>, char>(), "");
  static_assert(is_same<conditional<false, char, int>, int>(), "");

  // declval
  // decay
  test_decay<void, void>();
  test_decay<int, int>();
  test_decay<const volatile int, int>();
  test_decay<int*, int*>();
  test_decay<int[3], int*>();
  test_decay<const int[3], const int*>();
  test_decay<void(), void (*)()>();
  // common_type
  static_assert(is_same<common_type<int>::type, int>(), "");
  static_assert(is_same<common_type<char>::type, char>(), "");

  static_assert(is_same<common_type<double, char>::type, double>(), "");
  static_assert(is_same<common_type<short, char>::type, int>(), "");

  static_assert(is_same<common_type<double, char, long long>::type, double>(), "");
  static_assert(is_same<common_type<unsigned, char, long long>::type, long long>(), "");

  // result_of
  static_assert(is_same<result_of<S(int)>::type, short>::value, "Error!");
  static_assert(is_same<result_of<S&(unsigned char, int&)>::type, double>::value, "Error!");
  static_assert(is_same<result_of<PF1()>::type, bool>::value, "Error!");
  //static_assert(is_same<result_of<PMF(unique_ptr<S>, int)>::type, void>::value, "Error!");
  static_assert(is_same<result_of<PMD(S)>::type, char&&>::value, "Error!");
  static_assert(is_same<result_of<PMD(const S*)>::type, const char&>::value, "Error!");

  static_assert(is_same<result_of<S(int)>::type, short>(), "Error!");
  static_assert(is_same<result_of<S&(unsigned char, int&)>::type, double>(), "Error!");
  static_assert(is_same<result_of<PF1()>::type, bool>(), "Error!");
  //static_assert(is_same<result_of<PMS(unique_ptr<S>, int)>::type, void>(), "Error!");
  static_assert(is_same<result_of<PMF(S, int)>::type, void>(), "Error!");
  static_assert(is_same<result_of<PMF(const S&, int)>::type, void>(), "Error!");
  static_assert(is_same<result_of<PMD(S)>::type, char&&>(), "Error!");
  static_assert(is_same<result_of<PMD(const S*)>::type, const char&>(), "Error!");

  struct X {
    int i;
    void f1() { }
    void f2() volatile { }
  };

  typedef int X::*pm;
  typedef void (X::*pmf1)();
  typedef void (X::*pmf2)() volatile;

  typedef result_of<pm const&(X&)>::type result;
  static_assert(is_same<result, int&>::value,
                "invoking cv-qualified pointer-to-member-object");

  typedef result_of<pmf1 const&(X&)>::type result1;
  static_assert(is_void<result1>::value,
                "invoking cv-qualified pointer-to-member-function");

  typedef result_of<pmf2 const&(X&)>::type result2;
  static_assert(is_void<result2>::value,
                "invoking cv-qualified pointer-to-member-function");

  typedef result_of<pm(volatile X&)>::type result3;
  static_assert(is_same<result3, volatile int&>::value,
                "invoking pointer-to-member-object on volatile object");

  typedef result_of<pmf2(volatile X&)>::type result4;
  static_assert(is_void<result4>::value,
                "invoking pointer-to-member-function on volatile object");

  // is_same
  test_is_same<int, int>();
  test_is_same<void, void>();
  test_is_same<Class, Class>();
  test_is_same<int*, int*>();
  test_is_same_reference<int&, int&>();

  test_is_not_same<int, void>();
  test_is_not_same<void, Class>();
  test_is_not_same<Class, int*>();
  test_is_not_same<int*, int&>();
  test_is_not_same<int&, int>();
}
