#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Error: Please provide a filename\n");
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (file == NULL) {
        printf("Error opening file\n");
        return 1;
    }

    char word[256];
    
    while (fscanf(file, "%255s", word) == 1) {
        int should_delete = 0;
        
        for (int i = 2; i < argc; i++) {
            if (strcmp(word, argv[i]) == 0) {
                should_delete = 1;
                break; 
            }
        }
        
        if (!should_delete) {
            printf("%s ", word);
        }
    }

    printf("\n");
    fclose(file);
    return 0;
}