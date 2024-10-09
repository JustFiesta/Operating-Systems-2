#include <stdio.h>
#include <ctype.h>
#include <string.h>

int isNumber(const char *s) {

    int test = 0;
    int result = 0;
    
    for (int i = 1; i < strlen(s); i++)
    {
        if (s[0] == '-')
        {
            test += 1;
        }
        
        if (isdigit(s[i]))
        {
            test += 1;
        }
    }
    
    if (test == strlen(s) - 1) {
        result = 1;
    }

    return result;
}

int main() {

    const char *first = "P@wws0rd";
    const char *second = "1234eeee";
    const char *fifonz = "Fifonz";
    const char *number = "1234";
    const char *minus = "-";

    printf("%d", isNumber(minus));

    return 0;
}