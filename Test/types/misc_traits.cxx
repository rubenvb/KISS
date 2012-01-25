/**
 * Copyright 2012 Ruben Van Boxem. All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without modification, are
 * permitted provided that the following conditions are met:
 * 
 *    1. Redistributions of source code must retain the above copyright notice, this list of
 *       conditions and the following disclaimer.
 * 
 *    2. Redistributions in binary form must reproduce the above copyright notice, this list
 *       of conditions and the following disclaimer in the documentation and/or other materials
 *       provided with the distribution.
 * 
 * THIS SOFTWARE IS PROVIDED BY RUBEN VAN BOXEM ''AS IS'' AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND
 * FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL <COPYRIGHT HOLDER> OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * 
 * The views and conclusions contained in the software and documentation are those of the
 * authors and should not be interpreted as representing official policies, either expressed
 * or implied, of Ruben Van Boxem.
 ********************************************************************************************/
 
 /*
  * types/misc.cxx
  *  Miscellaneous traits
  */

#include <types.hxx>

#ifndef __clang__
auto l = [](){};
#endif
class Class {};
// all sorts of function pointers
typedef void (function)();
typedef const volatile int (cvfunction)();
typedef void (*fp)();
typedef const volatile void (*cvfp)();
typedef void (Class::*mfp)();
/*
 * Enable when  r-value for *this is widely available
typedef void (Class::*mfpr)()&;
typedef void (Class::*mfprr)()&&;
 */
typedef void (Class::*cvmfp)() const volatile;
typedef int Class::*ptm;
typedef const int Class::* const volatile cvptm;
#ifndef __clang__
typedef decltype(l) lambda;
#endif


