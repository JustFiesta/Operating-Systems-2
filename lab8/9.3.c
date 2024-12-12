#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define MAX 512

int main(int argc, char* argv[]) {
    int desc_zrod, desc_cel;
    int lbajt;
    char buf[MAX];

    if (argc < 3) {
        fprintf(stderr, "Za malo argumentow. Uzyj:\n");
        fprintf(stderr, "%s <plik zrodlowy> <plik docelowy>\n", argv[0]);
        exit(1);
    }

    desc_zrod = open(argv[1], O_RDONLY);

    if (desc_zrod == -1) {
        perror("Blad otwarcia pliku zrodlowego");
        exit(1);
    }

    desc_cel = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);

    if (desc_cel == -1) {
        perror("Owarcia utworzenia pliku docelowego");
        exit(1);
    }

    while ((lbajt = read(desc_zrod, buf, MAX)) > 0) {
        if (write(desc_cel, buf, lbajt) == -1) {
            perror("Blad zapisu pliku docelowego");
            exit(1);
        }
    }

    exit(0);
}