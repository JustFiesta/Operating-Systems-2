#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

#define BUFFER_SIZE 4096

void concatenate_files(char *output_filename, char **input_files, int input_count) {
    int output_fd = open(output_filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (output_fd == -1) {
        fprintf(stderr, "Nie mozna otworzyc pliku wyjsciowego %s: %s\n", 
                output_filename, strerror(errno));
        exit(1);
    }

    char buffer[BUFFER_SIZE];
    ssize_t bytes_read, bytes_written;

    for (int i = 0; i < input_count; i++) {
        int input_fd = open(input_files[i], O_RDONLY);
        if (input_fd == -1) {
            fprintf(stderr, "Nie mozna otworzyc pliku %s: %s\n", 
                    input_files[i], strerror(errno));
            continue;
        }

        while ((bytes_read = read(input_fd, buffer, BUFFER_SIZE)) > 0) {
            ssize_t total_written = 0;
            while (total_written < bytes_read) {
                bytes_written = write(output_fd, buffer + total_written, 
                                   bytes_read - total_written);
                if (bytes_written == -1) {
                    fprintf(stderr, "Blad podczas zapisu do pliku %s: %s\n", 
                            output_filename, strerror(errno));
                    close(input_fd);
                    close(output_fd);
                    exit(1);
                }
                total_written += bytes_written;
            }
        }

        if (bytes_read == -1) {
            fprintf(stderr, "Blad podczas odczytu pliku %s: %s\n", 
                    input_files[i], strerror(errno));
        }

        close(input_fd);
    }

    close(output_fd);
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Uzycie: %s plik1 [plik2 ... plikN] plik_wyjsciowy\n", argv[0]);
        return 1;
    }

    char *output_file = argv[argc-1];
    concatenate_files(output_file, &argv[1], argc-2);

    return 0;
}