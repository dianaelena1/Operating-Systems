#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <sys/wait.h>

#define FIFO_REQ "fifo_request"
#define FIFO_RES "fifo_response"

int main() {
    unlink(FIFO_REQ);
    unlink(FIFO_RES);

    if (mkfifo(FIFO_REQ, 0666) == -1 || mkfifo(FIFO_RES, 0666) == -1) {
        perror("Eroare la crearea FIFO-urilor");
        return 1;
    }

    pid_t pid = fork();

    if (pid < 0) {
        perror("Eroare la fork");
        return 1;
    }

    if (pid == 0) {
        int fd_req = open(FIFO_REQ, O_RDONLY);
        int fd_res = open(FIFO_RES, O_WRONLY);

        char filename[100];
        memset(filename, 0, 100);

        if (read(fd_req, filename, sizeof(filename)) > 0) {
            filename[strcspn(filename, "\n")] = 0;

            struct stat st;
            char message[100];
            memset(message, 0, 100);

            if (stat(filename, &st) == 0) {
                if (S_ISDIR(st.st_mode)) strcpy(message, "Este un DIRECTOR");
                else if (S_ISREG(st.st_mode)) strcpy(message, "Este un FISIER REGULAT");
                else strcpy(message, "Alt tip de fisier");
            } else {
                strcpy(message, "EROARE: Fisierul nu exista!");
            }

            write(fd_res, message, strlen(message) + 1);
        }

        close(fd_req);
        close(fd_res);
        exit(0);

    } else {
        char filename[100];
        printf("Introdu numele fisierului: ");
        if (fgets(filename, sizeof(filename), stdin) == NULL) return 1;

        filename[strcspn(filename, "\n")] = 0;

        int fd_req = open(FIFO_REQ, O_WRONLY);
        int fd_res = open(FIFO_RES, O_RDONLY);

        write(fd_req, filename, strlen(filename) + 1);

        char response[100];
        memset(response, 0, 100);

        if (read(fd_res, response, sizeof(response)) > 0) {
            printf("Rezultat de la copil: %s\n", response);
        } else {
            printf("Părintele nu a primit niciun răspuns.\n");
        }

        close(fd_req);
        close(fd_res);
        wait(NULL);

        unlink(FIFO_REQ);
        unlink(FIFO_RES);
    }

    return 0;
}