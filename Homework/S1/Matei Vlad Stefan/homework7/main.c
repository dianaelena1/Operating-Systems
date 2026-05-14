#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>

int main() {
    int p2c[2]; 
    int c2p[2]; 

    pipe(p2c);
    pipe(c2p);
    
    pid_t pid = fork();


    if (pid == 0) {
        

        close(p2c[1]); 
        close(c2p[0]); 

        char filename[50];
        read(p2c[0], filename, sizeof(filename));

        struct stat st;
        char message[50];

        if (stat(filename, &st) == -1) {
            strcpy(message, "Error: File does not exist");
        } else {
            if (S_ISREG(st.st_mode))
                strcpy(message, "Regular file");
            else if (S_ISDIR(st.st_mode))
                strcpy(message, "Directory");
            else
                strcpy(message, "Other file type");
        }

        write(c2p[1], message, strlen(message) + 1);

        close(p2c[0]);
        close(c2p[1]);
    }
    else {

        close(p2c[0]); 
        close(c2p[1]); 

        char filename[50];

        printf("Enter file name: ");
        scanf("%s", filename);

        write(p2c[1], filename, strlen(filename) + 1);

        char response[50];
        read(c2p[0], response, sizeof(response));

        printf("Child says: %s\n", response);

        close(p2c[1]);
        close(c2p[0]);

        wait(NULL);
    }

    return 0;
}