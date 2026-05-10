    #include <stdio.h>
    #include <stdlib.h>
    #include <unistd.h>
    #include <sys/wait.h>
    #include <string.h>

    int main(int argc, char *argv[]) {
        if (argc != 2) {
            printf("Usage: ./p10 <username>\n");
            return 1;
        }

        int pipe_p2c[2];
        int pipe_c2p[2];

        if (pipe(pipe_p2c) == -1 || pipe(pipe_c2p) == -1) {
            perror("Failed to create pipes");
            return 1;
        }

        pid_t pid = fork();

        if (pid < 0) {
            perror("Fork failed");
            return 1;
        }

        if (pid == 0) {
            close(pipe_p2c[1]);
            close(pipe_c2p[0]);

            char username[256];

            read(pipe_p2c[0], username, sizeof(username));
            close(pipe_p2c[0]);

            char command[512];
            snprintf(command, sizeof(command), "ps -u %s --no-headers | wc -l", username);

            FILE *terminal = popen(command, "r");
            if (terminal == NULL) {
                perror("Failed to run command");
                exit(1);
            }

            int process_count = 0;
            fscanf(terminal, "%d", &process_count);
            pclose(terminal);

            write(pipe_c2p[1], &process_count, sizeof(process_count));
            close(pipe_c2p[1]);

            exit(0);

        } else {
            close(pipe_p2c[0]);
            close(pipe_c2p[1]);

            write(pipe_p2c[1], argv[1], strlen(argv[1]) + 1);
            close(pipe_p2c[1]);

            int final_answer;

            read(pipe_c2p[0], &final_answer, sizeof(final_answer));
            close(pipe_c2p[0]);

            printf("User '%s' is running %d processes.\n", argv[1], final_answer);

            wait(NULL);
        }

        return 0;
    }