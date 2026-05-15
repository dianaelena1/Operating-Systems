#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <ctype.h>
#include <string.h>

// Comparison function for qsort in Process 4
int cmp_char(const void *a, const void *b) {
    return (*(char*)a - *(char*)b);
}

void process_2_3(int fd_in, int fd_out, int id) {
    char buf[11];
    int n;
    // Reads chunks sent by Process 1 [cite: 30]
    while ((n = read(fd_in, buf, 10)) > 0) {
        int sum = 0;
        for (int i = 0; i < n; i++) {
            if (isalpha(buf[i])) {
                buf[i] = 'Z';
            } else if (isdigit(buf[i])) {
                sum += buf[i] - '0';
            }
        }
        buf[n] = '\0';
        char out_buf[128];
        int len = snprintf(out_buf, sizeof(out_buf), "[P%d] String: %s | Sum of digits: %d\n", id, buf, sum);
        
        // Writes the modified string and sum to Process 5 [cite: 38]
        write(fd_out, out_buf, len);
    }
}

void process_4(int fd_in) {
    char *buf = NULL;
    int total = 0;
    char temp[128];
    int n;
    
    // Read all input until EOF
    while ((n = read(fd_in, temp, sizeof(temp))) > 0) {
        buf = realloc(buf, total + n);
        memcpy(buf + total, temp, n);
        total += n;
    }
    
    // Sort and print the final result
    if (total > 0) {
        qsort(buf, total, sizeof(char), cmp_char);
        printf("[P4] Sorted output: %.*s\n", total, buf);
        free(buf);
    }
}

void process_5(int fd_in) {
    char buf[128];
    int n;
    // Prints everything it receives from P2 and P3
    while ((n = read(fd_in, buf, sizeof(buf))) > 0) {
        // Outputting exactly what is received
        printf("[P5] Received: %.*s", n, buf);
    }
}

int main() {
    // Array creation for pipe descriptors [cite: 13]
    int p1_2[2], p1_3[2], p1_4[2], p_to_5[2];
    
    // Create the pipes [cite: 11, 19]
    if (pipe(p1_2) == -1 || pipe(p1_3) == -1 || pipe(p1_4) == -1 || pipe(p_to_5) == -1) {
        perror("Pipe creation failed");
        exit(1);
    }

    // --- Create Process 2 ---
    if (fork() == 0) {
        // Close unused ends [cite: 114]
        close(p1_2[1]); // P2 reads from p1_2, doesn't write
        close(p1_3[0]); close(p1_3[1]);
        close(p1_4[0]); close(p1_4[1]);
        close(p_to_5[0]); // P2 writes to p_to_5, doesn't read

        process_2_3(p1_2[0], p_to_5[1], 2);

        // Close used ends after finishing
        close(p1_2[0]);
        close(p_to_5[1]);
        exit(0);
    }

    // --- Create Process 3 ---
    if (fork() == 0) {
        close(p1_3[1]); 
        close(p1_2[0]); close(p1_2[1]);
        close(p1_4[0]); close(p1_4[1]);
        close(p_to_5[0]); 

        process_2_3(p1_3[0], p_to_5[1], 3);

        close(p1_3[0]);
        close(p_to_5[1]);
        exit(0);
    }

    // --- Create Process 4 ---
    if (fork() == 0) {
        close(p1_4[1]); 
        close(p1_2[0]); close(p1_2[1]);
        close(p1_3[0]); close(p1_3[1]);
        close(p_to_5[0]); close(p_to_5[1]); // P4 doesn't talk to P5

        process_4(p1_4[0]);

        close(p1_4[0]);
        exit(0);
    }

    // --- Create Process 5 ---
    if (fork() == 0) {
        close(p_to_5[1]); 
        close(p1_2[0]); close(p1_2[1]);
        close(p1_3[0]); close(p1_3[1]);
        close(p1_4[0]); close(p1_4[1]);

        process_5(p_to_5[0]);

        close(p_to_5[0]);
        exit(0);
    }

    // --- Process 1 (Parent) ---
    // Close read ends and unrelated pipes
    close(p1_2[0]);
    close(p1_3[0]);
    close(p1_4[0]);
    close(p_to_5[0]); close(p_to_5[1]);

    char buf[10];
    int n;
    
    // Read from standard input in chunks of 10 bytes and write to all 3 outputs 
    while ((n = read(STDIN_FILENO, buf, 10)) > 0) {
        write(p1_2[1], buf, n);
        write(p1_3[1], buf, n);
        write(p1_4[1], buf, n);
    }

    // Close write ends so children can receive EOF [cite: 33]
    close(p1_2[1]);
    close(p1_3[1]);
    close(p1_4[1]);

    // Wait for all 4 child processes to finish [cite: 108]
    for (int i = 0; i < 4; i++) {
        wait(NULL);
    }

    return 0;
}
