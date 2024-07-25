#ifndef MY_LIBRARY_HPP
#define MY_LIBRARY_HPP

#ifdef _WIN32
    #ifdef BUILDING_DLL
        #define DLL_PUBLIC __declspec(dllexport)
    #else
        #define DLL_PUBLIC __declspec(dllimport)
    #endif
#else
    #define DLL_PUBLIC
#endif

extern "C" {
    DLL_PUBLIC int add(int a, int b);
}

#endif // MY_LIBRARY_HPP
