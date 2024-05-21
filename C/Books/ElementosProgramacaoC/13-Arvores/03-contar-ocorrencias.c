// Compile command: gcc 03-contar-ocorrencias.c 01-funcoes-arvores.c -g -o 03-contar-ocorrencias.out

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "01-funcoes-arvores.h"

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
    return ungetc(c, f);    // returns c
}

// Cria uma nova string reservando a memória respetiva
char *strnew(const char *s)
{
    //                             + 1 is the extra char for '\0'
    return strcpy(malloc(strlen(s) + 1), s);
}

// Liberta a memória previamente reservada por strnew()
char *strfree(char *s)
{
    free(s);
    return s = NULL;
}

typedef struct {
    char *word;
    int count;
} Counter;
typedef Counter *counterItem;

counterItem *counters;
int n_counters;

int countercmp(counterItem x, counterItem y)
{
    return strcmp(x->word, y->word);
}

// Função análoga à função hashinstall()
int treeinstall(Tree *s, char *w)
{
    return ++((counterItem)treeroot(
                treeins(s, w, (int(*)(constTItem, constTItem))countercmp)
            ))->count;
}

void dumptree(constTree s, counterItem **x)
{
    if (!treenull(s))
    {
        dumptree(treechld(s, left), x);
        *x++ = treeroot(s);                     // infixo
        dumptree(treechld(s, right), x);
    }
}

// Counter functions for sort and print counters

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

int main()
{
    int n;
    Tree wtree;         // It's a pointer to a struct not a struct
    char word[256];

    treeclr(&wtree);    // Where the pointer is set to NULL_TREE
    
    while (ungetc(getchar(), stdin) != EOF)
    {
        while (SkipChars(stdin, &n) != '\n')
        {
            ReadWord(stdin, word);
            treeinstall(&wtree, word);
        }
        getchar();
    }
    
    treein(wtree, (void(*)(TItem))PrintCounter);
    
    n_counters = treesize(wtree);
    counters = calloc(sizeof(counterItem), n_counters);
    
    counterItem *p = counters;  // Variável auxiliar
    dumptree(wtree, &p);
    
    
    return 0;
}
