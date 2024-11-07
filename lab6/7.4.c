#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int cyfry1(int number) {
    if (number == 0) return 1;

    return (int)log10(abs(number)) + 1;
}

int cyfry2(int number) {
    char buffer[50];

    snprintf(buffer, sizeof(buffer), "%d", number);

    int count = 0;
    for (int i = 0; buffer[i] != '\0'; i++) { 
        if (buffer[i] >= '0' && buffer[i] <= '9') {
            count++;
        }
    }

    return count;
}

int cyfry3(int number) {
    if (number == 0) return 1;

    int count = 0;

    number = abs(number);

    while (number > 0) {
        number /= 10;
        count++;
    }

    return count;
}

int main() {
    int num = -3579;

    printf("cyfry1(%d) = %d\n", num, cyfry1(num));
    printf("cyfry2(%d) = %d\n", num, cyfry2(num));
    printf("cyfry3(%d) = %d\n", num, cyfry3(num));

    return 0;
}
