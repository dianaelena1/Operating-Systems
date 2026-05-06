/*
We have a file that contains N integer numbers.
Using two types of processes (one for determining the minimum and the other to determine the maximum value from an array),
write a program that determines the k-th element in increasing order of the integer array, without sorting the array.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <limits.h>

#define MAX_VAL 10000

int find_min_index(int arr[], int n) {
    int min_idx = 0;
    for (int i = 1; i < n; i++) {
        if (arr[i] < arr[min_idx]) {
            min_idx = i;
        }
    }
    return min_idx;
}

int find_max_value(int arr[], int n) {
    int max_val = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > max_val) {
            max_val = arr[i];
        }
    }
    return max_val;
}

int main() {
    int n, k;
    int arr[MAX_VAL];
    FILE *file = fopen("data.txt", "r");

    if (!file) {
        perror("Error opening file");
        return 1;
    }

    fscanf(file, "%d", &n);
    for (int i = 0; i < n; i++) {
        fscanf(file, "%d", &arr[i]);
    }
    fclose(file);

    printf("Enter k: ");
    scanf("%d", &k);

    if (k > n || k <= 0) {
        printf("Invalid k.\n");
        return 1;
    }

    int pipe_fd[2];
    int result_val;

    if (pipe(pipe_fd) == -1) return 1;
    pid_t pid_max = fork();

    if (pid_max == 0) {
        close(pipe_fd[0]);
        int max = find_max_value(arr, n);
        write(pipe_fd[1], &max, sizeof(int));
        close(pipe_fd[1]);
        exit(0);
    } else {
        int global_max;
        close(pipe_fd[1]);
        read(pipe_fd[0], &global_max, sizeof(int));
        close(pipe_fd[0]);
        wait(NULL);

        int neutralizer = global_max + 1;

        for (int i = 0; i < k; i++) {
            if (pipe(pipe_fd) == -1) return 1;
            pid_t pid_min = fork();

            if (pid_min == 0) {
                close(pipe_fd[0]);
                int min_idx = find_min_index(arr, n);
                write(pipe_fd[1], &min_idx, sizeof(int));
                close(pipe_fd[1]);
                exit(0);
            } else {
                int min_idx;
                close(pipe_fd[1]);
                read(pipe_fd[0], &min_idx, sizeof(int));
                close(pipe_fd[0]);
                wait(NULL);

                result_val = arr[min_idx];
                arr[min_idx] = neutralizer;
            }
        }

        printf("The %d-th element in increasing order is: %d\n", k, result_val);
    }

    return 0;
}