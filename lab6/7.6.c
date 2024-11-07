#include <stdio.h>
#include <string.h>

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

    result[len_max + 1] = '\0';
    carry[len_max + 1] = '\0';

    for (i = len_a - 1, j = len_b - 1; len_max >= 0; i--, j--, len_max--) {
        int digit_a = (i >= 0) ? str_a[i] - '0' : 0;
        int digit_b = (j >= 0) ? str_b[j] - '0' : 0;

        sum = digit_a + digit_b + carry_over;
        result[len_max + 1] = (sum % 10) + '0';
        carry[len_max + 1] = (carry_over > 0) ? carry_over + '0' : ' ';
        carry_over = sum / 10;
    }
    result[0] = carry_over > 0 ? carry_over + '0' : ' ';
    carry[0] = ' ';

    printf(" %s\n", carry);
    printf(" %*d\n+%*d\n", strlen(str_a), a, strlen(str_b), b);
    printf("------\n %s\n", result);
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
