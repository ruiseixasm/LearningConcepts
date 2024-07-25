#ifndef OTHERS_LIBRARY_HPP
#define OTHERS_LIBRARY_HPP

/*
    If <iostream> is included then ctypes thows an error,
    if <iostream> isn't included then ctypes works just fine!
*/
#include <iostream> // THIS SIMPLE INCLUSION MAKES CTYPES TO FAIL ON WINDOWS

int add_others(int a, int b);

#endif // OTHERS_LIBRARY_HPP
