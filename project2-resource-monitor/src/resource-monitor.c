#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <errno.h>
#include <ctype.h>

#define MAX_CMDLINE 1024
#define BUFFER_SIZE 256

// Struktura przechowująca informacje o wykorzystaniu zasobów
typedef struct {
    double cpu_usage;
    long memory_usage;
} ResourceUsage;

// Funkcja do parsowania linii poleceń
char** parse_command(const char* cmd) {
    char* cmd_copy = strdup(cmd);
    char** args = malloc(sizeof(char*) * MAX_CMDLINE);
    int i = 0;
    
    char* token = strtok(cmd_copy, " ");
    while (token != NULL && i < MAX_CMDLINE - 1) {
        args[i] = strdup(token);
        token = strtok(NULL, " ");
        i++;
    }
    args[i] = NULL;
    
    free(cmd_copy);
    return args;
}

// Funkcja do czyszczenia zaalokowanej pamięci
void cleanup_args(char** args) {
    for (int i = 0; args[i] != NULL; i++) {
        free(args[i]);
    }
    free(args);
}

// Funkcja do pobierania statystyk CPU procesu
double get_cpu_usage(pid_t pid) {
    char stat_path[64];
    snprintf(stat_path, sizeof(stat_path), "/proc/%d/stat", pid);
    
    FILE* f = fopen(stat_path, "r");
    if (!f) return -1.0;
    
    long utime, stime;
    char* line = NULL;
    size_t len = 0;
    
    if (getline(&line, &len, f) != -1) {
        char* token = strtok(line, " ");
        int i;
        for (i = 1; token && i < 14; i++) {
            token = strtok(NULL, " ");
        }
        if (token) {
            utime = atol(token);
            token = strtok(NULL, " ");
            if (token) {
                stime = atol(token);
                double total_time = (utime + stime) / (double)sysconf(_SC_CLK_TCK);
                free(line);
                fclose(f);
                return total_time * 100.0;
            }
        }
    }
    
    free(line);
    fclose(f);
    return -1.0;
}

// Funkcja do pobierania zużycia pamięci procesu
long get_memory_usage(pid_t pid) {
    char status_path[64];
    snprintf(status_path, sizeof(status_path), "/proc/%d/status", pid);
    
    FILE* f = fopen(status_path, "r");
    if (!f) return -1;
    
    char line[256];
    long vm_rss = -1;
    
    while (fgets(line, sizeof(line), f)) {
        if (strncmp(line, "VmRSS:", 6) == 0) {
            char* ptr = line + 6;
            while (*ptr && isspace(*ptr)) ptr++;
            vm_rss = atol(ptr);
            break;
        }
    }
    
    fclose(f);
    return vm_rss;
}

// Główna funkcja monitorująca
void monitor_process(pid_t pid) {
    printf("\nMonitoring process (PID: %d)\n", pid);
    printf("Press Ctrl+C to stop monitoring\n\n");
    
    double prev_cpu_time = 0;
    struct timespec sleep_time = {1, 0}; // 1 sekunda
    
    while (1) {
        if (kill(pid, 0) == -1) {
            if (errno == ESRCH) {
                printf("Process has terminated.\n");
                break;
            } else {
                perror("Error checking process status");
                break;
            }
        }
        
        double cpu_time = get_cpu_usage(pid);
        long memory_kb = get_memory_usage(pid);
        
        if (cpu_time >= 0 && memory_kb >= 0) {
            double cpu_usage = cpu_time - prev_cpu_time;
            double memory_mb = memory_kb / 1024.0;
            printf("CPU Usage: %.1f%% | Memory Usage: %.2f MB\n", 
                   cpu_usage, memory_mb);
            prev_cpu_time = cpu_time;
        } else {
            printf("Error reading process statistics, process may have terminated.\n");
            break;
        }
        
        nanosleep(&sleep_time, NULL);
    }
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s \"command [args...]\"\n", argv[0]);
        return 1;
    }
    
    // Parsuj komendę i argumenty
    char** cmd_args = parse_command(argv[1]);
    if (cmd_args[0] == NULL) {
        fprintf(stderr, "Error: Empty command\n");
        cleanup_args(cmd_args);
        return 1;
    }
    
    printf("Starting process: %s\n", argv[1]);
    
    // Utwórz nowy proces
    pid_t pid = fork();
    
    if (pid < 0) {
        perror("Fork failed");
        cleanup_args(cmd_args);
        return 1;
    }
    
    if (pid == 0) {
        execvp(cmd_args[0], cmd_args);
        perror("Exec failed");
        cleanup_args(cmd_args);
        return 1;
    }
    
    // Proces rodzicielski
    monitor_process(pid);
    
    // Poczekaj na zakończenie procesu potomnego
    int status;
    waitpid(pid, &status, 0);
    
    cleanup_args(cmd_args);
    
    if (WIFEXITED(status)) {
        return WEXITSTATUS(status);
    } else if (WIFSIGNALED(status)) {
        fprintf(stderr, "Process terminated by signal %d\n", WTERMSIG(status));
        return 1;
    } else {
        fprintf(stderr, "Process terminated abnormally\n");
        return 1;
    }
}