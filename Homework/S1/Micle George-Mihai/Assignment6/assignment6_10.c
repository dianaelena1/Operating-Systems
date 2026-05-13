#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/mman.h>

void remove_vowel(char *str, char vowel) {
    int i = 0, j = 0;
    while (str[i] != '\0') {
        if (str[i] != vowel && str[i] != (vowel - 32)) {
            str[j++] = str[i];
        }
        i++;
    }
    str[j] = '\0';
}

int main() {
    char vowels[] = {'a', 'e', 'i', 'o', 'u'};
    char initial_text[] = "Testez ACUM si atunci ";
    
    char *shared_array = mmap(NULL, 256, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    strcpy(shared_array, initial_text);

    for (int i = 0; i < 5; i++) {
        pid_t pid = fork();

        if (pid == 0) {
            remove_vowel(shared_array, vowels[i]);
            exit(0); 
        } else {
            wait(NULL);
        }
    }

    printf("Final: %s\n", shared_array);
    munmap(shared_array, 256);

    return 0;
}