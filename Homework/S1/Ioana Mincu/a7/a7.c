#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int p1[2];
    int p2[2];
    char username[] = "root";

    if (pipe(p1) == -1 || pipe(p2) == -1) {
        perror("Pipe failed");
        return 1;
    }

    pid_t pid = fork();
    if (pid < 0) {
        perror("Fork failed");
        return 1;
    }

    if (pid == 0) {
        close(p1[1]);
        close(p2[0]);

        char buffer[100];
        read(p1[0], buffer, sizeof(buffer));
        close(p1[0]);

        char cmd[256];
        snprintf(cmd, sizeof(cmd), "ps -u %s | grep -v PID | wc -l", buffer);

        FILE *fp = popen(cmd, "r");
        int count = 0;
        if (fp != NULL) {
            if (fscanf(fp, "%d", &count) != 1) {
                count = 0;
            }
            pclose(fp);
        }

        write(p2[1], &count, sizeof(count));
        close(p2[1]);
        exit(0);
    } else {
        close(p1[0]);
        close(p2[1]);

        write(p1[1], username, strlen(username) + 1);
        close(p1[1]);

        int count;
        read(p2[0], &count, sizeof(count));
        close(p2[0]);

        printf("User '%s' has %d running processes.\n", username, count);

        wait(NULL);
    }

    return 0;
}