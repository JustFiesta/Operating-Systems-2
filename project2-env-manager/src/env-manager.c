#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Deklaracja zewnętrznej zmiennej environ
extern char **environ;

void list_envs() {
    // Przechodzimy przez tablicę environ aż napotkamy NULL
    for(char **env = environ; *env != NULL; env++) {
        printf("%s\n", *env);
    }
}

void add_env(const char* var_name, const char* var_value) {
    // setenv zwraca 0 w przypadku sukcesu, -1 w przypadku błędu
    if (setenv(var_name, var_value, 1) == 0) {
        printf("Added %s\n", var_name);
    } else {
        fprintf(stderr, "Failed to add environment variable %s\n", var_name);
        exit(1);
    }
}

void remove_env(const char* var_name) {
    // Sprawdzamy czy zmienna istnieje
    if (getenv(var_name) == NULL) {
        fprintf(stderr, "Environment variable %s does not exist\n", var_name);
        exit(1);
    }
    
    // unsetenv zwraca 0 w przypadku sukcesu, -1 w przypadku błędu
    if (unsetenv(var_name) == 0) {
        printf("Removed %s\n", var_name);
    } else {
        fprintf(stderr, "Failed to remove environment variable %s\n", var_name);
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