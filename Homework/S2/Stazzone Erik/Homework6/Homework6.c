#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <x1> <x2> ... <xn>\n", argv[0]);
        return EXIT_FAILURE;
    }

    int n = argc - 1;

    int *numbers = malloc(n * sizeof(int));
    if (numbers == NULL) {
        perror("memory allocation failed");
        return EXIT_FAILURE;
    }

    for (int i = 0; i < n; i++) {
        numbers[i] = atoi(argv[i + 1]);
    }

    for (int i = 0; i < n; i++) {
        pid_t pid = fork();

        if (pid < 0) {
            perror("Fork failed");
            free(numbers);
            return EXIT_FAILURE;
        }
        if (pid == 0) {
            int sum = 0;

            for (int j = 0; j <= i; j++) {
                sum += numbers[j];
            }

            printf("Partial sum %d (calculated by PID %d): %d\n", i + 1, getpid(), sum);

            free(numbers);
            exit(EXIT_SUCCESS);
        }
    }

    for (int i = 0; i < n; i++) {
        wait(NULL);
    }

    free(numbers);
    return EXIT_SUCCESS;
}