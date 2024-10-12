#include <stdio.h>

int main() {
    char str[100];
    
    printf("Wpisz tekst (Ctrl+D lub Ctrl+Z na końcu wprowadzenia, aby zakończyć):\n");

    while (1) {
        if (fgets(str, sizeof(str), stdin) == NULL) {
            if (feof(stdin)) { // sprwadzenie czy podano EOF
                printf("Osiągnięto koniec pliku (EOF).\n");
                break;  
            } else {
                printf("Błąd wejścia.\n");
                break;
            }
        }
        printf("Wpisany tekst: %s", str);
    }

    return 0;
}
