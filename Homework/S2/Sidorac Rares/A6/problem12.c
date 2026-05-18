#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int divide_and_sum(int arr[], int start, int end) {
    if (start == end) {
        return arr[start];
    }

    int mid = start + (end - start) / 2;


    pid_t pid_left = fork();
    if (pid_left == 0) {
        int left_sum = divide_and_sum(arr, start, mid);

        exit(left_sum);
    }


    pid_t pid_right = fork();
    if (pid_right == 0) {
        int right_sum = divide_and_sum(arr, mid + 1, end);

        exit(right_sum);
    }


    int status_left, status_right;


    waitpid(pid_left, &status_left, 0);
    waitpid(pid_right, &status_right, 0);


    int left_res = WEXITSTATUS(status_left);
    int right_res = WEXITSTATUS(status_right);

    return left_res + right_res;
}

int main() {
    int arr[] = {1,2,3,4,5,6,8,9,10,11,12,13}; 
    int n = sizeof(arr) / sizeof(arr[0]);

    int total_sum = divide_and_sum(arr, 0, n - 1);
    printf("Total Sum: %d\n", total_sum);

    return 0;
}
