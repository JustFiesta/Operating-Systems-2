#include<stdio.h>
#include <stdlib.h>
#include <string.h>

void printWords(FILE *fp) {
    int maxLineLenght = 128;

    char *lineBuffer = (char *)malloc(sizeof(char) * maxLineLenght);

    while (fgets(lineBuffer, maxLineLenght, fp) != NULL) {
        // Użyj strtok do rozdzielenia linii na słowa
        char *word = strtok(lineBuffer, " \t\n");  // Dzielimy na spacje, tabulatory i nową linię
        while (word != NULL) {
            printf("%s\n", word);  // Wypisanie słowa
            word = strtok(NULL, " \t\n");  // Przejście do następnego słowa
        }
    }

    free(lineBuffer);
}


int main() {
    FILE *fp = fopen("./file.txt", "r");
    
    if (fp == NULL) {
        printf("Nie udalo się otworzyc pliku.\n");
        return 1;
    }
    printWords(fp);
    fclose(fp);

    return 0;
}