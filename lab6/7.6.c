#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BUFFER_SIZE 100

void add_numbers(int a, int b) {
    char str_a[BUFFER_SIZE], str_b[BUFFER_SIZE], result[BUFFER_SIZE], carry[BUFFER_SIZE];
    int len_a, len_b, len_max, carry_over = 0, sum, i, j;

    sprintf(str_a, "%d", a);
    sprintf(str_b, "%d", b);

    len_a = strlen(str_a);
    len_b = strlen(str_b);
    len_max = (len_a > len_b) ? len_a : len_b;

    memset(result, ' ', sizeof(result));
    memset(carry, ' ', sizeof(carry));

    result[len_max] = '\0';
    carry[len_max] = '\0';

    for (i = len_a - 1, j = len_b - 1; i >= 0 || j >= 0; i--, j--) {
        int digit_a = (i >= 0) ? str_a[i] - '0' : 0;
        int digit_b = (j >= 0) ? str_b[j] - '0' : 0;

        sum = digit_a + digit_b + carry_over;
        result[len_max--] = (sum % 10) + '0';
        carry[len_max + 1] = (carry_over > 0) ? carry_over + '0' : ' ';
        carry_over = sum / 10;
    }

    if (carry_over > 0) {
        result[len_max] = carry_over + '0';
    } else {
        memmove(result, result + 1, strlen(result));
    }

    int size_flag = 0;

    printf("%s\n", carry);
    if ((int)strlen(str_a) > (int)strlen(str_b))
    {
        printf(" %*d\n+%*d\n", (int)strlen(str_a), a, (int)strlen(str_a), b);
        size_flag = (int)strlen(str_a);
    } else {
        printf(" %*d\n+%*d\n", (int)strlen(str_b), a, (int)strlen(str_b), b);
        size_flag = (int)strlen(str_b);
    }

    for (int i = 0; i < size_flag + 1; i++)
    {
        printf("-");
    }
    
    
    printf("\n %s\n", result);
}

int main() {
    int a, b;
    printf("Podaj a: ");
    scanf("%d", &a);
    printf("Podaj b: ");
    scanf("%d", &b);

    add_numbers(a, b);
    return 0;
}