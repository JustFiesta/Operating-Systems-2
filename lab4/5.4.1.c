#include <stdio.h>

void printHex(FILE *fp) {
    char ch;

    while ((ch = fgetc(fp)) != EOF)
    {
        printf("%02X ", ch);
    }
}

int main() {
    FILE *fp = fopen("./file.txt", "r");
    
    if (fp == NULL) {
        printf("Nie udalo się otworzyc pliku.\n");
        return 1;
    }
    printHex(fp);
    fclose(fp);

    return 0;
}

