#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(int argc, char const *argv[])
{
    char command_buffer[256] = "";
    #ifdef _WIN32
    strcpy(command_buffer, "dir ");
    #else
    strcpy(command_buffer, "ls ");
    #endif

    for (int i = 0; i < argc; i++)
    {
        strcat(command_buffer, argv[i]);
        strcat(command_buffer, " ");
    }

    system(command_buffer);

    return 0;
}
