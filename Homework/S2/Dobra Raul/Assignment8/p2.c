#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <ctype.h>

#define FIFO12 "/tmp/fifo_1_2"
#define FIFO13 "/tmp/fifo_1_3"
#define FIFO14 "/tmp/fifo_1_4"
#define FIFO25 "/tmp/fifo_2_5"
#define FIFO35 "/tmp/fifo_3_5"

int compare_chars(const void *a, const void *b) {
    return (*(char *)a - *(char *)b);
}

int main() {
    mkfifo(FIFO12, 0666);
    mkfifo(FIFO13, 0666);
    mkfifo(FIFO14, 0666);
    mkfifo(FIFO25, 0666);
    mkfifo(FIFO35, 0666);

    pid_t p1, p2, p3, p4, p5;

    p1 = fork();
    if (p1 == 0) {
        char buffer[10];
        int bytes_read = read(STDIN_FILENO, buffer, 10);
        if (bytes_read > 0) {
            int fd2 = open(FIFO12, O_WRONLY);
            int fd3 = open(FIFO13, O_WRONLY);
            int fd4 = open(FIFO14, O_WRONLY);
            write(fd2, buffer, bytes_read);
            write(fd3, buffer, bytes_read);
            write(fd4, buffer, bytes_read);
            close(fd2);
            close(fd3);
            close(fd4);
        }
        exit(0);
    }

    p2 = fork();
    if (p2 == 0) {
        char buffer[10];
        int fd_in = open(FIFO12, O_RDONLY);
        int bytes_read = read(fd_in, buffer, 10);
        close(fd_in);

        if (bytes_read > 0) {
            int sum = 0;
            char out_buf[20];
            int idx = 0;
            for (int i = 0; i < bytes_read; i++) {
                if (isdigit(buffer[i])) {
                    sum += buffer[i] - '0';
                } else if (isalpha(buffer[i])) {
                    out_buf[idx++] = 'Z';
                } else {
                    out_buf[idx++] = buffer[i];
                }
            }
            idx += sprintf(out_buf + idx, "%d", sum);
            int fd_out = open(FIFO25, O_WRONLY);
            write(fd_out, out_buf, idx);
            close(fd_out);
        }
        exit(0);
    }

    p3 = fork();
    if (p3 == 0) {
        char buffer[10];
        int fd_in = open(FIFO13, O_RDONLY);
        int bytes_read = read(fd_in, buffer, 10);
        close(fd_in);

        if (bytes_read > 0) {
            int sum = 0;
            char out_buf[20];
            int idx = 0;
            for (int i = 0; i < bytes_read; i++) {
                if (isdigit(buffer[i])) {
                    sum += buffer[i] - '0';
                } else if (isalpha(buffer[i])) {
                    out_buf[idx++] = 'Z';
                } else {
                    out_buf[idx++] = buffer[i];
                }
            }
            idx += sprintf(out_buf + idx, "%d", sum);

            int fd_out = open(FIFO35, O_WRONLY);
            write(fd_out, out_buf, idx);
            close(fd_out);
        }
        exit(0);
    }

    p4 = fork();
    if (p4 == 0) {
        char buffer[10];
        int fd_in = open(FIFO14, O_RDONLY);
        int bytes_read = read(fd_in, buffer, 10);
        close(fd_in);

        if (bytes_read > 0) {
            qsort(buffer, bytes_read, sizeof(char), compare_chars);
            printf("[Proces 4] Rezultat sortat: ");
            fwrite(buffer, sizeof(char), bytes_read, stdout);
            printf("\n");
        }
        exit(0);
    }

    p5 = fork();
    if (p5 == 0) {
        char buffer[50];
        int fd25 = open(FIFO25, O_RDONLY);
        int bytes25 = read(fd25, buffer, sizeof(buffer) - 1);
        close(fd25);
        if (bytes25 > 0) {
            buffer[bytes25] = '\0';
            printf("[Proces 5] Primit de la P2: %s\n", buffer);
        }

        int fd35 = open(FIFO35, O_RDONLY);
        int bytes35 = read(fd35, buffer, sizeof(buffer) - 1);
        close(fd35);
        if (bytes35 > 0) {
            buffer[bytes35] = '\0';
            printf("[Proces 5] Primit de la P3: %s\n", buffer);
        }
        exit(0);
    }

    for (int i = 0; i < 5; i++) {
        wait(NULL);
    }

    unlink(FIFO12);
    unlink(FIFO13);
    unlink(FIFO14);
    unlink(FIFO25);
    unlink(FIFO35);

    return 0;
}