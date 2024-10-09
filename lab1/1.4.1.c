// Dziel i zwyciężaj
#include <stdio.h>

int a0() {
    return 1;
}

int a1() {
    return 4;
}

int sequence2(int number, int arr[], int level) {
    for (int i = 0; i < level; i++) {
        printf("  "); 
    }

    printf("a1(%d)\n", number);

    if (number == 0) {
        return a0();
    } else if (number == 1) {
        return a1();
    } else {
        int result = 2 * sequence2(number - 1, arr, level + 1) + 0.5 * sequence2(number - 2, arr, level + 1);
        return result;
    }
}


int main() {
    int array[10];

    array[0] = a0();
    array[1] = a1();

    int constraint = 4;

    printf("Analiza wywołania dla a1(%d):\n", constraint);

    int result = sequence2(constraint, array, 0);

    printf("Wynik a1(%d) = %d\n", constraint, result);
    
    return 0;
}