#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return EXIT_FAILURE;
    }

    FILE *file = fopen(argv[1], "r");
    if (file == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    int ch;
    while ((ch = fgetc(file)) != EOF) {
        putchar(ch);


        if (ch == '\n') {
            putchar('\n');
        }
    }

    fclose(file);
    return EXIT_SUCCESS;
}