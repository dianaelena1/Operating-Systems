#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "r+b");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    // Get file size
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    rewind(file);

    // Read the entire file into memory
    unsigned char *buffer = (unsigned char *)malloc(file_size * sizeof(unsigned char));
    if (buffer == NULL) {
        perror("Memory allocation failed");
        fclose(file);
        return 1;
    }

    if (fread(buffer, 1, file_size, file) != file_size) {
        perror("Error reading file");
        free(buffer);
        fclose(file);
        return 1;
    }

    // Reverse the bytes
    for (long i = 0; i < file_size / 2; i++) {
        unsigned char temp = buffer[i];
        buffer[i] = buffer[file_size - 1 - i];
        buffer[file_size - 1 - i] = temp;
    }

    // Write the reversed bytes back to the file
    rewind(file);
    if (fwrite(buffer, 1, file_size, file) != file_size) {
        perror("Error writing file");
        free(buffer);
        fclose(file);
        return 1;
    }

    // Truncate the file in case the reversed content is shorter
    ftruncate(fileno(file), file_size);

    free(buffer);
    fclose(file);

    return 0;
}
