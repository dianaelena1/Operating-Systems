#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Error: You must provide exactly one file name.\n");
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    int c;
    int beginning_of_line = 1;

    while ((c = fgetc(file)) != EOF) {
        if (beginning_of_line && c == '\n') {
            continue;
        }

        putchar(c);

        if (c == '\n') {
            beginning_of_line = 1;
        } else {
            beginning_of_line = 0;
        }
    }

    fclose(file);
    return 0;
}