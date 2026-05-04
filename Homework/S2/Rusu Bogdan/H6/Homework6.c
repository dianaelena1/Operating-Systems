#include <stdio.h>
#include <stdlib.h>

// Using the recommended main function header to access command line arguments
int main(int argc, char** argv) {
    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    // Open the text file for reading
    FILE *fp = fopen(argv[1], "r");
    if (fp == NULL) {
        printf("Error: Cannot open file '%s'.\n", argv[1]);
        return 1;
    }

    int c;
    int in_word = 0;       // State tracker: 1 if currently inside a word, 0 otherwise
    int word_count = 0;    // Words on the current line
    int line_number = 1;   // Current line number

    // Read file character by character until End Of File
    while ((c = fgetc(fp)) != EOF) {
        // Check for whitespace characters (space, tab, newline, carriage return)
        if (c == ' ' || c == '\t' || c == '\n' || c == '\r') {
            in_word = 0; // We have exited a word

            // If the whitespace is a newline, print the count and reset
            if (c == '\n') {
                printf("Line %d: %d words\n", line_number, word_count);
                word_count = 0;
                line_number++;
            }
        } else {
            // If it's not a whitespace and we weren't already in a word, a new word started
            if (in_word == 0) {
                in_word = 1;
                word_count++;
            }
        }
    }

    // Handle the final line in case the file does not end with a newline character
    if (in_word || word_count > 0) {
        printf("Line %d: %d words\n", line_number, word_count);
    }

    // Close the file stream
    fclose(fp);

    return 0;
}