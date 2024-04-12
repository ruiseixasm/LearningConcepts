// Compile command: gcc 02-structs-full.c -o 02-structs-full.out

#include <stdio.h>
#include <string.h>

#define MAX_GRID 26

typedef struct
{
    int number;
    char name[16];
} Car;

int fscanCar(FILE *, Car *);
int loadCars(FILE *, Car *);
int fprintCar(FILE *, Car *);
void dumpCars(FILE *, Car *, int);

#define MAX_CARS MAX_GRID
Car cars [MAX_CARS + 1];
int n_cars;

void carsbsort(void);
int carsindexof(int);

typedef struct
{
    char name[16];
    char initial;
    char team[20];
    int pts;
} Driver;

int scanDriver(FILE *, Driver *);
int loadDrivers(FILE *, Driver *);
int fprintDriver(FILE *, Driver *);
void printDriver(Driver *);
void dumpDrivers(FILE *, Driver *, int);

#define MAX_DRIVERS 36
Driver drivers [MAX_DRIVERS + 1];
int n_drivers;

int driversindexof(char *);
void driversbsort(void);

int points(int);



int main()
{
    FILE *f_cars;
    FILE *f_drivers;
    int number;
    char name[16];
    int index;
    int pts;
    int place;
    // When smaller than the destination array it initializes all remaining contents to 0
    int arrived [MAX_DRIVERS + 1] = {0};    // Entire array initialized to 0

    f_cars = fopen("CARS_GRID.txt", "r");
    n_cars = loadCars(f_cars, cars + 1);
    fclose(f_cars);

    carsbsort();

    f_drivers = fopen("DRIVERS_BEFORE.txt", "r");
    n_drivers = loadDrivers(f_drivers, drivers + 1);
    fclose(f_drivers);

    for (place = 1; place <= 6;)
    {
        printf("%dº. lugar: ", place);
        scanf("%d", &number);
        if (number <= 0) break;

        if ((index = carsindexof(number)) == 0)
            printf("ERRO: Esse carro não participou.\n");
        else if (arrived[number])
            printf("ERRO: Esse carro chegou em %d.º lugar.\n", arrived[number]);
        else
        {
            arrived[number] = place;
            strcpy(name, cars[index].name);
            pts = points(place);
            printf("%s, %d ponto%s.\n", name, pts, pts > 1 ? "s" : "");
            drivers[driversindexof(name)].pts += pts;
            ++place;
        }
    }

    driversbsort();

    f_drivers = fopen("DRIVERS_AFTER.txt", "w");
    dumpDrivers(f_drivers, drivers + 1, n_drivers);
    fclose(f_drivers);

    return 0;
}

int fscanCar(FILE *f, Car *p)
{
    return fscanf(f, "%d%s", &p->number, p->name);
}

int loadCars(FILE *f, Car *p)
{
    Car *i = p;
    while (fscanCar(f, i++) != EOF) {}
    return i - 1 - p;
}

int fprintCar(FILE *f, Car *p)
{
    return fprintf(f, "%2d %s\n", p->number, p->name);
}

void dumpCars(FILE *f, Car *p, int n)
{
    while (n--)
        fprintCar(f, p++);
}

int fscanDriver(FILE *f, Driver *p)
{
    // "%s":   Read the first string (e.g., "Senna", "Mansell", etc.).
    // "%*c":  Discard the next character (the space after the first name).
    // "%c":   Read the middle initial character (e.g., 'A', 'N', etc.).
    // "."     Match the literal period character.
    // "%s":   Read the team name (e.g., "McLaren-Honda", "Williams-Renault", etc.).
    // "%d":   Read the integer value (e.g., 77, 59, etc.).
    return fscanf(f, "%s%*c%c.%s%d", p->name, &p->initial, p->team, &p->pts);
}

int fprintDriver(FILE *f, Driver *p)
{
    // "%*s":      This is used to dynamically determine the width of the first string based on runtime conditions.
    // "%-20s":    This is a left-aligned string with a fixed width of 20 characters for the team name.
    // "%4d":      This is a fixed-width field of 4 characters for the points scored by the driver.
    // "\n":       This adds a newline character at the end of the output to start the next line.
    return fprintf(f, "%*s %-20s %4d\n",
                20 - fprintf(f, "%s %c.", p->name, p->initial), "",     // %*s
                p->team,                                                // %-20s
                p->pts);                                                // %4d
}

void printDriver(Driver *p)
{
    printf("%*s ", 20, p->name);
    printf("%c       %-20s %4d\n", p->initial, p->team, p->pts);
}

int loadDrivers(FILE *f, Driver *p)
{
    Driver *i = p;
    while (fscanDriver(f, i++) != EOF) {}
    return i - 1 - p;
}

void dumpDrivers(FILE *f, Driver *p, int n)
{
    while (n--)
    {
        printDriver(p);
        fprintDriver(f, p++);
    }
}

void carsbsort(void)
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

int carsindexof(int n)
{
    int a;
    int i = 1;
    int j = n_cars;
    while (i < j)
        if (n <= cars[a = (i + j)/2].number)
            j = a;
        else
            i = a + 1;
    return n == cars[i].number ? i : 0;
}

int driversindexof(char *s)
{
    Driver *i;
    //  assured find, so i <= drivers + n_drivers isn't really needed
    for (i = drivers + 1; i <= drivers + n_drivers && strcmp(i->name, s); ++i) {}
    return i - drivers;
}

void driversbsort(void)
{
    Driver d;
    Driver *i;
    Driver *j;
    for (i = drivers + 2; i <= drivers + n_drivers; i++)
        for (j = drivers + n_drivers; j >= i; j--)
            if ((j - 1)->pts < j->pts)
            {
                d = *(j - 1);
                *(j - 1) = *j;
                *j = d;
            }
}

int points(int i)
{
    static int table[] = {10, 6, 4, 3, 2, 1};
    return i <= 6 ? table[i - 1] : 0;
}
