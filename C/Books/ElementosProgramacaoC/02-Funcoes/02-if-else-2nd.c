/* Pontos numa corrida de F1; segunda versão */
#include <stdio.h>

int main() {
    
    int place;
    int pts;

    printf ("Qual é o lugar? ");
    scanf ("%d", &place);

    if (place == 1)
        pts = 10;
    else if (place == 2)
        pts = 6;
    else if (place == 3)
        pts = 4;
    else if (place == 4)
        pts = 3;
    else if (place == 5)
        pts = 2;
    else if (place == 6)
        pts = 1;
    else
        pts = 0;

    if (pts > 1)
        printf ("Ganhou %d pontos.\n", pts);
    else if (pts == 1)
        printf ("Ganhou 1 ponto.\n");
    else
        printf ("Não ganhou. pontos.\n");

    return 0;
}