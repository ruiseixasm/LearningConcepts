/* Pontos numa corrida de F1; terceira \nversao */

#include <stdio.h>
#include <math.h>   // needed for pow()
// Needs to be compiled with: gcc 04-functions.c -o 04-functions.out -lm

int points_f1(int place);   // Declaration
int points_f2(int place);   // Declaration
int points_f3(int place);   // Declaration
int points_f4(int place);   // Declaration
int points_f5(int place);   // Declaration
int points_f6(int place);   // Declaration
int points_f7(int place);   // Declaration
int points_f8(int place);   // Declaration
int points_f9(int place);   // Declaration

int ntrl(int n);                    // Número natural
int isbtwn(int n, int lb, int ub);  // is between

int main() {

    int place;
    int pts;

    printf("Qual e´ o lugar? ");
    scanf("%d", &place);

    printf("\nVersao da função f1\n");
    pts = points_f1(place);

    if (pts > 1)
        printf ("Ganhou %d pontos.\n", pts);
    else if (pts == 1)
        printf ("Ganhou 1 ponto.\n");
    else
        printf ("Não ganhou. pontos.\n");

    printf("\nVersao da função f2\n");
    pts = points_f2(place);

    if (pts > 1)
        printf ("Ganhou %d pontos.\n", pts);
    else if (pts == 1)
        printf ("Ganhou 1 ponto.\n");
    else
        printf ("Não ganhou. pontos.\n");

    printf("\nVersao da função f3\n");
    pts = points_f3(place);

    if (pts > 1)
        printf ("Ganhou %d pontos.\n", pts);
    else if (pts == 1)
        printf ("Ganhou 1 ponto.\n");
    else
        printf ("Não ganhou. pontos.\n");

    printf("\nVersao da função f4\n");
    pts = points_f4(place);

    if (pts > 1)
        printf ("Ganhou %d pontos.\n", pts);
    else if (pts == 1)
        printf ("Ganhou 1 ponto.\n");
    else
        printf ("Não ganhou. pontos.\n");

    printf("\nVersao da função f5\n");
    pts = points_f5(place);

    if (pts > 1)
        printf ("Ganhou %d pontos.\n", pts);
    else if (pts == 1)
        printf ("Ganhou 1 ponto.\n");
    else
        printf ("Não ganhou. pontos.\n");

    printf("\nVersao da função f6\n");
    pts = points_f6(place);

    if (pts > 1)
        printf ("Ganhou %d pontos.\n", pts);
    else if (pts == 1)
        printf ("Ganhou 1 ponto.\n");
    else
        printf ("Não ganhou. pontos.\n");

    printf("\nVersao da função f7\n");
    pts = points_f7(place);

    if (pts > 1)
        printf ("Ganhou %d pontos.\n", pts);
    else if (pts == 1)
        printf ("Ganhou 1 ponto.\n");
    else
        printf ("Não ganhou. pontos.\n");

    printf("\nVersao da função f8\n");
    pts = points_f8(place);

    if (pts > 1)
        printf ("Ganhou %d pontos.\n", pts);
    else if (pts == 1)
        printf ("Ganhou 1 ponto.\n");
    else
        printf ("Não ganhou. pontos.\n");

    printf("\nVersao da função f9\n");
    pts = points_f9(place);

    if (pts > 1)
        printf ("Ganhou %d pontos.\n", pts);
    else if (pts == 1)
        printf ("Ganhou 1 ponto.\n");
    else
        printf ("Não ganhou. pontos.\n");

    return 0;
}

int points_f1(int place) {  // Definition

    switch (place) {
    case 1:
        return 10;
    case 2:
        return 6;
    case 3:
        return 4;
    case 4:
        return 3;
    case 5:
        return 2;
    case 6:
        return 1;
    default:
        return 0;
    }
}

int points_f2(int place) {  // Definition

    switch (place) {
    case 1: case 2:
        return 14 - 4 * place;
    case 3: case 4: case 5: case 6:
        return 7 - place;
    default:
        return 0;
    }
}

int points_f3(int place) {  // Definition

    if (place <= 2)
        return 14 - 4 * place;
    else if (place <= 6)
        return 7 - place;
    else
        return 0;
}

int points_f4(int place) {  // Definition

    if (place <= 2)
        return 14 - 4 * place;
    else
        return ntrl(7 - place);
}

int points_f5(int place) {  // Definition

    return place <= 2 ? 14 - 4 * place : ntrl(7 - place);
}

int points_f6(int place) {  // Definition

    return (place <= 2) * (14 - 4 * place) +
           (3 <= place) * (place <= 6) * (7 - place);
}

int points_f7(int place) {  // Definition

    return (1 <= place && place <= 2) * (14 - 4 * place) +
           (3 <= place && place <= 6) * (7 - place);
}

int points_f8(int place) {  // Definition

    return isbtwn(place, 1, 2) * (14 - 4 * place) +
           isbtwn(place, 3, 6) * (7 - place);
}

int points_f9(int place) {  // Definition
    int points = (pow(place, 5) - 15*pow(place, 4) + 65*pow(place, 3) 
                    + 15*pow(place, 2) - 786*place + 1920)/120;
    printf("Polynomial result: %d\n", points);
    return points;
}


int ntrl(int n) {
    return n > 0 ? n : 0;       // in C booleans are integers, where 0 is false and 1 is true
}

int isbtwn(int n, int lb, int ub) {
    return lb <= n && n <= ub;
}
