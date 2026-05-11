#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <sys/wait.h>

#define MAX_LINE 256

void child_printer(int read_fd, int process_id)
{
    char buffer[MAX_LINE];
    FILE *stream = fdopen(read_fd, "r");

    while (fgets(buffer, sizeof(buffer), stream) != NULL)
    {
        // Strip the trailing newline so formatting stays perfectly clean
        buffer[strcspn(buffer, "\n")] = '\0';

        // Print cleanly and forcefully flush the terminal buffer
        printf("[Process %d received]: %s\n", process_id, buffer);
        fflush(stdout);
    }
    fclose(stream);
    exit(0);
}

int main()
{
    int p12[2], p13[2], p14[2];

    if (pipe(p12) == -1 || pipe(p13) == -1 || pipe(p14) == -1)
    {
        perror("Pipe failed");
        exit(1);
    }

    if (fork() == 0)
    {
        close(p12[1]);
        close(p13[0]);
        close(p13[1]);
        close(p14[0]);
        close(p14[1]);
        child_printer(p12[0], 2);
    }

    if (fork() == 0)
    {
        close(p13[1]);
        close(p12[0]);
        close(p12[1]);
        close(p14[0]);
        close(p14[1]);
        child_printer(p13[0], 3);
    }

    if (fork() == 0)
    {
        close(p14[1]);
        close(p12[0]);
        close(p12[1]);
        close(p13[0]);
        close(p13[1]);
        child_printer(p14[0], 4);
    }

    // --- Process 1 (Parent) ---
    close(p12[0]);
    close(p13[0]);
    close(p14[0]);

    char buffer[MAX_LINE];

    printf("Enter lines. Press Ctrl+D to finish:\n");
    while (fgets(buffer, sizeof(buffer), stdin) != NULL)
    {
        // Ignore completely empty lines to prevent blank outputs
        if (strcmp(buffer, "\n") == 0)
        {
            continue;
        }

        if (isalpha(buffer[0]))
        {
            write(p12[1], buffer, strlen(buffer));
        }
        else if (isdigit(buffer[0]))
        {
            write(p13[1], buffer, strlen(buffer));
        }
        else
        {
            write(p14[1], buffer, strlen(buffer));
        }
    }

    close(p12[1]);
    close(p13[1]);
    close(p14[1]);

    while (wait(NULL) > 0)
        ;
    return 0;
}