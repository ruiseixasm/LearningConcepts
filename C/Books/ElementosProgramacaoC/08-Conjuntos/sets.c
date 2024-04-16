#include "sets.h"

int Setisin(Setelem x, const Set s)     /* pertença */
{
    // same as:
    //   ( s[x/CHAR_BIT] >> ( x % CHAR_BIT ) ) & 1
    return s[x/CHAR_BIT] >> x % CHAR_BIT & 1;
}

SetPtr Setunion(Set s0, Set s1)         /* união de conjuntos */
{
    // Post-increment operator (i++) typically involves an additional operation to create
    //     a temporary copy of the original value of i before incrementing it.
    //     This extra operation can introduce a slight overhead.
    // However, in most cases, the difference in performance between pre-increment and post-increment
    //     is negligible, and modern compilers are often able to optimize both versions effectively.
    for (Setelem i = 0; i < SET_DIM; i++)
        s0[i] |= s1[i];
    return s0;
}

SetPtr Setinter(Set s0, Set s1)         /* intersecção de conjuntos */
{
    for (Setelem i = 0; i < SET_DIM; i++)
        s0[i] &= s1[i];
    return s0;
}

SetPtr Setdiff(Set s0, Set s1)          /* diferença de conjuntos (subtração) */
{
    for (Setelem i = 0; i < SET_DIM; i++)
        s0[i] &= ~s1[i];
    return s0;
}

SetPtr Setcompl(Set s)                  /* complementação */
{
    for (Setelem i = 0; i < SET_DIM; i++)
        s[i] = ~s[i];
    return s;
}

int Setissub(Set s0, Set s1)            /* inclusão */
{
    for (Setelem i = 0; i < SET_DIM; i++)
        if (s0[i] & ~s1[i])
            return 0;   // false
    return 1;           // true
}

size_t Setcard(const Set s)             /* cardinalidade */
{
    Setelem n = 0;
    Setelem x;
    for (Setelem i = 0; i < SET_DIM; i++)
        for (x = s[i]; x; x >>= 1)
            n += x & 1;
    return n;
}

// Decays to pointer a given paramenter array in this case, Set!
SetPtr Setclr(Set s)                    /* esvaziar */
{
    for (Setelem i = 0; i < SET_DIM; i++)
        s[i] = 0;
    return s;
}

int Setisempty(Set s)                   /* é vazio? */
{
    for (Setelem i = 0; i < SET_DIM; i++)
        if (s[i])
            return 0;   // false
    return 1;           // true
}

int Setisequal(Set s0, Set s1)          /* são iguais? */
{
    for (Setelem i = 0; i < SET_DIM; i++)
        if (s0[i] != s1[i])
            return 0;   // false
    return 1;           // true
}

SetPtr Setcpy(Set s0, const Set s1)           /* copiar o segundo para o primeiro */
{
    for (Setelem i = 0; i < SET_DIM; i++)
        s0[i] = s1[i];
    return s0;
}

SetPtr Setadd(Set s, Setelem x)         /* juntar */
{
    // same as:
    //               1 << (x % CHAR_BIT)
    s[x/CHAR_BIT] |= 1 << x % CHAR_BIT;
    return s;
}

SetPtr Setrm(Set s, Setelem x)          /* tirar */
{
    // same as:
    //               ~(1 << (x % CHAR_BIT))
    s[x/CHAR_BIT] &= ~(1 << x % CHAR_BIT);
    return s;
}

// EXTRA FUNCTIONS

SetPtr Setaddn(Set s, int n, ...)       /* adiciona sucessívos argumentos anónimos */
{
    va_list p;          // multiple arguments iterator
    va_start(p, n);     // initializes the iterator to n
    while (n--)
        Setadd(s, (Setelem) va_arg(p, int));    // va_arg returns present position
                                                // and moves to the next one (va_next)
    va_end(p);          // cleans up args iterator
    return s;    
}

SetPtr Setaddrng(Set s, Setelem x0, Setelem x1)     /* addiciona um range */
{
    while (x0 <= x1)
        Setadd(s, x0++);    // increments (moves) bit position
    return s;
}

SetPtr Setaddstr(Set s, char *w)        /* juntar string */
{
    while (*w)  // scans up to the last char that is 0 ('\0')
        Setadd(s, (Setelem) *w++);
    return s;
}

Setelem Setfirst(const Set s)           /* primeiro elemento NÃO vazio */
{
    Setelem i = 0;
    while (!Setisin(i, s))
        i++;
    return i;   // first element position
}

Setelem Setpos(const Set s, size_t n)   /* n-ésimo elemento NÃO vazio */
{
    Setelem i = 0;
    while (n -= Setisin(i, s))
        i++;
    return i;   // n-th element position
}

// MY OWN

/* print a Set */
void Setprint(const Set s, char *format_string, int increment, size_t elements)
{
    if (format_string == NULL)
        format_string = "%d ";
        
    Set s_copy;
    Setcpy(s_copy, s);
    
    for (Setelem i = 0; i <= SET_MAX; i++)
    {
        if (Setisin(i, s))
        {
            printf(format_string, i + increment);
            Setrm(s_copy, i);   // removes printed element from the s_copy
            if (Setisempty(s_copy) || elements && elements-- == 1)
                break;
                
        }
    }
}
