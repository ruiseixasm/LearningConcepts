// Compiling command: gcc 03-const-pointers.c -o 03-const-pointers.out

#include <stdio.h>
#include <string.h>

#define SIZE  60

// functions with const pointers parameters
void print_single_string(const char *single_string);
void print_multiple_strings(const char **multiple_strings, int array_size);

int main()
{
    // POINTERS(*) WORK AS RUSSIAN DOLLS ARROUND NUCLEAR OBJECTS
    
    char my_single_string[SIZE];
    strcpy(my_single_string, "String on stack!");
    
    print_single_string(my_single_string);
    
    printf("%-25s", "my_single_string:");
    printf("size %3d bytes, ", sizeof(my_single_string));       // SIZE
    printf("address %10p", my_single_string);
    printf(" (array of values)\n");
    printf("%-25s", "*my_single_string:");
    printf("size %3d bytes, ", sizeof(*my_single_string));      // 1 byte
    printf("address %10p", *my_single_string);
    printf(" (value)\n\n");
    
    // precedence of the "[]" operator is higher than the "*" operator
    
    // So, the solution for having equivalence would be: "char (*my_multiple_strings)[SIZE];"
    // same as my_multiple_strings[][SIZE]
    char (*my_multiple_strings)[SIZE];  // Single pointer to an Array[SIZE] (4 bytes)
    printf("%-25s", "my_multiple_strings:");
    printf("size %3d bytes, ", sizeof(my_multiple_strings));    // 4 bytes
    printf("address %10p", my_multiple_strings);
    printf(" (pointer)\n");
    printf("%-25s", "*my_multiple_strings:");
    printf("size %3d bytes, ", sizeof(*my_multiple_strings));   // SIZE bytes
    printf("address %10p", *my_multiple_strings);
    printf(" (array of values)\n\n");
    
    // same as *(my_multiple_chars[SIZE])
    char *my_multiple_pointers[SIZE];      // Array[SIZE] of pointers (SIZE * 4 bytes)
    printf("%-25s", "my_multiple_pointers:");
    printf("size %3d bytes, ", sizeof(my_multiple_pointers));      // SIZE * 4 bytes
    printf("address %10p", my_multiple_pointers);
    printf(" (array of pointers)\n");
    printf("%-25s", "*my_multiple_pointers:");
    printf("size %3d bytes, ", sizeof(*my_multiple_pointers));     // 4 bytes
    printf("address %10p", *my_multiple_pointers);
    printf(" (NULL pointer)\n\n");
    
    //So:
        //char my_multiple_strings[][SIZE]; is equivalent to char (*my_multiple_strings)[SIZE];
    //while:
        //char my_multiple_strings[][]; is equivalent to char *my_multiple_strings[];
    
    //Your observations are correct!
        //char my_multiple_strings[][SIZE]; declares a two-dimensional array of characters where
            //the size of the second dimension is specified (SIZE). This declaration is equivalent
            //to char (*my_multiple_strings)[SIZE];, which declares a pointer to an array of characters
            //with the second dimension size specified.
        //On the other hand, char my_multiple_strings[][]; is not a valid declaration in C because
            //it doesn't specify the size of any dimension. However, assuming it's meant to be
            //a declaration of an array of arrays of characters, the closest valid equivalent would
            //indeed be char *my_multiple_strings[];, which declares an array of pointers to characters.
    
    
    const char *array_const_strings[] = {"First string", "Second string", "Third string"};          // A
    //const char *array_const_strings[SIZE] = {"First string", "Second string", "Third string"};    // B
    
    //So, the values of each parcel are as follows:
        //sizeof(array_const_strings):     24 bytes.    (3 pointers for each string, first char)
        //sizeof(array_const_strings[0]):   8 bytes.
        //sizeof(array_const_strings) / sizeof(array_const_strings[0]): 3 elements.
    
    const int array_size = sizeof(array_const_strings) / sizeof(array_const_strings[0]);
    printf("%-25s", "array_const_strings:");
    printf("size %3d bytes, ", sizeof(array_const_strings));        // SIZE * 4 bytes
    printf("address %10p", array_const_strings);
    printf(" (array of pointers)\n");
    printf("%-25s", "*array_const_strings:");
    printf("size %3d bytes, ", sizeof(*array_const_strings));       // 4 bytes
    printf("address %10p", *array_const_strings);
    printf(" (pointer)\n\n");

    // Loop through the array and print each string
    for (int i = 0; i < array_size; i++) {
        printf("%*s", 25 - printf("String %d %s: ", i, array_const_strings[i]), "");
        printf("size %3d bytes, ", sizeof(array_const_strings[i]));        // 4 bytes
        printf("address %10p", array_const_strings[i]);
        printf(" (array of values)\n");
        printf("%-25s", "*array_const_strings[i]:");
        // POTENTIAL SEGMENTATION FAULT FOR THE B DECLARATION (INCORRECT ONE)
        printf("size %3d bytes, ", sizeof(*array_const_strings[i]));       // 1 byte
        printf("address %10p", *array_const_strings[i]);
        printf(" (value)\n");
    }
    
    print_multiple_strings(array_const_strings, array_size);

    return 0;
}

// functions with const pointers parameters

void print_single_string(const char *single_string)
{
    printf("single_string:     %s\n", single_string);
}

void print_multiple_strings(const char **multiple_strings, int array_size)
{
    printf("multiple_strings:\n");
    for (int i = 0; i < array_size; i++)
        printf("\tmultiple_strings[%d]:     %s\n", i, multiple_strings[i]);
}

// OUTPUT
//single_string:     String on stack!
//my_single_string:        size  60 bytes, address 0xbfdbf998 (array of values)
//*my_single_string:       size   1 bytes, address       0x53 (value)

//my_multiple_strings:     size   4 bytes, address 0xb7fa7b60 (pointer)
//*my_multiple_strings:    size  60 bytes, address 0xb7fa7b60 (array of values)

//my_multiple_pointers:    size 240 bytes, address 0xbfdbf8a8 (array of pointers)
//*my_multiple_pointers:   size   4 bytes, address        0x8 (NULL pointer)

//array_const_strings:     size  12 bytes, address 0xbfdbf89c (array of pointers)
//*array_const_strings:    size   4 bytes, address   0x47910b (pointer)

//String 0 First string:   size   4 bytes, address   0x47910b (array of values)
//*array_const_strings[i]: size   1 bytes, address       0x46 (value)
//String 1 Second string:  size   4 bytes, address   0x479118 (array of values)
//*array_const_strings[i]: size   1 bytes, address       0x53 (value)
//String 2 Third string:   size   4 bytes, address   0x479126 (array of values)
//*array_const_strings[i]: size   1 bytes, address       0x54 (value)
//multiple_strings:
	//multiple_strings[0]:     First string
	//multiple_strings[1]:     Second string
	//multiple_strings[2]:     Third string
