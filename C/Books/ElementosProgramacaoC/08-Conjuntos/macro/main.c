#include <stdio.h>

#define SET_MAX     32

#include "macro.h"

int main()
{
    printf("Main SET_MAX: %d\n", SET_MAX);
    
    macro_set_max();
    
    return 0;
}
