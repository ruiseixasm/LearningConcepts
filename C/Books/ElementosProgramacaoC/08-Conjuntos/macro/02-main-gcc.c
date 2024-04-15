// Compile command: gcc 02-main-gcc.c macro.c -DSET_MAX=32 -o 02-main-gcc.out

#include <stdio.h>
#include "macro.h"  // requires the -DSET_MAX=32 gcc parameter

int main()
{
    printf("Main SET_MAX: %d\n", SET_MAX);
    
    macro_set_max();
    
    return 0;
}
