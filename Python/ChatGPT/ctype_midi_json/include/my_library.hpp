#ifndef MY_LIBRARY_HPP
#define MY_LIBRARY_HPP

#ifdef _WIN32
    #define DLL_EXPORT __declspec(dllexport)
#else
    #define DLL_EXPORT
#endif

#include "RtMidi.h"

extern "C" {
    DLL_EXPORT int add(int a, int b);
}

#endif // MY_LIBRARY_HPP
