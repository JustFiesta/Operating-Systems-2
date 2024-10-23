#include <stdio.h>
#include <ctype.h>

int countWords1(FILE *fp){
    int counter = -1; // bo liczy o słowo za duzo czasami

    char ch;

    while ((ch = fgetc(fp)) != EOF)
    {
        if (!isspace(ch))
        {
            continue;
        }
                
        counter++;
    }
    printf("Liczba słów: %d", counter);
}

int main() {
    FILE *fp = fopen("./file.txt", "r");
    
    if (fp == NULL) {
        printf("Nie udalo się otworzyc pliku.\n");
        return 1;
    }
    countWords1(fp);
    fclose(fp);

    return 0;
}
