#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_SIZE 1024

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <file1> <file2>\n", argv[0]);
        return 1;
    }

    FILE *f1 = fopen(argv[1], "r");
    FILE *f2 = fopen(argv[2], "r");

    if (f1 == NULL || f2 == NULL) {
        perror("Error opening files");
        return 1;
    }

    char line1[MAX_LINE_SIZE];
    char line2[MAX_LINE_SIZE];

    char *ptr1 = fgets(line1, MAX_LINE_SIZE, f1);
    char *ptr2 = fgets(line2, MAX_LINE_SIZE, f2);

    while (ptr1 != NULL && ptr2 != NULL) {
        if (strcmp(line1, line2) < 0) {
            printf("%s", line1);
            ptr1 = fgets(line1, MAX_LINE_SIZE, f1);
        } else {
            printf("%s", line2);
            ptr2 = fgets(line2, MAX_LINE_SIZE, f2);
        }
    }

    while (ptr1 != NULL) {
        printf("%s", line1);
        ptr1 = fgets(line1, MAX_LINE_SIZE, f1);
    }

    while (ptr2 != NULL) {
        printf("%s", line2);
        ptr2 = fgets(line2, MAX_LINE_SIZE, f2);
    }
    printf("\n");
    fclose(f1);
    fclose(f2);

    return 0;
}