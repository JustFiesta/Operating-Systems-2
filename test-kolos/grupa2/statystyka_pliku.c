#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]){
    const char * path_name = argv[1];
    FILE *file = fopen(path_name, "r");
    
    if (file == NULL){
        printf("Nie udalo sie otworzyc pliku\n");
        return 1;
    }

    int chars = 0;
    int words = 0;
    int lines = 1;

    // jak przejść przez treść pliku?
    // 1. czytanie znak po znaku
    // 2. czytanie linia po linii
    // 3. czytanie słowo po słowie

    // implementacja
    char c;
    while ((c = fgetc(file)) != EOF)
    {
        chars++;
        if (c == ' ' || c == '\n' || c == '\t'){
            words++;
        }
        if (c == '\n'){
            lines++;
        }
    }

    fclose(file);

    printf("Liczba znakow: %d\n", chars);
    printf("Liczba slow: %d\n", words);
    printf("Liczba linii: %d\n", lines);
}