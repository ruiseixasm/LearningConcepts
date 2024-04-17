#ifndef LIB_SETS
#define LIB_SETS

#include <limits.h>     // for UCHAR_MAX and CHAR_BIT
#include <stddef.h>     // for size_t
#include <stdarg.h>     // variable number of arguments, ...
#include <stdio.h>

#ifndef SET_MAX         // use -DSET_MAX=49 for other SET_MAX values (Ex.: 49)
#define SET_MAX     UCHAR_MAX               // UCHAR_MAX = 255
#endif /* SET_MAX */
#define SET_DIM     SET_MAX/CHAR_BIT + 1    // CHAR_BIT = 8


typedef unsigned char Set[SET_DIM];
typedef size_t Setelem;                     // same as typedef unsigned Setelem;
typedef unsigned char * SetPtr;

int Setisin(Setelem x, const Set s);    /* pertença */
SetPtr Setunion(Set s0, Set s1);        /* união de conjuntos */
SetPtr Setinter(Set s0, Set s1);        /* intersecção de conjuntos */
SetPtr Setdiff(Set s0, Set s1);         /* diferença de conjuntos (subtração) */
SetPtr Setcompl(Set s);                 /* complementação */

int Setissub(Set s0, Set s1);           /* inclusão */
size_t Setcard(const Set s);            /* cardinalidade */
SetPtr Setclr(Set s);                   /* esvaziar */
int Setisempty(Set s);                  /* é vazio? */
int Setisequal(Set s0, Set s1);         /* são iguais? */
SetPtr Setcpy(Set s0, const Set s1);    /* copiar o segundo para o primeiro */
SetPtr Setadd(Set s, Setelem x);        /* juntar */
SetPtr Setrm(Set s, Setelem x);         /* tirar */

// EXTRA FUNCTIONS

SetPtr Setaddn(Set s, int n, ...);      /* adiciona sucessívos argumentos anónimos */
SetPtr Setaddrng(Set s, Setelem x0, Setelem x1);    /* addiciona um range */
SetPtr Setaddstr(Set s, char *w);       /* juntar string */

Setelem Setfirst(const Set s);          /* primeiro elemento NÃO vazio */
Setelem Setpos(const Set s, size_t n);  /* n-ésimo elemento NÃO vazio */

// MY OWN

/* print a Set */
void Setprint(const Set s, char *format_string, int increment, size_t elements);

#endif /* LIB_SETS */
