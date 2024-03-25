#include <stdio.h>
#include "lib/lowlevelmath.h"

int main(int argc, char **argv) {
    printf("Hello World!\n");
    int x = LowLevelAdd(1, 2);
    printf("%d\n", x);

    return 0;
}