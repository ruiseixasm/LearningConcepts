// Compiling command: gcc -Wall -g -c 04-string-pointers.c -o 04-string-pointers.o


// DECLARATION

char *strcpy(char *, char *);
        /*  "string copy"
            copia o segundo argumento para o primeiro,
            devolve o primeiro argumento            */

int strcmp(char *, char *);
        /*  "string comparison"
            devolve um número negativo se o primeiro
            argumento for menor que o segundo, zero
            se forem iguais, e um número positivo se
            o primeiro for maior que o segundo      */

size_t strlen(char *);
        /*  "string length"
            devolve o comprimento do argumento      */

char *strcat(char *, char *);
        /*  "string concatenation"
            concatena o segundo argumento ao primeiro,
            devolve o primeiro argumento            */

char *strchr(char *, char);
        /*  "char in string"
            devolve um apontador para a primeira
            ocorrência do carácter na cadeia,
            ou NULL se não ocorrer                  */

char *strstr(char *, char *);
        /*  "string in string"
            devolve um apontador para a primeira
            ocorrência da segunda cadeia na
            primeira, ou NULL se não ocorrer        */


// DEFINITION

char *strcpy(char *s, char *t)
{
    char *p = s;
    while ((*s++ = *t++)) {}
    return p;
}

int strcmp(char *s, char *t)
{
    for (; *s == *t; s++, t++)
        if (!*s)
            return 0;
    return *s - *t;
}

size_t strlen(char *s)
{
    char *p = s;
    while (*s)
        ++s;
    return s - p;
}

char *strcat(char *s, char *t)
{
    char *p = s;
    while (*s)
        ++s;
    while ((*s++ = *t++)) {}
    return p;
}

char *strchr(char *s, char c)
{
    for (; *s; ++s)
        if (*s == c)
            return s;
    return NULL;
}

char *strstr(char *s, char *t)
{
    char *p;
    char *q;
    for (; *s; ++s)
    {
        for (p = s, q = t; *q && *p == *q; ++p, ++q) {}
        if (!*q)
            return s;
    }
    return NULL;
}
