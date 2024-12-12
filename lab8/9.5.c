#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1024
#define MAX_WORD_LENGTH 100
#define N 10

void copy_last_n_characters(const char *input_filename, FILE *output_file, int n) {
    FILE *input_file = fopen(input_filename, "r");
    if (!input_file) return;

    fseek(input_file, 0, SEEK_END);
    long file_size = ftell(input_file);
    
    long start_pos = (file_size < n) ? 0 : file_size - n;
    fseek(input_file, start_pos, SEEK_SET);

    int c;
    fprintf(output_file, "Ostatnie %d znakow:\n", n);
    while ((c = fgetc(input_file)) != EOF) {
        fputc(c, output_file);
    }
    fputc('\n', output_file);
    fclose(input_file);
}

void copy_last_n_words(const char *input_filename, FILE *output_file, int n) {
    FILE *input_file = fopen(input_filename, "r");
    if (!input_file) return;

    char *words[N];
    for (int i = 0; i < n; i++) {
        words[i] = malloc(MAX_WORD_LENGTH);
        words[i][0] = '\0';
    }

    char word[MAX_WORD_LENGTH];
    int word_idx = 0;
    int c;

    fprintf(output_file, "Ostatnie %d slow:\n", n);
    while ((c = fgetc(input_file)) != EOF) {
        if (c == ' ' || c == '\n' || c == '\t') {
            if (word_idx > 0) {
                word[word_idx] = '\0';
                for (int i = 0; i < n - 1; i++) {
                    strcpy(words[i], words[i + 1]);
                }
                strcpy(words[n - 1], word);
                word_idx = 0;
            }
        } else {
            word[word_idx++] = c;
            if (word_idx >= MAX_WORD_LENGTH - 1) {
                word_idx = 0;
            }
        }
    }

    if (word_idx > 0) {
        word[word_idx] = '\0';
        for (int i = 0; i < n - 1; i++) {
            strcpy(words[i], words[i + 1]);
        }
        strcpy(words[n - 1], word);
    }

    for (int i = 0; i < n; i++) {
        if (words[i][0] != '\0') {
            fprintf(output_file, "%s ", words[i]);
        }
    }
    fprintf(output_file, "\n\n");

    for (int i = 0; i < n; i++) {
        free(words[i]);
    }
    fclose(input_file);
}

void copy_last_n_lines(const char *input_filename, FILE *output_file, int n) {
    FILE *input_file = fopen(input_filename, "r");
    if (!input_file) return;

    char *lines[N];
    for (int i = 0; i < n; i++) {
        lines[i] = malloc(MAX_LINE_LENGTH);
        lines[i][0] = '\0';
    }

    char line[MAX_LINE_LENGTH];
    int current = 0;
    
    fprintf(output_file, "Ostatnie %d linii:\n", n);
    while (fgets(line, MAX_LINE_LENGTH, input_file) != NULL) {
        strcpy(lines[current], line);
        current = (current + 1) % n;
    }

    for (int i = 0; i < n; i++) {
        int idx = (current + i) % n;
        if (lines[idx][0] != '\0') {
            fputs(lines[idx], output_file);
        }
    }

    for (int i = 0; i < n; i++) {
        free(lines[i]);
    }
    fclose(input_file);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Uzycie: %s <plik_wejsciowy> <plik_wyjsciowy>\n", argv[0]);
        return 1;
    }

    FILE *output_file = fopen(argv[2], "w");
    if (!output_file) {
        perror("Blad otwarcia pliku wyjsciowego");
        return 1;
    }

    copy_last_n_characters(argv[1], output_file, N);
    copy_last_n_words(argv[1], output_file, N);
    copy_last_n_lines(argv[1], output_file, N);

    fclose(output_file);
    return 0;
}