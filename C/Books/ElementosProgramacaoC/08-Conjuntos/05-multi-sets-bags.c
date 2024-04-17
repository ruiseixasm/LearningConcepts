// Compile command: gcc 05-multi-sets-bags.c bags.c -DBAG_MAX=255 -o 05-multi-sets-bags.out

#include <stdio.h>
#include <stdlib.h> // needed for rand() and srand()
#include <time.h>   // needed for time()
#include "bags.h"


int main()
{
    char ball_colors[][16] = {"Red", "Green", "Blue", "Purple", "Orange", "Black", "White", "Gray",
                              "Cyan", "Brown", "Violet", "Pink", "Aqua", "Beige", "Yellow", "Magenta"};   
    const size_t colors = sizeof(ball_colors) / 16;

    Bag balls;
    Bagclr(balls);

    const size_t picks = BAG_MAX + 1;
    srand(time(NULL));  // Needed to make it trully random!
    for (size_t i = 0; i < picks; i++)
        Bagadd(balls, rand() % colors);

    size_t frequency;
    for (size_t color = 0; color < colors; color++)
    {
        if ((frequency = Bagisin(color, balls)))
        {
            printf("%*s ", 16 - printf("%s:", ball_colors[color]), "");
            for (size_t i = 0; i < frequency; i++)
                printf(".");
            printf("\n");
        }
    }

    return 0;
}
