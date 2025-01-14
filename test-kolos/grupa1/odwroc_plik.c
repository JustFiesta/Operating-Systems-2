#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {

    FILE *file = fopen("file.txt", "r");
    FILE *file2 = fopen("odwrocony_file.txt", "w");

    if (file == NULL || file2 == NULL) {
        printf("Nie udalo sie otworzyc pliku\n");
        return 1;
    }

    fseek(file, 0, SEEK_END);
    long pos = ftell(file);

    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    while (pos > 0) {
        fseek(file, --pos, SEEK_SET);
        if (fgetc(file) == '\n' || pos == 0) {
            if (pos != 0) {
                fseek(file, pos + 1, SEEK_SET);
            } else {
                fseek(file, pos, SEEK_SET);
            }
            getline(&line, &len, file);
            fprintf(file2, "%s", line);
            fseek(file, pos, SEEK_SET);
        }
    }

    free(line);
    fclose(file);
    fclose(file2);

    return 0;
}