#include <stdio.h>      // Provides standard input and output functions (e.g., printf, fprintf) for displaying messages to the user
#include <stdlib.h>     // Defines memory management (e.g., malloc, free), conversion, and program control (e.g., EXIT_SUCCESS, EXIT_FAILURE) functions
#include <string.h>     // Contains functions for handling strings and memory (e.g., strncpy, strerror) used for copying and error messaging
#include <errno.h>      // Declares error codes and the errno variable, which helps capture and report specific errors from system calls
#include <unistd.h>     // Provides access to the POSIX operating system API, including functions like getopt (for handling command-line options) and syscall
#include <sys/syscall.h> // Defines system call numbers (e.g., __NR_mkdir) to be used with syscall, enabling direct calls to the OS's system-level functions
#include <sys/stat.h>   // Contains constants and functions for handling file attributes and modes (e.g., mode_t type), such as for setting directory permissions
#include <linux/limits.h> // Defines system-wide constants like PATH_MAX, which represents the maximum length of a filesystem path

// Get the system call number for mkdir from unistd.h header
#define MKDIR_SYSCALL_NUM  __NR_mkdir

// Print usage instructions to guide the user on how to use this program
void print_usage(const char *progname) {
    fprintf(stderr, "Usage: %s [-p] directory_path\n", progname); // Usage format with optional -p flag and directory path
}

// Function to call the mkdir syscall directly
int syscall_mkdir(const char *path, mode_t mode) {
    // Call mkdir using syscall number with specified path and mode (permissions)
    return syscall(MKDIR_SYSCALL_NUM, path, mode);
}

// Function to recursively create all parent directories in the specified path
int create_parents(const char *path, mode_t mode) {
    // Buffer to hold the directory path (up to maximum path length)
    char dir_path[PATH_MAX];
    strncpy(dir_path, path, PATH_MAX); // Copy path into dir_path buffer to avoid modifying the original input

    // Set umask to 0 temporarily to ensure permissions match the specified mode
    mode_t old_umask = umask(0);

    // Iterate over each '/' in the path to split it into subdirectories
    for (char *p = dir_path + 1; *p; p++) {
        if (*p == '/') {
            *p = '\0';  // Temporarily replace '/' with null character to mark end of current subdirectory

            // Create the current subdirectory
            if (syscall_mkdir(dir_path, mode) != 0 && errno != EEXIST) { // If mkdir fails and error is not "directory exists"
                perror("Failed to create parent directory"); // Print error for parent directory creation
                umask(old_umask);  // Restore original umask
                return -1;
            }
            *p = '/';  // Restore '/' after processing the current subdirectory
        }
    }

    // Create the final directory in the path
    if (syscall_mkdir(dir_path, mode) != 0 && errno != EEXIST) { // If mkdir fails and error is not "directory exists"
        perror("Failed to create directory"); // Print error for final directory creation
        umask(old_umask);  // Restore original umask
        return -1;
    }

    // Restore the original umask after creating directories
    umask(old_umask);
    return 0;  // Successfully created all required directories
}

int main(int argc, char *argv[]) {
    int opt;  // Variable for getopt to process options
    int create_parents_flag = 0;  // Flag to indicate whether to create parent directories

    // Default directory permissions (octal 0755) when no specific mode is set
    mode_t mode = 0755;

    // Parse command-line options using getopt
    while ((opt = getopt(argc, argv, "ph")) != -1) { // Supports -p for parent directories and -h for help
        switch (opt) {
            case 'p':
                create_parents_flag = 1; // Enable recursive directory creation when -p is specified
                break;
            case 'h':
                print_usage(argv[0]); // Display usage instructions if -h is specified
                return EXIT_SUCCESS;  // Exit successfully after displaying usage
            default:
                print_usage(argv[0]); // Display usage if an invalid option is provided
                return EXIT_FAILURE;  // Exit with failure status
        }
    }

    // Ensure a directory path is specified
    if (optind >= argc) { // optind is the index of the first non-option argument
        fprintf(stderr, "Error: No directory path provided.\n"); // Error if directory path is missing
        print_usage(argv[0]);
        return EXIT_FAILURE;
    }

    // Retrieve directory path from command-line arguments
    const char *dir_path = argv[optind];

    // Set umask to 0 to ensure specified permissions are applied correctly
    mode_t old_umask = umask(0);

    // Attempt to create the directory or directories based on the -p flag
    int result;
    if (create_parents_flag) {
        // If -p is set, create parent directories as needed
        result = create_parents(dir_path, mode);
    } else {
        // Without -p, create only the specified directory without creating parents
        result = syscall_mkdir(dir_path, mode);
    }

    // Restore the original umask value after directory creation
    umask(old_umask);

    // Check if directory creation was successful
    if (result != 0) { // If result is non-zero, an error occurred
        fprintf(stderr, "Error creating directory: %s\n", strerror(errno)); // Print specific error message
        return EXIT_FAILURE;
    }

    // Successful execution and directory creation
    printf("Directory created successfully.\n");
    return EXIT_SUCCESS;
}
