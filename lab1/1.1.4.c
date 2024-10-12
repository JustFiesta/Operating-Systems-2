#include <stdio.h>
#include <stdlib.h>

int main() {

    char str[10];

    fgets(str, 10, stdin); // działanie fgets - poprawnie zapobiega buffer overflow
    printf("%s",str);

    return 0;
}