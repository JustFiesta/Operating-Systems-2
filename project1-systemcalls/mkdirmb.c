#include <unistd.h>    // dla syscall
#include <sys/syscall.h> // dla SYS_mkdir
#include <sys/stat.h>  // dla praw dostępu
#include <stdio.h>

int main() {
    const char *directory_name = "new_directory";
    mode_t mode = 0755; // prawa dostępu (rwxr-xr-x)

    // Wywołanie syscall mkdir
    int result = syscall(SYS_mkdir, directory_name, mode);

    if (result == 0) {
        printf("Katalog został utworzony.\n");
    } else {
        perror("Błąd tworzenia katalogu");
    }

    return 0;
}
