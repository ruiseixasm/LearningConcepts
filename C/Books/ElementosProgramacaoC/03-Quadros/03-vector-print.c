// Compiling command: gcc 03-vector-print.c -o 03-vector-print.out -lm

#include <stdio.h>
#include <math.h>   // needed for floor() and fmod()    (-lm compiling flag)

#define MAX_ARRIVALS 26
int arrivals [MAX_ARRIVALS + 1];
              /* Ídice 0 não utilizado */
int n_arrivals;

#define MAX_LAPS 81
long times_per_lap [MAX_LAPS + 1];      // USES: long
                    /* Ídice 0 não utilizado */
int n_laps;

int get_arrivals(void);

int get_times(void);
int bestlap(void);

int printtime(long time);

int main()
{
    n_arrivals = get_arrivals();
    printf("Número de chagadas:     %2d\n"
           "Número de desistentes:  %2d\n",
            n_arrivals, MAX_ARRIVALS - n_arrivals);

    int the_best_lap;
    double the_best_time;

    if (!(n_laps = get_times()))
        printf("Não completou a primeira volta.\n");
    else
    {
        the_best_time = times_per_lap[the_best_lap = bestlap()];
        printf("Número de voltas:   %2d\n"
               "Melhor volta:       %2d\n",
                n_laps, the_best_lap);
        printf("Tempo:              ");
        printtime(times_per_lap[the_best_lap]);
        printf("\n");
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
    int i;
    int sec;
    int mil;
    for (i = 0; scanf("%d.%d", &sec, &mil) == 2; ++i)
        times_per_lap[i] = 1000L * sec + mil;   // L sets 1000 as long instead of int
    return i - 1;
}

int bestlap (void)
/* pre: n_laps >= 1 */
{
    int i;
    int best;

    for (best = 1, i = 2; i <= n_laps; ++i)
        if (times_per_lap[i] < times_per_lap[best])
            best = i;
    return best;
}

int printtime(long time) {
    return printf("%2ld:%02ld.%03ld",
                   time / 60000,
                   time % 60000 / 1000,
                   time % 1000);
}
