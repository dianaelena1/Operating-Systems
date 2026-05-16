#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    int arr[] = {2, 3, 7, 4, 6, 8, 10};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Original array: ");
    for(int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n\n");

    for (int i = 0; i < n; i++) {
        pid_t pid = fork(); // Create a new process

        if (pid < 0) {
            perror("Fork failed");
            exit(1);
        }
        else if (pid == 0) {
            // CHILD PROCESS
            int partial_sum = 0;

            // Calculate the sum from index 0 up to the current index 'i'
            for (int j = 0; j <= i; j++) {
                partial_sum += arr[j];
            }

            printf("Child Process [PID: %d] computed sum up to index %d: %d\n", getpid(), i, partial_sum);

            exit(0);
        }
    }

    // PARENT PROCESS
    for (int i = 0; i < n; i++) {
        wait(NULL);
    }

    printf("\nAll partial sums computed successfully by child processes.\n");

    return 0;
}