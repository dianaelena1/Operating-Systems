#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <dirent.h>

#define FIFO_P2C "/tmp/fifo_parent_to_child"
#define FIFO_C2P "/tmp/fifo_child_to_parent"

int main() {
    // Create the FIFOs (Named Pipes) in the file system
    // 0666 gives read and write permissions
    if (mkfifo(FIFO_P2C, 0666) == -1) {
        perror("Error creating Parent-to-Child FIFO (may already exist)");
    }
    if (mkfifo(FIFO_C2P, 0666) == -1) {
        perror("Error creating Child-to-Parent FIFO (may already exist)");
    }

    // Fork to create the child process
    pid_t pid = fork();

    if (pid < 0) {
        perror("Error forking process");
        exit(EXIT_FAILURE);
    }

    if (pid > 0) { 
        char dirname[256];
        printf("Parent: Enter a directory name to scan: ");
        scanf("%255s", dirname);

        // Open the P2C FIFO for writing and send the directory name
        // open() will block until the child opens the other end for reading
        int fd_write = open(FIFO_P2C, O_WRONLY);
        write(fd_write, dirname, strlen(dirname) + 1);
        close(fd_write);

        // Open the C2P FIFO for reading and wait for the child's response
        int fd_read = open(FIFO_C2P, O_RDONLY);
        char response[4096]; // Large buffer to hold potentially long lists of files
        int bytes_read = read(fd_read, response, sizeof(response) - 1);
        
        if (bytes_read > 0) {
            response[bytes_read] = '\0';
            printf("\nMessage from Child\n%s\n", response);
        }
        
        close(fd_read);
        wait(NULL); // Wait for child to terminate

        // Remove the FIFO files from the filesystem
        unlink(FIFO_P2C);
        unlink(FIFO_C2P);

    } else { 
        char dirname[256];
        
        // Open the P2C FIFO for reading and get the directory name
        int fd_read = open(FIFO_P2C, O_RDONLY);
        read(fd_read, dirname, sizeof(dirname));
        close(fd_read);

        char response[4096] = ""; // Buffer to build our response message
        DIR *dir = opendir(dirname);

        // Check if directory exists and can be opened
        if (dir == NULL) {
            strcpy(response, "Error: The directory does not exist or cannot be accessed.");
        } else {
            struct dirent *entry;
            int found_files = 0;

            // Read through the directory entries
            while ((entry = readdir(dir)) != NULL) {
                // Check if it's a regular file (DT_REG)
                if (entry->d_type == DT_REG) {
                    // Check if the file ends with ".txt"
                    char *dot = strrchr(entry->d_name, '.');
                    if (dot && strcmp(dot, ".txt") == 0) {
                        strcat(response, entry->d_name);
                        strcat(response, "\n");
                        found_files = 1;
                    }
                }
            }
            closedir(dir);

            if (!found_files) {
                strcpy(response, "Directory exists, but no text files (.txt) were found.");
            }
        }

        // Open the C2P FIFO for writing and send the response back
        int fd_write = open(FIFO_C2P, O_WRONLY);
        write(fd_write, response, strlen(response) + 1);
        close(fd_write);

        exit(EXIT_SUCCESS);
    }

    return 0;
}