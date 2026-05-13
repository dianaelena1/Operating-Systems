#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <ctype.h>
#include <sys/mman.h>

void count_letters(const char *text, char litera, int *results_array, int index) {
                     int count = 0;
                     for (int j = 0; text[j] != '\0'; j++) {
                         if (tolower(text[j]) == tolower(litera)) {
                             count++;
                         }
                     }
                     results_array[index] = count;
                 }

int main(){
    char text[1000];
    printf("Enter text: ");
    fgets(text, sizeof(text), stdin);

    int *results = mmap(NULL, 26 * sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);

    for (int i=0; i<26; i++){
        pid_t pid = fork();

        if (pid == 0){
            count_letters(text, 'a' + i, results, i);
            exit(0);
        }
    }

    for (int i=0;i<26;i++){
        wait(NULL);
    }

    printf("%-8s | %-10s\n", "Letter", "Frequency");
    printf("---------------------\n");
    for (int i=0;i<26;i++){
        if (results[i] > 0){
            printf("%-8c | %-10d\n", toupper('a'+i), results[i]);
        }
    }
    munmap(results, 26 * sizeof(int));
    return 0;
}