#include <stdio.h>
#include <ctype.h>
#include <string.h>

char *trim(char *s) {

    // przejdz przez poczatek, przesuwając wskaźnik na pierwszy właściwy char
    while (isspace((unsigned char)*s)) s++;

    // znajdz koniec stringa
    char *end = s + strlen(s) + 1;

    // przejdź od końca w lewo przesuwając wskaźnik stringa
    while (end > s && isspace((unsigned char)*end)) {
        end--;
    }

    // dodaj EOF
    *(end + 1) = '\0';

    return s;
}

int main() {

    char ala[] = "    Ala ma kota. ";
    char cat[] = "Kot ma ale     ";
    char both[] = "   oboje mają siebie   ";

    printf("%s", trim(both));

    return 0;
}