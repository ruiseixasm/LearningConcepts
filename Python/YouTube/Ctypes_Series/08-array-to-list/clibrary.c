#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int* getArray_c() {
    int* arr = malloc(sizeof(int) * 10);
    for (int i = 0; i < 10; ++i) {
        arr[i] = i;
    }
    return arr;
}

void delete_array_c(int* arr) {
    free(arr);
}


// Generate the .so file with this command
// gcc clibrary.c -shared -o clibrary.so -fPIC
