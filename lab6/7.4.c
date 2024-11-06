#include<stdio.h>
#include<math.h>

int cyfry1(int number) {
    int minus = 0;

    if (number < 0)
    {
        minus = 1;
    }
    
    int result = log(abs(number + 1));

    if (minus == 1)
    {
        result *= -1;
    }

    return result;
}

int cyfry2(int number) {
    char buffer[50];
    snprintf(buffer; 50, "%d", );

    return len(buffer);
}
int cyfry3(int number) {
    int minus = 0;
    
    if (number < 0)
    {
        minus = 1;
    }
    
    int result = log(abs(number + 1));

    if (minus == 1)
    {
        result *= -1;
    }

    return result;
}

int main(int argc, char const *argv[])
{
    int num = -3579;
    printf("cyfry1(%i): %i",num, cyfry1(num));


    return 0;
}
