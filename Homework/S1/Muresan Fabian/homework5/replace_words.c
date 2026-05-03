#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    char *word1 = argv[1];
    char *word2 = argv[2];
    
    FILE *file = fopen(argv[3], "r");
    if (!file) {
        perror("Error opening file");
        return 1;
    }

    char *line = NULL;
    size_t len = 0;
    size_t w1_len = strlen(word1);

    while (getline(&line, &len, file) != -1) {
        char *current_pos = line;
        char *next_occurrence;
        while ((next_occurrence = strstr(current_pos, word1)) != NULL) {
            fwrite(current_pos, 1, next_occurrence - current_pos, stdout);
            printf("%s", word2);
            current_pos = next_occurrence + w1_len;
        }
        
        printf("%s", current_pos);
    }

    free(line);
    fclose(file);
    
    return 0;
}