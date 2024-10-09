#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 33

char *login(const char *name, const char *surname) {
    char *result = malloc(MAX); // bo ostatni znak to znak terminacji

    if (result == NULL) {
        free(result);

        return NULL;
    }

    snprintf(result, MAX, "%c%s", name[0], surname);

    return result;

}

int main() {

    char *result = login("Mateusz", "Bocak");

    printf("%s", result);

    free(result);
    return 0;    
}