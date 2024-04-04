#include <stdio.h>

int add_v1(int num1, int num2) {
    return num1 + num2;
}

void display_v1(char* str) {
    printf("%s\n", str);
}

// Generate the .so file with this command
// gcc clibrary.c -shared -o clibrary.so -fPIC
