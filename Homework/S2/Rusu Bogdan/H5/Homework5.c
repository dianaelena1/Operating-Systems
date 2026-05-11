#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char** argv) {
    if (argc != 3) { 
        printf("Usage: %s <word> <filename>\n", argv[0]);
        return 1;
    }

    char* target_word = argv[1];
    char* filename = argv[2];
    int word_len = strlen(target_word);

    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: Could not open file %s.\n", filename);
        return 1;
    }

    FILE *temp = fopen("temp_output.txt", "w");
    if (temp == NULL) {
        printf("Error: Could not create temporary file.\n");
        fclose(file);
        return 1;
    }

    char buffer[1024];

    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        char *current_pos = buffer;
        char *match;

        while ((match = strstr(current_pos, target_word)) != NULL) {
            while (current_pos < match) {
                fputc(*current_pos, temp);
                current_pos++;
            }
            current_pos += word_len;
        } 

        fputs(current_pos, temp);
    }

    fclose(file);
    fclose(temp);

    remove(filename);
    rename("temp_output.txt", filename);

    printf("Successfully deleted occurrences of '%s' from %s.\n", target_word, filename);

    return 0;
}