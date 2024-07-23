#ifndef MY_LIBRARY_HPP
#define MY_LIBRARY_HPP

#ifdef _WIN32
    #ifdef BUILDING_DLL
        #define DLL_EXPORT __declspec(dllexport)
    #else
        #define DLL_EXPORT __declspec(dllimport)
    #endif
#else
    #define DLL_EXPORT
#endif

DLL_EXPORT void my_function();

#endif // MY_LIBRARY_HPP
