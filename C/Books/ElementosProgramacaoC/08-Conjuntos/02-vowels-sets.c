// Compile command: gcc 02-vowels-sets.c sets.c -o 02-vowels-sets.out

#define ASCII_MAX       127
#define SET_MAX         ASCII_MAX

#include <stdio.h>
#include "sets.h"

Set vowels;

int isvowel(char c)
{
    return Setisin(c, vowels);
  //return strchr("AEIOUaeiou", c) != NULL;
}

int main()
{
    Setclr(vowels);
    Setadd(Setadd(Setadd(Setadd(Setadd
        (vowels, 'A'), 'E'), 'I'), 'O'), 'U');
    Setadd(Setadd(Setadd(Setadd(Setadd
        (vowels, 'a'), 'e'), 'i'), 'o'), 'u');

    unsigned char user_char;
    printf("Escreva um caracter: ");
    scanf("%c", &user_char);

    if (user_char > 127)
        printf("O caracter introduzido NÃO é ASCII\n");
    else if (isvowel(user_char))
        printf("O caracter '%c' é uma vogal\n", user_char);
    else
        printf("O caracter '%c' NÃO é uma vogal\n", user_char);

    return 0;
}