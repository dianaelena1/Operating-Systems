#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main(int argc, char *argv[])
{
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <file>\n", argv[0]);
        return 1;
    }

    FILE *f = fopen(argv[1], "r");
    if (f == NULL) {
        fprintf(stderr, "Can't open file\n");
        return 1;
    }

    char *line = NULL;
    size_t capacity = 0;
    size_t len;

    while ((len = getline(&line, &capacity, f)) != -1) {
        
        int empty = 1;

        for (size_t i = 0; i < len; i++) {
            if (!isspace(line[i])){
                empty = 0;
                break;
            }
        }

        if (!empty)
            printf("%s", line);
    }

    free(line);
    fclose(f);

    return 0;
}