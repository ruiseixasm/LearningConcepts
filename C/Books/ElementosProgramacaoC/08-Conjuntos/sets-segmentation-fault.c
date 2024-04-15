#include "sets-segmentation-fault.h"

// Decays to pointer a given paramenter array in this case, Set!
SetPtr Setclr(Set s)                    /* esvaziar */
{    
    s[0] = 0;
    for (size_t i = 0; i < SET_DIM; i++)
    {
        printf("i: %d\tSET_DIM: %d\n", i, SET_DIM);
        s[i] = 0;
    }
    return s;
}
