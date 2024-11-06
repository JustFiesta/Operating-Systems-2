#include<stdio.h>

int main(int argc, char const *argv[])
{

    printf("argc = %i\n", argc);

    char *program_name = argv[0];
    for (int i = 0; argv[0][i] != '\0'; i++){
        if (argv[0][i] == '/' || argv[0][i] == '\\')
        {
            program_name = &argv[0][i + 1];
        }
    }
    printf("addr: %s\n", program_name);

    printf("name: %s\n", argv[0]);

    printf("params: \n");
        for (int i = 1; i < argc; i++){
        printf(" %s", argv[i]);
    }
    return 0;
}
