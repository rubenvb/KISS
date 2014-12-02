KISS - Keep It Simple, Stupid!
==============================

KISS is a replacement of the C++11 Standard library.

It leans on the C++11 Standard stuff when that is done right (e.g. type_traits, ...).
It does things differently where incompatible changes can improve things (e.g. string, ...)
It adds things missing from the C++11 Standard library where applicable.

It leans on basic C library functions only when needed (e.g. math function, low level file operations...).
No file in KISS includes C header files to prevent namespace contamination.

Currently GCC and Clang are supported.

To build, do
cmake
[g,mingw32-,n]make

To run the tests, do
ctest

Implementation details:
 - No language reserved identifiers were used.
 - The libc++ test suite is being used as a base for the tests,
   and all test code falls under the libc++ license, and may have been adapted to allow extensions or different behaviour.
 - For math functions, the C library math is used. Nonetheless, any other C functions are not used.
