#include "string_util.h"


char *strnew(const char *s)
{
    size_t n = strlen(s);
    return strnewn(s, n);
}

char *strnewn(const char *s, size_t n)
{
    return strncpy((char*)calloc(n + 1, 1), s, n);
}

char *strtolower(char *s)
{
    char *s0 = s;
    while (*s = tolower(*s))
        s++;
    return s0;
}

// Removes all characters equal to those in string t
char *strchrclr(char *s, const char *t)
{
    char *s0 = s;
    for (char *p = s; *p = *s; s++)
        if (strchr(t, *s) == NULL)  // strchr() search for character(2) in string(1)
            p++;    // if is NOT found
    return s0;
}

// Replaces all characters equal to those in string t with char c
char *strchrrep(char *s, const char *t, char c)
{
    for (char *p = s; *p; p++)
        if (strchr(t, *p) != NULL)
            *p = c; // if is found
    return s;
}

// Removes repeated chars
char *strchruniq(char *s)
{
    char *s0 = s;
    for (char *p = s; *p = *s; s++)
        if (*s != *(s + 1))
            p++;
    return s0;
}

// Inserts a char in the first position, moves forward the rest
char *strchrins1(char *s, char c)
{
    char *p = s;
    while (*p++) {}
    for (; p > s; p--)
        *p = *(p - 1);
    *p = c;
    return s;
}

// Normalize the string s
char *strstndrd(char *s)
{
    char c;
    strchrclr(s, " h");
    strchrrep(s, "y", 'i');
    strchrrep(s, "w", 'u');
    c = *s;
    strchrclr(s, "aeiou");
    if (strchr("aeiou", c) != NULL)
        strchrrep(s, "kqszx", 'c');
    strchrrep(s, "j", 'q');
    strchruniq(s);
    return s;
}

char *strtrmr(char *s)
{
    char *s0 = s;
    while (*s)
        s++;
    while (s > s0 && isspace(*--s))
        *s = '\0';
    return s0;
}

// const char *strtrml(const char *s)   // Doesn't allow any future changes!!
char *strtrml(char *s)                  // Allows future changes!
{
    while (isspace(*s))
        s++;
    return s;
}
