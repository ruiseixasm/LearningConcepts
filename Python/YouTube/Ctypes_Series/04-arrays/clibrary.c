#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int sumArray_v1(int *arr, int size) {
    int sum = 0;
    for (int i = 0; i < size; ++i) {
        sum += arr[i];
    }
    return sum;
}

int* incArray_v1(int *arr, int size) {
    for (int i = 0; i < size; ++i) {
        arr[i]++;
    }
    return arr;
}

int* getArray_v1() {
    int* arr = malloc(10 * sizeof(int));
    for (int i = 0; i < 10; i++) {
        arr[i] = i;
    }
    return arr;
}

// Needs to free memory in C because Python doesn't have the needed functions
void free_memory_v1(int* arr) {
    free(arr);
}

// Generate the .so file with this command
// gcc clibrary.c -shared -o clibrary.so -fPIC
