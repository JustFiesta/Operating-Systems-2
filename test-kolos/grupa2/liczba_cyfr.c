#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

    int liczba = 0;
    int user_input = 0;
    
    // Wczytanie liczby jako argument main
    if (argc > 1) {
        user_input = atoi(argv[1]);
    } else {
        printf("Brak argumentu liczby.\n");
        return 1;
    }

    while (user_input != 0) {
        user_input /= 10;
        liczba++;
    }

    printf("Liczba cyfr: %d\n", liczba);

    return 0;
}