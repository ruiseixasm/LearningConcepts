#ifndef LIB_STRING_UTIL
#define LIB_STRING_UTIL

#include <string.h>
#include <stddef.h>     // needed for size_t
#include <stdlib.h>     // needed for malloc and calloc
#include <ctype.h>      // needed for tolower

char *strnew(char *s);
char *strnewn(char *s, size_t n);

char *strtolower(char *s);
char *strchrclr(char *s, const char *t);
char *strchrrep(char *s, const char *t, char c);
char *strchruniq(char *s);
char *strchrins1(char *s, char c);
char *strstndrd(char *s);

#endif /* LIB_STRING_UTIL */
