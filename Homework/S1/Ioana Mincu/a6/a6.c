#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int main() {
    int numbers[] = {1, 2, 3, 4, 5};
    int n = sizeof(numbers) / sizeof(numbers[0]);

    int fd[2];
    int total_sum = 0;

    if (pipe(fd) == -1) {
        perror("Pipe failed");
        return 1;
    }

    printf("Parent: Starting %d child processes...\n", n);

    for (int i = 0; i < n; i++) {
        pid_t pid = fork();

        if (pid < 0) {
            perror("Fork failed");
            return 1;
        }

        if (pid == 0) {
            close(fd[0]);

            int val = numbers[i];
            int cube = val * val * val;

            printf("Child %d: Calculated %d^3 = %d\n", i + 1, val, cube);

            write(fd[1], &cube, sizeof(cube));

            close(fd[1]);
            exit(0);
        }
    }

    close(fd[1]);

    int received_cube;
    for (int i = 0; i < n; i++) {
        read(fd[0], &received_cube, sizeof(received_cube));
        total_sum += received_cube;
    }

    for (int i = 0; i < n; i++) {
        wait(NULL);
    }

    close(fd[0]);

    printf("Final result: The sum of cubes is %d\n", total_sum);

    return 0;
}