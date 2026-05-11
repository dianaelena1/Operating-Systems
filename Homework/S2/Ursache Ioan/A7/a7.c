/*
pb 3.   Problem Implement the following structure of processes,
        in which the vertices indicate the communication between processes using pipes:
    Process 1: write to 3 what is read from stdin
    Process 2: read from 3 and replace all vowels with digits (aeiou->12345)
    Process 3: read from 1 and write to 2 only alphanumeric lines (addition: no spaces, either)
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <sys/wait.h>

int main() {
    int p1_to_p3[2]; // process 1 ~ process 3
    int p3_to_p2[2]; // process 3 ~ process 2

    // Pipes
    if (pipe(p1_to_p3) == -1 || pipe(p3_to_p2) == -1) {
        perror("Pipe failed");
        exit(EXIT_FAILURE);
    }

    // Child Process 1
    if (fork() == 0) {
        close(p1_to_p3[0]);
        close(p3_to_p2[0]);
        close(p3_to_p2[1]);

        char buffer[1024];
        while (fgets(buffer, sizeof(buffer), stdin)) {
            write(p1_to_p3[1], buffer, strlen(buffer));
        }

        close(p1_to_p3[1]); // signals EOF to Process 3
        exit(0);
    }

    // Child Process 3
    if (fork() == 0) {
        close(p1_to_p3[1]);
        close(p3_to_p2[0]);

        FILE *stream_in = fdopen(p1_to_p3[0], "r");
        char buffer[1024];

        while (fgets(buffer, sizeof(buffer), stream_in)) {
            int is_alphanumeric = 1;
            int len = 0;

            for (int i = 0; buffer[i] != '\0' && buffer[i] != '\n'; i++) {
                if (!isalnum((unsigned char)buffer[i])) {
                    is_alphanumeric = 0;
                    break;
                }
                len++;
            }

            if (is_alphanumeric && len > 0) {
                write(p3_to_p2[1], buffer, strlen(buffer));
            }
        }

        fclose(stream_in);
        close(p3_to_p2[1]); // signals EOF to P2
        exit(0);
    }

    // Child Process 2
    if (fork() == 0) {
        close(p1_to_p3[0]);
        close(p1_to_p3[1]);
        close(p3_to_p2[1]);

        char ch;
        while (read(p3_to_p2[0], &ch, 1) > 0) {
            // Mapping: a->1, e->2, i->3, o->4, u->5
            switch (tolower((unsigned char)ch)) {
                case 'a': putchar('1'); break;
                case 'e': putchar('2'); break;
                case 'i': putchar('3'); break;
                case 'o': putchar('4'); break;
                case 'u': putchar('5'); break;
                default:  putchar(ch);  break;
            }
        }

        close(p3_to_p2[0]);
        exit(0);
    }

    // Parent
    close(p1_to_p3[0]);
    close(p1_to_p3[1]);
    close(p3_to_p2[0]);
    close(p3_to_p2[1]);

    for (int i = 0; i < 3; i++) {
        wait(NULL);
    }

    return 0;
}