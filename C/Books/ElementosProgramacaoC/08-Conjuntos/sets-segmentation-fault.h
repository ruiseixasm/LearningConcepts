#ifndef LIB_SETS
#define LIB_SETS

#include <stdio.h>
#include <limits.h>     // for UCHAR_MAX and CHAR_BIT
#include <stddef.h>     // for size_t

#ifndef SET_MAX         // ERROR HERE AS IT WILL END UP CONSIDERING 255 INSTEAD OF 49!!!! (SEGMENTATION FAULT)
#define SET_MAX     UCHAR_MAX
#endif /* SET_MAX */
#define SET_DIM     SET_MAX/CHAR_BIT + 1


typedef unsigned char Set[SET_DIM];
typedef unsigned char Setelem;          // same as typedef unsigned Setelem;
typedef unsigned char * SetPtr;

SetPtr Setclr(Set s);                   /* esvaziar */


#endif /* LIB_SETS */
