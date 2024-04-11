// Compiling command: gcc -Wall -g -c 05-function-pointers.c -o 05-function-pointers.o

#include <stddef.h>     // needed for size_t


// DECLARATION

double *vecbest_value(double *, int, int (*)(double, double));
double *vecbest_pointer(double *, int, double * (*)(double *, double *));
int *intvexists(int *, int, int (*)(int));
int isthis(int);
int *intvint(int *, int, int);


// DEFINITION

double *vecbest_value(double *x, int n, int (*better)(double, double))
/* pre: n >= 1  */
{
    double *mp;
    for (mp = x++; --n; ++x)
        if (!better(*mp, *x))
            mp = x;
    return mp;
}

int smaller(double x, double y)
{
    return x <= y;
}

double *dblvmin(double *x, int n)
/* pre: n >= 1  */
{
    return vecbest_value(x, n, smaller);
}

double *vecbest_pointer(double *x, int n, double * (*best)(double *, double *))
/* pre: n >= 1  */
{
    double *mp;
    for (mp = x++; --n; ++x)
        mp = best(mp, x);
    return mp;
}

double *smallest(double *x, double *y)
{
    return (*x <= *y ? x : y);
}

int *intvexists(int *x, int n, int (*b)(int))
{
    for (; n; --n, ++x)
        if (b(*x))
            return x;
    return NULL;
}

int this;

int isthis(int z)
{
    return z == this;
}

int *intvint(int *x, int n, int a)
{
    this = a;
    return intvexists(x, n, isthis);
}
