#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    FILE *originalFile = fopen(argv[1], "r");
    if (originalFile == NULL) {
        printf("Error: Could not open the file %s.\n", argv[1]);
        return 1;
    }

    FILE *tempFile = fopen("temp.txt", "w");
    if (tempFile == NULL) {
        printf("Could not create temporary file.\n");
        fclose(originalFile); 
        return 1;
    }

    int number;
    while (fscanf(originalFile, "%d", &number) == 1) {
        if (number % 2 != 0) {
            fprintf(tempFile, "%d ", number);
        }
    }

    fclose(originalFile);
    fclose(tempFile);

    remove(argv[1]);
    rename("temp.txt", argv[1]);

    printf("Even numbers deleted successfully.\n"); 

    return 0; 
}
