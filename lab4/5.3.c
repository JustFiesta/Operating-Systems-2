#include<stdio.h>
#include <stdlib.h>
#include <ctype.h>

void printWords(FILE *fp) {
    int maxLineLenght = 128;

    char *lineBuffer = (char *)malloc(sizeof(char) * maxLineLenght);
    char ch;
    int i = 0;

    while ((ch = fgetc(fp)) != EOF)
    {

        // drukuj słowo jeżeli wykryjesz spacje
        if (isspace(ch) && i > 0)
        {
            lineBuffer[i] = '\0';
            printf("%s\n", lineBuffer);
            i = 0;
        }
        
        // dodawaj do bufora kolejne znaki
        lineBuffer[i] = ch;
        i++;
    }

    // print ostatnie słowo
    if (i > 0)
    {
        lineBuffer[i] = '\0';
        printf("%s\n", lineBuffer);
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