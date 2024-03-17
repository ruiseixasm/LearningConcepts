#include<stdio.h>
#include<string.h>

int stringPointerLength (const char *stringPointer) {
    return strlen(stringPointer);
}

int main () {

    char C[20];
    C[0] = 'J';
    C[1] = 'O';
    C[2] = 'H';
    C[3] = 'N';
    C[4] = '\0';
    int len = strlen(C);
    printf("Length = %d\n", len);
    len = stringPointerLength(C);
    printf("Function Pointer Length = %d\n", len);


    // Testing String Constant
    char A[20] = "Hello";
    char MS[] = "Hello"; // MUTABLE String
    char *IS = "Hello"; // IMMUTABLE String !!

    printf("A = %s\n", A);
    printf("MS = %s\n", MS);
    printf("IS = %s\n", IS);

    A[0] = 'L';
    MS[0] = 'M';
    //IS[0] = 'I'; // Crashes!
    
    printf("A = %s\n", A);
    printf("B = %s\n", MS);
    printf("SizeOff = %ld\n", sizeof(IS));

}
