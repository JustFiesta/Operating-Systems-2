#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

struct Fraction {
    int num;
    int den;
};

int isNumber(const char *s) {
    if (*s == '-' || *s == '+') s++; 
    if (*s == '\0') return 0; 
    while (*s != '\0') {
        if (!isdigit(*s)) return 0; 
        s++;
    }
    return 1;
}

int getFraction(struct Fraction *x, const char *s) {
    char *slashPos = strchr(s, '/');
    
    if (slashPos) {
        char numerator[50];
        char denominator[50];

        strncpy(numerator, s, slashPos - s);
        numerator[slashPos - s] = '\0';
        strcpy(denominator, slashPos + 1);  

        if (isNumber(numerator) && isNumber(denominator)) {
            int num = atoi(numerator);       
            int den = atoi(denominator);

            if (den != 0) {  
                x->num = num;
                x->den = den;
                return 1;  
            }
        }
    } else {
        if (isNumber(s)) {
            x->num = atoi(s);
            x->den = 1;
            return 1;
        }
    }
    
    return 0;  
}

int main() {
    struct Fraction frac;
    const char *inputs[] = {"3/5", "7", "4/0", "-12/4", "-10", "abc", NULL};

    for (int i = 0; inputs[i] != NULL; i++) {
        if (getFraction(&frac, inputs[i])) {
            printf("'%s' jest poprawnym ulamkiem: %d/%d\n", inputs[i], frac.num, frac.den);
        } else {
            printf("'%s' nie jest poprawnym ulamkiem.\n", inputs[i]);
        }
    }

    return 0;
}
