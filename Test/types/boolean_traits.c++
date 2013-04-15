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
class dummy_class {};
union dummy_union {};
enum dummy_enum {};
enum class dummy_enum_class {};
// all sorts of function pointers
typedef void (function)();
//typedef const volatile int (cvfunction)();
typedef void (*fp)();
//typedef const volatile void (*cvfp)();
typedef void (dummy_class::*mfp)();
//r-value ref to this needed
//typedef void (dummy_class::*mfpr)();
//typedef void (dummy_class::*mfprr)();
typedef void (dummy_class::*cvmfp)() const volatile;
typedef int dummy_class::*ptm;
typedef const int dummy_class::* const volatile cvptm;
typedef decltype(l) lambda;

int main()
{
  // is_void
  static_assert(kiss::is_void<void>(),          "void not recognized as void" );
  static_assert(!kiss::is_void<void*>(),         "void* recognized as void" );
  static_assert(kiss::is_void<const void>(),    "const void not recognized as void" );
  static_assert(kiss::is_void<volatile void>(), "volatile void not recognized as void" );
  static_assert(!kiss::is_void<char>(),         "char recognized as void" );
  static_assert(!kiss::is_void<dummy_class>(),        "Class recognized as void" );

  // is_nullptr
  static_assert(kiss::is_nullptr<kiss::nullptr_type>(),           "nullptr_type not recognized as nullptr" );
  static_assert(!kiss::is_nullptr<kiss::nullptr_type&>(),         "nullptr_type& recognized as nullptr" );
  static_assert(!kiss::is_nullptr<kiss::nullptr_type&&>(),        "nullptr_type&& recognized as nullptr" );
  static_assert(!kiss::is_nullptr<const kiss::nullptr_type>(),    "const nullptr_type recognized as nullptr" );
  static_assert(!kiss::is_nullptr<volatile kiss::nullptr_type>(), "volatile nullptr_type recognized as nullptr" );
  static_assert(!kiss::is_nullptr<dummy_class>(),                       "Class recognized as nullptr" );
  static_assert(!kiss::is_nullptr<dummy_class*>(),                      "Class* recognized as nullptr" );

  // is_c_array
  static_assert(kiss::is_c_array<dummy_class[]>(),         "unknown length array not recognized as C array" );
  static_assert(kiss::is_c_array<const dummy_class[]>(),   "const unknown length array not recognized as C array" );
  static_assert(kiss::is_c_array<dummy_class[42]>(),       "fixed-length array not recognized as C array" );
  static_assert(kiss::is_c_array<const dummy_class[42]>(), "const fixed-length array not recognized as C array" );
  static_assert(!kiss::is_c_array<dummy_class*>(),         "decayed array aka pointer recognized as C array" );

  // is_pointer
  static_assert(!kiss::is_pointer<dummy_class>(),             "Class recognized as pointer" );
  static_assert(kiss::is_pointer<dummy_class*>(),             "Class* not recognized as pointer" );
  static_assert(kiss::is_pointer<dummy_class**>(),            "Class** not recognized as pointer" );
  static_assert(kiss::is_pointer<dummy_class const*>(),       "Class const* not recognized as pointer" );
  static_assert(kiss::is_pointer<dummy_class * const>(),      "Class *const not recognized as pointer" );
  static_assert(kiss::is_pointer<dummy_class const* const>(), "Class const* const not recognized as pointer" );
  static_assert(!kiss::is_pointer<kiss::nullptr_type>(),      "nullptr_type is recognized as pointer" );
  static_assert(!kiss::is_pointer<dummy_class&>(),            "Class& recognized as pointer" );
  static_assert(!kiss::is_pointer<dummy_class&&>(),           "Class&& recognized as pointer" );
  static_assert(!kiss::is_pointer<dummy_class*&>(),           "Class*& recognized as pointer" );

  // is_lvalue_reference
  static_assert(!kiss::is_lvalue_reference<dummy_class>(),   "Class recognized as lvalue reference" );
  static_assert(kiss::is_lvalue_reference<dummy_class&>(),   "Class& not recognized as lvalue reference" );
  static_assert(!kiss::is_lvalue_reference<dummy_class&&>(), "Class&& recognized as lvalue reference" );
  static_assert(!kiss::is_lvalue_reference<dummy_class*>(),  "Class* recognized as lvalue reference" );
  static_assert(kiss::is_lvalue_reference<dummy_class*&>(),  "Class*& recognized as lvalue reference" );

  // is_rvalue_reference
  static_assert(!kiss::is_rvalue_reference<dummy_class>(),   "Class recognized as rvalue reference" );
  static_assert(!kiss::is_rvalue_reference<dummy_class&>(),  "Class& recognized as rvalue reference" );
  static_assert(kiss::is_rvalue_reference<dummy_class&&>(),  "Class&& not recognized as rvalue reference" );
  static_assert(!kiss::is_rvalue_reference<dummy_class*>(),  "Class* recognized as rvalue reference" );
  static_assert(!kiss::is_rvalue_reference<dummy_class*&>(), "Class*& recognized as rvalue reference" );

  // is_reference
  static_assert(!kiss::is_reference<dummy_class>(),  "Class recognized as reference" );
  static_assert(kiss::is_reference<dummy_class&>(),  "Class& recognized as reference" );
  static_assert(kiss::is_reference<dummy_class&&>(), "Class&& not recognized as reference" );
  static_assert(!kiss::is_reference<dummy_class*>(), "Class* recognized as reference" );
  static_assert(kiss::is_reference<dummy_class*&>(), "Class*& recognized as reference" );

  // is_member_object_pointer

  // is_member_function_pointer
  static_assert(!kiss::is_member_function_pointer<char>(),     "char is recognized as member function pointer" );
  static_assert(!kiss::is_member_function_pointer<function>(), "function recognized as member function pointer" );
  static_assert(!kiss::is_member_function_pointer<lambda>(),   "lambda recognized as member function pointer" );
  static_assert(!kiss::is_member_function_pointer<fp>(),       "fp recognized as member function pointer" );
  static_assert(kiss::is_member_function_pointer<mfp>(),       "mfp not recognized as member function pointer" );
  static_assert(kiss::is_member_function_pointer<cvmfp>(),     "cvmfp not recognized as member function pointer" );
  static_assert(!kiss::is_member_function_pointer<ptm>(),      "ptm is recognized as member function pointer" );
  static_assert(!kiss::is_member_function_pointer<cvptm>(),    "cvptm is recognized as member function pointer" );
  //r-value ref to this needed
  static_assert(kiss::is_member_function_pointer<mfp&>(),      "mfpr not recognized as member function pointer" );
  static_assert(kiss::is_member_function_pointer<mfp&&>(),     "mfprr not recognized as member function pointer" );

  // is_function
  static_assert(!kiss::is_function<char>(),    "char recognized as function" );
  static_assert(kiss::is_function<function>(), "function not recognized as function" );
  static_assert(!kiss::is_function<lambda>(),  "lambda recognized as function" );
  static_assert(!kiss::is_function<fp>(),      "function pointer recognized as function" );
  static_assert(!kiss::is_function<mfp>(),     "member function pointer recognized as function" );
  static_assert(!kiss::is_function<cvmfp>(),   "cvmfp recognized as member function" );
  static_assert(!kiss::is_function<ptm>(),     "pointer to member recognized as function" );
  static_assert(!kiss::is_function<cvptm>(),   "cvptm recognized as member function" );

  // is_union
  static_assert( !kiss::is_union<char>(),                "char recognized as union" );
  static_assert( !kiss::is_union<dummy_class>(),         "dummy_class recognized as union" );
  static_assert( !kiss::is_union<dummy_enum>(),          "dummy_enum recognized as union" );
  static_assert( !kiss::is_union<dummy_enum_class>(),    "dummy_enum_class recognized as union" );
  static_assert( kiss::is_union<dummy_union>(),          "dummy_union not recognized as union" );
  static_assert( kiss::is_union<const dummy_union>(),    "const dummy_union not recognized as union" );
  static_assert( kiss::is_union<volatile dummy_union>(), "volatile dummy_union not recognized as union" );
  static_assert( !kiss::is_union<dummy_union*>(),        "dummy_union* recognized as union" );
  static_assert( !kiss::is_union<dummy_union&>(),        "dummy_union* recognized as union" );
  static_assert( !kiss::is_union<dummy_union&&>(),       "dummy_union* recognized as union" );

  // is_class
  static_assert( !kiss::is_class<char>(),                "char recognized as class" );
  static_assert( !kiss::is_class<dummy_union>(),         "dummy_union recognized as class" );
  static_assert( !kiss::is_class<dummy_enum>(),          "dummy_enum recognized as class" );
  static_assert( !kiss::is_class<dummy_enum_class>(),    "dummy_enum_class recognized as class" );
  static_assert( kiss::is_class<dummy_class>(),          "dummy_union not recognized as class" );
  static_assert( kiss::is_class<const dummy_class>(),    "const dummy_class not recognized as class" );
  static_assert( kiss::is_class<volatile dummy_class>(), "volatile dummy_class not recognized as class" );
  static_assert( !kiss::is_class<dummy_class*>(),        "dummy_class* recognized as class" );
  static_assert( !kiss::is_class<dummy_class&>(),        "dummy_class* recognized as class" );
  static_assert( !kiss::is_class<dummy_class&&>(),       "dummy_class* recognized as class" );

  // is_enum
  static_assert( !kiss::is_enum<char>(),               "char recognized as enum" );
  static_assert( !kiss::is_enum<dummy_union>(),         "dummy_union not recognized as enum" );
  static_assert( !kiss::is_enum<dummy_class>(),        "dummy_class recognized as enum" );
  static_assert( kiss::is_enum<dummy_enum>(),         "dummy_enum recognized as enum" );
  static_assert( kiss::is_enum<dummy_enum_class>(),   "dummy_enum_class recognized as enum" );
  static_assert( kiss::is_enum<const dummy_enum>(),    "const dummy_enum not recognized as enum" );
  static_assert( kiss::is_enum<volatile dummy_enum>(), "volatile dummy_enum not recognized as enum" );
  static_assert( !kiss::is_enum<dummy_enum*>(),        "dummy_enum* recognized as enum" );
  static_assert( !kiss::is_enum<dummy_enum&>(),        "dummy_enum* recognized as enum" );
  static_assert( !kiss::is_enum<dummy_enum&&>(),       "dummy_enum* recognized as enum" );
}
