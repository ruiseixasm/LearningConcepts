// Compiling command: gcc 04-matrix-char.c -o 04-matrix-char.out -lm

#include <stdio.h>
#include <math.h>   // needed for floor() and fmod()    (-lm compiling flag)
#include <string.h>
#include <float.h>

// In the global declaration you provided, the array times_per_lap will be
//     initialized with all elements set to zero. This is because it has
//     static storage duration, and when an array is declared at file scope
//     (outside of any function), but without an explicit initializer,
//     all elements are automatically initialized to zero in C.

#define MAX_LAPS 81
#define MAX_CARS 32
double times_per_lap [MAX_CARS + 1] [MAX_LAPS + 1];
int n_laps [MAX_CARS + 1];

#define MAX_ARRIVALS 26
int arrivals [MAX_ARRIVALS + 1];
              /* Ídice 0 não utilizado */

int get_arrivals(void);

int get_times(void);
int bestlap(double times[], int n_laps);

int printtime(double time);

int points(int number);

int main()
{
    int i;
    int my_best_lap;

    if (!get_times())
        printf("Nenhum carro completou a primeira volta.\n");
    else
    {
        printf("nº.  melhor volta    tempo\n\n");
        for (i = 1; i <= MAX_CARS; ++i)
            if (n_laps[i])
            {
                printf("%3d        %2d        ",
                i,
                my_best_lap = bestlap(times_per_lap[i], n_laps[i]));
                printtime(times_per_lap[i][my_best_lap]);
                printf("\n");
            }
    }

    return 0;
}

int get_arrivals(void)
{
    int i;
    int number;
    for (i = 1; i <= MAX_ARRIVALS; ++i)
    {
        printf("%2dº. lugar (0 para terminar): ", i);
        scanf ("%d", &number);
        if (!number)
            break;
        arrivals [i] = number;
    }
    return i - 1;
}

int get_times (void)
{
    int i_times;
    double this_time;
    double the_best_time;
    int the_best_lap;
    int the_fastest_car;

    char message [16];
    int number;
    double time;

    i_times = 0;
    the_best_time = DBL_MAX;

    for (;;)
    {
        scanf("%s", message);
        if (sscanf(message, "%d,%lf", &number, &time) == 2) // Inpit like "3,5.34"
        {
            ++i_times;
            times_per_lap[number][++n_laps[number]]
                        = this_time
                        = time - times_per_lap[number][0];
            if (this_time < the_best_time)
            {
                the_fastest_car = number;
                the_best_lap = n_laps[number];
                the_best_time = this_time;
            }
            times_per_lap[number][0] = time;
        }
        else if (!strcmp(message, "REPORT") && i_times)
        {
            printf("Melhor tempo: ");
            printtime(the_best_time);
            printf(" (Carro nº. %d, na %dª. volta).\n",
                    the_fastest_car,
                    the_best_lap);
        }
        else if (!strcmp(message, "STOP"))
            break;
        else
            printf("Must enter as '2,3.45'!\n");
    }
    return i_times;
}

int bestlap (double times[], int n_laps)
/* pre: n_laps >= 1 */
{
    int i;
    int best;

    for (best = 1, i = 2; i <= n_laps; ++i)
        if (times[i] < times[best])
            best = i;
    return best;
}

int printtime(double time) {
    return printf("%2d:%02d.%03d",
                   (int) time / 60,
                   (int) time % 60,
                   (int) ( (long) time * 1000 % 1000 ));
}

int points(int number) {
    static int my_points[] = {10, 6, 4, 3, 2, 1};
    return number <= 6 ? my_points[number - 1] : 0;
}
