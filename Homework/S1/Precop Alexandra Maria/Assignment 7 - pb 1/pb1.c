#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <sys/wait.h>
#include <string.h>

int main(void){
    int p12[2];
    int p13[2];

    if(pipe(p12) == -1 || pipe(p13) == -1){
        perror("Pipe error");
        exit(1);
    }

    pid_t pid2 = fork();

    if(pid2 == -1){
        perror("Fork error");
        exit(1);
    }

    if(pid2 == 0){
        close(p12[1]);
        close(p13[0]);
        close(p13[1]);

        char c;
        while(read(p12[0], &c, 1) >0){
            write(STDOUT_FILENO, &c, 1);
        }

        close(p12[0]);
        exit(0);
    }

    pid_t pid3 = fork();

    if(pid3 == -1){
        perror("Fork error");
        exit(1);
    }

    if(pid3 == 0){
        close(p13[1]);
        close(p12[0]);
        close(p12[1]);

        char c;
        while (read(p13[0], &c, 1) > 0) {
            c = toupper((unsigned char)c);
            write(STDOUT_FILENO, &c, 1);
        }

        close(p13[0]);
        exit(0);
    }

    close(p12[0]);
    close(p13[0]);

    char line[31];

    while (fgets(line, sizeof(line), stdin) != NULL) {
        for (int i = 0; line[i] != '\0'; i++) {
            if (isdigit((unsigned char)line[i])) {
                write(p12[1], &line[i], 1);
            } else if (isalpha((unsigned char)line[i])) {
                    write(p13[1], &line[i], 1);
                   }
        }

        if (strlen(line) == 30 && line[29] != '\n') {
            int ch;
            while ((ch = getchar()) != '\n' && ch != EOF);
        }
    }

    close(p12[1]);
    close(p13[1]);

    wait(NULL);
    wait(NULL);

    return 0;
}
