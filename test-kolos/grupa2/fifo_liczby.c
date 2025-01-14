#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    int pipe_fd[2]; // Tablica deskryptorów dla potoku (pipe)
    pid_t pid;

    // Utworzenie potoku
    if (pipe(pipe_fd) == -1) {
        perror("Błąd tworzenia potoku");
        return 1;
    }

    // Utworzenie procesu potomnego
    pid = fork();
    if (pid == -1) {
        perror("Błąd tworzenia procesu");
        return 1;
    }

    if (pid == 0) {
        // Kod dla procesu potomnego
        close(pipe_fd[1]); // Zamknięcie końca zapisu (niepotrzebny w procesie potomnym)
        int liczba, iloczyn = 1;

        // Odczyt liczb z potoku
        while (read(pipe_fd[0], &liczba, sizeof(int)) > 0) {
            iloczyn *= liczba;
        }

        close(pipe_fd[0]); // Zamknięcie końca odczytu
        printf("Iloczyn: %d\n", iloczyn);
        exit(0);
    } else {
        // Kod dla procesu rodzica
        close(pipe_fd[0]); // Zamknięcie końca odczytu (niepotrzebny w procesie rodzica)
        int liczby[3] = {3, 3, 2}; // Trzy liczby do wysłania

        // Wysłanie liczb do potoku
        for (int i = 0; i < 3; i++) {
            write(pipe_fd[1], &liczby[i], sizeof(int));
        }

        close(pipe_fd[1]); // Zamknięcie końca zapisu
        wait(NULL); // Oczekiwanie na zakończenie procesu potomnego
    }

    return 0;
}
