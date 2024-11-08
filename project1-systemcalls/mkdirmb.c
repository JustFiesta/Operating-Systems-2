#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <libgen.h>
#include <errno.h>

void print_usage(const char *progname) {
    fprintf(stderr, "Usage: %s [-p] [-m mode] directory_path\n", progname);
}

// Funkcja do rekurencyjnego tworzenia katalogów (gdy -p jest użyte)
int create_parents(const char *path, mode_t mode) {
    char *dir_path = strdup(path); // Duplikujemy ścieżkę, aby jej nie zmodyfikować
    if (!dir_path) {
        perror("Failed to duplicate path");
        return -1;
    }

    for (char *p = dir_path + 1; *p; p++) {
        if (*p == '/') {
            *p = '\0';
            if (mkdir(dir_path, mode) != 0 && errno != EEXIST) {
                perror("Failed to create parent directory");
                free(dir_path);
                return -1;
            }
            *p = '/';
        }
    }
    if (mkdir(dir_path, mode) != 0 && errno != EEXIST) {
        perror("Failed to create directory");
        free(dir_path);
        return -1;
    }
    free(dir_path);
    return 0;
}

int main(int argc, char *argv[]) {
    int opt;
    int create_parents_flag = 0;
    mode_t mode = 0755; // Domyślne prawa dostępu, jeśli nie podano innych

    // Przetwarzanie argumentów z użyciem getopt
    while ((opt = getopt(argc, argv, "pm:")) != -1) {
        switch (opt) {
            case 'p':
                create_parents_flag = 1; // Ustawienie flagi `-p`
                break;
            case 'm':
                mode = strtol(optarg, NULL, 8); // Konwersja uprawnień do systemu ósemkowego
                if (mode == 0 && errno == EINVAL) {
                    fprintf(stderr, "Invalid mode: %s\n", optarg);
                    return EXIT_FAILURE;
                }
                break;
            default:
                print_usage(argv[0]);
                return EXIT_FAILURE;
        }
    }

    // Sprawdza, czy podano ścieżkę katalogu
    if (optind >= argc) {
        fprintf(stderr, "Expected directory path\n");
        print_usage(argv[0]);
        return EXIT_FAILURE;
    }

    char *dir_path = argv[optind];

    // Tworzenie katalogu z flagą -p lub bez
    if (create_parents_flag) {
        if (create_parents(dir_path, mode) != 0) {
            fprintf(stderr, "Failed to create directories for path: %s\n", dir_path);
            return EXIT_FAILURE;
        }
    } else {
        if (mkdir(dir_path, mode) != 0) {
            perror("Failed to create directory");
            return EXIT_FAILURE;
        }
    }

    printf("Directory created successfully: %s\n", dir_path);
    return EXIT_SUCCESS;
}
