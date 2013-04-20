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
  * types/boolean_traits.c++
  *  Boolean traits tests.
  */

#include <types.h++>

auto l = [](){};
class Class {};
class Child : public Class {};
union Union {};
enum Enum {};
enum class Enum_class {};
// all sorts of function pointers
typedef void (function)();
//typedef const volatile int (cvfunction)();
typedef void (*fp)();
//typedef const volatile void (*cvfp)();
typedef void (Class::*mfp)();
//r-value ref to this needed
//typedef void (Class::*mfpr)();
//typedef void (Class::*mfprr)();
typedef void (Class::*cvmfp)() const volatile;
typedef int Class::*ptm;
typedef const int Class::* const volatile cvptm;
typedef decltype(l) lambda;

int main()
{
// Intrinsic implementations
  // is_class
  static_assert(!kiss::is_class<char>(),           "char recognized as class");
  static_assert(!kiss::is_class<Union>(),          "Union recognized as class");
  static_assert(!kiss::is_class<Enum>(),           "Enum recognized as class");
  static_assert(!kiss::is_class<Enum_class>(),     "Enum_class recognized as class");
  static_assert( kiss::is_class<Class>(),          "Union not recognized as class");
  static_assert( kiss::is_class<const Class>(),    "const Class not recognized as class");
  static_assert( kiss::is_class<volatile Class>(), "volatile Class not recognized as class");
  static_assert(!kiss::is_class<Class*>(),         "Class* recognized as class");
  static_assert(!kiss::is_class<Class&>(),         "Class* recognized as class");
  static_assert(!kiss::is_class<Class&&>(),        "Class* recognized as class");
  // is_enum
  static_assert(!kiss::is_enum<char>(),         "char recognized as enum");
  static_assert(!kiss::is_enum<Union>(),        "Union not recognized as enum");
  static_assert(!kiss::is_enum<Class>(),        "Class recognized as enum");
  static_assert( kiss::is_enum<Enum>(),          "Enum recognized as enum");
  static_assert( kiss::is_enum<Enum_class>(),    "Enum_class recognized as enum");
  static_assert( kiss::is_enum<const Enum>(),    "const Enum not recognized as enum");
  static_assert( kiss::is_enum<volatile Enum>(), "volatile Enum not recognized as enum");
  static_assert(!kiss::is_enum<Enum*>(),        "Enum* recognized as enum");
  static_assert(!kiss::is_enum<Enum&>(),        "Enum* recognized as enum");
  static_assert(!kiss::is_enum<Enum&&>(),       "Enum* recognized as enum");
  // is_union
  static_assert(!kiss::is_union<char>(),          "char recognized as union");
  static_assert(!kiss::is_union<Class>(),         "Class recognized as union");
  static_assert(!kiss::is_union<Enum>(),          "Enum recognized as union");
  static_assert(!kiss::is_union<Enum_class>(),    "Enum_class recognized as union");
  static_assert( kiss::is_union<Union>(),          "Union not recognized as union");
  static_assert( kiss::is_union<const Union>(),    "const Union not recognized as union");
  static_assert( kiss::is_union<volatile Union>(), "volatile Union not recognized as union");
  static_assert(!kiss::is_union<Union*>(),        "Union* recognized as union");
  static_assert(!kiss::is_union<Union&>(),        "Union* recognized as union");
  static_assert(!kiss::is_union<Union&&>(),       "Union* recognized as union");

// KISS implementations
  // is_convertible
  static_assert( kiss::is_convertible<double, int>(),    "double not convertible to int");
  static_assert( kiss::is_convertible<int, double>(),    "int not convertible to double");
  static_assert( kiss::is_convertible<Child, Class>(),   "Child not convertible to Class");
  static_assert(!kiss::is_convertible<Class, Child>(),   "Class convertible to Child");
  static_assert(!kiss::is_convertible<Class*, Child*>(), "Class* convertible to Child*");
  static_assert( kiss::is_convertible<Child*, Class*>(), "Child* not convertible to Class*");

  // is_void
  static_assert( kiss::is_void<void>(),          "void not recognized as void");
  static_assert(!kiss::is_void<void*>(),         "void* recognized as void");
  static_assert( kiss::is_void<const void>(),    "const void not recognized as void");
  static_assert( kiss::is_void<volatile void>(), "volatile void not recognized as void");
  static_assert(!kiss::is_void<char>(),         "char recognized as void");
  static_assert(!kiss::is_void<Class>(),        "Class recognized as void");

  // is_nullptr
  static_assert( kiss::is_nullptr<kiss::nullptr_type>(),           "nullptr_type not recognized as nullptr");
  static_assert(!kiss::is_nullptr<kiss::nullptr_type&>(),         "nullptr_type& recognized as nullptr");
  static_assert(!kiss::is_nullptr<kiss::nullptr_type&&>(),        "nullptr_type&& recognized as nullptr");
  static_assert(!kiss::is_nullptr<const kiss::nullptr_type>(),    "const nullptr_type recognized as nullptr");
  static_assert(!kiss::is_nullptr<volatile kiss::nullptr_type>(), "volatile nullptr_type recognized as nullptr");
  static_assert(!kiss::is_nullptr<Class>(),                       "Class recognized as nullptr");
  static_assert(!kiss::is_nullptr<Class*>(),                      "Class* recognized as nullptr");

  // is_c_array
  static_assert( kiss::is_c_array<Class[]>(),         "unknown length array not recognized as C array");
  static_assert( kiss::is_c_array<const Class[]>(),   "const unknown length array not recognized as C array");
  static_assert( kiss::is_c_array<Class[42]>(),       "fixed-length array not recognized as C array");
  static_assert( kiss::is_c_array<const Class[42]>(), "const fixed-length array not recognized as C array");
  static_assert(!kiss::is_c_array<Class*>(),          "decayed array aka pointer recognized as C array");

  // is_pointer
  static_assert(!kiss::is_pointer<Class>(),              "Class recognized as pointer");
  static_assert( kiss::is_pointer<Class*>(),             "Class* not recognized as pointer");
  static_assert( kiss::is_pointer<Class**>(),            "Class** not recognized as pointer");
  static_assert( kiss::is_pointer<Class const*>(),       "Class const* not recognized as pointer");
  static_assert( kiss::is_pointer<Class * const>(),      "Class *const not recognized as pointer");
  static_assert( kiss::is_pointer<Class const* const>(), "Class const* const not recognized as pointer");
  static_assert(!kiss::is_pointer<kiss::nullptr_type>(), "nullptr_type is recognized as pointer");
  static_assert(!kiss::is_pointer<Class&>(),             "Class& recognized as pointer");
  static_assert(!kiss::is_pointer<Class&&>(),            "Class&& recognized as pointer");
  static_assert(!kiss::is_pointer<Class*&>(),            "Class*& recognized as pointer");

  // is_lvalue_reference
  static_assert(!kiss::is_lvalue_reference<Class>(),   "Class recognized as lvalue reference");
  static_assert( kiss::is_lvalue_reference<Class&>(),  "Class& not recognized as lvalue reference");
  static_assert(!kiss::is_lvalue_reference<Class&&>(), "Class&& recognized as lvalue reference");
  static_assert(!kiss::is_lvalue_reference<Class*>(),  "Class* recognized as lvalue reference");
  static_assert( kiss::is_lvalue_reference<Class*&>(), "Class*& recognized as lvalue reference");

  // is_rvalue_reference
  static_assert(!kiss::is_rvalue_reference<Class>(),   "Class recognized as rvalue reference");
  static_assert(!kiss::is_rvalue_reference<Class&>(),  "Class& recognized as rvalue reference");
  static_assert( kiss::is_rvalue_reference<Class&&>(), "Class&& not recognized as rvalue reference");
  static_assert(!kiss::is_rvalue_reference<Class*>(),  "Class* recognized as rvalue reference");
  static_assert(!kiss::is_rvalue_reference<Class*&>(), "Class*& recognized as rvalue reference");

  // is_reference
  static_assert(!kiss::is_reference<Class>(),   "Class recognized as reference");
  static_assert( kiss::is_reference<Class&>(),  "Class& recognized as reference");
  static_assert( kiss::is_reference<Class&&>(), "Class&& not recognized as reference");
  static_assert(!kiss::is_reference<Class*>(),  "Class* recognized as reference");
  static_assert( kiss::is_reference<Class*&>(), "Class*& recognized as reference");

  // is_member_object_pointer

  // is_member_function_pointer
  static_assert(!kiss::is_member_function_pointer<char>(),     "char is recognized as member function pointer");
  static_assert(!kiss::is_member_function_pointer<function>(), "function recognized as member function pointer");
  static_assert(!kiss::is_member_function_pointer<lambda>(),   "lambda recognized as member function pointer");
  static_assert(!kiss::is_member_function_pointer<fp>(),       "fp recognized as member function pointer");
  static_assert( kiss::is_member_function_pointer<mfp>(),      "mfp not recognized as member function pointer");
  static_assert( kiss::is_member_function_pointer<cvmfp>(),    "cvmfp not recognized as member function pointer");
  static_assert(!kiss::is_member_function_pointer<ptm>(),      "ptm is recognized as member function pointer");
  static_assert(!kiss::is_member_function_pointer<cvptm>(),    "cvptm is recognized as member function pointer");
  //r-value ref to this needed
  static_assert( kiss::is_member_function_pointer<mfp&>(),     "mfpr not recognized as member function pointer");
  static_assert( kiss::is_member_function_pointer<mfp&&>(),    "mfprr not recognized as member function pointer");

  // is_function
  static_assert(!kiss::is_function<char>(),     "char recognized as function");
  static_assert( kiss::is_function<function>(), "function not recognized as function");
  static_assert(!kiss::is_function<lambda>(),   "lambda recognized as function");
  static_assert(!kiss::is_function<fp>(),       "function pointer recognized as function");
  static_assert(!kiss::is_function<mfp>(),      "member function pointer recognized as function");
  static_assert(!kiss::is_function<cvmfp>(),    "cvmfp recognized as member function");
  static_assert(!kiss::is_function<ptm>(),      "pointer to member recognized as function");
  static_assert(!kiss::is_function<cvptm>(),    "cvptm recognized as member function");
}
