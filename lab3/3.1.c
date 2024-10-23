#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct Fraction {
    int num, den;
};

int isNumber(const char *s) {
    if (*s == '-' || *s == '+') s++;
    while (*s) {
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

int getOperator(char *op, const char *s) {
    if (strlen(s) == 1 && (*s == '+' || *s == '-' || *s == '*' || *s == '/' || *s == ':')) {
        *op = *s;
        return 1;
    }
    
    return 0;
}

char *trim(char *s) {
    while (isspace((unsigned char)*s)) s++;

    char *end = s + strlen(s) + 1;

    while (end > s && isspace((unsigned char)*end)) {
        end--;
    }

    *(end + 1) = '\0';

    return s;
}

struct Fraction sum(struct Fraction x, struct Fraction y) {
    int a = x.num;
    int b = x.den;
    
    int c = y.num;
    int d = y.den;
    
    struct Fraction z;
    
    z.num = a * d + c * b;
    z.den = b * d;
    
    return z;
}

struct Fraction sub(struct Fraction x, struct Fraction y) {
    int a = x.num;
    int b = x.den;
    
    int c = y.num;
    int d = y.den;
    
    struct Fraction z;
    
    z.num = a * d - c * b;
    z.den = b * d;
    
    return z;
}

struct Fraction mul(struct Fraction x, struct Fraction y) {
    int a = x.num;
    int b = x.den;
    
    int c = y.num;
    int d = y.den;
    
    struct Fraction z;
    
    z.num = a * c;
    z.den = b * d;
    
    return z;
}

struct Fraction quo(struct Fraction x, struct Fraction y) {
    int a = x.num;
    int b = x.den;
    
    int c = y.num;
    int d = y.den;
    
    struct Fraction z;
    
    z.num = a * d;
    z.den = b * c;
    
    return z;
}

void print(struct Fraction x, struct Fraction y, const char op) {
    struct Fraction result;

    switch(op) {
        case '+':
            result = sum(x, y);
            printf("%d/%d + %d/%d = %d/%d\n", x.num, x.den, y.num, y.den, result.num, result.den);
            break;
        case '-':
            result = sub(x, y);
            printf("%d/%d - %d/%d = %d/%d\n", x.num, x.den, y.num, y.den, result.num, result.den);
            break;
        case '*':
            result = mul(x, y);
            printf("%d/%d * %d/%d = %d/%d\n", x.num, x.den, y.num, y.den, result.num, result.den);
            break;
        case '/':
        case ':':
            result = quo(x, y);
            printf("%d/%d %c %d/%d = %d/%d\n", x.num, x.den, op, y.num, y.den, result.num, result.den);
            break;
        default:
            printf("$ - nieznane dzialanie\n");
            break;
    }
}

int nwd(int a, int b) {
    if (b == 0) return abs(a);
    return nwd(b, a % b);
}

struct Fraction simplify(struct Fraction x) {
    int divisor = nwd(x.num, x.den);
    x.num /= divisor;
    x.den /= divisor;
    return x;
}

void printFraction(struct Fraction x) {
    if (x.den == 0) {
        printf("NaN\n");
    } else if (x.num == 0) {
        printf("0\n");
    } else {
        if (x.den < 0) {
            x.num = -x.num;
            x.den = -x.den;
        }

        x = simplify(x);

        if (x.den == 1) {
            printf("%d\n", x.num);
        } else {
            printf("%d/%d\n", x.num, x.den);
        }
    }
}

int main() {
    struct Fraction x, y;
    char input[100];
    char op;

    do {
        printf("a/b = ");
        fgets(input, sizeof(input), stdin);
        trim(input);
        input[strcspn(input, "\n")] = 0;
    } while (!getFraction(&x, input));

    do {
        printf("c/d = ");
        fgets(input, sizeof(input), stdin);
        trim(input);
        input[strcspn(input, "\n")] = 0;
    } while (!getFraction(&y, input));

    do {
        printf("op = ");
        fgets(input, sizeof(input), stdin);
        trim(input);
        input[strcspn(input, "\n")] = 0;
    } while (!getOperator(&op, input));

    print(x, y, op);

    return 0;
}
