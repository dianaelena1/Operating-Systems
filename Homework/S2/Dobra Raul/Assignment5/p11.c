#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

    if (argc != 2) {
        printf("Utilizare: %s <nume_fisier>\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "rb");
    if (file == NULL) {
        perror("Eroare la deschiderea fisierului");
        return 1;
    }

    int ch;
    long offset = 0;

    while ((ch = fgetc(file)) != EOF) {
        putchar(ch);

        if (offset % 2 == 0) {
            putchar(ch);
        }

        offset++;
    }

    fclose(file);

    return 0;
}