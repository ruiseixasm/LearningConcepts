#ifndef LIB_INPUT
#define LIB_INPUT

#include <stddef.h>     // for size_t
#include <stdio.h>
#include <string.h>

char *strreplace(char *s, char c0, char c1);

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

#endif /* LIB_INPUT */
