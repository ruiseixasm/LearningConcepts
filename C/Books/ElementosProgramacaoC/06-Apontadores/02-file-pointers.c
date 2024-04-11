// Compile command: gcc 02-file-pointers.c -o 02-file-pointers.out

#include <stdio.h>
#include <string.h>

#define MAX_GRID 26

char names  [MAX_GRID + 1][16];
int numbers [MAX_GRID + 1];

int n_cars;

int loadcars_value(FILE *f)     // For CARS_GRID.txt    (unsorted)
{
    int i;
    for (i = 1; fscanf(f, "%d%s", &numbers[i], names[i]) != EOF; ++i) {}
    return i - 1;
}

int loadcars_pointer(FILE *f)   // For CARS_GRID.txt    (unsorted)
{
    int *ip;
    char (*sp) [16];    // sizeof: 8 (integer 64 bits = 8 bytes)
    printf("sp sizeof: %ld\n", sizeof(sp));
    char *sp_dummy;     // sizeof: 8 (integer 64 bits = 8 bytes)
    printf("sp_dummy sizeof: %ld\n", sizeof(sp_dummy));
    char s_dummy[16];   // sizeof: 16 (char 8 bits -> 1 bytes * 16 = 16 bytes)
    printf("s_dummy sizeof: %ld\n", sizeof(s_dummy));
    //                                            same as:  ++sp  because: names[i] == names[i][0]
    for (ip = numbers, sp = names; fscanf(f, "%d%s", ++ip, *++sp) != EOF;) {}
    return ip - numbers - 1;
}

int indexof_number(int n)
{
    int i;
    for (i = n_cars; i && numbers[i] != n; --i) {}
    return i;
}

int indexof_number_sentinel_value(int n)
{
    int i;
    for (i = n_cars, numbers[0] = n; numbers[i] != n; --i) {}
    return i;
}

int indexof_number_sentinel_pointer(int n)
{
    int *ip;
    //                 same as: numbers[0] = n
    for (ip = numbers + n_cars, *numbers = n; *ip != n; --ip) {}
    return ip - numbers;
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
    n_cars = loadcars_pointer(f_cars);
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