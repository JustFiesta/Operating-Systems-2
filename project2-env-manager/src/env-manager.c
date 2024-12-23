#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <limits.h>

extern char **environ;

#define MAX_ENV_LENGTH 1000

// Sprawdza, czy nazwa zmiennej jest poprawna:
// - Może zawierać tylko litery, cyfry i podkreślenia
// - Musi zaczynać się od litery lub podkreślenia
// - Nie może być pusta
int is_valid_env_name(const char* name) {
    if (name == NULL || name[0] == '\0') {
        return 0;
    }
    
    // Pierwszy znak musi być literą lub podkreśleniem
    if (!isalpha(name[0]) && name[0] != '_') {
        return 0;
    }
    
    // Kolejne znaki mogą być literami, cyframi lub podkreśleniem
    for (int i = 1; name[i] != '\0'; i++) {
        if (!isalnum(name[i]) && name[i] != '_') {
            return 0;
        }
    }
    
    return 1;
}

// Sprawdza długość zmiennej
int check_length(const char* str, const char* what) {
    if (strlen(str) > MAX_ENV_LENGTH) {
        fprintf(stderr, "Error: %s too long (max %d characters)\n", 
                what, MAX_ENV_LENGTH);
        return 0;
    }
    return 1;
}

void list_envs() {
    // Przechodzimy przez tablicę environ aż napotkamy NULL
    for(char **env = environ; *env != NULL; env++) {
        printf("%s\n", *env);
    }
}

void add_env(const char* var_name, const char* var_value) {
    // Sprawdzenie poprawności nazwy
    if (!is_valid_env_name(var_name)) {
        fprintf(stderr, "Invalid variable name. Name must:\n");
        fprintf(stderr, "- Start with a letter or underscore\n");
        fprintf(stderr, "- Contain only letters, numbers, and underscores\n");
        fprintf(stderr, "- Not be empty\n");
        exit(1);
    }
    
    // Sprawdzenie długości
    if (!check_length(var_name, "Variable name") || 
        !check_length(var_value, "Variable value")) {
        exit(1);
    }
    
    // Próba ustawienia zmiennej
    if (setenv(var_name, var_value, 1) == 0) {
        printf("Added %s\n", var_name);
    } else {
        fprintf(stderr, "Failed to add environment variable %s: %s\n", 
                var_name, strerror(errno));
        exit(1);
    }
}

void remove_env(const char* var_name) {
    // Sprawdzenie poprawności nazwy
    if (!is_valid_env_name(var_name)) {
        fprintf(stderr, "Invalid variable name. Name must:\n");
        fprintf(stderr, "- Start with a letter or underscore\n");
        fprintf(stderr, "- Contain only letters, numbers, and underscores\n");
        fprintf(stderr, "- Not be empty\n");
        exit(1);
    }
    
    // Sprawdzenie długości
    if (!check_length(var_name, "Variable name")) {
        exit(1);
    }
    
    // Sprawdzenie czy zmienna istnieje
    if (getenv(var_name) == NULL) {
        fprintf(stderr, "Environment variable %s does not exist\n", var_name);
        exit(1);
    }
    
    // Próba usunięcia zmiennej
    if (unsetenv(var_name) == 0) {
        printf("Removed %s\n", var_name);
    } else {
        fprintf(stderr, "Failed to remove environment variable %s: %s\n", 
                var_name, strerror(errno));
        exit(1);
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s [list|add <name>=<value>|remove <name>]\n", argv[0]);
        return 1;
    }

    const char* command = argv[1];

    if (strcmp(command, "list") == 0) {
        if (argc != 2) {
            fprintf(stderr, "list command doesn't take any arguments\n");
            return 1;
        }
        list_envs();
    }
    else if (strcmp(command, "add") == 0) {
        if (argc != 3) {
            fprintf(stderr, "Usage: %s add <name>=<value>\n", argv[0]);
            return 1;
        }
        
        char* arg = argv[2];
        char* equals = strchr(arg, '=');
        if (equals == NULL) {
            fprintf(stderr, "Invalid format. Use: <name>=<value>\n");
            return 1;
        }
        
        *equals = '\0';  // Split string at '=' character
        char* name = arg;
        char* value = equals + 1;
        
        add_env(name, value);
    }
    else if (strcmp(command, "remove") == 0) {
        if (argc != 3) {
            fprintf(stderr, "Usage: %s remove <name>\n", argv[0]);
            return 1;
        }
        
        remove_env(argv[2]);
    }
    else {
        fprintf(stderr, "Unknown command: %s\n", command);
        fprintf(stderr, "Available commands: list, add, remove\n");
        return 1;
    }

    return 0;
}