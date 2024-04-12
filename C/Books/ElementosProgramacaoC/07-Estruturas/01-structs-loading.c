// Compile command: gcc 01-structs-loading.c -o 01-structs-loading.out

#include <stdio.h>

#define NO_SUCH_FILE 1

struct CarS
{
    int number;
    char name [16];
};


typedef struct CarTS
{
    int number;
    char name [16];
} CarTS;

typedef struct
{
    int number;
    char name [16];
} Car;

#define MAX_CARS 26
struct CarS cars_s [MAX_CARS + 1];
CarTS cars_ts [MAX_CARS + 1];
Car cars [MAX_CARS + 1];
        /* Ídice 0 não utilizado */
int n_cars;

int fscanCar(FILE *f, Car *p)
{
    return fscanf(f, "%d%s", &p->number, p->name);      // Operator "->" has the highest precedence
  //return fscanf(f, "%d%s", &(*p).number, (*p).name);  // Operator "." has the highest precedence
}

int fprintCar(FILE *f, Car *p)
{
    return fprintf(f, "%2d %s\n", p->number, p->name);      // Operator "->" has the highest precedence
  //return fprintf(f, "%2d %s\n", (*p).number, (*p).name);  // Operator "." has the highest precedence
}

int loadcars_index(FILE *f)
{
    int i = 0;
    while (fscanCar(f, &cars[++i]) != EOF) {}
    return i - 1;
}

int loadcars_pointer(FILE *f)
{
    Car *i = cars;
    while (fscanCar(f, ++i) != EOF) {}
    return i - 1 - cars;
}

int loadCars_function(FILE *f, Car *p)
{
    Car *i = p;
    while (fscanCar(f, ++i) != EOF) {}
    return i - 1 - p;
}

int loadCars(FILE *f, Car *p)
{
    Car *i = p + 1;
    while (fscanf(f, "%d%s", &i->number, i->name) != EOF)
        i++;
    return i - 1 - p;
}

void bubblesort_index()
{
    Car d;
    int i;
    int j;
    for (i = 2; i <= n_cars; i++)
        for (j = n_cars; j >= i; j--)
            if (cars[j - 1].number > cars[j].number)
            {
                d = cars[j - 1];
                cars[j - 1] = cars[j];
                cars[j] = d;
            }
}

void bubblesort_pointer()
{
    Car d;
    Car *i;
    Car *j;
    for (i = cars + 2; i <= cars + n_cars; i++)
        for (j = cars + n_cars; j >= i; j--)
            if ((j - 1)->number > j->number)
            {
                d = *(j - 1);
                *(j - 1) = *j;
                *j = d;
            }
}

int main()
{
    FILE *f_cars;

    if ((f_cars = fopen("CARS_GRID.txt", "r")) == NULL) {
        fprintf(stderr, "Ficheiro CARS_GRID.txt inacessível ou inexistente.\n");
        return NO_SUCH_FILE;
    }
    n_cars = loadCars(f_cars, cars);
    fclose(f_cars);

    printf("Unsorted:\n");
    for (Car *i = cars + 1; i <= cars + n_cars; ++i)
        printf("%02d %s\n", i->number, i->name);

    bubblesort_index();
    printf("\nSorted by index:\n");
    for (Car *i = cars + 1; i <= cars + n_cars; ++i)
        printf("%02d %s\n", i->number, i->name);

    if ((f_cars = fopen("CARS_GRID.txt", "r")) == NULL) {
        fprintf(stderr, "Ficheiro CARS_GRID.txt inacessível ou inexistente.\n");
        return NO_SUCH_FILE;
    }
    n_cars = loadCars(f_cars, cars);
    fclose(f_cars);

    printf("\nUnsorted:\n");
    for (Car *i = cars + 1; i <= cars + n_cars; ++i)
        printf("%02d %s\n", i->number, i->name);

    bubblesort_pointer();
    printf("\nSorted by pointer:\n");
    for (Car *i = cars + 1; i <= cars + n_cars; ++i)
        printf("%02d %s\n", i->number, i->name);

    return 0;
}
