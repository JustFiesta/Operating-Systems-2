#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1024

void reverse_line(char *line) {
    int length = strlen(line);
    int i;
    char temp;

    for (i = 0; i < length / 2; i++) {
        temp = line[i];
        line[i] = line[length - i - 1];
        line[length - i - 1] = temp;
    }
}
int main(int argc, char *argv[]) {
    FILE *input_file, *output_file;
    char line[MAX_LINE_LENGTH];

    if (argc != 2) {
        fprintf(stderr, "Uzycie: %s <nazwa_pliku>\n", argv[0]);
        exit(1);
    }

    input_file = fopen(argv[1], "r");
    if (input_file == NULL) {
        perror("Blad otwarcia pliku do odczytu");
        exit(1);
    }

    output_file = fopen("output.txt", "w");
    if (output_file == NULL) {
        perror("Blad otwarcia pliku do zapisu");
        exit(1);
    }

    while (fgets(line, sizeof(line), input_file) != NULL) {
        line[strcspn(line, "\n")] = '\0';

        reverse_line(line);

        fputs(line, output_file);
        fputs("\n", output_file);
    }

    fclose(input_file);
    fclose(output_file);

    printf("Plik został odwrocony. Zapis do 'output.txt'.\n");

    return 0;
}
