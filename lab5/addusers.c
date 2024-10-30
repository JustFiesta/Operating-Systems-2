#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct User {
    char name[50];
    char surname[50];
    char password[50];
};

int adduser(char* name, char* surname, char* password) {
    char command[200];
    snprintf(command, sizeof(command), "sudo useradd -m -p $(openssl passwd -1 %s) %s_%s", password, name, surname);
    return system(command);
}

int main() {
    FILE *file = fopen("baza.txt", "r");
    if (file == NULL) {
        perror("Nie można otworzyć pliku baza.txt");
        return 1;
    }

    struct User user;
    char line[150];

    while (fgets(line, sizeof(line), file) != NULL) {
        line[strcspn(line, "\r\n")] = '\0';

        char *token = strtok(line, ";");
        if (token != NULL) strcpy(user.name, token);

        token = strtok(NULL, ";");
        if (token != NULL) strcpy(user.surname, token);

        token = strtok(NULL, ";");
        if (token != NULL) strcpy(user.password, token);

        if (adduser(user.name, user.surname, user.password) != 0) {
            fprintf(stderr, "Nie udało się dodać użytkownika: %s %s\n", user.name, user.surname);
        } else {
            printf("Dodano użytkownika: %s %s\n", user.name, user.surname);
        }
    }

    fclose(file);
    return 0;
}

