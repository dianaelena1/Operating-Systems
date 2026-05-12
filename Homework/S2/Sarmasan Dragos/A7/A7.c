#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void factorize(int n, int start_divisor) {
    if (n <= 1) return;

    for (int i = start_divisor; i <= n; i++) {
        if (n % i == 0) {
            int multiplicity = 0;
            
            while (n % i == 0) {
                multiplicity++;
                n /= i;
            }
            
            printf("[PID: %d] Divisor: %d, Multiplicity: %d\n", getpid(), i, multiplicity);

            // launch child process for remaining factorization
            if (n > 1) {
                pid_t pid = fork();
                
                if (pid < 0) {
                    perror("Fork failed");
                    exit(1);
                } else if (pid == 0) {
                    // Child process handles the remaining factored number
                    factorize(n, i + 1);
                    exit(0); 
                } else {
                    // Parent waits for the child to complete the chain
                    wait(NULL);
                }
            }

            break; 
        }
    }
}

int main(int argc, char *argv[]) {
    int N = atoi(argv[1]);
    
    if (N <= 1) {
        printf("Number must be >1 \n");
        return 1;
    }

    factorize(N, 2);

    return 0;
}