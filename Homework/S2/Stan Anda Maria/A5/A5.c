#include <stdio.h>
#include <ctype.h>

int main() {
    FILE *file;
    char filename[] = "input.txt";
    int ch;
    int digit_count = 0;
    int line_number = 1;

    file = fopen(filename, "r");

    if (file == NULL) {
        perror("Eroare la deschiderea fisierului");
        return 1;
    }

    while ((ch = fgetc(file)) != EOF) {
        if (isdigit(ch)) {
            digit_count++;
        }

        if (ch == '\n') {
            printf("Linia %d are %d cifre.\n", line_number, digit_count);
            digit_count = 0;
            line_number++;
        }
    }

    if (ftell(file) > 0) {
            if (digit_count > 0) {
                printf("Linia %d are %d cifre.\n", line_number, digit_count);
            } else if (line_number == 1) {
                printf("Linia %d are 0 cifre.\n", line_number);
            }
        }

    fclose(file);
    return 0;
}