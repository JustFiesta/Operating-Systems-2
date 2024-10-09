// Rekurencja prosta
#include <stdio.h>

int a0() {
    return 1;
}

int a1() {
    return 4;
}

int sequence(int number, int arr[]){
    return 2 * arr[number - 1] + 0.5 * arr[number - 2];
}

int main() {

    printf("Hello world!");

    int array[10];

    array[0] = a0();
    array[1] = a1();

    int constraint = 10;

    for (int i = 2; i < constraint; i++) {
        array[i] = sequence(i, array);
    }
    
    printf("Pierwsze dziesięć wyrazów ciągu {an}:\n");
    for (int i = 0; i < constraint; i++) {
        printf("a(%d) = %d\n", i, array[i]);
    }

    return 0;
}
