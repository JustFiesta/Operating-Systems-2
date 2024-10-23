#include <stdio.h>

void printLinesHex(FILE *fp) {
	int ch;
    while ((ch = fgetc(fp)) != EOF) {
    	if(ch == '\n')
    	{
    		printf("\n");
		}
		else
		{
			printf("%02X ", ch);
		}
    }
}

int main() {
    FILE *fp = fopen("./file.txt", "r");
    
    if (fp == NULL) {
        printf("Nie udalo się otworzyc pliku.\n");
        return 1;
    }
    printLinesHex(fp);
    fclose(fp);

    return 0;
}