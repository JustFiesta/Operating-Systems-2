#include <stdio.h>
#include <ctype.h>
#include <string.h>

char *trim(char *s) {

    while (isspace(s)) s++;

    char *end = s + strlen(s) + 1;

    while (isspace(s)) s++;

    while (end > s && isspace((unsigned char)*end))
    {
        end--;
    }

    *(end + 1) = '\0';

    return s;
}

int main() {

    char *ala = "    Ala ma kota.";
    char *cat = "Kot ma ale     ";
    char *both = "   oboje mają siebie   ";

    printf("%s", trim(ala));

    return 0;
}