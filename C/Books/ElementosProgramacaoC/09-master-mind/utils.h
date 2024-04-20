#ifndef LIB_UTILS
#define LIB_UTILS

#include <stdlib.h>     // needed for rand() and srand()
#include <time.h>       // needed for time() and clock()
#include <stddef.h>     // needed for size_t
#include <stdbool.h>    // needed for type bool
#include <string.h>
#include <stdio.h>      // to enable debugging messages

// RANDOM

static bool seed_set = false;

void setSeed();
int iRandom(int module);
int iRandomrng(int start, int end);
long lNormRandom(long module);
long lNormRandomrng(long start, long end);

// STRING

char *strreplace(char *s, char c0, char c1);

// My own

void read_newline();
void press_any_key();

// Directly from the book
char *stradd(char *s, char c);
size_t decofstr_10(const char *s);
int ichar(char c);
char cint(int n);
size_t lbofstr_b(const char *s, int b);
size_t lbofstr(const char *s, int b);
char *strofchr(char *s, char c, int n);
int lblen(size_t n, int b);
char *stroflbw(char *s, int b, int w, size_t n);
char *stroflb(char *s, int b, size_t n);


#endif /* LIB_UTILS */
