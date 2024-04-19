#include "input.h"


char *strreplace(char *s, char c0, char c1)
{
    for (size_t i = 0; s[i] > 0; i++)
        if (s[i] == c0)
            s[i] = c1;
    return s;
}
