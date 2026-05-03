#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int compute(char op, int op1, int op2) {
    int fd[2];

    if (pipe(fd) == -1) {
        perror("Pipe failed");
        exit(1);
    }

    pid_t pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        exit(1);
    } else if (pid == 0) {
        close(fd[0]);

        int result = 0;
        if (op == '+') result = op1 + op2;
        else if (op == '-') result = op1 - op2;
        else if (op == '*') result = op1 * op2;
        else if (op == '/') {
            if (op2 == 0) {
                fprintf(stderr, "Error: Division by zero!\n");
                exit(1);
            }
            result = op1 / op2;
        }

        write(fd[1], &result, sizeof(result));
        close(fd[1]);
        exit(0);

    } else {
        close(fd[1]);

        int child_result;

        read(fd[0], &child_result, sizeof(child_result));
        close(fd[0]);

        wait(NULL);
        return child_result;
    }
}

int main(int argc, char *argv[]) {
    if (argc != 5) {
        printf("Usage: ./p8 a b c d\n");
        return 1;
    }


    int a = atoi(argv[1]);
    int b = atoi(argv[2]);
    int c = atoi(argv[3]);
    int d = atoi(argv[4]);



    int p1 = compute('*', b, c);
    int t1 = compute('+', a, p1);


    int p2 = compute('-', a, b);
    int p3 = compute('+', p2, d);
    int t2 = compute('-', p3, c);


    int left_side = compute('/', t1, t2);


    int m1 = compute('*', a, b);
    int m2 = compute('*', m1, c);
    int right_side = compute('*', m2, d);


    int final_result = compute('+', left_side, right_side);

    printf("The final result is: %d\n", final_result);

    return 0;
}