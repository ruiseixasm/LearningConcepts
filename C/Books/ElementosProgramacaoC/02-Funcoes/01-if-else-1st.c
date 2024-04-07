/* Pontos numa corrida de F1; primeira versão */

#include <stdio.h>

int main() {
    
    int place;

    printf ("Qual é o lugar? ");
    scanf ("%d", &place);

    if (place == 1)
        printf ("Ganhou 10 pontos.\n");
    else if (place == 2)
        printf ("Ganhou 6 pontos.\n");
    else if (place == 3)
        printf ("Ganhou 4 pontos.\n");
    else if (place == 4)
        printf ("Ganhou 3 pontos.\n");
    else if (place == 5)
        printf ("Ganhou 2 pontos.\n");
    else if (place == 6)
        printf ("Ganhou 1 ponto.\n");
    else
        printf ("Não ganhou pontos.\n");

    return 0;
}