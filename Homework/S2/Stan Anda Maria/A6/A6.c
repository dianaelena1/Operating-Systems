#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <fcntl.h>

int main() {
    int N;
    printf("Introdu N: ");
    if (scanf("%d", &N) != 1 || N < 2) {
        printf("N trebuie sa fie un numar >= 2.\n");
        return 1;
    }

    const char *filepath = "numere.dat";

    int fd = open(filepath, O_RDWR | O_CREAT | O_TRUNC, 0666);
    if (fd == -1) {
        perror("Eroare la deschiderea fisierului");
        exit(1);
    }

    for (int i = 1; i <= N; i++) {
        write(fd, &i, sizeof(int));
    }

    int *numbers = mmap(NULL, N * sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (numbers == MAP_FAILED) {
        perror("Eroare la mmap");
        exit(1);
    }

    for (int i = 2; i * i <= N; i++) {
        if (numbers[i - 1] != 0) {

            pid_t pid = fork();

            if (pid < 0) {
                perror("Eroare la fork");
                exit(1);
            }
            else if (pid == 0) {
                for (int j = i * i; j <= N; j += i) {
                    numbers[j - 1] = 0;
                }

                exit(0);
            }
        }
    }

    while (wait(NULL) > 0);

    printf("Numerele prime pana la %d sunt:\n", N);
    for (int i = 1; i < N; i++) {
        if (numbers[i] != 0) {
            printf("%d ", numbers[i]);
        }
    }
    printf("\n");

    munmap(numbers, N * sizeof(int));
    close(fd);

    unlink(filepath);

    return 0;
}