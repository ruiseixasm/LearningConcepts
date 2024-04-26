// Compiling command: gcc 01-format-specifiers.c -o 01-format-specifiers.out
#include <stdio.h>

int main()
{
    char ones[] = "11111";
    char twos[] = "22222";
    
    printf("%s%.*s", ones, 50, twos);
    printf("|\n");
    
    return 0;
}


