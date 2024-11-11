#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <sys/stat.h>
#include <linux/limits.h>

// get mkdir syscall number from unistd.h header
#define MKDIR_SYSCALL_NUM  __NR_mkdir

// print help/usage function
void print_usage(const char *progname) {
    fprintf(stderr, "Usage: %s [-p] directory_path\n", progname); // print error and usage
}

// mkdir syscall function
int syscall_mkdir(const char *path, mode_t mode) {
    return syscall(MKDIR_SYSCALL_NUM, path, mode); // call mkdir by its number on given path with given mode
}

// recursively create parent directories
int create_parents(const char *path, mode_t mode) {
    char dir_path[PATH_MAX]; // dir path buffer
    strncpy(dir_path, path, PATH_MAX); // copy path to buffer, to ensure that input wont be modified

    // set umask to ensure same modes for subdirs
    mode_t old_umask = umask(0);

    // split folders by '/' in buffer
    for (char *p = dir_path + 1; *p; p++) {
        if (*p == '/') {
            *p = '\0';
            // create subdir by calling mkdir syscall
            if (syscall_mkdir(dir_path, mode) != 0 && errno != EEXIST) {
                perror("Failed to create parent directory");
                umask(old_umask);  // set old umask back
                return -1;
            }
            *p = '/';
        }
    }

    // create last foler
    if (syscall_mkdir(dir_path, mode) != 0 && errno != EEXIST) {
        perror("Failed to create directory");
        umask(old_umask);
        return -1;
    }

    umask(old_umask);
    return 0;
}

int main(int argc, char *argv[]) {
    int opt;
    int create_parents_flag = 0;

    // default access mode
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

    // check if path was provided
    if (optind >= argc) {
        fprintf(stderr, "Error: No directory path provided.\n");
        print_usage(argv[0]);
        return EXIT_FAILURE;
    }

    // get path to variable from getopts
    const char *dir_path = argv[optind];

    // set umask to 0 to ensure proper permissions
    mode_t old_umask = umask(0);

    // try to create folder/folders
    int result;
    if (create_parents_flag) {
        result = create_parents(dir_path, mode); // create parents based on -p flag
    } else {
        result = syscall_mkdir(dir_path, mode); // create single folder in current dir
    }

    umask(old_umask);

    // check if error occured
    if (result != 0) {
        fprintf(stderr, "Error creating directory: %s\n", strerror(errno));
        return EXIT_FAILURE;
    }

    // if it didnt occur exit successfully
    printf("Directory created successfully.\n");
    return EXIT_SUCCESS;
}