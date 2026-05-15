#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <ctype.h>
#include <string.h>

int cmp_char(const void *a, const void *b) {
    return (*(char*)a - *(char*)b);
}

void process_2_3(int fd_in, int fd_out, int id) {
    char buf[11];
    int n;
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
        
        write(fd_out, out_buf, len);
    }
}

void process_4(int fd_in) {
    char *buf = NULL;
    int total = 0;
    char temp[128];
    int n;
    
    while ((n = read(fd_in, temp, sizeof(temp))) > 0) {
        buf = realloc(buf, total + n);
        memcpy(buf + total, temp, n);
        total += n;
    }
    
    if (total > 0) {
        qsort(buf, total, sizeof(char), cmp_char);
        printf("[P4] Sorted output: %.*s\n", total, buf);
        free(buf);
    }
}

void process_5(int fd_in) {
    char buf[128];
    int n;
    while ((n = read(fd_in, buf, sizeof(buf))) > 0) {
        printf("[P5] Received: %.*s", n, buf);
    }
}

int main() {
    int p1_2[2], p1_3[2], p1_4[2], p_to_5[2];
    
    if (pipe(p1_2) == -1 || pipe(p1_3) == -1 || pipe(p1_4) == -1 || pipe(p_to_5) == -1) {
        perror("Pipe creation failed");
        exit(1);
    }

    if (fork() == 0) {
        close(p1_2[1]); 
        close(p1_3[0]); close(p1_3[1]);
        close(p1_4[0]); close(p1_4[1]);
        close(p_to_5[0]); 

        process_2_3(p1_2[0], p_to_5[1], 2);

        close(p1_2[0]);
        close(p_to_5[1]);
        exit(0);
    }

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

    if (fork() == 0) {
        close(p1_4[1]); 
        close(p1_2[0]); close(p1_2[1]);
        close(p1_3[0]); close(p1_3[1]);
        close(p_to_5[0]); close(p_to_5[1]); 

        process_4(p1_4[0]);

        close(p1_4[0]);
        exit(0);
    }

    if (fork() == 0) {
        close(p_to_5[1]); 
        close(p1_2[0]); close(p1_2[1]);
        close(p1_3[0]); close(p1_3[1]);
        close(p1_4[0]); close(p1_4[1]);

        process_5(p_to_5[0]);

        close(p_to_5[0]);
        exit(0);
    }

    close(p1_2[0]);
    close(p1_3[0]);
    close(p1_4[0]);
    close(p_to_5[0]); close(p_to_5[1]);

    char buf[10];
    int n;
    
    while ((n = read(STDIN_FILENO, buf, 10)) > 0) {
        write(p1_2[1], buf, n);
        write(p1_3[1], buf, n);
        write(p1_4[1], buf, n);
    }

    close(p1_2[1]);
    close(p1_3[1]);
    close(p1_4[1]);

    for (int i = 0; i < 4; i++) {
        wait(NULL);
    }

    return 0;
}
