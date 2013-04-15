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
  * types/transforming_traits.c++
  *  Transforming traits tests.
  */

#include <types.h++>

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
