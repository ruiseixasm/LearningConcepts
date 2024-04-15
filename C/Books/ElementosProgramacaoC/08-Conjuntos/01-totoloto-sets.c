// Compile command: gcc 01-totoloto-sets.c sets.c -DSET_MAX=49 -o 01-totoloto-sets.out -lm

#define TOTOLOTO_MAX    49
#define CHAVE           6
// Requires the parameter -DSET_MAX=49 on the gcc command line
// Otherwise, if ommited, it will return segmentation fault, even with the following line:
// #define SET_MAX         TOTOLOTO_MAX

#include <stdio.h>
#include <stdlib.h> // needed for rand() and srand()
#include <time.h>   // needed for time()

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
    srand(time(NULL));  // Needed to make it trully random!
    
    Set play;
    Set result;
    
    Setclr(play);
    Setclr(result);
    
    unsigned int input_number;
    
    for (int i = 0; i < CHAVE; i++)
    {
        do
        {
            printf("Introduza o %dº número: ", i + 1);
            scanf("%ud", &input_number);
            input_number--;
        } while (input_number >= TOTOLOTO_MAX || Setisin(input_number, play));
        
        Setadd(play, input_number);
    }
    
    printf("Chave introduzida:");
    for (int i = 0; i < TOTOLOTO_MAX; i++)
    {
        if (Setisin(i, play))
            printf(" %d", i + 1);
    }
    printf("\n");
    
    int total = rand() % TOTOLOTO_MAX + 1;

    return 0;
}
