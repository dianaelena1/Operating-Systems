#include <stdio.h>
#include <ctype.h>

int main() {
    FILE *file;
    char filename[] = "input.txt"; // Numele fișierului tău
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

    if (digit_count > 0 || (line_number == 1 && !isdigit(ch))) {
         if (line_number > 0 && ftell(file) > 0) {
         }
    }

    fclose(file);
    return 0;
}