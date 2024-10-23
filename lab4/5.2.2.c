#include <stdio.h>
#include <ctype.h>

int countWords2(FILE *fp) {
    int ch = fgetc(fp);

    if (ch == EOF) {
        return 0;
    }

    if (!isspace(ch)) {
        while ((ch = fgetc(fp)) != EOF && !isspace(ch)) {
        }
        return 1 + countWords2(fp);
    } else {
        return countWords2(fp);
    }
}

int main() {
    FILE *fp = fopen("./file.txt", "r");

    if (fp == NULL) {
        printf("Nie udalo się otworzyc pliku.\n");
        return 1;
    }

    int wordCount = countWords2(fp);
    printf("Liczba słów: %d\n", wordCount);
    
    fclose(fp);

    return 0;
}
