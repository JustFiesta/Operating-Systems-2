#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 100
int liczby[SIZE];
long suma1 = 0, suma2 = 0;

void licz_sume1(voidarg) {
    for(int i = 0; i < SIZE/2; i++)
        suma1 += liczby[i];
    return NULL;
}

void licz_sume2(voidarg) {
    for(int i = SIZE/2; i < SIZE; i++)
        suma2 += liczby[i];
    return NULL;
}

int main() {
    clock_t start = clock();
    srand(time(NULL));

    for(int i = 0; i < SIZE; i++)
        liczby[i] = rand() % 1000 + 1;

    pthread_t t1, t2;
    pthread_create(&t1, NULL, licz_sume1, NULL);
    pthread_create(&t2, NULL, licz_sume2, NULL);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("Suma: %ld\n", suma1 + suma2);
    printf("Czas sekwencyjny: %.4f sekund\n", 
           (double)(clock() - start) / CLOCKS_PER_SEC);
    return 0;
}