#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX 1024

int main() {
    int p2c[2];
    int c2p[2];

    pipe(p2c);
    pipe(c2p);

    pid_t pid = fork();

    if (pid < 0) {
        perror("fork");
        exit(1);
    }

    if (pid == 0) {

        //Child
        close(p2c[1]);
        close(c2p[0]);

        char server[MAX];
        read(p2c[0], server, MAX);

        char command[MAX];

        snprintf(command, MAX,
                 "ssh %s \"who | awk '{print $1}' | sort -u\"",
                 server);

        FILE *fp = popen(command, "r");
        if (fp == NULL) {
            perror("popen");
            exit(1);
        }

        char buffer[MAX];

        while (fgets(buffer, MAX, fp) != NULL) {
            write(c2p[1], buffer, strlen(buffer));
        }

        pclose(fp);

        close(p2c[0]);
        close(c2p[1]);

        exit(0);
    } else {

        //Parent
        close(p2c[0]);
        close(c2p[1]);

        char server[MAX];

        printf("Give Unix server name: ");
        scanf("%s", server);

        write(p2c[1], server, strlen(server) + 1);

        close(p2c[1]);

        char buffer[MAX];
        int n;

        printf("Users currently logged on %s:\n", server);

        while ((n = read(c2p[0], buffer, MAX - 1)) > 0) {
            buffer[n] = '\0';
            printf("%s", buffer);
        }

        close(c2p[0]);

        wait(NULL);
    }

    return 0;
}