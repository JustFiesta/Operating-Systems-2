#include<stdio.h>

int main(int argc, char const *argv[])
{
    #ifdef _WIN32
    printf("Program compiled on: Windows");
    #else
    printf("Program compiled on: Linux");
    #endif

    return 0;
}
