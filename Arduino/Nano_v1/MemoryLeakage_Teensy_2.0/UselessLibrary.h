#ifndef LIBRARYCLASS_H_INCLUDED
#define LIBRARYCLASS_H_INCLUDED

class LibraryClass {

  public:
    static void locallyDefinedFunction(char* const string_pointer) {
      // does nothing
    }
  
    static void externallyDefinedFunction(char* const string_pointer);
  
};

#endif // LIBRARYCLASS_H_INCLUDED