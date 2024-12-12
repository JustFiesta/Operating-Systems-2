#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

// Funkcja do dopasowywania wyrażenia regularnego
void test_regex(const char *pattern, const char *text) {
    regex_t regex;
    int reti;

    // Kompilacja wzorca
    reti = regcomp(&regex, pattern, REG_EXTENDED);  // REG_EXTENDED - korzysta z rozszerzonych wyrażeń regularnych
    if (reti) {
        printf("Could not compile regex\n");
        exit(1);
    }

    // Dopasowanie wzorca do tekstu
    reti = regexec(&regex, text, 0, NULL, 0);
    if (!reti) {
        printf("Match found\n");
    } else if (reti == REG_NOMATCH) {
        printf("No match found\n");
    } else {
        char error_buf[100];
        regerror(reti, &regex, error_buf, sizeof(error_buf));
        printf("Regex match failed: %s\n", error_buf);
    }

    // Zwolnienie pamięci po kompilacji wzorca
    regfree(&regex);
}

int main() {
    // Test: Sprawdzenie, czy w tekście występuje numer telefonu
    const char *phone_pattern = "^\\+?[0-9]{1,4}?[-.\\s]?[0-9]+[-.\\s]?[0-9]+[-.\\s]?[0-9]+$";
    const char *text1 = "+1-800-555-5555";
    printf("Test 1 - Phone number: %s\n", text1);
    test_regex(phone_pattern, text1);

    // Test: Sprawdzenie, czy tekst pasuje do prostego wzorca emaila
    const char *email_pattern = "^[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\\.[A-Z|a-z]{2,}$";
    const char *text2 = "example@example.com";
    printf("Test 2 - Email: %s\n", text2);
    test_regex(email_pattern, text2);

    // Test: Dopasowanie słowa zawierającego tylko litery
    const char *word_pattern = "^[A-Za-z]+$";
    const char *text3 = "HelloWorld";
    printf("Test 3 - Word: %s\n", text3);
    test_regex(word_pattern, text3);

    // Test: Dopasowanie liczby
    const char *number_pattern = "^[0-9]+$";
    const char *text4 = "12345";
    printf("Test 4 - Number: %s\n", text4);
    test_regex(number_pattern, text4);

    return 0;
}
