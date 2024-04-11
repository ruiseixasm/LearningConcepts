// Compiling command: gcc 01-vector-pointers.c -o 01-vector-pointers.out -lm

#include <stdio.h>
#include <math.h>   // needed for floor() and fmod()    (-lm compiling flag)
#include <stdlib.h> // needed for rand()
#include <time.h>   // needed for time()

#define NO_SUCH_FILE 1

#define MAX_ARRIVALS 26
int arrivals [MAX_ARRIVALS + 1];
              /* Ídice 0 não utilizado */
int n_arrivals;

#define MAX_LAPS 81
double times_per_lap [MAX_LAPS + 1];    // USES: double
                      /* Ídice 0 não utilizado */
int n_laps;

int loadtimes(FILE *f);
int loadarrivals();

int get_times_value(void)
{
    int i;
    for (i = 0; scanf("%lf", &times_per_lap[++i]) == 1;) {}
    return i - 1;
}

int get_times_pointer(void)
{
    double *ip;
    for (ip = times_per_lap; scanf("%lf", ++ip) == 1;) {}
    return ip - times_per_lap - 1;
}

int bestlap(void)
/* pre: n_laps >= 1 */
{
    int i;
    int best;

    for (best = 1, i = 2; i <= n_laps; ++i)
        if (times_per_lap[i] < times_per_lap[best])
            best = i;
    return best;
}

int bestlap_value(double times[], int laps)
/* pre: laps >= 1 */
{
    int i;
    int best;

    for (best = 1, i = 2; i <= laps; ++i)
        if (times[i] < times[best])
            best = i;
    return best;
}

int bestlap_pointer(double times[], int laps)   // Normally "double *times" is used instead
/* pre: laps >= 1 */
{
    double *ip;
    double *bestp;
    double *lastp;
    //   skips 0            compares wiht 2
    for (bestp = times + 1, ip = bestp + 1, lastp = times + laps;
            ip <= lastp; ++ip)
        if (*ip < *bestp)
            bestp = ip;
    return bestp - times;
}

int main()
{
    FILE *f_laps;

    if ((f_laps = fopen("TIMES_LAP.txt", "r")) == NULL) {
        fprintf(stderr, "Ficheiro TIMES_LAP.txt inacessível ou inexistente.\n");
        return NO_SUCH_FILE;
    }
    n_laps = loadtimes(f_laps);
    fclose(f_laps);

    srand(time(NULL));  // Needed to make it trully random!
    n_arrivals = loadarrivals();
    printf(     "Número de chagadas:     %2d\n"
                "Número de desistentes:  %2d\n\n",
            n_arrivals, MAX_ARRIVALS - n_arrivals);

    int the_best_lap;
    double the_best_time;

    if (!n_laps)
        printf("Não completou a primeira volta.\n");
    else
    {
        the_best_time = times_per_lap[the_best_lap = bestlap_pointer(times_per_lap, n_laps)];
        printf( "Número de voltas:       %2d\n"
                "Melhor volta:           %2d\n"
                "Tempo:                  %2.0f:%06.3f\n",
            n_laps, the_best_lap,
            floor(the_best_time / 60),
            fmod(the_best_time, 60));
    }

    return 0;
}

int loadarrivals()
{
    int total = rand() % MAX_ARRIVALS + 1;
    for (size_t i = 0; i < total; ++i)
        arrivals[i] = rand() % 6 + 1;
    return total;
}

int loadtimes(FILE *f)
{
    int i;
    for (i = 0; fscanf(f, "%lf", &times_per_lap[i]) != EOF; ++i) {}
    return i - 1;
}
