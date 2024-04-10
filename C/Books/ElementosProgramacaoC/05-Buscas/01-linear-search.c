// Compile command: gcc 01-linear-search.c -o 01-linear-search.out

#include <stdio.h>
#include <string.h>

#define MAX_GRID 26

char names  [MAX_GRID + 1][16];
int numbers [MAX_GRID + 1];

int n_cars;

int loadcars(FILE *f)   // For CARS_GRID.txt    (unsorted)
{
    int i;
    for (i = 1; fscanf(f, "%d%s", &numbers[i], names[i]) != EOF; ++i) {}
    return i - 1;
}

int indexof_number(int n)
{
    int i;
    for (i = n_cars; i && numbers[i] != n; --i) {}
    return i;
}

int indexof_number_sentinel(int n)
{
    int i;
    for (i = n_cars, numbers[0] = n; numbers[0] != n; --i) {}
    return i;
}

int indexof_name(char s[])
{
    int i;
    for (i = n_cars; i && strcmp(names[i], s); --i) {}
    return i;
}

int indexof_name_sentinel(char s[])
{
    int i;
    for (i = n_cars, strcpy(names[0], s); strcmp(names[i], s); --i) {}
    return i;
}

int main()
{
    FILE *f_cars;
    char message[16];
    int number;
    int index;

    f_cars = fopen("CARS_GRID.txt", "r");
    n_cars = loadcars(f_cars);
    fclose(f_cars);

    if (n_cars == 0)
        return 0;

    // fgets(message, sizeof(message), stdin) returns NULL in the following circumstances:
    //     If an error occurs while reading from stdin.
    //     If the end-of-file (EOF) is reached before any characters are read.
    //     If the stream pointed to by stdin is at end-of-file, indicating that no further input can be read.
    // It's important to handle these cases properly to avoid undefined behavior
    //     and ensure robustness in your program.

    while (printf("Número: "), fgets(message, sizeof(message), stdin) != NULL)
    {
        if (strcmp(message, "\n") == 0) // Check if input is just a newline
            break;
        if (sscanf(message, "%d", &number) <= 0)
            printf("Número inválido.\n");
        else if (index = indexof_number(number))
            printf("%s(%d)\n", names[index], index);
        else
            printf("Não participa.\n");
    }

    return 0;
}
