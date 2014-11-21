/**
 * Written in 2014 by Ruben Van Boxem <vanboxem.ruben@gmail.com>
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
 * variant.h++
 *  Variant class: typesafe union-like class.
 **/

#ifndef KISS_VARIANT_H
#define KISS_VARIANT_H

#include "config.h++"
#include "utility.h++"

template<typename... Types>
class variant
{
  aligned_union
};


#endif
