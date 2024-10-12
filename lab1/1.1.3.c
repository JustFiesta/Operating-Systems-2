#include <stdio.h>
#include <stdlib.h>

int main() {

    char string[20];

    scanf("%10s", string); // dodanie %19s nic nie zmienia - nie przicina znaków na WIN11
    printf("%s", string);

    return 0;
}