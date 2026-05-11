#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <syst/wait.h>


int main() {
    int p2c[2]; // Pipe for Parent -> Child communication
    int c2p[2]; // Pipe for Child -> Parent communication

    // Create the pipes
    if (pipe(p2c) == -1 || pipe(c2p) == -1) {
        perror("Error creating pipes");
        exit(EXIT_FAILURE);
    }

    // Fork to create the child process
    pid_t pid = fork();

    if (pid < 0) {
        perror("Error forking process");
        exit(EXIT_FAILURE);
    }

    if (pid > 0) { 
        close(p2c[0]); // Close the read end of p2c pipe
        close(c2p[1]); // Close the write end of c2p pipe

        char filename[256];
        printf("Parent: Enter a file name to check: ");
        if (fgets(filename, sizeof(filename), stdin) == NULL) {
            perror("Error reading input");
            close(p2c[1]);
            close(c2p[0]);
            wait(NULL);
            exit(EXIT_FAILURE);
        }

        // Remove trailing newline if present
        filename[strcspn(filename, "\n")] = 0;

        // Send the file name to the child
        if (write(p2c[1], filename, strlen(filename) + 1) == -1) {
            perror("Error writing to pipe");
        }
        close(p2c[1]); // Close write end after sending

        // Wait for the child to process and read the response
        char response[512];
        ssize_t bytes_read = read(c2p[0], response, sizeof(response) - 1);
        
        if (bytes_read > 0) {
            response[bytes_read] = '\0'; // Null-terminate the string
            printf("Parent: Received message from child -> %s\n", response);
        } else if (bytes_read == -1) {
            perror("Error reading from pipe");
        }
        
        close(c2p[0]); // Close read end after receiving
        wait(NULL);    // Wait for child to terminate to avoid zombie processes

    } else { 
        close(p2c[1]); // Close the write end of p2c pipe
        close(c2p[0]); // Close the read end of c2p pipe

        char filename[256];
        
        // Read the file name from the parent
        ssize_t bytes_read = read(p2c[0], filename, sizeof(filename) - 1);
        if (bytes_read > 0) {
            filename[bytes_read] = '\0'; // Ensure null-termination
        } else {
            // If read fails or EOF, exit
            close(p2c[0]);
            close(c2p[1]);
            exit(EXIT_FAILURE);
        }
        close(p2c[0]); // Close read end after receiving

        struct stat file_stat;
        char response[512];

        // Check file existence and type
        if (stat(filename, &file_stat) == -1) {
            strcpy(response, "Error: The file does not exist or cannot be accessed.");
        } else {
            // Determine the file type using POSIX macros
            if (S_ISREG(file_stat.st_mode)) {
                strcpy(response, "It is a Regular File.");
            } else if (S_ISDIR(file_stat.st_mode)) {
                strcpy(response, "It is a Directory.");
            } else if (S_ISCHR(file_stat.st_mode)) {
                strcpy(response, "It is a Character Device.");
            } else if (S_ISBLK(file_stat.st_mode)) {
                strcpy(response, "It is a Block Device.");
            } else if (S_ISFIFO(file_stat.st_mode)) {
                strcpy(response, "It is a FIFO/Pipe.");
            } else if (S_ISLNK(file_stat.st_mode)) {
                strcpy(response, "It is a Symbolic Link.");
            } else if (S_ISSOCK(file_stat.st_mode)) {
                strcpy(response, "It is a Socket.");
            } else {
                strcpy(response, "Unknown file type.");
            }
        }

        // Send the response message back to the parent
        write(c2p[1], response, strlen(response) + 1);
        close(c2p[1]); // Close write end after sending

        exit(EXIT_SUCCESS);
    }

    return 0;
}