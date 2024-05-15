// Compiling command: gcc 05-char-array-pointers.c -o 05-char-array-pointers.out
#include <stdio.h>

int main()
{
    char my_array[10] = "Hello";
    unsigned long int address_all   = (unsigned long int)my_array;
    unsigned long int address_0     = (unsigned long int)(my_array[0]);
    
    printf("All: %lu, 0: %lu\n", address_all, address_0); // All: 3218596926, 0: 72
    
    return 0;
}
