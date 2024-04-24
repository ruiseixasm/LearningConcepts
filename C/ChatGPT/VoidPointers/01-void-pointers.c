#include <stdio.h>

void printValue(void *ptr, char type) {
    switch(type) {
        case 'i':
            printf("Integer Value: %d\n", *((int*)ptr));
            break;
        case 'f':
            printf("Float Value: %f\n", *((float*)ptr));
            break;
        case 'c':
            printf("Character Value: %c\n", *((char*)ptr));
            break;
        default:
            printf("Unknown Type\n");
    }
}

int main() {
    int intValue = 42;
    float floatValue = 3.14f;
    char charValue = 'A';

    // Void pointer example
    void *voidPtr;

    voidPtr = &intValue;
    printValue(voidPtr, 'i');

    voidPtr = &floatValue;
    printValue(voidPtr, 'f');

    voidPtr = &charValue;
    printValue(voidPtr, 'c');

    // Array of void pointers example
    void *voidPtrArray[] = { &intValue, &floatValue, &charValue };

    for (int i = 0; i < 3; i++) {
        printf("Value at index %d:\n", i);
        printValue(voidPtrArray[i], ' ');
    }

    return 0;
}
