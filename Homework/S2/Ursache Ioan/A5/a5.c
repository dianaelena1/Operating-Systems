/* 11. Write a C Program that receives as command line argument a name of a file.
The program duplicates the bytes from even offsets in the file. */

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    FILE *source = fopen(argv[1], "rb");
    if (source == NULL) {
        perror("Error opening source file");
        return 1;
    }

    FILE *temp = fopen("temp.bin", "wb");
    if (temp == NULL) {
        perror("Error creating temporary file");
        fclose(source);
        return 1;
    }

    int ch;
    long offset = 0;

    while ((ch = fgetc(source)) != EOF) {
        if (offset % 2 == 0) {
            fputc(ch, temp);
            fputc(ch, temp);
        } else {
            fputc(ch, temp);
        }
        offset++;
    }

    fclose(source);
    fclose(temp);

    if (remove(argv[1]) != 0) {
        perror("Error deleting original file");
        return 1;
    }
    if (rename("temp.bin", argv[1]) != 0) {
        perror("Error renaming temporary file");
        return 1;
    }

    printf("File processed successfully: duplicated even-offset bytes.\n");
    return 0;
}