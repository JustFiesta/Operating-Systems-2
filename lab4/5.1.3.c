#include <stdio.h>
#include <stdlib.h>

void copy(const char *addr1, const char *addr2) {
    FILE *source = fopen(addr1, "r");
    FILE *dest = fopen(addr2, "w");

    int bufferSize = 1024;

    char buffer[1024];

    int i = 0;
    while (fgets(buffer, sizeof(buffer), source) != NULL) {
        fputs(buffer, dest);
    }

    fclose(source);
    fclose(dest);
}

int main() {

    copy("./file.txt", "./file-copy.txt");

    return 0;
}
