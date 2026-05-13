#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/wait.h>
#define CHEIE_UNICA IPC_PRIVATE
#define CREAZA_SI_PERMITE_ACCES (IPC_CREAT | 0666)

int main() {
    int N = 31;

    int shmid = shmget(CHEIE_UNICA, N + 1, CREAZA_SI_PERMITE_ACCES);
    char *list = (char *)shmat(shmid, NULL, 0);

    for (int i = 0; i <= N; i++) list[i] = 1;
    list[0] = list[1] = 0;

    for (int i = 2; i * i <= N; i++) {
        if (list[i] == 1) {
            if (fork() == 0) {
                for (int j = i * i; j <= N; j += i) {
                    list[j] = 0;
                }
                exit(0);
            }
        }
    }

    while (wait(NULL) > 0);

    printf("Primes: ");
    for (int i = 2; i <= N; i++) {
        if (list[i] == 1) printf("%d ", i);
    }

    shmctl(shmid, IPC_RMID, NULL);
    return 0;
}