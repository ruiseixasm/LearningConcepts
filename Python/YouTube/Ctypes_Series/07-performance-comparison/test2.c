#include <stdio.h>
#include <stdint.h>

typedef uint64_t lli;   // long long int

lli fib(int n) {
    lli a = 0, b = 1, c;
    for (int i = 2; i <= n; ++i) {
        c = a + b;
        a = b;
        b = c;
    }
    return b;
}



// Generate the .so file with this command
// gcc test2.c -shared -o test2.so -fPIC
