#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/time.h>

int is_perfect(int n) {
    if (n < 2) return 0;
    int sum = 1;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            sum += i;
            if (i != n / i) sum += n / i;
        }
    }
    return sum == n;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s N\n", argv[0]);
        return 1;
    }

    int N = atoi(argv[1]);
    if (N <= 2) {
        printf("No perfect numbers below %d\n", N);
        return 0;
    }

    int procs = (int)sysconf(_SC_NPROCESSORS_ONLN);
    if (procs < 1) procs = 1;

    struct timeval start_time, end_time;
    gettimeofday(&start_time, NULL);

    int chunk = (N - 1) / procs + 1;

    for (int p = 0; p < procs; p++) {
        pid_t pid = fork();
        if (pid == 0) {
            int start = p * chunk + 2;
            int end = (p + 1) * chunk + 1;
            if (end > N) end = N;

            for (int i = start; i < end; i++) {
                if (is_perfect(i)) {
                    printf("%d\n", i);
                    fflush(stdout);
                }
            }
            exit(0);
        }
    }

    for (int p = 0; p < procs; p++) {
        wait(NULL);
    }

    gettimeofday(&end_time, NULL);

    double elapsed = (end_time.tv_sec - start_time.tv_sec) +
                     (end_time.tv_usec - start_time.tv_usec) / 1000000.0;

    printf("Processes used: %d\n", procs);
    printf("Time elapsed: %.6f seconds\n", elapsed);

    return 0;
}