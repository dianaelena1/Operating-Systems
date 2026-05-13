#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_NUMBERS 100

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <input_file>\n", argv[0]);
        fprintf(stderr, "Example: %s numbers.txt\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (file == NULL)
    {
        perror("Error opening file");
        return 1;
    }

    int numbers[MAX_NUMBERS];
    int n = 0;

    while (fscanf(file, "%d", &numbers[n]) == 1 && n < MAX_NUMBERS)
    {
        n++;
    }

    fclose(file);

    if (n == 0)
    {
        fprintf(stderr, "Error: No numbers read from file.\n");
        return 1;
    }

    printf("Read %d numbers from file: ", n);
    for (int i = 0; i < n; i++)
        printf("%d ", numbers[i]);
    printf("\n\n");

    int pipes[n][2];
    for (int i = 0; i < n; i++)
    {
        if (pipe(pipes[i]) == -1)
        {
            perror("pipe() error");
            exit(EXIT_FAILURE);
        }
    }

    int pids[n];
    for (int i = 0; i < n; i++)
    {
        pids[i] = fork();

        if (pids[i] == -1)
        {
            perror("fork() error");
            exit(EXIT_FAILURE);
        }

        if (pids[i] == 0) 
        {
            close(pipes[i][0]);

            long long cube = (long long)numbers[i] * numbers[i] * numbers[i];

            printf("[Child PID: %d] Number: %d, Cube: %lld\n", getpid(), numbers[i], cube);

            write(pipes[i][1], &cube, sizeof(long long));

            close(pipes[i][1]);

            exit(EXIT_SUCCESS);
        }
        {
            close(pipes[i][1]);
        }
    }

    long long sum = 0;

    for (int i = 0; i < n; i++)
    {
        long long cube;
        ssize_t bytes_read = read(pipes[i][0], &cube, sizeof(long long));

        if (bytes_read == sizeof(long long))
        {
            printf("[Parent] Received cube from child %d: %lld\n", i, cube);
            sum += cube;
        }

        close(pipes[i][0]);

        int status;
        wait(&status);
    }

    printf("Sum of cubes: %lld\n", sum);

    return 0;
}
