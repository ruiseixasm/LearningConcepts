#include <stdio.h>

// In C, all pointer types (char*, int*, float*, etc.) have the same size because they represent memory addresses,
//     and memory addresses typically have a fixed size determined by the architecture of the system.
// "In C, all pointers have the same size, while the size of values depends on their data type."

void BuildPointers(void **v, const void *p, size_t n, size_t s)
{
    // *p   - Array of pointers to values, in this case, long long int values (8 bytes)
    // **v  - Array of pointers to pointers, in this case, (void) addresses (always the same, 4 or 8 bytes)
    printf("n: %d, s: %d bytes, (long long int *)p: %p, (char *)p: %p, p: %p\n", n, s, (long long int *)p, (char *)p, p);
    // Pointers are like a needle on a record groove, they need to be place on the right groove,
    //     i += s   - 8 bytes offset for i means 8 grooves appart, because i is a pointer to a long long int value
    //     *v++     - always 4 bytes offset for *v because it's a pointer to an address and not a value
    for (char *i = (char *)p; n; n--, i += s, *v++) // Size s, bytes, is in multiple of chars, that have 1 byte
    {
        *v = (void *)i;   // All pointers have integer size, Ex. 4 bytes, equally sized, even void addresses!
        printf("Address i: %p, Address *v: %p, Value i: %d, Value *v: %d\n",
                        i, *v, *i, *((long long int *)*v));
    }
}

int main() {
    // Define an array of integers
    long long int array[] = {10, 20, 30, 40, 50};

    // Define an array of void pointers
    void *pointers[5];

    // Use the BuildPointers function to build pointers to the elements of the array
    BuildPointers(pointers, array, 5, sizeof(long long int));

    // Print the addresses and values pointed to by the pointers
    printf("\nAddresses and Values:\n");
    for (int i = 0; i < 5; i++) {
        printf("Pointer %d: Address=%p, Value=%d\n", i, pointers[i], *((long long int *)pointers[i]));
    }

    return 0;
}
