#ifndef LIB_SETS
#define LIB_SETS

#include <limits.h>     // for UCHAR_MAX and CHAR_BIT
#include <stddef.h>     // for size_t

#ifndef SET_MAX
#define SET_MAX     UCHAR_MAX
#endif /* SET_MAX */
#define SET_DIM     SET_MAX/CHAR_BIT + 1


typedef unsigned char Set[SET_DIM];
typedef unsigned char Setelem;          // same as typedef unsigned Setelem;
typedef unsigned char * SetPtr;

int Setisin(Setelem x, Set s);          /* pertença */
SetPtr Setunion(Set s0, Set s1);        /* união de conjuntos */
SetPtr Setinter(Set s0, Set s1);        /* intersecção de conjuntos */
SetPtr Setdiff(Set s0, Set s1);         /* diferença de conjuntos (subtração) */
SetPtr Setcompl(Set s);                 /* complementação */
int Setissub(Set s0, Set s1);           /* inclusão */
size_t Setcard(Set s);                  /* cardinalidade */
SetPtr Setclr(Set s);                   /* esvaziar */
int Setisempty(Set s);                  /* é vazio? */
int Setisequal(Set s0, Set s1);         /* são iguais? */
SetPtr Setcpy(Set s0, const Set s1);    /* copiar o segundo para o primeiro */
SetPtr Setadd(Set s, Setelem x);        /* juntar */
SetPtr Setrm(Set s, Setelem x);         /* tirar */


#endif /* LIB_SETS */
