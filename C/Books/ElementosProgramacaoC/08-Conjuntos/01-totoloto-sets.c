// Compile command: gcc 01-totoloto-sets.c sets.c -o 01-totoloto-sets.out

#define TOTOLOTO_MAX    49
#define SET_MAX         TOTOLOTO_MAX

#include <stdio.h>
#include "sets.h"

int hasprize(Set play, Set key)
{
    Set tmp;    // becaus Setinter modifies s0 (side effects)
    /* intersecção de conjuntos */
    return Setcard(Setinter(Setcpy(tmp, play), key)) >= 3;
}

int prize(Set play, Set key, int supl)
{
    Set tmp;
    switch (Setcard(Setinter(Setcpy(tmp, play), key)))
    {
        case 6: return 1;
        case 5: return 3 - Setisin(supl, play);
        case 4: return 4;
        case 3: return 5;
        case 2: case 1: case 0: return 0;   // same as default:
    }
}

int main()
{
    

    return 0;
}