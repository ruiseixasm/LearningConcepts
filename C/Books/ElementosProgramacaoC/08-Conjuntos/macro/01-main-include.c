// Compile command: gcc 01-main-include.c -o 01-main-include.out

#include <stdio.h>

#define SET_MAX     32
#include "macro.c"  // To announce the SET_MAX to the entire macro.h file

int main()
{
    printf("Main SET_MAX: %d\n", SET_MAX);
    
    macro_set_max();
    
    return 0;
}
