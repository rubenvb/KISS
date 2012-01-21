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

class dummy_class
{
    void member_function();
public:
    static void static_function();
};
void f() {return;};
void ff(...);
const int g(int);
const volatile char gg(...);
auto l = [](){};
auto fp = &f;

int main()
{
    // is_void
    static_assert( kiss::is_void<void>(),          "void not recognized as void" );
    static_assert( !kiss::is_void<void*>(),         "void* recognized as void" );
    static_assert( kiss::is_void<const void>(),    "const void not recognized as void" );
    static_assert( kiss::is_void<volatile void>(), "volatile void not recognized as void" );
    static_assert( !kiss::is_void<dummy_class>(),  "dummy_class recognized as void" );
    
    // is_nullptr
    static_assert( kiss::is_nullptr<kiss::nullptr_type>(),           "nullptr_type not recognized as nullptr" );
    static_assert( !kiss::is_nullptr<kiss::nullptr_type&>(),         "nullptr_type& recognized as nullptr" );
    static_assert( !kiss::is_nullptr<kiss::nullptr_type&&>(),        "nullptr_type&& recognized as nullptr" );
    static_assert( !kiss::is_nullptr<const kiss::nullptr_type>(),    "const nullptr_type recognized as nullptr" );
    static_assert( !kiss::is_nullptr<volatile kiss::nullptr_type>(), "volatile nullptr_type recognized as nullptr" );
    static_assert( !kiss::is_nullptr<dummy_class>(),                 "dummy_class recognized as nullptr" );
    static_assert( !kiss::is_nullptr<dummy_class*>(),                "dummy_class* recognized as nullptr" );
    
    // is_c_array
    static_assert( kiss::is_c_array<dummy_class[]>(),         "unknown length array not recognized as C array" );
    static_assert( kiss::is_c_array<const dummy_class[]>(),   "const unknown length array not recognized as C array" );
    static_assert( kiss::is_c_array<dummy_class[42]>(),       "fixed-length array not recognized as C array" );
    static_assert( kiss::is_c_array<const dummy_class[42]>(), "const fixed-length array not recognized as C array" );
    static_assert( !kiss::is_c_array<dummy_class*>(),         "decayed array aka pointer recognized as C array" );
    
    // is_pointer
    static_assert( !kiss::is_pointer<dummy_class>(),             "dummy_class recognized as pointer" );
    static_assert( kiss::is_pointer<dummy_class*>(),             "dummy_class* not recognized as pointer" );
    static_assert( kiss::is_pointer<dummy_class**>(),            "dummy_class** not recognized as pointer" );
    static_assert( kiss::is_pointer<dummy_class const*>(),       "dummy_class const* not recognized as pointer" );
    static_assert( kiss::is_pointer<dummy_class * const>(),      "dummy_class *const not recognized as pointer" );
    static_assert( kiss::is_pointer<dummy_class const* const>(), "dummy_class const* const not recognized as pointer" );
    static_assert( !kiss::is_pointer<kiss::nullptr_type>(),      "nullptr_type is recognized as pointer" );
    static_assert( !kiss::is_pointer<dummy_class&>(),            "dummy_class& recognized as pointer" );
    static_assert( !kiss::is_pointer<dummy_class&&>(),           "dummy_class&& recognized as pointer" );
    static_assert( !kiss::is_pointer<dummy_class*&>(),            "dummy_class*& recognized as pointer" );
    
    // is_function
    static_assert( !kiss::is_function<char>(),         "char recognized as function" );
    static_assert( kiss::is_function<
            decltype(dummy_class::static_function)>(), "static member function recognized as function" );
    static_assert( !kiss::is_function<decltype(l)>(),  "lambda recognized as function" );
    static_assert( !kiss::is_function<decltype(fp)>(), "function pointer recognized as function" );
    static_assert( kiss::is_function<decltype(f)>(),   "void function not recognized as a function" );
    static_assert( kiss::is_function<decltype(ff)>(),  "void variadic function not recognized as a function" );
    static_assert( kiss::is_function<decltype(g)>(),   "normal function not recognized as a function" );
    static_assert( kiss::is_function<decltype(gg)>(),  "const volatile function not recognized as a function" );
}