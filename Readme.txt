KISS - Keep It Simple, Stupid!
==============================

KISS is a replacement of the C++11 Standard library.

It leans on the C++11 Standard stuff when that is done right (e.g. type_traits, ...).
It does things differently where incompatible changes can improve things (e.g. string, ...)
It adds things missing from the C++11 Standard library where applicable.

It leans on basic C library functions only when needed (e.g. math function, low level file operations...).
No file in KISS includes C header files to prevent namespace contamination.

Currently GCC 4.8+ and Clang 3.2+ are supported.

To build, do
cmake
make

To run the tests, do
ctest

Current progress:
 - math.h++ contains C math functions wrapped in overloaded functions for each relevant type.
 - pair.h++ contains a compressed pair implementation that uses the Empty Base Class optimization for empty types.
 - types.h++ contains most type traits, but most lack tests so the untested ones may be wrong.
    The libc++ test suite is being used as a base to test these.
