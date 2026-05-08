#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int parallel_sum(int arr[], int start, int end) {
 
    if (start == end) {
        return arr[start];
    }

    int mid = start + (end - start) / 2;
    int fd_left[2], fd_right[2];

   
    if (pipe(fd_left) == -1 || pipe(fd_right) == -1) {
        perror("Pipe failed");
        exit(1);
    }

    pid_t pid_l = fork();
    if (pid_l == 0) {
        close(fd_left[0]); 
        int left_sum = parallel_sum(arr, start, mid);
        write(fd_left[1], &left_sum, sizeof(int));
        close(fd_left[1]);
        exit(0);
    }

    pid_t pid_r = fork();
    if (pid_r == 0) {
        close(fd_right[0]); 
        int right_sum = parallel_sum(arr, mid + 1, end);
        write(fd_right[1], &right_sum, sizeof(int));
        close(fd_right[1]);
        exit(0);
    }

    int left_res, right_res;
    
    close(fd_left[1]); 
    close(fd_right[1]);

    read(fd_left[0], &left_res, sizeof(int));
    read(fd_right[0], &right_res, sizeof(int));

    close(fd_left[0]);
    close(fd_right[0]);

    // wait for children 
    waitpid(pid_l, NULL, 0);
    waitpid(pid_r, NULL, 0);

    return left_res + right_res;
}

int main() {
    int data[] = {1, 2, 3, 4, 5, 6, 7, 8};
    int n = sizeof(data) / sizeof(data[0]);

    int total = parallel_sum(data, 0, n - 1);
    printf("The final sum is: %d\n", total);

    return 0;
}