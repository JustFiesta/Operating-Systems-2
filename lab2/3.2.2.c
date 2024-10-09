#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *identity(const char *name, const char *surname) {

    char *string;

    string = (char*)malloc(strlen(name) + strlen(surname) + 2);

    if (string == NULL) {
        free(string);

        return NULL;
    }

    sprintf(string, "%s %s", name, surname);

    return string;
}

int main() {

    char *result = identity("Mateusz", "Bocak");

    printf("%s", result);

    free(result);
    return 0;    
}