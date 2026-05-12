#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main() {
    int p12[2];   // Pipe from process 1 to 2
    int p_to_4[2]; // Pipe from process 2 & 3 to process 4
    
    if (pipe(p12) == -1 || pipe(p_to_4) == -1) {
        perror("Pipe failed");
        exit(1);
    }

    // p1 : Read from stdin, write to process 2
    if (fork() == 0) {
        close(p12[0]); 
        close(p_to_4[0]); 
        close(p_to_4[1]);
        
        char buf[1024];
        ssize_t n;
        while ((n = read(STDIN_FILENO, buf, sizeof(buf))) > 0) {
            write(p12[1], buf, n);
        }
        close(p12[1]);
        exit(0);
    }

    // p2: Read from p1, sort, write to p4
    if (fork() == 0) {
        close(p12[1]); 
        close(p_to_4[0]);
        
        dup2(p12[0], STDIN_FILENO);
        dup2(p_to_4[1], STDOUT_FILENO);
        close(p12[0]);
        close(p_to_4[1]);
        
        execlp("sort", "sort", NULL);
        perror("execlp sort");
        exit(1);
    }

    // p3 : Read from stdin, replace X to 0, write to process 4
    if (fork() == 0) {
        close(p12[0]); 
        close(p12[1]); 
        close(p_to_4[0]);
        
        char buf[1024];
        ssize_t n;

        while ((n = read(STDIN_FILENO, buf, sizeof(buf))) > 0) {
            for (ssize_t i = 0; i < n; i++) {
                if (buf[i] == 'X') buf[i] = '0';
            }
            write(p_to_4[1], buf, n);
        }
        close(p_to_4[1]);
        exit(0);
    }

    // p4 : Print only lines > 10 characters
    if (fork() == 0) {
        close(p12[0]); 
        close(p12[1]); 
        close(p_to_4[1]);
        
        FILE *stream = fdopen(p_to_4[0], "r");
        char *line = NULL;
        size_t len = 0;
        
        while (getline(&line, &len, stream) != -1) {
            // subtracting 1 to ignore '\n'
            if (strlen(line) - 1 > 10) {
                printf("%s", line);
            }
        }

        free(line);
        fclose(stream);
        exit(0);
    }

    // parent process : close all pipes and wait for children
    close(p12[0]); 
    close(p12[1]);
    close(p_to_4[0]); 
    close(p_to_4[1]);
    
    for (int i = 0; i < 4; i++) {
        wait(NULL);
    }

    return 0;
}