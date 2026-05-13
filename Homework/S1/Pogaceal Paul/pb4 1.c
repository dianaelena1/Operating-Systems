#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <sys/wait.h>

#define MAX_LINE 32 // 30 chars + newline + null terminator
#define MAX_LINES 1000

// Compare function for qsort
int compare_strings(const void *a, const void *b)
{
    return strcmp(*(const char **)a, *(const char **)b);
}

int main()
{
    int p12[2], p13[2], p_out[2];

    // Create pipes
    if (pipe(p12) == -1 || pipe(p13) == -1 || pipe(p_out) == -1)
    {
        perror("Pipe failed");
        exit(1);
    }

    // --- Process 2 ---
    if (fork() == 0)
    {
        close(p12[1]);
        close(p13[0]);
        close(p13[1]);
        close(p_out[0]);
        char buffer[MAX_LINE];
        int n;
        while ((n = read(p12[0], buffer, sizeof(buffer))) > 0)
        {
            for (int i = 0; i < n; i++)
            {
                if (isdigit(buffer[i]))
                    buffer[i] = '9';
            }
            write(p_out[1], buffer, n);
        }
        close(p12[0]);
        close(p_out[1]);
        exit(0);
    }

    // --- Process 3 ---
    if (fork() == 0)
    {
        close(p13[1]);
        close(p12[0]);
        close(p12[1]);
        close(p_out[0]);
        char buffer[MAX_LINE];
        int n;
        while ((n = read(p13[0], buffer, sizeof(buffer))) > 0)
        {
            for (int i = 0; i < n; i++)
            {
                if (isalpha(buffer[i]))
                    buffer[i] = 'G';
            }
            write(p_out[1], buffer, n);
        }
        close(p13[0]);
        close(p_out[1]);
        exit(0);
    }

    // --- Process 4 ---
    if (fork() == 0)
    {
        close(p12[0]);
        close(p12[1]);
        close(p13[0]);
        close(p13[1]);
        close(p_out[1]);

        char *lines[MAX_LINES];
        int line_count = 0;
        char buffer[MAX_LINE];

        // Read lines from pipe
        FILE *stream = fdopen(p_out[0], "r");
        while (fgets(buffer, sizeof(buffer), stream) != NULL && line_count < MAX_LINES)
        {
            lines[line_count] = strdup(buffer);
            line_count++;
        }
        fclose(stream);

        // Sort and print
        qsort(lines, line_count, sizeof(char *), compare_strings);
        printf("\n--- Sorted Output (Process 4) ---\n");
        for (int i = 0; i < line_count; i++)
        {
            printf("%s", lines[i]);
            free(lines[i]);
        }
        exit(0);
    }

    // --- Process 1 (Parent) ---
    close(p12[0]);
    close(p13[0]);
    close(p_out[0]);
    close(p_out[1]);

    char buffer[MAX_LINE];
    int turn = 0; // 0 for P2, 1 for P3

    printf("Enter lines (max 30 chars). Press Ctrl+D to finish:\n");
    while (fgets(buffer, sizeof(buffer), stdin) != NULL)
    {
        if (turn == 0)
        {
            write(p12[1], buffer, strlen(buffer));
        }
        else
        {
            write(p13[1], buffer, strlen(buffer));
        }
        turn = 1 - turn; // Alternate between 0 and 1
    }

    // Close write ends to signal EOF to children
    close(p12[1]);
    close(p13[1]);

    // Wait for all children
    while (wait(NULL) > 0)
        ;
    return 0;
}