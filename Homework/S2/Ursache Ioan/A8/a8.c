/*
pb 2.	Implement the following structure of processes,
		in which the vertices indicate the communication between processes using pipes:
	Process 1: read from stdin 10 bytes and write to each process 1,2 and 4 
	Processes 2, 3: add digits and replace letters with ‘Z’ 
	Process 4: sort the result and print it 
	Process 5: print the information received by pipes
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <ctype.h>
#include <sys/wait.h>

#define FIFO12 "/tmp/fifo12"
#define FIFO13 "/tmp/fifo13"
#define FIFO14 "/tmp/fifo14"
#define FIFO25 "/tmp/fifo25"
#define FIFO35 "/tmp/fifo35"

void sort_bytes(char *arr, int n) {
    for (int i = 0; i < n - 1; i++)
        for (int j = i + 1; j < n; j++)
            if (arr[i] > arr[j]) {
              char aux = arr[i];
              arr[i] = arr[j];
              arr[j] = aux;
            }
}

int main() {
    // FIFOs
    mkfifo(FIFO12, 0666); mkfifo(FIFO13, 0666); mkfifo(FIFO14, 0666);
    mkfifo(FIFO25, 0666);
    mkfifo(FIFO35, 0666);

    // Child Process 1
    if (fork() == 0) {
        char buf[11] = {0};
        int fd2 = open(FIFO12, O_WRONLY), fd3 = open(FIFO13, O_WRONLY), fd4 = open(FIFO14, O_WRONLY);

        printf("[P1] Enter 10 characters: ");
        if (fgets(buf, sizeof(buf), stdin) != NULL) {
            // buffer integrity
            buf[strcspn(buf, "\n")] = 0;
            while(strlen(buf) < 10) strcat(buf, " ");
        }

        write(fd2, buf, 10);
        write(fd3, buf, 10);
        write(fd4, buf, 10);

        close(fd2); close(fd3); close(fd4);
        exit(0);
    }

    // Child Processes 2 & 3
    for (int i = 0; i < 2; i++) {
        if (fork() == 0) {
            char buf[11] = {0};
            char out_msg[128];
            int sum = 0;
            int in_fd = open((i == 0) ? FIFO12 : FIFO13, O_RDONLY);
            int out_fd = open((i == 0) ? FIFO25 : FIFO35, O_WRONLY);

            read(in_fd, buf, 10);
            // String processing
            for (int j = 0; j < 10; j++) {
                if (isdigit((unsigned char)buf[j])) sum += (buf[j] - '0');
                if (isalpha((unsigned char)buf[j])) buf[j] = 'Z';
            }

            int len = sprintf(out_msg, "[P%d] Transformed: %s | Digit Sum: %d\n", (i + 2), buf, sum);
            write(out_fd, out_msg, len);

            close(in_fd); close(out_fd);
            exit(0);
        }
    }

    // Child Process 4
    if (fork() == 0) {
        char buf[11] = {0};
        int fd = open(FIFO14, O_RDONLY);
        read(fd, buf, 10);
        // Sort the 10 bytes
        sort_bytes(buf, 10);
        printf("[P4] Sorted Result: %s\n", buf);
        close(fd);
        exit(0);
    }

    // Child Process 5
    if (fork() == 0) {
        char msg[128];
        int fd25 = open(FIFO25, O_RDONLY), fd35 = open(FIFO35, O_RDONLY);
        int n;
        // Display info received from pipe
        while ((n = read(fd25, msg, sizeof(msg) - 1)) > 0) { write(1, msg, n); }
        while ((n = read(fd35, msg, sizeof(msg) - 1)) > 0) { write(1, msg, n); }
        close(fd25); close(fd35);
        exit(0);
    }

    // Parent Process
    for (int i = 0; i < 5; i++) wait(NULL);
    unlink(FIFO12); unlink(FIFO13); unlink(FIFO14); unlink(FIFO25); unlink(FIFO35);
    return 0;
}

