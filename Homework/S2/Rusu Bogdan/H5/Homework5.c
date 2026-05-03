#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// The program main entry point allowing access to command line arguments
int main(int argc, char** argv) {
    // 1. Validate command line arguments
    if (argc != 3) {
        printf("Usage: %s <word> <filename>\n", argv[0]);
        return 1;
    }

    char* target_word = argv[1];
    char* filename = argv[2];
    int word_len = strlen(target_word);

    // 2. Open the original file for reading
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: Could not open file %s.\n", filename);
        return 1;
    }

    // 3. Open a temporary file for writing
    FILE *temp = fopen("temp_output.txt", "w");
    if (temp == NULL) {
        printf("Error: Could not create temporary file.\n");
        fclose(file);
        return 1;
    }

    char buffer[1024];

    // 4. Read the text file line by line
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        char *current_pos = buffer;
        char *match;

        // 5. Find occurrences of the target word in the current line
        while ((match = strstr(current_pos, target_word)) != NULL) {
            // Write everything up to the match character by character
            while (current_pos < match) {
                fputc(*current_pos, temp);
                current_pos++;
            }
            // Skip the target word by moving the pointer forward
            current_pos += word_len;
        }

        // Write the remaining part of the line (after the last match) to the temp file
        fputs(current_pos, temp);
    }

    // 6. Close both files
    fclose(file);
    fclose(temp);

    // 7. Delete the original file and rename the temporary file to the original filename
    remove(filename);
    rename("temp_output.txt", filename);

    printf("Successfully deleted occurrences of '%s' from %s.\n", target_word, filename);

    return 0;
}