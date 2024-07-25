#ifndef MY_LIBRARY_HPP
#define MY_LIBRARY_HPP

#ifdef _WIN32
    #define DLL_EXPORT __declspec(dllexport)
#else
    #define DLL_EXPORT
#endif

/*
    If <iostream> is included then ctypes thows an error,
    if <iostream> isn't included then ctypes works just fine!
*/
// #include <iostream> // THIS SIMPLE INCLUSION MAKES CTYPES TO FAIL ON WINDOWS


extern "C" {
    DLL_EXPORT int add_ctypes(int a, int b);
}

#endif // MY_LIBRARY_HPP
