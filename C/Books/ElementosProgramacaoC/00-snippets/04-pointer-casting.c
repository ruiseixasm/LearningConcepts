// Compiling command: gcc 04-pointer-casting.c -o 04-pointer-casting.out
#include <stdio.h>
#include <stdlib.h>     // For malloc()

// All pointers regardless of type are implicit casted whenever necessarly

void char_ptr_function(char *ptr)
{
    ptr[0] = 'A';                   // Compiles OK
}

void void_ptr_function(void *ptr)
{
    char_ptr_function(ptr);         // Compiles OK
    ptr[0] = 'A';                   // ERROR while compiling (error: invalid use of void expression)
}

int main()
{
    char text_p[] = "11111";
    char *text_mp = malloc(sizeof(text_p));     // Compiles OK (without (char *) casting) (implicit casting)
    void *text_vp = malloc(sizeof(text_p));     // Compiles OK
    
    void_ptr_function(text_p);      // Compiles OK
    void_ptr_function(text_mp);     // Compiles OK
    
    text_p[0] = 'A';                // Compiles OK
    text_mp[0] = 'A';               // Compiles OK
    text_vp[0] = 'A';               // ERROR while compiling (error: invalid use of void expression)
    
    return 0;
}
