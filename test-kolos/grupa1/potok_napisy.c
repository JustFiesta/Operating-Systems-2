#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main() 
{
    int fd[2];
    pipe(fd);

    if (fork() == 0) {
        char *napisy[] = {"Ala", "Ma", "Kota"};
        close(fd[0]);

        for (int i = 0; i < 3; i++) {
            write(fd[1], napisy[i], strlen(napisy[i]));
        close(fd[1]);

        return 0;
    }
    close(fd[1]);

    char buf[256]; 
    char wynik[256] = "";
    int total_read = 0; 
    while ((total_read = read(fd[0], buf, sizeof(buf))) > 0) {
        buf[total_read] = '\0'; 
        strcat(wynik, buf); 
    }

    printf("Połączone napisy: %s\n", wynik);
    close(fd[0]);

    return 0;
}