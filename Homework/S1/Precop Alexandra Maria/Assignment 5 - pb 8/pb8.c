#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
    if(argc < 2){
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    FILE *inputFile = fopen(argv[1], "r");
    if (inputFile == NULL){
            perror("Error opening file");
            return 1;
        }
    FILE *tempFile = fopen("temp.txt", "w");

    int number;
    while(fscanf(inputFile, "%d", &number)!=EOF){
        if(number %2!=0){
            fprintf(tempFile,"%d\n", number);
        }
    }

    fclose(inputFile);
    fclose(tempFile);

    remove(argv[1]);
    rename("temp.txt", argv[1]);

    printf("Even numbers deleted succesfully from %s\n", argv[1]);
    return 0;
}