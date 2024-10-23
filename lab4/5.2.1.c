#include <stdio.h>
#include <ctype.h>

int countWords1(FILE *fp) {
    int inWord = 0;   // Flaga, czy jesteśmy wewnątrz słowa
    int counter = 0;
    char ch;

    while ((ch = fgetc(fp)) != EOF) {
        if (isspace(ch)) {
            if (inWord) {
                counter++;  // Koniec słowa
                inWord = 0;
            }
        } else {
            inWord = 1;  // Jesteśmy w środku słowa
        }
    }

    // Jeśli plik kończy się słowem, trzeba dodać to słowo
    if (inWord) {
        counter++;
    }

    return counter;
}

int main() {
    FILE *fp = fopen("./file.txt", "r");

    if (fp == NULL) {
        printf("Nie udalo się otworzyc pliku.\n");
        return 1;
    }

    int wordCount = countWords1(fp);
    printf("Liczba słów: %d\n", wordCount);
    
    fclose(fp);

    return 0;
}
