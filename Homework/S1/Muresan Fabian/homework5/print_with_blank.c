#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s filename\n", argv[0]);
        return 1;
    }

    FILE *f = fopen(argv[1], "r");
    if (!f) {
        perror("Error opening file");
        return 1;
    }

    unsigned char *line = NULL;
    size_t len = 0;
    ssize_t n;

    while ((n = getline(&line, &len, f)) != -1) {
        if (fwrite(line, 1, n, stdout) != (size_t)n) {
            perror("write");
            free(line);
            fclose(f);
            return 1;
        }
        if (putchar('\n') == EOF) {
            perror("putchar");
            free(line);
            fclose(f);
            return 1;
        }
    }

    free(line);
    fclose(f);
    return 0;
}
