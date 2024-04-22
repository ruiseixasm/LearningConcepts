#include "string_util.h"


char *strnew(char *s)
{
    size_t n = strlen(s);
    return strnewn(s, n);
}

char *strnewn(char *s, size_t n)
{
    return strncpy((char*)calloc(n + 1, 1), s, n);
}
