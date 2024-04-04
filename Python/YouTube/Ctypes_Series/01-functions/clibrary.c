#include <stdio.h>

void display1() {
    printf("Hello World\n");
}

void display2(char* str, int age) {
    printf("My name is %s and my age is %d\n", str, age);
}

char* display3(char* str, int age) {
    printf("My name is %s and my age is %d\n", str, age);
    return "Completed";
}

// Generate the .so file with this command
// gcc clibrary.c -shared -o clibrary.so -fPIC
