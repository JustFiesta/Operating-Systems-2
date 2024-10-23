#include <stdio.h>

void printChar(FILE *fp) {
    int c;
    while ((c = fgetc(fp)) != EOF) {
        if (c == '\n') {
            printf("'\\n' ");
        } else {
            printf("'%c' ", c);
        }
    }
    printf("\n");
}

int main() {
    FILE *fp = fopen("./file.txt", "r");
    
    if (fp == NULL) {
        printf("Nie udalo się otworzyc pliku.\n");
        return 1;
    }
    printChar(fp);
    fclose(fp);

    return 0;
}