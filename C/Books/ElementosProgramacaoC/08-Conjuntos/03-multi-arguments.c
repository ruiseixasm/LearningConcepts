// Compile command: gcc 03-multi-arguments.c sets.c -o 03-multi-arguments.out

#include <stdio.h>
#include "sets.h"


int main()
{
    // usage of multi arguments function
    Set squares;
    Setaddn(Setclr(squares), 16,    // total of 16 arguments as n
             0,  1,   4,   9,  16,  25,  36,  49,
            64, 81, 100, 121, 144, 169, 196, 225);
    
    printf("Squares: ");
    Setprint(squares, "%d ", 0, 0);
    printf("\n");
    
    return 0;
}
