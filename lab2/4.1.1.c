#include <stdio.h>
#include <ctype.h>
#include <string.h>

int isNumber(const char *s) {

    int test = 0;
    int result = 0;

    // puty to nie liczba - adios
    if (s == NULL || strlen(s) == 0) {
        return 0;
    }

    // sprawdzenie czy pierwszy znak to "-"
    if (s[0] == '-') {
        if (strlen(s) == 1) {
            return 0;
        }

        for (int i = 1; i < strlen(s); i++) {
            if (!isdigit(s[i])) {
                return 0;  
            }
        }

        return 1;  
    }

    // sprawdzenie całości bez znaku '-'
    for (int i = 0; i < strlen(s); i++) {
        if (!isdigit(s[i])) {
            return 0; 
        }
    }

    return 1;
}

int main() {

    const char *first = "P@wws0rd";
    const char *second = "1234eeee";
    const char *fifonz = "Fifonz";
    const char *number = "1234";
    const char *minus = "-";

    printf("%d", isNumber(minus));

    return 0;
}