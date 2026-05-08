#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main() {
    int p2c[2]; 
    int c2p[2]; 

    if (pipe(p2c) == -1 || pipe(c2p) == -1) {
        perror("Pipe failed");
        return 1;
    }

    pid_t pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        return 1;
    }

    if (pid > 0) { 
        close(p2c[0]); 
        close(c2p[1]); 

        char server_name[] = "localhost";
        printf("[Parent] Sending server name: %s\n", server_name);
        
        write(p2c[1], server_name, strlen(server_name) + 1);
        close(p2c[1]);

        char buffer[4096];
        printf("[Parent] List of users received:\n");
        while (read(c2p[0], buffer, sizeof(buffer)) > 0) {
            printf("%s", buffer);
        }

        close(c2p[0]);
        wait(NULL);
    } else { 
        close(p2c[1]); 
        close(c2p[0]);

        char received_server[256];
        read(p2c[0], received_server, sizeof(received_server));
        close(p2c[0]);

        
        dup2(c2p[1], STDOUT_FILENO);
        
        execlp("who", "who", NULL);

        perror("exec failed");
        exit(1);
    }

    return 0;
}