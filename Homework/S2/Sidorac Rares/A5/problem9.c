#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
    if (argc < 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    FILE *fp = fopen(argv[1], "r");
    FILE *temp = fopen("temp.txt", "w");

    if (fp == NULL || temp == NULL) {
        printf("Error opening files.\n");
        return 1;
    }

    int num;
    while (fscanf(fp, "%d", &num) == 1) {
        if (num % 2 != 0) {
            fprintf(temp, "%d\n", num);
        }
    }

    fclose(fp);
    fclose(temp);

    remove(argv[1]);
    rename("temp.txt", argv[1]);

    return 0;
}
