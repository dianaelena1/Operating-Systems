#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int product(int v[], int st, int dr)
{
    if (st == dr)
        return v[st];

    int mid = (st + dr) / 2;

    int pipe1[2], pipe2[2];
    pipe(pipe1);
    pipe(pipe2);

    pid_t p1 = fork();

    if (p1 == 0)
    {
        close(pipe1[0]);

        int res = product(v, st, mid);

        write(pipe1[1], &res, sizeof(int));
        close(pipe1[1]);

        exit(0);
    }

    pid_t p2 = fork();

    if (p2 == 0)
    {
        close(pipe2[0]);

        int res = product(v, mid + 1, dr);

        write(pipe2[1], &res, sizeof(int));
        close(pipe2[1]);

        exit(0);
    }

    close(pipe1[1]);
    close(pipe2[1]);

    int x, y;

    read(pipe1[0], &x, sizeof(int));
    read(pipe2[0], &y, sizeof(int));

    close(pipe1[0]);
    close(pipe2[0]);

    wait(NULL);
    wait(NULL);

    return x * y;
}

int main()
{
    int v[] = {2, 3, 4, 5};
    int n = 4;

    int result = product(v, 0, n - 1);

    printf("Product = %d\n", result);

    return 0;
}