// Compile command: gcc 02-file-read-dump.c -o 02-file-read-dump.out

#include <stdio.h>
#include <string.h>

#define NO_SUCH_FILE 1

#define MAX_CARS 35
char names [MAX_CARS + 1][16];

#define MAX_GRID 26
int grid [MAX_GRID + 1];
int n_grid;

int loadgrid(FILE *f);
int loadnames(FILE *f);
void dumpnames(FILE *f);
void listnames();

int main() {

    FILE *f_cars, *f_grid;

    if ((f_grid = fopen("GRID.txt", "r")) == NULL) {
        fprintf(stderr, "Ficheiro GRID.txt inacessível ou inexistente.\n");
        return NO_SUCH_FILE;
    }
    n_grid = loadgrid(f_grid);
    fclose(f_grid);

    if ((f_cars = fopen("CARS_TODAY.txt", "r")) == NULL) {
        fprintf(stderr, "Ficheiro CARS_TODAY.txt inacessível ou inexistente.\n");
        return NO_SUCH_FILE;
    }
    (void)loadnames(f_cars);
    fclose(f_cars);

    listnames();

    if ((f_cars = fopen("CARS_GRID.txt", "w")) == NULL) {
        fprintf(stderr, "Ficheiro CARS_GRID.txt inacessível ou inexistente.\n");
        return NO_SUCH_FILE;
    }
    dumpnames(f_cars);
    fclose(f_cars);

    return 0;
}

int loadgrid(FILE *f) {
    int i;
    for (i = 0; fscanf(f, "%d", &grid[i]) != EOF; ++i) {}
    return i - 1;
}

int loadnames(FILE *f) {
    int i, n;
    for (i = 1; fscanf(f, "%d", &n) != EOF; ++i)
        fscanf(f, "%s", names[n]);      // "%s" can't have spaces!!
    return i - 1;
}

void dumpnames(FILE *f) {
    int i;
    for (i = 1; i <= n_grid; ++i)
        fprintf(f, "%02d %s\n", grid[i], names[grid[i]]);
}

void listnames() {
    int i;
    for (i = 1; i <= n_grid; ++i)
        printf("%02d %s\n", grid[i], names[grid[i]]);
}