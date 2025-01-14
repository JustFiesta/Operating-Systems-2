#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Za malo argumentow\n");
        return 1;
    }

    const char * path_name1 = argv[1];
    const char * path_name2 = argv[2];
    FILE *file = fopen(path_name1, "r");

    // skopiuj 10 ostatnich linii do drugiego pliku
    FILE *file2 = fopen(path_name2, "w");

    if (file == NULL || file2 == NULL){
        printf("Nie udalo sie otworzyc pliku\n");
        return 1;
    }

    fseek(file, 0, SEEK_END);
    long pos = ftell(file);

    int lines = 0;

    while (pos) {
        fseek(file, --pos, SEEK_SET);
        if (fgetc(file) == '\n') {
            if (++lines == 10) break;
        }
    }

    // Move to the start of the file if less than 10 lines
    if (pos == 0) {
        fseek(file, 0, SEEK_SET);
    }

    char c;
    while ((c = fgetc(file)) != EOF) {
        fputc(c, file2);
    }

    fclose(file);
    fclose(file2);

    return 0;
}