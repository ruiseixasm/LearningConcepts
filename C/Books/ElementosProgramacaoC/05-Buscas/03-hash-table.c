// Compile command: gcc 03-hash-table.c -o 03-hash-table.out

#include <stdio.h>
#include <string.h>

#define MAX_GRID 26
#define MAX_HASH 37     // next prime above 26/0.80

char names  [MAX_HASH][16];
int numbers [MAX_HASH];

int n_cars;

void clearhashtable()   // Because global variable array content is initialized to 0
{
    int i;
    for (i = 0; i < MAX_HASH; ++i)
        strcpy(names[i], "");
}

int hash(char s[])
{
    int i, t, n = strlen(s);
    for (i = 0, t = 0; i < n; ++i)
        t += s[i];
    return t % MAX_HASH;    // Agora a posição de índice 0 (zero) está a ser utilizada pela tabela
}

int hash_hexa(char s[])
{
    int n = strlen(s);
    return (s[0] + s[n - 1] + 16*n) % MAX_HASH;
}

int hashinstall(char s[])
{
    int i;
    for (i = hash(s); strlen(names[i]); i = (i + 1) % MAX_HASH) {}
    strcpy(names[i], s);
    return i;
}

int loadhashtable(FILE *f)
{
    int n;
    char s[16];
    int i;
    for (i = 0; fscanf(f, "%d%s", &n, s) != EOF; ++i)
        numbers[hashinstall(s)] = n;
    return i;
}

int hashsrch(char s[])
{
    int i;
    for (i = hash(s); ; i = (i + 1) % MAX_HASH)
    {
        if (strlen(names[i]) == 0)
            return -1;
        if (strcmp(names[i], s) == 0)
            return i;
    }
}

int hashindex(char s[])
{
    int i;
    for (i = hash(s); strlen(names[i]) && strcmp(names[i], s); i = (i + 1) % MAX_HASH) {}
    return i;
}

int hashinstall_index(char s[])
{
    int i = hashindex(s);
    if (strlen(names[i]) == 0)
    {
        strcpy(names[i], s);
        return i;
    }
    else
        return -1;
}

int hashsrch_index(char s[])
{
    int i = hashindex(s);
    return strlen(names[i]) ? i : -1;
}

int main()
{
    FILE *f_cars;
    char message[16];
    int index;

    clearhashtable();
    f_cars = fopen("CARS_GRID.txt", "r");
    n_cars = loadhashtable(f_cars);
    fclose(f_cars);

    if (n_cars == 0)
        return 0;

    // fgets(message, sizeof(message), stdin) returns NULL in the following circumstances:
    //     If an error occurs while reading from stdin.
    //     If the end-of-file (EOF) is reached before any characters are read.
    //     If the stream pointed to by stdin is at end-of-file, indicating that no further input can be read.
    // It's important to handle these cases properly to avoid undefined behavior
    //     and ensure robustness in your program.

    while (printf("Nome: "), fgets(message, sizeof(message), stdin) != NULL)
    {
        if (strcmp(message, "\n") == 0) // Check if input is just a newline
            break;
          
        // Remove newline character included by fgets!!
        message[strcspn(message, "\n")] = '\0';

        if ((index = hashsrch(message)) >= 0)
            printf("%d\n", numbers[index]);
        else
            printf("Não participa.\n");
    }

    while (printf("Nome: "), fgets(message, sizeof(message), stdin) != NULL)
    {
        if (strcmp(message, "\n") == 0) // Check if input is just a newline
            break;

        // Remove newline character included by fgets!!
        message[strcspn(message, "\n")] = '\0';

        if ((index = hashsrch_index(message)) >= 0)
            printf("%d\n", numbers[index]);
        else
            printf("Não participa.\n");
    }

    return 0;
}
