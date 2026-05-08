#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int is_perfect(int num) {
    if (num <= 1) return 0;
    
    int sum = 0;
    for (int i = 1; i <= num / 2; i++) {
        if (num % i == 0) {
            sum += i;
        }
    }
    return sum == num;
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        printf("Usage: %s <N> <num_processes>\n", argv[0]);
        return 1;
    }

    int N = atoi(argv[1]);
    int num_processes = atoi(argv[2]);

    if (N <= 0 || num_processes <= 0) {
        printf("Error: N and num_processes must be positive integers.\n");
        return 1;
    }

    for (int i = 0; i < num_processes; i++) {
        pid_t pid = fork(); 

        if (pid == -1) {
            perror("fork() error\n");
            exit(EXIT_FAILURE); 
        } 
        else if (pid == 0) {
            for (int j = i + 1; j < N; j += num_processes) {
                if (is_perfect(j)) {
                    printf("[PID %d] Found perfect number: %d\n", getpid(), j);
                }
            }
            
            exit(EXIT_SUCCESS); 
        }
    }

    for (int i = 0; i < num_processes; i++) {
        wait(0); 
    }

    printf("All child processes have finished computing.\n");
    return 0;
}
