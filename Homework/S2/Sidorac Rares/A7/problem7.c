#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <sys/wait.h>
#include <sys/types.h>

#define MAX_LINE_LEN 256


int is_alphanumeric_line(const char *str) {
    int count = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == '\n' || str[i] == '\r') continue;
        count++;
        if (!isalnum((unsigned char)str[i]) && !isspace((unsigned char)str[i])) {
            return 0; 
        }
    }
    return count > 0; 
}


int has_no_letters(const char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (isalpha((unsigned char)str[i])) {
            return 0; // Found a letter
        }
    }
    return 1;
}

int main() {
    int p1_to_p2[2]; 
    int p1_to_p3[2]; 


    if (pipe(p1_to_p2) == -1 || pipe(p1_to_p3) == -1) {
        perror("Pipe creation failed");
        exit(EXIT_FAILURE);
    }


    pid_t pid2 = fork();
    if (pid2 == -1) {
        perror("Fork for Process 2 failed");
        exit(EXIT_FAILURE);
    }

    if (pid2 == 0) { 

        close(p1_to_p2[1]); 
        close(p1_to_p3[0]); 
        close(p1_to_p3[1]);

        int p2_to_p4[2]; 
        if (pipe(p2_to_p4) == -1) {
            perror("Pipe P2 to P4 failed");
            exit(EXIT_FAILURE);
        }

        pid_t pid4 = fork();
        if (pid4 == -1) {
            perror("Fork for Process 4 failed");
            exit(EXIT_FAILURE);
        }

        if (pid4 == 0) {

            close(p1_to_p2[0]);
            close(p2_to_p4[1]); 

            FILE *f_in4 = fdopen(p2_to_p4[0], "r");
            char buf4[MAX_LINE_LEN];

            // Read from Process 2 and print to stdout
            while (fgets(buf4, sizeof(buf4), f_in4)) {
                printf("[Process 4] %s", buf4);
                fflush(stdout);
            }

            fclose(f_in4);
            exit(EXIT_SUCCESS);
        } else {

            close(p2_to_p4[0]); 

            FILE *f_in2 = fdopen(p1_to_p2[0], "r");
            FILE *f_out2 = fdopen(p2_to_p4[1], "w");
            char buf2[MAX_LINE_LEN];


            while (fgets(buf2, sizeof(buf2), f_in2)) {

                for (int i = 0; buf2[i] != '\0'; i++) {
                    if (isdigit((unsigned char)buf2[i])) {
                        buf2[i] = '_';
                    }
                }

                fprintf(f_out2, "%s", buf2);
                fflush(f_out2);
            }

            fclose(f_in2);
            fclose(f_out2);
            wait(NULL);
            exit(EXIT_SUCCESS);
        }
    }


    pid_t pid3 = fork();
    if (pid3 == -1) {
        perror("Fork for Process 3 failed");
        exit(EXIT_FAILURE);
    }

    if (pid3 == 0) {

        close(p1_to_p2[0]);
        close(p1_to_p2[1]);
        close(p1_to_p3[1]); 

        FILE *f_in3 = fdopen(p1_to_p3[0], "r");
        char buf3[MAX_LINE_LEN];

        while (fgets(buf3, sizeof(buf3), f_in3)) {
            printf("[Process 3] %s", buf3);
            fflush(stdout);
        }

        fclose(f_in3);
        exit(EXIT_SUCCESS);
    }


    close(p1_to_p2[0]);
    close(p1_to_p3[0]);

    FILE *f_out_p2 = fdopen(p1_to_p2[1], "w");
    FILE *f_out_p3 = fdopen(p1_to_p3[1], "w");
    char input_buf[MAX_LINE_LEN];

    printf("Process 1: Enter lines of text (Press Ctrl+D/EOF to stop):\n");
    while (fgets(input_buf, sizeof(input_buf), stdin)) {
        

        if (is_alphanumeric_line(input_buf)) {
            fprintf(f_out_p2, "%s", input_buf);
            fflush(f_out_p2);
        }
        
        if (has_no_letters(input_buf)) {
            fprintf(f_out_p3, "%s", input_buf);
            fflush(f_out_p3);
        }
    }

    fclose(f_out_p2);
    fclose(f_out_p3);


    wait(NULL);
    wait(NULL);

    printf("Process 1: All child processes finished. Exiting.\n");
    return 0;
}