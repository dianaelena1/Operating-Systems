#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <sys/wait.h>

int is_alphanumeric_line(const char *line) {
    for (int i = 0; line[i] != '\0' && line[i] != '\n'; i++) {
        if (!isalnum(line[i])) return 0;
    }
    return 1;
}

char transform_vowel(char c) {
    switch (tolower(c)) {
        case 'a': return '1';
        case 'e': return '2';
        case 'i': return '3';
        case 'o': return '4';
        case 'u': return '5';
        default: return c;
    }
}

int main() {
    int pipe13[2]; 
    int pipe32[2];

    if (pipe(pipe13) == -1 || pipe(pipe32) == -1) {
        perror("Pipe failed");
        return 1;
    }


    if (fork() == 0) {
        close(pipe13[0]); 
        close(pipe32[0]); 
        close(pipe32[1]);

        char buffer[1024];
        while (fgets(buffer, sizeof(buffer), stdin)) {
            write(pipe13[1], buffer, strlen(buffer));
        }
        close(pipe13[1]);
        exit(0);
    }

    
    if (fork() == 0) {
        close(pipe13[1]);
        close(pipe32[0]);

        FILE *in = fdopen(pipe13[0], "r");
        char buffer[1024];
        while (fgets(buffer, sizeof(buffer), in)) {
            if (is_alphanumeric_line(buffer)) {
                write(pipe32[1], buffer, strlen(buffer));
            }
        }
        fclose(in);
        close(pipe32[1]);
        exit(0);
    }


    if (fork() == 0) {
        close(pipe13[0]);
        close(pipe13[1]);
        close(pipe32[1]);

        char c;
        while (read(pipe32[0], &c, 1) > 0) {
            putchar(transform_vowel(c));
        }
        close(pipe32[0]);
        exit(0);
    }

    close(pipe13[0]);
    close(pipe13[1]);
    close(pipe32[0]);
    close(pipe32[1]);

    for (int i = 0; i < 3; i++) wait(NULL);

    return 0;
}