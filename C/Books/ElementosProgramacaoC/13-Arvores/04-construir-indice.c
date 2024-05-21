// Compile command: gcc 04-construir-indice.c 00-funcoes-listas.c 01-funcoes-arvores.c -g -o 04-construir-indice.out

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "00-funcoes-listas.h"
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
    List lines;
} Index;
typedef Index *indexItem;

indexItem NewIndex(char *s)
{
    indexItem x = malloc(sizeof(Index));
    x->word = strnew(s);
    listclr(&x->lines);
    return x;
}

int indexcmp(indexItem x, indexItem y)
{
    return strcmp(x->word, y->word);
}

int linecmp(int x, int y)
{
    return x - y;
}

// Função análoga à função hashinstall()
void treeinstall(Tree *s, char *w, int n)
{
    indexItem word_item = NewIndex(w);
    Tree word_position = treemmbr(*s, word_item, (int(*)(constTItem, constTItem))indexcmp);

    if (!word_position)
        word_position = treeins(s, word_item, (int(*)(constTItem, constTItem))indexcmp);
    else
    {
        free(word_item->word);
        free(word_item);
    }
    
    LItem line_number = (LItem)n;   // pointers are integers
    List *word_list = &((indexItem)(word_position->value))->lines;
    List line_position = listmmbr(*word_list, line_number, (int(*)(constLItem, constLItem))linecmp);
    
    if (!line_position)
        listcons(line_number, word_list);
}

// Functions to print results

void PrintInt(int n)
{
    printf(" %d", n);
}

void PrintIndex(indexItem p)
{
    printf("%s", p->word);
    listbw(p->lines, (void(*)(LItem))PrintInt);
    printf("\n");
}

int main()
{
    int n, nl = 0;
    Tree itree;         // It's a pointer to a struct not a struct
    treeclr(&itree);    // Where the pointer is set to NULL_TREE
    char word[256];
    
    while (ungetc(getchar(), stdin) != EOF)
    {
        nl++;
        while (SkipChars(stdin, &n) != '\n')
        {
            ReadWord(stdin, word);
            treeinstall(&itree, word, nl);
        }
        getchar();
    }
    
    treein(itree, (void(*)(TItem))PrintIndex);
    
    
    return 0;
}
