#include <stdio.h>
#include <stdlib.h>

void printLines(FILE *fp) {
    int maxLineLenght = 128;
    char *lineBuffer = (char *)malloc(sizeof(char) * maxLineLenght);


    while (fgets(lineBuffer, maxLineLenght, fp))
    {
        printf("%s", lineBuffer);
    }
}

int main() {
    FILE *fp = fopen("./file.txt", "r");
    
    if (fp == NULL) {
        printf("Nie udalo się otworzyc pliku.\n");
        return 1;
    }
    printLines(fp);
    fclose(fp);

    return 0;
}