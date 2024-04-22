#ifndef LIB_STRING_UTIL
#define LIB_STRING_UTIL

#include <string.h>
#include <stddef.h>     // needed for size_t
#include <stdlib.h>     // needed for malloc and calloc

char *strnew(char *s);
char *strnewn(char *s, size_t n);

#endif /* LIB_STRING_UTIL */
