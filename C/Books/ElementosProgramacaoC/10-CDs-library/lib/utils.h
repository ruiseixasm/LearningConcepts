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
void read_input(char *input, size_t size);
char *gets_string(char *input, size_t size);    // equivalent to gets()

// Directly from the book

long ipow(int b, int n);    // same as <math.h> pow() but for int/long instead of double
char *stradd(char *s, char c);
size_t decofstr_10(const char *s);
int ichar(char c);          // [0 - 36]
char cint(int n);           // ['0' - 'z'] (ASCII) (case sensitive)
size_t lbofstr_b(const char *s, int b);
size_t lbofstr_2(const char *s);
size_t lbofstr_8(const char *s);
size_t lbofstr_10(const char *s);
size_t lbofstr_16(const char *s);
size_t lbofstr(const char *s, int b);
char *strofchr(char *s, char c, int n);
int lblen(size_t n, int v10);
char *stroflbw(char *s, int b, int w, size_t v10);
char *stroflb(char *s, int b, size_t v10);


#endif /* LIB_UTILS */
