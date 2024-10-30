#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct User {
    char name[50];
    char surname[50];
    char password[50];
};

int deluser(const char *username) {
    char command[100];
    snprintf(command, sizeof(command), "sudo userdel -r %s", username);
    return system(command); 
}

int main() {
    FILE *fp = fopen("baza.txt", "r");
    if (fp == NULL) {
        printf("Nie udało się otworzyć pliku.\n");
        return 1;
    }

    struct User user;
    while (fgets(user.name, sizeof(user.name), fp) != NULL) {
        user.name[strcspn(user.name, "\n")] = 0; 

        char *token = strtok(user.name, ";");
        if (token != NULL) {
            strcpy(user.name, token);
            token = strtok(NULL, ";");
            if (token != NULL) {
                strcpy(user.surname, token);
                token = strtok(NULL, ";");
                if (token != NULL) {
                    strcpy(user.password, token);
                    char username[100];
                    snprintf(username, sizeof(username), "%s_%s", user.name, user.surname);
                    deluser(username);
                }
            }
        }
    }

    fclose(fp);
    return 0;
}
