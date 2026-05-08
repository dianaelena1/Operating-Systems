#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    // number of arguments
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <target> <replacement> <filename>\n", argv[0]);
        return 1;
    }

    char *target = argv[1];
    char *replacement = argv[2];
    char *filename = argv[3];
    
    int target_len = strlen(target);

    // open file (reading)
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    int c;
    while ((c = fgetc(file)) != EOF) {
        // check first character
        if (c == target[0]) {
            char *buffer = (char *)malloc(target_len + 1);
            buffer[0] = (char)c;
            int i;

            // read the rest of chars
            for (i = 1; i < target_len; i++) {
                c = fgetc(file);
                if (c == EOF) break;
                buffer[i] = (char)c;
            }
            buffer[i] = '\0';

            // compare with target word
            if (strcmp(buffer, target) == 0) {
                printf("%s", replacement);
            } else {
                printf("%s", buffer);
            }
            
            free(buffer);
        } else {
            // just print the character
            putchar(c);
        }
    }

    fclose(file);
    return 0;
}