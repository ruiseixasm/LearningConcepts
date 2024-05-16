// Compile command: gcc 03-dispercao-encadeamentos-separados.c 02.2-funcoes-sobre-listas-void.c -o 03-dispercao-encadeamentos-separados.out

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "02.2-funcoes-sobre-listas-void.h"

// Uma sequência de letras e hífenes
int ReadWord(FILE *f, char *s)
{
    int c;
    while (c = getc(f), isalpha(c) || c == '-')
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
static char *table[MAX_HASH];
// Incrementing table2++ for the second declaration advances by MAX_HASH bytes (1 byte * MAX_HASH).
//static char table2[][MAX_HASH];

int hash(const char *s)
{
    int h = 0;
    while (*s)
        h += *s++;  // priority right to left
    return h % MAX_HASH;
}

// 3. Tableas de dispersão com encadeamentos separados

static List hash_table[MAX_HASH];

List hashsearch(const char *w) // Item = void *
{
    return listsrch(hash_table[hash(w)], w, (int(*)(constItem, constItem))strcmp);
}

List hashinstall(char *w)
{
    return listentr(&hash_table[hash(w)], strnew(w), (int(*)(constItem, constItem))strcmp);
}

typedef struct {
    char *word;
    int count;
} Counter;

typedef Counter *counterItem;

static List counter_table[MAX_HASH];

int countercmp(counterItem x, counterItem y)
{
    return strcmp(x->word, y->word);
}

counterItem NewCounter0(char *s)
{
    counterItem x = malloc(sizeof(Counter));
    x->word = strnew(s);
    x->count = 0;
    return x;
}

int counterinstall(char *w)
{
    return ++((counterItem)listhead(
            listentr(&hash_table[hash(w)], 
            w, 
            (int(*)(constItem, constItem))strcmp)
        ))->count;
}

// For post while in main()

int hashtablesize(void)
{
    List *p = hash_table;
    int s = 0;
    for (int i = MAX_HASH; i; i--)
        s += listlen(*p++);     // each table position has a list!
    return s;
}

Counter **counters; // where the multiple lists will be dump
int n_counters;

int dumphashtable(Counter **x)
{
    List *p = hash_table, s;
    Counter **x0 = x;

    for (int i = MAX_HASH; i; i--, p++)
    {
        s = *p;
        while (!listnull(s))
        {
            *x++ = listhead(s);
            s = listtail(s);
        }
    }
    return x - x0;
}

// counters functions for sort and print

void SortPointers(void **v, size_t n, int(*f)(const void *, const void *))
{
    void *m;
    for (size_t i = 1; i < n; i++)
        for (size_t j = n - 1; j >= i; j--)
            if (!f(v[j - 1], v[j]))
            {
                m = v[j - 1];
                v[j - 1] = v[j];
                v[j] = m;
            }
}

void SortCounters(int(*f)(const Counter *, const Counter *))
{
    SortPointers((void **) counters, n_counters,
                 (int(*)(const void *, const void *)) f);
}

int ltbyword(const Counter *x, const Counter *y)
{
    return strcmp(x->word, y->word) <= 0;
}

int ltbycount(const Counter *x, const Counter *y)
{
    return x->count >= y->count || x-> count == y->count && ltbyword(x, y);
}

void PrintCounter(const Counter *p)
{
    printf("%-24s %4d\n", p->word, p->count);
}

void IteratePointers(void **v, size_t n, void(*f)(void *))
{
    while (n--)
        f(*v++);
}

void PrintCounters(void)
{
    IteratePointers((void **) counters, n_counters, (void(*)(void *)) PrintCounter);
}

typedef enum {byword, bycount} SortCriterium;

int main()
{
    int n;
    char s[256];
    
    while (ungetc(getchar(), stdin) != EOF)
    {
        while (SkipChars(stdin, &n) != '\n')
        {
            ReadWord(stdin, s);
            hashinstall(s);
        }
        getchar();
    }

    n_counters = hashtablesize();
    counters = calloc(sizeof(Counter *), n_counters);   // implicit casting
    dumphashtable(counters);
    
    SortCriterium sortby = bycount;
    SortCounters(sortby == byword ? ltbyword : ltbycount);
    PrintCounters();

    return 0;
}
