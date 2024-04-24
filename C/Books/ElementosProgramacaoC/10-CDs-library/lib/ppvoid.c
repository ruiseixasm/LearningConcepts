#include "ppvoid.h"

void SortPointers(void **v, size_t n, int(*f)(const void *, const void *))
{
    if (iRandom(2))
        SortPointersBubble(v, n, f);
    else
        SortPointersQuick(v, n, f);    
}

void SortPointersBubble(void **v, size_t n, int(*f)(const void *, const void *))
{
    void *m;
    for (size_t i = 1; i < n; i++)
        for (size_t j = n - 1; j >= i; j--)
            if (!f(v[j - 1], v[j]))
            {
                m = v[j - 1];
                v[j - 1] = v[j];
                v[j] = m;
            }
}

void SortPointersQuick(void **v, size_t n, int(*f)(const void *, const void *))
{
    void **i = v;
    void **j = v + (n - 1);
    void *a = *(i + (j - i)/2); // middle position
    void *m;
    
    do
    {
        while (!f(a, *i))
            i++;
        while (!f(*j, a))
            j--;
        if (i <= j)
        {
            m = *i;
            *i++ = *j;
            *j-- = m;
        }
    } while (i <= j);
    
    if (v < j)
        SortPointersQuick(v, j - v + 1, f);
    else
        SortPointersQuick(i, v + n - i, f);
}

int RestrictPointers(void **v, size_t n, int(*f)(const void *))
{
    
}

void *FirstPointer(void **v, size_t n, int(*f)(const void *))     // returns void* pointer
{
    
}

// Enabling functions that convert multiple sized pointers to void pointers

void BuildPointers(void **v, const void *p, size_t n, size_t s)
{
    
}

void ClearPointers(void **v, size_t n)
{
    
}

void IteratePointers(void **v, size_t n, void(*f)(void *))
{
    
}
