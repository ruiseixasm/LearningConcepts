// Compile command: gcc 01-parameter-array.c -o 01-parameter-array.out

#include <stdio.h>

typedef unsigned char Set[64];
typedef unsigned char Setelem;          // same as typedef unsigned Setelem;
typedef unsigned char * SetPtr;

SetPtr outArray(Set inArray)
{   // function parameter ‘inArray’ will return size of ‘unsigned char *’
    int setSize = sizeof(inArray);
    printf("Sset size at getArray: %d\n", setSize); // Size: 4  (pointer)
    return inArray;
}


int main()
{
    Set basicSet;
    int setSize = sizeof(basicSet);
    
    printf("Set size at main: %d\n", setSize);      // Size: 64 (array)
    
    SetPtr basicSetPtr = outArray(basicSet);
    setSize = sizeof(basicSetPtr);
    printf("SetPtr size at main: %d\n", setSize);   // Size: 4  (pointer)
    
    return 0;
}
