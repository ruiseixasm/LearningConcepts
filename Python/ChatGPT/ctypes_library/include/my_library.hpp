#ifndef MY_LIBRARY_HPP
#define MY_LIBRARY_HPP

#ifdef _WIN32
    #define DLL_EXPORT __declspec(dllexport)
    #define CALL_CONV __stdcall
#else
    #define DLL_EXPORT
    #define CALL_CONV
#endif

/*
    If <iostream> is included then ctypes throws an error,
    if <iostream> isn't included then ctypes works just fine!
*/
#include <iostream> // THIS SIMPLE INCLUSION MAKES CTYPES TO FAIL ON WINDOWS


extern "C" {
    DLL_EXPORT int CALL_CONV add_ctypes(int a, int b);
}

#endif // MY_LIBRARY_HPP
