#ifndef LIB_PPVOID
#define LIB_PPVOID

#include <stddef.h>     // needed for size_t
#include "utils.h"

void SortPointers(void **v, size_t, int(*f)(const void *, const void *));
void SortPointersBubble(void **v, size_t n, int(*f)(const void *, const void *));
void SortPointersQuick(void **v, size_t n, int(*f)(const void *, const void *));
int RestrictPointers(void **v, size_t n, int(*f)(const void *));
void *FirstPointer(void **v, size_t n, int(*f)(const void *));    // returns void* pointer

// Enabling functions that convert multiple sized pointers to void pointers
void BuildPointers(void **v, const void *p, size_t n, size_t s);
void ClearPointers(void **v, size_t n);
void IteratePointers(void **v, size_t n, void(*f)(void *));

#endif /* LIB_PPVOID */
