#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    FILE *original_file = fopen(argv[1], "r");
    if (original_file == NULL) {
        printf("Error: Cannot open the file '%s'.\n", argv[1]);
        return 1;
    }

    FILE *temp_file = fopen("temp_output.tmp", "w");
    if (temp_file == NULL) {
        printf("Error: Cannot create temporary file.\n");
        fclose(original_file);
        return 1;
    }

    int c;
    int offset = 0;

    while ((c = fgetc(original_file)) != EOF) {
        if (offset % 2 != 0) {
            fputc(c, temp_file);
        }
        offset++;
    }

    fclose(original_file);
    fclose(temp_file);

    remove(argv[1]);
    rename("temp_output.tmp", argv[1]);

    printf("Success! Bytes at even offsets have been deleted from '%s'.\n", argv[1]);

    return 0;
}