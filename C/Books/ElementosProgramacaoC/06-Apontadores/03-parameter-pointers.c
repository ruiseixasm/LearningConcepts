// Compiling command: gcc 03-parameter-pointers.c -o 03-parameter-pointers.out -lm

#include <stdio.h>
#include <math.h>   // needed for floor() and fmod()    (-lm compiling flag)

int roots(double a, double b, double c,
            double *x1, double *x2)
{
    double delta = b*b - 4.0*a*c;
    if (delta >= 0.0)
    {
        *x1 = (-b + sqrt(delta)) / (2.0 * a);
        *x2 = *x1 - sqrt(delta)/a;
        return 1;
    }
    else
        return 0;
}

int tick_and(int *h, int *m)
{
    return !(*m = (*m + 1) % 60) && !(*h = (*h + 1) % 24);
}

int tick_or(int *h, int *m)
{
    return !((*m = (*m + 1) % 60) || (*h = (*h + 1) % 24));
}

int sumn(int n)
{
    int s;
    for (s = 0; n > 0; --n)
        s += n;
    return s;
}

void swap(int *ip, int *jp)
{
    int temp;
    temp = *ip;
    *ip = *jp;
    *jp = temp;
}

void intvadd_index(int x[], int y[], int n)
{
    int i;
    for (i = 0; i < n; ++i)
        x[i] += y[i];
}

void intvadd_pointer(int *x, int *y, int n)
{
    for (; n > 0; --n)
        *x++ += *y++;
}

double *dblvmin_backward(double *x, int n)
/* pre: n >= 1  */
{
    double *ip;
    double *mp;
    //                   jumps less 1
    for (mp = x + n - 1, ip = mp - 1; ip >= x; --ip)
        if (*ip < *mp)
            mp = ip;
    return mp;
}

double *dblvmin_forward(double *x, int n)
/* pre: n >= 1  */
{
    double *mp;
    //   jumps more 1
    for (mp = x++; --n; ++x)
        if (*x < *mp)
            mp = x;
    return mp;
}

int *intvint_while(int *x, int n, int a)
{
    while (n && *x != a)
    {
        --n;
        ++x;
    }
    return (n ? x : NULL);
}

int *intvint_for(int *x, int n, int a)
{
    for (; n; --n, ++n)
        if (*x == a)
            return x;
    return NULL;
}

int main()
{
    double a;
    double b;
    double c;
    double x1;
    double x2;
    printf("a b c: ");
    scanf("%lf%lf%lf", &a, &b, &c);
    if (roots(a, b, c, &x1, &x2))
        printf("x1 = %4.2lf x2 = %4.2lf\n", x1, x2);
    else
        printf("Não há raízes.\n");
    return 0;
}