#include "utils.h"

// RANDOM

void setSeed()
{
    if (!seed_set)
    {
        srand(time(NULL));  // Needed to make it trully random!
        //srand(clock());     // Alternative to the first that also works
        //printf("time(NULL): %ld | clock(): %ld\n", time(NULL), clock());
        //// time(NULL): 1713457747 | clock(): 3200
        seed_set = true;
    }
}

int iRandom(int module)
{
    setSeed();
    return rand() % module;
}

int iRandomrng(int start, int end)
{
    int module = abs(end - start);
    int rvalue = iRandom(module);
    return (double)rvalue * (end - start) / module + start;
}

long lNormRandom(long module)
{
    int loops = sizeof(long) * 8 / RAND_MAX + 1;
    long rvalue = 0;
    for (int i = 0; i < loops; i++)
        rvalue += iRandom(RAND_MAX);
    return rvalue % module;
}

long lNormRandomrng(long start, long end)
{
    long module = abs(end - start);
    long rvalue = lNormRandom(module);
    return (double)rvalue * (end - start) / module + start;
}

// STRING

char *strreplace(char *s, char c0, char c1)
{
    for (size_t i = 0; s[i] > 0; i++)
        if (s[i] == c0)
            s[i] = c1;
    return s;
}

// My own

void read_newline()
{
    char dummy;
    scanf("%c", &dummy);  // consumes last '\n'
}

void press_any_key()
{
    do 
    {
        printf("\nPress a key to continue...");
    } while (getchar() != '\n');
}

void read_input(char *input, size_t size)
{
    fgets(input, size, stdin);
    input[strcspn(input, "\n")] = '\0';  // Remove trailing newline character
}

// Directly from the book

long ipow(int b, int n)     // same as <math.h> pow() but for int/long instead of double
{
    long p = 1;     // for n = 0 it must return 1
    while (n--)
        p *= b;
    return p;
}

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

int ichar(char c)   // [0 - 36]
{
    return c <= '9' ? c - '0' : c - 'A' + 10;
}

char cint(int n)    // ['0' - 'z'] (ASCII) (case sensitive)
{
    return n < 10 ? n + '0' : n - 10 + 'A';
}

size_t lbofstr_b(const char *s, int b)  // base b
{
    size_t n = 0;
    while (*s)
        n = n * b + ichar(*s++);
    return n;
}

size_t lbofstr_2(const char *s)         // base 2
{
    return lbofstr_b(s, 2);
}

size_t lbofstr_8(const char *s)         // base 8
{
    return lbofstr_b(s, 8);
}

size_t lbofstr_10(const char *s)        // base 10
{
    return lbofstr_b(s, 10);
}

size_t lbofstr_16(const char *s)        // base 16
{
    return lbofstr_b(s, 16);
}

size_t lbofstr(const char *s, int b)    // alias to lbofstr_b
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

int lblen(size_t v10, int b)
{
    int k = 1;
    while (v10 /= b)
        k++;
    return k;
}

char *stroflbw(char *s, int b, int w, size_t v10)
{
    // Fixed size of w (word), example, 9 chars (w=8)
    // 12(10) -> "00001100'\0'" (b=2)
    //  5(10) -> "00000101'\0'" (b=2)
    s += w;
    *s = '\0';      // needs 1 extra char, w + 1
    while (w--)     // writes from right to left
    {
        *--s = cint(v10 % b);   // from [0 - 36] to ['0' to 'z'] (case sensitive)
        v10 /= b;   // writes zeroes at the end of the cycle (beginning of the word)
    }
    return s;
}

char *stroflb(char *s, int b, size_t v10)
{
    // Variable size (doesn't write extra zeroes)
    // 12(10) ->    "1100'\0'" (b=2)
    //  5(10) ->     "101'\0'" (b=2)
    int w = lblen(v10, b);
    return stroflbw(s, b, w, v10);
}