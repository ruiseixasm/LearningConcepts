#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int fib(int n) {
    if (n > 1)
        return fib(n - 1) + fib(n - 2);
    return n;
}



// Generate the .so file with this command
// gcc test1.c -shared -o test1.so -fPIC
