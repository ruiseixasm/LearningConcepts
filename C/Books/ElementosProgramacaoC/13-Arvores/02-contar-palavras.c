// Compile command: gcc 02-contar-palavras.c 01-funcoes-arvores.c -g -o 02-contar-palavras.out

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

int main()
{
    int n;
    long n_words, n_unique;
    Tree wtree;         // It's a pointer to a struct not a struct
    char word[256];
    
    treeclr(&wtree);    // Where the pointer is set to NULL_TREE
    n_words = 0;
    
    while (ungetc(getchar(), stdin) != EOF)
    {
        while (SkipChars(stdin, &n) != '\n')
        {
            ReadWord(stdin, word);
            n_words++;
            char* new_word = strnew(word);
            if (!treemmbr(wtree, new_word, (int(*)(constTItem, constTItem))strcmp))
                treeins(&wtree, new_word, (int(*)(constTItem, constTItem))strcmp);
            else
                strfree(new_word);
        }
        getchar();
    }
    
    n_unique = treesize(wtree);
    printf("%ld %ld\n", n_words, n_unique);

    return 0;
}