int main()
{
    // is_void
    static_assert( kiss::is_void<void>(),          "void not recognized as void" );
    static_assert( !kiss::is_void<void*>(),         "void* recognized as void" );
    static_assert( kiss::is_void<const void>(),    "const void not recognized as void" );
    static_assert( kiss::is_void<volatile void>(), "volatile void not recognized as void" );
    static_assert( !kiss::is_void<char>(),         "char recognized as void" );
    static_assert( !kiss::is_void<Class>(),  "Class recognized as void" );
    
    // is_nullptr
    static_assert( kiss::is_nullptr<kiss::nullptr_type>(),           "nullptr_type not recognized as nullptr" );
    static_assert( !kiss::is_nullptr<kiss::nullptr_type&>(),         "nullptr_type& recognized as nullptr" );
    static_assert( !kiss::is_nullptr<kiss::nullptr_type&&>(),        "nullptr_type&& recognized as nullptr" );
    static_assert( !kiss::is_nullptr<const kiss::nullptr_type>(),    "const nullptr_type recognized as nullptr" );
    static_assert( !kiss::is_nullptr<volatile kiss::nullptr_type>(), "volatile nullptr_type recognized as nullptr" );
    static_assert( !kiss::is_nullptr<Class>(),                 "Class recognized as nullptr" );
    static_assert( !kiss::is_nullptr<Class*>(),                "Class* recognized as nullptr" );
    
    // is_c_array
    static_assert( kiss::is_c_array<Class[]>(),         "unknown length array not recognized as C array" );
    static_assert( kiss::is_c_array<const Class[]>(),   "const unknown length array not recognized as C array" );
    static_assert( kiss::is_c_array<Class[42]>(),       "fixed-length array not recognized as C array" );
    static_assert( kiss::is_c_array<const Class[42]>(), "const fixed-length array not recognized as C array" );
    static_assert( !kiss::is_c_array<Class*>(),         "decayed array aka pointer recognized as C array" );
    
    // is_pointer
    static_assert( !kiss::is_pointer<Class>(),             "Class recognized as pointer" );
    static_assert( kiss::is_pointer<Class*>(),             "Class* not recognized as pointer" );
    static_assert( kiss::is_pointer<Class**>(),            "Class** not recognized as pointer" );
    static_assert( kiss::is_pointer<Class const*>(),       "Class const* not recognized as pointer" );
    static_assert( kiss::is_pointer<Class * const>(),      "Class *const not recognized as pointer" );
    static_assert( kiss::is_pointer<Class const* const>(), "Class const* const not recognized as pointer" );
    static_assert( !kiss::is_pointer<kiss::nullptr_type>(),      "nullptr_type is recognized as pointer" );
    static_assert( !kiss::is_pointer<Class&>(),            "Class& recognized as pointer" );
    static_assert( !kiss::is_pointer<Class&&>(),           "Class&& recognized as pointer" );
    static_assert( !kiss::is_pointer<Class*&>(),           "Class*& recognized as pointer" );
    
    // is_lvalue_reference
    static_assert( !kiss::is_lvalue_reference<Class>(),   "Class recognized as lvalue reference" );
    static_assert( kiss::is_lvalue_reference<Class&>(),   "Class& not recognized as lvalue reference" );
    static_assert( !kiss::is_lvalue_reference<Class&&>(), "Class&& recognized as lvalue reference" );
    static_assert( !kiss::is_lvalue_reference<Class*>(),  "Class* recognized as lvalue reference" );
    static_assert( kiss::is_lvalue_reference<Class*&>(),  "Class*& recognized as lvalue reference" );
    
    // is_rvalue_reference
    static_assert( !kiss::is_rvalue_reference<Class>(),  "Class recognized as rvalue reference" );
    static_assert( !kiss::is_rvalue_reference<Class&>(), "Class& recognized as rvalue reference" );
    static_assert( kiss::is_rvalue_reference<Class&&>(), "Class&& not recognized as rvalue reference" );
    static_assert( !kiss::is_rvalue_reference<Class*>(), "Class* recognized as rvalue reference" );
    static_assert( !kiss::is_rvalue_reference<Class*&>(), "Class*& recognized as rvalue reference" );
       
    // is_reference
    static_assert( !kiss::is_reference<Class>(),  "Class recognized as reference" );
    static_assert( kiss::is_reference<Class&>(), "Class& recognized as reference" );
    static_assert( kiss::is_reference<Class&&>(), "Class&& not recognized as reference" );
    static_assert( !kiss::is_reference<Class*>(), "Class* recognized as reference" );
    static_assert( kiss::is_reference<Class*&>(), "Class*& recognized as reference" );
    
    // is_member_object_pointer
    
    // is_member_function_pointer
    static_assert( !kiss::is_member_function_pointer<char>(),     "char is recognized as member function pointer" );
    static_assert( !kiss::is_member_function_pointer<function>(), "function recognized as member function pointer" );
    #ifndef __clang__
    static_assert( !kiss::is_member_function_pointer<lambda>(),   "lambda recognized as member function pointer" );
    #endif
    static_assert( !kiss::is_member_function_pointer<fp>(),       "fp recognized as member function pointer" );
    static_assert( kiss::is_member_function_pointer<mfp>(),       "mfp not recognized as member function pointer" );
    static_assert( kiss::is_member_function_pointer<cvmfp>(),     "cvmfp not recognized as member function pointer" );
    static_assert( !kiss::is_member_function_pointer<ptm>(),      "ptm is recognized as member function pointer" );
    static_assert( !kiss::is_member_function_pointer<cvptm>(),    "cvptm is recognized as member function pointer" );
/* Enable when  r-value for *this is widely available
    static_assert( kiss::is_member_function_pointer<mfpr>(),      "mfpr not recognized as member function pointer" );
    static_assert( kiss::is_member_function_pointer<mfprr>(),     "mfprr not recognized as member function pointer" ); 
 */
    
    // is_function
    static_assert( !kiss::is_function<char>(),    "char recognized as function" );
    static_assert( kiss::is_function<function>(), "function not recognized as function" );
    #ifndef __clang__
    static_assert( !kiss::is_function<lambda>(),  "lambda recognized as function" );
    #endif
    static_assert( !kiss::is_function<fp>(),      "function pointer recognized as function" );
    static_assert( !kiss::is_function<mfp>(),     "member function pointer recognized as function" );
    static_assert( !kiss::is_function<cvmfp>(),    "cvmfp recognized as member function" );
    static_assert( !kiss::is_function<ptm>(),     "pointer to member recognized as function" );
    static_assert( !kiss::is_function<cvptm>(),   "cvptm recognized as member function" );
}