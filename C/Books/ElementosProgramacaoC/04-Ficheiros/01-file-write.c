// Compile command: gcc 01-file-write.c -o 01-file-write.out

#include <stdio.h>
#include <string.h>

int main() {

    FILE *f_cars;
    int n_cars;
    int drivers;
    int i_cars;
    char name [16];

    printf("Quantos carros à partida? ");
    scanf("%d%*c", &n_cars); // "%*c" tells that the second parameter (char) is intended to be discarded
    f_cars = fopen("CARS_TODAY.txt", "w");

    drivers = 0;
    i_cars = 0;
    while (drivers < n_cars) {
        printf("Piloto do carro nº. %d: ", ++i_cars);
        if (fgets(name, sizeof(name), stdin) != NULL) {
            fprintf(f_cars, "%02d %s", i_cars, name);
            ++drivers;
        }
    }

    fclose(f_cars);

    return 0;
}