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
  * types/compiler_traits.cxx
  *  Traits implemented through compiler intrinsics
  */

#include <types.hxx>

class dummy_class {};
union dummy_union {};
enum dummy_enum {};
enum class dummy_enum_class {};

int main()
{
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