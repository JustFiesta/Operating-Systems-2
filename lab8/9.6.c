#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <errno.h>

#define BUFFER_SIZE 4096

int is_ascii_buffer(unsigned char *buffer, size_t length) {
    for (size_t i = 0; i < length; i++) {
        if (!isascii(buffer[i])) {
            return 0;
        }
    }
    return 1;
}

int is_text_file(const char *filename) {
    FILE *file;
    unsigned char buffer[BUFFER_SIZE];
    size_t bytes_read;
    
    file = fopen(filename, "rb");
    if (file == NULL) {
        fprintf(stderr, "Błąd podczas otwierania pliku '%s': %s\n", 
                filename, strerror(errno));
        return -1;
    }
    
    while ((bytes_read = fread(buffer, 1, BUFFER_SIZE, file)) > 0) {
        if (!is_ascii_buffer(buffer, bytes_read)) {
            fclose(file);
            return 0;
        }
    }
    
    if (ferror(file)) {
        fprintf(stderr, "Błąd podczas czytania pliku '%s': %s\n", 
                filename, strerror(errno));
        fclose(file);
        return -1;
    }
    
    fclose(file);
    return 1;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Użycie: %s <nazwa_pliku>\n", argv[0]);
        return EXIT_FAILURE;
    }
    
    int result = is_text_file(argv[1]);
    
    switch (result) {
        case 1:
            printf("Plik '%s' jest plikiem tekstowym\n", argv[1]);
            return EXIT_SUCCESS;
        case 0:
            printf("Plik '%s' nie jest plikiem tekstowym\n", argv[1]);
            return EXIT_FAILURE;
        default:
            return EXIT_FAILURE;
    }
}