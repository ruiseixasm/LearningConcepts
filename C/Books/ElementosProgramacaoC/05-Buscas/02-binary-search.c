// Compile command: gcc 02-binary-search.c -o 02-binary-search.out

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

void bubblesort(int v[], int n)
{
    int i;
    int j;
    int m;
    for (i = 2; i <= n; i++)
        for (j = n; j >= i; j--)
            if (v[j - 1] > v[j])
            {
                m = v[j - 1];
                v[j - 1] = v[j];
                v[j] = m;
            }
}

void bubblesort_numbers()
{
    char my_name[16];
    int my_number;
    int i;
    int j;
    for (i = 2; i <= n_cars; i++)
        for (j = n_cars; j >= i; j--)
            if (numbers[j - 1] > numbers[j])
            {
                my_number = numbers[j - 1];
                numbers[j - 1] = numbers[j];
                numbers[j] = my_number;
                strcpy(my_name, names[j - 1]);
                strcpy(names[j - 1], names[j]);
                strcpy(names[j], my_name);
            }
}

void bubblesort_names()
{
    char my_name[16];
    int my_number;
    int i;
    int j;
    for (i = 2; i <= n_cars; i++)
        for (j = n_cars; j >= i; j--)
            if (strcmp(names[j - 1], names[j]) > 0)
            {
                my_number = numbers[j - 1];
                numbers[j - 1] = numbers[j];
                numbers[j] = my_number;
                strcpy(my_name, names[j - 1]);
                strcpy(names[j - 1], names[j]);
                strcpy(names[j], my_name);
            }
}

int indexof_number_dichotomy(int n)
{
    int a;
    int i = 1;
    int j = n_cars;

    while (i < j)
        if (n <= numbers[a = (i + j) / 2])
            j = a;
        else
            i = a + 1;

    return n == numbers[i] ? i : 0;
}

int indexof_number_trichotomy(int n)
{
    int a;
    int i = 1;
    int j = n_cars;

    while (i <= j)
        if (n < numbers[a = (i + j) / 2])
            j = a - 1;
        else if (n > numbers[a])
            i = a + 1;
        else
            return a;

    return 0;
}

int indexof_name_dichotomy(char s[])
{
    int a;
    int i = 1;
    int j = n_cars;

    while (i < j)
        if (strcmp(s, names[a = (i + j) / 2]) <= 0)
            j = a;
        else
            i = a + 1;

    return strcmp(s, names[i]) ? 0 : i;
}

int indexof_name_trichotomy(char s[])
{
    int a;
    int i = 1;
    int j = n_cars;

    while (i <= j)
        if (strcmp(s, names[a = (i + j) / 2]) < 0)
            j = a - 1;
        else if (strcmp(s, names[a]) > 0)
            i = a + 1;
        else
            return a;

    return 0;
}

int sign(int n)
{
    return (n >= 0) - (n <= 0);
}

int indexof_number_switch(int n)
{
    int a;
    int i = 1;
    int j = n_cars;
    while (i <= j)
    {
        switch (sign(n - numbers[a = (i + j) / 2]))
        {
        case -1:
            j = a - 1;
            break;
        case 1:
            i = a + 1;
            break;
        default:    // For case 0
            return a;
        }
    }
    return 0;
}

int indexof_name_switch(char s[])
{
    int a;
    int i = 1;
    int j = n_cars;
    while (i <= j)
    {
        switch (sign(strcmp(s, names[a = (i + j) / 2])))
        {
        case -1:
            j = a - 1;
            break;
        case 1:
            i = a + 1;
            break;
        default:    // For case 0
            return a;
        }
    }
    return 0;
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

    bubblesort_numbers();   // Needs to sort numbers array in order to use binary search!

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
        else if (index = indexof_number_switch(number))
            printf("%s\n", names[index]);
        else
            printf("Não participa.\n");
    }

    return 0;
}
