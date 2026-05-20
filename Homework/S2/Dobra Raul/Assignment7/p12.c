#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>
#include <sys/wait.h>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Utilizare: %s <nume_director>\n", argv[0]);
        return 1;
    }

    int p2c[2];
    int c2p[2];
    pipe(p2c);
    pipe(c2p);

    if (fork() == 0) {
        close(p2c[1]);
        close(c2p[0]);

        char dir_name[100];
        read(p2c[0], dir_name, sizeof(dir_name));
        close(p2c[0]);

        DIR *d = opendir(dir_name);
        if (d == NULL) {

            char msg[] = "Eroare: Directorul nu exista.\n";
            write(c2p[1], msg, strlen(msg) + 1);
        } else {
            struct dirent *entry;
            char lista[1000] = "";

            while ((entry = readdir(d)) != NULL) {
                char *ext = strrchr(entry->d_name, '.');
                if (ext != NULL && strcmp(ext, ".txt") == 0) {
                    strcat(lista, entry->d_name);
                    strcat(lista, "\n");
                }
            }
            closedir(d);

            if (strlen(lista) == 0) {
                strcpy(lista, "Nu s-au gasit fisiere .txt\n");
            }
            write(c2p[1], lista, strlen(lista) + 1);
        }

        close(c2p[1]);
        exit(0);
    }

    close(p2c[0]);
    close(c2p[1]);

    write(p2c[1], argv[1], strlen(argv[1]) + 1);
    close(p2c[1]);

    char raspuns[1000];
    read(c2p[0], raspuns, sizeof(raspuns));
    close(c2p[0]);

    printf("Rezultat primit de la fiu:\n%s", raspuns);

    wait(NULL);
    return 0;
}