#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <sys/stat.h>
#include <linux/limits.h>

// Get mkdir syscall number from unistd.h header
#define MKDIR_SYSCALL_NUM  __NR_mkdir

// Help function
void print_usage(const char *progname) {
    fprintf(stderr, "Usage: %s [-p] directory_path\n", progname);
}

// Mkdir syscall function
int syscall_mkdir(const char *path, mode_t mode) {
    return syscall(MKDIR_SYSCALL_NUM, path, mode);
}

// Recursievelly create parent 
int create_parents(const char *path, mode_t mode) {
    char dir_path[PATH_MAX];
    strncpy(dir_path, path, PATH_MAX);

    for (char *p = dir_path + 1; *p; p++) {
        if (*p == '/') {
            *p = '\0';
            if (syscall_mkdir(dir_path, 0777) != 0 && errno != EEXIST) {
                perror("Failed to create parent directory");
                return -1;
            }
            *p = '/';
        }
    }
    if (syscall_mkdir(dir_path, mode) != 0 && errno != EEXIST) {
        perror("Failed to create directory");
        return -1;
    }
    return 0;
}

int main(int argc, char *argv[]) {
    int opt;
    int create_parents_flag = 0;

    // Default access mode
    mode_t mode = 0755;

    // getopt user interface for getting arguments
    while ((opt = getopt(argc, argv, "ph")) != -1) {
        switch (opt) {
            case 'p':
                create_parents_flag = 1; // set flag for -p
                break;
            case 'h':
                print_usage(argv[0]);
                return EXIT_SUCCESS;
            default:
                print_usage(argv[0]);
                return EXIT_FAILURE;
        }
    }

    // Check if path was provided
    if (optind >= argc) {
        fprintf(stderr, "Error: No directory path provided.\n");
        print_usage(argv[0]);
        return EXIT_FAILURE;
    }

    // Get path to variable
    const char *dir_path = argv[optind];

    // Try to create folder/folders
    int result;
    if (create_parents_flag) {
        result = create_parents(dir_path, mode);
    } else {
        result = syscall_mkdir(dir_path, mode);
    }

    if (result != 0) {
        fprintf(stderr, "Error creating directory: %s\n", strerror(errno));
        return EXIT_FAILURE;
    }

    printf("Directory created successfully.\n");
    return EXIT_SUCCESS;
}
