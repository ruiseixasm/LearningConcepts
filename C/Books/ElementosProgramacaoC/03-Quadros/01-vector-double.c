// Compiling command: gcc 01-vector.c -o 01-vector.out -lm

#include <stdio.h>
#include <math.h>   // needed for floor() and fmod()    (-lm compiling flag)

#define MAX_ARRIVALS 26
int arrivals [MAX_ARRIVALS + 1];
              /* Ídice 0 não utilizado */
int n_arrivals;

#define MAX_LAPS 81
double times_per_lap [MAX_LAPS + 1];    // USES: double
                      /* Ídice 0 não utilizado */
int n_laps;

int get_arrivals_for(void);
int get_arrivals_while_1(void);
int get_arrivals_while_0(void);

int get_times(void);
int bestlap(void);

int main()
{
    n_arrivals = get_arrivals_for();
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
               "Melhor volta:       %2d\n"
               "Tempo:              %2.0f:%06.3f\n",
        n_laps, the_best_lap,
        floor(the_best_time / 60),
        fmod(the_best_time, 60));
    }


    return 0;
}

int get_arrivals_for(void)
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

int get_arrivals_while_1(void)
{
    int i;
    int number;
    i = 1;
    while (i <= MAX_ARRIVALS)
    {
        printf("%2dº. lugar (0 para terminar): ", i);
        scanf ("%d", &number);
        if (!number)
            break;
        arrivals [i] = number;
        ++i;
    }
    return i - 1;
}

int get_arrivals_while_0(void)
{
    int i;
    int number;
    i = 0;
    while (i <= MAX_ARRIVALS)
    {
        printf("%2dº. lugar (0 para terminar): ", i + 1);
        scanf ("%d", &number);
        if (!number)
            break;
        arrivals [++i] = number;
    }
    return i;
}

int get_times (void)
{
    int i;
    for (i = 0; scanf("%lf", &times_per_lap[++i]) == 1;)
        ;
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
