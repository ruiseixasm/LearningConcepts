// Compiling command: gcc 03-const-pointers.c -o 03-const-pointers.out

#include <stdio.h>
#include <string.h>

// functions with const pointers parameters
void const_single_array(const char *single_array);
void const_multiple_array(const char **multiple_array);

int main()
{
    char my_single_array[60];
    strcpy(my_single_array, "String on stack!");

    printf("my_single_array: %s\n", my_single_array);

    return 0;
}

// functions with const pointers parameters

void const_single_array(const char *single_array)
{
    
}

void const_multiple_array(const char **multiple_array)
{
    
}
