#include <stdio.h>
#include <math.h>
#include <stdlib.h>

// obl liczbę cyfr liczby n
int liczba_cyfr(int n) {
    if (n == 0) {
        return 1;
    }
    // dla dodatnich i ujemnych używamy wartości bezwzględnej
    return (int)log10(abs(n)) + 1;
}

int main() {
    FILE *plik; 
    int n;
    
    plik = fopen("liczba.txt", "r");
    if (plik == NULL) {
        printf("Nie udalo sie otworzyc pliku.\n");
        return 1;
    }
    
    // Wczytujemy liczbę z pliku
    fscanf(plik, "%d", &n);
    
    // Zamykamy plik po odczycie
    fclose(plik);
    
    // Obliczamy liczbę cyfr
    int wynik = liczba_cyfr(n);
    
    // Otwieramy plik do zapisu wyniku
    plik = fopen("wynik.txt", "w");
    if (plik == NULL) {
        printf("Nie udalo sie otworzyc pliku do zapisu.\n");
        return 1;
    }
    
    // Zapisujemy wynik do pliku
    fprintf(plik, "Liczba cyfr liczby %d wynosi: %d\n", n, wynik);
    
    fclose(plik);
    
    printf("Liczba cyfr liczby %d wynosi: %d\n", n, wynik);
    
    return 0;
}
