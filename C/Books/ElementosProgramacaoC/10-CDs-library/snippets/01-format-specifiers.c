// Compiling command: gcc 01-format-specifiers.c -o 01-format-specifiers.out
#include <stdio.h>

int main()
{
    char ones[] = "11111";
    char twos[] = "22222";
    
    // 3 sets the maximum numbers of chars printed of twos (with '.')
    printf("%s%.*s", ones, 3, twos);
    printf("|\n");
    
    // 30 sets the minimum numbers of space occupied by twos (without '.')
    printf("%s%*s", ones, 30, twos);
    printf("|\n");
    
    return 0;
}
