#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

int main() {
  mkfifo("p2c", 0666);
  mkfifo("c2p", 0666);

  int pid = fork();

  if (pid > 0) {
    char fileName[100];
    char answer[100];

    printf("File name: ");
    scanf("%s", fileName);

    int fd = open("p2c", O_WRONLY);
    write(fd, fileName, strlen(fileName) + 1);
    close(fd);

    fd = open("c2p", O_RDONLY);
    read(fd, answer, sizeof(answer));
    close(fd);

    printf("%s\n", answer);

    unlink("p2c");
    unlink("c2p");
  } else {
    char fileName[100];
    char answer[100];
    struct stat info;

    int fd = open("p2c", O_RDONLY);
    read(fd, fileName, sizeof(fileName));
    close(fd);

    if (stat(fileName, &info) == -1) {
      strcpy(answer, "file does not exist");
    } else {
      if (S_ISREG(info.st_mode)) {
        strcpy(answer, "regular file");
      } else {
        if (S_ISDIR(info.st_mode)) {
          strcpy(answer, "directory");
        } else {
          if (S_ISFIFO(info.st_mode)) {
            strcpy(answer, "fifo file");
          } else {
            strcpy(answer, "other file");
          }
        }
      }
    }

    fd = open("c2p", O_WRONLY);
    write(fd, answer, strlen(answer) + 1);
    close(fd);
  }

  return 0;
}
