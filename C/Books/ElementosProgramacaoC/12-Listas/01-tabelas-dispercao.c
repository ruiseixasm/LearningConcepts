// Compile command: gcc 01-tabelas-dispercao.c -o 01-tabelas-dispercao.out

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

// Uma sequência de letras e hífenes
int ReadWord(FILE *f, char *s)
{
    int c;
    while (c = getc(f), !isalpha(c) || c == '-')
        *s++ = c;
    *s = '\0';
    return ungetc(c, f);    // c is forgoten and thus needs to be given
}

// Para uma sequência de letras e hífenes
int SkipChars(FILE *f, int *n)
{
    int c;
    int k = 0;
    while ((c = getc(f)) != '\n' &&
           (isspace(c) || isdigit(c) ||
            ispunct(c) && c != '-'))
        k++;
    *n = k;
    return ungetc(c, f);
}

char *strnew(const char *s)
{
    //                                    + 1 is the extra char for '\0'
    return strcpy((char*)malloc(strlen(s) + 1), s);
}

#define MAX_HASH 1259
// Incrementing table++ for the first declaration advances by the size of a pointer to char (4 bytes).
// Incrementing table2++ for the second declaration advances by MAX_HASH bytes (1 byte * MAX_HASH).
static char *table[MAX_HASH];
//static char table2[][MAX_HASH];

int hash(const char *s)
{
    int h = 0;
    while (*s)
        h += *s++;  // priority right to left
    return h % MAX_HASH;
}

char **hashptr(const char *s)
{
    char **p = table + hash(s);
    while (*p && strcmp(*p, s))
        if (p == table)
            p = table + MAX_HASH;
        else
            p--;
    return p;
}

char *hashsearch(const char *s)
{
    return *hashptr(s);
}

char *hashinstall(const char *s)
{
    char **p = hashptr(s);
    return *p ? NULL : (*p = strnew(s));
}

int main()
{
    int n;
    char s[256];
    long n_words = 0;
    long n_unique = 0;
    
    while (ungetc(getchar(), stdin) != EOF)
    {
        while (SkipChars(stdin, &n) != '\n')
        {
            ReadWord(stdin, s);
            n_words++;
            if (hashinstall(s))
                n_unique++;
        }
        getchar();
    }
    printf("%ld %ld\n", n_words, n_unique);
    
    return 0;
}
