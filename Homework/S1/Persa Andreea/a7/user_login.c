#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define BUFFER_SIZE 1024

int main() {
    int pipe1[2];
    int pipe2[2];
    pid_t pid;

    if (pipe(pipe1) == -1 || pipe(pipe2) == -1) {
        perror("Pipe failed");
        return 1;
    }

    pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        return 1;
    }

    if (pid > 0) {
        //parent process
        close(pipe1[0]);
        close(pipe2[1]);

        char username[50];
        printf("Enter username to search: ");
        scanf("%s", username);

        write(pipe1[1], username, strlen(username) + 1);
        close(pipe1[1]);

        printf("\nLogin dates for user %s:\n", username);
        char buffer[BUFFER_SIZE];
        ssize_t bytesRead;
        while ((bytesRead = read(pipe2[0], buffer, sizeof(buffer) - 1)) > 0) {
            buffer[bytesRead] = '\0';
            printf("%s", buffer);
        }

        close(pipe2[0]);
        wait(NULL);
    }
    else {
        //child process
        close(pipe1[1]);
        close(pipe2[0]);

        char receivedUser[50];
        read(pipe1[0], receivedUser, sizeof(receivedUser));
        close(pipe1[0]);

        dup2(pipe2[1], STDOUT_FILENO);
        close(pipe2[1]);

        execlp("last", "last", "-R", receivedUser, (char *)NULL);

        // If execlp fails
        perror("execlp failed");
        exit(1);
    }

    return 0;
}