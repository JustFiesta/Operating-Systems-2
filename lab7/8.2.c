#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <errno.h>

// 8.2.1
int losuj(int a, int b) {
    if (a >= b) {
        printf("Błąd: nieprawidłowy przedział (a >= b)\n");
        return 1;  
    }
    
    int przedzial = b - a;
    return a + (rand() % przedzial);
}

// 8.2.2
int wariacje1() {
    char string[] = "qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM0123456789";

    int n = strlen(string);

    return n * (n - 1);
}

// 8.2.3
int wariacje2() {
    int count = 0;

    char string[] = "qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM0123456789";

    int n = strlen(string);

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (i != j)
            {
                count++;
            }            
        }
    }
    
    return count;
}

// 8.2.4
//  dla crypt_r salt dwu elementowy string wybrany z  [a-zA-Z0-9./]. Na każdym miejscu może być 1 z 64 możliwych znaków => 64 * 64  = 4096 możliwości perturbacji hasła za pomocą salt

// naszego salt[2] nie można wykorzystać do zasolenia hasła, ponieważ w C wymagany jest salt zakończony '\0' co wymaga salt[3]
void set(char salt[2]) {
    char string[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

   int firstCharIndex =  rand() % sizeof(string);
   int secondCharIndex =  rand() % sizeof(string);

   salt[0] = string[firstCharIndex];
   salt[1] = string[secondCharIndex];
}

// 8.2.5
void errnoExample() {
    FILE *file = fopen("nonexistent_file.txt", "r");

    if (!file) {
        printf("\nError: %s (errno: %d)\n", strerror(errno), errno);
    }
}

// 8.2.6
void perrorExample() {
    FILE *file = fopen("nonexistent_file.txt", "r");

    if (!file) {
        perror("Błąd otwarcia pliku\n");
    }
}

int main() {
    srand(time(NULL));
    
    printf("Test funkcji\n");
    
    printf("\nTest 1 - Przedział [0,10):\n");
    for (int i = 0; i < 5; i++) {
        printf("losuj(0,10) = %d\n", losuj(0,10));
    }
    
    printf("\nTest 2 - Przedział [-5,5):\n");
    for (int i = 0; i < 5; i++) {
        printf("losuj(-5,5) = %d\n", losuj(-5,5));
    }
    
    printf("\nTest 3 - Nieprawidłowy przedział [10,5):\n");
    printf("losuj(10,5) = %d\n\n", losuj(10,5));

    printf("\nLiczba wariacji: %d\n", wariacje1());

    printf("\nLiczba wariacji (brutalna siła): %d\n", wariacje2());
    

    printf("\nUstawienie salt[2]\n");

    char salt[2];
    set(salt);

    printf("salt[0]:%c\n", salt[0]);
    printf("salt[1]:%c\n", salt[1]);

    printf("\nerrno do obsługi błędów");
    errnoExample();

    printf("\nperror() do obsługi błędów");  
    perrorExample();

    return 0;
}