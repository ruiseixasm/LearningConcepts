// Compile command: gcc 00-segmentation-fault.c sets-segmentation-fault.c -DSET_MAX=49 -o 00-segmentation-fault.out

#include <stdio.h>
#include <limits.h>     // for UCHAR_MAX and CHAR_BIT
#include <stddef.h>     // for size_t

#define TOTOLOTO_MAX    49
// Requires the parameter -DSET_MAX=49 on the gcc command line
// Otherwise, if ommited, it will return segmentation fault, even with the following line:
// #define SET_MAX         TOTOLOTO_MAX

#include "sets-segmentation-fault.h"

#define SET_DIM_LOCAL     SET_MAX/CHAR_BIT + 1

typedef unsigned char Set_local[SET_DIM_LOCAL];
typedef unsigned char * SetPtr_local;

// Decays to pointer a given paramenter array in this case, Set!
SetPtr_local Setclr_local(Set_local s)                    /* esvaziar */
{
    for (size_t i = 0; i < SET_DIM_LOCAL; i++)
    {
        printf("local i: %d\tSET_DIM_LOCAL: %d\n", i, SET_DIM_LOCAL);
        s[i] = 0;
    }
    return s;
}

int main()
{
    printf("SET_MAX: %d\n", SET_MAX);
    printf("UCHAR_MAX: %d\n", UCHAR_MAX);
    printf("CHAR_BIT: %d\n", CHAR_BIT);
    printf("SET_DIM_LOCAL: %d\n", SET_DIM_LOCAL);
    printf("SET_DIM: %d\n\n", SET_DIM);
    
    // DOESN'T RETURN SEGMENTATION FAULT
    Set_local play;
    Setclr_local(play);

    // RETURNS SEGMENTATION FAULT
    Set play_segmentation_fault;
    Setclr(play_segmentation_fault);

    return 0;
}
