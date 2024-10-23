#include <stdio.h>

void printChars(FILE *fp) {
    
    char ch;

    while ((ch = fgetc(fp)) != EOF)
    {
        printf("%c", ch);
    }
    
}

int main() {
    FILE *fp = fopen("./file.txt", "r");
    
    if (fp == NULL) {
        printf("Nie udalo się otworzyc pliku.\n");
        return 1;
    }
    printChars(fp);
    fclose(fp);

    return 0;
}