#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int pipe_12[2];   
    int pipe_to_4[2]; 

    if (pipe(pipe_12) == -1 || pipe(pipe_to_4) == -1) {
        perror("Error creating pipes");
        exit(EXIT_FAILURE);
    }

    // Process 1
    if (fork() == 0) {
        close(pipe_12[0]);   
        close(pipe_to_4[0]); 
        close(pipe_to_4[1]); 

        dup2(pipe_12[1], STDOUT_FILENO);
        close(pipe_12[1]);

        execlp("cat", "cat", NULL);
        perror("execlp cat failed");
        exit(EXIT_FAILURE);
    }

    // Process 2
    if (fork() == 0) {
        close(pipe_12[1]);   
        close(pipe_to_4[0]); 

        dup2(pipe_12[0], STDIN_FILENO);
        close(pipe_12[0]);

        dup2(pipe_to_4[1], STDOUT_FILENO);
        close(pipe_to_4[1]);

        execlp("sort", "sort", NULL);
        perror("execlp sort failed");
        exit(EXIT_FAILURE);
    }

    // Process 3
    if (fork() == 0) {
        close(pipe_12[0]);    
        close(pipe_12[1]);    
        close(pipe_to_4[0]);  

        dup2(pipe_to_4[1], STDOUT_FILENO);
        close(pipe_to_4[1]);

        execlp("tr", "tr", "X", "0", NULL);
        perror("execlp tr failed");
        exit(EXIT_FAILURE);
    }

    // Process 4
    if (fork() == 0) {
        close(pipe_12[0]);    
        close(pipe_12[1]);    
        close(pipe_to_4[1]);  

        dup2(pipe_to_4[0], STDIN_FILENO);
        close(pipe_to_4[0]);

        execlp("awk", "awk", "length($0) > 10", NULL);
        perror("execlp awk failed");
        exit(EXIT_FAILURE);
    }

    // Parent Process
    close(pipe_12[0]);
    close(pipe_12[1]);
    close(pipe_to_4[0]);
    close(pipe_to_4[1]);

    for (int i = 0; i < 4; i++) {
        wait(NULL);
    }

    return 0;
}