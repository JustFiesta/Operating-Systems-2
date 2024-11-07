#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

void add_numbers(int a, int b) {
    char str_a[20], str_b[20], result[20], carry[20];
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

int get_valid_int(const char *prompt) {
    int value;
    char input[20];
    char *endptr;

    while (1) {
        printf("%s", prompt);
        if (!fgets(input, sizeof(input), stdin)) {
            printf("Błąd odczytu danych. Spróbuj ponownie.\n");
            continue;
        }
        input[strcspn(input, "\n")] = '\0';

        value = strtol(input, &endptr, 10);
        if (*endptr != '\0') {
            printf("Podano niepoprawną liczbę całkowitą. Spróbuj ponownie.\n");
        } else {
            return value;
        }
    }
}

int main() {
    int a, b;
    long long int sum;

    a = get_valid_int("Podaj a: ");
    b = get_valid_int("Podaj b: ");

    sum = (long long int)a + b;
    if (sum > INT_MAX || sum < INT_MIN) {
        printf("Błąd: Suma przekracza zakres typu int.\n");
        return 1;
    }

    add_numbers(a, b);

    return 0;
}
