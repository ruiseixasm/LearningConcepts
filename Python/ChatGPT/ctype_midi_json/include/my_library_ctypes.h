#ifndef MY_LIBRARY_CTYPES_HPP
#define MY_LIBRARY_CTYPES_HPP

#include "my_library.hpp"

#ifdef _WIN32
    #ifdef BUILDING_DLL
        #define DLL_EXPORT __declspec(dllexport)
    #else
        #define DLL_EXPORT __declspec(dllimport)
    #endif
#else
    #define DLL_EXPORT
#endif

extern "C" {
    DLL_EXPORT int add_ctypes(int a, int b);
}

#endif // MY_LIBRARY_CTYPES_HPP
