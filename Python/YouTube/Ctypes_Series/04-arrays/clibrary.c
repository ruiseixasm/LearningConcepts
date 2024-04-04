#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* alloc_memory_v1() {
    // A copy of source is created dynamically and pointer to copy is returned.
    char* str = strdup("Hello World");  // strdup() and strndup() are used to duplicate a string.
    printf("Memory Allocated....\n");
    return str;
}

void free_memory_v1(char* ptr) {
    printf("Memory Deallocated\n");
    free(ptr);
}

// Generate the .so file with this command
// gcc clibrary.c -shared -o clibrary.so -fPIC
