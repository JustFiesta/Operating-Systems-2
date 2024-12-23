#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>  // Dodane dla pid_t
#include <sys/wait.h>   // Dodane dla wait()
#include <string.h>

#define BUFFER_SIZE 256

// Funkcja do odczytu zużycia CPU
float get_cpu_usage(pid_t pid) {
    char filename[BUFFER_SIZE];
    snprintf(filename, sizeof(filename), "/proc/%d/stat", pid);
    FILE *file = fopen(filename, "r");
    
    if (!file) {
        perror("fopen");
        return -1;
    }

    long utime, stime, cutime, cstime, starttime;
    fscanf(file, "%*d %*s %*c %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %ld %ld %ld %ld %ld", 
           &utime, &stime, &cutime, &cstime, &starttime);
    fclose(file);

    // Obliczanie całkowitego czasu CPU
    long total_time = utime + stime + cutime + cstime;
    long uptime = sysconf(_SC_CLK_TCK);  // Zegar systemowy
    float cpu_usage = (float)total_time / uptime * 100;  // Przemiana na procenty

    return cpu_usage;
}

// Funkcja do odczytu zużycia pamięci
long get_memory_usage(pid_t pid) {
    char filename[BUFFER_SIZE];
    snprintf(filename, sizeof(filename), "/proc/%d/status", pid);
    FILE *file = fopen(filename, "r");
    
    if (!file) {
        perror("fopen");
        return -1;
    }

    char line[BUFFER_SIZE];
    long memory_usage = 0;

    // Szukamy linii z "VmRSS", która podaje pamięć używaną przez proces
    while (fgets(line, sizeof(line), file)) {
        if (strncmp(line, "VmRSS:", 6) == 0) {
            sscanf(line, "VmRSS: %ld kB", &memory_usage);
            break;
        }
    }
    fclose(file);

    return memory_usage;
}

int main(int argc, char *argv[]) {
    // Sprawdzenie, czy podano odpowiednią liczbę argumentów
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <process_name>\n", argv[0]);
        return 1;
    }

    // Proces potomny
    pid_t pid = fork();
    if (pid < 0) {
        // Błąd przy tworzeniu procesu
        perror("fork failed");
        return 1;
    }

    if (pid == 0) {
        // Proces potomny - uruchomienie procesu
        printf("Starting process: %s\n", argv[1]);

        // Użycie execvp() do uruchomienia procesu
        if (execvp(argv[1], &argv[1]) == -1) {
            // Błąd przy uruchamianiu procesu
            perror("execvp failed");
            return 1;
        }
    } else {
        // Proces macierzysty - monitorowanie procesu
        printf("Monitoring process: %s\n", argv[1]);
        while (1) {
            // Monitorowanie zużycia CPU
            float cpu_usage = get_cpu_usage(pid);
            long memory_usage = get_memory_usage(pid);

            if (cpu_usage == -1 || memory_usage == -1) {
                break;  // Błąd odczytu danych
            }

            // Wyświetlanie zużycia zasobów
            printf("CPU Usage: %.2f%% | Memory Usage: %ld KB\n", cpu_usage, memory_usage);

            // Czekaj 1 sekundę
            sleep(1);

            // Sprawdzenie, czy proces nadal działa
            if (kill(pid, 0) == -1) {
                // Proces zakończył działanie
                break;
            }
        }

        wait(NULL);  // Czekaj, aż proces potomny się zakończy
        printf("Process %s finished\n", argv[1]);
    }

    return 0;
}