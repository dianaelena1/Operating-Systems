#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <sys/wait.h>

int main() {
    int p12[2], p13[2];

    if (pipe(p12) == -1 || pipe(p13) == -1) {
        perror("Eroare la crearea pipe-urilor");
        return 1;
    }

    pid_t pid1 = fork();
    if (pid1 == 0) {
        close(p12[1]);
        close(p13[0]); close(p13[1]);

        char buf[31];
        int n;
        while ((n = read(p12[0], buf, 30)) > 0) {
            buf[n] = '\0';
            printf("Proces 2 - Cifre: %s\n", buf);
        }
        close(p12[0]);
        exit(0);
    }

    pid_t pid2 = fork();
    if (pid2 == 0) {
        close(p13[1]);
        close(p12[0]); close(p12[1]);

        char buf[31];
        int n;
        while ((n = read(p13[0], buf, 30)) > 0) {
            buf[n] = '\0';
            for(int i = 0; i < n; i++) buf[i] = toupper(buf[i]);
            printf("Proces 3 - LITERE: %s\n", buf);
        }
        close(p13[0]);
        exit(0);
    }

    close(p12[0]);
    close(p13[0]);

    char input[100];
    printf("Introdu linii de text (max 30 caractere). Scrie 'exit' pentru a opri:\n");

    while (1) {
        if (fgets(input, sizeof(input), stdin) == NULL) break;
        if (strncmp(input, "exit", 4) == 0) break;

        char digits[31] = "", letters[31] = "";
        int d_idx = 0, l_idx = 0;

        for (int i = 0; input[i] != '\0' && i < 30; i++) {
            if (isdigit(input[i])) digits[d_idx++] = input[i];
            else if (isalpha(input[i])) letters[l_idx++] = input[i];
        }

        if (d_idx > 0) write(p12[1], digits, d_idx);
        if (l_idx > 0) write(p13[1], letters, l_idx);
    }

    close(p12[1]);
    close(p13[1]);
    wait(NULL);
    wait(NULL);

    return 0;
}