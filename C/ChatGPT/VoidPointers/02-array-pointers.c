#include <stdio.h>

// In C, all pointer types (char*, int*, float*, etc.) have the same size because they represent memory addresses,
//     and memory addresses typically have a fixed size determined by the architecture of the system.
// "In C, all pointers have the same size, while the size of values depends on their data type."

void BuildPointers(void **v, const void *p, size_t n, size_t s)
{
    printf("n: %d, s: %d bytes, (int *)p: %p, (char *)p: %p, p: %p\n", n, s, (int *)p, (char *)p, p);
    // Pointers are like a needle on a record groove, they need to be place on the right groove,
    //     4 bytes means 4 grooves appart (i += s)
    for (char *i = (char *)p; n; n--, i += s, *v++) // Size s, bytes, is in multiple of chars, that have 1 byte
    {
        *v = (void *)i;   // All pointers have integer size, Ex. 4 bytes, equally sized, even void addresses!
        printf("Address i: %p, Address *v: %p, Value i: %d, Value *v: %d\n",
                        i, *v, *i, *((int *)*v));
    }
}

int main() {
    // Define an array of integers
    int array[] = {10, 20, 30, 40, 50};

    // Define an array of void pointers
    void *pointers[5];

    // Use the BuildPointers function to build pointers to the elements of the array
    BuildPointers(pointers, array, 5, sizeof(int));

    // Print the addresses and values pointed to by the pointers
    printf("\nAddresses and Values:\n");
    for (int i = 0; i < 5; i++) {
        printf("Pointer %d: Address=%p, Value=%d\n", i, pointers[i], *((int *)pointers[i]));
    }

    return 0;
}
