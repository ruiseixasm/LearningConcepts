#include "input.h"

char *strreplace(char *s, char c0, char c1)
{
    for (size_t i = 0; s[i] > 0; i++)
        if (s[i] == c0)
            s[i] = c1;
    return s;
}

// Directly from the book
char *stradd(char *s, char c)
{
    char *r = s;
    while (*s)
        *s++ += c;
    return r;
}

size_t decofstr_10(const char *s)
{
    size_t n = 0;
    do
        n = n * 10 + *s - '0';
    while (++s);
    return n;
}

int ichar(char c)
{
    return c <= '9' ? c - '0' : c - 'A' + 10;
}

char cint(int n)
{
    return n < 10 ? n + '0' : n - 10 + 'A';
}

size_t lbofstr_b(const char *s, int b)
{
    size_t n = 0;
    while (*s)
        n = n * b + ichar(*s++);
    return n;
}

size_t lbofstr(const char *s, int b)
{
    return lbofstr_b(s, b);
}

char *strofchr(char *s, char c, int n)
{
    char *r = s;
    while (n--)
        *s++ = c;
    *s= '\0';
    return r;
}

int lblen(size_t n, int b)
{
    int k = 1;
    while (n /= b)
        k++;
    return k;
}

char *stroflbw(char *s, int b, int w, size_t n)
{
    s += w;
    *s = '\0';
    while (w--)
    {
        *--s = cint(n % b);
        n /= b;
    }
    return s;
}

char *stroflb(char *s, int b, size_t n)
{
    int w = lblen(n, b);
    return stroflbw(s, b, w, n);
}
