/* Pontos numa corrida de F1; terceira versão */

#include <stdio.h>

int main() {

    int place;
    int pts;

    printf("Qual é o lugar? ");
    scanf("%d", &place);

    switch (place) {
    case 1:
        pts = 10;
        break;
    case 2:
        pts = 6;
        break;
    case 3:
        pts = 4;
        break;
    case 4:
        pts = 3;
        break;
    case 5:
        pts = 2;
        break;
    case 6:
        pts = 1;
        break;
    default:
        pts = 0;
        break;
    }

    if (pts > 1)
        printf ("Ganhou %d pontos.\n", pts);
    else if (pts == 1)
        printf ("Ganhou 1 ponto.\n");
    else
        printf ("Não ganhou. pontos.\n");

    return 0;
}