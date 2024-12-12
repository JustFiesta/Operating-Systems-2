#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 4096

typedef struct {
    long total_chars;
    long current_line;
    long char_in_line;
} FilePosition;

void compare_files(const char *file1_name, const char *file2_name) {
    FILE *file1 = fopen(file1_name, "r");
    FILE *file2 = fopen(file2_name, "r");
    
    if (!file1 || !file2) {
        if (!file1) fprintf(stderr, "Nie mozna otworzyc pliku: %s\n", file1_name);
        if (!file2) fprintf(stderr, "Nie mozna otworzyc pliku: %s\n", file2_name);
        if (file1) fclose(file1);
        if (file2) fclose(file2);
        exit(1);
    }

    FilePosition pos = {0, 1, 0};
    int char1, char2;
    int difference_found = 0;
    
    while (1) {
        char1 = fgetc(file1);
        char2 = fgetc(file2);
        
        if (char1 == EOF && char2 == EOF) {
            printf("Pliki sa identyczne\n");
            break;
        }
        
        if (char1 != char2) {
            if (char1 == EOF) {
                long remaining = 0;
                while (fgetc(file2) != EOF) remaining++;
                printf("Plik %s zawiera %ld znakow wiecej niz zawartosc pliku %s\n",
                       file2_name, remaining + 1, file1_name);
                difference_found = 1;
                break;
            }
            if (char2 == EOF) {
                long remaining = 0;
                while (fgetc(file1) != EOF) remaining++;
                printf("Plik %s zawiera %ld znakow wiecej niz zawartosc pliku %s\n",
                       file1_name, remaining + 1, file2_name);
                difference_found = 1;
                break;
            }
            
            printf("Pliki roznia sie od znaku nr %ld w linii %ld\n",
                   pos.char_in_line + 1, pos.current_line);
            difference_found = 1;
            break;
        }
        
        pos.total_chars++;
        pos.char_in_line++;
        
        if (char1 == '\n') {
            pos.current_line++;
            pos.char_in_line = 0;
        }
    }
    
    fclose(file1);
    fclose(file2);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Uzycie: %s plik1 plik2\n", argv[0]);
        return 1;
    }
    
    compare_files(argv[1], argv[2]);
    return 0;
}