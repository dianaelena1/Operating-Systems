#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <ctype.h>

#define FIFO_NAME "/tmp/letter_stats_fifo"

typedef struct {
    char letter;
    int count;
} LetterRecord;

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    unlink(FIFO_NAME);
    if (mkfifo(FIFO_NAME, 0666) == -1) {
        perror("Failed to create FIFO");
        return 1;
    }

    for (int i = 0; i < 26; i++) {
        pid_t pid = fork();
        if (pid < 0) {
            perror("Fork failed");
            return 1;
        }

        if (pid == 0) {
            char target_letter = 'a' + i;
            int occurrences = 0;

            FILE *file = fopen(argv[1], "r");
            if (!file) {
                perror("Child failed to open file");
                exit(1);
            }

            int ch;
            while ((ch = fgetc(file)) != EOF) {
                if (tolower(ch) == target_letter) {
                    occurrences++;
                }
            }
            fclose(file);

            int fd = open(FIFO_NAME, O_WRONLY);
            if (fd == -1) {
                perror("Child failed to open FIFO");
                exit(1);
            }

            LetterRecord record;
            record.letter = target_letter;
            record.count = occurrences;

            write(fd, &record, sizeof(LetterRecord));
            close(fd);
            exit(0);
        }
    }

    int frequencies[26] = {0};
    int fd = open(FIFO_NAME, O_RDWR);
    if (fd == -1) {
        perror("Parent failed to open FIFO");
        return 1;
    }

    for (int i = 0; i < 26; i++) {
        LetterRecord record;
        read(fd, &record, sizeof(LetterRecord));
        frequencies[record.letter - 'a'] = record.count;
    }
    close(fd);
    unlink(FIFO_NAME);

    for (int i = 0; i < 26; i++) {
        wait(NULL);
    }

    printf("\n--- Alphabetical Letter Frequency ---\n");
    for (int i = 0; i < 26; i++) {
        printf("%c: %d\n", 'a' + i, frequencies[i]);
    }

    return 0;
}